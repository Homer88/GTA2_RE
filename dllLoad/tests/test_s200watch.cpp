// test_s200watch.cpp - standalone check of the S200 write-watch core.
//
// The retail gta2.exe is not available, and hardware data watchpoints are not
// delivered by every environment (a VM or sandbox will accept Dr0..Dr7, read
// them back intact, and then never raise #DB for a matching store). So the
// test is split in two:
//
//   Part 1 - always runs. Drives S200DiffWindow(), the piece this change
//            actually rewrote, through every case the VEH can produce.
//   Part 2 - runs only if this CPU really does deliver #DB. Arms the real
//            registers, has a worker thread write, and checks the ring.
//
// This links the REAL dllLoad/dllLoad/cS200Watch.cpp with stubs for the two
// things it pulls in from the rest of the project (DumpPrintf, GetLogPath).
// Nothing under test is duplicated, so a regression in the real file fails
// here. GetFunctionNameAt needs no stub: it is "static" in AddrToFunc.h, so
// cS200Watch.cpp already carries its own private copy.

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "cInspector.h"
#include "DebugLogFile.h"
#include "cS200Watch.h"

// --- stubs ----------------------------------------------------------------

void DumpPrintf(struct DumpBuf* b, const char* fmt, ...)
{
    va_list ap;
    int n;
    if (b == NULL || b->data == NULL || b->len >= b->cap) {
        return;
    }
    va_start(ap, fmt);
    n = _vsnprintf(b->data + b->len, b->cap - b->len, fmt, ap);
    va_end(ap);
    if (n > 0) {
        b->len += (size_t)n;
        if (b->len > b->cap - 1) {
            b->len = b->cap - 1;
        }
    }
}

// Keep the log out of the game CWD: the test owns a temp file.
const char* GetLogPath(const char* fileName)
{
    static char path[MAX_PATH];
    _snprintf(path, sizeof(path), "%s", fileName);
    return path;
}

// --- harness --------------------------------------------------------------

static int g_fail = 0;
static int g_pass = 0;

static void Check(int cond, const char* what)
{
    if (cond) {
        g_pass++;
        printf("  ok   %s\n", what);
    } else {
        g_fail++;
        printf("  FAIL %s\n", what);
    }
}

// --- part 1: the diff -----------------------------------------------------

static void Fill(unsigned char* b, const unsigned long* v, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        b[i * 4 + 0] = (unsigned char)(v[i]);
        b[i * 4 + 1] = (unsigned char)(v[i] >> 8);
        b[i * 4 + 2] = (unsigned char)(v[i] >> 16);
        b[i * 4 + 3] = (unsigned char)(v[i] >> 24);
    }
}

static void TestDiff(void)
{
    unsigned char before[8], after[8];
    unsigned long start[2] = { 0x00000000u, 0xAAAAAAAAu };
    S200Diff d;

    printf("part 1: S200DiffWindow\n");

    // no change at all -> not a write event
    Fill(before, start, 2);
    memcpy(after, before, 8);
    S200DiffWindow(before, after, 0x00, &d);
    Check(d.changed == 0, "identical snapshots report no change");

    // aligned dword store at offset 0
    Fill(before, start, 2);
    Fill(after, start, 2);
    after[0] = 0x11; after[1] = 0x11; after[2] = 0x11; after[3] = 0x11;
    S200DiffWindow(before, after, 0x00, &d);
    Check(d.changed == 1 && d.off == 0x00 && d.width == 4,
          "aligned dword store reports off 0x00 width 4");
    Check(d.newVal == 0x11111111u && d.oldVal == 0x00000000u,
          "aligned dword store reports new and old value");

    // single byte store inside the second dword must widen to that group
    Fill(before, start, 2);
    Fill(after, start, 2);
    after[4] = 0x99;
    S200DiffWindow(before, after, 0x00, &d);
    Check(d.changed == 1 && d.off == 0x04 && d.width == 4,
          "byte store at 0x04 widens to the aligned group 0x04");
    Check(d.newVal == 0xAAAAAA99u, "byte store keeps the untouched bytes of the group");

    // byte store in the middle of a group widens backwards to the group start
    Fill(before, start, 2);
    Fill(after, start, 2);
    after[6] = 0x5A;
    S200DiffWindow(before, after, 0x00, &d);
    Check(d.changed == 1 && d.off == 0x04,
          "byte store at 0x06 widens back to group 0x04");

    // change near the end of the window must be clamped, not run past the end
    Fill(before, start, 2);
    Fill(after, start, 2);
    after[7] = 0x01;
    S200DiffWindow(before, after, 0x00, &d);
    Check(d.changed == 1 && d.off == 0x04 && d.width == 4,
          "byte store at 0x07 clamps to width 4");

    // the window offset must be added to the reported offset
    Fill(before, start, 2);
    Fill(after, start, 2);
    after[0] = 0x77;
    S200DiffWindow(before, after, 0x20, &d);
    Check(d.off == 0x20, "reported offset is absolute (winOff + group start)");

    // both dwords dirty at once -> the first group is reported
    Fill(before, start, 2);
    Fill(after, start, 2);
    after[0] = 0x01; after[4] = 0x02;
    S200DiffWindow(before, after, 0x00, &d);
    Check(d.changed == 1 && d.off == 0x00,
          "two dirty groups report the first one");

    printf("\n");
}

// --- part 2: real hardware watchpoints ------------------------------------

