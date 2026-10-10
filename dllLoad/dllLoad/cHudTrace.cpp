#include <Windows.h>
#include <stdio.h>
#include <intrin.h>
#include "cHudTrace.h"

// Retail entry points (imagebase 0x3F0000 in gta2-resurected.exe).
LPVOID _Hud_4219F0                 = (LPVOID)0x004219F0;
LPVOID _Hud_45D3A0                 = (LPVOID)0x0045D3A0;
LPVOID _Hud_Hud_des                = (LPVOID)0x0045D3B0;
LPVOID _Hud_4C6940                 = (LPVOID)0x004C6940;
LPVOID _Hud_4C6960                 = (LPVOID)0x004C6960;
LPVOID _Hud_4C69A0                 = (LPVOID)0x004C69A0;
LPVOID _Hud_Hud1                   = (LPVOID)0x004C69C0;
LPVOID _Hud_Init_s_Wrapper         = (LPVOID)0x004C6D90;
LPVOID _Hud_4C6DA0                 = (LPVOID)0x004C6DA0;
LPVOID _Hud_SetSpeedText           = (LPVOID)0x004C6DC0;
LPVOID _Hud_4C6DE0                 = (LPVOID)0x004C6DE0;
LPVOID _Hud_HandleKeyboard_Wrapper = (LPVOID)0x004C6E20;
LPVOID _Hud_DrawSprite             = (LPVOID)0x004C71B0;
LPVOID _Hud_DrawSprite_Wrapper     = (LPVOID)0x004C94F0;
LPVOID _Hud_DrawUI                 = (LPVOID)0x004CA440;
LPVOID _Hud_DrawUIWrapper          = (LPVOID)0x004CA520;
LPVOID _Hud_Update2_Wrapper        = (LPVOID)0x004CA5D0;
LPVOID _Hud_4CAB50                 = (LPVOID)0x004CAB50;
LPVOID _Hud_SetSpeedText_Wrapper   = (LPVOID)0x004CABE0;
LPVOID _Hud_UpdateWrapper          = (LPVOID)0x004CAC30;

struct HudTraceRec {
    const char* name;
    DWORD caller;
    DWORD self;
    DWORD a1, a2, a3, a4;
};

#define HUD_RING_SIZE 16384
static HudTraceRec g_hudRing[HUD_RING_SIZE];
static volatile DWORD g_hudRingIdx = 0;
static DWORD g_hudTaped = 0;
static const char* kHudTapePath = "C:\\games\\gta2\\hud_trace.log";

static void HudTracePush(const char* name, DWORD caller, DWORD self,
                         DWORD a1, DWORD a2, DWORD a3, DWORD a4)
{
    DWORD idx = (g_hudRingIdx + 1) % HUD_RING_SIZE;
    HudTraceRec* r = &g_hudRing[idx];
    r->name   = name;
    r->caller = caller;
    r->self   = self;
    r->a1 = a1; r->a2 = a2; r->a3 = a3; r->a4 = a4;
    g_hudRingIdx = idx;
}

// ---- generic trampoline types ----------------------------------------------
typedef void  (__fastcall *Tc0)(void*);
typedef void  (__fastcall *Tc1)(void*, DWORD, DWORD);          // (self, dummy, a1)
typedef void  (__fastcall *Tc2)(void*, DWORD, DWORD, DWORD);   // (self, dummy, a1, a2)
typedef void* (__fastcall *Tc1r)(void*, DWORD, DWORD);
typedef unsigned char (__fastcall *Tc1b)(void*, DWORD, DWORD);
typedef unsigned char (__fastcall *Tc2b)(void*, DWORD, DWORD, DWORD);
typedef void  (__cdecl    *Cd0)(void);
typedef void  (__stdcall  *Sd9)(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);

