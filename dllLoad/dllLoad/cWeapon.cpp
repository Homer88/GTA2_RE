#include <Windows.h>
#include <stdio.h>

#include "cWeapon.h"
#include "cHookTrace.h"
#include "cInspector.h"
#include "DebugLogFile.h"

// Trampolines rewritten by DetourAttach in dllmain.cpp to the original retail code:
extern LPVOID _SetWeapon;
extern LPVOID _SetPed;

static void LogWeaponAddr(const char* call, const char* what, void* ptr)
{
    const char* sname = GetGlobalStructName((unsigned long)ptr);
    char buf[160];
    _snprintf(buf, sizeof(buf), "%s=0x%08X%s%s", what, (unsigned long)ptr,
        sname ? " == " : "", sname ? sname : "");
    writeFileLog((char*)"weapon.txt", buf, (char*)call, (char*)"");
}

// Retail Weapon::SetWeapon @0x00433810 is __thiscall(Weapon *this, WeaponType):
//     this -> ECX, WeaponType pushed on the stack, callee cleans 4 bytes.
// The detour is __fastcall(this, _EDX, TypeWeapon): the third parameter lands on
// the stack exactly where the retail caller pushed WeaponType and the __fastcall
// epilogue restores those same 4 bytes, so the retail call site stays balanced.
// Trace, then forward to the retail body (which does this->SMG = TypeWeapon).
void __fastcall SetWeapon(Weapon* pWeapon, void* _EDX, void* TypeWeapon)
{
    (void)_EDX;
    TraceCall("Weapon::SetWeapon @0x00433810", TRACE_CALLER_ADDR);
    LogWeaponAddr("SetWeapon", "pWeapon", pWeapon);
    writeFileLog((char*)"weapon.txt", (char*)"SetWeapon TypeWeapon", (char*)"", (unsigned int)TypeWeapon);
    if (pWeapon == NULL) {
        return;
    }
    ((void (__thiscall*)(Weapon*, void*))_SetWeapon)(pWeapon, TypeWeapon);
}

void __fastcall SetPed(Weapon* pWeapon, void* _EDX, void* pPed)
{
    (void)_EDX;
    TraceCall("Weapon::SetPed @0x004CCA10", TRACE_CALLER_ADDR);
    LogWeaponAddr("SetPed", "pWeapon", pWeapon);
    LogWeaponAddr("SetPed", "pPed", pPed);
    if (pWeapon == NULL) {
        return;
    }
    ((void (__thiscall*)(Weapon*, Ped*))_SetPed)(pWeapon, (Ped*)pPed);
}