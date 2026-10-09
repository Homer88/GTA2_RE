#include "gta2_shim.h"

// Module: other, Class: Weapon
// Functions: 45
// Source: unified (IDA+Ghidra)

// 0x004828c0: Weapon::sub_4828C0
// IDA: Weapon::sub_4828C0
// Ghidra: FUN_004828c0
void * gta2::Weapon_sub_4828C0(void *self,int *param_1)
{
  UseAmmo(self,param_1);
  UseAmmo((void *)((int)self + 4),param_1 + 1);
  return self;
}


// 0x004a4f80: Weapon::GetArmo
// IDA: Weapon::GetArmo
// Ghidra: ---
bool gta2::Weapon_GetArmo(struct Weapon *self)
{
  return self->Ammo != 0;
}


// 0x004a4f90: Weapon::GiveWeaponInfiniti
// IDA: Weapon::GiveWeaponInfiniti
// Ghidra: ---
void gta2::Weapon_GiveWeaponInfiniti(struct Weapon *self)
{
  self->Ammo = -1;
}


// 0x004a4fa0: Weapon::NotInfiniti
// IDA: Weapon::NotInfiniti
// Ghidra: ---
bool gta2::Weapon_NotInfiniti(struct Weapon *self)
{
  return self->Ammo == 0xFFFF;
}


// 0x004a4fb0: Weapon::GetDisplayAmmo
// IDA: Weapon::GetDisplayAmmo
// Ghidra: ---
char gta2::Weapon_GetDisplayAmmo(struct Weapon *self)
{
  int v2; // eax

  if ( gta2::Weapon_NotInfiniti(self) )
    LOBYTE(v2) = -1;
  else
    return (self->Ammo + 9) / 10;
  return v2;
}


// 0x004a4fe0: Weapon::GetAmmo
// IDA: Weapon::GetAmmo
// Ghidra: ---
unsigned __int16 gta2::Weapon_GetAmmo(struct Weapon *self)
{
  return self->Ammo;
}


// 0x004cc7d0: Weapon::Weapon
// IDA: Weapon::Weapon
// Ghidra: ---
void gta2::Weapon_Weapon(struct Weapon *self)
{
  self->Ammo = 0;
  self->Ped_ = 0;
  self->Car = 0;
  self->TimeToReload = 0;
  self->SMG = 0;
  self->NextWeapon = 0;
  self->TypeWeapon = Pistolet;
  self->short = 0;
  self->field_8 = 0;
  self->field_C = -1;
  self->field_20 = 0;
  self->field_21 = 0;
  self->field_2C = 0;
  self->SoundWeapon = 0;
}


// 0x004cc810: Weapon::InitializeWeapon
// IDA: Weapon::InitializeWeapon
// Ghidra: ---
int gta2::Weapon_InitializeWeapon(struct Weapon *self)
{
  int result; // eax
  int SoundWeapon; // ecx

  result = 0;
  SoundWeapon = self->SoundWeapon;
  self->Ped_ = 0;
  self->Car = 0;
  self->TypeWeapon = Pistolet;
  self->Ammo = 0;
  self->TimeToReload = 0;
  self->SMG = 0;
  self->field_21 = 0;
  self->field_8 = 0;
  self->field_C = -1;
  self->field_20 = 0;
  self->field_2C = 0;
  if ( !SoundWeapon && !skip_audio )
  {
    result = gta2::DMAudio_sub_410750(&gDMAudio, (CameraOrPhysics *)self);
    self->SoundWeapon = result;
  }
  return result;
}


// 0x004cc860: Weapon::SetAmmo
// IDA: Weapon::SetAmmo
// Ghidra: ---
void gta2::Weapon_SetAmmo(struct Weapon *self, byte pAmmo)
{
  self->Ammo = 10 * pAmmo;
}


// 0x004cc880: Weapon::sub_4CC880
// IDA: Weapon::sub_4CC880
// Ghidra: ---
bool gta2::Weapon_sub_4CC880(struct Weapon *self)
{
  return self->Ammo == 10 * byte_575904[self->TypeWeapon];
}


// 0x004cc8c0: Weapon::IsCarWeapon
// IDA: Weapon::IsCarWeapon
// Ghidra: ---
bool gta2::Weapon_IsCarWeapon(struct Weapon *self)
{
  bool result; // al

  switch ( self->TypeWeapon )
  {
    case CAR_BOMB:
    case CAR_OIL:
    case CAR_MINE:
    case WATER_CANNON:
    case CAR_BOMB_INSTANT:
      result = 0;
      break;
    case CAR_MACHINE_GUN:
    case TANK_MAIN_GUN:
    case FIRE_TRUCK_GUN:
    case ARMY_GUN_JEEP:
      result = 1;
      break;
    default:
      result = *(_DWORD *)&self->Ped_->field_10B == 0;
      break;
  }
  return result;
}


// 0x004cc910: Weapon::FUN_004cc910
// IDA: sub_4CC910
// Ghidra: Weapon::FUN_004cc910
byte gta2::Weapon_FUN_004cc910(struct Weapon *self)
{
  switch(self->TypeWeapon) {
  case CAR_BOMB:
  case CAR_OIL:
  case CAR_MINE:
  case TANK_MAIN_GUN:
  case CAR_BOMB_INSTANT:
    return 0;
  default:
    return 1;
  }
}


// 0x004cc950: Weapon::sub_4CC950
// IDA: Weapon::sub_4CC950
// Ghidra: ---
char gta2::Weapon_sub_4CC950(struct Weapon *self)
{
  char result; // al

  switch ( self->TypeWeapon )
  {
    case ROCKET:
    case Molotov:
    case CAR_BOMB:
    case CAR_MINE:
    case TANK_MAIN_GUN:
      result = 1;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


// 0x004cca00: Weapon::SetTypeWeapon_0
// IDA: Weapon::SetTypeWeapon_0
// Ghidra: ---
void gta2::Weapon_SetTypeWeapon_0(struct Weapon *self, WeaponType a2)
{
  self->TypeWeapon = a2;
}


// 0x004cca10: Weapon::SetPed
// IDA: Weapon::SetPed
// Ghidra: ---
void gta2::Weapon_SetPed(struct Weapon *self, Ped *pPed)
{
  self->Ped_ = pPed;
}


// 0x004cca20: Weapon::SetCar
// IDA: Weapon::SetCar
// Ghidra: ---
void gta2::Weapon_SetCar(struct Weapon *self, Car *pCar)
{
  self->Car = pCar;
}


// 0x004cca30: Weapon::Decrement10Ammo
// IDA: Weapon::Decrement10Ammo
// Ghidra: ---
void gta2::Weapon_Decrement10Ammo(struct Weapon *self)
{
  unsigned __int16 v2; // si

  *(_DWORD *)&v2 = self->Ammo - 10;
  if ( !gta2::Weapon_NotInfiniti(self) )
  {
    if ( *(int *)&v2 < 0 )
      v2 = 0;
    self->Ammo = v2;
  }
}


// 0x004cca60: Weapon::Decrement1Ammo
// IDA: Weapon::Decrement1Ammo
// Ghidra: ---
void gta2::Weapon_Decrement1Ammo(struct Weapon *self)
{
  if ( !gta2::Weapon_NotInfiniti(self) )
    --self->Ammo;
}


// 0x004cca80: Weapon::Set_4CCA80
// IDA: Weapon::Set_4CCA80
// Ghidra: ---
void gta2::Weapon_Set_4CCA80(struct Weapon *self, char a2)
{
  self->field_2C = a2;
}


// 0x004ccb10: Weapon::Weapon_dec
// IDA: Weapon::Weapon_dec
// Ghidra: ---
int * gta2::Weapon_Weapon_dec(struct Weapon *self)
{
  int *result; // eax

  result = (int *)self->SoundWeapon;
  self->Ped_ = 0;
  self->NextWeapon = 0;
  self->Car = 0;
  self->field_8 = 0;
  if ( result )
  {
    result = (int *)gta2::DMAudio_DMAudio_des(&gDMAudio, (cameraPosTarget *)result);
    self->SoundWeapon = 0;
  }
  return result;
}


// 0x004ccb40: Weapon::sub_4CCB40
// IDA: Weapon::sub_4CCB40
// Ghidra: ---
Weapon * gta2::Weapon_sub_4CCB40(struct Weapon *self)
{
  Weapon *result; // eax

  gta2::Weapon_InitializeWeapon(self);
  result = (Weapon *)self->SoundWeapon;
  self->field_8 = 0;
  if ( result )
  {
    result = (Weapon *)gta2::DMAudio_DMAudio_des(&gDMAudio, (cameraPosTarget *)result);
    self->SoundWeapon = 0;
  }
  return result;
}


// 0x004ccb70: Weapon::sub_4CCB70
// IDA: Weapon::sub_4CCB70
// Ghidra: ---
char gta2::Weapon_sub_4CCB70(struct Weapon *self, unsigned __int8 pAmmo)
{
  int pAmmo_1; // esi
  int v4; // ecx
  int v6; // eax

  pAmmo_1 = 10 * byte_575904[self->TypeWeapon];
  if ( gta2::Weapon_NotInfiniti(self) )
    return 0;
  HIWORD(v4) = 0;
  if ( self->Ammo == pAmmo_1 )
    return 0;
  LOWORD(v4) = self->Ammo;
  v6 = v4 + 10 * pAmmo;
  if ( v6 <= pAmmo_1 )
    self->Ammo = v6;
  else
    self->Ammo = pAmmo_1;
  return 1;
}


// 0x004cd000: Weapon::TimeToReload
// IDA: Weapon::TimeToReload
// Ghidra: ---
char gta2::Weapon_TimeToReload(struct Weapon *self)
{
  struct Ped *Ped; // eax
  struct Player *Player; // ecx

  Ped = self->Ped_;
  Player = Ped->isPlayer;
  if ( Player )
  {
    LOBYTE(Ped) = gta2::Player_GetPowerUp(Player, 8);
    if ( (_BYTE)Ped )
      self->TimeToReload = (unsigned __int8)self->TimeToReload >> 1;
  }
  return (char)Ped;
}


// 0x004cd020: Weapon::sub_4CD020
// IDA: Weapon::sub_4CD020
// Ghidra: Weapon::FUN_004cd020
void gta2::Weapon_sub_4CD020(struct Weapon *self)
{
  struct Ped *this_00;
  bool bVar1;
  char cVar2;
  S127 *pSVar3;
  SpawnPoint *pSVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int *piVar7;
  void *pvVar8;
  undefined2 *puVar9;
  undefined3 extraout_var;
  int *piVar10;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int iVar11;
  SpriteS1 *pSVar12;
  SpriteS1 *pSVar13;
  uint uVar14;
  struct Player *pPVar15;
  GlassInfo *pGVar16;
  undefined4 uVar17;
  undefined1 local_40 [4];
  undefined1 local_3c [12];
  undefined1 local_30 [4];
  undefined1 local_2c [8];
  undefined1 local_24 [8];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [8];
  int local_c;
  undefined1 local_8 [8];
  struct Ped *pPed;
  SpriteS1 *pS38;
  
  pS38 = gObject->SpriteS1_;
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)(local_3c + 4))
  ;
  pPed = self->Ped_;
  pSVar3 = (S127 *)gta2::Ped_GetYCoordinate(pPed, (int *)local_30);
  pGVar16 = (GlassInfo *)(local_3c + 8);
  pSVar4 = (SpawnPoint *)gta2::Ped_GetYCoordinate(pPed->ped3,(int)local_3c);
  puVar5 = (undefined4 *)gta2::Player_sub_401B40(pSVar4,pGVar16,pSVar3);
  pSVar3 = (S127 *)gta2::Ped_GetXCoordinate(pPed,(int)local_2c);
  pGVar16 = (GlassInfo *)(local_2c + 4);
  pSVar4 = (SpawnPoint *)gta2::Ped_GetXCoordinate(pPed->ped3,(int)local_24);
  puVar6 = (undefined4 *)gta2::Player_sub_401B40(pSVar4,pGVar16,pSVar3);
  String_ParseLine(local_8,puVar6,puVar5);
  FUN_004637b0(&PTR_005e6874);
  pPed = self->Ped_;
  pSVar3 = (S127 *)gta2::Ped_GetXCoordinate(pPed,(int)local_24);
  pGVar16 = (GlassInfo *)(local_24 + 4);
  pSVar4 = (SpawnPoint *)gta2::Ped_GetXCoordinate(pPed->ped3,(int)local_1c);
  piVar7 = (int *)gta2::Player_sub_401B40(pSVar4,pGVar16,pSVar3);
  pSVar3 = (S127 *)gta2::Ped_GetYCoordinate(pPed, (int *)local_18);
  pGVar16 = (GlassInfo *)local_14;
  pSVar4 = (SpawnPoint *)gta2::Ped_GetYCoordinate(pPed->ped3,(int)&local_c);
  pvVar8 = gta2::Player_sub_401B40(pSVar4,pGVar16,pSVar3);
  puVar9 = gta2::Player_FUN_0040e8d0((Player *)local_40,(undefined2 *)local_40,pvVar8,piVar7);
  local_3c._4_2_ = *puVar9;
  piVar7 = gta2::Player_sub_41E260((Player *)local_8,&local_c);
  local_3c._0_4_ = *piVar7;
  bVar1 = gta2::Car_sub_403800((Car *)local_3c,(int *)&DAT_006739e0);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    self->Ped_->ped3 = NULL;
    return;
  }
  pPed = self->Ped_;
  piVar7 = (int *)gta2::Ped_GetPositionZ(pPed,(int)&local_c);
  local_40 = (undefined1  [4])gta2::Ped_GetYCoordinate(pPed, (int *)local_14);
  piVar10 = (int *)gta2::Ped_GetXCoordinate(pPed,(int)local_18);
  gta2::SpriteS1_sub_420600((Sprite *)pS38,*piVar10,(int)*(Player **)local_40,*piVar7)
  ;
  gta2::SpriteS1_SetRotation((Sprite *)pS38,(short)local_3c._4_4_);
  gta2::SpriteS1_sub_4BCB90((Sprite *)pS38,_DAT_0067395c,_DAT_0067395c,_DAT_0067395c);
  bVar1 = gta2::Car_IsTrainOrTrainCarriage((Car *)local_3c,(Car *)&DAT_00673a4c);
  if (CONCAT31(extraout_var_00,bVar1) == 0) {
    local_40 = (undefined1  [4])_DAT_00673a4c;
    pPVar15 = _DAT_00673a4c;
  }
  else {
    piVar7 = (int *)gta2::sub_401B90((Player *)local_3c,&local_c,(int *)&DAT_0067395c)
    ;
    local_40 = (undefined1  [4])*piVar7;
    piVar7 = (int *)gta2::sub_401B90((Player *)local_3c,&local_c,(int *)local_40);
    pPVar15 = (Player *)*piVar7;
  }
  bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)local_40,(SpriteS1 *)&DAT_006739e4);
  if (CONCAT31(extraout_var_01,bVar1) != 0) {
    local_40 = (undefined1  [4])_DAT_006739e4;
    pPVar15 = (Player *)local_3c._0_4_;
  }
  local_3c._0_4_ = pPVar15;
  gta2::sub_41FC20((CarSystemManager *)local_30,local_3c + 4,(GlassInfo *)local_3c,
             (Ped *)local_30,(Ped *)(local_3c + 8));
  local_3c[4] = 1;
  iVar11 = DecoderFloat(local_40);
  if (0 < iVar11) {
    do {
      FUN_00469570(&local_c,pS38->Matrix3DArray[0].PositionX,
                   pS38->Matrix3DArray[0].PositionY,
                   pS38->Matrix3DArray[0].PositionZ);
      pSVar12 = gta2::S202_sub_401B20((Point2D *)&pS38->Matrix3DArray[0].PositionY,
                           (SpriteS1 *)local_14,(S127 *)(local_3c + 8));
      pSVar13 = gta2::S202_sub_401B20((Point2D *)&pS38->Matrix3DArray[0].PositionX,
                           (SpriteS1 *)local_18,(S127 *)local_30);
      gta2::SpriteS1_sub_420600((Sprite *)pS38,(int)pSVar13->FirstElement,
                          (int)pSVar12->FirstElement,
                          pS38->Matrix3DArray[0].PositionZ);
      cVar2 = FUN_004bd610();
      if (cVar2 != '\0') break;
      pSVar12 = gta2::SpriteS1_sub_4BDFE0(pS38,2);
      if (pSVar12 != NULL) {
        iVar11 = gta2::SpriteS1_getSpriteType(pSVar12);
        if (iVar11 == 2) {
          gta2::Weapon_SetWeapon(self->Ped_->SelectedWeapon,SNG);
          self->Ped_->ped3 = NULL;
          return;
        }
        if (iVar11 == 3) {
          pPed = self->Ped_;
          this_00 = (Ped *)(pSVar12->Matrix3DArray[0].Car)->PhysicsBitmask;
          if ((this_00 != pPed->ped3) && (this_00 != pPed)) {
            iVar11 = gta2::Ped_GetPedState(this_00);
            if ((iVar11 < 8) || (9 < iVar11)) {
              gta2::Weapon_SetWeapon(pPed->SelectedWeapon,SNG);
            }
          }
        }
      }
      local_3c[4] = local_3c[4] + '\x01';
      iVar11 = DecoderFloat(local_40);
    } while ((int)(local_3c._4_4_ & 0xff) <= iVar11);
  }
  gta2::sub_433BF0(self->Ped_->ped3,self->Ped_);
  self->Ped_->ped3->PedID = self->Ped_->ID;
  pPed = self->Ped_->ped3;
  uVar14._0_1_ = pPed->CurrentAction;
  uVar14._1_1_ = pPed->DamageState;
  uVar14._2_1_ = pPed->uns60;
  uVar14._3_1_ = pPed->uns61;
  uVar14 = uVar14 | 0x100;
  pPed->CurrentAction = (char)uVar14;
  pPed->DamageState = (char)(uVar14 >> 8);
  pPed->uns60 = (char)(uVar14 >> 0x10);
  pPed->uns61 = (char)(uVar14 >> 0x18);
  if (self->Ped_->field130_0x28c == 1) {
    gPolice->Ped_ = self->Ped_;
  }
  pPed = self->Ped_;
  puVar5 = (undefined4 *)gta2::Ped_GetPositionZ(pPed,(int)&local_c);
  puVar6 = (undefined4 *)
           gta2::SpriteS1_sub_4207B0(*(SpriteS1 **)&pPed->GameObject_->AIState,local_8);
  uVar17 = *puVar5;
  gta2::SpriteS1_sub_4207B0(*(SpriteS1 **)&pPed->ped3->GameObject_->AIState,local_14);
  FUN_004ccbd0(*puVar6,puVar6[1],uVar17);
  return;
}


// 0x004cd400: Weapon::sub_4CD400
// IDA: Weapon::sub_4CD400
// Ghidra: Weapon::FUN_004cd400
void gta2::Weapon_sub_4CD400(struct Weapon *self,char param_1)
{
  byte bVar1;
  struct Ped *pPVar2;
  struct Car *pCar;
  
  pPVar2 = gta2::Car_GetDriver(self->Car);
  self->Ped_ = pPVar2;
  gta2::Weapon_Set_4CCA80(self,1);
  gta2::Weapon_Decrement10Ammo(self);
  pCar = self->Car;
  bVar1 = gta2::Car_sub_41E460(pCar);
  if (bVar1 != 0) {
    gta2::Car_FUN_004295c0(*(Car **)((int)pCar->S___ + 0xc),param_1);
    gta2::Car_sub_427B20(self->Car);
    return;
  }
  gta2::Car_FUN_004295c0(pCar,param_1);
  return;
}


