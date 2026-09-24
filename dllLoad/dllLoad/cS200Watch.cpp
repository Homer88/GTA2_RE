// cS200Watch.cpp - hardware write-watch on the Ped S200 block.
//
// Windows debug registers let us watch for WRITES to a 1/2/4/8-byte window.
// The S200 block is 300 bytes, we arm four watchpoints at fixed offsets so
// writes anywhere in the block land in one of the watched windows. The VEH
// handler catches EXCEPTION_SINGLE_STEP (debug watchpoint), records EIP (the
// instruction that caused the write) + the written bytes, and continues.
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <tlhelp32.h>
#include "cS200Watch.h"
#include "cInspector.h"   // DumpBuf / DumpPrintf
#include "AddrToFunc.h"
#include "DebugLogFile.h"

#ifndef EXCEPTION_SINGLE_STEP
#define EXCEPTION_SINGLE_STEP 0x80000004
#endif

// Window size in bytes each debug register watches (1/2/4/8).
#define WATCH_SIZE 8

// Offsets inside the S200 block (relative to Ped base). The live records we
// have seen are the first 12 (0..11) = bytes 0x00..0x23, so watch that
// region contiguously with the four 8-byte windows: 0x00, 0x08, 0x10, 0x18.
#define WATCH_0_OFF 0x000
#define WATCH_1_OFF 0x008
#define WATCH_2_OFF 0x010
#define WATCH_3_OFF 0x018

static const void* s_pedBase = NULL;
static HANDLE      s_vehToken = NULL;
static volatile LONG s_armed = 0;

// Ring buffer of hits (written from the VEH handler, read by dump).
#define RING_CAP 512
typedef struct {
    unsigned long eip;
    unsigned long drNo;       // which debug reg fired (0..3)
    unsigned long addr;       // exact address that was written (approx)
    unsigned long value;      // dword value written (approx)
    unsigned long pcShown;    // EIP value, also shown
    unsigned long long seq;
} S200Hit;

static S200Hit        s_ring[RING_CAP];
static volatile LONG  s_ringWrite = 0;
static volatile LONG  s_ringRead = 0;
static unsigned long long s_seqCounter = 0;

// ---------------------------------------------------------------------------
// #DB handling for the write watchpoints.
//
// A hardware data*write* breakpoint is reported by x86 as a fault with
// *instruction restart*: the CPU rolls back and re-runs the storing
// instruction. While the watchpoint stays enabled in DR7 that restart trips
// the same breakpoint again -> infinite #DB loop (game freezes, makes no
// progress). The correct dance is:
//
//   1st #DB (Dr6 has B0..B3):  record EIP/window index, DISABLE the fired
//                              register (clear its Ln bit in DR7), set
//                              EFLAGS.TF, clear Dr6, continue. The restarted
//                              write instruction now completes once.
//   2nd #DB (TF single-step):  the write has landed. Re-enable the register in
//                              DR7 (drNo comes from the Dr7 bits), clear TF
//                              and Dr6, continue.
//
// The written *value* is not read in the handler at all: ring entries store
// the window offset (via drNo) and the dump/flush paths read the final value
// from memory afterwards. That keeps the VEH tiny, reentrant and race-free.
// ---------------------------------------------------------------------------
#define EFLAG_TF 0x00000100UL

static unsigned long WatchOffForDr(unsigned long drNo)
{
    switch (drNo) {
    case 0: return WATCH_0_OFF;
    case 1: return WATCH_1_OFF;
    case 2: return WATCH_2_OFF;
    default: return WATCH_3_OFF;
    }
}

// Local-enable bit for each register in DR7: L0=0x1, L1=0x4, L2=0x10, L3=0x40.
static unsigned long DrEnableBit(unsigned long drNo)
{
    return 1UL << (drNo * 2);
}

static void RecordHit(unsigned long eip, unsigned long drNo)
{
    int slot = InterlockedIncrement(&s_ringWrite);
    int idx = (slot - 1) % RING_CAP;
    S200Hit* h = &s_ring[idx];
    h->eip = eip;
    h->drNo = drNo;
    h->addr = (unsigned long)(ULONG_PTR)s_pedBase + WatchOffForDr(drNo);
    h->value = 0;   // filled lazily at dump time (write has landed by then)
    h->pcShown = eip;
    h->seq = ++s_seqCounter;
}

