#include "gta2_shim.h"

// Module: other, Class: HudArrow
// Functions: 33
// Source: unified (IDA+Ghidra)

// 0x00476840: HudArrow::PlayerHandler
// IDA: HudArrow::PlayerHandler
// Ghidra: ---
int gta2::HudArrow_PlayerHandler(HudArrow *self, int a2, int a3, int a4)
{
  return gta2::ArrowTrace_sub_4767C0(&self->S86_2_1_[0].m_ArrowTrace, a2, a3, a4);
}


// 0x00476850: HudArrow::SetParam
// IDA: HudArrow::SetParam
// Ghidra: ---
void gta2::HudArrow_SetParam(HudArrow *self, int a2)
{
  struct ArrowTrace *p_m_ArrowTrace; // ecx

  p_m_ArrowTrace = &self->S86_2_1_[0].m_ArrowTrace;
  p_m_ArrowTrace->m_nType = 2;
  p_m_ArrowTrace->field_0 = a2;
}


// 0x00476860: HudArrow::GetParam
// IDA: HudArrow::GetParam
// Ghidra: ---
int gta2::HudArrow_GetParam(HudArrow *self, int a2)
{
  int result; // eax
  struct ArrowTrace *p_m_ArrowTrace; // ecx

  p_m_ArrowTrace = &self->S86_2_1_[0].m_ArrowTrace;
  result = a2;
  p_m_ArrowTrace->m_nType = 3;
  p_m_ArrowTrace->field_4 = a2;
  return result;
}


// 0x00476870: HudArrow::ResetParam
// IDA: HudArrow::ResetParam
// Ghidra: ---
void gta2::HudArrow_ResetParam(HudArrow *self, int a2)
{
  gta2::ArrowTrace_sub_476810(&self->S86_2_1_[0].m_ArrowTrace, a2);
}


// 0x004c5e60: HudArrow::SetArrowType
// IDA: HudArrow::SetArrowType
// Ghidra: ---
unsigned int gta2::HudArrow_SetArrowType(HudArrow *self, unsigned int a2)
{
  unsigned int result; // eax

  result = a2;
  self->S86_2_1_[0].isSelect = a2;
  return result;
}


// 0x004c5e70: HudArrow::sub_4C5E70
// IDA: HudArrow::sub_4C5E70
// Ghidra: ---
HudArrow * gta2::HudArrow_sub_4C5E70(HudArrow *self, int *a2)
{
  struct HudArrow *result; // eax
  int v3; // edx

  result = self;
  v3 = 0;
  while ( result->S86_2_1_[0].field_2E )
  {
    ++v3;
    result = (HudArrow *)((char *)result + 124);
    if ( v3 >= 17 )
      return 0;
  }
  *a2 = v3;
  result->S86_2_1_[0].field_2E = 1;
  return result;
}


