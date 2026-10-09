#include "gta2_shim.h"

// Module: other, Class: S123
// Functions: 6
// Source: unified (IDA+Ghidra)

// 0x004b8d60: S123::sub_4B8D60
// IDA: S123::sub_4B8D60
// Ghidra: ---
__int16 gta2::S123_sub_4B8D60(struct S123 *self)
{
  if ( ++self->Arr_element > 0xDu )
    self->Arr_element = 9;
  return self->Arr_element;
}


// 0x004b8d80: S123::sub_4B8D80
// IDA: S123::sub_4B8D80
// Ghidra: ---
void gta2::S123_sub_4B8D80(struct S123 *self)
{
  ++self->count;
}


// 0x004b91f0: S123::sub_4B91F0
// IDA: S123::sub_4B91F0
// Ghidra: ---
void gta2::S123_sub_4B91F0(struct S123 *self, int a2, int a3, int a4, unsigned int a5)
{
  bool v6; // zf
  struct Game *Game; // eax
  struct Game *v8; // eax

  v6 = self->count == 0;
  if ( !self->count )
  {
    Game = gta2::S124_GetGame(&self->S124_);
    if ( Game )
    {
      while ( Game[1].ArrayPlayer[2] >= (Player *)a5 )
      {
        Game = (Game *)Game[1].ArrayPlayer[0];
        if ( !Game )
          goto LABEL_7;
      }
      gta2::sub_4B9000(&self->S124_.S125_1, (int)Game);
      ++self->count;
    }
LABEL_7:
    v6 = self->count == 0;
  }
  if ( !v6 )
  {
    v8 = gta2::S124_sub_4B8FE0(&self->S124_);
    if ( v8 )
    {
      --self->count;
      gta2::sub_4B8DE0(v8, a2, a3, a4, a5);
    }
  }
}


// 0x004b9260: S123::sub_4B9260
// IDA: S123::sub_4B9260
// Ghidra: ---
void gta2::S123_sub_4B9260(struct S123 *self)
{
  S124 *p_S124; // ebx
  struct Game *Game; // esi
  struct Game *v3; // edi
  struct Game *v4; // ebp
  struct Game *v5; // eax
  Player *S125_1; // eax

  p_S124 = &self->S124_;
  Game = self->S124_.Game;
  v3 = 0;
  LOWORD(self->field_FC) = 0;
  if ( Game )
  {
    do
    {
      ++LOWORD(p_S124[1].S125_1);
      v4 = (Game *)Game[1].ArrayPlayer[0];
      if ( gta2::sub_4B8F70(Game) )
      {
        if ( !v3 )
          goto LABEL_6;
        if ( (Game *)v3[1].ArrayPlayer[0] != Game )
        {
          v3 = 0;
LABEL_6:
          v5 = p_S124->Game_;
          if ( v5 == Game )
          {
            S125_1 = (Player *)p_S124->S125_1;
            p_S124->Game_ = (Game *)Game[1].ArrayPlayer[0];
            Game[1].ArrayPlayer[0] = S125_1;
            p_S124->S125_1 = (S125 *)Game;
          }
          else
          {
            v3 = p_S124->Game_;
            if ( (Game *)v5[1].ArrayPlayer[0] != Game )
            {
              do
                v3 = (Game *)v3[1].ArrayPlayer[0];
              while ( (Game *)v3[1].ArrayPlayer[0] != Game );
            }
            v3[1].ArrayPlayer[0] = Game[1].ArrayPlayer[0];
            Game[1].ArrayPlayer[0] = (Player *)p_S124->S125_1;
            p_S124->S125_1 = (S125 *)Game;
          }
          goto LABEL_13;
        }
        v3[1].ArrayPlayer[0] = Game[1].ArrayPlayer[0];
        Game[1].ArrayPlayer[0] = (Player *)p_S124->S125_1;
        p_S124->S125_1 = (S125 *)Game;
      }
      else
      {
        v3 = Game;
      }
LABEL_13:
      Game = v4;
    }
    while ( v4 );
  }
}


// 0x004b9490: S123::S123
// IDA: S123::S123
// Ghidra: ---
S123 * gta2::S123_S123(struct S123 *self)
{
  gta2::S124_S124(&self->S124_);
  self->Arr_element = 9;
  self->count = 3;
  return self;
}


// 0x004b98b0: S123::sub_4B98B0
// IDA: S123::sub_4B98B0
// Ghidra: ---
char gta2::S123_sub_4B98B0(struct S123 *self)
{
  struct Game *Game; // eax
  struct Game *i; // esi

  Game = gta2::S124_GetGame(&self->S124_);
  for ( i = Game; i; i = (Game *)i[1].ArrayPlayer[0] )
    LOBYTE(Game) = gta2::Game_sub_4B94B0(i);
  return (char)Game;
}



