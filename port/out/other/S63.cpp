#include "gta2_shim.h"

// Module: other, Class: S63
// Functions: 67
// Source: unified (IDA+Ghidra)

// 0x00482450: S63::S63
// IDA: S63::S63
// Ghidra: ---
void gta2::S63_S63(struct EventHandler *self)
{
  self->NextElement = 0;
  self->SpriteS1_ = 0;
  self->S63_1_ = 0;
  self->pEventHandler = 0;
  self->S65_ = 0;
  self->Car = 0;
  self->field_14 = 99;
  LOBYTE(self->S202_) = 0;
  BYTE1(self->S202_) = 0;
  BYTE2(self->S202_) = 99;
  self->field_20 = 0;
  HIBYTE(self->S202_) = 0;
  self->field_28 = -51;
  self->field_1C = 0;
}


// 0x004825a0: S63::sub_4825A0
// IDA: S63::sub_4825A0
// Ghidra: ---
void gta2::S63_sub_4825A0(struct EventHandler *self)
{
  struct Car *pCar; // eax

  pCar = self->Car;
  if ( pCar )
  {
    if ( pCar->Car )
      gta2::Car_sub_4BEF70(pCar, self->SpriteS1_);
  }
}


// 0x004825c0: S63::sub_4825C0
// IDA: S63::sub_4825C0
// Ghidra: ---
char gta2::S63_sub_4825C0(struct EventHandler *self)
{
  char result; // al

  if ( self->S63_1_ == (struct S63_1 *)128 )
    return gta2::Particles_sub_48DFC0(gParticles, self->SpriteS1_);
  return result;
}


// 0x00482630: S63::sub_482630
// IDA: S63::sub_482630
// Ghidra: ---
int gta2::S63_sub_482630(struct EventHandler *self)
{
  int result; // eax

  result = self->pEventHandler[1].field_14;
  switch ( result )
  {
    case 0:
    case 1:
      result = gta2::S56_sub_447BA0(gCheckpoint3, self->SpriteS1_);
      break;
    case 3:
      ++unk_66578C;
      result = gta2::S56_sub_447C00(gCheckpoint2, self->SpriteS1_);
      break;
    case 4:
      result = gta2::S56_sub_447C00(gCheckpoint1, self->SpriteS1_);
      break;
    default:
      return result;
  }
  return result;
}


// 0x004826a0: S63::sub_4826A0
// IDA: S63::sub_4826A0
// Ghidra: ---
void gta2::S63_sub_4826A0(struct EventHandler *self)
{
  switch ( self->pEventHandler[1].field_14 )
  {
    case 0:
    case 1:
      gta2::S56_sub_447BD0(gCheckpoint3, self->SpriteS1_);
      break;
    case 3:
      --unk_66578C;
      gta2::S56_sub_447C40(gCheckpoint2, self->SpriteS1_);
      break;
    case 4:
      gta2::S56_sub_447C40(gCheckpoint1, self->SpriteS1_);
      break;
    default:
      return;
  }
}


// 0x00482790: S63::sub_482790
// IDA: S63::sub_482790
// Ghidra: ---
_BYTE * gta2::S63_sub_482790(struct EventHandler *self, byte a2)
{
  _BYTE *result; // eax

  BYTE2(self->S202_) = a2;
  result = &gScriptThread->field[0].field_0[2 * a2 + 1];
  ++*result;
  return result;
}


// 0x004827b0: S63::sub_4827B0
// IDA: S63::sub_4827B0
// Ghidra: ---
void gta2::S63_sub_4827B0(struct EventHandler *self)
{
  BYTE1(self->S202_) = 1;
}


// 0x00482be0: S63::sub_482BE0
// IDA: S63::sub_482BE0
// Ghidra: ---
int gta2::S63_sub_482BE0(struct EventHandler *self)
{
  int result; // eax

  gta2::SpriteS1_sub_40F7B0(self->SpriteS1_, (int)self->pEventHandler[1].NextElement);
  return result;
}


// 0x00482bf0: S63::sub_482BF0
// IDA: S63::sub_482BF0
// Ghidra: CollisionBox::FUN_00482bf0
void gta2::S63_sub_482BF0(struct CollisionBox *self)
{
  gta2::SpriteS1_sub_40F7B0((struct SpriteS1 *)self->Index,0x1d);
  return;
}


// 0x00482c00: S63::sub_482C00
// IDA: S63::sub_482C00
// Ghidra: CollisionBox::FUN_00482c00
void gta2::S63_sub_482C00(struct CollisionBox *self,undefined1 param_1)
{
  self->EventHandler[0].field_0x1e = param_1;
  return;
}


// 0x00482c10: S63::sub_482C10
// IDA: S63::sub_482C10
// Ghidra: FUN_00482c10
int gta2::S63_sub_482C10(int param_1)
{
  int iVar1;
  uint3 uVar2;
  
  iVar1 = *(int *)(param_1 + 0xc);
  uVar2 = (uint3)((uint)iVar1 >> 8);
  if ((*(short *)(iVar1 + 4) == 0) && (*(char *)(iVar1 + 7) == '\0')) {
    return CONCAT31(uVar2,1);
  }
  return (uint)uVar2 << 8;
}


// 0x00482c30: S63::sub_482C30
// IDA: S63::sub_482C30
// Ghidra: FUN_00482c30
undefined4 gta2::S63_sub_482C30(int param_1,undefined4 param_2)
{
  gta2::SpriteS1_sub_4207B0(*(SpriteS1 **)(param_1 + 4),param_2);
  return param_2;
}


// 0x00482c50: S63::sub_482C50
// IDA: S63::sub_482C50
// Ghidra: FUN_00482c50
undefined4 * gta2::S63_sub_482C50(int param_1,undefined4 *param_2)
{
  if (*(int *)(param_1 + 0x10) != 0) {
    FUN_00482ba0(param_2);
    return param_2;
  }
  *param_2 = _DAT_006657d4;
  param_2[1] = _DAT_006657d8;
  return param_2;
}


// 0x00482c80: S63::sub_482C80
// IDA: S63::sub_482C80
// Ghidra: CollisionBox::FUN_00482c80
void gta2::S63_sub_482C80(struct CollisionBox *self,undefined4 *param_1)
{
  *param_1 = (self->EventHandler[0].NextElement)->DamageType;
  return;
}


// 0x00482c90: S63::sub_482C90
// IDA: S63::sub_482C90
// Ghidra: CollisionBox::FUN_00482c90
byte gta2::S63_sub_482C90(struct CollisionBox *self)
{
  struct EventHandler *pEVar1;
  int iVar2;
  
  pEVar1 = self->EventHandler[0].NextElement;
  iVar2 = pEVar1[1].Struc___;
  if (((iVar2 != 3) && (iVar2 != 4)) &&
     (((iVar2 != 0 && ((iVar2 != 1 && (iVar2 != 2)))) ||
      (pEVar1[1].DamageType != 2)))) {
    return 0;
  }
  return 1;
}


// 0x00482ed0: S63::sub_482ED0
// IDA: S63::sub_482ED0
// Ghidra: ---
_DWORD * gta2::S63_sub_482ED0(struct EventHandler *self)
{
  struct Car *Car; // eax
  _DWORD *result; // eax
  struct CarDoor *CarDoor; // edi
  int *p_doorState; // esi

  Car = self->Car;
  if ( *(_WORD *)&Car->CarDoor_[1].rezerv_2 == 1 )
  {
    gta2::Player_sub_40E530((struct Player *)&Car->CarDoor_[1], (struct Tango *)&unk_665948);
    gta2::Player_sub_40E530((struct Player *)&self->Car->CarDoor_[0].doorState, (struct Tango *)&self->Car->CarDoor_[1]);
  }
  else
  {
    gta2::Player_sub_40E530((struct Player *)Car->CarDoor_, (struct Tango *)&Car->CarDoor_[0].field_C);
    CarDoor = self->Car->CarDoor_;
    if ( gta2::sub_4037E0(CarDoor) )
    {
      *(_DWORD *)CarDoor->AnimationFrame = dword_665894;
      *(_DWORD *)&self->Car->CarDoor_[0].field_C = dword_665894;
    }
    p_doorState = &self->Car->CarDoor_[0].doorState;
    result = (_DWORD *)gta2::sub_4037E0(p_doorState);
    if ( result )
      *p_doorState = dword_665894;
  }
  return result;
}


// 0x00482f60: S63::sub_482F60
// IDA: S63::sub_482F60
// Ghidra: ---
EventHandler * gta2::S63_sub_482F60(struct EventHandler *self)
{
  struct EventHandler *result; // eax

  if ( self->field_20 == 2 )
  {
    result = gta2::S61_sub_4829E0(gCollisionBox, self);
    self->field_20 = 1;
  }
  return result;
}


// 0x00482f80: S63::sub_482F80
// IDA: S63::sub_482F80
// Ghidra: Sprite::FUN_00482f80
byte gta2::S63_sub_482F80(Sprite *self)
{
  byte in_AL;
  
  if (*(int *)&self->field_0x20 == 1) {
    in_AL = gta2::S61_sub_4829F0(gCollisionBox,(struct EventHandler *)self);
    *(undefined4 *)&self->field_0x20 = 2;
  }
  return in_AL;
}


// 0x00482fa0: S63::sub_482FA0
// IDA: S63::sub_482FA0
// Ghidra: CollisionBox::FUN_00482fa0
byte gta2::S63_sub_482FA0(struct CollisionBox *self,SpriteS1 *param_1)
{
  int iVar1;
  
  if (param_1 == NULL) {
switchD_00482fb4_caseD_4:
    return 0;
  }
  switch(*(undefined4 *)&self->EventHandler[0].NextElement[1].field19_0x28) {
  case 1:
    iVar1 = gta2::SpriteS1_getSpriteType(param_1);
    if (iVar1 == 2) {
      return 0;
    }
    break;
  case 2:
    iVar1 = gta2::SpriteS1_getSpriteType(param_1);
    if (iVar1 == 3) {
      return 0;
    }
    break;
  case 3:
    iVar1 = gta2::SpriteS1_getSpriteType(param_1);
    if (iVar1 == 4) {
      return 0;
    }
    iVar1 = gta2::SpriteS1_getSpriteType(param_1);
    if (iVar1 == 5) {
      return 0;
    }
    iVar1 = gta2::SpriteS1_getSpriteType(param_1);
    if (iVar1 == 1) {
      return 0;
    }
    break;
  case 4:
    goto switchD_00482fb4_caseD_4;
  }
  return 1;
}


// 0x00483030: S63::sub_483030
// IDA: S63::sub_483030
// Ghidra: CollisionBox::FUN_00483030
undefined1 gta2::S63_sub_483030(struct CollisionBox *self,SpriteS1 *param_1)
{
  byte bVar1;
  undefined4 uVar2;
  
  if (param_1 != NULL) {
    bVar1 = gta2::S63_sub_482FA0(self,param_1);
    if (bVar1 != 0) {
      uVar2 = gta2::CollisionBox_FUN_00482e80(self,param_1);
      if ((char)uVar2 == '\0') {
        return 1;
      }
    }
  }
  return 0;
}


