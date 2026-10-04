#include "gta2_shim.h"

// Module: other, Class: Gang
// Functions: 10
// Source: unified (IDA+Ghidra)

// 0x004758a0: Gang::SetRemap
// IDA: Gang::SetRemap
// Ghidra: ---
void gta2::Gang_SetRemap(struct Gang *self, char a2)
{
  self->remap = a2;
}


// 0x004758b0: Gang::SetWeapon1
// IDA: Gang::SetWeapon1
// Ghidra: ---
void gta2::Gang_SetWeapon1(struct Gang *self, Weapon *a2)
{
  self->Weapon1 = a2;
}


// 0x004758c0: Gang::SetWeapon2
// IDA: Gang::SetWeapon2
// Ghidra: ---
void gta2::Gang_SetWeapon2(struct Gang *self, Weapon *a2)
{
  self->Weapon2 = a2;
}


// 0x004758d0: Gang::SetWeapon3
// IDA: Gang::SetWeapon3
// Ghidra: ---
void gta2::Gang_SetWeapon3(struct Gang *self, int a2)
{
  self->Weapon3 = (struct Weapon *)a2;
}


// 0x004758e0: Gang::SetTypeCar
// IDA: Gang::SetTypeCar
// Ghidra: ---
void gta2::Gang_SetTypeCar(struct Gang *self, int a2)
{
  self->CarType = a2;
}


// 0x004758f0: Gang::SetCar_remap
// IDA: Gang::SetCar_remap
// Ghidra: ---
void gta2::Gang_SetCar_remap(struct Gang *self, char a2)
{
  self->Car_remap = a2;
}


// 0x00475900: Gang::Set_475900
// IDA: Gang::Set_475900
// Ghidra: ---
void gta2::Gang_Set_475900(struct Gang *self, char a2)
{
  self->field_111 = a2;
}


// 0x00475910: Gang::SetXYZ
// IDA: Gang::SetXYZ
// Ghidra: FUN_00475910
void gta2::Gang_SetXYZ(int param_1,undefined4 param_2,undefined4 param_3, undefined4 param_4)
{
  *(undefined4 *)(param_1 + 300) = param_2;
  *(undefined4 *)(param_1 + 0x130) = param_3;
  *(undefined4 *)(param_1 + 0x134) = param_4;
  return;
}


// 0x00475940: Gang::SetGang
// IDA: Gang::SetGang
// Ghidra: ---
void gta2::Gang_SetGang(struct Gang *self, GANG a2)
{
  self->NextGang = a2;
}


// 0x00475950: Gang::SetKillChar
// IDA: Gang::SetKillChar
// Ghidra: ---
void gta2::Gang_SetKillChar(struct Gang *self, byte a2)
{
  self->Visible = a2;
}



