#include "gta2_shim.h"

// Module: other, Class: Hud
// Functions: 18
// Source: unified (IDA+Ghidra)

// 0x004c6940: Hud::sub_4C6940
// IDA: Hud::sub_4C6940
// Ghidra: ---
void gta2::Hud_sub_4C6940(struct Hud *self)
{
  int v2; // eax

  if ( self->field_0 )
  {
    LOWORD(v2) = gta2::Font_GetStringWidth(self->field_2, unk_672F28);
    self->field_44 = v2;
  }
}


// 0x004c6960: Hud::sub_4C6960
// IDA: Hud::sub_4C6960
// Ghidra: ---
void gta2::Hud_sub_4C6960(struct Hud *self, char *pInfoByTypeCar)
{
  wchar_t *v3; // edi
  const wchar_t *retaddr; // [esp+8h] [ebp+0h]

  v3 = self->field_2;
  self->field_0 = 120;
  CopyWideString(self->field_2, retaddr);
  gta2::Text_ConvertWordsToBig(gText, v3);
  gta2::Hud_sub_4C6940(self);
  self->field_48 = -17;
}


// 0x004c69a0: Hud::sub_4C69A0
// IDA: Hud::sub_4C69A0
// Ghidra: ---
unsigned __int8 gta2::Hud_sub_4C69A0(struct Hud *self)
{
  unsigned __int8 result; // al

  result = self->field_0;
  if ( self->field_0 )
  {
    self->field_0 = --result;
    if ( result <= 0x50u )
    {
      if ( result < 0x28u )
        --self->field_48;
    }
    else
    {
      ++self->field_48;
    }
  }
  return result;
}


// 0x004c69c0: Hud::Hud1
// IDA: Hud::Hud1
// Ghidra: ---
void gta2::Hud_Hud1(struct Hud *self)
{
  self->field_0 = 0;
}


// 0x004c6d90: Hud::Init_s_Wrapper
// IDA: Hud::Init_s_Wrapper
// Ghidra: ---
Gang * gta2::Hud_Init_s_Wrapper(struct Hud *self)
{
  struct S86_10 *pS86_10; // esi
  struct Gang *pGang; // eax
  char v3; // dl
  char v4; // dl

  pS86_10 = &self->S86_10_;
  LOBYTE(pGang) = gta2::MapGm_GetGang(&gMapGm);
  if ( !(_BYTE)pGang )
  {
    LOBYTE(pGang) = pS86_10->field_1 - 1;
    pS86_10->field_1 = (char)pGang;
    if ( !(_BYTE)pGang )
    {
      v3 = pS86_10->field_0;
      pS86_10->field_1 = 45;
      v4 = v3 + 1;
      LOBYTE(pGang) = v4;
      pS86_10->field_0 = v4;
      if ( (unsigned __int8)v4 > 6u )
      {
        pS86_10->field_0 = 0;
        return pGang;
      }
      switch ( v4 )
      {
        case 1:
          pGang = gta2::Gangs_GetFirstUsedGang(gGangs);
          goto LABEL_14;
        case 2:
          pGang = gta2::Gangs_GetFirstUsedGang(gGangs);
          break;
        case 3:
          pGang = gta2::Gangs_GetFirstUsedGang(gGangs);
          if ( !pGang )
            goto LABEL_15;
          pGang = gta2::Gangs_GetNextUsedGang(gGangs);
          break;
        default:
          return pGang;
      }
      if ( pGang )
      {
        pGang = gta2::Gangs_GetNextUsedGang(gGangs);
LABEL_14:
        if ( pGang )
          return pGang;
      }
LABEL_15:
      pS86_10->field_0 = 4;
    }
  }
  return pGang;
}


// 0x004c6da0: Hud::sub_4C6DA0
// IDA: Hud::sub_4C6DA0
// Ghidra: ---
char gta2::Hud_sub_4C6DA0(struct Hud *self)
{
  char result; // al

  result = gLighting;
  if ( gLighting )
    return gbh_SetAmbient((void *)0x3F800000);
  return result;
}


// 0x004c6dc0: Hud::SetSpeedText
// IDA: Hud::SetSpeedText
// Ghidra: ---
void gta2::Hud_SetSpeedText(struct Hud *self)
{
  self->TextSpeed = gta2::Registry_sub_4B5500(&Registry, "text_speed", 3u);
}