// 0x004cd460: Weapon::sub_4CD460
// IDA: Weapon::sub_4CD460
// Ghidra: ---
void gta2::Weapon_sub_4CD460(struct Weapon *self)
{
  char *v2; // esi
  _DWORD *v3; // edi
  S202 *v4; // eax
  SpriteS1 *v5; // eax
  SpriteS1 *v6; // eax
  _DWORD *v7; // eax
  S122 *v8; // eax
  struct Player **v9; // eax
  int v10; // edi
  int v11; // ebx
  int v12; // ecx
  struct Player *pPlayer; // [esp+10h] [ebp-1Ch] BYREF
  int a4; // [esp+14h] [ebp-18h]
  int a2; // [esp+18h] [ebp-14h] BYREF
  int a3; // [esp+1Ch] [ebp-10h]
  int v17[2]; // [esp+20h] [ebp-Ch] BYREF
  int WindowHeight; // [esp+28h] [ebp-4h] BYREF

  v2 = (char *)gta2::Turrel_sub_41FC70((Arsenal *)self->Car);
  v3 = (_DWORD *)*((_DWORD *)v2 + 3);
  v4 = (S202 *)gta2::sub_447E10(v3, &WindowHeight);
  v5 = gta2::S202_sub_401B20(v4, (SpriteS1 *)v17, (PublicTransport *)&unk_673BA4);
  v6 = gta2::JustCopyByPtrAtoC(v5, (SpriteS1 *)&a2);
  a3 = *(_DWORD *)gta2::sub_401B90(v6, &pPlayer, &unk_673AC8);
  if ( (gta2::Weapon_GetDisplayAmmo(self) & 1) != 0 )
    a2 = (int)gta2::JustCopyByPtrAtoC(&dword_673B9C, (SpriteS1 *)&WindowHeight)->FirstElement;
  else
    a2 = dword_673B9C;
  gta2::Tango_sub_40F6B0((Tango *)&a2, (S900 *)v2);
  v7 = gta2::SpriteS1_sub_4207B0((SpriteS1 *)v2, v17);
  gta2::Tango_sub_40F680((Tango *)&a2, (int)v7);
  pPlayer = (Player *)2;
  v8 = (S122 *)gta2::sub_492170(v3, v17);
  gta2::S122_sub_401BF0(v8, (int)&WindowHeight, (int)&pPlayer);
  pPlayer = *v9;
  gta2::Player_sub_401B40((Player *)(v2 + 28), (S202 *)&WindowHeight, (int)&pPlayer);
  pPlayer = (Player *)gta2::S202_sub_401B20((S202 *)(v2 + 28), (SpriteS1 *)&WindowHeight, (PublicTransport *)&pPlayer)->FirstElement;
  if ( gta2::Player_sub_40CE70((Player *)&pPlayer, &unk_673984) )
    gta2::Player_sub_401B40((Player *)&unk_673984, (S202 *)&WindowHeight, (int)&unk_6739B4);
  v10 = a3;
  v11 = a2;
  if ( gta2::MapRelatedStruct_sub_469DC0(gMapRelatedStruct, (int *)a2, (SpriteS1 *)a3) )
  {
    LOWORD(v12) = *(_WORD *)v2;
    gta2::Object_SpawnObject(gObject, 8, v11, v10, a4, v12);
    gta2::Weapon_Decrement10Ammo(self);
    gta2::Weapon_Set_4CCA80(self, 1);
  }
}


// 0x004cd5f0: Weapon::sub_4CD5F0
// IDA: Weapon::sub_4CD5F0
// Ghidra: ---
void gta2::Weapon_sub_4CD5F0(struct Weapon *self)
{
  struct Car *Car; // esi
  char *v3; // esi
  _DWORD *v4; // ebx
  S202 *v5; // eax
  SpriteS1 *v6; // eax
  S202 *v7; // eax
  SpriteS1 *v8; // eax
  _DWORD *v9; // eax
  S122 *v10; // eax
  int *v11; // eax
  int v12; // ebx
  int v13; // ebp
  int v14; // eax
  EventHandler *pS63; // esi
  byte v16; // al
  int WindowWidth[2]; // [esp+10h] [ebp-24h] BYREF
  char v18; // [esp+18h] [ebp-1Ch] BYREF
  _BYTE v19[4]; // [esp+1Ch] [ebp-18h] BYREF
  int a2; // [esp+20h] [ebp-14h] BYREF
  int a3; // [esp+24h] [ebp-10h]
  int v22[2]; // [esp+28h] [ebp-Ch] BYREF
  int WindowHeight; // [esp+30h] [ebp-4h] BYREF

  Car = self->Car;
  self->Ped_ = gta2::Car_GetDriver(Car);
  v3 = (char *)gta2::Turrel_sub_41FC70((Arsenal *)Car);
  v4 = (_DWORD *)*((_DWORD *)v3 + 3);
  v5 = (S202 *)gta2::sub_447E10(v4, v22);
  v6 = gta2::S202_sub_401B20(v5, (SpriteS1 *)&a2, (PublicTransport *)&unk_673AD4);
  v7 = (S202 *)gta2::sub_401B90(v6, v19, &unk_673AC8);
  v8 = gta2::S202_sub_401B20(v7, (SpriteS1 *)&v18, (PublicTransport *)&unk_673A90);
  a3 = (int)gta2::JustCopyByPtrAtoC(v8, (SpriteS1 *)WindowWidth)->FirstElement;
  a2 = unk_673A4C;
  gta2::Tango_sub_40F6B0((Tango *)&a2, (S900 *)v3);
  v9 = gta2::SpriteS1_sub_4207B0((SpriteS1 *)v3, v22);
  gta2::Tango_sub_40F680((Tango *)&a2, (int)v9);
  WindowWidth[0] = 2;
  v10 = (S122 *)gta2::sub_492170(v4, v22);
  gta2::S122_sub_401BF0(v10, (int)&WindowHeight, (int)WindowWidth);
  WindowWidth[0] = *v11;
  gta2::Player_sub_401B40((Player *)(v3 + 28), (S202 *)&WindowHeight, (int)WindowWidth);
  WindowWidth[0] = (int)gta2::S202_sub_401B20((S202 *)(v3 + 28), (SpriteS1 *)&WindowHeight, (PublicTransport *)WindowWidth)->FirstElement;
  if ( gta2::Player_sub_40CE70((Player *)WindowWidth, &unk_673984) )
    gta2::Player_sub_401B40((Player *)&unk_673984, (S202 *)&WindowHeight, (int)&unk_6739B4);
  v12 = a3;
  v13 = a2;
  if ( gta2::MapRelatedStruct_sub_469DC0(gMapRelatedStruct, (int *)a2, (SpriteS1 *)a3) )
  {
    LOWORD(v14) = *(_WORD *)v3;
    pS63 = gta2::Object_SpawnObject(gObject, 10, v13, v12, WindowWidth[1], v14);
    v16 = gta2::sub_420B50(self->Ped_);
    gta2::S63_sub_482790(pS63, v16);
    gta2::Weapon_Decrement10Ammo(self);
    gta2::Weapon_Set_4CCA80(self, 1);
  }
}


// 0x004cda90: Weapon::sub_4CDA90
// IDA: Weapon::sub_4CDA90
// Ghidra: ---
int gta2::Weapon_sub_4CDA90(struct Weapon *self, int a1, void *a2)
{
  SpriteS1 *S202; // edi
  EventHandler *v5; // eax
  struct Ped *Ped; // ebx
  EventHandler *pS63; // esi
  int XCoordinate; // eax
  SpriteS1 *v9; // eax
  S202 *v10; // eax
  int v11; // eax
  SpriteS1 *v12; // eax
  S202 *v13; // eax
  int *v14; // eax
  CarSystemManager *v15; // ecx
  int SpriteType; // eax
  byte v17; // al
  byte v18; // al
  int result; // eax
  PublicTransport *v20; // [esp-4h] [ebp-2Ch]
  PublicTransport *v21; // [esp-4h] [ebp-2Ch]
  _BYTE v22[4]; // [esp+10h] [ebp-18h] BYREF
  char v23; // [esp+14h] [ebp-14h] BYREF
  int X; // [esp+18h] [ebp-10h] BYREF
  _BYTE v25[4]; // [esp+1Ch] [ebp-Ch] BYREF
  char v26; // [esp+20h] [ebp-8h] BYREF
  int Y; // [esp+24h] [ebp-4h] BYREF
  Player a3; // [esp+34h] [ebp+Ch] BYREF

  S202 = (SpriteS1 *)gObject->S63[1].S202;
  v5 = gta2::Object_SpawnObject(gObject, a1, (int)a2, (int)a3.CurrentPlayer, (int)a3.Player, *(int *)&a3.Rotate);
  Ped = self->Ped_;
  pS63 = v5;
  XCoordinate = gta2::Ped_GetXCoordinate(Ped, (int)&a3.Rotate);
  v9 = gta2::Player_sub_401B40((Player *)&a2, (S202 *)v22, XCoordinate);
  v20 = (PublicTransport *)gta2::sub_401B90(v9, &a2, &unk_673AC8);
  v10 = (S202 *)gta2::Ped_GetXCoordinate(Ped, (int)&X);
  a2 = gta2::S202_sub_401B20(v10, (SpriteS1 *)&v23, v20)->FirstElement;
  gta2::Ped_GetYCoordinate(Ped, (int *)&a3.Rotate);
  v12 = gta2::Player_sub_401B40(&a3, (S202 *)v25, v11);
  v21 = (PublicTransport *)gta2::sub_401B90(v12, &a3, &unk_673AC8);
  gta2::Ped_GetYCoordinate(Ped, &Y);
  v14 = (int *)gta2::S202_sub_401B20(v13, (SpriteS1 *)&v26, v21);
  gta2::SpriteS1_sub_420600(S202, (int)a2, *v14, (int)a3.Player);
  LOWORD(v15) = pS63->SpriteS1_->FirstElement;
  gta2::SpriteS1_SetRotation(S202, v15);
  gta2::SpriteS1_sub_4BCB90(
    S202,
    (SpriteS1 *)pS63->pEventHandler->NextElement,
    (SpriteS3 *)unk_673BE4.FirstElement,
    pS63->pEventHandler->pEventHandler);
  SpriteType = gta2::SpriteS1_getSpriteType(pS63->SpriteS1_);
  gta2::SpriteS1_sub_4206F0(S202, SpriteType);
  gta2::SpriteS1_SetS63(S202, (EventHandler *)pS63->SpriteS1_->S3_arr5031[0].GameObject);
  v17 = gta2::sub_420B50(self->Ped_);
  gta2::S63_sub_482790(pS63, v17);
  if ( a1 == 254 || a1 == 265 )
  {
    v18 = gta2::sub_435E40(self->Ped_);
    gta2::S63_sub_483C20(pS63, v18);
  }
  if ( gta2::SpriteS1_sub_4BD670(S202) )
  {
    gta2::S63_sub_4827B0(pS63);
    result = 0;
    unk_673941 = 0;
  }
  else
  {
    unk_673941 = 1;
    gta2::S63_sub_4849B0(pS63, a3.FW);
    return (int)pS63;
  }
  return result;
}


// 0x004cdc20: Weapon::sub_4CDC20
// IDA: Weapon::sub_4CDC20
// Ghidra: ---
char gta2::Weapon_sub_4CDC20(struct Weapon *self)
{
  struct Ped *Ped; // edi
  int *v3; // eax
  __int16 *v4; // eax
  struct Ped *v5; // ecx
  S900 **v6; // eax
  SpriteS1 *FirstElement; // edi
  char result; // al
  struct Ped *pPed; // esi
  __int16 Rotation; // [esp+10h] [ebp-20h] BYREF
  int v11; // [esp+14h] [ebp-1Ch] BYREF
  int Y; // [esp+18h] [ebp-18h] BYREF
  S900 *v13[3]; // [esp+1Ch] [ebp-14h] BYREF
  int a3; // [esp+28h] [ebp-8h] BYREF
  int v15; // [esp+2Ch] [ebp-4h] BYREF

  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&v11);
  Ped = self->Ped_;
  v13[0] = *(S900 **)gta2::Ped_GetXCoordinate(Ped, (int)v13);
  gta2::Ped_GetYCoordinate(Ped, &Y);
  Y = *v3;
  gta2::Ped_GetPositionZ(Ped, (int)&Rotation);
  v4 = gta2::Ped_GetRotation(Ped, &Rotation);
  v5 = self->Ped_;
  LOWORD(v11) = *v4;
  v6 = (S900 **)gta2::Ped_sub_435C20(v5, &a3);
  v13[1] = *v6;
  v13[2] = v6[1];
  gta2::sub_41E210(&a3, &unk_673BE4, (int)&v11);
  FirstElement = gta2::S202_sub_401B20((S202 *)v13, (SpriteS1 *)&Rotation, (PublicTransport *)&a3)->FirstElement;
  gta2::S202_sub_401B20((S202 *)&Y, (SpriteS1 *)&Rotation, (PublicTransport *)&v15);
  if ( self->SMG )
    return gta2::Weapon_sub_4CDA90(self, 195, v13[0]);
  gta2::Weapon_Set_4CCA80(self, 1);
  unk_673941 = 0;
  gta2::Weapon_sub_4CDA90(self, 154, FirstElement);
  result = unk_673941;
  if ( unk_673941 )
  {
    gta2::Particles_sub_48D4E0(gParticles, self->Ped_->GameObject2->SpriteS1_);
    if ( gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
      gta2::Weapon_Decrement1Ammo(self);
    gta2::Ped_sub_4350A0(self->Ped_);
    pPed = self->Ped_;
    result = gta2::Ped_IsPlayerControlled(pPed);
    if ( result )
      return gta2::S127_HandlePedInteraction(gS127, 2u, pPed);
  }
  return result;
}


// 0x004cdda0: Weapon::sub_4CDDA0
// IDA: Weapon::sub_4CDDA0
// Ghidra: ---
char gta2::Weapon_sub_4CDDA0(struct Weapon *self, __int16 a2, __int16 a3)
{
  char TimeToReload; // al
  struct Ped *Ped; // ebp
  void *v6; // edi
  int *v7; // eax
  int v8; // eax
  struct Ped *v9; // ecx
  struct Ped *v10; // edi
  char result; // al
  __int16 v12; // [esp-2h] [ebp-2Ah] BYREF
  __int16 v13; // [esp+0h] [ebp-28h] BYREF
  _BYTE v14[2]; // [esp+2h] [ebp-26h] BYREF
  _DWORD v15[2]; // [esp+4h] [ebp-24h] BYREF
  int v16; // [esp+Ch] [ebp-1Ch]
  int v17; // [esp+10h] [ebp-18h] BYREF
  int v18; // [esp+14h] [ebp-14h]
  int X; // [esp+18h] [ebp-10h]
  int v20; // [esp+1Ch] [ebp-Ch]

  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&v13);
  TimeToReload = self->TimeToReload;
  if ( TimeToReload )
  {
    result = TimeToReload - 1;
    self->TimeToReload = result;
  }
  else
  {
    Ped = self->Ped_;
    v6 = *(void **)gta2::Ped_GetXCoordinate(Ped, (int)&v17);
    gta2::Ped_GetYCoordinate(Ped, &v17);
    gta2::Ped_GetPositionZ(Ped, (int)&v17);
    v13 = *gta2::Ped_GetRotation(self->Ped_, &v12);
    v7 = gta2::Ped_sub_435C20(self->Ped_, &v17);
    X = *v7;
    v20 = v7[1];
    gta2::Weapon_Set_4CCA80(self, 1);
    if ( self->SMG )
    {
      gta2::sub_40E5A0((CarSystemManager *)&v13, (CarSystemManager *)&v12, &unk_6739BC);
      gta2::Weapon_sub_4CDA90(self, 193, v6);
      gta2::sub_40E5A0((CarSystemManager *)&v13, (CarSystemManager *)&v12, &unk_673A44);
      gta2::Weapon_sub_4CDA90(self, 193, v6);
      gta2::Weapon_sub_4CDA90(self, 193, v6);
      gta2::SpriteS1_sub_40E5D0((SpriteS1 *)&v13, (CarSystemManager *)&v12, &unk_673A44);
      gta2::Weapon_sub_4CDA90(self, 193, v6);
      gta2::SpriteS1_sub_40E5D0((SpriteS1 *)v15, (CarSystemManager *)v14, (__int16 *)&unk_6739BC);
      gta2::Weapon_sub_4CDA90(self, 193, v6);
      self->TimeToReload = 5;
    }
    else
    {
      gta2::sub_40E5A0((CarSystemManager *)&v13, (CarSystemManager *)&v12, &unk_673A44);
      v15[0] = gta2::Weapon_sub_4CDA90(self, 192, v6);
      gta2::sub_40E5A0((CarSystemManager *)&v13, (CarSystemManager *)&v12, &unk_673CE4);
      v15[1] = gta2::Weapon_sub_4CDA90(self, 192, v6);
      v16 = gta2::Weapon_sub_4CDA90(self, 192, v6);
      gta2::SpriteS1_sub_40E5D0((SpriteS1 *)&v13, (CarSystemManager *)&v12, &unk_673CE4);
      v18 = gta2::Weapon_sub_4CDA90(self, 192, v6);
      gta2::SpriteS1_sub_40E5D0((SpriteS1 *)v15, (CarSystemManager *)v14, &unk_673A44);
      v8 = gta2::Weapon_sub_4CDA90(self, 192, v6);
      if ( (v16 || v17 || v18 || X || v8) && gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
        gta2::Weapon_Decrement10Ammo(self);
      v9 = self->Ped_;
      self->TimeToReload = 40;
      gta2::Ped_sub_4350A0(v9);
      gta2::Particles_sub_48CD10(gParticles, self->Ped_->GameObject2->SpriteS1_);
      v10 = self->Ped_;
      if ( gta2::Ped_IsPlayerControlled(v10) )
      {
        gta2::S127_HandlePedInteraction(gS127, 2u, v10);
        return gta2::Weapon_TimeToReload(self);
      }
    }
    return gta2::Weapon_TimeToReload(self);
  }
  return result;
}


// 0x004ce070: Weapon::sub_4CE070
// IDA: Weapon::sub_4CE070
// Ghidra: ---
char gta2::Weapon_sub_4CE070(struct Weapon *self)
{
  char TimeToReload; // al
  bool IsSearchType; // al
  struct Ped *v4; // edi
  int v5; // ebx
  S202 **v6; // eax
  __int16 *v7; // eax
  struct Ped *v8; // ecx
  int *v9; // eax
  SpriteS1 *FirstElement; // edi
  struct Ped *v11; // eax
  struct Ped *v12; // edi
  char result; // al
  struct Ped *Ped; // edi
  S202 *v15; // eax
  void **XCoordinate; // edi
  __int16 Rotation; // [esp+4h] [ebp-28h] BYREF
  int Y; // [esp+8h] [ebp-24h] BYREF
  S202 v19; // [esp+Ch] [ebp-20h] BYREF

  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&Y);
  TimeToReload = self->TimeToReload;
  if ( TimeToReload )
  {
    result = TimeToReload - 1;
    self->TimeToReload = result;
  }
  else
  {
    gta2::Weapon_Set_4CCA80(self, 1);
    if ( self->SMG )
    {
      Ped = self->Ped_;
      sub_4CCA90(Ped, &Rotation);
      gta2::Ped_GetPositionZ(Ped, (int)&v19);
      gta2::Ped_GetYCoordinate(Ped, &Y);
      v19.S202 = v15;
      XCoordinate = (void **)gta2::Ped_GetXCoordinate(Ped, (int)&v19.CarSystemManager);
      gta2::Ped_sub_435C20(self->Ped_, &v19.field_18);
      gta2::Weapon_sub_4CDA90(self, 154, *XCoordinate);
      self->TimeToReload = 5;
    }
    else
    {
      IsSearchType = gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
      v4 = self->Ped_;
      v5 = IsSearchType ? 265 : 254;
      v19.field_0 = *(_DWORD *)gta2::Ped_GetXCoordinate(v4, (int)&v19.S202);
      gta2::Ped_GetYCoordinate(v4, (int *)&v19.S202);
      v19.S202 = *v6;
      gta2::Ped_GetPositionZ(v4, (int)&Rotation);
      v7 = gta2::Ped_GetRotation(v4, &Rotation);
      v8 = self->Ped_;
      LOWORD(Y) = *v7;
      v9 = gta2::Ped_sub_435C20(v8, (int *)&v19.CarSystemManager);
      v19.field_10 = (Weapon *)*v9;
      v19.pPlayer = (Player *)v9[1];
      gta2::sub_41E210(&v19.CarSystemManager, &unk_673BE4, (int)&Y);
      FirstElement = gta2::S202_sub_401B20(&v19, (SpriteS1 *)&Rotation, (PublicTransport *)&v19.CarSystemManager)->FirstElement;
      gta2::S202_sub_401B20((S202 *)&v19.S202, (SpriteS1 *)&v19, (PublicTransport *)&v19.field_C);
      if ( gta2::Weapon_sub_4CDA90(self, v5, FirstElement) )
      {
        if ( gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
          gta2::Weapon_Decrement10Ammo(self);
      }
      v11 = self->Ped_;
      self->TimeToReload = 20;
      gta2::Particles_sub_48CD10(gParticles, v11->GameObject2->SpriteS1_);
      gta2::Ped_sub_4350A0(self->Ped_);
      v12 = self->Ped_;
      if ( gta2::Ped_IsPlayerControlled(v12) )
      {
        gta2::S127_HandlePedInteraction(gS127, 2u, v12);
        return gta2::Weapon_TimeToReload(self);
      }
    }
    return gta2::Weapon_TimeToReload(self);
  }
  return result;
}


