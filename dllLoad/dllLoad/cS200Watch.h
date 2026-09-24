// cS200Watch.h - records which code writes into the Ped S200 block.
// Uses x86 hardware debug registers (Dr0..Dr3, write-watch) armed on every
// thread of the process + a vectored exception handler that logs the EIP
// of the writing instruction (and the written value) into a ring buffer.
#ifndef __CS200WATCH_H_
#define __CS200WATCH_H_

// Call once from DllMain (DLL_PROCESS_ATTACH).
void S200WatchInit(void);

// (Re)arm the write-watch on all threads for the Ped at base address.
// Pass the real Ped heap address; watches cover the first 300 bytes (S200).
void S200WatchSetTarget(const void* pedBase);

// Clear all watchpoints (optional; call on DLL_PROCESS_DETACH).
void S200WatchClear(void);

// Dump the current ring-buffer contents (live hits since last dump).
// Writes into the common console buffer via the cInspector DumpBuf helpers.
struct DumpBuf;
void S200WatchDump(struct DumpBuf* b);

// Write accumulated hits to the S200Write.log file (called by BuildDump loop).
void S200WatchFlushToFile(void);

#endif // !__CS200WATCH_H_