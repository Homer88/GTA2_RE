#include "gta2_shim.h"

// Module: other, Class: Player
// Functions: 382
// Source: unified (IDA+Ghidra)

// 0x004766a0: Player::GetMultiPlayer
// IDA: Player::GetMultiPlayer
// Ghidra: ---
PlayerStats * gta2::Player_GetMultiPlayer(Player *self)
{
  return (PlayerStats *)gta2::PlayerStats_getMoneyValue((PlayerStats *)&self->MultiPlayer);
}


// 0x004766b0: Player::SetMultiPlayer
// IDA: Player::SetMultiPlayer
// Ghidra: ---
int gta2::Player_SetMultiPlayer(Player *self, int a2)
{
  return gta2::PlayerStats_SetMultiPlayer((PlayerStats *)&self->MultiPlayer, a2);
}


// 0x004766c0: Player::getMoney
// IDA: Player::getMoney
// Ghidra: ---
PlayerStats * gta2::Player_getMoney(Player *self)
{
  return (PlayerStats *)gta2::PlayerStats_getMoneyValue((PlayerStats *)&self->Lives);
}


// 0x004766d0: Player::GetRespect
// IDA: Player::GetRespect
// Ghidra: ---
Gang * gta2::Player_GetRespect(Player *self)
{
  return self->RESPECT->Gang_;
}


// 0x00476700: Player::sub_476700
// IDA: Player::sub_476700
// Ghidra: ---
bool gta2::Player_sub_476700(Player *self)
{
  struct Ped *MainPed; // ecx
  bool result; // al

  result = 0;
  if ( LOBYTE(self->S103_2) )
  {
    if ( self->MoneyValue == 2 )
    {
      MainPed = self->MainPed;
      if ( !MainPed || gta2::Ped_GetState(MainPed) != 54 )
        return 1;
    }
  }
  return result;
}


// 0x00476730: Player::sub_476730
// IDA: Player::sub_476730
// Ghidra: ---
bool gta2::Player_sub_476730(Player *self)
{
  struct Ped *MainPed; // ecx
  bool result; // al

  result = 0;
  if ( LOBYTE(self->S103_2) )
  {
    if ( self->MoneyValue == 2 )
    {
      MainPed = self->MainPed;
      if ( MainPed )
      {
        if ( gta2::Ped_GetState(MainPed) == 54 )
          return 1;
      }
    }
  }
  return result;
}


// 0x004821c0: Player::sub_4821C0
// IDA: Player::sub_4821C0
// Ghidra: Network::FUN_004821c0
void gta2::Player_sub_4821C0(struct Network *self)
{
  byte bVar1;
  struct Ped *pPVar2;
  Car *this_00;
  int iVar3;
  struct Player *this_01;
  undefined4 uVar4;
  undefined *puVar5;
  
  bVar1 = FUN_00482090(self);
  switch(bVar1) {
  case 0:
    uVar4 = 0x6c;
    break;
  case 1:
  case 2:
    goto switchD_004821d7_caseD_1;
  case 3:
    iVar3 = self->field2_0x1c + 1;
    self->field2_0x1c = iVar3;
    if (iVar3 < 0x1e) {
LAB_00482220:
      this_01 = self->Player_;
      if (this_01 != NULL) goto LAB_00482235;
    }
    else {
      self->field2_0x1c = 0;
      if (self->Player_ != NULL) {
        if (_DAT_006626e4 != 0) {
          bVar1 = gta2::Player_GetID(self->Player_);
          self->array[bVar1] = self->array[bVar1] + 1;
        }
        goto LAB_00482220;
      }
    }
    gta2::Network_SetCurrentPlayer(self,NULL);
    this_01 = self->Player_;
    if (this_01 == NULL) {
      return;
    }
LAB_00482235:
    iVar3 = gta2::Player_GetPed(this_01);
    if (iVar3 == 0) {
      return;
    }
    pPVar2 = (Ped *)gta2::Player_GetPed(this_01);
    iVar3 = gta2::Ped_GetCarPlayers(pPVar2);
    if (iVar3 == 0) {
      return;
    }
    puVar5 = &DAT_006653dc;
    iVar3 = 0x11;
    pPVar2 = (Ped *)gta2::Player_GetPed(this_01);
    this_00 = (Car *)gta2::Ped_GetCarPlayers(pPVar2);
    gta2::Car_CollisionOnCar(this_00,iVar3,puVar5);
    return;
  default:
    uVar4 = 0x90;
  }
  gta2::DebugLog(0x431,"multip.cpp",uVar4);
switchD_004821d7_caseD_1:
  return;
}


// 0x00482cc0: Player::sub_482CC0
// IDA: Player::sub_482CC0
// Ghidra: ---
int gta2::Player_sub_482CC0(Player *self, EventHandler *pS63, _DWORD *arg4, int a3)
{
  int result; // eax

  gta2::Player_sub_49ECC0(self);
  *(_DWORD *)&unk_66AD08.S200[0].A = *arg4;
  unk_66AD0C = arg4[1];
  LOBYTE(result) = gta2::Player_sub_4A3A40(self, pS63, a3);
  return result;
}


// 0x0049dd10: Player::sub_49DD10
// IDA: Player::sub_49DD10
// Ghidra: ---
void * gta2::Player_sub_49DD10(void *self)
{
  void *result; // eax
  void *v2; // ecx

  result = (void *)*((_DWORD *)self + 23);
  v2 = (void *)*((_DWORD *)result + 25);
  if ( v2 )
    return gta2::sub_40F900(v2);
  return result;
}


// 0x0049dd20: Player::sub_49DD20
// IDA: Player::sub_49DD20
// Ghidra: ---
void gta2::Player_sub_49DD20(Player *self, _DWORD *a2)
{
  self->field_A0 = *a2;
}


// 0x0049dd30: Player::sub_49DD30
// IDA: Player::sub_49DD30
// Ghidra: Player::FUN_0049dd30
void gta2::Player_sub_49DD30(Player *self)
{
  if (self->CarPlayerPre->Driver != NULL) {
    if (*(int *)&self->field_0xa0 == 1) {
      self->field_0xad = 0xff;
      self->field_0x95 = 0;
      *(undefined1 *)((int)&self->CameraOrPhysics_ + 3) = 1;
      return;
    }
    if (*(int *)&self->field_0xa0 == 2) {
      self->field_0xad = 1;
      self->field_0x95 = 0;
      *(undefined1 *)((int)&self->CameraOrPhysics_ + 3) = 1;
    }
  }
  return;
}


// 0x0049dd80: Player::sub_49DD80
// IDA: Player::sub_49DD80
// Ghidra: ---
bool gta2::Player_sub_49DD80(Player *self)
{
  _DWORD *TrailerCtrl; // eax
  int v2; // eax

  TrailerCtrl = self->sCar1->TrailerCtrl;
  if ( TrailerCtrl )
    LOBYTE(v2) = *(_DWORD *)(*(_DWORD *)(TrailerCtrl[2] + 88) + 152) == 6
              && *(_DWORD *)(*(_DWORD *)(TrailerCtrl[3] + 88) + 152) == 6;
  else
    return self->State == 6;
  return v2;
}


// 0x0049ddc0: Player::FUN_0049ddc0
// IDA: sub_49DDC0
// Ghidra: Player::FUN_0049ddc0
byte gta2::Player_FUN_0049ddc0(Player *self)
{
  void *pvVar1;
  int iVar2;
  
  pvVar1 = self->CarPlayerPre->S___;
  if (pvVar1 == NULL) {
    return *(byte *)((int)&self->CameraOrPhysics_ + 1);
  }
  iVar2 = *(int *)(*(int *)((int)pvVar1 + 8) + 0x58);
  if (iVar2 != 0) {
    return *(byte *)(iVar2 + 0x91);
  }
  return 0;
}


// 0x0049ddf0: Player::sub_49DDF0
// IDA: Player::sub_49DDF0
// Ghidra: Player::FUN_0049ddf0
byte gta2::Player_sub_49DDF0(Player *self)
{
  char cVar1;
  void *pvVar2;
  int iVar3;
  
  pvVar2 = self->CarPlayerPre->S___;
  if (pvVar2 == NULL) {
    if (*(char *)((int)&self->CameraOrPhysics_ + 3) != '\0') {
      return 1;
    }
    cVar1 = self->ControlMode;
  }
  else {
    iVar3 = *(int *)(*(int *)((int)pvVar2 + 8) + 0x58);
    if (iVar3 == 0) {
      return 0;
    }
    if (*(char *)(iVar3 + 0x93) != '\0') {
      return 1;
    }
    cVar1 = *(char *)(iVar3 + 0x94);
  }
  if (cVar1 == '\0') {
    return 0;
  }
  return 1;
}


// 0x0049de40: Player::sub_49DE40
// IDA: Player::sub_49DE40
// Ghidra: ---
_DWORD * gta2::Player_sub_49DE40(Player *self)
{
  Car *sCar1; // eax
  _DWORD *result; // eax

  self->S103_5 = (S103 *)unk_66ACD0;
  self->RESPECT = (Gangs *)unk_66ACD4;
  self->field_6C = MEMORY[0x66AC88];
  LOWORD(self->field_58) = stru_66AC54;
  self->field_38 = (S103 *)MEMORY[0x66AC8C];
  self->field_3C = MEMORY[0x66AC90];
  *(_DWORD *)&self->Up = unk_66ABC4;
  sCar1 = self->sCar1;
  self->MultiPlayerMode = unk_66ABC8;
  result = sCar1->TrailerCtrl;
  if ( result )
  {
    result = *(_DWORD **)(result[3] + 88);
    result[12] = MEMORY[0x66AD68];
    result[13] = MEMORY[0x66AD6C];
    result[27] = unk_66AB98;
    *((_WORD *)result + 44) = *(_WORD *)&MEMORY[0x66AE44].S200[0].A;
    result[14] = unk_66AE54;
    result[15] = unk_66AE58;
    result[28] = MEMORY[0x66AC7C];
    result[26] = unk_66AC0C;
  }
  return result;
}


// 0x0049def0: Player::sub_49DEF0
// IDA: Player::sub_49DEF0
// Ghidra: ---
_DWORD * gta2::Player_sub_49DEF0(Player *self)
{
  _DWORD *result; // eax
  int v2; // eax

  unk_66ACD0 = self->S103_5;
  unk_66ACD4 = self->RESPECT;
  MEMORY[0x66AC88] = self->field_6C;
  stru_66AC54 = self->field_58;
  MEMORY[0x66AC8C] = self->field_38;
  MEMORY[0x66AC90] = self->field_3C;
  unk_66ABC4 = *(_DWORD *)&self->Up;
  unk_66ABC8 = self->MultiPlayerMode;
  result = self->sCar1->TrailerCtrl;
  if ( result )
  {
    v2 = *(_DWORD *)(result[3] + 88);
    MEMORY[0x66AD68] = *(_DWORD *)(v2 + 48);
    MEMORY[0x66AD6C] = *(_DWORD *)(v2 + 52);
    unk_66AB98 = *(_DWORD *)(v2 + 108);
    *(_WORD *)&MEMORY[0x66AE44].S200[0].A = *(_WORD *)(v2 + 88);
    unk_66AE54 = *(_DWORD *)(v2 + 56);
    unk_66AE58 = *(_DWORD *)(v2 + 60);
    MEMORY[0x66AC7C] = *(_DWORD *)(v2 + 112);
    result = *(_DWORD **)(v2 + 104);
    unk_66AC0C = result;
  }
  return result;
}


// 0x0049df90: Player::sub_49DF90
// IDA: Player::sub_49DF90
// Ghidra: FUN_0049df90
void gta2::Player_sub_49DF90(int param_1)
{
  int iVar1;
  
  *(undefined4 *)(param_1 + 0x30) = _DAT_0066abb8;
  *(undefined4 *)(param_1 + 0x34) = _DAT_0066abbc;
  *(undefined4 *)(param_1 + 0x6c) = _DAT_0066ac00;
  *(undefined2 *)(param_1 + 0x58) = _DAT_0066ad3c;
  *(undefined4 *)(param_1 + 0x38) = _DAT_0066ad20;
  *(undefined4 *)(param_1 + 0x3c) = _DAT_0066ad24;
  *(undefined4 *)(param_1 + 0x70) = _DAT_0066af68;
  *(undefined4 *)(param_1 + 0x68) = _DAT_0066b028;
  iVar1 = *(int *)(*(int *)(param_1 + 0x5c) + 100);
  if (iVar1 != 0) {
    iVar1 = *(int *)(*(int *)(iVar1 + 0xc) + 0x58);
    *(undefined4 *)(iVar1 + 0x30) = _DAT_0066acc0;
    *(undefined4 *)(iVar1 + 0x34) = _DAT_0066acc4;
    *(undefined4 *)(iVar1 + 0x6c) = _DAT_0066ac70;
    *(undefined2 *)(iVar1 + 0x58) = _DAT_0066ade0;
    *(undefined4 *)(iVar1 + 0x38) = _DAT_0066afe8;
    *(undefined4 *)(iVar1 + 0x3c) = _DAT_0066afec;
    *(undefined4 *)(iVar1 + 0x70) = _DAT_0066ac2c;
    *(undefined4 *)(iVar1 + 0x68) = _DAT_0066adb8;
  }
  return;
}


// 0x0049e040: Player::sub_49E040
// IDA: Player::sub_49E040
// Ghidra: ---
_DWORD * gta2::Player_sub_49E040(Player *self)
{
  _DWORD *result; // eax
  int v2; // eax

  unk_66ABB8.CurrentElement = (int)self->S103_5;
  unk_66ABBC.CurrentElement = (int)self->RESPECT;
  unk_66AC00.CurrentElement = self->field_6C;
  stru_66AD3C = self->field_58;
  unk_66AD20 = self->field_38;
  unk_66AD24 = self->field_3C;
  unk_66AF68 = *(_DWORD *)&self->Up;
  unk_66B028 = self->MultiPlayerMode;
  result = self->sCar1->TrailerCtrl;
  if ( result )
  {
    v2 = *(_DWORD *)(result[3] + 88);
    unk_66ACC0.CurrentPlayer = *(Player **)(v2 + 48);
    unk_66ACC4.CurrentPlayer = *(Player **)(v2 + 52);
    MEMORY[0x66AC70].CurrentElement = *(_DWORD *)(v2 + 108);
    stru_66ADE0 = *(_WORD *)(v2 + 88);
    unk_66AFE8 = *(_DWORD *)(v2 + 56);
    unk_66AFEC = *(_DWORD *)(v2 + 60);
    unk_66AC2C = *(_DWORD *)(v2 + 112);
    result = *(_DWORD **)(v2 + 104);
    unk_66ADB8 = result;
  }
  return result;
}


// 0x0049e270: Player::sub_49E270
// IDA: Player::sub_49E270
// Ghidra: ---
char gta2::Player_sub_49E270(Player *self)
{
  char v2; // bl
  _DWORD *TrailerCtrl; // eax

  gCarSystemManager->bool_ = 0;
  v2 = gta2::S56_sub_447480(gCheckpoint2, self->sCar1->CarSprite);
  TrailerCtrl = self->sCar1->TrailerCtrl;
  if ( TrailerCtrl )
    return gta2::S56_sub_447480(gCheckpoint2, *(void **)(TrailerCtrl[3] + 80)) | v2;
  return v2;
}


// 0x0049e330: Player::sub_49E330
// IDA: Player::sub_49E330
// Ghidra: Player::FUN_0049e330
void gta2::Player_sub_49E330(Player *self,undefined4 param_1)
{
  int *piVar1;
  struct Player *local_4;
  
  local_4 = self;
  piVar1 = (int *)gta2::WorldCoordinateToScreenCoord(&param_1,&local_4,_DAT_0066ab78);
  UseAmmo(&self->Tango1,piVar1);
  return;
}


// 0x0049e450: Player::FUN_0049e450
// IDA: sub_49E450
// Ghidra: Player::FUN_0049e450
byte gta2::Player_FUN_0049e450(Player *self)
{
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  
  bVar1 = gta2::Player_IsCurrentPlayer(self,(Player *)&DAT_0066acdc);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    bVar1 = gta2::Player_IsCurrentPlayer((Player *)&self->Player_,(Player *)&DAT_0066acdc);
    if (CONCAT31(extraout_var_00,bVar1) == 0) {
      return 0;
    }
  }
  return 1;
}


// 0x0049e480: Player::FUN_0049e480
// IDA: sub_49E480
// Ghidra: Player::FUN_0049e480
void gta2::Player_FUN_0049e480(Player *self,SpriteS1 *param_1)
{
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  struct Player **this_00;
  Matrix3D *pSpriteS1;
  
  bVar1 = gta2::Player_sub_40CE70(self,(Player *)&DAT_0066acdc);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)self,param_1);
    if (CONCAT31(extraout_var_01,bVar1) != 0) {
      self->CurrentPlayer = (Player *)param_1->FirstElement;
    }
  }
  else {
    bVar1 = gta2::Car_sub_403800((Car *)self,(int *)param_1);
    if (CONCAT31(extraout_var_00,bVar1) != 0) {
      self->CurrentPlayer = (Player *)param_1->FirstElement;
    }
  }
  this_00 = &self->Player_;
  bVar1 = gta2::Player_sub_40CE70((Player *)this_00,(Player *)&DAT_0066acdc);
  pSpriteS1 = param_1->Matrix3DArray;
  if (CONCAT31(extraout_var_02,bVar1) == 0) {
    bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)this_00,(SpriteS1 *)pSpriteS1);
    if (CONCAT31(extraout_var_04,bVar1) != 0) {
      *this_00 = (Player *)pSpriteS1->SpriteS1_;
    }
  }
  else {
    bVar1 = gta2::Car_sub_403800((Car *)this_00,(int *)pSpriteS1);
    if (CONCAT31(extraout_var_03,bVar1) != 0) {
      *this_00 = (Player *)pSpriteS1->SpriteS1_;
      return;
    }
  }
  return;
}


// 0x0049e650: Player::sub_49E650
// IDA: Player::sub_49E650
// Ghidra: FUN_0049e650
void * gta2::Player_sub_49E650(int param_1,void *param_2,void *param_3)
{
  undefined4 *puVar1;
  short *psVar2;
  GlassInfo *pGVar3;
  void *pvVar4;
  short *unaff_ESI;
  void *unaff_EDI;
  Car *local_18;
  struct Ped *local_14;
  SpawnPoint *local_10 [2];
  undefined1 local_8 [8];
  
  puVar1 = (undefined4 *)
           FUN_0040f600(param_3,local_8,(GlassInfo *)(_DAT_0066ab78 + 0xc));
  local_18 = (Car *)*puVar1;
  local_14 = *(Ped **)(puVar1 + 1);
  FUN_0040f6b0(&local_18,(GlassInfo *)(param_1 + 0x58));
  FUN_0040f680(&local_18,param_1 + 0x30);
  local_10[0] = (SpawnPoint *)*puVar1;
  local_10[1] = (SpawnPoint *)puVar1[1];
  psVar2 = (short *)FUN_0040f540(&param_3,param_1 + 0x74);
  pGVar3 = (GlassInfo *)
           gta2::sub_40E5A0((CarSystemManager *)(param_1 + 0x58),
                      (Ped *)&stack0xffffffe6,psVar2,unaff_EDI,unaff_ESI);
  FUN_0040f6b0(local_10,pGVar3);
  pvVar4 = FUN_0040f5c0((void *)(param_1 + 0x30),local_8,
                        (SpriteS1 *)(param_1 + 0x40));
  FUN_0040f680(local_10,(int)pvVar4);
  FUN_0040f600(local_10,param_2,(GlassInfo *)&local_18);
  return param_2;
}


// 0x0049e820: Player::sub_49E820
// IDA: Player::sub_49E820
// Ghidra: ---
bool gta2::Player_sub_49E820(Player *self)
{
  return *(_BYTE *)(unk_66AB70 + 1) && gta2::Player_sub_40CE70((Player *)&self->field_60, &unk_66AFBC);
}


// 0x0049e950: Player::sub_49E950
// IDA: Player::sub_49E950
// Ghidra: FUN_0049e950
void gta2::Player_sub_49E950(void *self)
{
  if (*(char *)((int)self + 0x93) != '\0') {
    gta2::FUN_0049e790(self);
    return;
  }
  if (*(char *)((int)self + 0x94) != '\0') {
    gta2::FUN_0049e7c0(self);
    return;
  }
  gta2::FUN_0049e7f0(self);
  return;
}


// 0x0049e980: Player::sub_49E980
// IDA: Player::sub_49E980
// Ghidra: FUN_0049e980
void gta2::Player_sub_49E980(int param_1)
{
  Car *self;
  bool bVar1;
  undefined3 extraout_var;
  undefined4 *puVar2;
  int local_4;
  
  if (((*(char *)(param_1 + 0x91) != '\0') && (*(int *)(param_1 + 0x98) != 7))
     && (*(int *)(param_1 + 0x98) != 8)) {
    self = (Car *)(param_1 + 100);
    local_4 = param_1;
    gta2::Player_sub_40E530((Point2D *)self,(int *)&DAT_0066af48);
    bVar1 = gta2::Car_sub_403800(self,(int *)&DAT_0066ad88);
    if (CONCAT31(extraout_var,bVar1) != 0) {
      self->Turret = _DAT_0066ad88;
    }
    puVar2 = (undefined4 *)
             gta2::WorldCoordinateToScreenCoord
                       ((void *)(_DAT_0066ab70 + 0x10),&local_4,(int *)self);
    _DAT_0066ac28 = *puVar2;
    return;
  }
  *(undefined4 *)(param_1 + 100) = _DAT_0066abe4;
  _DAT_0066ac28 = _DAT_0066acdc;
  return;
}


// 0x0049ea00: Player::FUN_0049ea00
// IDA: sub_49EA00
// Ghidra: Player::FUN_0049ea00
void * gta2::Player_FUN_0049ea00(Player *self,Player *pPlayer)
{
  if (self->CarPlayerPre->PhysicsBitmask == 2) {
    pPlayer->CurrentPlayer = _DAT_0066ad5c;
    return pPlayer;
  }
  pPlayer->CurrentPlayer = _DAT_0066acdc;
  return pPlayer;
}


// 0x0049ea60: Player::sub_49EA60
// IDA: Player::sub_49EA60
// Ghidra: ---
void gta2::Player_sub_49EA60(Player *self)
{
  gta2::Weapon_UseAmmo((Weapon *)&self->prevWeapon, &stru_66ADE0.field_2C);
}


// 0x0049ea70: Player::sub_49EA70
// IDA: Player::sub_49EA70
// Ghidra: ---
Tango * gta2::Player_sub_49EA70(Player *self)
{
  void *v2; // ecx
  struct Player *v3; // eax
  int v4; // eax
  struct Player *v5; // eax
  int v6; // eax
  Tango *result; // eax
  S900 *v8; // eax
  Tango *p_DeathReason; // ecx
  Tango *p_prevWeapon; // esi
  struct Player *v11; // eax
  int v12; // eax
  void *v13; // ecx
  struct Player *v14; // eax
  int v15; // eax
  S900 *v16; // eax
  Tango *v17; // ecx
  Tango *v18; // esi
  S103 **p_S103_4; // [esp-8h] [ebp-18h]
  int v20; // [esp+Ch] [ebp-4h] BYREF

  p_S103_4 = &self->S103_4;
  if ( gta2::Player_sub_49DD80(self) )
  {
    v3 = (Player *)gta2::sub_403840(v2, (Player *)&v20, p_S103_4);
    LOBYTE(v4) = gta2::Player_CheckCondition(v3, &unk_66AF84);
    if ( v4
      && (v5 = (Player *)gta2::sub_403840(&self->DeathReason, (Player *)&v20, &self->DeathReason),
          LOBYTE(v6) = gta2::Player_CheckCondition(v5, &unk_66AF84),
          v6) )
    {
      return gta2::Tango_sub_49E3A0((Tango *)&self->S103_4, (int *)&stru_66AD3C.CarType);
    }
    else
    {
      v8 = (S900 *)gta2::sub_401C80(&self->field_58, (Ped *)&v20);
      gta2::Tango_sub_40F6B0((Tango *)&self->S103_4, v8);
      gta2::Tango_sub_41E0D0((Tango *)&self->S103_4, (int *)&stru_66AD3C.CarType);
      p_DeathReason = (Tango *)&self->DeathReason;
      if ( self->sCar1->TrailerCtrl )
        gta2::Tango_sub_41E0D0(p_DeathReason, &stru_66ADE0.field_38);
      else
        gta2::Tango_sub_41E0D0(p_DeathReason, &dword_66ABC0);
      gta2::Tango_sub_40F6B0((Tango *)&self->S103_4, (S900 *)&self->field_58);
      p_prevWeapon = (Tango *)&self->prevWeapon;
      result = (Tango *)gta2::Radar_AddBlip(p_prevWeapon, (SpriteS1 *)&v20, (PublicTransport *)&unk_66AF50)->FirstElement;
      p_prevWeapon->field = (int)result;
    }
  }
  else
  {
    v11 = (Player *)gta2::sub_403840(&v20, (Player *)&v20, p_S103_4);
    LOBYTE(v12) = gta2::Player_CheckCondition(v11, &unk_66AF84);
    if ( v12
      && (v14 = (Player *)gta2::sub_403840(v13, (Player *)&v20, &self->DeathReason),
          LOBYTE(v15) = gta2::Player_CheckCondition(v14, &unk_66AF84),
          v15) )
    {
      return gta2::Tango_sub_49E3A0((Tango *)&self->S103_4, &dword_66B014);
    }
    else
    {
      v16 = (S900 *)gta2::sub_401C80(&self->field_58, (Ped *)&v20);
      gta2::Tango_sub_40F6B0((Tango *)&self->S103_4, v16);
      gta2::Tango_sub_41E0D0((Tango *)&self->S103_4, &dword_66B014);
      v17 = (Tango *)&self->DeathReason;
      if ( self->sCar1->TrailerCtrl )
        gta2::Tango_sub_41E0D0(v17, &dword_66AD04);
      else
        gta2::Tango_sub_41E0D0(v17, &dword_66AFF0);
      gta2::Tango_sub_40F6B0((Tango *)&self->S103_4, (S900 *)&self->field_58);
      v18 = (Tango *)&self->prevWeapon;
      result = (Tango *)gta2::Radar_AddBlip(v18, (SpriteS1 *)&v20, (PublicTransport *)&unk_66AD10);
      v18->field = result->field;
    }
  }
  return result;
}


// 0x0049ec80: Player::sub_49EC80
// IDA: Player::sub_49EC80
// Ghidra: FUN_0049ec80
void gta2::Player_sub_49EC80(void *self)
{
  byte bVar1;
  
  bVar1 = gta2::Car_sub_4220A0(*(Car **)((int)self + 0x5c));
  _DAT_0066ab70 = gta2::CarEngines_sub_4327E0(gCarEngines,bVar1);
  return;
}


// 0x0049eca0: Player::sub_49ECA0
// IDA: Player::sub_49ECA0
// Ghidra: Player::FUN_0049eca0
void gta2::Player_sub_49ECA0(Player *self)
{
  byte index;
  
  index = gta2::Car_sub_4220A0(self->CarPlayerPre);
  _DAT_0066ab78 = gta2::CarEngines_GetEngineState(gCarEngines,index);
  return;
}


// 0x0049ecc0: Player::sub_49ECC0
// IDA: Player::sub_49ECC0
// Ghidra: ---
Car * gta2::Player_sub_49ECC0(Player *self)
{
  Car *result; // eax
  char Index; // [esp+0h] [ebp-4h]

  Index = gta2::Car_sub_4220A0(self->sCar1);
  unk_66AB78 = gta2::CarEngines_GetEngineState(gCarEngines, Index);
  result = gta2::CarEngines_sub_4327E0(gCarEngines, Index);
  unk_66AB70 = result;
  return result;
}


// 0x0049ed00: Player::sub_49ED00
// IDA: Player::sub_49ED00
// Ghidra: ---
S103 ** gta2::Player_sub_49ED00(Player *self)
{
  int v2; // edx
  S103 **result; // eax
  int a3[2]; // [esp+4h] [ebp-10h] BYREF
  char v5[8]; // [esp+Ch] [ebp-8h] BYREF

  v2 = *(_DWORD *)(unk_66AB78 + 16);
  a3[0] = *(_DWORD *)(unk_66AB78 + 12);
  a3[1] = v2;
  gta2::Tango_sub_40F760((Tango *)a3);
  gta2::Tango_sub_40F6B0((Tango *)a3, (S900 *)&self->field_58);
  result = (S103 **)gta2::S103_sub_40F5C0((S103 *)&self->S103_5, v5, a3);
  self->field_38 = *result;
  self->field_3C = (int)result[1];
  return result;
}


// 0x0049ed60: Player::sub_49ED60
// IDA: Player::sub_49ED60
// Ghidra: ---
_DWORD * gta2::Player_sub_49ED60(Player *self)
{
  char pIndex; // al
  int EngineState; // eax
  int v4; // edx
  _DWORD *result; // eax
  int a3[2]; // [esp+4h] [ebp-10h] BYREF
  char v7[8]; // [esp+Ch] [ebp-8h] BYREF

  pIndex = gta2::Car_sub_4220A0(self->sCar1);
  EngineState = gta2::CarEngines_GetEngineState(gCarEngines, pIndex);
  v4 = *(_DWORD *)(EngineState + 16);
  a3[0] = *(_DWORD *)(EngineState + 12);
  a3[1] = v4;
  gta2::Tango_sub_40F6B0((Tango *)a3, (S900 *)&self->field_58);
  result = gta2::S103_sub_40F5C0((S103 *)&self->field_38, v7, a3);
  self->S103_5 = (S103 *)*result;
  self->RESPECT = (Gangs *)result[1];
  return result;
}


// 0x0049edc0: Player::sub_49EDC0
// IDA: Player::sub_49EDC0
// Ghidra: ---
S103 ** gta2::Player_sub_49EDC0(Player *self)
{
  int v2; // edx
  S103 **result; // eax
  Tango *pTango; // [esp+4h] [ebp-10h] BYREF
  int v5; // [esp+8h] [ebp-Ch]
  char v6[8]; // [esp+Ch] [ebp-8h] BYREF

  v2 = *(_DWORD *)(unk_66AB78 + 16);
  pTango = *(Tango **)(unk_66AB78 + 12);
  v5 = v2;
  gta2::Tango_sub_40F6B0((Tango *)&pTango, (S900 *)&self->field_58);
  result = (S103 **)gta2::S103_sub_40F5C0((S103 *)&self->field_38, v6, &pTango);
  self->S103_5 = *result;
  self->RESPECT = (Gangs *)result[1];
  return result;
}


// 0x0049ee10: Player::sub_49EE10
// IDA: Player::sub_49EE10
// Ghidra: ---
_DWORD * gta2::Player_sub_49EE10(Player *self, SpriteS1 *pSpriteS1)
{
  SpriteS1 *v2; // eax

  v2 = pSpriteS1;
  self->field_38 = (S103 *)pSpriteS1->S3_arr5031[0].PositionX;
  self->field_3C = v2->S3_arr5031[0].PositionY;
  self->field_6C = v2->S3_arr5031[0].PositionZ;
  LOWORD(self->field_58) = v2->FirstElement;
  gta2::bitShiftLeft1(&pSpriteS1, 0);
  *(_DWORD *)&self->Forward = pSpriteS1;
  return gta2::Player_sub_49ED60(self);
}


// 0x0049ee80: Player::sub_49EE80
// IDA: Player::sub_49EE80
// Ghidra: ---
SpriteS3 * gta2::Player_sub_49EE80(Player *self)
{
  SpriteS1 *CarSprite; // edi
  CarSystemManager *v3; // ecx

  CarSprite = self->sCar1->CarSprite;
  gta2::SpriteS1_sub_420600(CarSprite, (int)self->field_38, self->field_3C, self->field_6C);
  LOWORD(v3) = self->field_58;
  return gta2::SpriteS1_SetRotation(CarSprite, v3);
}


// 0x0049eeb0: Player::sub_49EEB0
// IDA: Player::sub_49EEB0
// Ghidra: ---
SpriteS1 * gta2::Player_sub_49EEB0(Player *self)
{
  SpriteS1 *result; // eax

  gta2::Player_sub_49EE80(self);
  result = (SpriteS1 *)self->sCar1->TrailerCtrl;
  if ( result )
    return gta2::Player_sub_49EE80((Player *)result->S3_arr5031[0].SpriteS3->S39_Arr48[4].field_8);
  return result;
}


// 0x0049eed0: Player::FUN_0049eed0
// IDA: ---
// Ghidra: Player::FUN_0049eed0
byte gta2::Player_FUN_0049eed0(Player *self)
{
  bool bVar1;
  Point2D *this_00;
  undefined3 extraout_var;
  SpriteS1 *pSpriteS1;
  struct Player *local_4;
  
  pSpriteS1 = (SpriteS1 *)&DAT_0066afc8;
  local_4 = self;
  this_00 = (Point2D *)
            gta2::Player_sub_41E260((Player *)&self->S103_,(int *)&local_4);
  bVar1 = gta2::Point2D_FUN_004037e0(this_00,pSpriteS1);
  return CONCAT31(extraout_var,bVar1) != 0;
}


// 0x0049ef50: Player::sub_49EF50
// IDA: Player::sub_49EF50
// Ghidra: ---
unsigned int gta2::Player_sub_49EF50(Player *self, int a2)
{
  unsigned int result; // eax

  result = a2 + gta2::General_GetCycle(gGeneral);
  if ( result > *(_DWORD *)&self->Rotate )
    *(_DWORD *)&self->Rotate = result;
  return result;
}


// 0x0049ef80: Player::sub_49EF80
// IDA: Player::sub_49EF80
// Ghidra: Player::FUN_0049ef80
byte gta2::Player_sub_49EF80(Player *self)
{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  
  iVar2 = FUN_00420360(&self->S103_);
  if (iVar2 != 0) {
    bVar1 = gta2::Player_IsCurrentPlayer((Player *)&self->DeathReason,(Player *)&DAT_0066acdc);
    if (CONCAT31(extraout_var,bVar1) != 0) {
      return 1;
    }
  }
  return 0;
}


// 0x0049f010: Player::sub_49F010
// IDA: Player::sub_49F010
// Ghidra: ---
char gta2::Player_sub_49F010(Player *self)
{
  char result; // al
  int v3; // edi
  int v4; // eax
  void *v5; // eax
  double v6; // st7
  double v7; // st7
  int v8; // [esp+8h] [ebp-10h]
  int v9; // [esp+8h] [ebp-10h]
  char v10[4]; // [esp+14h] [ebp-4h] BYREF

  result = do_show_instruments;
  if ( do_show_instruments )
  {
    gta2::Player_sub_49ECC0(self);
    gta2::Player_sub_41E260((Player *)&self->S103_4, (int)v10);
    v3 = unk_66AB70;
    if ( gta2::Car_sub_403800((Car *)v10, unk_66AB70 + 68) )
      v4 = 3;
    else
      v4 = (gta2::Car_sub_403800((Car *)v10, v3 + 64) != 0) + 1;
    v8 = v4;
    gta2::Player_sub_4211A0(self, v10);
    v6 = gta2::FloatDecoder(v5);
    ShowTextDisplay(&TextWcharT, (char *)L"speed:%3.3f(%d)", v6, v8);
    gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, 0, 16, unk_672F18, 1);
    v9 = gta2::Player_sub_49E820(self) ? 84 : 32;
    v7 = gta2::FloatDecoder(&self->field_60);
    ShowTextDisplay(&TextWcharT, (char *)off_574108, v7, v9);
    gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, 0, 32, unk_672F18, 1);
    ShowTextDisplay(&TextWcharT, (char *)off_5740F0, 100 * self->sCar1->Damage / 32000);
    return gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, 0, 48, unk_672F18, 1);
  }
  return result;
}


// 0x0049f170: Player::sub_49F170
// IDA: Player::sub_49F170
// Ghidra: Player::FUN_0049f170
byte gta2::Player_sub_49F170(Player *self)
{
  void *pvVar1;
  byte bVar2;
  
  pvVar1 = self->CarPlayerPre->S___;
  if (pvVar1 == NULL) {
    bVar2 = gta2::Player_sub_49EF80(self);
    return bVar2;
  }
  bVar2 = gta2::Player_sub_49EF80(*(Player **)(*(int *)((int)pvVar1 + 8) + 0x58));
  if (bVar2 != 0) {
    bVar2 = gta2::Player_sub_49EF80(*(Player **)(*(int *)((int)pvVar1 + 0xc) + 0x58));
    if (bVar2 != 0) {
      return 1;
    }
  }
  return 0;
}


// 0x0049f1b0: Player::sub_49F1B0
// IDA: Player::sub_49F1B0
// Ghidra: Player::FUN_0049f1b0
void gta2::Player_sub_49F1B0(Player *self)
{
  int iVar1;
  int *piVar2;
  void *pvVar3;
  undefined4 *puVar4;
  undefined2 *puVar5;
  undefined1 *puVar6;
  Sprite *this_00;
  undefined2 local_16;
  int local_14;
  undefined1 local_10 [8];
  undefined1 local_8 [8];
  
  pvVar3 = self->CarPlayerPre->S___;
  if (pvVar3 != NULL) {
    piVar2 = (int *)gta2::sub_401B90((Player *)&DAT_0066ac4c,&local_14,
                               (int *)&DAT_0066afc0);
    local_14 = *piVar2;
    piVar2 = &local_14;
    iVar1 = *(int *)(*(int *)((int)pvVar3 + 0xc) + 0x58);
    puVar6 = local_8;
    pvVar3 = FUN_0040f600((void *)(iVar1 + 0x38),local_10,
                          (GlassInfo *)&DAT_0066ae54);
    puVar4 = (undefined4 *)FUN_0041e1a0(pvVar3,puVar6,piVar2);
    *(undefined4 *)(iVar1 + 0x40) = *puVar4;
    piVar2 = &local_14;
    *(undefined4 *)(iVar1 + 0x44) = puVar4[1];
    this_00 = (Sprite *)local_10;
    puVar5 = gta2::sub_40EAB0(this_00,&local_16,(CarSystemManager *)&DAT_0066ae44,
                        iVar1 + 0x58);
    pvVar3 = (void *)FUN_0040f580(local_8,puVar5);
    puVar4 = (undefined4 *)gta2::WorldCoordinateToScreenCoord(pvVar3,this_00,piVar2);
    piVar2 = &local_14;
    puVar6 = local_8;
    *(undefined4 *)(iVar1 + 0x74) = *puVar4;
    pvVar3 = gta2::Player_sub_401B40((SpawnPoint *)(iVar1 + 0x6c),(GlassInfo *)local_10,
                        (S127 *)&DAT_0066ab98);
    puVar4 = (undefined4 *)gta2::WorldCoordinateToScreenCoord(pvVar3,puVar6,piVar2);
    *(undefined4 *)(iVar1 + 0x70) = *puVar4;
  }
  return;
}


// 0x0049f280: Player::sub_49F280
// IDA: Player::sub_49F280
// Ghidra: Player::FUN_0049f280
void gta2::Player_sub_49F280(Player *self)
{
  char cVar1;
  
  if (self->CarPlayerPre->S___ != NULL) {
    cVar1 = FUN_0049efb0();
    if (cVar1 != '\0') {
      if (self->ControlMode != '\0') {
        self->ControlMode = 0;
        *(undefined1 *)((int)&self->CameraOrPhysics_ + 1) = 1;
      }
      if (*(char *)((int)&self->CameraOrPhysics_ + 3) == '\0') {
        self->field_0xad = 0;
      }
    }
  }
  return;
}


// 0x0049f2d0: Player::sub_49F2D0
// IDA: Player::sub_49F2D0
// Ghidra: ---
char gta2::Player_sub_49F2D0(Player *self)
{
  char result; // al
  int v3; // eax
  int a2; // [esp+4h] [ebp-4h] BYREF

  result = gta2::Car_IsTrainOrTrainCarriage(self->sCar1);
  if ( !result )
  {
    v3 = self->field_A0;
    if ( v3 != 1 && v3 != 2 )
    {
      a2 = 2;
      if ( gta2::Random_Random(&gRandom, (__int16 *)&a2) )
        a2 = 1;
      else
        a2 = 2;
      gta2::Player_sub_49DD20(self, &a2);
    }
    self->gapA4[0] = 30;
    return gta2::Player_sub_49EF50(self, 30);
  }
  return result;
}


// 0x0049f350: Player::sub_49F350
// IDA: Player::sub_49F350
// Ghidra: ---
char gta2::Player_sub_49F350(Player *self)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  char v5; // al
  Car *sCar1; // edi
  struct Ped *Driver; // ebx
  Car *v8; // eax
  int v9; // eax
  int v11; // [esp-8h] [ebp-1Ch]
  int v12; // [esp-8h] [ebp-1Ch]
  int v13; // [esp-4h] [ebp-18h]
  int v14; // [esp-4h] [ebp-18h]
  SpriteS1 *a2; // [esp+10h] [ebp-4h] BYREF

  a2 = (SpriteS1 *)self->field_6C;
  v13 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)&a2);
  v11 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)&self->field_3C);
  v2 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)&self->field_38);
  if ( !gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct, v2, v11, v13) )
    a2 = gta2::Player_sub_401B40((Player *)&self->field_6C, (S202 *)&a2, (int)&unk_66AC4C)->FirstElement;
  v14 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)&a2);
  v12 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)&self->field_3C);
  v3 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)&self->field_38);
  v4 = gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct, v3, v12, v14);
  if ( v4 )
  {
    v5 = *(_BYTE *)(v4 + 11) & 3;
    if ( v5 == 2 || v5 == 3 )
    {
      sCar1 = self->sCar1;
      Driver = sCar1->Driver;
      if ( Driver )
      {
        if ( !gta2::Car_IsTrainOrTrainCarriage(self->sCar1) )
        {
          gta2::Player_sub_4211A0(self, &a2);
          if ( gta2::Car_sub_403800(v8, (int)&unk_66AF5C) || gta2::Car_sub_411970(sCar1) )
            gta2::Ped_sub_4350A0(Driver);
        }
      }
    }
  }
  v9 = self->field_A0;
  if ( v9 > 0 && v9 <= 2 )
  {
    LOBYTE(v9) = self->gapA4[0] - 1;
    self->gapA4[0] = v9;
    if ( !(_BYTE)v9 )
    {
      a2 = 0;
      gta2::Player_sub_49DD20(self, &a2);
    }
  }
  return v9;
}


// 0x0049f460: Player::sub_49F460
// IDA: Player::sub_49F460
// Ghidra: Player::FUN_0049f460
void gta2::Player_sub_49F460(Player *self,CollisionBox *pS61)
{
  SpriteS1 *pSVar1;
  char local_9;
  int local_8 [2];
  
  gta2::S63_sub_493090(pS61,&pS61,&local_9);
  local_8[0] = (int)(char)pS61;
  pSVar1 = FUN_00401bd0(&DAT_0066ac10,(SpriteS1 *)(local_8 + 1),local_8);
  gta2::Player_sub_40E530((Point2D *)&DAT_0066b004,(int *)pSVar1);
  local_8[0] = (int)local_9;
  pSVar1 = FUN_00401bd0(&DAT_0066ac10,(SpriteS1 *)(local_8 + 1),local_8);
  gta2::Player_sub_40E530((Point2D *)&DAT_0066b008,(int *)pSVar1);
  gta2::Player_sub_49EF50(self,0xf);
  return;
}


// 0x0049f4e0: Player::sub_49F4E0
// IDA: Player::sub_49F4E0
// Ghidra: Player::FUN_0049f4e0
void gta2::Player_sub_49F4E0(Player *self)
{
  FUN_0040f680(&self->S103_,0x66b004);
  return;
}


// 0x0049f4f0: Player::sub_49F4F0
// IDA: Player::sub_49F4F0
// Ghidra: Player::FUN_0049f4f0
void gta2::Player_sub_49F4F0(Player *self)
{
  FUN_004828c0(&self->S103_,(int *)&DAT_0066b004);
  return;
}


// 0x0049f500: Player::sub_49F500
// IDA: Player::sub_49F500
// Ghidra: Player::FUN_0049f500
void gta2::Player_sub_49F500(void)
{
  gta2::S103_sub_41E1E0((LinkedList *)&DAT_0066b004);
  return;
}


// 0x0049f570: Player::sub_49F570
// IDA: Player::sub_49F570
// Ghidra: FUN_0049f570
undefined4 * gta2::Player_sub_49F570(int param_1,undefined4 *param_2)
{
  int iVar1;
  undefined4 *puVar2;
  SpriteS1 *pSVar3;
  int *piVar4;
  void *self;
  undefined4 *puVar5;
  Player *local_1c [2];
  SpriteS1 *local_14;
  SpriteS1 *local_10;
  undefined1 local_c [4];
  undefined1 local_8 [8];
  
  if (*(int *)(*(int *)(param_1 + 0x5c) + 100) != 0) {
    puVar2 = (undefined4 *)FUN_00421cf0(&local_10);
    local_10 = (SpriteS1 *)*puVar2;
    puVar2 = (undefined4 *)FUN_00421cf0(&local_14);
    local_1c[0] = (Player *)*puVar2;
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&local_10,(SpriteS1 *)&local_14,
                        (S127 *)local_1c);
    local_14 = pSVar3->FirstElement;
    iVar1 = *(int *)(param_1 + 0x5c);
    piVar4 = (int *)gta2::sub_401B90((Player *)local_1c,local_c,(int *)&local_14);
    pSVar3 = (SpriteS1 *)
             FUN_0041e1a0((void *)(*(int *)(*(int *)(*(int *)(iVar1 + 100) + 0xc
                                                    ) + 0x58) + 0x30),local_1c,
                          piVar4);
    puVar2 = param_2;
    puVar5 = param_2;
    piVar4 = (int *)gta2::sub_401B90((Player *)&local_10,&param_2,(int *)&local_14);
    self = FUN_0041e1a0((void *)(*(int *)(*(int *)(*(int *)(iVar1 + 100) + 8) +
                                         0x58) + 0x30),local_8,piVar4);
    FUN_0040f5c0(self,puVar5,pSVar3);
    return puVar2;
  }
  *param_2 = *(undefined4 *)(param_1 + 0x30);
  param_2[1] = *(undefined4 *)(param_1 + 0x34);
  return param_2;
}


// 0x0049f660: Player::sub_49F660
// IDA: Player::sub_49F660
// Ghidra: ---
SpriteS1 * gta2::Player_sub_49F660(Player *self, SpriteS1 *a2)
{
  Car *sCar1; // ecx
  S900 *v4; // eax
  S900 *v6; // [esp-8h] [ebp-14h]
  char v7[4]; // [esp+4h] [ebp-8h] BYREF
  char v8[4]; // [esp+8h] [ebp-4h] BYREF

  sCar1 = self->sCar1;
  if ( sCar1->TrailerCtrl )
  {
    v6 = gta2::Car_sub_421CF0(*((Car **)sCar1->TrailerCtrl + 3), (S900 *)v7);
    v4 = gta2::Car_sub_421CF0(*((Car **)self->sCar1->TrailerCtrl + 2), (S900 *)v8);
    gta2::S202_sub_401B20((S202 *)v4, a2, (PublicTransport *)v6);
  }
  else
  {
    gta2::Car_sub_421CF0(sCar1, (S900 *)a2);
  }
  return a2;
}


// 0x0049f6c0: Player::sub_49F6C0
// IDA: Player::sub_49F6C0
// Ghidra: FUN_0049f6c0
SpriteS1 * gta2::Player_sub_49F6C0(int param_1,SpriteS1 *param_2)
{
  S127 *pS127;
  Point2D *self;
  SpriteS1 *pSpriteS1;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  if (*(int *)(*(int *)(param_1 + 0x5c) + 100) != 0) {
    pS127 = (S127 *)FUN_00425790(local_8);
    pSpriteS1 = param_2;
    self = (Point2D *)FUN_00425790(local_4);
    gta2::S202_sub_401B20(self,pSpriteS1,pS127);
    return param_2;
  }
  FUN_00425790(param_2);
  return param_2;
}


// 0x0049f720: Player::sub_49F720
// IDA: Player::sub_49F720
// Ghidra: FUN_0049f720
undefined4 * gta2::Player_sub_49F720(int param_1,undefined4 *param_2)
{
  byte bVar1;
  
  bVar1 = gta2::Car_sub_41E460(*(Car **)(param_1 + 0x5c));
  if (bVar1 != 0) {
    gta2::WorldCoordinateToScreenCoord
              ((void *)(_DAT_0066ab70 + 0x18),param_2,(int *)&DAT_0066adb0);
    return param_2;
  }
  *param_2 = *(undefined4 *)(_DAT_0066ab70 + 0x18);
  return param_2;
}


// 0x0049f930: Player::sub_49F930
// IDA: Player::sub_49F930
// Ghidra: ---
int * gta2::Player_sub_49F930(Player *self, int *a2)
{
  SpriteS1 *v3; // eax
  SpriteS1 *v4; // eax
  void *v5; // ecx
  SpriteS1 *v6; // eax
  void *v7; // ecx
  Car *v8; // eax
  void **v9; // eax
  Car *v10; // eax
  Car *v11; // eax
  Car *sCar1; // edx
  void *Car; // eax
  struct Player *TrailerCtrl; // ecx
  SpriteS1 *v15; // eax
  void *v16; // ecx
  SpriteS1 *v17; // eax
  void *v18; // ecx
  SpriteS1 *v19; // eax
  Car *v20; // eax
  void **v21; // eax
  Car *v22; // eax
  Car *v24; // [esp-14h] [ebp-48h]
  Car *v25; // [esp-14h] [ebp-48h]
  void **v26; // [esp-10h] [ebp-44h]
  void **v27; // [esp-10h] [ebp-44h]
  _DWORD *v28; // [esp-8h] [ebp-3Ch]
  _DWORD *v29; // [esp-8h] [ebp-3Ch]
  _DWORD *v30; // [esp-4h] [ebp-38h]
  void **v31; // [esp-4h] [ebp-38h]
  int a1; // [esp+4h] [ebp-30h] BYREF
  char v33[4]; // [esp+8h] [ebp-2Ch] BYREF
  int a2a; // [esp+Ch] [ebp-28h] BYREF
  S202 pS202; // [esp+10h] [ebp-24h] BYREF
  char v36[4]; // [esp+30h] [ebp-4h] BYREF

  v30 = (_DWORD *)gta2::Player_sub_40EC20(self, (int)&a1, (int)&stru_66AC54, (int)&stru_66AD3C, (int)&unk_66ACE8);
  v28 = gta2::sub_421EF0((int)self->sCar1, v33);
  v3 = gta2::Player_sub_401B40((Player *)&unk_66AC00, &pS202, (int)&stru_66AC54.UnitCars);
  v26 = (void **)gta2::sub_403840(&pS202.S202, (Player *)&pS202.S202, v3);
  v4 = gta2::Player_sub_401B40((Player *)&unk_66ABBC, (S202 *)&pS202.CarSystemManager, (int)&unk_66ACD4);
  v24 = (Car *)gta2::sub_403840(v5, (Player *)&pS202.field_C, v4);
  v6 = gta2::Player_sub_401B40((Player *)&unk_66ABB8, (S202 *)&pS202.field_10, (int)&unk_66ACD0);
  v8 = (Car *)gta2::sub_403840(v7, (Player *)&pS202.pPlayer, v6);
  v9 = sub_49E2C0((void **)&pS202.field_18, v8, v24, v26);
  v10 = (Car *)gta2::sub_401B90(v9, &a2a, v28);
  v11 = gta2::sub_41E130(&pS202.field_1C, v10, v30);
  sCar1 = self->sCar1;
  Car = v11->Car;
  a1 = (int)Car;
  TrailerCtrl = (Player *)sCar1->TrailerCtrl;
  if ( TrailerCtrl )
  {
    v31 = (void **)gta2::Player_sub_40EC20(
                     TrailerCtrl,
                     (int)&pS202.field_1C,
                     (int)&stru_66ADE0.SpriteS1_0,
                     (int)&stru_66ADE0,
                     (int)&unk_66ACE8);
    v29 = gta2::sub_421EF0(*((_DWORD *)self->sCar1->TrailerCtrl + 3), &pS202.field_18);
    v15 = gta2::Player_sub_401B40((Player *)&stru_66AC54.field_1C, (S202 *)&pS202.field_10, (int)&unk_66AB98);
    v27 = (void **)gta2::sub_403840(v16, (Player *)&pS202.field_C, v15);
    v17 = gta2::Player_sub_401B40(&unk_66ACC4, (S202 *)&pS202.CarSystemManager, (int)&stru_66AD3C.field_30);
    v25 = (Car *)gta2::sub_403840(v18, (Player *)&pS202.S202, v17);
    v19 = gta2::Player_sub_401B40(&unk_66ACC0, &pS202, (int)&stru_66AD3C.field_2C);
    v20 = (Car *)gta2::sub_403840(&a2a, (Player *)&a2a, v19);
    v21 = sub_49E2C0((void **)v33, v20, v25, v27);
    v22 = (Car *)gta2::sub_401B90(v21, &pS202.pPlayer, v29);
    Car = *sub_49E2C0((void **)v36, (Car *)&a1, v22, v31);
  }
  *a2 = (int)Car;
  return a2;
}


// 0x0049fac0: Player::sub_49FAC0
// IDA: Player::sub_49FAC0
// Ghidra: ---
ushort gta2::Player_sub_49FAC0(Player *self)
{
  ushort result; // ax
  int v3; // [esp+4h] [ebp-4h] BYREF

  gta2::S103_sub_41E1E0((S103 *)&self->Tango1);
  gta2::S103_sub_41E1E0((S103 *)&self->field_50);
  gta2::bitShiftLeft1(&v3, 0);
  *(_DWORD *)&self->Attack = v3;
  result = gta2::bitShiftLeft1(&v3, 0);
  *(_DWORD *)&self->PrevWeaponX = v3;
  return result;
}


// 0x0049fb00: Player::sub_49FB00
// IDA: Player::sub_49FB00
// Ghidra: ---
char gta2::Player_sub_49FB00(Player *self, char a2, char a3, char a4, char a5, char a6)
{
  char result; // al
  char v8; // cl
  char CameraOrPhysics1_high; // cl

  if ( gta2::SpriteS1_sub_420360((SpriteS1 *)&self->S103_4) )
  {
    HIBYTE(self->CameraOrPhysics1) = a2;
    result = 0;
    BYTE1(self->CameraOrPhysics1) = 0;
LABEL_10:
    self->field_94 = a3;
    goto LABEL_11;
  }
  if ( !gta2::Player_sub_40F840(self) )
  {
    CameraOrPhysics1_high = HIBYTE(self->CameraOrPhysics1);
    result = 0;
    HIBYTE(self->CameraOrPhysics1) = 0;
    if ( CameraOrPhysics1_high )
    {
      self->field_94 = 0;
      BYTE1(self->CameraOrPhysics1) = 0;
      goto LABEL_11;
    }
    BYTE1(self->CameraOrPhysics1) = a2;
    goto LABEL_10;
  }
  v8 = self->field_94;
  result = 0;
  self->field_94 = 0;
  if ( v8 )
  {
    HIBYTE(self->CameraOrPhysics1) = 0;
    BYTE1(self->CameraOrPhysics1) = 0;
  }
  else
  {
    HIBYTE(self->CameraOrPhysics1) = a2;
    BYTE1(self->CameraOrPhysics1) = a3;
  }
LABEL_11:
  BYTE2(self->CameraOrPhysics1) = a6;
  self->field_95 = 0;
  if ( a5 )
  {
    if ( !a4 )
    {
      self->gapAD[0] = -1;
      return result;
    }
  }
  else if ( a4 )
  {
    self->gapAD[0] = 1;
    return result;
  }
  self->gapAD[0] = 0;
  return result;
}


// 0x0049fbe0: Player::sub_49FBE0
// IDA: Player::sub_49FBE0
// Ghidra: FUN_0049fbe0
void gta2::Player_sub_49FBE0(int param_1,undefined4 *param_2,undefined4 *param_3)
{
  Car *self;
  SpriteS1 *pSVar1;
  bool bVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined3 extraout_var;
  int iVar5;
  S127 *pS127;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  SpawnPoint *pSVar6;
  SpawnPoint *local_14;
  SpriteS1 *local_10 [2];
  SpawnPoint *local_8;
  SpawnPoint *local_4;
  
  self = *(Car **)(param_1 + 0x5c);
  bVar2 = gta2::Car_sub_421720(self);
  if (bVar2) {
    local_8 = _DAT_0066ae54;
    local_4 = _DAT_0066ae58;
  }
  else {
    local_8 = _DAT_0066ac8c;
    local_4 = _DAT_0066ac90;
  }
  puVar3 = (undefined4 *)
           FUN_0040f600((void *)(param_1 + 0x38),local_10,(GlassInfo *)&local_8)
  ;
  local_8 = (SpawnPoint *)*puVar3;
  local_14 = (SpawnPoint *)puVar3[1];
  local_4 = local_14;
  switch(*(undefined4 *)(param_1 + 0x98)) {
  case 1:
    puVar3 = (undefined4 *)gta2::JustCopyByPtrAtoC(&local_4,local_10);
    local_14 = (SpawnPoint *)*puVar3;
    break;
  case 3:
    puVar3 = (undefined4 *)gta2::JustCopyByPtrAtoC(&local_8,local_10);
    local_14 = (SpawnPoint *)*puVar3;
  case 2:
    break;
  case 4:
    local_14 = local_8;
    break;
  default:
    *param_3 = _DAT_0066acdc;
    *param_2 = _DAT_0066acdc;
    return;
  }
  piVar4 = (int *)FUN_004634e0(local_10,*(undefined1 *)(param_1 + 0xa5));
  puVar3 = (undefined4 *)gta2::WorldCoordinateToScreenCoord(&local_14,&local_8,piVar4)
  ;
  pSVar6 = (SpawnPoint *)*puVar3;
  local_14 = pSVar6;
  if ((((*(char *)(param_1 + 0xa6) != '\0') ||
       (bVar2 = gta2::Car_sub_403800((Car *)&local_14,(int *)&DAT_0066acdc),
       CONCAT31(extraout_var,bVar2) == 0)) ||
      (iVar5 = DecoderFloat((void *)(param_1 + 0x6c)),
      (char)iVar5 != *(char *)(param_1 + 0xa7))) &&
     ((*(char *)(param_1 + 0xaa) == '\0' || (*(char *)(param_1 + 0xab) == '\0'))
     )) {
    bVar2 = gta2::Car_sub_403800((Car *)&local_14,(int *)&DAT_0066acdc);
    if ((CONCAT31(extraout_var_01,bVar2) != 0) &&
       ((self->S___ != NULL &&
        (iVar5 = FUN_0040f410(self),
        *(int *)(*(int *)(iVar5 + 0x58) + 0x98) != 6)))) {
      pSVar6 = _DAT_0066acdc;
    }
    *param_3 = pSVar6;
    *param_2 = pSVar6;
    return;
  }
  pS127 = (S127 *)FUN_0042a630(&local_8,param_1 + 0x6c);
  puVar3 = (undefined4 *)
           gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066ac4c,(GlassInfo *)local_10,pS127);
  pSVar1 = (SpriteS1 *)*puVar3;
  local_10[0] = pSVar1;
  bVar2 = gta2::Point2D_FUN_004037e0((Point2D *)&local_14,(SpriteS1 *)local_10);
  if (CONCAT31(extraout_var_00,bVar2) == 0) {
    *param_3 = pSVar6;
    *param_2 = pSVar6;
    return;
  }
  *param_3 = pSVar1;
  *param_2 = pSVar6;
  return;
}


// 0x0049fdc0: Player::sub_49FDC0
// IDA: Player::sub_49FDC0
// Ghidra: Player::thunk_FUN_0049fdc0
void gta2::Player_sub_49FDC0(Player *self)
{
  Sprite *this_00;
  undefined4 uVar1;
  bool bVar2;
  char cVar3;
  undefined4 *puVar4;
  undefined3 extraout_var;
  SpriteS1 *pSVar5;
  undefined3 extraout_var_00;
  undefined4 *puVar6;
  undefined3 extraout_var_01;
  int *pConditionValue;
  undefined3 extraout_var_02;
  undefined4 *puVar7;
  SpriteS1 *pSVar8;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  SpriteS1 *pSStack_8;
  undefined1 auStack_4 [4];
  
  puVar4 = (undefined4 *)
           gta2::MapRelatedStruct_sub_466F70(gMapRelatedStruct,&pSStack_8,self->field27_0x38,
                      self->field28_0x3c);
  pSVar8 = (SpriteS1 *)*puVar4;
  pSStack_8 = pSVar8;
  bVar2 = gta2::Player_IsCurrentPlayer((Player *)&pSStack_8,(Player *)&DAT_0066acdc);
  if (CONCAT31(extraout_var,bVar2) != 0) {
    pSStack_8 = _DAT_0066ac4c;
    pSVar8 = _DAT_0066ac4c;
  }
  puVar4 = &self->Debug;
  pSVar5 = gta2::S202_sub_401B20((Point2D *)puVar4,(SpriteS1 *)auStack_4,
                      (S127 *)&DAT_0066aec0);
  bVar2 = gta2::Player_sub_40CE70((Player *)&pSStack_8,(Player *)pSVar5);
  if (CONCAT31(extraout_var_00,bVar2) != 0) {
    puVar6 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)&pSStack_8,(GlassInfo *)auStack_4,
                        (S127 *)&DAT_0066ac4c);
    puVar6 = gta2::MapRelatedStruct_sub_466E20(gMapRelatedStruct,&pSStack_8,self->field27_0x38,
                        self->field28_0x3c,(SpriteS1 *)*puVar6);
    pSVar8 = (SpriteS1 *)*puVar6;
    pSStack_8 = pSVar8;
    pSVar5 = gta2::S202_sub_401B20((Point2D *)puVar4,(SpriteS1 *)auStack_4,
                        (S127 *)&DAT_0066ac4c);
    bVar2 = gta2::Player_sub_40CE70((Player *)&pSStack_8,(Player *)pSVar5);
    if (CONCAT31(extraout_var_01,bVar2) != 0) {
      pSVar8 = (SpriteS1 *)*puVar4;
      pSStack_8 = pSVar8;
    }
  }
  pConditionValue =
       (int *)gta2::Player_sub_401B40((SpawnPoint *)puVar4,(GlassInfo *)auStack_4,
                         (S127 *)&DAT_0066aec0);
  bVar2 = gta2::Player_CheckCondition((Player *)&pSStack_8,pConditionValue);
  if (CONCAT31(extraout_var_02,bVar2) == 0) {
    bVar2 = gta2::Point2D_FUN_004037e0((Point2D *)&pSStack_8,(SpriteS1 *)puVar4);
    if (CONCAT31(extraout_var_04,bVar2) != 0) {
      gta2::Player_sub_49EE80(self);
      this_00 = self->CarPlayerPre->CarSprite;
      gta2::SpriteS1_sub_420600(this_00,(int)this_00->Point2D1,
                          *(int *)&this_00->field_0x18,(int)pSVar8);
      cVar3 = gta2::SpriteS1_sub_4BD670((SpriteS1 *)self->CarPlayerPre->CarSprite);
      if (cVar3 != '\0') {
        pSStack_8 = (SpriteS1 *)*puVar4;
      }
    }
  }
  else {
    puVar7 = (undefined4 *)FUN_0049fbe0(&pSStack_8,auStack_4);
    puVar6 = &self->ID;
    *puVar6 = *puVar7;
    pSVar8 = gta2::S202_sub_401B20((Point2D *)puVar4,(SpriteS1 *)auStack_4,(S127 *)puVar6);
    pSStack_8 = pSVar8->FirstElement;
    bVar2 = gta2::Car_IsTrainOrTrainCarriage((Car *)&stack0x00000004,(Car *)&DAT_0066acdc);
    if (CONCAT31(extraout_var_03,bVar2) != 0) {
      FUN_0048a1a0(puVar6,(int *)&stack0x00000004);
    }
  }
  puVar6 = (undefined4 *)
           gta2::Player_sub_401B40((SpawnPoint *)&pSStack_8,(GlassInfo *)auStack_4,
                      (S127 *)puVar4);
  uVar1 = *puVar6;
  self->field44_0x70 = (char)uVar1;
  self->field45_0x71 = (char)((uint)uVar1 >> 8);
  self->field46_0x72 = (char)((uint)uVar1 >> 0x10);
  self->field47_0x73 = (char)((uint)uVar1 >> 0x18);
  gta2::Player_sub_40E530((Point2D *)puVar4,(int *)&self->field44_0x70);
  bVar2 = gta2::Car_IsTrainOrTrainCarriage((Car *)&stack0x00000004,(Car *)&DAT_0066acdc);
  if (CONCAT31(extraout_var_05,bVar2) != 0) {
    FUN_0048a1a0(&self->field44_0x70,(int *)&stack0x00000004);
  }
  return;
}


// 0x0049ff80: Player::sub_49FF80
// IDA: Player::sub_49FF80
// Ghidra: FUN_0049ff80
void gta2::Player_sub_49FF80(int param_1,byte param_2)
{
  SpriteS1 *self;
  byte bVar1;
  bool bVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined1 local_c [4];
  undefined1 local_8 [8];
  
  self = *(SpriteS1 **)(*(int *)(param_1 + 0x5c) + 0x50);
  bVar1 = gta2::SpriteS1_sub_4BAA90(self);
  if ((bVar1 == 0) &&
     (bVar2 = gta2::Car_GetFullDamage(*(Car **)(param_1 + 0x5c)), !bVar2)) {
    if (param_2 == 0) {
      param_2 = FUN_004bd350(local_c);
    }
    iVar4 = 0;
    bVar1 = 1;
    do {
      if ((bVar1 & param_2) == bVar1) {
        puVar3 = (undefined4 *)FUN_0049ea30(local_8,iVar4);
        FUN_0048db00(*puVar3,puVar3[1],*(undefined4 *)(param_1 + 0x6c),
                     *(undefined4 *)(param_1 + 0x40),
                     *(undefined4 *)(param_1 + 0x44));
      }
      iVar4 = iVar4 + 1;
      bVar1 = bVar1 * '\x02';
    } while (iVar4 < 4);
  }
  gta2::CameraOrPhysics_sub_4102A0((CameraOrPhysics *)gCameraOrPhysics,(GlassInfo *)self);
  return;
}


// 0x004a0020: Player::sub_4A0020
// IDA: Player::sub_4A0020
// Ghidra: Player::FUN_004a0020
byte gta2::Player_sub_4A0020(Player *self)
{
  void *pvVar1;
  char cVar2;
  SpriteS1 *pSVar3;
  SpriteS1 *this_00;
  
  this_00 = (SpriteS1 *)self->CarPlayerPre->CarSprite;
  cVar2 = gta2::SpriteS1_sub_4BD670(this_00);
  if ((cVar2 == '\0') &&
     (pSVar3 = gta2::SpriteS1_sub_4BDFE0(this_00,0), pSVar3 == NULL)) {
    pvVar1 = self->CarPlayerPre->S___;
    if (pvVar1 == NULL) {
      return 0;
    }
    this_00 = *(SpriteS1 **)(*(int *)((int)pvVar1 + 0xc) + 0x50);
    cVar2 = gta2::SpriteS1_sub_4BD670(this_00);
    if ((cVar2 == '\0') &&
       (pSVar3 = gta2::SpriteS1_sub_4BDFE0(this_00,0), pSVar3 == NULL)) {
      return 0;
    }
  }
  FUN_0049ef10(&PTR_005e6874,this_00);
  return 1;
}


// 0x004a0080: Player::sub_4A0080
// IDA: Player::sub_4A0080
// Ghidra: FUN_004a0080
void gta2::Player_sub_4A0080(Player *param_1)
{
  bool bVar1;
  byte bVar2;
  int iVar3;
  
  bVar1 = gta2::Car_IsTrainOrTrainCarriage(param_1->CarPlayerPre);
  if (!bVar1) {
    gta2::Player_sub_49DE40(param_1);
    gta2::Player_sub_49EEB0(param_1);
    bVar2 = gta2::Player_sub_4A0020(param_1);
    if (bVar2 != 0) {
      if (PTR_005e6874 == (void *)0x3) {
        iVar3 = gta2::SpriteS1_getSpriteType(DAT_005e6894);
        if (iVar3 != 3) {
          gta2::SpriteS1_GetCar(DAT_005e6898);
          gta2::DebugLog(0x7df,"physics.cpp",0x7a0);
          return;
        }
      }
      else {
        gta2::SpriteS1_GetCar(DAT_005e6898);
        gta2::DebugLog(0x434,"physics.cpp",0x7a9);
      }
    }
  }
  return;
}


// 0x004a0120: Player::sub_4A0120
// IDA: Player::sub_4A0120
// Ghidra: FUN_004a0120
void gta2::Player_sub_4A0120(void *self,Player *pPlayer,GlassInfo *pCar,Ped *param_3,int param_4 )
{
  GlassInfo *this_00;
  char cVar1;
  bool bVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  undefined2 *puVar6;
  undefined3 extraout_var;
  int Type;
  CollisionBox *pEventHandler;
  CollisionBox *pCVar7;
  int y;
  undefined1 *puVar8;
  int z;
  struct Player **ppPVar9;
  undefined4 uVar10;
  undefined4 local_18 [2];
  struct Player *local_10;
  struct Player *local_c;
  undefined1 local_8 [8];
  
  FUN_0040f6b0(&pCar,(GlassInfo *)((int)self + 0x58));
  FUN_0040f680(&pCar,(int)self + 0x38);
  cVar1 = FUN_00466af0(pCar,param_3,*(undefined4 *)((int)self + 0x6c));
  if ((cVar1 != '\x05') && ((param_4 != 3 || (cVar1 == '\a')))) {
    this_00 = (GlassInfo *)((int)self + ((uint)pPlayer & 0xff) * 8 + 0x10);
    iVar3 = FUN_00420360(this_00);
    if (iVar3 == 0) {
      puVar4 = (undefined4 *)FUN_0040f600(&pCar,local_18,this_00);
      local_10 = (Player *)*puVar4;
      pPlayer = (Player *)0x2;
      local_c = (Player *)puVar4[1];
      ppPVar9 = &pPlayer;
      puVar8 = local_8;
      FUN_0040f5c0(this_00,local_18,(SpriteS1 *)&pCar);
      piVar5 = (int *)gta2::FUN_0049e360(puVar8,ppPVar9);
      iVar3 = *piVar5;
      y = piVar5[1];
      puVar6 = gta2::Player_FUN_0040f790((Player *)&local_10,(undefined2 *)&pPlayer);
      local_18[0] = CONCAT22(local_18[0]._2_2_,*puVar6);
      piVar5 = gta2::Player_sub_41E260((Player *)&local_10,(int *)&pPlayer);
      pPlayer = (Player *)*piVar5;
      bVar2 = gta2::Car_sub_403800((Car *)&pPlayer,(int *)&DAT_0066acdc);
      if (CONCAT31(extraout_var,bVar2) != 0) {
        z = *(int *)((int)self + 0x6c);
        uVar10 = local_18[0];
        Type = gta2::Player_physicsSelect(pPlayer,pPlayer);
        pEventHandler =
             (CollisionBox *)
             gta2::Object_SpawnObject(gObject,Type,iVar3,y,z,(short)uVar10);
        if ((pEventHandler != NULL) &&
           (pCVar7 = pEventHandler,
           gta2::Sprite_FUN_004bd250((Sprite *)pEventHandler->Index),
           (char)pCVar7 != '\0')) {
          gta2::S63_sub_4827B0(pEventHandler);
        }
      }
    }
    this_00->car = (Car *)pCar;
    this_00->pPed = param_3;
    return;
  }
  gta2::S103_sub_41E1E0((LinkedList *)((int)self + ((uint)pPlayer & 0xff) * 8 + 0x10)
                  );
  return;
}


// 0x004a0290: Player::sub_4A0290
// IDA: Player::sub_4A0290
// Ghidra: ---
char gta2::Player_sub_4A0290(Player *self)
{
  Car *sCar1; // edi
  Tango *v3; // eax
  SpriteS1 *v4; // eax
  int v5; // ebx
  SpriteS1 *v6; // eax
  SpriteS1 *v7; // eax
  int State; // edi
  SpriteS1 *v9; // eax
  int v10; // edi
  SpriteS1 *v11; // eax
  S103 **p_pS103; // ecx
  char result; // al
  SpriteS1 *v14; // [esp-8h] [ebp-2Ch]
  SpriteS1 *FirstElement; // [esp+Ch] [ebp-18h] BYREF
  SpriteS1 *a2; // [esp+10h] [ebp-14h] BYREF
  SpriteS1 *a3; // [esp+14h] [ebp-10h] BYREF
  char v18[4]; // [esp+18h] [ebp-Ch] BYREF
  _DWORD v19[2]; // [esp+1Ch] [ebp-8h] BYREF

  if ( gta2::Car_sub_41F940(self->sCar1) )
  {
    sCar1 = self->sCar1;
    gta2::Car_sub_48A930(sCar1, &a2);
    v4 = gta2::Radar_AddBlip(v3, (SpriteS1 *)&a3, (PublicTransport *)&stru_66ADE0.field_10);
    v5 = unk_66AB78;
    FirstElement = v4->FirstElement;
    v6 = gta2::Car_sub_421910(sCar1, (SpriteS1 *)&a3, *(SpriteS1 **)(unk_66AB78 + 8));
    v14 = *(SpriteS1 **)(v5 + 4);
    a2 = v6->FirstElement;
    v7 = gta2::Car_sub_421910(sCar1, (SpriteS1 *)&a3, v14);
    State = self->State;
    a3 = v7->FirstElement;
    if ( State == 7
      || State == 8
      || State == 9
      || (gta2::Player_sub_40CE70((Player *)&self->field_88, (_DWORD *)(v5 + 40))
       || self->field_AC && gta2::Car_sub_403800((Car *)(v5 + 32), (int)&unk_66ACDC))
      && State != 6 )
    {
      v9 = gta2::JustCopyByPtrAtoC(&FirstElement, (SpriteS1 *)v18);
      gta2::S103_sub_401D20((S103 *)v19, v9, &a2);
      gta2::Player_sub_4A0120(self, 0);
      gta2::S103_sub_401D20((S103 *)v19, &FirstElement, &a2);
      gta2::Player_sub_4A0120(self, (void *)1);
    }
    else
    {
      gta2::S103_sub_41E1E0((S103 *)&self->S103_);
      gta2::S103_sub_41E1E0((S103 *)&self->S103_1);
    }
    v10 = self->State;
    if ( v10 == 7
      || v10 == 8
      || v10 == 9
      || (gta2::Player_sub_40CE70((Player *)&self->field_84, (_DWORD *)(unk_66AB78 + 36))
       || self->field_AC && gta2::Car_sub_403800((Car *)(unk_66AB70 + 8), (int)&unk_66ACDC))
      && v10 != 6 )
    {
      v11 = gta2::JustCopyByPtrAtoC(&FirstElement, (SpriteS1 *)v18);
      gta2::S103_sub_401D20((S103 *)v19, v11, &a3);
      gta2::Player_sub_4A0120(self, (void *)3);
      gta2::S103_sub_401D20((S103 *)v19, &FirstElement, &a3);
      gta2::Player_sub_4A0120(self, (void *)2);
      goto LABEL_23;
    }
    gta2::S103_sub_41E1E0((S103 *)&self->S103_2);
    p_pS103 = &self->pS103;
  }
  else
  {
    gta2::S103_sub_41E1E0((S103 *)&self->S103_);
    gta2::S103_sub_41E1E0((S103 *)&self->S103_1);
    gta2::S103_sub_41E1E0((S103 *)&self->pS103);
    p_pS103 = &self->S103_2;
  }
  gta2::S103_sub_41E1E0((S103 *)p_pS103);
LABEL_23:
  result = self->field_AC;
  if ( result )
    self->field_AC = --result;
  return result;
}


// 0x004a0560: Player::sub_4A0560
// IDA: Player::sub_4A0560
// Ghidra: ---
char gta2::Player_sub_4A0560(Player *self)
{
  _DWORD *TrailerCtrl; // eax
  struct Player *v3; // esi

  LOBYTE(TrailerCtrl) = skip_skidmarks;
  if ( !skip_skidmarks )
  {
    gta2::Player_sub_4A0290(self);
    TrailerCtrl = self->sCar1->TrailerCtrl;
    if ( TrailerCtrl )
    {
      v3 = *(Player **)(TrailerCtrl[3] + 88);
      gta2::Player_sub_49ECC0(v3);
      v3->field_84 = unk_66ACDC;
      v3->field_88 = unk_66ACDC;
      gta2::Player_sub_4A0290(v3);
      LOBYTE(TrailerCtrl) = (unsigned __int8)gta2::Player_sub_49ECC0(self);
    }
  }
  return (char)TrailerCtrl;
}


// 0x004a0850: Player::sub_4A0850
// IDA: Player::sub_4A0850
// Ghidra: FUN_004a0850
void gta2::Player_sub_4A0850(int param_1,undefined4 *param_2,Car *param_3,Ped *param_4)
{
  Car *pCVar1;
  void *pvVar2;
  S127 *pS127;
  SpawnPoint *self;
  int *piVar3;
  undefined4 *puVar4;
  Passenger **ppPVar5;
  GlassInfo *pGVar6;
  Car *pCVar7;
  undefined4 local_c;
  struct Ped *local_8;
  
  local_c = *param_2;
  local_8 = (Ped *)param_2[1];
  if (param_4 == (Ped *)0x1) {
    FUN_0040f6b0(&local_c,(GlassInfo *)(param_1 + 0x58));
    FUN_0040f680(&local_c,param_1 + 0x38);
  }
  pCVar1 = param_3;
  FUN_0040f680((void *)(param_1 + 0x48),(int)param_3);
  puVar4 = &param_2;
  pCVar7 = pCVar1;
  pvVar2 = gta2::Player_sub_401B40((SpawnPoint *)&local_8,(GlassInfo *)&param_4,
                      (S127 *)(param_1 + 0x34));
  pS127 = (S127 *)gta2::WorldCoordinateToScreenCoord(pvVar2,puVar4,(int *)pCVar7);
  pGVar6 = (GlassInfo *)&param_3;
  ppPVar5 = &pCVar1->Passengers;
  puVar4 = &local_c;
  pvVar2 = gta2::Player_sub_401B40((SpawnPoint *)&local_c,(GlassInfo *)&stack0xfffffffc,
                      (S127 *)(param_1 + 0x30));
  self = (SpawnPoint *)
         gta2::WorldCoordinateToScreenCoord(pvVar2,puVar4,(int *)ppPVar5);
  piVar3 = (int *)gta2::Player_sub_401B40(self,pGVar6,pS127);
  gta2::Player_sub_40E530((Point2D *)(param_1 + 0x7c),piVar3);
  return;
}


// 0x004a0900: Player::sub_4A0900
// IDA: Player::sub_4A0900
// Ghidra: FUN_004a0900
void gta2::Player_sub_4A0900(void *self,void *param_1)
{
  void *pvVar1;
  undefined1 local_8 [8];
  
  pvVar1 = FUN_0041e1a0(param_1,local_8,(int *)(_DAT_0066ab70 + 4));
  FUN_0040f680((void *)((int)self + 0x48),(int)pvVar1);
  return;
}


// 0x004a0930: Player::sub_4A0930
// IDA: Player::sub_4A0930
// Ghidra: ---
void * gta2::Player_sub_4A0930(Player *self, Tango *a2)
{
  SpriteS1 *v3; // eax
  _DWORD *v4; // eax
  char v6[4]; // [esp+4h] [ebp-Ch] BYREF
  char v7[8]; // [esp+8h] [ebp-8h] BYREF

  v3 = gta2::Player_sub_49F660(self, (SpriteS1 *)v6);
  v4 = gta2::Tango_sub_41E1A0(a2, v7, v3);
  return gta2::Tango_sub_40F680((Tango *)&self->Tango1, (int)v4);
}


// 0x004a0960: Player::sub_4A0960
// IDA: Player::sub_4A0960
// Ghidra: ---
Car * gta2::Player_sub_4A0960(Player *self, Tango *a2)
{
  Car *sCar1; // esi
  struct Player *v4; // esi

  sCar1 = self->sCar1;
  if ( !gta2::Car_sub_421720(sCar1) )
    return (Car *)gta2::Player_sub_4A0900(self, a2);
  v4 = *(Player **)(*((_DWORD *)sCar1->TrailerCtrl + 2) + 88);
  gta2::Player_sub_49ECC0(v4);
  gta2::Player_sub_4A0900(v4, a2);
  return gta2::Player_sub_49ECC0(self);
}


// 0x004a09b0: Player::sub_4A09B0
// IDA: Player::sub_4A09B0
// Ghidra: ---
void gta2::Player_sub_4A09B0(Player *self, int *a2, int a3)
{
  int *v4; // eax
  int v5; // edx
  _DWORD v6[2]; // [esp+4h] [ebp-10h] BYREF
  char v7[8]; // [esp+Ch] [ebp-8h] BYREF

  if ( !gta2::Car_IsTrainOrTrainCarriage(self->sCar1) )
  {
    if ( BYTE2(self->CameraOrPhysics1) )
      v4 = sub_4202E0(a2, v7, (S900 *)&stru_66AD3C.field_44);
    else
      v4 = a2;
    v5 = v4[1];
    v6[0] = *v4;
    v6[1] = v5;
    gta2::Player_sub_4A0960(self, (Tango *)v6);
    gta2::Player_sub_49EF50(self, a3);
    if ( !gta2::Car_IsDriverPlayer(self->sCar1) )
      gta2::Player_sub_421260(self);
  }
}


// 0x004a0a30: Player::sub_4A0A30
// IDA: Player::sub_4A0A30
// Ghidra: Player::FUN_004a0a30
byte gta2::Player_sub_4A0A30(Player *self,GameObject *param_1,Passenger *param_2)
{
  void *pvVar1;
  GameObject *this_00;
  bool bVar2;
  GameObject **ppGVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  Car *pCVar6;
  undefined3 extraout_var;
  int *piVar7;
  struct Player *this_01;
  Car *pCVar8;
  int iVar9;
  undefined1 *puVar10;
  int local_28 [2];
  struct Player *local_20;
  struct Player *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined1 local_10 [8];
  undefined1 local_8 [8];
  
  this_00 = param_1;
  ppGVar3 = &param_1;
  gta2::GameObject_GetY(param_1,ppGVar3);
  puVar4 = (undefined4 *)gta2::GameObject_GetX(this_00,local_28);
  String_ParseLine(local_10,puVar4,ppGVar3);
  FUN_0049f570(&local_20);
  puVar4 = (undefined4 *)
           gta2::Player_GetCarPoints(self,local_28,(GlassInfo *)&DAT_0066ad08);
  local_18 = *puVar4;
  local_14 = puVar4[1];
  puVar4 = (undefined4 *)
           FUN_0040f600(&local_20,local_28,(GlassInfo *)&DAT_0066ad08);
  _DAT_0066afb4 = *puVar4;
  _DAT_0066afb8 = puVar4[1];
  puVar4 = (undefined4 *)FUN_0049f6c0(&param_1);
  puVar5 = (undefined4 *)gta2::Player_sub_49F660(self,local_28);
  puVar4 = (undefined4 *)
           FUN_004a05c0(local_8,*puVar5,_DAT_0066ac44,&local_18,&DAT_0066afb4,
                        &DAT_0066ad08,&local_20,local_10,*puVar4,_DAT_0066aea0,
                        _DAT_0066ae88);
  local_20 = (Player *)*puVar4;
  local_1c = (Player *)puVar4[1];
  if (self->State == 6) {
    pCVar6 = (Car *)&param_1;
    pCVar8 = (Car *)&self->CarPlayerPre->CarSprite->Point2D;
    gta2::GameObject_GetZ(this_00,(undefined4 *)pCVar6);
    bVar2 = gta2::Car_IsTrainOrTrainCarriage(pCVar6,pCVar8);
    if (CONCAT31(extraout_var,bVar2) == 0) goto LAB_004a0b3f;
  }
  else {
LAB_004a0b3f:
    if ((char)param_2 != '\0') {
      param_2 = (Passenger *)((uint)param_2 & 0xffffff00);
      goto LAB_004a0b53;
    }
  }
  param_2 = (Passenger *)CONCAT31(param_2._1_3_,1);
LAB_004a0b53:
  piVar7 = gta2::Player_sub_41E260((Player *)&local_20,(int *)&param_1);
  _DAT_0066b034 = *piVar7;
  puVar10 = local_8;
  piVar7 = (int *)&DAT_0066ac44;
  pCVar6 = self->CarPlayerPre;
  this_01 = (Player *)gta2::Player_FUN_0040f640((Player *)&local_20,local_10);
  puVar4 = (undefined4 *)gta2::Player_FUN_004202e0(this_01,puVar10,piVar7);
  local_20 = (Player *)*puVar4;
  local_1c = (Player *)puVar4[1];
  if (pCVar6->Driver == NULL) {
    pvVar1 = pCVar6->S___;
    if ((((pvVar1 != NULL) && (*(Car **)((int)pvVar1 + 0xc) != NULL)) &&
        (*(Car **)((int)pvVar1 + 0xc) == pCVar6)) &&
       ((pCVar8 = *(Car **)((int)pvVar1 + 8), pCVar8 != NULL &&
        (pCVar6 = pCVar8, pCVar8->Driver != NULL)))) {
      *(int *)(this_00->ScriptRef + 0x204) = pCVar8->Driver->ID;
      *(undefined1 *)(this_00->ScriptRef + 0x264) = 0x32;
      pvVar1 = (void *)this_00->ScriptRef;
      iVar9 = FUN_0049ef40(pvVar1);
      *(uint *)((int)pvVar1 + 0x290) =
           (uint)(iVar9 == *(int *)((int)self->CarPlayerPre->S___ + 8)) * 2 + 1;
    }
  }
  else {
    *(int *)(this_00->ScriptRef + 0x204) = pCVar6->Driver->ID;
    *(undefined1 *)(this_00->ScriptRef + 0x264) = 0x32;
    pvVar1 = (void *)this_00->ScriptRef;
    pCVar8 = (Car *)FUN_0049ef40(pvVar1);
    *(uint *)((int)pvVar1 + 0x290) =
         (uint)(pCVar8 == self->CarPlayerPre) * 2 + 1;
  }
  FUN_00497570(this_00,(int)pCVar6,param_2,local_20,local_1c);
  return (byte)local_1c;
}


// 0x004a0c60: Player::sub_4A0C60
// IDA: Player::sub_4A0C60
// Ghidra: Player::FUN_004a0c60
void * gta2::Player_sub_4A0C60(Player *self)
{
  undefined4 uVar1;
  int *piVar2;
  struct Player *this_00;
  undefined4 *puVar3;
  undefined1 *puVar4;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined1 local_8 [8];
  
  piVar2 = (int *)gta2::Player_sub_49F660(self,local_10);
  piVar2 = (int *)gta2::Player_FUN_004202e0((Player *)&self->field31_0x48,local_8,piVar2);
  self->timeSecond = *piVar2;
  self->field37_0x54 = piVar2[1];
  piVar2 = (int *)FUN_0049f6c0(local_10);
  puVar4 = local_c;
  this_00 = (Player *)gta2::JustCopyByPtrAtoC(&self->Tango1,local_8);
  puVar3 = (undefined4 *)gta2::sub_401B90(this_00,puVar4,piVar2);
  uVar1 = *puVar3;
  self->PrevWeaponX = (char)uVar1;
  self->keySpecial = (char)((uint)uVar1 >> 8);
  self->keySpecial2 = (char)((uint)uVar1 >> 0x10);
  self->field63_0x83 = (char)((uint)uVar1 >> 0x18);
  return puVar3;
}


// 0x004a0cc0: Player::sub_4A0CC0
// IDA: Player::sub_4A0CC0
// Ghidra: Player::FUN_004a0cc0
void * gta2::Player_sub_4A0CC0(Player *self)
{
  undefined1 *this_00;
  void *pvVar1;
  undefined4 *puVar2;
  void *this_01;
  struct Player *local_4;
  
  local_4 = self;
  FUN_0040f680(&self->S103_,(int)&self->timeSecond);
  this_00 = &self->DeathReason;
  gta2::Player_sub_40E530((Point2D *)this_00,(int *)&self->PrevWeaponX);
  gta2::Player_ResetControlState(self);
  gta2::Tango_sub_49E3C0((Player *)&self->S103_);
  puVar2 = (undefined4 *)FUN_00482730(this_01,&local_4,(GlassInfo *)this_00);
  pvVar1 = (void *)*puVar2;
  *(void **)this_00 = pvVar1;
  return pvVar1;
}


// 0x004a0d10: Player::sub_4A0D10
// IDA: Player::sub_4A0D10
// Ghidra: Player::FUN_004a0d10
void * gta2::Player_sub_4A0D10(Player *self,void *param_1,GlassInfo *param_2)
{
  gta2::Player_sub_49ECA0(self);
  gta2::Player_GetCarPoints(self,param_1,param_2);
  return param_1;
}


// 0x004a0d40: Player::sub_4A0D40
// IDA: Player::sub_4A0D40
// Ghidra: FUN_004a0d40
void gta2::Player_sub_4A0D40(int param_1,int *param_2,Player *param_3,undefined4 param_4, SpriteS1 *param_5)
{
  byte bVar1;
  int iVar2;
  struct Player *pPVar3;
  bool bVar4;
  undefined4 *puVar5;
  GlassInfo *pGVar6;
  int *piVar7;
  undefined3 extraout_var;
  struct Player *pPVar8;
  undefined3 extraout_var_00;
  void *self;
  SpriteS1 *pSVar9;
  int iVar10;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  int *piVar11;
  struct Player *pPVar12;
  struct Player *local_10;
  struct Player *local_c;
  struct Player *local_8;
  struct Player *local_4;
  
  pPVar3 = param_3;
  if (*(char *)(param_1 + 0x95) == '\0') {
    puVar5 = (undefined4 *)FUN_0049e650(&local_8,param_3);
    local_10 = (Player *)*puVar5;
    local_c = (Player *)puVar5[1];
    pGVar6 = (GlassInfo *)
             gta2::sub_401C80((CarSystemManager *)&param_4,&param_3);
    FUN_0040f6b0(&local_10,pGVar6);
    pSVar9 = param_5;
    piVar7 = (int *)gta2::JustCopyByPtrAtoC(param_5,&param_3);
    puVar5 = (undefined4 *)
             gta2::WorldCoordinateToScreenCoord(&local_10,&param_5,piVar7);
    local_8 = (Player *)*puVar5;
    piVar7 = (int *)gta2::JustCopyByPtrAtoC(pSVar9->Matrix3DArray,&param_3);
    puVar5 = (undefined4 *)
             gta2::WorldCoordinateToScreenCoord(&local_c,&param_5,piVar7);
    local_4 = (Player *)*puVar5;
  }
  else {
    FUN_00432860(&local_8,(undefined4 *)&DAT_0066acdc,
                 (undefined4 *)&DAT_0066acdc);
  }
  piVar7 = gta2::Player_FUN_00403840((Player *)&local_c,(int *)&param_3,(GlassInfo *)&local_c);
  param_3 = (Player *)*piVar7;
  piVar7 = gta2::Player_FUN_00403840((Player *)&local_8,(int *)&param_5,(GlassInfo *)&local_8);
  iVar2 = *piVar7;
  if ((*(int *)(param_1 + 0x8c) == 2) &&
     (bVar4 = gta2::Car_isTank(*(Car **)(param_1 + 0x5c)), !bVar4)) {
    bVar4 = gta2::Player_CheckCondition((Player *)&param_3,(int *)&DAT_0066ace0);
    if (CONCAT31(extraout_var,bVar4) != 0) {
      pPVar12 = (Player *)&DAT_0066ac80;
      pPVar8 = (Player *)
               gta2::Player_FUN_00403840((Player *)&param_5,(int *)&param_5,
                          (GlassInfo *)&stack0x00000014);
      bVar4 = gta2::Player_sub_40CE70(pPVar8,pPVar12);
      if (CONCAT31(extraout_var_00,bVar4) != 0) {
        piVar7 = (int *)&param_3;
        pSVar9 = (SpriteS1 *)&param_5;
        pPVar8 = (Player *)&stack0xffffffec;
        piVar11 = (int *)&DAT_0066ac80;
        param_3 = (Player *)0x8;
        pPVar12 = (Player *)
                  gta2::Player_FUN_00403840(pPVar8,(int *)&local_10,
                             (GlassInfo *)&stack0x00000014);
        self = gta2::sub_401B90(pPVar12,pPVar8,piVar11);
        pSVar9 = FUN_00401bd0(self,pSVar9,piVar7);
        iVar10 = DecoderFloat(pSVar9);
        *(char *)(param_1 + 0xac) = (char)iVar10;
        goto LAB_004a0ee8;
      }
    }
    if (((*(char *)(param_1 + 0x92) != '\0') &&
        (((bVar1 = *(byte *)(param_1 + 0xac), bVar1 != 0 &&
          (bVar4 = gta2::Car_sub_403800((Car *)&param_3,(int *)&DAT_0066acdc),
          CONCAT31(extraout_var_01,bVar4) != 0)) ||
         (bVar4 = gta2::Player_sub_40CE70((Player *)&param_3,(Player *)&DAT_0066b010),
         CONCAT31(extraout_var_02,bVar4) != 0)))) && (bVar1 < 2)) {
      *(undefined1 *)(param_1 + 0xac) = 2;
    }
  }
LAB_004a0ee8:
  gta2::Player_sub_40E530((Point2D *)&local_4,(int *)&stack0x00000014);
  FUN_0040f6b0(&local_8,(GlassInfo *)&param_4);
  FUN_004a0850(pPVar3,&local_8,1);
  *param_2 = iVar2;
  return;
}


// 0x004a0f30: Player::sub_4A0F30
// IDA: Player::sub_4A0F30
// Ghidra: FUN_004a0f30
void gta2::Player_sub_4A0F30(int param_1,undefined4 *param_2)
{
  int iVar1;
  bool bVar2;
  int *piVar3;
  undefined3 extraout_var;
  void *pvVar4;
  undefined4 *puVar5;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined1 *puVar6;
  struct Player **pS110;
  struct Player *local_c;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  bVar2 = gta2::Car_IsEngineOn(*(Car **)(param_1 + 0x5c));
  if (((bVar2) && (*(int *)(param_1 + 0x98) != 7)) &&
     (*(int *)(param_1 + 0x98) != 8)) {
    if (*(int *)(param_1 + 0x8c) == 2) {
      piVar3 = gta2::Player_sub_41E260((Player *)(param_1 + 0x40),(int *)&local_c)
      ;
      local_c = (Player *)*piVar3;
      if (*(char *)(param_1 + 0x94) == '\0') {
        if (*(char *)(param_1 + 0x93) != '\0') {
          bVar2 = gta2::Player_IsCurrentPlayer((Player *)&local_c,(Player *)&DAT_0066acdc);
          iVar1 = _DAT_0066ab70;
          if ((CONCAT31(extraout_var_00,bVar2) == 0) ||
             (*(char *)(param_1 + 0x92) == '\0')) {
            bVar2 = gta2::Car_sub_403800((Car *)&local_c,
                                    (int *)(_DAT_0066ab70 + 0x44));
            if (CONCAT31(extraout_var_01,bVar2) != 0) {
              piVar3 = (int *)(iVar1 + 0x3c);
              puVar6 = local_4;
              pvVar4 = (void *)FUN_0049e850(local_8);
              puVar5 = (undefined4 *)
                       gta2::WorldCoordinateToScreenCoord(pvVar4,puVar6,piVar3);
              *param_2 = *puVar5;
              return;
            }
            bVar2 = gta2::Car_sub_403800((Car *)&local_c,(int *)(iVar1 + 0x40));
            if (CONCAT31(extraout_var_02,bVar2) != 0) {
              piVar3 = (int *)(iVar1 + 0x38);
              puVar6 = local_4;
              pvVar4 = (void *)FUN_0049e850(local_8);
              puVar5 = (undefined4 *)
                       gta2::WorldCoordinateToScreenCoord(pvVar4,puVar6,piVar3);
              *param_2 = *puVar5;
              return;
            }
            piVar3 = (int *)(iVar1 + 0x34);
            puVar6 = local_4;
            pvVar4 = (void *)FUN_0049e8e0(local_8);
            puVar5 = (undefined4 *)
                     gta2::WorldCoordinateToScreenCoord(pvVar4,puVar6,piVar3);
            *param_2 = *puVar5;
            return;
          }
        }
      }
      else {
        bVar2 = gta2::Player_IsCurrentPlayer((Player *)&local_c,(Player *)&DAT_0066acdc);
        if ((CONCAT31(extraout_var,bVar2) == 0) ||
           (*(char *)(param_1 + 0x92) == '\0')) {
          pS110 = &local_c;
          piVar3 = (int *)(_DAT_0066ab70 + 0x34);
          puVar6 = local_8;
          pvVar4 = (void *)FUN_0049e8e0(local_4);
          pvVar4 = gta2::JustCopyByPtrAtoC(pvVar4,puVar6);
          puVar5 = (undefined4 *)
                   gta2::WorldCoordinateToScreenCoord(pvVar4,pS110,piVar3);
          *param_2 = *puVar5;
          return;
        }
      }
    }
    else {
      if (*(char *)(param_1 + 0x93) != '\0') {
        puVar5 = (undefined4 *)FUN_0049e850(local_4);
        *param_2 = *puVar5;
        return;
      }
      if (*(char *)(param_1 + 0x94) != '\0') {
        puVar6 = local_4;
        pvVar4 = (void *)FUN_0049e850(local_8);
        puVar5 = (undefined4 *)gta2::JustCopyByPtrAtoC(pvVar4,puVar6);
        *param_2 = *puVar5;
        return;
      }
    }
  }
  *param_2 = _DAT_0066acdc;
  return;
}


// 0x004a1130: Player::sub_4A1130
// IDA: Player::sub_4A1130
// Ghidra: FUN_004a1130
undefined4 * gta2::Player_sub_4A1130(Player *param_1,undefined4 *param_2)
{
  SpriteS1 *pSVar1;
  int iVar2;
  byte bVar3;
  bool bVar4;
  void *self;
  undefined4 *puVar5;
  SpriteS1 *pSVar6;
  undefined3 extraout_var;
  SpriteS1 *pSVar7;
  short *psVar8;
  undefined2 *puVar9;
  short *unaff_EBP;
  void *unaff_EDI;
  SpriteS1 **pS110;
  int *piVar10;
  undefined1 local_30 [4];
  SpriteS1 *local_2c;
  SpriteS1 *local_28;
  SpriteS1 *local_24;
  undefined1 local_20 [12];
  undefined1 local_14 [8];
  undefined1 local_c [4];
  undefined1 local_8 [8];
  
  gta2::bitShiftLeft1(&local_24,NULL);
  String_ParseLine(local_8,&local_24,(undefined4 *)(_DAT_0066ab78 + 4));
  bVar3 = gta2::Player_sub_49DD80(param_1);
  iVar2 = _DAT_0066ab70;
  if (bVar3 != 0) {
    *param_2 = _DAT_0066acdc;
    return param_2;
  }
  pS110 = &local_24;
  piVar10 = (int *)(_DAT_0066ab70 + 8);
  self = (void *)FUN_004a0f30(&local_28);
  puVar5 = (undefined4 *)gta2::WorldCoordinateToScreenCoord(self,pS110,piVar10);
  pSVar1 = (SpriteS1 *)*puVar5;
  local_24 = pSVar1;
  if (param_1->field_0xad == '\0') {
    local_2c = _DAT_0066ac4c;
  }
  else {
    pSVar6 = gta2::S202_sub_401B20((Point2D *)&DAT_0066ac4c,(SpriteS1 *)&local_28,
                        (S127 *)(iVar2 + 0x14));
    local_2c = pSVar6->FirstElement;
  }
  iVar2 = *(int *)&param_1->field_0xa0;
  if (iVar2 == 0) {
    puVar5 = (undefined4 *)
             gta2::WorldCoordinateToScreenCoord
                       (&DAT_0066afdc,local_20,(int *)&local_2c);
    local_28 = (SpriteS1 *)*puVar5;
    local_30 = (undefined1  [4])_DAT_0066ab80;
    puVar5 = (undefined4 *)
             gta2::WorldCoordinateToScreenCoord
                       (&DAT_0066ac28,local_c,(int *)&DAT_0066afd0);
    local_24 = (SpriteS1 *)*puVar5;
    local_2c = *(SpriteS1 **)&param_1->KEY_UP;
  }
  else if ((0 < iVar2) && (iVar2 < 3)) {
    bVar4 = gta2::Player_IsCurrentPlayer((Player *)&local_24,(Player *)&DAT_0066acdc)
    ;
    pSVar6 = _DAT_0066acdc;
    if (CONCAT31(extraout_var,bVar4) == 0) {
      puVar5 = (undefined4 *)
               gta2::WorldCoordinateToScreenCoord
                         (&DAT_0066afdc,local_20,(int *)&local_2c);
      local_28 = (SpriteS1 *)*puVar5;
      local_30 = (undefined1  [4])_DAT_0066ab80;
      if (iVar2 == 1) {
        local_24 = (SpriteS1 *)0x1e;
        pSVar7 = FUN_00401bd0(&DAT_0066afe4,(SpriteS1 *)&local_2c,
                              (int *)&local_24);
        pSVar7 = gta2::S202_sub_401B20((Point2D *)&param_1->KEY_UP,
                            (SpriteS1 *)(local_20 + 4),(S127 *)pSVar7);
        local_2c = pSVar7->FirstElement;
        local_24 = pSVar6;
      }
      else {
        local_24 = (SpriteS1 *)0xffffffe2;
        pSVar7 = FUN_00401bd0(&DAT_0066afe4,(SpriteS1 *)(local_20 + 8),
                              (int *)&local_24);
        pSVar7 = gta2::S202_sub_401B20((Point2D *)&param_1->KEY_UP,(SpriteS1 *)local_14,
                            (S127 *)pSVar7);
        local_2c = pSVar7->FirstElement;
        local_24 = pSVar6;
      }
    }
    else {
      local_2c = *(SpriteS1 **)&param_1->KEY_UP;
      local_28 = _DAT_0066acdc;
      local_30 = (undefined1  [4])_DAT_0066acdc;
      local_24 = _DAT_0066acdc;
    }
  }
  pSVar6 = gta2::S202_sub_401B20((Point2D *)local_30,(SpriteS1 *)local_c,(S127 *)&local_24)
  ;
  FUN_00432860(local_14,&local_28,&pSVar6->FirstElement);
  psVar8 = (short *)FUN_0040f540(local_30,(int)&local_2c);
  puVar9 = (undefined2 *)
           gta2::sub_40E5A0((CarSystemManager *)&param_1->theta,(Ped *)&local_2c,
                      psVar8,unaff_EDI,unaff_EBP);
  FUN_004a0d40(param_2,local_8,*puVar9,local_14,pSVar1);
  return param_2;
}


// 0x004a1360: Player::sub_4A1360
// IDA: Player::sub_4A1360
// Ghidra: FUN_004a1360
undefined4 * gta2::Player_sub_4A1360(Player *param_1,undefined4 *param_2)
{
  byte bVar1;
  bool bVar2;
  void *pvVar3;
  undefined4 *puVar4;
  undefined3 extraout_var;
  uint *puVar5;
  SpriteS1 *pSVar6;
  SpriteS1 *pSVar7;
  S127 *pSVar8;
  int iVar9;
  undefined2 *puVar10;
  int *piVar11;
  struct Ped **pS110;
  short *pS110_00;
  SpriteS1 **ppSVar12;
  uint local_4c;
  SpriteS1 *local_48;
  SpriteS1 *local_44;
  SpriteS1 *local_40;
  GlassInfo local_3c;
  int local_c;
  undefined1 local_8 [8];
  
  gta2::bitShiftLeft1(&local_3c.pPed,NULL);
  iVar9 = _DAT_0066ab78;
  String_ParseLine(local_8,&local_3c.pPed,(undefined4 *)(_DAT_0066ab78 + 8));
  bVar1 = gta2::Player_sub_49DD80(param_1);
  if (bVar1 == 0) {
    piVar11 = (int *)(iVar9 + 0x20);
    pS110 = &local_3c.pPed;
    pvVar3 = (void *)FUN_004a0f30(&local_3c);
    puVar4 = (undefined4 *)gta2::WorldCoordinateToScreenCoord(pvVar3,pS110,piVar11);
    local_3c.pPed = (Ped *)*puVar4;
    if (param_1->field_0xad == '\0') {
      local_48 = _DAT_0066ac4c;
    }
    else {
      puVar4 = (undefined4 *)
               gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066ac4c,&local_3c,
                          (S127 *)(_DAT_0066ab70 + 0x14));
      local_48 = (SpriteS1 *)*puVar4;
    }
    iVar9 = *(int *)&param_1->field_0xa0;
    if (iVar9 == 0) {
      local_40 = _DAT_0066ab80;
      puVar4 = (undefined4 *)
               gta2::WorldCoordinateToScreenCoord
                         (&DAT_0066ac28,&local_3c.SpawnPoint,
                          (int *)&DAT_0066af30);
      local_3c.car = (Car *)*puVar4;
      if (*(char *)((int)&param_1->CameraOrPhysics_ + 2) == '\0') {
        param_1->field_0xa8 = 0;
        puVar4 = (undefined4 *)
                 gta2::WorldCoordinateToScreenCoord
                           (&DAT_0066afdc,&local_c,(int *)&local_48);
        local_48 = (SpriteS1 *)*puVar4;
        local_44 = _DAT_0066acdc;
      }
      else {
        if (param_1->field_0xa8 != -0x80) {
          param_1->field_0xa8 = param_1->field_0xa8 + '\x01';
        }
        iVar9 = _DAT_0066ab70;
        pS110_00 = &local_3c.count;
        piVar11 = (int *)(_DAT_0066ab70 + 0x20);
        pvVar3 = gta2::WorldCoordinateToScreenCoord
                           (&DAT_0066afdc,&local_3c.field17_0x20,
                            (int *)&local_48);
        puVar4 = (undefined4 *)
                 gta2::WorldCoordinateToScreenCoord(pvVar3,pS110_00,piVar11);
        local_48 = (SpriteS1 *)*puVar4;
        local_4c = (uint)(byte)param_1->field_0xa8;
        ppSVar12 = &local_44;
        pSVar7 = (SpriteS1 *)&local_3c.field19_0x28;
        local_44 = (SpriteS1 *)0x80;
        pSVar6 = FUN_00401bd0((void *)(iVar9 + 0x10),
                              (SpriteS1 *)&local_3c.field20_0x2c,
                              (int *)&local_4c);
        pSVar7 = gta2::S122_sub_401BF0((Model *)pSVar6,pSVar7,(int *)ppSVar12);
        local_44 = pSVar7->FirstElement;
      }
      local_4c._0_1_ = param_1->KEY_UP;
      local_4c._1_1_ = param_1->Backward;
      local_4c._2_1_ = param_1->RotateLeft;
      local_4c._3_1_ = param_1->RotateRight;
    }
    else if ((0 < iVar9) && (iVar9 < 3)) {
      bVar2 = gta2::Player_IsCurrentPlayer((Player *)&local_3c.pPed,(Player *)&DAT_0066acdc);
      pSVar7 = _DAT_0066acdc;
      if (CONCAT31(extraout_var,bVar2) == 0) {
        puVar4 = (undefined4 *)
                 gta2::WorldCoordinateToScreenCoord
                           (&DAT_0066afdc,&local_3c.SpawnPoint,(int *)&local_48)
        ;
        local_48 = (SpriteS1 *)*puVar4;
        local_40 = _DAT_0066ab80;
        if (iVar9 == 1) {
          local_3c.car = (Car *)0x1e;
          pSVar6 = FUN_00401bd0(&DAT_0066afe4,(SpriteS1 *)&local_3c.field_0xc,
                                (int *)&local_3c);
          puVar5 = (uint *)gta2::Player_sub_401B40((SpawnPoint *)&param_1->KEY_UP,
                                      (GlassInfo *)&local_3c.field_0x10,
                                      (S127 *)pSVar6);
          local_4c = *puVar5;
        }
        else {
          local_3c.car = (Car *)0xffffffe2;
          pSVar6 = FUN_00401bd0(&DAT_0066afe4,(SpriteS1 *)&local_3c.field11_0x14
                                ,(int *)&local_3c);
          puVar5 = (uint *)gta2::Player_sub_401B40((SpawnPoint *)&param_1->KEY_UP,
                                      (GlassInfo *)&local_3c.field12_0x18,
                                      (S127 *)pSVar6);
          local_4c = *puVar5;
        }
      }
      else {
        local_4c._0_1_ = param_1->KEY_UP;
        local_4c._1_1_ = param_1->Backward;
        local_4c._2_1_ = param_1->RotateLeft;
        local_4c._3_1_ = param_1->RotateRight;
        local_48 = _DAT_0066acdc;
        local_40 = _DAT_0066acdc;
      }
      local_3c.car = (Car *)pSVar7;
      local_44 = pSVar7;
      param_1->field_0xa8 = 0;
    }
    pSVar8 = (S127 *)&local_44;
    pSVar7 = (SpriteS1 *)&local_c;
    pSVar6 = gta2::S202_sub_401B20((Point2D *)&local_40,(SpriteS1 *)&local_3c.field20_0x2c,
                        (S127 *)&local_3c);
    pSVar7 = gta2::S202_sub_401B20((Point2D *)pSVar6,pSVar7,pSVar8);
    FUN_00432860(&local_3c.field17_0x20,&local_48,&pSVar7->FirstElement);
    gta2::Tango_sub_49E3A0((Car *)&local_3c.field17_0x20,
                      (int *)(_DAT_0066ab70 + 0x1c));
    pSVar8 = (S127 *)gta2::Player_sub_41E260((Player *)&param_1->S103_,&local_c);
    puVar4 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066add0,
                        (GlassInfo *)&local_3c.field19_0x28,pSVar8);
    local_3c.car = (Car *)*puVar4;
    piVar11 = (int *)gta2::WorldCoordinateToScreenCoord
                               (&DAT_0066add0,&local_c,(int *)&DAT_0066ac3c);
    puVar4 = (undefined4 *)
             gta2::sub_401B90((Player *)&local_3c,&local_3c.field20_0x2c,piVar11);
    local_3c.car = (Car *)*puVar4;
    pvVar3 = gta2::WorldCoordinateToScreenCoord(&local_4c,&local_c,(int *)&local_3c);
    iVar9 = FUN_0040f540(&local_4c,(int)pvVar3);
    puVar10 = (undefined2 *)
              gta2::SpriteS1_sub_40E5D0((CarSystemManager *)&param_1->theta,(Ped *)&local_48,
                         iVar9);
    FUN_004a0d40(param_2,local_8,*puVar10,&local_3c.field17_0x20,local_3c.pPed);
    return param_2;
  }
  *param_2 = _DAT_0066acdc;
  return param_2;
}


// 0x004a16b0: Player::sub_4A16B0
// IDA: Player::sub_4A16B0
// Ghidra: Player::FUN_004a16b0
void gta2::Player_sub_4A16B0(Player *self)
{
  undefined4 uVar1;
  bool bVar2;
  void *pvVar3;
  SpriteS1 *pSVar4;
  S127 *pS127;
  int *piVar5;
  undefined3 extraout_var;
  undefined4 *puVar6;
  SpriteS1 **ppSVar7;
  undefined1 *pS110;
  undefined1 local_18 [4];
  SpriteS1 *local_14;
  int local_10;
  undefined1 local_c [8];
  undefined1 local_4 [4];
  
  piVar5 = (int *)local_18;
  if (self->CarPlayerPre->PhysicsBitmask != 2) {
    local_18 = (undefined1  [4])(int)(char)self->field_0xad;
    pSVar4 = (SpriteS1 *)&local_14;
    pvVar3 = (void *)FUN_0049f720(&local_10);
    pSVar4 = FUN_00401bd0(pvVar3,pSVar4,piVar5);
    *(SpriteS1 **)&self->KEY_UP = pSVar4->FirstElement;
    return;
  }
  pS127 = (S127 *)gta2::Player_sub_41E260((Player *)&self->S103_,&local_10);
  piVar5 = (int *)gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066add0,(GlassInfo *)&local_14,
                             pS127);
  local_18 = (undefined1  [4])*piVar5;
  bVar2 = gta2::Point2D_FUN_004037e0((Point2D *)local_18,(SpriteS1 *)&DAT_0066b060);
  if (CONCAT31(extraout_var,bVar2) != 0) {
    local_18 = (undefined1  [4])_DAT_0066b060;
  }
  local_14 = (SpriteS1 *)(int)(char)self->field_0xad;
  piVar5 = (int *)gta2::WorldCoordinateToScreenCoord
                            (&DAT_0066add0,&local_10,(int *)&DAT_0066ae10);
  piVar5 = (int *)gta2::sub_401B90((Player *)local_18,local_c,piVar5);
  pS110 = local_18;
  ppSVar7 = &local_14;
  pSVar4 = (SpriteS1 *)(local_c + 4);
  pvVar3 = (void *)FUN_0049f720(local_4);
  pSVar4 = FUN_00401bd0(pvVar3,pSVar4,(int *)ppSVar7);
  puVar6 = (undefined4 *)gta2::WorldCoordinateToScreenCoord(pSVar4,pS110,piVar5);
  uVar1 = *puVar6;
  self->KEY_UP = (bool)(char)uVar1;
  self->Backward = (bool)(char)((uint)uVar1 >> 8);
  self->RotateLeft = (bool)(char)((uint)uVar1 >> 0x10);
  self->RotateRight = (bool)(char)((uint)uVar1 >> 0x18);
  return;
}


// 0x004a17a0: Player::FUN_004a17a0
// IDA: sub_4A17A0
// Ghidra: Player::FUN_004a17a0
byte gta2::Player_FUN_004a17a0(Player *self)
{
  bool bVar1;
  struct Player *pPlayer;
  
  pPlayer = self;
  gta2::Player_FUN_0049ea00(self,(Player *)&pPlayer);
  bVar1 = gta2::Player_sub_40CE70((Player *)&self->Revs,(Player *)&pPlayer);
  return bVar1;
}


// 0x004a17c0: Player::sub_4A17C0
// IDA: Player::sub_4A17C0
// Ghidra: Player::FUN_004a17c0
void * gta2::Player_sub_4A17C0(Player *self)
{
  struct EngineStruct *pEVar1;
  Turrel *pTVar2;
  bool bVar3;
  byte bVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  void *pvVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  undefined3 extraout_var_02;
  SpriteS1 *pSVar10;
  undefined3 extraout_var_03;
  undefined4 *puVar11;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  undefined3 extraout_var_08;
  undefined3 extraout_var_09;
  undefined3 extraout_var_10;
  undefined3 extraout_var_11;
  undefined3 extraout_var_12;
  undefined3 extraout_var_13;
  undefined3 extraout_var_14;
  S86_7 *this_00;
  Turrel *local_8;
  undefined1 local_4 [4];
  
  FUN_0040f580(&local_8,&self->theta);
  _DAT_0066ae0c = _DAT_0066acdc;
  pEVar1 = self->CarPlayerPre->EngineStruct_;
  if ((pEVar1 != NULL) && ((pEVar1->field12_0x24 & 0x2000) == 0)) {
    _DAT_0066ae0c = _DAT_0066acdc;
    return pEVar1;
  }
  bVar3 = gta2::Player_IsCurrentPlayer((Player *)&self->KEY_UP,(Player *)&DAT_0066acdc);
  if (CONCAT31(extraout_var,bVar3) == 0) {
    return NULL;
  }
  bVar4 = gta2::Player_FUN_004a17a0(self);
  if (bVar4 == 0) {
    return (void *)CONCAT31(extraout_var_00,bVar4);
  }
  bVar4 = gta2::Player_sub_40F840(self);
  if (bVar4 == 0) {
    return (void *)CONCAT31(extraout_var_01,bVar4);
  }
  pvVar5 = (void *)FUN_00420360(&self->S103_);
  if (pvVar5 != NULL) {
    return pvVar5;
  }
  if (*(void **)&self->field_0xa0 != NULL) {
    return *(void **)&self->field_0xa0;
  }
  pvVar5 = gta2::Player_sub_401B40((SpawnPoint *)&self->Debug,(GlassInfo *)local_4,
                      (S127 *)&DAT_0066ac4c);
  iVar6 = DecoderFloat(pvVar5);
  iVar7 = DecoderFloat(&self->field28_0x3c);
  iVar8 = DecoderFloat(&self->field27_0x38);
  pvVar5 = (void *)gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct,iVar8,iVar7,iVar6);
  if (pvVar5 == NULL) {
    return NULL;
  }
  if ((*(byte *)((int)pvVar5 + 0xb) & 3) != 1) {
    return pvVar5;
  }
  if ((*(byte *)((int)pvVar5 + 10) & 0x33) != 0) {
    piVar9 = (int *)gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066ac1c,(GlassInfo *)local_4,
                               (S127 *)&DAT_0066b038);
    bVar3 = gta2::Car_sub_403800((Car *)&local_8,piVar9);
    if (CONCAT31(extraout_var_02,bVar3) != 0) {
      pSVar10 = gta2::S202_sub_401B20((Point2D *)&DAT_0066ac1c,(SpriteS1 *)local_4,
                           (S127 *)&DAT_0066b038);
      bVar3 = gta2::Point2D_FUN_004037e0((Point2D *)&local_8,pSVar10);
      if (CONCAT31(extraout_var_03,bVar3) != 0) {
        puVar11 = (undefined4 *)
                  gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066ac1c,(GlassInfo *)local_4,
                             (S127 *)&local_8);
        _DAT_0066ae0c = (Turrel *)*puVar11;
        goto LAB_004a1a36;
      }
    }
    piVar9 = (int *)gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066acfc,(GlassInfo *)local_4,
                               (S127 *)&DAT_0066b038);
    bVar3 = gta2::Car_sub_403800((Car *)&local_8,piVar9);
    if (CONCAT31(extraout_var_04,bVar3) != 0) {
      pSVar10 = gta2::S202_sub_401B20((Point2D *)&DAT_0066acfc,(SpriteS1 *)local_4,
                           (S127 *)&DAT_0066b038);
      bVar3 = gta2::Point2D_FUN_004037e0((Point2D *)&local_8,pSVar10);
      if (CONCAT31(extraout_var_05,bVar3) != 0) {
        puVar11 = (undefined4 *)
                  gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066acfc,(GlassInfo *)local_4,
                             (S127 *)&local_8);
        _DAT_0066ae0c = (Turrel *)*puVar11;
      }
    }
    goto LAB_004a1a36;
  }
  if ((*(byte *)((int)pvVar5 + 10) & 0xcc) == 0) goto LAB_004a1a36;
  piVar9 = (int *)gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066aed0,(GlassInfo *)local_4,
                             (S127 *)&DAT_0066b038);
  bVar3 = gta2::Car_sub_403800((Car *)&local_8,piVar9);
  if (CONCAT31(extraout_var_06,bVar3) == 0) {
LAB_004a19d3:
    piVar9 = (int *)gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066af34,(GlassInfo *)local_4,
                               (S127 *)&DAT_0066b038);
    bVar3 = gta2::Car_sub_403800((Car *)&local_8,piVar9);
    if (CONCAT31(extraout_var_08,bVar3) != 0) {
      puVar11 = (undefined4 *)
                gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066af34,(GlassInfo *)local_4,
                           (S127 *)&local_8);
      _DAT_0066ae0c = (Turrel *)*puVar11;
      goto LAB_004a1a36;
    }
    bVar3 = gta2::Point2D_FUN_004037e0((Point2D *)&local_8,(SpriteS1 *)&DAT_0066b038)
    ;
    if (CONCAT31(extraout_var_09,bVar3) == 0) goto LAB_004a1a36;
    puVar11 = (undefined4 *)gta2::JustCopyByPtrAtoC(&local_8,local_4);
  }
  else {
    pSVar10 = gta2::S202_sub_401B20((Point2D *)&DAT_0066aed0,(SpriteS1 *)local_4,
                         (S127 *)&DAT_0066b038);
    bVar3 = gta2::Point2D_FUN_004037e0((Point2D *)&local_8,pSVar10);
    if (CONCAT31(extraout_var_07,bVar3) == 0) goto LAB_004a19d3;
    puVar11 = (undefined4 *)
              gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066aed0,(GlassInfo *)local_4,
                         (S127 *)&local_8);
  }
  _DAT_0066ae0c = (Turrel *)*puVar11;
LAB_004a1a36:
  bVar3 = gta2::Car_IsTrainOrTrainCarriage((Car *)&DAT_0066ae0c,(Car *)&DAT_0066acdc)
  ;
  this_00 = (S86_7 *)CONCAT31(extraout_var_10,bVar3);
  if (this_00 != NULL) {
    puVar11 = (undefined4 *)gta2::Car_sub_4234A0(self->CarPlayerPre,local_4);
    pTVar2 = (Turrel *)*puVar11;
    local_8 = pTVar2;
    bVar3 = gta2::Car_sub_403800((Car *)&DAT_0066ae0c,(int *)&DAT_0066acdc);
    if (CONCAT31(extraout_var_11,bVar3) == 0) {
      pSVar10 = (SpriteS1 *)gta2::JustCopyByPtrAtoC(&local_8,local_4);
      bVar3 = gta2::Point2D_FUN_004037e0((Point2D *)&DAT_0066ae0c,pSVar10);
      puVar11 = (undefined4 *)CONCAT31(extraout_var_13,bVar3);
      if (puVar11 != NULL) {
        puVar11 = (undefined4 *)gta2::JustCopyByPtrAtoC(&local_8,local_4);
        _DAT_0066ae0c = (Turrel *)*puVar11;
      }
    }
    else {
      bVar3 = gta2::Car_sub_403800((Car *)&DAT_0066ae0c,(int *)&local_8);
      puVar11 = (undefined4 *)CONCAT31(extraout_var_12,bVar3);
      if (puVar11 != NULL) {
        _DAT_0066ae0c = pTVar2;
      }
    }
    this_00 = (S86_7 *)CONCAT31((int3)((uint)puVar11 >> 8),gDoShowInstruments);
    if (((gDoShowInstruments != 0) &&
        (this_00 = (S86_7 *)self->CarPlayerPre->Driver, this_00 != NULL)) &&
       (this_00 = *(S86_7 **)&this_00->field_0x15c, this_00 != NULL)) {
      bVar4 = gta2::Player_GetCurrentPlayer((Player *)this_00);
      this_00 = (S86_7 *)CONCAT31(extraout_var_14,bVar4);
      if (bVar4 != 0) {
        this_00 = gta2::S86_7_PrintText(&gHud->S86_7_,L"snap",0,0x40,_DAT_00672f18,1)
        ;
      }
    }
    gta2::Player_sub_40E530((Point2D *)&self->DeathReason,(int *)&DAT_0066ae0c);
  }
  return this_00;
}


// 0x004a1b20: Player::sub_4A1B20
// IDA: Player::sub_4A1B20
// Ghidra: Player::FUN_004a1b20
void gta2::Player_sub_4A1B20(Player *self)
{
  byte bVar1;
  bool bVar2;
  Car *pCar;
  undefined3 extraout_var;
  struct Ped *pPVar3;
  S103 **pPlayer;
  Car **ppCVar4;
  int local_10;
  Car *local_c;
  undefined1 local_8 [8];
  
  bVar1 = gta2::Player_sub_49DD80(self);
  if (bVar1 == 0) {
    bVar1 = gta2::Player_sub_40F840(self);
    if (bVar1 == 0) {
      local_c = *(Car **)(_DAT_0066ab70 + 0x40);
    }
    else {
      local_c = *(Car **)(_DAT_0066ab70 + 0x28);
    }
    ppCVar4 = &local_c;
    pPlayer = &self->S103_;
    pCar = (Car *)gta2::Player_sub_41E260((Player *)pPlayer,&local_10);
    bVar2 = gta2::Car_sub_403800(pCar,(int *)ppCVar4);
    if (CONCAT31(extraout_var,bVar2) != 0) {
      pPVar3 = (Ped *)gta2::Player_FUN_0040f790((Player *)pPlayer,(undefined2 *)&local_10);
      FUN_0041e210(local_8,(GlassInfo *)&local_c,pPVar3);
      gta2::Player_FUN_0049e480((Player *)pPlayer,(SpriteS1 *)local_8);
    }
  }
  return;
}


// 0x004a1ba0: Player::sub_4A1BA0
// IDA: Player::sub_4A1BA0
// Ghidra: Player::FUN_004a1ba0
undefined1 gta2::Player_sub_4A1BA0(Player *self)
{
  byte bVar1;
  
  bVar1 = gta2::Player_sub_49F170(self);
  if (bVar1 == 0) {
    *(undefined1 *)&self->CameraOrPhysics_ = 0;
  }
  else {
    if (*(char *)&self->CameraOrPhysics_ != -1) {
      *(char *)&self->CameraOrPhysics_ = *(char *)&self->CameraOrPhysics_ + '\x01'
      ;
    }
    if (0x13 < *(byte *)&self->CameraOrPhysics_) {
      return 1;
    }
  }
  return 0;
}


// 0x004a1be0: Player::sub_4A1BE0
// IDA: Player::sub_4A1BE0
// Ghidra: ---
int gta2::Player_sub_4A1BE0(Player *self)
{
  int v2; // eax
  int result; // eax
  int a2; // [esp+8h] [ebp-4h] BYREF

  gta2::S103_sub_41E1E0((S103 *)&self->S103_4);
  gta2::bitShiftLeft1(&a2, 0);
  *(_DWORD *)&self->prevWeapon = a2;
  *(_DWORD *)&self->Up = unk_66ACDC;
  gta2::Player_sub_49FAC0(self);
  BYTE1(self->CameraOrPhysics1) = 0;
  BYTE2(self->CameraOrPhysics1) = 0;
  HIBYTE(self->CameraOrPhysics1) = 0;
  self->field_94 = 0;
  self->field_95 = 0;
  self->gapAD[0] = 0;
  self->field_A9 = -1;
  self->field_A8 = 0;
  LOBYTE(self->CameraOrPhysics1) = 0;
  a2 = 0;
  gta2::Player_sub_49DD20(self, &a2);
  self->gapA4[0] = 0;
  self->State = 0;
  self->AudioManager_ = 0;
  self->gapA4[1] = 0;
  self->gapA4[2] = 0;
  gta2::S103_sub_41E1E0((S103 *)&self->S103_);
  gta2::S103_sub_41E1E0((S103 *)&self->S103_1);
  gta2::S103_sub_41E1E0((S103 *)&self->pS103);
  gta2::S103_sub_41E1E0((S103 *)&self->S103_2);
  *(_DWORD *)&self->AttackIsChanged = 1;
  *(_DWORD *)&self->Rotate = 0;
  v2 = unk_66AE74;
  self->field_AC = 0;
  self->field_60 = v2;
  self->field_64 = unk_66ABE4;
  self->MultiPlayerMode = unk_66ACDC;
  result = unk_66ACDC;
  self->field_84 = unk_66ACDC;
  self->field_88 = unk_66ACDC;
  self->sbw = 0;
  self->tpa = 0;
  return result;
}


// 0x004a1d30: Player::FUN_004a1d30
// IDA: sub_4A1D30
// Ghidra: Player::FUN_004a1d30
void * gta2::Player_FUN_004a1d30(Player *self,Car *pCar)
{
  byte bVar1;
  undefined3 extraout_var;
  void *pvVar2;
  
  self->CarPlayerPre = pCar;
  bVar1 = gta2::Car_IsDriverPlayer(pCar);
  pvVar2 = (void *)CONCAT31(extraout_var,bVar1);
  if (bVar1 != 0) {
    gta2::Player_SetAttackIsChanged(self);
    return pvVar2;
  }
  gta2::Player_SetAttackChanged(self);
  return pvVar2;
}


// 0x004a1da0: Player::sub_4A1DA0
// IDA: Player::sub_4A1DA0
// Ghidra: ---
char gta2::Player_sub_4A1DA0(Player *self)
{
  char result; // al
  double v3; // st7
  double v4; // st7
  wchar_t *v5; // eax
  double v6; // st7
  SpriteS1 *v7; // eax
  double v8; // st7
  double v9; // st7
  void *v10; // ebx
  double v11; // st7
  int v12; // eax
  int v13; // ebx
  void *v14; // ebp
  double v15; // [esp+8h] [ebp-38h]
  double v16; // [esp+10h] [ebp-30h]
  double v17; // [esp+18h] [ebp-28h]
  double v18; // [esp+18h] [ebp-28h]
  double v19; // [esp+20h] [ebp-20h]
  double v20; // [esp+20h] [ebp-20h]
  char v21[4]; // [esp+3Ch] [ebp-4h] BYREF

  result = do_show_physics;
  if ( do_show_physics )
  {
    gta2::Player_sub_49ECC0(self);
    v19 = gta2::FloatDecoder(&self->field_6C);
    v17 = gta2::FloatDecoder(&self->field_3C);
    v16 = gta2::FloatDecoder(&self->field_38);
    v15 = gta2::FloatDecoder(&self->RESPECT);
    v3 = gta2::FloatDecoder(&self->S103_5);
    ShowTextDisplay(&TextWcharT, (char *)off_5742A8, v3, v15, v16, v17, v19);
    gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, 0, 64, unk_672F18, 1);
    v20 = gta2::FloatDecoder(&self->prevWeapon);
    v18 = gta2::FloatDecoder(&self->DeathReason);
    v4 = gta2::FloatDecoder(&self->S103_4);
    ShowTextDisplay(&TextWcharT, (char *)L"linvel = (%3.3f,%3.3f) angvelrad = %3.3f", v4, v18, v20);
    gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, 0, 80, unk_672F18, 1);
    v5 = gta2::sub_49E240((__int16 *)&self->field_58);
    ShowTextDisplay(&TextWcharT, (char *)L"theta = %s", v5);
    gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, 0, 96, unk_672F18, 1);
    v6 = gta2::FloatDecoder(&self->Forward);
    ShowTextDisplay(&TextWcharT, (char *)L"pointingangrad = %3.3f", v6);
    gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, 0, 112, unk_672F18, 1);
    v7 = gta2::Player_sub_49F660(self, (SpriteS1 *)v21);
    v8 = gta2::FloatDecoder(v7);
    ShowTextDisplay(&TextWcharT, (char *)off_5741EC, v8);
    gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, 0, 128, unk_672F18, 1);
    v9 = gta2::FloatDecoder(&self->field_84);
    ShowTextDisplay(&TextWcharT, (char *)L"front skid = %3.3f", v9);
    v10 = (void *)gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, 0, 144, unk_672F18, 1);
    if ( gta2::Player_sub_40CE70((Player *)&self->field_84, (_DWORD *)(unk_66AB78 + 36))
      || self->field_AC && gta2::Car_sub_403800((Car *)(unk_66AB70 + 8), (int)&unk_66ACDC) )
    {
      sub_45AFD0(v10, 5);
    }
    v11 = gta2::FloatDecoder(&self->field_88);
    ShowTextDisplay(&TextWcharT, (char *)off_5741A0, v11);
    v12 = gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, 0, 160, unk_672F18, 1);
    v13 = unk_66AB78;
    v14 = (void *)v12;
    if ( gta2::Player_sub_40CE70((Player *)&self->field_88, (_DWORD *)(unk_66AB78 + 40))
      || self->field_AC && gta2::Car_sub_403800((Car *)(v13 + 32), (int)&unk_66ACDC) )
    {
      sub_45AFD0(v14, 5);
    }
    ShowTextDisplay(&TextWcharT, (char *)L"surface_mode = %d sbw = %d tpa = %d", self->State, self->sbw, self->tpa);
    return gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, 0, 176, unk_672F18, 1);
  }
  return result;
}


// 0x004a20e0: Player::sub_4A20E0
// IDA: Player::sub_4A20E0
// Ghidra: FUN_004a20e0
void gta2::Player_sub_4A20E0(Player *param_1)
{
  bool bVar1;
  int *piVar2;
  void *pvVar3;
  undefined4 *puVar4;
  undefined1 *puVar5;
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined4 local_8;
  undefined4 local_4;
  
  if ((((param_1->field_0xa5 == '\x01') &&
       (*(char *)((int)&param_1->CameraOrPhysics_ + 2) == '\0')) &&
      (*(char *)((int)&param_1->CameraOrPhysics_ + 1) == '\0')) &&
     (bVar1 = gta2::Car_IsTrainOrTrainCarriage(param_1->CarPlayerPre), !bVar1)) {
    switch(param_1->State) {
    case 1:
      local_8 = _DAT_0066acdc;
      piVar2 = (int *)FUN_004634e0(local_30,1);
      puVar4 = (undefined4 *)
               gta2::WorldCoordinateToScreenCoord(&DAT_0066b044,local_2c,piVar2);
      local_4 = *puVar4;
      gta2::Player_sub_4A0930(param_1);
      return;
    case 2:
      local_8 = _DAT_0066acdc;
      piVar2 = (int *)FUN_004634e0(local_28,1);
      puVar5 = local_24;
      pvVar3 = gta2::JustCopyByPtrAtoC(&DAT_0066b044,local_20);
      puVar4 = (undefined4 *)gta2::WorldCoordinateToScreenCoord(pvVar3,puVar5,piVar2);
      local_4 = *puVar4;
      break;
    case 3:
      piVar2 = (int *)FUN_004634e0(local_1c,1);
      puVar4 = (undefined4 *)
               gta2::WorldCoordinateToScreenCoord(&DAT_0066b044,local_18,piVar2);
      local_8 = *puVar4;
      local_4 = _DAT_0066acdc;
      gta2::Player_sub_4A0930(param_1);
      return;
    case 4:
      piVar2 = (int *)FUN_004634e0(local_14,1);
      puVar5 = local_10;
      pvVar3 = gta2::JustCopyByPtrAtoC(&DAT_0066b044,local_c);
      puVar4 = (undefined4 *)gta2::WorldCoordinateToScreenCoord(pvVar3,puVar5,piVar2);
      local_8 = *puVar4;
      local_4 = _DAT_0066acdc;
      break;
    default:
      goto switchD_004a212f_caseD_4;
    }
    gta2::Player_sub_4A0930(param_1);
  }
switchD_004a212f_caseD_4:
  return;
}


// 0x004a2240: Player::sub_4A2240
// IDA: Player::sub_4A2240
// Ghidra: FUN_004a2240
void gta2::Player_sub_4A2240(Player *param_1)
{
  int iVar1;
  Sprite *pSVar2;
  undefined4 uVar3;
  bool bVar4;
  byte bVar5;
  char cVar6;
  undefined3 extraout_var;
  undefined4 *puVar7;
  S127 *pS127;
  SpriteS1 *pSVar8;
  uint uVar9;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  SpriteS1 *pSVar10;
  undefined3 extraout_var_03;
  Car *self;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  undefined3 extraout_var_08;
  int *pConditionValue;
  undefined3 extraout_var_09;
  undefined3 extraout_var_10;
  undefined3 extraout_var_11;
  undefined3 extraout_var_12;
  undefined3 extraout_var_13;
  undefined3 extraout_var_14;
  undefined4 *puVar11;
  undefined3 extraout_var_15;
  SpriteS1 **this_00;
  Car *pCVar12;
  SpriteS1 *local_c;
  SpriteS1 *local_8;
  undefined1 local_4 [4];
  undefined3 extraout_var_00;
  
  uVar9 = param_1->State;
  if (uVar9 == 6) {
    puVar11 = &param_1->Debug;
    bVar4 = gta2::Car_sub_403800((Car *)puVar11,(int *)&DAT_0066ad1c);
    if (CONCAT31(extraout_var,bVar4) != 0) {
      *puVar11 = _DAT_0066ad1c;
    }
    puVar7 = (undefined4 *)
             FUN_00469570(&local_8,param_1->field27_0x38,param_1->field28_0x3c,
                          *puVar11);
    pSVar10 = (SpriteS1 *)*puVar7;
    local_8 = pSVar10;
    pS127 = (S127 *)gta2::WorldCoordinateToScreenCoord
                              (&DAT_0066abc8,&local_c,(int *)&stack0x00000004);
    pSVar8 = gta2::S202_sub_401B20((Point2D *)puVar11,(SpriteS1 *)local_4,pS127);
    pSVar8 = pSVar8->FirstElement;
    local_c = pSVar8;
    bVar4 = gta2::Player_CheckCondition((Player *)&local_c,(int *)&local_8);
    uVar9 = CONCAT31(extraout_var_00,bVar4);
    if (uVar9 == 0) {
      bVar4 = gta2::Car_sub_403800((Car *)&local_c,(int *)&DAT_0066ad1c);
      uVar9 = CONCAT31(extraout_var_01,bVar4);
      pSVar10 = _DAT_0066ad1c;
      if (uVar9 == 0) goto LAB_004a2563;
    }
  }
  else {
    if ((uVar9 != 7) && (uVar9 != 8)) {
      puVar11 = (undefined4 *)
                gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct,(float10 *)local_4,
                           (float10 *)param_1->field27_0x38,
                           (float10 *)param_1->field28_0x3c);
      pSVar8 = (SpriteS1 *)*puVar11;
      local_c = pSVar8;
      bVar4 = gta2::Player_IsCurrentPlayer((Player *)&local_c,(Player *)&DAT_0066acdc);
      if (CONCAT31(extraout_var_02,bVar4) != 0) {
        local_c = _DAT_0066ac4c;
        pSVar8 = _DAT_0066ac4c;
      }
      puVar11 = &param_1->Debug;
      pSVar10 = gta2::S202_sub_401B20((Point2D *)puVar11,(SpriteS1 *)local_4,
                           (S127 *)&DAT_0066aec0);
      bVar4 = gta2::Player_sub_40CE70((Player *)&local_c,(Player *)pSVar10);
      if (CONCAT31(extraout_var_03,bVar4) != 0) {
        iVar1 = param_1->State;
        if ((((iVar1 == 1) || (iVar1 == 2)) || (iVar1 == 3)) || (iVar1 == 4)) {
          pCVar12 = (Car *)&DAT_0066acdc;
          self = (Car *)FUN_0042a630(local_4,&local_c);
          bVar4 = gta2::Car_IsTrainOrTrainCarriage(self,pCVar12);
          if (CONCAT31(extraout_var_04,bVar4) != 0) {
            pSVar10 = gta2::S202_sub_401B20((Point2D *)puVar11,(SpriteS1 *)local_4,
                                 (S127 *)&DAT_0066ac4c);
            bVar4 = gta2::Player_CheckCondition((Player *)&local_c,(int *)pSVar10);
            if (CONCAT31(extraout_var_05,bVar4) != 0) goto LAB_004a2475;
          }
        }
        puVar7 = (undefined4 *)
                 gta2::Player_sub_401B40((SpawnPoint *)&local_c,(GlassInfo *)local_4,
                            (S127 *)&DAT_0066ac10);
        puVar7 = (undefined4 *)
                 FUN_00469570(&local_8,param_1->field27_0x38,
                              param_1->field28_0x3c,*puVar7);
        pSVar8 = (SpriteS1 *)*puVar7;
        local_c = pSVar8;
        bVar4 = gta2::Car_sub_403800((Car *)&local_c,puVar11);
        if (CONCAT31(extraout_var_06,bVar4) != 0) {
          puVar7 = (undefined4 *)
                   gta2::Player_sub_401B40((SpawnPoint *)&local_c,(GlassInfo *)local_4,
                              (S127 *)&DAT_0066ac10);
          puVar7 = (undefined4 *)
                   FUN_00469850(&local_8,param_1->field27_0x38,
                                param_1->field28_0x3c,*puVar7);
          pSVar10 = (SpriteS1 *)*puVar7;
          local_8 = pSVar10;
          bVar4 = gta2::Car_sub_403800((Car *)&local_8,(int *)&DAT_0066acdc);
          if (CONCAT31(extraout_var_07,bVar4) != 0) {
            pSVar8 = pSVar10;
            local_c = pSVar10;
          }
        }
        pSVar10 = gta2::S202_sub_401B20((Point2D *)puVar11,(SpriteS1 *)local_4,
                             (S127 *)&DAT_0066ac4c);
        bVar4 = gta2::Player_sub_40CE70((Player *)&local_c,(Player *)pSVar10);
        if (CONCAT31(extraout_var_08,bVar4) != 0) {
          pSVar8 = (SpriteS1 *)*puVar11;
          local_c = pSVar8;
        }
      }
LAB_004a2475:
      pConditionValue =
           (int *)gta2::Player_sub_401B40((SpawnPoint *)puVar11,(GlassInfo *)local_4,
                             (S127 *)&DAT_0066aec0);
      bVar4 = gta2::Player_CheckCondition((Player *)&local_c,pConditionValue);
      if ((CONCAT31(extraout_var_09,bVar4) != 0) ||
         (((bVar4 = gta2::Point2D_FUN_004037e0((Point2D *)&local_c,(SpriteS1 *)puVar11),
           CONCAT31(extraout_var_10,bVar4) != 0 && (param_1->field_0xaa != '\0')
           ) && (param_1->field_0xab != '\0')))) {
        puVar7 = (undefined4 *)FUN_0049fbe0(local_4,&local_8);
        param_1->ID = *puVar7;
        pSVar8 = gta2::S202_sub_401B20((Point2D *)puVar11,(SpriteS1 *)local_4,
                            (S127 *)&local_8);
        pSVar8 = pSVar8->FirstElement;
        local_c = pSVar8;
        bVar4 = gta2::Car_IsTrainOrTrainCarriage((Car *)&stack0x00000004,(Car *)&DAT_0066acdc);
        if (CONCAT31(extraout_var_11,bVar4) != 0) {
          FUN_0048a1a0(&param_1->ID,(int *)&stack0x00000004);
        }
        bVar4 = gta2::Car_sub_403800((Car *)&local_c,(int *)&DAT_0066ad1c);
        if (CONCAT31(extraout_var_12,bVar4) != 0) {
          local_c = _DAT_0066ad1c;
          pSVar8 = _DAT_0066ad1c;
        }
      }
      bVar4 = gta2::Point2D_FUN_004037e0((Point2D *)&local_c,(SpriteS1 *)puVar11);
      uVar9 = CONCAT31(extraout_var_13,bVar4);
      if (uVar9 == 0) goto LAB_004a2563;
      gta2::Player_sub_49EE80(param_1);
      pSVar2 = param_1->CarPlayerPre->CarSprite;
      gta2::SpriteS1_sub_420600(pSVar2,(int)pSVar2->Point2D1,
                          *(int *)&pSVar2->field_0x18,(int)pSVar8);
      bVar5 = gta2::SpriteS1_sub_4BD670((SpriteS1 *)param_1->CarPlayerPre->CarSprite);
      uVar9 = (uint)bVar5;
      if (bVar5 == 0) goto LAB_004a2563;
    }
    pSVar10 = (SpriteS1 *)param_1->Debug;
  }
  pSVar8 = pSVar10;
  local_c = pSVar8;
LAB_004a2563:
  cVar6 = (char)uVar9;
  gta2::Car_sub_414F70(param_1->CarPlayerPre);
  if (cVar6 != '\0') {
    gta2::Player_sub_49EE80(param_1);
    pSVar2 = param_1->CarPlayerPre->CarSprite;
    gta2::SpriteS1_sub_420600(pSVar2,(int)pSVar2->Point2D1,*(int *)&pSVar2->field_0x18
                        ,(int)pSVar8);
    gCarSystemManager->field44_0x60 = 2;
    gCarSystemManager->CarType = _DAT_0066acdc;
    gta2::S56_sub_4474E0(gCheckpoint,(SpriteS1 *)param_1->CarPlayerPre->CarSprite,2);
    gta2::Player_sub_40E530((Point2D *)&gCarSystemManager->CarType,(int *)&DAT_0066af60);
    this_00 = &gCarSystemManager->CarType;
    bVar4 = gta2::Car_sub_403800((Car *)this_00,(int *)&local_c);
    if (CONCAT31(extraout_var_14,bVar4) != 0) {
      local_c = *this_00;
    }
  }
  puVar11 = (undefined4 *)
            gta2::Player_sub_401B40((SpawnPoint *)&local_c,(GlassInfo *)local_4,
                       (S127 *)&param_1->Debug);
  uVar3 = *puVar11;
  param_1->field44_0x70 = (char)uVar3;
  param_1->field45_0x71 = (char)((uint)uVar3 >> 8);
  param_1->field46_0x72 = (char)((uint)uVar3 >> 0x10);
  param_1->field47_0x73 = (char)((uint)uVar3 >> 0x18);
  gta2::Player_sub_40E530((Point2D *)&param_1->Debug,(int *)&param_1->field44_0x70);
  bVar4 = gta2::Car_IsTrainOrTrainCarriage((Car *)&stack0x00000004,(Car *)&DAT_0066acdc);
  if (CONCAT31(extraout_var_15,bVar4) != 0) {
    FUN_0048a1a0(&param_1->field44_0x70,(int *)&stack0x00000004);
  }
  return;
}


// 0x004a2640: Player::sub_4A2640
// IDA: Player::sub_4A2640
// Ghidra: Player::FUN_004a2640
void gta2::Player_sub_4A2640(Player *self,undefined4 param_1)
{
  undefined4 *pSpriteS1;
  undefined4 *this_00;
  void *pvVar1;
  struct Player *this_01;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  bool bVar5;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  
  FUN_004a2240(param_1);
  pvVar1 = self->CarPlayerPre->S___;
  if (pvVar1 != NULL) {
    this_01 = *(Player **)(*(int *)((int)pvVar1 + 0xc) + 0x58);
    gta2::Player_sub_49ECC0(this_01);
    FUN_004a2240(param_1);
    gta2::Player_sub_49ECC0(self);
    pSpriteS1 = &this_01->Debug;
    this_00 = &self->Debug;
    bVar5 = gta2::Car_sub_403800((Car *)this_00,pSpriteS1);
    if (CONCAT31(extraout_var,bVar5) != 0) {
      *pSpriteS1 = *this_00;
      uVar2 = self->field45_0x71;
      uVar3 = self->field46_0x72;
      uVar4 = self->field47_0x73;
      this_01->field44_0x70 = self->field44_0x70;
      this_01->field45_0x71 = uVar2;
      this_01->field46_0x72 = uVar3;
      this_01->field47_0x73 = uVar4;
      return;
    }
    bVar5 = gta2::Point2D_FUN_004037e0((Point2D *)this_00,(SpriteS1 *)pSpriteS1);
    if (CONCAT31(extraout_var_00,bVar5) != 0) {
      *this_00 = *pSpriteS1;
      uVar2 = this_01->field45_0x71;
      uVar3 = this_01->field46_0x72;
      uVar4 = this_01->field47_0x73;
      self->field44_0x70 = this_01->field44_0x70;
      self->field45_0x71 = uVar2;
      self->field46_0x72 = uVar3;
      self->field47_0x73 = uVar4;
    }
  }
  return;
}


// 0x004a26c0: Player::sub_4A26C0
// IDA: Player::sub_4A26C0
// Ghidra: FUN_004a26c0
undefined1 gta2::Player_sub_4A26C0(Player *param_1,byte *param_2)
{
  byte bVar1;
  bool bVar2;
  char cVar3;
  int *piVar4;
  undefined3 extraout_var;
  undefined4 uVar5;
  Car *pCVar6;
  undefined4 *puVar7;
  struct Player *pPVar8;
  undefined3 extraout_var_00;
  void *pvVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  GlassInfo *pGVar14;
  int iVar15;
  undefined1 *puVar16;
  undefined1 *puVar17;
  struct Player *pPlayer;
  char *pcVar18;
  undefined1 local_2f;
  char local_2e;
  undefined1 local_2d;
  Sprite *local_2c;
  int local_28;
  undefined1 local_24 [4];
  undefined1 local_20 [8];
  undefined1 local_18 [8];
  undefined1 local_10 [12];
  
  local_2c = param_1->CarPlayerPre->CarSprite;
  param_1->field_0xab = 0;
  bVar1 = gta2::Player_sub_49DD80(param_1);
  if (bVar1 != 0) {
    piVar4 = (int *)gta2::JustCopyByPtrAtoC(&DAT_0066ad4c,local_24);
    bVar2 = gta2::Car_sub_403800((Car *)&param_1->ID,piVar4);
    if (CONCAT31(extraout_var,bVar2) != 0) {
      UseAmmo(&param_1->ID,(int *)&DAT_0066af58);
    }
  }
  uVar5 = gta2::FUN_00469b00(gMapRelatedStruct,param_1->field27_0x38,
                       param_1->field28_0x3c);
  if ((char)uVar5 == '\0') {
    iVar15 = 0;
    param_1->field81_0x9c = 0;
    bVar1 = FUN_004bd350(&local_28);
    *param_2 = bVar1;
    if ((local_28 == 1) || (local_28 == 2)) {
      param_1->field_0xab = 1;
    }
    if (*param_2 == 0) {
      iVar15 = param_1->State;
      if (((((iVar15 != 1) && (iVar15 != 2)) && (iVar15 != 3)) && (iVar15 != 4))
         || (cVar3 = FUN_004bd490(), cVar3 == '\0')) {
        param_1->State = 6;
        return 0;
      }
    }
    else {
      pCVar6 = param_1->CarPlayerPre;
      if (pCVar6->S___ != NULL) {
        iVar10 = FUN_0040f410(pCVar6);
        pCVar6 = *(Car **)(iVar10 + 0x58);
        if (pCVar6->LocksDoor != 6) goto LAB_004a284e;
      }
      bVar1 = 1;
      do {
        if ((*param_2 & bVar1) != bVar1) {
          gta2::bitShiftLeft1(local_24,(void *)0x32);
          puVar17 = local_20;
          pGVar14 = (GlassInfo *)&param_1->EnterControlStatus;
          puVar16 = local_18;
          pvVar9 = (void *)FUN_0049ea30(local_10,iVar15);
          pPVar8 = (Player *)FUN_0040f600(pvVar9,puVar16,pGVar14);
          pCVar6 = (Car *)gta2::Player_FUN_004202e0(pPVar8,puVar17,(int *)pCVar6);
          gta2::Player_ApplyCollisionVelocity(param_1,pCVar6);
        }
        iVar15 = iVar15 + 1;
        bVar1 = bVar1 * '\x02';
      } while (iVar15 < 4);
    }
  }
  else {
    *param_2 = 0;
    puVar7 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)&param_1->Debug,(GlassInfo *)local_24,
                        (S127 *)&DAT_0066ac4c);
    uVar5 = FUN_00465650(param_1->field27_0x38,param_1->field28_0x3c,*puVar7);
    param_1->field81_0x9c = uVar5;
  }
LAB_004a284e:
  pvVar9 = &param_1->Debug;
  pPlayer = (Player *)&DAT_0066acdc;
  local_2d = param_1->State == 6;
  pPVar8 = (Player *)FUN_0042a630(local_24,pvVar9);
  bVar2 = gta2::Player_IsCurrentPlayer(pPVar8,pPlayer);
  if (CONCAT31(extraout_var_00,bVar2) != 0) {
    pvVar9 = gta2::Player_sub_401B40((SpawnPoint *)pvVar9,(GlassInfo *)local_24,
                        (S127 *)&DAT_0066ac4c);
  }
  iVar10 = DecoderFloat(pvVar9);
  pcVar18 = &local_2e;
  puVar17 = &local_2f;
  iVar15 = iVar10;
  iVar11 = DecoderFloat(&param_1->field28_0x3c);
  iVar12 = DecoderFloat(&param_1->field27_0x38);
  uVar13 = FUN_0049ebe0(iVar12,iVar11,iVar15,puVar17,pcVar18);
  uVar13 = uVar13 & 0xff;
  if (uVar13 != 5) {
    param_1->State = uVar13;
    param_1->field_0xa5 = local_2f;
    param_1->field_0xa6 = local_2e;
    param_1->field_0xa7 = (char)iVar10;
    if (uVar13 == 7) {
      piVar4 = (int *)FUN_004bdd40();
      local_2e = (char)piVar4;
      if (local_2e == '\x0f') {
        param_1->State = 8;
        return local_2d;
      }
      iVar15 = 0;
      bVar1 = 1;
      do {
        if (((byte)piVar4 & bVar1) != bVar1) {
          gta2::bitShiftLeft1(local_24,(void *)0x32);
          puVar17 = local_10;
          pGVar14 = (GlassInfo *)FUN_0049ea30(local_18,iVar15);
          pPVar8 = (Player *)
                   FUN_0040f600(&param_1->EnterControlStatus,local_20,pGVar14);
          pvVar9 = gta2::Player_FUN_004202e0(pPVar8,puVar17,piVar4);
          gta2::Player_ApplyCollisionVelocity(param_1,pvVar9);
          piVar4 = (int *)CONCAT31((int3)((uint)pvVar9 >> 8),local_2e);
        }
        iVar15 = iVar15 + 1;
        bVar1 = bVar1 * '\x02';
      } while (iVar15 < 4);
    }
  }
  return local_2d;
}


// 0x004a2980: Player::sub_4A2980
// IDA: Player::sub_4A2980
// Ghidra: ---
char gta2::Player_sub_4A2980(Player *self)
{
  bool v2; // cl
  _DWORD *TrailerCtrl; // eax
  struct Player *pPlayer; // esi
  bool v5; // bl
  bool v7; // [esp+Bh] [ebp-9h]
  int v8; // [esp+Ch] [ebp-8h] BYREF
  int v9; // [esp+10h] [ebp-4h] BYREF

  v2 = gta2::Player_sub_4A26C0(self, (char *)&v8);
  v7 = v2;
  TrailerCtrl = self->sCar1->TrailerCtrl;
  if ( TrailerCtrl )
  {
    pPlayer = *(Player **)(TrailerCtrl[3] + 88);
    gta2::Player_sub_49ECC0(pPlayer);
    v5 = gta2::Player_sub_4A26C0(pPlayer, (char *)&v9);
    if ( v5 && (v7 || self->State == 6) )
      gta2::Player_sub_49FF80(pPlayer, v9);
    LOBYTE(TrailerCtrl) = (unsigned __int8)gta2::Player_sub_49ECC0(self);
    if ( v5 || pPlayer->State == 6 )
    {
      LOBYTE(TrailerCtrl) = v7;
      if ( v7 )
        goto LABEL_11;
    }
  }
  else if ( v2 )
  {
LABEL_11:
    LOBYTE(TrailerCtrl) = gta2::Player_sub_49FF80(self, v8);
  }
  return (char)TrailerCtrl;
}


// 0x004a2a30: Player::FUN_004a2a30
// IDA: ---
// Ghidra: Player::FUN_004a2a30
void gta2::Player_FUN_004a2a30(Player *self)
{
  bool bVar1;
  short *psVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined4 *puVar3;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  void *this_00;
  void *unaff_ESI;
  undefined4 uVar4;
  int *piVar5;
  short *in_stack_ffffffec;
  short local_10 [4];
  undefined1 local_8 [8];
  
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)local_10);
  if (self->ControlMode == '\0') {
    local_10[0] = *(short *)&self->theta;
  }
  else {
    psVar2 = (short *)gta2::sub_40E5A0((CarSystemManager *)&self->theta,
                                 (Ped *)&stack0xffffffee,(short *)&DAT_0066ae50,
                                 unaff_ESI,in_stack_ffffffec);
    local_10[0] = *psVar2;
  }
  bVar1 = gta2::Car_sub_403800((Car *)&DAT_0066afb4,(int *)&DAT_0066acdc);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    bVar1 = gta2::CarSystemManager_less_than((CarSystemManager *)local_10,(short *)&DAT_0066afac);
    if (CONCAT31(extraout_var_02,bVar1) == 0) {
      bVar1 = gta2::CarSystemManager_less_than((CarSystemManager *)local_10,(short *)&DAT_0066ae50);
      uVar4 = _DAT_0066ae3c;
      if (CONCAT31(extraout_var_03,bVar1) == 0) goto LAB_004a2b02;
    }
    else {
      puVar3 = (undefined4 *)gta2::JustCopyByPtrAtoC(&DAT_0066ae3c,local_10);
      uVar4 = *puVar3;
    }
  }
  else {
    bVar1 = gta2::CarSystemManager_greater_than((CarSystemManager *)local_10,(short *)&DAT_0066ad38);
    uVar4 = _DAT_0066ae3c;
    if (CONCAT31(extraout_var_00,bVar1) == 0) {
      bVar1 = gta2::CarSystemManager_greater_than((CarSystemManager *)local_10,(short *)&DAT_0066ae50);
      if (CONCAT31(extraout_var_01,bVar1) == 0) goto LAB_004a2b02;
      puVar3 = (undefined4 *)gta2::JustCopyByPtrAtoC(&DAT_0066ae3c,local_10);
      uVar4 = *puVar3;
    }
  }
  gta2::Player_sub_49E330(self,uVar4);
LAB_004a2b02:
  psVar2 = local_10;
  piVar5 = (int *)&DAT_0066aea8;
  this_00 = gta2::Player_FUN_00420390((Player *)&DAT_0066afb4,local_8);
  FUN_0041e1a0(this_00,psVar2,piVar5);
  gta2::Player_sub_4A0930(self);
  self->field_0xaa = 1;
  return;
}


// 0x004a2b40: Player::FUN_004a2b40
// IDA: ---
// Ghidra: Player::FUN_004a2b40
void gta2::Player_FUN_004a2b40(Player *self)
{
  bool bVar1;
  undefined2 *puVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined4 *puVar3;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  void *this_00;
  void *unaff_ESI;
  CarSystemManager **ppCVar4;
  undefined4 uVar5;
  int *piVar6;
  short *in_stack_ffffffec;
  CarSystemManager *pCarSystemManager;
  undefined1 local_8 [8];
  
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&pCarSystemManager);
  if (self->ControlMode == '\0') {
    pCarSystemManager._0_2_ = *(undefined2 *)&self->theta;
  }
  else {
    puVar2 = (undefined2 *)
             gta2::sub_40E5A0((CarSystemManager *)&self->theta,(Ped *)&stack0xffffffee
                        ,(short *)&DAT_0066ae50,unaff_ESI,in_stack_ffffffec);
    pCarSystemManager._0_2_ = *puVar2;
  }
  bVar1 = gta2::Car_sub_403800((Car *)&DAT_0066afb8,(int *)&DAT_0066acdc);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    bVar1 = gta2::CarSystemManager_less_than((CarSystemManager *)&pCarSystemManager,
                       (short *)&DAT_0066afac);
    uVar5 = _DAT_0066ae3c;
    if (CONCAT31(extraout_var_04,bVar1) == 0) {
      bVar1 = gta2::CarSystemManager_greater_than((CarSystemManager *)&pCarSystemManager,
                         (short *)&DAT_0066ad38);
      if (CONCAT31(extraout_var_05,bVar1) == 0) goto LAB_004a2c31;
      puVar3 = (undefined4 *)gta2::JustCopyByPtrAtoC(&DAT_0066ae3c,&pCarSystemManager)
      ;
      uVar5 = *puVar3;
    }
  }
  else {
    bVar1 = gta2::CarSystemManager_greater_than((CarSystemManager *)&pCarSystemManager,
                       (short *)&DAT_0066afac);
    if ((CONCAT31(extraout_var_00,bVar1) == 0) ||
       (bVar1 = gta2::CarSystemManager_less_than((CarSystemManager *)&pCarSystemManager,
                           (short *)&DAT_0066ae50),
       CONCAT31(extraout_var_01,bVar1) == 0)) {
      bVar1 = gta2::CarSystemManager_greater_than((CarSystemManager *)&pCarSystemManager,
                         (short *)&DAT_0066ae50);
      if ((CONCAT31(extraout_var_02,bVar1) == 0) ||
         (bVar1 = gta2::CarSystemManager_less_than((CarSystemManager *)&pCarSystemManager,
                             (short *)&DAT_0066ad38), uVar5 = _DAT_0066ae3c,
         CONCAT31(extraout_var_03,bVar1) == 0)) goto LAB_004a2c31;
    }
    else {
      puVar3 = (undefined4 *)gta2::JustCopyByPtrAtoC(&DAT_0066ae3c,&pCarSystemManager)
      ;
      uVar5 = *puVar3;
    }
  }
  gta2::Player_sub_49E330(self,uVar5);
LAB_004a2c31:
  ppCVar4 = &pCarSystemManager;
  piVar6 = (int *)&DAT_0066aea8;
  this_00 = gta2::Player_FUN_00420390((Player *)&DAT_0066afb4,local_8);
  FUN_0041e1a0(this_00,ppCVar4,piVar6);
  gta2::Player_sub_4A0930(self);
  self->field_0xaa = 1;
  return;
}


// 0x004a2c70: Player::sub_4A2C70
// IDA: Player::sub_4A2C70
// Ghidra: Player::FUN_004a2c70
void gta2::Player_sub_4A2C70(Player *self)
{
  byte bVar1;
  bool bVar2;
  EventHandler *pEVar3;
  char *pcVar4;
  GlassInfo *pGVar5;
  undefined3 extraout_var;
  undefined4 *puVar6;
  void *this_00;
  undefined4 uVar7;
  int *piVar8;
  undefined1 local_1c [8];
  undefined4 local_14 [2];
  int local_c;
  char local_8 [4];
  char local_4 [4];
  
  pEVar3 = gta2::SpriteS1_sub_40FEC0(DAT_005e6894);
  if ((pEVar3 == NULL) || (pEVar3->DamageType != 0xa6)) {
    bVar1 = gta2::Car_IsDriverPlayer(self->CarPlayerPre);
    if (bVar1 == 0) {
      local_c = _DAT_0066abcc;
      uVar7 = _DAT_0066ae40;
    }
    else {
      local_c = _DAT_0066af80;
      uVar7 = _DAT_0066acf8;
    }
  }
  else {
    local_c = _DAT_0066aea8;
    uVar7 = _DAT_0066ae3c;
  }
  local_14[0] = uVar7;
  pcVar4 = (char *)FUN_0040f600(&self->field27_0x38,local_1c,
                                (GlassInfo *)&DAT_0066ad08);
  local_8 = *(char (*) [4])pcVar4;
  local_4 = *(char (*) [4])(pcVar4 + 4);
  pGVar5 = (GlassInfo *)
           gta2::sub_401C80((CarSystemManager *)&self->theta,local_1c);
  FUN_0040f6b0(local_8,pGVar5);
  bVar2 = gta2::Point2D_FUN_004037e0((Point2D *)local_8,(SpriteS1 *)&DAT_0066acdc);
  if (CONCAT31(extraout_var,bVar2) == 0) {
    puVar6 = (undefined4 *)gta2::JustCopyByPtrAtoC(local_14,local_1c);
    uVar7 = *puVar6;
  }
  gta2::Player_sub_49E330(self,uVar7);
  piVar8 = &local_c;
  pcVar4 = local_8;
  this_00 = gta2::Player_FUN_00420390((Player *)&DAT_0066afb4,local_14);
  FUN_0041e1a0(this_00,pcVar4,piVar8);
  gta2::Player_sub_4A0930(self);
  return;
}


// 0x004a2d70: Player::sub_4A2D70
// IDA: Player::sub_4A2D70
// Ghidra: Player::FUN_004a2d70
byte gta2::Player_sub_4A2D70(Player *self)
{
  if (PTR_005e6874 == (void *)0x1) {
    gta2::Player_FUN_004a2b40(self);
    return 1;
  }
  if (PTR_005e6874 != (void *)0x2) {
    if (PTR_005e6874 == (void *)0x3) {
      gta2::Player_sub_4A2C70(self);
      self->field_0xaa = 0;
    }
    return 0;
  }
  gta2::Player_FUN_004a2a30(self);
  return 1;
}


// 0x004a2db0: Player::sub_4A2DB0
// IDA: Player::sub_4A2DB0
// Ghidra: Player::FUN_004a2db0
byte gta2::Player_sub_4A2DB0(Player *self)
{
  char in_AL;
  byte bVar1;
  
  gta2::Car_sub_414F70(self->CarPlayerPre);
  if (in_AL != '\0') {
    gCarSystemManager->field44_0x60 = 1;
    bVar1 = gta2::S56_sub_4474E0(gCheckpoint,(SpriteS1 *)self->CarPlayerPre->CarSprite,2);
    if (bVar1 != 0) {
      return 1;
    }
    gta2::Car_sub_49EFD0(self->CarPlayerPre);
  }
  return 0;
}


// 0x004a2e00: Player::sub_4A2E00
// IDA: Player::sub_4A2E00
// Ghidra: FUN_004a2e00
void gta2::Player_sub_4A2E00(Player *param_1,undefined4 param_2)
{
  FUN_004a0850(param_2,&stack0x00000008,0);
  gta2::Player_sub_4A0C60(param_1);
  gta2::Player_sub_4A0CC0(param_1);
  return;
}


// 0x004a2e30: Player::sub_49EEB0
// IDA: Player::sub_49EEB0
// Ghidra: ---
      return gta2::Player_sub_49EEB0(self);
    }


// 0x004a2f20: Player::sub_4A2F20
// IDA: Player::sub_4A2F20
// Ghidra: Player::FUN_004a2f20
void gta2::Player_sub_4A2F20(Player *self)
{
  undefined4 uVar1;
  undefined4 *puVar2;
  struct Player *pLinkedList;
  
  pLinkedList = self;
  puVar2 = FUN_00421b90(self->CarPlayerPre,(LinkedList *)&pLinkedList);
  _DAT_0066afc4 = *puVar2;
  FUN_0049e950(self);
  FUN_0049e980();
  puVar2 = (undefined4 *)FUN_004a1130(&pLinkedList);
  uVar1 = *puVar2;
  self->field64_0x84 = (char)uVar1;
  self->field65_0x85 = (short)((uint)uVar1 >> 8);
  self->field66_0x87 = (char)((uint)uVar1 >> 0x18);
  puVar2 = (undefined4 *)FUN_004a1360(&pLinkedList);
  uVar1 = *puVar2;
  self->field67_0x88 = (char)uVar1;
  self->field68_0x89 = (char)((uint)uVar1 >> 8);
  self->field69_0x8a = (char)((uint)uVar1 >> 0x10);
  self->field70_0x8b = (char)((uint)uVar1 >> 0x18);
  FUN_004a20e0();
  gta2::Player_sub_4A0C60(self);
  gta2::Player_sub_4A0CC0(self);
  return;
}


// 0x004a30a0: Player::FUN_004a30a0
// IDA: ---
// Ghidra: Player::FUN_004a30a0
byte gta2::Player_FUN_004a30a0(Player *self,SpriteS1 *param_1,SpriteS1 *param_2)
{
  SpriteS1 *pS127;
  SpriteS1 *this_00;
  byte bVar1;
  SpriteS1 *this_01;
  SpriteS1 *pSVar2;
  int *piVar3;
  int local_8;
  int local_4;
  
  this_00 = param_2;
  pS127 = param_1;
  local_4 = 2;
  local_8 = 3;
  do {
    gta2::Player_sub_49DE40(self);
    piVar3 = &local_4;
    pSVar2 = (SpriteS1 *)&param_2;
    this_01 = gta2::S202_sub_401B20((Point2D *)this_00,(SpriteS1 *)&param_1,(S127 *)pS127);
    pSVar2 = gta2::S122_sub_401BF0((Model *)this_01,pSVar2,piVar3);
    pSVar2 = pSVar2->FirstElement;
    gta2::Player_sub_49EEB0(self,(int)pSVar2);
    bVar1 = gta2::Player_sub_4A0020(self);
    if (bVar1 == 0) {
      this_00->FirstElement = pSVar2;
    }
    else {
      pS127->FirstElement = pSVar2;
    }
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  return 0;
}


// 0x004a3140: Player::sub_4A3140
// IDA: Player::sub_4A3140
// Ghidra: FUN_004a3140
void gta2::Player_sub_4A3140(Player *param_1,undefined4 param_2,undefined4 *param_3)
{
  Car *self;
  bool bVar1;
  
  self = param_1->CarPlayerPre;
  bVar1 = gta2::Car_sub_421720(self);
  if (bVar1) {
    gta2::Player_sub_49ECC0(*(Player **)(*(int *)((int)self->S___ + 8) + 0x58));
    FUN_004a2e00(param_2,*param_3,param_3[1]);
    gta2::Player_sub_49ECC0(param_1);
    return;
  }
  FUN_004a2e00(param_2,*param_3,param_3[1]);
  return;
}


// 0x004a31b0: Player::sub_4A31B0
// IDA: Player::sub_4A31B0
// Ghidra: FUN_004a31b0
void gta2::Player_sub_4A31B0(Player *param_1,undefined4 *param_2,undefined4 param_3, Player *param_4,Player *param_5)
{
  struct Player *self;
  bool bVar1;
  byte bVar2;
  int *piVar3;
  Car *pCVar4;
  undefined3 extraout_var;
  struct Player *this_00;
  undefined3 extraout_var_00;
  undefined4 *puVar5;
  int *piVar6;
  struct Player *local_10;
  struct Player *local_c;
  undefined1 local_8 [8];
  
  self = param_4;
  gta2::Player_sub_41E260(param_4,(int *)&param_4);
  piVar6 = (int *)&DAT_0066aeb0;
  piVar3 = (int *)gta2::Player_sub_49F660(param_1,&local_10);
  pCVar4 = (Car *)gta2::sub_401B90((Player *)&param_4,local_8,piVar3);
  bVar1 = gta2::Car_sub_403800(pCVar4,piVar6);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    local_c = self->Player_;
    local_10 = self->CurrentPlayer;
    pCVar4 = param_1->CarPlayerPre;
    bVar2 = gta2::Car_sub_411930(pCVar4,0x800);
    if (bVar2 != 0) {
      bVar2 = gta2::Car_IsDriverPlayer(pCVar4);
      if (bVar2 == 0) {
        piVar3 = (int *)&DAT_0066ab90;
        this_00 = (Player *)gta2::Player_sub_4211C0(param_1,local_8);
        bVar1 = gta2::Player_CheckCondition(this_00,piVar3);
        if ((CONCAT31(extraout_var_00,bVar1) != 0) ||
           (*(char *)((int)&param_1->CameraOrPhysics_ + 2) != '\0')) {
          puVar5 = (undefined4 *)
                   gta2::Player_FUN_004202e0(self,local_8,(int *)&DAT_0066ac48);
          local_10 = (Player *)*puVar5;
          local_c = (Player *)puVar5[1];
        }
      }
    }
    gta2::Car_sub_426F00(pCVar4);
    bVar2 = gta2::Car_sub_411930(param_1->CarPlayerPre,2);
    if (bVar2 == 0) {
      FUN_004a3140(param_3,&local_10);
      gta2::Player_sub_49EF50(param_1,(int)param_5);
      bVar2 = gta2::Car_IsDriverPlayer(param_1->CarPlayerPre);
      if (bVar2 != 0) goto LAB_004a32be;
      gta2::Player_sub_421260(param_1);
    }
    *param_2 = param_4;
    return;
  }
LAB_004a32be:
  *param_2 = param_4;
  return;
}


// 0x004a32d0: Player::sub_4A32D0
// IDA: Player::sub_4A32D0
// Ghidra: FUN_004a32d0
void gta2::Player_sub_4A32D0(Player *param_1,Player *param_2)
{
  struct Player *self;
  bool bVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined3 extraout_var;
  void *this_00;
  Point2D *this_01;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  int iVar5;
  undefined3 extraout_var_03;
  Car *this_02;
  undefined3 extraout_var_04;
  struct Player *this_03;
  undefined4 uVar6;
  undefined *puVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int *piVar10;
  SpriteS1 *pSpriteS1;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [8];
  undefined1 local_8 [8];
  
  puVar2 = (undefined4 *)FUN_0049f6c0(local_18);
  puVar3 = (undefined4 *)gta2::Player_sub_49F660(param_1,local_14);
  uVar6 = *puVar2;
  puVar7 = &DAT_0066abd8;
  uVar8 = _DAT_0066acdc;
  uVar9 = _DAT_0066ae38;
  uVar4 = FUN_0049f570(local_8);
  self = param_2;
  FUN_004a05c0(local_10,*puVar3,_DAT_0066ac60,param_2,&DAT_0066afb4,
               &DAT_0066ad08,uVar4,puVar7,uVar6,uVar8,uVar9);
  if (param_1->State == 6) {
    bVar1 = gta2::Player_CheckCondition((Player *)&param_1->field44_0x70,(int *)&DAT_0066acdc);
    if (CONCAT31(extraout_var,bVar1) != 0) {
      puVar3 = &param_2;
      piVar10 = (int *)&DAT_0066ae48;
      puVar2 = &param_1->ID;
      this_00 = gta2::JustCopyByPtrAtoC(puVar2,local_14);
      puVar3 = (undefined4 *)
               gta2::WorldCoordinateToScreenCoord(this_00,puVar3,piVar10);
      pSpriteS1 = (SpriteS1 *)&DAT_0066ade4;
      *puVar2 = *puVar3;
      this_01 = (Point2D *)
                gta2::Player_FUN_00403840(this_03,(int *)&param_2,(GlassInfo *)puVar2);
      bVar1 = gta2::Point2D_FUN_004037e0(this_01,pSpriteS1);
      if (CONCAT31(extraout_var_00,bVar1) != 0) {
        *puVar2 = _DAT_0066acdc;
      }
    }
  }
  puVar2 = (undefined4 *)FUN_004a31b0(&param_2,&DAT_0066ad08,local_10,0xf);
  uVar6 = *puVar2;
  _DAT_0066b034 = uVar6;
  if (param_1->State == 6) {
    bVar1 = gta2::Player_IsCurrentPlayer((Player *)&param_1->field44_0x70,(Player *)&DAT_0066acdc)
    ;
    if (CONCAT31(extraout_var_01,bVar1) != 0) {
      bVar1 = gta2::Player_IsCurrentPlayer((Player *)&param_1->ID,(Player *)&DAT_0066acdc);
      if (CONCAT31(extraout_var_02,bVar1) != 0) {
        iVar5 = FUN_00420360(&param_1->S103_);
        if (iVar5 != 0) {
          bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)&DAT_0066b034,(SpriteS1 *)&DAT_0066aff4)
          ;
          if (CONCAT31(extraout_var_03,bVar1) != 0) {
            _DAT_0066b034 = _DAT_0066aff4;
            uVar6 = _DAT_0066aff4;
          }
        }
      }
    }
  }
  gta2::Car_sub_4292F0(param_1->CarPlayerPre,uVar6);
  piVar10 = (int *)&DAT_0066af5c;
  this_02 = (Car *)gta2::Player_sub_41E260((Player *)&param_1->S103_,(int *)&param_2);
  bVar1 = gta2::Car_sub_403800(this_02,piVar10);
  if (CONCAT31(extraout_var_04,bVar1) != 0) {
    bVar1 = gta2::Car_GetFullDamage(param_1->CarPlayerPre);
    if (!bVar1) {
      puVar2 = (undefined4 *)gta2::Player_FUN_0040f640(self,local_8);
      FUN_0048db00(_DAT_0066ad08,_DAT_0066ad0c,param_1->Debug,*puVar2,puVar2[1])
      ;
    }
    FUN_00423180(DAT_0066ab6c,_DAT_0066b034);
  }
  return;
}


// 0x004a34a0: Player::sub_4A34A0
// IDA: Player::sub_4A34A0
// Ghidra: ---
EngineStruct * gta2::Player_sub_4A34A0(Player *self, Car *pCar)
{
  struct Player *pPlayer; // edi
  int *v4; // eax
  int v5; // edx
  int v6; // eax
  GameEntity *v7; // eax
  int *v8; // eax
  int v9; // edx
  int *v10; // eax
  int v11; // edx
  int *v12; // eax
  int v13; // edx
  Car **v14; // eax
  struct Player **v15; // eax
  int *v16; // eax
  int v17; // ecx
  int v18; // edx
  int State; // eax
  int v20; // eax
  SpriteS1 *v21; // eax
  int *v22; // eax
  void *v23; // ecx
  void *v24; // eax
  _DWORD *v25; // eax
  _DWORD *v26; // eax
  int *v27; // eax
  int v28; // edx
  Car *sCar1; // ecx
  int *v30; // eax
  Tango *v31; // eax
  SpriteS1 *v32; // eax
  Car *v33; // eax
  Car *v34; // eax
  struct Ped *v35; // eax
  int **v36; // eax
  int *v37; // eax
  struct Ped *v38; // eax
  struct Player *v39; // eax
  int *v40; // eax
  struct Ped *v41; // eax
  struct Ped *v42; // edi
  Car *v43; // eax
  _DWORD *v44; // eax
  struct Ped *v45; // eax
  struct Ped *v46; // edi
  struct EngineStruct *EngineStruct; // eax
  struct EngineStruct *result; // eax
  void *v49; // [esp+0h] [ebp-58h]
  char v50; // [esp+Fh] [ebp-49h]
  int *a3; // [esp+10h] [ebp-48h]
  int *a3a; // [esp+10h] [ebp-48h]
  int v53; // [esp+14h] [ebp-44h] BYREF
  int v54; // [esp+18h] [ebp-40h] BYREF
  char v55[4]; // [esp+1Ch] [ebp-3Ch] BYREF
  int v56[2]; // [esp+20h] [ebp-38h] BYREF
  int *arg0[2]; // [esp+28h] [ebp-30h] BYREF
  _DWORD v58[2]; // [esp+30h] [ebp-28h] BYREF
  _DWORD v59[2]; // [esp+38h] [ebp-20h] BYREF
  int v60; // [esp+40h] [ebp-18h] BYREF
  int v61; // [esp+44h] [ebp-14h]
  int v62; // [esp+48h] [ebp-10h] BYREF
  int v63; // [esp+4Ch] [ebp-Ch]
  _DWORD a2[2]; // [esp+50h] [ebp-8h] BYREF

  gta2::Player_sub_49F660(self, (SpriteS1 *)&v53);
  gta2::Car_CarMakeDriveable4(pCar);
  pPlayer = pCar->Player_;
  gta2::Player_sub_49ECC0(pPlayer);
  v4 = gta2::Player_sub_49E5A0(pPlayer, &v60, &unk_66AD08);
  v5 = *v4;
  v6 = v4[1];
  v62 = v5;
  v63 = v6;
  gta2::Player_sub_49ECC0(self);
  v7 = (GameEntity *)gta2::Player_sub_49E5A0(self, &v60, &unk_66AD08);
  v8 = gta2::S1_sub_40F600(v7, v59, (int)&v62);
  v9 = v8[1];
  v62 = *v8;
  v63 = v9;
  v10 = gta2::Player_sub_49F570(self, (int *)arg0);
  v11 = v10[1];
  v58[0] = *v10;
  v58[1] = v11;
  v12 = gta2::Player_sub_49F570(pPlayer, v56);
  v13 = v12[1];
  v60 = *v12;
  v61 = v13;
  v14 = (Car **)gta2::S1_sub_40F600((GameEntity *)v58, v59, (int)&unk_66AD08);
  unk_66AFB4 = *v14;
  unk_66AFB8 = v14[1];
  gta2::Player_sub_49F6C0(pPlayer, (SpriteS1 *)v55);
  v54 = (int)gta2::Player_sub_49F6C0(self, (SpriteS1 *)v56);
  v15 = (Player **)gta2::Player_sub_49F660(pPlayer, (SpriteS1 *)arg0);
  v16 = sub_4A05C0(a2, v53, *v15);
  v17 = *v16;
  v18 = v16[1];
  State = self->State;
  v59[0] = v17;
  v59[1] = v18;
  if ( State == 6
    && (LOWORD(v20) = gta2::Car_sub_403820(
                        (Car *)&pCar->CarSprite->S3_arr5031[0].PositionZ,
                        &self->sCar1->CarSprite->S3_arr5031[0].PositionZ),
        v20) )
  {
    v21 = gta2::JustCopyByPtrAtoC(&self->MultiPlayerMode, (SpriteS1 *)v56);
    v22 = (int *)gta2::Radar_AddBlip((Tango *)v21, (SpriteS1 *)arg0, (PublicTransport *)&stru_66ADE0.bool);
    v23 = (void *)*v22;
    self->MultiPlayerMode = *v22;
    v24 = gta2::sub_403840(v23, (Player *)arg0, &self->MultiPlayerMode);
    if ( gta2::sub_4037E0(v24) )
      self->MultiPlayerMode = unk_66ACDC;
    v54 = 10;
    v25 = gta2::S1_sub_40F600((GameEntity *)v58, arg0, (int)&v60);
    v26 = (_DWORD *)sub_420390(v25, v58);
    v27 = sub_49E360(v26, a2, (SpriteS1 *)&v54);
    v28 = v27[1];
    v60 = *v27;
    sCar1 = self->sCar1;
    v61 = v28;
    if ( !gta2::Car_sub_49EFE0(sCar1, v49) || gta2::Car_sub_4216E0(pCar) )
    {
      gta2::Player_sub_4A09B0(self, &v60, 50);
      v30 = sub_40F640(&v60, a2);
      gta2::Player_sub_4A09B0(pPlayer, v30, 50);
    }
    else
    {
      gta2::Car_sub_49EFC0(self->sCar1);
    }
    v54 = 50;
    v31 = (Tango *)gta2::sub_403840(v55, (Player *)v55, &self->Up);
    v32 = gta2::Radar_AddBlip(v31, (SpriteS1 *)v56, (PublicTransport *)&v53);
    unk_66B034.Car = gta2::sub_401BD0(v32, (SpriteS1 *)arg0, &v54)->FirstElement;
  }
  else
  {
    gta2::bitShiftLeft1(&v54, 0);
    unk_66B034.Car = (void *)v54;
  }
  if ( gta2::Car_sub_49EFE0(self->sCar1, v49)
    && !gta2::Car_sub_4216E0(pCar)
    && (v33 = (Car *)gta2::Player_sub_41E260((Player *)v59, (int)arg0), gta2::Car_sub_403800(v33, (int)&unk_66AF60))
    && (gta2::Player_sub_4211A0(self, arg0), gta2::Car_sub_403800(v34, (int)&unk_66AB9C)) )
  {
    v50 = 1;
    gta2::Car_sub_49EFC0(self->sCar1);
    if ( gta2::Car_IsCopCar(pCar) )
    {
      v35 = gta2::Car_sub_423480(self->sCar1);
      v54 = (int)v35;
      if ( v35 )
      {
        if ( gta2::Ped_IsPlayerControlled(v35) && *(__int16 *)(v54 + 522) < 600 )
          *(_WORD *)(v54 + 522) = 600;
      }
    }
  }
  else
  {
    v50 = 0;
    v36 = gta2::Player_sub_4A31B0(self, arg0, (int *)&unk_66AD08, (Player *)v59, 50);
    gta2::Player_sub_40E530((Player *)&unk_66B034, (Tango *)v36);
  }
  gta2::Car_sub_425CA0(self->sCar1, pCar);
  LOWORD(v37) = gta2::Car_sub_4292F0(self->sCar1, (Car *)unk_66B034.Car);
  a3 = v37;
  if ( (__int16)v37 > 200 )
  {
    v38 = gta2::Car_sub_423480(pCar);
    v54 = (int)v38;
    if ( v38 )
    {
      if ( gta2::Ped_IsPlayerControlled(v38) )
        gta2::PlayerStats_sub_4B8870((PlayerStats *)(*(_DWORD *)(v54 + 348) + 724), self->sCar1, a3);
    }
  }
  if ( !v50 )
  {
    gta2::Player_sub_49ECC0(pPlayer);
    v39 = (Player *)sub_40F640(v59, a2);
    gta2::Player_sub_4A31B0(pPlayer, arg0, (int *)&unk_66AD08, v39, 50);
    if ( gta2::Car_IsTrainOrTrainCarriage(self->sCar1) )
    {
      gta2::Car_ExplodeCar(pCar, 19);
      a3a = (int *)32000;
    }
    else
    {
      LOWORD(v40) = gta2::Car_sub_4292F0(pCar, (Car *)unk_66B034.Car);
      a3a = v40;
      if ( (__int16)v40 <= 200 )
      {
LABEL_32:
        gta2::Player_sub_49ECC0(self);
        goto LABEL_33;
      }
    }
    v41 = gta2::Car_sub_423480(self->sCar1);
    v42 = v41;
    if ( v41 && gta2::Ped_IsPlayerControlled(v41) )
      gta2::PlayerStats_sub_4B8870((PlayerStats *)&v42->isPlayer->Money, pCar, a3a);
    goto LABEL_32;
  }
LABEL_33:
  v43 = (Car *)gta2::Player_sub_41E260((Player *)&self->S103_4, (int)arg0);
  if ( gta2::Car_sub_403800(v43, (int)&unk_66AF5C) && !gta2::Car_GetFullDamage(self->sCar1) )
  {
    v44 = sub_40F640(&v62, a2);
    gta2::Particles_sub_48DB00(gParticles, *(int *)&unk_66AD08.S200[0].A, unk_66AD0C, self->field_6C, *v44, v44[1]);
  }
  if ( gta2::Car_sub_403800(&unk_66B034, (int)&unk_66AD00) )
  {
    gta2::Car_sub_423180(self->sCar1, byte_66AB6C, (int)unk_66B034.Car);
    gta2::Car_sub_423180(pCar, unk_66AB74, (int)unk_66B034.Car);
    if ( gta2::Car_sub_403800(&unk_66B034, (int)&stru_66AC54.field_24) )
    {
      if ( gta2::Car_IsCopCar(pCar) )
      {
        v45 = gta2::Car_sub_423480(self->sCar1);
        v46 = v45;
        if ( v45 )
        {
          if ( gta2::Ped_IsPlayerControlled(v45) && v46->PoliceStar1 < 600 )
            v46->PoliceStar1 = 600;
        }
      }
    }
  }
  EngineStruct = self->sCar1->EngineStruct_;
  if ( EngineStruct )
  {
    EngineStruct->Flags |= 4096u;
    self->sCar1->EngineStruct_->Car = pCar;
  }
  result = pCar->EngineStruct_;
  if ( result )
  {
    result->Flags |= 4096u;
    pCar->EngineStruct_->Car = self->sCar1;
  }
  return result;
}


// 0x004a3a40: Player::sub_4A3A40
// IDA: Player::sub_4A3A40
// Ghidra: Player::FUN_004a3a40
void gta2::Player_sub_4A3A40(Player *self,CollisionBox *param_1,undefined4 param_2)
{
  byte bVar1;
  bool bVar2;
  undefined4 *puVar3;
  SpriteS1 **ppSVar4;
  void *pvVar5;
  struct Player *pPVar6;
  undefined3 extraout_var;
  undefined4 *puVar7;
  Point2D *this_00;
  undefined3 extraout_var_00;
  int *piVar8;
  undefined3 extraout_var_01;
  undefined1 *puVar9;
  undefined1 *puVar10;
  GlassInfo *pGVar11;
  int *piVar12;
  SpriteS1 *pSVar13;
  int local_50;
  SpriteS1 *local_4c;
  int local_48 [2];
  undefined1 local_40 [16];
  struct Player *local_30;
  struct Player *local_2c;
  Car *local_28;
  struct Ped *local_24;
  SpawnPoint *local_20;
  struct Player *local_1c;
  undefined1 local_18 [8];
  undefined1 local_10 [12];
  
  FUN_00482c30(local_40);
  FUN_0049f570(local_40 + 8);
  gta2::Player_sub_49F660(self,&local_50);
  puVar3 = (undefined4 *)
           FUN_0040f600(local_40 + 8,&local_20,(GlassInfo *)&DAT_0066ad08);
  _DAT_0066afb4 = *puVar3;
  _DAT_0066afb8 = puVar3[1];
  bVar1 = gta2::S63_sub_482C90(param_1);
  if (bVar1 == 0) {
    puVar3 = (undefined4 *)
             gta2::Player_GetCarPoints(self,local_10,(GlassInfo *)&DAT_0066ad08);
    local_30 = (Player *)*puVar3;
    local_2c = (Player *)puVar3[1];
    puVar3 = (undefined4 *)FUN_0049f6c0(local_48);
    puVar3 = (undefined4 *)
             FUN_004a05c0(local_10,local_50,_DAT_0066ac60,&local_30,
                          &DAT_0066afb4,&DAT_0066ad08,local_40 + 8,local_40,
                          *puVar3,_DAT_0066afd8,_DAT_0066adb4);
    local_20 = (SpawnPoint *)*puVar3;
    local_1c = (Player *)puVar3[1];
  }
  else {
    ppSVar4 = &local_4c;
    gta2::S63_sub_482C80(param_1,ppSVar4);
    pSVar13 = *ppSVar4;
    local_4c = pSVar13;
    puVar3 = (undefined4 *)FUN_00482c50(&local_20);
    local_28 = (Car *)*puVar3;
    pGVar11 = (GlassInfo *)&local_28;
    local_24 = (Ped *)puVar3[1];
    piVar8 = local_48;
    pvVar5 = gta2::Player_GetCarPoints(self,&local_20,(GlassInfo *)&DAT_0066ad08);
    puVar3 = (undefined4 *)FUN_0040f600(pvVar5,piVar8,pGVar11);
    local_30 = (Player *)*puVar3;
    local_2c = (Player *)puVar3[1];
    puVar3 = (undefined4 *)FUN_0049f6c0(local_48);
    puVar3 = (undefined4 *)
             FUN_004a05c0(local_18,local_50,pSVar13,&local_30,&DAT_0066afb4,
                          &DAT_0066ad08,local_40 + 8,local_40,*puVar3,
                          _DAT_0066afd8,_DAT_0066aea4);
    local_20 = (SpawnPoint *)*puVar3;
    local_1c = (Player *)puVar3[1];
    ppSVar4 = &local_4c;
    puVar9 = local_10;
    pPVar6 = (Player *)gta2::Player_FUN_0040f640((Player *)&local_20,local_18);
    puVar3 = (undefined4 *)gta2::Player_FUN_004202e0(pPVar6,puVar9,(int *)ppSVar4);
    local_28 = (Car *)*puVar3;
    local_24 = (Ped *)puVar3[1];
    gta2::S63_sub_484A40((EventHandler *)param_1,&local_28);
  }
  if (self->State == 6) {
    bVar2 = gta2::Car_IsTrainOrTrainCarriage((Car *)&param_1->Index->z,
                       (Car *)&self->CarPlayerPre->CarSprite->Point2D);
    if (CONCAT31(extraout_var,bVar2) != 0) {
      piVar8 = local_48;
      puVar3 = &self->ID;
      piVar12 = (int *)&DAT_0066ae48;
      pvVar5 = gta2::JustCopyByPtrAtoC(puVar3,&local_4c);
      puVar7 = (undefined4 *)gta2::WorldCoordinateToScreenCoord(pvVar5,piVar8,piVar12)
      ;
      pPVar6 = (Player *)*puVar7;
      pSVar13 = (SpriteS1 *)&DAT_0066ade4;
      *puVar3 = pPVar6;
      this_00 = (Point2D *)
                gta2::Player_FUN_00403840(pPVar6,local_48,(GlassInfo *)puVar3);
      bVar2 = gta2::Point2D_FUN_004037e0(this_00,pSVar13);
      if (CONCAT31(extraout_var_00,bVar2) != 0) {
        *puVar3 = _DAT_0066acdc;
      }
      ppSVar4 = &local_4c;
      puVar9 = local_10;
      puVar10 = local_18;
      local_4c = (SpriteS1 *)0xa;
      pPVar6 = (Player *)
               FUN_0040f600(local_40 + 8,local_48,(GlassInfo *)local_40);
      gta2::Player_FUN_00420390(pPVar6,puVar10);
      puVar3 = (undefined4 *)gta2::FUN_0049e360(puVar9,ppSVar4);
      local_40._8_4_ = *puVar3;
      local_40._12_4_ = puVar3[1];
      gta2::Player_sub_4A09B0(self,(undefined4 *)(local_40 + 8),0x32);
      bVar1 = gta2::S63_sub_482C90(param_1);
      if (bVar1 != 0) {
        pvVar5 = gta2::Player_FUN_0040f640((Player *)(local_40 + 8),local_10);
        gta2::S63_sub_484A40((EventHandler *)param_1,pvVar5);
      }
      ppSVar4 = &local_4c;
      pSVar13 = (SpriteS1 *)local_48;
      piVar8 = &local_50;
      puVar9 = local_40;
      local_4c = (SpriteS1 *)0x32;
      piVar12 = gta2::Player_FUN_00403840((Player *)(local_40 + 8),(int *)(local_40 + 8),
                           (GlassInfo *)&self->field44_0x70);
      pvVar5 = gta2::WorldCoordinateToScreenCoord(piVar12,puVar9,piVar8);
      pSVar13 = FUN_00401bd0(pvVar5,pSVar13,(int *)ppSVar4);
      _DAT_0066b034 = pSVar13->FirstElement;
      goto LAB_004a3d3f;
    }
  }
  gta2::bitShiftLeft1(&local_4c,NULL);
  _DAT_0066b034 = local_4c;
LAB_004a3d3f:
  piVar8 = (int *)FUN_004a31b0(local_40 + 8,&DAT_0066ad08,&local_20,0xf);
  gta2::Player_sub_40E530((Point2D *)&DAT_0066b034,piVar8);
  gta2::Car_sub_4292F0(self->CarPlayerPre,_DAT_0066b034);
  gta2::S63_sub_486410(param_1,(SpriteS1 *)self->CarPlayerPre->CarSprite);
  bVar2 = gta2::Car_sub_403800((Car *)&DAT_0066b034,(int *)&DAT_0066ad00);
  if (CONCAT31(extraout_var_01,bVar2) != 0) {
    bVar2 = gta2::Car_GetFullDamage(self->CarPlayerPre);
    if (!bVar2) {
      puVar3 = (undefined4 *)gta2::Player_FUN_0040f640((Player *)&local_30,local_10);
      FUN_0048db00(_DAT_0066ad08,_DAT_0066ad0c,self->Debug,*puVar3,puVar3[1]);
    }
    FUN_00423180(param_2,_DAT_0066b034);
  }
  return;
}


// 0x004a3df0: Player::sub_4A3DF0
// IDA: Player::sub_4A3DF0
// Ghidra: Player::FUN_004a3df0
void * gta2::Player_sub_4A3DF0(Player *self,Car *param_1)
{
  char cVar1;
  bool bVar2;
  undefined4 *puVar3;
  void *pvVar4;
  GlassInfo *pGVar5;
  SpriteS1 *pSpriteS1;
  Point2D *this_00;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  struct Player *this_01;
  undefined1 local_10 [8];
  SpawnPoint *local_8 [2];
  
  cVar1 = FUN_004bcd00(DAT_005e688c,&DAT_0066ad08,&DAT_0066ab6c);
  if (cVar1 != '\0') {
    gta2::bitShiftLeft1(&stack0x00000008,NULL);
    puVar3 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)&self->field28_0x3c,(GlassInfo *)&param_1,
                        (S127 *)&DAT_005e688c);
    FUN_00432860(&DAT_0066afb4,(undefined4 *)&stack0x00000008,puVar3);
    puVar3 = (undefined4 *)
             gta2::Player_GetCarPoints(self,local_10,(GlassInfo *)&DAT_0066ad08);
    local_8[0] = (SpawnPoint *)*puVar3;
    local_8[1] = (SpawnPoint *)puVar3[1];
    pvVar4 = (void *)FUN_004a32d0(local_8);
    return pvVar4;
  }
  FUN_00432860(&DAT_0066ad08,&DAT_005e6888,&DAT_005e688c);
  FUN_004828c0(&DAT_0066ad08,(int *)param_1);
  pGVar5 = (GlassInfo *)
           gta2::SpriteS1_sub_40E5D0((CarSystemManager *)&self->theta,(Ped *)&param_1,
                      (int)&stack0x00000008);
  FUN_0040f6b0(&DAT_0066ad08,pGVar5);
  gta2::Player_sub_40E530((Point2D *)&DAT_0066ad08,&self->field27_0x38);
  _DAT_0066ad0c = DAT_005e688c;
  pGVar5 = (GlassInfo *)
           gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066ad08,(GlassInfo *)&stack0x00000008,
                      (S127 *)&DAT_005e687c);
  pSpriteS1 = (SpriteS1 *)
              gta2::Player_FUN_00403840((Player *)&param_1,(int *)&param_1,pGVar5);
  pGVar5 = (GlassInfo *)
           gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066ad08,(GlassInfo *)local_10,
                      (S127 *)&DAT_005e6878);
  this_00 = (Point2D *)gta2::Player_FUN_00403840(this_01,(int *)local_8,pGVar5);
  bVar2 = gta2::Point2D_FUN_004037e0(this_00,pSpriteS1);
  if (CONCAT31(extraout_var,bVar2) == 0) {
    _DAT_0066ad08 = DAT_005e687c;
  }
  else {
    _DAT_0066ad08 = DAT_005e6878;
  }
  puVar3 = (undefined4 *)
           gta2::Player_GetCarPoints(self,local_10,(GlassInfo *)&DAT_0066ad08);
  local_8[0] = (SpawnPoint *)*puVar3;
  local_8[1] = (SpawnPoint *)puVar3[1];
  bVar2 = gta2::Point2D_FUN_004037e0((Point2D *)&self->field28_0x3c,(SpriteS1 *)&DAT_0066ad0c);
  if (CONCAT31(extraout_var_00,bVar2) == 0) {
    gta2::bitShiftLeft1(&stack0x00000008,NULL);
    puVar3 = (undefined4 *)&DAT_0066ac4c;
  }
  else {
    gta2::bitShiftLeft1(&stack0x00000008,NULL);
    puVar3 = (undefined4 *)gta2::JustCopyByPtrAtoC(&DAT_0066ac4c,&param_1);
  }
  FUN_00432860(&DAT_0066afb4,(undefined4 *)&stack0x00000008,puVar3);
  pvVar4 = (void *)FUN_004a32d0(local_8);
  return pvVar4;
}


// 0x004a3fb0: Player::sub_4A3FB0
// IDA: Player::sub_4A3FB0
// Ghidra: Player::FUN_004a3fb0
void gta2::Player_sub_4A3FB0(Player *self,Car *param_1)
{
  char cVar1;
  bool bVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  GlassInfo *pGVar5;
  SpriteS1 *pSpriteS1;
  Point2D *this_00;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  struct Player *this_01;
  undefined1 local_10 [8];
  SpawnPoint *local_8 [2];
  
  cVar1 = FUN_004bcfa0(DAT_005e6888,&DAT_0066ad08,&DAT_0066ab6c);
  if (cVar1 != '\0') {
    gta2::bitShiftLeft1(&stack0x00000008,NULL);
    puVar4 = (undefined4 *)&stack0x00000008;
    puVar3 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)&self->field27_0x38,(GlassInfo *)&param_1,
                        (S127 *)&DAT_005e6888);
    FUN_00432860(&DAT_0066afb4,puVar3,puVar4);
    puVar4 = (undefined4 *)
             gta2::Player_GetCarPoints(self,local_10,(GlassInfo *)&DAT_0066ad08);
    local_8[0] = (SpawnPoint *)*puVar4;
    local_8[1] = (SpawnPoint *)puVar4[1];
    FUN_004a32d0(local_8);
    return;
  }
  FUN_00432860(&DAT_0066ad08,&DAT_005e6888,&DAT_005e688c);
  FUN_004828c0(&DAT_0066ad08,(int *)param_1);
  pGVar5 = (GlassInfo *)
           gta2::SpriteS1_sub_40E5D0((CarSystemManager *)&self->theta,(Ped *)&param_1,
                      (int)&stack0x00000008);
  FUN_0040f6b0(&DAT_0066ad08,pGVar5);
  gta2::Player_sub_40E530((Point2D *)&DAT_0066ad0c,&self->field28_0x3c);
  _DAT_0066ad08 = DAT_005e6888;
  pGVar5 = (GlassInfo *)
           gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066ad0c,(GlassInfo *)&stack0x00000008,
                      (S127 *)&DAT_005e6884);
  pSpriteS1 = (SpriteS1 *)
              gta2::Player_FUN_00403840((Player *)&param_1,(int *)&param_1,pGVar5);
  pGVar5 = (GlassInfo *)
           gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066ad0c,(GlassInfo *)local_10,
                      (S127 *)&DAT_005e6880);
  this_00 = (Point2D *)gta2::Player_FUN_00403840(this_01,(int *)local_8,pGVar5);
  bVar2 = gta2::Point2D_FUN_004037e0(this_00,pSpriteS1);
  if (CONCAT31(extraout_var,bVar2) == 0) {
    _DAT_0066ad0c = DAT_005e6884;
  }
  else {
    _DAT_0066ad0c = DAT_005e6880;
  }
  puVar4 = (undefined4 *)
           gta2::Player_GetCarPoints(self,local_10,(GlassInfo *)&DAT_0066ad08);
  local_8[0] = (SpawnPoint *)*puVar4;
  local_8[1] = (SpawnPoint *)puVar4[1];
  bVar2 = gta2::Point2D_FUN_004037e0((Point2D *)&self->field27_0x38,(SpriteS1 *)&DAT_0066ad08);
  if (CONCAT31(extraout_var_00,bVar2) == 0) {
    gta2::bitShiftLeft1(&stack0x00000008,NULL);
    puVar4 = (undefined4 *)&stack0x00000008;
    puVar3 = (undefined4 *)&DAT_0066ac4c;
  }
  else {
    gta2::bitShiftLeft1(&stack0x00000008,NULL);
    puVar4 = (undefined4 *)&stack0x00000008;
    puVar3 = (undefined4 *)gta2::JustCopyByPtrAtoC(&DAT_0066ac4c,&param_1);
  }
  FUN_00432860(&DAT_0066afb4,puVar3,puVar4);
  FUN_004a32d0(local_8);
  return;
}


// 0x004a4170: Player::sub_4A4170
// IDA: Player::sub_4A4170
// Ghidra: ---
void gta2::Player_sub_4A4170(Player *self, SpriteS1 *pPed, S202 *pPed_4)
{
  Weapon **v4; // eax
  SpriteS1 *v5; // edi
  Car *pCar; // eax
  SpriteS1 *GameObject; // eax
  EventHandler *v8; // eax
  char v9; // [esp-4h] [ebp-14h]
  Weapon *arg0[2]; // [esp+8h] [ebp-8h] BYREF

  switch ( dword_5E6874 )
  {
    case 1:
      gta2::Player_sub_4A3DF0(self, pPed);
      break;
    case 2:
      gta2::Player_sub_4A3FB0(self, pPed, pPed_4);
      break;
    case 3:
      v4 = gta2::SpriteS1_sub_4BD8A0(
             self->sCar1->CarSprite,
             arg0,
             unk_5E6894,
             (int *)pPed,
             (__int16)pPed_4,
             byte_66AB6C,
             &unk_66AB74,
             (char *)&pPed_4);
      v5 = unk_5E6894;
      *(_DWORD *)&unk_66AD08.S200[0].A = *v4;
      unk_66AD0C = v4[1];
      pCar = gta2::SpriteS1_GetCar(unk_5E6894);
      if ( pCar )
      {
        gta2::Player_sub_4A34A0(self, pCar);
      }
      else
      {
        GameObject = (SpriteS1 *)gta2::SpriteS1_GetGameObject(v5);
        if ( GameObject )
        {
          gta2::Player_sub_4A0A30(self, GameObject);
        }
        else
        {
          v9 = byte_66AB6C[0];
          v8 = (EventHandler *)gta2::SpriteS1_sub_40FEC0(v5);
          gta2::Player_sub_4A3A40(self, v8, v9);
        }
      }
      break;
  }
  gta2::CameraOrPhysics_sub_410210(gCameraOrPhysics, self->sCar1->CarSprite, (int)unk_66B034.Car);
}


// 0x004a4310: Player::FUN_004a4310
// IDA: ---
// Ghidra: Player::FUN_004a4310
undefined1 gta2::Player_FUN_004a4310(Player *self)
{
  bool bVar1;
  byte bVar2;
  undefined3 extraout_var;
  undefined4 uVar3;
  int iVar4;
  void *this_00;
  undefined4 *puVar5;
  undefined3 extraout_var_00;
  undefined1 uVar6;
  int iVar7;
  int iVar8;
  undefined1 *pS110;
  int *piVar9;
  SpriteS1 *local_24;
  SpriteS1 *local_20;
  SpriteS1 *local_1c;
  undefined1 local_18 [8];
  int aiStack_10 [4];
  
  uVar6 = 0;
  iVar8 = 0;
  iVar7 = 2;
  bVar1 = gta2::Player_sub_40CE70((Player *)&DAT_0066afc0,(Player *)&DAT_0066ad4c)
  ;
  iVar4 = CONCAT31(extraout_var,bVar1);
  while( true ) {
    if (iVar4 == 0) {
      return uVar6;
    }
    FUN_004637b0(&PTR_005e6874);
    gta2::bitShiftLeft1(&local_1c,NULL);
    *(SpriteS1 **)&self->field44_0x70 = local_1c;
    gta2::Player_sub_49DEF0(self);
    gta2::Player_sub_49EEB0(self,_DAT_0066ac4c);
    gta2::Player_sub_49F1B0(self);
    uVar3 = gta2::Player_LowerCarToGround(self,(int *)&local_20,(int *)&local_24);
    if ((char)uVar3 != '\0') {
      uVar6 = 1;
      if ((DAT_005e6894 != 0) && (iVar4 = 0, 0 < iVar8)) {
        do {
          if (aiStack_10[iVar4] == DAT_005e6894) {
            gta2::Player_sub_49DE40(self);
            gta2::Player_sub_49EEB0(self);
            gta2::Player_sub_4A2980(self);
            return 1;
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < iVar8);
      }
      gta2::Player_FUN_004a30a0(self,(SpriteS1 *)&local_20,(SpriteS1 *)&local_24);
      bVar1 = gta2::Car_IsTrainOrTrainCarriage(self->CarPlayerPre);
      if ((bVar1) &&
         (bVar2 = gta2::Player_FUN_0049e450((Player *)&self->S103_), bVar2 == 0)) {
        local_24 = _DAT_0066acdc;
      }
      gta2::Player_CollideCars(self,local_20,local_24);
    }
    pS110 = local_18;
    piVar9 = (int *)&DAT_0066afc0;
    this_00 = gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066ac4c,(GlassInfo *)(local_18 + 4)
                         ,(S127 *)&local_24);
    puVar5 = (undefined4 *)gta2::WorldCoordinateToScreenCoord(this_00,pS110,piVar9);
    _DAT_0066afc0 = *puVar5;
    aiStack_10[iVar8] = DAT_005e6894;
    iVar8 = iVar8 + 1;
    bVar2 = FUN_0049ef20(&PTR_005e6874);
    if (((bVar2 != 0) || (bVar2 = FUN_00446aa0(&PTR_005e6874), bVar2 != 0)) &&
       (iVar7 < 4)) {
      iVar7 = iVar7 + 1;
    }
    gta2::Player_sub_4A2980(self);
    if (iVar7 <= iVar8) break;
    bVar1 = gta2::Player_sub_40CE70((Player *)&DAT_0066afc0,(Player *)&DAT_0066ad4c);
    iVar4 = CONCAT31(extraout_var_00,bVar1);
  }
  return uVar6;
}


// 0x004a4490: Player::sub_4A4490
// IDA: Player::sub_4A4490
// Ghidra: Player::FUN_004a4490
byte gta2::Player_sub_4A4490(Player *self)
{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  byte bVar4;
  bool bVar5;
  byte bVar6;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined4 *puVar7;
  undefined4 local_c;
  int local_8;
  
  local_8 = self->RESPECT;
  local_c = *(undefined4 *)&self->EnterControlStatus;
  bVar6 = 0;
  while( true ) {
    _DAT_0066afc0 = _DAT_0066ac4c;
    bVar4 = gta2::Player_FUN_004a4310(self);
    if (bVar6 != 0) break;
    self->field_0xaa = 0;
    bVar5 = gta2::Player_IsCurrentPlayer((Player *)&DAT_0066afc0,(Player *)&DAT_0066ac4c);
    if ((CONCAT31(extraout_var,bVar5) == 0) || (bVar4 == 0)) goto LAB_004a452c;
    bVar6 = gta2::Player_sub_49DDF0(self);
    if (bVar6 == 0) goto LAB_004a452c;
    bVar6 = gta2::Player_sub_4A2D70(self);
    if (bVar6 == 0) goto LAB_004a452c;
    gta2::Player_sub_4A0C60(self);
    gta2::Player_sub_4A0CC0(self);
  }
  bVar5 = gta2::Player_IsCurrentPlayer((Player *)&DAT_0066afc0,(Player *)&DAT_0066ac4c);
  if (CONCAT31(extraout_var_00,bVar5) != 0) {
    gta2::S103_sub_41E1E0((LinkedList *)&self->S103_);
    uVar1 = DAT_0066acdc_1;
    uVar2 = uRam0066acde;
    uVar3 = uRam0066acdf;
    self->DeathReason = DAT_0066acdc;
    self->field49_0x75 = uVar1;
    self->DoDebugKeys1 = uVar2;
    self->DoDebugKeys = uVar3;
  }
LAB_004a452c:
  puVar7 = (undefined4 *)
           gta2::Player_sub_401B40((SpawnPoint *)&self->EnterControlStatus,
                      (GlassInfo *)&stack0xfffffffc,(S127 *)&stack0xfffffff4);
  self->CurrentPlayer = (Player *)*puVar7;
  puVar7 = (undefined4 *)
           gta2::Player_sub_401B40((SpawnPoint *)&self->RESPECT,(GlassInfo *)&stack0xfffffffc
                      ,(S127 *)&local_8);
  self->Player_ = (Player *)*puVar7;
  return bVar4;
}


// 0x004a4570: Player::sub_4A4570
// IDA: Player::sub_4A4570
// Ghidra: ---
bool gta2::Player_sub_4A4570(Player *self)
{
  SpriteS1 *v1; // edi
  char v3; // al
  int v4; // eax
  char v5; // bl
  char v6; // bl
  char v7; // bl
  char v8; // bl
  char v9; // bl
  bool IsDriverPlayer; // al
  struct Player *pPlayer; // ecx
  char v12; // bl
  char v13; // bl
  bool v14; // al
  int State; // esi
  bool result; // al
  char v17; // [esp+Bh] [ebp-1h]

  gta2::Player_sub_49ECC0(self);
  v3 = gta2::Car_sub_4220A0(self->sCar1);
  if ( v3 != self->field_A9 )
  {
    self->field_A9 = v3;
    gta2::Player_sub_49EDC0(self);
  }
  self->field_84 = unk_66ACDC;
  v4 = *(_DWORD *)&self->AttackIsChanged;
  self->field_88 = unk_66ACDC;
  switch ( v4 )
  {
    case 0:
      v12 = gta2::Player_sub_49E270(self);
      gta2::Player_sub_49F350(self);
      v13 = gta2::Player_sub_4A4490(self) | v12;
      v7 = gta2::Player_sub_4A2DB0(self) | v13;
      goto LABEL_10;
    case 1:
      gta2::Player_sub_49F500(self);
      v5 = gta2::Player_sub_49E270(self);
      gta2::Player_sub_49DD30(self);
      goto LABEL_5;
    case 2:
      gta2::Player_sub_49F500(self);
      v5 = gta2::Player_sub_49E270(self);
LABEL_5:
      gta2::Player_sub_49F280(self);
      gta2::Player_sub_4A16B0(self);
      gta2::Player_sub_4A2F20(self);
      gta2::Player_sub_49EA70(self);
      gta2::Player_sub_4A1B20(self);
      gta2::Player_sub_49F4E0(self);
      gta2::Player_sub_4A17C0(self, v1);
      gta2::Player_sub_49F350(self);
      v6 = gta2::Player_sub_4A4490(self) | v5;
      v7 = gta2::Player_sub_4A2DB0(self) | v6;
      gta2::Player_sub_4A0560(self);
      gta2::Player_sub_49F4F0(self);
      gta2::Player_sub_49EA60(self);
      break;
    case 3:
      v8 = gta2::Player_sub_49E270(self);
      gta2::Player_sub_4A2F20(self);
      gta2::Player_sub_49F350(self);
      gta2::Player_sub_4A2DB0(self);
      v9 = gta2::Player_sub_4A4490(self) | v8;
      v7 = gta2::Player_sub_4A2DB0(self) | v9;
      gta2::Player_sub_4A0560(self);
      IsDriverPlayer = gta2::Car_IsDriverPlayer(self->sCar1);
      pPlayer = self;
      if ( IsDriverPlayer )
        goto LABEL_8;
      goto LABEL_13;
    case 4:
      v7 = gta2::Player_sub_49E270(self);
      gta2::Player_sub_4A3120(self);
      gta2::Player_sub_4A2980(self);
LABEL_10:
      gta2::Player_sub_4A0560(self);
      v14 = gta2::Car_IsDriverPlayer(self->sCar1);
      pPlayer = self;
      if ( v14 )
LABEL_8:
        gta2::Player_SetAttackIsChanged(pPlayer);
      else
LABEL_13:
        gta2::Player_SetAttackChanged(pPlayer);
      break;
    default:
      v7 = v17;
      break;
  }
  result = 0;
  if ( gta2::Player_sub_4A1BA0(self) )
  {
    if ( !v7 )
    {
      State = self->State;
      if ( State != 7 && State != 8 && State != 6 )
        return 1;
    }
  }
  return result;
}


// 0x004a4780: Player::sub_4A4780
// IDA: Player::sub_4A4780
// Ghidra: ---
char gta2::Player_sub_4A4780(Player *self, Car *a2, char a3)
{
  int *v3; // eax
  char v5; // cl
  int *v6; // esi
  int v7; // ecx

  v3 = &self->field_58;
  if ( gNetworkGame )
    return 0;
  if ( a2 != self->sCar1 )
  {
    v5 = 1;
    while ( (Car *)*v3 != a2 )
    {
      --v3;
      if ( --v5 < 0 )
        return 0;
    }
    v6 = v3 + 1;
    if ( v5 < 2 )
    {
      v7 = (unsigned __int8)(2 - v5);
      do
      {
        if ( !a3 )
          *v3++ = *v6++;
        --v7;
      }
      while ( v7 );
    }
    if ( !a3 )
      *v3 = (int)a2;
  }
  return 1;
}


// 0x004a47f0: Player::sub_4A47F0
// IDA: Player::sub_4A47F0
// Ghidra: ---
void * gta2::Player_sub_4A47F0(Player *self, Car *a2)
{
  void *result; // eax
  unsigned __int8 v3; // dl
  int *v4; // ecx

  result = &self->field_54;
  if ( !gNetworkGame )
  {
    v3 = 0;
    while ( *(Car **)result != a2 )
    {
      result = (char *)result + 4;
      if ( ++v3 >= 2u )
      {
        v4 = &self->field_54 + v3;
        if ( *v4 == *(_DWORD *)result )
          *v4 = 0;
        return result;
      }
    }
    *(_DWORD *)result = *((_DWORD *)result + 1);
    if ( v3 < 2u )
    {
      qmemcpy(result, (char *)result + 4, 4 * (unsigned __int8)(2 - v3));
      result = (char *)result + 4 * (unsigned __int8)(2 - v3);
    }
    *(_DWORD *)result = 0;
  }
  return result;
}


// 0x004a4870: Player::FUN_004a4870
// IDA: sub_4A4870
// Ghidra: Player::FUN_004a4870
undefined4 gta2::Player_FUN_004a4870(Player *self)
{
  if (self->SelectWeapon == -1) {
    return 0;
  }
  return self->sWeapon[self->SelectWeapon];
}


// 0x004a4890: Player::sub_4A4890
// IDA: Player::sub_4A4890
// Ghidra: ---
int gta2::Player_sub_4A4890(Player *self, Weapon *pWeapon)
{
  int index; // eax

  LOWORD(index) = pWeapon->TypeWeapon;
  self->sWeapon[(__int16)index] = pWeapon;
  if ( !BYTE1(self->S103_5) )
    self->SelectWeapon = index;
  return index;
}


// 0x004a48c0: Player::SetDefautWeapon
// IDA: Player::SetDefautWeapon
// Ghidra: ---
void gta2::Player_SetDefautWeapon(Player *self)
{
  memset(&self->sWeapon[15], 0, 52u);
}


// 0x004a48e0: Player::SetActivePowerUps
// IDA: Player::SetActivePowerUps
// Ghidra: ---
int gta2::Player_SetActivePowerUps(Player *self)
{
  int result; // eax
  bool v2; // bl

  for ( result = 0; result < 17; ++result )
  {
    if ( result == 11 )
    {
      v2 = gHUNSRUS;
      goto LABEL_6;
    }
    if ( result == 7 )
    {
      v2 = gSCHURULZ;
LABEL_6:
      if ( v2 )
        continue;
    }
    self->PowerUp[result] = POWERUP_TYPE_MULTIPLIER;
  }
  return result;
}


// 0x004a4930: Player::SetPlayer
// IDA: Player::SetPlayer
// Ghidra: ---
void gta2::Player_SetPlayer(Player *self, Player *a2)
{
  self->Player_ = a2;
}


// 0x004a4940: Player::sub_4A4940
// IDA: Player::sub_4A4940
// Ghidra: ---
char gta2::Player_sub_4A4940(Player *self, unsigned __int8 a2)
{
  Gangs *pGang; // esi
  Gang *NextUsedGang; // eax
  int v5; // edi

  pGang = (Gangs *)gta2::Gangs_GetFirstUsedGang(gGangs);
  LOBYTE(NextUsedGang) = a2;
  if ( a2 )
  {
    v5 = a2;
    do
    {
      NextUsedGang = gta2::Gangs_GetNextUsedGang(gGangs);
      --v5;
      pGang = (Gangs *)NextUsedGang;
    }
    while ( v5 );
  }
  if ( pGang )
  {
    if ( gta2::Gang_GetRespectForPlayer(pGang->Gang_, self->Ids) < 100 )
      gta2::Gangs_IncreaseRespectForPlayer(pGang, self->Ids, 20);
    else
      gta2::Gang_SetRespectForPlayer(pGang->Gang_, self->Ids, -100);
  }
  return (char)NextUsedGang;
}


// 0x004a49b0: Player::sub_4A49B0
// IDA: Player::sub_4A49B0
// Ghidra: ---
byte gta2::Player_sub_4A49B0(Player *self)
{
  struct Ped *v1; // ecx
  byte result; // al
  struct Ped *v3; // ecx
  byte v4; // dl
  byte a2; // [esp+0h] [ebp-4h]

  switch ( gta2::Ped_GetCopStars(self->MainPed) )
  {
    case 0u:
      gta2::sub_434C40(v1, 600u);
      break;
    case 1u:
      gta2::sub_434C40(v1, 1600u);
      break;
    case 2u:
      gta2::sub_434C40(v1, 3000u);
      break;
    case 3u:
      gta2::sub_434C40(v1, 5000u);
      break;
    case 4u:
      gta2::sub_434C40(v1, 8000u);
      break;
    case 5u:
      gta2::sub_434C40(v1, 12000u);
      break;
    case 6u:
      gta2::sub_434C40(v1, 0);
      break;
    default:
      break;
  }
  a2 = gPolice->MaxFrameRateChek;
  result = gta2::Ped_GetCopStars(v1);
  if ( result > v4 )
    return gta2::Ped_HandleWantedEvent(v3, a2);
  return result;
}


// 0x004a49c0: Player::sub_4A49C0
// IDA: Player::sub_4A49C0
// Ghidra: ---
char gta2::Player_sub_4A49C0(_BYTE *self, __int16 a2)
{
  char result; // al

  result = a2 - 71;
  switch ( a2 )
  {
    case 71:
      self[116] = 0;
      break;
    case 72:
      self[112] = 0;
      break;
    case 73:
      self[117] = 0;
      break;
    case 75:
      self[114] = 0;
      break;
    case 77:
      self[115] = 0;
      break;
    case 80:
      self[113] = 0;
      break;
    case 201:
      result = do_debug_keys;
      if ( do_debug_keys )
        self[119] = 0;
      break;
    case 209:
      result = do_debug_keys;
      if ( do_debug_keys )
        self[118] = 0;
      break;
    default:
      return result;
  }
  return result;
}


// 0x004a4ae0: Player::sub_4A4AE0
// IDA: Player::sub_4A4AE0
// Ghidra: ---
bool gta2::Player_sub_4A4AE0(int self)
{
  int v1; // esi
  char v2; // al
  bool v3; // zf
  char v4; // al
  char v5; // al
  char v6; // dl
  char v7; // al
  char v8; // dl
  char v9; // al
  char v10; // dl
  char v11; // al
  char v12; // dl
  char v13; // al
  char v14; // dl
  char v15; // al
  char v16; // al
  int v17; // esi
  char v18; // dl
  bool result; // al

  v1 = *(_DWORD *)(self + 4);
  v2 = (v1 & 1) == 1;
  v3 = v2 == *(_BYTE *)(self + 120);
  *(_BYTE *)(self + 120) = v2;
  *(_BYTE *)(self + 139) = !v3;
  v4 = (v1 & 2) == 2;
  v3 = v4 == *(_BYTE *)(self + 121);
  *(_BYTE *)(self + 121) = v4;
  *(_BYTE *)(self + 140) = !v3;
  *(_BYTE *)(self + 122) = (v1 & 4) == 4;
  *(_BYTE *)(self + 123) = (v1 & 8) == 8;
  v5 = (v1 & 0x10) == 16;
  v3 = v5 == *(_BYTE *)(self + 124);
  *(_BYTE *)(self + 124) = v5;
  *(_BYTE *)(self + 141) = !v3;
  v6 = *(_BYTE *)(self + 126);
  v7 = (v1 & 0x40) == 64;
  *(_BYTE *)(self + 126) = v7;
  *(_BYTE *)(self + 138) = v7 != v6;
  v8 = *(_BYTE *)(self + 125);
  v9 = (v1 & 0x20) == 32;
  *(_BYTE *)(self + 125) = v9;
  *(_BYTE *)(self + 137) = v9 != v8;
  v10 = *(_BYTE *)(self + 127);
  v11 = (v1 & 0x80) == 0x80;
  *(_BYTE *)(self + 127) = v11;
  *(_BYTE *)(self + 136) = v11 != v10;
  v12 = *(_BYTE *)(self + 128);
  v13 = (v1 & 0x100) == 256;
  *(_BYTE *)(self + 128) = v13;
  *(_BYTE *)(self + 135) = v13 != v12;
  v14 = *(_BYTE *)(self + 129);
  v15 = (v1 & 0x200) == 512;
  *(_BYTE *)(self + 129) = v15;
  *(_BYTE *)(self + 132) = v15 != v14;
  v16 = (v1 & 0x400) == 1024;
  v3 = v16 == *(_BYTE *)(self + 130);
  *(_BYTE *)(self + 130) = v16;
  v17 = v1 & 0x800;
  *(_BYTE *)(self + 133) = !v3;
  v18 = *(_BYTE *)(self + 131);
  *(_BYTE *)(self + 131) = v17 == 2048;
  result = (v17 == 2048) != v18;
  *(_BYTE *)(self + 134) = result;
  return result;
}


// 0x004a4c40: Player::sub_4A4C40
// IDA: Player::sub_4A4C40
// Ghidra: Player::FUN_004a4c40
byte gta2::Player_sub_4A4C40(Player *self,Car *pCar)
{
  byte bVar1;
  undefined4 in_EAX;
  undefined3 uVar2;
  char local_4;
  undefined3 uStack_3;
  
  uStack_3 = (undefined3)((uint)self >> 8);
  if (self->SelectWeapon < 0xf) {
    local_4 = self->Tango1;
    in_EAX = CONCAT31((int3)((uint)in_EAX >> 8),local_4);
  }
  else {
    local_4 = '\0';
  }
  uVar2 = (undefined3)((uint)in_EAX >> 8);
  bVar1 = gta2::Car_sub_429810(pCar,CONCAT31(uVar2,self->KEY_UP),
                     CONCAT31(uStack_3,self->Backward),
                     CONCAT31(uVar2,self->RotateLeft),
                     CONCAT31(uStack_3,self->RotateRight),
                     CONCAT31(uVar2,self->Jump),
                     CONCAT31(uStack_3,self->keySpecial),self->field64_0x84,
                     local_4);
  return bVar1;
}


// 0x004a4c90: Player::sub_4A4C90
// IDA: Player::sub_4A4C90
// Ghidra: ---
int gta2::Player_sub_4A4C90(Player *self)
{
  int result; // eax

  result = self->Sound;
  if ( result )
    *(_DWORD *)(result + 12) = &self->CameraOrPhysics_;
  return result;
}


// 0x004a4cb0: Player::sub_4A4CB0
// IDA: Player::sub_4A4CB0
// Ghidra: ---
void gta2::Player_sub_4A4CB0(Player *self)
{
  if ( self->debugKey1 )
  {
    gta2::sub_41E510(&self->CameraOrPhysics1);
    gta2::sub_41E510(&self->CameraOrPhysics2);
  }
  if ( self->debugKey2 )
  {
    gta2::sub_41E4E0(&self->CameraOrPhysics1);
    gta2::sub_41E4E0(&self->CameraOrPhysics2);
  }
}


// 0x004a4cf0: Player::sub_4A4CF0
// IDA: Player::sub_4A4CF0
// Ghidra: FUN_004a4cf0
void gta2::Player_sub_4A4CF0(int param_1,CameraOrPhysics *param_2)
{
  if (*(char *)(param_1 + 0x82) != '\0') {
    FUN_0041eef0(*(undefined1 *)(param_1 + 0x78),*(undefined1 *)(param_1 + 0x79)
                 ,*(undefined1 *)(param_1 + 0x7a),
                 *(undefined1 *)(param_1 + 0x7b));
    *(undefined1 *)(param_1 + 0x7a) = 0;
    *(undefined1 *)(param_1 + 0x7b) = 0;
    *(undefined1 *)(param_1 + 0x78) = 0;
    *(undefined1 *)(param_1 + 0x79) = 0;
    *(undefined1 *)(param_1 + 0x8b) = 0;
    *(undefined1 *)(param_1 + 0x8c) = 0;
    return;
  }
  gta2::CameraOrPhysics_sub_41F0A0(param_2);
  return;
}


// 0x004a4d50: Player::AddLives
// IDA: Player::AddLives
// Ghidra: ---
int gta2::Player_AddLives(Player *self, int a2)
{
  int result; // eax

  result = a2;
  if ( !do_infinite_lives || a2 > 0 )
    return gta2::PlayerStats_SetMultiPlayer((PlayerStats *)&self->Lives, a2);
  return result;
}


// 0x004a4e10: Player::GetDeathDescription
// IDA: Player::GetDeathDescription
// Ghidra: ---
const char * gta2::Player_GetDeathDescription(Player *self)
{
  const char *result; // eax

  switch ( self->DeathReason )
  {
    case WASTED0:
    case WASTED:
      result = "wasted";
      break;
    case FRIED:
      result = "fried";
      break;
    case NICKED:
      result = "nicked";
      break;
    case SHOCKED:
      result = "shocked";
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


// 0x004a4e70: Player::sub_4A4E70
// IDA: Player::sub_4A4E70
// Ghidra: ---
void gta2::Player_sub_4A4E70(Player *self)
{
  BYTE1(self->S103_5) = 0;
}


// 0x004a4ea0: Player::PlayerControl
// IDA: Player::PlayerControl
// Ghidra: ---
void gta2::Player_PlayerControl(Player *self)
{
  self->Forward = 0;
  self->Backward = 0;
  self->RotateLeft = 0;
  self->RotateRight = 0;
  self->Attack = 0;
  self->Enter = 0;
  self->Jump = 0;
  self->NextWeaponZ = 0;
  self->PrevWeaponX = 0;
  self->keySpecial = 0;
  self->keySpecial2 = 0;
  self->field_83 = 0;
  LOBYTE(self->field_84) = 0;
  LOBYTE(self->field_88) = 0;
  HIBYTE(self->field_84) = 0;
  BYTE1(self->field_88) = 0;
  self->field_8D = 0;
  BYTE2(self->field_88) = 0;
  HIBYTE(self->field_88) = 0;
  self->AttackIsChanged = 0;
}


// 0x004a5100: Player::sub_4A5100
// IDA: Player::sub_4A5100
// Ghidra: ---
char gta2::Player_sub_4A5100(Player *self)
{
  struct Ped *pPassenger; // ecx
  ALL_PED CurrentOccupation; // eax

  if ( !self->field_2D0
    || (pPassenger = self->pPassenger) == 0
    || (CurrentOccupation = gta2::Ped_GetCurrentOccupation(pPassenger), CurrentOccupation != EMPTY) )
  {
    LOBYTE(CurrentOccupation) = 0;
  }
  return CurrentOccupation;
}


// 0x004a5130: Player::GetCurrentPed
// IDA: Player::GetCurrentPed
// Ghidra: ---
Ped * gta2::Player_GetCurrentPed(Player *self)
{
  if ( self->MultiPlayerMode == 2 )
    return self->pPassenger;
  else
    return self->MainPed;
}


// 0x004a5150: Player::GetActivePed
// IDA: Player::GetActivePed
// Ghidra: ---
Ped * gta2::Player_GetActivePed(Player *self)
{
  int MultiPlayerMode; // eax

  MultiPlayerMode = self->MultiPlayerMode;
  if ( MultiPlayerMode == 2 || MultiPlayerMode == 3 )
    return self->pPassenger;
  else
    return self->MainPed;
}


// 0x004a5180: Player::sub_4A5180
// IDA: Player::sub_4A5180
// Ghidra: Player::FUN_004a5180
void gta2::Player_sub_4A5180(Player *self)
{
  self->timeSecond = 0;
  return;
}


// 0x004a51c0: Player::sub_4A51C0
// IDA: Player::sub_4A51C0
// Ghidra: ---
char gta2::Player_sub_4A51C0(Player *self, Car *pCar)
{
  char result; // al
  int *v3; // esi
  int *v4; // edi
  int v5; // edx

  result = gNetworkGame;
  v3 = &self->field_54;
  v4 = &self->field_54;
  if ( !gNetworkGame )
  {
    result = gta2::Player_sub_4A4780(self, pCar, 0);
    if ( !result )
    {
      while ( *v4 )
      {
        ++v4;
        if ( (unsigned __int8)++result >= 3u )
        {
          gta2::sub_420920((void *)*v3);
          v5 = v3[2];
          result = (char)v3;
          *v3 = v3[1];
          v3[1] = v5;
          v3[2] = (int)pCar;
          return result;
        }
      }
      *v4 = (int)pCar;
    }
  }
  return result;
}


// 0x004a5220: Player::sub_4A5220
// IDA: Player::sub_4A5220
// Ghidra: ---
void gta2::Player_sub_4A5220(Player *self, Car *a1, WeaponType pWeaponType)
{
  Weapon *WeaponInPool; // eax
  Weapon *pWeapon; // ebx
  struct Ped *Driver; // edi

  LOWORD(self->S103_1) = self->SelectWeapon;
  WeaponInPool = gta2::Turrel_FindWeaponInPool(gArsenal, a1, pWeaponType);
  pWeapon = WeaponInPool;
  if ( WeaponInPool )
  {
    HIWORD(self->S103_1) = gta2::Weapon_GetAmmo(WeaponInPool);
  }
  else
  {
    HIWORD(self->S103_1) = 0;
    pWeapon = gta2::Turrel_CreateWeaponForTurret(gArsenal, pWeaponType, a1, 0);
  }
  *(_DWORD *)&self->SelectWeaponNext = pWeaponType;
  self->pS103 = (S103 *)a1;
  self->ID = a1->ID;
  gta2::Weapon_GiveWeaponInfiniti(pWeapon);
  Driver = a1->Driver;
  if ( Driver )
  {
    if ( Driver->isPlayer == self )
    {
      self->sWeapon[pWeaponType] = pWeapon;
      self->SelectWeapon = self->SelectWeaponNext;
    }
  }
}


// 0x004a5300: Player::ProcessWeaponChange
// IDA: Player::ProcessWeaponChange
// Ghidra: ---
void gta2::Player_ProcessWeaponChange(Player *self)
{
  Arsenal *pCar; // ebx
  WeaponType pWeaponType; // edi
  Car *pS103; // eax
  Weapon *WeaponInPool; // edi
  EventHandler *S63_9; // eax

  if ( LOWORD(self->S103_1) != 0xFFFE )
  {
    pCar = gArsenal;
    pWeaponType = *(_DWORD *)&self->SelectWeaponNext;
    if ( gta2::Turrel_GetCarBomb(gArsenal, pWeaponType) )
    {
      pS103 = (Car *)self->pS103;
      if ( pS103->ID != self->ID )
        goto LABEL_14;
      WeaponInPool = gta2::Turrel_FindWeaponInPool(pCar, pS103, pWeaponType);
      gta2::sub_4A4FF0(WeaponInPool, HIWORD(self->S103_1));
      if ( HIWORD(self->S103_1) )
        goto LABEL_14;
      gta2::Weapon1_sub_4A4F20(gWeaponDatabase, WeaponInPool);
      S63_9 = self->pS103->S104_.S63_9;
      if ( !S63_9 || *(Player **)&S63_9[7].field_28 != self )
        goto LABEL_14;
      self->sWeapon[*(_DWORD *)&self->SelectWeaponNext] = 0;
    }
    else
    {
      if ( gVOLTFEST && pWeaponType == ElectorGun || FLAMEON && pWeaponType == FireGun )
        goto LABEL_14;
      gta2::Player_sub_4A4E70(self);
      gta2::sub_4A4FF0(&self->sWeapon[*(_DWORD *)&self->SelectWeaponNext]->Ammo, HIWORD(self->S103_1));
    }
    self->SelectWeapon = (__int16)self->S103_1;
LABEL_14:
    LOWORD(self->S103_1) = -2;
  }
}


// 0x004a53d0: Player::sub_4A53D0
// IDA: Player::sub_4A53D0
// Ghidra: Player::FUN_004a53d0
bool gta2::Player_sub_4A53D0(Player *self)
{
  bool bVar1;
  int iVar2;
  Weapon **ppWVar3;
  
  iVar2 = 0;
  ppWVar3 = self->sWeapon;
  do {
    bVar1 = gta2::Weapon_GetArmo(*ppWVar3);
    if (bVar1) {
      return true;
    }
    iVar2 = iVar2 + 1;
    ppWVar3 = ppWVar3 + 1;
  } while (iVar2 < 0xf);
  return bVar1;
}


// 0x004a5400: Player::sub_4A5400
// IDA: Player::sub_4A5400
// Ghidra: ---
char gta2::Player_sub_4A5400(Player *self, WeaponType Id, unsigned __int8 pAmmo)
{
  struct Ped *CurrentPed; // eax
  bool v5; // bl
  char result; // al

  CurrentPed = gta2::Player_GetCurrentPed(self);
  if ( gta2::Ped_GetCarPlayers(CurrentPed) )
    v5 = 0;
  else
    v5 = !gta2::Player_sub_4A53D0(self);
  result = gta2::Weapon_sub_4CCB70(self->sWeapon[Id], pAmmo);
  if ( !BYTE1(self->S103_5) && result && v5 )
    self->SelectWeapon = Id;
  return result;
}


// 0x004a5460: Player::sub_4A5460
// IDA: Player::sub_4A5460
// Ghidra: ---
char gta2::Player_sub_4A5460(Player *self, char a2, char a3)
{
  struct Ped *pPed; // eax
  int v5; // edi
  __int16 SelectWeapon; // ax
  __int16 v7; // cx
  Weapon *v8; // eax
  Weapon *v9; // ecx
  __int16 v10; // ax
  Weapon *v11; // ecx

  pPed = gta2::Player_GetCurrentPed(self);
  if ( !BYTE1(self->S103_5) )
  {
    if ( !pPed || (v5 = 28, !gta2::Ped_GetCarPlayers(pPed)) )
      v5 = 15;
    SelectWeapon = self->SelectWeapon;
    if ( SelectWeapon < -1 || SelectWeapon >= v5 )
      self->SelectWeapon = 0;
    if ( a2 )
    {
      while ( 1 )
      {
        v7 = ++self->SelectWeapon;
        if ( v7 == v5 )
          break;
        if ( v7 != -1 )
        {
          v8 = self->sWeapon[v7];
          if ( !v8 || !gta2::Weapon_GetArmo(v8) )
            continue;
        }
        goto LABEL_15;
      }
      self->SelectWeapon = -1;
    }
LABEL_15:
    if ( !a3 )
    {
      LOWORD(pPed) = self->SelectWeapon;
      if ( (_WORD)pPed == 0xFFFF )
        return (char)pPed;
      v9 = self->sWeapon[(__int16)pPed];
      if ( v9 )
      {
        LOBYTE(pPed) = gta2::Weapon_GetArmo(v9);
        if ( (_BYTE)pPed )
          return (char)pPed;
      }
      self->field_8F = 1;
    }
    while ( 1 )
    {
      v10 = self->SelectWeapon;
      if ( v10 == -1 )
        self->SelectWeapon = v5 - 1;
      else
        self->SelectWeapon = v10 - 1;
      LOWORD(pPed) = self->SelectWeapon;
      if ( (_WORD)pPed == 0xFFFF )
        break;
      v11 = self->sWeapon[(__int16)pPed];
      if ( v11 )
      {
        LOBYTE(pPed) = gta2::Weapon_GetArmo(v11);
        if ( (_BYTE)pPed )
          break;
      }
    }
  }
  return (char)pPed;
}


// 0x004a5570: Player::sub_4A5570
// IDA: Player::sub_4A5570
// Ghidra: ---
char gta2::Player_sub_4A5570(Player *self, Car *a1)
{
  WeaponType v3; // esi
  Weapon **v4; // edi
  Weapon *WeaponInPool; // eax
  char result; // al
  __int16 TypeWeapon; // ax
  __int16 v8; // [esp+10h] [ebp-4h]

  v8 = -1;
  v3 = CAR_BOMB;
  v4 = &self->sWeapon[15];
  do
  {
    WeaponInPool = gta2::Turrel_FindWeaponInPool(gArsenal, a1, v3);
    *v4 = WeaponInPool;
    if ( WeaponInPool )
      v8 = v3;
    ++v3;
    ++v4;
  }
  while ( v3 < NO_WEAPON );
  result = BYTE1(self->S103_5);
  if ( !result )
  {
    self->Sw = self->SelectWeapon;
    TypeWeapon = self->TypeWeapon;
    if ( self->sWeapon[TypeWeapon] || (TypeWeapon = v8, v8 != -1) )
      self->SelectWeapon = TypeWeapon;
    return gta2::Player_sub_4A5460(self, 0, 0);
  }
  return result;
}


// 0x004a5600: Player::sub_4A5600
// IDA: Player::sub_4A5600
// Ghidra: ---
void gta2::Player_sub_4A5600(Player *self)
{
  Weapon **sWeapon; // esi
  int v2; // ebx
  Weapon *sWeapon_15; // edi

  sWeapon = &self->sWeapon[15];
  v2 = 13;
  do
  {
    sWeapon_15 = *sWeapon;
    if ( *sWeapon )
    {
      if ( !gta2::Weapon_GetArmo(*sWeapon) )
        gta2::Weapon1_sub_4A4F20(gWeaponDatabase, sWeapon_15);
    }
    *sWeapon++ = 0;
    --v2;
  }
  while ( v2 );
}


// 0x004a5640: Player::RestoreOnFootWeapons
// IDA: Player::RestoreOnFootWeapons
// Ghidra: ---
char gta2::Player_RestoreOnFootWeapons(Player *self)
{
  __int16 SelectWeapon; // ax
  __int16 S103_1; // ax
  __int16 Sw; // cx

  gta2::Player_sub_4A5600(self);
  SelectWeapon = self->SelectWeapon;
  if ( SelectWeapon >= 15 )
  {
    self->TypeWeapon = SelectWeapon;
    self->SelectWeapon = self->Sw;
  }
  S103_1 = (__int16)self->S103_1;
  if ( S103_1 >= 15 )
  {
    Sw = self->Sw;
    self->TypeWeapon = S103_1;
    LOWORD(self->S103_1) = Sw;
  }
  return gta2::Player_sub_4A5460(self, 0, 0);
}


// 0x004a5690: Player::sub_4A5690
// IDA: Player::sub_4A5690
// Ghidra: ---
char gta2::Player_sub_4A5690(Player *self)
{
  int v2; // ebx
  Weapon *v3; // esi
  __int16 SelectWeapon; // ax

  v2 = 15;
  v3 = self->sWeapon[0];
  do
  {
    if ( (!gVOLTFEST || v3->TypeWeapon != ElectorGun) && (!FLAMEON || v3->TypeWeapon != FireGun) && gta2::Weapon_GetArmo(v3) )
      gta2::Weapon_SetAmmo(v3, 0);
    ++v3;
    --v2;
  }
  while ( v2 );
  SelectWeapon = self->SelectWeapon;
  if ( SelectWeapon < 15 )
  {
    self->Sw = SelectWeapon;
    self->SelectWeapon = 0;
  }
  return gta2::Player_sub_4A5460(self, 0, 0);
}


// 0x004a5710: Player::sub_4A5710
// IDA: Player::sub_4A5710
// Ghidra: ---
int gta2::Player_sub_4A5710(Player *self)
{
  POWERUP_TYPE v2; // di
  int result; // eax

  v2 = self->PowerUp[POWERUP_TYPE_GET_OUTTA_JAIL_FREE_CARD];
  if ( self->PowerUp[POWERUP_TYPE_INVULNERABILITY] )
    gta2::Ped_sub_435F00(self->MainPed);
  if ( self->PowerUp[POWERUP_TYPE_ELECTROFINGERS] )
    gta2::Ped_SetMoneyValue(self->MainPed);
  if ( self->PowerUp[POWERUP_TYPE_INVISIBILITY] && !gHUNSRUS )
    gta2::Ped_DisableInvisibility(self->MainPed);
  result = gta2::Player_SetActivePowerUps(self);
  self->PowerUp[POWERUP_TYPE_GET_OUTTA_JAIL_FREE_CARD] = v2;
  return result;
}


// 0x004a5780: Player::GivePowerUp
// IDA: Player::GivePowerUp
// Ghidra: ---
char gta2::Player_GivePowerUp(Player *self, POWERUP_TYPE POWERUPTYPE)
{
  char result; // al
  struct Ped *MainPed; // esi
  struct Ped *pPed; // esi
  Gangs *RESPECT; // ecx
  struct Ped *v7; // esi

  switch ( POWERUPTYPE )
  {
    case POWERUP_TYPE_MULTIPLIER:
      if ( gta2::PlayerStats_getMoneyValue((PlayerStats *)&self->MultiPlayer) == 99 )
        goto LABEL_28;
      gta2::Player_SetMultiPlayer(self, 1);
      result = 1;
      break;
    case POWERUP_TYPE_LIFE:
      if ( gta2::PlayerStats_getMoneyValue((PlayerStats *)&self->Lives) == 99 )
        goto LABEL_28;
      gta2::Player_AddLives(self, 1);
      result = 1;
      break;
    case POWERUP_TYPE_HEALTH:
      MainPed = self->MainPed;
      if ( gta2::Ped_GetHealth(MainPed) >= 100 )
        goto LABEL_28;
      gta2::Ped_SetHealthFull(MainPed);
      result = 1;
      break;
    case POWERUP_TYPE_ARMOR:
      if ( self->PowerUp[POWERUP_TYPE_ARMOR] == POWERUP_TYPE_RESPECT )
        goto LABEL_28;
      self->PowerUp[3] = POWERUP_TYPE_RESPECT;
      result = 1;
      break;
    case POWERUP_TYPE_COP_BRIBE:
      pPed = self->MainPed;
      if ( !gta2::Ped_GetPoliceStar(pPed) )
        goto LABEL_28;
      gta2::Ped_SetPoliceNoStar(pPed);
      result = 1;
      break;
    case POWERUP_TYPE_INVULNERABILITY:
      if ( self->PowerUp[6] == 1200 )
        goto LABEL_28;
      self->PowerUp[6] = 1200;
      gta2::Ped_sub_43B560(self->MainPed);
      result = 1;
      break;
    case POWERUP_TYPE_DOUBLE_DAMAGE:
      if ( self->PowerUp[7] == 1800 )
        goto LABEL_28;
      self->PowerUp[7] = 1800;
      result = 1;
      break;
    case POWERUP_TYPE_FAST_RELOAD:
      if ( self->PowerUp[8] == 1800 )
        goto LABEL_28;
      self->PowerUp[8] = 1800;
      result = 1;
      break;
    case POWERUP_TYPE_ELECTROFINGERS:
      if ( self->PowerUp[9] == 2100 )
        goto LABEL_28;
      self->PowerUp[9] = 2100;
      gta2::Ped_sub_4A5060(self->MainPed);
      result = 1;
      break;
    case POWERUP_TYPE_RESPECT:
      RESPECT = self->RESPECT;
      if ( !RESPECT || gta2::Gang_GetRespectForPlayer(RESPECT->Gang_, self->Ids) == 100 )
        goto LABEL_28;
      gta2::Gangs_IncreaseRespectForPlayer(self->RESPECT, self->Ids, 20);
      result = 1;
      break;
    case POWERUP_TYPE_INVISIBILITY:
      if ( self->PowerUp[11] == 1800 )
        goto LABEL_28;
      self->PowerUp[11] = 1800;
      gta2::Ped_EnableInvisibility(self->MainPed);
      result = 1;
      break;
    case POWERUP_TYPE_INSTANT_GANG:
      v7 = self->MainPed;
      if ( !gta2::Ped_sub_4A5020(v7) )
        goto LABEL_28;
      gta2::Ped_sub_444930(v7, 4, dword_66B098);
      result = 1;
      break;
    default:
      if ( self->PowerUp[POWERUPTYPE] == POWERUP_TYPE_LIFE )
      {
LABEL_28:
        result = 0;
      }
      else
      {
        self->PowerUp[POWERUPTYPE] = POWERUP_TYPE_LIFE;
        result = 1;
      }
      break;
  }
  return result;
}


// 0x004a59a0: Player::sub_4A59A0
// IDA: Player::sub_4A59A0
// Ghidra: ---
char gta2::Player_sub_4A59A0(Player *self)
{
  POWERUP_TYPE v2; // ax
  POWERUP_TYPE v3; // ax
  POWERUP_TYPE v4; // ax
  POWERUP_TYPE v5; // ax
  POWERUP_TYPE v6; // ax
  POWERUP_TYPE v7; // ax
  POWERUP_TYPE v8; // ax

  v2 = self->PowerUp[6];
  if ( v2 )
  {
    v3 = v2 - 1;
    self->PowerUp[6] = v3;
    if ( v3 == POWERUP_TYPE_MULTIPLIER )
      gta2::Ped_sub_435F00(self->MainPed);
  }
  v4 = self->PowerUp[7];
  if ( v4 && !gSCHURULZ )
    self->PowerUp[7] = v4 - 1;
  v5 = self->PowerUp[8];
  if ( v5 )
    self->PowerUp[8] = v5 - 1;
  v6 = self->PowerUp[9];
  if ( v6 )
  {
    v7 = v6 - 1;
    self->PowerUp[9] = v7;
    if ( v7 == POWERUP_TYPE_MULTIPLIER )
      gta2::Ped_SetMoneyValue(self->MainPed);
  }
  v8 = self->PowerUp[11];
  if ( v8 )
  {
    if ( !gHUNSRUS )
    {
      self->PowerUp[11] = --v8;
      if ( v8 == POWERUP_TYPE_MULTIPLIER )
        LOBYTE(v8) = gta2::Ped_DisableInvisibility(self->MainPed);
    }
  }
  return v8;
}


// 0x004a5a50: Player::sub_4A5A50
// IDA: Player::sub_4A5A50
// Ghidra: ---
int gta2::Player_sub_4A5A50(Player *self, int a2)
{
  int v3; // esi
  POWERUP_TYPE *PowerUp; // edi
  POWERUP_TYPE *v5; // ebx
  int result; // eax
  int v7; // [esp+14h] [ebp+4h]

  v3 = 0;
  PowerUp = self->PowerUp;
  v5 = (POWERUP_TYPE *)(a2 + 26);
  v7 = 17;
  do
  {
    if ( *v5 )
    {
      *PowerUp = *v5;
      switch ( v3 )
      {
        case 6:
          gta2::Ped_sub_43B560(self->MainPed);
          break;
        case 9:
          gta2::Ped_sub_4A5060(self->MainPed);
          break;
        case 11:
          gta2::Ped_EnableInvisibility(self->MainPed);
          break;
      }
    }
    ++v3;
    ++v5;
    ++PowerUp;
    result = --v7;
  }
  while ( v7 );
  return result;
}


// 0x004a5ad0: Player::DoTeleport
// IDA: Player::DoTeleport
// Ghidra: ---
void gta2::Player_DoTeleport(Player *self)
{
  wchar_t *v2; // eax

  gta2::Ped_SetPedTeleportTarget(self->MainPed, (int *)self->Camer_X_View, (int *)self->Camer_Y_View);
  qmemcpy(&self->CameraOrPhysics1, &self->CameraOrPhysics_, 188u);
  self->field_6C = 0;
  self->MultiPlayerMode = 0;
  gta2::CameraOrPhysics_ResetAccuracy((CameraOrPhysics *)&self->CameraOrPhysics1);
  v2 = gta2::Text__Bsearch(gText, "tport");
  gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v2, 3);
}


// 0x004a5b40: Player::sub_4A5B40
// IDA: Player::sub_4A5B40
// Ghidra: ---
int gta2::Player_sub_4A5B40(Player *self, Ped *pPed_1)
{
  struct Ped *pPed; // ebx
  WeaponType Index; // edi
  CarSystemManager *v5; // eax
  Weapon **sWeapon; // ebp
  char pAmmo[2]; // [esp+12h] [ebp-2h] BYREF

  pPed = pPed_1;
  Index = Pistolet;
  LOBYTE(self->S103_2) = 0;
  self->field_640 = 0;
  BYTE1(self->S103_2) = 0;
  self->MoneyValue = 0;
  self->MainPed = pPed;
  self->Rotate = unk_66B0C4;
  v5 = (CarSystemManager *)gta2::sub_40E5A0(&unk_66B25C, (CarSystemManager *)pAmmo, &unk_66B20C);
  *((_WORD *)&self->Rotate + 1) = *(_WORD *)gta2::sub_40E5A0(v5, (CarSystemManager *)&pPed_1, &unk_66B20C);
  self->FW = unk_66B15C;
  gta2::bitShiftLeft1(&pPed_1, 0);
  self->S103_ = (S103 *)pPed_1;
  self->field_680 = 0;
  self->field_682 = 1000;
  gta2::Ped_sub_435C40(pPed, self, 0);
  self->MultiPlayerMode = 0;
  sWeapon = self->sWeapon;
  do
  {
    if ( !gGetAllWeapons || Index >= L || Index == Shoker )
      LOBYTE(pPed_1) = 0;
    else
      LOBYTE(pPed_1) = gta2::Turrel_sub_4CC990(gArsenal);
    *sWeapon++ = gta2::Turrel_sub_4CD770(gArsenal, Index++, pPed, (byte)pPed_1);
  }
  while ( Index < CAR_BOMB );
  gta2::Player_SetDefautWeapon(self);
  self->SelectWeapon = -1;
  self->Sw = -1;
  self->TypeWeapon = 27;
  return gta2::Player_SetActivePowerUps(self);
}


// 0x004a5c50: Player::FUN_004a5c50
// IDA: sub_4A5C50
// Ghidra: Player::FUN_004a5c50
byte gta2::Player_FUN_004a5c50(Player *self,Ped *pPed)
{
  undefined2 *puVar1;
  short sVar2;
  uint uVar3;
  bool bVar4;
  undefined2 *puVar5;
  short *psVar6;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined4 *puVar7;
  int iVar8;
  GameObject *pGVar9;
  uint uVar10;
  CarSystemManager *this_00;
  undefined4 uVar11;
  short *unaff_ESI;
  void *unaff_EDI;
  struct Player *local_4;
  struct Ped *pPed2;
  
  local_4 = self;
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&local_4);
  pPed2 = pPed;
  sVar2 = self->field3_0xa;
  uVar10._0_1_ = pPed->CurrentAction;
  uVar10._1_1_ = pPed->DamageState;
  uVar10._2_1_ = pPed->uns60;
  uVar10._3_1_ = pPed->uns61;
  uVar10 = uVar10 & 0xff7fffff;
  pPed->CurrentAction = (char)uVar10;
  pPed->DamageState = (char)(uVar10 >> 8);
  pPed->uns60 = (char)(uVar10 >> 0x10);
  pPed->uns61 = (char)(uVar10 >> 0x18);
  local_4._0_2_ = sVar2;
  if (self->RotateRight == true) {
    gta2::Ped_FUN_0043e1e0(pPed);
    if ((self->Tango1 != false) && (self->KEY_UP == false)) {
      local_4._0_2_ = _DAT_0066b3ec;
    }
    puVar1 = &self->Player_;
    if (*(char *)&self->field41_0x64 == '\0') {
      puVar5 = (undefined2 *)
               gta2::SpriteS1_sub_40E5D0((CarSystemManager *)puVar1,(Ped *)&pPed,(int)&local_4)
      ;
      *puVar1 = *puVar5;
      psVar6 = (short *)gta2::sub_401C80((CarSystemManager *)&DAT_0066b3c8,&pPed);
      bVar4 = gta2::CarSystemManager_less_than((CarSystemManager *)puVar1,psVar6);
      if (CONCAT31(extraout_var_00,bVar4) != 0) {
        this_00 = (CarSystemManager *)&DAT_0066b3c8;
        goto LAB_004a5d23;
      }
    }
    else {
      puVar5 = (undefined2 *)
               gta2::SpriteS1_sub_40E5D0((CarSystemManager *)puVar1,(Ped *)&pPed,0x66b20c);
      *puVar1 = *puVar5;
      psVar6 = (short *)gta2::sub_401C80((CarSystemManager *)&DAT_0066b284,&pPed);
      bVar4 = gta2::CarSystemManager_less_than((CarSystemManager *)puVar1,psVar6);
      if (CONCAT31(extraout_var,bVar4) != 0) {
        this_00 = (CarSystemManager *)&DAT_0066b284;
LAB_004a5d23:
        puVar5 = (undefined2 *)gta2::sub_401C80(this_00,&pPed);
        *puVar1 = *puVar5;
      }
    }
  }
  if (self->RotateLeft == true) {
    gta2::Ped_FUN_0043e1e0(pPed2);
    if ((self->Tango1 != false) && (self->KEY_UP == false)) {
      local_4._0_2_ = _DAT_0066b3ec;
    }
    puVar1 = &self->Player_;
    if (*(char *)&self->field41_0x64 == '\0') {
      puVar5 = (undefined2 *)
               gta2::sub_40E5A0((CarSystemManager *)puVar1,(Ped *)&pPed,
                          (short *)&local_4,unaff_EDI,unaff_ESI);
      *puVar1 = *puVar5;
      bVar4 = gta2::CarSystemManager_greater_than((CarSystemManager *)puVar1,(short *)&DAT_0066b3c8);
      if (CONCAT31(extraout_var_02,bVar4) != 0) {
        *puVar1 = _DAT_0066b3c8;
      }
    }
    else {
      puVar5 = (undefined2 *)
               gta2::sub_40E5A0((CarSystemManager *)puVar1,(Ped *)&pPed,
                          (short *)&DAT_0066b20c,unaff_EDI,unaff_ESI);
      *puVar1 = *puVar5;
      bVar4 = gta2::CarSystemManager_greater_than((CarSystemManager *)puVar1,(short *)&DAT_0066b284);
      if (CONCAT31(extraout_var_01,bVar4) != 0) {
        *puVar1 = _DAT_0066b284;
      }
    }
  }
  if ((self->RotateLeft == false) && (self->RotateRight == false)) {
    self->Player_ = _DAT_0066b0c4;
  }
  if (self->KEY_UP == true) {
    gta2::Ped_FUN_0043e1e0(pPed2);
    uVar11 = _DAT_0066b0f8;
  }
  else {
    uVar11 = _DAT_0066b15c;
    if (self->Backward == true) {
      gta2::Ped_FUN_0043e1e0(pPed2);
      puVar7 = (undefined4 *)gta2::JustCopyByPtrAtoC(&DAT_0066b0f8,&pPed);
      self->Forw = *puVar7;
      goto LAB_004a5e20;
    }
  }
  self->Forw = uVar11;
LAB_004a5e20:
  if ((((self->Jump == '\x01') && (self->field69_0x8a != '\0')) &&
      (pPed2->GameObject_ != NULL)) &&
     ((iVar8 = gta2::GameObject_GetDoorState(pPed2->GameObject_), iVar8 != 0xf &&
      (uVar3._0_1_ = pPed2->CurrentAction, uVar3._1_1_ = pPed2->DamageState,
      uVar3._2_1_ = pPed2->uns60, uVar3._3_1_ = pPed2->uns61,
      (uVar3 & 0x8000000) == 0)))) {
    gta2::Ped_sub_433C40(pPed2);
  }
  pGVar9 = pPed2->GameObject_;
  if (((pGVar9 != NULL) &&
      (pGVar9 = (GameObject *)(uint)(byte)self->keySpecial,
      self->keySpecial != 0)) &&
     ((pGVar9 = (GameObject *)(uint)(byte)self->field64_0x84,
      self->field64_0x84 != 0 &&
      (pGVar9 = (GameObject *)(uint)self->Tango1, self->Tango1 == false)))) {
    gta2::Ped_sub_433DD0(pPed2,0x14);
  }
  return (byte)pGVar9;
}


// 0x004a5e90: Player::sub_4A5E90
// IDA: Player::sub_4A5E90
// Ghidra: ---
char gta2::Player_sub_4A5E90(Player *self, char a2)
{
  char result; // al
  struct Ped *pPed; // eax
  Car *CarPlayers; // eax
  Car *v6; // edi
  struct Player *Player; // ecx
  double v8; // st7
  double pCamerX; // st7
  double pCamerXView; // st7
  double v11; // [esp+8h] [ebp-14h]
  double pCamerY; // [esp+8h] [ebp-14h]
  double pCamerYView; // [esp+8h] [ebp-14h]
  double v14; // [esp+10h] [ebp-Ch]
  double pCamerZ; // [esp+10h] [ebp-Ch]
  double pCamerZView; // [esp+10h] [ebp-Ch]

  result = a2;
  if ( !a2 )
  {
    pPed = gta2::Player_GetCurrentPed(self);
    CarPlayers = gta2::Ped_GetCarPlayers(pPed);
    v6 = CarPlayers;
    if ( CarPlayers )
    {
      Player = CarPlayers->Player_;
      if ( Player )
      {
        gta2::Player_sub_4A1DA0(Player);
        gta2::Player_sub_49F010(v6->Player_);
      }
    }
    if ( gdo_show_camera )
    {
      v14 = gta2::FloatDecoder(&self->field_130);
      v11 = gta2::FloatDecoder(&self->field_12C);
      v8 = gta2::FloatDecoder(&self->field_128);
      ShowTextDisplay(&TextWcharT, (char *)off_5743D0, v8, v11, v14);
      gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, 0, 64, unk_672F18, 1);
      pCamerZ = gta2::FloatDecoder(&self->AuxGameCameraZ);
      pCamerY = gta2::FloatDecoder(&self->AuxGameCameraY);
      pCamerX = gta2::FloatDecoder(&self->AuxGameCameraX);
      ShowTextDisplay(&TextWcharT, (char *)L"aux game camera: (%3.3f,%3.3f,%3.3f)", pCamerX, pCamerY, pCamerZ);
      gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, 0, 80, unk_672F18, 1);
      pCamerZView = gta2::FloatDecoder(&self->Camer_Z_View);
      pCamerYView = gta2::FloatDecoder(&self->Camer_Y_View);
      pCamerXView = gta2::FloatDecoder(&self->Camer_X_View);
      ShowTextDisplay(&TextWcharT, (char *)L"view camera: (%3.3f,%3.3f,%3.3f)", pCamerXView, pCamerYView, pCamerZView);
      gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, 0, 96, unk_672F18, 1);
    }
    if ( show_cycle )
      gta2::General_sub_44AA90(gGeneral);
    if ( do_show_input )
      gta2::Replay_sub_45F990(&gReplay);
    return gta2::Game_sub_45BA10(gGame);
  }
  return result;
}


// 0x004a6050: Player::sub_4A6050
// IDA: Player::sub_4A6050
// Ghidra: ---
void gta2::Player_sub_4A6050(Player *self)
{
  char *v2; // eax
  struct Ped *MainPed; // esi
  Weapon *v4; // eax
  Weapon *XCoordinate; // eax
  unsigned __int8 v6; // al
  char *v7; // eax
  unsigned __int8 v8; // [esp-Ch] [ebp-18h]
  char v9[4]; // [esp+4h] [ebp-8h] BYREF
  char v10[4]; // [esp+8h] [ebp-4h] BYREF

  if ( !gta2::Network_GetNetworkGame(&gNetwork) && !self->field_640 )
    gta2::Player_AddLives(self, -1);
  if ( gta2::PlayerStats_getMoneyValue((PlayerStats *)&self->Lives) > 0 )
  {
    if ( gta2::Network_GetNetworkGame(&gNetwork) )
    {
      v2 = gta2::MapRelatedStruct_sub_464DA0(gMapRelatedStruct, 16);
      gta2::Ped_sub_43E140(self->MainPed, (int)v2);
    }
    else
    {
      MainPed = self->MainPed;
      gta2::Ped_GetYCoordinate(MainPed, (int *)v9);
      v8 = gta2::Weapon_sub_41C1E0(v4);
      XCoordinate = (Weapon *)gta2::Ped_GetXCoordinate(MainPed, (int)v10);
      v6 = gta2::Weapon_sub_41C1E0(XCoordinate);
      v7 = gta2::MapRelatedStruct_sub_469110(gMapRelatedStruct, v6, v8, 16);
      gta2::Ped_sub_43E140(self->MainPed, (int)v7);
    }
  }
}


// 0x004a6100: Player::sub_4A6100
// IDA: Player::sub_4A6100
// Ghidra: ---
unsigned __int8 * gta2::Player_sub_4A6100(Player *self)
{
  struct Ped *CurrentPed; // edi
  int v3; // ebx
  int v4; // edi
  int *v5; // eax
  unsigned __int8 v6; // al
  unsigned __int8 v7; // al
  unsigned __int8 v8; // al
  unsigned __int8 *result; // eax
  unsigned __int8 v10; // [esp-8h] [ebp-1Ch]
  unsigned __int8 v11; // [esp-8h] [ebp-1Ch]
  unsigned __int8 v12; // [esp-8h] [ebp-1Ch]
  int Y; // [esp+Ch] [ebp-8h] BYREF
  int X; // [esp+10h] [ebp-4h] BYREF

  CurrentPed = gta2::Player_GetCurrentPed(self);
  v3 = *(_DWORD *)gta2::Ped_GetXCoordinate(CurrentPed, (int)&X);
  X = v3;
  gta2::Ped_GetYCoordinate(CurrentPed, &Y);
  Y = *v5;
  v4 = Y;
  v10 = gta2::Weapon_sub_41C1E0((Weapon *)&Y);
  v6 = gta2::Weapon_sub_41C1E0((Weapon *)&X);
  self->field_38 = (S103 *)gta2::MapRelatedStruct_sub_464FE0(gMapRelatedStruct, v6, v10, 15);
  v11 = gta2::Weapon_sub_41C1E0((Weapon *)&Y);
  v7 = gta2::Weapon_sub_41C1E0((Weapon *)&X);
  self->field_3C = (int)gta2::MapRelatedStruct_sub_464FE0(gMapRelatedStruct, v7, v11, 1);
  v12 = gta2::Weapon_sub_41C1E0((Weapon *)&Y);
  v8 = gta2::Weapon_sub_41C1E0((Weapon *)&X);
  self->S103_4 = (S103 *)gta2::MapRelatedStruct_sub_464FE0(gMapRelatedStruct, v8, v12, 5);
  result = (unsigned __int8 *)gta2::MapRelatedStruct_sub_465350(gMapRelatedStruct, v3, v4);
  self->RESPECT = (Gangs *)result;
  return result;
}


// 0x004a61f0: Player::sub_4A61F0
// IDA: Player::sub_4A61F0
// Ghidra: FUN_004a61f0
void gta2::Player_sub_4A61F0(int param_1)
{
  CameraOrPhysics *self;
  int iVar1;
  CameraOrPhysics *pCVar2;
  undefined4 *puVar3;
  
  gta2::Player_sub_4A5E90((Player *)param_1,'\x01');
  switch(*(undefined4 *)(param_1 + 0x68)) {
  case 0:
    pCVar2 = (CameraOrPhysics *)(param_1 + 0x90);
    gta2::CameraOrPhysics_sub_41E7A0(pCVar2);
    if (*(char *)(param_1 + 0x2d0) != '\0') {
      self = (CameraOrPhysics *)(param_1 + 0x208);
      break;
    }
    goto LAB_004a624a;
  case 1:
    self = (CameraOrPhysics *)(param_1 + 0x90);
    pCVar2 = self;
    break;
  case 2:
  case 3:
    gta2::CameraOrPhysics_sub_41E7A0((CameraOrPhysics *)(param_1 + 0x90));
    self = (CameraOrPhysics *)(param_1 + 0x208);
    pCVar2 = self;
    break;
  default:
    goto switchD_004a6204_caseD_4;
  }
  gta2::CameraOrPhysics_sub_41E7A0(self);
LAB_004a624a:
  if (*(int *)(param_1 + 0x6c) == 0) {
    puVar3 = (undefined4 *)(param_1 + 0x14c);
    for (iVar1 = 0x2f; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = pCVar2->m_vPosition;
      pCVar2 = (CameraOrPhysics *)&pCVar2->S132;
      puVar3 = puVar3 + 1;
    }
  }
switchD_004a6204_caseD_4:
  if (*(int *)(param_1 + 0x6c) != 1) {
    return;
  }
  pCVar2 = (CameraOrPhysics *)(param_1 + 0x14c);
  gta2::CameraOrPhysics_sub_4A5070(pCVar2);
  gta2::CameraOrPhysics_sub_41EA10((Player *)pCVar2,*(char *)(param_1 + 0x70),
             *(char *)(param_1 + 0x71),*(char *)(param_1 + 0x72),
             *(char *)(param_1 + 0x73),*(char *)(param_1 + 0x74),
             *(char *)(param_1 + 0x75));
  gta2::CameraOrPhysics_sub_41F2F0(pCVar2);
  return;
}


// 0x004a62b0: Player::sub_4A62B0
// IDA: Player::sub_4A62B0
// Ghidra: ---
char gta2::Player_sub_4A62B0(Player *self)
{
  Car *CarPlayers; // edi
  Car *CurrentCar; // eax

  CarPlayers = gta2::Ped_GetCarPlayers(self->pPassenger);
  if ( CarPlayers->Driver )
    gta2::Car_sub_4235D0(CarPlayers);
  gta2::Car_sub_475C80(CarPlayers);
  gta2::Ped_sub_4411B0(self->pPassenger);
  self->pPassenger = 0;
  gta2::Player_RestoreOnFootWeapons(self);
  CurrentCar = self->MainPed->field_10B;
  if ( CurrentCar )
    LOBYTE(CurrentCar) = gta2::Player_sub_4A5570(self, self->MainPed->field_10B);
  return (char)CurrentCar;
}


// 0x004a6310: Player::sub_4A6310
// IDA: Player::sub_4A6310
// Ghidra: ---
byte gta2::Player_sub_4A6310(Player *self)
{
  byte result; // al

  if ( !LOBYTE(self->S103_2) )
  {
    self->MultiPlayerMode = 0;
    if ( gta2::Player_sub_4A5100(self) )
      gta2::Player_SetPedOutOfCar(self);
    self->pPassenger = 0;
    self->sCar2 = 0;
    self->field_2D0 = 0;
    gta2::CameraOrPhysics_ResetAccuracy((CameraOrPhysics *)&self->CameraOrPhysics1);
  }
  return result;
}


// 0x004a6350: Player::sub_4A6350
// IDA: Player::sub_4A6350
// Ghidra: ---
char gta2::Player_sub_4A6350(Player *self, Car *pCar)
{
  struct Ped *PedInCar; // eax
  struct Ped *pPassenger; // [esp-4h] [ebp-10h]

  PedInCar = gta2::Character_CreatePedInCar(gCharacter, pCar);
  self->pPassenger = PedInCar;
  gta2::Ped_SetSearchType(PedInCar, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
  gta2::Ped_SetCurrentOccupation(self->pPassenger, EMPTY);
  gta2::Ped_sub_435C40(self->pPassenger, self, 1);
  gta2::Ped_sub_436040(self->pPassenger);
  gta2::Car_sub_427A20(pCar, self->pPassenger);
  gta2::Car_SetLocksDoor(pCar);
  pPassenger = self->pPassenger;
  self->MultiPlayerMode = 2;
  gta2::CameraOrPhysics_sub_41F410((CameraOrPhysics *)&self->CameraOrPhysics2, (S131 *)pPassenger);
  gta2::CameraOrPhysics_sub_41E410((CameraOrPhysics *)&self->CameraOrPhysics2);
  gta2::CameraOrPhysics_sub_41E010((CameraOrPhysics *)&self->CameraOrPhysics2);
  self->field_2D0 = 1;
  gta2::Player_RestoreOnFootWeapons(self);
  return gta2::Player_sub_4A5570(self, pCar);
}


// 0x004a6400: Player::sub_4A6400
// IDA: Player::sub_4A6400
// Ghidra: Player::FUN_004a6400
void gta2::Player_sub_4A6400(Player *self,Car *pCar)
{
  CameraOrPhysics **this_00;
  
  if (((self->field615_0x2d0 == false) && (self->Passenger_ == NULL)) &&
     (self->field614_0x2cc == 0)) {
    this_00 = &self->CameraOrPhysics1;
    self->field614_0x2cc = pCar;
    gta2::CameraOrPhysics_sub_41EE30((CameraOrPhysics *)this_00,pCar);
    gta2::CameraOrPhysics_sub_41E410((CameraOrPhysics *)this_00);
    gta2::CameraOrPhysics_sub_41E010((CameraOrPhysics *)this_00);
    self->ID = 3;
    self->field615_0x2d0 = true;
  }
  return;
}


// 0x004a6530: Player::sub_4A6530
// IDA: Player::sub_4A6530
// Ghidra: ---
int gta2::Player_sub_4A6530(Player *self, void *Y)
{
  struct Ped *ActivePed; // esi
  Weapon *XCoordinate; // eax
  char v5; // al
  Weapon *v6; // eax
  char v7; // al
  Weapon *PositionZ; // eax
  int result; // eax
  CameraOrPhysics *MultiPlayerMode; // esi
  char v11; // al
  char v12; // al
  SpriteS1 *v13; // eax
  char v14[4]; // [esp+8h] [ebp-4h] BYREF
  _BYTE *v15; // [esp+14h] [ebp+8h]
  _BYTE *v16; // [esp+18h] [ebp+Ch]

  ActivePed = gta2::Player_GetActivePed(self);
  if ( ActivePed )
  {
    XCoordinate = (Weapon *)gta2::Ped_GetXCoordinate(ActivePed, (int)v14);
    v5 = gta2::Weapon_sub_41C1E0(XCoordinate);
    *(_BYTE *)Y = v5;
    gta2::Ped_GetYCoordinate(ActivePed, (int *)&Y);
    v7 = gta2::Weapon_sub_41C1E0(v6);
    *v15 = v7;
    PositionZ = (Weapon *)gta2::Ped_GetPositionZ(ActivePed, (int)&Y);
    result = gta2::Weapon_sub_41C1E0(PositionZ);
  }
  else
  {
    MultiPlayerMode = gta2::Player_GetMultiPlayerMode(self);
    v11 = gta2::Weapon_sub_41C1E0((Weapon *)&MultiPlayerMode->cameraPosTarget_[3].Player);
    *(_BYTE *)Y = v11;
    v12 = gta2::Weapon_sub_41C1E0((Weapon *)&MultiPlayerMode->cameraPosTarget_[3].field_20);
    *v15 = v12;
    v13 = gta2::sub_4A5090((S202 *)MultiPlayerMode, (SpriteS1 *)&Y);
    result = gta2::Weapon_sub_41C1E0((Weapon *)v13);
  }
  *v16 = result;
  return result;
}


// 0x004a65e0: Player::GetActivePlayerCar
// IDA: Player::GetActivePlayerCar
// Ghidra: ---
Car * gta2::Player_GetActivePlayerCar(Player *self)
{
  struct Ped *ActivePed; // eax
  struct Ped *v2; // esi
  Car *result; // eax

  ActivePed = gta2::Player_GetActivePed(self);
  v2 = ActivePed;
  if ( !ActivePed )
    return 0;
  result = gta2::Ped_GetCarPlayers(ActivePed);
  if ( !result )
    return gta2::Ped_GetCar(v2);
  return result;
}


// 0x004a6610: Player::sub_4A6610
// IDA: Player::sub_4A6610
// Ghidra: ---
GameObject ** gta2::Player_sub_4A6610(Player *self, void *Y)
{
  struct Ped *pPed; // eax
  struct Ped *pPEd1; // esi
  Car *pCar; // edi
  _DWORD *v6; // eax
  int *v7; // eax
  GameObject **result; // eax
  _DWORD *PositionX; // eax
  int *v10; // eax
  CameraOrPhysics *MultiPlayerMode; // eax
  SpriteS1 *FirstElement; // edx
  char v13[4]; // [esp+8h] [ebp-4h] BYREF
  int *v14; // [esp+14h] [ebp+8h]
  GameObject **v15; // [esp+18h] [ebp+Ch]

  pPed = gta2::Player_GetActivePed(self);
  pPEd1 = pPed;
  if ( pPed )
  {
    pCar = gta2::Ped_GetCar(pPed);
    if ( pCar )
    {
      gta2::Car_GetX(pCar, (int *)v13);
      *(_DWORD *)Y = *v6;
      gta2::Car_GetY(pCar, (int *)&Y);
      *v14 = *v7;
      gta2::Car_GetZ(pCar, (int *)&Y);
    }
    else
    {
      PositionX = (_DWORD *)gta2::Ped_GetXCoordinate(pPEd1, (int)v13);
      *(_DWORD *)Y = *PositionX;
      gta2::Ped_GetYCoordinate(pPEd1, (int *)&Y);
      *v14 = *v10;
      result = (GameObject **)gta2::Ped_GetPositionZ(pPEd1, (int)&Y);
    }
    *v15 = *result;
  }
  else
  {
    MultiPlayerMode = gta2::Player_GetMultiPlayerMode(self);
    *(_DWORD *)Y = MultiPlayerMode->cameraPosTarget_[3].Player;
    *v14 = MultiPlayerMode->cameraPosTarget_[3].field_20;
    FirstElement = gta2::sub_4A5090((S202 *)MultiPlayerMode, (SpriteS1 *)&Y)->FirstElement;
    result = v15;
    *v15 = (GameObject *)FirstElement;
  }
  return result;
}


// 0x004a6900: Player::sub_4A6900
// IDA: Player::sub_4A6900
// Ghidra: ---
int gta2::Player_sub_4A6900(Player *self)
{
  int MultiPlayerMode; // eax
  struct Ped *pPassenger; // esi
  Car *CarPlayers; // edi
  int result; // eax

  MultiPlayerMode = self->MultiPlayerMode;
  if ( MultiPlayerMode )
  {
    if ( MultiPlayerMode != 2 )
      goto LABEL_12;
    pPassenger = self->pPassenger;
  }
  else
  {
    pPassenger = self->MainPed;
  }
  if ( pPassenger )
  {
    gta2::Ped_sub_403A40(pPassenger);
    CarPlayers = gta2::Ped_GetCarPlayers(pPassenger);
    if ( CarPlayers )
    {
      if ( gta2::Ped_IsTargetCarDoor(pPassenger) )
      {
        if ( gta2::Car_IsTrainOrTrainCarriage(CarPlayers) )
        {
          self->Rotate = unk_66B0C4;
          self->FW = unk_66B15C;
        }
        else if ( CarPlayers->Player_ )
        {
          gta2::Car_sub_429810(CarPlayers, 0, 0, 0, 0, 0, 0, 0, 0);
        }
      }
    }
  }
LABEL_12:
  self->Rotate = unk_66B0C4;
  result = unk_66B15C;
  self->FW = unk_66B15C;
  return result;
}


// 0x004a69a0: Player::sub_4A69A0
// IDA: Player::sub_4A69A0
// Ghidra: ---
int gta2::Player_sub_4A69A0(Player *self)
{
  self->field_2F = 1;
  return gta2::Player_sub_4A6900(self);
}


// 0x004a6a80: Player::sub_4A6A80
// IDA: Player::sub_4A6A80
// Ghidra: ---
int gta2::Player_sub_4A6A80(Player *self)
{
  int *v1; // esi
  __int16 *v2; // ebx
  int v3; // ebp
  Car *v4; // edi
  int result; // eax

  v1 = (int *)&unk_664680;
  v2 = word_664698;
  v3 = 3;
  do
  {
    if ( gta2::Car_sub_403800((Car *)(v1 - 3), (int)&unk_66B15C) && gta2::Car_sub_403800((Car *)v1, (int)&unk_66B15C) )
    {
      v4 = gta2::CarSystemManager_SpawnCar(
             gCarSystemManager,
             *(v1 - 3),
             *v1,
             v1[3],
             *v2,
             (CarModel *)(unsigned __int16)v2[12]);
      gta2::Player_sub_4A51C0(self, v4);
      gta2::sub_4A51A0(&v4->PlayerStats_, v1 + 9);
      gta2::sub_4A51B0(v4, v2[3]);
    }
    ++v1;
    ++v2;
    --v3;
  }
  while ( v3 );
  result = 0;
  memset(dword_664674, 0, 0x44u);
  return result;
}


// 0x004a6b20: Player::sub_4A6B20
// IDA: Player::sub_4A6B20
// Ghidra: ---
int gta2::Player_sub_4A6B20(Player *self, int a2)
{
  _DWORD *XCoordinate; // eax
  int v4; // edi
  _DWORD *v5; // eax
  unsigned __int8 v6; // bl
  char *v7; // ebp
  Gang *v8; // eax
  char *v9; // ebp
  Weapon **sWeapon; // ebx
  _DWORD *v11; // ecx
  int *v12; // eax
  int v13; // edx
  int v14; // ebx
  int result; // eax
  char v16[4]; // [esp+10h] [ebp-4h] BYREF

  XCoordinate = (_DWORD *)gta2::Ped_GetXCoordinate(self->MainPed, (int)v16);
  v4 = a2;
  *(_DWORD *)a2 = *XCoordinate;
  gta2::Ped_GetYCoordinate(self->MainPed, &a2);
  *(_DWORD *)(v4 + 4) = *v5;
  *(_DWORD *)(v4 + 8) = *(_DWORD *)gta2::Ped_GetPositionZ(self->MainPed, (int)&a2);
  *(_WORD *)(v4 + 12) = *gta2::Ped_GetRotation(self->MainPed, (__int16 *)&a2);
  *(_DWORD *)(v4 + 16) = gta2::Player_GetMoneyPlayer(self);
  *(_DWORD *)(v4 + 20) = gta2::Player_GetMultiPlayer(self);
  *(_WORD *)(v4 + 24) = gta2::Ped_GetHealth(self->MainPed);
  *(_BYTE *)(v4 + 127) = gta2::Ped_GetRemap(self->MainPed);
  *(_BYTE *)(v4 + 128) = (unsigned __int8)gta2::Player_getMoney(self);
  *(_WORD *)(v4 + 130) = self->SelectWeapon;
  v6 = 0;
  *(_WORD *)(v4 + 140) = gta2::Ped_GetPoliceStar(self->MainPed);
  LOBYTE(a2) = 0;
  v7 = (char *)(v4 + 117);
  do
  {
    v8 = gta2::Gangs_SelectGang(gGangs, (GANG)a2);
    *v7 = gta2::Gang_GetRespectForPlayer(v8, self->Ids);
    ++v6;
    ++v7;
    LOBYTE(a2) = v6;
  }
  while ( v6 < 0xAu );
  v9 = (char *)(v4 + 102);
  sWeapon = self->sWeapon;
  a2 = 15;
  do
  {
    *v9++ = gta2::Weapon_GetDisplayAmmo(*sWeapon++);
    --a2;
  }
  while ( a2 );
  v11 = (_DWORD *)(v4 + 60);
  v12 = &self->field_644;
  v13 = 10;
  do
  {
    v14 = *v12++;
    *v11++ = v14;
    --v13;
  }
  while ( v13 );
  *(_DWORD *)(v4 + 132) = self->field_678;
  result = self->field_67C;
  *(_DWORD *)(v4 + 136) = result;
  return result;
}


// 0x004a6c80: Player::sub_4A6C80
// IDA: Player::sub_4A6C80
// Ghidra: ---
int gta2::Player_sub_4A6C80(Player *self, int a2)
{
  GANG v4; // bl
  char *v5; // ebp
  Gang *v6; // eax
  byte *v7; // ebp
  Weapon **sWeapon; // ebx
  int *v9; // ecx
  int *v10; // eax
  int v11; // edx
  int v12; // ebx
  GANG a2a; // [esp+14h] [ebp+4h]
  int a2b; // [esp+14h] [ebp+4h]

  gta2::PlayerStats_SetMonyeLives((PlayerStats *)&self->Lives, *(unsigned __int8 *)(a2 + 128));
  gta2::PlayerStats_SetMonyeLives((PlayerStats *)&self->MultiPlayer, *(_DWORD *)(a2 + 20));
  gta2::PlayerStats_GivenMoney((PlayerStats *)&self->Money, *(_DWORD *)(a2 + 16));
  self->SelectWeapon = *(_WORD *)(a2 + 130);
  gta2::Ped_SetHealth(self->MainPed, *(_WORD *)(a2 + 24));
  gta2::Ped_SetPoliceNoStar(self->MainPed);
  gta2::Ped_UpdateWantedLevel(self->MainPed, *(_WORD *)(a2 + 140));
  v4 = Yakuza;
  v5 = (char *)(a2 + 117);
  a2a = Yakuza;
  do
  {
    v6 = gta2::Gangs_SelectGang(gGangs, a2a);
    gta2::Gang_SetRespectForPlayer(v6, self->Ids, *v5);
    ++v4;
    ++v5;
    a2a = v4;
  }
  while ( v4 < GANG_10 );
  v7 = (byte *)(a2 + 102);
  sWeapon = self->sWeapon;
  a2b = 15;
  do
  {
    gta2::Weapon_SetAmmo(*sWeapon++, *v7++);
    --a2b;
  }
  while ( a2b );
  v9 = &self->field_644;
  v10 = (int *)(a2 + 60);
  v11 = 10;
  do
  {
    v12 = *v10++;
    *v9++ = v12;
    --v11;
  }
  while ( v11 );
  self->field_678 = *(_DWORD *)(a2 + 132);
  self->field_67C = *(_DWORD *)(a2 + 136);
  gta2::Player_sub_4A5A50(self, a2);
  return gta2::Player_sub_4A6A80(self);
}


// 0x004a6da0: Player::StartGames
// IDA: Player::StartGames
// Ghidra: ---
char gta2::Player_StartGames(Player *self)
{
  Gang *i; // eax
  Gang *pGang; // eax

  if ( gDANISGOD )
    gta2::PlayerStats_GivenMoney((PlayerStats *)&self->Money, 200000);
  if ( gIAMDAVEJ )
    gta2::PlayerStats_GivenMoney((PlayerStats *)&self->Money, 9999999);
  if ( gVOLTFEST )
    gta2::Weapon_GiveWeaponInfiniti(self->sWeapon[ElectorGun]);
  if ( FLAMEON )
    gta2::Weapon_GiveWeaponInfiniti(self->sWeapon[FireGun]);
  if ( gMADEMAN )
  {
    for ( i = gta2::Gangs_GetFirstUsedGang(gGangs); i; i = gta2::Gangs_GetNextUsedGang(gGangs) )
      gta2::Gang_SetRespectForPlayer(i, self->Ids, 100);
  }
  if ( gHeats99 )
    gta2::PlayerStats_SetMonyeLives((PlayerStats *)&self->Lives, 99);
  if ( gSEGARULZ )
    gta2::PlayerStats_SetMultiPlayer((PlayerStats *)&self->MultiPlayer, 9);
  if ( gBunt )
    gCharacter->Bunt = 1;
  if ( gFYOHZZ0 )
    gta2::Player_GivePowerUp(self, POWERUP_TYPE_GET_OUTTA_JAIL_FREE_CARD);
  if ( gHUNSRUS )
    gta2::Player_GivePowerUp(self, POWERUP_TYPE_INVISIBILITY);
  if ( gSCHURULZ )
    gta2::Player_GivePowerUp(self, POWERUP_TYPE_DOUBLE_DAMAGE);
  LOBYTE(pGang) = unk_5EADA2;
  if ( unk_5EADA2 )
  {
    gta2::Player_GivePowerUp(self, POWERUP_TYPE_GET_OUTTA_JAIL_FREE_CARD);
    gta2::Player_sub_4A5400(self, SMG, 0x32u);
    for ( pGang = gta2::Gangs_GetFirstUsedGang(gGangs); pGang; pGang = gta2::Gangs_GetNextUsedGang(gGangs) )
      gta2::Gang_SetRespectForPlayer(pGang, self->Ids, 80);
  }
  return (char)pGang;
}


// 0x004a6ef0: Player::sub_4A6EF0
// IDA: Player::sub_4A6EF0
// Ghidra: ---
void gta2::Player_sub_4A6EF0(Player *self)
{
  int *v2; // ecx

  v2 = &self->field_54;
  self->MainPed = 0;
  self->pPassenger = 0;
  self->sCar2 = 0;
  self->RESPECT = 0;
  self->field_38 = 0;
  self->field_3C = 0;
  *v2 = 0;
  v2[1] = 0;
  v2[2] = 0;
  if ( self->Sound )
  {
    gta2::DMAudio_DMAudio_des(&gDMAudio, (cameraPosTarget *)self->Sound);
    self->Sound = 0;
  }
  nullsub_12();
  gta2::PlayerStats_sub_4A4F10((PlayerStats *)&self->Money);
  gta2::CameraOrPhysics_nullsub_6();
  gta2::CameraOrPhysics_nullsub_6();
  gta2::CameraOrPhysics_nullsub_6();
}


// 0x004a6fd0: Player::sub_4A6FD0
// IDA: Player::sub_4A6FD0
// Ghidra: ---
char gta2::Player_sub_4A6FD0(Player *self)
{
  Car *v2; // eax
  Car *v3; // edi

  v2 = gta2::CarSystemManager_sub_426AA0(gCarSystemManager, self->Camer_X_View, self->Camer_Y_View, self->Camer_Z_View, 0);
  v3 = v2;
  if ( v2 )
  {
    gta2::Player_sub_4A6310(self);
    LOBYTE(v2) = gta2::Player_sub_4A6400(self, v3);
  }
  return (char)v2;
}


// 0x004a7010: Player::sub_4A7010
// IDA: Player::sub_4A7010
// Ghidra: ---
void gta2::Player_sub_4A7010(Player *self, const CHAR *pKey)
{
  unsigned __int8 v3; // al
  BYTE CDVol; // al
  struct Ped *pMainPed; // ecx
  struct Ped *MainPed; // ecx
  struct Player *Player; // ecx
  Car *ActivePlayerCar; // eax
  Car *v9; // eax
  void *v10; // [esp+0h] [ebp-Ch]
  char pKeya; // [esp+10h] [ebp+4h]

  if ( !gta2::Hud_Update2_Wrapper(gHud, (unsigned __int16)pKey, self) )
  {
    switch ( (__int16)pKey )
    {
      case 1:
        if ( skip_quit_confirm )
        {
          if ( gta2::Player_GetCurrentPlayer(self) )
            gta2::Game_SetState(gGame, 1, 2);
        }
        else
        {
          gta2::Player_sub_4C5F60(self);
        }
        return;
      case 2:
        if ( do_debug_keys )
          gta2::Player_sub_4A4940(self, 0);
        return;
      case 3:
        if ( do_debug_keys )
          gta2::Player_sub_4A4940(self, 1u);
        return;
      case 4:
        if ( do_debug_keys )
          gta2::Player_sub_4A4940(self, 2u);
        return;
      case 5:
        if ( do_debug_keys )
          gta2::Player_sub_4A49B0(self);
        return;
      case 6:
        if ( do_debug_keys )
        {
          MainPed = self->MainPed;
          if ( MainPed )
            gta2::Ped_SetPoliceNoStar(MainPed);
        }
        return;
      case 7:
      case 8:
      case 9:
      case 10:
      case 11:
        if ( gdo_test )
          gta2::sub_4C1F80(unk_670C7C, (ushort)pKey);
        if ( do_brian_test )
        {
          gta2::sub_41D0B0(unk_5E32B0, pKey);
        }
        else if ( do_iain_test )
        {
          gta2::Character_HandlePlayerInvisibilityCommand(gCharacter, (__int16)pKey);
        }
        return;
      case 46:
        if ( do_debug_keys && gta2::Player_GetCurrentPlayer(self) )
          gta2::sub_4A4760(&gHud->s);
        return;
      case 59:
        pKeya = 0;
        goto LABEL_83;
      case 60:
        pKeya = 1;
LABEL_83:
        if ( !unk_66BEED )
        {
          unk_66BEED = 10;
          if ( gGame )
          {
            Player = gGame->PlayerMain;
            if ( Player )
            {
              if ( gta2::Player_GetActivePlayerCar(Player) )
              {
                ActivePlayerCar = gta2::Player_GetActivePlayerCar(gGame->PlayerMain);
                if ( !gta2::AudioManager_IsSpecialCarModel(&unk_5DCBC8, ActivePlayerCar) )
                {
                  v9 = gta2::Player_GetActivePlayerCar(gGame->PlayerMain);
                  if ( !gta2::AudioManager_IsTransportOrCargo(&unk_5DCBC8, v9) )
                    LOBYTE(unk_5DCBC8.AudioBuffer[2].isActive) = (pKeya == 0) + 1;
                }
              }
            }
          }
        }
        return;
      case 61:
        if ( gta2::DMAudio_GetCDVol(&gDMAudio) - 10 <= 0 )
          v3 = 0;
        else
          v3 = gta2::DMAudio_GetCDVol(&gDMAudio) - 10;
        goto LABEL_18;
      case 62:
        if ( gta2::DMAudio_GetCDVol(&gDMAudio) + 10 >= 127 )
          v3 = 127;
        else
          v3 = gta2::DMAudio_GetCDVol(&gDMAudio) + 10;
LABEL_18:
        gta2::DMAudio_SetCDVol(&gDMAudio, v3);
        CDVol = gta2::DMAudio_GetCDVol(&gDMAudio);
        gta2::Registry_sub_4B5110((HKEY)&Registry, "CDVol", CDVol);
        break;
      case 64:
        Game::45BAA0(gGame);
        break;
      case 65:
        if ( gta2::Player_GetCurrentPlayer(self) )
          gta2::HudBrief_CheckQueue(&gHud->HudBrief_);
        break;
      case 66:
        if ( gta2::Player_GetCurrentPlayer(self) && !gNetworkGame )
          gta2::Start_GTAManager();
        break;
      case 67:
        if ( gta2::Player_GetCurrentPlayer(self) )
          gta2::S86_8_sub_4A4770(&gHud->S86_8_);
        break;
      case 68:
        if ( gNetworkGame )
          gta2::Player_OpenChat(self, v10);
        break;
      case 71:
        if ( do_debug_keys )
        {
          self->field_6C = 1;
          self->prevWeapon = 1;
        }
        break;
      case 72:
        if ( do_debug_keys )
        {
          self->field_6C = 1;
          self->Up = 1;
        }
        break;
      case 73:
        if ( do_debug_keys )
        {
          self->field_6C = 1;
          self->nextWeapon = 1;
        }
        break;
      case 74:
        if ( do_debug_keys )
          gta2::Game_sub_4A4750(gGame);
        break;
      case 75:
        if ( do_debug_keys )
        {
          self->field_6C = 1;
          self->Left = 1;
        }
        break;
      case 76:
        if ( do_debug_keys )
          self->field_6C = 0;
        break;
      case 77:
        if ( do_debug_keys )
        {
          self->field_6C = 1;
          self->Right = 1;
        }
        break;
      case 78:
        if ( do_debug_keys )
          gta2::Game_sub_45A6F0(gGame);
        break;
      case 79:
        if ( do_debug_keys )
          LOBYTE(self->Tango1) = LOBYTE(self->Tango1) == 0;
        break;
      case 80:
        if ( do_debug_keys )
        {
          self->field_6C = 1;
          self->Down = 1;
        }
        break;
      case 82:
        if ( do_debug_keys )
          gta2::Player_DoTeleport(self);
        break;
      case 83:
        if ( do_debug_keys )
        {
          pMainPed = self->MainPed;
          if ( pMainPed )
            gta2::Ped_sub_435F40(pMainPed);
        }
        break;
      case 87:
        if ( do_debug_keys )
        {
          self->MultiPlayerMode = 0;
          gta2::CameraOrPhysics_ResetAccuracy((CameraOrPhysics *)&self->CameraOrPhysics1);
        }
        break;
      case 88:
        if ( do_debug_keys )
        {
          self->MultiPlayerMode = 1;
          gta2::CameraOrPhysics_sub_4A5070((CameraOrPhysics *)&self->CameraOrPhysics1);
        }
        break;
      case 181:
        if ( do_debug_keys )
          gta2::Player_sub_4A6FD0(self);
        break;
      case 199:
        if ( do_debug_keys )
        {
          gta2::CameraOrPhysics_sub_41DFB0((CameraOrPhysics *)&self->CameraOrPhysics1);
          gta2::CameraOrPhysics_sub_41DFB0((CameraOrPhysics *)&self->CameraOrPhysics2);
        }
        break;
      case 201:
        if ( do_debug_keys )
          self->debugKey2 = 1;
        break;
      case 209:
        if ( do_debug_keys )
          self->debugKey1 = 1;
        break;
      default:
        return;
    }
  }
}


// 0x004a7680: Player::sub_4A7680
// IDA: Player::sub_4A7680
// Ghidra: ---
void gta2::Player_sub_4A7680(Player *self)
{
  struct Player *Player; // ecx
  const CHAR *v3; // [esp-4h] [ebp-8h]

  gta2::Player_sub_4A4AE0((int)self);
  Player = self->Player_;
  if ( Player )
  {
    if ( (((unsigned int)Player >> 12) & 0x1FF) != 0 )
    {
      v3 = (const CHAR *)(((unsigned int)Player >> 12) & 0x1FF);
      if ( ((unsigned int)Player & 0x200000) != 0 )
      {
        gta2::Player_sub_4A7010(self, v3);
        self->Player_ = 0;
        return;
      }
      gta2::Player_sub_4A49C0(self, (__int16)v3);
    }
    self->Player_ = 0;
  }
}


// 0x004a76d0: Player::sub_4A76D0
// IDA: Player::sub_4A76D0
// Ghidra: Player::FUN_004a76d0
byte gta2::Player_sub_4A76D0(Player *self,Ped *pPed)
{
  GameObject *pGVar1;
  undefined4 uVar2;
  byte bVar3;
  bool bVar4;
  char cVar5;
  Car *pCar;
  int iVar6;
  Car *pCar1;
  
  pCar = (Car *)gta2::Ped_GetCarPlayers(pPed);
  pCar1 = pCar;
  if ((pPed == NULL) ||
     (pCar1 = (Car *)gta2::Ped_GetPedState(pPed), pCar1 == (Car *)0x9))
  goto LAB_004a7906;
  if ((self->Enter == false) || (self->field68_0x89 == '\0')) {
    iVar6 = gta2::Ped_GetState(pPed);
    if ((iVar6 == 0x23) || (iVar6 = gta2::Ped_GetState(pPed), iVar6 == 0x25)) {
      iVar6 = gta2::Ped_GetPedState(pPed);
      if (iVar6 == 10) {
        cVar5 = gta2::Ped_GetDamageState(pPed);
        if (cVar5 != '\0') {
          gta2::Ped_PedSetObjective(pPed,0,9999);
          gta2::Ped_SetAnimationState(pPed,0,9999);
          gta2::Ped_UpdatePedState(pPed,PEDSTATE_IN_CAR);
          gta2::Ped_sub_4332B0(pPed,10);
        }
      }
      else {
        cVar5 = gta2::Ped_GetDamageState(pPed);
        if ((cVar5 == '\x02') || (iVar6 = gta2::Ped_GetVehicle(pPed), iVar6 == 0)) {
          gta2::Ped_PedSetObjective(pPed,0,9999);
          gta2::Ped_SetAnimationState(pPed,0,9999);
          gta2::GameObject_sub_4A5030(pPed);
        }
      }
    }
  }
  else {
    bVar3 = gta2::Ped_IsInCar(pPed);
    if (bVar3 == 0) {
      iVar6 = gta2::Ped_GetState(pPed);
      if ((iVar6 != 0x24) &&
         (pGVar1 = pPed->GameObject_, uVar2._0_1_ = pGVar1->AIState,
         uVar2._1_1_ = pGVar1->AISubState, uVar2._2_1_ = pGVar1->AITarget,
         uVar2._3_1_ = pGVar1->AITimer,
         pCar1 = (Car *)gta2::CarSystemManager_sub_424E70(gCarSystemManager,uVar2,3), pCar1 != NULL)) {
        gta2::Ped_SetAnimationState(pPed,0,9999);
        bVar4 = gta2::Car_IsTrainOrTrainCarriage(pCar1);
        if (bVar4) {
          iVar6 = 0x25;
        }
        else {
          iVar6 = 0x23;
        }
        gta2::Ped_PedSetObjective(pPed,iVar6,9999);
        gta2::Ped_SetCurrentCar(pPed,pCar1);
        gta2::Ped_SetTargetCarDoor(pPed,0);
        gta2::Ped_SetAnimationState(pPed,0);
      }
    }
    else {
      bVar3 = gta2::Car_sub_4222A0(pCar);
      if (bVar3 != 0) {
        gta2::Ped_SetAnimationState(pPed,0,9999);
        if (pPed->CurrentCar->CarType == TRAIN) {
          iVar6 = 0x26;
        }
        else {
          iVar6 = 0x24;
        }
        gta2::Ped_PedSetObjective(pPed,iVar6,9999);
        gta2::Ped_SetCurrentCar(pPed,pPed->CurrentCar);
      }
    }
  }
  if ((self->Tango1 == true) && (self->MultiPlayerMode == 0)) {
    if ((self->field72_0x8d == '\0') && (self->SelectWeapon != -1)) {
      bVar3 = gta2::Weapon_FUN_004cc910(self->sWeapon[self->SelectWeapon]);
      if (bVar3 == 0) goto LAB_004a78d1;
      gta2::Ped_sub_4A5010(pPed);
    }
    else {
      gta2::Ped_sub_4A5010(pPed);
    }
  }
  else {
LAB_004a78d1:
    gta2::Ped_sub_403A40(pPed);
  }
  if (pCar != NULL) {
    bVar4 = gta2::Ped_IsTargetCarDoor(pPed);
    pCar1 = (Car *)(uint)bVar4;
    if (!bVar4) goto LAB_004a7906;
    bVar4 = gta2::Car_IsTrainOrTrainCarriage(pCar);
    if (!bVar4) {
      bVar3 = gta2::Player_sub_4A4C40(self,pCar);
      return bVar3;
    }
  }
  bVar3 = gta2::Player_FUN_004a5c50(self,pPed);
  pCar1 = (Car *)(uint)bVar3;
LAB_004a7906:
  return (byte)pCar1;
}


// 0x004a7910: Player::HandleDeath
// IDA: Player::HandleDeath
// Ghidra: ---
void gta2::Player_HandleDeath(Player *self)
{
  struct Ped *Ped; // eax
  struct Ped *v3; // esi
  struct Player *isPlayer; // eax
  char Id; // al
  struct Player *PlayerSlotByIndex; // eax
  struct Ped *MainPed; // ecx
  wchar_t *v8; // eax
  const char *DeathDescription; // eax
  wchar_t *v10; // eax
  struct Ped *v11; // eax
  struct Ped *pPassenger; // ecx
  __int16 MoneyValue; // ax
  struct Ped *v14; // ecx
  struct Player *v15; // [esp-4h] [ebp-10h]

  if ( gNetworkGame )
  {
    if ( !self->MainPed->PedId
      || (Ped = gta2::Character_FindPed(gCharacter, (Ped *)self->MainPed->PedId), (v3 = Ped) == 0)
      || !gta2::Ped_IsSearchType(Ped, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY)
      || (isPlayer = v3->isPlayer) == 0 )
    {
      isPlayer = 0;
    }
    v15 = isPlayer;
    Id = gta2::Player_GetId(self);
    PlayerSlotByIndex = gta2::Game_GetPlayerSlotByIndex(gGame, Id);
    gta2::Network_SetSpectateTarget(&gNetwork, PlayerSlotByIndex, v15);
  }
  MainPed = self->MainPed;
  BYTE1(self->S103_2) = 0;
  gta2::Ped_sub_403A40(MainPed);
  if ( LOBYTE(self->S103_2) )
  {
    pPassenger = self->pPassenger;
    if ( pPassenger )
      gta2::Ped_sub_403A40(pPassenger);
    MoneyValue = self->MoneyValue;
    if ( MoneyValue )
    {
      self->MoneyValue = MoneyValue - 1;
    }
    else if ( gta2::PlayerStats_getMoneyValue((PlayerStats *)&self->Lives) > 0 || gNetworkGame )
    {
      gta2::Player_ProcessWeaponChange(self);
      if ( !gKeep_weapons_after_death )
      {
        gta2::Player_RestoreOnFootWeapons(self);
        gta2::Player_sub_4A5690(self);
        gta2::Player_sub_4A5710(self);
      }
      self->MultiPlayerMode = 0;
      gta2::CameraOrPhysics_sub_41E010((CameraOrPhysics *)&self->CameraOrPhysics1);
      gta2::CameraOrPhysics_ResetAccuracy((CameraOrPhysics *)&self->CameraOrPhysics1);
      v14 = self->pPassenger;
      if ( v14 )
      {
        gta2::Ped_sub_43E650(v14);
        self->pPassenger = 0;
        self->field_2D0 = 0;
      }
      gta2::Ped_sub_435FA0(self->MainPed);
      LOBYTE(self->S103_2) = 0;
    }
    else
    {
      gta2::Game_SetState(gGame, 0, 3);
    }
  }
  else
  {
    if ( gta2::Player_GetCurrentPlayer(self) )
    {
      if ( gta2::PlayerStats_getMoneyValue((PlayerStats *)&self->Lives) > 1 || gNetworkGame )
      {
        DeathDescription = gta2::Player_GetDeathDescription(self);
        v10 = gta2::Text__Bsearch(gText, DeathDescription);
        gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v10, 1);
        gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_WASTED);
      }
      else
      {
        v8 = gta2::Text__Bsearch(gText, "g_over");
        gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v8, 3);
        gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_GAME_OVER);
      }
    }
    gta2::Player_SetPlayerState(self, 0);
    if ( self->field_2D0 )
      gta2::Player_sub_4A6310(self);
    LOBYTE(self->S103_2) = 1;
    self->MoneyValue = 70;
    if ( gta2::PlayerStats_getMoneyValue((PlayerStats *)&self->Lives) > 1 )
    {
      v11 = gta2::Character_sub_43DFB0(gCharacter, self->MainPed);
      self->pPassenger = v11;
      v11->WeaponSelect = 0;
      self->pPassenger->Gang1 = 0;
      gta2::Ped_sub_403A40(self->pPassenger);
      HIBYTE(self->pPassenger->ID) = 0;
      self->MultiPlayerMode = 2;
      qmemcpy(&self->CameraOrPhysics2, &self->CameraOrPhysics1, 0xBCu);
      self->field_2D0 = 1;
    }
    gta2::Player_sub_4A6050(self);
  }
}


// 0x004a7b70: Player::sub_4A7B70
// IDA: Player::sub_4A7B70
// Ghidra: ---
void gta2::Player_sub_4A7B70(Player *self)
{
  if ( BYTE1(self->S103_2) )
  {
    if ( !--self->MoneyValue )
    {
      BYTE1(self->S103_2) = 0;
      gta2::Player_sub_4A6310(self);
    }
  }
  else
  {
    BYTE1(self->S103_2) = 1;
    self->MoneyValue = 70;
  }
}


// 0x004a7ba0: Player::sub_4A7BA0
// IDA: Player::sub_4A7BA0
// Ghidra: ---
char gta2::Player_sub_4A7BA0(Player *self)
{
  struct Ped *MainPed; // ecx
  const char *DeathDescription; // eax
  wchar_t *v4; // eax
  char v5; // al
  S169 *pPassenger; // ecx
  struct Ped *v7; // eax
  struct Ped *pMainPed; // ebp
  int MoneyValue; // eax
  struct Ped *v10; // ecx
  int v11; // eax

  MainPed = self->MainPed;
  BYTE1(self->S103_2) = 0;
  gta2::Ped_sub_403A40(MainPed);
  if ( LOBYTE(self->S103_2) )
  {
    v10 = self->pPassenger;
    --self->MoneyValue;
    gta2::Ped_sub_403A40(v10);
    LOWORD(MoneyValue) = self->MoneyValue;
    if ( (_WORD)MoneyValue )
    {
      if ( (_WORD)MoneyValue == 2 )
      {
        MoneyValue = gta2::PlayerStats_getMoneyValue((PlayerStats *)&self->Lives);
        if ( MoneyValue > 0 )
        {
          LOBYTE(MoneyValue) = gta2::MapGm_GetGang(&gMapGm);
          if ( (_BYTE)MoneyValue != 1 )
          {
            LOWORD(self->MainPed->XCoordinate) = 0;
            self->MainPed->PoliceStar1 = 0;
            gta2::Ped_PedSetObjective(self->MainPed, 54, 60);
            LOBYTE(MoneyValue) = gta2::Ped_SetCurrentCar(self->MainPed, 0);
          }
        }
      }
    }
    else if ( gta2::PlayerStats_getMoneyValue((PlayerStats *)&self->Lives) <= 0 || gta2::MapGm_GetGang(&gMapGm) == 1 )
    {
      LOBYTE(MoneyValue) = gta2::Game_SetState(gGame, 0, 3);
    }
    else
    {
      gta2::GUI_SetInteface((GUI *)&gHud->HudMessage_);
      gta2::Player_ProcessWeaponChange(self);
      if ( gta2::Player_GetPowerUp(self, 4) )
      {
        if ( !gFYOHZZ0 )
          gta2::Player_DecrPowerUp(self, 4);
      }
      else
      {
        if ( !gKeep_weapons_after_death )
        {
          gta2::Player_RestoreOnFootWeapons(self);
          gta2::Player_sub_4A5690(self);
          gta2::Player_sub_4A5710(self);
        }
        v11 = gta2::PlayerStats_getMoneyValue((PlayerStats *)&self->MultiPlayer) / 2;
        if ( !v11 )
          v11 = 1;
        gta2::PlayerStats_SetMonyeLives((PlayerStats *)&self->MultiPlayer, v11);
      }
      self->MultiPlayerMode = 0;
      gta2::CameraOrPhysics_sub_41E010((CameraOrPhysics *)&self->CameraOrPhysics1);
      gta2::CameraOrPhysics_ResetAccuracy((CameraOrPhysics *)&self->CameraOrPhysics1);
      LOWORD(self->pPassenger->XCoordinate) = 0;
      LOWORD(self->pPassenger->XCoordinate) = 0;
      self->pPassenger->PoliceStar1 = 0;
      LOBYTE(MoneyValue) = gta2::Ped_sub_43E650(self->pPassenger);
      self->pPassenger = 0;
      self->field_2D0 = 0;
      self->field_640 = 0;
      LOBYTE(self->S103_2) = 0;
    }
  }
  else
  {
    gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_BUSTED);
    gta2::Player_SetPlayerState(self, 3);
    if ( gta2::Player_GetCurrentPlayer(self) )
    {
      DeathDescription = gta2::Player_GetDeathDescription(self);
      v4 = gta2::Text__Bsearch(gText, DeathDescription);
      gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v4, 1);
    }
    gta2::Player_SetPlayerState(self, 0);
    v5 = self->field_2D0;
    LOBYTE(self->S103_2) = 1;
    self->MoneyValue = 70;
    if ( v5 )
      gta2::Player_sub_4A6310(self);
    pPassenger = *(S169 **)&self->MainPed->field_103;
    if ( pPassenger )
      gta2::S169_ManageGroupPedObjectives(pPassenger);
    v7 = gta2::Character_sub_43DFB0(gCharacter, self->MainPed);
    self->pPassenger = v7;
    v7->WeaponSelect = 0;
    self->pPassenger->Gang1 = 0;
    gta2::Ped_sub_403A40(self->pPassenger);
    HIBYTE(self->pPassenger->ID) = 0;
    gta2::Police_sub_4A9670(gPolice, self->MainPed, self->pPassenger);
    self->MultiPlayerMode = 2;
    qmemcpy(&self->CameraOrPhysics2, &self->CameraOrPhysics1, 0xBCu);
    self->field_2D0 = 1;
    gta2::Player_sub_4A6050(self);
    LOWORD(self->MainPed->XCoordinate) = 0;
    self->MainPed->PoliceStar1 = 0;
    pMainPed = self->MainPed;
    MoneyValue = pMainPed->PositionX1;
    LOBYTE(MoneyValue) = MoneyValue & 0xDF;
    pMainPed->PositionX1 = MoneyValue;
  }
  return MoneyValue;
}


// 0x004a7e80: Player::sub_4A7E80
// IDA: Player::sub_4A7E80
// Ghidra: ---
__int16 gta2::Player_sub_4A7E80(Player *self)
{
  unsigned int Health; // eax
  PlayerStats **p_Money; // ecx
  PlayerStats *v3; // eax
  PlayerStats *v4; // eax
  void *v5; // edi
  unsigned __int16 v7; // ax
  char v8; // cl
  char v9; // al
  CameraOrPhysics **p_CameraOrPhysics1; // esi
  CameraOrPhysics **p_CameraOrPhysics2; // ecx
  struct Ped *MainPed; // ecx
  bool v13; // zf
  char v14; // al
  struct Ped *pPassenger; // ecx
  bool Enter; // [esp+8h] [ebp-4h]
  char v18; // [esp+9h] [ebp-3h]
  bool keySpecial; // [esp+Ah] [ebp-2h]
  char v20; // [esp+Bh] [ebp-1h]

  Enter = self->Enter;
  v18 = BYTE1(self->field_88);
  v20 = self->field_84;
  v7 = self->field_680;
  keySpecial = self->keySpecial;
  if ( v7 < 100u )
    self->field_680 = v7 + 1;
  gta2::Player_sub_4A59A0(self);
  gta2::Player_sub_4A5E90(self, 0);
  if ( LOBYTE(self->S103_5) )
  {
    self->Enter = 0;
    BYTE1(self->field_88) = 0;
  }
  gta2::PlayerStats_sub_4B7770((PlayerStats *)&self->Money);
  sub_44A1E0(&self->field_644);
  v8 = LOBYTE(self->field_88) && self->NextWeaponZ;
  v9 = HIBYTE(self->field_84) && self->PrevWeaponX;
  gta2::Player_sub_4A5460(self, v9, v8);
  if ( self->field_8F )
  {
    if ( self->Attack )
      self->Attack = 0;
    else
      self->field_8F = 0;
  }
  if ( do_debug_keys )
    gta2::Player_sub_4A4CB0(self);
  switch ( self->MultiPlayerMode )
  {
    case 0:
      p_CameraOrPhysics1 = &self->CameraOrPhysics1;
      gta2::Player_sub_4A4CF0(self, (SpriteS1 *)&self->CameraOrPhysics1, v5);
      if ( !self->field_2F )
        gta2::Player_sub_4A76D0(self, self->MainPed);
      gta2::CameraOrPhysics_sub_41F410((CameraOrPhysics *)&self->CameraOrPhysics1, (S131 *)self->MainPed);
      gta2::CameraOrPhysics_sub_41F2F0((CameraOrPhysics *)&self->CameraOrPhysics1);
      if ( !self->field_2D0 )
        goto LABEL_41;
      if ( self->pPassenger )
      {
        gta2::CameraOrPhysics_sub_41F410((CameraOrPhysics *)&self->CameraOrPhysics2, (S131 *)self->pPassenger);
        p_CameraOrPhysics2 = &self->CameraOrPhysics2;
      }
      else
      {
        if ( self->sCar2 )
          gta2::CameraOrPhysics_sub_41EE30((CameraOrPhysics *)&self->CameraOrPhysics2, self->sCar2);
        p_CameraOrPhysics2 = &self->CameraOrPhysics2;
      }
      goto LABEL_40;
    case 1:
      p_CameraOrPhysics1 = &self->CameraOrPhysics1;
      gta2::CameraOrPhysics_sub_41EA10(
        (CameraOrPhysics *)&self->CameraOrPhysics1,
        self->Forward,
        self->Backward,
        self->RotateLeft,
        self->RotateRight,
        self->NextWeaponZ,
        self->PrevWeaponX);
      goto LABEL_39;
    case 2:
      p_CameraOrPhysics1 = &self->CameraOrPhysics2;
      self->Enter = 0;
      BYTE1(self->field_88) = 0;
      gta2::Player_sub_4A4CF0(self, (SpriteS1 *)&self->CameraOrPhysics2, v5);
      if ( self->pPassenger )
      {
        if ( !self->field_2F )
          gta2::Player_sub_4A76D0(self, self->pPassenger);
        gta2::CameraOrPhysics_sub_41F410((CameraOrPhysics *)&self->CameraOrPhysics2, (S131 *)self->pPassenger);
      }
      gta2::CameraOrPhysics_sub_41F410((CameraOrPhysics *)&self->CameraOrPhysics1, (S131 *)self->MainPed);
      gta2::CameraOrPhysics_sub_41F2F0((CameraOrPhysics *)&self->CameraOrPhysics1);
      goto LABEL_39;
    case 3:
      gta2::CameraOrPhysics_sub_41F410((CameraOrPhysics *)&self->CameraOrPhysics1, (S131 *)self->MainPed);
      if ( self->pPassenger )
      {
        gta2::CameraOrPhysics_sub_41F410((CameraOrPhysics *)&self->CameraOrPhysics2, (S131 *)self->pPassenger);
      }
      else if ( self->sCar2 )
      {
        gta2::CameraOrPhysics_sub_41EE30((CameraOrPhysics *)&self->CameraOrPhysics2, self->sCar2);
      }
      gta2::CameraOrPhysics_sub_41F2F0((CameraOrPhysics *)&self->CameraOrPhysics1);
      p_CameraOrPhysics1 = &self->CameraOrPhysics2;
LABEL_39:
      p_CameraOrPhysics2 = p_CameraOrPhysics1;
LABEL_40:
      gta2::CameraOrPhysics_sub_41F2F0((CameraOrPhysics *)p_CameraOrPhysics2);
LABEL_41:
      if ( !self->field_6C )
        qmemcpy(&self->CameraOrPhysics_, p_CameraOrPhysics1, 0xBCu);
      break;
    default:
      break;
  }
  gta2::Player_sub_4A6100(self);
  if ( self->field_6C == 1 )
  {
    gta2::CameraOrPhysics_sub_4A5070((CameraOrPhysics *)&self->CameraOrPhysics_);
    gta2::CameraOrPhysics_sub_41EA10(
      (CameraOrPhysics *)&self->CameraOrPhysics_,
      self->Up,
      self->Down,
      self->Left,
      self->Right,
      self->prevWeapon,
      self->nextWeapon);
    if ( LOBYTE(self->Tango1) )
      gta2::sub_41E580(&self->CameraOrPhysics_, &self->CameraOrPhysics1);
    gta2::CameraOrPhysics_sub_41F2F0((CameraOrPhysics *)&self->CameraOrPhysics_);
  }
  gta2::Player_sub_4A4C90(self);
  MainPed = self->MainPed;
  if ( MainPed )
  {
    if ( (MainPed->PositionX1 & 0x20) != 0 )
      self->field_640 = 1;
    v13 = gta2::Ped_GetPedState(MainPed) == 9;
    v14 = self->field_640;
    if ( v13 )
    {
      if ( !v14 )
      {
        gta2::Player_HandleDeath(self);
        goto LABEL_55;
      }
    }
    else if ( !v14 )
    {
      goto LABEL_55;
    }
    gta2::Player_sub_4A7BA0(self);
  }
LABEL_55:
  if ( self->field_2D0 )
  {
    pPassenger = self->pPassenger;
    if ( pPassenger )
    {
      if ( gta2::Ped_GetPedState(pPassenger) == 9 && !LOBYTE(self->S103_2) )
        gta2::Player_sub_4A7B70(self);
    }
  }
  self->Enter = Enter;
  BYTE1(self->field_88) = v18;
  LOBYTE(self->field_84) = v20;
  self->keySpecial = keySpecial;
  LOWORD(Health) = gNetworkGame;
  if ( !gNetworkGame )
  {
    LOWORD(Health) = (_WORD)gMissionManager;
    if ( gMissionManager )
    {
      p_Money = &self->Money;
      if ( self->field_60 )
      {
        Health = gta2::PlayerStats_GetHealth((PlayerStats *)p_Money);
        if ( Health < gMissionManager->Health )
        {
          self->field_60 = 0;
          v4 = gta2::PlayerStats_sub_4B74D0((PlayerStats *)&self->Money);
          LOWORD(Health) = gta2::PlayerStats_sub_44B300(v4, 2, 0);
        }
      }
      else
      {
        Health = gta2::PlayerStats_GetHealth((PlayerStats *)p_Money);
        if ( Health >= gMissionManager->Health )
        {
          self->field_60 = 1;
          v3 = gta2::PlayerStats_sub_4B74D0((PlayerStats *)&self->Money);
          LOWORD(Health) = gta2::PlayerStats_sub_44B300(v3, 7, 6);
        }
      }
    }
  }
  return Health;
}


// 0x004a81e0: Player::sub_4A81E0
// IDA: Player::sub_4A81E0
// Ghidra: ---
__int16 gta2::Player_sub_4A81E0(Player *self)
{
  PlayerStats *v1; // eax
  char *v2; // eax
  PlayerStats *v3; // eax
  char *v4; // eax
  PlayerStats *v5; // eax
  char *v6; // eax
  PlayerStats *v7; // eax
  char *v8; // eax
  PlayerStats *v9; // eax
  char *v10; // eax
  PlayerStats *pS161_1; // eax
  char *v12; // eax
  PlayerStats *v13; // eax
  char *v14; // eax
  unsigned __int8 Gang; // al
  void *pS161; // ecx
  int pNetworkGame; // eax

  if ( !gta2::MapRelatedStruct_sub_464E70(gMapRelatedStruct, 16) )
    gta2::debug_log(0x83u, "player.cpp", 2895);
  self->field_60 = 0;
  BYTE1(self->S103_2) = 0;
  LOBYTE(self->S103_2) = 0;
  self->field_640 = 0;
  self->field_680 = 0;
  self->field_682 = 1000;
  gta2::PlayerStats_sub_4B7D50((PlayerStats *)&self->Money);
  gta2::PlayerStats_sub_44B260((PlayerStats *)&self->Lives);
  gta2::PlayerStats_sub_44B260((PlayerStats *)&self->MultiPlayer);
  LOBYTE(self->field_64) = 0;
  LOWORD(self->S103_1) = -2;
  if ( gta2::MissionManager_sub_475A20(gMissionManager) )
  {
    gta2::Player_sub_4A6C80(self, (int)&dword_6645E4);
  }
  else
  {
    Gang = gta2::MapGm_GetGang(&gMapGm);
    pS161 = &self->Lives;
    if ( Gang )
      gta2::PlayerStats_SetMultiPlayer((PlayerStats *)pS161, 1);
    else
      gta2::PlayerStats_SetMultiPlayer((PlayerStats *)pS161, 5);
    gta2::PlayerStats_SetMultiPlayer((PlayerStats *)&self->MultiPlayer, 1);
  }
  gta2::CameraOrPhysics_sub_41F410((CameraOrPhysics *)&self->CameraOrPhysics1, (S131 *)self->MainPed);
  gta2::CameraOrPhysics_ResetAccuracy((CameraOrPhysics *)&self->CameraOrPhysics1);
  gta2::CameraOrPhysics_sub_41E410((CameraOrPhysics *)&self->CameraOrPhysics1);
  gta2::CameraOrPhysics_sub_41E010((CameraOrPhysics *)&self->CameraOrPhysics1);
  gta2::CameraOrPhysics_sub_41F410((CameraOrPhysics *)&self->CameraOrPhysics2, (S131 *)self->MainPed);
  gta2::CameraOrPhysics_ResetAccuracy((CameraOrPhysics *)&self->CameraOrPhysics2);
  gta2::CameraOrPhysics_sub_41E410((CameraOrPhysics *)&self->CameraOrPhysics2);
  gta2::CameraOrPhysics_sub_41E010((CameraOrPhysics *)&self->CameraOrPhysics2);
  self->field_2D0 = 0;
  if ( gta2::Player_GetCurrentPlayer(self) && !skip_audio )
    self->Sound = gta2::DMAudio_sub_410750(&gDMAudio, (CameraOrPhysics *)&self->CameraOrPhysics1);
  self->sPed1 = (Ped *)2;
  *(_WORD *)self->gap790 = 0;
  LOWORD(pNetworkGame) = gNetworkGame;
  if ( gNetworkGame )
  {
    pNetworkGame = gta2::Ped_GetRemap(self->MainPed) - 5;
    switch ( pNetworkGame )
    {
      case 0:
      case 1:
        v13 = gta2::PlayerStats_sub_4B74D0((PlayerStats *)&self->Money);
        gta2::PlayerStats_sub_44B300(v13, 7, 4);
        v14 = gta2::PlayerStats_sub_4B7570((PlayerStats *)&self->Money);
        LOWORD(pNetworkGame) = gta2::PlayerStats_sub_44B300((PlayerStats *)v14, 7, 4);
        *(_WORD *)self->gap790 = 4;
        self->sPed1 = (Ped *)7;
        break;
      case 2:
        pS161_1 = gta2::PlayerStats_sub_4B74D0((PlayerStats *)&self->Money);
        gta2::PlayerStats_sub_44B300(pS161_1, 7, 8);
        v12 = gta2::PlayerStats_sub_4B7570((PlayerStats *)&self->Money);
        LOWORD(pNetworkGame) = gta2::PlayerStats_sub_44B300((PlayerStats *)v12, 7, 8);
        *(_WORD *)self->gap790 = 8;
        self->sPed1 = (Ped *)7;
        break;
      case 3:
        v9 = gta2::PlayerStats_sub_4B74D0((PlayerStats *)&self->Money);
        gta2::PlayerStats_sub_44B300(v9, 7, 7);
        v10 = gta2::PlayerStats_sub_4B7570((PlayerStats *)&self->Money);
        LOWORD(pNetworkGame) = gta2::PlayerStats_sub_44B300((PlayerStats *)v10, 7, 7);
        *(_WORD *)self->gap790 = 7;
        self->sPed1 = (Ped *)7;
        break;
      case 4:
        v7 = gta2::PlayerStats_sub_4B74D0((PlayerStats *)&self->Money);
        gta2::PlayerStats_sub_44B300(v7, 7, 5);
        v8 = gta2::PlayerStats_sub_4B7570((PlayerStats *)&self->Money);
        LOWORD(pNetworkGame) = gta2::PlayerStats_sub_44B300((PlayerStats *)v8, 7, 5);
        *(_WORD *)self->gap790 = 5;
        self->sPed1 = (Ped *)7;
        break;
      case 5:
        v5 = gta2::PlayerStats_sub_4B74D0((PlayerStats *)&self->Money);
        gta2::PlayerStats_sub_44B300(v5, 7, 6);
        v6 = gta2::PlayerStats_sub_4B7570((PlayerStats *)&self->Money);
        LOWORD(pNetworkGame) = gta2::PlayerStats_sub_44B300((PlayerStats *)v6, 7, 6);
        *(_WORD *)self->gap790 = 6;
        self->sPed1 = (Ped *)7;
        break;
      case 6:
        v3 = gta2::PlayerStats_sub_4B74D0((PlayerStats *)&self->Money);
        gta2::PlayerStats_sub_44B300(v3, 7, 3);
        v4 = gta2::PlayerStats_sub_4B7570((PlayerStats *)&self->Money);
        LOWORD(pNetworkGame) = gta2::PlayerStats_sub_44B300((PlayerStats *)v4, 7, 3);
        *(_WORD *)self->gap790 = 3;
        self->sPed1 = (Ped *)7;
        break;
      case 8:
        v1 = gta2::PlayerStats_sub_4B74D0((PlayerStats *)&self->Money);
        gta2::PlayerStats_sub_44B300(v1, 7, 2);
        v2 = gta2::PlayerStats_sub_4B7570((PlayerStats *)&self->Money);
        LOWORD(pNetworkGame) = gta2::PlayerStats_sub_44B300((PlayerStats *)v2, 7, 2);
        *(_WORD *)self->gap790 = 2;
        self->sPed1 = (Ped *)7;
        break;
      default:
        return pNetworkGame;
    }
  }
  return pNetworkGame;
}


// 0x004a8340: Player::sub_4A8340
// IDA: Player::sub_4A8340
// Ghidra: ---
void gta2::Player_sub_4A8340(Player *self)
{
  Car *v2; // edi
  int v3; // [esp+4h] [ebp-Ch]
  int v4; // [esp+8h] [ebp-8h]
  int Y; // [esp+Ch] [ebp-4h] BYREF

  if ( gta2::Player_sub_4A5100(self) )
  {
    if ( self->MultiPlayerMode == 2 )
      gta2::Player_sub_4A6900(self);
    gta2::Player_sub_4A6310(self);
  }
  else if ( !self->field_2D0 )
  {
    gta2::Player_sub_4A6610(self, &Y);
    v2 = gta2::CarSystemManager_sub_426A80(gCarSystemManager, Y, v4, v3, 0);
    if ( v2 )
    {
      gta2::Player_sub_4A6900(self);
      gta2::Player_sub_4A6350(self, v2);
    }
  }
}


// 0x004a83c0: Player::Player
// IDA: Player::Player
// Ghidra: ---
Player * gta2::Player_Player(Player *self, unsigned __int8 IDs)
{
  KeyPlayer *p_Rotate; // edi
  S103 *v4; // ecx
  struct Player *v5; // ecx
  _DWORD v7[5]; // [esp+10h] [ebp-14h] BYREF

  v7[1] = self;
  p_Rotate = &self->Rotate;
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&self->Rotate);
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)(&self->Rotate + 1));
  gta2::CameraOrPhysics_SUB_0041f580((CameraOrPhysics *)&self->CameraOrPhysics1);
  v7[4] = 4;
  gta2::CameraOrPhysics_SUB_0041f580((CameraOrPhysics *)&self->CameraOrPhysics_);
  gta2::CameraOrPhysics_SUB_0041f580((CameraOrPhysics *)&self->CameraOrPhysics2);
  gta2::PlayerStats_Money((PlayerStats *)&self->Money);
  gta2::sub_44A1D0(&self->field_644);
  gta2::PlayerStats_Lives((PlayerStats *)&self->Lives);
  gta2::PlayerStats_Lives((PlayerStats *)&self->MultiPlayer);
  gta2::sub_4A6FC0(&self->Network_);
  self->Ids = IDs;
  LOBYTE(self->S103_2) = 0;
  self->field_640 = 0;
  self->field_680 = 0;
  self->field_682 = 1000;
  BYTE1(self->S103_2) = 0;
  self->Player_ = 0;
  self->PlayerNext = 1;
  self->MainPed = 0;
  self->pPassenger = 0;
  self->sCar2 = 0;
  self->RESPECT = 0;
  self->field_38 = 0;
  self->field_3C = 0;
  gta2::Player_PlayerControl(self);
  *p_Rotate = unk_66B0C4;
  *((_WORD *)&self->Rotate + 1) = unk_66B0C4;
  self->FW = unk_66B15C;
  gta2::bitShiftLeft1(v7, 0);
  v4 = (S103 *)v7[0];
  self->SelectWeapon = 0;
  self->S103_ = v4;
  self->MultiPlayerMode = 1;
  self->field_6C = 0;
  LOBYTE(self->Tango1) = 0;
  self->field_8F = 0;
  self->field_2F = 0;
  LOBYTE(self->S103_5) = 0;
  BYTE1(self->S103_5) = 0;
  self->Up = 0;
  self->Down = 0;
  self->Left = 0;
  self->Right = 0;
  self->nextWeapon = 0;
  self->prevWeapon = 0;
  self->debugKey2 = 0;
  self->debugKey1 = 0;
  memset(self->sWeapon, 0, sizeof(self->sWeapon));
  self->field_54 = 0;
  self->field_58 = 0;
  self->sCar1 = 0;
  LOBYTE(self->CurrentPlayer) = 0;
  self->field_2D0 = 0;
  self->MoneyValue = 0;
  self->Sound = 0;
  self->Ids = IDs;
  gta2::PlayerStats_sub_4B7490((PlayerStats *)&self->Money, self, 2, 999999999, 158, 999u);
  gta2::PlayerStats_sub_44B220((PlayerStats *)&self->Lives, 1, 99, 115);
  gta2::PlayerStats_sub_44B220((PlayerStats *)&self->MultiPlayer, 1, 99, 116);
  gta2::Player_SetActivePowerUps(self);
  gta2::Player_sub_4A5180(v5);
  gta2::Player_SetPlayerState(self, 0);
  if ( gNetworkGame )
    gta2::Network_sub_409DA0((Network *)&dword_674214.BaseCar[1].S82, self->string_Arr0x16);
  else
    self->string_Arr0x16[0] = 0;
  self->quit1 = 0;
  return self;
}


// 0x004ba0a0: Player::sub_4BA0A0
// IDA: Player::sub_4BA0A0
// Ghidra: FUN_004ba0a0
void gta2::Player_sub_4BA0A0(void *self,undefined4 *param_1,undefined4 *param_2)
{
  undefined4 *puVar1;
  SpriteS1 *pSVar2;
  int local_8 [2];
  
  local_8[0] = 2;
  pSVar2 = gta2::S122_sub_401BF0((Model *)self,(SpriteS1 *)(local_8 + 1),local_8);
  puVar1 = param_1;
  param_1 = (undefined4 *)0x2;
  *puVar1 = pSVar2->FirstElement;
  pSVar2 = gta2::S122_sub_401BF0((Model *)((int)self + 4),(SpriteS1 *)(local_8 + 1)
                              ,(int *)&param_1);
  *param_2 = pSVar2->FirstElement;
  return;
}


// 0x004c5f60: Player::sub_4C5F60
// IDA: Player::sub_4C5F60
// Ghidra: FUN_004c5f60
void gta2::Player_sub_4C5F60(void *self,Player *pPlayer)
{
  pPlayer->field1684_0x78a = true;
  return;
}


// 0x004c7340: Player::sub_4C7340
// IDA: Player::sub_4C7340
// Ghidra: ---
Tango * gta2::Player_sub_4C7340(Player *self)
{
  return (Tango *)self->S103_4;
}


// 0x004c8a20: Player::OpenChat
// IDA: Player::OpenChat
// Ghidra: ---
int gta2::Player_OpenChat(void *self, void *a1)
{
  *((_BYTE *)self + 1940) = 1;
  return gta2::sub_4A50F0((char *)self + 1940);
}


// 0x004ccab0: Player::sub_4CCAB0
// IDA: Player::sub_4CCAB0
// Ghidra: ---
int gta2::Player_sub_4CCAB0(Player *self)
{
  int v1; // eax
  int result; // eax

  v1 = self->field_50;
  if ( v1 >= 0 )
    self->field_50 = v1 + 1;
  result = 270;
  if ( self->field_50 > 270 )
    self->field_50 = 270;
  return result;
}


// 0x004ccad0: Player::sub_4CCAD0
// IDA: Player::sub_4CCAD0
// Ghidra: ---
int gta2::Player_sub_4CCAD0(Player *self)
{
  int result; // eax

  result = self->field_50;
  if ( result > 60 )
    return 60;
  return result;
}


// 0x004ccae0: Player::sub_4CCAE0
// IDA: Player::sub_4CCAE0
// Ghidra: ---
int gta2::Player_sub_4CCAE0(Player *self)
{
  return self->field_50;
}


// 0x004ccb00: Player::FUN_004ccb00
// IDA: sub_4CCB00
// Ghidra: Player::FUN_004ccb00
byte gta2::Player_FUN_004ccb00(Player *self)
{
  return -1 < self->timeSecond;
}


// 0x004e4d40: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(
           (Player *)&stru_5D22FC.gap2D8[12],
           (S202 *)&stru_5D22FC.gap194[16],
           (int)&stru_5D22FC.gap194[12]);
}


// 0x004e5540: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&stru_5D22FC, (S202 *)&stru_5D22FC.gapBC[16], (int)&stru_5D22FC.S103_2);
}


// 0x004e6260: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(
           (Player *)&stru_5D22FC.field_480,
           (S202 *)&stru_5D22FC.gap344[152],
           (int)&stru_5D22FC.gap344[148]);
}


// 0x004e6ba0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_004e6ba0
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005d303c,(GlassInfo *)&DAT_005d2ed0,
             (S127 *)&DAT_005d2ecc);
  return;
}


// 0x004e73a0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_004e73a0
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)(gBufferSize + 0x1390),
             (GlassInfo *)(gBufferSize + 0x1474),(S127 *)(gBufferSize + 0x13bc))
  ;
  return;
}


// 0x004e8350: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&stru_5D31C0.pPlayer, &stru_5D3130, (int)&stru_5D3110.field_1C);
}


// 0x004e8c90: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&stru_5D3354.pPlayer, &stru_5D32C4, (int)&stru_5D32A4.field_1C);
}


// 0x004e8d40: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&stru_5D31E0.pPlayer, (S202 *)&stru_5D3254.CarSystemManager, (int)&unk_5D3208);
}


// 0x004e95f0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5D3518, &stru_5D3474, (int)&stru_5D3454.field_1C);
}


// 0x004e96a0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&stru_5D3390.pPlayer, (S202 *)&stru_5D3404.CarSystemManager, (int)&unk_5D33B8);
}


// 0x004e9f50: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5D38A4, (S202 *)&unk_5D3734, (int)&unk_5D3730);
}


// 0x004ea750: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&stru_5D3548.field_10, (S202 *)&unk_5D3644, (int)&unk_5D3588);
}


// 0x004eb770: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5D7E50, (S202 *)&unk_5D507C, (int)&unk_5D5078);
}


// 0x004ec590: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5D81C8, (S202 *)&unk_5D805C, (int)&unk_5D8058);
}


// 0x004ecd90: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5D7E8C, (S202 *)&unk_5D7F70, (int)&unk_5D7EB8);
}


// 0x004edd10: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5D854C, (S202 *)&unk_5D83E0, (int)&unk_5D83DC);
}


// 0x004ee510: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5D8210, (S202 *)&unk_5D82F4, (int)&unk_5D823C);
}


// 0x004ef490: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5DC754, (S202 *)&unk_5DC5E8, (int)&unk_5DC5E4);
}


// 0x004efc90: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5D8590, (S202 *)&unk_5DC4FC, (int)&unk_5DC444);
}


// 0x004f0c30: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5DCAF4, (S202 *)&unk_5DC988, (int)&unk_5DC984);
}


// 0x004f0ce0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5DC7A8, (S202 *)&unk_5DC8AC, (int)&unk_5DC7D8);
}


// 0x004f2460: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_004f2460
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e2450,(GlassInfo *)&DAT_005e22e0,
             (S127 *)&DAT_005e22dc);
  return;
}


// 0x004f2c60: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5DCB90, (S202 *)&unk_5E21F0, (int)&unk_5DCBBC);
}


// 0x004f3c20: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5E27F8, (S202 *)&unk_5E2694, (int)&unk_5E2690);
}


// 0x004f3cd0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5E24C0, &unk_5E25BC, (int)&unk_5E24EC);
}


// 0x004f53a0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5E2B84, (S202 *)&unk_5E2A10, (int)&unk_5E2A0C);
}


// 0x004f5ba0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5E2840, (S202 *)&unk_5E2924, (int)&unk_5E286C);
}


// 0x004f6b40: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&byte_5E2F10, (S202 *)&unk_5E2DA4, (int)&unk_5E2DA0);
}


// 0x004f7340: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5E2BD4, (S202 *)&unk_5E2CB8, (int)&unk_5E2C00);
}


// 0x004f82c0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5E3290, (S202 *)&unk_5E3124, (int)&unk_5E3120);
}


// 0x004f8ac0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5E2F54, (S202 *)&unk_5E3038, (int)&unk_5E2F80);
}


// 0x004f9a40: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5E3620, (S202 *)&unk_5E34B4, (int)&unk_5E34B0);
}


// 0x004fa240: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5E32E4, (S202 *)&unk_5E33C8, (int)&unk_5E3310);
}


// 0x004fb1c0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5E3828, (S202 *)&unk_5E3784, (int)&unk_5E3780);
}


// 0x004fbb00: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5E3CB0, (S202 *)&unk_5E3B44, (int)&unk_5E3B40);
}


// 0x004fc270: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5E3964, (S202 *)&unk_5E3BD8, (int)&unk_5E3994);
}


// 0x004fd320: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5E4074, (S202 *)&unk_5E3EFC, (int)&unk_5E3EF8);
}


// 0x004fdb20: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5E3D04, &unk_5E3DF8, (int)&unk_5E3D34);
}


// 0x004fec30: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5E5064, (S202 *)&unk_5E4EE4, (int)&unk_5E4EE0);
}


// 0x004ff430: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5E4CE8, &unk_5E4DE8, (int)&unk_5E4D18);
}


// 0x00500610: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_00500610
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e542c,(GlassInfo *)&DAT_005e52ac,
             (S127 *)&DAT_005e52a8);
  return;
}


// 0x00500e10: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_00500e10
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e50cc,(GlassInfo *)&DAT_005e51bc,
             (S127 *)&DAT_005e50fc);
  return;
}


// 0x00501da0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_00501da0
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e57f8,(GlassInfo *)&DAT_005e5690,
             (S127 *)&DAT_005e568c);
  return;
}


// 0x00502510: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_00502510
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e54c4,(GlassInfo *)&DAT_005e5720,
             (S127 *)&DAT_005e54ec);
  return;
}


// 0x00503520: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_00503520
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e5b7c,(GlassInfo *)&DAT_005e5a18,
             (S127 *)&DAT_005e5a14);
  return;
}


// 0x005035d0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_005035d0
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e5844,(GlassInfo *)&DAT_005e5940,
             (S127 *)&DAT_005e5870);
  return;
}


// 0x00504ca0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_00504ca0
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e5fa4,(GlassInfo *)&DAT_005e5e18,
             (S127 *)&DAT_005e5e14);
  return;
}


// 0x005054a0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5E5C34, (S202 *)&unk_5E5D24, (int)&unk_5E5C64);
}


// 0x00506560: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_00506560
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e632c,(GlassInfo *)&DAT_005e61c0,
             (S127 *)&DAT_005e61bc);
  return;
}


// 0x00506d60: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_00506d60
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e5ff0,(GlassInfo *)&DAT_005e60d4,
             (S127 *)&DAT_005e601c);
  return;
}


// 0x00507ce0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_00507ce0
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e663c,(GlassInfo *)&DAT_005e64fc,
             (S127 *)&DAT_005e64f8);
  return;
}


// 0x005084e0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_005084e0
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e6364,(GlassInfo *)&DAT_005e642c,
             (S127 *)&DAT_005e638c);
  return;
}


// 0x00509190: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_00509190
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e6a3c,(GlassInfo *)&DAT_005e68cc,
             (S127 *)&DAT_005e68c8);
  return;
}


// 0x00509990: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_00509990
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e66cc,(GlassInfo *)&DAT_005e67b8,
             (S127 *)&DAT_005e66fc);
  return;
}


// 0x0050a920: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_0050a920
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e7470,(GlassInfo *)&DAT_005e7378,
             (S127 *)&DAT_005e7374);
  return;
}


// 0x0050b920: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_0050b920
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e784c,(GlassInfo *)&DAT_005e76bc,
             (S127 *)&DAT_005e76b8);
  return;
}


// 0x0050c120: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_0050c120
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e74c4,(GlassInfo *)&DAT_005e75c8,
             (S127 *)&DAT_005e74f8);
  return;
}


// 0x0050d310: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_0050d310
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e79e8,(GlassInfo *)&DAT_005e7944,
             (S127 *)&DAT_005e7940);
  return;
}


// 0x0050dc50: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_0050dc50
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005e7d5c,(GlassInfo *)&DAT_005e7bf0,
             (S127 *)&DAT_005e7bec);
  return;
}


// 0x0050e450: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5E7A20, (S202 *)&unk_5E7B04, (int)&unk_5E7A4C);
}


// 0x0050f3d0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5E80F4, (S202 *)&unk_5E7F8C, (int)&unk_5E7F88);
}


// 0x0050f480: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5E7DA8, (S202 *)&unk_5E7EAC, (int)&unk_5E7DD4);
}


// 0x00510be0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5E8424, (S202 *)&unk_5E82DC, (int)&unk_5E82D8);
}


// 0x005113e0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5E8130, (S202 *)&unk_5E8204, (int)&unk_5E8158);
}


// 0x005121a0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5E85B8, (S202 *)&unk_5E8514, (int)&unk_5E8510);
}


// 0x00512ae0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5E8844, (S202 *)&unk_5E8738, (int)&unk_5E8734);
}


// 0x005132e0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5E85E4, (S202 *)&unk_5E868C, (int)&unk_5E8608);
}


// 0x00513c20: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5E8B68, (S202 *)&unk_5E8A28, (int)&unk_5E8A24);
}


// 0x00513cd0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5E8878, (S202 *)&unk_5E8964, (int)&unk_5E88A0);
}


// 0x005151e0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5E8EF0, (S202 *)&unk_5E8D84, (int)&unk_5E8D80);
}


// 0x005159e0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5E8BB4, (S202 *)&unk_5E8C98, (int)&unk_5E8BE0);
}


// 0x00516960: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5E932C, (S202 *)&unk_5E91C4, (int)&unk_5E91C0);
}


// 0x00516a10: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5E8FDC, (S202 *)&unk_5E90DC, (int)&unk_5E9008);
}


// 0x00518180: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5E96E8, (S202 *)&unk_5E957C, (int)&unk_5E9578);
}


// 0x00518980: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5E93AC, (S202 *)&unk_5E9490, (int)&unk_5E93D8);
}


// 0x00519900: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5EA9B8, (S202 *)&unk_5EA820, (int)&unk_5EA81C);
}


// 0x005199b0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5EA630, (S202 *)&unk_5EA75C, (int)&unk_5EA658);
}


// 0x0051af00: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5EAD3C, (S202 *)&unk_5EABD0, (int)&unk_5EABCC);
}


// 0x0051b700: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5EAA00, (S202 *)&unk_5EAAE4, (int)&unk_5EAA2C);
}


// 0x0051c680: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_0051c680
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_005eaf3c,(GlassInfo *)&DAT_005eae98,
             (S127 *)&DAT_005eae94);
  return;
}


// 0x0051cfd0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5EB4E8, (S202 *)&unk_5EB37C, (int)&unk_5EB378);
}


// 0x0051d080: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5EB194, (S202 *)&unk_5EB294, (int)&unk_5EB1C0);
}


// 0x0051e800: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_5EB884, (S202 *)&unk_5EB70C, (int)&unk_5EB708);
}


// 0x0051f000: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5EB52C, (S202 *)&unk_5EB618, (int)&unk_5EB558);
}


// 0x00520030: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5EBB1C, (S202 *)&unk_5EBA10, (int)&unk_5EBA0C);
}


// 0x00520830: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_5EB8BC, (S202 *)&unk_5EB964, (int)&unk_5EB8E0);
}


// 0x00521170: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5EBEA0, (S202 *)&unk_5EBD34, (int)&unk_5EBD30);
}


// 0x00521970: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5EBB64, (S202 *)&unk_5EBC48, (int)&unk_5EBB90);
}


// 0x005228f0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5EC7A0, (S202 *)&unk_5EC63C, (int)&unk_5EC638);
}


// 0x005229a0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5EBEEC, (S202 *)&unk_5EBFE8, (int)&unk_5EBF18);
}


// 0x00524080: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_661E84, (S202 *)&unk_5EC9C8, (int)&unk_5EC9C4);
}


// 0x00524880: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_5EC7E4, (S202 *)&unk_5EC8CC, (int)&unk_5EC810);
}


// 0x005258c0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66211C, (S202 *)&unk_662014, (int)&unk_662010);
}


// 0x00526030: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_661EBC, (S202 *)&unk_662074, (int)&unk_661EE0);
}


// 0x00526a00: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_6622B0, (S202 *)&unk_66220C, (int)&unk_662208);
}


// 0x00527340: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_662508, (S202 *)&unk_662410, (int)&unk_66240C);
}


// 0x00528340: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_66269C, (S202 *)&unk_6625F8, (int)&unk_6625F4);
}


// 0x005283f0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_662528, (S202 *)&unk_662590, (int)&unk_66253C);
}


// 0x00528ca0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_662B08, (S202 *)&unk_6629A0, (int)&unk_66299C);
}


// 0x00528d50: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_6627B8, (S202 *)&unk_6628B8, (int)&unk_6627E4);
}


// 0x0052a4c0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66327C, &unk_663110, (int)&unk_66310C);
}


// 0x0052acc0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_662C3C, (S202 *)&unk_662D20, (int)&unk_662C68);
}


// 0x0052c1b0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_663730, &unk_6635C4, (int)&unk_6635C0);
}


// 0x0052c9b0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_6633F4, &unk_6634D8, (int)&unk_66341C);
}


// 0x0052d7e0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_663DD4, (S202 *)&unk_6638C4, (int)&unk_6638C0);
}


// 0x0052dfe0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66376C, (S202 *)&unk_663818, (int)&unk_663790);
}


// 0x0052e950: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_664154, (S202 *)&unk_663FE8, (int)&unk_663FE4);
}


// 0x0052f150: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_663E18, (S202 *)&unk_663EFC, (int)&unk_663E44);
}


// 0x005300d0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_664488, (S202 *)&unk_664340, (int)&unk_66433C);
}


// 0x005308d0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_664194, (S202 *)&unk_664268, (int)&unk_6641BC);
}


// 0x00531690: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_664FDC, (S202 *)&unk_664E68, (int)&unk_664E64);
}


// 0x00531e90: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_664504, (S202 *)&unk_664D78, (int)&unk_664534);
}


// 0x00532ef0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_665394, (S202 *)&unk_66524C, (int)&unk_665248);
}


// 0x005336f0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_6650A0, (S202 *)&unk_665174, (int)&unk_6650C8);
}


// 0x005344b0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66574C, (S202 *)&unk_6655B4, (int)&unk_6655B0);
}


// 0x00534cb0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_6653D8, (S202 *)&unk_6654C4, (int)&unk_665408);
}


// 0x00535ce0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_665B28, (S202 *)&unk_6659AC, (int)&unk_6659A8);
}


// 0x005364e0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_6657D0, (S202 *)&unk_6658BC, (int)&unk_6657FC);
}


// 0x005374b0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&byte_669AD8, (S202 *)&stru_6691E4.S202, (int)&stru_6691E4);
}


// 0x00537cb0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_665B64, (S202 *)&unk_665C10, (int)&unk_665B88);
}


// 0x0053d120: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_669E5C, (S202 *)&unk_669CF4, (int)&stru_669CD4.field_1C);
}


// 0x0053d1d0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)stru_669B08.gap14, &unk_669C18, (int)&unk_669B48);
}


// 0x0053e8c0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_66A210, (S202 *)&unk_66A098, (int)&unk_66A094);
}


// 0x0053f0c0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_669EB8, (S202 *)&unk_669FA4, (int)&unk_669EE4);
}


// 0x00540120: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66A3B0, (S202 *)&unk_66A30C, (int)&unk_66A308);
}


// 0x00540a60: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_66A79C, (S202 *)&unk_66A600, (int)&unk_66A5FC);
}


// 0x00541260: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_66A404, &unk_66A500, (int)&unk_66A438);
}


// 0x00542420: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_66AB58, (S202 *)&unk_66A9EC, (int)&unk_66A9E8);
}


// 0x00542c20: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_66A81C, (S202 *)&unk_66A900, (int)&unk_66A848);
}


// 0x00543ba0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_66B048, (S202 *)&unk_66AE60, (int)&unk_66AE5C);
}


// 0x005443a0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_66ABD4, (S202 *)&dword_66AD1C, (int)&unk_66AC10);
}


// 0x00544b30: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66AC4C, (S202 *)&dword_66B014, (int)&unk_66AB94);
}


// 0x00544b50: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66AC4C, (S202 *)&dword_66AFF0, (int)&unk_66AF5C);
}


// 0x00544b70: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66AC4C, (S202 *)&dword_66AD04, (int)&unk_66AF5C);
}


// 0x00544b90: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66AC4C, (S202 *)&unk_66AD10, (int)&MEMORY[0x66ACAC]);
}


// 0x00544bc0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66AC4C, (S202 *)&MEMORY[0x66AD94], (int)&unk_66AB90);
}


// 0x00544c40: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66AC4C, (S202 *)&unk_66AF50, (int)&unk_66AF78);
}


// 0x00544cc0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66AC4C, (S202 *)&unk_66AF30, (int)&unk_66AFD0);
}


// 0x005458b0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_66B3F0, (S202 *)&unk_66B274, (int)&unk_66B270);
}


// 0x005460b0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_005460b0
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&PTR_0066b098,(GlassInfo *)&DAT_0066b184,
             (S127 *)&DAT_0066b0c8);
  return;
}


// 0x00547120: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&stru_66B76C.Select, (S202 *)&stru_66B600.Weapon_, (int)&stru_66B600.field_4);
}


// 0x00547920: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_66B438, (S202 *)&unk_66B51C, (int)&unk_66B464);
}


// 0x005488a0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66BB1C, (S202 *)&unk_66B9B0, (int)&unk_66B9AC);
}


// 0x005490a0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&stru_66B7D0.TargetCar, (S202 *)&unk_66B8C0, (int)&unk_66B808);
}


// 0x0054a030: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_66BED4, (S202 *)&unk_66BD6C, (int)&unk_66BD68);
}


// 0x0054a0e0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_66BB8C, (S202 *)&unk_66BC90, (int)&unk_66BBBC);
}


// 0x0054b850: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_66C25C, (S202 *)&unk_66C0F0, (int)&unk_66C0EC);
}


// 0x0054c050: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_66BF20, (S202 *)&unk_66C004, (int)&unk_66BF4C);
}


// 0x0054cfd0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_66C610, (S202 *)&unk_66C498, (int)&unk_66C494);
}


// 0x0054d7d0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_66C2B4, &unk_66C39C, (int)&unk_66C2E0);
}


// 0x0054e7e0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66C7AC, (S202 *)&unk_66C708, (int)&unk_66C704);
}


// 0x0054f130: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&stru_66F22C.Select, (S202 *)&stru_66F090.field_38, (int)&stru_66F090.UnitCars);
}


// 0x0054f930: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66C7E0, (S202 *)&unk_66C8C4, (int)&unk_66C80C);
}


// 0x005508d0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_66F5C8, (S202 *)&unk_66F458, (int)&unk_66F454);
}


// 0x005510d0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&stru_66F26C.field_10, (S202 *)&unk_66F368, (int)&unk_66F2AC);
}


// 0x005520f0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_66F970, (S202 *)&unk_66F7FC, (int)&unk_66F7F8);
}


// 0x005521a0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_005521a0
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&gSpawnPoint,(GlassInfo *)&DAT_0066f714,
             (S127 *)&DAT_0066f63c);
  return;
}


// 0x005539d0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66FB08, (S202 *)&unk_66FA64, (int)&unk_66FA60);
}


// 0x00554310: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_66FE08, (S202 *)&unk_66FCC8, (int)&unk_66FCC4);
}


// 0x00554b10: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66FB30, (S202 *)&unk_66FBF8, (int)&unk_66FB58);
}


// 0x005557c0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_6702A8, (S202 *)&unk_670138, (int)&unk_670134);
}


// 0x00555fc0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_66FF54, (S202 *)&unk_67003C, (int)&unk_66FF80);
}


// 0x00556fe0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_67062C, (S202 *)&unk_6704C0, (int)&unk_6704BC);
}


// 0x005577e0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_6702F0, (S202 *)&unk_6703D4, (int)&unk_67031C);
}


// 0x00558760: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_6708D4, (S202 *)&unk_6707DC, (int)&unk_6707D8);
}


// 0x00559760: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_670C50, (S202 *)&unk_670AEC, (int)&unk_670AE8);
}


// 0x00559810: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_670918, (S202 *)&unk_670A14, (int)&unk_670944);
}


// 0x0055aee0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_671038, (S202 *)&unk_670EC4, (int)&unk_670EC0);
}


// 0x0055b6e0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&stru_670CD8.field_10, (S202 *)&unk_670DD4, (int)&unk_670D18);
}


// 0x0055c710: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_67186C, (S202 *)&unk_671724, (int)&unk_671720);
}


// 0x0055cf10: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_671578, (S202 *)&unk_67164C, (int)&unk_6715A0);
}


// 0x0055dcd0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_671BFC, &unk_671AF0, (int)&unk_671AEC);
}


// 0x0055e4d0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_67199C, (S202 *)&unk_671A44, (int)&unk_6719C0);
}


// 0x0055ee10: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_671E90, (S202 *)&unk_671D84, (int)&unk_671D80);
}


// 0x0055f610: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_671C30, (S202 *)&unk_671CD8, (int)&unk_671C54);
}


// 0x0055ff50: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_6721BC, (S202 *)&unk_672074, (int)&unk_672070);
}


// 0x00560750: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_671EC8, (S202 *)&unk_671F9C, (int)&unk_671EF0);
}


// 0x00561520: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_672560, (S202 *)&unk_6723E4, (int)&unk_6723E0);
}


// 0x00561d20: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_672204, (S202 *)&unk_6722F4, (int)&unk_672234);
}


// 0x00562db0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_672800, (S202 *)&unk_6726F4, (int)&unk_6726F0);
}


// 0x005635b0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_6725A0, (S202 *)&unk_672648, (int)&unk_6725C4);
}


// 0x00563ef0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_672B7C, (S202 *)&unk_672A10, (int)&unk_672A0C);
}


// 0x005646f0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&dword_672840, (S202 *)&unk_672924, (int)&unk_67286C);
}


// 0x00565670: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_672F00, (S202 *)&unk_672D94, (int)&unk_672D90);
}


// 0x00565e70: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_672BC4, (S202 *)&unk_672CA8, (int)&unk_672BF0);
}


// 0x00566df0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_6732C8, (S202 *)&unk_673154, (int)&unk_673150);
}


// 0x005675f0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_672F70, &unk_673058, (int)&unk_672F9C);
}


// 0x00568630: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_67392C, (S202 *)&unk_6737BC, (int)&unk_6737B8);
}


// 0x00568e30: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_6735D8, (S202 *)&unk_6736C0, (int)&unk_673604);
}


// 0x00569e50: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_673D04, &unk_673B80, (int)&unk_673B7C);
}


// 0x0056a650: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40((Player *)&unk_673984, &unk_673A78, (int)&unk_6739B4);
}


// 0x0056b7e0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: FUN_0056b7e0
void gta2::Player_sub_401B40(void)
{
  gta2::Player_sub_401B40((SpawnPoint *)&DAT_00674f94,(GlassInfo *)&DAT_0067416c,
             (S127 *)&DAT_00674168);
  return;
}


// 0x0056bfe0: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
  return gta2::Player_sub_401B40(&unk_673F88, (S202 *)&stru_67404C.field_24, (int)&unk_673FB4);
}