// 0x004c6de0: Hud::sub_4C6DE0
// IDA: Hud::sub_4C6DE0
// Ghidra: ---
bool gta2::Hud_sub_4C6DE0(struct Hud *self, KeyCode Button)
{
  int v2; // edx
  bool result; // al

  if ( gta2::sub_4C5F30(&self->S86_10_.field_2, Button) )
    return 1;
  result = gta2::sub_4C5F70((void *)(v2 + 10783), Button);
  if ( result )
    return 1;
  return result;
}


// 0x004c6e20: Hud::HandleKeyboard_Wrapper
// IDA: Hud::HandleKeyboard_Wrapper
// Ghidra: ---
bool gta2::Hud_HandleKeyboard_Wrapper(struct Hud *self, KeyCode a2)
{
  return gta2::sub_4C5F30(&self->S86_10_.field_2, a2);
}


// 0x004c71b0: Hud::DrawSprite
// IDA: Hud::DrawSprite
// Ghidra: ---
int gta2::Hud_DrawSprite(
        struct Hud *self,
        int id1,
        int id2,
        int X,
        int Y,
        char style,
        const int *mode,
        int enableAlpha,
        int alpha)
{
  struct PublicTransport *v9; // esi
  struct SpriteS1 *v10; // edi
  int *v11; // eax
  char v13; // [esp+8h] [ebp-4h] BYREF

  v9 = (struct PublicTransport *)&gCameraOrPhysics->cameraPosTarget_[4].field_4;
  v10 = gta2::Radar_AddBlip(
          (struct Tango *)&Y,
          (struct SpriteS1 *)&v13,
          (struct PublicTransport *)&gCameraOrPhysics->cameraPosTarget_[4].field_4);
  v11 = (int *)gta2::Radar_AddBlip((struct Tango *)&X, (struct SpriteS1 *)&Y, v9);
  return gta2::sub_4CBA50((void *)id2, id1, id2, *v11, v10->FirstElement);
}


// 0x004c8ca0: Hud::DrawSprite
// IDA: Hud::DrawSprite
// Ghidra: GarageInfo::FUN_004c8ca0
void gta2::Hud_DrawSprite(GarageInfo *self,SpriteS1 *param_1,int param_2)
{
  int iVar1;
  struct SpriteS1 *pSVar2;
  struct Hud *this_00;
  undefined2 extraout_var;
  struct SpriteS1 *pSVar3;
  struct SpriteS1 *extraout_ECX;
  struct Hud *this_01;
  undefined2 extraout_var_00;
  struct SpriteS1 *extraout_ECX_00;
  struct Hud *this_02;
  undefined2 extraout_var_01;
  struct SpriteS1 *extraout_ECX_01;
  struct Hud *this_03;
  int iVar4;
  int iVar5;
  int iVar6;
  int local_8;
  
  iVar1 = *(int *)self->CarGenerator[0].field1_0x4;
  iVar4 = iVar1 % 10;
  iVar6 = (iVar1 % 100 - iVar4) / 10;
  iVar5 = ((iVar1 % 1000 - iVar6) - iVar4) / 100;
  iVar1 = ((iVar1 - iVar5) - iVar6) - iVar4;
  local_8 = iVar1 / 1000;
  pSVar2 = (struct SpriteS1 *)-(iVar1 >> 0x1f);
  if (((local_8 == 0) && (local_8 = -1, iVar5 == 0)) && (iVar5 = -1, iVar6 == 0)
     ) {
    iVar6 = -1;
  }
  iVar1 = param_2 + 2;
  gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffd0,iVar1);
  pSVar3 = param_1;
  gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffcc,
             (int)((int)&param_1->Matrix3DArray[0].Car + 3));
  gta2::Hud_DrawSprite(this_00,6,(void *)(iVar4 + 0x7b),pSVar3,pSVar2);
  pSVar3 = (struct SpriteS1 *)CONCAT22(extraout_var,_DAT_00672f98);
  gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffd0,iVar1);
  pSVar2 = extraout_ECX;
  gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffcc,(int)param_1->Matrix3DArray);
  gta2::Hud_DrawSprite(this_01,6,(void *)(iVar6 + 0x7b),pSVar2,pSVar3);
  pSVar3 = (struct SpriteS1 *)CONCAT22(extraout_var_00,_DAT_00672f98);
  gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffd0,iVar1);
  pSVar2 = extraout_ECX_00;
  gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffcc,
             (int)&param_1[-1].Matrix3DArray[0x13a6].field21_0x39);
  gta2::Hud_DrawSprite(this_02,6,(void *)(iVar5 + 0x7b),pSVar2,pSVar3);
  pSVar3 = (struct SpriteS1 *)CONCAT22(extraout_var_01,_DAT_00672f98);
  gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffd0,iVar1);
  pSVar2 = extraout_ECX_01;
  gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffcc,
             (int)((int)&param_1[-1].Matrix3DArray[0x13a6].SpriteS1_1 + 2));
  gta2::Hud_DrawSprite(this_03,6,(void *)(local_8 + 0x7b),pSVar2,pSVar3);
  return;
}


