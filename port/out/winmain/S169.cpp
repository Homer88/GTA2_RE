#include "gta2_shim.h"

// Module: winmain, Class: S169
// Functions: 29
// Source: unified (IDA+Ghidra)

// 0x004035b0: S169::S169
// IDA: S169::S169
// Ghidra: ---
int gta2::S169_S169(struct S169 *self)
{
  int result; // eax

  result = 0;
  LOBYTE(self->field_40) = 0;
  self->field_38 = 2;
  self->field_30 = 0;
  self->field_36 = 0;
  self->Ped_ = 0;
  LOBYTE(self->Ped1[0]) = 1;
  BYTE1(self->Ped1[0]) = 0;
  self->Index = 0;
  self->field_35 = 0;
  memset(self->Ped_Arr9, 0, sizeof(self->Ped_Arr9));
  return result;
}


// 0x00403650: S169::sub_403650
// IDA: S169::sub_403650
// Ghidra: FUN_00403650
byte gta2::S169_sub_403650(void *self)
{
  struct Ped *this_00;
  byte bVar1;
  byte bVar2;
  uint local_8;
  uint local_4;
  
  *(undefined1 *)((int)self + 0x36) = *(undefined1 *)((int)self + 0x34);
  if ((*(Ped **)((int)self + 0x2c))->CurrentCar != NULL) {
    gta2::Ped_sub_4411B0(*(Ped **)((int)self + 0x2c));
    *(undefined4 *)((int)self + 0x2c) = 0;
  }
  bVar2 = 0;
  local_8 = 0;
  if (*(char *)((int)self + 0x34) != '\0') {
    do {
      this_00 = *(Ped **)((int)self + local_8 * 4 + 4);
      if (this_00->CurrentCar != NULL) {
        gta2::Ped_sub_4411B0(this_00);
        *(undefined4 *)((int)self + local_8 * 4 + 4) = 0;
      }
      bVar2 = bVar2 + 1;
      local_8 = (uint)bVar2;
    } while (bVar2 < *(byte *)((int)self + 0x34));
  }
  bVar2 = 0;
  local_8 = 0;
  if (*(char *)((int)self + 0x34) != '\0') {
    do {
      if ((*(int *)((int)self + local_8 * 4 + 4) == 0) &&
         (bVar1 = bVar2, bVar2 < *(byte *)((int)self + 0x34))) {
        do {
          local_4 = (uint)bVar1;
          if (*(int *)((int)self + local_4 * 4 + 4) != 0) {
            *(undefined4 *)((int)self + local_8 * 4 + 4) =
                 *(undefined4 *)((int)self + local_4 * 4 + 4);
            *(undefined4 *)((int)self + local_4 * 4 + 4) = 0;
            break;
          }
          bVar1 = bVar1 + 1;
        } while (bVar1 < *(byte *)((int)self + 0x34));
      }
      bVar2 = bVar2 + 1;
      local_8 = (uint)bVar2;
    } while (bVar2 < *(byte *)((int)self + 0x34));
  }
  bVar2 = 0;
  if (*(int *)((int)self + 4) != 0) {
    do {
      bVar2 = bVar2 + 1;
      local_8 = (uint)bVar2;
    } while (*(int *)((int)self + local_8 * 4 + 4) != 0);
    if (bVar2 != 0) {
      return 1;
    }
  }
  return 0;
}


// 0x004037a0: S169::AreAnyPedActive
// IDA: S169::AreAnyPedActive
// Ghidra: ---
char gta2::S169_AreAnyPedActive(struct S169 *self)
{
  unsigned __int8 Index; // dl
  unsigned __int8 v2; // al
  unsigned __int8 v4; // [esp+8h] [ebp-4h]

  Index = self->Index;
  v2 = 0;
  v4 = 0;
  if ( !Index )
    return 1;
  while ( !self->Ped_Arr9[v4]->field_10B )
  {
    v4 = ++v2;
    if ( v2 >= Index )
      return 1;
  }
  return 0;
}


// 0x004038e0: S169::SetInUse
// IDA: S169::SetInUse
// Ghidra: ---
void gta2::S169_SetInUse(struct S169 *self)
{
  LOBYTE(self->field_40) = 1;
}


// 0x004038f0: S169::GetInUse
// IDA: S169::GetInUse
// Ghidra: ---
char gta2::S169_GetInUse(struct S169 *self)
{
  return self->field_40;
}


// 0x00403be0: S169::sub_403BE0
// IDA: S169::sub_403BE0
// Ghidra: ---
int gta2::S169_sub_403BE0(struct S169 *self)
{
  struct Ped *Ped; // ecx
  int result; // eax
  struct Ped **Ped_Arr9; // esi
  int v5; // edi

  Ped = self->Ped_;
  LOBYTE(self->field_40) = 0;
  self->field_38 = 2;
  self->field_30 = 0;
  self->field_36 = 0;
  self->Index = 0;
  if ( Ped )
    gta2::Ped_SetDefault(Ped);
  self->Ped_ = 0;
  LOBYTE(self->Ped1[0]) = 1;
  BYTE1(self->Ped1[0]) = 0;
  self->Index = 0;
  self->field_35 = 0;
  Ped_Arr9 = self->Ped_Arr9;
  v5 = 9;
  do
  {
    if ( *Ped_Arr9 )
      gta2::Ped_SetDefault(*Ped_Arr9);
    *Ped_Arr9++ = 0;
    --v5;
  }
  while ( v5 );
  return result;
}


// 0x00403c40: S169::sub_403C40
// IDA: S169::sub_403C40
// Ghidra: ---
char gta2::S169_sub_403C40(struct S169 *self)
{
  struct Ped *Ped; // ecx
  unsigned __int8 v3; // bl
  struct Ped *v4; // ecx
  unsigned __int8 v6; // [esp+8h] [ebp-4h]

  Ped = self->Ped_;
  if ( Ped->GameObject2 && gta2::Ped_GetSub_4039F0(Ped) >= 0x28u )
  {
    v3 = 0;
    v6 = 0;
    if ( !self->Index )
      return 1;
    while ( 1 )
    {
      v4 = self->Ped_Arr9[v6];
      if ( !v4->GameObject2 || gta2::Ped_GetSub_4039F0(v4) < 0x28u )
        break;
      v6 = ++v3;
      if ( v3 >= self->Index )
        return 1;
    }
  }
  return 0;
}


// 0x00403d10: S169::sub_403D10
// IDA: S169::sub_403D10
// Ghidra: FUN_00403d10
void gta2::S169_sub_403D10(void *self)
{
  gta2::Ped_IsInCar(*(Ped **)((int)self + 0x2c));
  return;
}


