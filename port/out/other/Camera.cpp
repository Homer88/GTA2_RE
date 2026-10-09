#include "gta2_shim.h"

// Module: other, Class: Camera
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x00476760: Camera::S33_FUN_00476760
// IDA: ---
// Ghidra: Camera::S33_FUN_00476760
{
  Viewport *this_00;
  byte extraout_CL;
  
  this_00 = self->Viewport;
  self->Viewport = this_00->NextElement;
  gta2::Viewport_S34_FUN_00474f90(this_00);
  return extraout_CL;
}