// 0x004c94f0: Hud::DrawSprite_Wrapper
// IDA: Hud::DrawSprite_Wrapper
// Ghidra: ---
void gta2::Hud_DrawSprite_Wrapper(struct Hud *self)
{
  __int64 v2; // rax
  int v3; // ecx
  int v4; // edi
  int v5; // ecx
  struct Hud *v6; // ecx
  struct CarSystemManager *v7; // ecx
  int v8; // edx
  int v9; // ecx
  struct Hud *v10; // ecx
  struct CarSystemManager *v11; // ecx
  int v12; // edx
  int v13; // ecx
  struct Hud *v14; // ecx
  int v15; // ecx
  int v16; // kr08_4
  int v17; // eax
  int v18; // ecx
  struct Hud *v19; // ecx
  struct CarSystemManager *v20; // ecx
  int v21; // edx
  int v22; // ecx
  struct Hud *v23; // ecx
  int CharHeight; // eax
  int v25; // edx
  struct Player *v26; // ecx
  int v27; // eax
  struct Weapon *v28; // ecx
  S202 v29; // [esp-1Ch] [ebp-2Ch] BYREF
  int Y; // [esp+Ch] [ebp-4h] BYREF

  if ( self->field_0 )
  {
    LODWORD(v2) = gta2::sub_4C7220(11);
    v3 = self->field_44;
    v4 = v2;
    memset(&v29.field_10, 0, 12);
    Y = 2;
    v29.field_C = (int)&Y;
    if ( v3 <= 2 * (int)v2 - 10 )
    {
      v2 = (int)v2;
      WORD2(v2) = unk_672F98.Index;
      v29.CarSystemManager = (struct CarSystemManager *)HIDWORD(v2);
      v16 = v2;
      v17 = self->field_48;
      v29.S202 = (struct S202 *)&Y;
      gta2::S202_sub_41F980((struct S202 *)&v29.S202, v17);
      v29.field_0 = v18;
      gta2::S202_sub_41F980(&v29, 320 - v16 / 2);
      gta2::Hud_DrawSprite(
        v19,
        6,
        11,
        v29.field_0,
        (int)v29.S202,
        (char)v29.CarSystemManager,
        (const int *)v29.field_C,
        (int)v29.field_10,
        (int)v29.pPlayer);
      LOWORD(v20) = unk_672F98.Index;
      v21 = self->field_48;
      memset(&v29.field_10, 0, 12);
      v29.field_C = (int)&Y;
      v29.CarSystemManager = v20;
      v29.S202 = (struct S202 *)v20;
      Y = 2;
      gta2::S202_sub_41F980((struct S202 *)&v29.S202, v21);
      v29.field_0 = v22;
      gta2::S202_sub_41F980(&v29, v16 / 2 + 320);
      gta2::Hud_DrawSprite(
        v23,
        6,
        13,
        v29.field_0,
        (int)v29.S202,
        (char)v29.CarSystemManager,
        (const int *)v29.field_C,
        (int)v29.field_10,
        (int)v29.pPlayer);
    }
    else
    {
      WORD2(v2) = unk_672F98.Index;
      LODWORD(v2) = self->field_48;
      v29.CarSystemManager = (struct CarSystemManager *)HIDWORD(v2);
      v29.S202 = (struct S202 *)&Y;
      gta2::S202_sub_41F980((struct S202 *)&v29.S202, v2);
      v29.field_0 = v5;
      gta2::S202_sub_41F980(&v29, v4 + 320);
      gta2::Hud_DrawSprite(
        v6,
        6,
        13,
        v29.field_0,
        (int)v29.S202,
        (char)v29.CarSystemManager,
        (const int *)v29.field_C,
        (int)v29.field_10,
        (int)v29.pPlayer);
      LOWORD(v7) = unk_672F98.Index;
      v8 = self->field_48;
      memset(&v29.field_10, 0, 12);
      v29.field_C = (int)&Y;
      v29.CarSystemManager = v7;
      v29.S202 = (struct S202 *)v7;
      Y = 2;
      gta2::S202_sub_41F980((struct S202 *)&v29.S202, v8);
      v29.field_0 = v9;
      gta2::bitShiftLeft1(&v29, 320);
      gta2::Hud_DrawSprite(
        v10,
        6,
        12,
        v29.field_0,
        (int)v29.S202,
        (char)v29.CarSystemManager,
        (const int *)v29.field_C,
        (int)v29.field_10,
        (int)v29.pPlayer);
      LOWORD(v11) = unk_672F98.Index;
      v12 = self->field_48;
      memset(&v29.field_10, 0, 12);
      v29.field_C = (int)&Y;
      v29.CarSystemManager = v11;
      v29.S202 = (struct S202 *)v11;
      Y = 2;
      gta2::S202_sub_41F980((struct S202 *)&v29.S202, v12);
      v29.field_0 = v13;
      gta2::S202_sub_41F980(&v29, 320 - v4);
      gta2::Hud_DrawSprite(
        v14,
        6,
        11,
        v29.field_0,
        (int)v29.S202,
        (char)v29.CarSystemManager,
        (const int *)v29.field_C,
        (int)v29.field_10,
        (int)v29.pPlayer);
    }
    LOWORD(v15) = unk_672F28;
    v29.field_18 = v15;
    CharHeight = gta2::Font_GetCharHeight(unk_672F28);
    v25 = self->field_48;
    v29.pPlayer = v26;
    gta2::S202_sub_41F980((struct S202 *)&v29.pPlayer, v25 - CharHeight / 2);
    v27 = 640 - self->field_44;
    v29.field_10 = v28;
    gta2::S202_sub_41F980((struct S202 *)&v29.field_10, v27 / 2);
    gta2::sub_4BA2C0(self->field_2, (int)v29.field_10, (struct SpriteS1 *)v29.pPlayer);
  }
}