// 0x00483060: S63::sub_483060
// IDA: S63::sub_483060
// Ghidra: CollisionBox::FUN_00483060
pSVar11 = gta2::S63_sub_483060((Point2D *)self,(struct SpriteS1 *)(local_20 + 8), (struct S127 *)&stack0xffffffc8); gta2::SpriteS1_sub_420600((Sprite *)this_01,(int)pSVar11->FirstElement, (int)local_44->FirstElement,*this_00); gta2::SpriteS1_SetRotation((Sprite *)this_01,(short)param_3); cVar5 = gta2::SpriteS1_sub_4BD670(this_01); if ((cVar5 != '\0') || (bVar4 = gta2::CollisionBox_FUN_00483060(param_1,this_01), bVar4 != 0))
          {
            piVar14 = (int *)gta2::SpriteS1_sub_4207B0(this_01,local_20);
            local_8 = (struct SpriteS3 *)*piVar14;
            local_4 = (struct S103 *)piVar14[1];
            gta2::SpriteS1_sub_420600((Sprite *)this_01,(int)local_30,(int)local_34,
                                *this_00);
            gta2::SpriteS1_SetRotation((Sprite *)this_01,(short)local_2c);
            gta2::sub_483100((struct EventHandler *)param_1,this_01);
          }


// 0x00483460: S63::sub_483460
// IDA: S63::sub_483460
// Ghidra: CollisionBox::FUN_00483460
byte gta2::S63_sub_483460(struct CollisionBox *self,undefined4 param_1)
{
  byte bVar1;
  bool bVar2;
  undefined3 extraout_var;
  
  _DAT_00665790 = 0;
  bVar1 = gta2::CollisionBox_FUN_00483060(self,(struct SpriteS1 *)self->Index);
  if (bVar1 == 0) {
    *(undefined4 *)(self->EventHandler[0].Struc___ + 0x34) = 2;
  }
  else {
    DAT_00593214 = 0;
    if (DAT_00665798 == '\0') {
      _DAT_00665790 = DAT_005e6894;
      bVar2 = gta2::Player_CheckCondition((struct Player *)&param_1,(int *)&DAT_006657ac);
      if (CONCAT31(extraout_var,bVar2) != 0) {
        if (*(int *)(self->EventHandler[0].Struc___ + 0x34) == 1) {
          gta2::S63_sub_482BF0(self);
        }
        else {
          gta2::SpriteS1_sub_40F7B0((struct SpriteS1 *)self->Index,6);
        }
        *(undefined4 *)(self->EventHandler[0].Struc___ + 0xc) = _DAT_006657ac;
        *(undefined4 *)(self->EventHandler[0].Struc___ + 0x18) =
             *(undefined4 *)&(self->EventHandler[0].NextElement)->CameraX;
        return 1;
      }
    }
  }
  return 0;
}


// 0x00483500: S63::sub_483500
// IDA: S63::sub_483500
// Ghidra: FUN_00483500
void gta2::S63_sub_483500(int param_1)
{
  struct CarSystemManager *self;
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  
  if (PTR_005e6874 != (void *)0x1) {
    if (PTR_005e6874 == (void *)0x2) {
      bVar1 = gta2::CarSystemManager_less_than((struct CarSystemManager *)(*(int *)(param_1 + 0x10) + 4),
                         (short *)&DAT_006659a4);
      _DAT_00665794 = 2 - (uint)(CONCAT31(extraout_var_01,bVar1) != 0);
    }
    return;
  }
  self = (struct CarSystemManager *)(*(int *)(param_1 + 0x10) + 4);
  bVar1 = gta2::CarSystemManager_less_than(self,(short *)&DAT_006658d0);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    bVar1 = gta2::CarSystemManager_greater_than(self,(short *)&DAT_00665ad0);
    if (CONCAT31(extraout_var_00,bVar1) != 0) {
      _DAT_00665794 = 4;
      return;
    }
  }
  _DAT_00665794 = 3;
  return;
}


// 0x004837f0: S63::sub_4837F0
// IDA: S63::sub_4837F0
// Ghidra: FUN_004837f0
void gta2::S63_sub_4837F0(CollisionBox *param_1,SpriteS1 *param_2)
{
  struct EventHandler *self;
  byte bVar1;
  char cVar2;
  struct Car *this_00;
  struct Ped *pPVar3;
  int explosionSize;
  void *this_01;
  
  bVar1 = FUN_00475a80(param_1);
  if ((((bVar1 != 0) && (cVar2 = FUN_00482c10(), cVar2 != '\0')) &&
      (bVar1 = gta2::FUN_00482400(this_01), bVar1 != 0)) &&
     (this_00 = (struct Car *)gta2::SpriteS1_GetCar(param_2), this_00 != NULL)) {
    if (param_1->EventHandler[0].GameObject == (struct GameObject *)0x84) {
      bVar1 = gta2::S63_sub_420FF0(param_1);
      pPVar3 = (struct Ped *)gta2::S68_sub_420F10(gScriptThread,bVar1);
      if (pPVar3 != NULL) {
        this_00->lastDamagingPed = pPVar3;
        this_00->DamageType = 0xc;
        this_00->Mask = 0x32;
      }
    }
    self = param_1->EventHandler[0].NextElement;
    explosionSize = gta2::FUN_004825e0(self,self[1].GameObject);
    gta2::Car_ExplodeCar(this_00,explosionSize);
  }
  return;
}


// 0x00483880: S63::sub_483880
// IDA: S63::sub_483880
// Ghidra: FUN_00483880
void gta2::S63_sub_483880(int param_1,SpriteS1 *param_2)
{
  struct SpriteS1 *self;
  undefined4 uVar1;
  undefined1 *this_00;
  undefined4 *puVar2;
  struct Car *pCVar3;
  undefined2 *puVar4;
  int iVar5;
  undefined1 *pS110;
  int *piVar6;
  undefined1 local_c [12];
  
  self = param_2;
  uVar1 = gta2::SpriteS1_getSpriteType(param_2);
  switch(uVar1) {
  case 2:
    pCVar3 = gta2::Car_sub_421D90(self->Matrix3DArray[0].Car,(struct Car *)(local_c + 8));
    *(Turrel **)(*(int *)(param_1 + 0x10) + 0xc) = pCVar3->Turret;
    puVar4 = (undefined2 *)FUN_00421e00(&param_2);
    *(undefined2 *)(*(int *)(param_1 + 0x10) + 4) = *puVar4;
    pCVar3 = (struct Car *)gta2::SpriteS1_GetCar(self);
    iVar5 = gta2::Car_sub_4243C0(pCVar3);
    gta2::SpriteS1_sub_40F7B0(*(SpriteS1 **)(param_1 + 4),iVar5);
    return;
  case 3:
    this_00 = local_c;
    piVar6 = (int *)&DAT_00665a60;
    pS110 = this_00;
    gta2::GameObject_sub_41B080((struct GameObject *)self->Matrix3DArray[0].Car,
               (SpawnPoint *)(local_c + 4));
    puVar2 = (undefined4 *)gta2::WorldCoordinateToScreenCoord(this_00,pS110,piVar6);
    *(undefined4 *)(*(int *)(param_1 + 0x10) + 0xc) = *puVar2;
    *(undefined2 *)(*(int *)(param_1 + 0x10) + 4) =
         *(undefined2 *)&self->FirstElement;
    gta2::SpriteS1_sub_40F7B0(*(SpriteS1 **)(param_1 + 4),0x1b);
    return;
  case 4:
  case 5:
    iVar5 = (self->Matrix3DArray[0].Car)->CarDoor_[0].doorState;
    if (iVar5 != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x10) + 0xc) =
           *(undefined4 *)(iVar5 + 0xc);
      *(undefined2 *)(*(int *)(param_1 + 0x10) + 4) =
           *(undefined2 *)
            ((self->Matrix3DArray[0].Car)->CarDoor_[0].doorState + 4);
      *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x10) =
           *(undefined4 *)
            ((self->Matrix3DArray[0].Car)->CarDoor_[0].doorState + 0x10);
    }
    gta2::SpriteS1_sub_40F7B0(*(SpriteS1 **)(param_1 + 4),0xc);
  }
  return;
}


// 0x00483990: S63::sub_483990
// IDA: S63::sub_483990
// Ghidra: ---
EventHandler * gta2::S63_sub_483990(struct EventHandler *self, S63_1 *a2, int x, int y, int z, CarSystemManager *a6)
{
  struct EventHandler *v7; // ecx
  struct SpriteS1 *SpriteS1; // eax

  v7 = (struct EventHandler *)gta2::PathNode_sub_488170(gPathNode, (int)a2);
  SpriteS1 = self->SpriteS1_;
  self->pEventHandler = v7;
  self->S63_1_ = a2;
  LOBYTE(self->S202_) = 0;
  if ( SpriteS1 )
    gta2::sub_4883A0(v7, SpriteS1);
  else
    self->SpriteS1_ = gta2::sub_488EF0(v7);
  gta2::SpriteS1_sub_420600(self->SpriteS1_, x, y, z);
  gta2::SpriteS1_SetRotation(self->SpriteS1_, a6);
  return gta2::SpriteS1_SetS63(self->SpriteS1_, self);
}


// 0x00483a20: S63::sub_483A20
// IDA: S63::sub_483A20
// Ghidra: FUN_00483a20
undefined4 gta2::S63_sub_483A20(CollisionBox *param_1,int param_2,int param_3)
{
  if (param_2 == 1) {
    if (param_3 == 2) {
      if (gObject->count == 0x168) {
LAB_00483a51:
        gta2::S63_sub_4827B0(param_1);
        return 1;
      }
      gObject->count = gObject->count + 1;
    }
    else if (param_3 == 3) {
      gObject->count_1 = gObject->count_1 + 1;
      FUN_004bed60(&gObject->SpriteS4,param_1->Index);
      return 0;
    }
  }
  else if (param_2 == 2) {
    if (param_3 == 1) {
      gObject->count = gObject->count + -1;
      return 0;
    }
    if (param_3 == 3) {
      gObject->count = gObject->count + -1;
      gObject->count_1 = gObject->count_1 + 1;
      FUN_004bed60(&gObject->SpriteS4,param_1->Index);
      return 0;
    }
  }
  else if (param_2 == 3) {
    if (param_3 == 1) {
      gObject->count_1 = gObject->count_1 + -1;
      FUN_004bec60(&gObject->SpriteS4,(struct VehiclePool *)param_1->Index);
      return 0;
    }
    if (param_3 == 2) {
      if (gObject->count != 0x168) {
        gObject->count_1 = gObject->count_1 + -1;
        FUN_004bec60(&gObject->SpriteS4,(struct VehiclePool *)param_1->Index);
        gObject->count = gObject->count + 1;
        return 0;
      }
      goto LAB_00483a51;
    }
  }
  return 0;
}


// 0x00483b50: S63::sub_483B50
// IDA: S63::sub_483B50
// Ghidra: ---
char gta2::S63_sub_483B50(struct EventHandler *self, SpriteS1 *a2)
{
  struct GameObject *GameObject; // eax
  struct Car *pCar; // eax

  if ( !a2 )
    return 0;
  GameObject = gta2::SpriteS1_GetGameObject(a2);
  if ( GameObject )
    return gta2::GameObject_sub_4930F0(GameObject, self);
  pCar = gta2::SpriteS1_GetCar(a2);
  if ( pCar )
    return gta2::Car_sub_4293D0(pCar, self);
  else
    return 0;
}


// 0x00483ba0: S63::sub_483BA0
// IDA: S63::sub_483BA0
// Ghidra: ---
void gta2::S63_sub_483BA0(struct EventHandler *self)
{
  struct Car *Car; // eax

  Car = self->Car;
  if ( Car )
    LOBYTE(Car->CarDoor_[2].doorState) = 1;
  if ( (gta2::General_GetCycle(gGeneral) & 3) == 0 )
  {
    gta2::SpriteS1_sub_4BAB10(self->SpriteS1_, 1);
    if ( gta2::SpriteS1_sub_4BDDD0(self->SpriteS1_, (int *)unk_665940, (int)unk_665940) )
    {
      gta2::SpriteS1_sub_420660(self->SpriteS1_, dword_665894);
      gta2::S63_sub_4827B0(self);
    }
  }
}


