#include "gta2_shim.h"

// Module: other, Class: S33
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x00476780: S33::S33_sub_476780
// IDA: S33::S33_sub_476780
// Ghidra: ---
Viewport * gta2::S33_S33_sub_476780(struct Camera *self, Viewport *pS34)
{
  struct Viewport *result; // eax

  result = pS34;
  pS34->NextElement = self->FirstElement;
  self->FirstElement = pS34;
  return result;
}



