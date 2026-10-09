#include "gta2_shim.h"

// Module: other, Class: SpriteS4
// Functions: 5
// Source: unified (IDA+Ghidra)

// 0x004bdcd0: SpriteS4::sub_4BDCD0
// IDA: SpriteS4::sub_4BDCD0
// Ghidra: ---
int gta2::SpriteS4_sub_4BDCD0(SpriteS4 *self)
{
  self->dat = 0;
  return gta2::Construct_0(self->S46_Arr300, 0x18, 300, S46::S46_Des);
}


// 0x004bdcf0: SpriteS4::SpriteS4
// IDA: SpriteS4::SpriteS4
// Ghidra: ---
SpriteS4 * gta2::SpriteS4_SpriteS4(SpriteS4 *self)
{
  VehiclePool *S46_Arr300; // esi
  VehiclePool *pS46; // eax
  int v4; // ecx

  S46_Arr300 = self->S46_Arr300;
  gta2::Construct(self->S46_Arr300, 24, 300, S46::S46, S46::S46_Des);
  pS46 = (VehiclePool *)&S46_Arr300->NextElement;
  v4 = 299;
  do
  {
    pS46->DATA = (VehiclePool *)&pS46->DATA1;
    ++pS46;
    --v4;
  }
  while ( v4 );
  self->S46_Arr300[299].NextElement = 0;
  self->dat = (int)S46_Arr300;
  return self;
}


// 0x004be710: SpriteS4::SpriteS4_Des
// IDA: SpriteS4::SpriteS4_Des
// Ghidra: ---
SpriteS4 * gta2::SpriteS4_SpriteS4_Des(SpriteS4 *self, char a2)
{
  gta2::SpriteS4_sub_4BDCD0(self);
  if ( (a2 & 1) != 0 )
    free(self);
  return self;
}


// 0x004bec40: SpriteS4::sub_4BEC40
// IDA: SpriteS4::sub_4BEC40
// Ghidra: ---
void gta2::SpriteS4_sub_4BEC40(SpriteS4 *self)
{
  self->dat = *(_DWORD *)(self->dat + 4);
}


// 0x004bec50: SpriteS4::sub_4BEC50
// IDA: SpriteS4::sub_4BEC50
// Ghidra: ---
void gta2::SpriteS4_sub_4BEC50(SpriteS4 *self, Arsenal *a2)
{
  *(_DWORD *)&a2->Count = self->dat;
  self->dat = (int)a2;
}