// 0x00483c20: S63::sub_483C20
// IDA: S63::sub_483C20
// Ghidra: EventHandler::FUN_00483c20
void * gta2::S63_sub_483C20(struct EventHandler *self,undefined4 param_1)
{
  short sVar1;
  void *pvVar2;
  
  sVar1 = *(short *)(self->Struc___ + 0x1e) + (ushort)(byte)param_1;
  pvVar2 = (void *)CONCAT22((short)((uint)self->Struc___ >> 0x10),sVar1);
  gta2::SpriteS1_sub_4206C0(self->Sprite,sVar1);
  return pvVar2;
}


// 0x00483c40: S63::sub_483C40
// IDA: S63::sub_483C40
// Ghidra: ---
void gta2::S63_sub_483C40(struct EventHandler *self)
{
  gta2::S63_sub_482F60(self);
  gta2::S63_sub_4827B0(self);
}


// 0x00483c50: S63::sub_483C50
// IDA: S63::sub_483C50
// Ghidra: ---
EventHandler * gta2::S63_sub_483C50(struct EventHandler *self)
{
  struct EventHandler *result; // eax

  result = gta2::S63_sub_482F60(self);
  LOBYTE(self->S202_) = 1;
  return result;
}


// 0x00483c60: S63::sub_483C60
// IDA: S63::sub_483C60
// Ghidra: ---
char gta2::S63_sub_483C60(struct EventHandler *self, char a2)
{
  char result; // al

  gta2::S63_sub_482F60(self);
  result = a2;
  LOBYTE(self->S202_) = a2;
  return result;
}


