#include "gta2_shim.h"

// Module: other, Class: Network
// Functions: 8
// Source: unified (IDA+Ghidra)

// 0x00482050: Network::sub_482050
// IDA: Network::sub_482050
// Ghidra: Network::FUN_00482050
void gta2::Network_sub_482050(struct Network *self)
{
  int iVar1;
  int *pArray;
  
  self->Player_ = NULL;
  self->field2_0x1c = 0;
  pArray = self->array;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pArray = 0;
    pArray = pArray + 1;
  }
  self->field3_0x20 = 0;
  self->field4_0x24 = 0;
  return;
}


// 0x004820c0: Network::sub_4820C0
// IDA: Network::sub_4820C0
// Ghidra: Network::FUN_004820c0
void * gta2::Network_sub_4820C0(struct Network *self)
{
  gta2::Network_sub_482050(self);
  return self;
}


// 0x004820d0: Network::SetCurrentPed
// IDA: Network::SetCurrentPed
// Ghidra: ---
void gta2::Network_SetCurrentPed(struct Network *self, Player *CurrentPed)
{
  struct Player *_CurentPlayer; // eax
  struct Player *pCurrentPlayer; // edi
  struct Ped *Ped; // eax
  struct Ped *ManPed; // eax
  struct Ped *pPed; // eax
  struct HudArrow *pHudArrow; // edi
  wchar_t *v9; // eax

  _CurentPlayer = CurrentPed;
  if ( !CurrentPed )
    _CurentPlayer = gta2::Game_GetPlayer1(gGame);
  self->Player_ = _CurentPlayer;
  gta2::HudArrow_sub_4C8620(&gHud->HudArrow_);
  gta2::Player_RestoreOnFootWeapons(self->Player_);
  gta2::Player_sub_4A5690(self->Player_);
  gta2::Player_SetActivePowerUps(self->Player_);
  pCurrentPlayer = self->Player_;
  if ( gta2::Player_GetPed(self->Player_) )
  {
    Ped = gta2::Player_GetPed(pCurrentPlayer);
    gta2::Ped_DisableInvisibility(Ped);
    ManPed = gta2::Player_GetPed(self->Player_);
    gta2::Ped_sub_435F00(ManPed);
    pPed = gta2::Player_GetPed(self->Player_);
    gta2::Ped_SetMoneyValue(pPed);
  }
  if ( gta2::Player_GetCurrentPlayer(self->Player_) )
  {
    v9 = gta2::Text__Bsearch(gText, "yourit");
    gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v9, 3);
  }
  else
  {
    pHudArrow = gta2::HudArrow_GetHudArrow(&gHud->HudArrow_);
    gta2::ArrowTrace_SetPlayer(&pHudArrow->S86_2_1_[0].m_ArrowTrace, self->Player_);
    if ( self->Player_->MainPed )
      gta2::HudArrow_ArrowTrace(pHudArrow, self->Player_->MainPed);
  }
}


