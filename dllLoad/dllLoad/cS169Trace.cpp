#include <Windows.h>
#include <stdio.h>
#include <intrin.h>
#include "cS169Trace.h"

// Retail entry points (imagebase 0x3F0000 in gta2-resurected.exe).
LPVOID _S169_4035B0 = (LPVOID)0x004035B0;
LPVOID _S169_403650 = (LPVOID)0x00403650;
LPVOID _S169_4037A0 = (LPVOID)0x004037A0;
LPVOID _S169_4038E0 = (LPVOID)0x004038E0;
LPVOID _S169_4038F0 = (LPVOID)0x004038F0;
LPVOID _S169_403BE0 = (LPVOID)0x00403BE0;
LPVOID _S169_403C40 = (LPVOID)0x00403C40;
LPVOID _S169_403D10 = (LPVOID)0x00403D10;
LPVOID _S169_403D20 = (LPVOID)0x00403D20;
LPVOID _S169_403DA0 = (LPVOID)0x00403DA0;
LPVOID _S169_403E90 = (LPVOID)0x00403E90;
LPVOID _S169_403FB0 = (LPVOID)0x00403FB0;
LPVOID _S169_404120 = (LPVOID)0x00404120;
LPVOID _S169_404400 = (LPVOID)0x00404400;
LPVOID _S169_404420 = (LPVOID)0x00404420;
LPVOID _S169_404450 = (LPVOID)0x00404450;
LPVOID _S169_404480 = (LPVOID)0x00404480;
LPVOID _S169_404490 = (LPVOID)0x00404490;
LPVOID _S169_4045D0 = (LPVOID)0x004045D0;
LPVOID _S169_4046F0 = (LPVOID)0x004046F0;
LPVOID _S169_404840 = (LPVOID)0x00404840;
LPVOID _S169_4048A0 = (LPVOID)0x004048A0;
LPVOID _S169_404900 = (LPVOID)0x00404900;
LPVOID _S169_4049F0 = (LPVOID)0x004049F0;
LPVOID _S169_404AD0 = (LPVOID)0x00404AD0;
LPVOID _S169_404C90 = (LPVOID)0x00404C90;
LPVOID _S169_404CE0 = (LPVOID)0x00404CE0;
LPVOID _S169_404D40 = (LPVOID)0x00404D40;
LPVOID _S169_404EF0 = (LPVOID)0x00404EF0;
LPVOID _S169_405240 = (LPVOID)0x00405240;
LPVOID _S169_405760 = (LPVOID)0x00405760;
LPVOID _S169_433360 = (LPVOID)0x00433360;
LPVOID _S169_433370 = (LPVOID)0x00433370;
LPVOID _S169_439970 = (LPVOID)0x00439970;

struct S169TraceRec {
    const char* name;
    DWORD caller;
    DWORD self;
    DWORD a1, a2, a3, a4;
};

#define S169_RING_SIZE 16384
static S169TraceRec g_s169Ring[S169_RING_SIZE];
static volatile DWORD g_s169RingIdx = 0;
static DWORD g_s169Taped = 0;
static const char* kS169TapePath = "C:\\games\\gta2\\s169_trace.log";

static void S169TracePush(const char* name, DWORD caller, DWORD self,
                          DWORD a1, DWORD a2, DWORD a3, DWORD a4)
{
    DWORD idx = (g_s169RingIdx + 1) % S169_RING_SIZE;
    S169TraceRec* r = &g_s169Ring[idx];
    r->name   = name;
    r->caller = caller;
    r->self   = self;
    r->a1 = a1; r->a2 = a2; r->a3 = a3; r->a4 = a4;
    g_s169RingIdx = idx;
}

// ---- generic trampoline types ----------------------------------------------
typedef void  (__fastcall *Tc0)(void*);
typedef void* (__fastcall *Tc0r)(void*);
typedef unsigned char (__fastcall *Tc0b)(void*);
typedef int   (__fastcall *Tc0i)(void*);
typedef void  (__fastcall *Tc1)(void*, DWORD, DWORD);
typedef void* (__fastcall *Tc1r)(void*, DWORD, DWORD);
typedef unsigned char (__fastcall *Tc1b)(void*, DWORD, DWORD);
typedef void  (__fastcall *Tc2)(void*, DWORD, DWORD, DWORD);

int __fastcall HookS169_4035B0(void* self)
{
    int r = ((Tc0i)_S169_4035B0)(self);
    S169TracePush("S169::S169", (DWORD)_ReturnAddress(), (DWORD)self, (DWORD)r, 0, 0, 0);
    return r;
}