// 0x00483cc0: S63::sub_483CC0
// IDA: S63::sub_483CC0
// Ghidra: ---
int gta2::S63_sub_483CC0(struct EventHandler *self)
{
  struct SpriteS1 *SpriteS1; // esi
  int v3; // eax
  _WORD *v4; // esi
  int result; // eax
  int v6; // [esp-8h] [ebp-10h]
  int v7; // [esp-4h] [ebp-Ch]

  SpriteS1 = self->SpriteS1_;
  v7 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&SpriteS1->S3_arr5031[0].PositionZ);
  v6 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&SpriteS1->S3_arr5031[0].PositionY);
  v3 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&SpriteS1->S3_arr5031[0].PositionX);
  v4 = (_WORD *)gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct, v3, v6, v7);
  switch ( gta2::S63_GetIndex(self) )
  {
    case '-':
    case '/':
      result = gta2::Style_sub_462FD0(gStyle, *v4 & 0x3FF);
      break;
    case '.':
    case '0':
      result = gta2::Style_sub_462FD0(gStyle, v4[1] & 0x3FF);
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


// 0x00483d50: S63::sub_483D50
// IDA: S63::sub_483D50
// Ghidra: ---
void gta2::S63_sub_483D50(struct EventHandler *self)
{
  struct S63_1 *S63_1; // eax
  WeaponType v3; // eax
  char Weapon; // al

  S63_1 = self->S63_1_;
  if ( (int)S63_1 < 200 )
    v3 = (WeaponType)&S63_1[-2].field_2A;
  else
    v3 = (WeaponType)&S63_1[-4].field_C;
  if ( v3 <= WEAPON_27 )
  {
    Weapon = gta2::Turrel_GetWeapon(gArsenal, v3);
    gta2::S63_sub_45E0A0(self, Weapon);
  }
}


// 0x00483e50: S63::sub_483E50
// IDA: S63::sub_483E50
// Ghidra: ---
void gta2::S63_sub_483E50(struct EventHandler *self, SpriteS1 *a2)
{
  struct Car *Car; // eax
  int v4; // eax

  gta2::S63_sub_4826A0(self);
  if ( self->pEventHandler[1].pEventHandler != (struct EventHandler *)11 )
    gta2::S56_sub_447BA0(gCheckpoint3, self->SpriteS1_);
  gta2::S63_sub_482F80(self);
  Car = gta2::SpriteS1_GetCar(a2);
  if ( Car )
  {
    v4 = gta2::Car_sub_4243C0(Car);
    gta2::SpriteS1_sub_40F7B0(self->SpriteS1_, v4);
  }
}


// 0x00484260: S63::sub_484260
// IDA: S63::sub_484260
// Ghidra: FUN_00484260
undefined4 gta2::S63_sub_484260(CollisionBox *param_1,SpriteS1 *param_2,undefined4 *param_3, undefined1 *param_4,undefined1 *param_5)
{
  struct EventHandler *pEVar1;
  int iVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  undefined3 extraout_var;
  undefined4 *puVar6;
  undefined1 local_8 [8];
  
  *(undefined2 *)(param_1->EventHandler[0].Struc___ + 0x2a) = 1;
  bVar3 = gta2::Car_sub_403800((struct Car *)&param_2->Matrix3DArray[0].PositionZ,
                          (int *)&DAT_006658bc);
  if (CONCAT31(extraout_var,bVar3) != 0) {
    gta2::SpriteS1_sub_420660((Sprite *)param_2,_DAT_006658bc);
    *(undefined4 *)(param_1->EventHandler[0].Struc___ + 0x10) = _DAT_00665894;
    *(undefined4 *)(param_1->EventHandler[0].Struc___ + 0x1c) = _DAT_00665894;
  }
  cVar4 = FUN_004bbbe0();
  if (cVar4 != '\0') {
    *param_5 = 1;
    *(undefined4 *)(param_1->EventHandler[0].Struc___ + 0x10) = _DAT_00665894;
    *(undefined4 *)(param_1->EventHandler[0].Struc___ + 0x1c) = _DAT_00665894;
    pEVar1 = param_1->EventHandler[0].NextElement;
    iVar2._0_1_ = pEVar1[1].field15_0x24;
    iVar2._1_1_ = pEVar1[1].field16_0x25;
    iVar2._2_1_ = pEVar1[1].field17_0x26;
    iVar2._3_1_ = pEVar1[1].field18_0x27;
    if (iVar2 == 4) {
      return 1;
    }
  }
  cVar4 = gta2::SpriteS1_sub_4BD670(param_2);
  if (cVar4 != '\0') {
    iVar2 = param_1->EventHandler[0].Struc___;
    *(undefined4 *)(iVar2 + 0x14) = *(undefined4 *)(iVar2 + 0xc);
    puVar6 = (undefined4 *)gta2::SpriteS1_sub_4207B0(param_2,local_8);
    *param_3 = *puVar6;
    param_3[1] = puVar6[1];
    *param_4 = 1;
    FUN_00483500();
    return 1;
  }
  bVar5 = gta2::CollisionBox_FUN_00483060(param_1,param_2);
  if (bVar5 == 0) {
    return 0;
  }
  iVar2 = param_1->EventHandler[0].Struc___;
  bVar3 = DAT_00665798 == '\0';
  *(undefined4 *)(iVar2 + 0x14) = *(undefined4 *)(iVar2 + 0xc);
  if (bVar3) {
    puVar6 = (undefined4 *)gta2::SpriteS1_sub_4207B0(param_2,local_8);
    *param_3 = *puVar6;
    param_3[1] = puVar6[1];
    return 1;
  }
  puVar6 = (undefined4 *)gta2::SpriteS1_sub_4207B0(param_2,local_8);
  *param_3 = *puVar6;
  param_3[1] = puVar6[1];
  *param_4 = 1;
  return 1;
}


// 0x00484740: S63::sub_484740
// IDA: S63::sub_484740
// Ghidra: ---
char gta2::S63_sub_484740(struct EventHandler *self)
{
  if ( !gta2::SpriteS1_sub_4BAA90(self->SpriteS1_) )
    return 0;
  gta2::S63_sub_483BA0(self);
  return 1;
}


// 0x00484760: S63::sub_484760
// IDA: S63::sub_484760
// Ghidra: ---
void gta2::S63_sub_484760(struct EventHandler *self)
{
  struct S65 *pS116; // ecx
  struct Car *Car; // ecx

  pS116 = self->S65_;
  if ( pS116 )
  {
    if ( self->pEventHandler[1].pEventHandler == (struct EventHandler *)11 )
    {
      gta2::S115_sub_47F4F0(gS115, pS116);
    }
    else if ( self->field_1C )
    {
      gta2::S116_sub_48A510((struct S116 *)pS116);
    }
    else
    {
      gta2::S64_sub_483FC0(gTriggerVolume, pS116);
    }
    self->S65_ = 0;
  }
  Car = self->Car;
  if ( Car )
  {
    if ( Car->Car )
      gta2::Car_sub_4BF000(Car);
    gta2::S66_sub_484000(unk_665780, (struct S67 *)self->Car);
    self->Car = 0;
  }
}


// 0x004847d0: S63::sub_4847D0
// IDA: S63::sub_4847D0
// Ghidra: ---
int * gta2::S63_sub_4847D0(struct EventHandler *self, void *a2)
{
  struct Car *Element; // eax
  int v4; // ecx
  struct Player *v5; // edi
  int *result; // eax

  Element = (struct Car *)gta2::S66_NextElement(unk_665780);
  v4 = self->field_14;
  v5 = (struct Player *)a2;
  self->Car = Element;
  Element->CarDoor_[1].doorState = v4;
  *(_DWORD *)self->Car->CarDoor_[0].AnimationFrame = *(_DWORD *)gta2::Player_sub_41E260(v5, (int)&a2);
  sub_40F790(v5, (struct Car *)&a2);
  LOWORD(self->Car->Passenger_) = *(_WORD *)result;
  return result;
}


// 0x00484880: S63::sub_484880
// IDA: S63::sub_484880
// Ghidra: ---
EventHandler * gta2::S63_sub_484880(struct EventHandler *self)
{
  struct Car *Element; // eax
  int v3; // ecx

  if ( !self->Car )
  {
    Element = (struct Car *)gta2::S66_NextElement(unk_665780);
    v3 = self->field_14;
    self->Car = Element;
    Element->CarDoor_[1].doorState = v3;
    *(_DWORD *)self->Car->CarDoor_[0].AnimationFrame = dword_665894;
    self->Car->CarDoor_[0].doorState = dword_665894;
  }
  return gta2::S63_sub_482F60(self);
}


// 0x00484910: S63::sub_484910
// IDA: S63::sub_484910
// Ghidra: ---
SpriteS1 * gta2::S63_sub_484910(struct EventHandler *self)
{
  struct EventHandler *pS63; // eax
  struct SpriteS1 *SpriteS1; // eax
  unsigned __int8 v4; // al
  struct SpriteS1 *result; // eax

  pS63 = self->pEventHandler;
  self->S63_1_ = 0;
  SpriteS1 = pS63[2].SpriteS1;
  if ( SpriteS1 == (struct SpriteS1 *)2 )
  {
    --gObject->S63[0].pEventHandler;
  }
  else if ( SpriteS1 == (struct SpriteS1 *)3 )
  {
    --gObject->S63[0].S65;
    gta2::VehiclePool_S46_1FUN_004becb0((struct Arsenal *)&gObject->S63[0].field_14, (int)self->SpriteS1_);
  }
  --unk_66578C;
  if ( gta2::S63_sub_421080(self) )
  {
    v4 = BYTE2(self->S202_);
    if ( v4 )
    {
      gta2::S68_sub_4B9940(gScriptThread, v4);
      BYTE2(self->S202_) = 0;
    }
  }
  gta2::S63_sub_484760(self);
  result = self->SpriteS1_;
  if ( result )
  {
    result = gta2::SpriteS1_SpriteS1_Des(gSpriteS1, self->SpriteS1_);
    self->SpriteS1_ = 0;
  }
  self->field_14 = 0;
  return result;
}


// 0x004849b0: S63::sub_4849B0
// IDA: S63::sub_4849B0
// Ghidra: EventHandler::FUN_004849b0
void gta2::S63_sub_4849B0(struct EventHandler *self,Player *param_1)
{
  struct GameObject *pGVar1;
  undefined4 uVar2;
  void *this_00;
  undefined4 *puVar3;
  int *piVar4;
  undefined2 *puVar5;
  undefined1 *puVar6;
  struct SpriteS1 *pSVar7;
  struct Player *pPlayer;
  struct Player *local_14;
  undefined1 local_10 [8];
  undefined1 local_8 [8];
  
  pGVar1 = self->GameObject_;
  if (pGVar1 != NULL) {
    puVar6 = local_10;
    pSVar7 = (struct SpriteS1 *)param_1;
    this_00 = (void *)FUN_00482c50(local_8);
    puVar3 = (undefined4 *)FUN_0040f5c0(this_00,puVar6,pSVar7);
    pPlayer = (struct Player *)*puVar3;
    local_14 = (struct Player *)puVar3[1];
    piVar4 = gta2::Player_sub_41E260((struct Player *)&pPlayer,(int *)&param_1);
    pGVar1->S7[0].AnimationFrame = *piVar4;
    puVar5 = gta2::Player_FUN_0040f790((struct Player *)&pPlayer,(undefined2 *)&param_1);
    *(undefined2 *)&self->GameObject_->ObjectId = *puVar5;
    pGVar1 = self->GameObject_;
    uVar2 = *(undefined4 *)(self->Struc___ + 0x14);
    pGVar1->S7[0].ID = (char)uVar2;
    pGVar1->S7[0].field4_0xd = (char)((uint)uVar2 >> 8);
    pGVar1->S7[0].field5_0xe = (char)((uint)uVar2 >> 0x10);
    pGVar1->S7[0].field6_0xf = (char)((uint)uVar2 >> 0x18);
    return;
  }
  gta2::S63_sub_4847D0(self,param_1);
  return;
}


// 0x00484a40: S63::sub_484A40
// IDA: S63::sub_484A40
// Ghidra: EventHandler::FUN_00484a40
Player * gta2::S63_sub_484A40(struct EventHandler *self,Player *pPlayer)
{
  short sVar1;
  undefined2 extraout_var;
  
  gta2::S63_sub_4849B0(self,pPlayer);
  if ((*(int *)(self->Struc___ + 0x4c) == 3) &&
     (self->GameObject_->S7[2].PedInDoor == (struct Ped *)0x2)) {
    pPlayer = (struct Player *)0x9;
    sVar1 = gta2::Random_Random((struct Random *)&gRandom,(short)&pPlayer);
    pPlayer = (struct Player *)CONCAT22(extraout_var,sVar1);
    if (sVar1 < 6) {
      if (sVar1 < 3) {
        self->GameObject_->S7[2].PedInDoor = (struct Ped *)0x1;
        return pPlayer;
      }
      self->GameObject_->S7[2].PedInDoor = NULL;
    }
  }
  return pPlayer;
}


// 0x00484aa0: S63::sub_484AA0
// IDA: S63::sub_484AA0
// Ghidra: ---
char gta2::S63_sub_484AA0(struct EventHandler *self, byte a2)
{
  struct Car *Car; // eax

  if ( self->Car )
  {
    LOBYTE(Car) = a2;
    self->Car->CarDoor_[2].field_C = a2;
  }
  else
  {
    gta2::S63_sub_4847D0(self, &unk_6657D4);
    Car = self->Car;
    Car->CarDoor_[2].field_C = a2;
  }
  return (char)Car;
}


// 0x00484dd0: S63::sub_484DD0
// IDA: S63::sub_484DD0
// Ghidra: ---
void gta2::S63_sub_484DD0(struct EventHandler *self, EventHandler *a2)
{
  byte Index; // al

  if ( a2->S63_1_ == (struct S63_1 *)139 )
  {
    Index = gta2::S63_GetIndex(a2);
    gta2::S63_sub_484AA0(self, Index);
  }
  else if ( a2->S63_1_ == (struct S63_1 *)141 )
  {
    if ( LOBYTE(self->pEventHandler[2].pEventHandler) )
      gta2::S63_sub_483C40(self);
  }
}


// 0x00485760: S63::sub_485760
// IDA: S63::sub_485760
// Ghidra: CollisionBox::FUN_00485760
byte gta2::S63_sub_485760(struct CollisionBox *self,int param_1)
{
  struct Ped *pPVar1;
  int *piVar2;
  byte in_AL;
  byte bVar3;
  int iVar4;
  struct EventHandler *pEVar5;
  struct S67 *pSVar6;
  Sprite *pSVar7;
  void *this_00;
  undefined2 extraout_var;
  bool bVar8;
  undefined4 local_8;
  undefined4 local_4;
  
  if (param_1 == 0) {
    gta2::S63_sub_4827B0(self);
    return in_AL;
  }
  bVar3 = gta2::FUN_00482400(self);
  if (bVar3 == 0) {
    if (param_1 == 0x103) {
      pPVar1 = (struct Ped *)self->Index;
      FUN_0041e210(&local_8,(GlassInfo *)&DAT_00665a60,pPVar1);
      bVar3 = FUN_0048db00(*(undefined4 *)&pPVar1->S200_[6].c,
                           *(undefined4 *)(pPVar1->S200_ + 8),
                           *(undefined4 *)&pPVar1->S200_[9].Y,local_8,local_4);
      gta2::S63_sub_4827B0(self);
      return bVar3;
    }
    iVar4 = gta2::S57_sub_488170(gPathNode,param_1);
    pSVar7 = self->EventHandler[0].NextElement[2].Sprite;
    if ((pSVar7 == *(Sprite **)(iVar4 + 0x5c)) ||
       (bVar3 = FUN_00483a20(pSVar7,*(Sprite **)(iVar4 + 0x5c)), bVar3 == 0)) {
      if ((DAT_00665774 == '\0') && (DAT_00665761 == 0)) {
        gta2::S63_sub_4826A0(self);
      }
      gta2::S3_sub_4BCCC0((Matrix3D *)self->Index);
      switch(*(undefined4 *)(iVar4 + 0x34)) {
      case 0:
      case 1:
      case 6:
      case 10:
      case 0xc:
        gta2::S63_sub_484760(self);
        pEVar5 = self->Index;
        gta2::S63_sub_483990(self,param_1,*(undefined4 *)&pEVar5->CameraX,
                   pEVar5->DamageType,*(undefined4 *)&pEVar5->z,
                   *(undefined2 *)&pEVar5->NextElement);
        if (self->EventHandler[0].Struc___ != 0) {
          return (byte)pEVar5;
        }
        break;
      case 2:
      case 8:
        piVar2 = (int *)self->EventHandler[0].Struc___;
        if ((piVar2 != NULL) && (*piVar2 == 0)) {
          gta2::S6_AddToList(piVar2);
          self->EventHandler[0].Struc___ = 0;
        }
        bVar8 = self->EventHandler[0].Sprite == NULL;
        if (bVar8) {
          pSVar7 = (Sprite *)gta2::S64_sub_483FA0(gS64);
          self->EventHandler[0].Sprite = pSVar7;
        }
        pEVar5 = self->EventHandler[0].NextElement;
        if ((*(char *)(iVar4 + 0x65) !=
             *(char *)((int)&pEVar5[2].DamageInfo + 1)) || (bVar8)) {
          *(short *)&(self->EventHandler[0].Sprite)->field1_0x4 =
               (short)*(char *)(iVar4 + 0x65);
          *(undefined1 *)((int)&(self->EventHandler[0].Sprite)->field1_0x4 + 3)
               = 0;
          *(undefined1 *)((int)&(self->EventHandler[0].Sprite)->field1_0x4 + 2)
               = 0;
        }
        else if (*(byte *)(iVar4 + 0x6c) < pEVar5[2].CameraX) {
          *(bool *)((int)&(self->EventHandler[0].Sprite)->field1_0x4 + 3) =
               bVar8;
        }
        pEVar5 = self->Index;
        gta2::S63_sub_483990(self,param_1,*(undefined4 *)&pEVar5->CameraX,
                   pEVar5->DamageType,*(undefined4 *)&pEVar5->z,
                   *(undefined2 *)&pEVar5->NextElement);
        gta2::SpriteS1_sub_4206C0((Sprite *)self->Index,
                         (ushort)*(byte *)((int)&(self->EventHandler[0].Sprite)
                                                 ->field1_0x4 + 3) +
                         *(short *)&(self->EventHandler[0].NextElement)->
                                    field_0x1e);
        break;
      case 3:
      case 7:
        if (self->EventHandler[0].Struc___ == 0) {
          pSVar6 = gta2::S66_NextElement(gS66);
          self->EventHandler[0].Struc___ = pSVar6;
          pSVar6->field11_0x20 = self->EventHandler[0].DamageInfo;
        }
        pSVar7 = self->EventHandler[0].Sprite;
        if (pSVar7 != NULL) {
          gta2::S64_sub_483FC0(gS64,&pSVar7->field0_0x0);
          self->EventHandler[0].Sprite = NULL;
        }
        *(undefined4 *)(self->EventHandler[0].Struc___ + 0x18) =
             *(undefined4 *)(iVar4 + 0x14);
        *(undefined4 *)(self->EventHandler[0].Struc___ + 0x1c) = _DAT_00665894;
        *(undefined4 *)(self->EventHandler[0].Struc___ + 0x10) = _DAT_00665894;
        *(short *)(self->EventHandler[0].Struc___ + 0x28) =
             (short)*(char *)(iVar4 + 0x65);
        pEVar5 = self->Index;
        gta2::S63_sub_483990(self,param_1,*(undefined4 *)&pEVar5->CameraX,
                   pEVar5->DamageType,*(undefined4 *)&pEVar5->z,
                   *(undefined2 *)&pEVar5->NextElement);
        break;
      case 4:
      case 9:
        if (self->EventHandler[0].Struc___ == 0) {
          pSVar6 = gta2::S66_NextElement(gS66);
          self->EventHandler[0].Struc___ = pSVar6;
          pSVar6->field11_0x20 = self->EventHandler[0].DamageInfo;
        }
        bVar8 = self->EventHandler[0].Sprite == NULL;
        if (bVar8) {
          pSVar7 = (Sprite *)gta2::S64_sub_483FA0(gS64);
          self->EventHandler[0].Sprite = pSVar7;
        }
        pEVar5 = self->EventHandler[0].NextElement;
        if ((*(char *)(iVar4 + 0x65) !=
             *(char *)((int)&pEVar5[2].DamageInfo + 1)) || (bVar8)) {
          *(short *)&(self->EventHandler[0].Sprite)->field1_0x4 =
               (short)*(char *)(iVar4 + 0x65);
          *(undefined1 *)((int)&(self->EventHandler[0].Sprite)->field1_0x4 + 3)
               = 0;
          *(undefined1 *)((int)&(self->EventHandler[0].Sprite)->field1_0x4 + 2)
               = 0;
        }
        else if (*(byte *)(iVar4 + 0x6c) < pEVar5[2].CameraX) {
          *(bool *)((int)&(self->EventHandler[0].Sprite)->field1_0x4 + 3) =
               bVar8;
        }
        pEVar5 = self->Index;
        gta2::S63_sub_483990(self,param_1,*(undefined4 *)&pEVar5->CameraX,
                   pEVar5->DamageType,*(undefined4 *)&pEVar5->z,
                   *(undefined2 *)&pEVar5->NextElement);
        gta2::SpriteS1_sub_4206C0((Sprite *)self->Index,
                         (ushort)*(byte *)((int)&(self->EventHandler[0].Sprite)
                                                 ->field1_0x4 + 3) +
                         *(short *)&(self->EventHandler[0].NextElement)->
                                    field_0x1e);
        *(undefined4 *)(self->EventHandler[0].Struc___ + 0x18) =
             *(undefined4 *)(iVar4 + 0x14);
        *(undefined4 *)(self->EventHandler[0].Struc___ + 0x1c) = _DAT_00665894;
        *(undefined4 *)(self->EventHandler[0].Struc___ + 0x10) = _DAT_00665894;
      }
      if ((*(char *)(iVar4 + 0x61) == '\0') &&
         (self->EventHandler[0].field_0x1d == '\0')) {
        gta2::S63_sub_482F80((Sprite *)self);
      }
      bVar3 = DAT_00665761;
      if (DAT_00665761 == 0) {
        DAT_00665760 = 1;
        bVar3 = gta2::S63_sub_482630(self);
      }
    }
    return bVar3;
  }
  pEVar5 = self->Index;
  gta2::S68_sub_420F10(gScriptThread,self->EventHandler[0].field_0x1e);
  iVar4 = gta2::FUN_004825e0(this_00,param_1);
  pEVar5 = (struct EventHandler *)
           gta2::Object_sub_485540(gObject,*(undefined4 *)&pEVar5->CameraX,pEVar5->DamageType
                      ,*(undefined4 *)&pEVar5->z,
                      (void *)CONCAT22(extraout_var,_DAT_006657f8______S38),
                      iVar4);
  if (pEVar5 != NULL) {
    gta2::S63_sub_482790(pEVar5,self->EventHandler[0].field_0x1e);
  }
  bVar3 = (byte)pEVar5;
  gta2::S63_sub_4827B0(self);
  return bVar3;
}


// 0x00485b00: S63::sub_485B00
// IDA: S63::sub_485B00
// Ghidra: ---
char gta2::S63_sub_485B00(struct EventHandler *self, void *a2)
{
  struct Ped *Ped; // eax
  int v4; // ebx
  struct SpriteS1 *SpriteS1; // esi
  int v6; // eax
  int v7; // ecx
  struct EventHandler *v8; // eax
  char v9; // al
  struct Ped *v10; // eax

  Ped = (struct Ped *)&self->S63_1_[-3].field_1F;
  if ( (unsigned int)Ped <= 0x95 )
  {
    switch ( byte_485BF0[(_DWORD)Ped] )
    {
      case 0:
        if ( *((_DWORD *)a2 + 6) == 166 )
          v4 = sub_483C80(a2);
        else
          v4 = (*(_DWORD *)(*((_DWORD *)a2 + 2) + 72) == 13) + 18;
        SpriteS1 = self->SpriteS1_;
        v6 = gta2::S68_sub_420F10(gScriptThread, BYTE2(self->S202_));
        LOWORD(v7) = word_6657F8[0];
        v8 = (struct EventHandler *)gta2::Object_sub_485540(
                               gObject,
                               SpriteS1->S3_arr5031[0].PositionX,
                               SpriteS1->S3_arr5031[0].PositionY,
                               SpriteS1->S3_arr5031[0].PositionZ,
                               v7,
                               v4,
                               v6);
        if ( v8 )
          gta2::S63_sub_482790(v8, BYTE2(self->S202_));
        goto LABEL_8;
      case 1:
LABEL_8:
        v9 = gta2::S63_sub_420FF0(self);
        v10 = (struct Ped *)gta2::S68_sub_420F10(gScriptThread, v9);
        if ( v10 )
          Ped = gta2::Character_FindPed(gCharacter, v10);
        else
          Ped = 0;
        if ( *((_DWORD *)a2 + 6) == 166 && Ped )
          LOBYTE(Ped) = sub_435180(
                          Ped,
                          self->SpriteS1_->S3_arr5031[0].PositionX,
                          self->SpriteS1_->S3_arr5031[0].PositionY,
                          (struct Car *)self->S63_1_);
        break;
      case 2:
        return (char)Ped;
    }
  }
  return (char)Ped;
}


// 0x00485bf1: S63::sub_485C90
// IDA: S63::sub_485C90
// Ghidra: ---
  return gta2::S63_sub_485C90(self);
}


