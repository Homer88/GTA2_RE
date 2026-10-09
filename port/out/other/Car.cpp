#include "gta2_shim.h"

// Module: other, Class: Car
// Functions: 39
// Source: unified (IDA+Ghidra)

// 0x00475aa0: Car::sub_475AA0
// IDA: Car::sub_475AA0
// Ghidra: FUN_00475aa0
byte gta2::Car_sub_475AA0(void *self)
{
  int iVar1;
  
  iVar1 = *(int *)((int)self + 0x18);
  if ((((iVar1 != 0xb0) && (iVar1 != 0xb1)) && (iVar1 != 0xb2)) &&
     (((iVar1 != 0xb3 && (iVar1 != 0xb4)) && (iVar1 != 0xb5)))) {
    return 0;
  }
  return 1;
}


// 0x00475c10: Car::SetLocksDoor
// IDA: Car::SetLocksDoor
// Ghidra: ---
void gta2::Car_SetLocksDoor(Car *self)
{
  if ( self->locksDoor != 4 )
    self->locksDoor = 1;
}


// 0x00475c30: Car::SetLocksDoor_4
// IDA: Car::SetLocksDoor_4
// Ghidra: ---
void gta2::Car_SetLocksDoor_4(Car *self)
{
  self->locksDoor = 4;
}


// 0x00475c40: Car::SetLocksDoor2
// IDA: Car::SetLocksDoor2
// Ghidra: ---
void gta2::Car_SetLocksDoor2(Car *self)
{
  if ( self->locksDoor != 4 )
    self->locksDoor = 2;
}


// 0x00475c80: Car::sub_475C80
// IDA: Car::sub_475C80
// Ghidra: ---
void gta2::Car_sub_475C80(Car *self)
{
  if ( self->locksDoor != 4 )
    self->locksDoor = 3;
}


// 0x004761f0: Car::sub_4761F0
// IDA: Car::sub_4761F0
// Ghidra: Car::FUN_004761f0
void gta2::Car_sub_4761F0(Car *self,ushort param_1)
{
  self->bitMask = self->bitMask & ~param_1;
  return;
}


// 0x00476230: Car::sub_476230
// IDA: Car::sub_476230
// Ghidra: Car::FUN_00476230
void gta2::Car_sub_476230(Car *self)
{
  gta2::Car_sub_4761F0(self,2);
  return;
}


// 0x00476270: Car::sub_476270
// IDA: Car::sub_476270
// Ghidra: ---
void gta2::Car_sub_476270(Car *self)
{
  gta2::Car_sub_421890(self, 16);
}


// 0x004762d0: Car::sub_4762D0
// IDA: Car::sub_4762D0
// Ghidra: FUN_004762d0
void gta2::Car_sub_4762D0(Car *param_1)
{
  gta2::Car_sub_421890(param_1,0x200);
  return;
}


// 0x004762e0: Car::jam_accelerator
// IDA: Car::jam_accelerator
// Ghidra: ---
void gta2::Car_jam_accelerator(Car *self)
{
  gta2::Car_sub_421890(self, 4096);
}


// 0x004762f0: Car::sub_4762F0
// IDA: Car::sub_4762F0
// Ghidra: FUN_004762f0
void gta2::Car_sub_4762F0(Car *param_1)
{
  gta2::Car_sub_4761F0(param_1,0x100);
  return;
}


// 0x00476300: Car::sub_476300
// IDA: Car::sub_476300
// Ghidra: FUN_00476300
void gta2::Car_sub_476300(Car *param_1)
{
  gta2::Car_sub_4761F0(param_1,0x200);
  return;
}


// 0x00476310: Car::sub_476310
// IDA: Car::sub_476310
// Ghidra: FUN_00476310
void gta2::Car_sub_476310(Car *param_1)
{
  gta2::Car_sub_4761F0(param_1,0x400);
  return;
}


// 0x00476350: Car::unjam_accelerator
// IDA: Car::unjam_accelerator
// Ghidra: ---
int gta2::Car_unjam_accelerator(Car *self)
{
  int result; // eax

  gta2::Car_sub_4761F0(self, 4096);
  return result;
}