// 0x004c5ea0: HudArrow::ToggleVisibility
// IDA: HudArrow::ToggleVisibility
// Ghidra: ---
int gta2::HudArrow_ToggleVisibility(HudArrow *self, int a2)
{
  int v2; // eax
  int result; // eax

  switch ( v2 )
  {
    case 176:
    case 177:
      result = 2;
      break;
    case 178:
    case 179:
      result = 1;
      break;
    case 180:
    case 181:
      result = 3;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


// 0x004c6f80: HudArrow::AreBothArrowTracesUsed
// IDA: HudArrow::AreBothArrowTracesUsed
// Ghidra: ---
bool gta2::HudArrow_AreBothArrowTracesUsed(HudArrow *self)
{
  return gta2::ArrowTrace_SetDefaultType(&self->S86_2_1_[0].m_ArrowTrace)
      && gta2::ArrowTrace_SetDefaultType(&self->S86_2_1_[0].m_SecondArrowTrace);
}


// 0x004c6fb0: HudArrow::UpdatePosition
// IDA: HudArrow::UpdatePosition
// Ghidra: HudArrow::FUN_004c6fb0
undefined1 gta2::HudArrow_UpdatePosition(HudArrow *self)
{
  byte bVar1;
  
  bVar1 = gta2::ArrowTrace_SetDefaultType(&self->S86_2_1_[0].m_ArrowTrace);
  if (bVar1 == 0) {
    bVar1 = gta2::ArrowTrace_SetDefaultType(&self->S86_2_1_[0].m_SecondArrowTrace);
    if (bVar1 == 0) {
      return 1;
    }
  }
  return 0;
}


// 0x004c6fe0: HudArrow::SetSpriteID
// IDA: HudArrow::SetSpriteID
// Ghidra: ---
void gta2::HudArrow_SetSpriteID(HudArrow *self, __int16 a2)
{
  self->S86_2_1_[0].m_nSpriteId = a2;
}


// 0x004c7040: HudArrow::Init
// IDA: HudArrow::Init
// Ghidra: ---
bool gta2::HudArrow_Init(HudArrow *self, bool a2)
{
  bool result; // al

  result = a2;
  self->S86_2_1_[0].m_bVisible = a2;
  return result;
}


// 0x004c7050: HudArrow::IsArrowVisible
// IDA: HudArrow::IsArrowVisible
// Ghidra: ---
bool gta2::HudArrow_IsArrowVisible(HudArrow *self)
{
  return self->S86_2_1_[0].ArrowVisible;
}


// 0x004c7060: HudArrow::sub_4C7060
// IDA: HudArrow::sub_4C7060
// Ghidra: HudArrow::FUN_004c7060
void gta2::HudArrow_sub_4C7060(HudArrow *self)
{
  struct ArrowTrace *pAVar1;
  
  pAVar1 = &self->S86_2_1_[0].m_ArrowTrace;
  if (self->S86_2_1_[0].ArrowTrace == pAVar1) {
    pAVar1 = &self->S86_2_1_[0].m_SecondArrowTrace;
  }
  self->S86_2_1_[0].ArrowTrace = pAVar1;
  return;
}


// 0x004c7080: HudArrow::HudArrow
// IDA: HudArrow::HudArrow
// Ghidra: ---
void gta2::HudArrow_HudArrow(HudArrow *self)
{
  gta2::constructor(self, 124, 17, S86_2_1::S86_2_1);
  self->field_83C = 1;
  self->HudArrowNext = 0;
  self->field_844 = 0;
}


// 0x004c70b0: HudArrow::Clear
// IDA: HudArrow::Clear
// Ghidra: ---
byte gta2::HudArrow_Clear(HudArrow *self)
{
  return self->field_83C;
}


// 0x004c7e60: HudArrow::MainLogic
// IDA: HudArrow::MainLogic
// Ghidra: ---
char gta2::HudArrow_MainLogic(HudArrow *self)
{
  char v3; // al
  struct ArrowTrace *ArrowTrace; // edi
  SpriteS1 *v5; // eax
  Player *v6; // eax
  struct ArrowTrace *v7; // ebx
  SpriteS1 *v8; // eax
  Player *v9; // eax
  SpriteS1 *FirstElement; // ecx
  SpriteS1 *v11; // [esp-Ch] [ebp-38h]
  SpriteS1 *v12; // [esp-Ch] [ebp-38h]
  int v13; // [esp+4h] [ebp-28h] BYREF
  int Y; // [esp+8h] [ebp-24h] BYREF
  S202 a3; // [esp+Ch] [ebp-20h] BYREF

  gta2::ArrowTrace_MainLogic(&self->S86_2_1_[0].m_ArrowTrace);
  gta2::ArrowTrace_MainLogic(&self->S86_2_1_[0].m_SecondArrowTrace);
  if ( gta2::ArrowTrace_SetDefaultType(self->S86_2_1_[0].ArrowTrace) )
  {
    gta2::HudArrow_sub_4C7060(self);
    if ( gta2::ArrowTrace_SetDefaultType(self->S86_2_1_[0].ArrowTrace) )
      return 1;
  }
  if ( gta2::HudArrow_UpdatePosition(self)
    && self->S86_2_1_[0].m_ArrowTrace.field_23
    && self->S86_2_1_[0].m_SecondArrowTrace.field_23 )
  {
    v3 = self->S86_2_1_[0].field_26;
    if ( v3 )
    {
      LOBYTE(self->S86_2_1_[0].field_26) = v3 - 1;
      return 0;
    }
    gta2::Player_sub_4A6610(gGame->PlayerMain, &Y);
    ArrowTrace = self->S86_2_1_[0].ArrowTrace;
    v11 = gta2::Player_sub_401B40((Player *)&v13, &a3, (int)&ArrowTrace->m_vPos1);
    v5 = gta2::Player_sub_401B40((Player *)&Y, (S202 *)&a3.CarSystemManager, (int)&ArrowTrace->m_vPos);
    gta2::Weapon_sub_432860((Weapon *)&a3.field_18, v5, v11);
    v6 = (Player *)gta2::Player_sub_41E260((Player *)&a3.field_18, (int)&a3.CarSystemManager);
    a3.field_0 = (int)gta2::Player_sub_401B40(v6, (S202 *)&a3.field_C, (int)&self->S86_2_1_[0].field_10)->FirstElement;
    gta2::HudArrow_sub_4C7060(self);
    v7 = self->S86_2_1_[0].ArrowTrace;
    v12 = gta2::Player_sub_401B40((Player *)&v13, (S202 *)&a3.field_C, (int)&v7->m_vPos1);
    v8 = gta2::Player_sub_401B40((Player *)&Y, (S202 *)&a3.field_10, (int)&v7->m_vPos);
    gta2::Weapon_sub_432860((Weapon *)&a3.field_18, v8, v12);
    v9 = (Player *)gta2::Player_sub_41E260((Player *)&a3.field_18, (int)&a3.field_10);
    FirstElement = gta2::Player_sub_401B40(v9, (S202 *)&a3.pPlayer, (int)&a3)->FirstElement;
    LOBYTE(self->S86_2_1_[0].field_26) = 20;
    *(_DWORD *)&self->S86_2_1_[0].field_10 = FirstElement;
  }
  return 0;
}


// 0x004c7fc0: HudArrow::Draw
// IDA: HudArrow::Draw
// Ghidra: ---
CarTransforms * gta2::HudArrow_Draw(HudArrow *self)
{
  struct ArrowTrace *ArrowTrace; // edi
  SpriteS1 *v3; // eax
  __int16 *v4; // eax
  S202 **v5; // eax
  struct ArrowTrace *v6; // edx
  SpriteS1 *FirstElement; // ebp
  AudioManager *v8; // eax
  char *v9; // ecx
  Player *v10; // edi
  BOOL v11; // eax
  CameraOrPhysics *MultiPlayerMode; // edi
  int *p_m_vPos3; // ebp
  SpriteS1 *v14; // eax
  SpriteS1 *v15; // eax
  SpriteS1 *v16; // eax
  Radar *v17; // eax
  Radar *v18; // eax
  SpriteS1 *v19; // eax
  Radar *v20; // eax
  SpriteS1 *v21; // eax
  int *v22; // ebp
  Radar *v23; // eax
  SpriteS1 *v24; // eax
  int *v25; // eax
  SpriteS1 *v27; // [esp-Ch] [ebp-4Ch]
  SpriteS1 *v28; // [esp-4h] [ebp-44h]
  SpriteS1 *v29; // [esp-4h] [ebp-44h]
  S202 a2; // [esp+10h] [ebp-30h] BYREF
  char v31; // [esp+30h] [ebp-10h] BYREF
  int v32; // [esp+34h] [ebp-Ch] BYREF
  _BYTE v33[8]; // [esp+38h] [ebp-8h] BYREF

  gta2::Player_sub_4A6610(gGame->PlayerMain, &a2.field_10);
  ArrowTrace = self->S86_2_1_[0].ArrowTrace;
  v28 = gta2::Player_sub_401B40((Player *)&a2.field_C, (S202 *)&a2.pPlayer, (int)&ArrowTrace->m_vPos1);
  v3 = gta2::Player_sub_401B40((Player *)&a2.field_10, (S202 *)&a2.S202, (int)&ArrowTrace->m_vPos);
  gta2::Weapon_sub_432860((Weapon *)v33, v3, v28);
  sub_40F790(v33, (Car *)&a2);
  self->S86_2_1_[0].m_nPointRotation = *v4;
  v5 = (S202 **)gta2::Player_sub_41E260((Player *)v33, (int)&a2.pPlayer);
  v6 = self->S86_2_1_[0].ArrowTrace;
  a2.S202 = *v5;
  if ( v6->field_23 )
  {
    FirstElement = gta2::Player_sub_401B40((Player *)&a2.S202, (S202 *)&a2.pPlayer, (int)&unk_6732A4)->FirstElement;
    a2.field_0 = (int)FirstElement;
    if ( gta2::sub_4037E0(&a2) )
    {
      FirstElement = unk_67302C.FirstElement;
      a2.field_0 = (int)unk_67302C.FirstElement;
    }
  }
  else
  {
    FirstElement = *(SpriteS1 **)&self->S86_2_1_[0].field_C;
    a2.field_0 = (int)FirstElement;
    if ( gta2::Player_GetActivePlayerCar(gGame->PlayerMain) )
    {
      gta2::Player_sub_40E530((Player *)&a2, (Tango *)&unk_673038);
      FirstElement = (SpriteS1 *)a2.field_0;
    }
  }
  v8 = gta2::Car_sub_403800((Car *)&self->S86_2_1_[0].field_10, (int)&a2);
  v9 = &self->S86_2_1_[0].field_10;
  if ( v8 )
  {
    v10 = (Player *)&self->S86_2_1_[0].field_14;
    gta2::Weapon_UseAmmo((Weapon *)v9, &self->S86_2_1_[0].field_14);
    LOBYTE(v11) = gta2::Player_CheckCondition((Player *)&self->S86_2_1_[0].field_10, &a2.field_0);
  }
  else
  {
    if ( !gta2::sub_4037E0(v9) )
    {
      *(_DWORD *)&self->S86_2_1_[0].field_14 = unk_672FAC;
      goto LABEL_15;
    }
    v10 = (Player *)&self->S86_2_1_[0].field_14;
    gta2::Player_sub_40E530((Player *)&self->S86_2_1_[0].field_10, (Tango *)&self->S86_2_1_[0].field_14);
    v11 = gta2::Player_sub_40CE70((Player *)&self->S86_2_1_[0].field_10, &a2);
  }
  if ( v11 )
  {
    *(_DWORD *)&self->S86_2_1_[0].field_10 = FirstElement;
    v10->CurrentPlayer = (Player *)unk_672FAC;
  }
  else if ( gta2::sub_4037E0(v10) )
  {
    gta2::Player_sub_40E530(v10, &unk_67327C);
  }
LABEL_15:
  MultiPlayerMode = gta2::Player_GetMultiPlayerMode(gGame->PlayerMain);
  p_m_vPos3 = &self->S86_2_1_[0].ArrowTrace->m_vPos3;
  v14 = gta2::Player_sub_401B40((Player *)&unk_672F70, &a2, (int)p_m_vPos3);
  v15 = gta2::S202_sub_401B20(
          (S202 *)v14,
          (SpriteS1 *)&a2.pPlayer,
          (PublicTransport *)&MultiPlayerMode->cameraPosTarget_[3].field_24);
  a2.field_0 = *(_DWORD *)gta2::sub_401B90(&dword_672FC8, &a2.field_18, v15);
  a2.pPlayer = (Player *)64;
  v27 = gta2::Radar_AddBlip(
          (Radar *)&MultiPlayerMode->cameraPosTarget_[2].Car,
          (SpriteS1 *)&a2.field_18,
          (PublicTransport *)&a2);
  v16 = gta2::sub_401BD0(&self->S86_2_1_[0].field_10, (SpriteS1 *)&a2, &a2.pPlayer);
  v17 = (Radar *)gta2::sub_401B90(v16, &a2.pPlayer, v27);
  a2.field_0 = (int)gta2::Radar_AddBlip(
                      v17,
                      (SpriteS1 *)&a2.field_1C,
                      (PublicTransport *)&MultiPlayerMode->cameraPosTarget_[4].field_4)->FirstElement;
  if ( gta2::Player_IsCurrentPlayer((Player *)&a2.S202, (Player *)&unk_67302C) || self->S86_2_1_[0].ArrowTrace->field_23 )
  {
    a2.S202 = (S202 *)*p_m_vPos3;
  }
  else
  {
    v29 = gta2::Player_sub_401B40((Player *)p_m_vPos3, (S202 *)&a2.field_1C, (int)&a2.CarSystemManager);
    v18 = (Radar *)gta2::sub_401B90(&self->S86_2_1_[0].field_10, &a2.pPlayer, &a2.S202);
    v19 = gta2::Radar_AddBlip(v18, (SpriteS1 *)&a2.field_18, (PublicTransport *)v29);
    a2.S202 = (S202 *)gta2::S202_sub_401B20((S202 *)&a2.CarSystemManager, (SpriteS1 *)&a2.S202, (PublicTransport *)v19)->FirstElement;
  }
  sub_40F520(&a2.field_18, &self->S86_2_1_[0].m_nPointRotation);
  v21 = gta2::Radar_AddBlip(v20, (SpriteS1 *)&a2.field_1C, (PublicTransport *)&a2);
  v22 = (int *)gta2::Player_sub_401B40((Player *)&a2.field_C, (S202 *)&a2.pPlayer, (int)v21);
  gta2::sub_40F500(&v32, &self->S86_2_1_[0].m_nPointRotation);
  v24 = gta2::Radar_AddBlip(v23, (SpriteS1 *)&v31, (PublicTransport *)&a2);
  v25 = (int *)gta2::Player_sub_401B40((Player *)&a2.field_10, &a2, (int)v24);
  return gta2::CameraOrPhysics_WorldToScreen2D(
           MultiPlayerMode,
           *v25,
           *v22,
           (int)a2.S202,
           (int *)self,
           &self->S86_2_1_[0].Point2);
}


// 0x004c82c0: HudArrow::UpdateRadar
// IDA: HudArrow::UpdateRadar
// Ghidra: ---
char gta2::HudArrow_UpdateRadar(HudArrow *self)
{
  char IsArrowVisible; // al
  int v3; // edx
  int v4; // edi
  int v6; // [esp+8h] [ebp-4h]

  IsArrowVisible = gta2::HudArrow_AreBothArrowTracesUsed(self);
  if ( !IsArrowVisible )
  {
    IsArrowVisible = gta2::HudArrow_IsArrowVisible(self);
    if ( IsArrowVisible )
    {
      if ( self->S86_2_1_[0].isSelect == 5 )
        gta2::General_GetCycle(gGeneral);
      gta2::Player_GetMultiPlayerMode(gGame->PlayerMain);
      LOWORD(v3) = self->S86_2_1_[0].m_nSpriteId;
      gta2::sub_4CBA50((void *)self->S86_2_1_[0].Point, 6, v3, self->S86_2_1_[0].Point, (void *)self->S86_2_1_[0].Point2);
      *(_DWORD *)&IsArrowVisible = self->S86_2_1_[0].isSelect - 1;
      switch ( self->S86_2_1_[0].isSelect )
      {
        case 1u:
          v4 = 0;
          goto LABEL_10;
        case 2u:
          v4 = 2;
          goto LABEL_10;
        case 3u:
          v4 = 1;
          goto LABEL_10;
        case 4u:
        case 5u:
          return IsArrowVisible;
        default:
          v4 = v6;
LABEL_10:
          gta2::Player_GetMultiPlayerMode(gGame->PlayerMain);
          IsArrowVisible = gta2::sub_4CBA50(
                             (void *)self->S86_2_1_[0].Point2,
                             6,
                             v4 + 8,
                             self->S86_2_1_[0].Point,
                             (void *)self->S86_2_1_[0].Point2);
          break;
      }
    }
  }
  return IsArrowVisible;
}


// 0x004c83d0: HudArrow::ArrowTrace
// IDA: HudArrow::ArrowTrace
// Ghidra: ---
void gta2::HudArrow_ArrowTrace(HudArrow *self, Ped *pMainPed)
{
  switch ( gta2::Ped_GetRemap(pMainPed) )
  {
    case REMAP_REDNECK_1:
    case REMAP_REDNECK_2:
      gta2::HudArrow_SetSpriteID(self, 4);
      break;
    case REMAP_SCIENTIST:
      gta2::HudArrow_SetSpriteID(self, 5);
      break;
    case REMAP_ZAIBATSU:
      gta2::HudArrow_SetSpriteID(self, 3);
      break;
    case REMAP_KRISHNA:
      gta2::HudArrow_SetSpriteID(self, 6);
      break;
    case REMAP_RUSSIAN:
      gta2::HudArrow_SetSpriteID(self, 7);
      break;
    case REMAP_LOONIE:
      gta2::HudArrow_SetSpriteID(self, 1);
      break;
    case REMAP_YAKUZA:
      gta2::HudArrow_SetSpriteID(self, 2);
      break;
    default:
      return;
  }
}


// 0x004c8470: HudArrow::sub_4C8470
// IDA: HudArrow::sub_4C8470
// Ghidra: ---
char gta2::HudArrow_sub_4C8470(HudArrow *self, HudArrow *a2)
{
  struct Gang *Gang; // ebp
  int v3; // edi

  Gang = a2->S86_2_1_[0].Gang;
  v3 = 0;
  while ( self == a2
       || gta2::HudArrow_AreBothArrowTracesUsed(self)
       || !gta2::HudArrow_IsArrowVisible(self)
       || self->S86_2_1_[0].Gang != Gang )
  {
    ++v3;
    self = (HudArrow *)((char *)self + 124);
    if ( v3 >= 17 )
      return 0;
  }
  return 1;
}


// 0x004c84c0: HudArrow::sub_4C84C0
// IDA: HudArrow::sub_4C84C0
// Ghidra: ---
char gta2::HudArrow_sub_4C84C0(HudArrow *self)
{
  int v2; // edi
  struct ArrowTrace *p_m_ArrowTrace; // esi
  Player *CurrentPlayer; // eax
  Player *pPlayer; // eax
  struct Ped *Ped; // eax

  v2 = 17;
  if ( gta2::Network_GetNetworkGame(&gNetwork) )
  {
    p_m_ArrowTrace = &self->S86_2_1_[0].m_ArrowTrace;
    do
    {
      if ( !gta2::ArrowTrace_GetCurrentPlayer(p_m_ArrowTrace)
        || (CurrentPlayer = gta2::ArrowTrace_GetCurrentPlayer(p_m_ArrowTrace), !gta2::Player_GetPed(CurrentPlayer))
        || (pPlayer = gta2::ArrowTrace_GetCurrentPlayer(p_m_ArrowTrace),
            Ped = gta2::Player_GetPed(pPlayer),
            (Ped->PositionX1 & 0x2000000) == 0) )
      {
        LOBYTE(Ped) = gta2::HudArrow_UpdateRadar((HudArrow *)((char *)&p_m_ArrowTrace[-2].m_nType + 2));
      }
      p_m_ArrowTrace = (ArrowTrace *)((char *)p_m_ArrowTrace + 124);
      --v2;
    }
    while ( v2 );
  }
  else
  {
    do
    {
      LOBYTE(Ped) = gta2::HudArrow_UpdateRadar(self);
      self = (HudArrow *)((char *)self + 124);
      --v2;
    }
    while ( v2 );
  }
  return (char)Ped;
}


// 0x004c8540: HudArrow::sub_4C8540
// IDA: HudArrow::sub_4C8540
// Ghidra: ---
char gta2::HudArrow_sub_4C8540(HudArrow *self)
{
  int v2; // edi
  struct HudArrow *i; // esi
  _BYTE *p_inUse; // eax

  v2 = 0;
  for ( i = self; ; i = (HudArrow *)((char *)i + 124) )
  {
    LOBYTE(p_inUse) = gta2::HudArrow_AreBothArrowTracesUsed(i);
    if ( !(_BYTE)p_inUse )
    {
      p_inUse = &i->S86_2_1_[0].Gang->inUse;
      if ( p_inUse )
      {
        p_inUse = i->S86_2_1_[0].ArrowTrace;
        if ( p_inUse[32] )
          break;
      }
    }
    if ( ++v2 >= 17 )
    {
      self->HudArrowNext = 0;
      return (char)p_inUse;
    }
  }
  self->HudArrowNext = i;
  return (char)p_inUse;
}


// 0x004c8590: HudArrow::sub_4C8590
// IDA: HudArrow::sub_4C8590
// Ghidra: HudArrow::FUN_004c8590
byte gta2::HudArrow_sub_4C8590(HudArrow *self,Gang *pGang)
{
  char cVar1;
  struct ArrowTrace *pArrowTrace;
  int iVar2;
  
  iVar2 = 0;
  pArrowTrace = (ArrowTrace *)&self->S86_2_1_[0].ArrowTrace;
  while( true ) {
    cVar1 = gta2::HudArrow_AreBothArrowTracesUsed((HudArrow *)&pArrowTrace[-4].m_vPos1);
    if (((cVar1 == '\0') && ((Gang *)pArrowTrace[-3].m_vPos3 == pGang)) &&
       (*(int *)(pArrowTrace->field0_0x0 + 0x10) != 5)) break;
    iVar2 = iVar2 + 1;
    pArrowTrace = (ArrowTrace *)&pArrowTrace[3].m_nType;
    if (0x10 < iVar2) {
      return 0;
    }
  }
  return 1;
}


// 0x004c85d0: HudArrow::sub_4C85D0
// IDA: HudArrow::sub_4C85D0
// Ghidra: HudArrow::FUN_004c85d0
void gta2::HudArrow_sub_4C85D0(HudArrow *self)
{
  char cVar1;
  byte bVar2;
  int iVar3;
  int *piVar4;
  
  iVar3 = 0x11;
  piVar4 = &self->S86_2_1_[0].field25_0x28;
  do {
    cVar1 = gta2::HudArrow_AreBothArrowTracesUsed((HudArrow *)(piVar4 + -10));
    if (((cVar1 == '\0') && ((Gang *)*piVar4 != NULL)) &&
       (((ArrowTrace *)piVar4[0x14])->m_nType == 5)) {
      bVar2 = gta2::HudArrow_sub_4C8590(self,(Gang *)*piVar4);
      if (bVar2 == 0) {
        FUN_00476880((HudArrow *)(piVar4 + -10));
      }
    }
    piVar4 = piVar4 + 0x1f;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}


// 0x004c8620: HudArrow::sub_4C8620
// IDA: HudArrow::sub_4C8620
// Ghidra: ---
void gta2::HudArrow_sub_4C8620(HudArrow *self)
{
  char *v1; // esi
  int v2; // edi

  v1 = &self->S86_2_1_[0].field_2E;
  v2 = 17;
  do
  {
    if ( *v1 )
    {
      gta2::sub_476880(v1 - 46);
      *v1 = 0;
    }
    v1 += 124;
    --v2;
  }
  while ( v2 );
}


// 0x004c8650: HudArrow::sub_4C8650
// IDA: HudArrow::sub_4C8650
// Ghidra: FUN_004c8650
HudArrow * gta2::HudArrow_sub_4C8650(HudArrow *param_1,int param_2,int param_3)
{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    cVar1 = gta2::HudArrow_AreBothArrowTracesUsed(param_1);
    if (((cVar1 == '\0') && (param_1->S86_2_1_[0].field25_0x28 == param_2)) &&
       (*(int *)&param_1->S86_2_1_[0].field_0x20 == param_3)) break;
    iVar2 = iVar2 + 1;
    param_1 = (HudArrow *)(param_1->S86_2_1_ + 1);
    if (0x10 < iVar2) {
      return NULL;
    }
  }
  return param_1;
}


// 0x004ca610: HudArrow::sub_4CA610
// IDA: HudArrow::sub_4CA610
// Ghidra: ---
__int16 gta2::HudArrow_sub_4CA610(HudArrow *self)
{
  struct HudArrow *v2; // ecx
  __int16 result; // ax

  *(_DWORD *)&self->S86_2_1_[0].field_10 = unk_67302C.FirstElement;
  *(_DWORD *)&self->S86_2_1_[0].field_14 = unk_672FAC;
  gta2::HudArrow_SetArrowType(self, 4u);
  gta2::HudArrow_SetSpriteID(v2, 0);
  self->S86_2_1_[0].Gang = 0;
  self->S86_2_1_[0].ArrowVisible = 1;
  self->S86_2_1_[0].m_bVisible = 0;
  return result;
}


// 0x004ca650: HudArrow::sub_4CA650
// IDA: HudArrow::sub_4CA650
// Ghidra: ---
int gta2::HudArrow_sub_4CA650(HudArrow *self)
{
  return gta2::ArrowTrace_sub_4C7CC0(&self->S86_2_1_[0].m_ArrowTrace, (int *)&self->S86_2_1_[0].Gang->inUse);
}


// 0x004ca770: HudArrow::sub_4CA770
// IDA: HudArrow::sub_4CA770
// Ghidra: HudArrow::FUN_004ca770
byte gta2::HudArrow_sub_4CA770(HudArrow *self)
{
  char cVar1;
  byte ID;
  struct Gang *pGang1;
  int iVar2;
  struct HudArrow *pHudArrow;
  struct Gang *pGang;
  Player *pPlayer;
  
  pGang = (Gang *)self->S86_2_1_[0].field25_0x28;
  if (pGang == NULL) {
    return 1;
  }
  pHudArrow = &gHud->HudArrow_;
  cVar1 = gta2::HudArrow_Clear(pHudArrow);
  if (cVar1 != '\0') {
    if (gShowAllArrows != 0) {
      return 1;
    }
    ID = gta2::MissionManager_MissionManager_1(gMissionManager);
    if (ID == 0) {
      pPlayer = gGame->PlayerMain;
      pGang1 = (Gang *)gta2::Player_GetRespect(pPlayer);
      if ((pGang1 != NULL) && (iVar2 = gta2::Player_sub_4C7340(pPlayer), iVar2 != 0)) {
        pGang1 = NULL;
      }
      if ((self->S86_2_1_[0].ArrowTrace)->m_nType == 5) {
        if (pGang1 == pGang) {
          ID = gta2::HudArrow_sub_4C8470(pHudArrow,self);
          if (ID == 0) {
            return 1;
          }
          return 0;
        }
        if (pGang1 == NULL) {
          return 1;
        }
        ID = gta2::HudArrow_sub_4C8590(pHudArrow,pGang1);
        if (ID == 0) {
          return 1;
        }
        return 0;
      }
      if (pGang1 == pGang) {
        ID = gta2::Player_GetID(pPlayer);
        cVar1 = gta2::Gang_GetRespectForPlayer(pGang,ID);
        if (self->S86_2_1_[0].m_bVisible <= cVar1) {
          pHudArrow = (HudArrow *)(gHud->HudArrow_).field5_0x840;
          if (pHudArrow == NULL) {
            return 1;
          }
          if (pHudArrow == self) {
            return 1;
          }
        }
      }
    }
  }
  return 0;
}


// 0x004ca860: HudArrow::sub_4CA860
// IDA: HudArrow::sub_4CA860
// Ghidra: HudArrow::FUN_004ca860
byte gta2::HudArrow_sub_4CA860(HudArrow *self)
{
  byte bVar1;
  
  bVar1 = gta2::HudArrow_MainLogic(self);
  if (bVar1 == 0) {
    bVar1 = gta2::HudArrow_sub_4CA770(self);
    self->S86_2_1_[0].ArrowVisible = (bool)bVar1;
    if ((bool)bVar1 != false) {
      gta2::HudArrow_Draw(self);
      return bVar1;
    }
  }
  return bVar1;
}


// 0x004ca890: HudArrow::sub_4CA890
// IDA: HudArrow::sub_4CA890
// Ghidra: ---
void gta2::HudArrow_sub_4CA890(HudArrow *self)
{
  struct HudArrow *v2; // esi
  int v3; // ebx

  gta2::HudArrow_sub_4C8540(self);
  v2 = self;
  v3 = 17;
  do
  {
    if ( !gta2::HudArrow_AreBothArrowTracesUsed(v2) )
      gta2::HudArrow_sub_4CA860(v2);
    v2 = (HudArrow *)((char *)v2 + 124);
    --v3;
  }
  while ( v3 );
  if ( self->field_844 )
  {
    gta2::HudArrow_sub_4C85D0(self);
    self->field_844 = 0;
  }
}


// 0x004ca8e0: HudArrow::GetHudArrow
// IDA: HudArrow::GetHudArrow
// Ghidra: ---
HudArrow * gta2::HudArrow_GetHudArrow(HudArrow *self)
{
  struct HudArrow *v1; // esi
  int v3; // [esp+4h] [ebp-4h] BYREF

  v1 = gta2::HudArrow_sub_4C5E70(self, &v3);
  gta2::HudArrow_sub_4CA610(v1);
  gta2::sub_4C6FF0(v1, (SpriteS1 *)(16 - v3));
  return v1;
}


// 0x004ca910: HudArrow::Update
// IDA: HudArrow::Update
// Ghidra: ---
void gta2::HudArrow_Update(HudArrow *self, int a2)
{
  EventHandler *v2; // ebx
  void *v4; // ebp
  int *v5; // eax
  int *v6; // edi
  int *v7; // eax
  struct Gang *pGang; // edi
  _DWORD *v9; // eax
  _DWORD *v10; // eax
  struct HudArrow *v11; // eax
  struct ArrowTrace *p_m_SecondArrowTrace; // esi
  void *v13; // ecx
  char *pColorArrow; // eax
  char *v15; // edx
  char v16; // cl
  char *NameGang; // eax
  char v18; // cl
  struct HudArrow *HudArrow; // esi
  void *v20; // ecx
  int v21; // ecx
  char v22; // al
  int v23; // [esp-18h] [ebp-38h]
  int v24; // [esp-8h] [ebp-28h] BYREF
  int v25; // [esp-4h] [ebp-24h] BYREF
  int v26; // [esp+0h] [ebp-20h] BYREF
  int v27; // [esp+4h] [ebp-1Ch] BYREF
  EventHandler *pS63; // [esp+Ch] [ebp-14h] BYREF

  v2 = pS63;
  v4 = (void *)gta2::HudArrow_ToggleVisibility(self, v23);
  gta2::S63_sub_4340E0(pS63, &v24);
  v6 = v5;
  gta2::S63_sub_4340D0(v2, &v25);
  pGang = gta2::MapRelatedStruct_sub_465350(gMapRelatedStruct, *v7, *v6);
  if ( !pGang )
  {
    gta2::S63_sub_4340D0(v2, &v26);
    unk_5EA828 = *v9;
    gta2::S63_sub_4340E0(v2, &v27);
    unk_5EA98C = *v10;
    gta2::bitShiftLeft1(&pS63, 0);
    unk_5EA984 = pS63;
    gta2::debug_log(0xFA7u, "user.cpp", 1451);
  }
  v11 = gta2::HudArrow_sub_4C8650(self, pGang, v4);
  if ( v11 )
  {
    p_m_SecondArrowTrace = &v11->S86_2_1_[0].m_SecondArrowTrace;
    if ( !gta2::ArrowTrace_SetDefaultType(&v11->S86_2_1_[0].m_SecondArrowTrace) )
    {
      pColorArrow = (char *)gta2::getColorArrow(v13);
      v15 = (char *)(byte_5EA508 - pColorArrow);
      do
      {
        v16 = *pColorArrow;
        pColorArrow[(_DWORD)v15] = *pColorArrow;
        ++pColorArrow;
      }
      while ( v16 );
      NameGang = pGang->NameGang;
      do
      {
        v18 = *NameGang;
        NameGang[byte_5E9908 - pGang->NameGang] = *NameGang;
        ++NameGang;
      }
      while ( v18 );
      gta2::debug_log(0x1F41u, "user.cpp", 1455);
    }
    gta2::ArrowTrace_sub_476810(p_m_SecondArrowTrace, (int)v2);
  }
  else
  {
    HudArrow = gta2::HudArrow_GetHudArrow(self);
    gta2::HudArrow_ResetParam(HudArrow, (int)v2);
    gta2::HudArrow_SetArrowType(HudArrow, (unsigned int)v4);
    gta2::sub_4C7030(v20, pGang);
    v22 = gta2::sub_4C5F10(v21);
    gta2::HudArrow_Init(HudArrow, v22);
    gta2::HudArrow_SetSpriteID(HudArrow, pGang->NextGang);
  }
}