// 0x00485c90: S63::sub_485C90
// IDA: S63::sub_485C90
// Ghidra: ---
char gta2::S63_sub_485C90(struct EventHandler *self)
{
  struct Ped *Ped; // eax
  struct SpriteS1 *SpriteS1; // edi
  int v4; // eax
  struct EventHandler *v5; // eax
  struct SpriteS1 *v6; // edi
  void *v7; // eax
  char v8; // al
  int v10; // [esp-Ch] [ebp-1Ch]
  int v11; // [esp-8h] [ebp-18h]
  _WORD a2[2]; // [esp+4h] [ebp-Ch] BYREF
  char argC[4]; // [esp+8h] [ebp-8h] BYREF
  int a6; // [esp+Ch] [ebp-4h]

  Ped = (struct Ped *)&self->S63_1_[-3].field_1F;
  if ( (unsigned int)Ped <= 0x95 )
  {
    switch ( byte_485D9C[(_DWORD)Ped] )
    {
      case 0:
        SpriteS1 = self->SpriteS1_;
        v11 = gta2::S68_sub_420F10(gScriptThread, BYTE2(self->S202_));
        v4 = sub_482410(unk_665794);
        v10 = v4;
        LOWORD(v4) = word_6657F8[0];
        v5 = (struct EventHandler *)gta2::Object_sub_485540(
                               gObject,
                               SpriteS1->S3_arr5031[0].PositionX,
                               SpriteS1->S3_arr5031[0].PositionY,
                               SpriteS1->S3_arr5031[0].PositionZ,
                               v4,
                               v10,
                               v11);
        if ( v5 )
          gta2::S63_sub_482790(v5, BYTE2(self->S202_));
        goto LABEL_5;
      case 1:
        goto LABEL_6;
      case 2:
LABEL_5:
        v6 = self->SpriteS1_;
        v7 = gta2::sub_40E5A0((struct CarSystemManager *)v6, (struct CarSystemManager *)&a2[1], &unk_6659A4);
        gta2::sub_41E210(argC, &unk_665A60, (int)v7);
        gta2::Particles_sub_48DB00(
          gParticles,
          v6->S3_arr5031[0].PositionX,
          v6->S3_arr5031[0].PositionY,
          v6->S3_arr5031[0].PositionZ,
          argC[0],
          a6);
LABEL_6:
        v8 = gta2::S63_sub_420FF0(self);
        Ped = (struct Ped *)gta2::S68_sub_420F10(gScriptThread, v8);
        if ( Ped )
        {
          Ped = gta2::Character_FindPed(gCharacter, Ped);
          if ( Ped )
            LOBYTE(Ped) = sub_435180(
                            Ped,
                            self->SpriteS1_->S3_arr5031[0].PositionX,
                            self->SpriteS1_->S3_arr5031[0].PositionY,
                            (struct Car *)self->S63_1_);
        }
        break;
      case 3:
        return (char)Ped;
    }
  }
  return (char)Ped;
}


// 0x00485fd0: S63::sub_485FD0
// IDA: S63::sub_485FD0
// Ghidra: ---
void gta2::S63_sub_485FD0(struct EventHandler *self)
{
  struct S65 *S65; // eax
  struct S65 *v3; // eax
  struct S65 *v4; // eax
  __int16 v5; // cx

  ++LOBYTE(self->S65_->field_6);
  S65 = self->S65_;
  if ( LOBYTE(S65->field_6) >= SLOBYTE(self->pEventHandler[2].S65) )
  {
    LOBYTE(S65->field_6) = 0;
    ++HIBYTE(self->S65_->field_6);
    v3 = self->S65_;
    if ( HIBYTE(v3->field_6) >= LOBYTE(self->pEventHandler[2].field_14) )
    {
      HIBYTE(v3->field_6) = 0;
      v4 = self->S65_;
      v5 = v4->field_4;
      if ( v5 > 0 )
        v4->field_4 = v5 - 1;
    }
    gta2::SpriteS1_sub_4206C0(self->SpriteS1_, *(_WORD *)&self->pEventHandler->field_1E + HIBYTE(self->S65_->field_6));
    if ( gta2::S63_sub_482C10(self) )
      gta2::S63_sub_485760(self, (int)self->pEventHandler[1].Car);
  }
}