// 0x00482d90: Car::sub_482D90
// IDA: Car::sub_482D90
// Ghidra: FUN_00482d90
void gta2::Car_sub_482D90(int param_1,int *param_2,undefined2 *param_3)
{
  struct SpriteS1 *pSVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined2 *puVar4;
  char local_26;
  char local_25;
  int local_24;
  int local_20 [2];
  Player *local_18;
  Player *local_14;
  struct SpriteS1 *local_10;
  struct SpriteS1 *local_c;
  undefined1 local_8 [8];
  
  if (*(char *)(param_1 + 0x38) != '\0') {
    FUN_00482770(*(char *)(param_1 + 0x38),&local_26,&local_25);
    local_24 = (int)local_26;
    pSVar1 = FUN_00401bd0(&DAT_006657fc,(SpriteS1 *)local_20,&local_24);
    local_10 = pSVar1->FirstElement;
    local_24 = (int)local_25;
    pSVar1 = FUN_00401bd0(&DAT_006657fc,(SpriteS1 *)local_20,&local_24);
    local_c = pSVar1->FirstElement;
    pSVar1 = (SpriteS1 *)FUN_00482ba0(local_20);
    puVar2 = (undefined4 *)FUN_0040f5c0(&local_10,local_8,pSVar1);
    local_18 = (Player *)*puVar2;
    local_14 = (Player *)puVar2[1];
    piVar3 = gta2::Player_sub_41E260((Player *)&local_18,local_20);
    *param_2 = *piVar3;
    puVar4 = gta2::Player_FUN_0040f790((Player *)&local_18,(undefined2 *)&param_2);
    *param_3 = *puVar4;
    FUN_00482bd0();
    return;
  }
  *param_2 = *(int *)(param_1 + 0xc);
  *param_3 = *(undefined2 *)(param_1 + 4);
  return;
}


// 0x004895e0: Car::sub_4895E0
// IDA: Car::sub_4895E0
// Ghidra: Car::FUN_004895e0
void gta2::Car_sub_4895E0(Car *self)
{
  gta2::Car_sub_4761F0(self,8);
  return;
}


// 0x0048a930: Car::sub_48A930
// IDA: Car::sub_48A930
// Ghidra: FUN_0048a930
Model * gta2::Car_sub_48A930(int param_1,Model *param_2)
{
  gta2::SpriteS1_sub_420740(*(Sprite **)(param_1 + 0x50),param_2);
  return param_2;
}


// 0x0049efc0: Car::sub_49EFC0
// IDA: Car::sub_49EFC0
// Ghidra: ---
__int16 gta2::Car_sub_49EFC0(Car *self)
{
  __int16 result; // ax

  gta2::Car_sub_421890(self, 0x2000);
  return result;
}


// 0x0049efd0: Car::sub_49EFD0
// IDA: Car::sub_49EFD0
// Ghidra: Car::FUN_0049efd0
void gta2::Car_sub_49EFD0(Car *self)
{
  gta2::Car_sub_4761F0(self,0x2000);
  return;
}


// 0x0049efe0: Car::sub_49EFE0
// IDA: Car::sub_49EFE0
// Ghidra: ---
bool gta2::Car_sub_49EFE0(Car *self, void *a2)
{
  return gta2::Car_sub_4216E0(self) && (gta2::Car_isTank(self) || !gta2::Car_IsDriverActive(self));
}


// 0x004a9ad0: Car::sub_4A9AD0
// IDA: Car::sub_4A9AD0
// Ghidra: ---
__int16 gta2::Car_sub_4A9AD0(Car *self)
{
  return self->field_76;
}


