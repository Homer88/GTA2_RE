#ifndef __CHOOKTRACE_H__
#define __CHOOKTRACE_H__

void TraceInit(void);
void TraceEvent(const char* funcName);
void TraceClose(void);

#endif // !__CHOOKTRACE_H__