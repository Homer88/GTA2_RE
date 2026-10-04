#include "gta2_shim.h"

// Module: other, Class: SpriteS3
// Functions: 6
// Source: unified (IDA+Ghidra)

// 0x00482980: SpriteS3::sub_482980
// IDA: SpriteS3::sub_482980
// Ghidra: ---
EventHandler * gta2::SpriteS3_sub_482980(struct SpriteS3 *self, SpriteS1 *a2, SpriteS3 *a3, EventHandler *a4)
{
  struct EventHandler *result; // eax

  self->S39_Arr48[0].field_0 = (int)a2;
  result = a4;
  self->S39_Arr48[0].SpriteS3 = a3;
  self->S39_Arr48[0].field_8 = (struct AudioSourceParams *)a4;
  return result;
}


// 0x004b9f00: SpriteS3::SpriteS3_des
// IDA: SpriteS3::SpriteS3_des
// Ghidra: ---
SpriteS3 * gta2::SpriteS3_SpriteS3_des(struct SpriteS3 *self, char a2)
{
  gta2::SpriteS3_sub_44AE70(self);
  if ( (a2 & 1) != 0 )
    free(self);
  return self;
}


// 0x004ba020: SpriteS3::sub_4BA020
// IDA: SpriteS3::sub_4BA020
// Ghidra: ---
void gta2::SpriteS3_sub_4BA020(struct SpriteS3 *self)
{
  self->S39_Arr48[2].SpriteS3 = 0;
}


// 0x004bc580: SpriteS3::sub_4BC580
// IDA: SpriteS3::sub_4BC580
// Ghidra: SpriteS1::FUN_004bc580
void gta2::SpriteS3_sub_4BC580(struct SpriteS1 *self)
{
  gta2::AudioSourceParams_sub_4BA5E0((Point2D *)&self->Matrix3DArray[0].field14_0x2c);
  return;
}


// 0x004bc8f0: SpriteS3::sub_4BC8F0
// IDA: SpriteS3::sub_4BC8F0
// Ghidra: ---
void gta2::SpriteS3_sub_4BC8F0(struct SpriteS3 *self)
{
  gta2::SpriteS3_sub_4BA020(self);
  LOBYTE(self->S39_Arr48[3].field_C) = 0;
}


// 0x004c2ef0: SpriteS3::sub_4C2EF0
// IDA: SpriteS3::sub_4C2EF0
// Ghidra: ---
int gta2::SpriteS3_sub_4C2EF0(struct SpriteS3 *self, unsigned __int16 *index)
{
  return self->S39_Arr48[*index].field_0;
}