// 0x00486060: S63::sub_486060
// IDA: S63::sub_486060
// Ghidra: ---
char gta2::S63_sub_486060(struct EventHandler *self)
{
  char S202; // al
  struct EventHandler *pEventHandler; // edi
  char result; // al
  struct EventHandler *v5; // eax
  struct S63_1 *S63_1; // ecx

  S202 = (char)self->S202_;
  if ( S202 )
  {
    pEventHandler = self->pEventHandler;
    switch ( (unsigned int)pEventHandler[1].S63_1 )
    {
      case 1u:
      case 2u:
      case 5u:
      case 6u:
      case 8u:
      case 0xBu:
        if ( S202 == 1 )
          gta2::S63_sub_485760(self, (int)pEventHandler[1].S65);
        else
          gta2::S63_sub_485760(self, LOBYTE(self->S202_));
        LOBYTE(self->S202_) = 0;
        result = 1;
        break;
      case 4u:
        if ( S202 != 1 )
          gta2::S63_sub_485760(self, LOBYTE(self->S202_));
        LOBYTE(self->S202_) = 0;
        result = 1;
        break;
      case 7u:
      case 0xAu:
        LOBYTE(self->S202_) = 0;
        gta2::S63_sub_4827B0(self);
        result = 1;
        break;
      default:
        LOBYTE(self->S202_) = 0;
        result = 0;
        break;
    }
  }
  else
  {
    v5 = self->pEventHandler;
    S63_1 = v5[1].S63_1;
    if ( S63_1 == (struct S63_1 *)3 || S63_1 == (struct S63_1 *)4 )
    {
      gta2::S63_sub_485760(self, (int)v5[1].S65);
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return result;
}


// 0x00486390: S63::sub_486390
// IDA: S63::sub_486390
// Ghidra: ---
char gta2::S63_sub_486390(struct EventHandler *self, SpriteS1 *a2)
{
  struct GameObject *GameObject; // eax
  struct Car *pCar; // eax
  struct Car *v6; // esi
  char v7; // al
  struct Ped *v8; // eax
  struct Ped *Ped; // eax

  GameObject = gta2::SpriteS1_GetGameObject(a2);
  if ( GameObject )
    return gta2::sub_4932D0(GameObject, self);
  pCar = gta2::SpriteS1_GetCar(a2);
  if ( pCar )
    return gta2::Car_sub_4274C0(pCar, self);
  v6 = (struct Car *)gta2::SpriteS1_sub_40FEC0(a2);
  v7 = gta2::S63_sub_420FF0(self);
  v8 = (struct Ped *)gta2::S68_sub_420F10(gScriptThread, v7);
  if ( v8 )
  {
    Ped = gta2::Character_FindPed(gCharacter, v8);
    if ( Ped )
      gta2::Ped_sub_4350C0(Ped, v6);
  }
  return gta2::sub_486360(v6, self);
}


// 0x00486410: S63::sub_486410
// IDA: S63::sub_486410
// Ghidra: ---
char gta2::S63_sub_486410(struct EventHandler *self, void *a2)
{
  char result; // al
  struct EventHandler *pEventHandler; // eax
  char v5; // al
  char v6; // al

  result = (char)self->S202_;
  if ( !result && (!a2 || (result = gta2::S63_sub_482FA0(self, (struct SpriteS1 *)a2)) != 0) )
  {
    pEventHandler = self->pEventHandler;
    LOBYTE(self->S202_) = 1;
    switch ( (unsigned int)pEventHandler[1].S63_1 )
    {
      case 1u:
      case 2u:
        goto LABEL_10;
      case 3u:
        LOBYTE(self->S202_) = gta2::SpriteS1_GetCar((struct SpriteS1 *)a2) != 0;
        goto LABEL_14;
      case 4u:
      case 5u:
        LOBYTE(self->S202_) = gta2::SpriteS1_GetGameObject((struct SpriteS1 *)a2) != 0;
        goto LABEL_14;
      case 6u:
        v5 = gta2::S63_sub_483B50(self, (struct SpriteS1 *)a2);
        LOBYTE(self->S202_) = v5;
        if ( v5 )
          goto LABEL_10;
        break;
      case 7u:
      case 8u:
        if ( a2 )
          LOBYTE(self->S202_) = gta2::S63_sub_486390(self, (struct SpriteS1 *)a2);
        else
          gta2::S63_sub_485C90(self);
LABEL_14:
        result = (char)self->S202_;
        if ( !result )
          return result;
LABEL_10:
        gta2::S63_sub_482F60(self);
        break;
      case 9u:
        v6 = gta2::S63_sub_483B50(self, (struct SpriteS1 *)a2);
        goto LABEL_18;
      case 0xAu:
        if ( !a2 )
          break;
        v6 = gta2::SpriteS1_GetGameObject((struct SpriteS1 *)a2) != 0;
LABEL_18:
        LOBYTE(self->S202_) = v6;
        break;
      case 0xBu:
        LOBYTE(self->S202_) = 0;
        break;
      default:
        break;
    }
    result = (char)self->S202_;
    if ( result )
    {
      if ( a2 )
      {
        if ( !gta2::S63_sub_421060(self) )
          return gta2::CameraOrPhysics_sub_410480(gCameraOrPhysics, self->SpriteS1_, (int)a2);
        result = sub_4BCA80((struct SpriteS1 *)a2);
        if ( !result )
          return gta2::CameraOrPhysics_sub_410480(gCameraOrPhysics, self->SpriteS1_, (int)a2);
      }
      else if ( dword_5E6874 == 4 )
      {
        return gta2::CameraOrPhysics_sub_4102A0(gCameraOrPhysics, self->SpriteS1_);
      }
      else if ( dword_5E6874 == 5 )
      {
        return gta2::CameraOrPhysics_sub_410370(gCameraOrPhysics, self->SpriteS1_);
      }
      else
      {
        return gta2::CameraOrPhysics_sub_410460(gCameraOrPhysics, self->SpriteS1_);
      }
    }
  }
  return result;
}


// 0x00486580: S63::sub_486580
// IDA: S63::sub_486580
// Ghidra: CollisionBox::FUN_00486580
byte gta2::S63_sub_486580(struct CollisionBox *self,int param_1,GlassInfo *param_2)
{
  struct CollisionBox *pCVar1;
  int iVar2;
  byte bVar3;
  bool bVar4;
  undefined4 *puVar5;
  GlassInfo *pGVar6;
  void *pvVar7;
  undefined4 *puVar8;
  struct Player *this_00;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  struct Player *pPVar9;
  int *piVar10;
  struct CarSystemManager *this_01;
  undefined3 extraout_var_01;
  undefined1 *puVar11;
  short *psVar12;
  undefined4 local_60 [2];
  short local_58;
  undefined4 local_54;
  struct CollisionBox *local_50;
  struct Player *local_4c;
  struct CollisionBox *local_48;
  struct Player *local_44;
  struct Player *local_40;
  struct Player *local_3c;
  undefined1 local_38 [8];
  undefined1 local_30 [8];
  undefined1 local_28 [8];
  undefined1 local_20 [8];
  undefined1 local_18 [8];
  undefined1 local_10 [12];
  
  FUN_00482c30(local_30);
  FUN_00482c30(local_38);
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&local_58);
  puVar5 = (undefined4 *)FUN_0040f600(local_38,&local_40,param_2);
  local_50 = (struct CollisionBox *)*puVar5;
  local_4c = (struct Player *)puVar5[1];
  bVar3 = gta2::S63_sub_482C90((struct CollisionBox *)param_1);
  if (bVar3 == 0) {
    puVar5 = (undefined4 *)FUN_00482c50(local_10);
    pCVar1 = (struct CollisionBox *)*puVar5;
    local_44 = (struct Player *)puVar5[1];
    local_48 = pCVar1;
    bVar4 = gta2::Player_IsCurrentPlayer((struct Player *)&local_50,(struct Player *)&DAT_00665894)
    ;
    pPVar9 = (struct Player *)CONCAT31(extraout_var,bVar4);
    if ((struct Player *)CONCAT31(extraout_var,bVar4) != NULL) {
      bVar4 = gta2::Player_IsCurrentPlayer((struct Player *)&local_4c,(struct Player *)&DAT_00665894);
      pPVar9 = (struct Player *)CONCAT31(extraout_var_00,bVar4);
      if ((struct Player *)CONCAT31(extraout_var_00,bVar4) != NULL) {
        local_4c = local_44;
        pPVar9 = local_44;
        local_50 = pCVar1;
      }
    }
    gta2::S63_sub_482C80(self,&local_54);
    puVar5 = (undefined4 *)
             FUN_004a05c0(local_10,pPVar9->CurrentPlayer,_DAT_0066583c,&local_48
                          ,&local_50,param_2,local_38,local_30,_DAT_00665ae4,
                          _DAT_00665ae4,_DAT_00665a3c);
    local_40 = (struct Player *)*puVar5;
    local_3c = (struct Player *)puVar5[1];
  }
  else {
    pGVar6 = (GlassInfo *)FUN_00482c50(&local_40);
    puVar5 = local_60;
    pvVar7 = (void *)FUN_00482c50(local_28);
    puVar5 = (undefined4 *)FUN_0040f600(pvVar7,puVar5,pGVar6);
    local_48 = (struct CollisionBox *)*puVar5;
    local_44 = (struct Player *)puVar5[1];
    puVar5 = local_60;
    gta2::S63_sub_482C80((struct CollisionBox *)param_1,puVar5);
    puVar8 = puVar5;
    gta2::S63_sub_482C80(self,&local_54);
    puVar5 = (undefined4 *)
             FUN_004a05c0(local_20,*puVar8,*puVar5,&local_48,&local_50,param_2,
                          local_38,local_30,_DAT_00665ae4,_DAT_00665ae4,
                          _DAT_006659f0);
    local_40 = (struct Player *)*puVar5;
    pPVar9 = (struct Player *)puVar5[1];
    local_3c = pPVar9;
    gta2::S63_sub_482C80((struct CollisionBox *)param_1,&local_54);
    puVar11 = local_18;
    this_00 = (struct Player *)gta2::Player_FUN_0040f640((struct Player *)&local_40,local_10);
    pvVar7 = gta2::Player_FUN_004202e0(this_00,puVar11,(int *)pPVar9);
    gta2::S63_sub_484A40((struct EventHandler *)param_1,pvVar7);
  }
  piVar10 = (int *)self->EventHandler[0].Struc___;
  if (piVar10 != NULL) {
    local_58 = (short)piVar10[1];
  }
  gta2::S63_sub_482C80(self,&local_54);
  pvVar7 = gta2::Player_FUN_004202e0((struct Player *)&local_40,local_10,piVar10);
  gta2::S63_sub_484A40((struct EventHandler *)self,pvVar7);
  if ((DAT_00665798 != '\0') &&
     (iVar2 = self->EventHandler[0].Struc___, iVar2 != 0)) {
    psVar12 = (short *)&DAT_00665ad0;
    this_01 = (struct CarSystemManager *)
              gta2::sub_40EAB0((Sprite *)&local_58,(undefined2 *)local_60,
                         (struct CarSystemManager *)(iVar2 + 4),(int)&local_58);
    bVar4 = gta2::CarSystemManager_less_than(this_01,psVar12);
    if (CONCAT31(extraout_var_01,bVar4) != 0) {
      gta2::CarSystemManager_FUN_0041fa70((struct CarSystemManager *)(self->EventHandler[0].Struc___ + 4),
                 (short *)&DAT_006659a4);
    }
  }
  gta2::S63_sub_486410((struct CollisionBox *)param_1,(struct SpriteS1 *)self->Index);
  bVar3 = gta2::S63_sub_486410(self,*(SpriteS1 **)(param_1 + 4));
  return bVar3;
}


// 0x004867e0: S63::sub_4867E0
// IDA: S63::sub_4867E0
// Ghidra: CollisionBox::FUN_004867e0
void gta2::S63_sub_4867E0(struct CollisionBox *self,int param_1,GlassInfo *param_2)
{
  struct Ped *this_00;
  bool bVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  struct Player **ppPVar5;
  void *pPlayer_00;
  struct Player *pPVar6;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  struct SpriteS1 *pSVar7;
  struct VehiclePool **ppVVar8;
  undefined1 *puVar9;
  undefined1 *puVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  int *piVar14;
  struct Player *pPlayer;
  struct Player *local_4c;
  struct Player *local_48;
  struct Player *local_44;
  undefined1 local_40 [8];
  struct VehiclePool *local_38;
  struct Ped *local_34;
  undefined1 local_30 [8];
  undefined1 local_28 [8];
  undefined1 local_20 [8];
  undefined1 local_18 [8];
  undefined1 local_10 [12];
  
  this_00 = *(Ped **)(param_1 + 0x7c);
  puVar2 = (undefined4 *)gta2::Ped_GetYCoordinate(this_00, &pPlayer);
  puVar3 = (undefined4 *)gta2::Ped_GetXCoordinate(this_00,(int)&local_48);
  String_ParseLine(local_30,puVar3,puVar2);
  FUN_00482c30(local_40);
  puVar2 = (undefined4 *)FUN_0040f600(local_40,&local_48,param_2);
  local_38 = (struct VehiclePool *)*puVar2;
  local_34 = (struct Ped *)puVar2[1];
  pPVar6 = (struct Player *)&local_48;
  gta2::S63_sub_482C80(self,(undefined4 *)pPVar6);
  puVar10 = local_30;
  puVar9 = local_40;
  ppVVar8 = &local_38;
  uVar11 = _DAT_00665ae4;
  uVar12 = _DAT_006659ec;
  uVar13 = _DAT_006659d4;
  pPlayer = pPVar6;
  uVar4 = FUN_00493780(local_28);
  puVar2 = (undefined4 *)
           FUN_004a05c0(local_20,pPlayer->CurrentPlayer,_DAT_00665824,uVar4,
                        ppVVar8,param_2,puVar9,puVar10,uVar11,uVar12,uVar13);
  pPlayer = (struct Player *)*puVar2;
  local_4c = (struct Player *)puVar2[1];
  ppPVar5 = &local_48;
  gta2::S63_sub_482C80(self,ppPVar5);
  pPlayer_00 = gta2::Player_FUN_004202e0((struct Player *)&pPlayer,local_18,(int *)ppPVar5);
  gta2::S63_sub_484A40((struct EventHandler *)self,pPlayer_00);
  piVar14 = (int *)&DAT_00665824;
  puVar10 = local_10;
  pPVar6 = (struct Player *)gta2::Player_FUN_0040f640((struct Player *)&pPlayer,local_18);
  gta2::Player_FUN_004202e0(pPVar6,puVar10,piVar14);
  pPVar6 = _DAT_00665894;
  local_48 = _DAT_00665894;
  local_44 = _DAT_00665894;
  bVar1 = gta2::Car_IsTrainOrTrainCarriage((struct Car *)&local_48,(struct Car *)&DAT_00665894);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    bVar1 = gta2::Car_IsTrainOrTrainCarriage((struct Car *)&local_44,(struct Car *)&DAT_00665894);
    if (CONCAT31(extraout_var_00,bVar1) == 0) goto LAB_00486936;
  }
  FUN_00497570((void *)param_1,0,0,pPVar6,pPVar6);
LAB_00486936:
  pSVar7 = (struct SpriteS1 *)FUN_004338d0((void *)param_1);
  gta2::S63_sub_486410(self,pSVar7);
  return;
}