unsigned char __fastcall HookS169_403650(void* self)
{
    unsigned char r = ((Tc0b)_S169_403650)(self);
    S169TracePush("S169::sub_403650", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    return r;
}

unsigned char __fastcall HookS169_4037A0(void* self)
{
    unsigned char r = ((Tc0b)_S169_4037A0)(self);
    S169TracePush("S169::AreAnyPedActive", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    return r;
}

void __fastcall HookS169_4038E0(void* self)
{
    S169TracePush("S169::SetInUse", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_S169_4038E0)(self);
}

unsigned char __fastcall HookS169_4038F0(void* self)
{
    unsigned char r = ((Tc0b)_S169_4038F0)(self);
    S169TracePush("S169::GetInUse", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    return r;
}

int __fastcall HookS169_403BE0(void* self)
{
    int r = ((Tc0i)_S169_403BE0)(self);
    S169TracePush("S169::sub_403BE0", (DWORD)_ReturnAddress(), (DWORD)self, (DWORD)r, 0, 0, 0);
    return r;
}

unsigned char __fastcall HookS169_403C40(void* self)
{
    unsigned char r = ((Tc0b)_S169_403C40)(self);
    S169TracePush("S169::sub_403C40", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    return r;
}

unsigned char __fastcall HookS169_403D10(void* self)
{
    unsigned char r = ((Tc0b)_S169_403D10)(self);
    S169TracePush("S169::sub_403D10", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    return r;
}

unsigned char __fastcall HookS169_403D20(void* self)
{
    unsigned char r = ((Tc0b)_S169_403D20)(self);
    S169TracePush("S169::sub_403D20", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    return r;
}

void __fastcall HookS169_403DA0(void* self)
{
    S169TracePush("S169::sub_403DA0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_S169_403DA0)(self);
}

void __fastcall HookS169_403E90(void* self)
{
    S169TracePush("S169::ManageGroupPedObjectives", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_S169_403E90)(self);
}

void __fastcall HookS169_403FB0(void* self, DWORD d, DWORD a2)
{
    S169TracePush("S169::sub_403FB0", (DWORD)_ReturnAddress(), (DWORD)self, a2, 0, 0, 0);
    ((Tc1)_S169_403FB0)(self, 0, a2);
}

void __fastcall HookS169_404120(void* self, DWORD d, DWORD Index)
{
    S169TracePush("S169::sub_404120", (DWORD)_ReturnAddress(), (DWORD)self, Index, 0, 0, 0);
    ((Tc1)_S169_404120)(self, 0, Index);
}

void __fastcall HookS169_404400(void* self, DWORD d, DWORD pPed)
{
    S169TracePush("S169::sub_404400", (DWORD)_ReturnAddress(), (DWORD)self, pPed, 0, 0, 0);
    ((Tc1)_S169_404400)(self, 0, pPed);
}

void __fastcall HookS169_404420(void* self, DWORD d, DWORD a2, DWORD Id)
{
    S169TracePush("S169::AddPedtoList", (DWORD)_ReturnAddress(), (DWORD)self, a2, Id, 0, 0);
    ((Tc2)_S169_404420)(self, 0, a2, Id);
}

void* __fastcall HookS169_404450(void* self)
{
    void* r = ((Tc0r)_S169_404450)(self);
    S169TracePush("S169::sub_404450", (DWORD)_ReturnAddress(), (DWORD)self, (DWORD)r, 0, 0, 0);
    return r;
}

int __fastcall HookS169_404480(void* self)
{
    int r = ((Tc0i)_S169_404480)(self);
    S169TracePush("S169::sub_404480", (DWORD)_ReturnAddress(), (DWORD)self, (DWORD)r, 0, 0, 0);
    return r;
}

void* __fastcall HookS169_404490(void* self, DWORD d, DWORD arg0)
{
    void* r = ((Tc1r)_S169_404490)(self, 0, arg0);
    S169TracePush("S169::sub_404490", (DWORD)_ReturnAddress(), (DWORD)self, arg0, (DWORD)r, 0, 0);
    return r;
}

unsigned char __fastcall HookS169_4045D0(void* self)
{
    unsigned char r = ((Tc0b)_S169_4045D0)(self);
    S169TracePush("S169::sub_4045D0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    return r;
}

void __fastcall HookS169_4046F0(void* self, DWORD d, DWORD X)
{
    S169TracePush("S169::sub_4046F0", (DWORD)_ReturnAddress(), (DWORD)self, X, 0, 0, 0);
    ((Tc1)_S169_4046F0)(self, 0, X);
}

unsigned char __fastcall HookS169_404840(void* self)
{
    unsigned char r = ((Tc0b)_S169_404840)(self);
    S169TracePush("S169::sub_404840", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    return r;
}

unsigned char __fastcall HookS169_4048A0(void* self)
{
    unsigned char r = ((Tc0b)_S169_4048A0)(self);
    S169TracePush("S169::sub_4048A0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    return r;
}

unsigned char __fastcall HookS169_404900(void* self, DWORD d, DWORD X)
{
    unsigned char r = ((Tc1b)_S169_404900)(self, 0, X);
    S169TracePush("S169::sub_404900", (DWORD)_ReturnAddress(), (DWORD)self, X, r, 0, 0);
    return r;
}

unsigned char __fastcall HookS169_4049F0(void* self)
{
    unsigned char r = ((Tc0b)_S169_4049F0)(self);
    S169TracePush("S169::sub_4049F0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    return r;
}

void* __fastcall HookS169_404AD0(void* self, DWORD d, DWORD a2)
{
    void* r = ((Tc1r)_S169_404AD0)(self, 0, a2);
    S169TracePush("S169::sub_404AD0", (DWORD)_ReturnAddress(), (DWORD)self, a2, (DWORD)r, 0, 0);
    return r;
}

void __fastcall HookS169_404C90(void* self, DWORD d, DWORD pPed)
{
    S169TracePush("S169::AddPedToEndOfList", (DWORD)_ReturnAddress(), (DWORD)self, pPed, 0, 0, 0);
    ((Tc1)_S169_404C90)(self, 0, pPed);
}

unsigned char __fastcall HookS169_404CE0(void* self)
{
    unsigned char r = ((Tc0b)_S169_404CE0)(self);
    S169TracePush("S169::sub_404CE0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    return r;
}

void __fastcall HookS169_404D40(void* self, DWORD d, DWORD pPed)
{
    S169TracePush("S169::sub_404D40", (DWORD)_ReturnAddress(), (DWORD)self, pPed, 0, 0, 0);
    ((Tc1)_S169_404D40)(self, 0, pPed);
}

void __fastcall HookS169_404EF0(void* self, DWORD d, DWORD a2)
{
    S169TracePush("S169::sub_404EF0", (DWORD)_ReturnAddress(), (DWORD)self, a2, 0, 0, 0);
    ((Tc1)_S169_404EF0)(self, 0, a2);
}

unsigned char __fastcall HookS169_405240(void* self, DWORD d, DWORD a2)
{
    unsigned char r = ((Tc1b)_S169_405240)(self, 0, a2);
    S169TracePush("S169::sub_405240", (DWORD)_ReturnAddress(), (DWORD)self, a2, r, 0, 0);
    return r;
}

void __fastcall HookS169_405760(void* self, DWORD d, DWORD a2)
{
    S169TracePush("S169::sub_405760", (DWORD)_ReturnAddress(), (DWORD)self, a2, 0, 0, 0);
    ((Tc1)_S169_405760)(self, 0, a2);
}

void __fastcall HookS169_433360(void* self, DWORD d, DWORD ListSize)
{
    S169TracePush("S169::SetListSize", (DWORD)_ReturnAddress(), (DWORD)self, ListSize, 0, 0, 0);
    ((Tc1)_S169_433360)(self, 0, ListSize);
}

void* __fastcall HookS169_433370(void* self)
{
    void* r = ((Tc0r)_S169_433370)(self);
    S169TracePush("S169::sub_433370", (DWORD)_ReturnAddress(), (DWORD)self, (DWORD)r, 0, 0, 0);
    return r;
}

void __fastcall HookS169_439970(void* self)
{
    S169TracePush("S169::sub_439970", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0)_S169_439970)(self);
}

void DumpS169Ring(FILE* f)
{
    DWORD total = g_s169RingIdx;
    DWORD n = (total < S169_RING_SIZE) ? total : S169_RING_SIZE;
    fprintf(f, "S169-CALL RING (last %lu of %lu):\r\n",
            (unsigned long)n, (unsigned long)total);
    for (DWORD k = 0; k < n; ++k) {
        const S169TraceRec* r = &g_s169Ring[(g_s169RingIdx - n + 1 + k) % S169_RING_SIZE];
        if (!r->name) continue;
        fprintf(f, "  %-32s call=0x%08lX self=0x%08lX a1=0x%08lX a2=0x%08lX a3=0x%08lX a4=0x%08lX\r\n",
                r->name ? r->name : "?",
                (unsigned long)r->caller, (unsigned long)r->self,
                (unsigned long)r->a1, (unsigned long)r->a2,
                (unsigned long)r->a3, (unsigned long)r->a4);
    }
}

void DumpS169RingFile(void)
{
    FILE* f = fopen(kS169TapePath, "ab");
    if (!f) return;
    DWORD total = g_s169RingIdx;
    DWORD delta = total - g_s169Taped;
    if (delta == 0) {
        fclose(f);
        return;
    }
    if (delta > S169_RING_SIZE) {
        // ring wrapped past the tape: skip to the oldest still-valid entry
        g_s169Taped = total - S169_RING_SIZE;
        delta = S169_RING_SIZE;
    }
    for (DWORD k = 0; k < delta; ++k) {
        const S169TraceRec* r = &g_s169Ring[(g_s169Taped + k) % S169_RING_SIZE];
        if (!r->name) continue;
        fprintf(f, "  %-32s call=0x%08lX self=0x%08lX a1=0x%08lX a2=0x%08lX a3=0x%08lX a4=0x%08lX\r\n",
                r->name ? r->name : "?",
                (unsigned long)r->caller, (unsigned long)r->self,
                (unsigned long)r->a1, (unsigned long)r->a2,
                (unsigned long)r->a3, (unsigned long)r->a4);
    }
    g_s169Taped = total;
    fclose(f);
}
