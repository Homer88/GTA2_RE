#include "gta2_shim.h"

// Module: other, Class: S86_8
// Functions: 7
// Source: unified (IDA+Ghidra)

// 0x004a4770: S86_8::sub_4A4770
// IDA: S86_8::sub_4A4770
// Ghidra: ---
void gta2::S86_8_sub_4A4770(struct S86_8 *self)
{
  self->field_88 = 0;
  self->field_8C = 0;
}


// 0x004c6ad0: S86_8::sub_4C6AD0
// IDA: S86_8::sub_4C6AD0
// Ghidra: ---
void gta2::S86_8_sub_4C6AD0(struct S86_8 *self)
{
  void *v2; // eax

  if ( self->field_0 )
  {
    LOWORD(v2) = gta2::Font_GetStringWidth(self->str, unk_672F30);
    self->field_84 = v2;
  }
}


// 0x004c6af0: S86_8::sub_4C6AF0
// IDA: S86_8::sub_4C6AF0
// Ghidra: ---
void gta2::S86_8_sub_4C6AF0(struct S86_8 *self, _BYTE *a2, _BYTE *a3)
{
  wchar_t *v4; // eax
  wchar_t *v5; // [esp-8h] [ebp-Ch]
  void *retaddr; // [esp+4h] [ebp+0h]

  self->field_88 = (int)retaddr;
  self->field_8C = (int)a2;
  if ( a2 )
    v4 = gta2::sub_462BE0(a2);
  else
    v4 = gta2::sub_462BE0(retaddr);
  v5 = gta2::Text_ConvertWordsToBig(gText, v4);
  CopyWideString(self->str, v5);
  self->field_0 = 90;
  gta2::S86_8_sub_4C6AD0(self);
  self->field_90 = 1;
  self->field_94 = 0;
}


// 0x004c6b70: S86_8::sub_4C6B70
// IDA: S86_8::sub_4C6B70
// Ghidra: ---
void gta2::S86_8_sub_4C6B70(struct S86_8 *self)
{
  char *v2; // edi
  char *v3; // eax
  unsigned __int8 v4; // al
  unsigned __int8 v5; // al
  unsigned __int8 v6; // al
  int v7; // [esp+Ch] [ebp-8h]
  int Y; // [esp+10h] [ebp-4h] BYREF

  gta2::Player_sub_4A6530(gGame->PlayerMain, &Y);
  v2 = gta2::MapRelatedStruct_sub_464FE0(gMapRelatedStruct, Y, v7, 1);
  v3 = gta2::MapRelatedStruct_sub_464FE0(gMapRelatedStruct, Y, v7, 15);
  if ( v2 || v3 )
  {
    if ( v3 == (char *)self->field_8C && (v3 || v2 == (char *)self->field_88) )
    {
      if ( self->field_0 )
      {
        v4 = self->field_0 - 1;
        self->field_0 = v4;
        if ( v4 <= 57u )
        {
          if ( v4 < 31u )
          {
            v6 = self->field_94;
            self->field_90 = 1;
            if ( v6 )
              self->field_94 = v6 - 1;
          }
        }
        else
        {
          v5 = self->field_94 + 1;
          self->field_94 = v5;
          if ( v5 > 0x1Fu )
          {
            self->field_90 = 0;
            self->field_94 = 31;
          }
        }
      }
    }
    else
    {
      gta2::S86_8_sub_4C6AF0(self, v2, v3);
    }
  }
  else
  {
    self->field_0 = 0;
    self->field_88 = 0;
  }
}


// 0x004c6c60: S86_8::sub_4C6C60
// IDA: S86_8::sub_4C6C60
// Ghidra: ---
void gta2::S86_8_sub_4C6C60(struct S86_8 *self)
{
  self->field_90 = 0;
  self->field_94 = 0;
}


// 0x004c6c70: S86_8::S86_8
// IDA: S86_8::S86_8
// Ghidra: ---
void gta2::S86_8_S86_8(struct S86_8 *self)
{
  self->field_0 = 0;
  self->field_88 = 0;
  self->field_8C = 0;
}