// 0x004afb30: Car::sub_4AFB30
// IDA: Car::sub_4AFB30
// Ghidra: ---
char gta2::Car_sub_4AFB30(Car *self)
{
  char result; // al
  struct Car *v3; // ebp
  char v4; // al
  struct Car *Car; // ecx
  unsigned __int8 v6; // al
  Ped *v7; // ecx
  Ped *v8; // esi
  struct Car *v9; // ecx
  unsigned __int8 v10; // al
  Passenger *v11; // esi
  Ped *v12; // esi
  char v13; // al
  Ped *v14; // esi
  char v15; // al
  unsigned __int8 v16; // [esp+4h] [ebp-8h]
  __int16 a2[2]; // [esp+8h] [ebp-4h] BYREF

  result = skip_trains;
  if ( skip_trains )
    return result;
  result = skip_dummies;
  if ( skip_dummies )
    return result;
  result = (char)gCharacter;
  if ( gCharacter->dummy_chars >= 0x32u )
    return result;
  if ( self->PlayerStats_ != LEFT_REAR_LIGHT_IS_BROKEN )
  {
    if ( !gta2::Game_sub_45C420(gGame, *(SpriteS1 **)(*(_DWORD *)self->CarDoor_[0].AnimationFrame + 80), byte_66BC54[0])
      || SLOBYTE(self->Driver) > 0
      || gPublicTransport->field_1818 )
    {
      goto LABEL_32;
    }
    if ( !gta2::Car_sub_425B60(*(Car **)self->CarDoor_[0].AnimationFrame, (Ped *)2) )
      goto LABEL_29;
    v11 = (Passenger *)(*(_DWORD *)self->CarDoor_[0].AnimationFrame + 4);
    if ( gta2::Passenger_Passenger_des(v11) )
    {
      if ( SBYTE2(self->Driver) <= 6 && LOBYTE(self->Car) )
      {
LABEL_31:
        *(_DWORD *)a2 = 20;
        LOBYTE(self->Driver) = gta2::Random_Random(&gRandom, a2) + 40;
        goto LABEL_32;
      }
      v12 = gta2::Character_sub_43DEB0(gCharacter);
      v12->field_10B = *(Car **)self->CarDoor_[0].AnimationFrame;
      gta2::Passenger_sub_445F10((Passenger *)(*(_DWORD *)self->CarDoor_[0].AnimationFrame + 4), v12);
      gta2::Ped_PedSetObjective(v12, 38, 9999);
      gta2::Ped_SetCurrentCar(v12, *(Car **)self->CarDoor_[0].AnimationFrame);
      gta2::Ped_SetAnimationState_0(v12, 2);
      gta2::Ped_SetCurrentOccupation(v12, UNKNOWN_OCUPATION8);
      if ( LOBYTE(self->Car) == 1 )
      {
        v13 = BYTE2(self->Driver);
LABEL_28:
        BYTE2(self->Driver) = v13 - 1;
      }
    }
    else
    {
      v14 = (Ped *)sub_446100(v11);
      v14->field_10B = *(Car **)self->CarDoor_[0].AnimationFrame;
      gta2::Ped_PedSetObjective(v14, 38, 9999);
      gta2::Ped_SetCurrentCar(v14, *(Car **)self->CarDoor_[0].AnimationFrame);
      gta2::Ped_SetAnimationState_0(v14, 2);
      gta2::Ped_SetCurrentOccupation(v14, UNKNOWN_OCUPATION8);
      if ( LOBYTE(self->Car) == 1 )
      {
        v13 = BYTE2(self->Driver);
        if ( v13 > 0 )
          goto LABEL_28;
      }
    }
LABEL_29:
    if ( !LOBYTE(self->Car) )
    {
      *(_DWORD *)a2 = 20;
      v15 = gta2::Random_Random(&gRandom, a2) + 20;
      LOBYTE(self->Driver) = v15;
      result = v15 - 1;
      LOBYTE(self->Driver) = result;
      return result;
    }
    goto LABEL_31;
  }
  v16 = 0;
  if ( !HIBYTE(self->CarDoor_[3].doorState) )
  {
LABEL_32:
    result = LOBYTE(self->Driver) - 1;
    LOBYTE(self->Driver) = result;
    return result;
  }
  do
  {
    v3 = (Car *)&self->CarDoor_[0].AnimationFrame[4 * v16 + 4];
    if ( gta2::Car_GetModelCar((Car *)v3->Car) == TRAIN )
    {
      BYTE2(self->Driver) = 1;
      if ( gta2::Game_sub_45C420(gGame, *((SpriteS1 **)v3->Car + 20), byte_66BC54[0]) )
      {
        if ( SLOBYTE(self->Driver) <= 0 )
        {
          *(_DWORD *)a2 = 4;
          v4 = gta2::Random_Random(&gRandom, a2);
          Car = (Car *)v3->Car;
          byte_66BEE8[0] = v4;
          v6 = gta2::Car_sub_41F880(Car);
          LOBYTE(v7) = byte_66BEE8[0];
          if ( (unsigned int)byte_66BEE8[0] < v6 )
          {
            do
            {
              if ( gta2::Car_sub_425B60((Car *)v3->Car, v7) && SBYTE2(self->Driver) > 0 )
              {
                v8 = gta2::Character_sub_43DEB0(gCharacter);
                v8->field_10B = (Car *)v3->Car;
                gta2::Ped_PedSetObjective(v8, 38, 9999);
                gta2::Ped_SetCurrentCar(v8, (Car *)v3->Car);
                gta2::Passenger_sub_445F10((Passenger *)&v8->field_10B->Passenger_, v8);
                gta2::Ped_SetAnimationState_0(v8, byte_66BEE8[0]);
                --BYTE2(self->Driver);
              }
              v9 = (Car *)v3->Car;
              ++byte_66BEE8[0];
              v10 = gta2::Car_sub_41F880(v9);
              LOBYTE(v7) = byte_66BEE8[0];
            }
            while ( (unsigned int)byte_66BEE8[0] < v10 );
          }
          LOBYTE(self->Driver) = 7;
        }
      }
    }
    ++v16;
  }
  while ( v16 < HIBYTE(self->CarDoor_[3].doorState) );
  result = LOBYTE(self->Driver) - 1;
  LOBYTE(self->Driver) = result;
  return result;
}


