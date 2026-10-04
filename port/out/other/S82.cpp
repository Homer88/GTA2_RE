#include "gta2_shim.h"

// Module: other, Class: S82
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x004af1c0: S82::S82
// IDA: S82::S82
// Ghidra: ---
void gta2::S82_S82(struct BaseCar *self)
{
  self->field = 0;
  self->field_4 = 0;
  self->field_8 = 0;
  self->field_C = 0;
  self->count = 0;
  self->Status = 0;
  self->field_18 = 0;
  self->field_1C = 0;
  self->S82 = 0;
  self->field_2E = 0;
  self->field_2F = 0;
  self->SkipTrains = 16843009;
  self->field_28 = 16843009;
  self->field_2C = 257;
}


// 0x004af200: S82::S82_Des
// IDA: S82::S82_Des
// Ghidra: ---
int gta2::S82_S82_Des(_DWORD *self)
{
  int result; // eax

  result = 0;
  self[6] = 0;
  self[1] = 0;
  self[2] = 0;
  self[3] = 0;
  self[4] = 0;
  self[8] = 0;
  return result;
}



