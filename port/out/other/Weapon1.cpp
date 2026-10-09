#include "gta2_shim.h"

// Module: other, Class: Weapon1
// Functions: 7
// Source: unified (IDA+Ghidra)

// 0x004a4f20: Weapon1::sub_4A4F20
// IDA: Weapon1::sub_4A4F20
// Ghidra: ---
Weapon * gta2::Weapon1_sub_4A4F20(struct WeaponDatabase *self, Weapon *pWeapon)
{
  Weapon *NextWeapon; // esi
  Weapon *v4; // edi
  Weapon *result; // eax
  Weapon *sWeapon; // edx

  NextWeapon = self->NextWeapon;
  v4 = 0;
  if ( NextWeapon )
  {
    result = pWeapon;
    while ( NextWeapon != pWeapon )
    {
      v4 = NextWeapon;
      NextWeapon = NextWeapon->NextWeapon;
      if ( !NextWeapon )
        return result;
    }
    result = gta2::Weapon_sub_4CCB40(NextWeapon);
    if ( v4 )
    {
      result = NextWeapon->NextWeapon;
      v4->NextWeapon = result;
      NextWeapon->NextWeapon = self->sWeapon;
    }
    else
    {
      sWeapon = self->sWeapon;
      self->NextWeapon = NextWeapon->NextWeapon;
      NextWeapon->NextWeapon = sWeapon;
    }
    self->sWeapon = NextWeapon;
  }
  return result;
}


// 0x004cc9b0: Weapon1::GetNextWeapon
// IDA: Weapon1::GetNextWeapon
// Ghidra: ---
Weapon * gta2::Weapon1_GetNextWeapon(struct WeaponDatabase *self)
{
  return self->NextWeapon;
}


// 0x004cc9c0: Weapon1::MoveWeaponToNextList
// IDA: Weapon1::MoveWeaponToNextList
// Ghidra: ---
Weapon * gta2::Weapon1_MoveWeaponToNextList(struct WeaponDatabase *self)
{
  Weapon *NextWeapon; // edx
  Weapon *sWeapon; // esi

  NextWeapon = self->NextWeapon;
  sWeapon = self->sWeapon;
  self->sWeapon = self->sWeapon->NextWeapon;
  sWeapon->NextWeapon = NextWeapon;
  self->NextWeapon = sWeapon;
  gta2::Weapon_InitializeWeapon(sWeapon);
  return sWeapon;
}


// 0x004cc9e0: Weapon1::sub_4CC9E0
// IDA: Weapon1::sub_4CC9E0
// Ghidra: ---
Weapon * gta2::Weapon1_sub_4CC9E0(struct WeaponDatabase *self)
{
  Weapon *sWeapon; // esi

  sWeapon = self->sWeapon;
  self->sWeapon = self->sWeapon->NextWeapon;
  sWeapon->NextWeapon = 0;
  gta2::Weapon_InitializeWeapon(sWeapon);
  return sWeapon;
}


// 0x004cd9f0: Weapon1::sub_4CD9F0
// IDA: Weapon1::sub_4CD9F0
// Ghidra: FUN_004cd9f0
void gta2::Weapon1_sub_4CD9F0(undefined4 *param_1)
{
  *param_1 = 0;
  param_1[1] = 0;
  _eh_vector_destructor_iterator_(param_1 + 2,0x30,0xff,Weapon::~Weapon);
  return;
}


// 0x004cda70: Weapon1::sub_4CDA70
// IDA: Weapon1::sub_4CDA70
// Ghidra: ---
void gta2::Weapon1_sub_4CDA70(struct WeaponDatabase *self, Weapon *a2)
{
  gta2::Weapon_sub_4CCB40(a2);
  a2->NextWeapon = self->sWeapon;
  self->sWeapon = a2;
}


// 0x004d07e0: Weapon1::sub_4D07E0
// IDA: Weapon1::sub_4D07E0
// Ghidra: FUN_004d07e0
void * gta2::Weapon1_sub_4D07E0(void *param_1,byte param_2)
{
  FUN_004cd9f0();
  if ((param_2 & 1) != 0) {
    free(param_1);
  }
  return param_1;
}