// 0x004ca440: Hud::DrawUI
// IDA: Hud::DrawUI
// Ghidra: ---
void gta2::Hud_DrawUI(struct Hud *self)
{
  wchar_t *v1; // edi
  int v2; // eax
  int v3; // ebp
  int NumberLines; // ebx
  __int64 v5; // rax
  int v6; // esi
  int v7; // ecx
  wchar_t *v8; // edi
  struct CarSystemManager *v9; // eax
  struct CarSystemManager *v10; // ebp
  struct S202 *v11; // ecx
  int v12; // ecx
  wchar_t *v13; // edi
  struct CarSystemManager *v14; // eax
  struct CarSystemManager *v15; // ebp
  struct S202 *v16; // ecx
  int v17; // ecx
  char *v19; // ecx
  int v20; // esi
  S202 v21; // [esp-2Ch] [ebp-30h] BYREF
  int v22; // [esp-Ch] [ebp-10h]
  int v23; // [esp+0h] [ebp-4h] BYREF

  if ( !skip_user )
  {
    gta2::Hud_sub_4C6DA0(self);
    sub_4C9C20(&self->S86_5_.field_C);
    gta2::S86_5_sub_4C74A0(&self->S86_5_);
    gta2::sub_4C78A0(&self->field_2AF0);
    gta2::S86_4_sub_4C7A30(&self->struc_S86_4);
    gta2::sub_4C74F0(&self->struc_S86_4.field_54);
    gta2::sub_4C7B70();
    gta2::S86_8_sub_4C9890(&self->S86_8_);
    gta2::Hud_DrawSprite_Wrapper(self);
    gta2::sub_4C9690((struct CarSystemManager *)&self->field_27B8);
    gta2::HudBrief_sub_4C9430(&self->HudBrief_);
    gta2::S166_sub_4C92A0(&self->S166_);
    gta2::S86_7_sub_4C8C80(&self->S86_7_);
    gta2::HudArrow_sub_4C84C0(&self->HudArrow_);
    gta2::sub_4C96F0(self->S86_9);
    gta2::HudMessage_sub_4C8A40(&self->HudMessage_);
    gta2::S86_10_sub_4C9FA0(&self->S86_10_);
    gta2::DrawChat(&self->S86_10_.field_3);
    v19 = &self->S86_10_.field_2;
    v20 = v23;
    v23 = (int)v19;
    v22 = v20;
    if ( gGame->PlayerMain->quit1 )
    {
      v1 = gta2::Text__Bsearch(gText, "quit1");
      LOWORD(v2) = gta2::Font_GetStringWidth(v1, Len);
      v3 = v2;
      NumberLines = gta2::Font_GetNumberLines(v1, Len);
      memset(&v21.field_10, 0, 12);
      v5 = 3 * (160 - NumberLines);
      LODWORD(v5) = v5 - HIDWORD(v5);
      WORD2(v5) = Len;
      v21.field_C = (int)&v23;
      v6 = (int)v5 >> 1;
      v21.CarSystemManager = (struct CarSystemManager *)HIDWORD(v5);
      v21.S202 = (struct S202 *)&v23;
      v23 = 2;
      gta2::S202_sub_41F980((struct S202 *)&v21.S202, ((int)v5 >> 1) - NumberLines);
      v21.field_0 = v7;
      gta2::S202_sub_41F980(&v21, (640 - v3) / 2);
      sub_4C7280(v1, v21.field_0, (struct SpriteS1 *)v21.S202);
      v8 = gta2::Text__Bsearch(gText, "quit2");
      LOWORD(v9) = gta2::Font_GetStringWidth(v8, Len);
      v10 = v9;
      LOWORD(v9) = Len;
      memset(&v21.field_10, 0, 12);
      v21.field_C = (int)&v23;
      v21.CarSystemManager = v9;
      v21.S202 = v11;
      v23 = 2;
      gta2::S202_sub_41F980((struct S202 *)&v21.S202, v6);
      v21.field_0 = v12;
      gta2::S202_sub_41F980(&v21, (640 - (int)v10) / 2);
      sub_4C7280(v8, v21.field_0, (struct SpriteS1 *)v21.S202);
      v13 = gta2::Text__Bsearch(gText, "quit3");
      LOWORD(v14) = gta2::Font_GetStringWidth(v13, Len);
      v15 = v14;
      LOWORD(v14) = Len;
      memset(&v21.field_10, 0, 12);
      v21.field_C = (int)&v23;
      v21.CarSystemManager = v14;
      v21.S202 = v16;
      v23 = 2;
      gta2::S202_sub_41F980((struct S202 *)&v21.S202, NumberLines + v6);
      v21.field_0 = v17;
      gta2::S202_sub_41F980(&v21, (640 - (int)v15) / 2);
      sub_4C7280(v13, v21.field_0, (struct SpriteS1 *)v21.S202);
    }
  }
}


