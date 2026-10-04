#include "gta2_shim.h"

// Module: other, Class: S86_4
// Functions: 6
// Source: unified (IDA+Ghidra)

// 0x004c5e00: S86_4::sub_4C5E00
// IDA: S86_4::sub_4C5E00
// Ghidra: FUN_004c5e00
void gta2::S86_4_sub_4C5E00(void *self,char param_2)
{
  char cVar1;
  int iVar2;
  
  if (param_2 == '\0') {
    *(undefined4 *)((int)self + 4) = 0;
  }
  cVar1 = *(char *)((int)self + 1) + -1;
  *(char *)((int)self + 1) = cVar1;
  if (cVar1 == '\0') {
    *(undefined1 *)((int)self + 1) = *(undefined1 *)((int)self + 2);
                              // WARNING: Load size is inaccurate
    *(bool *)self = *self == '\0';
    if (param_2 != '\0') {
      iVar2 = *(int *)((int)self + 4) + *(int *)((int)self + 8);
      *(int *)((int)self + 4) = iVar2;
      if (iVar2 == -4) {
        *(undefined4 *)((int)self + 8) = 1;
        return;
      }
      if (iVar2 == 4) {
        *(undefined4 *)((int)self + 8) = 0xffffffff;
      }
    }
  }
  return;
}


// 0x004c6ea0: S86_4::sub_4C6EA0
// IDA: S86_4::sub_4C6EA0
// Ghidra: ---
void gta2::S86_4_sub_4C6EA0(struct S86_4 *self, char a2)
{
  self->S83_3[0].field_2 = a2;
  self->S83_3[0].field_1 = a2;
}


// 0x004c6ee0: S86_4::S86_4
// IDA: S86_4::S86_4
// Ghidra: ---
void gta2::S86_4_S86_4(struct S86_4 *self)
{
  gta2::constructor(self, 12, 6, S86_3::S86_3);
  self->CopStars = 0;
}


// 0x004c79d0: S86_4::sub_4C79D0
// IDA: S86_4::sub_4C79D0
// Ghidra: ---
void gta2::S86_4_sub_4C79D0(struct S86_4 *self)
{
  struct Ped *Ped; // edi
  int v3; // edi
  struct S86_4 *i; // ecx
  int v5; // ecx
  char a2; // [esp+8h] [ebp-4h]

  Ped = gta2::Player_GetPed(gGame->PlayerMain);
  self->CopStars = gta2::Ped_GetCopStars(Ped);
  a2 = gta2::Police_sub_4A9590(gPolice, Ped);
  v3 = 0;
  for ( i = self; v3 < self->CopStars; i = (struct S86_4 *)(v5 + 12) )
  {
    gta2::S86_4_sub_4C5E00(i, a2);
    ++v3;
  }
}


// 0x004c7a30: S86_4::sub_4C7A30
// IDA: S86_4::sub_4C7A30
// Ghidra: ---
void gta2::S86_4_sub_4C7A30(struct S86_4 *self)
{
  struct Player *v2; // eax
  struct SpriteS1 *v3; // eax
  int v4; // ebx
  struct S86_4 *v5; // esi
  int v6; // ecx
  struct PublicTransport *v7; // eax
  int *v8; // eax
  int v9; // edx
  int CopStars; // [esp-10h] [ebp-34h]
  struct SpriteS1 *v11; // [esp-Ch] [ebp-30h]
  int a1; // [esp+10h] [ebp-14h] BYREF
  int mode; // [esp+14h] [ebp-10h] BYREF
  int WindowHeight; // [esp+18h] [ebp-Ch] BYREF
  char v15; // [esp+1Ch] [ebp-8h] BYREF
  int v16; // [esp+20h] [ebp-4h] BYREF

  CopStars = self->CopStars;
  mode = 2;
  v11 = sub_4C60D0((struct SpriteS1 *)&WindowHeight, CopStars, &self->field_4C);
  gta2::sub_40CE00(&v16, 640);
  v3 = gta2::Player_sub_401B40(v2, (struct S202 *)&v15, (int)v11);
  gta2::S122_sub_401BF0((struct S122 *)v3, (int)&a1, (int)&mode);
  mode = 2;
  gta2::S122_sub_401BF0((struct S122 *)&self->field_50, (int)&WindowHeight, (int)&mode);
  v4 = 0;
  v5 = self;
  while ( v4 < self->CopStars )
  {
    v6 = v5->S83_3[0].field_4;
    mode = 2;
    gta2::S202_sub_41F980((struct S202 *)&v16, v6);
    v8 = (int *)gta2::S202_sub_401B20((struct S202 *)&WindowHeight, (struct SpriteS1 *)&v15, v7);
    LOWORD(v9) = (unsigned __int8)v5->S83_3[0].field_0;
    gta2::Hud_DrawSprite((struct Hud *)a1, 6, v9 + 14, a1, *v8, unk_672F98.Index, &mode, 0, 0);
    ++v4;
    v5 = (struct S86_4 *)((char *)v5 + 12);
    gta2::Player_sub_40E530((struct Player *)&a1, (struct Tango *)&self->field_4C);
  }
}


// 0x004c7b10: S86_4::sub_4C7B10
// IDA: S86_4::sub_4C7B10
// Ghidra: ---
char gta2::S86_4_sub_4C7B10(struct S86_4 *self)
{
  unsigned __int16 GlobalSpriteId; // ax
  int Sprite; // edi
  int *v4; // eax
  int *v5; // eax
  int v6; // edi
  char result; // al
  int v8; // [esp+8h] [ebp-4h] BYREF

  GlobalSpriteId = gta2::Style_GetGlobalSpriteId(gStyle, 6, 14);
  Sprite = gta2::Style_GetSprite(gStyle, GlobalSpriteId);
  gta2::S202_sub_40CE30((struct S202 *)&v8, *(_BYTE *)(Sprite + 4));
  self->field_4C = *v4;
  gta2::S202_sub_40CE30((struct S202 *)&v8, *(_BYTE *)(Sprite + 5));
  v6 = 6;
  self->field_50 = *v5;
  do
  {
    gta2::S86_4_sub_4C6EA0(self, 2);
    self = (struct S86_4 *)((char *)self + 12);
    --v6;
  }
  while ( v6 );
  return result;
}



