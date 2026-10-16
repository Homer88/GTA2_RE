#include <Windows.h>
#include <stdio.h>
#include <intrin.h>
#include "cCharacterTrace.h"

// Retail entry points (imagebase 0x3F0000 in gta2-resurected.exe).
LPVOID _Character_420C30 = (LPVOID)0x00420C30;
LPVOID _Character_43AE10 = (LPVOID)0x0043AE10;
LPVOID _Character_43DB40 = (LPVOID)0x0043DB40;
LPVOID _Character_43DBD0 = (LPVOID)0x0043DBD0;
LPVOID _Character_43DC60 = (LPVOID)0x0043DC60;
LPVOID _Character_43DD80 = (LPVOID)0x0043DD80;
LPVOID _Character_43DE10 = (LPVOID)0x0043DE10;
LPVOID _Character_43DEB0 = (LPVOID)0x0043DEB0;
LPVOID _Character_43DF60 = (LPVOID)0x0043DF60;
LPVOID _Character_43DFB0 = (LPVOID)0x0043DFB0;
LPVOID _Character_43E080 = (LPVOID)0x0043E080;
LPVOID _Character_440CC0 = (LPVOID)0x00440CC0;
LPVOID _Character_4416B0 = (LPVOID)0x004416B0;
LPVOID _Character_441960 = (LPVOID)0x00441960;
LPVOID _Character_445A20 = (LPVOID)0x00445A20;
LPVOID _Character_45AA30 = (LPVOID)0x0045AA30;

struct CharacterTraceRec {
    const char* name;
    DWORD caller;
    DWORD self;
    DWORD a1, a2, a3, a4;
};

#define CHARACTER_RING_SIZE 16384
static CharacterTraceRec g_characterRing[CHARACTER_RING_SIZE];
static volatile DWORD g_characterRingIdx = 0;
static DWORD g_characterTaped = 0;
static const char* kCharacterTapePath = "C:\\games\\gta2\\character_trace.log";

static void CharacterTracePush(const char* name, DWORD caller, DWORD self,
                               DWORD a1, DWORD a2, DWORD a3, DWORD a4)
{
    DWORD idx = (g_characterRingIdx + 1) % CHARACTER_RING_SIZE;
    CharacterTraceRec* r = &g_characterRing[idx];
    r->name   = name;
    r->caller = caller;
    r->self   = self;
    r->a1 = a1; r->a2 = a2; r->a3 = a3; r->a4 = a4;
    g_characterRingIdx = idx;
}

// ---- generic trampoline types ----------------------------------------------
typedef void  (__fastcall *Tc0)(void*);
typedef void* (__fastcall *Tc0r)(void*);
typedef void  (__fastcall *Tc1)(void*, DWORD, DWORD);
typedef void* (__fastcall *Tc1r)(void*, DWORD, DWORD);
typedef unsigned char (__fastcall *Tc1b)(void*, DWORD, DWORD);
typedef void* (__fastcall *Tc2r)(void*, DWORD, DWORD, DWORD);
typedef void* (__fastcall *Tc5r)(void*, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);

unsigned char __fastcall HookCharacter_420C30(void* self, DWORD d, DWORD pPed)
{
    unsigned char r = ((Tc1b)_Character_420C30)(self, 0, pPed);
    CharacterTracePush("Character::sub_420C30", (DWORD)_ReturnAddress(), (DWORD)self, pPed, r, 0, 0);
    return r;
}

void* __fastcall HookCharacter_43AE10(void* self, DWORD d, DWORD pID)
{
    void* r = ((Tc1r)_Character_43AE10)(self, 0, pID);
    CharacterTracePush("Character::FindPed", (DWORD)_ReturnAddress(), (DWORD)self, pID, (DWORD)r, 0, 0);
    return r;
}

void* __fastcall HookCharacter_43DB40(void* self, DWORD d, DWORD x, DWORD y, DWORD z, DWORD remap, DWORD a5)
{
    CharacterTracePush("Character::SpawnPedAtPosition", (DWORD)_ReturnAddress(), (DWORD)self, x, y, z, remap);
    return ((Tc5r)_Character_43DB40)(self, 0, x, y, z, remap, a5);
}

void* __fastcall HookCharacter_43DBD0(void* self, DWORD d, DWORD pCar)
{
    void* r = ((Tc1r)_Character_43DBD0)(self, 0, pCar);
    CharacterTracePush("Character::CreatePedInCar", (DWORD)_ReturnAddress(), (DWORD)self, pCar, (DWORD)r, 0, 0);
    return r;
}

void* __fastcall HookCharacter_43DC60(void* self, DWORD d, DWORD pCar, DWORD a3)
{
    void* r = ((Tc2r)_Character_43DC60)(self, 0, pCar, a3);
    CharacterTracePush("Character::sub_43DC60", (DWORD)_ReturnAddress(), (DWORD)self, pCar, a3, (DWORD)r, 0);
    return r;
}

void* __fastcall HookCharacter_43DD80(void* self, DWORD d, DWORD pCar)
{
    void* r = ((Tc1r)_Character_43DD80)(self, 0, pCar);
    CharacterTracePush("Character::sub_43DD80", (DWORD)_ReturnAddress(), (DWORD)self, pCar, (DWORD)r, 0, 0);
    return r;
}

