#include "gta2_shim.h"

// Module: other, Class: S46
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004bca70: S46::S46
// IDA: S46::S46
// Ghidra: ---
void gta2::S46_S46(struct VehiclePool *self)
{
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&self->CarSystemManager_);
}