// 0x00486950: S63::sub_486950
// IDA: S63::sub_486950
// Ghidra: FUN_00486950
void gta2::S63_sub_486950(CollisionBox *param_1,undefined4 param_2,undefined4 param_3, undefined4 param_4)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  int *piVar3;
  void *pPlayer;
  undefined *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 local_1c;
  undefined1 local_18 [8];
  undefined1 local_10 [8];
  undefined1 local_8 [8];
  
  puVar1 = &local_1c;
  gta2::S63_sub_482C80(param_1,&local_1c);
  puVar4 = &DAT_006657d4;
  uVar5 = _DAT_00665ae4;
  uVar6 = _DAT_00665894;
  uVar7 = _DAT_006657b8;
  uVar2 = FUN_00482c30(local_10);
  piVar3 = (int *)FUN_004a05c0(local_18,*puVar1,_DAT_0066583c,param_4,param_3,
                               param_2,uVar2,puVar4,uVar5,uVar6,uVar7);
  gta2::S63_sub_482C80(param_1,&param_2);
  pPlayer = gta2::Player_FUN_004202e0((struct Player *)local_18,local_8,piVar3);
  gta2::S63_sub_484A40((struct EventHandler *)param_1,pPlayer);
  gta2::S63_sub_486410(param_1,NULL);
  return;
}


// 0x004869e0: S63::sub_4869E0
// IDA: S63::sub_4869E0
// Ghidra: CollisionBox::FUN_004869e0
void gta2::S63_sub_4869E0(struct CollisionBox *self,Car *param_1)
{
  char cVar1;
  bool bVar2;
  char *pcVar3;
  undefined4 *puVar4;
  GlassInfo *pGVar5;
  struct SpriteS1 *pSpriteS1;
  Point2D *this_00;
  undefined3 extraout_var;
  struct Player *this_01;
  struct Player *this_02;
  undefined1 local_29;
  int local_28 [2];
  int local_20 [2];
  undefined1 local_18 [8];
  struct Player *local_10;
  struct Player *local_c;
  struct Ped *local_8;
  struct Ped *local_4;
  
  pcVar3 = (char *)FUN_00482c50(local_20);
  local_10 = *(Player **)pcVar3;
  local_c = *(Player **)(pcVar3 + 4);
  cVar1 = FUN_004bcd00(DAT_005e688c,local_18,&local_29);
  if (cVar1 == '\0') {
    FUN_00432860(local_18,&DAT_005e6888,&DAT_005e688c);
    FUN_004828c0(local_18,(int *)param_1);
    gta2::Player_sub_40E530((Point2D *)local_18,(int *)&self->Index->CameraX);
    local_18._4_4_ = DAT_005e688c;
    pGVar5 = (GlassInfo *)
             gta2::Player_sub_401B40((SpawnPoint *)local_18,(GlassInfo *)&param_1,
                        (struct S127 *)&DAT_005e687c);
    pSpriteS1 = (struct SpriteS1 *)gta2::Player_FUN_00403840(this_01,local_28,pGVar5);
    pGVar5 = (GlassInfo *)
             gta2::Player_sub_401B40((SpawnPoint *)local_18,(GlassInfo *)(local_28 + 1),
                        (struct S127 *)&DAT_005e6878);
    this_00 = (Point2D *)gta2::Player_FUN_00403840(this_02,local_20,pGVar5);
    bVar2 = gta2::Point2D_FUN_004037e0(this_00,pSpriteS1);
    if (CONCAT31(extraout_var,bVar2) == 0) {
      local_18[0] = (byte)DAT_005e687c;
      local_18[1] = DAT_005e687c._1_1_;
      local_18[2] = DAT_005e687c._2_1_;
      local_18[3] = DAT_005e687c._3_1_;
    }
    else {
      local_18[0] = (byte)DAT_005e6878;
      local_18[1] = DAT_005e6878._1_1_;
      local_18[2] = DAT_005e6878._2_1_;
      local_18[3] = DAT_005e6878._3_1_;
    }
    puVar4 = (undefined4 *)gta2::Player_FUN_0040f640((struct Player *)&local_10,local_20);
    local_8 = (struct Ped *)*puVar4;
    local_4 = (struct Ped *)puVar4[1];
  }
  else {
    gta2::bitShiftLeft1(&param_1,NULL);
    puVar4 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)&self->Index->DamageType,
                        (GlassInfo *)local_28,(struct S127 *)&DAT_005e688c);
    FUN_00432860(&local_8,&param_1,puVar4);
  }
  FUN_00486950(local_18,&local_8,&local_10);
  return;
}


// 0x00486b20: S63::sub_486B20
// IDA: S63::sub_486B20
// Ghidra: CollisionBox::FUN_00486b20
void gta2::S63_sub_486B20(struct CollisionBox *self,Car *param_1)
{
  char cVar1;
  bool bVar2;
  char *pcVar3;
  undefined4 *puVar4;
  GlassInfo *pGVar5;
  struct SpriteS1 *pSpriteS1;
  Point2D *this_00;
  undefined3 extraout_var;
  struct Player *this_01;
  struct Player *this_02;
  struct Car **ppCVar6;
  undefined1 local_29;
  int local_28 [2];
  int local_20 [2];
  undefined4 local_18;
  int local_14;
  struct Player *local_10;
  struct Player *local_c;
  struct Ped *local_8;
  struct Ped *local_4;
  
  pcVar3 = (char *)FUN_00482c50(local_20);
  local_10 = *(Player **)pcVar3;
  local_c = *(Player **)(pcVar3 + 4);
  cVar1 = FUN_004bcfa0(DAT_005e6888,&local_18,&local_29);
  if (cVar1 == '\0') {
    FUN_00432860(&local_18,&DAT_005e6888,&DAT_005e688c);
    FUN_004828c0(&local_18,(int *)param_1);
    gta2::Player_sub_40E530((Point2D *)&local_14,&self->Index->DamageType);
    local_18 = DAT_005e6888;
    pGVar5 = (GlassInfo *)
             gta2::Player_sub_401B40((SpawnPoint *)&local_14,(GlassInfo *)&param_1,
                        (struct S127 *)&DAT_005e6884);
    pSpriteS1 = (struct SpriteS1 *)gta2::Player_FUN_00403840(this_01,local_28,pGVar5);
    pGVar5 = (GlassInfo *)
             gta2::Player_sub_401B40((SpawnPoint *)&local_14,(GlassInfo *)(local_28 + 1),
                        (struct S127 *)&DAT_005e6880);
    this_00 = (Point2D *)gta2::Player_FUN_00403840(this_02,local_20,pGVar5);
    bVar2 = gta2::Point2D_FUN_004037e0(this_00,pSpriteS1);
    if (CONCAT31(extraout_var,bVar2) == 0) {
      local_14 = DAT_005e6884;
    }
    else {
      local_14 = DAT_005e6880;
    }
    puVar4 = (undefined4 *)gta2::Player_FUN_0040f640((struct Player *)&local_10,local_20);
    local_8 = (struct Ped *)*puVar4;
    local_4 = (struct Ped *)puVar4[1];
  }
  else {
    gta2::bitShiftLeft1(&param_1,NULL);
    ppCVar6 = &param_1;
    puVar4 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)&self->Index->CameraX,
                        (GlassInfo *)local_28,(struct S127 *)&DAT_005e6888);
    FUN_00432860(&local_8,puVar4,ppCVar6);
  }
  FUN_00486950(&local_18,&local_8,&local_10);
  return;
}


// 0x00486c60: S63::sub_486C60
// IDA: S63::sub_486C60
// Ghidra: CollisionBox::FUN_00486c60
byte gta2::S63_sub_486C60(struct CollisionBox *self,Car *param_1)
{
  struct SpriteS1 *this_00;
  byte bVar1;
  int iVar2;
  undefined4 *puVar3;
  struct Car *this_01;
  struct EventHandler *pEVar4;
  struct Car **ppCVar5;
  undefined4 local_18;
  undefined1 local_14 [4];
  struct Car *local_10;
  struct Ped *local_c;
  undefined1 local_8 [8];
  
  iVar2 = (int)PTR_005e6874 + -1;
  if (iVar2 == 0) {
    gta2::S63_sub_4869E0(self,param_1);
  }
  else {
    iVar2 = (int)PTR_005e6874 + -2;
    if (iVar2 == 0) {
      gta2::S63_sub_486B20(self,param_1);
      return (byte)iVar2;
    }
    iVar2 = (int)PTR_005e6874 + -3;
    if (iVar2 == 0) {
      puVar3 = (undefined4 *)
               FUN_004bd8a0(local_8,DAT_005e6894,param_1,
                            CONCAT22((short)((uint)&local_18 >> 0x10),
                                     *(undefined2 *)&self->Index->NextElement),
                            &param_1,&local_18,local_14);
      this_00 = DAT_005e6894;
      local_10 = (struct Car *)*puVar3;
      local_c = (struct Ped *)puVar3[1];
      this_01 = (struct Car *)gta2::SpriteS1_GetCar(DAT_005e6894);
      if (this_01 != NULL) {
        gta2::Car_CarMakeDriveable4(this_01);
        bVar1 = gta2::CollisionBox_FUN_00482cc0(self,&local_10,local_18);
        return bVar1;
      }
      iVar2 = gta2::SpriteS1_GetGameObject(this_00);
      if (iVar2 != 0) {
        gta2::S63_sub_4867E0(self,iVar2,(GlassInfo *)&local_10);
        bVar1 = gta2::S63_sub_486410(self,DAT_005e6894);
        return bVar1;
      }
      ppCVar5 = &local_10;
      pEVar4 = gta2::SpriteS1_sub_40FEC0(this_00);
      bVar1 = gta2::S63_sub_486580(self,(int)pEVar4,ppCVar5);
      return bVar1;
    }
  }
  return (byte)iVar2;
}


