#include "gta2_shim.h"

// Module: other, Class: HudBrief
// Functions: 14
// Source: unified (IDA+Ghidra)

// 0x004768a0: HudBrief::IsMessageVisible
// IDA: HudBrief::IsMessageVisible
// Ghidra: ---
bool gta2::HudBrief_IsMessageVisible(struct HudBrief *self)
{
  struct HudBrief_S2 *HudBrief_S2; // eax

  HudBrief_S2 = self->HudBrief_S2_;
  return HudBrief_S2 && HudBrief_S2->field_8;
}


// 0x004c2450: HudBrief::sub_4C2450
// IDA: HudBrief::sub_4C2450
// Ghidra: FUN_004c2450
short gta2::HudBrief_sub_4C2450(void *self,short *param_1,short *param_2,int param_3,ushort param_4 )
{
  short sVar1;
  short *psVar2;
  byte bVar3;
  short sVar4;
  undefined2 extraout_var_01;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  void *extraout_ECX;
  void *this_00;
  void *extraout_ECX_00;
  void *extraout_ECX_01;
  int iVar5;
  short *psVar6;
  short *psVar7;
  short *psVar8;
  short *psVar9;
  undefined2 in_stack_00000012;
  
  psVar8 = param_2;
  psVar9 = param_1;
  param_2 = (short *)0x1;
  sVar4 = FUN_004c23d0(self,param_4);
  psVar6 = NULL;
  iVar5 = 0;
  sVar1 = *psVar8;
  param_1 = NULL;
  this_00 = extraout_ECX;
  while (sVar1 != 0) {
    *psVar9 = *psVar8;
    sVar1 = *psVar8;
    this_00 = (void *)CONCAT22((short)((uint)this_00 >> 0x10),sVar1);
    if (sVar1 == 10) {
      psVar7 = NULL;
      iVar5 = 0;
      param_2 = (short *)((int)param_2 + 1);
      param_1 = NULL;
    }
    else if (sVar1 == 0x20) {
      iVar5 = iVar5 + CONCAT22(extraout_var_01,sVar4);
      psVar7 = psVar9;
      param_1 = psVar8;
    }
    else {
      psVar7 = psVar6;
      if (sVar1 != 0x23) {
        bVar3 = FUN_004539d0(this_00,_param_4,this_00);
        iVar5 = iVar5 + CONCAT31(extraout_var,bVar3);
        this_00 = extraout_ECX_00;
      }
    }
    psVar2 = param_1;
    psVar6 = psVar7;
    if (param_3 < iVar5) {
      iVar5 = 0;
      if ((param_1 == NULL) || (psVar7 == NULL)) {
        *psVar9 = 10;
        psVar9 = psVar9 + 1;
        bVar3 = FUN_004539d0(_param_4,_param_4,
                             CONCAT22((short)((uint)param_1 >> 0x10),*psVar8));
        iVar5 = CONCAT31(extraout_var_00,bVar3);
        *psVar9 = *psVar8;
        this_00 = extraout_ECX_01;
      }
      else {
        *psVar7 = 10;
        param_1 = NULL;
        psVar6 = NULL;
        psVar8 = psVar2;
        psVar9 = psVar7;
      }
      param_2 = (short *)((int)param_2 + 1);
    }
    psVar8 = psVar8 + 1;
    psVar9 = psVar9 + 1;
    sVar1 = *psVar8;
  }
  *psVar9 = 0;
  return (short)param_2;
}


// 0x004c62d0: HudBrief::ShowMessageToPlayer_0
// IDA: HudBrief::ShowMessageToPlayer_0
// Ghidra: ---
void gta2::HudBrief_ShowMessageToPlayer_0(struct HudBrief *self)
{
  struct HudBrief_S2 *pHudBrief_S2; // eax

  pHudBrief_S2 = self->pHudBrief_S2;
  self->pHudBrief_S2 = pHudBrief_S2->nextHudBrief_S2;
  pHudBrief_S2->nextHudBrief_S2 = self->HudBrief_S2_;
  self->HudBrief_S2_ = pHudBrief_S2;
}


