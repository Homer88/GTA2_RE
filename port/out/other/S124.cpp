#include "gta2_shim.h"

// Module: other, Class: S124
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x004b8fd0: S124::GetGame
// IDA: S124::GetGame
// Ghidra: ---
Game * gta2::S124_GetGame(struct S124 *self)
{
  return self->Game_;
}


// 0x004b8fe0: S124::sub_4B8FE0
// IDA: S124::sub_4B8FE0
// Ghidra: ---
Game * gta2::S124_sub_4B8FE0(struct S124 *self)
{
  Game *result; // eax

  result = (Game *)self->S125_1;
  self->S125_1 = (S125 *)self->S125_1->field_44;
  result[1].ArrayPlayer[0] = (Player *)self->Game_;
  self->Game_ = result;
  return result;
}


// 0x004b9440: S124::S124
// IDA: S124::S124
// Ghidra: ---
S124 * gta2::S124_S124(struct S124 *self)
{
  struct S125 *S125; // edi

  S125 = self->S125_;
  gta2::Construct(self->S125_, 0x50, 3, S125::S125, S125::S125_Dec);
  S125->field_44 = (int)&S125[1];
  S125[1].field_44 = (int)&S125[2];
  self->S125_[2].field_44 = 0;
  self->S125_1 = S125;
  self->Game_ = 0;
  LOWORD(self[1].S125_1) = 0;
  return self;
}