// 0x004ca520: Hud::DrawUIWrapper
// IDA: Hud::DrawUIWrapper
// Ghidra: ---
__int16 gta2::Hud_DrawUIWrapper(struct Hud *self)
{
  __int16 result; // ax
  __int16 v2; // dx

  if ( gta2::Text_LanguageJapan(gText) )
  {
    result = word_67065C[0];
    v2 = word_670650;
    unk_672F28 = word_67065C[0];
    unk_672F30 = word_67065C[0];
    LOWORD(unk_672F1C) = unk_670668;
    LOWORD(unk_672F2C) = word_670650;
  }
  else
  {
    result = unk_670668;
    unk_672F28 = unk_670640;
    unk_672F30 = unk_670674;
    v2 = unk_670654;
    LOWORD(unk_672F1C) = unk_670668;
    LOWORD(unk_672F2C) = unk_670678;
  }
  unk_672F38 = unk_670668;
  LOWORD(unk_672F34) = result;
  LOWORD(unk_672F3C) = result;
  unk_672F18 = result;
  Len = result;
  unk_672F20 = v2;
  unk_672F14 = result;
  return result;
}


// 0x004ca5d0: Hud::Update2_Wrapper
// IDA: Hud::Update2_Wrapper
// Ghidra: ---
char gta2::Hud_Update2_Wrapper(struct Hud *self, int pKey, Player *a2)
{
  char result; // al

  if ( gta2::sub_4C8690(&self->S86_10_.field_2, pKey, a2) )
    return 1;
  result = gta2::sub_4C8880(&self->S86_10_.field_3, pKey, a2);
  if ( result )
    return 1;
  return result;
}


