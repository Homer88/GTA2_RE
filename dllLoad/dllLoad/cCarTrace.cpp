#include <Windows.h>
#include <stdio.h>
#include <intrin.h>
#include "cCarTrace.h"

// Retail entry points (imagebase 0x3F0000 in gta2-resurected.exe).
LPVOID _Car_403800 = (LPVOID)0x00403800;
LPVOID _Car_403820 = (LPVOID)0x00403820;
LPVOID _Car_403BA0 = (LPVOID)0x00403BA0;
LPVOID _Car_403BC0 = (LPVOID)0x00403BC0;
LPVOID _Car_40F890 = (LPVOID)0x0040F890;
LPVOID _Car_4112A0 = (LPVOID)0x004112A0;
LPVOID _Car_4118B0 = (LPVOID)0x004118B0;
LPVOID _Car_4118C0 = (LPVOID)0x004118C0;
LPVOID _Car_4118D0 = (LPVOID)0x004118D0;
LPVOID _Car_4118F0 = (LPVOID)0x004118F0;
LPVOID _Car_411900 = (LPVOID)0x00411900;
LPVOID _Car_411910 = (LPVOID)0x00411910;
LPVOID _Car_411920 = (LPVOID)0x00411920;
LPVOID _Car_411930 = (LPVOID)0x00411930;
LPVOID _Car_411940 = (LPVOID)0x00411940;
LPVOID _Car_411950 = (LPVOID)0x00411950;
LPVOID _Car_411970 = (LPVOID)0x00411970;
LPVOID _Car_411990 = (LPVOID)0x00411990;
LPVOID _Car_414F20 = (LPVOID)0x00414F20;
LPVOID _Car_414F60 = (LPVOID)0x00414F60;
LPVOID _Car_414F70 = (LPVOID)0x00414F70;
LPVOID _Car_414F80 = (LPVOID)0x00414F80;
LPVOID _Car_416B80 = (LPVOID)0x00416B80;
LPVOID _Car_416BB0 = (LPVOID)0x00416BB0;
LPVOID _Car_41E430 = (LPVOID)0x0041E430;
LPVOID _Car_41E440 = (LPVOID)0x0041E440;
LPVOID _Car_41E450 = (LPVOID)0x0041E450;
LPVOID _Car_41E460 = (LPVOID)0x0041E460;
LPVOID _Car_41F6E0 = (LPVOID)0x0041F6E0;
LPVOID _Car_41F700 = (LPVOID)0x0041F700;
LPVOID _Car_41F730 = (LPVOID)0x0041F730;
LPVOID _Car_41F750 = (LPVOID)0x0041F750;
LPVOID _Car_41F860 = (LPVOID)0x0041F860;
LPVOID _Car_41F880 = (LPVOID)0x0041F880;
LPVOID _Car_41F8A0 = (LPVOID)0x0041F8A0;
LPVOID _Car_41F8F0 = (LPVOID)0x0041F8F0;
LPVOID _Car_41F940 = (LPVOID)0x0041F940;
LPVOID _Car_41F960 = (LPVOID)0x0041F960;
LPVOID _Car_41FA60 = (LPVOID)0x0041FA60;
LPVOID _Car_41FAB0 = (LPVOID)0x0041FAB0;
LPVOID _Car_41FAC0 = (LPVOID)0x0041FAC0;
LPVOID _Car_41FBB0 = (LPVOID)0x0041FBB0;
LPVOID _Car_41FBD0 = (LPVOID)0x0041FBD0;
LPVOID _Car_41FD50 = (LPVOID)0x0041FD50;
LPVOID _Car_41FDA0 = (LPVOID)0x0041FDA0;
LPVOID _Car_41FDF0 = (LPVOID)0x0041FDF0;
LPVOID _Car_41FF00 = (LPVOID)0x0041FF00;
LPVOID _Car_420330 = (LPVOID)0x00420330;
LPVOID _Car_420450 = (LPVOID)0x00420450;
LPVOID _Car_4207F0 = (LPVOID)0x004207F0;
LPVOID _Car_420840 = (LPVOID)0x00420840;
LPVOID _Car_4208F0 = (LPVOID)0x004208F0;
LPVOID _Car_420950 = (LPVOID)0x00420950;
LPVOID _Car_4209F0 = (LPVOID)0x004209F0;
LPVOID _Car_4213D0 = (LPVOID)0x004213D0;
LPVOID _Car_421430 = (LPVOID)0x00421430;
LPVOID _Car_421460 = (LPVOID)0x00421460;
LPVOID _Car_421470 = (LPVOID)0x00421470;
LPVOID _Car_421490 = (LPVOID)0x00421490;
LPVOID _Car_4214B0 = (LPVOID)0x004214B0;
LPVOID _Car_4214D0 = (LPVOID)0x004214D0;
LPVOID _Car_4214E0 = (LPVOID)0x004214E0;
LPVOID _Car_4214F0 = (LPVOID)0x004214F0;
LPVOID _Car_421510 = (LPVOID)0x00421510;
LPVOID _Car_421540 = (LPVOID)0x00421540;
LPVOID _Car_421550 = (LPVOID)0x00421550;
LPVOID _Car_421560 = (LPVOID)0x00421560;
LPVOID _Car_421570 = (LPVOID)0x00421570;
LPVOID _Car_421590 = (LPVOID)0x00421590;
LPVOID _Car_4215B0 = (LPVOID)0x004215B0;
LPVOID _Car_4215C0 = (LPVOID)0x004215C0;
LPVOID _Car_4215F0 = (LPVOID)0x004215F0;
LPVOID _Car_421610 = (LPVOID)0x00421610;
LPVOID _Car_421620 = (LPVOID)0x00421620;
LPVOID _Car_421640 = (LPVOID)0x00421640;
LPVOID _Car_421660 = (LPVOID)0x00421660;
LPVOID _Car_421680 = (LPVOID)0x00421680;
LPVOID _Car_4216A0 = (LPVOID)0x004216A0;
LPVOID _Car_4216C0 = (LPVOID)0x004216C0;
LPVOID _Car_4216E0 = (LPVOID)0x004216E0;
LPVOID _Car_421700 = (LPVOID)0x00421700;
LPVOID _Car_421720 = (LPVOID)0x00421720;
LPVOID _Car_421740 = (LPVOID)0x00421740;
LPVOID _Car_421760 = (LPVOID)0x00421760;
LPVOID _Car_421780 = (LPVOID)0x00421780;
LPVOID _Car_421790 = (LPVOID)0x00421790;
LPVOID _Car_4217A0 = (LPVOID)0x004217A0;
LPVOID _Car_4217B0 = (LPVOID)0x004217B0;
LPVOID _Car_4217C0 = (LPVOID)0x004217C0;
LPVOID _Car_4217D0 = (LPVOID)0x004217D0;
LPVOID _Car_4217E0 = (LPVOID)0x004217E0;
LPVOID _Car_4217F0 = (LPVOID)0x004217F0;
LPVOID _Car_421810 = (LPVOID)0x00421810;
LPVOID _Car_421830 = (LPVOID)0x00421830;
LPVOID _Car_421870 = (LPVOID)0x00421870;
LPVOID _Car_421890 = (LPVOID)0x00421890;
LPVOID _Car_4218A0 = (LPVOID)0x004218A0;
LPVOID _Car_4218B0 = (LPVOID)0x004218B0;
LPVOID _Car_4218C0 = (LPVOID)0x004218C0;
LPVOID _Car_4218D0 = (LPVOID)0x004218D0;
LPVOID _Car_4218E0 = (LPVOID)0x004218E0;
LPVOID _Car_4218F0 = (LPVOID)0x004218F0;
LPVOID _Car_421900 = (LPVOID)0x00421900;
LPVOID _Car_421910 = (LPVOID)0x00421910;
LPVOID _Car_421950 = (LPVOID)0x00421950;
LPVOID _Car_421C40 = (LPVOID)0x00421C40;
LPVOID _Car_421CF0 = (LPVOID)0x00421CF0;
LPVOID _Car_421D80 = (LPVOID)0x00421D80;
LPVOID _Car_421D90 = (LPVOID)0x00421D90;
LPVOID _Car_421DF0 = (LPVOID)0x00421DF0;
LPVOID _Car_421E70 = (LPVOID)0x00421E70;
LPVOID _Car_421EC0 = (LPVOID)0x00421EC0;
LPVOID _Car_421F40 = (LPVOID)0x00421F40;
LPVOID _Car_421F80 = (LPVOID)0x00421F80;
LPVOID _Car_421FD0 = (LPVOID)0x00421FD0;
LPVOID _Car_4220A0 = (LPVOID)0x004220A0;
LPVOID _Car_4221D0 = (LPVOID)0x004221D0;
LPVOID _Car_422260 = (LPVOID)0x00422260;
LPVOID _Car_4222A0 = (LPVOID)0x004222A0;
LPVOID _Car_4222D0 = (LPVOID)0x004222D0;
LPVOID _Car_4222F0 = (LPVOID)0x004222F0;
LPVOID _Car_422360 = (LPVOID)0x00422360;
LPVOID _Car_422500 = (LPVOID)0x00422500;
LPVOID _Car_422670 = (LPVOID)0x00422670;
LPVOID _Car_4226C0 = (LPVOID)0x004226C0;
LPVOID _Car_422980 = (LPVOID)0x00422980;
LPVOID _Car_422A40 = (LPVOID)0x00422A40;
LPVOID _Car_422AA0 = (LPVOID)0x00422AA0;
LPVOID _Car_422B70 = (LPVOID)0x00422B70;
LPVOID _Car_422BD0 = (LPVOID)0x00422BD0;
LPVOID _Car_422CB0 = (LPVOID)0x00422CB0;
LPVOID _Car_422D20 = (LPVOID)0x00422D20;
LPVOID _Car_422D80 = (LPVOID)0x00422D80;
LPVOID _Car_422DE0 = (LPVOID)0x00422DE0;
LPVOID _Car_422E00 = (LPVOID)0x00422E00;
LPVOID _Car_422F00 = (LPVOID)0x00422F00;
LPVOID _Car_4230D0 = (LPVOID)0x004230D0;
LPVOID _Car_423180 = (LPVOID)0x00423180;
LPVOID _Car_423290 = (LPVOID)0x00423290;
LPVOID _Car_423310 = (LPVOID)0x00423310;
LPVOID _Car_423480 = (LPVOID)0x00423480;
LPVOID _Car_4234A0 = (LPVOID)0x004234A0;
LPVOID _Car_423510 = (LPVOID)0x00423510;
LPVOID _Car_423590 = (LPVOID)0x00423590;
LPVOID _Car_4235D0 = (LPVOID)0x004235D0;
LPVOID _Car_423630 = (LPVOID)0x00423630;
LPVOID _Car_423720 = (LPVOID)0x00423720;
LPVOID _Car_4237B0 = (LPVOID)0x004237B0;
LPVOID _Car_4237F0 = (LPVOID)0x004237F0;
LPVOID _Car_423830 = (LPVOID)0x00423830;
LPVOID _Car_423850 = (LPVOID)0x00423850;
LPVOID _Car_423940 = (LPVOID)0x00423940;
LPVOID _Car_423A50 = (LPVOID)0x00423A50;
LPVOID _Car_423A70 = (LPVOID)0x00423A70;
LPVOID _Car_423AA0 = (LPVOID)0x00423AA0;
LPVOID _Car_423B30 = (LPVOID)0x00423B30;
LPVOID _Car_423B50 = (LPVOID)0x00423B50;
LPVOID _Car_423B80 = (LPVOID)0x00423B80;
LPVOID _Car_423C30 = (LPVOID)0x00423C30;
LPVOID _Car_424010 = (LPVOID)0x00424010;
LPVOID _Car_424030 = (LPVOID)0x00424030;
LPVOID _Car_424090 = (LPVOID)0x00424090;
LPVOID _Car_4241C0 = (LPVOID)0x004241C0;
LPVOID _Car_424220 = (LPVOID)0x00424220;
LPVOID _Car_424280 = (LPVOID)0x00424280;
LPVOID _Car_4243C0 = (LPVOID)0x004243C0;
LPVOID _Car_424400 = (LPVOID)0x00424400;
LPVOID _Car_4244A0 = (LPVOID)0x004244A0;
LPVOID _Car_424630 = (LPVOID)0x00424630;
LPVOID _Car_424660 = (LPVOID)0x00424660;
LPVOID _Car_424680 = (LPVOID)0x00424680;
LPVOID _Car_4246A0 = (LPVOID)0x004246A0;
LPVOID _Car_424700 = (LPVOID)0x00424700;
LPVOID _Car_424880 = (LPVOID)0x00424880;
LPVOID _Car_424960 = (LPVOID)0x00424960;
LPVOID _Car_424E30 = (LPVOID)0x00424E30;
LPVOID _Car_424F80 = (LPVOID)0x00424F80;
LPVOID _Car_425590 = (LPVOID)0x00425590;
LPVOID _Car_425650 = (LPVOID)0x00425650;
LPVOID _Car_425760 = (LPVOID)0x00425760;
LPVOID _Car_425770 = (LPVOID)0x00425770;
LPVOID _Car_425780 = (LPVOID)0x00425780;
LPVOID _Car_425790 = (LPVOID)0x00425790;
LPVOID _Car_4257B0 = (LPVOID)0x004257B0;
LPVOID _Car_425A40 = (LPVOID)0x00425A40;
LPVOID _Car_425B60 = (LPVOID)0x00425B60;
LPVOID _Car_425CA0 = (LPVOID)0x00425CA0;
LPVOID _Car_425D60 = (LPVOID)0x00425D60;
LPVOID _Car_425D90 = (LPVOID)0x00425D90;
LPVOID _Car_425DD0 = (LPVOID)0x00425DD0;
LPVOID _Car_425DF0 = (LPVOID)0x00425DF0;
LPVOID _Car_425E30 = (LPVOID)0x00425E30;
LPVOID _Car_425E60 = (LPVOID)0x00425E60;
LPVOID _Car_425ED0 = (LPVOID)0x00425ED0;
LPVOID _Car_425F20 = (LPVOID)0x00425F20;
LPVOID _Car_425FD0 = (LPVOID)0x00425FD0;
LPVOID _Car_426030 = (LPVOID)0x00426030;
LPVOID _Car_4260C0 = (LPVOID)0x004260C0;
LPVOID _Car_426120 = (LPVOID)0x00426120;
LPVOID _Car_426140 = (LPVOID)0x00426140;
LPVOID _Car_426220 = (LPVOID)0x00426220;
LPVOID _Car_4262B0 = (LPVOID)0x004262B0;
LPVOID _Car_4262E0 = (LPVOID)0x004262E0;
LPVOID _Car_426580 = (LPVOID)0x00426580;
LPVOID _Car_4266F0 = (LPVOID)0x004266F0;
LPVOID _Car_426730 = (LPVOID)0x00426730;
LPVOID _Car_4267B0 = (LPVOID)0x004267B0;
LPVOID _Car_426E00 = (LPVOID)0x00426E00;
LPVOID _Car_426EE0 = (LPVOID)0x00426EE0;
LPVOID _Car_426F00 = (LPVOID)0x00426F00;
LPVOID _Car_426F40 = (LPVOID)0x00426F40;
LPVOID _Car_426F60 = (LPVOID)0x00426F60;
LPVOID _Car_426FA0 = (LPVOID)0x00426FA0;
LPVOID _Car_427180 = (LPVOID)0x00427180;
LPVOID _Car_427290 = (LPVOID)0x00427290;
LPVOID _Car_427450 = (LPVOID)0x00427450;
LPVOID _Car_4274C0 = (LPVOID)0x004274C0;
LPVOID _Car_4279E0 = (LPVOID)0x004279E0;
LPVOID _Car_427A20 = (LPVOID)0x00427A20;
LPVOID _Car_427B20 = (LPVOID)0x00427B20;
LPVOID _Car_427B40 = (LPVOID)0x00427B40;
LPVOID _Car_427BD0 = (LPVOID)0x00427BD0;
LPVOID _Car_427CA0 = (LPVOID)0x00427CA0;
LPVOID _Car_427D10 = (LPVOID)0x00427D10;
LPVOID _Car_4292F0 = (LPVOID)0x004292F0;
LPVOID _Car_429370 = (LPVOID)0x00429370;
LPVOID _Car_4293D0 = (LPVOID)0x004293D0;
LPVOID _Car_429660 = (LPVOID)0x00429660;
LPVOID _Car_429800 = (LPVOID)0x00429800;
LPVOID _Car_429810 = (LPVOID)0x00429810;
LPVOID _Car_4298B0 = (LPVOID)0x004298B0;
LPVOID _Car_429E50 = (LPVOID)0x00429E50;
LPVOID _Car_429FC0 = (LPVOID)0x00429FC0;
LPVOID _Car_429FF0 = (LPVOID)0x00429FF0;
LPVOID _Car_42A360 = (LPVOID)0x0042A360;
LPVOID _Car_42A510 = (LPVOID)0x0042A510;
LPVOID _Car_42A5B0 = (LPVOID)0x0042A5B0;
LPVOID _Car_42AC60 = (LPVOID)0x0042AC60;
LPVOID _Car_42C030 = (LPVOID)0x0042C030;
LPVOID _Car_42C8B0 = (LPVOID)0x0042C8B0;
LPVOID _Car_42D390 = (LPVOID)0x0042D390;
LPVOID _Car_42D820 = (LPVOID)0x0042D820;
LPVOID _Car_42FB80 = (LPVOID)0x0042FB80;
LPVOID _Car_430090 = (LPVOID)0x00430090;
LPVOID _Car_430320 = (LPVOID)0x00430320;
LPVOID _Car_430CC0 = (LPVOID)0x00430CC0;
LPVOID _Car_431770 = (LPVOID)0x00431770;
LPVOID _Car_431C10 = (LPVOID)0x00431C10;
LPVOID _Car_432370 = (LPVOID)0x00432370;
LPVOID _Car_4327A0 = (LPVOID)0x004327A0;
LPVOID _Car_447EA0 = (LPVOID)0x00447EA0;
LPVOID _Car_447EB0 = (LPVOID)0x00447EB0;
LPVOID _Car_447EC0 = (LPVOID)0x00447EC0;
LPVOID _Car_447ED0 = (LPVOID)0x00447ED0;
LPVOID _Car_447F00 = (LPVOID)0x00447F00;
LPVOID _Car_44A3E0 = (LPVOID)0x0044A3E0;
LPVOID _Car_450CC0 = (LPVOID)0x00450CC0;
LPVOID _Car_475AA0 = (LPVOID)0x00475AA0;
LPVOID _Car_475C10 = (LPVOID)0x00475C10;
LPVOID _Car_475C30 = (LPVOID)0x00475C30;
LPVOID _Car_475C40 = (LPVOID)0x00475C40;
LPVOID _Car_475C80 = (LPVOID)0x00475C80;
LPVOID _Car_4761F0 = (LPVOID)0x004761F0;
LPVOID _Car_476230 = (LPVOID)0x00476230;
LPVOID _Car_476270 = (LPVOID)0x00476270;
LPVOID _Car_4762D0 = (LPVOID)0x004762D0;
LPVOID _Car_4762E0 = (LPVOID)0x004762E0;
LPVOID _Car_4762F0 = (LPVOID)0x004762F0;
LPVOID _Car_476300 = (LPVOID)0x00476300;
LPVOID _Car_476310 = (LPVOID)0x00476310;
LPVOID _Car_476350 = (LPVOID)0x00476350;
LPVOID _Car_482D90 = (LPVOID)0x00482D90;
LPVOID _Car_4895E0 = (LPVOID)0x004895E0;
LPVOID _Car_48A930 = (LPVOID)0x0048A930;
LPVOID _Car_49EFC0 = (LPVOID)0x0049EFC0;
LPVOID _Car_49EFD0 = (LPVOID)0x0049EFD0;
LPVOID _Car_49EFE0 = (LPVOID)0x0049EFE0;
LPVOID _Car_4A9AD0 = (LPVOID)0x004A9AD0;
LPVOID _Car_4AFB30 = (LPVOID)0x004AFB30;
LPVOID _Car_4B9A30 = (LPVOID)0x004B9A30;
LPVOID _Car_4BE7A0 = (LPVOID)0x004BE7A0;
LPVOID _Car_4BE980 = (LPVOID)0x004BE980;
LPVOID _Car_4BE9C0 = (LPVOID)0x004BE9C0;
LPVOID _Car_4BE9F0 = (LPVOID)0x004BE9F0;
LPVOID _Car_4BEA20 = (LPVOID)0x004BEA20;
LPVOID _Car_4BEAC0 = (LPVOID)0x004BEAC0;
LPVOID _Car_4BEB30 = (LPVOID)0x004BEB30;
LPVOID _Car_4BEB70 = (LPVOID)0x004BEB70;
LPVOID _Car_4BEBC0 = (LPVOID)0x004BEBC0;
LPVOID _Car_4BED90 = (LPVOID)0x004BED90;
LPVOID _Car_4BEE10 = (LPVOID)0x004BEE10;
LPVOID _Car_4BEF70 = (LPVOID)0x004BEF70;
LPVOID _Car_4BF000 = (LPVOID)0x004BF000;
LPVOID _Car_4BF070 = (LPVOID)0x004BF070;
LPVOID _Car_4BF100 = (LPVOID)0x004BF100;
LPVOID _Car_4BF180 = (LPVOID)0x004BF180;