void __fastcall HookHud_4219F0(void* self)
{
    HudTracePush("Hud::sub_4219F0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_Hud_4219F0)(self);
}

void __fastcall HookHud_45D3A0(void* self)
{
    HudTracePush("Hud::sub_45D3A0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_Hud_45D3A0)(self);
}

void* __fastcall HookHud_Hud_des(void* self, DWORD d, DWORD flags)
{
    HudTracePush("Hud::Hud_des", (DWORD)_ReturnAddress(), (DWORD)self, flags, 0, 0, 0);
    return ((Tc1r)_Hud_Hud_des)(self, 0, flags);
}

void __fastcall HookHud_4C6940(void* self)
{
    HudTracePush("Hud::sub_4C6940", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_Hud_4C6940)(self);
}

void __fastcall HookHud_4C6960(void* self, DWORD d, DWORD a1)
{
    HudTracePush("Hud::sub_4C6960", (DWORD)_ReturnAddress(), (DWORD)self, a1, 0, 0, 0);
    ((Tc1)_Hud_4C6960)(self, 0, a1);
}

void __fastcall HookHud_4C69A0(void* self)
{
    HudTracePush("Hud::sub_4C69A0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_Hud_4C69A0)(self);
}

void __fastcall HookHud_Hud1(void* self)
{
    HudTracePush("Hud::Hud1", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_Hud_Hud1)(self);
}

void __fastcall HookHud_Init_s_Wrapper(void* self)
{
    HudTracePush("Hud::Init_s_Wrapper", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_Hud_Init_s_Wrapper)(self);
}

void __cdecl HookHud_4C6DA0(void)
{
    HudTracePush("Hud::sub_4C6DA0", (DWORD)_ReturnAddress(), 0, 0, 0, 0, 0);
    ((Cd0)_Hud_4C6DA0)();
}

void __fastcall HookHud_SetSpeedText(void* self)
{
    HudTracePush("Hud::SetSpeedText", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_Hud_SetSpeedText)(self);
}

unsigned char __fastcall HookHud_4C6DE0(void* self, DWORD d, DWORD a1)
{
    unsigned char r = ((Tc1b)_Hud_4C6DE0)(self, 0, a1);
    HudTracePush("Hud::sub_4C6DE0", (DWORD)_ReturnAddress(), (DWORD)self, a1, r, 0, 0);
    return r;
}

void __fastcall HookHud_HandleKeyboard_Wrapper(void* self)
{
    HudTracePush("Hud::HandleKeyboard_Wrapper", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_Hud_HandleKeyboard_Wrapper)(self);
}

void __stdcall HookHud_DrawSprite(DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5,
                                  DWORD a6, DWORD a7, DWORD a8, DWORD a9)
{
    HudTracePush("Hud::DrawSprite", (DWORD)_ReturnAddress(), a1, a2, a3, a4, a5);
    ((Sd9)_Hud_DrawSprite)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

void __fastcall HookHud_DrawSprite_Wrapper(void* self)
{
    HudTracePush("Hud::DrawSprite_Wrapper", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_Hud_DrawSprite_Wrapper)(self);
}

void __fastcall HookHud_DrawUI(void* self)
{
    HudTracePush("Hud::DrawUI", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_Hud_DrawUI)(self);
}

void __cdecl HookHud_DrawUIWrapper(void)
{
    HudTracePush("Hud::DrawUIWrapper", (DWORD)_ReturnAddress(), 0, 0, 0, 0, 0);
    ((Cd0)_Hud_DrawUIWrapper)();
}

unsigned char __fastcall HookHud_Update2_Wrapper(void* self, DWORD d, DWORD a1, DWORD a2)
{
    unsigned char r = ((Tc2b)_Hud_Update2_Wrapper)(self, 0, a1, a2);
    HudTracePush("Hud::Update2_Wrapper", (DWORD)_ReturnAddress(), (DWORD)self, a1, a2, r, 0);
    return r;
}

void __fastcall HookHud_4CAB50(void* self)
{
    HudTracePush("Hud::sub_4CAB50", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_Hud_4CAB50)(self);
}

void __fastcall HookHud_SetSpeedText_Wrapper(void* self)
{
    HudTracePush("Hud::SetSpeedText_Wrapper", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_Hud_SetSpeedText_Wrapper)(self);
}

void __fastcall HookHud_UpdateWrapper(void* self)
{
    HudTracePush("Hud::UpdateWrapper", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_Hud_UpdateWrapper)(self);
}

void DumpHudRing(FILE* f)
{
    DWORD total = g_hudRingIdx;
    DWORD n = (total < HUD_RING_SIZE) ? total : HUD_RING_SIZE;
    fprintf(f, "HUD-CALL RING (last %lu of %lu):\r\n",
            (unsigned long)n, (unsigned long)total);
    for (DWORD k = 0; k < n; ++k) {
        const HudTraceRec* r = &g_hudRing[(g_hudRingIdx - n + 1 + k) % HUD_RING_SIZE];
        if (!r->name) continue;
        fprintf(f, "  %-28s call=0x%08lX self=0x%08lX a1=0x%08lX a2=0x%08lX a3=0x%08lX a4=0x%08lX\r\n",
                r->name ? r->name : "?",
                (unsigned long)r->caller, (unsigned long)r->self,
                (unsigned long)r->a1, (unsigned long)r->a2,
                (unsigned long)r->a3, (unsigned long)r->a4);
    }
}

void DumpHudRingFile(void)
{
    FILE* f = fopen(kHudTapePath, "ab");
    if (!f) return;
    DWORD total = g_hudRingIdx;
    DWORD delta = total - g_hudTaped;
    if (delta == 0) {
        fclose(f);
        return;
    }
    if (delta > HUD_RING_SIZE) {
        // ring wrapped past the tape: skip to the oldest still-valid entry
        g_hudTaped = total - HUD_RING_SIZE;
        delta = HUD_RING_SIZE;
    }
    for (DWORD k = 0; k < delta; ++k) {
        const HudTraceRec* r = &g_hudRing[(g_hudTaped + k) % HUD_RING_SIZE];
        if (!r->name) continue;
        fprintf(f, "  %-28s call=0x%08lX self=0x%08lX a1=0x%08lX a2=0x%08lX a3=0x%08lX a4=0x%08lX\r\n",
                r->name ? r->name : "?",
                (unsigned long)r->caller, (unsigned long)r->self,
                (unsigned long)r->a1, (unsigned long)r->a2,
                (unsigned long)r->a3, (unsigned long)r->a4);
    }
    g_hudTaped = total;
    fclose(f);
}