// 0x004b9a30: Car::sub_4B9A30
// IDA: Car::sub_4B9A30
// Ghidra: FUN_004b9a30
byte gta2::Car_sub_4B9A30(void *self,Sprite *param_1)
{
  byte bVar1;
  bool bVar2;
  
  switch(*(undefined4 *)((int)self + 0x30)) {
  case 1:
  case 4:
  case 5:
    bVar2 = gta2::CollisionBox_ShouldCollide(*(CollisionBox **)((int)self + 8),(SpriteS1 *)param_1);
    return bVar2;
  case 2:
    bVar1 = gta2::Car_CanBeHit(*(Car **)((int)self + 8),(SpriteS1 *)param_1);
    return bVar1;
  case 3:
    bVar2 = FUN_00497480(*(void **)((int)self + 8),(SpriteS1 *)param_1);
    return bVar2;
  default:
    return 1;
  }
}


// 0x004be7a0: Car::sub_4BE7A0
// IDA: Car::sub_4BE7A0
// Ghidra: Car::FUN_004be7a0
void gta2::Car_sub_4BE7A0(Car *self,void *param_1)
{
  Turrel *pTVar1;
  
  for (pTVar1 = self->Turret; pTVar1 != NULL;
      pTVar1 = *(Turrel **)&pTVar1->count) {
    FUN_004b9a80(pTVar1->void1,param_1);
  }
  return;
}


// 0x004be980: Car::sub_4BE980
// IDA: Car::sub_4BE980
// Ghidra: ---
_DWORD * gta2::Car_sub_4BE980(Car *self, int a2)
{
  struct SpriteS1 **Car; // esi
  GameObject *v3; // eax

  Car = (SpriteS1 **)self->Car;
  if ( !self->Car )
    return 0;
  while ( 1 )
  {
    v3 = gta2::SpriteS1_sub_40FEC0(*Car);
    if ( v3 )
    {
      if ( v3->field_18 == a2 )
        break;
    }
    Car = (SpriteS1 **)Car[1];
    if ( !Car )
      return 0;
  }
  return Car;
}


// 0x004be9c0: Car::sub_4BE9C0
// IDA: Car::sub_4BE9C0
// Ghidra: ---
GameObject * gta2::Car_sub_4BE9C0(Car *self, int a2)
{
  struct SpriteS1 **Car; // esi
  GameObject *result; // eax

  Car = (SpriteS1 **)self->Car;
  if ( !self->Car )
    return 0;
  while ( 1 )
  {
    result = gta2::SpriteS1_sub_40FEC0(*Car);
    if ( result )
    {
      if ( result->field_18 == a2 )
        break;
    }
    Car = (SpriteS1 **)Car[1];
    if ( !Car )
      return 0;
  }
  return result;
}


