#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <cstddef>

unsigned int NewMemory(unsigned int size, void** outPtr);
// IDA 0x4059B0: malloc wrapper; logs 1029/Memory.cpp/44 on failure.
void* CreateBuffer(size_t dwBytes);

#endif // !_MEMORY_H_
