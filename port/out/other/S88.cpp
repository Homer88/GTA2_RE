#include "gta2_shim.h"

// Module: other, Class: S88
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004c2f70: S88::S88
// IDA: S88::S88
// Ghidra: ---
S88 * gta2::S88_S88(struct S88 *self)
{
  struct S88 *result; // eax

  result = self;
  self->field_0 = 0;
  self->GLuint_ = 0;
  self->field_8 = 0;
  self->field_A = 0;
  return result;
}