// 0x004c6340: HudBrief::sub_4C6340
// IDA: HudBrief::sub_4C6340
// Ghidra: ---
HudBrief_S2 * gta2::HudBrief_sub_4C6340(struct HudBrief *self)
{
  struct HudBrief_S2 *i; // eax
  struct HudBrief_S2 *result; // eax

  for ( i = self->pHudBrief_S2; i->nextHudBrief_S2; i = i->nextHudBrief_S2 )
    ;
  i->nextHudBrief_S2 = self->HudBrief_S2_;
  self->HudBrief_S2_->field_8 = 0;
  self->HudBrief_S2_ = self->HudBrief_S2_->nextHudBrief_S2;
  result = i->nextHudBrief_S2;
  result->nextHudBrief_S2 = 0;
  return result;
}


// 0x004c6380: HudBrief::sub_4C6380
// IDA: HudBrief::sub_4C6380
// Ghidra: ---
HudBrief_S2 * gta2::HudBrief_sub_4C6380(struct HudBrief *self)
{
  struct HudBrief_S2 *result; // eax
  struct HudBrief_S2 *nextHudBrief_S2; // edx
  struct HudBrief_S2 *v3; // esi
  struct HudBrief_S2 *v4; // edx

  result = (struct HudBrief_S2 *)self->field_6FC;
  if ( result )
  {
    self->field_6FC = (int)result->nextHudBrief_S2;
    return result;
  }
  result = self->pHudBrief_S2;
  if ( result )
  {
    nextHudBrief_S2 = result->nextHudBrief_S2;
    if ( !nextHudBrief_S2 )
      goto LABEL_7;
    do
    {
      v3 = result;
      result = nextHudBrief_S2;
      nextHudBrief_S2 = nextHudBrief_S2->nextHudBrief_S2;
    }
    while ( nextHudBrief_S2 );
    if ( !v3 )
    {
LABEL_7:
      self->pHudBrief_S2 = 0;
      return result;
    }
    goto LABEL_11;
  }
  result = self->HudBrief_S2_;
  v4 = result->nextHudBrief_S2;
  if ( v4 )
  {
    do
    {
      v3 = result;
      result = v4;
      v4 = v4->nextHudBrief_S2;
    }
    while ( v4 );
    if ( v3 )
    {
LABEL_11:
      v3->nextHudBrief_S2 = 0;
      return result;
    }
  }
  self->HudBrief_S2_ = 0;
  return result;
}


