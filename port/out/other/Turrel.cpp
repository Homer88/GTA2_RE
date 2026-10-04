#include "gta2_shim.h"

// Module: other, Class: Turrel
// Functions: 18
// Source: unified (IDA+Ghidra)

// 0x004be7c0: Turrel::SpriteContains
// IDA: Turrel::SpriteContains
// Ghidra: ---
char gta2::Turrel_SpriteContains(struct Arsenal *self, int a2)
{
  _DWORD *Sprite; // eax

  Sprite = self->Sprite;
  if ( !self->Sprite )
    return 0;
  while ( *Sprite != a2 )
  {
    Sprite = (_DWORD *)Sprite[1];
    if ( !Sprite )
      return 0;
  }
  return 1;
}


// 0x004bea60: Turrel::sub_4BEA60
// IDA: Turrel::sub_4BEA60
// Ghidra: FUN_004bea60
undefined4 gta2::Turrel_sub_4BEA60(undefined4 *param_1,int param_2)
{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)*param_1;
  while( true ) {
    if (piVar1 == NULL) {
      return 0;
    }
    if (*piVar1 == param_2) break;
    piVar1 = (int *)piVar1[1];
  }
  iVar2 = gta2::General_GetCycle(gGeneral);
  piVar1[5] = iVar2;
  return 1;
}


// 0x004bec60: Turrel::sub_4BEC60
// IDA: Turrel::sub_4BEC60
// Ghidra: FUN_004bec60
void gta2::Turrel_sub_4BEC60(void *self,VehiclePool *param_1)
{
  struct VehiclePool *pVVar1;
  struct VehiclePool *pS46_;
  
                              // WARNING: Load size is inaccurate
  pS46_ = *self;
  if (pS46_->Head != param_1) {
    do {
      pVVar1 = pS46_;
      pS46_ = pVVar1->NextElement;
    } while (pS46_->Head != param_1);
    if (pVVar1 != NULL) {
      pVVar1->NextElement = pS46_->NextElement;
      gta2::SpriteS4_sub_4BEC50(gSpriteS4,pS46_);
      return;
    }
  }
  *(VehiclePool **)self = pS46_->NextElement;
  gta2::SpriteS4_sub_4BEC50(gSpriteS4,pS46_);
  return;
}


// 0x004becb0: Turrel::sub_4BECB0
// IDA: Turrel::sub_4BECB0
// Ghidra: ---
_DWORD * gta2::Turrel_sub_4BECB0(struct Arsenal *self, int a2)
{
  _DWORD *result; // eax
  _DWORD *v3; // edx

  result = self->Sprite;
  v3 = 0;
  if ( self->Sprite )
  {
    while ( *result != a2 )
    {
      v3 = result;
      result = (_DWORD *)result[1];
      if ( !result )
        return result;
    }
    if ( v3 )
      v3[1] = result[1];
    else
      self->Sprite = (void *)result[1];
    gta2::SpriteS4_sub_4BEC50(gSpriteS4, (struct Arsenal *)result);
  }
  return result;
}


// 0x004bed00: Turrel::sub_4BED00
// IDA: Turrel::sub_4BED00
// Ghidra: ---
Arsenal * gta2::Turrel_sub_4BED00(struct Arsenal *self, int a2)
{
  struct Arsenal *v3; // edi
  struct Arsenal *result; // eax
  struct Arsenal *v5; // esi

  v3 = 0;
  result = (struct Arsenal *)self->Sprite;
  if ( self->Sprite )
  {
    do
    {
      if ( *(_DWORD *)&result[2].Count == a2 )
      {
        v3 = result;
        result = *(Arsenal **)&result->Count;
      }
      else if ( v3 )
      {
        *(_DWORD *)&v3->Count = *(_DWORD *)&result->Count;
        gta2::SpriteS4_sub_4BEC50(gSpriteS4, result);
        result = *(Arsenal **)&v3->Count;
      }
      else
      {
        v5 = *(Arsenal **)&result->Count;
        gta2::SpriteS4_sub_4BEC50(gSpriteS4, result);
        result = v5;
        self->Sprite = v5;
      }
    }
    while ( result );
  }
  return result;
}


// 0x004bed60: Turrel::sub_4BED60
// IDA: Turrel::sub_4BED60
// Ghidra: FUN_004bed60
void gta2::Turrel_sub_4BED60(void *self,EventHandler *pS63)
{
  undefined4 *in_EAX;
  
  gta2::SpriteS4_sub_4BEC40(gSpriteS4);
  *in_EAX = pS63;
                              // WARNING: Load size is inaccurate
  in_EAX[1] = *self;
  gta2::S103_sub_41E1E0((LinkedList *)(in_EAX + 2));
  *(undefined4 **)self = in_EAX;
  return;
}