// 0x004be9f0: Car::sub_4BE9F0
// IDA: Car::sub_4BE9F0
// Ghidra: ---
SpriteS1 ** gta2::Car_sub_4BE9F0(Car *self)
{
  struct SpriteS1 **Car; // esi
  GameObject *v2; // eax

  Car = (SpriteS1 **)self->Car;
  if ( !self->Car )
    return 0;
  while ( 1 )
  {
    v2 = gta2::SpriteS1_sub_40FEC0(*Car);
    if ( v2 )
    {
      if ( gta2::sub_482540(v2) )
        break;
    }
    Car = (SpriteS1 **)Car[1];
    if ( !Car )
      return 0;
  }
  return Car;
}


// 0x004bea20: Car::sub_4BEA20
// IDA: Car::sub_4BEA20
// Ghidra: ---
void gta2::Car_sub_4BEA20(Car *self)
{
  _DWORD *Car; // esi

  Car = self->Car;
  if ( self->Car )
  {
    do
    {
      gta2::sub_4BE920(Car);
      Car = (_DWORD *)Car[1];
    }
    while ( Car );
  }
}


// 0x004beac0: Car::sub_4BEAC0
// IDA: Car::sub_4BEAC0
// Ghidra: ---
Car * gta2::Car_sub_4BEAC0(Car *self, char a2, char a3)
{
  int *Car; // edi
  int i; // ebp
  int v5; // esi
  void *v6; // ebx
  void *v8; // [esp+8h] [ebp-Ch] BYREF
  void *v9; // [esp+Ch] [ebp-8h] BYREF
  _BYTE v10[4]; // [esp+10h] [ebp-4h] BYREF

  Car = (int *)self->Car;
  gta2::bitShiftLeft1(&v8, 99999);
  for ( i = 0; Car; Car = (int *)Car[1] )
  {
    v5 = *Car;
    v6 = gta2::sub_42A6B0(v10, v10)->Car;
    v9 = v6;
    if ( gta2::sub_4037E0(&v9) )
    {
      i = v5;
      v8 = v6;
    }
  }
  return (Car *)i;
}


// 0x004beb30: Car::sub_4BEB30
// IDA: Car::sub_4BEB30
// Ghidra: FUN_004beb30
int gta2::Car_sub_4BEB30(void *self)
{
  undefined4 *puVar1;
  byte bVar2;
  EventHandler *this_00;
  int iVar3;
  
                              // WARNING: Load size is inaccurate
  puVar1 = *self;
  while( true ) {
    if (puVar1 == NULL) {
      return 0;
    }
    this_00 = gta2::SpriteS1_sub_40FEC0((SpriteS1 *)*puVar1);
    if ((this_00 != NULL) &&
       (bVar2 = gta2::EventHandler_FUN_004be850(this_00), bVar2 != 0)) break;
    puVar1 = (undefined4 *)puVar1[1];
  }
  iVar3 = FUN_0040fef0(this_00);
  return iVar3 + -0x11e;
}


// 0x004beb70: Car::sub_4BEB70
// IDA: Car::sub_4BEB70
// Ghidra: ---
void gta2::Car_sub_4BEB70(Car *self)
{
  struct SpriteS1 **Car; // esi
  struct SpriteS1 *v2; // edi
  int SpriteType; // eax

  Car = (SpriteS1 **)self->Car;
  if ( self->Car )
  {
    do
    {
      v2 = *Car;
      SpriteType = gta2::SpriteS1_getSpriteType(*Car);
      if ( SpriteType == 1 || SpriteType > 3 && SpriteType <= 5 )
      {
        if ( gta2::sub_4BE830(&v2->S3_arr5031[0].GameObject->NextGameObject1) )
          *(_WORD *)((*Car)->S3_arr5031[0].GameObject->field_C + 26) = 2;
      }
      Car = (SpriteS1 **)Car[1];
    }
    while ( Car );
  }
}


