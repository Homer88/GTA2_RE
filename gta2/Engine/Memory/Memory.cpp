
#include "memory.h"
#include <stdlib.h>
#include "../Debug/DebugLogFile.h"

unsigned int NewMemory(unsigned int size, void** outPtr)
{
    void* raw = malloc(size + 0x10000);
    *outPtr = raw;
    if (raw == NULL) {
        DebugLog(0x405, "Memory.cpp", 76);
    }
    return ((unsigned int) raw + 0xFFFF) & 0xFFFF0000;
}
