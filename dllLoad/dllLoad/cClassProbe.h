#ifndef __CCLASSPROBE_H__
#define __CCLASSPROBE_H__

// Runtime class identification.
//
// Static analysis gives the layout of a class, but not proof that a given
// retail function really operates on that class. The probe records the
// actual `this` pointer each hooked method receives, so identical pointer
// values across functions prove they share one object, and therefore one
// class.
//
// Pairs are de-duplicated on (retail address, this pointer): the file stays
// small even for 2677 call sites, while still containing every distinct
// (function, object) combination the game actually exercised.

// retailAddr - the hooked retail address (also used to resolve a name)
// name        - "Class::Method" label for the log
// pThis       - the `this` the retail code received
void ProbeThis(unsigned long retailAddr, const char* name, const void* pThis);

// Where the probe CSV is written (next to the DLL by default).
const char* ProbeThisLogPath(void);

// Internal: reports probe-open diagnostics into the session log dir.
// msg may embed '\n' characters; each becomes its own log line.
void ProbeDiag(const char* msg);

// Number of distinct pairs recorded so far.
unsigned long ProbeThisCount(void);

// Opens the CSV eagerly (call from DllMain DLL_PROCESS_ATTACH) and reports the
// resolved path plus success into the session log.
void ProbeThisInit(void);

// Closes the log file. Call from DllMain DLL_PROCESS_DETACH.
void ProbeThisClose(void);

#endif // !__CCLASSPROBE_H__