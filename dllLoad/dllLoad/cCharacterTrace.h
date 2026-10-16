#pragma once
#include <Windows.h>
#include <stdio.h>

// ---- Character observer hooks ----------------------------------------------
// Every Character::* function listed in AddrToFunc.h is wrapped by an observer
// that records (caller, this, up to four args) into a ring and forwards to the
// retail trampoline. Nothing about the game's behaviour is changed.
//
// Signatures taken from dump\IDA\gta2.exe.c. Calling conventions are __thiscall:
//   thiscall, 0 args .... __fastcall Hook(void* self)
//   thiscall, N args .... __fastcall Hook(void* self, DWORD /*dummy edx*/, args...)
//
// Trampolines are detached LPVOID slots patched by DetourAttach (dllmain.cpp).

extern LPVOID _Character_420C30;   // Character::sub_420C30        thiscall,1 -> bool
extern LPVOID _Character_43AE10;   // Character::FindPed            thiscall,1 -> Ped*
extern LPVOID _Character_43DB40;   // Character::SpawnPedAtPosition thiscall,5 -> Ped*
extern LPVOID _Character_43DBD0;   // Character::CreatePedInCar     thiscall,1 -> Ped*
extern LPVOID _Character_43DC60;   // Character::sub_43DC60         thiscall,2 -> Ped*
extern LPVOID _Character_43DD80;   // Character::sub_43DD80         thiscall,1 -> Ped*
extern LPVOID _Character_43DE10;   // Character::sub_43DE10         thiscall   -> Ped*
extern LPVOID _Character_43DEB0;   // Character::sub_43DEB0         thiscall   -> Ped*
extern LPVOID _Character_43DF60;   // Character::CreatePed          thiscall   -> Ped*
extern LPVOID _Character_43DFB0;   // Character::sub_43DFB0         thiscall,1 -> Ped*
extern LPVOID _Character_43E080;   // Character::HandlePlayerInvisibilityCommand thiscall,1
extern LPVOID _Character_440CC0;   // Character::sub_440CC0         thiscall,1 -> char
extern LPVOID _Character_4416B0;   // Character::Character          thiscall   -> Character*
extern LPVOID _Character_441960;   // Character::Destructor         thiscall   -> SpriteS1*
extern LPVOID _Character_445A20;   // Character::sub_445A20         thiscall   -> void*
extern LPVOID _Character_45AA30;   // Character::Character_Des      thiscall,1 -> int*

unsigned char __fastcall HookCharacter_420C30(void* self, DWORD d, DWORD pPed);
void* __fastcall HookCharacter_43AE10(void* self, DWORD d, DWORD pID);
void* __fastcall HookCharacter_43DB40(void* self, DWORD d, DWORD x, DWORD y, DWORD z, DWORD remap, DWORD a5);
void* __fastcall HookCharacter_43DBD0(void* self, DWORD d, DWORD pCar);
void* __fastcall HookCharacter_43DC60(void* self, DWORD d, DWORD pCar, DWORD a3);
void* __fastcall HookCharacter_43DD80(void* self, DWORD d, DWORD pCar);
void* __fastcall HookCharacter_43DE10(void* self);
void* __fastcall HookCharacter_43DEB0(void* self);
void* __fastcall HookCharacter_43DF60(void* self);
void* __fastcall HookCharacter_43DFB0(void* self, DWORD d, DWORD _Ped);
void __fastcall HookCharacter_43E080(void* self, DWORD d, DWORD pKey);
unsigned char __fastcall HookCharacter_440CC0(void* self, DWORD d, DWORD pSpriteS1);
void* __fastcall HookCharacter_4416B0(void* self);
void* __fastcall HookCharacter_441960(void* self);
void* __fastcall HookCharacter_445A20(void* self);
void* __fastcall HookCharacter_45AA30(void* self, DWORD d, DWORD a2);

void DumpCharacterRing(FILE* f);     // full ring dump (crash forensics)
void DumpCharacterRingFile(void);    // append new entries to character_trace.log
