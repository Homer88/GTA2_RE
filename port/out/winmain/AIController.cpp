#include "gta2_shim.h"

// Module: winmain, Class: AIController
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x00403cb0: AIController::FUN_00403cb0
// IDA: ---
// Ghidra: AIController::FUN_00403cb0
byte gta2::AIController_FUN_00403cb0(AIController *self)
{
  byte bVar1;
  byte bVar2;
  uint local_4;
  
  bVar2 = 0;
  local_4 = 0;
  bVar1 = self->IndexPed;
  if (bVar1 != 0) {
    do {
      gta2::Ped_sub_403960(self->Ped_[local_4]);
      gta2::Ped_SetAnimationState(self->Ped_[local_4],9,9999);
      gta2::Ped_SetPed2(self->Ped_[local_4],self->PedDefault);
      bVar1 = self->IndexPed;
      bVar2 = bVar2 + 1;
      local_4 = (uint)bVar2;
    } while (bVar2 < bVar1);
  }
  return bVar1;
}



