#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <assert.h>

// Forward declarations: Player only ever holds pointers to these; the full
// types live in their own headers (cPed.h, cCar.h, cWeapon.h, cGangs.h,
// cAudioManager.h) which include this file, so we must not include them here.
struct S103;
struct Tango;
struct CameraOrPhysics;
struct S131;
struct PlayerStats;
struct Ped;
struct Car;
struct Weapon;
struct Gangs;
struct AudioManager;

enum StarPolice {
	StarPolice_0=0u,
	StarPolice_1 = 600u,                  /// ���� ������
	StarPolice_2 = 1600u,                 /// ��� ������ 
	StarPolice_3 = 3000u,
	StarPolice_4 = 5000u,
	StarPolice_5 = 8000u,
	StarPolice_6 = 12000u,
};


enum WantedLevel {
	Level_0 = 0u,
	Level_1 = 1u,
	Level_2 = 2u,
	Level_3 = 3u,
	Level_4 = 4u,
	Level_5 = 5u,
	Level_6 = 6u,
};

// Layout reconstructed from IDA struct Player (gta2.exe.h:3394) and verified
// against operator_new(0x85C) in the Player allocation (gta2.exe.c:77107) and
// the Player::Player ctor / Player_Des dtor. Offsets are exact; gap* arrays
// are raw bytes IDA could not type. Size == 0x85C.
struct Player {
	unsigned char CurrentPlayer;          // +0x00
	Player*        Player;                // +0x04 self/index pointer
	unsigned short Rotate;                // +0x08 KeyPlayer (enum : short)
	unsigned int   FW;                    // +0x0C FW enum (int)
	::S103*          S103;                  // +0x10
	short          Sw;                    // +0x14
	short          TypeWeapon;            // +0x16
	::S103*          S103_1;                // +0x18
	short          SelectWeaponNext;      // +0x1C
	char           field_1E;              // +0x1E
	char           field_1F;              // +0x1F
	::S103*          pS103;                 // +0x20
	int            ID;                    // +0x24
	::S103*          S103_2;                // +0x28
	short          MoneyValue;            // +0x2C
	unsigned char  Ids;                   // +0x2E
	char           field_2F;              // +0x2F
	::S103*          S103_5;                // +0x30
	Gangs*         RESPECT;               // +0x34
	::S103*          field_38;              // +0x38
	int            field_3C;              // +0x3C
	::S103*          S103_4;                // +0x40
	unsigned int   DeathReason;           // +0x44 DEATH_REASON enum (int)
	Tango*         Tango1;                // +0x48
	int            Sound;                 // +0x4C
	int            field_50;              // +0x50
	int            field_54;              // +0x54
	int            field_58;              // +0x58
	Car*           sCar1;                 // +0x5C
	int            field_60;              // +0x60
	int            field_64;              // +0x64
	int            MultiPlayerMode;       // +0x68
	int            field_6C;              // +0x6C
	unsigned char  Up;                    // +0x70
	unsigned char  Down;                  // +0x71
	unsigned char  Left;                  // +0x72
	unsigned char  Right;                 // +0x73
	unsigned char  prevWeapon;            // +0x74
	unsigned char  nextWeapon;            // +0x75
	unsigned char  debugKey1;             // +0x76
	unsigned char  debugKey2;             // +0x77
	bool           Forward;               // +0x78
	bool           Backward;              // +0x79
	bool           RotateLeft;            // +0x7A
	bool           RotateRight;           // +0x7B
	bool           Attack;                // +0x7C
	bool           Enter;                 // +0x7D
	bool           Jump;                  // +0x7E
	bool           NextWeaponZ;           // +0x7F
	bool           PrevWeaponX;           // +0x80
	bool           keySpecial;            // +0x81
	bool           keySpecial2;           // +0x82
	char           field_83;              // +0x83
	int            field_84;              // +0x84
	int            field_88;              // +0x88
	char           AttackIsChanged;       // +0x8C
	char           field_8D;              // +0x8D
	unsigned char  PlayerNext;            // +0x8E
	char           field_8F;              // +0x8F
	::CameraOrPhysics* CameraOrPhysics1;    // +0x90
	char           field_94;              // +0x94
	char           field_95;              // +0x95
	char           field_96;              // +0x96
	char           field_97;              // +0x97
	int            State;                 // +0x98
	AudioManager*  AudioManager;          // +0x9C
	int            field_A0;              // +0xA0
	char           gapA4[3];              // +0xA4
	char           field_A7;              // +0xA7
	char           field_A8;              // +0xA8
	char           field_A9;              // +0xA9
	unsigned char  sbw;                   // +0xAA
	unsigned char  tpa;                   // +0xAB
	char           field_AC;              // +0xAC
	char           gapAD[11];             // +0xAD
	S131*          S1__;                  // +0xB8
	char           gapBC[23];             // +0xBC
	char           field_D3;              // +0xD3
	char           gapD4[7];              // +0xD4
	char           field_DB;              // +0xDB
	char           gapDC[14];             // +0xDC
	char           field_EA;              // +0xEA
	char           gapEB[12];             // +0xEB
	char           field_F7;              // +0xF7
	char           gapF8[10];             // +0xF8
	char           field_102;             // +0x102
	char           gap103[18];            // +0x103
	char           field_115;             // +0x115
	char           field_116;             // +0x116
	char           field_117;             // +0x117
	int            field_118;             // +0x118
	int            field_11C;             // +0x11C
	int            field_120;             // +0x120
	char           field_124;             // +0x124
	char           field_125;             // +0x125
	char           field_126;             // +0x126
	char           field_127;             // +0x127
	int            field_128;             // +0x128
	int            field_12C;             // +0x12C
	int            field_130;             // +0x130
	char           gap134[24];            // +0x134
	::CameraOrPhysics* CameraOrPhysics;     // +0x14C
	char           gap150[4];             // +0x150
	char           field_154;             // +0x154
	char           gap155[62];            // +0x155
	char           field_193;             // +0x193
	char           gap194[18];            // +0x194
	char           field_1A6;             // +0x1A6
	char           gap1A7[32];            // +0x1A7
	char           field_1C7;             // +0x1C7
	char           gap1C8[9];             // +0x1C8
	char           field_1D1;             // +0x1D1
	int            field_1D4;             // +0x1D4
	int            field_1D8;             // +0x1D8
	int            field_1DC;             // +0x1DC
	char           gap1E0[4];             // +0x1E0
	int            Camer_X_View;          // +0x1E4
	int            Camer_Y_View;          // +0x1E8
	int            Camer_Z_View;          // +0x1EC
	char           gap1F0[3];             // +0x1F0
	char           field_1F3;             // +0x1F3
	char           gap1F4[6];             // +0x1F4
	char           field_1FA;             // +0x1FA
	char           gap1FB[7];             // +0x1FB
	char           field_202;             // +0x202
	char           gap203[5];             // +0x203
	::CameraOrPhysics* CameraOrPhysics2;    // +0x208
	char           field_20C;             // +0x20C
	char           gap20D[28];            // +0x20D
	char           field_229;             // +0x229
	char           gap22A[35];            // +0x22A
	char           field_24D;             // +0x24D
	char           gap24E[11];            // +0x24E
	char           field_259;             // +0x259
	char           gap25A[17];            // +0x25A
	char           field_26B;             // +0x26B
	char           gap26C[32];            // +0x26C
	char           field_28C;             // +0x28C
	char           gap28D[11];            // +0x28D
	char           field_298;             // +0x298
	char           gap299[5];             // +0x299
	char           field_29E;             // +0x29E
	char           field_29F;             // +0x29F
	int            AuxGameCameraX;        // +0x2A0
	int            AuxGameCameraY;        // +0x2A4
	int            AuxGameCameraZ;        // +0x2A8
	char           gap2AC[24];            // +0x2AC
	Ped*           MainPed;               // +0x2C4
	Ped*           pPassenger;            // +0x2C8
	Car*           sCar2;                 // +0x2CC
	char           field_2D0;             // +0x2D0
	PlayerStats*   Money;                 // +0x2D4
	char           gap2D8[107];           // +0x2D8
	char           field_343;             // +0x343
	char           gap344[160];           // +0x344
	char           field_3E4;             // +0x3E4
	char           gap3E5[53];            // +0x3E5
	char           field_41A;             // +0x41A
	char           gap41B[46];            // +0x41B
	char           field_449;             // +0x449
	char           gap44A[31];            // +0x44A
	char           field_469;             // +0x469
	char           field_46A;             // +0x46A
	char           field_46B;             // +0x46B
	char           field_46C;             // +0x46C
	char           field_46D;             // +0x46D
	char           field_46E;             // +0x46E
	char           field_46F;             // +0x46F
	char           field_470;             // +0x470
	char           field_471;             // +0x471
	char           field_472;             // +0x472
	char           field_473;             // +0x473
	char           field_474;             // +0x474
	char           field_475;             // +0x475
	char           field_476;             // +0x476
	char           field_477;             // +0x477
	char           field_478;             // +0x478
	char           field_479;             // +0x479
	char           field_47A;             // +0x47A
	char           field_47B;             // +0x47B
	char           field_47C;             // +0x47C
	char           field_47D;             // +0x47D
	char           field_47E;             // +0x47E
	char           field_47F;             // +0x47F
	char           field_480;             // +0x480
	char           gap481[9];             // +0x481
	char           field_48A;             // +0x48A
	char           gap48B[437];           // +0x48B
	char           field_640;             // +0x640
	int            field_644;             // +0x644
	char           gap648[48];            // +0x648
	int            field_678;             // +0x678
	int            field_67C;             // +0x67C
	unsigned short field_680;             // +0x680
	short          field_682;             // +0x682
	PlayerStats*   Lives;                 // +0x684
	char           gap688[52];            // +0x688
	PlayerStats*   MultiPlayer;           // +0x6BC
	char           field_6C0;             // +0x6C0
	char           gap6C1[24];            // +0x6C1
	char           field_6D9;             // +0x6D9
	char           gap6DA[11];            // +0x6DA
	char           field_6E5;             // +0x6E5
	char           gap6E6[6];             // +0x6E6
	char           field_6EC;             // +0x6EC
	__declspec(align(4)) char field_6F0;  // +0x6F0
	short          PowerUp[18];           // +0x6F2 POWERUP_TYPE : short
	Weapon*        sWeapon[28];           // +0x718
	short          SelectWeapon;          // +0x788
	bool           quit1;                 // +0x78A
	char           field_78B;             // +0x78B
	Ped*           sPed1;                 // +0x78C
	char           gap790[4];             // +0x790
	char           Network;               // +0x794
	char           gap795[9];             // +0x795
	char           field_79E;             // +0x79E
	char           gap79F[157];           // +0x79F
	wchar_t        string_Arr0x16[16];    // +0x83C
};

static_assert (sizeof(Player) == 0x85C, "ERROR PLAYER");

#endif // !__PLAYER_H__
