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

// How many bytes of the Ped we want covered, and how the four debug
// registers are rotated across that range. Four 8-byte windows only cover
// 32 bytes at any instant, but the interesting S200/anim area is much larger,
// so the 32-byte window slides through the range over successive refreshes.
#define WATCH_SPAN      0x0C0   // 0x00..0xBF of the Ped
#define WATCH_STRIDE    0x20    // step of the sliding window (one full span)
#define WATCH_N_WINDOWS 4       // Dr0..Dr3

static const void* s_pedBase = NULL;
static HANDLE      s_vehToken = NULL;
static volatile LONG s_armed = 0;

// Offsets of the four windows, as a function of the current window phase.
static unsigned long s_winOff[WATCH_N_WINDOWS];
static volatile LONG s_winPhase = 0;

// Ring buffer of hits (written from the VEH handler, read by dump).
#define RING_CAP 512
typedef struct {
    unsigned long eip;        // address of the storing instruction
    unsigned long drNo;       // which debug reg fired (0..3)
    unsigned long off;        // exact byte offset inside the Ped that changed
    unsigned long newVal;     // value stored at that offset (after the write)
    unsigned long oldVal;     // value that was there before the write
    unsigned long width;      // how many consecutive bytes changed
    unsigned long tick;       // GetTickCount() at the moment of the write
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
// The written *value* is captured by diffing memory across the step: the
// 8 bytes of the fired window are snapshotted during the 1st #DB (the store
// has NOT been applied yet - x86 faulted with instruction restart) and read
// again in the 2nd #DB, once the store has retired. Comparing the two gives
// the exact byte offset that changed plus the value the game actually wrote,
// with no x86 instruction decoding.
// ---------------------------------------------------------------------------
#define EFLAG_TF 0x00000100UL

// Per-thread: which hardware register we disabled for the one-instruction step,
// plus the pre-write snapshot of its window and the faulting EIP.
static __declspec(thread) unsigned long s_tlsDisabledDr = 4;  // 0..3 or 4=none
static __declspec(thread) unsigned long s_tlsSnap[WATCH_SIZE];
static __declspec(thread) unsigned long s_tlsEip = 0;

// Local-enable bit for each register in DR7: L0=0x1, L1=0x4, L2=0x10, L3=0x40.
static unsigned long DrEnableBit(unsigned long drNo)
{
    return 1UL << (drNo * 2);
}

static void SnapWindow(unsigned long winOff)
{
    const unsigned char* p =
        (const unsigned char*)s_pedBase + winOff;
    int i;
    for (i = 0; i < WATCH_SIZE; i++) {
        s_tlsSnap[i] = p[i];
    }
}

// Pure diff of an 8-byte watch window across the trap-flag step. Kept free of
// Win32 and of any shared state so the unit test can drive it directly - the
// hardware watchpoint path itself needs a machine whose CPU actually delivers
// #DB, which is not every environment.
void S200DiffWindow(const unsigned char* before, const unsigned char* after,
                    unsigned long winOff, struct S200Diff* out)
{
    int i, first = -1, last = -1;
    int start, end, k;
    unsigned long val = 0, old = 0;

    for (i = 0; i < WATCH_SIZE; i++) {
        if (before[i] != after[i]) {
            if (first < 0) {
                first = i;
            }
            last = i;
        }
    }
    // Nothing changed: a read-only access that overlapped the window, or the
    // store was rolled back. Not a write event.
    if (first < 0) {
        out->changed = 0;
        out->off = winOff;
        out->width = 0;
        out->newVal = 0;
        out->oldVal = 0;
        return;
    }
    // Report the aligned 4-byte group the change belongs to, not the raw byte
    // range: that is the natural granularity of the game's Ped fields, and it
    // keeps a single byte store from being logged as a meaningless 1-byte write.
    start = first & ~3;
    end = last;
    if (end - start < 3) {
        end = start + 3;
    }
    if (end > WATCH_SIZE - 1) {
        end = WATCH_SIZE - 1;
    }
    for (k = start; k <= end; k++) {
        val |= (unsigned long)after[k] << (8 * (k - start));
        old |= (unsigned long)before[k] << (8 * (k - start));
    }
    out->changed = 1;
    out->off = winOff + (unsigned long)start;
    out->width = (unsigned long)(end - start + 1);
    out->newVal = val;
    out->oldVal = old;
}

// Read the window back, diff it against the snapshot and push one ring entry
// describing exactly what changed. Runs in the 2nd #DB, after the store.
static void RecordHit(unsigned long winOff)
{
    const unsigned char* p =
        (const unsigned char*)s_pedBase + winOff;
    unsigned char newBuf[WATCH_SIZE];
    S200Diff d;
    int i, slot, idx;
    S200Hit* h;

    for (i = 0; i < WATCH_SIZE; i++) {
        newBuf[i] = p[i];
    }
    S200DiffWindow((const unsigned char*)s_tlsSnap, newBuf, winOff, &d);
    if (!d.changed) {
        return;
    }
    slot = InterlockedIncrement(&s_ringWrite);
    idx = (slot - 1) % RING_CAP;
    h = &s_ring[idx];
    h->eip = s_tlsEip;
    h->drNo = s_tlsDisabledDr;
    h->off = d.off;
    h->newVal = d.newVal;
    h->oldVal = d.oldVal;
    h->width = d.width;
    h->tick = GetTickCount();
    h->seq = ++s_seqCounter;
}

static LONG WINAPI S200Veh(PEXCEPTION_POINTERS ep)
{
    CONTEXT* ctx;
    unsigned long dr6;
    unsigned long eip;
    unsigned long drNo;
    unsigned long winOff;

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
        if (drNo >= WATCH_N_WINDOWS) {
            return EXCEPTION_CONTINUE_SEARCH;
        }
        winOff = s_winOff[drNo];
        // Snapshot BEFORE the store retires - this is the "before" snapshot.
        __try {
            SnapWindow(winOff);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            s_tlsDisabledDr = 4;
            ctx->Dr6 = 0;
            return EXCEPTION_CONTINUE_SEARCH;
        }
        s_tlsEip = eip;
        s_tlsDisabledDr = drNo;
        ctx->Dr7 &= ~DrEnableBit(drNo); // disable Ln so restart won't re-trip
        ctx->Dr6 = 0;                   // clear B bits (sticky)
        ctx->EFlags |= EFLAG_TF;        // step exactly one instruction
        return EXCEPTION_CONTINUE_EXECUTION;
    }

    // --- Case 2: single-step #DB from our Trap Flag (write has landed). ----
    // The storing instruction has now retired, so memory holds the NEW value.
    // Diff it against the snapshot, record the change, then re-enable the
    // register and clear TF.
    if ((ctx->EFlags & EFLAG_TF) && s_tlsDisabledDr < WATCH_N_WINDOWS) {
        winOff = s_winOff[s_tlsDisabledDr];
        __try {
            RecordHit(winOff);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            // watched memory went away; do not take the process down
        }
        ctx->Dr7 |= DrEnableBit(s_tlsDisabledDr);
        s_tlsDisabledDr = WATCH_N_WINDOWS;
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
                ctx.Dr0 = base + s_winOff[0];
                ctx.Dr1 = base + s_winOff[1];
                ctx.Dr2 = base + s_winOff[2];
                ctx.Dr3 = base + s_winOff[3];
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

// Recompute the four window offsets for the current phase. The four 8-byte
// windows form one 0x20-byte band that slides through WATCH_SPAN in
// WATCH_STRIDE steps, so the whole span is covered over successive arms.
static void UpdateWindows(void)
{
    long base = (InterlockedIncrement(&s_winPhase) - 1) * WATCH_STRIDE;
    int i;
    for (i = 0; i < WATCH_N_WINDOWS; i++) {
        long off = base + i * WATCH_SIZE;
        long maxOff = WATCH_SPAN - WATCH_SIZE;
        if (off > maxOff) {
            off = maxOff;
        }
        if (off < 0) {
            off = 0;
        }
        s_winOff[i] = (unsigned long)off;
    }
}

void S200WatchSetTarget(const void* pedBase)
{
    // Re-arm when the ped moves to a new heap block, and periodically to catch
    // threads the game spawns after the first arm and to slide the watch band
    // forward (ArmThreads suspends every thread, so do it every few refreshes
    // rather than every one).
    int doArm;
    if (pedBase != s_pedBase) {
        s_pedBase = pedBase;
        doArm = 1;
    } else {
        doArm = (InterlockedIncrement(&s_armCounter) % 4) == 0;
    }
    if (pedBase != NULL && doArm) {
        UpdateWindows();
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

// Render one hit. Both the on-screen dump and the log file want the same
// "offset: old -> new, written by <fn>" shape.
static void FormatHit(char* buf, int cap, S200Hit* h, unsigned long tickBase)
{
    const char* fname = GetFunctionNameAt(h->eip ? h->eip - 1 : 0);
    _snprintf(buf, cap,
              "#%llu t+%lums off=0x%03X w=%lu 0x%08X->0x%08X EIP=0x%08X %s",
              h->seq, (unsigned long)(h->tick - tickBase), h->off, h->width,
              h->oldVal, h->newVal, h->eip, fname ? fname : "?");
}

static unsigned long FirstTick(void)
{
    LONG wr = s_ringWrite;
    if (wr <= 0) {
        return GetTickCount();
    }
    return s_ring[(wr - 1) % RING_CAP].tick;
}

static void S200WatchDumpRing(DumpBuf* b)
{
    LONG wr = s_ringWrite;
    LONG num = (wr > SHOW_N) ? SHOW_N : wr;
    unsigned long t0 = FirstTick();
    char line[256];
    LONG i;
    for (i = num - 1; i >= 0; i--) {
        S200Hit* h = &s_ring[(wr - num + i) % RING_CAP];
        FormatHit(line, sizeof(line), h, t0);
        DumpPrintf(b, "  %s\n", line);
    }
}

void S200WatchDump(DumpBuf* b)
{
    DumpPrintf(b, "-- S200 write-watch (Dr0..Dr3, %dB each, band 0x%03X..0x%03X, ped 0x%08X):\n",
               WATCH_SIZE, s_winOff[0], s_winOff[3] + WATCH_SIZE - 1,
               (unsigned long)(ULONG_PTR)s_pedBase);
    if (!s_armed) {
        DumpPrintf(b, "   (not armed)\n");
        return;
    }
    if (s_ringWrite == s_ringRead) {
        DumpPrintf(b, "   (no writes recorded)\n");
        return;
    }
    S200WatchDumpRing(b);
}

void S200WatchFlushToFile(void)
{
    FILE* f;
    LONG wr = s_ringWrite;
    LONG from = s_ringRead;
    LONG i;
    unsigned long t0;
    char line[256];
    LONG lost = 0;

    if (wr <= from) {
        return;
    }
    // The ring holds RING_CAP entries; if more arrived since the last flush the
    // oldest ones were overwritten and must be reported as lost rather than
    // silently written out under wrong sequence numbers.
    if (wr - from > RING_CAP) {
        lost = (wr - from) - RING_CAP;
        from = wr - RING_CAP;
    }
    f = fopen(GetLogPath("S200Write.log"), "a");
    if (f == NULL) {
        return;
    }
    t0 = s_ring[from % RING_CAP].tick;
    if (lost > 0) {
        fprintf(f, "... %ld hit(s) lost, ring wrapped ...\n", lost);
    }
    for (i = from; i < wr; i++) {
        S200Hit* h = &s_ring[i % RING_CAP];
        FormatHit(line, sizeof(line), h, t0);
        fprintf(f, "%s\n", line);
    }
    fclose(f);
    // Advance the read cursor instead of rewinding the write counter: the VEH
    // may be appending right now, and zeroing s_ringWrite would collide with
    // its InterlockedIncrement and renumber every later hit.
    InterlockedExchange(&s_ringRead, wr);
}
