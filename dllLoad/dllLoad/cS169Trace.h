#pragma once
#include <Windows.h>
#include <stdio.h>

// ---- S169 observer hooks ----------------------------------------------------
// S169 is the reconstruction's "AIController": every S169::* function listed in
// AddrToFunc.h is wrapped by an observer that records (caller, this, up to four
// args) into a ring and forwards to the retail trampoline. Behaviour unchanged.
//
// Signatures taken from dump\IDA\gta2.exe.c. Calling conventions are __thiscall:
//   thiscall, 0 args .... __fastcall Hook(void* self)
//   thiscall, N args .... __fastcall Hook(void* self, DWORD /*dummy edx*/, args...)
//
// Trampolines are detached LPVOID slots patched by DetourAttach (dllmain.cpp).

extern LPVOID _S169_4035B0;   // S169::S169                  thiscall   -> int
extern LPVOID _S169_403650;   // S169::sub_403650            thiscall   -> bool
extern LPVOID _S169_4037A0;   // S169::AreAnyPedActive       thiscall   -> char
extern LPVOID _S169_4038E0;   // S169::SetInUse              thiscall
extern LPVOID _S169_4038F0;   // S169::GetInUse              thiscall   -> char
extern LPVOID _S169_403BE0;   // S169::sub_403BE0            thiscall   -> int
extern LPVOID _S169_403C40;   // S169::sub_403C40            thiscall   -> char
extern LPVOID _S169_403D10;   // S169::sub_403D10            thiscall   -> bool
extern LPVOID _S169_403D20;   // S169::sub_403D20            thiscall   -> bool
extern LPVOID _S169_403DA0;   // S169::sub_403DA0            thiscall
extern LPVOID _S169_403E90;   // S169::ManageGroupPedObjectives thiscall
extern LPVOID _S169_403FB0;   // S169::sub_403FB0            thiscall,1 (Ped*)
extern LPVOID _S169_404120;   // S169::sub_404120            thiscall,1 (u8)
extern LPVOID _S169_404400;   // S169::sub_404400            thiscall,1 (Ped*)
extern LPVOID _S169_404420;   // S169::AddPedtoList          thiscall,2 (Ped*,u8)
extern LPVOID _S169_404450;   // S169::sub_404450            thiscall   -> Ped*
extern LPVOID _S169_404480;   // S169::sub_404480            thiscall   -> int
extern LPVOID _S169_404490;   // S169::sub_404490            thiscall,1 -> Ped*
extern LPVOID _S169_4045D0;   // S169::sub_4045D0            thiscall   -> char
extern LPVOID _S169_4046F0;   // S169::sub_4046F0            thiscall,1 (u8)
extern LPVOID _S169_404840;   // S169::sub_404840            thiscall   -> bool
extern LPVOID _S169_4048A0;   // S169::sub_4048A0            thiscall   -> char
extern LPVOID _S169_404900;   // S169::sub_404900            thiscall,1 -> bool
extern LPVOID _S169_4049F0;   // S169::sub_4049F0            thiscall   -> bool
extern LPVOID _S169_404AD0;   // S169::sub_404AD0            thiscall,1 -> Ped*
extern LPVOID _S169_404C90;   // S169::AddPedToEndOfList     thiscall,1 (Ped*)
extern LPVOID _S169_404CE0;   // S169::sub_404CE0            thiscall   -> u8
extern LPVOID _S169_404D40;   // S169::sub_404D40            thiscall,1 (Ped*)
extern LPVOID _S169_404EF0;   // S169::sub_404EF0            thiscall,1 (Ped*)
extern LPVOID _S169_405240;   // S169::sub_405240            thiscall,1 -> char
extern LPVOID _S169_405760;   // S169::sub_405760            thiscall,1 (u8)
extern LPVOID _S169_433360;   // S169::SetListSize           thiscall,1 (char)
extern LPVOID _S169_433370;   // S169::sub_433370            thiscall   -> Ped*
extern LPVOID _S169_439970;   // S169::sub_439970            thiscall

int __fastcall HookS169_4035B0(void* self);
unsigned char __fastcall HookS169_403650(void* self);
unsigned char __fastcall HookS169_4037A0(void* self);
void __fastcall HookS169_4038E0(void* self);
unsigned char __fastcall HookS169_4038F0(void* self);
int __fastcall HookS169_403BE0(void* self);
unsigned char __fastcall HookS169_403C40(void* self);
unsigned char __fastcall HookS169_403D10(void* self);
unsigned char __fastcall HookS169_403D20(void* self);
void __fastcall HookS169_403DA0(void* self);
void __fastcall HookS169_403E90(void* self);
void __fastcall HookS169_403FB0(void* self, DWORD d, DWORD a2);
void __fastcall HookS169_404120(void* self, DWORD d, DWORD Index);
void __fastcall HookS169_404400(void* self, DWORD d, DWORD pPed);
void __fastcall HookS169_404420(void* self, DWORD d, DWORD a2, DWORD Id);
void* __fastcall HookS169_404450(void* self);
int __fastcall HookS169_404480(void* self);
void* __fastcall HookS169_404490(void* self, DWORD d, DWORD arg0);
unsigned char __fastcall HookS169_4045D0(void* self);
void __fastcall HookS169_4046F0(void* self, DWORD d, DWORD X);
unsigned char __fastcall HookS169_404840(void* self);
unsigned char __fastcall HookS169_4048A0(void* self);
unsigned char __fastcall HookS169_404900(void* self, DWORD d, DWORD X);
unsigned char __fastcall HookS169_4049F0(void* self);
void* __fastcall HookS169_404AD0(void* self, DWORD d, DWORD a2);
void __fastcall HookS169_404C90(void* self, DWORD d, DWORD pPed);
unsigned char __fastcall HookS169_404CE0(void* self);
void __fastcall HookS169_404D40(void* self, DWORD d, DWORD pPed);
void __fastcall HookS169_404EF0(void* self, DWORD d, DWORD a2);
unsigned char __fastcall HookS169_405240(void* self, DWORD d, DWORD a2);
void __fastcall HookS169_405760(void* self, DWORD d, DWORD a2);
void __fastcall HookS169_433360(void* self, DWORD d, DWORD ListSize);
void* __fastcall HookS169_433370(void* self);
void __fastcall HookS169_439970(void* self);

void DumpS169Ring(FILE* f);      // full ring dump (crash forensics)
void DumpS169RingFile(void);     // append new entries to s169_trace.log
