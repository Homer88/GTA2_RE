#include <Windows.h>
#include <stdio.h>
#include <intrin.h>
#include "cPlayerTrace.h"

// Retail entry points (imagebase 0x3F0000 in gta2-resurected.exe).
LPVOID _Player_401B40 = (LPVOID)0x00401B40;
LPVOID _Player_401B90 = (LPVOID)0x00401B90;
LPVOID _Player_40CE50 = (LPVOID)0x0040CE50;
LPVOID _Player_40CE70 = (LPVOID)0x0040CE70;
LPVOID _Player_40E530 = (LPVOID)0x0040E530;
LPVOID _Player_40E570 = (LPVOID)0x0040E570;
LPVOID _Player_40E8D0 = (LPVOID)0x0040E8D0;
LPVOID _Player_40EC20 = (LPVOID)0x0040EC20;
LPVOID _Player_40F790 = (LPVOID)0x0040F790;
LPVOID _Player_40F820 = (LPVOID)0x0040F820;
LPVOID _Player_40F840 = (LPVOID)0x0040F840;
LPVOID _Player_411810 = (LPVOID)0x00411810;
LPVOID _Player_411820 = (LPVOID)0x00411820;
LPVOID _Player_411830 = (LPVOID)0x00411830;
LPVOID _Player_411840 = (LPVOID)0x00411840;
LPVOID _Player_411850 = (LPVOID)0x00411850;
LPVOID _Player_411860 = (LPVOID)0x00411860;
LPVOID _Player_41D020 = (LPVOID)0x0041D020;
LPVOID _Player_41DC40 = (LPVOID)0x0041DC40;
LPVOID _Player_41DC70 = (LPVOID)0x0041DC70;
LPVOID _Player_41E1E0 = (LPVOID)0x0041E1E0;
LPVOID _Player_41E260 = (LPVOID)0x0041E260;
LPVOID _Player_41E390 = (LPVOID)0x0041E390;
LPVOID _Player_4202A0 = (LPVOID)0x004202A0;
LPVOID _Player_4202E0 = (LPVOID)0x004202E0;
LPVOID _Player_420360 = (LPVOID)0x00420360;
LPVOID _Player_420390 = (LPVOID)0x00420390;
LPVOID _Player_421100 = (LPVOID)0x00421100;
LPVOID _Player_421150 = (LPVOID)0x00421150;
LPVOID _Player_4211A0 = (LPVOID)0x004211A0;
LPVOID _Player_4211C0 = (LPVOID)0x004211C0;
LPVOID _Player_421260 = (LPVOID)0x00421260;
LPVOID _Player_421270 = (LPVOID)0x00421270;
LPVOID _Player_4212A0 = (LPVOID)0x004212A0;
LPVOID _Player_4212B0 = (LPVOID)0x004212B0;
LPVOID _Player_421980 = (LPVOID)0x00421980;
LPVOID _Player_421990 = (LPVOID)0x00421990;
LPVOID _Player_4219A0 = (LPVOID)0x004219A0;
LPVOID _Player_4219D0 = (LPVOID)0x004219D0;
LPVOID _Player_424470 = (LPVOID)0x00424470;
LPVOID _Player_4348F0 = (LPVOID)0x004348F0;
LPVOID _Player_434900 = (LPVOID)0x00434900;
LPVOID _Player_434920 = (LPVOID)0x00434920;
LPVOID _Player_434940 = (LPVOID)0x00434940;
LPVOID _Player_434950 = (LPVOID)0x00434950;
LPVOID _Player_453A90 = (LPVOID)0x00453A90;
LPVOID _Player_453AB0 = (LPVOID)0x00453AB0;
LPVOID _Player_45A970 = (LPVOID)0x0045A970;
LPVOID _Player_45B0C0 = (LPVOID)0x0045B0C0;
LPVOID _Player_45B0D0 = (LPVOID)0x0045B0D0;
LPVOID _Player_461DB0 = (LPVOID)0x00461DB0;
LPVOID _Player_4766A0 = (LPVOID)0x004766A0;
LPVOID _Player_4766B0 = (LPVOID)0x004766B0;
LPVOID _Player_4766C0 = (LPVOID)0x004766C0;
LPVOID _Player_4766D0 = (LPVOID)0x004766D0;
LPVOID _Player_476700 = (LPVOID)0x00476700;
LPVOID _Player_476730 = (LPVOID)0x00476730;
LPVOID _Player_482CC0 = (LPVOID)0x00482CC0;
LPVOID _Player_49DD10 = (LPVOID)0x0049DD10;
LPVOID _Player_49DD20 = (LPVOID)0x0049DD20;
LPVOID _Player_49DD30 = (LPVOID)0x0049DD30;
LPVOID _Player_49DD80 = (LPVOID)0x0049DD80;
LPVOID _Player_49DDF0 = (LPVOID)0x0049DDF0;
LPVOID _Player_49DE40 = (LPVOID)0x0049DE40;
LPVOID _Player_49DEF0 = (LPVOID)0x0049DEF0;
LPVOID _Player_49DF90 = (LPVOID)0x0049DF90;
LPVOID _Player_49E040 = (LPVOID)0x0049E040;
LPVOID _Player_49E270 = (LPVOID)0x0049E270;
LPVOID _Player_49E650 = (LPVOID)0x0049E650;
LPVOID _Player_49E820 = (LPVOID)0x0049E820;
LPVOID _Player_49E850 = (LPVOID)0x0049E850;
LPVOID _Player_49E8E0 = (LPVOID)0x0049E8E0;
LPVOID _Player_49E950 = (LPVOID)0x0049E950;
LPVOID _Player_49E980 = (LPVOID)0x0049E980;
LPVOID _Player_49EA60 = (LPVOID)0x0049EA60;
LPVOID _Player_49EA70 = (LPVOID)0x0049EA70;
LPVOID _Player_49EC80 = (LPVOID)0x0049EC80;
LPVOID _Player_49ECA0 = (LPVOID)0x0049ECA0;
LPVOID _Player_49ECC0 = (LPVOID)0x0049ECC0;
LPVOID _Player_49ED00 = (LPVOID)0x0049ED00;
LPVOID _Player_49ED60 = (LPVOID)0x0049ED60;
LPVOID _Player_49EDC0 = (LPVOID)0x0049EDC0;
LPVOID _Player_49EE10 = (LPVOID)0x0049EE10;
LPVOID _Player_49EE80 = (LPVOID)0x0049EE80;
LPVOID _Player_49EEB0 = (LPVOID)0x0049EEB0;
LPVOID _Player_49EF50 = (LPVOID)0x0049EF50;
LPVOID _Player_49EF80 = (LPVOID)0x0049EF80;
LPVOID _Player_49F010 = (LPVOID)0x0049F010;
LPVOID _Player_49F170 = (LPVOID)0x0049F170;
LPVOID _Player_49F1B0 = (LPVOID)0x0049F1B0;
LPVOID _Player_49F280 = (LPVOID)0x0049F280;
LPVOID _Player_49F2D0 = (LPVOID)0x0049F2D0;
LPVOID _Player_49F350 = (LPVOID)0x0049F350;
LPVOID _Player_49F460 = (LPVOID)0x0049F460;
LPVOID _Player_49F4E0 = (LPVOID)0x0049F4E0;
LPVOID _Player_49F4F0 = (LPVOID)0x0049F4F0;
LPVOID _Player_49F500 = (LPVOID)0x0049F500;
LPVOID _Player_49F570 = (LPVOID)0x0049F570;
LPVOID _Player_49F660 = (LPVOID)0x0049F660;
LPVOID _Player_49F6C0 = (LPVOID)0x0049F6C0;
LPVOID _Player_49F720 = (LPVOID)0x0049F720;
LPVOID _Player_49F930 = (LPVOID)0x0049F930;
LPVOID _Player_49FAC0 = (LPVOID)0x0049FAC0;
LPVOID _Player_49FB00 = (LPVOID)0x0049FB00;
LPVOID _Player_49FBE0 = (LPVOID)0x0049FBE0;
LPVOID _Player_49FDC0 = (LPVOID)0x0049FDC0;
LPVOID _Player_49FF70 = (LPVOID)0x0049FF70;
LPVOID _Player_49FF80 = (LPVOID)0x0049FF80;
LPVOID _Player_4A0020 = (LPVOID)0x004A0020;
LPVOID _Player_4A0080 = (LPVOID)0x004A0080;
LPVOID _Player_4A0120 = (LPVOID)0x004A0120;
LPVOID _Player_4A0290 = (LPVOID)0x004A0290;
LPVOID _Player_4A0560 = (LPVOID)0x004A0560;
LPVOID _Player_4A0850 = (LPVOID)0x004A0850;
LPVOID _Player_4A0900 = (LPVOID)0x004A0900;
LPVOID _Player_4A0930 = (LPVOID)0x004A0930;
LPVOID _Player_4A0960 = (LPVOID)0x004A0960;
LPVOID _Player_4A09B0 = (LPVOID)0x004A09B0;
LPVOID _Player_4A0C60 = (LPVOID)0x004A0C60;
LPVOID _Player_4A0CC0 = (LPVOID)0x004A0CC0;
LPVOID _Player_4A0D10 = (LPVOID)0x004A0D10;
LPVOID _Player_4A0D40 = (LPVOID)0x004A0D40;
LPVOID _Player_4A0F30 = (LPVOID)0x004A0F30;
LPVOID _Player_4A1130 = (LPVOID)0x004A1130;
LPVOID _Player_4A1360 = (LPVOID)0x004A1360;
LPVOID _Player_4A16B0 = (LPVOID)0x004A16B0;
LPVOID _Player_4A1B20 = (LPVOID)0x004A1B20;
LPVOID _Player_4A1BA0 = (LPVOID)0x004A1BA0;
LPVOID _Player_4A1BE0 = (LPVOID)0x004A1BE0;
LPVOID _Player_4A1DA0 = (LPVOID)0x004A1DA0;
LPVOID _Player_4A20E0 = (LPVOID)0x004A20E0;
LPVOID _Player_4A2240 = (LPVOID)0x004A2240;
LPVOID _Player_4A2640 = (LPVOID)0x004A2640;
LPVOID _Player_4A26C0 = (LPVOID)0x004A26C0;
LPVOID _Player_4A2980 = (LPVOID)0x004A2980;
LPVOID _Player_4A2A30 = (LPVOID)0x004A2A30;
LPVOID _Player_4A2B40 = (LPVOID)0x004A2B40;
LPVOID _Player_4A2C70 = (LPVOID)0x004A2C70;
LPVOID _Player_4A2D70 = (LPVOID)0x004A2D70;
LPVOID _Player_4A2DB0 = (LPVOID)0x004A2DB0;
LPVOID _Player_4A2E00 = (LPVOID)0x004A2E00;
LPVOID _Player_4A2E30 = (LPVOID)0x004A2E30;
LPVOID _Player_4A2F20 = (LPVOID)0x004A2F20;
LPVOID _Player_4A2F90 = (LPVOID)0x004A2F90;
LPVOID _Player_4A30A0 = (LPVOID)0x004A30A0;
LPVOID _Player_4A3120 = (LPVOID)0x004A3120;
LPVOID _Player_4A3140 = (LPVOID)0x004A3140;
LPVOID _Player_4A31B0 = (LPVOID)0x004A31B0;
LPVOID _Player_4A32D0 = (LPVOID)0x004A32D0;
LPVOID _Player_4A34A0 = (LPVOID)0x004A34A0;
LPVOID _Player_4A3A40 = (LPVOID)0x004A3A40;
LPVOID _Player_4A3DF0 = (LPVOID)0x004A3DF0;
LPVOID _Player_4A3FB0 = (LPVOID)0x004A3FB0;
LPVOID _Player_4A4170 = (LPVOID)0x004A4170;
LPVOID _Player_4A4270 = (LPVOID)0x004A4270;
LPVOID _Player_4A4310 = (LPVOID)0x004A4310;
LPVOID _Player_4A4490 = (LPVOID)0x004A4490;
LPVOID _Player_4A4570 = (LPVOID)0x004A4570;
LPVOID _Player_4A4780 = (LPVOID)0x004A4780;
LPVOID _Player_4A47F0 = (LPVOID)0x004A47F0;
LPVOID _Player_4A4890 = (LPVOID)0x004A4890;
LPVOID _Player_4A48C0 = (LPVOID)0x004A48C0;
LPVOID _Player_4A48E0 = (LPVOID)0x004A48E0;
LPVOID _Player_4A4930 = (LPVOID)0x004A4930;
LPVOID _Player_4A4940 = (LPVOID)0x004A4940;
LPVOID _Player_4A49B0 = (LPVOID)0x004A49B0;
LPVOID _Player_4A49C0 = (LPVOID)0x004A49C0;
LPVOID _Player_4A4AE0 = (LPVOID)0x004A4AE0;
LPVOID _Player_4A4C40 = (LPVOID)0x004A4C40;
LPVOID _Player_4A4C90 = (LPVOID)0x004A4C90;
LPVOID _Player_4A4CB0 = (LPVOID)0x004A4CB0;
LPVOID _Player_4A4CF0 = (LPVOID)0x004A4CF0;
LPVOID _Player_4A4D50 = (LPVOID)0x004A4D50;
LPVOID _Player_4A4E10 = (LPVOID)0x004A4E10;
LPVOID _Player_4A4E70 = (LPVOID)0x004A4E70;
LPVOID _Player_4A4EA0 = (LPVOID)0x004A4EA0;
LPVOID _Player_4A5100 = (LPVOID)0x004A5100;
LPVOID _Player_4A5130 = (LPVOID)0x004A5130;
LPVOID _Player_4A5150 = (LPVOID)0x004A5150;
LPVOID _Player_4A5180 = (LPVOID)0x004A5180;
LPVOID _Player_4A51C0 = (LPVOID)0x004A51C0;
LPVOID _Player_4A5220 = (LPVOID)0x004A5220;
LPVOID _Player_4A5300 = (LPVOID)0x004A5300;
LPVOID _Player_4A53D0 = (LPVOID)0x004A53D0;
LPVOID _Player_4A5400 = (LPVOID)0x004A5400;
LPVOID _Player_4A5460 = (LPVOID)0x004A5460;
LPVOID _Player_4A5570 = (LPVOID)0x004A5570;
LPVOID _Player_4A5600 = (LPVOID)0x004A5600;
LPVOID _Player_4A5640 = (LPVOID)0x004A5640;
LPVOID _Player_4A5690 = (LPVOID)0x004A5690;
LPVOID _Player_4A5710 = (LPVOID)0x004A5710;
LPVOID _Player_4A5780 = (LPVOID)0x004A5780;
LPVOID _Player_4A59A0 = (LPVOID)0x004A59A0;
LPVOID _Player_4A5A50 = (LPVOID)0x004A5A50;
LPVOID _Player_4A5AD0 = (LPVOID)0x004A5AD0;
LPVOID _Player_4A5B40 = (LPVOID)0x004A5B40;
LPVOID _Player_4A5E90 = (LPVOID)0x004A5E90;
LPVOID _Player_4A6050 = (LPVOID)0x004A6050;
LPVOID _Player_4A6100 = (LPVOID)0x004A6100;
LPVOID _Player_4A61F0 = (LPVOID)0x004A61F0;
LPVOID _Player_4A62B0 = (LPVOID)0x004A62B0;
LPVOID _Player_4A6310 = (LPVOID)0x004A6310;
LPVOID _Player_4A6350 = (LPVOID)0x004A6350;
LPVOID _Player_4A6400 = (LPVOID)0x004A6400;
LPVOID _Player_4A6530 = (LPVOID)0x004A6530;
LPVOID _Player_4A65E0 = (LPVOID)0x004A65E0;
LPVOID _Player_4A6610 = (LPVOID)0x004A6610;
LPVOID _Player_4A6900 = (LPVOID)0x004A6900;
LPVOID _Player_4A69A0 = (LPVOID)0x004A69A0;
LPVOID _Player_4A6A80 = (LPVOID)0x004A6A80;
LPVOID _Player_4A6B20 = (LPVOID)0x004A6B20;
LPVOID _Player_4A6C80 = (LPVOID)0x004A6C80;
LPVOID _Player_4A6EF0 = (LPVOID)0x004A6EF0;
LPVOID _Player_4A6FD0 = (LPVOID)0x004A6FD0;
LPVOID _Player_4A7010 = (LPVOID)0x004A7010;
LPVOID _Player_4A7680 = (LPVOID)0x004A7680;
LPVOID _Player_4A76D0 = (LPVOID)0x004A76D0;
LPVOID _Player_4A7910 = (LPVOID)0x004A7910;
LPVOID _Player_4A7B70 = (LPVOID)0x004A7B70;
LPVOID _Player_4A7BA0 = (LPVOID)0x004A7BA0;
LPVOID _Player_4A7E80 = (LPVOID)0x004A7E80;
LPVOID _Player_4A81E0 = (LPVOID)0x004A81E0;
LPVOID _Player_4A8340 = (LPVOID)0x004A8340;
LPVOID _Player_4A83C0 = (LPVOID)0x004A83C0;
LPVOID _Player_4BA0A0 = (LPVOID)0x004BA0A0;
LPVOID _Player_4C7340 = (LPVOID)0x004C7340;
LPVOID _Player_4CCAB0 = (LPVOID)0x004CCAB0;
LPVOID _Player_4CCAD0 = (LPVOID)0x004CCAD0;
LPVOID _Player_4CCAE0 = (LPVOID)0x004CCAE0;