// 0x004ce270: Weapon::sub_4CE270
// IDA: Weapon::sub_4CE270
// Ghidra: ---
char gta2::Weapon_sub_4CE270(struct Weapon *self, __int16 a2)
{
  char TimeToReload; // al
  int *v4; // eax
  struct Ped *Ped; // edi
  _DWORD *v6; // eax
  __int16 *v7; // eax
  struct Ped *v8; // ecx
  SpriteS1 *FirstElement; // ebp
  SpriteS1 *v10; // edi
  int v11; // eax
  struct Ped *v12; // ecx
  struct Ped *v13; // edi
  char result; // al
  __int16 v15; // [esp+0h] [ebp-24h] BYREF
  __int16 Rotation; // [esp+4h] [ebp-20h] BYREF
  _BYTE a4[28]; // [esp+8h] [ebp-1Ch] BYREF

  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&Rotation);
  TimeToReload = self->TimeToReload;
  if ( TimeToReload )
  {
    result = TimeToReload - 1;
    self->TimeToReload = result;
  }
  else
  {
    v4 = gta2::Ped_sub_435C20(self->Ped_, (int *)&a4[16]);
    Ped = self->Ped_;
    *(_DWORD *)&a4[8] = *v4;
    *(_DWORD *)&a4[12] = v4[1];
    *(_DWORD *)a4 = *(_DWORD *)gta2::Ped_GetXCoordinate(Ped, (int)&a4[4]);
    gta2::Ped_GetYCoordinate(Ped, (int *)&a4[4]);
    *(_DWORD *)&a4[4] = *v6;
    gta2::Ped_GetPositionZ(Ped, (int)&v15);
    v7 = gta2::Ped_GetRotation(Ped, &v15);
    v8 = self->Ped_;
    Rotation = *v7;
    gta2::Ped_sub_435C20(v8, (int *)&a4[16]);
    gta2::sub_41E210(&a4[16], &unk_673BE4, (int)&Rotation);
    FirstElement = gta2::S202_sub_401B20((S202 *)a4, (SpriteS1 *)&v15, (PublicTransport *)&a4[16])->FirstElement;
    v10 = gta2::S202_sub_401B20((S202 *)&a4[4], (SpriteS1 *)a4, (PublicTransport *)&a4[20])->FirstElement;
    gta2::Weapon_Set_4CCA80(self, 1);
    if ( self->SMG )
    {
      gta2::SpriteS1_sub_40E5D0((SpriteS1 *)&Rotation, (CarSystemManager *)&v15, &unk_673A44);
      gta2::Weapon_sub_4CDA90(self, 154, FirstElement);
      gta2::sub_40E5A0((CarSystemManager *)a4, (CarSystemManager *)&Rotation, &unk_673A44);
      gta2::Weapon_sub_4CDA90(self, 154, v10);
      self->TimeToReload = 5;
    }
    else
    {
      *(_DWORD *)a4 = gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) ? 265 : 254;
      gta2::SpriteS1_sub_40E5D0((SpriteS1 *)&Rotation, (CarSystemManager *)&v15, &unk_673A44);
      *(_DWORD *)&a4[8] = gta2::Weapon_sub_4CDA90(self, *(int *)&a4[4], FirstElement);
      gta2::sub_40E5A0((CarSystemManager *)a4, (CarSystemManager *)&Rotation, &unk_673A44);
      v11 = gta2::Weapon_sub_4CDA90(self, *(int *)&a4[4], FirstElement);
      if ( (*(_DWORD *)&a4[8] || v11) && gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
        gta2::Weapon_Decrement10Ammo(self);
      v12 = self->Ped_;
      self->TimeToReload = 10;
      gta2::Ped_sub_4350A0(v12);
      gta2::Particles_sub_48CD10(gParticles, self->Ped_->GameObject2->SpriteS1_);
      v13 = self->Ped_;
      if ( gta2::Ped_IsPlayerControlled(v13) )
      {
        gta2::S127_HandlePedInteraction(gS127, 2u, v13);
        return gta2::Weapon_TimeToReload(self);
      }
    }
    return gta2::Weapon_TimeToReload(self);
  }
  return result;
}


// 0x004ce4b0: Weapon::TimeToReload
// IDA: Weapon::TimeToReload
// Ghidra: ---
          return gta2::Weapon_TimeToReload(self);
        }