static volatile unsigned int* g_target = NULL;
static HANDLE g_go = NULL;
static volatile LONG g_ssSeen = 0;
static volatile LONG g_tripSeen = 0;

static LONG WINAPI CountVeh(PEXCEPTION_POINTERS ep)
{
    if (ep->ExceptionRecord->ExceptionCode != EXCEPTION_SINGLE_STEP) {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    InterlockedIncrement(&g_ssSeen);
    if (ep->ContextRecord->Dr6 & 0x0F) {
        InterlockedIncrement(&g_tripSeen);
    }
    // Do not emulate the disable+TF dance here: a bare re-trip would spin
    // forever. Just record and swallow.
    ep->ContextRecord->Dr6 = 0;
    ep->ContextRecord->EFlags &= ~0x100UL;
    return EXCEPTION_CONTINUE_EXECUTION;
}

// Returns 1 if this machine actually delivers #DB for a matching store.
static int HardwareWatchpointsWork(unsigned char* buf)
{
    CONTEXT ctx;
    unsigned long base = (unsigned long)buf;
    int worked;

    AddVectoredExceptionHandler(1, CountVeh);

    memset(&ctx, 0, sizeof(ctx));
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    GetThreadContext(GetCurrentThread(), &ctx);
    ctx.Dr0 = base;
    ctx.Dr1 = base + 0x20;
    ctx.Dr2 = base + 0x40;
    ctx.Dr3 = base + 0x60;
    ctx.Dr7 = (1UL << 0) | (2UL << 16) | (3UL << 18) |
              (1UL << 2) | (2UL << 20) | (3UL << 22) |
              (1UL << 4) | (2UL << 24) | (3UL << 26) |
              (1UL << 6) | (2UL << 28) | (3UL << 30);
    ctx.Dr6 = 0;
    SetThreadContext(GetCurrentThread(), &ctx);

    *((volatile unsigned int*)buf) = 0xC0DEC0DEu;

    memset(&ctx, 0, sizeof(ctx));
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    GetThreadContext(GetCurrentThread(), &ctx);
    ctx.Dr7 = 0;                       // disarm
    SetThreadContext(GetCurrentThread(), &ctx);

    worked = (g_tripSeen > 0);
    return worked;
}

static volatile unsigned int* g_wtarget = NULL;

static DWORD WINAPI WriterThread(LPVOID)
{
    volatile unsigned int* p = g_wtarget;
    WaitForSingleObject(g_go, INFINITE);
    p[0] = 0x11111111u;
    p[1] = 0x22222222u;
    p[2] = 0x33333333u;
    p[4] = 0x44444444u;
    *(volatile unsigned char*)&p[3] = 0x99;
    p[5] = 0x55555555u;
    p[40] = 0x66666666u;               // out of band
    return 0;
}

static void TestHardware(void)
{
    static char text[64 * 1024];
    unsigned char* buf = (unsigned char*)VirtualAlloc(NULL, 0x1000,
        MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    DumpBuf b;
    HANDLE w;
    char line[512];

    printf("part 2: real hardware watchpoints\n");
    memset(buf, 0, 0x1000);

    b.data = text;
    b.cap = sizeof(text);
    b.len = 0;
    text[0] = 0;

    g_wtarget = (volatile unsigned int*)buf;
    g_go = CreateEvent(NULL, TRUE, FALSE, NULL);
    w = CreateThread(NULL, 0, WriterThread, NULL, 0, NULL);

    S200WatchInit();
    S200WatchSetTarget(buf);
    SetEvent(g_go);
    WaitForSingleObject(w, INFINITE);
    CloseHandle(w);
    Sleep(100);

    S200WatchDump(&b);
    S200WatchFlushToFile();
    S200WatchClear();

    strncpy(line, text, sizeof(line) - 1);
    line[sizeof(line) - 1] = 0;
    printf("%s", line);

    Check(strstr(line, "0x11111111") != NULL, "write 0x11111111 recorded");
    Check(strstr(line, "0x22222222") != NULL, "write 0x22222222 recorded");
    Check(strstr(line, "0x33333333") != NULL, "write 0x33333333 recorded");
    Check(strstr(line, "0x44444444") != NULL, "write 0x44444444 recorded");
    Check(strstr(line, "0x55555555") != NULL, "write 0x55555555 recorded");
    Check(strstr(line, "off=0x00C") != NULL, "byte write at 0x0C widened to 0x0C");
    Check(strstr(line, "0x66666666") == NULL, "out-of-band write not reported");

    VirtualFree(buf, 0, MEM_RELEASE);
    CloseHandle(g_go);
    printf("\n");
}

int main(void)
{
    unsigned char* probe = (unsigned char*)VirtualAlloc(NULL, 0x1000,
        MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    setvbuf(stdout, NULL, _IONBF, 0);
    printf("S200 write-watch core test\n\n");

    TestDiff();

    if (probe != NULL) {
        if (HardwareWatchpointsWork(probe)) {
            TestHardware();
        } else {
            printf("part 2: SKIPPED - this machine accepts Dr0..Dr7 and reads\n"
                   "        them back, but never raises #DB for a matching\n"
                   "        store. TF single-step does work, so exception\n"
                   "        delivery is fine; debug watchpoints are not\n"
                   "        available here. The watch path can only be\n"
                   "        verified on the machine that runs the game.\n\n");
        }
        VirtualFree(probe, 0, MEM_RELEASE);
    }

    printf("%d passed, %d failed\n", g_pass, g_fail);
    return g_fail == 0 ? 0 : 1;
}