// 0x004c9890: S86_8::sub_4C9890
// IDA: S86_8::sub_4C9890
// Ghidra: ---
void gta2::S86_8_sub_4C9890(void *self)
{
  int v2; // ebx
  Player *v3; // ecx
  CarSystemManager *v4; // eax
  int v5; // ecx
  Hud *v6; // ecx
  CarSystemManager *v7; // eax
  Player *v8; // ecx
  int v9; // ecx
  Hud *v10; // ecx
  CarSystemManager *v11; // ecx
  Player *v12; // edx
  int v13; // ecx
  Hud *v14; // ecx
  CarSystemManager *v15; // eax
  Player *v16; // ecx
  int v17; // ecx
  Hud *v18; // ecx
  int v19; // eax
  Player *v20; // ecx
  int CharHeight; // eax
  S202 *v22; // ecx
  S202 v23; // [esp-1Ch] [ebp-30h] BYREF
  int mode; // [esp+10h] [ebp-4h] BYREF

  if ( *(_BYTE *)self )
  {
    v2 = gta2::sub_4C7220(159);
    v3 = (Player *)*((_DWORD *)self + 36);
    v4 = (CarSystemManager *)(v2 - (v2 >> 31));
    LOBYTE(v4) = *((_BYTE *)self + 148);
    v23.field_18 = v4;
    LOWORD(v4) = unk_672F98.Index;
    v23.pPlayer = v3;
    v23.field_10 = 0;
    v23.field_C = (int)&mode;
    v23.CarSystemManager = v4;
    v23.S202 = (S202 *)v3;
    mode = 2;
    gta2::S202_sub_41F980((S202 *)&v23.S202, 27);
    v23.field_0 = v5;
    gta2::S202_sub_41F980(&v23, 320 - v2 / 2 - v2);
    v7 = (CarSystemManager *)gta2::Hud_DrawSprite(
                               v6,
                               6,
                               159,
                               v23.field_0,
                               (int)v23.S202,
                               (char)v23.CarSystemManager,
                               (const int *)v23.field_C,
                               (int)v23.field_10,
                               (int)v23.pPlayer);
    LOBYTE(v7) = *((_BYTE *)self + 148);
    v8 = (Player *)*((_DWORD *)self + 36);
    v23.field_18 = v7;
    LOWORD(v7) = unk_672F98.Index;
    v23.pPlayer = v8;
    v23.field_10 = 0;
    v23.field_C = (int)&mode;
    v23.CarSystemManager = v7;
    v23.S202 = (S202 *)v8;
    mode = 2;
    gta2::S202_sub_41F980((S202 *)&v23.S202, 27);
    v23.field_0 = v9;
    gta2::S202_sub_41F980(&v23, 320 - v2 / 2);
    gta2::Hud_DrawSprite(
      v10,
      6,
      160,
      v23.field_0,
      (int)v23.S202,
      (char)v23.CarSystemManager,
      (const int *)v23.field_C,
      (int)v23.field_10,
      (int)v23.pPlayer);
    LOBYTE(v11) = *((_BYTE *)self + 148);
    v12 = (Player *)*((_DWORD *)self + 36);
    v23.field_18 = v11;
    LOWORD(v11) = unk_672F98.Index;
    v23.pPlayer = v12;
    v23.field_10 = 0;
    v23.field_C = (int)&mode;
    v23.CarSystemManager = v11;
    v23.S202 = (S202 *)v11;
    mode = 2;
    gta2::S202_sub_41F980((S202 *)&v23.S202, 27);
    v23.field_0 = v13;
    gta2::S202_sub_41F980(&v23, v2 / 2 + 320);
    v15 = (CarSystemManager *)gta2::Hud_DrawSprite(
                                v14,
                                6,
                                161,
                                v23.field_0,
                                (int)v23.S202,
                                (char)v23.CarSystemManager,
                                (const int *)v23.field_C,
                                (int)v23.field_10,
                                (int)v23.pPlayer);
    LOBYTE(v15) = *((_BYTE *)self + 148);
    v16 = (Player *)*((_DWORD *)self + 36);
    v23.field_18 = v15;
    mode = 2;
    v23.pPlayer = v16;
    LOWORD(v15) = unk_672F98.Index;
    v23.field_10 = 0;
    v23.field_C = (int)&mode;
    v23.CarSystemManager = v15;
    v23.S202 = (S202 *)v16;
    gta2::S202_sub_41F980((S202 *)&v23.S202, 27);
    v23.field_0 = v17;
    gta2::S202_sub_41F980(&v23, v2 / 2 + v2 + 320);
    v19 = gta2::Hud_DrawSprite(
            v18,
            6,
            162,
            v23.field_0,
            (int)v23.S202,
            (char)v23.CarSystemManager,
            (const int *)v23.field_C,
            (int)v23.field_10,
            (int)v23.pPlayer);
    LOBYTE(v19) = *((_BYTE *)self + 148);
    v20 = (Player *)*((_DWORD *)self + 36);
    v23.field_18 = v19;
    v23.pPlayer = v20;
    v23.field_10 = 0;
    LOWORD(v20) = unk_672F30;
    v23.field_C = (int)&mode;
    v23.CarSystemManager = (CarSystemManager *)v20;
    mode = 2;
    CharHeight = gta2::Font_GetCharHeight(unk_672F30);
    v23.S202 = v22;
    gta2::S202_sub_41F980((S202 *)&v23.S202, 27 - CharHeight / 2);
    v23.field_0 = *((_DWORD *)self + 33);
    gta2::S202_sub_41F980(&v23, (640 - v23.field_0) / 2);
    sub_4C7280((unsigned __int16 *)self + 1, v23.field_0, (SpriteS1 *)v23.S202);
  }
}



