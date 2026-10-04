#include "gta2_shim.h"

// Module: other, Class: MapGm
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x00476b10: MapGm::sub_476B10
// IDA: MapGm::sub_476B10
// Ghidra: ---
int gta2::MapGm_sub_476B10(struct MapGm *self, int a2)
{
  int result; // eax

  result = a2;
  self->SpecialTokens = a2;
  return result;
}


// 0x005237e0: MapGm::MapGm
// IDA: MapGm::MapGm
// Ghidra: FUN_005237e0
void gta2::sub_45E860(void)
{
  gta2::sub_45E860(&gMapGm);
  return;
}



