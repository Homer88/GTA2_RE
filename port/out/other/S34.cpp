#include "gta2_shim.h"

// Module: other, Class: S34
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x00474f90: S34::S34_sub_474F90
// IDA: S34::S34_sub_474F90
// Ghidra: ---
int gta2::S34_S34_sub_474F90(struct Viewport *self)
{
  int result; // eax

  result = 0;
  self->Data1 = 0;
  self->Data2 = 0;
  self->NextElement = 0;
  return result;
}


// 0x00476e00: S34::sub_476E00
// IDA: S34::sub_476E00
// Ghidra: FUN_00476e00
Viewport * gta2::S34_sub_476E00(void *self,Viewport *pS34)
{
  struct Viewport *pVVar1;
  
  pVVar1 = gta2::S33_S33_sub_476780(gCamera,pS34);
  return pVVar1;
}