// 0x004c6470: HudBrief::MainLogic
// IDA: HudBrief::MainLogic
// Ghidra: ---
size_t gta2::HudBrief_MainLogic(struct HudBrief *self, wchar_t *a2)
{
  __int16 v2; // di
  struct HudBrief_S2 *HudBrief_S2; // eax
  char *v5; // eax
  char v6; // al
  struct HudBrief *v7; // ecx
  wchar_t *v8; // eax
  size_t v9; // edi
  char *v10; // eax
  char v11; // al
  char v12; // al
  struct HudBrief *v13; // ecx
  char v14; // al
  wchar_t *v15; // ecx
  void *v16; // eax
  int v18; // [esp-8h] [ebp-10h]
  int v19; // [esp-8h] [ebp-10h]
  wchar_t *v20; // [esp-8h] [ebp-10h]
  __int16 v21; // [esp-4h] [ebp-Ch]
  __int16 v22; // [esp-4h] [ebp-Ch]
  size_t v23; // [esp+4h] [ebp-4h]

  HudBrief_S2 = self->HudBrief_S2_;
  if ( HudBrief_S2 )
  {
    if ( HudBrief_S2[1].field_2 == -1 )
    {
      gta2::Text__Bsearch(gText, HudBrief_S2);
      v12 = gta2::sub_4C63F0(v2);
      self->field_502 = v12;
      if ( v12 )
        v13 = (struct HudBrief *)((char *)v13 + 2);
      else
        self->field_502 = 8;
      self->field_508 = (void *)gta2::HudBrief_sub_4C2450(v13, &self->field_0, (int)v13, (__int16)dword_595004);
      v9 = gta2::_wcslen(&self->field_0);
      if ( !show_brief_number )
        return v9;
      gta2::Text__Bsearch(gText, self->HudBrief_S2_);
      v14 = gta2::sub_4C63F0(v22);
      self->field_502 = v14;
      if ( v14 )
        ++v15;
      else
        self->field_502 = 8;
      v20 = v15;
    }
    else
    {
      v18 = HudBrief_S2[1].field_2;
      v5 = (char *)gta2::Text__Bsearch(gText, HudBrief_S2);
      ShowTextDisplay(&TextWcharT, v5, v18);
      v6 = gta2::sub_4C63F0(v2);
      self->field_502 = v6;
      if ( v6 )
      {
        v8 = &word_5E9F0A;
      }
      else
      {
        v8 = &TextWcharT;
        self->field_502 = 8;
      }
      LOWORD(v7) = (_WORD)unk_672F3C;
      self->field_508 = (void *)gta2::HudBrief_sub_4C2450(v7, &self->field_0, (int)v8, (__int16)dword_595004);
      v9 = gta2::_wcslen(&self->field_0);
      if ( !show_brief_number )
        return v9;
      v19 = self->HudBrief_S2_[1].field_2;
      v10 = (char *)gta2::Text__Bsearch(gText, self->HudBrief_S2_);
      ShowTextDisplay(&TextWcharT, v10, v19);
      v11 = gta2::sub_4C63F0(v21);
      self->field_502 = v11;
      if ( v11 )
      {
        v20 = &word_5E9F0A;
      }
      else
      {
        self->field_502 = 8;
        v20 = &TextWcharT;
      }
    }
    v16 = sub_4C2300(&self->HudBrief_S2_->field_0);
    ShowTextDisplay(dest, (char *)L"(%s)%s", v16, v20);
    self->field_508 = (void *)gta2::HudBrief_sub_4C2450(dword_595004, &self->field_0, (int)dest, (__int16)dword_595004);
    return v9;
  }
  return v23;
}


// 0x004c6640: HudBrief::sub_4C6640
// IDA: HudBrief::sub_4C6640
// Ghidra: ---
int gta2::HudBrief_sub_4C6640(struct HudBrief *self)
{
  struct HudBrief_S2 *HudBrief_S2; // edx
  int result; // eax
  wchar_t *v4; // [esp+0h] [ebp-4h]

  self->field_510 = gta2::HudBrief_MainLogic(self, v4);
  HudBrief_S2 = self->HudBrief_S2_;
  result = 0;
  self->field_504 = LOWORD(self->field_510) * LOWORD(gHud->TextSpeed);
  self->field_50C = 0;
  self->field_514 = 0;
  HudBrief_S2->field_10 = 0;
  return result;
}


// 0x004c6690: HudBrief::ShowMessageWithParam
// IDA: HudBrief::ShowMessageWithParam
// Ghidra: ---
int gta2::HudBrief_ShowMessageWithParam(struct HudBrief *self, int timeInSeconds, const char *messageCode, int a4)
{
  int v4; // ecx
  struct HudBrief_S2 *v5; // esi
  int result; // eax
  int v7; // ecx
  struct HudBrief_S2 *v8; // ecx

  v5 = gta2::HudBrief_sub_4C6380(self);
  strcpy(&v5->field_0, messageCode);
  v5->field_8 = (void *)timeInSeconds;
  v5->field_10 = 0;
  v5[1].field_2 = a4;
  result = *(_DWORD *)(v4 + 1784);
  if ( result )
  {
    if ( *(_DWORD *)(result + 8) < timeInSeconds || timeInSeconds == 3 )
    {
      if ( *(_BYTE *)(result + 16) )
        gta2::sub_4C6310((void *)v4);
      v5->nextHudBrief_S2 = *(HudBrief_S2 **)(v4 + 1784);
      *(_DWORD *)(v4 + 1784) = v5;
      return gta2::HudBrief_sub_4C6640((struct HudBrief *)v4);
    }
    else
    {
      if ( *(_DWORD *)(result + 12) )
      {
        do
        {
          v7 = *(_DWORD *)(result + 12);
          if ( *(_DWORD *)(v7 + 8) < timeInSeconds )
            break;
          result = *(_DWORD *)(result + 12);
        }
        while ( *(_DWORD *)(v7 + 12) );
      }
      v8 = *(HudBrief_S2 **)(result + 12);
      if ( v8 )
      {
        v5->nextHudBrief_S2 = v8;
        *(_DWORD *)(result + 12) = v5;
      }
      else
      {
        *(_DWORD *)(result + 12) = v5;
        v5->nextHudBrief_S2 = 0;
      }
    }
  }
  else
  {
    *(_DWORD *)(v4 + 1784) = v5;
    v5->nextHudBrief_S2 = 0;
    return gta2::HudBrief_sub_4C6640((struct HudBrief *)v4);
  }
  return result;
}


