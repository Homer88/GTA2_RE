#pragma once
#include <Windows.h>
#include <stdio.h>

// ---- HUD observer hooks -----------------------------------------------------
// Every Hud::* function listed in AddrToFunc.h is wrapped by an observer that
// records (caller, this, up to four args) into a ring and forwards to the retail
// trampoline. Nothing about the game's behaviour is changed.
//
// Calling conventions (verified by disassembling gta2-resurected.exe):
//   thiscall, 0 args .... __fastcall Hook(void* self)
//   thiscall, N args .... __fastcall Hook(void* self, DWORD /*dummy edx*/, args...)
//   cdecl,   0 args .... __cdecl    Hook(void)
//   stdcall, 9 args .... __stdcall  Hook(a1..a9)
//
// Trampolines are detached LPVOID slots patched by DetourAttach (dllmain.cpp).

extern LPVOID _Hud_4219F0;                 // Hud::sub_4219F0          thiscall
extern LPVOID _Hud_45D3A0;                 // Hud::sub_45D3A0          thiscall
extern LPVOID _Hud_Hud_des;                // Hud::Hud_des             thiscall,1 -> void*
extern LPVOID _Hud_4C6940;                 // Hud::sub_4C6940          thiscall
extern LPVOID _Hud_4C6960;                 // Hud::sub_4C6960          thiscall,1
extern LPVOID _Hud_4C69A0;                 // Hud::sub_4C69A0          thiscall
extern LPVOID _Hud_Hud1;                   // Hud::Hud1                thiscall
extern LPVOID _Hud_Init_s_Wrapper;         // Hud::Init_s_Wrapper      thiscall
extern LPVOID _Hud_4C6DA0;                 // Hud::sub_4C6DA0          cdecl
extern LPVOID _Hud_SetSpeedText;           // Hud::SetSpeedText        thiscall
extern LPVOID _Hud_4C6DE0;                 // Hud::sub_4C6DE0          thiscall,1 -> bool
extern LPVOID _Hud_HandleKeyboard_Wrapper; // Hud::HandleKeyboard_Wrapper thiscall
extern LPVOID _Hud_DrawSprite;             // Hud::DrawSprite          stdcall,9
extern LPVOID _Hud_DrawSprite_Wrapper;     // Hud::DrawSprite_Wrapper  thiscall
extern LPVOID _Hud_DrawUI;                 // Hud::DrawUI              thiscall
extern LPVOID _Hud_DrawUIWrapper;          // Hud::DrawUIWrapper       cdecl
extern LPVOID _Hud_Update2_Wrapper;        // Hud::Update2_Wrapper     thiscall,2 -> bool
extern LPVOID _Hud_4CAB50;                 // Hud::sub_4CAB50          thiscall
extern LPVOID _Hud_SetSpeedText_Wrapper;   // Hud::SetSpeedText_Wrapper thiscall
extern LPVOID _Hud_UpdateWrapper;          // Hud::UpdateWrapper       thiscall

void __fastcall HookHud_4219F0(void* self);
void __fastcall HookHud_45D3A0(void* self);
void* __fastcall HookHud_Hud_des(void* self, DWORD d, DWORD flags);
void __fastcall HookHud_4C6940(void* self);
void __fastcall HookHud_4C6960(void* self, DWORD d, DWORD a1);
void __fastcall HookHud_4C69A0(void* self);
void __fastcall HookHud_Hud1(void* self);
void __fastcall HookHud_Init_s_Wrapper(void* self);
void __cdecl HookHud_4C6DA0(void);
void __fastcall HookHud_SetSpeedText(void* self);
unsigned char __fastcall HookHud_4C6DE0(void* self, DWORD d, DWORD a1);
void __fastcall HookHud_HandleKeyboard_Wrapper(void* self);
void __stdcall HookHud_DrawSprite(DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5,
                                  DWORD a6, DWORD a7, DWORD a8, DWORD a9);
void __fastcall HookHud_DrawSprite_Wrapper(void* self);
void __fastcall HookHud_DrawUI(void* self);
void __cdecl HookHud_DrawUIWrapper(void);
unsigned char __fastcall HookHud_Update2_Wrapper(void* self, DWORD d, DWORD a1, DWORD a2);
void __fastcall HookHud_4CAB50(void* self);
void __fastcall HookHud_SetSpeedText_Wrapper(void* self);
void __fastcall HookHud_UpdateWrapper(void* self);

void DumpHudRing(FILE* f);        // full ring dump (crash forensics)
void DumpHudRingFile(void);       // append new entries to hud_trace.log