// 0x004ce6d0: Weapon::sub_4CE6D0
// IDA: Weapon::sub_4CE6D0
// Ghidra: ---
char gta2::Weapon_sub_4CE6D0(struct Weapon *self)
{
  bool IsSearchType; // al
  struct Ped *v3; // edi
  int v4; // eax
  void **v5; // edi
  int v6; // eax
  int v7; // eax
  void **v8; // edi
  char result; // al
  int v10; // eax
  void **v11; // edi
  int v12; // edi
  struct Ped *v13; // eax
  struct Ped *v14; // edi
  struct Ped *Ped; // edi
  int v16; // eax
  void **XCoordinate; // edi
  __int16 v18; // [esp+12h] [ebp-1Ah] BYREF
  int v19; // [esp+14h] [ebp-18h]
  int Z; // [esp+18h] [ebp-14h] BYREF
  int Y; // [esp+1Ch] [ebp-10h] BYREF
  int X; // [esp+20h] [ebp-Ch] BYREF
  int v23[2]; // [esp+24h] [ebp-8h] BYREF

  if ( self->TimeToReload )
  {
    if ( !self->field_20 )
      self->Ped_->PositionX1 &= ~0x400000u;
    result = self->TimeToReload - 1;
    self->TimeToReload = result;
  }
  else
  {
    gta2::Weapon_Set_4CCA80(self, 1);
    if ( self->SMG )
    {
      Ped = self->Ped_;
      sub_4CCA90(Ped, &v18);
      gta2::Ped_GetPositionZ(Ped, (int)&X);
      gta2::Ped_GetYCoordinate(Ped, &Y);
      v19 = v16;
      XCoordinate = (void **)gta2::Ped_GetXCoordinate(Ped, (int)&Z);
      gta2::Ped_sub_435C20(self->Ped_, v23);
      gta2::Weapon_sub_4CDA90(self, 159, *XCoordinate);
      self->TimeToReload = 5;
      self->field_20 = 0;
    }
    else
    {
      IsSearchType = gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
      v3 = self->Ped_;
      if ( IsSearchType )
      {
        sub_4CCA90(self->Ped_, &v18);
        gta2::Ped_GetPositionZ(v3, (int)&Z);
        gta2::Ped_GetYCoordinate(v3, &Y);
        v19 = v4;
        v5 = (void **)gta2::Ped_GetXCoordinate(v3, (int)&X);
        gta2::Ped_sub_435C20(self->Ped_, v23);
        v6 = gta2::Weapon_sub_4CDA90(self, 128, *v5);
      }
      else
      {
        if ( !self->field_20 )
        {
          sub_4CCA90(v3, &v18);
          gta2::Ped_GetPositionZ(v3, (int)&X);
          gta2::Ped_GetYCoordinate(v3, &Y);
          v19 = v7;
          v8 = (void **)gta2::Ped_GetXCoordinate(v3, (int)&Z);
          gta2::Ped_sub_435C20(self->Ped_, v23);
          result = gta2::Weapon_sub_4CDA90(self, 159, *v8);
          self->TimeToReload = 5;
          self->field_20 = 1;
          return result;
        }
        sub_4CCA90(self->Ped_, &v18);
        gta2::Ped_GetPositionZ(v3, (int)&X);
        gta2::Ped_GetYCoordinate(v3, &Y);
        v19 = v10;
        v11 = (void **)gta2::Ped_GetXCoordinate(v3, (int)&Z);
        gta2::Ped_sub_435C20(self->Ped_, v23);
        v6 = gta2::Weapon_sub_4CDA90(self, 128, *v11);
      }
      v12 = v6;
      gta2::Ped_sub_4350A0(self->Ped_);
      if ( v12 )
      {
        if ( gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
          gta2::Weapon_Decrement10Ammo(self);
      }
      v13 = self->Ped_;
      self->TimeToReload = 50;
      gta2::Particles_sub_48CD10(gParticles, v13->GameObject2->SpriteS1_);
      v14 = self->Ped_;
      self->field_20 = 0;
      if ( gta2::Ped_IsPlayerControlled(v14) )
      {
        gta2::S127_HandlePedInteraction(gS127, 2u, v14);
        return gta2::Weapon_TimeToReload(self);
      }
    }
    return gta2::Weapon_TimeToReload(self);
  }
  return result;
}


// 0x004ce970: Weapon::sub_4CE970
// IDA: Weapon::sub_4CE970
// Ghidra: ---
void gta2::Weapon_sub_4CE970(struct Weapon *self, S900 *arg0, SpriteS1 *pSpriteS1)
{
  SpriteS1 *v3; // edi
  char TimeToReload; // al
  struct Ped *v6; // edi
  _WORD *v7; // ebx
  _DWORD **v8; // ebp
  int *v9; // eax
  void **v10; // edi
  PublicTransport *v11; // eax
  int v12; // edx
  _DWORD *v13; // eax
  PublicTransport *v14; // edx
  void *v15; // eax
  struct Ped *v16; // esi
  struct Ped *v17; // edi
  _WORD *v18; // ebx
  int *v19; // ebp
  int *v20; // eax
  int *v21; // eax
  int v22; // ecx
  struct Ped *v23; // edi
  _DWORD *v24; // eax
  void *v25; // eax
  Tango *v26; // eax
  SpriteS1 *v27; // eax
  _DWORD *v28; // eax
  void *v29; // eax
  Tango *v30; // eax
  SpriteS1 *v31; // eax
  char v32; // al
  SpriteS1 *v33; // eax
  struct Ped *v34; // edi
  int *v35; // ebp
  _WORD *v36; // ebx
  S202 *v37; // eax
  int v38; // eax
  int *v39; // eax
  int v40; // ecx
  S900 *v41; // ebx
  EventHandler *v42; // eax
  EventHandler *pS63; // edi
  struct Ped *pPed; // ecx
  int *v45; // eax
  PublicTransport *v46; // ecx
  int v47; // ecx
  int v48; // ecx
  EventHandler *v49; // eax
  PublicTransport *v50; // ecx
  EventHandler *v51; // ebx
  _DWORD *v52; // ecx
  int *v53; // eax
  int *v54; // ebx
  int *v55; // eax
  _DWORD *v56; // edx
  int *v57; // ebp
  PublicTransport *v58; // edx
  int v59; // ecx
  int v60; // ebx
  _DWORD *v61; // ecx
  struct Ped *v62; // edi
  struct Ped *v63; // eax
  struct Ped *Ped; // edi
  _WORD *v65; // ebx
  _DWORD **PositionZ; // ebp
  int *v67; // eax
  void **XCoordinate; // edi
  PublicTransport *v69; // eax
  _DWORD *v70; // ecx
  PublicTransport *v71; // eax
  void *v72; // ecx
  char v73; // al
  int v74; // [esp-18h] [ebp-64h] BYREF
  int v75; // [esp-14h] [ebp-60h] BYREF
  PublicTransport *v76; // [esp-10h] [ebp-5Ch] BYREF
  int v77; // [esp-Ch] [ebp-58h] BYREF
  int v78; // [esp-8h] [ebp-54h] BYREF
  int ID; // [esp-4h] [ebp-50h]
  __int16 v80; // [esp+10h] [ebp-3Ch] BYREF
  S202 a2; // [esp+14h] [ebp-38h] BYREF
  int Y; // [esp+38h] [ebp-14h] BYREF
  int X[2]; // [esp+3Ch] [ebp-10h] BYREF
  int v84[2]; // [esp+44h] [ebp-8h] BYREF
  int *pSpriteS1_4; // [esp+58h] [ebp+Ch] BYREF

  v3 = pSpriteS1;
  if ( !pSpriteS1 )
    return;
  TimeToReload = self->TimeToReload;
  self->field_21 = 0;
  if ( !TimeToReload )
  {
    gta2::Weapon_Set_4CCA80(self, 1);
    if ( self->SMG )
    {
      Ped = self->Ped_;
      v65 = sub_4CCA90(Ped, &arg0);
      PositionZ = (_DWORD **)gta2::Ped_GetPositionZ(Ped, (int)&pSpriteS1);
      gta2::Ped_GetYCoordinate(Ped, X);
      pSpriteS1_4 = v67;
      XCoordinate = (void **)gta2::Ped_GetXCoordinate(Ped, (int)&Y);
      v69 = (PublicTransport *)gta2::Ped_sub_435C20(self->Ped_, (int *)&a2.field_1C);
      v70 = *PositionZ;
      ID = (int)v69;
      LOWORD(v69) = *v65;
      v78 = (int)v69;
      v71 = (PublicTransport *)*pSpriteS1_4;
      v77 = (int)v70;
      v72 = *XCoordinate;
      v76 = v71;
      gta2::Weapon_sub_4CDA90(self, 159, v72);
      self->TimeToReload = 5;
      self->field_20 = 0;
      gta2::Weapon_TimeToReload(self);
      return;
    }
    if ( !gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) && !self->field_20 )
    {
      v6 = self->Ped_;
      v7 = sub_4CCA90(v6, &arg0);
      v8 = (_DWORD **)gta2::Ped_GetPositionZ(v6, (int)&pSpriteS1);
      gta2::Ped_GetYCoordinate(v6, &a2.field_C);
      pSpriteS1_4 = v9;
      v10 = (void **)gta2::Ped_GetXCoordinate(v6, (int)&a2.CarSystemManager);
      v11 = (PublicTransport *)gta2::Ped_sub_435C20(self->Ped_, X);
      LOWORD(v12) = *v7;
      ID = (int)v11;
      v13 = *v8;
      v78 = v12;
      v14 = (PublicTransport *)*pSpriteS1_4;
      v77 = (int)v13;
      v15 = *v10;
      v76 = v14;
      gta2::Weapon_sub_4CDA90(self, 159, v15);
      self->TimeToReload = 5;
      self->field_20 = 1;
      v16 = self->Ped_;
      if ( gta2::Ped_IsPlayerControlled(v16) )
        gta2::S127_HandlePedInteraction(gS127, 2u, v16);
      return;
    }
    if ( arg0 == (S900 *)183 )
    {
      if ( pSpriteS1_4 == (int *)96 )
      {
        v17 = self->Ped_;
        v18 = sub_4CCA90(v17, &arg0);
        v19 = (int *)gta2::Ped_GetPositionZ(v17, (int)&pSpriteS1);
        gta2::Ped_GetYCoordinate(v17, &a2.field_C);
        pSpriteS1_4 = v20;
        v21 = (int *)gta2::Ped_GetXCoordinate(v17, (int)&a2.CarSystemManager);
        LOWORD(v22) = *v18;
        gta2::Object_sub_485540(gObject, *v21, *pSpriteS1_4, *v19, v22, 18, v17->Gang1);
        if ( gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
          gta2::Weapon_Decrement10Ammo(self);
        v23 = self->Ped_;
        if ( gta2::Ped_IsPlayerControlled(v23) )
          gta2::S127_HandlePedInteraction(gS127, 2u, v23);
LABEL_29:
        v63 = self->Ped_;
        if ( v63->isPlayer )
          self->TimeToReload = 4;
        else
          self->TimeToReload = 50;
        v63->PositionX1 |= (unsigned int)byte_400000;
        self->field_21 = 1;
        gta2::Weapon_TimeToReload(self);
        return;
      }
      ID = (int)gta2::S202_sub_401B20(&unk_67395C, (SpriteS1 *)&pSpriteS1, (PublicTransport *)&unk_673C3C);
      gta2::S202_sub_41F980((S202 *)&a2.CarSystemManager, 60);
      v77 = (int)v24;
      gta2::S202_sub_41F980(&a2, (int)v3);
      v26 = (Tango *)gta2::sub_401B90(v25, &a2.S202, (_DWORD *)v77);
      v27 = gta2::Radar_AddBlip(v26, (SpriteS1 *)&a2.field_C, (PublicTransport *)ID);
      a2.field_0 = (int)gta2::S202_sub_401B20(&unk_673960, (SpriteS1 *)&v80, (PublicTransport *)v27)->FirstElement;
    }
    else
    {
      gta2::S202_sub_41F980((S202 *)&a2.field_C, 60);
      v77 = (int)v28;
      gta2::S202_sub_41F980((S202 *)&a2.S202, (int)v3);
      v30 = (Tango *)gta2::sub_401B90(v29, &a2.CarSystemManager, (_DWORD *)v77);
      v31 = gta2::Radar_AddBlip(v30, (SpriteS1 *)&pSpriteS1, (PublicTransport *)&unk_67395C);
      a2.field_0 = (int)gta2::S202_sub_401B20(&unk_673C3C, (SpriteS1 *)&a2, (PublicTransport *)v31)->FirstElement;
    }
    v32 = gta2::sub_420B50(self->Ped_);
    gta2::Object_sub_482960(gObject, v32);
    v33 = gta2::JustCopyByPtrAtoC(&unk_673C98, (SpriteS1 *)&a2.pPlayer);
    v34 = self->Ped_;
    v35 = (int *)v33;
    v36 = sub_4CCA90(v34, &pSpriteS1);
    a2.S202 = (S202 *)sub_4CCA90(v34, &v80);
    v37 = (S202 *)gta2::Ped_GetPositionZ(v34, (int)&a2.field_1C);
    a2.CarSystemManager = (CarSystemManager *)gta2::S202_sub_401B20(
                                                v37,
                                                (SpriteS1 *)&a2.field_18,
                                                (PublicTransport *)&unk_673BDC);
    gta2::Ped_GetYCoordinate(v34, &Y);
    a2.field_C = v38;
    v39 = (int *)gta2::Ped_GetXCoordinate(v34, (int)X);
    v40 = *v35;
    ID = unk_67395C.field_0;
    v78 = v40;
    LOWORD(v40) = *v36;
    v41 = arg0;
    gta2::Object_sub_485500(
      gObject,
      arg0,
      *v39,
      *(_DWORD *)a2.field_C,
      *(_DWORD *)a2.CarSystemManager,
      a2.S202->field_0,
      v40,
      (Ped *)a2.field_0,
      v78,
      unk_67395C.field_0);
    pS63 = v42;
    if ( v42 )
    {
      pPed = self->Ped_;
      if ( (pPed->GameObject2->field_58 & 8) == 0 )
      {
        v45 = gta2::Ped_sub_435C20(pPed, &a2.field_C);
        v84[0] = *v45;
        v84[1] = v45[1];
        gta2::S63_sub_4849B0(pS63, (int)v84);
        if ( !gta2::SpriteS1_sub_420360((SpriteS1 *)v84) )
          gta2::Player_sub_40E530((Player *)pS63->Car->CarDoor_, &unk_673CE0);
      }
      if ( v41 == (S900 *)138 )
      {
        ID = 255;
        v78 = (int)pPed;
        arg0 = (S900 *)&v78;
        gta2::bitShiftLeft1(&v78, 3);
        v77 = 16744448;
        v76 = v46;
        arg0 = (S900 *)&v76;
        gta2::bitShiftLeft1(&v76, 2);
        v75 = v47;
        arg0 = (S900 *)&v75;
        gta2::bitShiftLeft1(&v75, 138);
        v74 = v48;
        arg0 = (S900 *)&v74;
        gta2::bitShiftLeft1(&v74, 94);
        v49 = gta2::Object_sub_485370(gObject, v74, v75, (int)v76, v77, v78, ID);
        LOWORD(v50) = unk_6739B0.Index;
        v51 = v49;
        ID = (int)v50;
        v78 = (int)v50;
        arg0 = (S900 *)&v78;
        gta2::bitShiftLeft1(&v78, 0);
        v77 = (int)v52;
        arg0 = (S900 *)&v77;
        gta2::bitShiftLeft1(&v77, 0);
        gta2::SpriteS1_sub_4B9D50(pS63->SpriteS1_, (int)v51->SpriteS1_, (SpriteS1 *)v77, v78, ID);
        LOWORD(v53) = gta2::bitShiftLeft1(&arg0, 145);
        v54 = v53;
        LOWORD(v55) = gta2::bitShiftLeft1(&pSpriteS1_4, 113);
        LOWORD(v56) = unk_6739B0.Index;
        v57 = v55;
        ID = self->Ped_->Gang1;
        v78 = 5;
        v77 = (int)v56;
        v76 = (PublicTransport *)ID;
        a2.field_C = (int)&v76;
        gta2::bitShiftLeft1(&v76, 2);
        v60 = gta2::Object_sub_485540(gObject, *v57, *v54, (int)v76, v77, v78, ID);
        if ( v60 )
        {
          LOWORD(v58) = unk_6739B0.Index;
          ID = (int)v58;
          v78 = v59;
          a2.field_C = (int)&v78;
          gta2::bitShiftLeft1(&v78, 0);
          v77 = (int)v61;
          a2.field_C = (int)&v77;
          gta2::bitShiftLeft1(&v77, 0);
          gta2::SpriteS1_sub_4B9D50(pS63->SpriteS1_, *(_DWORD *)(v60 + 4), (SpriteS1 *)v77, v78, ID);
        }
      }
      else
      {
        gta2::S63_sub_434130(pS63, (96 - (int)pSpriteS1_4) / 8);
      }
      if ( gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
        gta2::Weapon_Decrement10Ammo(self);
      v62 = self->Ped_;
      self->field_21 = 1;
      if ( gta2::Ped_IsPlayerControlled(v62) )
        gta2::S127_HandlePedInteraction(gS127, 2u, v62);
      gta2::Ped_sub_4350A0(self->Ped_);
    }
    goto LABEL_29;
  }
  if ( !self->field_20 )
    self->Ped_->PositionX1 &= ~0x400000u;
  v73 = self->TimeToReload - 1;
  self->TimeToReload = v73;
  if ( (unsigned __int8)v73 < 0x1Eu && self->field_21 )
  {
    self->field_21 = 0;
    self->Ped_->PositionX1 &= ~0x400000u;
  }
}


// 0x004cf380: Weapon::sub_4CF380
// IDA: Weapon::sub_4CF380
// Ghidra: Weapon::FUN_004cf380
void gta2::Weapon_sub_4CF380(struct Weapon *self,char param_1,SpriteS1 *param_2)
{
  short *psVar1;
  bool bVar2;
  char cVar3;
  bool bVar4;
  byte bVar5;
  short sVar6;
  undefined4 *puVar7;
  SpriteS1 *pSVar8;
  Weapon *pWVar9;
  int iVar10;
  undefined4 uVar11;
  int *piVar12;
  void *pvVar13;
  undefined2 *puVar14;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined2 extraout_var_05;
  uint uVar15;
  struct Player *this_00;
  void *this_01;
  undefined4 *pS127;
  SpriteS1 *pSVar16;
  undefined2 local_74 [2];
  undefined1 local_70 [20];
  undefined1 local_5c [8];
  undefined1 local_54 [8];
  undefined1 local_4c [4];
  undefined1 local_48 [8];
  undefined4 local_40 [2];
  undefined1 local_38 [8];
  undefined1 local_30 [8];
  undefined1 local_28 [8];
  undefined1 local_20 [8];
  Point2D local_18;
  undefined4 puVar8;
  undefined4 *pSpawnPoint;
  
  local_70._16_4_ = self;
  gta2::Arsenal_Reset((Turrel *)local_5c);
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)(local_70 + 8))
  ;
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)(local_70 + 0xc));
  bVar4 = false;
  if (param_1 == '\0') {
    pSpawnPoint = &param_2->Matrix3DArray[0].PositionX;
    puVar7 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)pSpawnPoint,(GlassInfo *)(local_5c + 4),
                        (S127 *)&DAT_00673ac8);
    uVar11 = *puVar7;
    pSVar8 = gta2::S202_sub_401B20((Point2D *)pSpawnPoint,(SpriteS1 *)(local_5c + 4),
                        (S127 *)&DAT_00673ac8);
    local_70._0_4_ = pSVar8->FirstElement;
    pSpawnPoint = &param_2->Matrix3DArray[0].PositionY;
    puVar7 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)pSpawnPoint,(GlassInfo *)(local_5c + 4),
                        (S127 *)&DAT_00673ac8);
    local_70._4_4_ = *puVar7;
    pSVar8 = gta2::S202_sub_401B20((Point2D *)pSpawnPoint,(SpriteS1 *)(local_5c + 4),
                        (S127 *)&DAT_00673ac8);
  }
  else {
    pSpawnPoint = &param_2->Matrix3DArray[0].PositionX;
    puVar7 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)pSpawnPoint,(GlassInfo *)(local_5c + 4),
                        (S127 *)&DAT_006739e4);
    uVar11 = *puVar7;
    pSVar8 = gta2::S202_sub_401B20((Point2D *)pSpawnPoint,(SpriteS1 *)(local_5c + 4),
                        (S127 *)&DAT_006739e4);
    local_70._0_4_ = pSVar8->FirstElement;
    puVar7 = &param_2->Matrix3DArray[0].PositionY;
    pSpawnPoint = (undefined4 *)
                  gta2::Player_sub_401B40((SpawnPoint *)puVar7,(GlassInfo *)(local_5c + 4),
                             (S127 *)&DAT_006739e4);
    local_70._4_4_ = *pSpawnPoint;
    pSVar8 = gta2::S202_sub_401B20((Point2D *)puVar7,(SpriteS1 *)(local_5c + 4),
                        (S127 *)&DAT_006739e4);
  }
  pS127 = &param_2->Matrix3DArray[0].PositionX;
  puVar7 = &param_2->Matrix3DArray[0].PositionY;
  gta2::Point2D_Set(&local_18,uVar11,local_70._0_4_,local_70._4_4_,
               pSVar8->FirstElement);
  pSpawnPoint = &param_2->Matrix3DArray[0].PositionZ;
  local_5c._4_4_ =
       gta2::S202_sub_401B20((Point2D *)pSpawnPoint,(SpriteS1 *)(local_70 + 4),
                  (S127 *)&DAT_006739e4);
  pSpawnPoint = (undefined4 *)
                gta2::Player_sub_401B40((SpawnPoint *)pSpawnPoint,(GlassInfo *)local_70,
                           (S127 *)&DAT_006739e4);
  gta2::Point2D_Set2(&local_18,*pSpawnPoint,*(SpriteS1 **)local_5c._4_4_);
  _DAT_00673cb8 =
       **(undefined2 **)
         &(*(Ped **)(local_70._16_4_ + 0x24))->GameObject_->AIState;
  pWVar9 = (Weapon *)local_70._16_4_;
  gta2::Ped_sub_435C20(*(Ped **)(local_70._16_4_ + 0x24),local_40);
  _DAT_00673ad8 = pWVar9->armo;
  unique0x00009682 = pWVar9->TimeToReload;
  unique0x00009683 = pWVar9->field_0x3;
  uVar11 = pWVar9->TypeWeapons;
  _DAT_00673adc = uVar11;
  gta2::Checkpoint_FUN_00447c80(gCheckpoint,&local_18,0,0,param_2,local_5c);
  if (((char)uVar11 != '\0') && ((VehiclePool *)local_5c._0_4_ != NULL)) {
    do {
      pSVar8 = (SpriteS1 *)
               gta2::Car_sub_4BEE10((VehiclePool *)local_5c);
      iVar10 = gta2::SpriteS1_getSpriteType(pSVar8);
      if (iVar10 == 2) {
        if (param_2 != pSVar8) {
          uVar11 = gta2::Turrel_SpriteContains(gTurrel,(int)pSVar8);
          if ((char)uVar11 == '\0') {
            piVar12 = (int *)gta2::Player_sub_401B40((SpawnPoint *)
                                        &pSVar8->Matrix3DArray[0].PositionX,
                                        (GlassInfo *)local_48,(S127 *)pS127);
            pvVar13 = gta2::Player_sub_401B40((SpawnPoint *)
                                 &pSVar8->Matrix3DArray[0].PositionY,
                                 (GlassInfo *)(local_48 + 4),(S127 *)puVar7);
            puVar14 = gta2::Player_FUN_0040e8d0((Player *)local_70,(undefined2 *)local_70,
                                 pvVar13,piVar12);
            local_70._12_2_ = *puVar14;
            FUN_0042a6b0(this_01,local_40,
                         (GlassInfo *)&pSVar8->Matrix3DArray[0].PositionX,
                         &pSVar8->Matrix3DArray[0].PositionY,(GlassInfo *)pS127,
                         (GlassInfo *)puVar7);
            puVar14 = (undefined2 *)
                      gta2::SpriteS1_sub_40E5D0((CarSystemManager *)(local_70 + 0xc),
                                 (Ped *)(local_70 + 4),(int)&stack0x0000000c);
            local_70._8_2_ = *puVar14;
            bVar2 = gta2::CarSystemManager_less_than((CarSystemManager *)(local_70 + 8),
                               (short *)&DAT_00673a54);
            if (CONCAT31(extraout_var_02,bVar2) == 0) {
              bVar2 = gta2::CarSystemManager_greater_than((CarSystemManager *)(local_70 + 8),
                                 (short *)&DAT_00673c50);
              if (CONCAT31(extraout_var_03,bVar2) == 0) goto LAB_004cf981;
            }
            cVar3 = FUN_00469f90(_DAT_0067395c,_DAT_0067395c,_DAT_0067395c,
                                 *pS127,*puVar7,
                                 param_2->Matrix3DArray[0].PositionZ,
                                 pSVar8->Matrix3DArray[0].PositionX,
                                 pSVar8->Matrix3DArray[0].PositionY,
                                 pSVar8->Matrix3DArray[0].PositionZ);
            if (cVar3 != '\0') {
              DAT_00673940 = param_1;
              bVar4 = gta2::Car_sub_403800((Car *)&pSVar8->Matrix3DArray[0].PositionZ
                                      ,&param_2->Matrix3DArray[0].PositionZ);
              if (CONCAT31(extraout_var_04,bVar4) == 0) {
                local_5c._4_4_ = param_2->Matrix3DArray[0].PositionZ;
              }
              else {
                local_5c._4_4_ = pSVar8->Matrix3DArray[0].PositionZ;
              }
              pSpawnPoint = (undefined4 *)
                            gta2::SpriteS1_sub_4207B0(param_2,local_28);
              pSVar16 = (SpriteS1 *)local_5c._4_4_;
              gta2::SpriteS1_sub_4207B0(pSVar8,local_20);
              FUN_004ccbd0(*pSpawnPoint,pSpawnPoint[1],pSVar16);
              gta2::Turrel_sub_4BEDD0(gTurrel,(Sprite *)pSVar8);
              puVar8 = local_70._16_4_;
              cVar3 = param_1;
              if (param_1 == '\0') {
                cVar3 = '\x01';
                gta2::Weapon_sub_4CF380((Weapon *)local_70._16_4_,'\x01',pSVar8);
              }
              gta2::Car_sub_425770(pSVar8->Matrix3DArray[0].Car);
              if (cVar3 == '\0') {
                (pSVar8->Matrix3DArray[0].Car)->lastDamagingPed =
                     (Ped *)(*(Ped **)(puVar8 + 0x24))->ID;
                (pSVar8->Matrix3DArray[0].Car)->DamageType = 0x12;
                (pSVar8->Matrix3DArray[0].Car)->Mask = 0x32;
                sVar6 = gta2::Car_CollisionOnCar(pSVar8->Matrix3DArray[0].Car,300,
                                            &DAT_00673988);
                local_5c._4_4_ = CONCAT22(extraout_var_05,sVar6);
                gta2::Car_sub_426F00(pSVar8->Matrix3DArray[0].Car);
                bVar4 = gta2::Ped_IsSearchType(*(Ped **)(puVar8 + 0x24),
                                           SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY)
                ;
                if ((bVar4) && (0 < (short)local_5c._4_2_)) {
                  gta2::PlayerStats_sub_4B89B0((SaveSlotAnimatedValue *)
                             &(*(Ped **)(puVar8 + 0x24))->isPlayer->Money,
                             pSVar8->Matrix3DArray[0].Car,1);
                }
              }
              bVar5 = gta2::Ped_IsPlayerControlled(*(Ped **)(puVar8 + 0x24));
              if (bVar5 != 0) {
                gta2::S127_HandlePedInteraction(gS127,2,*(Ped **)(puVar8 + 0x24));
              }
              gta2::Ped_sub_4350A0(*(Ped **)(puVar8 + 0x24));
            }
            bVar4 = true;
            gta2::MissionManager_sub_476530(gMissionManager,(pSVar8->Matrix3DArray[0].Car)->ID_Object
                       ,0xa0,'\0');
          }
        }
      }
      else if ((iVar10 == 3) && (param_2 != pSVar8)) {
        uVar11 = gta2::Turrel_SpriteContains(gTurrel,(int)pSVar8);
        if ((char)uVar11 == '\0') {
          piVar12 = (int *)gta2::Player_sub_401B40((SpawnPoint *)
                                      &pSVar8->Matrix3DArray[0].PositionX,
                                      (GlassInfo *)local_54,(S127 *)pS127);
          pvVar13 = gta2::Player_sub_401B40((SpawnPoint *)&pSVar8->Matrix3DArray[0].PositionY
                               ,(GlassInfo *)(local_54 + 4),(S127 *)puVar7);
          puVar14 = gta2::Player_FUN_0040e8d0(this_00,local_74,pvVar13,piVar12);
          local_70._12_2_ = *puVar14;
          FUN_0042a6b0(local_4c,(undefined4 *)local_4c,
                       (GlassInfo *)&pSVar8->Matrix3DArray[0].PositionX,
                       &pSVar8->Matrix3DArray[0].PositionY,(GlassInfo *)pS127,
                       (GlassInfo *)puVar7);
          puVar14 = (undefined2 *)
                    gta2::SpriteS1_sub_40E5D0((CarSystemManager *)(local_70 + 0xc),
                               (Ped *)(local_74 + 1),(int)&stack0x0000000c);
          local_70._8_2_ = *puVar14;
          bVar2 = gta2::CarSystemManager_less_than((CarSystemManager *)(local_70 + 8),
                             (short *)&DAT_00673a54);
          if (CONCAT31(extraout_var,bVar2) == 0) {
            bVar2 = gta2::CarSystemManager_greater_than((CarSystemManager *)(local_70 + 8),
                               (short *)&DAT_00673c50);
            if (CONCAT31(extraout_var_00,bVar2) == 0) goto LAB_004cf981;
          }
          cVar3 = FUN_00469f90(_DAT_0067395c,_DAT_0067395c,_DAT_0067395c,*pS127,
                               *puVar7,param_2->Matrix3DArray[0].PositionZ,
                               pSVar8->Matrix3DArray[0].PositionX,
                               pSVar8->Matrix3DArray[0].PositionY,
                               pSVar8->Matrix3DArray[0].PositionZ);
          if (cVar3 != '\0') {
            DAT_00673940 = param_1;
            bVar4 = gta2::Car_sub_403800((Car *)&pSVar8->Matrix3DArray[0].PositionZ,
                                    &param_2->Matrix3DArray[0].PositionZ);
            if (CONCAT31(extraout_var_01,bVar4) == 0) {
              local_5c._4_4_ = param_2->Matrix3DArray[0].PositionZ;
            }
            else {
              local_5c._4_4_ = pSVar8->Matrix3DArray[0].PositionZ;
            }
            pSpawnPoint = (undefined4 *)
                          gta2::SpriteS1_sub_4207B0(param_2,local_38);
            pSVar16 = (SpriteS1 *)local_5c._4_4_;
            gta2::SpriteS1_sub_4207B0(pSVar8,local_30);
            FUN_004ccbd0(*pSpawnPoint,pSpawnPoint[1],pSVar16);
            gta2::Turrel_sub_4BEDD0(gTurrel,(Sprite *)pSVar8);
            uVar11 = local_70._16_4_;
            if (param_1 == '\0') {
              gta2::Weapon_sub_4CF380((Weapon *)local_70._16_4_,'\x01',pSVar8);
            }
            gta2::sub_433BF0((Ped *)(pSVar8->Matrix3DArray[0].Car)->
                                     PhysicsBitmask,*(Ped **)(uVar11 + 0x24));
            *(int *)((pSVar8->Matrix3DArray[0].Car)->PhysicsBitmask + 0x204) =
                 (*(Ped **)(uVar11 + 0x24))->ID;
            *(undefined4 *)
             ((pSVar8->Matrix3DArray[0].Car)->PhysicsBitmask + 0x290) = 0x12;
            *(undefined1 *)
             ((pSVar8->Matrix3DArray[0].Car)->PhysicsBitmask + 0x264) = 0x32;
            psVar1 = (short *)((pSVar8->Matrix3DArray[0].Car)->PhysicsBitmask +
                              0x210);
            *psVar1 = *psVar1 + 5;
            bVar5 = gta2::Ped_IsPlayerControlled(*(Ped **)(uVar11 + 0x24));
            if (bVar5 != 0) {
              gta2::S127_HandlePedInteraction(gS127,2,*(Ped **)(uVar11 + 0x24));
            }
            gta2::Ped_sub_4350A0(*(Ped **)(uVar11 + 0x24));
            gta2::MissionManager_sub_476530(gMissionManager,
                       *(int *)((pSVar8->Matrix3DArray[0].Car)->PhysicsBitmask +
                               0x200),0xa0,'\x01');
          }
          bVar4 = true;
        }
      }
LAB_004cf981:
      uVar11 = local_70._16_4_;
    } while ((VehiclePool *)local_5c._0_4_ != NULL);
    if ((bVar4) && (param_1 == '\0')) {
      gta2::Weapon_Set_4CCA80((Weapon *)local_70._16_4_,1);
      bVar4 = gta2::Ped_IsSearchType(*(Ped **)(uVar11 + 0x24),
                                 SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
      if (bVar4) {
        uVar15 = gta2::General_GetCycle(gGeneral);
        if ((uVar15 & 1) != 0) {
          gta2::Weapon_Decrement1Ammo((Weapon *)uVar11);
        }
      }
    }
  }
  return;
}


