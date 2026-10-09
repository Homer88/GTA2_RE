#include "gta2_shim.h"

// Module: other, Class: S110
// Functions: 4
// Source: unified (IDA+Ghidra)

// 0x004c5480: S110::sub_4C5480
// IDA: S110::sub_4C5480
// Ghidra: ---
int gta2::S110_sub_4C5480(struct S110 *self)
{
  int result; // eax

  result = 0;
  self->field_1A = 150;
  self->field_1E = 0;
  self->field_20 = 0;
  self->field_24 = 0;
  self->Car = 0;
  self->Ped_ = 0;
  self->field_28 = 0;
  self->NPC = 0;
  self->field_2C = 0;
  self->field_1C = 0;
  return result;
}


// 0x004c54c0: S110::sub_4C54C0
// IDA: S110::sub_4C54C0
// Ghidra: FUN_004c54c0
void gta2::S110_sub_4C54C0(void *self,void *param_1)
{
  gta2::S169_sub_404D40(*(SpawnPoint **)((int)self + 8),param_1);
  *(undefined4 *)((int)self + 4) =
       *(undefined4 *)(*(int *)((int)self + 8) + 0x2c);
  return;
}


// 0x004c54f0: S110::sub_4C54F0
// IDA: S110::sub_4C54F0
// Ghidra: FUN_004c54f0
undefined1 gta2::S110_sub_4C54F0(void *self)
{
  bool bVar1;
  
  if (*(Ped **)((int)self + 4) != NULL) {
    bVar1 = gta2::Ped_GetDeadPed(*(Ped **)((int)self + 4));
    if (bVar1) {
      return 0;
    }
  }
  return 1;
}


// 0x004c5510: S110::sub_4C5510
// IDA: S110::sub_4C5510
// Ghidra: FUN_004c5510
undefined4 gta2::S110_sub_4C5510(void *self)
{
  byte index;
  int iVar1;
  Ped *pPed;
  Ped *pPed1;
  SpawnPoint *pS169;
  
  pS169 = *(SpawnPoint **)((int)self + 8);
  if (pS169 != NULL) {
    index = 0;
    pPed1 = pS169->Ped_Array[0];
    while (pPed1 != NULL) {
      iVar1 = gta2::Ped_GetPedState(pPed1);
      if ((iVar1 != 9) && (pPed1->CurrentCar == NULL)) {
        if (*(int *)((int)*(void **)((int)self + 4) + 0x16c) == 0) {
          gta2::S169_sub_404120(pS169,index);
          pPed = *(Ped **)(*(int *)((int)self + 8) + 0x2c);
          *(Ped **)((int)self + 4) = pPed;
          gta2::Ped_PedSetObjective(pPed,0,9999);
          iVar1 = gta2::Ped_GetCurrentOccupation(pPed1);
          gta2::Ped_SetCurrentOccupation(pPed1,3);
          gta2::Ped_sub_4411B0(pPed1);
          gta2::Ped_SetCurrentOccupation(pPed1,iVar1);
          gta2::Ped_PedSetObjective(pPed1,0x1c,9999);
          return 1;
        }
        FUN_004c54c0(self,*(void **)((int)self + 4));
        return 1;
      }
      index = index + 1;
      pPed1 = pS169->Ped_Array[index];
    }
  }
  return 0;
}



