#include "gta2_shim.h"

// Module: other, Class: S125
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x004b8d90: S125::S125_Dec
// IDA: S125::S125_Dec
// Ghidra: ---
void gta2::S125_S125_Dec(_DWORD *self)
{
  self[17] = 0;
}


// 0x004b9270: S125::S125
// IDA: S125::S125
// Ghidra: ---
void gta2::S125_S125(struct S125 *self)
{
  *(_DWORD *)&self->field = 0;
  memset(self->field_4, 0, sizeof(self->field_4));
  self->field_36 = 0;
  self->field_38 = 0;
  self->field_3C = 0;
  *(_DWORD *)&self->field_40 = 0;
  self->field_4C = 0;
  self->field_48 = 0;
  self->field_44 = 0;
  self->field_34 = 9;
}



