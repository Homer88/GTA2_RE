#include "gta2_shim.h"

// Module: other, Class: S100
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x0048a880: S100::S100
// IDA: S100::S100
// Ghidra: ---
S100 * gta2::S100_S100(struct S100 *self)
{
  char v2; // al
  char *v3; // edx
  char *v4; // ecx
  struct S100 *result; // eax

  gta2::Construct(self, 48, 20, S101::S101, S101::S101_des);
  v2 = 0;
  v3 = &self->field_3C0;
  v4 = &self->S101_[0].field_4;
  do
  {
    *v4 = v2;
    *v3 = 0;
    ++v2;
    v4 += 48;
    ++v3;
  }
  while ( (unsigned __int8)v2 < 0x14u );
  result = self;
  unk_669E80 = 0;
  return result;
}