// 0x004822a0: Network::SetSpectateTarget
// IDA: Network::SetSpectateTarget
// Ghidra: ---
void gta2::Network_SetSpectateTarget(struct Network *self, Player *X, Player *a3)
{
  struct Player *Player1; // eax
  struct Player *Player; // edi
  struct Player *v6; // esi
  struct Player *v7; // ebx
  struct Ped *Ped; // eax
  struct Ped *v9; // eax
  struct Player **v10; // eax
  struct Ped *v11; // eax
  struct Player *v12; // eax
  struct SpriteS1 *v13; // eax
  void *v14; // ecx
  struct Ped *v15; // eax
  struct Player *XCoordinate; // eax
  struct SpriteS1 *v17; // eax
  struct S202 *v18; // eax
  struct SpriteS1 *FirstElement; // edi
  struct PublicTransport *v20; // [esp-10h] [ebp-38h]
  struct SpriteS1 *v21; // [esp+4h] [ebp-24h] BYREF
  int Y; // [esp+8h] [ebp-20h] BYREF
  _BYTE v23[28]; // [esp+Ch] [ebp-1Ch] BYREF

  gta2::bitShiftLeft1(&v21, 0xFFFF);
  if ( gta2::Network_IsTimeLimitGame(self) && self->Player_ == X )
  {
    if ( a3 )
    {
      gta2::Network_SetCurrentPed(self, a3);
    }
    else
    {
      Player1 = gta2::Game_GetPlayer1(gGame);
      Player = self->Player_;
      v6 = Player1;
      v7 = 0;
      Ped = gta2::Player_GetPed(self->Player_);
      a3 = *(Player **)gta2::Ped_GetXCoordinate(Ped, (int)&X);
      v9 = gta2::Player_GetPed(Player);
      gta2::Ped_GetYCoordinate(v9, &Y);
      X = *v10;
      if ( v6 )
      {
        do
        {
          if ( v6 != self->Player_ )
          {
            v11 = gta2::Player_GetPed(v6);
            gta2::Ped_GetYCoordinate(v11, (int *)&v23[4]);
            v13 = gta2::Player_sub_401B40(v12, (struct S202 *)v23, (int)&X);
            v20 = (struct PublicTransport *)gta2::sub_403840(v14, (struct Player *)&v23[8], v13);
            v15 = gta2::Player_GetPed(v6);
            XCoordinate = (struct Player *)gta2::Ped_GetXCoordinate(v15, (int)&v23[20]);
            v17 = gta2::Player_sub_401B40(XCoordinate, (struct S202 *)&v23[16], (int)&a3);
            v18 = (struct S202 *)gta2::sub_403840(&v23[24], (struct Player *)&v23[24], v17);
            FirstElement = gta2::S202_sub_401B20(v18, (struct SpriteS1 *)&v23[12], v20)->FirstElement;
            Y = (int)FirstElement;
            if ( gta2::sub_4037E0(&Y) )
            {
              v21 = FirstElement;
              v7 = v6;
            }
          }
          v6 = gta2::Game_GetPlayer(gGame);
        }
        while ( v6 );
        if ( v7 )
          gta2::Network_SetCurrentPed(self, v7);
      }
    }
  }
}


// 0x004c72f0: Network::sub_4C72F0
// IDA: Network::sub_4C72F0
// Ghidra: FUN_004c72f0
void gta2::Network_sub_4C72F0(void *self,undefined2 param_1)
{
  int iVar1;
  
  if (*(int *)((int)self + 0xa4) < 0x4f) {
    *(undefined2 *)((int)self + *(int *)((int)self + 0xa4) * 2 + 2) = param_1;
    iVar1 = *(int *)((int)self + 0xa4) + 1;
    *(int *)((int)self + 0xa4) = iVar1;
    *(undefined2 *)((int)self + iVar1 * 2 + 2) = 0;
  }
  return;
}


// 0x004c7320: Network::sub_4C7320
// IDA: Network::sub_4C7320
// Ghidra: FUN_004c7320
void gta2::Network_sub_4C7320(void *self)
{
  int iVar1;
  
  if (0 < *(int *)((int)self + 0xa4)) {
    iVar1 = *(int *)((int)self + 0xa4) + -1;
    *(int *)((int)self + 0xa4) = iVar1;
    *(undefined2 *)((int)self + iVar1 * 2 + 2) = 0;
  }
  return;
}


// 0x004c7370: Network::FUN_004c7370
// IDA: sub_4C7370
// Ghidra: Network::FUN_004c7370
bool gta2::Network_FUN_004c7370(struct Network *self)
{
  byte bVar1;
  
  bVar1 = gta2::MapGm_get_45E700(&gMapGm);
  return bVar1 != 3;
}


// 0x00535440: Network::sub_4820C0
// IDA: Network::sub_4820C0
// Ghidra: FUN_00535440
void gta2::Network_sub_4820C0(void)
{
  gta2::Network_sub_4820C0((struct Network *)&gNetwork);
  return;
}



