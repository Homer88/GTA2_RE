#ifndef ___WEAPON___H_
#define ___WEAPON___H_

#include <assert.h>

// Weapon struct (IDA gta2.exe.h:4961). Size 0x30 (48 bytes). Entries live in
// gWeaponDatabase: heap WeaponDatabase (operator_new(0x2FDC)),
// 255 slots x 0x30 + 8 header bytes.
// WeaponType enum: IDA gta2.exe.h (WeaponType).
struct Player;
struct Car;
struct Ped;

struct Weapon {
    unsigned short Ammo;
    char TimeToReload;
    char field_3;
    int SMG;
    int field_8;
    int field_C;
    short shortField;          // __int16 short
    char field_12;
    char field_13;
    Car* Car;
    Weapon* NextWeapon;
    int TypeWeapon;            // WeaponType enum
    char field_20;
    char field_21;
    char field_22;
    char field_23;
    Ped* Ped;
    int SoundWeapon;
    char field_2C;
    char field_2D;
    char field_2E;
    char field_2F;
};
static_assert(sizeof(Weapon) == 0x30, "Weapon size 0x30");

// WeaponDatabase (IDA gta2.exe.h:7355), size 0x2FDC:
// 8 header + 255 * 0x30 = 0x2FD8 base; tail 4 bytes (field_2FD8 short + 2 chars).
struct WeaponDatabase {
    Weapon* sWeapon;
    Weapon* NextWeapon;
    Weapon sWeapon_Arr255[255];
    short field_2FD8;
    char field_2FDA;
    char field_2FDB;
};
static_assert(sizeof(WeaponDatabase) == 0x2FDC, "WeaponDatabase size 0x2FDC");

// Detours must mirror the retail __thiscall ABI exactly. The __fastcall form
// (this, _EDX, <stack args...>) keeps ECX = this, places the retail-pushed
// arguments on the stack at the right offsets and cleans the 4/8 bytes the
// retail caller expects, so the call site stays balanced.
void __fastcall SetWeapon(Weapon* pWeapon, void* _EDX, void* TypeWeapon); // Weapon::SetWeapon @0x00433810
void __fastcall SetPed(Weapon* pWeapon, void* _EDX, void* pPed);          // Weapon::SetPed    @0x004CCA10

#endif