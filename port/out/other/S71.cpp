#include "gta2_shim.h"

// Module: other, Class: S71
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x004c33a0: S71::S71
// IDA: S71::S71
// Ghidra: ---
TileAnim2 * gta2::S71_S71(struct TileAnim2 *self)
{
  TileAnim2 *result; // eax

  result = self;
  self->field = 0;
  self->field_2 = 0;
  self->field_4 = 0;
  self->field_6 = 0;
  self->field_8 = 0;
  self->field_A = 0;
  self->field_C = 0;
  self->field_10 = 0;
  *(_WORD *)&self->TileAnim = 0;
  self->NextTileAnim2 = 0;
  return result;
}


// 0x004c33d0: S71::S71_Dec
// IDA: S71::S71_Dec
// Ghidra: ---
int gta2::S71_S71_Dec(struct TileAnim2 *self)
{
  int result; // eax

  result = 0;
  self->field_C = 0;
  self->NextTileAnim2 = 0;
  return result;
}