// 0x004bebc0: Car::sub_4BEBC0
// IDA: Car::sub_4BEBC0
// Ghidra: ---
char gta2::Car_sub_4BEBC0(Car *self, SpriteS1 *pCarSprite, char a3)
{
  char v4; // al
  struct SpriteS1 **Car; // esi
  char v6; // bl
  struct SpriteS1 *v7; // edi
  char v8; // al
  char result; // al
  void *ppCarSprite; // esi
  char a2; // [esp+10h] [ebp-4h]

  v4 = gta2::SpriteS1_sub_4BD2E0(pCarSprite);
  Car = (SpriteS1 **)self->Car;
  v6 = v4;
  a2 = v4;
  if ( self->Car )
  {
    do
    {
      v7 = *Car;
      if ( gta2::SpriteS1_sub_446950(*Car) )
      {
        v8 = gta2::SpriteS1_sub_4BD2E0(v7);
        if ( v8 > v6 )
          v6 = v8;
      }
      Car = (SpriteS1 **)Car[1];
    }
    while ( Car );
    a2 = v6;
  }
  result = a3;
  if ( a3 )
    gta2::SpriteS1_sub_4BA220(pCarSprite, a2);
  for ( ppCarSprite = self->Car; ppCarSprite; ppCarSprite = (void *)*((_DWORD *)ppCarSprite + 1) )
    gta2::SpriteS1_sub_4BA220(*(SpriteS1 **)ppCarSprite, a2);
  return result;
}


// 0x004bed90: Car::sub_4BED90
// IDA: Car::sub_4BED90
// Ghidra: FUN_004bed90
void gta2::Car_sub_4BED90(void *self,undefined4 param_1,undefined4 param_2,undefined4 param_3 ,undefined2 param_4)
{
  undefined4 *in_EAX;
  
  gta2::SpriteS4_sub_4BEC40(gSpriteS4);
  *in_EAX = param_1;
                              // WARNING: Load size is inaccurate
  in_EAX[1] = *self;
  in_EAX[2] = param_2;
  in_EAX[3] = param_3;
  *(undefined2 *)(in_EAX + 4) = param_4;
  *(undefined4 **)self = in_EAX;
  return;
}


// 0x004bee10: Car::sub_4BEE10
// IDA: Car::sub_4BEE10
// Ghidra: ---
SpriteS1 * gta2::Car_sub_4BEE10(Car *self)
{
  struct SpriteS1 *result; // eax
  struct SpriteS1 *FirstElement; // esi

  result = (SpriteS1 *)self->Car;
  if ( self->Car )
  {
    FirstElement = result->FirstElement;
    self->Car = result->S3_arr5031[0].SpriteS1_;
    gta2::SpriteS4_sub_4BEC50(gSpriteS4, (Arsenal *)result);
    return FirstElement;
  }
  return result;
}


// 0x004bef70: Car::sub_4BEF70
// IDA: Car::sub_4BEF70
// Ghidra: ---
void gta2::Car_sub_4BEF70(Car *self, SpriteS1 *CarSprite)
{
  struct SpriteS1 *Car; // esi
  struct SpriteS1 **p_FirstElement; // edi
  struct SpriteS1 *SpriteS1; // ebx

  Car = (SpriteS1 *)self->Car;
  p_FirstElement = 0;
  if ( self->Car )
  {
    do
    {
      SpriteS1 = Car->S3_arr5031[0].SpriteS1_;
      if ( !gta2::sub_4BE870(Car, CarSprite) )
      {
        p_FirstElement = &Car->FirstElement;
        goto LABEL_13;
      }
      if ( p_FirstElement )
      {
        if ( p_FirstElement[1] == Car )
          goto LABEL_11;
        p_FirstElement = 0;
      }
      if ( self->Car != Car )
      {
        for ( p_FirstElement = (SpriteS1 **)self->Car;
              p_FirstElement[1] != Car;
              p_FirstElement = (SpriteS1 **)p_FirstElement[1] )
        {
          ;
        }
LABEL_11:
        p_FirstElement[1] = Car->S3_arr5031[0].SpriteS1_;
        gta2::SpriteS4_sub_4BEC50(gSpriteS4, (Arsenal *)Car);
        goto LABEL_13;
      }
      self->Car = Car->S3_arr5031[0].SpriteS1_;
      gta2::SpriteS4_sub_4BEC50(gSpriteS4, (Arsenal *)Car);
LABEL_13:
      Car = SpriteS1;
    }
    while ( SpriteS1 );
  }
}