struct CarTraceRec {
    const char* name;
    DWORD caller;
    DWORD self;
    DWORD a1, a2, a3, a4;
};

#define CAR_RING_SIZE 32768
static CarTraceRec g_carRing[CAR_RING_SIZE];
static volatile DWORD g_carRingIdx = 0;
static DWORD g_carTaped = 0;
static const char* kCarTapePath = "C:\\games\\gta2\\car_trace.log";

static void CarTracePush(const char* name, DWORD caller, DWORD self,
                         DWORD a1, DWORD a2, DWORD a3, DWORD a4)
{
    DWORD idx = (g_carRingIdx + 1) % CAR_RING_SIZE;
    CarTraceRec* r = &g_carRing[idx];
    r->name   = name;
    r->caller = caller;
    r->self   = self;
    r->a1 = a1; r->a2 = a2; r->a3 = a3; r->a4 = a4;
    g_carRingIdx = idx;
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
typedef DWORD (__fastcall *Tc6)(void*, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
typedef void  (__fastcall *Tc6v)(void*, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
typedef DWORD (__fastcall *Tc7)(void*, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
typedef void  (__fastcall *Tc7v)(void*, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
typedef DWORD (__fastcall *Tc8)(void*, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
typedef void  (__fastcall *Tc8v)(void*, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);

DWORD __fastcall HookCar_403800(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_403800)(self, 0, a0);
    CarTracePush("Car::sub_403800", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_403820(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_403820)(self, 0, a0);
    CarTracePush("Car::sub_403820", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_403BA0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_403BA0)(self, 0);
    CarTracePush("Car::IsTrainOrTrainCarriage", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_403BC0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_403BC0)(self, 0);
    CarTracePush("Car::isSWATVANOrBankVan", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_40F890(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_40F890)(self, 0);
    CarTracePush("Car::GetFullDamage", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4112A0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4112A0)(self, 0);
    CarTracePush("Car::HasEmergencyLights", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4118B0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4118B0)(self, 0);
    CarTracePush("Car::GetDriver", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4118C0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4118C0)(self, 0);
    CarTracePush("Car::IsEngineOn", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4118D0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4118D0)(self, 0);
    CarTracePush("Car::IsDriverPlayer", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4118F0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4118F0)(self, 0);
    CarTracePush("Car::isFileTruck", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_411900(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_411900)(self, 0);
    CarTracePush("Car::isTank", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_411910(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_411910)(self, 0);
    CarTracePush("Car::isGunJeep", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_411920(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_411920)(self, 0);
    CarTracePush("Car::isEDSELFBI", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_411930(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_411930)(self, 0, a0);
    CarTracePush("Car::sub_411930", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_411940(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_411940)(self, 0);
    CarTracePush("Car::GetModelCar", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_411950(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_411950)(self, 0);
    CarTracePush("Car::sub_411950", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_411970(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_411970)(self, 0);
    CarTracePush("Car::sub_411970", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_411990(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_411990)(self, 0);
    CarTracePush("Car::sub_411990", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_414F20(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_414F20)(self, 0);
    CarTracePush("Car::IsEmergencyOrFbiCar", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_414F60(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_414F60)(self, 0);
    CarTracePush("Car::sub_414F60", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_414F70(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_414F70)(self, 0);
    CarTracePush("Car::sub_414F70", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_414F80(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_414F80)(self, 0);
    CarTracePush("Car::sub_414F80", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_416B80(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2)
{
    CarTracePush("Car::sub_416B80", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, 0);
    ((Tc3v)_Car_416B80)(self, 0, a0, a1, a2);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_416BB0(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::sub_416BB0", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_416BB0)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_41E430(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::GetX", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_41E430)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_41E440(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::GetY", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_41E440)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_41E450(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::GetZ", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_41E450)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_41E460(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_41E460)(self, 0);
    CarTracePush("Car::sub_41E460", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_41F6E0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_41F6E0)(self, 0);
    CarTracePush("Car::IsCopCar", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_41F700(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_41F700)(self, 0);
    CarTracePush("Car::GetInfoByTypeCar", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_41F730(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_41F730)(self, 0, a0);
    CarTracePush("Car::sub_41F730", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_41F750(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_41F750)(self, 0);
    CarTracePush("Car::IsCurrentCarBus", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_41F860(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_41F860)(self, 0, a0);
    CarTracePush("Car::GetCarDoor", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_41F880(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_41F880)(self, 0);
    CarTracePush("Car::sub_41F880", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_41F8A0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_41F8A0)(self, 0);
    CarTracePush("Car::sub_41F8A0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_41F8F0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_41F8F0)(self, 0);
    CarTracePush("Car::sub_41F8F0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_41F940(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_41F940)(self, 0);
    CarTracePush("Car::sub_41F940", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_41F960(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_41F960)(self, 0);
    CarTracePush("Car::sub_41F960", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_41FA60(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_41FA60)(self, 0);
    CarTracePush("Car::sub_41FA60", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_41FAB0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_41FAB0)(self, 0);
    CarTracePush("Car::sub_41FAB0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_41FAC0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_41FAC0)(self, 0, a0);
    CarTracePush("Car::sub_41FAC0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_41FBB0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_41FBB0)(self, 0);
    CarTracePush("Car::sub_41FBB0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_41FBD0(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::sub_41FBD0", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_41FBD0)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_41FD50(void* self, DWORD d)
{
    CarTracePush("Car::AddRoofWaterGun", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_41FD50)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_41FDA0(void* self, DWORD d)
{
    CarTracePush("Car::AddRoofTankTurret", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_41FDA0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_41FDF0(void* self, DWORD d)
{
    CarTracePush("Car::AddRoofGun", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_41FDF0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_41FF00(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_41FF00)(self, 0);
    CarTracePush("Car::CanDriverOverCars", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_420330(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_420330)(self, 0);
    CarTracePush("Car::DecrementHorn", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_420450(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_420450)(self, 0);
    CarTracePush("Car::sub_420450", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4207F0(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2)
{
    DWORD r = ((Tc3)_Car_4207F0)(self, 0, a0, a1, a2);
    CarTracePush("Car::SetPosition", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, r);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_420840(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_420840)(self, 0, a0);
    CarTracePush("Car::sub_420840", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_4208F0(void* self, DWORD d)
{
    CarTracePush("Car::TransformToRecycledType", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4208F0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_420950(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3)
{
    CarTracePush("Car::sub_420950", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, a3);
    ((Tc4v)_Car_420950)(self, 0, a0, a1, a2, a3);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_4209F0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4209F0)(self, 0);
    CarTracePush("Car::UpdateDamageCooldown", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_4213D0(void* self, DWORD d)
{
    CarTracePush("Car::sub_4213D0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4213D0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_421430(void* self, DWORD d)
{
    CarTracePush("Car::sub_421430", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_421430)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_421460(void* self, DWORD d)
{
    CarTracePush("Car::SetHornDefault", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_421460)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_421470(void* self, DWORD d)
{
    CarTracePush("Car::isMask4", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_421470)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_421490(void* self, DWORD d)
{
    CarTracePush("Car::isMask3", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_421490)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_4214B0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4214B0)(self, 0);
    CarTracePush("Car::isMask", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4214D0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4214D0)(self, 0);
    CarTracePush("Car::GetMask7", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_4214E0(void* self, DWORD d)
{
    CarTracePush("Car::SetMask7", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4214E0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_4214F0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4214F0)(self, 0);
    CarTracePush("Car::IsDriverActive", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421510(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421510)(self, 0);
    CarTracePush("Car::CarMakeDriveable2", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_421540(void* self, DWORD d)
{
    CarTracePush("Car::sub_421540", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_421540)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_421550(void* self, DWORD d)
{
    CarTracePush("Car::sub_421550", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_421550)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_421560(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::CarMakeDriveable1", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_421560)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_421570(void* self, DWORD d)
{
    CarTracePush("Car::FixCarBrokenEngine", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_421570)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_421590(void* self, DWORD d)
{
    CarTracePush("Car::sub_421590", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_421590)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_4215B0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4215B0)(self, 0);
    CarTracePush("Car::GetMask", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4215C0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4215C0)(self, 0);
    CarTracePush("Car::sub_4215C0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_4215F0(void* self, DWORD d)
{
    CarTracePush("Car::SetMask", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4215F0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_421610(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421610)(self, 0);
    CarTracePush("Car::is_train", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421620(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421620)(self, 0);
    CarTracePush("Car::IsCar", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421640(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421640)(self, 0);
    CarTracePush("Car::is_trailer", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421660(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421660)(self, 0);
    CarTracePush("Car::sub_421660", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421680(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421680)(self, 0);
    CarTracePush("Car::sub_421680", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4216A0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4216A0)(self, 0);
    CarTracePush("Car::sub_4216A0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4216C0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4216C0)(self, 0);
    CarTracePush("Car::has_for_hire_lights", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4216E0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4216E0)(self, 0);
    CarTracePush("Car::sub_4216E0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421700(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421700)(self, 0);
    CarTracePush("Car::sub_421700", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421720(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421720)(self, 0);
    CarTracePush("Car::sub_421720", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421740(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421740)(self, 0);
    CarTracePush("Car::sub_421740", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421760(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421760)(self, 0);
    CarTracePush("Car::sub_421760", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421780(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421780)(self, 0);
    CarTracePush("Car::isMedicCar", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421790(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421790)(self, 0);
    CarTracePush("Car::isCopCar", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4217A0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4217A0)(self, 0);
    CarTracePush("Car::isSWATVAN", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4217B0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4217B0)(self, 0);
    CarTracePush("Car::isJeep", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4217C0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4217C0)(self, 0);
    CarTracePush("Car::IsAPC", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4217D0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4217D0)(self, 0);
    CarTracePush("Car::GetGT24640", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4217E0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4217E0)(self, 0);
    CarTracePush("Car::isTVVAN", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4217F0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4217F0)(self, 0);
    CarTracePush("Car::isTaxi", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421810(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421810)(self, 0);
    CarTracePush("Car::sub_421810", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421830(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421830)(self, 0);
    CarTracePush("Car::sub_421830", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421870(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421870)(self, 0);
    CarTracePush("Car::GetPlayer", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_421890(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::sub_421890", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_421890)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_4218A0(void* self, DWORD d)
{
    CarTracePush("Car::sub_4218A0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4218A0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_4218B0(void* self, DWORD d)
{
    CarTracePush("Car::sub_4218B0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4218B0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_4218C0(void* self, DWORD d)
{
    CarTracePush("Car::sub_4218C0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4218C0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_4218D0(void* self, DWORD d)
{
    CarTracePush("Car::sub_4218D0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4218D0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_4218E0(void* self, DWORD d)
{
    CarTracePush("Car::sub_4218E0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4218E0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_4218F0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4218F0)(self, 0);
    CarTracePush("Car::sub_4218F0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_421900(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::sub_421900", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_421900)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_421910(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Car_421910)(self, 0, a0, a1);
    CarTracePush("Car::sub_421910", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_421950(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::SetSound", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_421950)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_421C40(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_421C40)(self, 0, a0);
    CarTracePush("Car::sub_421C40", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421CF0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_421CF0)(self, 0, a0);
    CarTracePush("Car::sub_421CF0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421D80(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421D80)(self, 0);
    CarTracePush("Car::sub_421D80", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421D90(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_421D90)(self, 0, a0);
    CarTracePush("Car::sub_421D90", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421DF0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_421DF0)(self, 0);
    CarTracePush("Car::IsPlayerDriving", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421E70(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_421E70)(self, 0, a0);
    CarTracePush("Car::sub_421E70", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421EC0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_421EC0)(self, 0, a0);
    CarTracePush("Car::sub_421EC0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421F40(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_421F40)(self, 0, a0);
    CarTracePush("Car::sub_421F40", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421F80(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_421F80)(self, 0, a0);
    CarTracePush("Car::sub_421F80", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_421FD0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_421FD0)(self, 0, a0);
    CarTracePush("Car::SetRemap", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4220A0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4220A0)(self, 0);
    CarTracePush("Car::sub_4220A0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_4221D0(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::sub_4221D0", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_4221D0)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_422260(void* self, DWORD d)
{
    CarTracePush("Car::sub_422260", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_422260)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_4222A0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4222A0)(self, 0);
    CarTracePush("Car::sub_4222A0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_4222D0(void* self, DWORD d)
{
    CarTracePush("Car::sub_4222D0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4222D0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_4222F0(void* self, DWORD d)
{
    CarTracePush("Car::sub_4222F0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4222F0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_422360(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_422360)(self, 0, a0);
    CarTracePush("Car::sub_422360", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_422500(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2)
{
    DWORD r = ((Tc3)_Car_422500)(self, 0, a0, a1, a2);
    CarTracePush("Car::sub_422500", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, r);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_422670(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_422670)(self, 0);
    CarTracePush("Car::sub_422670", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4226C0(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Car_4226C0)(self, 0, a0, a1);
    CarTracePush("Car::sub_4226C0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_422980(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_422980)(self, 0);
    CarTracePush("Car::sub_422980", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_422A40(void* self, DWORD d)
{
    CarTracePush("Car::sub_422A40", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_422A40)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_422AA0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_422AA0)(self, 0);
    CarTracePush("Car::sub_422AA0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_422B70(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_422B70)(self, 0);
    CarTracePush("Car::sub_422B70", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_422BD0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_422BD0)(self, 0);
    CarTracePush("Car::sub_422BD0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_422CB0(void* self, DWORD d)
{
    CarTracePush("Car::sub_422CB0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_422CB0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_422D20(void* self, DWORD d)
{
    CarTracePush("Car::sub_422D20", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_422D20)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_422D80(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_422D80)(self, 0);
    CarTracePush("Car::sub_422D80", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_422DE0(void* self, DWORD d)
{
    CarTracePush("Car::sub_422DE0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_422DE0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_422E00(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_422E00)(self, 0, a0);
    CarTracePush("Car::sub_422E00", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_422F00(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_422F00)(self, 0, a0);
    CarTracePush("Car::sub_422F00", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4230D0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_4230D0)(self, 0, a0);
    CarTracePush("Car::sub_4230D0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_423180(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Car_423180)(self, 0, a0, a1);
    CarTracePush("Car::sub_423180", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_423290(void* self, DWORD d)
{
    CarTracePush("Car::sub_423290", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_423290)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_423310(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_423310)(self, 0);
    CarTracePush("Car::sub_423310", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_423480(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_423480)(self, 0);
    CarTracePush("Car::sub_423480", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4234A0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_4234A0)(self, 0, a0);
    CarTracePush("Car::sub_4234A0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_423510(void* self, DWORD d)
{
    CarTracePush("Car::CarPutDummyDriverIn", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_423510)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_423590(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::sub_423590", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_423590)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_4235D0(void* self, DWORD d)
{
    CarTracePush("Car::sub_4235D0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4235D0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_423630(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_423630)(self, 0, a0);
    CarTracePush("Car::sub_423630", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_423720(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_423720)(self, 0, a0);
    CarTracePush("Car::sub_423720", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4237B0(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3)
{
    DWORD r = ((Tc4)_Car_4237B0)(self, 0, a0, a1, a2, a3);
    CarTracePush("Car::sub_4237B0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, a3);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4237F0(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3)
{
    DWORD r = ((Tc4)_Car_4237F0)(self, 0, a0, a1, a2, a3);
    CarTracePush("Car::sub_4237F0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, a3);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_423830(void* self, DWORD d)
{
    CarTracePush("Car::sub_423830", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_423830)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_423850(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_423850)(self, 0);
    CarTracePush("Car::sub_423850", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_423940(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_423940)(self, 0, a0);
    CarTracePush("Car::sub_423940", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_423A50(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_423A50)(self, 0);
    CarTracePush("Car::sub_423A50", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_423A70(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_423A70)(self, 0);
    CarTracePush("Car::sub_423A70", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_423AA0(void* self, DWORD d)
{
    CarTracePush("Car::sub_423AA0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_423AA0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_423B30(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_423B30)(self, 0);
    CarTracePush("Car::sub_423B30", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_423B50(void* self, DWORD d)
{
    CarTracePush("Car::sub_423B50", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_423B50)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_423B80(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_423B80)(self, 0);
    CarTracePush("Car::sub_423B80", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_423C30(void* self, DWORD d)
{
    CarTracePush("Car::sub_423C30", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_423C30)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_424010(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_424010)(self, 0);
    CarTracePush("Car::sub_424010", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_424030(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_424030)(self, 0);
    CarTracePush("Car::sub_424030", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_424090(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_424090)(self, 0);
    CarTracePush("Car::sub_424090", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4241C0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4241C0)(self, 0);
    CarTracePush("Car::HandleMaskTransition", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_424220(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_424220)(self, 0, a0);
    CarTracePush("Car::sub_424220", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_424280(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_424280)(self, 0);
    CarTracePush("Car::sub_424280", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4243C0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4243C0)(self, 0);
    CarTracePush("Car::sub_4243C0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_424400(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_424400)(self, 0);
    CarTracePush("Car::sub_424400", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_4244A0(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::sub_4244A0", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_4244A0)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_424630(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_424630)(self, 0, a0);
    CarTracePush("Car::sub_424630", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_424660(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::sub_424660", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_424660)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_424680(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_424680)(self, 0, a0);
    CarTracePush("Car::sub_424680", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4246A0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4246A0)(self, 0);
    CarTracePush("Car::sub_4246A0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_424700(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_424700)(self, 0);
    CarTracePush("Car::sub_424700", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_424880(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_424880)(self, 0);
    CarTracePush("Car::sub_424880", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_424960(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_424960)(self, 0);
    CarTracePush("Car::Car_Des", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_424E30(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_424E30)(self, 0, a0);
    CarTracePush("Car::sub_424E30", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_424F80(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_424F80)(self, 0);
    CarTracePush("Car::sub_424F80", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425590(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_425590)(self, 0);
    CarTracePush("Car::sub_425590", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425650(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_425650)(self, 0);
    CarTracePush("Car::sub_425650", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425760(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_425760)(self, 0);
    CarTracePush("Car::sub_425760", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425770(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_425770)(self, 0);
    CarTracePush("Car::sub_425770", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425780(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_425780)(self, 0);
    CarTracePush("Car::sub_425780", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425790(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_425790)(self, 0, a0);
    CarTracePush("Car::sub_425790", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4257B0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4257B0)(self, 0);
    CarTracePush("Car::sub_4257B0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425A40(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_425A40)(self, 0, a0);
    CarTracePush("Car::sub_425A40", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425B60(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_425B60)(self, 0, a0);
    CarTracePush("Car::sub_425B60", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425CA0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_425CA0)(self, 0, a0);
    CarTracePush("Car::sub_425CA0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425D60(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_425D60)(self, 0, a0);
    CarTracePush("Car::sub_425D60", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425D90(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_425D90)(self, 0);
    CarTracePush("Car::sub_425D90", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425DD0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_425DD0)(self, 0);
    CarTracePush("Car::CarMakeDriveable4", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425DF0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_425DF0)(self, 0);
    CarTracePush("Car::sub_425DF0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425E30(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_425E30)(self, 0);
    CarTracePush("Car::EnableSiren", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425E60(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_425E60)(self, 0);
    CarTracePush("Car::sub_425E60", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_425ED0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_425ED0)(self, 0);
    CarTracePush("Car::sub_425ED0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_425F20(void* self, DWORD d)
{
    CarTracePush("Car::FixCarDamage", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_425F20)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_425FD0(void* self, DWORD d)
{
    CarTracePush("Car::AddRoofAntenna", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_425FD0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_426030(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_426030)(self, 0);
    CarTracePush("Car::sub_426030", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_4260C0(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::sub_4260C0", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_4260C0)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_426120(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_426120)(self, 0);
    CarTracePush("Car::sub_426120", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_426140(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_426140)(self, 0);
    CarTracePush("Car::sub_426140", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_426220(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_426220)(self, 0);
    CarTracePush("Car::sub_426220", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4262B0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_4262B0)(self, 0, a0);
    CarTracePush("Car::sub_4262B0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_4262E0(void* self, DWORD d)
{
    CarTracePush("Car::sub_4262E0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4262E0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_426580(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_426580)(self, 0, a0);
    CarTracePush("Car::sub_426580", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4266F0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4266F0)(self, 0);
    CarTracePush("Car::sub_4266F0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_426730(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_426730)(self, 0);
    CarTracePush("Car::sub_426730", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_4267B0(void* self, DWORD d)
{
    CarTracePush("Car::Car", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4267B0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_426E00(void* self, DWORD d)
{
    CarTracePush("Car::ENGINE_ON", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_426E00)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_426EE0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_426EE0)(self, 0);
    CarTracePush("Car::sub_426EE0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_426F00(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_426F00)(self, 0);
    CarTracePush("Car::sub_426F00", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_426F40(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_426F40)(self, 0);
    CarTracePush("Car::sub_426F40", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_426F60(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_426F60)(self, 0);
    CarTracePush("Car::sub_426F60", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_426FA0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_426FA0)(self, 0, a0);
    CarTracePush("Car::ExplodeCar", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_427180(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Car_427180)(self, 0, a0, a1);
    CarTracePush("Car::CollisionOnCar", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_427290(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_427290)(self, 0);
    CarTracePush("Car::sub_427290", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_427450(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_427450)(self, 0);
    CarTracePush("Car::sub_427450", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4274C0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_4274C0)(self, 0, a0);
    CarTracePush("Car::sub_4274C0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_4279E0(void* self, DWORD d)
{
    CarTracePush("Car::CarMakeDummy", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4279E0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_427A20(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::sub_427A20", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_427A20)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_427B20(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_427B20)(self, 0);
    CarTracePush("Car::sub_427B20", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_427B40(void* self, DWORD d)
{
    CarTracePush("Car::sub_427B40", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_427B40)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_427BD0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_427BD0)(self, 0, a0);
    CarTracePush("Car::MaxPaynt", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_427CA0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_427CA0)(self, 0, a0);
    CarTracePush("Car::sub_427CA0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_427D10(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_427D10)(self, 0, a0);
    CarTracePush("Car::sub_427D10", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4292F0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_4292F0)(self, 0, a0);
    CarTracePush("Car::sub_4292F0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_429370(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::sub_429370", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_429370)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_4293D0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_4293D0)(self, 0, a0);
    CarTracePush("Car::sub_4293D0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_429660(void* self, DWORD d)
{
    CarTracePush("Car::sub_429660", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_429660)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_429800(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_429800)(self, 0);
    CarTracePush("Car::sub_429800", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_429810(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7)
{
    DWORD r = ((Tc8)_Car_429810)(self, 0, a0, a1, a2, a3, a4, a5, a6, a7);
    CarTracePush("Car::sub_429810", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, a3);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4298B0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4298B0)(self, 0);
    CarTracePush("Car::sub_4298B0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_429E50(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_429E50)(self, 0);
    CarTracePush("Car::sub_429E50", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_429FC0(void* self, DWORD d)
{
    CarTracePush("Car::sub_429FC0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_429FC0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_429FF0(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3)
{
    DWORD r = ((Tc4)_Car_429FF0)(self, 0, a0, a1, a2, a3);
    CarTracePush("Car::sub_429FF0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, a3);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_42A360(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_42A360)(self, 0, a0);
    CarTracePush("Car::sub_42A360", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_42A510(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_42A510)(self, 0);
    CarTracePush("Car::sub_42A510", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_42A5B0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_42A5B0)(self, 0);
    CarTracePush("Car::sub_42A5B0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_42AC60(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_42AC60)(self, 0);
    CarTracePush("Car::sub_42AC60", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_42C030(void* self, DWORD d)
{
    CarTracePush("Car::sub_42C030", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_42C030)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_42C8B0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_42C8B0)(self, 0);
    CarTracePush("Car::sub_42C8B0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_42D390(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_42D390)(self, 0);
    CarTracePush("Car::sub_42D390", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_42D820(void* self, DWORD d)
{
    CarTracePush("Car::sub_42D820", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_42D820)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_42FB80(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_42FB80)(self, 0);
    CarTracePush("Car::sub_42FB80", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_430090(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_430090)(self, 0);
    CarTracePush("Car::sub_430090", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_430320(void* self, DWORD d)
{
    CarTracePush("Car::sub_430320", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_430320)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_430CC0(void* self, DWORD d)
{
    CarTracePush("Car::sub_430CC0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_430CC0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_431770(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_431770)(self, 0);
    CarTracePush("Car::sub_431770", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_431C10(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_431C10)(self, 0);
    CarTracePush("Car::sub_431C10", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_432370(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_432370)(self, 0);
    CarTracePush("Car::sub_432370", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4327A0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4327A0)(self, 0);
    CarTracePush("Car::sub_4327A0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_447EA0(void* self, DWORD d)
{
    CarTracePush("Car::SetMask1", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_447EA0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_447EB0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_447EB0)(self, 0);
    CarTracePush("Car::sub_447EB0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_447EC0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_447EC0)(self, 0);
    CarTracePush("Car::is_truck", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_447ED0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_447ED0)(self, 0);
    CarTracePush("Car::sub_447ED0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_447F00(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_447F00)(self, 0);
    CarTracePush("Car::sub_447F00", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_44A3E0(void* self, DWORD d)
{
    CarTracePush("Car::sub_44A3E0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_44A3E0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_450CC0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_450CC0)(self, 0);
    CarTracePush("Car::sub_450CC0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_475AA0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_475AA0)(self, 0);
    CarTracePush("Car::sub_475AA0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_475C10(void* self, DWORD d)
{
    CarTracePush("Car::SetLocksDoor", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_475C10)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_475C30(void* self, DWORD d)
{
    CarTracePush("Car::SetLocksDoor_4", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_475C30)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_475C40(void* self, DWORD d)
{
    CarTracePush("Car::SetLocksDoor2", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_475C40)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_475C80(void* self, DWORD d)
{
    CarTracePush("Car::sub_475C80", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_475C80)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_4761F0(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::sub_4761F0", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_4761F0)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_476230(void* self, DWORD d)
{
    CarTracePush("Car::sub_476230", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_476230)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_476270(void* self, DWORD d)
{
    CarTracePush("Car::sub_476270", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_476270)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_4762D0(void* self, DWORD d)
{
    CarTracePush("Car::sub_4762D0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4762D0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_4762E0(void* self, DWORD d)
{
    CarTracePush("Car::jam_accelerator", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4762E0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_4762F0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4762F0)(self, 0);
    CarTracePush("Car::sub_4762F0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_476300(void* self, DWORD d)
{
    CarTracePush("Car::sub_476300", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_476300)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_476310(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_476310)(self, 0);
    CarTracePush("Car::sub_476310", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_476350(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_476350)(self, 0);
    CarTracePush("Car::unjam_accelerator", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_482D90(void* self, DWORD d, DWORD a0, DWORD a1)
{
    CarTracePush("Car::sub_482D90", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, 0, 0);
    ((Tc2v)_Car_482D90)(self, 0, a0, a1);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_4895E0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4895E0)(self, 0);
    CarTracePush("Car::sub_4895E0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_48A930(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::sub_48A930", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_48A930)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_49EFC0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_49EFC0)(self, 0);
    CarTracePush("Car::sub_49EFC0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_49EFD0(void* self, DWORD d)
{
    CarTracePush("Car::sub_49EFD0", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_49EFD0)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_49EFE0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_49EFE0)(self, 0);
    CarTracePush("Car::sub_49EFE0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4A9AD0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4A9AD0)(self, 0);
    CarTracePush("Car::sub_4A9AD0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4AFB30(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4AFB30)(self, 0);
    CarTracePush("Car::sub_4AFB30", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4B9A30(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_4B9A30)(self, 0, a0);
    CarTracePush("Car::sub_4B9A30", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4BE7A0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_4BE7A0)(self, 0, a0);
    CarTracePush("Car::sub_4BE7A0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4BE980(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_4BE980)(self, 0, a0);
    CarTracePush("Car::sub_4BE980", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4BE9C0(void* self, DWORD d, DWORD a0)
{
    DWORD r = ((Tc1)_Car_4BE9C0)(self, 0, a0);
    CarTracePush("Car::sub_4BE9C0", (DWORD)_ReturnAddress(), (DWORD)self, a0, r, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4BE9F0(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4BE9F0)(self, 0);
    CarTracePush("Car::sub_4BE9F0", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_4BEA20(void* self, DWORD d)
{
    CarTracePush("Car::sub_4BEA20", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4BEA20)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_4BEAC0(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Car_4BEAC0)(self, 0, a0, a1);
    CarTracePush("Car::sub_4BEAC0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4BEB30(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4BEB30)(self, 0);
    CarTracePush("Car::sub_4BEB30", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_4BEB70(void* self, DWORD d)
{
    CarTracePush("Car::sub_4BEB70", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4BEB70)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_4BEBC0(void* self, DWORD d, DWORD a0, DWORD a1)
{
    DWORD r = ((Tc2)_Car_4BEBC0)(self, 0, a0, a1);
    CarTracePush("Car::sub_4BEBC0", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, r, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4BED90(void* self, DWORD d, DWORD a0, DWORD a1, DWORD a2, DWORD a3)
{
    DWORD r = ((Tc4)_Car_4BED90)(self, 0, a0, a1, a2, a3);
    CarTracePush("Car::sub_4BED90", (DWORD)_ReturnAddress(), (DWORD)self, a0, a1, a2, a3);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

DWORD __fastcall HookCar_4BEE10(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4BEE10)(self, 0);
    CarTracePush("Car::sub_4BEE10", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_4BEF70(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::sub_4BEF70", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_4BEF70)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

DWORD __fastcall HookCar_4BF000(void* self, DWORD d)
{
    DWORD r = ((Tc0)_Car_4BF000)(self, 0);
    CarTracePush("Car::sub_4BF000", (DWORD)_ReturnAddress(), (DWORD)self, r, 0, 0, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
    return r;
}

void __fastcall HookCar_4BF070(void* self, DWORD d)
{
    CarTracePush("Car::ExtinguishCar", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4BF070)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_4BF100(void* self, DWORD d)
{
    CarTracePush("Car::sub_4BF100", (DWORD)_ReturnAddress(), (DWORD)self, 0, 0, 0, 0);
    ((Tc0v)_Car_4BF100)(self, 0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void __fastcall HookCar_4BF180(void* self, DWORD d, DWORD a0)
{
    CarTracePush("Car::sub_4BF180", (DWORD)_ReturnAddress(), (DWORD)self, a0, 0, 0, 0);
    ((Tc1v)_Car_4BF180)(self, 0, a0);
    __asm {
        mov ecx, self
        mov edx, d
    }
}

void DumpCarRing(FILE* f)
{
    DWORD total = g_carRingIdx;
    DWORD n = (total < CAR_RING_SIZE) ? total : CAR_RING_SIZE;
    fprintf(f, "CAR-CALL RING (last %lu of %lu):\r\n",
            (unsigned long)n, (unsigned long)total);
    for (DWORD k = 0; k < n; ++k) {
        const CarTraceRec* r = &g_carRing[(g_carRingIdx - n + 1 + k) % CAR_RING_SIZE];
        if (!r->name) continue;
        fprintf(f, "  %-40s call=0x%08lX self=0x%08lX a1=0x%08lX a2=0x%08lX a3=0x%08lX a4=0x%08lX\r\n",
                r->name ? r->name : "?",
                (unsigned long)r->caller, (unsigned long)r->self,
                (unsigned long)r->a1, (unsigned long)r->a2,
                (unsigned long)r->a3, (unsigned long)r->a4);
    }
}

void DumpCarRingFile(void)
{
    FILE* f = fopen(kCarTapePath, "ab");
    if (!f) return;
    DWORD total = g_carRingIdx;
    DWORD delta = total - g_carTaped;
    if (delta == 0) {
        fclose(f);
        return;
    }
    if (delta > CAR_RING_SIZE) {
        g_carTaped = total - CAR_RING_SIZE;
        delta = CAR_RING_SIZE;
    }
    for (DWORD k = 0; k < delta; ++k) {
        const CarTraceRec* r = &g_carRing[(g_carTaped + k) % CAR_RING_SIZE];
        if (!r->name) continue;
        fprintf(f, "  %-40s call=0x%08lX self=0x%08lX a1=0x%08lX a2=0x%08lX a3=0x%08lX a4=0x%08lX\r\n",
                r->name ? r->name : "?",
                (unsigned long)r->caller, (unsigned long)r->self,
                (unsigned long)r->a1, (unsigned long)r->a2,
                (unsigned long)r->a3, (unsigned long)r->a4);
    }
    g_carTaped = total;
    fclose(f);
}