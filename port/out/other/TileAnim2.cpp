#include "gta2_shim.h"

// Module: other, Class: TileAnim2
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x004c3240: TileAnim2::sub_4C3240
// IDA: TileAnim2::sub_4C3240
// Ghidra: ---
void gta2::TileAnim2_sub_4C3240(struct TileAnim2 *self)
{
  *(struct TileAnim *)&self->TileAnim = *gTileAnim;
  ++*(_WORD *)gTileAnim;
}


// 0x004c3260: TileAnim2::sub_4C3260
// IDA: TileAnim2::sub_4C3260
// Ghidra: ---
void gta2::TileAnim2_sub_4C3260(struct TileAnim2 *self)
{
  int v1; // eax

  v1 = self->field_C;
  if ( v1 )
    gta2::Style_ChangeTileByIdx(gStyle, self->field_10, *(_WORD *)(v1 + 2 * (unsigned __int16)self->field_8 + 6));
  else
    gta2::Style_ChangeTileByIdx(gStyle, self->field_10, self->field_8);
}


// 0x004c3300: TileAnim2::sub_4C3300
// IDA: TileAnim2::sub_4C3300
// Ghidra: ---
char gta2::TileAnim2_sub_4C3300(struct TileAnim2 *self)
{
  unsigned __int16 v2; // ax
  __int16 field; // cx
  bool v4; // al
  __int16 v5; // ax
  __int16 v6; // ax

  if ( !--self->field_A )
  {
    v2 = self->field_2;
    field = self->field;
    if ( v2 >= (unsigned int)self->field )
      v4 = (unsigned int)++self->field_8 > v2;
    else
      v4 = (unsigned int)--self->field_8 < v2;
    if ( v4 )
    {
      v5 = self->field_6;
      if ( v5 )
      {
        v6 = v5 - 1;
        self->field_6 = v6;
        if ( !v6 )
          return 1;
      }
      self->field_8 = field;
    }
    gta2::TileAnim2_sub_4C3260(self);
    self->field_A = self->field_4;
  }
  return 0;
}



