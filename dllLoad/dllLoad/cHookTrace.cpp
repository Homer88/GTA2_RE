// cHookTrace.cpp - log of hooked function calls to hook_trace.log
#include <windows.h>
#include <stdio.h>
#include "cHookTrace.h"
#include "AddrToFunc.h"
#include "DebugLogFile.h"

static FILE* s_trace = NULL;
static unsigned long long s_seq = 0;

void TraceInit(void)
{
    s_seq = 0;
    if (s_trace != NULL) {
        return;
    }
    s_trace = fopen(GetLogPath("hook_trace.log"), "w");
    if (s_trace) {
        fprintf(s_trace, "GTA2 hook trace start\n");
        fflush(s_trace);
    }
}

void TraceEvent(const char* funcName)
{
    if (s_trace == NULL || funcName == NULL) {
        return;
    }
    s_seq++;
    fprintf(s_trace, "%6I64u  %s\n", s_seq, funcName);
    fflush(s_trace);
}

void TraceCall(const char* funcName, unsigned long fromAddr)
{
    if (s_trace == NULL || funcName == NULL) {
        return;
    }
    s_seq++;
    const char* fromName = GetFunctionNameAt(fromAddr);
    fprintf(s_trace, "%6I64u  %-48s <- called from 0x%08lX %s\n",
            s_seq, funcName, fromAddr, fromName ? fromName : "?");
    fflush(s_trace);
}

void TraceClose(void)
{
    if (s_trace) {
        fclose(s_trace);
        s_trace = NULL;
    }
}