#include "gta2_shim.h"

// Module: other, Class: TileAnim1
// Functions: 4
// Source: unified (IDA+Ghidra)

// 0x004c3380: TileAnim1::sub_4C3380
// IDA: TileAnim1::sub_4C3380
// Ghidra: ---
void * gta2::TileAnim1_sub_4C3380(struct TileAnim1 *self)
{
  struct TileAnim2 *TileAnim2; // ecx
  void *v3; // ecx

  TileAnim2 = self->TileAnim2_;
  self->TileAnim2_ = TileAnim2->NextTileAnim2;
  TileAnim2->NextTileAnim2 = self->NextS71;
  self->NextS71 = TileAnim2;
  gta2::TileAnim2_sub_4C3240(TileAnim2);
  return v3;
}


// 0x004c3490: TileAnim1::TileAnim1_Des
// IDA: TileAnim1::TileAnim1_Des
// Ghidra: ---
int gta2::TileAnim1_TileAnim1_Des(struct TileAnim1 *self)
{
  self->TileAnim2_ = 0;
  self->NextS71 = 0;
  return gta2::Construct_0(self->TileAnim2_Arr50, 24, 50, S71::S71_Dec);
}


// 0x004c34b0: TileAnim1::TileAnim1
// IDA: TileAnim1::TileAnim1
// Ghidra: ---
TileAnim1 * gta2::TileAnim1_TileAnim1(struct TileAnim1 *self)
{
  struct TileAnim2 *TileAnim2_Arr50; // edi
  struct TileAnim2 **p_NextTileAnim2; // eax
  int count; // ecx

  TileAnim2_Arr50 = self->TileAnim2_Arr50;
  gta2::Construct(self->TileAnim2_Arr50, 0x18, 50, S71::S71, S71::S71_Dec);
  p_NextTileAnim2 = &TileAnim2_Arr50->NextTileAnim2;
  count = 49;
  do
  {
    *p_NextTileAnim2 = (TileAnim2 *)(p_NextTileAnim2 + 1);
    p_NextTileAnim2 += 6;
    --count;
  }
  while ( count );
  self->TileAnim2_ = TileAnim2_Arr50;
  self->TileAnim2_Arr50[49].NextTileAnim2 = 0;
  self->NextS71 = 0;
  self->field_4B8 = 0;
  return self;
}


// 0x004c3630: TileAnim1::TileAnim1Des
// IDA: TileAnim1::TileAnim1Des
// Ghidra: ---
TileAnim1 * gta2::TileAnim1_TileAnim1Des(struct TileAnim1 *self, char BitStatus)
{
  gta2::TileAnim1_TileAnim1_Des(self);
  if ( (BitStatus & 1) != 0 )
    free(self);
  return self;
}