// 0x004cf9e0: Weapon::FUN_004cf9e0
// IDA: ---
// Ghidra: Weapon::FUN_004cf9e0
void gta2::Weapon_FUN_004cf9e0(struct Weapon *self)
{
  struct Ped *this_00;
  byte bVar1;
  
  gta2::Turrel_sub_4BEE80((Car *)gTurrel);
  gta2::Weapon_sub_4CF380(self,'\0',*(SpriteS1 **)&self->Ped_->GameObject_->AIState);
  this_00 = self->Ped_;
  bVar1 = gta2::Ped_IsPlayerControlled(this_00);
  if (bVar1 != 0) {
    gta2::S127_HandlePedInteraction(gS127,2,this_00);
  }
  return;
}


// 0x004cfa30: Weapon::sub_4CFA30
// IDA: Weapon::sub_4CFA30
// Ghidra: ---
char gta2::Weapon_sub_4CFA30(struct Weapon *self)
{
  struct Ped *Ped; // ecx
  int sPed3; // eax
  char TimeToReload; // al
  struct Ped *v5; // edi
  int v6; // eax
  void **v7; // edi
  int v8; // eax
  void **XCoordinate; // edi
  struct Ped *v10; // edi
  __int16 v12; // [esp+Eh] [ebp-1Ah] BYREF
  int v13; // [esp+10h] [ebp-18h]
  int Z; // [esp+14h] [ebp-14h] BYREF
  int Y; // [esp+18h] [ebp-10h] BYREF
  int X; // [esp+1Ch] [ebp-Ch] BYREF
  int v17[2]; // [esp+20h] [ebp-8h] BYREF

  Ped = self->Ped_;
  sPed3 = (int)Ped->field_136;
  if ( sPed3 )
  {
    if ( *(_DWORD *)(sPed3 + 360) )
    {
      if ( gta2::Ped_IsSearchType(Ped, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY)
        && (v10 = self->Ped_, sPed3 = gta2::Ped_GetPedState(v10->field_136), sPed3 >= 8)
        && sPed3 <= 9 )
      {
        v10->field_136 = 0;
      }
      else
      {
        LOBYTE(sPed3) = gta2::Weapon_sub_4CD020(self);
      }
    }
    else
    {
      Ped->field_136 = 0;
    }
  }
  else
  {
    TimeToReload = self->TimeToReload;
    if ( TimeToReload )
    {
      LOBYTE(sPed3) = TimeToReload - 1;
      self->TimeToReload = sPed3;
    }
    else
    {
      gta2::Weapon_Set_4CCA80(self, 1);
      v5 = self->Ped_;
      if ( self->SMG )
      {
        sub_4CCA90(v5, &v12);
        gta2::Ped_GetPositionZ(v5, (int)&X);
        gta2::Ped_GetYCoordinate(v5, &Y);
        v13 = v8;
        XCoordinate = (void **)gta2::Ped_GetXCoordinate(v5, (int)&Z);
        gta2::Ped_sub_435C20(self->Ped_, v17);
        gta2::Weapon_sub_4CDA90(self, 154, *XCoordinate);
        self->TimeToReload = 5;
        LOBYTE(sPed3) = gta2::Weapon_TimeToReload(self);
      }
      else
      {
        sub_4CCA90(self->Ped_, &v12);
        gta2::Ped_GetPositionZ(v5, (int)&Z);
        gta2::Ped_GetYCoordinate(v5, &Y);
        v13 = v6;
        v7 = (void **)gta2::Ped_GetXCoordinate(v5, (int)&X);
        gta2::Ped_sub_435C20(self->Ped_, v17);
        if ( gta2::Weapon_sub_4CDA90(self, 277, *v7) && gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
          gta2::Weapon_Decrement10Ammo(self);
        self->TimeToReload = 20;
        LOBYTE(sPed3) = gta2::Weapon_TimeToReload(self);
      }
    }
  }
  return sPed3;
}


// 0x004cfbe0: Weapon::sub_4CFBE0
// IDA: Weapon::sub_4CFBE0
// Ghidra: ---
void gta2::Weapon_sub_4CFBE0(struct Weapon *self)
{
  struct Car *Car; // edi
  CarSystemManager **v3; // eax
  struct Car *v4; // edi
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // eax
  _DWORD a2[2]; // [esp+8h] [ebp-2Ch] BYREF
  int v9; // [esp+10h] [ebp-24h] BYREF
  S900 *v10; // [esp+14h] [ebp-20h] BYREF
  _DWORD v11[4]; // [esp+1Ch] [ebp-18h] BYREF
  _DWORD v12[2]; // [esp+2Ch] [ebp-8h] BYREF

  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&v9);
  Car = self->Car;
  self->Ped_ = gta2::Car_GetDriver(Car);
  v3 = (CarSystemManager **)gta2::Car_sub_4BE980(Car, 114);
  if ( v3 )
  {
    LOWORD(v9) = *(_WORD *)gta2::sub_40E5A0(*v3, (CarSystemManager *)a2, &unk_673B78);
    gta2::bitShiftLeft1(a2, 0);
    gta2::Weapon_sub_432860((Weapon *)&v10, a2, &unk_673AD0);
    gta2::Tango_sub_40F6B0((Tango *)&v10, (S900 *)&v9);
    gta2::bitShiftLeft1(a2, 0);
    gta2::Weapon_sub_432860((Weapon *)v11, a2, &unk_673B54);
  }
  else
  {
    LOWORD(v9) = *(_WORD *)*gta2::Car_sub_4BE980(self->Car, 248);
    gta2::bitShiftLeft1(a2, 0);
    gta2::Weapon_sub_432860((Weapon *)&v10, a2, &unk_673A04);
    gta2::Tango_sub_40F6B0((Tango *)&v10, (S900 *)&v9);
    gta2::bitShiftLeft1(a2, 0);
    gta2::Weapon_sub_432860((Weapon *)v11, a2, &unk_673CB0);
  }
  v4 = self->Car;
  gta2::Tango_sub_40F6B0((Tango *)v11, (S900 *)v4->CarSprite);
  v5 = gta2::SpriteS1_sub_4207B0(v4->CarSprite, a2);
  v6 = gta2::S103_sub_40F5C0((S103 *)v11, v12, v5);
  gta2::Tango_sub_40F680((Tango *)&v10, (int)v6);
  v7 = gta2::Player_sub_4A0D10(v4->Player_, v12, (Ped *)&v10);
  v11[2] = *v7;
  v11[3] = v7[1];
  gta2::Weapon_Set_4CCA80(self, 1);
  if ( self->SMG )
    gta2::Weapon_sub_4CDA90(self, 195, v10);
  else
    gta2::Particles_sub_48D4E0(gParticles, self->Car->CarSprite);
}


// 0x004cfd80: Weapon::sub_4CFD80
// IDA: Weapon::sub_4CFD80
// Ghidra: ---
void gta2::Weapon_sub_4CFD80(struct Weapon *self)
{
  struct Car *Car; // edi
  CarSystemManager **v3; // eax
  struct Car *v4; // edi
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // eax
  _DWORD a2[2]; // [esp+8h] [ebp-2Ch] BYREF
  int v9; // [esp+10h] [ebp-24h] BYREF
  S900 *v10; // [esp+14h] [ebp-20h] BYREF
  _DWORD v11[4]; // [esp+1Ch] [ebp-18h] BYREF
  _DWORD v12[2]; // [esp+2Ch] [ebp-8h] BYREF

  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&v9);
  Car = self->Car;
  self->Ped_ = gta2::Car_GetDriver(Car);
  v3 = (CarSystemManager **)gta2::Car_sub_4BE980(Car, 114);
  LOWORD(v9) = *(_WORD *)gta2::sub_40E5A0(*v3, (CarSystemManager *)a2, &unk_673B78);
  gta2::bitShiftLeft1(a2, 0);
  gta2::Weapon_sub_432860((Weapon *)&v10, a2, &unk_673AD0);
  gta2::Tango_sub_40F6B0((Tango *)&v10, (S900 *)&v9);
  gta2::bitShiftLeft1(a2, 0);
  gta2::Weapon_sub_432860((Weapon *)v11, a2, &unk_673B54);
  v4 = self->Car;
  gta2::Tango_sub_40F6B0((Tango *)v11, (S900 *)v4->CarSprite);
  v5 = gta2::SpriteS1_sub_4207B0(v4->CarSprite, a2);
  v6 = gta2::S103_sub_40F5C0((S103 *)v11, v12, v5);
  gta2::Tango_sub_40F680((Tango *)&v10, (int)v6);
  v7 = gta2::Player_sub_4A0D10(v4->Player_, v12, (Ped *)&v10);
  v11[2] = *v7;
  v11[3] = v7[1];
  gta2::Weapon_Set_4CCA80(self, 1);
  gta2::Weapon_Set_4CCA80(self, 1);
  if ( self->SMG )
    gta2::Weapon_sub_4CDA90(self, 199, v10);
  else
    gta2::Particles_sub_48D8B0(gParticles, self->Car->CarSprite);
}


// 0x004cfec0: Weapon::sub_4CFEC0
// IDA: Weapon::sub_4CFEC0
// Ghidra: ---
char gta2::Weapon_sub_4CFEC0(struct Weapon *self)
{
  char TimeToReload; // al
  struct Car *Car; // edi
  struct Car *v4; // edi
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  S103 **v7; // eax
  struct Ped *Ped; // ecx
  struct Ped *v9; // edi
  char result; // al
  int v11; // [esp+4h] [ebp-2Ch] BYREF
  S900 *a2[2]; // [esp+8h] [ebp-28h] BYREF
  S900 *v13; // [esp+10h] [ebp-20h] BYREF
  S103 *pS103; // [esp+18h] [ebp-18h] BYREF
  S103 *v15; // [esp+1Ch] [ebp-14h]
  _DWORD v16[2]; // [esp+20h] [ebp-10h] BYREF
  _DWORD v17[2]; // [esp+28h] [ebp-8h] BYREF

  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&v11);
  TimeToReload = self->TimeToReload;
  if ( TimeToReload )
  {
    result = TimeToReload - 1;
    self->TimeToReload = result;
  }
  else
  {
    Car = self->Car;
    self->Ped_ = gta2::Car_GetDriver(Car);
    LOWORD(v11) = *(_WORD *)*gta2::Car_sub_4BE980(Car, 148);
    gta2::bitShiftLeft1(a2, 0);
    gta2::Weapon_sub_432860((Weapon *)&v13, a2, &unk_673A64);
    gta2::Tango_sub_40F6B0((Tango *)&v13, (S900 *)&v11);
    gta2::bitShiftLeft1(a2, 0);
    gta2::Weapon_sub_432860((Weapon *)v16, a2, &unk_6739F8);
    v4 = self->Car;
    gta2::Tango_sub_40F6B0((Tango *)v16, (S900 *)v4->CarSprite);
    v5 = gta2::SpriteS1_sub_4207B0(v4->CarSprite, a2);
    v6 = gta2::S103_sub_40F5C0((S103 *)v16, v17, v5);
    gta2::Tango_sub_40F680((Tango *)&v13, (int)v6);
    if ( v4->Player_ )
    {
      v7 = (S103 **)gta2::Player_sub_4A0D10(v4->Player_, v17, (Ped *)&v13);
      pS103 = *v7;
      v15 = v7[1];
    }
    else
    {
      gta2::S103_sub_41E1E0((S103 *)&pS103);
    }
    gta2::Weapon_Set_4CCA80(self, 1);
    if ( self->SMG )
    {
      gta2::Weapon_sub_4CDA90(self, 159, v13);
      self->TimeToReload = 5;
    }
    else
    {
      if ( gta2::Weapon_sub_4CDA90(self, 128, v13) )
      {
        if ( gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
          gta2::Weapon_Decrement10Ammo(self);
      }
      Ped = self->Ped_;
      self->TimeToReload = 50;
      gta2::Ped_sub_4350A0(Ped);
      v9 = self->Ped_;
      if ( gta2::Ped_IsPlayerControlled(v9) )
      {
        gta2::S127_HandlePedInteraction(gS127, 2u, v9);
        return gta2::Weapon_TimeToReload(self);
      }
    }
    return gta2::Weapon_TimeToReload(self);
  }
  return result;
}


// 0x004d0080: Weapon::sub_4D0080
// IDA: Weapon::sub_4D0080
// Ghidra: ---
char gta2::Weapon_sub_4D0080(struct Weapon *self)
{
  char TimeToReload; // al
  struct Car *Car; // edi
  struct Car *v4; // edi
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  S900 **v7; // eax
  struct Ped *Ped; // ecx
  struct Ped *v9; // edi
  char result; // al
  int v11; // [esp+4h] [ebp-2Ch] BYREF
  S900 *a2[2]; // [esp+8h] [ebp-28h] BYREF
  S900 *v13[4]; // [esp+10h] [ebp-20h] BYREF
  _DWORD v14[2]; // [esp+20h] [ebp-10h] BYREF
  _DWORD v15[2]; // [esp+28h] [ebp-8h] BYREF

  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&v11);
  TimeToReload = self->TimeToReload;
  if ( TimeToReload )
  {
    result = TimeToReload - 1;
    self->TimeToReload = result;
  }
  else
  {
    Car = self->Car;
    self->Ped_ = gta2::Car_GetDriver(Car);
    LOWORD(v11) = *(_WORD *)*gta2::Car_sub_4BE980(Car, 248);
    gta2::bitShiftLeft1(a2, 0);
    gta2::Weapon_sub_432860((Weapon *)v13, a2, &unk_673A04);
    gta2::Tango_sub_40F6B0((Tango *)v13, (S900 *)&v11);
    gta2::bitShiftLeft1(a2, 0);
    gta2::Weapon_sub_432860((Weapon *)v14, a2, &unk_673CB0);
    v4 = self->Car;
    gta2::Tango_sub_40F6B0((Tango *)v14, (S900 *)v4->CarSprite);
    v5 = gta2::SpriteS1_sub_4207B0(v4->CarSprite, a2);
    v6 = gta2::S103_sub_40F5C0((S103 *)v14, v15, v5);
    gta2::Tango_sub_40F680((Tango *)v13, (int)v6);
    v7 = (S900 **)gta2::Player_sub_4A0D10(v4->Player_, v15, (Ped *)v13);
    v13[2] = *v7;
    v13[3] = v7[1];
    gta2::Weapon_Set_4CCA80(self, 1);
    if ( self->SMG )
    {
      gta2::Weapon_sub_4CDA90(self, 154, v13[0]);
      self->TimeToReload = 1;
    }
    else
    {
      if ( gta2::Weapon_sub_4CDA90(self, 254, v13[0]) )
      {
        if ( gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
          gta2::Weapon_Decrement1Ammo(self);
      }
      Ped = self->Ped_;
      self->TimeToReload = 2;
      gta2::Ped_sub_4350A0(Ped);
      v9 = self->Ped_;
      if ( gta2::Ped_IsPlayerControlled(v9) )
      {
        gta2::S127_HandlePedInteraction(gS127, 2u, v9);
        return gta2::Weapon_TimeToReload(self);
      }
    }
    return gta2::Weapon_TimeToReload(self);
  }
  return result;
}


// 0x004d0230: Weapon::sub_4D0230
// IDA: Weapon::sub_4D0230
// Ghidra: Weapon::FUN_004d0230
byte gta2::Weapon_sub_4D0230(struct Weapon *self)
{
  struct Car *pCVar1;
  SpriteS1 *this_00;
  bool bVar2;
  byte bVar3;
  struct Ped *pPVar4;
  Model *pMVar5;
  SpriteS1 *pSVar6;
  SpriteS1 *pSVar7;
  int iVar8;
  undefined4 *puVar9;
  int *piVar10;
  EventHandler *pEVar11;
  EventHandler *pEVar12;
  struct Ped *pPed;
  SpawnPoint **ppSVar13;
  struct Ped **ppPVar14;
  S127 *pSVar15;
  GlassInfo local_48;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&local_48);
  if (self->TimeToReload == 0) {
    pCVar1 = self->Car;
    pPVar4 = gta2::Car_GetDriver(pCVar1);
    self->Ped_ = pPVar4;
    this_00 = (SpriteS1 *)pCVar1->CarSprite;
    pSVar7 = (SpriteS1 *)&local_48.pPed;
    pSVar15 = (S127 *)&DAT_0067397c;
    ppSVar13 = &local_48.SpawnPoint;
    local_48.car = (Car *)CONCAT22(local_48.car._2_2_,
                                   *(undefined2 *)&this_00->FirstElement);
    pSVar6 = (SpriteS1 *)&local_48.field_0xc;
    local_48.SpawnPoint = (SpawnPoint *)0x2;
    pMVar5 = (Model *)FUN_0048a930(&local_48.field_0x10);
    pSVar6 = gta2::S122_sub_401BF0(pMVar5,pSVar6,(int *)ppSVar13);
    pSVar7 = gta2::S202_sub_401B20((Point2D *)pSVar6,pSVar7,pSVar15);
    local_48.SpawnPoint = (SpawnPoint *)pSVar7->FirstElement;
    pSVar7 = (SpriteS1 *)&local_48.field11_0x14;
    pSVar15 = (S127 *)&DAT_00673c64;
    ppPVar14 = &local_48.pPed;
    pSVar6 = (SpriteS1 *)&local_48.field12_0x18;
    local_48.pPed = (Ped *)0x2;
    pMVar5 = (Model *)FUN_0048a950(&local_48.field_0x10);
    pSVar6 = gta2::S122_sub_401BF0(pMVar5,pSVar6,(int *)ppPVar14);
    pSVar7 = gta2::S202_sub_401B20((Point2D *)pSVar6,pSVar7,pSVar15);
    local_48.pPed = (Ped *)pSVar7->FirstElement;
    FUN_00432860(&local_48.field17_0x20,&local_48.SpawnPoint,&local_48.pPed);
    FUN_0040f6b0(&local_48.field17_0x20,&local_48);
    iVar8 = gta2::SpriteS1_sub_4207B0(this_00,&local_48.field12_0x18);
    FUN_0040f680(&local_48.field17_0x20,iVar8);
    ppPVar14 = &local_48.pPed;
    puVar9 = (undefined4 *)
             gta2::JustCopyByPtrAtoC(&local_48.SpawnPoint,&local_48.field12_0x18);
    FUN_00432860(&local_48.field19_0x28,puVar9,ppPVar14);
    FUN_0040f6b0(&local_48.field19_0x28,&local_48);
    iVar8 = gta2::SpriteS1_sub_4207B0(this_00,&local_48.field12_0x18);
    FUN_0040f680(&local_48.field19_0x28,iVar8);
    piVar10 = (int *)gta2::Player_sub_4A0D10(pCVar1->Player_,&local_48.field12_0x18,
                                (GlassInfo *)&local_48.field17_0x20);
    local_18 = *piVar10;
    local_14 = piVar10[1];
    piVar10 = (int *)gta2::Player_sub_4A0D10(self->Car->Player_,&local_48.field12_0x18,
                                (GlassInfo *)&local_48.field19_0x28);
    pCVar1 = local_48.car;
    local_10 = *piVar10;
    local_c = piVar10[1];
    if (self->TypeWeapons == 0) {
      pEVar11 = gta2::Weapon_sub_4CDA90(self,0xfe,local_48.field17_0x20,local_48.field18_0x24
                           ,this_00->Matrix3DArray[0].PositionZ,
                           (GlassInfo *)local_48.car,(Ped *)&local_18);
      pEVar12 = gta2::Weapon_sub_4CDA90(self,0xfe,local_48.field19_0x28,local_48._44_4_,
                           this_00->Matrix3DArray[0].PositionZ,
                           (GlassInfo *)pCVar1,(Ped *)&local_10);
      if ((pEVar11 != NULL) || (pEVar12 != NULL)) {
        bVar2 = gta2::Ped_IsSearchType(self->Ped_,
                                   SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
        if (bVar2) {
          gta2::Weapon_Decrement1Ammo(self);
        }
      }
      FUN_0048cd10((SpriteS1 *)self->Car->CarSprite);
      self->TimeToReload = 2;
      gta2::Ped_sub_4350A0(self->Ped_);
      pPVar4 = self->Ped_;
      bVar3 = gta2::Ped_IsPlayerControlled(pPVar4);
      if (bVar3 != 0) {
        gta2::S127_HandlePedInteraction(gS127,2,pPVar4);
      }
    }
    else {
      gta2::Weapon_sub_4CDA90(self,0x9a,local_48.field17_0x20,local_48.field18_0x24,
                 this_00->Matrix3DArray[0].PositionZ,(GlassInfo *)local_48.car,
                 (Ped *)&local_18);
      gta2::Weapon_sub_4CDA90(self,0x9a,local_48.field19_0x28,local_48._44_4_,
                 this_00->Matrix3DArray[0].PositionZ,(GlassInfo *)pCVar1,
                 (Ped *)&local_10);
      self->TimeToReload = 1;
    }
    pPed = (Ped *)gta2::Weapon_TimeToReload(self);
    pPed._0_1_ = (byte)pPed;
    gta2::Weapon_Set_4CCA80(self,1);
    return (byte)pPed;
  }
  bVar3 = self->TimeToReload - 1;
  self->TimeToReload = bVar3;
  return bVar3;
}


