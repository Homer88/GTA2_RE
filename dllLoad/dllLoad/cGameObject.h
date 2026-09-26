#ifndef __GAMEOBJECT__H_
#define __GAMEOBJECT__H_

#include <stddef.h>

struct Ped;
struct Car;
struct SpriteS1;

// Source of truth: IDA struct GameObject, gta2.exe.h:4988-5061.
// sizeof == 0xB4 == pool element size: Construct(this->GameObject, 180, 400, ...)
// (gta2.exe.c:46983).  NOTE: the PedPool itself is only ever heap-allocated
// (operator_new(0x11944), gta2.exe.c:56082) - done.md's 0x0066A3B4 "S50
// PedPool" row is NOT a static pool; 0x0066A3B8 is unk_66A3B8 (a byte counter,
// gta2.exe.c:129025) and 0x0066A3BC is unk_66A3BC (the free-list head pointer,
// gta2.exe.c:125639-125641).  Reach live instances via Ped::GameObject2.
//
// Independently confirmed from raw dword/byte accesses (gta2.exe.c:121949/121957/121959):
//   *((_DWORD*)this + 31) == Ped      -> 0x7C
//   *((_DWORD*)this + 32) == SpriteS1  -> 0x80
//   *((_BYTE *)this + 22) == field_16  -> 0x16
struct GameObject
{
    GameObject* NextGameObject1; // 0x00 free-list link / next in list
    char        field_4;         // 0x04 0 = free slot, 1 = active (sub_497C20)
    char        Remap;           // 0x05 remap index, 0xFF = none
    char        field_6;         // 0x06
    char        field_7;         // 0x07
    int         field_8;         // 0x08 ped state (set_ped_state_1), init 11
    int         field_C;         // 0x0C init 28
    int         field_10;        // 0x10 door state (GetDoorState), init 36
    short       field_14;        // 0x14
    char        field_16;        // 0x16 set to 1 by Ped::SetPointedFlag (121957)
    char        field_17;        // 0x17
    int         field_18;        // 0x18
    int         ProbablyPhysics; // 0x1C
    int         field_20;        // 0x20
    int         field_24;        // 0x24 init 3
    short       field_28;        // 0x28
    short       field_2A;        // 0x2A
    short       field_2C;        // 0x2C
    char        field_2E;        // 0x2E
    char        field_2F;        // 0x2F
    int         field_30;        // 0x30 init 4
    short       short_;          // 0x34 IDA names it "short" (keyword) - renamed
    char        field_36;        // 0x36
    char        field_37;        // 0x37
    int         Speed;           // 0x38 (SetSpeed stores a pointer here)
    GameObject* NextGameObject;  // 0x3C
    short       Rotation;        // 0x40 SetRotation / get_rotation
    short       field_42;        // 0x42
    char        field_44;        // 0x44 GetDoorState-ish type, compared == 2
    char        field_45;        // 0x45
    short       field_46;        // 0x46
    char        field_48;        // 0x48
    char        field_49;        // 0x49
    short       CigaretteIdleTimer; // 0x4A
    Car*        Car1;            // 0x4C
    Car*        Car2;            // 0x50
    char        field_54;        // 0x54
    char        field_55;        // 0x55
    char        field_56;        // 0x56
    char        field_57;        // 0x57
    int         field_58;        // 0x58 bitfield (ctor masks 0xFE/0xFB/0xFD/0xD5)
    int         field_5C;        // 0x5C
    int         field_60;        // 0x60
    int         field_64;        // 0x64
    char        field_68;        // 0x68
    char        field_69;        // 0x69
    char        field_6A;        // 0x6A
    char        field_6B;        // 0x6B
    int         field_6C;        // 0x6C init 18
    char        field_70;        // 0x70
    char        field_71;        // 0x71
    char        field_72;        // 0x72
    char        field_73;        // 0x73
    short       field_74;        // 0x74
    char        field_76;        // 0x76
    char        field_77;        // 0x77
    GameObject* GameObject;      // 0x78 pool free-list next (NOT a self-ref)
    Ped*        Ped;             // 0x7C owner ped  (raw: *((_DWORD*)this+31))
    SpriteS1*   SpriteS1;        // 0x80 sprite    (raw: *((_DWORD*)this+32))
    Car*        GetVehicle;      // 0x84 current vehicle (GetCar)
    Car*        Car;             // 0x88 car linked list head
    int         field_8C;        // 0x8C
    int         Speed1;          // 0x90
    int         field_94;        // 0x94
    int         deltaX;          // 0x98
    int         deltaY;          // 0x9C
    int         field_A0;        // 0xA0 (ctor skips it - see cGameObject notes)
    int         teleportX;       // 0xA4
    int         teleportY;       // 0xA8
    int         teleportZ;       // 0xAC
    int         field_B0;        // 0xB0
};

static_assert(sizeof(GameObject) == 0xB4, "ERROR SIZE GameObject");
static_assert(offsetof(GameObject, field_16) == 0x16, "GameObject field_16");
static_assert(offsetof(GameObject, field_6C) == 0x6C, "GameObject field_6C");
static_assert(offsetof(GameObject, Ped) == 0x7C, "GameObject Ped");
static_assert(offsetof(GameObject, SpriteS1) == 0x80, "GameObject SpriteS1");
static_assert(offsetof(GameObject, GetVehicle) == 0x84, "GameObject GetVehicle");
static_assert(offsetof(GameObject, field_B0) == 0xB0, "GameObject field_B0");

#endif // !__GAMEOBJECT__H_
