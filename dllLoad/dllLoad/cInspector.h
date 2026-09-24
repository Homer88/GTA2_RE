#ifndef __CINSPECTOR_H__
#define __CINSPECTOR_H__

#include <stddef.h>

void StartInspector(void);
void StopInspector(void);
void InspectorRequestRefresh(void);

const char* GetGlobalStructName(unsigned long addr);

// Shared text buffer used by the inspector window and helper formatters.
struct DumpBuf {
    char* data;
    size_t cap;
    size_t len;
};
void DumpPrintf(struct DumpBuf* b, const char* fmt, ...);

#endif // !__CINSPECTOR_H__