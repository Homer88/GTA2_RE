#ifndef ___PED___H_
#define ___PED___H_

#include <assert.h>

enum OCUPATION : unsigned char {
	OCCUPATION_PLAYER = 0u,
	OCCUPATION_EMPTY = 1u,
	OCCUPATION_2 = 2u,
	OCCUPATION_DUMMY = 3u,
	OCCUPATION_4 = 4u,
	OCCUPATION_DRIVER = 5u,
	OCCUPATION_PSYCHO = 14u,
	OCCUPATION_MUGGER = 15u,
	OCCUPATION_CARTHIEF = 16u,
	OCCUPATION_BANK_ROBBER = 17u,
	OCCUPATION_CRIMINAL = 18u,
	OCCUPATION_ELVIS = 22u,
	OCCUPATION_POLICE = 24u,
	OCCUPATION_SWAT = 25u,
	OCCUPATION_FBI = 26u,
	OCCUPATION_ARMY = 27u,
	OCCUPATION_GUARD = 28u,
	OCCUPATION_GUARD_AGAINST_PLAYER = 32u,
	OCCUPATION_CRIMINAL_TYPE1 = 33u,
	OCCUPATION_CRIMINAL_TYPE2 = 34u,
	OCCUPATION_SPECIAL_GROUP_MEMBER = 35u,
	OCCUPATION_TANK_DRIVER = 36u,
	OCCUPATION_37 = 37u,
	OCCUPATION_FIREMAN = 38u,
	OCCUPATION_ROAD_BLOCK_TANK_MAN = 39u,
	OCCUPATION_DRONE = 41u,
	OCCUPATION_42 = 42u,
	OCCUPATION_STAND_STILL_BLOKE = 43u,
	OCCUPATION_ELVIS_LEADER = 44u,
	OCCUPATION_REFUGEES = 45u,
	OCCUPATION_ANY_LAW_ENFORCEMENT = 46u,
	OCCUPATION_ANY_EMERGENCY_SERVICE_MAN = 47u,
	OCCUPATION_ANY_GANG_MEMBER = 48u,
	OCCUPATION_ANY_ELVIS = 49u,
	OCCUPATION_50 = 50u,
	OCCUPATION_NONE = 51u
};

enum PedActions : unsigned int {
	ACTION_ENTERING_CAR = 1u,
	ACTION_EXITING_CAR = 59u
};

enum PedState : unsigned int {
	PEDSTATE_MOVE_TURN = 0u,
	PEDSTATE_ENTER_CAR = 3u,
	PEDSTATE_EXIT_CAR = 4u,
	PEDSTATE_IDLE = 7u,
	PEDSTATE_FALL = 8u,
	PEDSTATE_DEAD = 9u,
	PEDSTATE_IN_CAR = 10u
};

enum Remap : unsigned char {
	REMAP_COP = 0u,
	REMAP_GREEN_COP = 1u,
	REMAP_RED_COP = 2u,
	REMAP_YELLOW_COP = 3u,
	REMAP_ARMY = 4u,
	REMAP_REDNECK_1 = 5u,
	REMAP_REDNECK_2 = 6u,
	REMAP_SCIENTIST = 7u,
	REMAP_ZAIBATSU = 8u,
	REMAP_KRISHNA = 9u,
	REMAP_RUSSIAN = 10u,
	REMAP_LOONIE = 11u,
	REMAP_ELVIS = 12u,
	REMAP_YAKUZA = 13u,
	REMAP_FIRE_FIGHTER = 14u,
	REMAP_CAR_JACKER = 15u,
	REMAP_MEDIC = 16u,
	REMAP_PICKPOCKET = 17u,
	REMAP_BLUE_PEDESTRIAN = 18u,
	REMAP_LIGHT_BLUE_PEDESTRIAN = 19u,
	REMAP_RED_PEDESTRIAN = 20u,
	REMAP_PEDESTRIAN = 21u,
	REMAP_PRISONER = 22u,
	REMAP_HULK = 23u,
	REMAP_HULK_GREEN = 24u,
	REMAP_PLAYER = 25u,
	REMAP_NAKED_PEDESTRIAN = 26u,
};

// Ped struct (IDA gta2.exe.h:3925). Size 0x294 (660 bytes), verified:
// PedManager pool = operator_new(0x203AC); Construct(this->Ped, 0x294, 200, ...)
// free-list step +165 dwords (=+660) => 200 peds x 0x294.
// IDA named the header block S200[3] and then jumped to field_CB: the unnamed
// animation area 0x09..0xCA is kept as gap. Pack(1) preserves the raw offsets
// (several pointer fields sit on unaligned addresses).

struct Player;
struct Car;
struct GameObject;
struct Weapon;
struct Gang;
struct S94;
struct S169;

