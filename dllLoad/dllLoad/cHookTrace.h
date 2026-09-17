#ifndef __CHOOKTRACE_H__
#define __CHOOKTRACE_H__

#include <intrin.h>

void TraceInit(void);
void TraceEvent(const char* funcName);
// TraceEvent + "кто вызвал": logs where the retail caller will continue.
// Pass TRACE_CALLER_ADDR as fromAddr - it reads the caller's return address
// out of the detour frame and resolves it to a function name via AddrToFunc.h.
void TraceCall(const char* funcName, unsigned long fromAddr);
void TraceClose(void);

// A Detours detour is jumped to with the retail caller's stack intact, so its
// return slot holds the address of the instruction the RETAIL caller continues
// at. That is exactly "откуда вызвана функция".
#define TRACE_CALLER_ADDR ((unsigned long)((void**)_AddressOfReturnAddress())[0])

#endif // !__CHOOKTRACE_H__