void* __fastcall HookCharacter_43DE10(void* self)
{
    void* r = ((Tc0r)_Character_43DE10)(self);
    CharacterTracePush("Character::sub_43DE10", (DWORD)_ReturnAddress(), (DWORD)self, (DWORD)r, 0, 0, 0);
    return r;
}

void* __fastcall HookCharacter_43DEB0(void* self)
{
    void* r = ((Tc0r)_Character_43DEB0)(self);
    CharacterTracePush("Character::sub_43DEB0", (DWORD)_ReturnAddress(), (DWORD)self, (DWORD)r, 0, 0, 0);
    return r;
}

void* __fastcall HookCharacter_43DF60(void* self)
{
    void* r = ((Tc0r)_Character_43DF60)(self);
    CharacterTracePush("Character::CreatePed", (DWORD)_ReturnAddress(), (DWORD)self, (DWORD)r, 0, 0, 0);
    return r;
}

void* __fastcall HookCharacter_43DFB0(void* self, DWORD d, DWORD _Ped)
{
    void* r = ((Tc1r)_Character_43DFB0)(self, 0, _Ped);
    CharacterTracePush("Character::sub_43DFB0", (DWORD)_ReturnAddress(), (DWORD)self, _Ped, (DWORD)r, 0, 0);
    return r;
}

void __fastcall HookCharacter_43E080(void* self, DWORD d, DWORD pKey)
{
    CharacterTracePush("Character::HandlePlayerInvisibilityCommand", (DWORD)_ReturnAddress(), (DWORD)self, pKey, 0, 0, 0);
    ((Tc1)_Character_43E080)(self, 0, pKey);
}

unsigned char __fastcall HookCharacter_440CC0(void* self, DWORD d, DWORD pSpriteS1)
{
    unsigned char r = ((Tc1b)_Character_440CC0)(self, 0, pSpriteS1);
    CharacterTracePush("Character::sub_440CC0", (DWORD)_ReturnAddress(), (DWORD)self, pSpriteS1, r, 0, 0);
    return r;
}

void* __fastcall HookCharacter_4416B0(void* self)
{
    void* r = ((Tc0r)_Character_4416B0)(self);
    CharacterTracePush("Character::Character", (DWORD)_ReturnAddress(), (DWORD)self, (DWORD)r, 0, 0, 0);
    return r;
}

void* __fastcall HookCharacter_441960(void* self)
{
    void* r = ((Tc0r)_Character_441960)(self);
    CharacterTracePush("Character::Destructor", (DWORD)_ReturnAddress(), (DWORD)self, (DWORD)r, 0, 0, 0);
    return r;
}

void* __fastcall HookCharacter_445A20(void* self)
{
    void* r = ((Tc0r)_Character_445A20)(self);
    CharacterTracePush("Character::sub_445A20", (DWORD)_ReturnAddress(), (DWORD)self, (DWORD)r, 0, 0, 0);
    return r;
}

void* __fastcall HookCharacter_45AA30(void* self, DWORD d, DWORD a2)
{
    void* r = ((Tc1r)_Character_45AA30)(self, 0, a2);
    CharacterTracePush("Character::Character_Des", (DWORD)_ReturnAddress(), (DWORD)self, a2, (DWORD)r, 0, 0);
    return r;
}

void DumpCharacterRing(FILE* f)
{
    DWORD total = g_characterRingIdx;
    DWORD n = (total < CHARACTER_RING_SIZE) ? total : CHARACTER_RING_SIZE;
    fprintf(f, "CHARACTER-CALL RING (last %lu of %lu):\r\n",
            (unsigned long)n, (unsigned long)total);
    for (DWORD k = 0; k < n; ++k) {
        const CharacterTraceRec* r = &g_characterRing[(g_characterRingIdx - n + 1 + k) % CHARACTER_RING_SIZE];
        if (!r->name) continue;
        fprintf(f, "  %-40s call=0x%08lX self=0x%08lX a1=0x%08lX a2=0x%08lX a3=0x%08lX a4=0x%08lX\r\n",
                r->name ? r->name : "?",
                (unsigned long)r->caller, (unsigned long)r->self,
                (unsigned long)r->a1, (unsigned long)r->a2,
                (unsigned long)r->a3, (unsigned long)r->a4);
    }
}

void DumpCharacterRingFile(void)
{
    FILE* f = fopen(kCharacterTapePath, "ab");
    if (!f) return;
    DWORD total = g_characterRingIdx;
    DWORD delta = total - g_characterTaped;
    if (delta == 0) {
        fclose(f);
        return;
    }
    if (delta > CHARACTER_RING_SIZE) {
        // ring wrapped past the tape: skip to the oldest still-valid entry
        g_characterTaped = total - CHARACTER_RING_SIZE;
        delta = CHARACTER_RING_SIZE;
    }
    for (DWORD k = 0; k < delta; ++k) {
        const CharacterTraceRec* r = &g_characterRing[(g_characterTaped + k) % CHARACTER_RING_SIZE];
        if (!r->name) continue;
        fprintf(f, "  %-40s call=0x%08lX self=0x%08lX a1=0x%08lX a2=0x%08lX a3=0x%08lX a4=0x%08lX\r\n",
                r->name ? r->name : "?",
                (unsigned long)r->caller, (unsigned long)r->self,
                (unsigned long)r->a1, (unsigned long)r->a2,
                (unsigned long)r->a3, (unsigned long)r->a4);
    }
    g_characterTaped = total;
    fclose(f);
}
