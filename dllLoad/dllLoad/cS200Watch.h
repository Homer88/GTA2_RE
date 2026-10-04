// cS200Watch.h - records which code writes into the Ped S200 block.
// Uses x86 hardware debug registers (Dr0..Dr3, write-watch) armed on every
// thread of the process + a vectored exception handler that logs the EIP
// of the writing instruction, the byte offset that changed and the value the
// game actually wrote into a ring buffer.
//
// Only four watchpoints exist, so a 0x20-byte band slides through the first
// 0xC0 bytes of the Ped across re-arms. Each log line is therefore stamped
// with the band position in force when the write happened.
#ifndef __CS200WATCH_H_
#define __CS200WATCH_H_

// Result of comparing one 8-byte watch window across the trap-flag step.
struct S200Diff {
    int           changed;   // 0 = nothing changed (read-only overlap)
    unsigned long off;       // absolute byte offset of the changed group
    unsigned long width;     // bytes covered by the reported group
    unsigned long newVal;    // little-endian value after the store
    unsigned long oldVal;    // little-endian value before the store
};

// Pure, Win32-free diff of one watch window. Exposed so it can be unit tested
// without a CPU that actually delivers #DB for hardware watchpoints.
void S200DiffWindow(const unsigned char* before, const unsigned char* after,
                    unsigned long winOff, struct S200Diff* out);

// Call once from DllMain (DLL_PROCESS_ATTACH).
void S200WatchInit(void);

// (Re)arm the write-watch on all threads for the Ped at base address.
// Pass the real Ped heap address; watches cover the sliding 0x20-byte band.
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