struct PlayerTraceRec {
    const char* name;
    DWORD caller;
    DWORD self;
    DWORD a1, a2, a3, a4;
};

#define PLAYER_RING_SIZE 32768
static PlayerTraceRec g_playerRing[PLAYER_RING_SIZE];
static volatile DWORD g_playerRingIdx = 0;
static DWORD g_playerTaped = 0;
static const char* kPlayerTapePath = "C:\\games\\gta2\\player_trace.log";

static void PlayerTracePush(const char* name, DWORD caller, DWORD self,
                            DWORD a1, DWORD a2, DWORD a3, DWORD a4)
{
    DWORD idx = (g_playerRingIdx + 1) % PLAYER_RING_SIZE;
    PlayerTraceRec* r = &g_playerRing[idx];
    r->name   = name;
    r->caller = caller;
    r->self   = self;
    r->a1 = a1; r->a2 = a2; r->a3 = a3; r->a4 = a4;
    g_playerRingIdx = idx;
}

// ---- generic trampoline types ------------------------------------------------
// TcN   = returns DWORD, N stack args (+ self, dummy edx)
// TcNv  = void return,   N stack args
typedef DWORD (__fastcall *Tc0)(void*, DWORD);
typedef void  (__fastcall *Tc0v)(void*, DWORD);
typedef DWORD (__fastcall *Tc1)(void*, DWORD, DWORD);
typedef void  (__fastcall *Tc1v)(void*, DWORD, DWORD);
typedef DWORD (__fastcall *Tc2)(void*, DWORD, DWORD, DWORD);
typedef void  (__fastcall *Tc2v)(void*, DWORD, DWORD, DWORD);
typedef DWORD (__fastcall *Tc3)(void*, DWORD, DWORD, DWORD, DWORD);
typedef void  (__fastcall *Tc3v)(void*, DWORD, DWORD, DWORD, DWORD);
typedef DWORD (__fastcall *Tc4)(void*, DWORD, DWORD, DWORD, DWORD, DWORD);
typedef void  (__fastcall *Tc4v)(void*, DWORD, DWORD, DWORD, DWORD, DWORD);
typedef DWORD (__fastcall *Tc5)(void*, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
typedef void  (__fastcall *Tc5v)(void*, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);

DWORD __fastcall HookPlayer_401B40(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_401B40)(self, 0, a0, a1);
    PlayerTracePush("Player::sub_401B40", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_401B90(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_401B90)(self, 0, a0, a1);
    PlayerTracePush("Player::sub_401B90", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_40CE50(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_40CE50)(self, 0, a0);
    PlayerTracePush("Player::CheckCondition", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_40CE70(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_40CE70)(self, 0, a0);
    PlayerTracePush("Player::sub_40CE70", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_40E530(void* self, DWORD d, DWORD a0)
{
    PlayerTracePush("Player::sub_40E530", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Player_40E530)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_40E570(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_40E570)(self, 0, a0);
    PlayerTracePush("Player::IsCurrentPlayer", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_40E8D0(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2)
{
    DWORD r = ((Tc3)_Player_40E8D0)(self, 0, a0, a1, a2);
    PlayerTracePush("Player::sub_40E8D0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, r);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_40EC20(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3)
{
    DWORD r = ((Tc4)_Player_40EC20)(self, 0, a0, a1, a2, a3);
    PlayerTracePush("Player::TransformSprite", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, a3);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_40F790(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_40F790)(self, 0, a0);
    PlayerTracePush("Player::sub_40F790", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_40F820(void* self, DWORD d, DWORD a0)
{
    PlayerTracePush("Player::sub_40F820", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Player_40F820)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_40F840(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_40F840)(self, 0);
    PlayerTracePush("Player::IsOnScreen", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_411810(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_411810)(self, 0);
    PlayerTracePush("Player::sub_411810", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_411820(void* self, DWORD d, DWORD a0)
{
    PlayerTracePush("Player::sub_411820", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Player_411820)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_411830(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_411830)(self, 0);
    PlayerTracePush("Player::IsAudioEnabled", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_411840(void* self, DWORD d, DWORD a0)
{
    PlayerTracePush("Player::ReadEngineValue", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Player_411840)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_411850(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_411850)(self, 0, a0);
    PlayerTracePush("Player::ReadEngineValue2", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_411860(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_411860)(self, 0);
    PlayerTracePush("Player::GetSoundHandle", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_41D020(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_41D020)(self, 0);
    PlayerTracePush("Player::GetPed", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_41DC40(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_41DC40)(self, 0, a0);
    PlayerTracePush("Player::AddMoney", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_41DC70(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_41DC70)(self, 0);
    PlayerTracePush("Player::GetCurrentPlayer", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_41E1E0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_41E1E0)(self, 0);
    PlayerTracePush("Player::Init", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_41E260(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_41E260)(self, 0, a0);
    PlayerTracePush("Player::WorldToScreen", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_41E390(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_41E390)(self, 0);
    PlayerTracePush("Player::IsActionAllowed", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4202A0(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_4202A0)(self, 0, a0, a1);
    PlayerTracePush("Player::sub_4202A0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4202E0(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_4202E0)(self, 0, a0, a1);
    PlayerTracePush("Player::sub_4202E0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_420360(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_420360)(self, 0);
    PlayerTracePush("Player::sub_420360", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_420390(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_420390)(self, 0, a0);
    PlayerTracePush("Player::sub_420390", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_421100(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_421100)(self, 0);
    PlayerTracePush("Player::IsStateEightWithCondition", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_421150(void* self, DWORD d, DWORD a0)
{
    PlayerTracePush("Player::sub_421150", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Player_421150)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookPlayer_4211A0(void* self, DWORD d, DWORD a0)
{
    PlayerTracePush("Player::GetSpeed", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Player_4211A0)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4211C0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4211C0)(self, 0, a0);
    PlayerTracePush("Player::sub_4211C0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_421260(void* self, DWORD d)
{
    PlayerTracePush("Player::ClearPlayerFlag", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_421260)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_421270(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_421270)(self, 0);
    PlayerTracePush("Player::sub_421270", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4212A0(void* self, DWORD d)
{
    PlayerTracePush("Player::SetAttackChanged", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4212A0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookPlayer_4212B0(void* self, DWORD d)
{
    PlayerTracePush("Player::SetAttackIsChanged", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4212B0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_421980(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_421980)(self, 0);
    PlayerTracePush("Player::GetMoneyPlayer", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_421990(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_421990)(self, 0, a0);
    PlayerTracePush("Player::DecreaseInMoney", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4219A0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4219A0)(self, 0, a0);
    PlayerTracePush("Player::sub_4219A0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4219D0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4219D0)(self, 0);
    PlayerTracePush("Player::GetId", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_424470(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_424470)(self, 0, a0);
    PlayerTracePush("Player::NotMoney", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4348F0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4348F0)(self, 0, a0);
    PlayerTracePush("Player::sub_4348F0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_434900(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_434900)(self, 0);
    PlayerTracePush("Player::GetMultiPlayerMode", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_434920(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_434920)(self, 0, a0);
    PlayerTracePush("Player::GetPowerUp", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_434940(void* self, DWORD d, DWORD a0)
{
    PlayerTracePush("Player::DecrPowerUp", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Player_434940)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookPlayer_434950(void* self, DWORD d, DWORD a0)
{
    PlayerTracePush("Player::SetPlayerState", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Player_434950)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_453A90(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_453A90)(self, 0, a0);
    PlayerTracePush("Player::sub_453A90", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_453AB0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_453AB0)(self, 0);
    PlayerTracePush("Player::sub_453AB0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_45A970(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_45A970)(self, 0, a0);
    PlayerTracePush("Player::Player_Des", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_45B0C0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_45B0C0)(self, 0);
    PlayerTracePush("Player::IsMainPedSet", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_45B0D0(void* self, DWORD d)
{
    PlayerTracePush("Player::SetActive", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_45B0D0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_461DB0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_461DB0)(self, 0);
    PlayerTracePush("Player::NextPlayer", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4766A0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4766A0)(self, 0);
    PlayerTracePush("Player::GetMultiPlayer", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4766B0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4766B0)(self, 0, a0);
    PlayerTracePush("Player::SetMultiPlayer", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4766C0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4766C0)(self, 0);
    PlayerTracePush("Player::getMoney", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4766D0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4766D0)(self, 0);
    PlayerTracePush("Player::GetRespect", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_476700(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_476700)(self, 0);
    PlayerTracePush("Player::sub_476700", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_476730(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_476730)(self, 0);
    PlayerTracePush("Player::sub_476730", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_482CC0(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2)
{
    DWORD r = ((Tc3)_Player_482CC0)(self, 0, a0, a1, a2);
    PlayerTracePush("Player::sub_482CC0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, r);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49DD10(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49DD10)(self, 0);
    PlayerTracePush("Player::GetCarWithTrailer", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_49DD20(void* self, DWORD d, DWORD a0)
{
    PlayerTracePush("Player::SetActivePlayer", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Player_49DD20)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_49DD30(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49DD30)(self, 0);
    PlayerTracePush("Player::ApplyEntryControlState", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49DD80(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49DD80)(self, 0);
    PlayerTracePush("Player::IsTrailerAttached", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49DDF0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49DDF0)(self, 0);
    PlayerTracePush("Player::sub_49DDF0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49DE40(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49DE40)(self, 0);
    PlayerTracePush("Player::sub_49DE40", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49DEF0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49DEF0)(self, 0);
    PlayerTracePush("Player::SavePlayerGlobals2", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49DF90(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49DF90)(self, 0);
    PlayerTracePush("Player::sub_49DF90", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49E040(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49E040)(self, 0);
    PlayerTracePush("Player::RestorePlayerGlobals", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49E270(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49E270)(self, 0);
    PlayerTracePush("Player::IsVisible", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49E650(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_49E650)(self, 0, a0, a1);
    PlayerTracePush("Player::GetRelativePosition", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49E820(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49E820)(self, 0);
    PlayerTracePush("Player::sub_49E820", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49E850(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_49E850)(self, 0, a0);
    PlayerTracePush("Player::sub_49E850", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49E8E0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_49E8E0)(self, 0, a0);
    PlayerTracePush("Player::sub_49E8E0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49E950(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49E950)(self, 0);
    PlayerTracePush("Player::UpdateSoundFlagDispatch", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49E980(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49E980)(self, 0);
    PlayerTracePush("Player::UpdateTargetScreenPos", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_49EA60(void* self, DWORD d)
{
    PlayerTracePush("Player::UseAmmo", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_49EA60)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_49EA70(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49EA70)(self, 0);
    PlayerTracePush("Player::AmmunitionUpdate", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49EC80(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49EC80)(self, 0);
    PlayerTracePush("Player::CacheCarEngineValue", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49ECA0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49ECA0)(self, 0);
    PlayerTracePush("Player::CacheCarEngineState", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49ECC0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49ECC0)(self, 0);
    PlayerTracePush("Player::SetActiveEngine", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49ED00(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49ED00)(self, 0);
    PlayerTracePush("Player::UpdateCarPosition", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49ED60(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49ED60)(self, 0);
    PlayerTracePush("Player::sub_49ED60", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49EDC0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49EDC0)(self, 0);
    PlayerTracePush("Player::ConvertToScreen", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49EE10(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_49EE10)(self, 0, a0);
    PlayerTracePush("Player::sub_49EE10", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49EE80(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49EE80)(self, 0);
    PlayerTracePush("Player::UpdateCarSprite", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49EEB0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49EEB0)(self, 0);
    PlayerTracePush("Player::UpdateCarSpriteWithTrailer", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49EF50(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_49EF50)(self, 0, a0);
    PlayerTracePush("Player::sub_49EF50", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49EF80(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49EF80)(self, 0);
    PlayerTracePush("Player::IsSpriteActiveAndCurrent", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49F010(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49F010)(self, 0);
    PlayerTracePush("Player::sub_49F010", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49F170(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49F170)(self, 0);
    PlayerTracePush("Player::AreTrailerSpritesActive", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49F1B0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49F1B0)(self, 0);
    PlayerTracePush("Player::SetupCarBlips", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49F280(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49F280)(self, 0);
    PlayerTracePush("Player::ApplyAlarmControlState", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49F2D0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49F2D0)(self, 0);
    PlayerTracePush("Player::sub_49F2D0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49F350(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49F350)(self, 0);
    PlayerTracePush("Player::HandleCarSurface", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49F460(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_49F460)(self, 0, a0);
    PlayerTracePush("Player::sub_49F460", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49F4E0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49F4E0)(self, 0);
    PlayerTracePush("Player::sub_49F4E0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49F4F0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49F4F0)(self, 0);
    PlayerTracePush("Player::sub_49F4F0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49F500(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49F500)(self, 0);
    PlayerTracePush("Player::sub_49F500", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49F570(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_49F570)(self, 0, a0);
    PlayerTracePush("Player::sub_49F570", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49F660(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_49F660)(self, 0, a0);
    PlayerTracePush("Player::GetCarHudSourcePosition", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49F6C0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_49F6C0)(self, 0, a0);
    PlayerTracePush("Player::sub_49F6C0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49F720(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_49F720)(self, 0, a0);
    PlayerTracePush("Player::sub_49F720", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49F930(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_49F930)(self, 0, a0);
    PlayerTracePush("Player::UpdateTrackedCar", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49FAC0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_49FAC0)(self, 0);
    PlayerTracePush("Player::ResetWeaponTimers", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49FB00(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3, DWORD a4)
{
    DWORD r = ((Tc5)_Player_49FB00)(self, 0, a0, a1, a2, a3, a4);
    PlayerTracePush("Player::sub_49FB00", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, a3);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49FBE0(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_49FBE0)(self, 0, a0, a1);
    PlayerTracePush("Player::sub_49FBE0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49FDC0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_49FDC0)(self, 0, a0);
    PlayerTracePush("Player::RefreshCarSpriteAndBlip", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49FF70(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_49FF70)(self, 0, a0);
    PlayerTracePush("Player::sub_49FF70", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_49FF80(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_49FF80)(self, 0, a0);
    PlayerTracePush("Player::sub_49FF80", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A0020(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A0020)(self, 0);
    PlayerTracePush("Player::AddCarSpriteToRender", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A0080(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A0080)(self, 0);
    PlayerTracePush("Player::sub_4A0080", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A0120(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3)
{
    DWORD r = ((Tc4)_Player_4A0120)(self, 0, a0, a1, a2, a3);
    PlayerTracePush("Player::sub_4A0120", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, a3);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A0290(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A0290)(self, 0);
    PlayerTracePush("Player::UpdatePlayerCarVisual", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A0560(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A0560)(self, 0);
    PlayerTracePush("Player::RenderArrowsTrailer", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A0850(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2)
{
    DWORD r = ((Tc3)_Player_4A0850)(self, 0, a0, a1, a2);
    PlayerTracePush("Player::UpdateCarArrows", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, r);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A0900(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A0900)(self, 0, a0);
    PlayerTracePush("Player::sub_4A0900", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A0930(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A0930)(self, 0, a0);
    PlayerTracePush("Player::sub_4A0930", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A0960(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A0960)(self, 0, a0);
    PlayerTracePush("Player::sub_4A0960", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A09B0(void* self, DWORD d, DWORD a0, DWORD a1)
{
    PlayerTracePush("Player::sub_4A09B0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, 0, 0);
    ((Tc2v)_Player_4A09B0)(self, 0, a0, a1);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A0C60(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A0C60)(self, 0);
    PlayerTracePush("Player::UpdateHudCarPosition", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A0CC0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A0CC0)(self, 0);
    PlayerTracePush("Player::FinalizeHudCarPosition", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A0D10(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_4A0D10)(self, 0, a0, a1);
    PlayerTracePush("Player::sub_4A0D10", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A0D40(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3, DWORD a4)
{
    DWORD r = ((Tc5)_Player_4A0D40)(self, 0, a0, a1, a2, a3, a4);
    PlayerTracePush("Player::UpdateCarWeapon", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, a3);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A0F30(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A0F30)(self, 0, a0);
    PlayerTracePush("Player::UpdateCarArrows2", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A1130(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A1130)(self, 0, a0);
    PlayerTracePush("Player::sub_4A1130", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A1360(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A1360)(self, 0, a0);
    PlayerTracePush("Player::sub_4A1360", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A16B0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A16B0)(self, 0);
    PlayerTracePush("Player::sub_4A16B0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A1B20(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A1B20)(self, 0);
    PlayerTracePush("Player::sub_4A1B20", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A1BA0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A1BA0)(self, 0);
    PlayerTracePush("Player::IncCounterTo20", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A1BE0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A1BE0)(self, 0);
    PlayerTracePush("Player::ResetPlayerState", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A1DA0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A1DA0)(self, 0);
    PlayerTracePush("Player::sub_4A1DA0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A20E0(void* self, DWORD d)
{
    PlayerTracePush("Player::sub_4A20E0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4A20E0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A2240(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A2240)(self, 0, a0);
    PlayerTracePush("Player::sub_4A2240", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A2640(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A2640)(self, 0, a0);
    PlayerTracePush("Player::sub_4A2640", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A26C0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A26C0)(self, 0, a0);
    PlayerTracePush("Player::UpdatePlayerSpriteFlag", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A2980(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A2980)(self, 0);
    PlayerTracePush("Player::ProcessArrows", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A2A30(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A2A30)(self, 0);
    PlayerTracePush("Player::sub_4A2A30", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A2B40(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A2B40)(self, 0);
    PlayerTracePush("Player::sub_4A2B40", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A2C70(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A2C70)(self, 0);
    PlayerTracePush("Player::sub_4A2C70", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A2D70(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A2D70)(self, 0);
    PlayerTracePush("Player::sub_4A2D70", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A2DB0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A2DB0)(self, 0);
    PlayerTracePush("Player::TryStartRaceMusic", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A2E00(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2)
{
    DWORD r = ((Tc3)_Player_4A2E00)(self, 0, a0, a1, a2);
    PlayerTracePush("Player::sub_4A2E00", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, r);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A2E30(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A2E30)(self, 0, a0);
    PlayerTracePush("Player::PlaceCar", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A2F20(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A2F20)(self, 0);
    PlayerTracePush("Player::UpdateHudCarState", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A2F90(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_4A2F90)(self, 0, a0, a1);
    PlayerTracePush("Player::sub_4A2F90", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A30A0(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_4A30A0)(self, 0, a0, a1);
    PlayerTracePush("Player::sub_4A30A0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A3120(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A3120)(self, 0);
    PlayerTracePush("Player::Render", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A3140(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_4A3140)(self, 0, a0, a1);
    PlayerTracePush("Player::sub_4A3140", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A31B0(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3)
{
    DWORD r = ((Tc4)_Player_4A31B0)(self, 0, a0, a1, a2, a3);
    PlayerTracePush("Player::sub_4A31B0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, a3);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A32D0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A32D0)(self, 0, a0);
    PlayerTracePush("Player::sub_4A32D0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A34A0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A34A0)(self, 0, a0);
    PlayerTracePush("Player::sub_4A34A0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A3A40(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_4A3A40)(self, 0, a0, a1);
    PlayerTracePush("Player::sub_4A3A40", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A3DF0(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_4A3DF0)(self, 0, a0, a1);
    PlayerTracePush("Player::sub_4A3DF0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A3FB0(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_4A3FB0)(self, 0, a0, a1);
    PlayerTracePush("Player::sub_4A3FB0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A4170(void* self, DWORD d, DWORD a0, DWORD a1)
{
    PlayerTracePush("Player::sub_4A4170", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, 0, 0);
    ((Tc2v)_Player_4A4170)(self, 0, a0, a1);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookPlayer_4A4270(void* self, DWORD d, DWORD a0, DWORD a1)
{
    PlayerTracePush("Player::sub_4A4270", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, 0, 0);
    ((Tc2v)_Player_4A4270)(self, 0, a0, a1);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A4310(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A4310)(self, 0);
    PlayerTracePush("Player::sub_4A4310", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A4490(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A4490)(self, 0);
    PlayerTracePush("Player::UpdateHornState", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A4570(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A4570)(self, 0);
    PlayerTracePush("Player::UpdateControlState", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A4780(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_4A4780)(self, 0, a0, a1);
    PlayerTracePush("Player::UpdateRecentCarList", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A47F0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A47F0)(self, 0, a0);
    PlayerTracePush("Player::sub_4A47F0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A4890(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A4890)(self, 0, a0);
    PlayerTracePush("Player::sub_4A4890", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A48C0(void* self, DWORD d)
{
    PlayerTracePush("Player::SetDefautWeapon", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4A48C0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A48E0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A48E0)(self, 0);
    PlayerTracePush("Player::SetActivePowerUps", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A4930(void* self, DWORD d, DWORD a0)
{
    PlayerTracePush("Player::SetPlayer", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Player_4A4930)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A4940(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A4940)(self, 0, a0);
    PlayerTracePush("Player::sub_4A4940", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A49B0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A49B0)(self, 0);
    PlayerTracePush("Player::sub_4A49B0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A49C0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A49C0)(self, 0, a0);
    PlayerTracePush("Player::sub_4A49C0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A4AE0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A4AE0)(self, 0);
    PlayerTracePush("Player::sub_4A4AE0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A4C40(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A4C40)(self, 0, a0);
    PlayerTracePush("Player::sub_4A4C40", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A4C90(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A4C90)(self, 0);
    PlayerTracePush("Player::sub_4A4C90", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A4CB0(void* self, DWORD d)
{
    PlayerTracePush("Player::sub_4A4CB0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4A4CB0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A4CF0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A4CF0)(self, 0, a0);
    PlayerTracePush("Player::sub_4A4CF0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A4D50(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A4D50)(self, 0, a0);
    PlayerTracePush("Player::AddLives", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A4E10(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A4E10)(self, 0);
    PlayerTracePush("Player::GetDeathDescription", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A4E70(void* self, DWORD d)
{
    PlayerTracePush("Player::sub_4A4E70", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4A4E70)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookPlayer_4A4EA0(void* self, DWORD d)
{
    PlayerTracePush("Player::PlayerControl", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4A4EA0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A5100(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A5100)(self, 0);
    PlayerTracePush("Player::HasPedInCar", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A5130(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A5130)(self, 0);
    PlayerTracePush("Player::GetCurrentPed", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A5150(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A5150)(self, 0);
    PlayerTracePush("Player::GetActivePed", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A5180(void* self, DWORD d)
{
    PlayerTracePush("Player::sub_4A5180", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4A5180)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A51C0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A51C0)(self, 0, a0);
    PlayerTracePush("Player::sub_4A51C0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A5220(void* self, DWORD d, DWORD a0, DWORD a1)
{
    PlayerTracePush("Player::sub_4A5220", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, 0, 0);
    ((Tc2v)_Player_4A5220)(self, 0, a0, a1);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookPlayer_4A5300(void* self, DWORD d)
{
    PlayerTracePush("Player::ProcessWeaponChange", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4A5300)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A53D0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A53D0)(self, 0);
    PlayerTracePush("Player::sub_4A53D0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A5400(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_4A5400)(self, 0, a0, a1);
    PlayerTracePush("Player::sub_4A5400", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A5460(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_4A5460)(self, 0, a0, a1);
    PlayerTracePush("Player::sub_4A5460", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A5570(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A5570)(self, 0, a0);
    PlayerTracePush("Player::GetCarWeapons", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A5600(void* self, DWORD d)
{
    PlayerTracePush("Player::sub_4A5600", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4A5600)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A5640(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A5640)(self, 0);
    PlayerTracePush("Player::RestoreOnFootWeapons", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A5690(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A5690)(self, 0);
    PlayerTracePush("Player::StoreOnFootWeapons", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A5710(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A5710)(self, 0);
    PlayerTracePush("Player::sub_4A5710", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A5780(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A5780)(self, 0, a0);
    PlayerTracePush("Player::GivePowerUp", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A59A0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A59A0)(self, 0);
    PlayerTracePush("Player::sub_4A59A0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A5A50(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A5A50)(self, 0, a0);
    PlayerTracePush("Player::sub_4A5A50", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A5AD0(void* self, DWORD d)
{
    PlayerTracePush("Player::DoTeleport", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4A5AD0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A5B40(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A5B40)(self, 0, a0);
    PlayerTracePush("Player::sub_4A5B40", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A5E90(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A5E90)(self, 0, a0);
    PlayerTracePush("Player::sub_4A5E90", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A6050(void* self, DWORD d)
{
    PlayerTracePush("Player::sub_4A6050", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4A6050)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A6100(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A6100)(self, 0);
    PlayerTracePush("Player::sub_4A6100", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A61F0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A61F0)(self, 0);
    PlayerTracePush("Player::sub_4A61F0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A62B0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A62B0)(self, 0);
    PlayerTracePush("Player::SetPedOutOfCar", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A6310(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A6310)(self, 0);
    PlayerTracePush("Player::sub_4A6310", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A6350(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A6350)(self, 0, a0);
    PlayerTracePush("Player::sub_4A6350", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A6400(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A6400)(self, 0, a0);
    PlayerTracePush("Player::sub_4A6400", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A6530(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2)
{
    DWORD r = ((Tc3)_Player_4A6530)(self, 0, a0, a1, a2);
    PlayerTracePush("Player::sub_4A6530", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, r);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A65E0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A65E0)(self, 0);
    PlayerTracePush("Player::GetActivePlayerCar", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A6610(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2)
{
    DWORD r = ((Tc3)_Player_4A6610)(self, 0, a0, a1, a2);
    PlayerTracePush("Player::GetPosition", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, r);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A6900(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A6900)(self, 0);
    PlayerTracePush("Player::sub_4A6900", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A69A0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A69A0)(self, 0);
    PlayerTracePush("Player::sub_4A69A0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A6A80(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A6A80)(self, 0);
    PlayerTracePush("Player::sub_4A6A80", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A6B20(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A6B20)(self, 0, a0);
    PlayerTracePush("Player::sub_4A6B20", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A6C80(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A6C80)(self, 0, a0);
    PlayerTracePush("Player::sub_4A6C80", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A6EF0(void* self, DWORD d)
{
    PlayerTracePush("Player::sub_4A6EF0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4A6EF0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A6FD0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A6FD0)(self, 0);
    PlayerTracePush("Player::sub_4A6FD0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A7010(void* self, DWORD d, DWORD a0)
{
    PlayerTracePush("Player::sub_4A7010", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Player_4A7010)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookPlayer_4A7680(void* self, DWORD d)
{
    PlayerTracePush("Player::sub_4A7680", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4A7680)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A76D0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A76D0)(self, 0, a0);
    PlayerTracePush("Player::sub_4A76D0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A7910(void* self, DWORD d)
{
    PlayerTracePush("Player::HandleDeath", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4A7910)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookPlayer_4A7B70(void* self, DWORD d)
{
    PlayerTracePush("Player::sub_4A7B70", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4A7B70)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A7BA0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A7BA0)(self, 0);
    PlayerTracePush("Player::sub_4A7BA0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A7E80(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A7E80)(self, 0);
    PlayerTracePush("Player::sub_4A7E80", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4A81E0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4A81E0)(self, 0);
    PlayerTracePush("Player::sub_4A81E0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookPlayer_4A8340(void* self, DWORD d)
{
    PlayerTracePush("Player::sub_4A8340", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Player_4A8340)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookPlayer_4A83C0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Player_4A83C0)(self, 0, a0);
    PlayerTracePush("Player::Player", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4BA0A0(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Player_4BA0A0)(self, 0, a0, a1);
    PlayerTracePush("Player::sub_4BA0A0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4C7340(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4C7340)(self, 0);
    PlayerTracePush("Player::sub_4C7340", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4CCAB0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4CCAB0)(self, 0);
    PlayerTracePush("Player::sub_4CCAB0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4CCAD0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4CCAD0)(self, 0);
    PlayerTracePush("Player::sub_4CCAD0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookPlayer_4CCAE0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Player_4CCAE0)(self, 0);
    PlayerTracePush("Player::sub_4CCAE0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void DumpPlayerRing(FILE* f)
{
    DWORD total = g_playerRingIdx;
    DWORD n = (total < PLAYER_RING_SIZE) ? total : PLAYER_RING_SIZE;
    fprintf(f, "PLAYER-CALL RING (last %lu of %lu):\r\n",
            (unsigned long)n, (unsigned long)total);
    for (DWORD k = 0; k < n; ++k) {
        const PlayerTraceRec* r = &g_playerRing[(g_playerRingIdx - n + 1 + k) % PLAYER_RING_SIZE];
        if (!r->name) continue;
        fprintf(f, "  %-40s call=0x%08lX self=0x%08lX a1=0x%08lX a2=0x%08lX a3=0x%08lX a4=0x%08lX\r\n",
                r->name ? r->name : "?",
                (unsigned long)r->caller, (unsigned long)r->self,
                (unsigned long)r->a1, (unsigned long)r->a2,
                (unsigned long)r->a3, (unsigned long)r->a4);
    }
}

void DumpPlayerRingFile(void)
{
    FILE* f = fopen(kPlayerTapePath, "ab");
    if (!f) return;
    DWORD total = g_playerRingIdx;
    DWORD delta = total - g_playerTaped;
    if (delta == 0) {
        fclose(f);
        return;
    }
    if (delta > PLAYER_RING_SIZE) {
        g_playerTaped = total - PLAYER_RING_SIZE;
        delta = PLAYER_RING_SIZE;
    }
    for (DWORD k = 0; k < delta; ++k) {
        const PlayerTraceRec* r = &g_playerRing[(g_playerTaped + k) % PLAYER_RING_SIZE];
        if (!r->name) continue;
        fprintf(f, "  %-40s call=0x%08lX self=0x%08lX a1=0x%08lX a2=0x%08lX a3=0x%08lX a4=0x%08lX\r\n",
                r->name ? r->name : "?",
                (unsigned long)r->caller, (unsigned long)r->self,
                (unsigned long)r->a1, (unsigned long)r->a2,
                (unsigned long)r->a3, (unsigned long)r->a4);
    }
    g_playerTaped = total;
    fclose(f);
}