// 0x00403d20: S169::sub_403D20
// IDA: S169::sub_403D20
// Ghidra: FUN_00403d20
undefined4 gta2::S169_sub_403D20(int param_1)
{
  struct Ped *self;
  int iVar1;
  
  self = *(Ped **)(param_1 + 0x2c);
  iVar1 = gta2::Ped_GetPedState(self);
  if (iVar1 != 3) {
    iVar1 = gta2::Ped_GetPedState(self);
    if (iVar1 != 5) {
      return 0;
    }
  }
  return 1;
}


// 0x00403da0: S169::sub_403DA0
// IDA: S169::sub_403DA0
// Ghidra: ---
void gta2::S169_sub_403DA0(struct S169 *self)
{
  unsigned __int8 v2; // bl
  struct Ped *v3; // edi
  struct Ped **v4; // esi
  struct Ped *v5; // esi
  unsigned int Flags; // edx
  unsigned __int8 i; // [esp+4h] [ebp-4h]

  if ( LOBYTE(self->field_40) )
  {
    gta2::Ped_SetDefault(self->Ped_);
    if ( self->Ped_Arr9[0] )
    {
      v2 = 0;
      for ( i = 0; v2 < self->Index; i = v2 )
      {
        v3 = self->Ped_Arr9[i];
        v4 = &self->Ped_Arr9[i];
        if ( gta2::Ped_GetPedState(v3) == 9 || v3->Flags == 9 )
        {
          gta2::Ped_SetDefault(v3);
        }
        else
        {
          if ( gta2::Ped_IsInCar(v3) )
          {
            gta2::Ped_PedSetObjective(v3, 34, 9999);
            gta2::Ped_SetCurrentCar(*v4, (Car *)((*v4)->field_10B));
          }
          else
          {
            gta2::Ped_PedSetObjective(v3, 0, 9999);
          }
          gta2::Ped_SetAnimationState(*v4, 0, 9999);
          gta2::Ped_SetDefault(*v4);
          gta2::Ped_SetSearchType(*v4, SEARCHTYPE_AREA);
        }
        v5 = *v4;
        Flags = v5->PositionX1;
        BYTE1(Flags) |= 4u;
        ++v2;
        v5->PositionX1 = Flags;
      }
    }
    gta2::S169_sub_403BE0(self);
  }
}


// 0x00403e90: S169::ManageGroupPedObjectives
// IDA: S169::ManageGroupPedObjectives
// Ghidra: ---
void gta2::S169_ManageGroupPedObjectives(struct S169 *self)
{
  struct Ped *Ped; // esi
  unsigned __int8 v3; // bl
  struct Ped *Ped2; // edi
  struct Ped **Ped1; // esi
  unsigned __int8 i; // [esp+4h] [ebp-4h]

  if ( LOBYTE(self->field_40) )
  {
    Ped = self->Ped_;
    if ( gta2::Ped_GetPedState(Ped) != 9 && Ped->Flags != 9 )
    {
      gta2::Ped_PedSetObjective(Ped, 0, 9999);
      gta2::Ped_SetAnimationState(self->Ped_, 0, 9999);
    }
    gta2::Ped_SetDefault(self->Ped_);
    if ( self->Ped_Arr9[0] )
    {
      v3 = 0;
      for ( i = 0; v3 < self->Index; i = v3 )
      {
        Ped2 = self->Ped_Arr9[i];
        Ped1 = &self->Ped_Arr9[i];
        if ( gta2::Ped_GetPedState(Ped2) == 9 || Ped2->Flags == 9 )
        {
          gta2::Ped_SetDefault(Ped2);
        }
        else
        {
          if ( gta2::Ped_IsInCar(Ped2) )
          {
            gta2::Ped_SetAnimationState(Ped2, 0, 9999);
            gta2::Ped_PedSetObjective(*Ped1, 34, 9999);
            gta2::Ped_SetCurrentCar(*Ped1, (Car *)((*Ped1)->field_10B));
          }
          else
          {
            gta2::Ped_PedSetObjective(Ped2, 0, 9999);
            gta2::Ped_SetAnimationState(*Ped1, 0, 9999);
          }
          gta2::Ped_SetDefault(*Ped1);
          gta2::Ped_SetSearchType(*Ped1, SEARCHTYPE_AREA);
        }
        ++v3;
      }
    }
    gta2::S169_sub_403BE0(self);
  }
}


