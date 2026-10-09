#include "cPed.h"
#include <Windows.h>
#include <stdio.h>
#include "DebugLogFile.h"
#include "cHookTrace.h"
#include "cClassProbe.h"

// Retail Ped setters are single-store stubs (byte listing in cPed.h). The
// __fastcall form preserves the __thiscall ABI: this in ECX, value on the
// stack, callee cleans 4 bytes ("ret 4"). Re-implementing the store against
// our own Ped struct is a full replacement, so no trampoline is required.

static void PedStoreLog(Ped* pPed, unsigned int retailAddr, const char* name,
                        const char* field, unsigned int offset,
                        long before, long after)
{
    char msg[96];
    char val[16];
    char ev[64];
    sprintf(ev, "%s (body)", name);
    TraceEvent(ev);
    sprintf(val, "%ld", after);
    sprintf(msg, "Ped->%s @0x%X = %ld (was %ld)", field, offset, after, before);
    writeFileLog((char*)"Ped", msg, (char*)"Info", val);
    (void)pPed;
    (void)retailAddr;
}

void __fastcall HookSetSearchType(Ped* pPed, void* _EDX, int value)
{
    long before;
    (void)_EDX;
    TraceCall("Ped::SetSearchType @0x00403920", TRACE_CALLER_ADDR);
    ProbeThis(0x00403920u, "Ped::SetSearchType", pPed);
    before = pPed ? (long)pPed->SearchType : 0;
    if (pPed != NULL) {
        pPed->SearchType = value;
    }
    PedStoreLog(pPed, 0x00403920u, "Ped::SetSearchType", "SearchType", 0x238,
                before, (long)value);
}

void __fastcall HookSetS169(Ped* pPed, void* _EDX, int value)
{
    long before;
    (void)_EDX;
    TraceCall("Ped::SetS169 @0x00403930", TRACE_CALLER_ADDR);
    ProbeThis(0x00403930u, "Ped::SetS169", pPed);
    before = pPed ? (long)pPed->S169 : 0;
    if (pPed != NULL) {
        pPed->S169 = (S169*)value;
    }
    PedStoreLog(pPed, 0x00403930u, "Ped::SetS169", "S169", 0x164,
                before, (long)value);
}

void __fastcall HookSetCarId(Ped* pPed, void* _EDX, unsigned char value)
{
    long before;
    (void)_EDX;
    TraceCall("Ped::SetCarId @0x00403940", TRACE_CALLER_ADDR);
    ProbeThis(0x00403940u, "Ped::SetCarId", pPed);
    before = pPed ? (long)(unsigned char)pPed->CarId : 0;
    if (pPed != NULL) {
        pPed->CarId = (char)value;
    }
    PedStoreLog(pPed, 0x00403940u, "Ped::SetCarId", "CarId", 0x23C,
                before, (long)value);
}

void __fastcall HookSetHealth(Ped* pPed, void* _EDX, short value)
{
    long before;
    (void)_EDX;
    TraceCall("Ped::SetHealth @0x004039A0", TRACE_CALLER_ADDR);
    ProbeThis(0x004039A0u, "Ped::SetHealth", pPed);
    before = pPed ? (long)pPed->Health : 0;
    if (pPed != NULL) {
        pPed->Health = value;
    }
    PedStoreLog(pPed, 0x004039A0u, "Ped::SetHealth", "Health", 0x216,
                before, (long)value);
}