// 0x004d04b0: Weapon::FUN_004d04b0
// IDA: ---
// Ghidra: Weapon::FUN_004d04b0
byte gta2::Weapon_FUN_004d04b0(struct Weapon *self)
{
  byte ptImer;
  SpriteS1 *pSVar1;
  SpriteS1 *pSVar2;
  struct Ped *pPed;
  struct Player *pPlayer;
  
  if (self->TimeToReload != 0) {
    ptImer = self->TimeToReload - 1;
    self->TimeToReload = ptImer;
    return ptImer;
  }
  pPed = self->Ped_;
  if (((pPed != NULL) && (pPlayer = pPed->isPlayer, pPlayer != NULL)) &&
     ((pPed = (Ped *)self->TypeWeapon, pPed == (Ped *)0x4 ||
      (pPed == (Ped *)0x5)))) {
    ptImer = gta2::Player_FUN_004ccb00(pPlayer);
    if (ptImer != 0) {
      pSVar1 = (SpriteS1 *)gta2::Player_sub_4CCAE0(pPlayer);
      pSVar2 = (SpriteS1 *)gta2::Player_sub_4CCAD0(pPlayer);
      gta2::Weapon_sub_4CE970(self,(undefined1 *)
                      ((-(uint)(pPed != (Ped *)0x4) & 0x2d) + 0x8a),pSVar2,
                 pSVar1);
    }
    pPed = self->Ped_;
    gta2::Player_sub_4A5180(pPed->isPlayer);
    return (byte)pPed;
  }
  return (byte)pPed;
}