// 0x004bedd0: Turrel::sub_4BEDD0
// IDA: Turrel::sub_4BEDD0
// Ghidra: ---
void * gta2::Turrel_sub_4BEDD0(struct Arsenal *self, int a2)
{
  void *result; // eax

  result = self->Sprite;
  if ( self->Sprite )
  {
    while ( *(_DWORD *)result != a2 )
    {
      result = (void *)*((_DWORD *)result + 1);
      if ( !result )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    gta2::SpriteS4_sub_4BEC40(gSpriteS4);
    *(_DWORD *)result = a2;
    *((_DWORD *)result + 1) = self->Sprite;
    self->Sprite = result;
  }
  return result;
}


// 0x004bee80: Turrel::sub_4BEE80
// IDA: Turrel::sub_4BEE80
// Ghidra: ---
void gta2::Turrel_sub_4BEE80(struct Arsenal *self)
{
  struct Arsenal *Sprite; // esi
  struct Arsenal *v3; // eax

  Sprite = (struct Arsenal *)self->Sprite;
  if ( self->Sprite )
  {
    do
    {
      v3 = Sprite;
      Sprite = *(Arsenal **)&Sprite->Count;
      gta2::SpriteS4_sub_4BEC50(gSpriteS4, v3);
    }
    while ( Sprite );
  }
  self->Sprite = 0;
}


// 0x004beeb0: Turrel::sub_4BEEB0
// IDA: Turrel::sub_4BEEB0
// Ghidra: FUN_004beeb0
VehiclePool * gta2::Turrel_sub_4BEEB0(void *self,int *param_1,undefined *param_2)
{
  struct SpriteS1 *pSVar1;
  byte bVar2;
  bool bVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  struct SpriteS1 *pSVar4;
  struct SpriteS1 *pSVar5;
  struct SpriteS1 *pS46_;
  struct SpriteS1 *local_14;
  struct SpriteS1 *local_10;
  struct SpriteS1 *local_c;
  struct SpriteS3 *local_8;
  undefined1 local_4 [4];
  
                              // WARNING: Load size is inaccurate
  pSVar5 = *self;
  pS46_ = NULL;
  pSVar4 = NULL;
  local_10 = NULL;
  local_8 = (struct SpriteS3 *)self;
  gta2::bitShiftLeft1(&local_14,(void *)0x1869f);
  if (pSVar5 != NULL) {
    do {
      bVar2 = FUN_0042a6b0(local_4,(undefined4 *)local_4,(GlassInfo *)&param_1,
                           (int *)&param_2,
                           (GlassInfo *)
                           &pSVar5->FirstElement->Matrix3DArray[0].PositionX,
                           (GlassInfo *)
                           &pSVar5->FirstElement->Matrix3DArray[0].PositionY);
      pSVar1 = *(SpriteS1 **)CONCAT31(extraout_var,bVar2);
      local_c = pSVar1;
      bVar3 = gta2::Point2D_FUN_004037e0((Point2D *)&local_c,(struct SpriteS1 *)&local_14);
      if (CONCAT31(extraout_var_00,bVar3) != 0) {
        pS46_ = pSVar5;
        local_14 = pSVar1;
        local_10 = pSVar4;
      }
      pSVar1 = pSVar5->Matrix3DArray[0].SpriteS1;
      pSVar4 = pSVar5;
      pSVar5 = pSVar1;
    } while (pSVar1 != NULL);
    if (pS46_ != NULL) {
      pSVar5 = pS46_->FirstElement;
      if (local_10 == NULL) {
        *(SpriteS1 **)local_8->S39_Arr48 = pS46_->Matrix3DArray[0].SpriteS1;
      }
      else {
        local_10->Matrix3DArray[0].SpriteS1 = pS46_->Matrix3DArray[0].SpriteS1;
      }
      gta2::SpriteS4_sub_4BEC50(gSpriteS4,(struct VehiclePool *)pS46_);
      return (struct VehiclePool *)pSVar5;
    }
  }
  return NULL;
}


// 0x004cc990: Turrel::sub_4CC990
// IDA: Turrel::sub_4CC990
// Ghidra: ---
byte gta2::Turrel_sub_4CC990(struct Arsenal *self)
{
  int v2; // [esp+4h] [ebp+4h]

  return byte_575904[v2];
}


// 0x004cc9a0: Turrel::GetWeapon
// IDA: Turrel::GetWeapon
// Ghidra: ---
char gta2::Turrel_GetWeapon(struct Arsenal *self, WeaponType ID_Weapon)
{
  return Weapon[ID_Weapon];
}


// 0x004cd770: Turrel::sub_4CD770
// IDA: Turrel::sub_4CD770
// Ghidra: ---
Weapon * gta2::Turrel_sub_4CD770(struct Arsenal *self, WeaponType TypeWeapon, Ped *pPed, byte pAmmo)
{
  struct Weapon *pWeapon; // eax
  struct Weapon *pWeapon1; // esi

  pWeapon = gta2::Weapon1_sub_4CC9E0(gWeaponDatabase);
  ++self->Count;
  pWeapon1 = pWeapon;
  gta2::Weapon_SetTypeWeapon_0(pWeapon, TypeWeapon);
  gta2::Weapon_SetPed(pWeapon1, pPed);
  gta2::Weapon_SetAmmo(pWeapon1, pAmmo);
  return pWeapon1;
}


// 0x004cd7b0: Turrel::CreateWeaponForTurret
// IDA: Turrel::CreateWeaponForTurret
// Ghidra: ---
Weapon * gta2::Turrel_CreateWeaponForTurret(struct Arsenal *self, WeaponType pWeaponType, Car *pCar, int pAmmo)
{
  struct Weapon *pWeapon; // esi

  pWeapon = gta2::Weapon1_MoveWeaponToNextList(gWeaponDatabase);
  gta2::Weapon_SetTypeWeapon_0(pWeapon, pWeaponType);
  gta2::Weapon_SetCar(pWeapon, pCar);
  gta2::Weapon_SetAmmo(pWeapon, pAmmo);
  return pWeapon;
}


// 0x004cd7f0: Turrel::FindWeaponInPool
// IDA: Turrel::FindWeaponInPool
// Ghidra: ---
Weapon * gta2::Turrel_FindWeaponInPool(struct Arsenal *self, Car *pCar, WeaponType pWeaponType)
{
  struct Weapon *result; // eax

  result = gta2::Weapon1_GetNextWeapon(gWeaponDatabase);
  if ( !result )
    return 0;
  while ( result->Car != pCar || result->TypeWeapon != pWeaponType )
  {
    result = result->NextWeapon;
    if ( !result )
      return 0;
  }
  return result;
}


// 0x004cd820: Turrel::CarAddWeapon
// IDA: Turrel::CarAddWeapon
// Ghidra: ---
char gta2::Turrel_CarAddWeapon(struct Arsenal *self, WeaponType pWeaponType, unsigned __int8 pAmmo, Car *pCar)
{
  struct Weapon *pWeapon; // edi
  char v6; // bl
  struct Ped *Driver; // eax
  struct Player *Player; // ecx

  pWeapon = gta2::Turrel_FindWeaponInPool(self, pCar, pWeaponType);
  if ( pWeapon )
  {
    v6 = gta2::Weapon_sub_4CCB70(pWeapon, pAmmo);
    if ( !v6 )
      return v6;
  }
  else
  {
    pWeapon = gta2::Turrel_CreateWeaponForTurret(self, pWeaponType, pCar, pAmmo);
    v6 = 1;
  }
  Driver = pCar->Driver;
  if ( Driver )
  {
    Player = Driver->isPlayer;
    if ( Player )
    {
      gta2::Player_sub_4A4890(Player, pWeapon);
      return v6;
    }
    if ( Driver )
    {
      pCar->Driver->field_117 = gta2::Turrel_sub_4CD770(gArsenal, pWeaponType, Driver, 0x63u);
      pCar->Driver->field_117->Car = pCar;
    }
  }
  return v6;
}


// 0x004d06e0: Turrel::sub_4D06E0
// IDA: Turrel::sub_4D06E0
// Ghidra: ---
void gta2::Turrel_sub_4D06E0(struct Arsenal *self, Weapon *a2)
{
  gta2::Weapon1_sub_4CDA70(gWeaponDatabase, a2);
  --self->Count;
}


// 0x004d0700: Turrel::sub_4D0700
// IDA: Turrel::sub_4D0700
// Ghidra: ---
Weapon * gta2::Turrel_sub_4D0700(struct Arsenal *self, Car *pCar)
{
  struct Weapon *result; // eax
  struct Weapon *pWeapon; // esi
  struct Weapon *pWeapon4; // eax

  result = gta2::Weapon1_GetNextWeapon(gWeaponDatabase);
  pWeapon = result;
  while ( pWeapon )
  {
    if ( pWeapon->Car == pCar )
    {
      pWeapon4 = pWeapon;
      pWeapon = pWeapon->NextWeapon;
      result = gta2::Weapon1_sub_4A4F20(gWeaponDatabase, pWeapon4);
    }
    else
    {
      pWeapon = pWeapon->NextWeapon;
    }
  }
  return result;
}


// 0x004d0800: Turrel::sub_4D0800
// IDA: Turrel::sub_4D0800
// Ghidra: FUN_004d0800
void gta2::Turrel_sub_4D0800(void)
{
  if (gTextLabel != NULL) {
    FUN_004d07e0(1);
    gTextLabel = NULL;
  }
  return;
}



