#include "gta2_shim.h"

// Module: other, Class: S83
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x004af220: S83::S83
// IDA: S83::S83
// Ghidra: ---
Bus * gta2::S83_S83(struct Bus *self)
{
  struct Bus *result; // eax
  void *v2; // esi
  void *v3; // edx
  int count; // edi

  result = self;
  self->Status = 0;
  self->Car = 0;
  self->field_44 = 0;
  self->field_4C = 0;
  self->field_4 = 0;
  self->Car1 = 0;
  self->field_2 = 0;
  self->field_48 = 0;
  self->field_50 = 2;
  self->field_54 = 0;
  self->field_55 = 0;
  self->SkipCount = 0;
  self->field_0 = 0;
  v2 = &self->field_38;
  v3 = &self->field_10;
  count = 10;
  do
  {
    *(_DWORD *)v3 = 0;
    *(_BYTE *)v2 = -1;
    v3 = (char *)v3 + 4;
    v2 = (char *)v2 + 1;
    --count;
  }
  while ( count );
  self->field_42 = -1;
  self->field_43 = 0;
  self->field_1 = 0;
  return result;
}


// 0x004af280: S83::S83_des
// IDA: S83::S83_des
// Ghidra: ---
int gta2::S83_S83_des(_DWORD *self)
{
  int result; // eax

  result = 0;
  self[3] = 0;
  self[19] = 0;
  return result;
}