// 0x00403fb0: S169::sub_403FB0
// IDA: S169::sub_403FB0
// Ghidra: ---
void gta2::S169_sub_403FB0(struct S169 *self, Ped *a2)
{
  int v4; // edi
  struct Ped *v5; // ebp
  char a2a; // [esp+Ch] [ebp+4h]

  if ( a2 )
  {
    if ( !gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
    {
      gta2::Ped_PedSetObjective(self->Ped_, 3, 9999);
      gta2::Ped_SetDriverPed(self->Ped_, a2);
      gta2::Ped_SetAnimationState(self->Ped_, 3, 9999);
      gta2::Ped_SetPed2(self->Ped_, a2);
      gta2::Ped_sub_403950(self->Ped_);
      gta2::Ped_SetSub_403A20(self->Ped_);
      gta2::Ped_sub_403A50(self->Ped_, (GameObject *)stru_5D2E18.field_10);
    }
    gta2::Ped_SetDefault(self->Ped_);
    a2a = 0;
    if ( self->Index )
    {
      v4 = 0;
      do
      {
        v5 = self->Ped_Arr9[v4];
        if ( gta2::Ped_IsInCar(v5) )
        {
          gta2::Ped_SetAnimationState(v5, 0, 9999);
          gta2::Ped_PedSetObjective(self->Ped_Arr9[v4], 6, 9999);
          gta2::Ped_SetDriverPed(self->Ped_Arr9[v4], a2);
          gta2::Ped_SetSub_403A20(self->Ped_Arr9[v4]);
          gta2::Ped_SetDefault(self->Ped_Arr9[v4]);
        }
        else
        {
          gta2::Ped_PedSetObjective(v5, 3, 9999);
          gta2::Ped_SetDriverPed(self->Ped_Arr9[v4], a2);
          gta2::Ped_SetAnimationState(self->Ped_Arr9[v4], 3, 9999);
          gta2::Ped_SetPed2(self->Ped_Arr9[v4], a2);
          gta2::Ped_sub_403950(self->Ped_Arr9[v4]);
          gta2::Ped_SetSub_403A20(self->Ped_Arr9[v4]);
          gta2::Ped_sub_403A50(self->Ped_Arr9[v4], (GameObject *)stru_5D2E18.field_10);
          gta2::Ped_SetDefault(self->Ped_Arr9[v4]);
          gta2::Ped_SetSearchType(self->Ped_Arr9[v4], SEARCHTYPE_AREA);
        }
        v4 = ++a2a;
      }
      while ( a2a < (int)self->Index );
    }
    gta2::S169_sub_403BE0(self);
  }
  else
  {
    gta2::S169_ManageGroupPedObjectives(self);
  }
}


// 0x00404120: S169::sub_404120
// IDA: S169::sub_404120
// Ghidra: ---
void gta2::S169_sub_404120(struct S169 *self, unsigned __int8 Index_1)
{
  struct Ped *pPed; // edi
  struct Ped *pPed_2; // ecx
  Weapon *SelectedWeapon; // ebp
  int v6; // eax
  int State; // eax
  int v8; // eax
  int CurrentAction; // eax
  char Sub_4039E0; // al
  char Sub_4039D0; // al
  struct Ped *Driver; // eax
  Car *CarPed; // eax
  struct Ped *v14; // eax
  Car *CurrentCar; // eax
  int TargetCarDoor; // eax
  char Index; // al
  struct Ped *v18; // ebp
  struct GameObject *GameObject; // eax
  struct Ped *pPed_1; // ecx
  struct GameObject *v21; // ebp
  struct Ped *v22; // ecx
  unsigned int Flags; // eax
  struct Ped *Ped; // [esp-4h] [ebp-20h]
  int v25; // [esp-4h] [ebp-20h]
  int v26; // [esp-4h] [ebp-20h]
  char *v27; // [esp+10h] [ebp-Ch]
  Weapon *pWeapon; // [esp+14h] [ebp-8h]
  Weapon *Weapon1; // [esp+18h] [ebp-4h]

  pPed = gta2::PedManager_sub_403890(gPedManager);
  Ped = self->Ped_;
  pPed_2 = self->Ped_Arr9[Index_1];
  SelectedWeapon = Ped->WeaponSelect;
  pWeapon = pPed_2->WeaponSelect;
  Weapon1 = *(Weapon **)&pPed_2->field_113;
  v27 = (char *)(intptr_t)*(Weapon **)&Ped->field_113;
  gta2::Ped_CopyPed(pPed, Ped);
  gta2::Ped_CopyPed(self->Ped_, self->Ped_Arr9[Index_1]);
  self->Ped_->WeaponSelect = SelectedWeapon;
  *(Weapon **)&self->Ped_->field_113 = (Weapon *)(intptr_t)v27;
  LOWORD(v6) = gta2::Ped_Get_sub_403B30(pPed);
  v25 = v6;
  State = gta2::Ped_GetState(pPed);
  gta2::Ped_PedSetObjective(self->Ped_, State, v25);
  LOWORD(v8) = gta2::Ped_Get_sub_403B20(pPed);
  v26 = v8;
  CurrentAction = gta2::Ped_GetCurrentAction(pPed);
  gta2::Ped_SetAnimationState(self->Ped_, CurrentAction, v26);
  Sub_4039E0 = gta2::Ped_GetDamageState(pPed);
  gta2::Ped_sub_403B40(self->Ped_, Sub_4039E0);
  Sub_4039D0 = gta2::Ped_GetExitAnim(pPed);
  gta2::Ped_SetExitAnimState(self->Ped_, Sub_4039D0);
  Driver = gta2::Ped_GetDriver(pPed);
  gta2::Ped_SetDriverPed(self->Ped_, Driver);
  CarPed = gta2::Ped_GetVehicle(pPed);
  gta2::Ped_SetCurrentCar(self->Ped_, CarPed);
  self->Ped_->field_13C = pPed->field_13C;
  self->Ped_->Car1 = pPed->Car1;
  self->Ped_->Weapon2 = pPed->Weapon2;
  self->Ped_->Gang_ = pPed->Gang_;
  self->Ped_->DriverPed = pPed->DriverPed;
  v14 = gta2::Ped_GetLinkedPed(pPed);
  gta2::Ped_SetPed2(self->Ped_, v14);
  CurrentCar = gta2::Ped_GetCurrentVehicle(pPed);
  gta2::Ped_SetCarPed(self->Ped_, CurrentCar);
  self->Ped_->CurrentCar = pPed->CurrentCar;
  self->Ped_->SelectedWeapon = pPed->SelectedWeapon;
  self->Ped_->Weapon1 = pPed->Weapon1;
  gta2::Ped_SetCarId(self->Ped_, 99);
  TargetCarDoor = gta2::Ped_GetTargetCarDoor(pPed);
  gta2::Ped_SetTargetCarDoor(self->Ped_, TargetCarDoor);
  Index = gta2::Ped_GetAnimationState(pPed);
  gta2::Ped_SetAnimationState_0(self->Ped_, Index);
  v18 = self->Ped_;
  GameObject = v18->GameObject2;
  if ( GameObject )
  {
    GameObject->Ped_ = v18;
  }
  else if ( !gta2::Ped_GetTargetCarDoor(self->Ped_) && (*(Car **)&v18->field_10B)->Driver != v18 )
  {
    gta2::Ped_SetTargetCarDoor(v18, 1);
  }
  gta2::Ped_CopyPed(self->Ped_Arr9[Index_1], pPed);
  gta2::Ped_SetCarId(self->Ped_Arr9[Index_1], Index_1);
  self->Ped_Arr9[Index_1]->WeaponSelect = pWeapon;
  *(Weapon **)&self->Ped_Arr9[Index_1]->field_113 = Weapon1;
  pPed_1 = self->Ped_Arr9[Index_1];
  v21 = pPed_1->GameObject2;
  if ( v21 && gta2::Ped_GetCurrentOccupation(pPed_1) == UNKNOWN_OCUPATION_23 )
  {
    v21->Ped_ = self->Ped_Arr9[Index_1];
    gta2::Ped_SetTargetCarDoor(self->Ped_Arr9[Index_1], 1);
  }
  else
  {
    if ( v21 )
      v21->Ped_ = self->Ped_Arr9[Index_1];
    if ( Index_1 >= self->Index - 1 )
    {
      *(void **)&self->Ped_Arr9[Index_1]->field_103 = 0;
      self->Ped_Arr9[Index_1] = 0;
    }
    else
    {
      gta2::Ped_SetDefault(self->Ped_Arr9[Index_1]);
      v22 = self->Ped1[self->Index];
      self->Ped_Arr9[Index_1] = v22;
      gta2::Ped_SetCarId(v22, Index_1);
    }
    --self->Index;
    gta2::Ped_SetCarId(self->Ped_, 99);
  }
  if ( pPed->field_1D4 == (SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT) )
  {
    gta2::Ped_sub_435B80(pPed);
    Flags = pPed->PositionX1;
    BYTE1(Flags) |= 4u;
    pPed->PositionX1 = Flags;
  }
  else
  {
    gta2::Ped_sub_435B80(pPed);
  }
  gta2::Ped_SetHealth(pPed, 100);
  gta2::Ped_SetCurrentOccupation(pPed, UNKNOWN_OCUPATION2);
  gta2::Ped_sub_4411B0(pPed);
}


// 0x00404400: S169::sub_404400
// IDA: S169::sub_404400
// Ghidra: ---
void gta2::S169_sub_404400(struct S169 *self, Ped *pPed)
{
  self->Ped_ = pPed;
  gta2::Ped_sub_403930(pPed, self);
  gta2::Ped_SetCarId(self->Ped_, 99);
}


// 0x00404420: S169::AddPedtoList
// IDA: S169::AddPedtoList
// Ghidra: ---
void gta2::S169_AddPedtoList(struct S169 *self, Ped *a2, unsigned __int8 Id)
{
  self->Ped_Arr9[Id] = a2;
  gta2::Ped_sub_403930(a2, self);
  gta2::Ped_SetCarId(a2, Id);
}


// 0x00404450: S169::sub_404450
// IDA: S169::sub_404450
// Ghidra: ---
Ped * gta2::S169_sub_404450(struct S169 *self)
{
  char v2; // bl

  v2 = self->Index - 1;
  if ( v2 < 0 )
    return 0;
  while ( gta2::Ped_IsCrouching(self->Ped_Arr9[v2]) )
  {
    if ( --v2 < 0 )
      return 0;
  }
  return self->Ped_Arr9[v2];
}


// 0x00404480: S169::sub_404480
// IDA: S169::sub_404480
// Ghidra: ---
int gta2::S169_sub_404480(struct S169 *self)
{
  int result; // eax

  LOBYTE(result) = gta2::Ped_IsCrouching(self->Ped_);
  return result;
}


// 0x00404490: S169::sub_404490
// IDA: S169::sub_404490
// Ghidra: ---
Ped * gta2::S169_sub_404490(struct S169 *self, int *arg0)
{
  unsigned __int8 v2; // bl
  S169 *v3; // ebp
  unsigned __int8 Index; // al
  struct Ped *Ped; // edi
  struct Ped **Ped_Arr9; // ebp
  SpriteS1 *X; // eax
  struct Ped *v8; // esi
  int v9; // eax
  int *v10; // eax
  int v11; // eax
  bool v12; // zf
  int *p_pPLayera; // eax
  int v14; // esi
  int v15; // edx
  unsigned __int8 v17; // [esp+Bh] [ebp-35h]
  SpriteS1 *pPLayera; // [esp+Ch] [ebp-34h] BYREF
  int a2; // [esp+10h] [ebp-30h] BYREF
  int v20; // [esp+14h] [ebp-2Ch] BYREF
  int v21; // [esp+18h] [ebp-28h]
  S169 *v22; // [esp+1Ch] [ebp-24h]
  int localX; // [esp+20h] [ebp-20h] BYREF
  int v24; // [esp+24h] [ebp-1Ch] BYREF
  char v25[4]; // [esp+28h] [ebp-18h] BYREF
  int Y; // [esp+2Ch] [ebp-14h] BYREF
  int v27; // [esp+30h] [ebp-10h] BYREF
  char v28[4]; // [esp+34h] [ebp-Ch] BYREF
  char v29[4]; // [esp+38h] [ebp-8h] BYREF
  char v30[4]; // [esp+3Ch] [ebp-4h] BYREF

  v2 = 0;
  v3 = self;
  v22 = self;
  gta2::bitShiftLeft1((ushort *)&v20, 0);
  Index = v3->Index;
  LOBYTE(v21) = 0;
  v17 = Index;
  if ( Index )
  {
    Ped = v3->Ped_;
    Ped_Arr9 = v3->Ped_Arr9;
    do
    {
      gta2::Ped_GetXCoordinate(Ped, &localX);
      v8 = *Ped_Arr9;
      pPLayera = (SpriteS1 *)(intptr_t)localX;
      gta2::Ped_GetXCoordinate(v8, &v24);
      v9 = *(int *)&v24;
      pPLayera = gta2::Player_sub_401B40((Player *)&pPLayera, (S202 *)v25, (void *)(intptr_t)v9)->FirstElement;
      gta2::Ped_GetYCoordinate(Ped, &Y);
      a2 = *v10;
      gta2::Ped_GetYCoordinate(v8, &v27);
      a2 = (int)gta2::Player_sub_401B40((Player *)&a2, (S202 *)v28, (void *)(intptr_t)v11)->FirstElement;
      pPLayera = *(SpriteS1 **)gta2::sub_403840(&pPLayera, (Player *)v29, &pPLayera);
      a2 = *(_DWORD *)gta2::sub_403840(&a2, (Player *)v30, &a2);
      v12 = gta2::Car_sub_403800((Car *)&pPLayera, &a2) == 0;
      p_pPLayera = (int *)&pPLayera;
      if ( v12 )
        p_pPLayera = &a2;
      v14 = *p_pPLayera;
      a2 = *p_pPLayera;
      if ( gta2::Car_sub_403800((Car *)&a2, &v20) )
      {
        v20 = v14;
        LOBYTE(v21) = v2;
      }
      ++v2;
      ++Ped_Arr9;
    }
    while ( v2 < v17 );
    v3 = v22;
  }
  v15 = (unsigned __int8)v21;
  *arg0 = v20;
  return v3->Ped_Arr9[v15];
}


// 0x004045d0: S169::sub_4045D0
// IDA: S169::sub_4045D0
// Ghidra: ---
char gta2::S169_sub_4045D0(struct S169 *self)
{
  struct Ped *Ped; // eax
  unsigned __int8 v3; // bl
  struct Ped *v4; // esi
  Car *v5; // eax
  int v6; // eax
  struct Ped *v7; // eax
  unsigned __int8 i; // [esp+4h] [ebp-8h]
  _BYTE a2[4]; // [esp+8h] [ebp-4h] BYREF

  Ped = self->Ped_;
  if ( !Ped->field_10B && (Ped->PositionX1 & 0x8000000) == 0 )
  {
    LOBYTE(Ped) = self->Index;
    v3 = 0;
    for ( i = 0; v3 < (unsigned __int8)Ped; i = ++v3 )
    {
      v4 = self->Ped_Arr9[i];
      if ( gta2::Ped_GetCurrentAction(v4) != 9 && v4->GameObject2 )
        gta2::Ped_SetAnimationState(v4, 9, 9999);
      if ( self->field_38 == 1 )
      {
        if ( !v3 )
          goto LABEL_19;
        gta2::Ped_SetPed2(v4, self->Ped1[i]);
      }
      else if ( !gta2::Ped_GetDeadPed(v4) )
      {
        v5 = (Car *)gta2::Ped_sub_436160(self->Ped_, a2);
        LOWORD(v6) = gta2::Car_sub_403820(v5, &stru_5D22FC.gap48B[233]);
        if ( v6 )
        {
          switch ( i )
          {
            case 3u:
              v7 = self->Ped_Arr9[0];
              goto LABEL_20;
            case 4u:
              gta2::Ped_SetPed2(v4, self->Ped_Arr9[1]);
              break;
            case 5u:
              gta2::Ped_SetPed2(v4, self->Ped_Arr9[2]);
              break;
            case 6u:
              v7 = self->Ped_Arr9[3];
              goto LABEL_20;
            case 7u:
              gta2::Ped_SetPed2(v4, self->Ped_Arr9[4]);
              break;
            default:
              gta2::Ped_SetPed2(v4, self->Ped_);
              break;
          }
          goto LABEL_21;
        }
LABEL_19:
        v7 = self->Ped_;
LABEL_20:
        gta2::Ped_SetPed2(v4, v7);
      }
LABEL_21:
      gta2::Ped_sub_403A40(v4);
      LOBYTE(Ped) = self->Index;
    }
  }
  return (char)Ped;
}


// 0x004046f0: S169::sub_4046F0
// IDA: S169::sub_4046F0
// Ghidra: ---
void gta2::S169_sub_4046F0(struct S169 *self, unsigned __int8 XIdx)
{
  struct Ped *Ped; // edi
  struct Ped *v4; // esi
  int XCoordinate; // eax
  int v18; // eax
  int v7; // eax
  bool v8; // zf
  _DWORD *p_X; // eax
  BOOL v10; // eax
  struct Ped *v11; // ecx
  int pPLayera; // [esp+Ch] [ebp-Ch] BYREF
  int Y; // [esp+10h] [ebp-8h] BYREF
  _BYTE v14[4]; // [esp+14h] [ebp-4h] BYREF

  int X;
  Ped = self->Ped_;
  v4 = self->Ped_Arr9[XIdx];
  if ( gta2::Ped_GetGameObject(Ped) )
  {
    *(_DWORD *)&X = *(_DWORD *)gta2::Ped_GetXCoordinate(Ped, &X);
    XCoordinate = gta2::Ped_GetXCoordinate(v4, &pPLayera);
    *(_DWORD *)&X = (int)(intptr_t)gta2::Player_sub_401B40((Player *)&X, (S202 *)&Y, (void *)(intptr_t)XCoordinate)->FirstElement;
    gta2::Ped_GetYCoordinate(Ped, &Y);
    pPLayera = Y;
    gta2::Ped_GetYCoordinate(v4, &Y);
    pPLayera = (int)gta2::Player_sub_401B40((Player *)&pPLayera, (S202 *)v14, (void *)(intptr_t)v7)->FirstElement;
    *(_DWORD *)&X = *(_DWORD *)gta2::sub_403840((void *)pPLayera, (Player *)v14, &X);
    pPLayera = *(_DWORD *)gta2::sub_403840((void *)X, (Player *)v14, &pPLayera);
    v8 = gta2::Car_sub_403800((Car *)&X, &pPLayera) == 0;
    p_X = (_DWORD *)&X;
    if ( v8 )
      p_X = (_DWORD *)&pPLayera;
    *(_DWORD *)&X = *p_X;
    v10 = gta2::sub_4037E0(&X);
    v11 = v4;
    if ( v10 )
    {
      gta2::Ped_SetAnimationState(v4, 9, 9999);
      gta2::Ped_SetPed2(v4, self->Ped_);
      gta2::Ped_sub_403A40(v4);
      gta2::Ped_PedSetObjective(v4, 0, 9999);
      return;
    }
  }
  else
  {
    v11 = v4;
  }
  if ( gta2::Ped_GetLinkedPed(v11) == Ped && gta2::Ped_GetCurrentAction(v4) == 9 )
    gta2::Ped_SetAnimationState(v4, 0, 9999);
}


// 0x00404840: S169::sub_404840
// IDA: S169::sub_404840
// Ghidra: ---
bool gta2::S169_sub_404840(struct S169 *self)
{
  unsigned __int8 Index; // bl
  unsigned __int8 v4; // [esp+8h] [ebp-4h]

  Index = self->Index;
  if ( !Index )
    return self->Ped_->field_10B != 0;
  v4 = 0;
  while ( gta2::Ped_GetPedState(self->Ped_Arr9[v4]) == 10 )
  {
    if ( ++v4 >= Index )
      return 1;
  }
  return 0;
}


// 0x004048a0: S169::sub_4048A0
// IDA: S169::sub_4048A0
// Ghidra: FUN_004048a0
uint gta2::S169_sub_4048A0(int param_1)
{
  struct Ped *self;
  undefined4 in_EAX;
  undefined3 uVar2;
  uint uVar1;
  byte bVar3;
  undefined4 local_4;
  
  bVar3 = 0;
  uVar2 = (undefined3)((uint)in_EAX >> 8);
  local_4 = 0;
  if (*(char *)(param_1 + 0x34) != '\0') {
    do {
      self = *(Ped **)(param_1 + 4 + local_4 * 4);
      uVar1 = gta2::Ped_GetPedState(self);
      if (uVar1 != 10) {
        uVar1 = gta2::Ped_GetPedState(self);
        if (uVar1 != 9) {
          return uVar1 & 0xffffff00;
        }
      }
      uVar2 = (undefined3)(uVar1 >> 8);
      bVar3 = bVar3 + 1;
      local_4 = (uint)bVar3;
    } while (bVar3 < *(byte *)(param_1 + 0x34));
  }
  return CONCAT31(uVar2,1);
}


// 0x00404900: S169::sub_404900
// IDA: S169::sub_404900
// Ghidra: SpawnPoint::FUN_00404900
undefined4 gta2::S169_sub_404900(SpawnPoint *self,Player *param_1)
{
  struct Ped *this_00;
  struct Ped *this_01;
  bool bVar1;
  undefined4 *puVar2;
  S127 *pSVar3;
  int *piVar4;
  undefined3 extraout_var;
  Player **ppPVar5;
  undefined3 extraout_var_00;
  Player *local_c;
  undefined1 local_8 [4];
  int local_4;
  
  this_00 = self->Ped_Array[(uint)param_1 & 0xff];
  gta2::Ped_GetXCoordinate(this_00,&param_1);
  puVar2 = (undefined4 *)&param_1;
  param_1 = (Player *)*puVar2;
  this_01 = self->Ped_;
  gta2::Ped_GetXCoordinate(this_01,&local_c);
  pSVar3 = (S127 *)&local_c;
  puVar2 = (undefined4 *)
           gta2::Player_sub_401B40((Player *)&param_1,(GlassInfo *)local_8,pSVar3);
  param_1 = (Player *)*puVar2;
  gta2::Ped_GetYCoordinate(this_00,&local_8);
  puVar2 = (undefined4 *)&local_8;
  local_c = (Player *)*puVar2;
  gta2::Ped_GetYCoordinate(this_01,&local_8);
  pSVar3 = (S127 *)&local_8;
  puVar2 = (undefined4 *)
           gta2::Player_sub_401B40((Player *)&local_c,(GlassInfo *)&local_4,pSVar3);
  local_c = (Player *)*puVar2;
  piVar4 = gta2::Player_FUN_00403840(local_c,&local_4,(GlassInfo *)&param_1);
  param_1 = (Player *)*piVar4;
  piVar4 = gta2::Player_FUN_00403840(param_1,&local_4,(GlassInfo *)&local_c);
  local_c = (Player *)*piVar4;
  bVar1 = gta2::Car_sub_403800((Car *)&param_1,(int *)&local_c);
  ppPVar5 = &param_1;
  if (CONCAT31(extraout_var,bVar1) == 0) {
    ppPVar5 = &local_c;
  }
  param_1 = *ppPVar5;
  bVar1 = gta2::Car_sub_403800((Car *)&param_1,(int *)(gBufferSize + 0x13f4));
  return CONCAT31(extraout_var_00,CONCAT31(extraout_var_00,bVar1) != 0);
}


// 0x004049f0: S169::sub_4049F0
// IDA: S169::sub_4049F0
// Ghidra: SpawnPoint::FUN_004049f0
bool gta2::S169_sub_4049F0(SpawnPoint *self)
{
  struct Ped *this_00;
  bool bVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  undefined3 extraout_var;
  struct Ped **ppPVar5;
  undefined3 extraout_var_00;
  struct Ped *local_c;
  Ped *local_8 [2];
  
  this_00 = self->Ped_;
  gta2::Ped_GetXCoordinate(this_00,&local_8);
  puVar2 = (undefined4 *)&local_8;
  local_c = (Ped *)*puVar2;
  iVar3 = (int)(intptr_t)gta2::Ped_GetCurrentCar(this_00);
  if (iVar3 == 0) {
    iVar3 = (int)(intptr_t)gta2::Ped_GetVehicle(this_00);
  }
  iVar3 = (int)(intptr_t)*(Car **)((char *)iVar3 + 0x50);
  puVar2 = (undefined4 *)
           gta2::Player_sub_401B40((Player *)&local_c,(GlassInfo *)local_8,
                      (S127 *)(iVar3 + 0x14));
  local_c = (Ped *)*puVar2;
  gta2::Ped_GetYCoordinate(this_00,&local_8);
  puVar2 = (undefined4 *)&local_8;
  local_8[0] = (Ped *)*puVar2;
  puVar2 = (undefined4 *)
           gta2::Player_sub_401B40((Player *)local_8,(GlassInfo *)(local_8 + 1),
                      (S127 *)(iVar3 + 0x18));
  local_8[0] = (Ped *)*puVar2;
  piVar4 = gta2::Player_FUN_00403840((Player *)(local_8 + 1),(int *)(local_8 + 1),
                      (GlassInfo *)&local_c);
  local_c = (Ped *)*piVar4;
  piVar4 = gta2::Player_FUN_00403840((Player *)(local_8 + 1),(int *)(local_8 + 1),
                      (GlassInfo *)local_8);
  local_8[0] = (Ped *)*piVar4;
  bVar1 = gta2::Car_sub_403800((Car *)&local_c,(int *)local_8);
  ppPVar5 = &local_c;
  if (CONCAT31(extraout_var,bVar1) == 0) {
    ppPVar5 = local_8;
  }
  local_8[0] = *ppPVar5;
  bVar1 = gta2::Car_sub_403800((Car *)local_8,(int *)(gBufferSize + 0x13f4));
  return CONCAT31(extraout_var_00,bVar1) == 0;
}


// 0x00404ad0: S169::sub_404AD0
// IDA: S169::sub_404AD0
// Ghidra: FUN_00404ad0
undefined4 gta2::S169_sub_404AD0(int param_1,byte param_2)
{
  struct Ped *self;
  struct Ped *this_00;
  bool bVar1;
  char cVar2;
  undefined4 *puVar3;
  S127 *pSVar4;
  int *piVar5;
  undefined3 extraout_var;
  Player **ppPVar6;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  byte bVar7;
  Player *local_34;
    _DWORD local_30[2];
  unsigned char local_28;
  unsigned char local_24;
  undefined1 local_20 [4];
  undefined1 local_1c [8];
  undefined1 local_14 [4];
  undefined1 local_10 [8];
  int local_8;
  int local_4;
  
  local_30[1] = DAT_005d2e44;
  bVar7 = 0;
  local_24 = 0;
  self = *(Ped **)(param_1 + 4 + (uint)param_2 * 4);
  local_28 = 0;
  if (*(char *)(param_1 + 0x34) != '\0') {
    do {
      this_00 = *(Ped **)(param_1 + 4 + ((uint)local_28 & 0xff) * 4);
      if (bVar7 != param_2) {
        gta2::Ped_GetXCoordinate(self,&local_20);
      puVar3 = (undefined4 *)&local_20;
        local_34 = (Player *)*puVar3;
        gta2::Ped_GetXCoordinate(this_00,&local_1c);
        pSVar4 = (S127 *)&local_1c;
        puVar3 = (undefined4 *)
                 gta2::Player_sub_401B40((Player *)local_34,(GlassInfo *)(local_1c + 4),
                            pSVar4);
        local_34 = (Player *)*puVar3;
        gta2::Ped_GetYCoordinate(self,&local_14);
        puVar3 = (undefined4 *)&local_14;
        local_30[0] = (int)(intptr_t)*puVar3;
        gta2::Ped_GetYCoordinate(this_00,&local_10);
  pSVar4 = (S127 *)&local_10;
        puVar3 = (undefined4 *)
                 gta2::Player_sub_401B40((Player *)local_30,(GlassInfo *)(local_10 + 4),
                            pSVar4);
        local_30[0] = (int)(intptr_t)*puVar3;
        piVar5 = gta2::Player_FUN_00403840((Player *)local_34,&local_8,(GlassInfo *)&local_34)
        ;
        local_34 = (Player *)*piVar5;
        piVar5 = gta2::Player_FUN_00403840((Player *)local_30,&local_4,(GlassInfo *)local_30);
        local_30[0] = (int)(intptr_t)*piVar5;
        bVar1 = gta2::Car_sub_403800((Car *)local_34,(int *)local_30);
        ppPVar6 = &local_34;
        if (CONCAT31(extraout_var,bVar1) == 0) {
          ppPVar6 = (Player **)local_30;
        }
        local_30[0] = (int)(intptr_t)*ppPVar6;
        bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)local_30,(SpriteS1 *)(intptr_t)&local_30[1]);
        if ((CONCAT31(extraout_var_00,bVar1) != 0) &&
           (cVar2 = gta2::FUN_00433b00(), cVar2 != '\0')) {
          local_24 = (unsigned char)bVar7;
          local_30[1] = local_30[0];
        }
      }
      bVar7 = bVar7 + 1;
      local_28 = (unsigned char)bVar7;
    } while (bVar7 < *(byte *)(param_1 + 0x34));
  }
  bVar1 = gta2::Car_IsTrainOrTrainCarriage((Car *)(intptr_t)&local_30[1]);
  if (CONCAT31(extraout_var_01,bVar1) == 0) {
    return 0;
  }
  return *(undefined4 *)(param_1 + 4 + ((uint)local_24 & 0xff) * 4);
}