// 0x004d0530: Weapon::FUN_004d0530
// IDA: ---
// Ghidra: Weapon::FUN_004d0530
byte gta2::Weapon_FUN_004d0530(struct Weapon *self)
{
  undefined4 uVar1;
  bool bVar2;
  SpriteS1 *pSVar4;
  undefined3 extraout_var;
  SpriteS1 *pSVar5;
  Point2D *pPVar6;
  int iVar7;
  Model *pMVar8;
  undefined4 *puVar9;
  undefined3 extraout_var_00;
  short *psVar10;
  struct Ped *pPVar11;
  undefined3 extraout_var_01;
  uint uVar12;
  byte bVar3;
  undefined2 *puVar13;
  SpriteS1 *pSVar14;
  struct Car *pCVar15;
  int *piVar16;
  SpriteS1 *pSVar17;
  void *pvVar18;
  EventHandler *pEVar19;
  WeaponType pSecond;
  int minut;
  undefined2 extraout_var_02;
  GlassInfo *pGVar20;
  undefined2 extraout_var_03;
  undefined2 extraout_var_04;
  undefined2 extraout_var_05;
  undefined2 extraout_var_06;
  undefined2 extraout_var_07;
  undefined2 extraout_var_08;
  undefined2 extraout_var_09;
  undefined2 extraout_var_10;
  undefined2 extraout_var_11;
  undefined2 extraout_var_12;
  undefined2 extraout_var_13;
  undefined2 extraout_var_14;
  undefined2 extraout_var_15;
  undefined2 extraout_var_16;
  SpriteS1 *unaff_EBP;
  SpriteS1 *unaff_ESI;
  SpriteS1 *unaff_EDI;
  S127 *pSVar21;
  SpriteS1 **ppSVar22;
  S127 *pS127;
  undefined1 *puVar23;
  undefined4 uVar24;
  undefined4 *puVar25;
  SpriteS1 *pSpriteS1;
  undefined4 in_stack_ffffffcc;
  undefined2 uVar26;
  SpriteS1 *in_stack_ffffffd4;
  ushort uVar27;
  SpriteS1 *in_stack_ffffffdc;
  undefined2 uVar28;
  SpriteS1 *in_stack_ffffffe0;
  undefined4 uStack_1c;
  SpriteS1 *pSStack_18;
  struct Ped *pPed;
  struct Player *pPlayer;
  
  uVar27 = (ushort)((uint)in_stack_ffffffdc >> 0x10);
  uVar28 = (undefined2)((uint)in_stack_ffffffcc >> 0x10);
  uVar26 = (undefined2)((uint)in_stack_ffffffd4 >> 0x10);
  pSVar17 = (SpriteS1 *)&stack0xfffffff8;
  pSecond = self->TypeWeapon;
  switch(pSecond) {
  case Pistol:
    gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&stack0xffffffdc);
    if (self->TimeToReload != 0) {
      bVar3 = self->TimeToReload - 1;
      self->TimeToReload = bVar3;
      return bVar3;
    }
    gta2::Weapon_Set_4CCA80(self,1);
    if (self->TypeWeapons == 0) {
      bVar2 = gta2::Ped_IsSearchType(self->Ped_,SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY)
      ;
      pPed = self->Ped_;
      gta2::Ped_GetXCoordinate(pPed,(int)&uStack_1c);
      piVar16 = (int *)gta2::Ped_GetYCoordinate(pPed, &uStack_1c);
      uStack_1c = (SpriteS1 *)*piVar16;
      puVar25 = (undefined4 *)gta2::Ped_GetPositionZ(pPed,(int)&stack0xffffffd8);
      uVar24 = *puVar25;
      psVar10 = gta2::Ped_GetRotation(pPed,(short *)&stack0xffffffd8);
      pSVar4 = (SpriteS1 *)CONCAT22(uVar27,*psVar10);
      gta2::Ped_sub_435C20(self->Ped_,&pSStack_18);
      FUN_0041e210(&pSStack_18,(GlassInfo *)&DAT_00673be4,
                   (Ped *)&stack0xffffffdc);
      pSVar17 = gta2::S202_sub_401B20((Point2D *)&stack0xffffffe0,
                           (SpriteS1 *)&stack0xffffffd8,(S127 *)&pSStack_18);
      pSVar17 = pSVar17->FirstElement;
      pSVar14 = gta2::S202_sub_401B20((Point2D *)&uStack_1c,(SpriteS1 *)&stack0xffffffe0,
                           (S127 *)&stack0xffffffec);
      pEVar19 = gta2::Weapon_sub_4CDA90(self,(-(uint)bVar2 & 0xb) + 0xfe,pSVar17,
                           pSVar14->FirstElement,uVar24,(GlassInfo *)pSVar4,
                           (Ped *)&stack0xfffffff0);
      if ((pEVar19 != NULL) &&
         (bVar2 = gta2::Ped_IsSearchType(self->Ped_,
                                     SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY),
         bVar2)) {
        gta2::Weapon_Decrement10Ammo(self);
      }
      self->TimeToReload = 0x14;
      FUN_0048cd10(*(SpriteS1 **)&self->Ped_->GameObject_->AIState);
      gta2::Ped_sub_4350A0(self->Ped_);
      pPed = self->Ped_;
      bVar3 = gta2::Ped_IsPlayerControlled(pPed);
      if (bVar3 != 0) {
        gta2::S127_HandlePedInteraction(gS127,2,pPed);
        pvVar18 = gta2::Weapon_TimeToReload(self);
        return (byte)pvVar18;
      }
    }
    else {
      pPed = self->Ped_;
      puVar13 = (undefined2 *)&stack0xffffffd8;
      gta2::Ped_FUN_004cca90(pPed,puVar13);
      puVar25 = (undefined4 *)gta2::Ped_GetPositionZ(pPed,(int)&stack0xffffffe0);
      uStack_1c = (SpriteS1 *)gta2::Ped_GetYCoordinate(pPed, &stack0xffffffdc);
      pPVar11 = (Ped *)gta2::Ped_GetXCoordinate(pPed,(int)&pSStack_18);
      pPed = pPVar11;
      gta2::Ped_sub_435C20(self->Ped_,(undefined4 *)&stack0xfffffff8);
      gta2::Weapon_sub_4CDA90(self,0x9a,*(void **)pPVar11->S200_,uStack_1c->FirstElement,
                 *puVar25,(GlassInfo *)CONCAT22(extraout_var_11,*puVar13),pPed);
      self->TimeToReload = 5;
    }
    pvVar18 = gta2::Weapon_TimeToReload(self);
    return (byte)pvVar18;
  case SNG:
  case SMG_S:
    if (self->TimeToReload != 0) {
      bVar3 = self->TimeToReload - 1;
      self->TimeToReload = bVar3;
      return bVar3;
    }
    gta2::Weapon_Set_4CCA80(self,1);
    puVar13 = (undefined2 *)&stack0xffffffcc;
    if (self->TypeWeapons == 0) {
      gta2::Ped_ComputeFacingRotation(self->Ped_,puVar13);
      pGVar20 = (GlassInfo *)CONCAT22(uVar28,*puVar13);
      piVar16 = (int *)gta2::JustCopyByPtrAtoC(&DAT_00673c6c,&stack0xffffffd0);
      pSStack_18 = (SpriteS1 *)*piVar16;
      gta2::S202_sub_401B20((Point2D *)&DAT_0067395c,(SpriteS1 *)&stack0xffffffd0,
                 (S127 *)&DAT_00673c3c);
      pPed = self->Ped_;
      pSVar17 = (SpriteS1 *)pPed->GameObject_;
      FUN_0040f6b0(&pSStack_18,(GlassInfo *)pSVar17->Matrix3DArray[2].Car);
      gta2::Ped_sub_435C20(pPed,(undefined4 *)&stack0xffffffd0);
      puVar25 = (undefined4 *)FUN_0040f5c0(&pSStack_18,&stack0xfffffff0,pSVar17)
      ;
      pSStack_18 = (SpriteS1 *)*puVar25;
      pPed = self->Ped_;
      puVar25 = (undefined4 *)gta2::Ped_GetPositionZ(pPed,(int)&stack0xffffffd0);
      pSVar21 = (S127 *)&stack0xffffffec;
      pSVar17 = (SpriteS1 *)&stack0xffffffd8;
      pPVar6 = (Point2D *)gta2::Ped_GetYCoordinate(pPed, &stack0xffffffdc);
      pSVar14 = gta2::S202_sub_401B20(pPVar6,pSVar17,pSVar21);
      pSVar21 = (S127 *)&pSStack_18;
      pSVar17 = (SpriteS1 *)&stack0xffffffe0;
      pPVar6 = (Point2D *)gta2::Ped_GetXCoordinate(pPed,(int)&uStack_1c);
      pSVar4 = gta2::S202_sub_401B20(pPVar6,pSVar17,pSVar21);
      pSVar17 = pSVar4;
      gta2::Ped_sub_435C20(self->Ped_,(undefined4 *)&stack0xfffffff8);
      pEVar19 = gta2::Weapon_sub_4CDA90(self,0xfe,pSVar4->FirstElement,pSVar14->FirstElement,
                           *puVar25,pGVar20,(Ped *)pSVar17);
      if ((pEVar19 != NULL) &&
         (bVar2 = gta2::Ped_IsSearchType(self->Ped_,
                                     SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY),
         bVar2)) {
        gta2::Weapon_Decrement1Ammo(self);
      }
      self->TimeToReload = 2;
      FUN_0048cd10(*(SpriteS1 **)&self->Ped_->GameObject_->AIState);
      if (self->TypeWeapon != SMG_S) {
        gta2::Ped_sub_4350A0(self->Ped_);
        pPed = self->Ped_;
        bVar3 = gta2::Ped_IsPlayerControlled(pPed);
        if (bVar3 != 0) {
          gta2::S127_HandlePedInteraction(gS127,2,pPed);
          pvVar18 = gta2::Weapon_TimeToReload(self);
          return (byte)pvVar18;
        }
      }
    }
    else {
      pPed = self->Ped_;
      gta2::Ped_FUN_004cca90(pPed,puVar13);
      puVar25 = (undefined4 *)gta2::Ped_GetPositionZ(pPed,(int)&uStack_1c);
      pSVar17 = (SpriteS1 *)gta2::Ped_GetYCoordinate(pPed, &stack0xffffffe0);
      pPVar11 = (Ped *)gta2::Ped_GetXCoordinate(pPed,(int)&stack0xffffffdc);
      pPed = pPVar11;
      gta2::Ped_sub_435C20(self->Ped_,(undefined4 *)&stack0xfffffff8);
      gta2::Weapon_sub_4CDA90(self,0x9a,*(void **)pPVar11->S200_,pSVar17->FirstElement,
                 *puVar25,(GlassInfo *)CONCAT22(extraout_var_13,*puVar13),pPed);
      self->TimeToReload = 1;
    }
    pvVar18 = gta2::Weapon_TimeToReload(self);
    return (byte)pvVar18;
  case RPG:
    if (self->TimeToReload != 0) {
      if (self->field12_0x20 == '\0') {
        pPed = self->Ped_;
        uVar12._0_1_ = pPed->CurrentAction;
        uVar12._1_1_ = pPed->DamageState;
        uVar12._2_1_ = pPed->uns60;
        uVar12._3_1_ = pPed->uns61;
        uVar12 = uVar12 & 0xffbfffff;
        pPed->CurrentAction = (char)uVar12;
        pPed->DamageState = (char)(uVar12 >> 8);
        pPed->uns60 = (char)(uVar12 >> 0x10);
        pPed->uns61 = (char)(uVar12 >> 0x18);
      }
      bVar3 = self->TimeToReload - 1;
      self->TimeToReload = bVar3;
      return bVar3;
    }
    gta2::Weapon_Set_4CCA80(self,1);
    if (self->TypeWeapons == 0) {
      bVar2 = gta2::Ped_IsSearchType(self->Ped_,SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY)
      ;
      pPed = self->Ped_;
      if (bVar2) {
        puVar13 = (undefined2 *)((int)&uStack_1c + 2);
        gta2::Ped_FUN_004cca90(pPed,puVar13);
        puVar25 = (undefined4 *)gta2::Ped_GetPositionZ(pPed,(int)&stack0xffffffec);
        pSStack_18 = (SpriteS1 *)gta2::Ped_GetYCoordinate(pPed, &stack0xfffffff0);
        pSVar4 = (SpriteS1 *)gta2::Ped_GetXCoordinate(pPed,(int)&stack0xfffffff4);
        pSVar17 = pSVar4;
        gta2::Ped_sub_435C20(self->Ped_,(undefined4 *)&stack0xfffffff8);
        pGVar20 = (GlassInfo *)CONCAT22(extraout_var_14,*puVar13);
        uVar24 = *puVar25;
        pSVar14 = pSStack_18->FirstElement;
        pvVar18 = *(void **)&pSVar4->FirstElement;
      }
      else {
        puVar13 = (undefined2 *)CONCAT31(extraout_var_01,self->field12_0x20);
        if (self->field12_0x20 == '\0') {
          gta2::Ped_FUN_004cca90(pPed,(undefined2 *)((int)&uStack_1c + 2));
          puVar25 = (undefined4 *)gta2::Ped_GetPositionZ(pPed,(int)&stack0xfffffff4);
          pSStack_18 = (SpriteS1 *)gta2::Ped_GetYCoordinate(pPed, &stack0xfffffff0)
          ;
          pPVar11 = (Ped *)gta2::Ped_GetXCoordinate(pPed,(int)&stack0xffffffec);
          pPed = pPVar11;
          gta2::Ped_sub_435C20(self->Ped_,(undefined4 *)&stack0xfffffff8);
          pEVar19 = gta2::Weapon_sub_4CDA90(self,0x9f,*(void **)pPVar11->S200_,
                               pSStack_18->FirstElement,*puVar25,
                               (GlassInfo *)
                               CONCAT22((short)((uint)pPed >> 0x10),*puVar13),
                               pPed);
          self->TimeToReload = 5;
          self->field12_0x20 = 1;
          return (byte)pEVar19;
        }
        gta2::Ped_FUN_004cca90(pPed,(undefined2 *)((int)&uStack_1c + 2));
        puVar25 = (undefined4 *)gta2::Ped_GetPositionZ(pPed,(int)&stack0xfffffff4);
        pSStack_18 = (SpriteS1 *)gta2::Ped_GetYCoordinate(pPed, &stack0xfffffff0);
        puVar9 = (undefined4 *)gta2::Ped_GetXCoordinate(pPed,(int)&stack0xffffffec);
        gta2::Ped_sub_435C20(self->Ped_,(undefined4 *)&stack0xfffffff8);
        pGVar20 = (GlassInfo *)CONCAT22(extraout_var_02,*puVar13);
        uVar24 = *puVar25;
        pSVar14 = pSStack_18->FirstElement;
        pvVar18 = (void *)*puVar9;
      }
      pEVar19 = gta2::Weapon_sub_4CDA90(self,0x80,pvVar18,pSVar14,uVar24,pGVar20,
                           (Ped *)pSVar17);
      gta2::Ped_sub_4350A0(self->Ped_);
      if ((pEVar19 != NULL) &&
         (bVar2 = gta2::Ped_IsSearchType(self->Ped_,
                                     SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY),
         bVar2)) {
        gta2::Weapon_Decrement10Ammo(self);
      }
      self->TimeToReload = 0x32;
      FUN_0048cd10(*(SpriteS1 **)&self->Ped_->GameObject_->AIState);
      pPed = self->Ped_;
      self->field12_0x20 = 0;
      bVar3 = gta2::Ped_IsPlayerControlled(pPed);
      if (bVar3 != 0) {
        gta2::S127_HandlePedInteraction(gS127,2,pPed);
        pvVar18 = gta2::Weapon_TimeToReload(self);
        return (byte)pvVar18;
      }
    }
    else {
      pPed = self->Ped_;
      puVar13 = (undefined2 *)((int)&uStack_1c + 2);
      gta2::Ped_FUN_004cca90(pPed,puVar13);
      puVar25 = (undefined4 *)gta2::Ped_GetPositionZ(pPed,(int)&stack0xfffffff4);
      pSStack_18 = (SpriteS1 *)gta2::Ped_GetYCoordinate(pPed, &stack0xfffffff0);
      pPVar11 = (Ped *)gta2::Ped_GetXCoordinate(pPed,(int)&stack0xffffffec);
      pPed = pPVar11;
      gta2::Ped_sub_435C20(self->Ped_,(undefined4 *)&stack0xfffffff8);
      gta2::Weapon_sub_4CDA90(self,0x9f,*(void **)pPVar11->S200_,pSStack_18->FirstElement,
                 *puVar25,(GlassInfo *)CONCAT22(extraout_var_15,*puVar13),pPed);
      self->TimeToReload = 5;
      self->field12_0x20 = 0;
    }
    pvVar18 = gta2::Weapon_TimeToReload(self);
    return (byte)pvVar18;
  case ElctoGan:
    bVar3 = gta2::Weapon_FUN_004cf9e0(self);
    return bVar3;
  case Molotov:
    pPlayer = (Player *)self->Ped_;
    if ((pPlayer != NULL) && (pPlayer = pPlayer->Player2, pPlayer != NULL)) {
      gta2::Player_sub_4CCAB0(pPlayer);
      return (byte)pPlayer;
    }
    bVar3 = (byte)pPlayer;
    pSStack_18 = (SpriteS1 *)0x4d05ce;
    gta2::Weapon_sub_4CE970(self,(undefined1 *)0x8a,(SpriteS1 *)0x1e,(SpriteS1 *)0x2d);
    return bVar3;
  case Granata:
    pPed = self->Ped_;
    if ((pPed == NULL) || (pPed->isPlayer == NULL)) {
      pSStack_18 = (SpriteS1 *)0x4d0638;
      gta2::Weapon_sub_4CE970(self,(undefined1 *)0xb7,(SpriteS1 *)0x1e,(SpriteS1 *)0x2d);
      return (byte)pPed;
    }
    gta2::Player_sub_4CCAB0(pPed->isPlayer);
    pPlayer = self->Ped_->isPlayer;
    pSecond = gta2::Player_sub_4CCAE0(pPlayer);
    if (pSecond == 0x60) {
      pSVar17 = (SpriteS1 *)gta2::Player_sub_4CCAE0(pPlayer);
      minut = gta2::Player_sub_4CCAD0(pPlayer);
      pSStack_18 = (SpriteS1 *)0x4d0618;
      gta2::Weapon_sub_4CE970(self,(undefined1 *)183,(SpriteS1 *)minut,pSVar17);
      self->Ped_->isPlayer->timeSecond = -1;
      return (byte)minut;
    }
    break;
  case ShotGun:
    gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&stack0xffffffe0);
    uVar28 = (undefined2)((uint)in_stack_ffffffe0 >> 0x10);
    if (self->TimeToReload != 0) {
      bVar3 = self->TimeToReload - 1;
      self->TimeToReload = bVar3;
      return bVar3;
    }
    pPed = self->Ped_;
    puVar25 = (undefined4 *)gta2::Ped_GetXCoordinate(pPed,(int)&stack0xfffffff0);
    pvVar18 = (void *)*puVar25;
    puVar25 = (undefined4 *)gta2::Ped_GetYCoordinate(pPed, &stack0xfffffff0);
    uVar24 = *puVar25;
    puVar25 = (undefined4 *)gta2::Ped_GetPositionZ(pPed,(int)&stack0xfffffff0);
    uVar1 = *puVar25;
    psVar10 = gta2::Ped_GetRotation(self->Ped_,(short *)&stack0xffffffde);
    pSVar17 = (SpriteS1 *)CONCAT22(uVar28,*psVar10);
    gta2::Ped_sub_435C20(self->Ped_,(undefined4 *)&stack0xfffffff0);
    gta2::Weapon_Set_4CCA80(self,1);
    if (self->TypeWeapons == 0) {
      puVar13 = (undefined2 *)
                gta2::sub_40E5A0((CarSystemManager *)&stack0xffffffe0,
                           (Ped *)&stack0xffffffde,(short *)&DAT_00673a44,
                           unaff_EDI,(short *)unaff_EBP);
      uStack_1c = (SpriteS1 *)
                  gta2::Weapon_sub_4CDA90(self,0xc0,pvVar18,uVar24,uVar1,
                             (GlassInfo *)CONCAT22(extraout_var_03,*puVar13),
                             (Ped *)&stack0xfffffff8);
      puVar13 = (undefined2 *)
                gta2::sub_40E5A0((CarSystemManager *)&stack0xffffffe0,
                           (Ped *)&stack0xffffffde,(short *)&DAT_00673ce4,
                           unaff_EDI,(short *)unaff_EBP);
      pSStack_18 = (SpriteS1 *)
                   gta2::Weapon_sub_4CDA90(self,0xc0,pvVar18,uVar24,uVar1,
                              (GlassInfo *)CONCAT22(extraout_var_04,*puVar13),
                              (Ped *)&stack0xfffffff8);
      pSVar17 = (SpriteS1 *)
                gta2::Weapon_sub_4CDA90(self,0xc0,pvVar18,uVar24,uVar1,(GlassInfo *)pSVar17,
                           (Ped *)&stack0xfffffff8);
      puVar13 = (undefined2 *)
                gta2::SpriteS1_sub_40E5D0((CarSystemManager *)&stack0xffffffe0,
                           (Ped *)&stack0xffffffde,0x673ce4);
      pSVar14 = (SpriteS1 *)
                gta2::Weapon_sub_4CDA90(self,0xc0,pvVar18,uVar24,uVar1,
                           (GlassInfo *)CONCAT22(extraout_var_05,*puVar13),
                           (Ped *)&stack0xfffffff8);
      puVar13 = (undefined2 *)
                gta2::SpriteS1_sub_40E5D0((CarSystemManager *)&stack0xffffffe0,
                           (Ped *)&stack0xffffffde,0x673a44);
      pEVar19 = gta2::Weapon_sub_4CDA90(self,0xc0,pvVar18,uVar24,uVar1,
                           (GlassInfo *)CONCAT22(extraout_var_06,*puVar13),
                           (Ped *)&stack0xfffffff8);
      if (((((uStack_1c != NULL) || (pSStack_18 != NULL)) || (pSVar17 != NULL))
          || ((pSVar14 != NULL || (pEVar19 != NULL)))) &&
         (bVar2 = gta2::Ped_IsSearchType(self->Ped_,
                                     SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY),
         bVar2)) {
        gta2::Weapon_Decrement10Ammo(self);
      }
      self->TimeToReload = 0x28;
      gta2::Ped_sub_4350A0(self->Ped_);
      FUN_0048cd10(*(SpriteS1 **)&self->Ped_->GameObject_->AIState);
      pPed = self->Ped_;
      bVar3 = gta2::Ped_IsPlayerControlled(pPed);
      if (bVar3 != 0) {
        gta2::S127_HandlePedInteraction(gS127,2,pPed);
        pvVar18 = gta2::Weapon_TimeToReload(self);
        return (byte)pvVar18;
      }
    }
    else {
      puVar13 = (undefined2 *)
                gta2::sub_40E5A0((CarSystemManager *)&stack0xffffffe0,
                           (Ped *)&stack0xffffffde,(short *)&DAT_006739bc,
                           unaff_EDI,(short *)unaff_EBP);
      gta2::Weapon_sub_4CDA90(self,0xc1,pvVar18,uVar24,uVar1,
                 (GlassInfo *)CONCAT22(extraout_var_07,*puVar13),
                 (Ped *)&stack0xfffffff8);
      puVar13 = (undefined2 *)
                gta2::sub_40E5A0((CarSystemManager *)&stack0xffffffe0,
                           (Ped *)&stack0xffffffde,(short *)&DAT_00673a44,
                           unaff_EDI,(short *)unaff_EBP);
      gta2::Weapon_sub_4CDA90(self,0xc1,pvVar18,uVar24,uVar1,
                 (GlassInfo *)CONCAT22(extraout_var_08,*puVar13),
                 (Ped *)&stack0xfffffff8);
      gta2::Weapon_sub_4CDA90(self,0xc1,pvVar18,uVar24,uVar1,(GlassInfo *)pSVar17,
                 (Ped *)&stack0xfffffff8);
      puVar13 = (undefined2 *)
                gta2::SpriteS1_sub_40E5D0((CarSystemManager *)&stack0xffffffe0,
                           (Ped *)&stack0xffffffde,0x673a44);
      gta2::Weapon_sub_4CDA90(self,0xc1,pvVar18,uVar24,uVar1,
                 (GlassInfo *)CONCAT22(extraout_var_09,*puVar13),
                 (Ped *)&stack0xfffffff8);
      puVar13 = (undefined2 *)
                gta2::SpriteS1_sub_40E5D0((CarSystemManager *)&stack0xffffffe0,
                           (Ped *)&stack0xffffffde,0x6739bc);
      gta2::Weapon_sub_4CDA90(self,0xc1,pvVar18,uVar24,uVar1,
                 (GlassInfo *)CONCAT22(extraout_var_10,*puVar13),
                 (Ped *)&stack0xfffffff8);
      self->TimeToReload = 5;
    }
    pvVar18 = gta2::Weapon_TimeToReload(self);
    return (byte)pvVar18;
  case Shoker:
    pPed = self->Ped_;
    pPVar11 = pPed->ped3;
    if (pPVar11 != NULL) {
      if (pPVar11->GameObject_ == NULL) {
        pPed->ped3 = NULL;
        return (byte)pPVar11;
      }
      bVar2 = gta2::Ped_IsSearchType(pPed,SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
      uVar12 = (uint)bVar2;
      if (bVar2) {
        pPed = self->Ped_;
        uVar12 = gta2::Ped_GetPedState(pPed->ped3);
        if ((7 < (int)uVar12) && ((int)uVar12 < 10)) {
          pPed->ped3 = NULL;
          return (byte)uVar12;
        }
      }
      bVar3 = (byte)uVar12;
      gta2::Weapon_sub_4CD020(self);
      return bVar3;
    }
    if (self->TimeToReload != 0) {
      bVar3 = self->TimeToReload - 1;
      self->TimeToReload = bVar3;
      return bVar3;
    }
    gta2::Weapon_Set_4CCA80(self,1);
    puVar13 = (undefined2 *)self->TypeWeapons;
    pPed = self->Ped_;
    if (puVar13 != NULL) {
      gta2::Ped_FUN_004cca90(pPed,(undefined2 *)((int)&uStack_1c + 2));
      puVar25 = (undefined4 *)gta2::Ped_GetPositionZ(pPed,(int)&stack0xfffffff4);
      pSStack_18 = (SpriteS1 *)gta2::Ped_GetYCoordinate(pPed, &stack0xfffffff0);
      pPVar11 = (Ped *)gta2::Ped_GetXCoordinate(pPed,(int)&stack0xffffffec);
      pPed = pPVar11;
      gta2::Ped_sub_435C20(self->Ped_,(undefined4 *)&stack0xfffffff8);
      gta2::Weapon_sub_4CDA90(self,0x9a,*(void **)pPVar11->S200_,pSStack_18->FirstElement,
                 *puVar25,(GlassInfo *)
                          CONCAT22((short)((uint)pPed >> 0x10),*puVar13),pPed);
      self->TimeToReload = 5;
      pvVar18 = gta2::Weapon_TimeToReload(self);
      return (byte)pvVar18;
    }
    puVar13 = (undefined2 *)((int)&uStack_1c + 2);
    gta2::Ped_FUN_004cca90(pPed,puVar13);
    puVar25 = (undefined4 *)gta2::Ped_GetPositionZ(pPed,(int)&stack0xffffffec);
    pSStack_18 = (SpriteS1 *)gta2::Ped_GetYCoordinate(pPed, &stack0xfffffff0);
    pPVar11 = (Ped *)gta2::Ped_GetXCoordinate(pPed,(int)&stack0xfffffff4);
    pPed = pPVar11;
    gta2::Ped_sub_435C20(self->Ped_,(undefined4 *)&stack0xfffffff8);
    pEVar19 = gta2::Weapon_sub_4CDA90(self,0x115,*(void **)pPVar11->S200_,
                         pSStack_18->FirstElement,*puVar25,
                         (GlassInfo *)CONCAT22(extraout_var_16,*puVar13),pPed);
    if ((pEVar19 != NULL) &&
       (bVar2 = gta2::Ped_IsSearchType(self->Ped_,
                                   SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY), bVar2)
       ) {
      gta2::Weapon_Decrement10Ammo(self);
    }
    self->TimeToReload = 0x14;
    pvVar18 = gta2::Weapon_TimeToReload(self);
    return (byte)pvVar18;
  case FireGun:
    gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&uStack_1c);
    pPed = self->Ped_;
    puVar25 = (undefined4 *)gta2::Ped_GetXCoordinate(pPed,(int)&stack0xffffffec);
    pSVar17 = (SpriteS1 *)*puVar25;
    piVar16 = (int *)gta2::Ped_GetYCoordinate(pPed, &pSStack_18);
    pSStack_18 = (SpriteS1 *)*piVar16;
    puVar25 = (undefined4 *)gta2::Ped_GetPositionZ(pPed,(int)&stack0xffffffe0);
    uVar24 = *puVar25;
    psVar10 = gta2::Ped_GetRotation(pPed,(short *)&stack0xffffffe0);
    uStack_1c = (SpriteS1 *)CONCAT22(uStack_1c._2_2_,*psVar10);
    gta2::Ped_sub_435C20(self->Ped_,(undefined4 *)&stack0xfffffff8);
    FUN_0041e210(&stack0xfffffff8,(GlassInfo *)&DAT_00673be4,(Ped *)&uStack_1c);
    pSVar14 = gta2::S202_sub_401B20((Point2D *)&stack0xffffffec,
                         (SpriteS1 *)&stack0xffffffe0,(S127 *)&stack0xfffffff8);
    pSVar14 = pSVar14->FirstElement;
    pSVar4 = gta2::S202_sub_401B20((Point2D *)&pSStack_18,(SpriteS1 *)&stack0xffffffe0,
                        (S127 *)&stack0xfffffffc);
    pSVar4 = pSVar4->FirstElement;
    if (self->TypeWeapons == 0) {
      gta2::Weapon_Set_4CCA80(self,1);
      DAT_00673941 = 0;
      gta2::Weapon_sub_4CDA90(self,0x9a,pSVar14,pSVar4,uVar24,(GlassInfo *)uStack_1c,
                 (Ped *)&stack0xfffffff0);
      bVar3 = DAT_00673941;
      if (DAT_00673941 != 0) {
        gta2::Particles_sub_48D4E0(gParticles,*(GlassInfo **)&self->Ped_->GameObject_->AIState);
        bVar2 = gta2::Ped_IsSearchType(self->Ped_,
                                   SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
        if (bVar2) {
          gta2::Weapon_Decrement1Ammo(self);
        }
        gta2::Ped_sub_4350A0(self->Ped_);
        pPed = self->Ped_;
        bVar3 = gta2::Ped_IsPlayerControlled(pPed);
        if (bVar3 != 0) {
          gta2::S127_HandlePedInteraction(gS127,2,pPed);
          return bVar3;
        }
      }
    }
    else {
      pEVar19 = gta2::Weapon_sub_4CDA90(self,0xc3,pSVar17,pSStack_18,uVar24,
                           (GlassInfo *)uStack_1c,(Ped *)&stack0xfffffff0);
      bVar3 = (byte)pEVar19;
    }
    return bVar3;
  case DualPistol:
    gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&uStack_1c);
    if (self->TimeToReload != 0) {
      bVar3 = self->TimeToReload - 1;
      self->TimeToReload = bVar3;
      return bVar3;
    }
    gta2::Ped_sub_435C20(self->Ped_,(undefined4 *)&stack0xfffffff8);
    pPed = self->Ped_;
    piVar16 = (int *)gta2::Ped_GetXCoordinate(pPed,(int)&stack0xffffffec);
    pSStack_18 = (SpriteS1 *)*piVar16;
    gta2::Ped_GetYCoordinate(pPed, &stack0xffffffec);
    puVar25 = (undefined4 *)gta2::Ped_GetPositionZ(pPed,(int)&stack0xffffffe0);
    uVar24 = *puVar25;
    psVar10 = gta2::Ped_GetRotation(pPed,(short *)&stack0xffffffe0);
    uStack_1c = (SpriteS1 *)CONCAT22(uStack_1c._2_2_,*psVar10);
    gta2::Ped_sub_435C20(self->Ped_,(undefined4 *)&stack0xfffffff8);
    FUN_0041e210(&stack0xfffffff8,(GlassInfo *)&DAT_00673be4,(Ped *)&uStack_1c);
    pSVar17 = gta2::S202_sub_401B20((Point2D *)&pSStack_18,(SpriteS1 *)&stack0xffffffe0,
                         (S127 *)&stack0xfffffff8);
    pSVar17 = pSVar17->FirstElement;
    pSVar14 = gta2::S202_sub_401B20((Point2D *)&stack0xffffffec,(SpriteS1 *)&pSStack_18,
                         (S127 *)&stack0xfffffffc);
    pSVar14 = pSVar14->FirstElement;
    gta2::Weapon_Set_4CCA80(self,1);
    if (self->TypeWeapons == 0) {
      bVar2 = gta2::Ped_IsSearchType(self->Ped_,SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY)
      ;
      pSStack_18 = (SpriteS1 *)((-(uint)bVar2 & 0xb) + 0xfe);
      puVar13 = (undefined2 *)
                gta2::SpriteS1_sub_40E5D0((CarSystemManager *)&uStack_1c,
                           (Ped *)&stack0xffffffe0,0x673a44);
      pSVar4 = (SpriteS1 *)
               gta2::Weapon_sub_4CDA90(self,(int)pSStack_18,pSVar17,pSVar14,uVar24,
                          (GlassInfo *)
                          CONCAT22((short)((uint)puVar13 >> 0x10),*puVar13),
                          (Ped *)&stack0xfffffff0);
      puVar13 = (undefined2 *)
                gta2::sub_40E5A0((CarSystemManager *)&uStack_1c,
                           (Ped *)&stack0xffffffe0,(short *)&DAT_00673a44,
                           unaff_EDI,(short *)unaff_EBP);
      pEVar19 = gta2::Weapon_sub_4CDA90(self,(int)pSStack_18,pSVar17,pSVar14,uVar24,
                           (GlassInfo *)CONCAT22(extraout_var_12,*puVar13),
                           (Ped *)&stack0xfffffff0);
      if (((pSVar4 != NULL) || (pEVar19 != NULL)) &&
         (bVar2 = gta2::Ped_IsSearchType(self->Ped_,
                                     SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY),
         bVar2)) {
        gta2::Weapon_Decrement10Ammo(self);
      }
      self->TimeToReload = 10;
      gta2::Ped_sub_4350A0(self->Ped_);
      FUN_0048cd10(*(SpriteS1 **)&self->Ped_->GameObject_->AIState);
      pPed = self->Ped_;
      bVar3 = gta2::Ped_IsPlayerControlled(pPed);
      if (bVar3 != 0) {
        gta2::S127_HandlePedInteraction(gS127,2,pPed);
        pvVar18 = gta2::Weapon_TimeToReload(self);
        return (byte)pvVar18;
      }
    }
    else {
      puVar13 = (undefined2 *)
                gta2::SpriteS1_sub_40E5D0((CarSystemManager *)&uStack_1c,
                           (Ped *)&stack0xffffffe0,0x673a44);
      gta2::Weapon_sub_4CDA90(self,0x9a,pSVar17,pSVar14,uVar24,
                 (GlassInfo *)CONCAT22((short)((uint)puVar13 >> 0x10),*puVar13),
                 (Ped *)&stack0xfffffff0);
      puVar13 = (undefined2 *)
                gta2::sub_40E5A0((CarSystemManager *)&uStack_1c,
                           (Ped *)&stack0xffffffe0,(short *)&DAT_00673a44,
                           unaff_EDI,(short *)unaff_EBP);
      gta2::Weapon_sub_4CDA90(self,0x9a,pSVar14,pSVar14,uVar24,
                 (GlassInfo *)CONCAT22((short)((uint)puVar13 >> 0x10),*puVar13),
                 (Ped *)&stack0xfffffff0);
      self->TimeToReload = 5;
    }
    pvVar18 = gta2::Weapon_TimeToReload(self);
    return (byte)pvVar18;
  case CAR_BOMB:
    gta2::Weapon_sub_4CD400(self,'\0');
    return (byte)pSecond;
  case CAR_OIL:
    pSVar4 = (SpriteS1 *)gta2::Turrel_sub_41FC70(self->Car);
    puVar25 = &uStack_1c;
    pSVar14 = (SpriteS1 *)&DAT_00673ac8;
    puVar23 = &stack0xffffffec;
    pSVar17 = (SpriteS1 *)&stack0xfffffff4;
    pSVar21 = (S127 *)&DAT_00673ba4;
    pPVar6 = (Point2D *)&stack0xfffffffc;
    FUN_00447e10(pSVar4->Matrix3DArray[0].SpriteS3,(undefined4 *)pPVar6);
    pSVar17 = gta2::S202_sub_401B20(pPVar6,pSVar17,pSVar21);
    pPlayer = (Player *)gta2::JustCopyByPtrAtoC(pSVar17,puVar23);
    piVar16 = (int *)gta2::sub_401B90(pPlayer,puVar25,(int *)pSVar14);
    pSVar17 = (SpriteS1 *)*piVar16;
    bVar3 = gta2::Weapon_GetDisplayAmmo(self);
    pSVar14 = _DAT_00673b9c;
    if ((bVar3 & 1) != 0) {
      piVar16 = (int *)gta2::JustCopyByPtrAtoC(&DAT_00673b9c,&stack0xfffffffc);
      pSVar14 = (SpriteS1 *)*piVar16;
    }
    FUN_0040f6b0(&stack0xffffffec,(GlassInfo *)pSVar4);
    iVar7 = gta2::SpriteS1_sub_4207B0(pSVar4,&stack0xfffffff4);
    FUN_0040f680(&stack0xffffffec,iVar7);
    pSVar5 = (SpriteS1 *)&uStack_1c;
    pSpriteS1 = (SpriteS1 *)&stack0xfffffffc;
    uStack_1c = (SpriteS1 *)0x2;
    pMVar8 = (Model *)FUN_00492170(&stack0xfffffff4);
    pSVar5 = gta2::S122_sub_401BF0(pMVar8,pSpriteS1,(int *)pSVar5);
    uStack_1c = pSVar5->FirstElement;
    puVar25 = &pSVar4->Matrix3DArray[0].PositionZ;
    puVar9 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)puVar25,(GlassInfo *)&stack0xfffffffc,
                        (S127 *)&uStack_1c);
    uVar24 = *puVar9;
    pSVar5 = gta2::S202_sub_401B20((Point2D *)puVar25,(SpriteS1 *)&stack0xfffffffc,
                        (S127 *)&uStack_1c);
    uStack_1c = pSVar5->FirstElement;
    bVar2 = gta2::Player_sub_40CE70((Player *)&uStack_1c,(Player *)&DAT_00673984);
    if (CONCAT31(extraout_var,bVar2) != 0) {
      gta2::Player_sub_401B40((SpawnPoint *)&DAT_00673984,(GlassInfo *)&stack0xfffffffc,
                 (S127 *)&DAT_006739b4);
    }
    bVar3 = FUN_00469dc0(pSVar14,pSVar17,uVar24);
    if (bVar3 != 0) {
      pvVar18 = gta2::Object_SpawnObject(gObject,8,(int)pSVar14,(int)pSVar17,
                                    (int)pSStack_18,
                                    *(short *)&pSVar4->FirstElement);
      bVar3 = (byte)pvVar18;
      gta2::Weapon_Decrement10Ammo(self);
      gta2::Weapon_Set_4CCA80(self,1);
    }
    return bVar3;
  case CAR_MINE:
    pCVar15 = self->Car;
    pPed = gta2::Car_GetDriver(pCVar15);
    self->Ped_ = pPed;
    pSVar5 = (SpriteS1 *)gta2::Turrel_sub_41FC70(pCVar15);
    puVar23 = &stack0xffffffdc;
    pSVar17 = (SpriteS1 *)&uStack_1c;
    pS127 = (S127 *)&DAT_00673a90;
    ppSVar22 = &pSStack_18;
    piVar16 = (int *)&DAT_00673ac8;
    pSVar14 = (SpriteS1 *)&stack0xffffffec;
    pSVar21 = (S127 *)&DAT_00673ad4;
    pSVar4 = pSVar14;
    FUN_00447e10(pSVar5->Matrix3DArray[0].SpriteS3,
                 (undefined4 *)&stack0xfffffff4);
    pSVar14 = gta2::S202_sub_401B20((Point2D *)pSVar14,pSVar4,pSVar21);
    pPVar6 = (Point2D *)
             gta2::sub_401B90((Player *)pSVar14,ppSVar22,piVar16);
    pSVar17 = gta2::S202_sub_401B20(pPVar6,pSVar17,pS127);
    piVar16 = (int *)gta2::JustCopyByPtrAtoC(pSVar17,puVar23);
    pSVar14 = (SpriteS1 *)*piVar16;
    pSVar4 = _DAT_00673a4c;
    FUN_0040f6b0(&stack0xffffffec,(GlassInfo *)pSVar5);
    iVar7 = gta2::SpriteS1_sub_4207B0(pSVar5,&stack0xfffffff4);
    FUN_0040f680(&stack0xffffffec,iVar7);
    piVar16 = (int *)&stack0xffffffdc;
    pSVar17 = (SpriteS1 *)&stack0xfffffffc;
    pMVar8 = (Model *)FUN_00492170(&stack0xfffffff4);
    gta2::S122_sub_401BF0(pMVar8,pSVar17,piVar16);
    puVar25 = &pSVar5->Matrix3DArray[0].PositionZ;
    puVar9 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)puVar25,(GlassInfo *)&stack0xfffffffc,
                        (S127 *)&stack0xffffffdc);
    uVar24 = *puVar9;
    pSVar17 = gta2::S202_sub_401B20((Point2D *)puVar25,(SpriteS1 *)&stack0xfffffffc,
                         (S127 *)&stack0xffffffdc);
    pSVar17 = pSVar17->FirstElement;
    bVar2 = gta2::Player_sub_40CE70((Player *)&stack0xffffffdc,(Player *)&DAT_00673984);
    if (CONCAT31(extraout_var_00,bVar2) != 0) {
      puVar25 = (undefined4 *)
                gta2::Player_sub_401B40((SpawnPoint *)&DAT_00673984,
                           (GlassInfo *)&stack0xfffffffc,(S127 *)&DAT_006739b4);
      pSVar17 = (SpriteS1 *)*puVar25;
    }
    bVar3 = FUN_00469dc0(pSVar4,pSVar14,uVar24,pSVar17,&stack0xffffffe0);
    if (bVar3 != 0) {
      pEVar19 = (EventHandler *)
                gta2::Object_SpawnObject(gObject,10,(int)pSVar4,(int)pSVar14,
                                    (int)in_stack_ffffffe0,
                                    *(short *)&pSVar5->FirstElement);
      bVar3 = gta2::sub_420B50(self->Ped_);
      gta2::S63_sub_482790(pEVar19,bVar3);
      gta2::Weapon_Decrement10Ammo(self);
      gta2::Weapon_Set_4CCA80(self,1);
    }
    return bVar3;
  case CAR_MACHINE_GUN:
    bVar3 = gta2::Weapon_sub_4D0230(self);
    return bVar3;
  case TANK_MAIN_GUN:
    gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&stack0xffffffd4);
    if (self->TimeToReload != 0) {
      bVar3 = self->TimeToReload - 1;
      self->TimeToReload = bVar3;
      return bVar3;
    }
    pCVar15 = self->Car;
    pPed = gta2::Car_GetDriver(pCVar15);
    self->Ped_ = pPed;
    piVar16 = gta2::Car_sub_4BE980(pCVar15,0x94);
    pSVar14 = (SpriteS1 *)CONCAT22(uVar26,*(undefined2 *)*piVar16);
    gta2::bitShiftLeft1(&stack0xffffffd8,NULL);
    FUN_00432860(&stack0xffffffe0,(undefined4 *)&stack0xffffffd8,
                 (undefined4 *)&DAT_00673a64);
    FUN_0040f6b0(&stack0xffffffe0,(GlassInfo *)&stack0xffffffd4);
    gta2::bitShiftLeft1(&stack0xffffffd8,NULL);
    FUN_00432860(&stack0xfffffff0,(undefined4 *)&stack0xffffffd8,
                 (undefined4 *)&DAT_006739f8);
    pCVar15 = self->Car;
    FUN_0040f6b0(&stack0xfffffff0,(GlassInfo *)pCVar15->CarSprite);
    pSVar17 = (SpriteS1 *)
              gta2::SpriteS1_sub_4207B0((SpriteS1 *)pCVar15->CarSprite,&stack0xffffffd8);
    pvVar18 = FUN_0040f5c0(&stack0xfffffff0,&stack0xfffffff8,pSVar17);
    FUN_0040f680(&stack0xffffffe0,(int)pvVar18);
    if (pCVar15->Player_ == NULL) {
      gta2::S103_sub_41E1E0((LinkedList *)&pSStack_18);
    }
    else {
      puVar25 = (undefined4 *)
                gta2::Player_sub_4A0D10(pCVar15->Player_,&stack0xfffffff8,
                           (GlassInfo *)&stack0xffffffe0);
      pSStack_18 = (SpriteS1 *)*puVar25;
    }
    gta2::Weapon_Set_4CCA80(self,1);
    if (self->TypeWeapons == 0) {
      pEVar19 = gta2::Weapon_sub_4CDA90(self,0x80,in_stack_ffffffe0,uStack_1c,
                           self->Car->CarSprite->Point2D,(GlassInfo *)pSVar14,
                           (Ped *)&pSStack_18);
      if ((pEVar19 != NULL) &&
         (bVar2 = gta2::Ped_IsSearchType(self->Ped_,
                                     SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY),
         bVar2)) {
        gta2::Weapon_Decrement10Ammo(self);
      }
      self->TimeToReload = 0x32;
      gta2::Ped_sub_4350A0(self->Ped_);
      pPed = self->Ped_;
      bVar3 = gta2::Ped_IsPlayerControlled(pPed);
      if (bVar3 != 0) {
        gta2::S127_HandlePedInteraction(gS127,2,pPed);
        pvVar18 = gta2::Weapon_TimeToReload(self);
        return (byte)pvVar18;
      }
    }
    else {
      gta2::Weapon_sub_4CDA90(self,0x9f,in_stack_ffffffe0,uStack_1c,
                 self->Car->CarSprite->Point2D,(GlassInfo *)pSVar14,
                 (Ped *)&pSStack_18);
      self->TimeToReload = 5;
    }
    pvVar18 = gta2::Weapon_TimeToReload(self);
    return (byte)pvVar18;
  case WATER_CANNON:
    gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&stack0xffffffdc);
    pCVar15 = self->Car;
    pPed = gta2::Car_GetDriver(pCVar15);
    self->Ped_ = pPed;
    piVar16 = gta2::Car_sub_4BE980(pCVar15,0x72);
    puVar13 = (undefined2 *)
              gta2::sub_40E5A0((CarSystemManager *)*piVar16,(Ped *)&stack0xffffffd4,
                         (short *)&DAT_00673b78,unaff_EDI,(short *)unaff_ESI);
    pSVar14 = (SpriteS1 *)CONCAT22(uVar27,*puVar13);
    gta2::bitShiftLeft1(&stack0xffffffd4,NULL);
    FUN_00432860(&stack0xffffffe0,(undefined4 *)&stack0xffffffd4,
                 (undefined4 *)&DAT_00673ad0);
    FUN_0040f6b0(&stack0xffffffe0,(GlassInfo *)&stack0xffffffdc);
    gta2::bitShiftLeft1(&stack0xffffffd4,NULL);
    FUN_00432860(&pSStack_18,(undefined4 *)&stack0xffffffd4,
                 (undefined4 *)&DAT_00673b54);
    pCVar15 = self->Car;
    FUN_0040f6b0(&pSStack_18,(GlassInfo *)pCVar15->CarSprite);
    pSVar17 = (SpriteS1 *)
              gta2::SpriteS1_sub_4207B0((SpriteS1 *)pCVar15->CarSprite,&stack0xffffffd4);
    pvVar18 = FUN_0040f5c0(&pSStack_18,&stack0xfffffff8,pSVar17);
    FUN_0040f680(&stack0xffffffe0,(int)pvVar18);
    gta2::Player_sub_4A0D10(pCVar15->Player_,&stack0xfffffff8,(GlassInfo *)&stack0xffffffe0);
    gta2::Weapon_Set_4CCA80(self,1);
    gta2::Weapon_Set_4CCA80(self,1);
    if (self->TypeWeapons != 0) {
      pEVar19 = gta2::Weapon_sub_4CDA90(self,199,in_stack_ffffffe0,uStack_1c,
                           self->Car->CarSprite->Point2D,(GlassInfo *)pSVar14,
                           (Ped *)&stack0xfffffff0);
      return (byte)pEVar19;
    }
    bVar3 = FUN_0048d8b0(self->Car->CarSprite);
    return bVar3;
  case FIRE_TRUCK_GUN:
    gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&stack0xffffffdc);
    pCVar15 = self->Car;
    pPed = gta2::Car_GetDriver(pCVar15);
    self->Ped_ = pPed;
    piVar16 = gta2::Car_sub_4BE980(pCVar15,0x72);
    if (piVar16 == NULL) {
      piVar16 = gta2::Car_sub_4BE980(self->Car,0xf8);
      pSVar17 = (SpriteS1 *)CONCAT22(uVar27,*(undefined2 *)*piVar16);
      gta2::bitShiftLeft1(&stack0xffffffd4,NULL);
      FUN_00432860(&stack0xffffffe0,(undefined4 *)&stack0xffffffd4,
                   (undefined4 *)&DAT_00673a04);
      FUN_0040f6b0(&stack0xffffffe0,(GlassInfo *)&stack0xffffffdc);
      gta2::bitShiftLeft1(&stack0xffffffd4,NULL);
      puVar25 = (undefined4 *)&DAT_00673cb0;
    }
    else {
      puVar13 = (undefined2 *)
                gta2::sub_40E5A0((CarSystemManager *)*piVar16,(Ped *)&stack0xffffffd4,
                           (short *)&DAT_00673b78,unaff_EDI,(short *)unaff_ESI);
      pSVar17 = (SpriteS1 *)CONCAT22(uVar27,*puVar13);
      gta2::bitShiftLeft1(&stack0xffffffd4,NULL);
      FUN_00432860(&stack0xffffffe0,(undefined4 *)&stack0xffffffd4,
                   (undefined4 *)&DAT_00673ad0);
      FUN_0040f6b0(&stack0xffffffe0,(GlassInfo *)&stack0xffffffdc);
      gta2::bitShiftLeft1(&stack0xffffffd4,NULL);
      puVar25 = (undefined4 *)&DAT_00673b54;
    }
    FUN_00432860(&pSStack_18,(undefined4 *)&stack0xffffffd4,puVar25);
    pCVar15 = self->Car;
    FUN_0040f6b0(&pSStack_18,(GlassInfo *)pCVar15->CarSprite);
    pSVar14 = (SpriteS1 *)
              gta2::SpriteS1_sub_4207B0((SpriteS1 *)pCVar15->CarSprite,&stack0xffffffd4);
    pvVar18 = FUN_0040f5c0(&pSStack_18,&stack0xfffffff8,pSVar14);
    FUN_0040f680(&stack0xffffffe0,(int)pvVar18);
    gta2::Player_sub_4A0D10(pCVar15->Player_,&stack0xfffffff8,(GlassInfo *)&stack0xffffffe0);
    gta2::Weapon_Set_4CCA80(self,1);
    if (self->TypeWeapons != 0) {
      pEVar19 = gta2::Weapon_sub_4CDA90(self,0xc3,in_stack_ffffffe0,uStack_1c,
                           self->Car->CarSprite->Point2D,(GlassInfo *)pSVar17,
                           (Ped *)&stack0xfffffff0);
      return (byte)pEVar19;
    }
    pCVar15 = self->Car;
    gta2::Particles_sub_48D4E0(gParticles,(GlassInfo *)pCVar15->CarSprite);
    return (byte)pCVar15;
  case ARMY_GUN_JEEP:
    gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&stack0xffffffd4);
    if (self->TimeToReload != 0) {
      bVar3 = self->TimeToReload - 1;
      self->TimeToReload = bVar3;
      return bVar3;
    }
    pCVar15 = self->Car;
    pPed = gta2::Car_GetDriver(pCVar15);
    self->Ped_ = pPed;
    piVar16 = gta2::Car_sub_4BE980(pCVar15,0xf8);
    pSVar14 = (SpriteS1 *)CONCAT22(uVar26,*(undefined2 *)*piVar16);
    gta2::bitShiftLeft1(&stack0xffffffd8,NULL);
    FUN_00432860(&stack0xffffffe0,(undefined4 *)&stack0xffffffd8,
                 (undefined4 *)&DAT_00673a04);
    FUN_0040f6b0(&stack0xffffffe0,(GlassInfo *)&stack0xffffffd4);
    gta2::bitShiftLeft1(&stack0xffffffd8,NULL);
    FUN_00432860(&stack0xfffffff0,(undefined4 *)&stack0xffffffd8,
                 (undefined4 *)&DAT_00673cb0);
    pCVar15 = self->Car;
    FUN_0040f6b0(&stack0xfffffff0,(GlassInfo *)pCVar15->CarSprite);
    pSVar17 = (SpriteS1 *)
              gta2::SpriteS1_sub_4207B0((SpriteS1 *)pCVar15->CarSprite,&stack0xffffffd8);
    pvVar18 = FUN_0040f5c0(&stack0xfffffff0,&stack0xfffffff8,pSVar17);
    FUN_0040f680(&stack0xffffffe0,(int)pvVar18);
    piVar16 = (int *)gta2::Player_sub_4A0D10(pCVar15->Player_,&stack0xfffffff8,
                                (GlassInfo *)&stack0xffffffe0);
    pSStack_18 = (SpriteS1 *)*piVar16;
    gta2::Weapon_Set_4CCA80(self,1);
    if (self->TypeWeapons == 0) {
      pEVar19 = gta2::Weapon_sub_4CDA90(self,0xfe,in_stack_ffffffe0,uStack_1c,
                           self->Car->CarSprite->Point2D,(GlassInfo *)pSVar14,
                           (Ped *)&pSStack_18);
      if ((pEVar19 != NULL) &&
         (bVar2 = gta2::Ped_IsSearchType(self->Ped_,
                                     SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY),
         bVar2)) {
        gta2::Weapon_Decrement1Ammo(self);
      }
      self->TimeToReload = 2;
      gta2::Ped_sub_4350A0(self->Ped_);
      pPed = self->Ped_;
      bVar3 = gta2::Ped_IsPlayerControlled(pPed);
      if (bVar3 != 0) {
        gta2::S127_HandlePedInteraction(gS127,2,pPed);
        pvVar18 = gta2::Weapon_TimeToReload(self);
        return (byte)pvVar18;
      }
    }
    else {
      gta2::Weapon_sub_4CDA90(self,0x9a,in_stack_ffffffe0,uStack_1c,
                 self->Car->CarSprite->Point2D,(GlassInfo *)pSVar14,
                 (Ped *)&pSStack_18);
      self->TimeToReload = 1;
    }
    pvVar18 = gta2::Weapon_TimeToReload(self);
    return (byte)pvVar18;
  case CAR_BOMB_INSTANT:
    gta2::Weapon_sub_4CD400(self,'\x01');
  }
  return (byte)pSecond;
}