// 0x00486d70: S63::sub_486D70
// IDA: S63::sub_486D70
// Ghidra: ---
char gta2::S63_sub_486D70(struct EventHandler *self, int a2, int a3, char a4, char a5)
{
  int v6; // eax

  if ( gta2::SpriteS1_sub_4BAA90(self->SpriteS1_) )
  {
    *(_DWORD *)self->Car->CarDoor_[0].AnimationFrame = dword_665894;
    LOBYTE(v6) = dword_665894;
    self->Car->CarDoor_[0].doorState = dword_665894;
  }
  else
  {
    v6 = self->pEventHandler[1].field_20;
    switch ( v6 )
    {
      case 0:
      case 1:
        if ( a4 )
          goto LABEL_8;
        if ( a5 )
          gta2::sub_482A80(&dword_5E6874);
        goto LABEL_16;
      case 2:
      case 3:
        LOBYTE(v6) = gta2::S63_sub_486C60(self, &a2);
        break;
      case 4:
        if ( unk_5E6894 )
          gta2::SpriteS1_sub_420660(self->SpriteS1_, unk_5E6894->S3_arr5031[0].PositionZ);
        if ( !a4 || dword_5E6874 == 3 )
        {
          if ( a5 && dword_5E6874 != 3 )
            gta2::sub_482A80(&dword_5E6874);
LABEL_16:
          LOBYTE(v6) = gta2::S63_sub_486410(self, unk_5E6894);
        }
        else
        {
LABEL_8:
          gta2::sub_482A70(&dword_5E6874);
          LOBYTE(v6) = gta2::S63_sub_486410(self, unk_5E6894);
        }
        break;
      default:
        return v6;
    }
  }
  return v6;
}


// 0x00487a30: S63::sub_487A30
// IDA: S63::sub_487A30
// Ghidra: ---
int gta2::S63_sub_487A30(struct EventHandler *self)
{
  struct CarDoor *CarDoor; // edi
  int result; // eax
  struct Car *pCar; // ecx
  struct Car *Car; // eax
  __int16 v6; // cx
  char v7; // al
  struct Ped *v8; // eax
  struct Ped *Ped; // eax
  __int16 a3[2]; // [esp+4h] [ebp-8h] BYREF
  struct Player *arg0; // [esp+8h] [ebp-4h] BYREF

  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)a3);
  gta2::S63_sub_482ED0(self);
  gta2::Car_sub_482D90(self->Car, &arg0, a3);
  if ( self->pEventHandler[2].NextElement )
    gta2::S63_sub_486E90(self, arg0, a3[0]);
  else
    gta2::S63_sub_4874D0(self, (struct Car *)arg0);
  gta2::S63_sub_4825C0(self);
  CarDoor = self->Car->CarDoor_;
  *(_DWORD *)CarDoor->AnimationFrame = *gta2::sub_482730(a3, a3);
  LOBYTE(result) = gta2::S63_sub_486060(self);
  if ( !(_BYTE)result )
  {
    pCar = self->Car;
    if ( pCar->Car )
      gta2::Car_sub_4BEF70(pCar, self->SpriteS1_);
    if ( !gta2::Player_IsCurrentPlayer((struct Player *)&arg0, (struct Player *)&dword_665894)
      || (Car = self->Car, *(_WORD *)&Car->CarDoor_[1].rezerv_2)
      || Car->CarDoor_[2].PedInDoor == (struct Ped *)2
      || gta2::S63_sub_484740(self) )
    {
      result = (int)self->Car;
      v6 = *(_WORD *)(result + 40);
      if ( v6 > 0 )
      {
        *(_WORD *)(result + 40) = v6 - 1;
        if ( !*(_WORD *)&self->Car->CarDoor_[1].field_C )
        {
          if ( gta2::S63_sub_420FF0(self) )
          {
            v7 = gta2::S63_sub_420FF0(self);
            v8 = (struct Ped *)gta2::S68_sub_420F10(gScriptThread, v7);
            if ( v8 )
            {
              Ped = gta2::Character_FindPed(gCharacter, v8);
              if ( Ped )
                sub_435220(Ped, (WeaponType)self->S63_1_);
            }
          }
          gta2::S63_sub_485760(self, (int)self->pEventHandler[1].Car);
        }
      }
    }
    else
    {
      *(_DWORD *)self->Car->CarDoor_[1].AnimationFrame = dword_665894;
      self->Car->CarDoor_[0].doorState = dword_665894;
      gta2::S63_sub_485760(self, (int)self->pEventHandler[1].S65);
      LOBYTE(result) = gta2::S63_sub_421080(self);
      if ( (_BYTE)result )
      {
        LOBYTE(result) = gta2::S63_sub_420FF0(self);
        if ( (_BYTE)result )
        {
          LOBYTE(result) = gta2::S68_sub_4B9940(gScriptThread, BYTE2(self->S202_));
          BYTE2(self->S202_) = 0;
        }
      }
    }
  }
  return result;
}


// 0x00487bc0: S63::sub_487BC0
// IDA: S63::sub_487BC0
// Ghidra: ---
void gta2::S63_sub_487BC0(struct EventHandler *self)
{
  struct SpriteS1 *SpriteS1; // eax
  int PositionX; // ecx
  int PositionY; // edx
  int PositionZ; // eax
  void *v6; // ecx
  struct CarDoor *CarDoor; // edi
  struct EventHandler *pEventHandler; // eax
  struct SpriteS1 *v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  struct Car *Car; // ecx
  struct Car *v14; // eax
  __int16 a3[2]; // [esp+4h] [ebp-14h] BYREF
  struct Player *arg0; // [esp+8h] [ebp-10h] BYREF
  int a2; // [esp+Ch] [ebp-Ch] BYREF
  int v18; // [esp+10h] [ebp-8h] BYREF
  int v19; // [esp+14h] [ebp-4h] BYREF

  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)a3);
  SpriteS1 = self->SpriteS1_;
  PositionX = SpriteS1->S3_arr5031[0].PositionX;
  PositionY = SpriteS1->S3_arr5031[0].PositionY;
  PositionZ = SpriteS1->S3_arr5031[0].PositionZ;
  a2 = PositionX;
  v18 = PositionY;
  v19 = PositionZ;
  gta2::S63_sub_482ED0(self);
  gta2::Car_sub_482D90(self->Car, &arg0, a3);
  if ( self->pEventHandler[2].NextElement )
    gta2::S63_sub_486E90(self, arg0, a3[0]);
  else
    gta2::S63_sub_4874D0(self, (struct Car *)arg0);
  CarDoor = self->Car->CarDoor_;
  *(_DWORD *)CarDoor->AnimationFrame = *gta2::sub_482730(v6, a3);
  pEventHandler = self->pEventHandler;
  if ( BYTE1(pEventHandler[2].S65) != 0xFF
    || pEventHandler[1].pEventHandler == (struct EventHandler *)9
    || (v9 = self->SpriteS1_, LOWORD(v10) = gta2::Car_sub_403820((struct Car *)&v9->S3_arr5031[0].PositionX, &a2), v10)
    || (LOWORD(v11) = gta2::Car_sub_403820((struct Car *)&v9->S3_arr5031[0].PositionY, &v18), v11)
    || (LOWORD(v12) = gta2::Car_sub_403820((struct Car *)&v9->S3_arr5031[0].PositionZ, &v19), v12) )
  {
    if ( !LOBYTE(self->Car->CarDoor_[2].doorState) )
      gta2::S63_sub_485FD0(self);
  }
  if ( !gta2::S63_sub_486060(self) )
  {
    Car = self->Car;
    if ( Car->Car )
    {
      gta2::Car_sub_4BEF70(Car, self->SpriteS1_);
      if ( !self->Car->Car && self->S63_1_ == (struct S63_1 *)127 )
        gta2::S63_sub_4827B0(self);
    }
    if ( gta2::Player_IsCurrentPlayer((struct Player *)&arg0, (struct Player *)&dword_665894) )
    {
      v14 = self->Car;
      if ( !*(_WORD *)&v14->CarDoor_[1].rezerv_2
        && v14->CarDoor_[2].PedInDoor == (struct Ped *)2
        && !gta2::S63_sub_484740(self)
        && !unk_665790 )
      {
        *(_DWORD *)self->Car->CarDoor_[1].AnimationFrame = dword_665894;
        self->Car->CarDoor_[0].doorState = dword_665894;
        if ( self->S63_1_ != (struct S63_1 *)183 && gta2::S63_sub_421080(self) )
        {
          if ( gta2::S63_sub_420FF0(self) )
          {
            gta2::S68_sub_4B9940(gScriptThread, BYTE2(self->S202_));
            BYTE2(self->S202_) = 0;
          }
        }
        gta2::S63_sub_485760(self, (int)self->pEventHandler[1].S65);
      }
    }
  }
}


// 0x00487d70: S63::sub_487D70
// IDA: S63::sub_487D70
// Ghidra: ---
void gta2::S63_sub_487D70(struct EventHandler *self)
{
  struct S65 *S65; // ecx

  unk_665790 = 0;
  while ( 2 )
  {
    switch ( (unsigned int)self->pEventHandler[1].pEventHandler )
    {
      case 0u:
        if ( !gta2::S63_sub_486060(self) )
          goto LABEL_4;
        return;
      case 1u:
        if ( !gta2::S63_sub_486060(self) )
        {
          gta2::S63_sub_4825A0(self);
          if ( self->S63_1_ == (struct S63_1 *)139 || self->S63_1_ == (struct S63_1 *)141 )
          {
            gta2::S56_sub_447480(gCheckpoint1, self->SpriteS1_);
            gta2::S56_sub_447480(gCheckpoint2, self->SpriteS1_);
          }
        }
        return;
      case 2u:
      case 8u:
        if ( !gta2::S63_sub_486060(self) )
        {
          gta2::S63_sub_4825A0(self);
          gta2::S63_sub_485FD0(self);
        }
        return;
      case 3u:
      case 7u:
        gta2::S63_sub_4826A0(self);
        unk_665774 = 1;
        gta2::S63_sub_487A30(self);
        goto LABEL_15;
      case 4u:
      case 9u:
        gta2::S63_sub_4826A0(self);
        unk_665774 = 1;
        gta2::S63_sub_487BC0(self);
LABEL_15:
        if ( !unk_665760 )
          gta2::S63_sub_482630(self);
        return;
      case 5u:
        S65 = self->S65_;
        if ( S65 && gta2::S65_sub_491A70(S65, (struct S65 *)dword_665894, word_6657F8[0]) )
          BYTE1(self->S202_) = 1;
        return;
      case 6u:
      case 0xAu:
      case 0xBu:
        gta2::S63_sub_486060(self);
        goto LABEL_4;
      case 0xCu:
LABEL_4:
        gta2::S63_sub_4825A0(self);
        return;
      default:
        continue;
    }
  }
}


// 0x00487e80: S63::sub_487E80
// IDA: S63::sub_487E80
// Ghidra: ---
char gta2::S63_sub_487E80(struct EventHandler *self)
{
  char v2; // al

  unk_665774 = 0;
  unk_665760 = 0;
  if ( BYTE1(self->S202_) != 1 )
    gta2::S63_sub_487D70(self);
  v2 = BYTE1(self->S202_);
  if ( !v2 || v2 == 2 && gta2::Game_sub_45C420(gGame, self->SpriteS1_, dword_665894) )
    return 0;
  gta2::S63_sub_4826A0(self);
  return 1;
}


// 0x00493090: S63::sub_493090
// IDA: S63::sub_493090
// Ghidra: ---
char gta2::S63_sub_493090(struct EventHandler *self, EventHandler *a2, void *a3)
{
  unsigned __int8 Index; // al
  char result; // al

  Index = gta2::S63_GetIndex(self);
  sub_482770(Index, a2, a3);
  return result;
}


// 0x004973e0: S63::sub_4973E0
// IDA: S63::sub_4973E0
// Ghidra: FUN_004973e0
undefined1 gta2::S63_sub_4973E0(CollisionBox *param_1,char param_2)
{
  byte bVar1;
  
  bVar1 = gta2::S63_sub_421080(param_1);
  if ((bVar1 != 0) && (param_1->EventHandler[0].field_0x1e == param_2)) {
    return 1;
  }
  return 0;
}