// 0x00404c90: S169::AddPedToEndOfList
// IDA: S169::AddPedToEndOfList
// Ghidra: ---
void gta2::S169_AddPedToEndOfList(struct S169 *self, Ped *pPed)
{
  char v3; // al

  gta2::Ped_SetAnimationState(pPed, 0, 9999);
  gta2::Ped_PedSetObjective(pPed, 0, 9999);
  gta2::S169_AddPedtoList(self, pPed, self->Index);
  v3 = self->field_36 + 1;
  ++self->Index;
  self->field_36 = v3;
}


// 0x00404ce0: S169::sub_404CE0
// IDA: S169::sub_404CE0
// Ghidra: FUN_00404ce0
void gta2::S169_sub_404CE0(void *self,Ped *param_1)
{
  byte bVar1;
  
  gta2::AIController_GroupAddPed((AIController *)self,*(Ped **)((int)self + 0x2c));
  *(Ped **)((int)self + 0x2c) = param_1;
  gta2::Ped_SetCarId(param_1,99);
  bVar1 = 0;
  param_1 = NULL;
  if (*(char *)((int)self + 0x34) != '\0') {
    do {
      gta2::Ped_SetAnimationState(*(Ped **)((int)self + (int)param_1 * 4 + 4),0,9999)
      ;
      bVar1 = bVar1 + 1;
      param_1 = (Ped *)(uint)bVar1;
    } while (bVar1 < *(byte *)((int)self + 0x34));
  }
  return;
}


