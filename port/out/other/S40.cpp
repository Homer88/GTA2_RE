#include "gta2_shim.h"

// Module: other, Class: S40
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x004bc900: S40::S40
// IDA: S40::S40
// Ghidra: ---
void gta2::S40_S40(struct GangInfo *self)
{
  gta2::Construct(self->S41_, 8, 4, S41::S41, S41::S41_Dec);
  gta2::SpriteS3__FUN_004bc8f0((struct SpriteS3 *)self);
}


// 0x004bc930: S40::S40_Des
// IDA: S40::S40_Des
// Ghidra: ---
int gta2::S40_S40_Des(struct GangInfo *self)
{
  return gta2::Construct_0(self->S41_, 8, 4, S41::S41_Dec);
}



