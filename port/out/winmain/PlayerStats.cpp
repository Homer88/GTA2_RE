#include "gta2_shim.h"

// Module: winmain, Class: PlayerStats
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004035e0: PlayerStats::sub_4035E0
// IDA: PlayerStats::sub_4035E0
// Ghidra: FUN_004035e0
void gta2::PlayerStats_sub_4035E0(int param_1)
{
  byte bVar1;
  undefined4 local_4;
  
  gta2::Ped_PedSetObjective(*(Ped **)(param_1 + 0x2c),0,9999);
  gta2::Ped_SetAnimationState(*(Ped **)(param_1 + 0x2c),0,9999);
  bVar1 = 0;
  local_4 = 0;
  if (*(char *)(param_1 + 0x34) != '\0') {
    do {
      gta2::Ped_PedSetObjective(*(Ped **)(param_1 + 4 + local_4 * 4),0,9999);
      gta2::Ped_SetAnimationState(*(Ped **)(param_1 + 4 + local_4 * 4),0,9999);
      bVar1 = bVar1 + 1;
      local_4 = (uint)bVar1;
    } while (bVar1 < *(byte *)(param_1 + 0x34));
  }
  return;
}



