#include "gta2_shim.h"

// Module: other, Class: WeaponDatabase
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004cda20: WeaponDatabase::WeaponDatabase
// IDA: WeaponDatabase::WeaponDatabase
// Ghidra: ---
WeaponDatabase * gta2::WeaponDatabase_WeaponDatabase(struct WeaponDatabase *self)
{
  struct Weapon *sWeapon_Arr255; // edi
  struct Weapon *p_NextWeapon; // eax
  int count; // ecx

  sWeapon_Arr255 = self->sWeapon_Arr255;
  gta2::Construct(self->sWeapon_Arr255, 48, 255, Weapon::Weapon, Weapon::Weapon_dec);
  p_NextWeapon = (struct Weapon *)&sWeapon_Arr255->NextWeapon;
  count = 254;
  do
  {
    *(_DWORD *)&p_NextWeapon->Ammo = &p_NextWeapon->NextWeapon;
    ++p_NextWeapon;
    --count;
  }
  while ( count );
  self->sWeapon = sWeapon_Arr255;
  self->sWeapon_Arr255[254].NextWeapon = 0;
  self->NextWeapon = 0;
  self->field_2FD8 = 0;
  return self;
}