// 0x004c6750: HudBrief::ShowMessageToPlayer
// IDA: HudBrief::ShowMessageToPlayer
// Ghidra: ---
int gta2::HudBrief_ShowMessageToPlayer(struct HudBrief *self, int timeInSeconds, const char *messageCode)
{
  return gta2::HudBrief_ShowMessageWithParam(self, timeInSeconds, messageCode, -1);
}


// 0x004c6770: HudBrief::sub_4C6770
// IDA: HudBrief::sub_4C6770
// Ghidra: ---
int gta2::HudBrief_sub_4C6770(void *self)
{
  int v1; // edi
  int v2; // eax
  int result; // eax
  int v4; // et2
  int v5; // edx
  int v6; // eax
  int v7; // esi
  struct HudBrief *v8; // ecx

  v1 = *((_DWORD *)self + 446);
  if ( v1 )
  {
    v2 = (unsigned __int16)--*((_WORD *)self + 642);
    v4 = v2 % 3;
    result = v2 / 3;
    if ( !v4 )
    {
      v5 = *((_DWORD *)self + 324);
      v6 = *((_DWORD *)self + 325) + 1;
      *((_DWORD *)self + 325) = v6;
      if ( v6 == v5 )
        *((_DWORD *)self + 325) = 0;
      v7 = *((unsigned __int16 *)self + *((_DWORD *)self + 325));
      result = (unsigned __int16)v7 / 20;
      if ( (unsigned __int16)v7 % 20 )
        *((_DWORD *)self + 323) = 2 * (v7 % 2);
      else
        *((_DWORD *)self + 323) = 1;
    }
    *(_BYTE *)(v1 + 16) = 1;
    if ( !*((_WORD *)self + 642) )
    {
      gta2::sub_4C6310(self);
      result = (int)v8->HudBrief_S2_;
      if ( result )
        return gta2::HudBrief_sub_4C6640(v8);
    }
  }
  return result;
}


// 0x004c6830: HudBrief::CheckQueue
// IDA: HudBrief::CheckQueue
// Ghidra: ---
HudBrief_S2 * gta2::HudBrief_CheckQueue(struct HudBrief *self)
{
  struct HudBrief_S2 *result; // eax
  struct HudBrief_S2 *HudBrief_S2; // eax
  struct HudBrief *v3; // ecx

  result = self->pHudBrief_S2;
  if ( result )
  {
    HudBrief_S2 = self->HudBrief_S2_;
    if ( HudBrief_S2 )
    {
      if ( HudBrief_S2->field_10 )
        gta2::HudBrief_sub_4C6340(self);
    }
    gta2::HudBrief_ShowMessageToPlayer_0(self);
    return (struct HudBrief_S2 *)gta2::HudBrief_sub_4C6640(v3);
  }
  return result;
}


