#include "gta2_shim.h"

// Module: other, Class: ArrowTrace
// Functions: 9
// Source: unified (IDA+Ghidra)

// 0x004767c0: ArrowTrace::sub_4767C0
// IDA: ArrowTrace::sub_4767C0
// Ghidra: ---
int gta2::ArrowTrace_sub_4767C0(struct ArrowTrace *self, int a2, int a3, int a4)
{
  int result; // eax

  self->m_vPos = a2;
  result = a4;
  self->m_vPos1 = a3;
  self->m_vPos3 = a4;
  self->m_nType = 1;
  return result;
}


// 0x00476810: ArrowTrace::sub_476810
// IDA: ArrowTrace::sub_476810
// Ghidra: ---
void gta2::ArrowTrace_sub_476810(struct ArrowTrace *self, int a2)
{
  self->m_nType = 4;
  self->field_8 = a2;
}


// 0x00476830: ArrowTrace::sub_476830
// IDA: ArrowTrace::sub_476830
// Ghidra: FUN_00476830
void gta2::ArrowTrace_sub_476830(int param_1)
{
  *(undefined4 *)(param_1 + 0x10) = 0;
  return;
}


// 0x004820a0: ArrowTrace::SetPlayer
// IDA: ArrowTrace::SetPlayer
// Ghidra: ---
void gta2::ArrowTrace_SetPlayer(struct ArrowTrace *self, Player *CurrentPlayer)
{
  self->m_nType = 6;
  self->CurrentPlayer = CurrentPlayer;
}


// 0x004c6f00: ArrowTrace::ArrowTrace
// IDA: ArrowTrace::ArrowTrace
// Ghidra: ---
ArrowTrace * gta2::ArrowTrace_ArrowTrace(struct ArrowTrace *self)
{
  struct ArrowTrace *result; // eax

  result = self;
  self->field_0 = 0;
  self->field_4 = 0;
  self->field_8 = 0;
  self->CurrentPlayer = 0;
  self->m_nType = 0;
  self->field_23 = 0;
  return result;
}


// 0x004c6f20: ArrowTrace::SetDefaultType
// IDA: ArrowTrace::SetDefaultType
// Ghidra: ---
bool gta2::ArrowTrace_SetDefaultType(struct ArrowTrace *self)
{
  return self->m_nType == 0;
}


// 0x004c6f30: ArrowTrace::GetCurrentPlayer
// IDA: ArrowTrace::GetCurrentPlayer
// Ghidra: ---
Player * gta2::ArrowTrace_GetCurrentPlayer(struct ArrowTrace *self)
{
  return self->CurrentPlayer;
}


// 0x004c7cc0: ArrowTrace::sub_4C7CC0
// IDA: ArrowTrace::sub_4C7CC0
// Ghidra: ---
int gta2::ArrowTrace_sub_4C7CC0(struct ArrowTrace *self, int *a2)
{
  int result; // eax

  result = gta2::ArrowTrace_sub_4767C0(self, a2[75], a2[76], a2[77]);
  self->m_nType = 5;
  return result;
}


// 0x004c7cf0: ArrowTrace::MainLogic
// IDA: ArrowTrace::MainLogic
// Ghidra: ---
char gta2::ArrowTrace_MainLogic(struct ArrowTrace *self)
{
  int m_nType; // eax
  struct Player *CurrentPlayer; // edi
  int *v4; // eax
  struct Ped *v5; // edi
  int *v6; // eax
  struct Car *v7; // edi
  struct CameraOrPhysics *pCameraOrPhysics; // eax
  struct SpriteS1 *m_vPos; // [esp-Ch] [ebp-2Ch]
  struct Player *m_vPos1; // [esp-8h] [ebp-28h]
  int X; // [esp+8h] [ebp-18h] BYREF
  int Y; // [esp+Ch] [ebp-14h] BYREF
  int Z; // [esp+10h] [ebp-10h] BYREF
  int v15; // [esp+14h] [ebp-Ch] BYREF
  int v16; // [esp+18h] [ebp-8h] BYREF
  int v17; // [esp+1Ch] [ebp-4h] BYREF

  m_nType = self->m_nType;
  switch ( m_nType )
  {
    case 0:
      return m_nType;
    case 2:
      v5 = (struct Ped *)self->field_0;
      if ( !gta2::Ped_Get_433B40((struct Ped *)self->field_0) )
        goto LABEL_10;
      self->m_vPos = *(_DWORD *)gta2::Ped_GetXCoordinate(v5, (int)&v15);
      gta2::Ped_GetYCoordinate(v5, &v16);
      self->m_vPos1 = *v6;
      self->m_vPos3 = *(_DWORD *)gta2::Ped_GetPositionZ(v5, (int)&v17);
      break;
    case 3:
      v7 = (struct Car *)self->field_4;
      if ( gta2::Car_GetMask(v7) )
        goto LABEL_10;
      gta2::SpriteS1_GetXYZ(v7->CarSprite, &self->m_vPos, &self->m_vPos1, &self->m_vPos3);
      break;
    case 4:
      if ( gta2::sub_4828B0((void *)self->field_8) )
      {
        gta2::SpriteS1_GetXYZ(*(SpriteS1 **)(self->field_8 + 4), &self->m_vPos, &self->m_vPos1, &self->m_vPos3);
      }
      else
      {
        gHud->HudArrow_.field_844 = 1;
LABEL_10:
        gta2::ArrowTrace_sub_476830(self);
      }
      break;
    case 6:
      CurrentPlayer = self->CurrentPlayer;
      if ( !gta2::Player_NextPlayer(CurrentPlayer) )
        goto LABEL_10;
      self->m_vPos = *(_DWORD *)gta2::Ped_GetXCoordinate(CurrentPlayer->MainPed, (int)&X);
      gta2::Ped_GetYCoordinate(CurrentPlayer->MainPed, &Y);
      self->m_vPos1 = *v4;
      self->m_vPos3 = *(_DWORD *)gta2::Ped_GetPositionZ(CurrentPlayer->MainPed, (int)&Z);
      break;
    default:
      break;
  }
  m_vPos1 = (struct Player *)self->m_vPos1;
  m_vPos = (struct SpriteS1 *)self->m_vPos;
  pCameraOrPhysics = gta2::Player_GetMultiPlayerMode(gGame->PlayerMain);
  LOBYTE(m_nType) = gta2::CameraOrPhysics_sub_41E710(pCameraOrPhysics, m_vPos, m_vPos1);
  self->field_23 = m_nType;
  return m_nType;
}



