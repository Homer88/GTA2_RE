// cHookTrace.cpp - log of hooked function calls:
//   callGen.log            common log for every call
//   call_<Class>.log       per-class log (class part before "::" in funcName)
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "cHookTrace.h"
#include "AddrToFunc.h"
#include "DebugLogFile.h"

static FILE* s_trace = NULL;
static unsigned long long s_seq = 0;

// Small cache of already-open per-class files so we do not reopen on every call.
#define CALL_CLASS_CACHE 32
static FILE* s_classFiles[CALL_CLASS_CACHE];
static char s_classNames[CALL_CLASS_CACHE][64];
static int s_classCount = 0;

// Extract the class name from "Class::Func @0x..." -> "Class".
// Returns 0 when there is no "::" scope separator.
static BOOL ExtractClassName(const char* funcName, char* out, int outSize)
{
    const char* sep;
    int n;
    if (funcName == NULL) {
        return FALSE;
    }
    sep = strstr(funcName, "::");
    if (sep == NULL) {
        return FALSE;
    }
    n = (int)(sep - funcName);
    if (n <= 0 || n >= outSize) {
        return FALSE;
    }
    memcpy(out, funcName, n);
    out[n] = 0;
    return TRUE;
}

static FILE* ClassFile(const char* className)
{
    char path[96];
    FILE* f;
    int i;
    for (i = 0; i < s_classCount; i++) {
        if (strcmp(s_classNames[i], className) == 0) {
            return s_classFiles[i];
        }
    }
    if (s_classCount >= CALL_CLASS_CACHE) {
        return NULL;
    }
    _snprintf(path, sizeof(path), "call_%s.log", className);
    f = fopen(GetLogPath(path), "a");
    if (f == NULL) {
        return NULL;
    }
    s_classNames[s_classCount][0] = 0;
    strncpy(s_classNames[s_classCount], className, sizeof(s_classNames[0]) - 1);
    s_classFiles[s_classCount] = f;
    s_classCount++;
    return f;
}

void TraceInit(void)
{
    s_seq = 0;
    if (s_trace != NULL) {
        return;
    }
    s_trace = fopen(GetLogPath("callGen.log"), "w");
    if (s_trace) {
        fprintf(s_trace, "GTA2 hook trace start\n");
        fflush(s_trace);
    }
}

void TraceEvent(const char* funcName)
{
    char className[64];
    FILE* cf;
    if (s_trace == NULL || funcName == NULL) {
        return;
    }
    s_seq++;
    fprintf(s_trace, "%6I64u  %s\n", s_seq, funcName);
    if (ExtractClassName(funcName, className, sizeof(className))) {
        cf = ClassFile(className);
        if (cf != NULL) {
            fprintf(cf, "%6I64u  %s\n", s_seq, funcName);
            fflush(cf);
        }
    }
    fflush(s_trace);
}

void TraceCall(const char* funcName, unsigned long fromAddr)
{
    char className[64];
    FILE* cf;
    if (s_trace == NULL || funcName == NULL) {
        return;
    }
    s_seq++;
    const char* fromName = GetFunctionNameAt(fromAddr);
    fprintf(s_trace, "%6I64u  %-48s <- called from 0x%08lX %s\n",
            s_seq, funcName, fromAddr, fromName ? fromName : "?");
    if (ExtractClassName(funcName, className, sizeof(className))) {
        cf = ClassFile(className);
        if (cf != NULL) {
            fprintf(cf, "%6I64u  %-48s <- called from 0x%08lX %s\n",
                    s_seq, funcName, fromAddr, fromName ? fromName : "?");
            fflush(cf);
        }
    }
    fflush(s_trace);
}

void TraceClose(void)
{
    int i;
    if (s_trace) {
        fclose(s_trace);
        s_trace = NULL;
    }
    for (i = 0; i < s_classCount; i++) {
        if (s_classFiles[i]) {
            fclose(s_classFiles[i]);
            s_classFiles[i] = NULL;
        }
    }
    s_classCount = 0;
}