// 0x00404d40: S169::sub_404D40
// IDA: S169::sub_404D40
// Ghidra: ---
void gta2::S169_sub_404D40(struct S169 *self, Ped *pPed)
{
  struct Ped *Ped; // ecx
  struct Ped *v5; // ebx
  unsigned int v6; // eax
  struct Ped *v7; // ebp
  bool DeadPed; // al
  S169 *v9; // ecx
  S169 v24; // ecx
  struct Ped *v10; // ebx
  int CurrentAction; // eax
  bool Occupation; // zf
  unsigned __int8 Index; // al
  unsigned __int8 v14; // dl
  struct Ped *v15; // ecx
  unsigned int Flags; // eax
  unsigned __int8 pPeda; // [esp+14h] [ebp+4h]

  Ped = self->Ped_;
  if ( pPed != Ped )
  {
    v14 = 0;
    pPeda = 0;
    if ( self->Index )
    {
      while ( self->Ped_Arr9[pPeda] != pPed )
      {
        pPeda = ++v14;
        if ( v14 >= self->Index )
          return;
      }
      v15 = self->Ped1[self->Index];
      self->Ped_Arr9[pPeda] = v15;
      gta2::Ped_SetCarId(v15, pPeda);
      self->Ped1[self->Index] = pPed;
      gta2::Ped_SetCarId(pPed, self->Index - 1);
      if ( gta2::Ped_GetCurrentOccupation(pPed) != UNKNOWN_OCUPATION_23 )
      {
        gta2::Ped_SetDefault(self->Ped1[self->Index]);
        self->Ped1[self->Index] = 0;
        if ( pPed->field_1D4 == (SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT) )
        {
          Flags = pPed->PositionX1;
          BYTE1(Flags) |= 4u;
          pPed->PositionX1 = Flags;
        }
      }
      --self->Index;
    }
    return;
  }
  if ( gta2::Ped_IsSearchType(Ped, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
    return;
  v5 = self->Ped_;
  if ( gta2::Ped_GetPedState(v5) == 9 && v5->field_1D4 == (SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT) )
  {
    v6 = v5->PositionX1;
    BYTE1(v6) |= 4u;
    v5->PositionX1 = v6;
  }
  v7 = self->Ped_Arr9[0];
  if ( !v7 )
  {
    v9 = self;
    goto LABEL_15;
  }
  DeadPed = gta2::Ped_GetDeadPed(self->Ped_Arr9[0]);
  v9 = self;
  if ( DeadPed )
  {
LABEL_15:
    gta2::S169_sub_403BE0(v9);
    return;
  }
  gta2::S169_sub_404120(self, 0);
  v10 = self->Ped_;
  CurrentAction = gta2::Ped_GetCurrentAction(v10);
  gta2::Ped_sub_433650(v10, CurrentAction == 0);
  Occupation = gta2::Ped_GetCurrentOccupation(pPed) == UNKNOWN_OCUPATION_23;
  Index = self->Index;
  if ( Occupation )
  {
    if ( Index )
    {
      self->Ped_Arr9[self->Index] = v7;
      gta2::Ped_SetCarId(self->Ped_Arr9[self->Index], self->field_36 - 1);
      gta2::S169_sub_4045D0(self);
      return;
    }
  }
  else if ( Index )
  {
    self->Ped_Arr9[self->Index] = 0;
  }
  gta2::S169_sub_4045D0(self);
}


// 0x00404ef0: S169::sub_404EF0
// IDA: S169::sub_404EF0
// Ghidra: ---
void gta2::S169_sub_404EF0(struct S169 *self, Ped *a2)
{
  S169 *pS169Link; // ebx
  char v5; // bl
  struct Ped *v6; // eax
  struct Ped *v7; // esi
  char Index_1; // al
  struct Ped *pPed2; // esi
  struct Ped *v10; // edi
  struct Ped *v11; // ecx
  signed __int16 v12; // ax
  int v13; // edi
  struct Ped *v14; // ecx
  struct Ped *v15; // ecx
  bool v16; // zf
  struct Ped *Ped; // esi
  struct Ped *pPed; // ecx
  struct Ped *v19; // ecx
  Player *X; // [esp+10h] [ebp-8h]
  Player *Xa; // [esp+10h] [ebp-8h]
  __int16 a2a[2]; // [esp+14h] [ebp-4h] BYREF
  struct Ped **v23; // [esp+1Ch] [ebp+4h]
  struct Ped **pPed1; // [esp+1Ch] [ebp+4h]

  self->field_30 = 1;
  pS169Link = *(S169 **)(void *)&a2->field_103;
  if ( pS169Link )
  {
    Index_1 = self->Index - 1;
    if ( Index_1 < 0 )
    {
LABEL_38:
      Ped = self->Ped_;
      if ( !gta2::Ped_IsCrouching(Ped) && !gta2::Ped_IsCrouching(pS169Link->Ped_) )
      {
        if ( !gta2::Ped_IsSearchType(Ped, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
        {
          pPed = self->Ped_;
          if ( (pPed->PositionX1 & 0x8000000) == 0 )
          {
            if ( pPed->GameObject2 )
            {
              gta2::Ped_SetAnimationState(pPed, 20, 9999);
              gta2::Ped_SetPed2(self->Ped_, pS169Link->Ped_);
              gta2::Ped_sub_403950(self->Ped_);
            }
          }
        }
        if ( !gta2::Ped_IsSearchType(pS169Link->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
        {
          v19 = pS169Link->Ped_;
          if ( (v19->PositionX1 & 0x8000000) == 0 )
          {
            if ( v19->GameObject2 )
            {
              gta2::Ped_SetAnimationState(v19, 20, 9999);
              gta2::Ped_SetPed2(pS169Link->Ped_, self->Ped_);
              gta2::Ped_sub_403950(pS169Link->Ped_);
            }
          }
        }
      }
      return;
    }
    pPed1 = &self->Ped_Arr9[Index_1];
    Xa = (Player *)self->Index;
    while ( 1 )
    {
      pPed2 = *pPed1;
      if ( gta2::Ped_IsCrouching(*pPed1) || (pPed2->PositionX1 & 0x8000000) != 0 || !pPed2->GameObject2 )
        goto LABEL_37;
      v10 = gta2::S169_sub_404450(pS169Link);
      if ( !v10 )
        break;
      gta2::Ped_SetAnimationState(pPed2, 20, 9999);
      gta2::Ped_SetPed2(pPed2, v10);
      gta2::Ped_sub_403950(pPed2);
      if ( !gta2::Ped_IsInCar(v10) )
      {
        gta2::Ped_SetAnimationState(v10, 20, 9999);
        gta2::Ped_SetPed2(v10, pPed2);
        v11 = v10;
LABEL_36:
        gta2::Ped_sub_403950(v11);
      }
LABEL_37:
      v16 = Xa == (Player *)1;
      --pPed1;
      Xa = (Player *)((char *)Xa - 1);
      if ( v16 )
        goto LABEL_38;
    }
    *(_DWORD *)&a2a[0] = pS169Link->Index + 1;
    v12 = gta2::Random_Random(&gRandom, (short *)&a2a[0]);
    v13 = v12;
    if ( v12 == pS169Link->Index )
    {
      v14 = pS169Link->Ped_;
      if ( !v14 || gta2::Ped_GetPedState(v14) == 9 )
        goto LABEL_37;
      gta2::Ped_SetAnimationState(pPed2, 20, 9999);
      gta2::Ped_SetPed2(pPed2, pS169Link->Ped_);
    }
    else
    {
      v15 = pS169Link->Ped_Arr9[v12];
      if ( !v15 || gta2::Ped_GetPedState(v15) == 9 )
        goto LABEL_37;
      gta2::Ped_SetAnimationState(pPed2, 20, 9999);
      gta2::Ped_SetPed2(pPed2, pS169Link->Ped_Arr9[v13]);
    }
    v11 = pPed2;
    goto LABEL_36;
  }
  v5 = self->Index - 1;
  LOBYTE(X) = v5;
  if ( v5 >= 0 )
  {
    v23 = &self->Ped_Arr9[v5];
    do
    {
      v6 = *v23;
      if ( gta2::Ped_IsCrouching(*v23) || (v6->PositionX1 & 0x8000000) != 0 || !v6->GameObject2 )
        goto LABEL_13;
      if ( gta2::S169_sub_404900((SpawnPoint *)self, X) )
      {
        gta2::Ped_SetAnimationState(v6, 7, 9999);
        gta2::Ped_SetPed2(v6, self->Ped_);
      }
      else
      {
        if ( gta2::Ped_GetCurrentAction(self->Ped_) == 35 && !gta2::S169_sub_4049F0((SpawnPoint *)self) )
          goto LABEL_13;
        gta2::Ped_SetAnimationState(v6, 20, 9999);
        gta2::Ped_SetPed2(v6, a2);
      }
      gta2::Ped_sub_403950(v6);
LABEL_13:
      LOBYTE(X) = --v5;
      --v23;
    }
    while ( v5 >= 0 );
  }
  if ( !gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
  {
    v7 = self->Ped_;
    if ( !gta2::Ped_IsCrouching(v7) && !gta2::Ped_IsInCar(v7) && (v7->PositionX1 & 0x8000000) == 0 && !v7->field_10B )
    {
      gta2::Ped_SetAnimationState(v7, 20, 9999);
      gta2::Ped_SetPed2(self->Ped_, a2);
      gta2::Ped_sub_403950(self->Ped_);
    }
  }
}
















