// 0x004c6860: HudBrief::Clear
// IDA: HudBrief::Clear
// Ghidra: ---
HudBrief_S2 * gta2::HudBrief_Clear(struct HudBrief *self, void *a2)
{
  struct HudBrief_S2 *v3; // ebx
  struct HudBrief_S2 *HudBrief_S2; // esi
  struct HudBrief_S2 *result; // eax

  v3 = 0;
  HudBrief_S2 = self->HudBrief_S2_;
  while ( HudBrief_S2 )
  {
    if ( HudBrief_S2->field_8 == a2 )
    {
      if ( v3 )
      {
        result = HudBrief_S2->nextHudBrief_S2;
        v3->nextHudBrief_S2 = result;
        HudBrief_S2->nextHudBrief_S2 = (struct HudBrief_S2 *)self->field_6FC;
        self->field_6FC = (int)HudBrief_S2;
        HudBrief_S2 = v3->nextHudBrief_S2;
      }
      else
      {
        if ( self->HudBrief_S2_->field_10 )
          result = (struct HudBrief_S2 *)gta2::sub_4C6310(self);
        else
          result = (struct HudBrief_S2 *)gta2::sub_4C62F0(self);
        HudBrief_S2 = self->HudBrief_S2_;
        if ( !HudBrief_S2 )
          return result;
        result = (struct HudBrief_S2 *)gta2::HudBrief_sub_4C6640(self);
      }
    }
    else
    {
      v3 = HudBrief_S2;
      HudBrief_S2 = HudBrief_S2->nextHudBrief_S2;
    }
  }
  return result;
}


// 0x004c68e0: HudBrief::HudBrief
// IDA: HudBrief::HudBrief
// Ghidra: ---
void gta2::HudBrief_HudBrief(struct HudBrief *self)
{
  int v2; // ecx
  int v3; // edx

  self->field_50C = 0;
  self->field_6FC = (int)&self->field_518;
  self->field_510 = 0;
  self->field_514 = 0;
  self->HudBrief_S2_ = 0;
  self->pHudBrief_S2 = 0;
  self->field_504 = 0;
  v2 = (int)&self->field_524;
  v3 = 19;
  do
  {
    *(_DWORD *)v2 = v2 + 12;
    v2 += 24;
    --v3;
  }
  while ( v3 );
  self->field_6EC = 0;
}


// 0x004c9430: HudBrief::sub_4C9430
// IDA: HudBrief::sub_4C9430
// Ghidra: ---
void gta2::HudBrief_sub_4C9430(HudBrief *a1)
{
  struct HudBrief *v1; // esi
  int v2; // ecx
  int v3; // eax
  int v4; // edx
  struct Hud *v5; // ecx
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // [esp-1Ch] [ebp-24h] BYREF
  S202 v10; // [esp-18h] [ebp-20h] BYREF

  v1 = a1;
  if ( a1->HudBrief_S2_ )
  {
    LOWORD(a1) = unk_672F98.Index;
    memset(&v10.field_C, 0, 12);
    v10.CarSystemManager = (struct CarSystemManager *)&v10.field_1C;
    v10.S202 = (struct S202 *)a1;
    v10.field_0 = (int)a1;
    *(_DWORD *)&v10.field_1C = 2;
    gta2::bitShiftLeft1(&v10, 443);
    v9 = v2;
    gta2::bitShiftLeft1(&v9, 32);
    LOWORD(v3) = (unsigned __int8)v1->field_502;
    --v3;
    v4 = 3 * v3;
    LOWORD(v4) = LOWORD(v1->field_50C) + 3 * v3;
    gta2::Hud_DrawSprite(
      v5,
      6,
      v4 + 19,
      v9,
      v10.field_0,
      (char)v10.S202,
      (const int *)v10.CarSystemManager,
      v10.field_C,
      (int)v10.field_10);
    v6 = (int)v1->field_508 * gta2::Font_GetCharHeight((__int16)unk_672F3C);
    v7 = 480 - v6;
    LOWORD(v6) = (_WORD)unk_672F3C;
    memset(&v10.field_C, 0, 12);
    v10.CarSystemManager = (struct CarSystemManager *)&v10.field_1C;
    v10.S202 = (struct S202 *)v6;
    v10.field_0 = v6;
    *(_DWORD *)&v10.field_1C = 2;
    gta2::S202_sub_41F980(&v10, v7);
    v9 = v8;
    gta2::bitShiftLeft1(&v9, 64);
    sub_4C7280(&v1->field_0, v9, (struct SpriteS1 *)v10.field_0);
  }
}



