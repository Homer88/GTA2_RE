#include "gta2_shim.h"

// Module: other, Class: SpriteS2
// Functions: 5
// Source: unified (IDA+Ghidra)

// 0x004bc950: SpriteS2::sub_4BC950
// IDA: SpriteS2::sub_4BC950
// Ghidra: ---
int gta2::SpriteS2_sub_4BC950(SpriteS2 *self)
{
  self->FirstElement = 0;
  return gta2::Construct_0(self->S40_ARR5031, 76, 5031, S40::S40_Des);
}


// 0x004bc9a0: SpriteS2::SpriteS2
// IDA: SpriteS2::SpriteS2
// Ghidra: ---
SpriteS2 * gta2::SpriteS2_SpriteS2(SpriteS2 *self)
{
  GangInfo *pS40; // esi
  GangInfo *pS40_; // eax
  int Count; // ecx

  pS40 = self->S40_ARR5031;
  gta2::Construct(self->S40_ARR5031, 76, 5031, S40::S40, S40::S40_Des);
  pS40_ = (GangInfo *)&pS40->NextElement;
  Count = 5030;
  do
  {
    pS40_->NextElement1 = (GangInfo *)&pS40_->S41_[2].S63;
    ++pS40_;
    --Count;
  }
  while ( Count );
  self->S40_ARR5031[5030].NextElement = 0;
  self->FirstElement = (SpriteS3 *)pS40;
  return self;
}


// 0x004bc9f0: SpriteS2::sub_4BC9F0
// IDA: SpriteS2::sub_4BC9F0
// Ghidra: ---
SpriteS3 * gta2::SpriteS2_sub_4BC9F0(SpriteS2 *self)
{
  SpriteS3 *FirstElement; // esi

  FirstElement = self->FirstElement;
  self->FirstElement = self->FirstElement->S39_Arr48[2].SpriteS3;
  gta2::SpriteS3__FUN_004bc8f0(FirstElement);
  return FirstElement;
}


// 0x004bca10: SpriteS2::sub_4BCA10
// IDA: SpriteS2::sub_4BCA10
// Ghidra: ---
SpriteS3 * gta2::SpriteS2_sub_4BCA10(SpriteS2 *self, SpriteS3 *a2)
{
  SpriteS3 *result; // eax

  result = a2;
  a2->S39_Arr48[2].SpriteS3 = self->FirstElement;
  self->FirstElement = a2;
  return result;
}


// 0x004bdcb0: SpriteS2::SpriteS2_des
// IDA: SpriteS2::SpriteS2_des
// Ghidra: ---
SpriteS2 * gta2::SpriteS2_SpriteS2_des(SpriteS2 *self, char a2)
{
  gta2::SpriteS2_sub_4BC950(self);
  if ( (a2 & 1) != 0 )
    free(self);
  return self;
}