// 0x004bf000: Car::sub_4BF000
// IDA: Car::sub_4BF000
// Ghidra: ---
int gta2::Car_sub_4BF000(Car *self)
{
  Arsenal **Car; // esi
  Arsenal *pS72; // edi
  int result; // eax

  Car = (Arsenal **)self->Car;
  if ( self->Car )
  {
    do
    {
      pS72 = *Car;
      switch ( gta2::SpriteS1_getSpriteType((SpriteS1 *)*Car) )
      {
        case 1:
        case 4:
        case 5:
          gta2::Object_sub_485260(gObject, (int *)pS72[1].Sprite);
          break;
        case 2:
          gta2::CarSystemManager_sub_428F70(gCarSystemManager, (int)pS72[1].Sprite);
          break;
        default:
          break;
      }
      Car = (Arsenal **)Car[1];
    }
    while ( Car );
  }
  gta2::Turrel_sub_4BEE80((Arsenal *)self);
  return result;
}


// 0x004bf070: Car::ExtinguishCar
// IDA: Car::ExtinguishCar
// Ghidra: ---
void gta2::Car_ExtinguishCar(Car *self)
{
  struct SpriteS1 **v2; // ebx
  struct SpriteS1 **Car; // esi
  struct SpriteS1 *v4; // edi
  int SpriteType; // eax
  struct SpriteS1 *v6; // edi

  v2 = 0;
  Car = (SpriteS1 **)self->Car;
  if ( self->Car )
  {
    do
    {
      v4 = *Car;
      SpriteType = gta2::SpriteS1_getSpriteType(*Car);
      if ( (SpriteType == 1 || SpriteType > 3 && SpriteType <= 5)
        && gta2::sub_4BE830(&v4->S3_arr5031[0].GameObject->NextGameObject1) )
      {
        gta2::Object_sub_485260(gObject, (int *)(*Car)->S3_arr5031[0].GameObject);
        if ( v2 )
        {
          v2[1] = Car[1];
          gta2::SpriteS4_sub_4BEC50(gSpriteS4, (Arsenal *)Car);
          Car = (SpriteS1 **)v2[1];
        }
        else
        {
          v6 = Car[1];
          gta2::SpriteS4_sub_4BEC50(gSpriteS4, (Arsenal *)Car);
          Car = &v6->FirstElement;
          self->Car = v6;
        }
      }
      else
      {
        v2 = Car;
        Car = (SpriteS1 **)Car[1];
      }
    }
    while ( Car );
  }
}


// 0x004bf100: Car::sub_4BF100
// IDA: Car::sub_4BF100
// Ghidra: ---
void gta2::Car_sub_4BF100(Car *self)
{
  _DWORD *v2; // ebx
  void *Car; // esi
  GameObject *v4; // eax
  int *v5; // edi

  v2 = 0;
  Car = self->Car;
  if ( self->Car )
  {
    while ( 1 )
    {
      v4 = gta2::SpriteS1_sub_40FEC0(*(SpriteS1 **)Car);
      v5 = (int *)v4;
      if ( v4 )
      {
        if ( sub_4BE850(v4) )
          break;
      }
      v2 = Car;
      Car = (void *)*((_DWORD *)Car + 1);
      if ( !Car )
        return;
    }
    gta2::Object_sub_485260(gObject, v5);
    if ( v2 )
      v2[1] = *((_DWORD *)Car + 1);
    else
      self->Car = (void *)*((_DWORD *)Car + 1);
    gta2::SpriteS4_sub_4BEC50(gSpriteS4, (Arsenal *)Car);
  }
}


// 0x004bf180: Car::sub_4BF180
// IDA: Car::sub_4BF180
// Ghidra: ---
void gta2::Car_sub_4BF180(Car *self, _DWORD *a2)
{
  Arsenal *v3; // ebx
  Arsenal *Car; // esi
  Arsenal *v5; // edi

  v3 = 0;
  Car = (Arsenal *)self->Car;
  gta2::SpriteS1_sub_4BCB40(a2);
  while ( Car )
  {
    if ( gta2::sub_4BCAC0(a2, (SpriteS1 *)Car->Sprite) )
    {
      v3 = Car;
      Car = *(Arsenal **)&Car->Count;
    }
    else if ( v3 )
    {
      *(_DWORD *)&v3->Count = *(_DWORD *)&Car->Count;
      gta2::SpriteS4_sub_4BEC50(gSpriteS4, Car);
      Car = *(Arsenal **)&v3->Count;
    }
    else
    {
      v5 = *(Arsenal **)&Car->Count;
      gta2::SpriteS4_sub_4BEC50(gSpriteS4, Car);
      Car = v5;
      self->Car = v5;
    }
  }
}



