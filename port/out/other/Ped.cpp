#include "gta2_shim.h"

// Module: other, Class: Ped
// Functions: 10
// Source: unified (IDA+Ghidra)

// 0x00472fd0: Ped::sub_472FD0
// IDA: Ped::sub_472FD0
// Ghidra: ---
bool gta2::Ped_sub_472FD0(struct Ped *self)
{
  return self->field_1D8 == 99;
}


// 0x00482080: Ped::SetMoneyValue
// IDA: Ped::SetMoneyValue
// Ghidra: ---
void gta2::Ped_SetMoneyValue(struct Ped *self)
{
  self->PositionX1 &= 0xFBFFFFFF;
}


// 0x00493040: Ped::FUN_00493040
// IDA: sub_493040
// Ghidra: Ped::FUN_00493040
byte gta2::Ped_FUN_00493040(struct Ped *self,GameObject *pGameObject)
{
  int iVar1;
  
  if (pGameObject != self->GameObject1) {
    self->GameObject1 = pGameObject;
    self->uns63 = self->uns63 & 0xfb;
    iVar1 = pGameObject->ScriptRef;
    *(GameObject **)(iVar1 + 0x138) = self->GameObject_;
    gta2::Ped_sub_433DD0(self,0x16);
    return (byte)iVar1;
  }
  return (byte)pGameObject;
}


// 0x004a5010: Ped::sub_4A5010
// IDA: Ped::sub_4A5010
// Ghidra: Ped::FUN_004a5010
void gta2::Ped_sub_4A5010(struct Ped *self)
{
  uint uVar1;
  
  uVar1._0_1_ = self->CurrentAction;
  uVar1._1_1_ = self->DamageState;
  uVar1._2_1_ = self->uns60;
  uVar1._3_1_ = self->uns61;
  uVar1 = uVar1 | 0x800;
  self->CurrentAction = (char)uVar1;
  self->DamageState = (char)(uVar1 >> 8);
  self->uns60 = (char)(uVar1 >> 0x10);
  self->uns61 = (char)(uVar1 >> 0x18);
  return;
}


// 0x004a5020: Ped::sub_4A5020
// IDA: Ped::sub_4A5020
// Ghidra: ---
int gta2::Ped_sub_4A5020(struct Ped *self)
{
  return (int)self->GameObject2;
}


// 0x004a5040: Ped::IsTargetCarDoor
// IDA: Ped::IsTargetCarDoor
// Ghidra: ---
bool gta2::Ped_IsTargetCarDoor(struct Ped *self)
{
  return self->PositionZ1 != 1;
}


// 0x004a5050: Ped::SetHealthFull
// IDA: Ped::SetHealthFull
// Ghidra: ---
__int16 gta2::Ped_SetHealthFull(struct Ped *self)
{
  __int16 result; // ax

  gta2::Ped_SetHealth(self, 100);
  return result;
}


// 0x004a5060: Ped::sub_4A5060
// IDA: Ped::sub_4A5060
// Ghidra: ---
void gta2::Ped_sub_4A5060(struct Ped *self)
{
  self->PositionX1 |= 0x4000000u;
}


// 0x004c4f20: Ped::GetID
// IDA: Ped::GetID
// Ghidra: FUN_004c4f20
undefined4 gta2::Ped_GetID(int param_1)
{
  return *(undefined4 *)(param_1 + 0x200);
}


// 0x004cca90: Ped::FUN_004cca90
// IDA: sub_4CCA90
// Ghidra: Ped::FUN_004cca90
void gta2::Ped_FUN_004cca90(struct Ped *self,undefined2 *param_1)
{
  *param_1 = self->field4_0x12e;
  return;
}