#pragma pack(push, 1)
struct Ped {
    char S200[9];            // 0x00 S200[3] (header / anim block prefix)
    char gap9[0xC2];         // 0x09..0xCA (unnamed animation area)
    char field_CB;           // 0xCB
    char field_CC;
    char field_CD;
    char field_CE;
    char field_CF;
    char field_D0;
    char field_D1;
    char field_D2;
    char field_D3;
    char field_D4;
    char field_D5;
    char field_D6;
    char field_D7;
    char field_D8;
    char field_D9;
    char field_DA;
    char field_DB;
    char field_DC;
    char field_DD;
    char field_DE;
    char field_DF;
    char field_E0;
    char field_E1;
    char field_E2;
    char field_E3;
    char field_E4;
    char field_E5;
    char field_E6;
    char field_E7;
    char field_E8;
    char field_E9;
    char field_EA;
    char field_EB;
    char field_EC;
    char field_ED;
    char field_EE;
    char field_EF;
    char field_F0;
    char field_F1;
    char field_F2;
    char field_F3;
    char field_F4;
    char field_F5;
    char field_F6;
    char field_F7;
    char field_F8;
    char field_F9;
    char field_FA;
    Player* isPlayer;        // 0xFB
    char field_FF;
    char field_100;
    char field_101;
    char field_102;
    char field_103;
    char field_104;
    char field_105;
    char field_106;
    GameObject* GameObject2; // 0x107
    char field_10B;
    char field_10C;
    char field_10D;
    char field_10E;
    Weapon* WeaponSelect;    // 0x10F
    char field_113;
    char field_114;
    char field_115;
    char field_116;
    short field_117;
    char field_119;
    char field_11A;
    char field_11B;
    char field_11C;
    char field_11D;
    char field_11E;
    char field_11F;
    char field_120;
    char field_121;
    char field_122;
    char field_123;
    char field_124;
    char field_125;
    char field_126;
    char field_127;
    short field_128;
    char field_12A;
    char field_12B;
    short field_12C;
    short field_12E;
    short field_130;
    short field_132;
    short field_134;
    char field_136;
    char field_137;
    GameObject* GameObject1; // 0x138
    int field_13C;
    Car* Car1;               // 0x140
    Ped* sPed1;              // 0x144
    Ped* Driver;             // 0x148
    Ped* LinkedPed;          // 0x14C
    Car* Vehicle;            // 0x150
    Car* CurrentVehicle;     // 0x154
    Car* TargetCarForEnter;  // 0x158
    Player* Player;          // 0x15C
    Ped* NextPed;            // 0x160
    S169* S169;              // 0x164
    GameObject* GameObject;  // 0x168
    Car* CurrentCar;         // 0x16C
    Weapon* SelectedWeapon;  // 0x170
    Weapon* Weapon1;         // 0x174
    Weapon* Weapon2;         // 0x178
    struct Gang* Gang;        // 0x17C (member name shadows type Gang)
    Ped* DriverPed;          // 0x180
    int field_184;
    Ped* LastCharPunched;    // 0x188
    Ped* field_18C;
    S94* S94;                // 0x190
    int field_194;
    Ped* sPed3;              // 0x198
    struct Gang* Gang1;      // 0x19C
    int PedId;               // 0x1A0
    short TargetCarDoor1;    // 0x1A4
    short PoliceStar1;       // 0x1A6
    Ped* ElvisLeader;        // 0x1A8
    int XCoordinate;         // 0x1AC
    int PositionY;           // 0x1B0
    int Camer_Z_View;        // 0x1B4
    int PositionX1;          // 0x1B8
    int PositionY1;          // 0x1BC
    int PositionZ2;          // 0x1C0
    int X;                   // 0x1C4
    int Y;                   // 0x1C8
    int Z;                   // 0x1CC
    int field_1D0;
    int field_1D4;
    int field_1D8;
    int OCCUPATION;          // 0x1DC
    Ped* DriverPed1;         // 0x1E0
    int PositionZ1;          // 0x1E4
    int field_1E8;
    int field_1EC;
    int field_1F0;
    int field_1F4;
    int CurrentAction1;      // 0x1F8
    int field_1FC;
    int ID;                  // 0x200
    int IDPed;               // 0x204
    short Invulnerability;   // 0x208
    short PoliceStar;        // 0x20A
    short field_20C;
    unsigned short field_20E;
    short field_210;
    short field_212;
    short field_214;         // PedState (GetPedState returns field_214)
    short Health;            // 0x216 (HIWORD of PositionY alias in SetHealth)
    short ObjectiveTimer;
    short CarStateTimer;
    unsigned int Flags;      // 0x21C
    int field_220;
    char field_224;
    char DamageState;        // 0x225
    unsigned char ExitAnimState;
    char field_227;
    int field_228;
    int field_22C;
    int field_230;
    char field_234;
    char field_235;
    char field_236;
    char field_237;
    int SearchType;          // 0x238
    char CarId;              // 0x23C
    char field_23D;
    char field_23E;
    char field_23F;
    int Occupation;          // 0x240 (ALL_PED)
    char Remap;              // 0x244 (enum :int8)
    char field_245;
    char field_246;
    char field_247;
    int TargetCarDoor;       // 0x248
    char AnimationState;     // 0x24C
    char field_24D;
    char field_24E;
    char field_24F;
    int field_250;
    char field_254;
    char field_255;
    char field_256;
    char field_257;
    int ActionState;         // 0x258
    int CurrentAction;       // 0x25C
    char field_260;
    char field_261;
    char field_262;
    char field_263;
    char field_264;
    unsigned char field_265;
    char field_266;
    char field_267;
    char field_268;
    char field_269;
    char field_26A;
    char field_26B;
    int GraphicType;         // 0x26C
    int field_270;
    int GangCarModel;        // 0x274
    int PedState;            // 0x278
    int field_27C;
    int SavedState;          // 0x280
    int field_284;
    int field_288;
    int field_28C;
    int DamageType;          // 0x290
};
#pragma pack(pop)
static_assert(sizeof(Ped) == 0x294, "Ped size 0x294");

// PedManager (gta2.exe.h:10201), heap pool 0x203AC =
// 8 header + 200*0x294 + PedsInUse(2) + 2. Global gPedManager ptr @0x005E5BBC.
struct PedManager {
    Ped* FirstElement;
    Ped* NextPed;
    Ped Ped[200];
    short PedsInUse;
    char field_203AA;
    char field_203AB;
};
static_assert(sizeof(PedManager) == 0x203AC, "PedManager size 0x203AC");

#endif