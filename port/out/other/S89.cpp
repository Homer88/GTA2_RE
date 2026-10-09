#include "gta2_shim.h"

// Module: other, Class: S89
// Functions: 8
// Source: unified (IDA+Ghidra)

// 0x004c2710: S89::sub_4C2710
// IDA: S89::sub_4C2710
// Ghidra: ---
void gta2::S89_sub_4C2710(struct S89 *self, __int16 a2, __int16 a3, int a4, int a5)
{
  unsigned int i; // eax

  if ( !self->S89_2_ )
  {
    if ( a2 )
    {
      self->Count = a3 * a2;
      self->field_6 = a3;
      self->field_10 = 1;
      self->sprite_type = a4;
      self->field_C = a5;
      self->S89_2_ = (S89_2 *)gta2::createBuffer(4 * (unsigned __int16)(a3 * a2));
      for ( i = 0; i < self->Count; self->S89_2_->field_0[i++] = 0 )
        ;
    }
  }
}


// 0x004c2780: S89::sub_4C2780
// IDA: S89::sub_4C2780
// Ghidra: ---
char gta2::S89_sub_4C2780(struct S89 *self)
{
  int v2; // eax
  unsigned int i; // esi
  int Sprite; // edi
  unsigned __int16 global_palette_id; // ax

  LOBYTE(v2) = self->field_10;
  if ( (_BYTE)v2 )
  {
    for ( i = 0; i < self->Count; self->S89_2_->field_0[i++] = v2 )
    {
      Sprite = gta2::Style_GetSprite(gStyle, i);
      global_palette_id = gta2::Style_get_global_palette_id(gStyle, 2, i);
      gta2::Style_get_physical_palette(gStyle, global_palette_id);
      v2 = gta2::gbh_RegisterTexture(*(unsigned __int8 *)(Sprite + 4), *(unsigned __int8 *)(Sprite + 5), *(_DWORD *)Sprite);
    }
  }
  return v2;
}


// 0x004c27f0: S89::sub_4C27F0
// IDA: S89::sub_4C27F0
// Ghidra: ---
char gta2::S89_sub_4C27F0(struct S89 *self)
{
  int v2; // eax
  unsigned int v3; // ebp
  unsigned __int16 GlobalSpriteId; // ax
  unsigned int v5; // edi
  int Sprite; // ebx
  unsigned __int16 global_palette_id; // ax
  unsigned int v9; // [esp+0h] [ebp-18h]

  LOBYTE(v2) = self->field_10;
  if ( (_BYTE)v2 )
  {
    v2 = self->Count / (int)(unsigned __int16)self->field_6;
    v3 = 0;
    if ( v2 )
    {
      do
      {
        GlobalSpriteId = gta2::Style_GetGlobalSpriteId(gStyle, self->sprite_type, v3);
        v5 = 0;
        Sprite = gta2::Style_GetSprite(gStyle, GlobalSpriteId);
        ++unk_671974;
        if ( self->field_6 )
        {
          do
          {
            global_palette_id = gta2::Style_get_global_palette_id(gStyle, self->field_C, v5);
            gta2::Style_get_physical_palette(gStyle, global_palette_id);
            v9 = 1;
            self->S89_2_->field_0[v5 + v3 * (unsigned __int16)self->field_6] = gta2::gbh_RegisterTexture(
                                                                                *(unsigned __int8 *)(Sprite + 4),
                                                                                *(unsigned __int8 *)(Sprite + 5),
                                                                                *(_DWORD *)Sprite);
            ++v5;
            ++unk_671970;
          }
          while ( v5 < (unsigned __int16)self->field_6 );
        }
        LOBYTE(v2) = v9;
        ++v3;
      }
      while ( v3 < v9 );
    }
  }
  return v2;
}


// 0x004c28d0: S89::sub_4C28D0
// IDA: S89::sub_4C28D0
// Ghidra: ---
void gta2::S89_sub_4C28D0(struct S89 *self)
{
  unsigned __int16 i; // di

  if ( self->field_10 && self->S89_2_ )
  {
    for ( i = 0; i < self->Count; ++i )
      gta2::gbh_FreeTexture((GLuint *)self->S89_2_->field_0[i]);
    gta2::free_0(self->S89_2_);
    self->S89_2_ = 0;
  }
}


// 0x004c2920: S89::sub_4C2920
// IDA: S89::sub_4C2920
// Ghidra: ---
int gta2::S89_sub_4C2920(struct S89 *self, int sprite_type, __int16 spriteId)
{
  return self->S89_2_->field_0[gta2::Style_GetGlobalSpriteId(gStyle, sprite_type, spriteId)];
}


// 0x004c2950: S89::sub_4C2950
// IDA: S89::sub_4C2950
// Ghidra: ---
int gta2::S89_sub_4C2950(struct S89 *self, __int16 spriteId, __int16 a3)
{
  return self->S89_2_->field_0[(unsigned __int16)(a3 + spriteId * self->field_6)];
}


// 0x004c2f10: S89::S89
// IDA: S89::S89
// Ghidra: ---
S89 * gta2::S89_S89(struct S89 *self)
{
  S89 *result; // eax

  result = self;
  self->S89_2_ = 0;
  self->Count = 0;
  self->field_6 = 0;
  self->sprite_type = 0;
  self->field_C = 0;
  self->field_10 = 0;
  return result;
}


// 0x004c2f30: S89::sub_4C2F30
// IDA: S89::sub_4C2F30
// Ghidra: ---
void gta2::S89_sub_4C2F30(struct S89 *self, int a4, int a2)
{
  __int16 v4; // ax
  __int16 v5; // [esp-Ch] [ebp-14h]

  v5 = gta2::Style_sub_4BF3A0(gStyle, a2);
  v4 = gta2::Style_sub_4BF330(gStyle, a4);
  gta2::S89_sub_4C2710(self, v4, v5, a4, a2);
}