// 0x004cab50: Hud::sub_4CAB50
// IDA: Hud::sub_4CAB50
// Ghidra: ---
char gta2::Hud_sub_4CAB50(struct Hud *self)
{
  char result; // al

  gta2::sub_4C6CA0(&self->S86_5_.field_C);
  ((void (__thiscall *)(struct S86_5 *))S86_5::MainLogic)(&self->S86_5_);
  gta2::sub_4CA680(&self->s);
  gta2::S86_4_sub_4C79D0(&self->struc_S86_4);
  gta2::Hud_sub_4C69A0(self);
  gta2::sub_4C6A40(&self->field_27B8);
  gta2::S86_8_sub_4C6B70(&self->S86_8_);
  gta2::HudBrief_sub_4C6770(&self->HudBrief_);
  gta2::S166_sub_4C62B0(&self->S166_);
  gta2::S86_7_sub_4C6170(&self->S86_7_);
  gta2::HudArrow_sub_4CA890(&self->HudArrow_);
  gta2::HudMessage_DicrementTimeToShow(&self->HudMessage_);
  result = self->S86_9[0];
  if ( result )
    self->S86_9[0] = --result;
  return result;
}


// 0x004cabe0: Hud::SetSpeedText_Wrapper
// IDA: Hud::SetSpeedText_Wrapper
// Ghidra: ---
void gta2::Hud_SetSpeedText_Wrapper(struct Hud *self)
{
  wchar_t *v2; // [esp+0h] [ebp-4h]

  gta2::Hud_DrawUIWrapper(self);
  gta2::HudBrief_MainLogic(&self->HudBrief_, v2);
  gta2::Hud_sub_4C6940(self);
  gta2::S86_8_sub_4C6AD0(&self->S86_8_);
  gta2::HudMessage_ShowBigOnScreenLabel_0(&self->HudMessage_);
  gta2::S86_9_sub_4C6A60((S86_9 *)self->S86_9);
  gta2::sub_4C69D0(&self->field_27B8);
}


// 0x004cac30: Hud::UpdateWrapper
// IDA: Hud::UpdateWrapper
// Ghidra: ---
char gta2::Hud_UpdateWrapper(struct Hud *self)
{
  struct HudArrow *pHudArrow; // ebx
  struct Player *Player1; // eax
  struct Player *i; // esi
  struct HudArrow *pHudArrow_1; // edi
  struct Ped *MainPed; // esi

  gta2::Hud_SetSpeedText(self);
  gta2::Hud_DrawUIWrapper(self);
  gta2::S86_8_sub_4C6C60(&self->S86_8_);
  gta2::S86_4_sub_4C7B10(&self->struc_S86_4);
  pHudArrow = &self->HudArrow_;
  LOBYTE(Player1) = gta2::Network_GetNetworkGame(&gNetwork);
  if ( (_BYTE)Player1 )
  {
    LOBYTE(Player1) = sub_4C7370();
    if ( (_BYTE)Player1 )
    {
      gta2::HudArrow_sub_4C8620(pHudArrow);
      Player1 = gta2::Game_GetPlayer1(gGame);
      for ( i = Player1; Player1; i = Player1 )
      {
        if ( !gta2::Player_GetCurrentPlayer(i) )
        {
          pHudArrow_1 = gta2::HudArrow_GetHudArrow(pHudArrow);
          gta2::ArrowTrace_SetPlayer(&pHudArrow_1->S86_2_1_[0].m_ArrowTrace, i);
          MainPed = i->MainPed;
          if ( MainPed )
            gta2::HudArrow_ArrowTrace(pHudArrow_1, MainPed);
        }
        Player1 = gta2::Game_GetPlayer(gGame);
      }
    }
  }
  return (char)Player1;
}