// Per-thread: which hardware register we disabled for the one-instruction step.
static __declspec(thread) unsigned long s_tlsDisabledDr = 4;  // 0..3 or 4=none

static LONG WINAPI S200Veh(PEXCEPTION_POINTERS ep)
{
    CONTEXT* ctx;
    unsigned long dr6;
    unsigned long eip;
    unsigned long drNo;

    if (ep == NULL || ep->ExceptionRecord == NULL || ep->ContextRecord == NULL) {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    // Windows reports debug watchpoint / single-step breakpoints as
    // EXCEPTION_SINGLE_STEP.
    if (ep->ExceptionRecord->ExceptionCode != EXCEPTION_SINGLE_STEP) {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    if (s_pedBase == NULL) {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    ctx = ep->ContextRecord;
    dr6 = ctx->Dr6;
    eip = ctx->Eip;

    // --- Case 1: hardware watchpoint fired (Dr6 bits B0..B3). --------------
    // x86 reports a write watchpoint as a fault and *restarts* the storing
    // instruction. If the register stays enabled in DR7 the restart re-trips
    // the same watchpoint forever -> game freezes. So: disable the register,
    // set TF, let the instruction complete exactly once.
    if (dr6 & 0x0F) {
        drNo = (dr6 & 1) ? 0 : (dr6 & 2) ? 1 : (dr6 & 4) ? 2 : 3;
        RecordHit(eip, drNo);
        s_tlsDisabledDr = drNo;
        ctx->Dr7 &= ~DrEnableBit(drNo); // disable Ln so restart won't re-trip
        ctx->Dr6 = 0;                   // clear B bits (sticky)
        ctx->EFlags |= EFLAG_TF;        // step exactly one instruction
        return EXCEPTION_CONTINUE_EXECUTION;
    }

    // --- Case 2: single-step #DB from our Trap Flag (write has landed). ----
    // Re-enable the register we disabled in Case 1, then clear TF.
    if ((ctx->EFlags & EFLAG_TF) && s_tlsDisabledDr < 4) {
        ctx->Dr7 |= DrEnableBit(s_tlsDisabledDr);
        s_tlsDisabledDr = 4;
        ctx->Dr6 = 0;
        ctx->EFlags &= ~EFLAG_TF;
        return EXCEPTION_CONTINUE_EXECUTION;
    }

    // Not ours (someone else's single-step); let other handlers/debugger see.
    return EXCEPTION_CONTINUE_SEARCH;
}

// Enumerate all threads of this process and arm Dr's for the watched offsets.
static void ArmThreads(void)
{
    DWORD pid = GetCurrentProcessId();
    HANDLE snap;
    THREADENTRY32 te;
    int w = 0;

    if (s_pedBase == NULL) {
        return;
    }
    snap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (snap == INVALID_HANDLE_VALUE) {
        return;
    }
    te.dwSize = sizeof(te);
    if (Thread32First(snap, &te)) {
        unsigned long me = GetCurrentThreadId();
        do {
            HANDLE hThread;
            CONTEXT ctx;
            if (te.th32OwnerProcessID != pid) {
                continue;
            }
            // Never suspend the thread that is itself doing the arming
            // (the inspector thread) -- that would deadlock the window.
            if (te.th32ThreadID == me) {
                continue;
            }
            hThread = OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT |
                                 THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
            if (hThread == NULL) {
                continue;
            }
            if (SuspendThread(hThread) == (DWORD)-1) {
                CloseHandle(hThread);
                continue;
            }
            memset(&ctx, 0, sizeof(ctx));
            ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
            if (GetThreadContext(hThread, &ctx)) {
                unsigned long base = (unsigned long)(ULONG_PTR)s_pedBase;
                ctx.Dr0 = base + WATCH_0_OFF;
                ctx.Dr1 = base + WATCH_1_OFF;
                ctx.Dr2 = base + WATCH_2_OFF;
                ctx.Dr3 = base + WATCH_3_OFF;
                // L0/L1/L2/L3 local enable + write-watch (R/W=10) + 8-byte len.
                // Dr7 bits: L0=0, L1=2, L2=4, L3=6; RW0..3 at 16/20/24/28.
                ctx.Dr7 = (1UL << 0) | ((2UL) << 16) | (3UL << 18) |   // Dr0 write 8
                          (1UL << 2) | ((2UL) << 20) | (3UL << 22) |   // Dr1 write 8
                          (1UL << 4) | ((2UL) << 24) | (3UL << 26) |   // Dr2 write 8
                          (1UL << 6) | ((2UL) << 28) | (3UL << 30);     // Dr3 write 8
                ctx.Dr6 = 0;
                SetThreadContext(hThread, &ctx);
                w++;
            }
            ResumeThread(hThread);
            CloseHandle(hThread);
        } while (Thread32Next(snap, &te));
    }
    CloseHandle(snap);
    (void)w;
}

void S200WatchInit(void)
{
    if (s_vehToken == NULL) {
        s_vehToken = AddVectoredExceptionHandler(1, S200Veh);
    }
}

static volatile LONG s_armCounter = 0;

void S200WatchSetTarget(const void* pedBase)
{
    // Re-arm when the ped moves to a new heap block, and every 30 refreshes
    // (cosmetic) to catch threads the game spawns after the first arm, without
    // suspending every thread each second.
    int doArm;
    if (pedBase != s_pedBase) {
        s_pedBase = pedBase;
        doArm = 1;
    } else {
        doArm = (InterlockedIncrement(&s_armCounter) % 30) == 0;
    }
    if (pedBase != NULL && doArm) {
        ArmThreads();
        InterlockedExchange(&s_armed, 1);
    } else if (pedBase == NULL) {
        InterlockedExchange(&s_armed, 0);
    }
}

void S200WatchClear(void)
{
    s_pedBase = NULL;
    InterlockedExchange(&s_armed, 0);
    // note: we do not re-arm Dr's to zero on running threads; harmless.
}

#define SHOW_N 40
static void S200FillHitValue(S200Hit* h)
{
    // The write has landed by the time we dump/flush; grab the dword at the
    // watched window so the log carries the actual written value.
    if (h->value != 0 || s_pedBase == NULL) {
        return;
    }
    __try {
        const unsigned char* p = (const unsigned char*)s_pedBase + WatchOffForDr(h->drNo);
        h->value = p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        h->value = 0;
    }
}

static void S200WatchDumpRing(DumpBuf* b)
{
    LONG wr = s_ringWrite;
    LONG num = (wr > SHOW_N) ? SHOW_N : wr;
    LONG i;
    for (i = num - 1; i >= 0; i--) {
        S200Hit* h = &s_ring[(wr - num + i) % RING_CAP];
        const char* fname = GetFunctionNameAt(h->eip ? h->eip - 1 : 0);
        const char* fname2 = GetFunctionNameAt(h->eip);
        S200FillHitValue(h);
        DumpPrintf(b, "  #%llu  EIP=0x%08X [%s] (next=0x%08X [%s])  dr=%lu dword@off=0x%08X\n",
                   h->seq, h->pcShown, fname ? fname : "?",
                   h->pcShown + 1, fname2 ? fname2 : "?", h->drNo, h->value);
    }
}

void S200WatchDump(DumpBuf* b)
{
    DumpPrintf(b, "-- S200 write-watch (Dr0..Dr3, size %d, ped 0x%08X):\n",
               WATCH_SIZE, (unsigned long)(ULONG_PTR)s_pedBase);
    if (!s_armed) {
        DumpPrintf(b, "   (not armed)\n");
        return;
    }
    S200WatchDumpRing(b);
}

void S200WatchFlushToFile(void)
{
    FILE* f;
    LONG wr = s_ringWrite;
    LONG i;

    if (wr <= 0) {
        return;
    }
    f = fopen(GetLogPath("S200Write.log"), "a");
    if (f == NULL) {
        return;
    }
    for (i = 0; i < wr; i++) {
        S200Hit* h = &s_ring[i % RING_CAP];
        const char* fname = GetFunctionNameAt(h->eip ? h->eip - 1 : 0);
        S200FillHitValue(h);
        fprintf(f, "%llu EIP=0x%08X %-40s dr=%lu dword00=0x%08X\n",
                h->seq, h->pcShown, fname ? fname : "?", h->drNo, h->value);
    }
    fclose(f);
    // reset counter only for already-flushed entries (crude: reset all).
    InterlockedExchange(&s_ringWrite, 0);
}