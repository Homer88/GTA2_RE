#include "gta2_shim.h"

// Module: other, Class: GameObject
// Functions: 50
// Source: unified (IDA+Ghidra)

// 0x00491de0: GameObject::sub_491DE0
// IDA: GameObject::sub_491DE0
// Ghidra: FUN_00491de0
void gta2::GameObject_sub_491DE0(void *self)
{
  *(undefined4 *)((int)self + 0xb0) = 0xffffffff;
  gta2::Car_ExtinguishCar((struct Car *)((int)self + 0x88));
  return;
}


// 0x00491e00: GameObject::sub_491E00
// IDA: GameObject::sub_491E00
// Ghidra: ---
void gta2::GameObject_sub_491E00(struct GameObject *self, int x, int y, int z)
{
  int v4; // eax

  v4 = self->field_58;
  LOBYTE(v4) = v4 | 0x20;
  self->teleportY = y;
  self->field_58 = v4;
  self->teleportX = x;
  self->teleportZ = z;
}


// 0x00491e40: GameObject::sub_491E40
// IDA: GameObject::sub_491E40
// Ghidra: ---
bool gta2::GameObject_sub_491E40(struct GameObject *self)
{
  return gta2::SpriteS1_sub_4BAA90(self->SpriteS1_);
}


// 0x00491e60: GameObject::sub_491E60
// IDA: GameObject::sub_491E60
// Ghidra: ---
unsigned __int16 gta2::GameObject_sub_491E60(struct GameObject *self)
{
  unsigned __int16 result; // ax

  self->field_18 = 0;
  self->ProbablyPhysics = 0;
  self->field_20 = 0;
  self->field_2C = unk_66A434.Index;
  self->field_69 = 0;
  self->field_24 = 0;
  self->field_28 = unk_66A434.Index;
  self->field_2A = unk_66A434.Index;
  result = unk_66A434.Index;
  self->field_2C = unk_66A434.Index;
  return result;
}


// 0x00491ea0: GameObject::sub_491EA0
// IDA: GameObject::sub_491EA0
// Ghidra: GameObject::FUN_00491ea0
bool gta2::GameObject_sub_491EA0(struct GameObject *self)
{
  byte bVar1;
  
  bVar1 = gta2::Game_sub_45C420(gGame,*(Sprite **)&self->AIState,_DAT_0066a4d8);
  return bVar1 == 1;
}


// 0x00491ec0: GameObject::sub_491EC0
// IDA: GameObject::sub_491EC0
// Ghidra: GameObject::FUN_00491ec0
void gta2::GameObject_sub_491EC0(struct GameObject *self)
{
  DAT_0066a3c9 = 0;
  gta2::S56_sub_447480(gCheckpoint2,*(SpriteS1 **)&self->AIState);
  return;
}


// 0x00491fa0: GameObject::sub_491FA0
// IDA: GameObject::sub_491FA0
// Ghidra: GameObject::FUN_00491fa0
byte gta2::GameObject_sub_491FA0(struct GameObject *self)
{
  short *psVar1;
  byte in_AL;
  short sVar2;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  sVar2 = (short)&local_10;
  if (*(short *)((int)&self->S7[3].PedInDoor + 2) == 0) {
    in_AL = DAT_0066a3b8;
    switch(DAT_0066a3b8) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
      self->S7[0].doorState = 1;
      self->PhysicsFlags = 0;
      local_10 = 400;
      break;
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
      sVar2 = (short)&local_c;
      self->S7[0].doorState = 3;
      self->PhysicsFlags = 0;
      local_c = 200;
      break;
    case 0xf:
      sVar2 = (short)&local_8;
      self->S7[0].doorState = 4;
      self->PhysicsFlags = 1;
      local_8 = 200;
      break;
    default:
      goto switchD_00491fc9_caseD_10;
    case 0x14:
      self->S7[0].doorState = 7;
      self->PhysicsFlags = 2;
      local_4 = 200;
      sVar2 = (short)&local_4;
    }
    sVar2 = gta2::Random_Random((struct Random *)&gRandom,sVar2);
    in_AL = (byte)sVar2;
    *(short *)((int)&self->S7[3].PedInDoor + 2) = sVar2;
  }
switchD_00491fc9_caseD_10:
  psVar1 = (short *)((int)&self->S7[3].PedInDoor + 2);
  *psVar1 = *psVar1 + -1;
  if ((*(short *)((int)&self->S7[3].PedInDoor + 2) == 0xff) &&
     (self->S7[0].doorState != 0x19)) {
    *(undefined2 *)((int)&self->S7[3].PedInDoor + 2) = 0;
  }
  return in_AL;
}


// 0x00492190: GameObject::sub_492190
// IDA: GameObject::sub_492190
// Ghidra: FUN_00492190
undefined1 gta2::GameObject_sub_492190(void *self,Car *param_1)
{
  uint uVar1;
  struct Car *pCVar2;
  char cVar3;
  byte bVar4;
  bool bVar5;
  undefined1 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  struct Car *pCVar12;
  char *pcVar13;
  undefined4 uVar14;
  char local_d;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar7 = *(int *)((int)self + 0x80);
  local_8 = *(undefined4 *)(iVar7 + 0x14);
  local_c = *(undefined4 *)(iVar7 + 0x18);
  local_4 = *(undefined4 *)(iVar7 + 0x1c);
  iVar7 = DecoderFloat(&local_4);
  iVar7 = iVar7 + -1;
  local_d = '\0';
  if ((*(byte *)((int)self + 0x58) & 1) != 0) {
    iVar7 = DecoderFloat(&local_4);
  }
  pCVar2 = param_1;
  pcVar13 = &local_d;
  uVar14 = 0;
  pCVar12 = param_1;
  iVar8 = DecoderFloat(&local_4);
  iVar9 = DecoderFloat(&local_c);
  iVar10 = DecoderFloat(&local_8);
  cVar3 = FUN_004656d0(iVar10,iVar9,iVar8,pCVar12,pcVar13,uVar14);
  if (cVar3 != '\0') {
    DAT_00593228 = pCVar2;
    return 0;
  }
  iVar7 = iVar7 + local_d;
  if (iVar7 < 0) {
    return 0;
  }
  switch(pCVar2) {
  case (struct Car *)0x1:
    iVar8 = DecoderFloat(&local_c);
    iVar8 = iVar8 + -1;
    iVar9 = DecoderFloat(&local_8);
    break;
  case (struct Car *)0x2:
    iVar8 = DecoderFloat(&local_c);
    iVar8 = iVar8 + 1;
    iVar9 = DecoderFloat(&local_8);
    break;
  case (struct Car *)0x3:
    iVar8 = DecoderFloat(&local_c);
    iVar9 = DecoderFloat(&local_8);
    iVar9 = iVar9 + 1;
    break;
  case (struct Car *)0x4:
    iVar8 = DecoderFloat(&local_c);
    iVar9 = DecoderFloat(&local_8);
    iVar9 = iVar9 + -1;
    break;
  default:
    goto switchD_00492236_caseD_4;
  }
  bVar4 = gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct,iVar9,iVar8,iVar7);
  if (bVar4 == 0) {
switchD_00492236_caseD_4:
    uVar1 = *(uint *)((int)self + 0x58);
    if ((uVar1 & 1) != 0) {
      puVar11 = (undefined4 *)FUN_0042a630(&local_8,&local_4);
      param_1 = (struct Car *)*puVar11;
      bVar5 = gta2::Point2D_FUN_004037e0((Point2D *)&param_1,(struct SpriteS1 *)&DAT_0066a65c);
      if (CONCAT31(extraout_var,bVar5) != 0) {
        *(uint *)((int)self + 0x58) = uVar1 & 0xfffffffe;
        uVar6 = FUN_00492190(self,pCVar2);
        *(uint *)((int)self + 0x58) = *(uint *)((int)self + 0x58) | 1;
        return uVar6;
      }
      bVar5 = gta2::Ped_IsSearchType(*(Ped **)((int)self + 0x7c),
                                 SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
      if (!bVar5) {
        bVar5 = gta2::Car_sub_403800((struct Car *)&param_1,(int *)&DAT_0066a65c);
        if (CONCAT31(extraout_var_00,bVar5) == 0) {
          return 0;
        }
        *(uint *)((int)self + 0x58) = *(uint *)((int)self + 0x58) & 0xfffffffe;
        FUN_004824e0(&param_1,0);
        uVar6 = FUN_00492190(self,pCVar2);
        FUN_00482510((void *)(*(int *)((int)self + 0x80) + 0x1c),
                     (GlassInfo *)&param_1);
        *(uint *)((int)self + 0x58) = *(uint *)((int)self + 0x58) | 1;
        return uVar6;
      }
    }
  }
  else if ((bVar4 == 0) || (4 < bVar4)) {
    return 0;
  }
  return 1;
}


// 0x004923a0: GameObject::FUN_004923a0
// IDA: sub_4923A0
// Ghidra: GameObject::FUN_004923a0
void gta2::GameObject_FUN_004923a0(struct GameObject *self)
{
  int *this_00;
  
  this_00 = &self->S7[3].doorState;
  gta2::CarSystemManager_FUN_0040e490((struct CarSystemManager *)this_00);
  gta2::CarSystemManager_FUN_0041fa70((struct CarSystemManager *)this_00,(short *)&DAT_0066a738);
  self->S7[0].doorState = 8;
  *(undefined2 *)((int)&self->S7[3].PedInDoor + 2) = 10;
  return;
}


// 0x004923d0: GameObject::FUN_004923d0
// IDA: sub_4923D0
// Ghidra: GameObject::FUN_004923d0
void gta2::GameObject_FUN_004923d0(struct GameObject *self)
{
  int *this_00;
  
  this_00 = &self->S7[3].doorState;
  gta2::CarSystemManager_FUN_0040e490((struct CarSystemManager *)this_00);
  gta2::CarSystemManager_FUN_0041fa70((struct CarSystemManager *)this_00,(short *)&DAT_0066a4a4);
  self->S7[0].doorState = 9;
  *(undefined2 *)((int)&self->S7[3].PedInDoor + 2) = 10;
  return;
}


// 0x00492420: GameObject::FUN_00492420
// IDA: sub_492420
// Ghidra: GameObject::FUN_00492420
bool gta2::GameObject_FUN_00492420(struct GameObject *self,undefined4 param_1,SpriteS1 *param_2)
{
  undefined4 uVar1;
  undefined4 uVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  char cVar7;
  int iVar8;
  int iVar9;
  struct SpriteS1 *pSVar10;
  void *pvVar11;
  struct SpriteS1 *pSVar12;
  char cVar13;
  char cVar14;
  bool local_9;
  
  iVar9 = *(int *)&self->AIState;
  uVar1 = *(undefined4 *)(iVar9 + 0x14);
  uVar2 = *(undefined4 *)(iVar9 + 0x18);
  pvVar11 = (void *)(iVar9 + 0x14);
  iVar8 = FUN_00491ee0(pvVar11);
  cVar14 = (char)param_1 - (char)iVar8;
  iVar9 = FUN_00491ee0((void *)(iVar9 + 0x18));
  cVar7 = (char)iVar9;
  cVar13 = (char)param_2 - cVar7;
  if ((char)param_1 == (char)iVar8) {
    if ((char)param_2 != cVar7) {
      if (cVar13 == -1) {
        cVar7 = FUN_00492190(self,(struct Car *)0x1);
        if (cVar7 == '\0') {
          DAT_00593228 = 1;
          return false;
        }
      }
      else {
        cVar7 = FUN_00492190(self,(struct Car *)0x2);
        if (cVar7 == '\0') {
          DAT_00593228 = 2;
          return false;
        }
      }
    }
  }
  else {
    if ((char)param_2 != cVar7) {
      if (cVar14 == -1) {
        if (cVar13 == -1) {
          local_9 = true;
          FUN_00491f00(pvVar11);
          pSVar10 = param_2;
          bVar3 = gta2::GameObject_FUN_00492420(self,param_1,param_2);
          if (!bVar3) {
            local_9 = bVar3;
          }
          *(undefined4 *)(*(int *)&self->AIState + 0x14) = uVar1;
          FUN_00491f00((void *)(*(int *)&self->AIState + 0x18));
          bVar3 = gta2::GameObject_FUN_00492420(self,param_1,pSVar10);
          if (!bVar3) {
            local_9 = bVar3;
          }
          *(undefined4 *)(*(int *)&self->AIState + 0x14) = uVar1;
          *(undefined4 *)(*(int *)&self->AIState + 0x18) = uVar2;
          pSVar10 = (struct SpriteS1 *)DecoderFloat(&DAT_0066a74c);
          pvVar11 = gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a480,(GlassInfo *)&param_2
                               ,(struct S127 *)&DAT_0066a46c);
          iVar9 = DecoderFloat(pvVar11);
          bVar3 = gta2::GameObject_FUN_00492420(self,iVar9,pSVar10);
          if (!bVar3) {
            local_9 = bVar3;
          }
          pvVar11 = gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a74c,(GlassInfo *)&param_2
                               ,(struct S127 *)&DAT_0066a46c);
          pSVar10 = (struct SpriteS1 *)DecoderFloat(pvVar11);
          iVar9 = DecoderFloat(&DAT_0066a480);
          bVar3 = gta2::GameObject_FUN_00492420(self,iVar9,pSVar10);
          if (!bVar3) {
            local_9 = bVar3;
          }
          return local_9;
        }
        FUN_00491f00(pvVar11);
        pSVar10 = param_2;
        bVar4 = gta2::GameObject_FUN_00492420(self,param_1,param_2);
        *(undefined4 *)(*(int *)&self->AIState + 0x14) = uVar1;
        FUN_00491ef0((void *)(*(int *)&self->AIState + 0x18));
        bVar5 = gta2::GameObject_FUN_00492420(self,param_1,pSVar10);
        *(undefined4 *)(*(int *)&self->AIState + 0x14) = uVar1;
        *(undefined4 *)(*(int *)&self->AIState + 0x18) = uVar2;
        iVar9 = *(int *)&self->AIState;
        pSVar10 = (struct SpriteS1 *)DecoderFloat((void *)(iVar9 + 0x18));
        pvVar11 = gta2::Player_sub_401B40((SpawnPoint *)(iVar9 + 0x14),(GlassInfo *)&param_2,
                             (struct S127 *)&DAT_0066a46c);
        iVar9 = DecoderFloat(pvVar11);
        bVar3 = gta2::GameObject_FUN_00492420(self,iVar9,pSVar10);
        bVar3 = bVar3 && (bVar5 && bVar4);
      }
      else {
        if (cVar13 == -1) {
          FUN_00491ef0(pvVar11);
          pSVar10 = param_2;
          bVar3 = gta2::GameObject_FUN_00492420(self,param_1,param_2);
          if (!bVar3) {
            DAT_00593228 = 3;
          }
          *(undefined4 *)(*(int *)&self->AIState + 0x14) = uVar1;
          FUN_00491f00((void *)(*(int *)&self->AIState + 0x18));
          bVar4 = gta2::GameObject_FUN_00492420(self,param_1,pSVar10);
          if (!bVar4) {
            DAT_00593228 = 1;
          }
          *(undefined4 *)(*(int *)&self->AIState + 0x14) = uVar1;
          *(undefined4 *)(*(int *)&self->AIState + 0x18) = uVar2;
          iVar9 = *(int *)&self->AIState;
          pSVar10 = (struct SpriteS1 *)DecoderFloat((void *)(iVar9 + 0x18));
          pSVar12 = gta2::S202_sub_401B20((Point2D *)(iVar9 + 0x14),(struct SpriteS1 *)&param_2,
                               (struct S127 *)&DAT_0066a46c);
          iVar9 = DecoderFloat(pSVar12);
          bVar5 = gta2::GameObject_FUN_00492420(self,iVar9,pSVar10);
          if (!bVar5) {
            DAT_00593228 = 1;
          }
          iVar9 = *(int *)&self->AIState;
          pvVar11 = gta2::Player_sub_401B40((SpawnPoint *)(iVar9 + 0x18),
                               (GlassInfo *)&param_2,(struct S127 *)&DAT_0066a46c);
          pSVar10 = (struct SpriteS1 *)DecoderFloat(pvVar11);
          iVar9 = DecoderFloat((void *)(iVar9 + 0x14));
          bVar6 = gta2::GameObject_FUN_00492420(self,iVar9,pSVar10);
          if (!bVar6) {
            DAT_00593228 = 3;
          }
          return bVar6 && (bVar5 && (bVar4 && bVar3));
        }
        FUN_00491ef0(pvVar11);
        pSVar10 = param_2;
        bVar3 = gta2::GameObject_FUN_00492420(self,param_1,param_2);
        *(undefined4 *)(*(int *)&self->AIState + 0x14) = uVar1;
        FUN_00491ef0((void *)(*(int *)&self->AIState + 0x18));
        bVar4 = gta2::GameObject_FUN_00492420(self,param_1,pSVar10);
        if (!bVar4) {
          bVar3 = false;
        }
        *(undefined4 *)(*(int *)&self->AIState + 0x14) = uVar1;
        *(undefined4 *)(*(int *)&self->AIState + 0x18) = uVar2;
        iVar9 = *(int *)&self->AIState;
        pSVar10 = (struct SpriteS1 *)DecoderFloat((void *)(iVar9 + 0x18));
        pSVar12 = gta2::S202_sub_401B20((Point2D *)(iVar9 + 0x14),(struct SpriteS1 *)&param_2,
                             (struct S127 *)&DAT_0066a46c);
        iVar9 = DecoderFloat(pSVar12);
        bVar4 = gta2::GameObject_FUN_00492420(self,iVar9,pSVar10);
        if (!bVar4) {
          bVar3 = false;
        }
      }
      iVar9 = *(int *)&self->AIState;
      pSVar10 = gta2::S202_sub_401B20((Point2D *)(iVar9 + 0x18),(struct SpriteS1 *)&param_2,
                           (struct S127 *)&DAT_0066a46c);
      pSVar10 = (struct SpriteS1 *)DecoderFloat(pSVar10);
      iVar9 = DecoderFloat((void *)(iVar9 + 0x14));
      bVar4 = gta2::GameObject_FUN_00492420(self,iVar9,pSVar10);
      if (!bVar4) {
        bVar3 = false;
      }
      return bVar3;
    }
    if (cVar14 == -1) {
      cVar7 = FUN_00492190(self,(struct Car *)0x4);
      if (cVar7 == '\0') {
        DAT_00593228 = 4;
        return false;
      }
    }
    else {
      cVar7 = FUN_00492190(self,(struct Car *)0x3);
      if (cVar7 == '\0') {
        DAT_00593228 = 3;
        return false;
      }
    }
  }
  return true;
}


// 0x004928a0: GameObject::sub_4928A0
// IDA: GameObject::sub_4928A0
// Ghidra: FUN_004928a0
void gta2::GameObject_sub_4928A0(void *self)
{
  gta2::CarSystemManager_FUN_0041fa70((struct CarSystemManager *)((int)self + 0x40),(short *)&stack0x00000004);
  return;
}


// 0x004930c0: GameObject::sub_4930C0
// IDA: GameObject::sub_4930C0
// Ghidra: Car::FUN_004930c0
undefined4 gta2::GameObject_sub_4930C0(struct Car *self,int param_1)
{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (((struct Ped *)self->PhysicsBitmask)->isPlayer != NULL) {
    uVar2 = *(undefined4 *)(param_1 + 0x14);
    uVar1 = gta2::Ped_sub_420B60((struct Ped *)self->PhysicsBitmask);
    uVar2 = FUN_0047f3b0(uVar1,uVar2);
    return uVar2;
  }
  return 0;
}


// 0x004930f0: GameObject::sub_4930F0
// IDA: GameObject::sub_4930F0
// Ghidra: ---
char gta2::GameObject_sub_4930F0(struct GameObject *self, EventHandler *pS63)
{
  struct EventHandler *pS63_1; // edi
  char result; // al
  int v5; // eax
  struct Ped *v6; // eax
  struct Car **v7; // eax
  int v8; // ecx
  unsigned __int8 Index; // [esp-4h] [ebp-1Ch]
  char v10; // [esp+Bh] [ebp-Dh] BYREF
  int v11; // [esp+Ch] [ebp-Ch] BYREF
  int v12; // [esp+10h] [ebp-8h] BYREF
  int v13; // [esp+14h] [ebp-4h] BYREF

  pS63_1 = pS63;
  if ( gta2::S63_sub_421060(pS63) )
    return sub_43E550(self->Ped_, pS63_1);
  switch ( (unsigned int)pS63_1->S63_1_ )
  {
    case 0x8Bu:
      gta2::S63_sub_493090(pS63_1, (struct EventHandler *)&pS63, &v10);
      v11 = (char)pS63;
      v7 = (Car **)gta2::sub_401BD0(&unk_66A438, (struct SpriteS1 *)&v12, &v11);
      v8 = v10;
      self->Car1 = *v7;
      v11 = v8;
      self->Car2 = (struct Car *)gta2::sub_401BD0(&unk_66A438, (struct SpriteS1 *)&v13, &v11)->FirstElement;
      goto LABEL_12;
    case 0x8Du:
      gta2::Ped_sub_4411B0(self->Ped_);
      return 0;
    case 0xA1u:
      gta2::MissionObjective_sub_4C4FE0(gMissionObjective, HIBYTE(pS63_1->S202_), self->SpriteS1_);
      return 0;
    case 0xA4u:
    case 0xB1u:
    case 0xB3u:
    case 0xB5u:
      return gta2::GameObject_sub_4930C0(self, pS63_1);
    case 0xA7u:
      Index = gta2::S63_GetIndex(pS63_1);
      v6 = gta2::GameObject_sub_433A20(self);
      gta2::S76_sub_44D1B0(gDoor->S76, v6, Index);
      return 0;
    case 0x101u:
    case 0x102u:
      v5 = self->field_8;
      if ( v5 == 9 || v5 == 8 )
        goto LABEL_12;
      gta2::Ped_sub_43E480(self->Ped_, pS63_1);
      result = 0;
      break;
    case 0x10Au:
      return sub_43E550(self->Ped_, pS63_1);
    default:
LABEL_12:
      result = 0;
      break;
  }
  return result;
}


// 0x00493390: GameObject::sub_493390
// IDA: GameObject::sub_493390
// Ghidra: FUN_00493390
void gta2::GameObject_sub_493390(int param_1,undefined4 param_2,undefined4 param_3, undefined4 param_4,char param_5)
{
  undefined2 *puVar1;
  byte bVar2;
  bool bVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  struct Ped *self;
  char cVar7;
  
  cVar7 = param_5;
  if ((*(Ped **)(param_1 + 0x7c))->TargetCarDoor != 0) {
    cVar7 = '\0';
  }
  iVar4 = gta2::Ped_GetPedState(*(Ped **)(param_1 + 0x7c));
  if (iVar4 == 9) {
    return;
  }
  *(undefined1 *)(param_1 + 0x16) = 1;
  puVar5 = (undefined4 *)gta2::JustCopyByPtrAtoC(&DAT_0066a6c0,&param_5);
  puVar1 = *(undefined2 **)(param_1 + 0x80);
  uVar6 = *(undefined4 *)(puVar1 + 10);
  gta2::sub_4854C0(gObject,0x6e,uVar6,*(undefined4 *)(puVar1 + 0xc),
             *(undefined4 *)(puVar1 + 0xe),param_2,
             CONCAT22((short)((uint)*puVar5 >> 0x10),*puVar1),param_3,*puVar5,
             param_4);
  *(undefined4 *)(*(int *)(param_1 + 0x7c) + 0x184) = uVar6;
  if (*(char *)(*(int *)(param_1 + 0x7c) + 0x267) == '\0') {
    bVar2 = gta2::S68_sub_4B98D0(gScriptThread,
                       *(undefined4 *)(*(int *)(param_1 + 0x7c) + 0x200));
    *(byte *)(*(int *)(param_1 + 0x7c) + 0x267) = bVar2;
  }
  gta2::S63_sub_482790(*(EventHandler **)(*(int *)(param_1 + 0x7c) + 0x184),
             *(undefined1 *)(*(int *)(param_1 + 0x7c) + 0x267));
  gta2::Ped_UpdatePedState(*(Ped **)(param_1 + 0x7c),PEDSTATE_FALL);
  if (cVar7 == '\0') {
    *(undefined4 *)
     (*(int *)(*(int *)(*(int *)(param_1 + 0x7c) + 0x184) + 0x10) + 0x10) =
         _DAT_0066a4d8;
    gta2::Ped_sub_4332B0(*(Ped **)(param_1 + 0x7c),0x18);
    *(undefined4 *)(param_1 + 0xc) = 0x18;
    return;
  }
  if (cVar7 == '\x01') {
    *(undefined4 *)
     (*(int *)(*(int *)(*(int *)(param_1 + 0x7c) + 0x184) + 0x10) + 0x10) =
         param_4;
    self = *(Ped **)(param_1 + 0x7c);
    if (self->TargetCarDoor != 0) goto LAB_004934d2;
    bVar3 = gta2::Ped_IsSearchType(self,SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
    self = *(Ped **)(param_1 + 0x7c);
    if (bVar3) {
      iVar4 = 0x19;
      goto LAB_00493485;
    }
  }
  else {
    if (cVar7 != '\x02') {
      return;
    }
    *(undefined4 *)
     (*(int *)(*(int *)(*(int *)(param_1 + 0x7c) + 0x184) + 0x10) + 0x10) =
         param_4;
    self = *(Ped **)(param_1 + 0x7c);
    if (self->TargetCarDoor != 0) {
LAB_004934d2:
      iVar4 = 0x18;
      goto LAB_00493485;
    }
  }
  iVar4 = 0x1a;
LAB_00493485:
  gta2::Ped_sub_4332B0(self,iVar4);
  *(undefined4 *)(param_1 + 0xc) = 0x18;
  iVar4 = *(int *)(param_1 + 0x80);
  gta2::Particles_sub_48C9C0(gParticles,*(undefined4 *)(iVar4 + 0x14),
             *(undefined4 *)(iVar4 + 0x18),*(undefined4 *)(iVar4 + 0x1c),param_2
            );
  return;
}


// 0x004935f0: GameObject::GameObject_des
// IDA: GameObject::GameObject_des
// Ghidra: ---
int gta2::GameObject_GameObject_des(struct GameObject *self)
{
  int result; // eax

  result = 0;
  self->field_18 = 0;
  self->ProbablyPhysics = 0;
  self->GameObject_ = 0;
  self->Ped_ = 0;
  self->SpriteS1_ = 0;
  self->GetVehicle = 0;
  return result;
}


// 0x00493640: GameObject::sub_493640
// IDA: GameObject::sub_493640
// Ghidra: FUN_00493640
void gta2::GameObject_sub_493640(void *self)
{
  if (*(SpriteS1 **)((int)self + 0x80) != NULL) {
    gta2::S56_sub_447C40(gCheckpoint,*(SpriteS1 **)((int)self + 0x80));
    gta2::SpriteS1_SpriteS1_Des(gSpriteS1,*(SpriteS1 **)((int)self + 0x80));
    *(undefined4 *)((int)self + 0x80) = 0;
  }
  gta2::Car_sub_4BF000((struct Car *)((int)self + 0x88));
  *(undefined4 *)((int)self + 0xb0) = 0xffffffff;
  return;
}


// 0x00493710: GameObject::sub_493710
// IDA: GameObject::sub_493710
// Ghidra: GameObject::FUN_00493710
byte gta2::GameObject_sub_493710(struct GameObject *self)
{
  int iVar1;
  undefined4 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined4 *in_EAX;
  struct GameObject *local_4;
  
  if (self->ModelId != 8) {
    in_EAX = (undefined4 *)0x5;
    if ((self->S7[0].doorState == 0xf) && (self->PhysicsFlags == 5)) {
      if (4 < *(byte *)&self->CollisionData) {
        *(undefined1 *)&self->CollisionData = 5;
        self->field_0x71 = 2;
        self->BehaviorFlags = 0;
        return 5;
      }
    }
    else {
      self->S7[0].doorState = 0xf;
      iVar1 = *(int *)&self->AIState;
      self->PhysicsFlags = 5;
      *(undefined1 *)&self->CollisionData = 0;
      uVar3 = gS51_1_1;
      uVar4 = uRam0066a506;
      uVar5 = uRam0066a507;
      self->S7[2].ID = gS51_1;
      self->S7[2].field4_0xd = uVar3;
      self->S7[2].field5_0xe = uVar4;
      self->S7[2].field6_0xf = uVar5;
      local_4 = self;
      in_EAX = (undefined4 *)DecoderFloat((void *)(iVar1 + 0x1c));
      gta2::FUN_0040ce30(&local_4,(byte)in_EAX);
      uVar2 = *in_EAX;
      self->AmmoCount = (char)uVar2;
      self->WeaponState = (char)((uint)uVar2 >> 8);
      self->FireMode = (char)((uint)uVar2 >> 0x10);
      self->ReloadTimer = (char)((uint)uVar2 >> 0x18);
    }
  }
  return (byte)in_EAX;
}


// 0x00493850: GameObject::sub_493850
// IDA: GameObject::sub_493850
// Ghidra: ---
void gta2::GameObject_sub_493850(struct GameObject *self)
{
  struct SpriteS1 *pSpriteS1; // eax

  pSpriteS1 = gta2::SpriteS1_sub_421000(gSpriteS1);
  self->SpriteS1_ = pSpriteS1;
  gta2::SpriteS1_sub_4206F0(pSpriteS1, 3);
  gta2::SpriteS1_sub_4BCB90(self->SpriteS1_, *(SpriteS1 **)&unk_66A780.field0, *(SpriteS3 **)&unk_66A780.field0, unk_66A768);
  gta2::SpriteS1_SetGameObject(self->SpriteS1_, self);
  gta2::SpriteS1_sub_4B9CA0(self->SpriteS1_);
}


// 0x004938a0: GameObject::sub_4938A0
// IDA: GameObject::sub_4938A0
// Ghidra: ---
int gta2::GameObject_sub_4938A0(struct GameObject *self)
{
  struct SpriteS1 *SpriteS1; // edi
  struct S900 *v3; // ecx
  struct Ped *Ped; // edx
  int result; // eax
  char v6[2]; // [esp+Ah] [ebp-2h] BYREF

  gta2::Ped_UpdatePedState(self->Ped_, 8);
  gta2::Ped_sub_4332B0(self->Ped_, 20);
  SpriteS1 = self->SpriteS1_;
  self->field_16 = 1;
  LOWORD(v3) = *(_WORD *)gta2::sub_40E5A0((struct CarSystemManager *)SpriteS1, (struct CarSystemManager *)v6, &unk_66A5F4);
  gta2::Particles_sub_48D1F0(
    gParticles,
    SpriteS1->S3_arr5031[0].PositionX,
    SpriteS1->S3_arr5031[0].PositionY,
    SpriteS1->S3_arr5031[0].PositionZ,
    v3);
  gta2::Ped_sub_433DD0(self->Ped_, 28);
  Ped = self->Ped_;
  result = Ped->PedId;
  if ( result )
  {
    result = (int)gta2::Character_FindPed(gCharacter, (struct Ped *)Ped->PedId);
    if ( result )
    {
      result = (int)self->Ped_;
      *(_DWORD *)(result + 656) = 5;
      self->Ped_->ID = 50;
    }
  }
  return result;
}


// 0x00494180: GameObject::sub_494180
// IDA: GameObject::sub_494180
// Ghidra: ---
__int16 gta2::GameObject_sub_494180(struct GameObject *self)
{
  struct SpriteS1 *SpriteS1; // edi
  char v3; // al
  unsigned __int8 v4; // al
  int *v5; // eax
  int v6; // eax
  int z; // [esp+8h] [ebp-Ch] BYREF
  struct SpriteS1 *FirstElement; // [esp+Ch] [ebp-8h] BYREF
  char v10[4]; // [esp+10h] [ebp-4h] BYREF

  z = *(_DWORD *)&unk_66A4D8.Ammo;
  SpriteS1 = self->SpriteS1_;
  z = SpriteS1->S3_arr5031[0].PositionZ;
  if ( unk_66A3C4 == 1 )
    gta2::sub_482510(&z, (struct SpriteS1 *)&FirstElement, 0);
  v3 = gta2::MapRelatedStruct_sub_466B70(
         gMapRelatedStruct,
         (int *)SpriteS1->S3_arr5031[0].PositionX,
         (struct S202 *)SpriteS1->S3_arr5031[0].PositionY);
  if ( v3 )
  {
    self->field_45 = v3;
    v6 = self->field_58;
    LOBYTE(v6) = v6 | 1;
    self->field_58 = v6;
    return gta2::SpriteS1_sub_420600(
             self->SpriteS1_,
             self->SpriteS1_->S3_arr5031[0].PositionX,
             self->SpriteS1_->S3_arr5031[0].PositionY,
             z);
  }
  if ( !self->field_45 )
  {
    self->field_58 &= ~1u;
    v4 = gta2::Weapon_sub_41C1E0((struct Weapon *)&z);
    gta2::S202_sub_40CE30((struct S202 *)v10, v4);
    z = *v5;
    goto LABEL_8;
  }
  FirstElement = sub_42A630((struct SpriteS1 *)&FirstElement, (struct S202 *)&z)->FirstElement;
  z = (int)gta2::sub_462EA0((struct SpriteS1 *)v10, &z)->FirstElement;
  if ( !gta2::Car_sub_403800((struct Car *)&FirstElement, (int)&unk_66A748) )
  {
LABEL_8:
    self->field_45 = 0;
    return gta2::SpriteS1_sub_420600(
             self->SpriteS1_,
             self->SpriteS1_->S3_arr5031[0].PositionX,
             self->SpriteS1_->S3_arr5031[0].PositionY,
             z);
  }
  gta2::sub_4824E0(&z, (struct SpriteS1 *)v10, 0);
  self->field_45 = 0;
  return gta2::SpriteS1_sub_420600(
           self->SpriteS1_,
           self->SpriteS1_->S3_arr5031[0].PositionX,
           self->SpriteS1_->S3_arr5031[0].PositionY,
           z);
}


// 0x00494280: if
// IDA: if
// Ghidra: GameObject::FUN_00494280
void gta2::if(struct GameObject *self,int param_1)
{
  int iVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  byte bVar5;
  bool bVar6;
  int iVar7;
  undefined3 extraout_var;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int *piVar11;
  void *pvVar12;
  struct CarSystemManager *pCVar13;
  undefined2 *puVar14;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  struct Player *pPlayer;
  struct Player *this_00;
  struct Player *this_01;
  struct Player *this_02;
  struct Player *this_03;
  short *unaff_ESI;
  void *unaff_EDI;
  short *psVar15;
  short *psVar16;
  undefined2 local_4e [4];
  undefined2 local_46;
  undefined2 local_44;
  undefined2 local_42 [3];
  GameState local_3c;
  undefined1 local_38 [8];
  GlassInfo local_30;
  struct Ped *pPed1;
  struct Ped *pPed2;
  
  pPed1 = (struct Ped *)self->ScriptRef;
  _local_3c = gta2::Ped_sub_420B70(pPed1);
  iVar8 = param_1;
  pPed2 = *(Ped **)(param_1 + 0x7c);
  param_1 = gta2::Ped_sub_420B70(pPed2);
  iVar7 = FUN_0048a4c0((void *)iVar8);
  if ((((iVar7 != 9) && (iVar7 = FUN_0048a4c0((void *)iVar8), iVar7 != 8)) &&
      (-1 < *(char *)&self->MaxHealth)) && (self->S7[0].doorState != 0xf)) {
    bVar5 = gta2::Ped_IsPlayerControlled(pPed1);
    if ((bVar5 == 0) || (bVar6 = gta2::Ped_GetOCcupationIsElvis(pPed2), !bVar6)) {
      bVar5 = gta2::Ped_IsPlayerControlled(pPed1);
      if (((bVar5 != 0) || ((pPed1->ID & 3) == 0)) &&
         (bVar5 = gta2::Ped_IsPlayerControlled(pPed2), bVar5 == 0)) {
        gta2::sub_493000(pPed1,iVar8);
      }
    }
    else {
      gta2::Ped_FUN_00493040(pPed2,pPed1->GameObject_);
    }
    switch(_local_3c) {
    case 2:
      switch(param_1) {
      case 2:
switchD_00494355_caseD_2:
        gta2::SpriteS1_sub_420600(*(Sprite **)&self->AIState,_DAT_0066a480,
                            _DAT_0066a74c,_DAT_0066a754);
        return;
      case 3:
      case 4:
      case 6:
        self->S7[0].doorState = 1;
        bVar6 = gta2::Car_IsTrainOrTrainCarriage((struct Car *)&self->S7[2].ID,(struct Car *)&DAT_0066a634);
        if ((CONCAT31(extraout_var,bVar6) != 0) &&
           ((iVar7 = *(int *)(self->ScriptRef + 0x164), iVar7 == 0 ||
            (*(int *)(*(int *)(iVar8 + 0x7c) + 0x164) != iVar7)))) {
          *(undefined1 *)(iVar8 + 0x6a) = 4;
          iVar7 = *(int *)(iVar8 + 0x80);
          iVar1 = *(int *)&self->AIState;
          pPed1 = (struct Ped *)&stack0xffffffb0;
          psVar15 = (short *)&DAT_0066a5f4;
          piVar11 = (int *)gta2::Player_sub_401B40((SpawnPoint *)(iVar1 + 0x14),&local_30,
                                      (struct S127 *)(iVar7 + 0x14));
          pvVar12 = gta2::Player_sub_401B40((SpawnPoint *)(iVar1 + 0x18),
                               (GlassInfo *)&local_30.pPed,
                               (struct S127 *)(iVar7 + 0x18));
          pCVar13 = (struct CarSystemManager *)
                    gta2::Player_FUN_0040e8d0(pPlayer,local_4e,pvVar12,piVar11);
          puVar14 = (undefined2 *)
                    gta2::sub_40E5A0(pCVar13,pPed1,psVar15,unaff_EDI,unaff_ESI);
          *(undefined2 *)(iVar8 + 0x74) = *puVar14;
          return;
        }
        break;
      case 5:
        iVar7 = *(int *)(self->ScriptRef + 0x164);
        if ((iVar7 == 0) || (*(int *)(*(int *)(iVar8 + 0x7c) + 0x164) != iVar7))
        {
          iVar7 = gta2::Ped_GetCurrentOccupation(*(Ped **)(iVar8 + 0x7c));
          if (iVar7 != 0x2b) {
            *(undefined1 *)(iVar8 + 0x6a) = 4;
            iVar7 = *(int *)(iVar8 + 0x80);
            iVar1 = *(int *)&self->AIState;
            pPed1 = (struct Ped *)&param_1;
            psVar15 = (short *)&DAT_0066a5f4;
            piVar11 = (int *)gta2::Player_sub_401B40((SpawnPoint *)(iVar1 + 0x14),
                                        (GlassInfo *)local_38,
                                        (struct S127 *)(iVar7 + 0x14));
            pvVar12 = gta2::Player_sub_401B40((SpawnPoint *)(iVar1 + 0x18),
                                 (GlassInfo *)(local_38 + 4),
                                 (struct S127 *)(iVar7 + 0x18));
            pCVar13 = (struct CarSystemManager *)
                      gta2::Player_FUN_0040e8d0((struct Player *)&stack0xffffffae,
                                 (undefined2 *)&stack0xffffffae,pvVar12,piVar11)
            ;
            puVar14 = (undefined2 *)
                      gta2::sub_40E5A0(pCVar13,pPed1,psVar15,unaff_EDI,unaff_ESI);
            *(undefined2 *)(iVar8 + 0x74) = *puVar14;
            return;
          }
          goto switchD_00494355_caseD_2;
        }
      }
      break;
    case 3:
      pPed1 = (struct Ped *)self->ScriptRef;
      iVar7 = gta2::Ped_GetCurrentAction(pPed1);
      if ((((iVar7 == 0x30) ||
           (iVar7 = gta2::Ped_GetCurrentAction(pPed1), iVar7 == 0x25)) ||
          (iVar7 = gta2::Ped_GetCurrentAction(pPed1), iVar7 == 0x26)) ||
         (iVar7 = gta2::Ped_GetCurrentAction(pPed1), iVar7 == 0xc)) {
        uVar2 = DAT_0066a428_1;
        uVar3 = uRam0066a42a;
        uVar4 = uRam0066a42b;
        self->S7[2].ID = DAT_0066a428;
        self->S7[2].field4_0xd = uVar2;
        self->S7[2].field5_0xe = uVar3;
        self->S7[2].field6_0xf = uVar4;
      }
      else {
        switch(param_1) {
        case 2:
          if ((*(short *)(*(int *)(iVar8 + 0x7c) + 0x20a) < 1) ||
             (bVar5 = gta2::Ped_GetOccupationStatus(pPed1), bVar5 == 0)) {
            bVar6 = gta2::Car_IsTrainOrTrainCarriage((struct Car *)(iVar8 + 0x38),(struct Car *)&DAT_0066a634);
            if (CONCAT31(extraout_var_00,bVar6) == 0) {
              iVar8 = *(int *)(iVar8 + 0x80);
              iVar7 = *(int *)&self->AIState;
              piVar11 = (int *)gta2::Player_sub_401B40((SpawnPoint *)(iVar7 + 0x14),
                                          (GlassInfo *)&local_30.field12_0x18,
                                          (struct S127 *)(iVar8 + 0x14));
              pvVar12 = gta2::Player_sub_401B40((SpawnPoint *)(iVar7 + 0x18),
                                   (GlassInfo *)&local_30.count,
                                   (struct S127 *)(iVar8 + 0x18));
              puVar14 = gta2::Player_FUN_0040e8d0(this_01,&local_44,pvVar12,piVar11);
              *(undefined2 *)&self->S7[3].doorState = *puVar14;
              return;
            }
            goto switchD_004946dc_caseD_4;
          }
          break;
        case 3:
          if (self->S7[1].doorState == 0) {
            *(undefined1 *)(iVar8 + 0x6a) = 4;
            iVar7 = *(int *)(iVar8 + 0x80);
            iVar1 = *(int *)&self->AIState;
            pPed1 = (struct Ped *)(local_42 + 1);
            psVar16 = (short *)&DAT_0066a70c;
            pPed2 = (struct Ped *)(local_42 + 2);
            psVar15 = (short *)&DAT_0066a5f4;
            piVar11 = (int *)gta2::Player_sub_401B40((SpawnPoint *)(iVar1 + 0x14),
                                        (GlassInfo *)&local_30.field19_0x28,
                                        (struct S127 *)(iVar7 + 0x14));
            pvVar12 = gta2::Player_sub_401B40((SpawnPoint *)(iVar1 + 0x18),
                                 (GlassInfo *)&local_30.field20_0x2c,
                                 (struct S127 *)(iVar7 + 0x18));
            pCVar13 = (struct CarSystemManager *)
                      gta2::Player_FUN_0040e8d0(this_03,(undefined2 *)&local_3c,pvVar12,piVar11
                                );
            pCVar13 = (struct CarSystemManager *)
                      gta2::sub_40E5A0(pCVar13,pPed2,psVar15,pPed1,psVar16);
            puVar14 = (undefined2 *)
                      gta2::sub_40E5A0(pCVar13,pPed1,psVar16,unaff_EDI,unaff_ESI);
            *(undefined2 *)(iVar8 + 0x74) = *puVar14;
            return;
          }
          break;
        case 5:
          bVar6 = gta2::Car_IsTrainOrTrainCarriage((struct Car *)(iVar8 + 0x38),(struct Car *)&DAT_0066a634);
          if (CONCAT31(extraout_var_01,bVar6) == 0) {
            iVar8 = *(int *)(iVar8 + 0x80);
            iVar7 = *(int *)&self->AIState;
            piVar11 = (int *)gta2::Player_sub_401B40((SpawnPoint *)(iVar7 + 0x14),
                                        (GlassInfo *)&local_30.field17_0x20,
                                        (struct S127 *)(iVar8 + 0x14));
            pvVar12 = gta2::Player_sub_401B40((SpawnPoint *)(iVar7 + 0x18),
                                 (GlassInfo *)&local_30.field18_0x24,
                                 (struct S127 *)(iVar8 + 0x18));
            puVar14 = gta2::Player_FUN_0040e8d0(this_02,local_42,pvVar12,piVar11);
            *(undefined2 *)&self->S7[3].doorState = *puVar14;
            return;
          }
        case 4:
        case 6:
switchD_004946dc_caseD_4:
          uVar2 = DAT_0066a550_1;
          uVar3 = uRam0066a552;
          uVar4 = uRam0066a553;
          self->S7[2].ID = DAT_0066a550;
          self->S7[2].field4_0xd = uVar2;
          self->S7[2].field5_0xe = uVar3;
          self->S7[2].field6_0xf = uVar4;
          return;
        }
      }
      break;
    case 4:
    case 6:
      switch(param_1) {
      case 2:
        if (0 < *(short *)(*(int *)(iVar8 + 0x7c) + 0x20a)) {
          gta2::Ped_GetOccupationStatus((struct Ped *)self->ScriptRef);
          return;
        }
        break;
      case 3:
        *(undefined1 *)(iVar8 + 0x6a) = 4;
        iVar7 = *(int *)(iVar8 + 0x80);
        iVar1 = *(int *)&self->AIState;
        pPed1 = (struct Ped *)(local_4e + 3);
        psVar15 = (short *)&DAT_0066a5f4;
        piVar11 = (int *)gta2::Player_sub_401B40((SpawnPoint *)(iVar1 + 0x14),
                                    (GlassInfo *)&local_30.field_0x10,
                                    (struct S127 *)(iVar7 + 0x14));
        pvVar12 = gta2::Player_sub_401B40((SpawnPoint *)(iVar1 + 0x18),
                             (GlassInfo *)&local_30.field11_0x14,
                             (struct S127 *)(iVar7 + 0x18));
        pCVar13 = (struct CarSystemManager *)
                  gta2::Player_FUN_0040e8d0(this_00,&local_46,pvVar12,piVar11);
        puVar14 = (undefined2 *)
                  gta2::sub_40E5A0(pCVar13,pPed1,psVar15,unaff_EDI,unaff_ESI);
        *(undefined2 *)(iVar8 + 0x74) = *puVar14;
        return;
      case 4:
      case 6:
        if (self->S7[0].doorState != 10) {
          pPed1 = (struct Ped *)self->ScriptRef;
          uVar9 = gta2::Ped_sub_420B60(*(Ped **)(iVar8 + 0x7c));
          uVar10 = gta2::Ped_sub_420B60(pPed1);
          if (uVar10 < uVar9) {
            if ((pPed1->AIController != NULL) &&
               (pPed1->AIController->field10_0x30 == 0)) {
              return;
            }
            if (self->ModelId == 3) {
              return;
            }
LAB_004944f9:
            iVar8 = gta2::Ped_GetCurrentAction(pPed1);
            if (iVar8 != 0xb) {
              gta2::CarSystemManager_FUN_0041fa70((struct CarSystemManager *)&self->S7[3].doorState,
                         (short *)&DAT_0066a70c);
            }
            self->S7[0].doorState = 10;
            return;
          }
        }
LAB_00494532:
        self->S7[0].doorState = 1;
        return;
      }
      break;
    case 5:
      switch(param_1) {
      case 3:
      case 4:
      case 6:
        *(undefined1 *)(iVar8 + 0x6a) = 4;
        iVar7 = *(int *)(iVar8 + 0x80);
        iVar1 = *(int *)&self->AIState;
        pPed1 = (struct Ped *)(local_4e + 1);
        psVar15 = (short *)&DAT_0066a5f4;
        piVar11 = (int *)gta2::Player_sub_401B40((SpawnPoint *)(iVar1 + 0x14),
                                    (GlassInfo *)&local_30.SpawnPoint,
                                    (struct S127 *)(iVar7 + 0x14));
        pvVar12 = gta2::Player_sub_401B40((SpawnPoint *)(iVar1 + 0x18),
                             (GlassInfo *)&local_30.field_0xc,
                             (struct S127 *)(iVar7 + 0x18));
        pCVar13 = (struct CarSystemManager *)
                  gta2::Player_FUN_0040e8d0((struct Player *)(local_4e + 2),local_4e + 2,pvVar12,
                             piVar11);
        puVar14 = (undefined2 *)
                  gta2::sub_40E5A0(pCVar13,pPed1,psVar15,unaff_EDI,unaff_ESI);
        *(undefined2 *)(iVar8 + 0x74) = *puVar14;
        return;
      case 5:
        if (self->S7[0].doorState != 10) {
          pPed1 = (struct Ped *)self->ScriptRef;
          uVar9 = gta2::Ped_sub_420B60(*(Ped **)(iVar8 + 0x7c));
          uVar10 = gta2::Ped_sub_420B60(pPed1);
          if (uVar10 < uVar9) {
            if ((pPed1->AIController != NULL) &&
               (pPed1->AIController->field10_0x30 == 0)) {
              return;
            }
            if (self->ModelId == 3) {
              uVar2 = DAT_0066a634_1;
              uVar3 = uRam0066a636;
              uVar4 = uRam0066a637;
              self->S7[2].ID = DAT_0066a634;
              self->S7[2].field4_0xd = uVar2;
              self->S7[2].field5_0xe = uVar3;
              self->S7[2].field6_0xf = uVar4;
              return;
            }
            goto LAB_004944f9;
          }
        }
        goto LAB_00494532;
      }
    }
  }
  return;
}


// 0x004948c0: GameObject::FUN_004948c0
// IDA: sub_4948C0
// Ghidra: GameObject::FUN_004948c0
void * gta2::GameObject_FUN_004948c0(struct GameObject *self,Car *pCar,int param_2,int param_3)
{
  byte *pbVar1;
  undefined1 *pS127;
  Point2D **pS127_00;
  short sVar2;
  struct Ped *pPVar3;
  Sprite *pSVar4;
  undefined1 uVar5;
  bool bVar6;
  byte bVar7;
  int iVar8;
  struct Model *pMVar9;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  void *pvVar10;
  struct SpriteS1 *pSVar11;
  short *psVar12;
  undefined4 *puVar13;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  struct SpriteS1 *pSVar14;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  undefined3 extraout_var_08;
  undefined3 extraout_var_09;
  undefined2 *puVar15;
  undefined3 extraout_var_10;
  struct Car *pCVar16;
  undefined3 extraout_var_11;
  uint uVar17;
  undefined3 extraout_var_12;
  undefined3 extraout_var_13;
  undefined3 extraout_var_14;
  undefined3 extraout_var_15;
  undefined3 extraout_var_16;
  undefined3 extraout_var_17;
  undefined3 extraout_var_18;
  undefined2 uVar18;
  Sprite *pSVar19;
  short *unaff_ESI;
  void *unaff_EDI;
  Point2D **ppPVar20;
  undefined1 *puVar21;
  undefined1 *puVar22;
  struct Model *pMVar23;
  int *piVar24;
  undefined1 *puVar25;
  bool local_37;
  undefined2 local_36;
  undefined1 local_34 [8];
  undefined1 local_2c [8];
  undefined1 local_24 [8];
  struct SpriteS1 *local_1c;
  struct SpriteS1 *local_18;
  struct SpriteS1 *local_14;
  struct SpriteS1 *local_10;
  struct Car *local_c;
  int local_8 [2];
  
  pSVar19 = *(Sprite **)&self->AIState;
  local_18 = (struct SpriteS1 *)((uint)local_18 & 0xffffff00);
  local_37 = false;
  local_14 = *(SpriteS1 **)&pSVar19->field_0x18;
  local_1c = (struct SpriteS1 *)pSVar19->Point2D1;
  puVar15 = (undefined2 *)
            CONCAT22((short)((uint)local_1c >> 0x10),_DAT_0066a434);
  local_34._4_2_ = _DAT_0066a434;
  local_24._4_2_ = _DAT_0066a434;
  if (self->S7[0].doorState != 0xf) {
    gta2::SpriteS1_sub_420600(pSVar19,_DAT_0066a480,_DAT_0066a74c,_DAT_0066a754);
    iVar8 = DecoderFloat(&DAT_0066a414);
    *(char *)((int)&self->S7[3].PedInDoor + 1) = (char)iVar8;
    self->S7[0].doorState = 0x1b;
    puVar15 = (undefined2 *)CONCAT22((short)((uint)iVar8 >> 0x10),_DAT_0066a434)
    ;
  }
  if (*(char *)((int)&self->CollisionData + 1) != '\0') {
    if ((pCar == NULL) && (pCar = (struct Car *)param_3, param_2 != 0)) {
      piVar24 = (int *)&DAT_0066a65c;
      pCVar16 = (struct Car *)FUN_00492170(&param_3);
      bVar6 = gta2::Car_sub_403800(pCVar16,piVar24);
      local_37 = CONCAT31(extraout_var_17,bVar6) != 0;
      pCar = (struct Car *)param_2;
    }
    pCVar16 = (struct Car *)self->S7[1].AnimationFrame;
    if ((pCVar16 != pCar) && (pCVar16 != NULL)) {
      if (self->S7[1].doorState == 2) {
        return pCar;
      }
      pvVar10 = (void *)CONCAT31((int3)((uint)pCar >> 8),local_37);
      if (local_37 != false) {
        return pvVar10;
      }
      if (self->S7[0].doorState != 0xf) {
        bVar7 = gta2::GameObject_sub_493710(self);
        return (void *)CONCAT31(extraout_var_18,bVar7);
      }
      if (*(byte *)&self->CollisionData < 5) {
        return pvVar10;
      }
      *(undefined1 *)&self->CollisionData = 5;
      self->field_0x71 = 2;
      self->BehaviorFlags = 0;
      return pvVar10;
    }
    if (self->S7[0].doorState == 0xf) {
      *(undefined1 *)((int)&self->CollisionData + 1) = 0;
      uVar5 = DAT_0066a434_1;
      self->S7[1].field5_0xe = DAT_0066a434;
      self->S7[1].field6_0xf = uVar5;
      return pCar;
    }
    goto LAB_00495165;
  }
  if (pCar == NULL) {
    if (param_2 != 0) {
      pSVar19 = *(Sprite **)(param_2 + 4);
      pMVar9 = (struct Model *)&local_c;
      pSVar14 = (struct SpriteS1 *)local_8;
      local_c = (struct Car *)0x2;
      pMVar23 = pMVar9;
      FUN_00420590(pSVar19->field3_0xc,&local_10);
      gta2::S122_sub_401BF0(pMVar9,pSVar14,(int *)pMVar23);
      pMVar9 = (struct Model *)&local_c;
      pSVar14 = (struct SpriteS1 *)(local_8 + 1);
      local_c = (struct Car *)0x2;
      pMVar23 = pMVar9;
      FUN_00447e10(pSVar19->field3_0xc,&local_10);
      gta2::S122_sub_401BF0(pMVar9,pSVar14,(int *)pMVar23);
      puVar15 = gta2::Player_FUN_0040e8d0((struct Player *)(local_8 + 1),&local_36,
                           (struct Player *)(local_8 + 1),local_8);
      local_34._4_2_ = *puVar15;
      piVar24 = (int *)&DAT_0066a65c;
      pCVar16 = (struct Car *)FUN_00492170(&local_c);
      bVar6 = gta2::Car_sub_403800(pCVar16,piVar24);
      bVar6 = CONCAT31(extraout_var,bVar6) == 0;
      goto LAB_00494976;
    }
    local_34[4] = DAT_0066a4e0;
    local_34[5] = DAT_0066a4e0_1;
    pSVar19 = *(Sprite **)(param_3 + 0x80);
    *(short *)&pSVar19->field0_0x0 = (short)puVar15;
  }
  else {
    gta2::Car_sub_41FAC0(pCar,&local_36);
    local_34._4_2_ = *puVar15;
    pSVar19 = pCar->CarSprite;
    bVar6 = gta2::S119_IsCarEqual((CrashData *)gCrashData,pCar);
    bVar6 = !bVar6;
LAB_00494976:
    if (!bVar6) {
      local_37 = true;
      DAT_0066a3c8 = 1;
    }
  }
  pPVar3 = (struct Ped *)self->ScriptRef;
  iVar8 = FUN_00492c20(pPVar3);
  if (((iVar8 == 2) ||
      (iVar8 = CONCAT31((int3)((uint)iVar8 >> 8),*(char *)&self->Armor),
      *(char *)&self->Armor != '\0')) && (self->S7[0].doorState != 0xf)) {
    if (local_37 == false) {
      bVar6 = gta2::Ped_IsSearchType(pPVar3,SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
      pvVar10 = (void *)param_3;
      iVar8 = param_3;
      if (bVar6) {
        pvVar10 = (void *)CONCAT31(extraout_var_00,bVar6);
        iVar8 = self->ModelId + -3;
      }
      if (iVar8 == 0) {
        bVar7 = gta2::GameObject_sub_493710(self);
        pvVar10 = (void *)CONCAT31(extraout_var_01,bVar7);
      }
      goto LAB_00494a7e;
    }
LAB_00494aed:
    uVar5 = DAT_0066a73c_1;
    self->S7[1].field5_0xe = DAT_0066a73c;
    self->S7[1].field6_0xf = uVar5;
    bVar6 = gta2::Ped_IsSearchType(pPVar3,SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
    iVar8 = self->S7[0].doorState;
    if (bVar6) {
      if ((iVar8 != 0xf) && (self->ModelId != 3)) {
        gta2::SpriteS1_sub_420600(*(Sprite **)&self->AIState,_DAT_0066a480,
                            _DAT_0066a74c,_DAT_0066a754);
        pvVar10 = (void *)DecoderFloat(&DAT_0066a414);
        *(char *)((int)&self->S7[3].PedInDoor + 1) = (char)pvVar10;
        self->S7[0].doorState = 0x1b;
        return pvVar10;
      }
      if (self->S7[1].doorState == 1) {
        gta2::SpriteS1_sub_420600(*(Sprite **)&self->AIState,_DAT_0066a480,
                            _DAT_0066a74c,_DAT_0066a754);
        puVar15 = (undefined2 *)
                  gta2::sub_40E5A0(*(CarSystemManager **)&self->AIState,
                             (struct Ped *)&param_3,(short *)&DAT_0066a5f4,unaff_EDI,
                             unaff_ESI);
        *(undefined2 *)&self->S7[3].doorState = *puVar15;
        return puVar15;
      }
      gta2::SpriteS1_sub_420600(*(Sprite **)&self->AIState,_DAT_0066a480,_DAT_0066a74c
                          ,_DAT_0066a754);
      piVar24 = &self->S7[3].doorState;
      *(short *)piVar24 = (short)pSVar19->field0_0x0;
      pbVar1 = &self->S7[2].ID;
      gta2::sub_41FC20((struct CarSystemManager *)pbVar1,piVar24,(GlassInfo *)pbVar1,
                 (struct Ped *)&local_c,(struct Ped *)&local_10);
      pSVar4 = *(Sprite **)&self->AIState;
      pSVar14 = gta2::S202_sub_401B20((Point2D *)&pSVar4->field_0x18,(struct SpriteS1 *)local_2c,
                           (struct S127 *)&local_10);
      pSVar11 = gta2::S202_sub_401B20((Point2D *)&pSVar4->Point2D1,(struct SpriteS1 *)local_34,
                           (struct S127 *)&local_c);
      gta2::SpriteS1_sub_420600(pSVar4,(int)pSVar11->FirstElement,
                          (int)pSVar14->FirstElement,(int)pSVar4->Point2D);
    }
    else if ((iVar8 == 0xf) && (4 < *(byte *)&self->CollisionData)) {
      *(undefined1 *)&self->CollisionData = 5;
      self->field_0x71 = 2;
      self->BehaviorFlags = 0;
    }
  }
  else {
    pvVar10 = (void *)CONCAT31((int3)((uint)iVar8 >> 8),local_37);
    if (local_37 != false) goto LAB_00494aed;
LAB_00494a7e:
    if (self->S7[0].doorState == 0xf) {
      if (4 < *(byte *)&self->CollisionData) {
        *(undefined1 *)&self->CollisionData = 5;
        self->field_0x71 = 2;
        self->BehaviorFlags = 0;
      }
      *(undefined1 *)((int)&self->CollisionData + 1) = 0;
      if (pCar == NULL) {
        return pvVar10;
      }
      pvVar10 = *(void **)&self->AIState;
      bVar6 = gta2::Player_sub_40CE70((struct Player *)&pCar->CarSprite->Point2D,
                         (struct Player *)((int)pvVar10 + 0x1c));
      if (CONCAT31(extraout_var_02,bVar6) == 0) {
        return NULL;
      }
      *(undefined1 *)&self->field43_0xa0 = 1;
      pvVar10 = FUN_004be570(pvVar10,pCar->CarSprite);
      return pvVar10;
    }
  }
  puVar25 = local_24;
  puVar22 = local_2c + 4;
  pS127 = &pSVar19->field_0x18;
  pS127_00 = &pSVar19->Point2D1;
  ppPVar20 = pS127_00;
  puVar21 = pS127;
  pvVar10 = gta2::sub_401C80((struct CarSystemManager *)pSVar19,&local_36)
  ;
  FUN_0042a720(*(int *)&self->AIState + 0x14,*(int *)&self->AIState + 0x18,
               pvVar10,ppPVar20,puVar21,puVar22,puVar25);
  psVar12 = gta2::Player_FUN_0040e8d0((struct Player *)&local_36,&local_36,local_24,
                       (int *)(local_2c + 4));
  local_24._4_2_ = *psVar12;
  puVar13 = (undefined4 *)FUN_00492ce0(local_2c);
  local_34._0_4_ = *puVar13;
  puVar13 = (undefined4 *)FUN_00492cf0(local_2c);
  local_2c._0_4_ = *puVar13;
  bVar6 = gta2::Player_IsCurrentPlayer((struct Player *)local_34,(struct Player *)&DAT_0066a47c);
  if ((CONCAT31(extraout_var_03,bVar6) != 0) ||
     (bVar6 = gta2::Player_IsCurrentPlayer((struct Player *)local_2c,(struct Player *)&DAT_0066a47c),
     CONCAT31(extraout_var_04,bVar6) != 0)) {
    gta2::sub_41FC20((struct CarSystemManager *)local_2c,&self->S7[3].doorState,
               (GlassInfo *)&DAT_0066a474,(struct Ped *)local_34,(struct Ped *)local_2c);
    gta2::Player_sub_40E530((Point2D *)local_34,(int *)(*(int *)&self->AIState + 0x14));
    gta2::Player_sub_40E530((Point2D *)local_2c,(int *)(*(int *)&self->AIState + 0x18));
  }
  puVar25 = local_24;
  puVar22 = local_2c + 4;
  ppPVar20 = pS127_00;
  puVar21 = pS127;
  pvVar10 = gta2::sub_401C80((struct CarSystemManager *)pSVar19,&local_36)
  ;
  FUN_0042a720(local_34,local_2c,pvVar10,ppPVar20,puVar21,puVar22,puVar25);
  pSVar14 = gta2::S202_sub_401B20((Point2D *)(local_2c + 4),(struct SpriteS1 *)local_2c,
                       (struct S127 *)pS127_00);
  local_34._0_4_ = pSVar14->FirstElement;
  pSVar14 = gta2::S202_sub_401B20((Point2D *)local_24,(struct SpriteS1 *)local_2c,(struct S127 *)pS127);
  local_2c._0_4_ = pSVar14->FirstElement;
  puVar25 = local_24;
  puVar22 = local_2c + 4;
  ppPVar20 = pS127_00;
  puVar21 = pS127;
  pvVar10 = gta2::sub_401C80((struct CarSystemManager *)pSVar19,&local_36)
  ;
  FUN_0042a720(&local_1c,&local_14,pvVar10,ppPVar20,puVar21,puVar22,puVar25);
  pSVar14 = gta2::S202_sub_401B20((Point2D *)(local_2c + 4),(struct SpriteS1 *)&local_14,
                       (struct S127 *)pS127_00);
  local_1c = pSVar14->FirstElement;
  pSVar14 = gta2::S202_sub_401B20((Point2D *)local_24,(struct SpriteS1 *)&local_14,(struct S127 *)pS127);
  local_14 = pSVar14->FirstElement;
  psVar12 = (short *)gta2::sub_401C80((struct CarSystemManager *)(local_34 + 4),&local_36);
  bVar6 = gta2::CarSystemManager_less_than((struct CarSystemManager *)(local_24 + 4),psVar12);
  if (CONCAT31(extraout_var_05,bVar6) == 0) {
    bVar6 = gta2::Point2D_FUN_004037e0((Point2D *)local_34,(struct SpriteS1 *)&local_1c);
    psVar12 = (short *)&DAT_0066a73c;
    if (CONCAT31(extraout_var_16,bVar6) == 0) {
LAB_00494eb8:
      puVar15 = (undefined2 *)
                gta2::sub_40E5A0((struct CarSystemManager *)pSVar19,(struct Ped *)&local_36,psVar12,
                           unaff_EDI,unaff_ESI);
LAB_00494ec4:
      uVar18 = *puVar15;
      self->S7[1].ID = (char)uVar18;
      self->S7[1].field4_0xd = (char)((ushort)uVar18 >> 8);
      uVar18 = _DAT_0066a488;
    }
    else {
      puVar15 = (undefined2 *)
                gta2::SpriteS1_sub_40E5D0((struct CarSystemManager *)pSVar19,(struct Ped *)&local_36,0x66a73c
                          );
LAB_0049511e:
      uVar18 = *puVar15;
      self->S7[1].ID = (char)uVar18;
      self->S7[1].field4_0xd = (char)((ushort)uVar18 >> 8);
      uVar18 = _DAT_0066a5c8;
    }
    self->S7[1].field5_0xe = (char)uVar18;
    self->S7[1].field6_0xf = (char)((ushort)uVar18 >> 8);
  }
  else {
    local_18 = (struct SpriteS1 *)CONCAT31(local_18._1_3_,3);
    psVar12 = (short *)gta2::sub_40E5A0((struct CarSystemManager *)&DAT_0066a5f4,
                                  (struct Ped *)&local_36,(short *)(local_34 + 4),
                                  unaff_EDI,unaff_ESI);
    bVar6 = gta2::CarSystemManager_less_than((struct CarSystemManager *)(local_24 + 4),psVar12);
    if (CONCAT31(extraout_var_06,bVar6) == 0) {
      bVar6 = gta2::Point2D_FUN_004037e0((Point2D *)local_2c,(struct SpriteS1 *)&local_14);
      pbVar1 = &self->S7[1].field5_0xe;
      if (CONCAT31(extraout_var_13,bVar6) == 0) {
        bVar6 = FUN_0040e690(pbVar1,(short *)&DAT_0066a5c8);
        if (CONCAT31(extraout_var_15,bVar6) == 0) {
          sVar2 = (short)pSVar19->field0_0x0;
          self->S7[1].ID = (char)sVar2;
          self->S7[1].field4_0xd = (char)((ushort)sVar2 >> 8);
          uVar5 = DAT_0066a488_1;
          self->S7[1].field5_0xe = DAT_0066a488;
          self->S7[1].field6_0xf = uVar5;
        }
        else {
          puVar15 = (undefined2 *)
                    gta2::sub_40E5A0((struct CarSystemManager *)pSVar19,(struct Ped *)&local_36,
                               (short *)&DAT_0066a5f4,unaff_EDI,unaff_ESI);
          uVar18 = *puVar15;
          self->S7[1].ID = (char)uVar18;
          self->S7[1].field4_0xd = (char)((ushort)uVar18 >> 8);
          uVar5 = DAT_0066a5c8_1;
          self->S7[1].field5_0xe = DAT_0066a5c8;
          self->S7[1].field6_0xf = uVar5;
        }
      }
      else {
        bVar6 = FUN_0040e690(pbVar1,(short *)&DAT_0066a5c8);
        if (CONCAT31(extraout_var_14,bVar6) == 0) {
          sVar2 = (short)pSVar19->field0_0x0;
          self->S7[1].ID = (char)sVar2;
          self->S7[1].field4_0xd = (char)((ushort)sVar2 >> 8);
          uVar5 = DAT_0066a488_1;
          self->S7[1].field5_0xe = DAT_0066a488;
          self->S7[1].field6_0xf = uVar5;
        }
        else {
          puVar15 = (undefined2 *)
                    gta2::sub_40E5A0((struct CarSystemManager *)pSVar19,(struct Ped *)&local_36,
                               (short *)&DAT_0066a5f4,unaff_EDI,unaff_ESI);
          uVar18 = *puVar15;
          self->S7[1].ID = (char)uVar18;
          self->S7[1].field4_0xd = (char)((ushort)uVar18 >> 8);
          uVar5 = DAT_0066a5c8_1;
          self->S7[1].field5_0xe = DAT_0066a5c8;
          self->S7[1].field6_0xf = uVar5;
        }
      }
    }
    else {
      local_18 = (struct SpriteS1 *)CONCAT31(local_18._1_3_,2);
      psVar12 = (short *)gta2::SpriteS1_sub_40E5D0((struct CarSystemManager *)&DAT_0066a5f4,
                                    (struct Ped *)&local_36,(int)(local_34 + 4));
      bVar6 = gta2::CarSystemManager_less_than((struct CarSystemManager *)(local_24 + 4),psVar12);
      if (CONCAT31(extraout_var_07,bVar6) == 0) {
        bVar6 = gta2::Point2D_FUN_004037e0((Point2D *)local_34,(struct SpriteS1 *)&local_1c)
        ;
        if (CONCAT31(extraout_var_12,bVar6) == 0) {
          puVar15 = (undefined2 *)
                    gta2::sub_40E5A0((struct CarSystemManager *)pSVar19,(struct Ped *)&local_36,
                               (short *)&DAT_0066a73c,unaff_EDI,unaff_ESI);
          goto LAB_0049511e;
        }
        puVar15 = (undefined2 *)
                  gta2::SpriteS1_sub_40E5D0((struct CarSystemManager *)pSVar19,(struct Ped *)&local_36,
                             0x66a73c);
        goto LAB_00494ec4;
      }
      local_18 = (struct SpriteS1 *)CONCAT31(local_18._1_3_,1);
      bVar6 = gta2::CarSystemManager_less_than((struct CarSystemManager *)(local_24 + 4),
                         (short *)(local_34 + 4));
      if (CONCAT31(extraout_var_08,bVar6) == 0) {
        bVar6 = gta2::Point2D_FUN_004037e0((Point2D *)local_2c,(struct SpriteS1 *)&local_14)
        ;
        if (CONCAT31(extraout_var_10,bVar6) != 0) {
          psVar12 = (short *)&DAT_0066a5f4;
          goto LAB_00494eb8;
        }
        sVar2 = (short)pSVar19->field0_0x0;
        self->S7[1].ID = (char)sVar2;
        self->S7[1].field4_0xd = (char)((ushort)sVar2 >> 8);
        uVar5 = DAT_0066a5c8_1;
        self->S7[1].field5_0xe = DAT_0066a5c8;
        self->S7[1].field6_0xf = uVar5;
      }
      else {
        local_18 = (struct SpriteS1 *)((uint)local_18 & 0xffffff00);
        bVar6 = gta2::Point2D_FUN_004037e0((Point2D *)local_34,(struct SpriteS1 *)&local_1c)
        ;
        if (CONCAT31(extraout_var_09,bVar6) == 0) {
          puVar15 = (undefined2 *)
                    gta2::sub_40E5A0((struct CarSystemManager *)pSVar19,(struct Ped *)&local_36,
                               (short *)&DAT_0066a73c,unaff_EDI,unaff_ESI);
          uVar18 = *puVar15;
          self->S7[1].ID = (char)uVar18;
          self->S7[1].field4_0xd = (char)((ushort)uVar18 >> 8);
          uVar5 = DAT_0066a488_1;
          self->S7[1].field5_0xe = DAT_0066a488;
          self->S7[1].field6_0xf = uVar5;
        }
        else {
          puVar15 = (undefined2 *)
                    gta2::SpriteS1_sub_40E5D0((struct CarSystemManager *)pSVar19,(struct Ped *)&local_36,
                               0x66a73c);
          uVar18 = *puVar15;
          self->S7[1].ID = (char)uVar18;
          self->S7[1].field4_0xd = (char)((ushort)uVar18 >> 8);
          uVar5 = DAT_0066a5c8_1;
          self->S7[1].field5_0xe = DAT_0066a5c8;
          self->S7[1].field6_0xf = uVar5;
        }
      }
    }
  }
  *(undefined1 *)((int)&self->CollisionData + 1) = 1;
  gta2::SpriteS1_sub_420600(*(Sprite **)&self->AIState,_DAT_0066a480,_DAT_0066a74c,
                      _DAT_0066a754);
  bVar6 = gta2::Ped_IsSearchType((struct Ped *)self->ScriptRef,
                             SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
  if (bVar6) {
    pPVar3 = (struct Ped *)self->ScriptRef;
    pvVar10 = (void *)gta2::Ped_GetCurrentAction(pPVar3);
    if (pvVar10 != (void *)0x23) {
      return pvVar10;
    }
    pCVar16 = (struct Car *)gta2::Ped_GetCurrentCar(pPVar3);
    bVar6 = gta2::S119_IsCarEqual((CrashData *)gCrashData,pCVar16);
    if (bVar6) {
      return (void *)CONCAT31(extraout_var_11,bVar6);
    }
  }
  gta2::sub_41FC20((struct CarSystemManager *)&local_c,&self->S7[1].ID,
             (GlassInfo *)&self->S7[2].ID,(struct Ped *)&local_c,(struct Ped *)&local_10);
  pSVar4 = *(Sprite **)&self->AIState;
  local_10 = gta2::S202_sub_401B20((Point2D *)&pSVar4->field_0x18,(struct SpriteS1 *)&local_14,
                        (struct S127 *)&local_10);
  pSVar14 = gta2::S202_sub_401B20((Point2D *)&pSVar4->Point2D1,(struct SpriteS1 *)&local_1c,
                       (struct S127 *)&local_c);
  gta2::SpriteS1_sub_420600(pSVar4,(int)pSVar14->FirstElement,
                      (int)local_10->FirstElement,(int)pSVar4->Point2D);
  gta2::GameObject_FUN_00499f00(self,DAT_0059322c);
  iVar8._0_1_ = self->S7[0].ID;
  iVar8._1_1_ = self->S7[0].field4_0xd;
  iVar8._2_1_ = self->S7[0].field5_0xe;
  iVar8._3_1_ = self->S7[0].field6_0xf;
  if (iVar8 != 0) {
    uVar17 = (uint)local_18 & 0xff;
    if (uVar17 == 1) {
LAB_00494fbc:
      puVar15 = (undefined2 *)
                gta2::SpriteS1_sub_40E5D0((struct CarSystemManager *)pSVar19,(struct Ped *)&local_36,0x66a73c
                          );
      uVar18 = *puVar15;
      self->S7[1].ID = (char)uVar18;
      self->S7[1].field4_0xd = (char)((ushort)uVar18 >> 8);
    }
    else if (uVar17 == 2) {
      sVar2 = (short)pSVar19->field0_0x0;
      self->S7[1].ID = (char)sVar2;
      self->S7[1].field4_0xd = (char)((ushort)sVar2 >> 8);
    }
    else if (uVar17 == 3) goto LAB_00494fbc;
    if (self->S7[0].doorState == 0xf) {
      if (4 < *(byte *)&self->CollisionData) {
        *(undefined1 *)&self->CollisionData = 5;
        self->field_0x71 = 2;
        self->BehaviorFlags = 0;
      }
    }
    else {
      gta2::SpriteS1_sub_447E20(*(SpriteS1 **)&self->AIState,_DAT_0066a480,_DAT_0066a74c);
    }
  }
  if ((pCar == NULL) && (pCar = (struct Car *)param_2, param_2 == 0)) {
    pCar = (struct Car *)param_3;
  }
LAB_00495165:
  self->S7[1].AnimationFrame = (int)pCar;
  *(Car **)&self->S7[0].ID = pCar;
  return pCar;
}


// 0x00495220: GameObject::sub_495220
// IDA: GameObject::sub_495220
// Ghidra: GameObject::FUN_00495220
uint gta2::GameObject_sub_495220(struct GameObject *self,Car *param_1)
{
  byte bVar1;
  struct Car *pCVar2;
  bool bVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  uint uVar11;
  struct Car *pCVar12;
  undefined1 *puVar13;
  undefined4 uVar14;
  undefined1 local_11;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  undefined4 local_4;
  
  local_8 = local_8 & 0xffffff00;
  iVar5 = *(int *)&self->AIState;
  local_c = *(undefined4 *)(iVar5 + 0x14);
  local_10 = *(undefined4 *)(iVar5 + 0x18);
  local_4 = *(undefined4 *)(iVar5 + 0x1c);
  iVar5 = DecoderFloat(&local_4);
  iVar5 = iVar5 + -1;
  bVar1 = 0;
  if ((((self->S7[0].doorState == 0xf) || (self->ModelId == 9)) ||
      (bVar3 = gta2::Ped_IsSearchType((struct Ped *)self->ScriptRef,
                                  SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY), bVar3))
     || (iVar6 = gta2::Ped_GetCurrentOccupation((struct Ped *)self->ScriptRef), iVar6 == 0x29)) {
    bVar1 = 1;
  }
  if ((*(byte *)&self->MaxHealth & 1) != 0) {
    iVar5 = DecoderFloat(&local_4);
  }
  pCVar2 = param_1;
  puVar13 = &local_11;
  uVar14 = 0;
  pCVar12 = param_1;
  iVar6 = DecoderFloat(&local_4);
  iVar7 = DecoderFloat(&local_10);
  iVar8 = DecoderFloat(&local_c);
  uVar9 = FUN_004656d0(iVar8,iVar7,iVar6,pCVar12,puVar13,uVar14);
  if ((char)uVar9 != '\0') goto switchD_0049535b_caseD_5;
  switch(pCVar2) {
  case (struct Car *)0x1:
    iVar6 = DecoderFloat(&local_10);
    iVar6 = iVar6 + -1;
    iVar7 = DecoderFloat(&local_c);
    break;
  case (struct Car *)0x2:
    iVar6 = DecoderFloat(&local_10);
    iVar6 = iVar6 + 1;
    iVar7 = DecoderFloat(&local_c);
    break;
  case (struct Car *)0x3:
    iVar6 = DecoderFloat(&local_10);
    iVar7 = DecoderFloat(&local_c);
    iVar7 = iVar7 + 1;
    break;
  case (struct Car *)0x4:
    iVar6 = DecoderFloat(&local_10);
    iVar7 = DecoderFloat(&local_c);
    iVar7 = iVar7 + -1;
    break;
  default:
    goto switchD_004952d8_caseD_4;
  }
  bVar4 = gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct,iVar7,iVar6,iVar5);
  local_8 = CONCAT31(local_8._1_3_,bVar4);
switchD_004952d8_caseD_4:
  uVar9 = local_8 & 0xff;
  switch(uVar9) {
  case 0:
    uVar11 = self->MaxHealth;
    if ((uVar11 & 1) != 0) {
      puVar10 = (undefined4 *)FUN_0042a630(&local_8,&local_4);
      param_1 = (struct Car *)*puVar10;
      bVar3 = gta2::Point2D_FUN_004037e0((Point2D *)&param_1,(struct SpriteS1 *)&DAT_0066a678);
      if (CONCAT31(extraout_var,bVar3) != 0) {
        self->MaxHealth = uVar11 & 0xfffffffe;
        uVar9 = gta2::GameObject_sub_495220(self,pCVar2);
        self->MaxHealth = self->MaxHealth | 1;
        return uVar9;
      }
      bVar3 = gta2::Car_sub_403800((struct Car *)&param_1,(int *)&DAT_0066a65c);
      uVar9 = CONCAT31(extraout_var_00,bVar3);
      if (uVar9 != 0) {
        self->MaxHealth = uVar11 & 0xfffffffe;
        FUN_004824e0(&param_1,0);
        uVar11 = gta2::GameObject_sub_495220(self,pCVar2);
        FUN_00482510((void *)(*(int *)&self->AIState + 0x1c),
                     (GlassInfo *)&param_1);
        uVar9 = self->MaxHealth;
        self->MaxHealth = uVar9 | 1;
        return CONCAT31((int3)(uVar9 >> 8),(char)uVar11);
      }
    }
    break;
  case 1:
  case 3:
    return (uint)bVar1;
  case 2:
  case 4:
    return 1;
  }
switchD_0049535b_caseD_5:
  return uVar9 & 0xffffff00;
}


// 0x00495470: GameObject::FUN_00495470
// IDA: sub_495470
// Ghidra: GameObject::FUN_00495470
byte gta2::GameObject_FUN_00495470(struct GameObject *self)
{
  byte bVar1;
  undefined3 extraout_var;
  uint uVar2;
  struct Car **ppCVar3;
  undefined3 extraout_var_00;
  undefined2 extraout_var_01;
  bool bVar4;
  char local_e [2];
  struct Car *local_c;
  struct Car *local_8;
  struct Car *local_4;
  
  bVar1 = gta2::SpriteS1_sub_472C00(self,(struct CarSystemManager *)&self->S7[3].doorState);
  local_c = (struct Car *)CONCAT31(extraout_var,bVar1);
  uVar2 = gta2::GameObject_sub_495220(self,local_c);
  if ((byte)uVar2 != 0) {
    return (byte)uVar2;
  }
  local_e[0] = '\x01';
  local_4 = (struct Car *)FUN_00491f10(local_e,&local_c,local_e);
  uVar2 = gta2::GameObject_sub_495220(self,local_4);
  bVar4 = (char)uVar2 != '\x01';
  local_e[0] = '\0';
  local_8 = (struct Car *)FUN_00491f10(&local_c,&local_c,local_e);
  uVar2 = gta2::GameObject_sub_495220(self,local_8);
  if ((byte)uVar2 == 1) {
    if (bVar4) {
      ppCVar3 = &local_8;
      goto LAB_0049551b;
    }
    uVar2 = (int)DAT_0066a3b8 & 0x80000001;
    bVar4 = uVar2 == 0;
    if ((int)uVar2 < 0) {
      bVar4 = (uVar2 - 1 | 0xfffffffe) == 0xffffffff;
    }
    if (bVar4) {
      ppCVar3 = &local_8;
      goto LAB_0049551b;
    }
  }
  else if (bVar4) {
    return (byte)uVar2;
  }
  ppCVar3 = &local_4;
LAB_0049551b:
  bVar1 = FUN_004725b0(local_e,(undefined2 *)local_e,ppCVar3);
  bVar1 = FUN_00492400(CONCAT22(extraout_var_01,
                                *(undefined2 *)CONCAT31(extraout_var_00,bVar1)))
  ;
  return bVar1;
}


// 0x00495540: GameObject::sub_495540
// IDA: GameObject::sub_495540
// Ghidra: GameObject::FUN_00495540
byte gta2::GameObject_sub_495540(struct GameObject *self,char param_1,char param_2)
{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 local_8;
  undefined4 local_4;
  
  local_8 = *(undefined4 *)(*(int *)&self->AIState + 0x14);
  local_4 = *(undefined4 *)(*(int *)&self->AIState + 0x18);
  iVar2 = FUN_00491ee0(&local_8);
  iVar3 = FUN_00491ee0(&local_4);
  cVar1 = (char)iVar3;
  if (param_1 != (char)iVar2) {
    if (param_2 != cVar1) {
      return 0;
    }
    if ((char)(param_1 - (char)iVar2) == -1) {
      uVar4 = gta2::GameObject_sub_495220(self,(struct Car *)0x4);
      return (byte)uVar4;
    }
    uVar4 = gta2::GameObject_sub_495220(self,(struct Car *)0x3);
    return (byte)uVar4;
  }
  if (param_2 == cVar1) {
    return 1;
  }
  if ((char)(param_2 - cVar1) == -1) {
    uVar4 = gta2::GameObject_sub_495220(self,(struct Car *)0x1);
    return (byte)uVar4;
  }
  uVar4 = gta2::GameObject_sub_495220(self,(struct Car *)0x2);
  return (byte)uVar4;
}


// 0x004955f0: GameObject::sub_4955F0
// IDA: GameObject::sub_4955F0
// Ghidra: FUN_004955f0
void gta2::GameObject_sub_4955F0(void *self)
{
  struct CarSystemManager *this_00;
  bool bVar1;
  short sVar2;
  SpawnPoint *this_01;
  int *piVar3;
  void *pvVar4;
  short *psVar5;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  GlassInfo *pGVar6;
  struct S127 *pS127;
  undefined4 local_18;
  short local_14;
  undefined4 local_10 [2];
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  undefined2 extraout_var_03;
  
  local_14 = _DAT_0066a434;
  local_18 = 0x20;
  sVar2 = gta2::Random_Random((struct Random *)&gRandom,(short)&local_18);
  if (0x16 < sVar2) {
    local_14 = *(short *)((int)self + 0x42);
    this_00 = (struct CarSystemManager *)((int)self + 0x42);
    pGVar6 = (GlassInfo *)(local_10 + 1);
    pS127 = (struct S127 *)&DAT_0066a404;
    local_10[0] = 0x10;
    sVar2 = gta2::Random_Random((struct Random *)&gRandom,(short)local_10);
    this_01 = (SpawnPoint *)CONCAT22(extraout_var_03,sVar2);
    gta2::Decoder_SetValue(local_8,sVar2);
    piVar3 = (int *)gta2::Player_sub_401B40(this_01,pGVar6,pS127);
    pvVar4 = gta2::WorldCoordinateToScreenCoord(&DAT_0066a6b8,local_4,piVar3);
    psVar5 = (short *)FUN_0040f540(&local_18,(int)pvVar4);
    this_00->index = *psVar5;
    bVar1 = gta2::CarSystemManager_greater_than((struct CarSystemManager *)&local_14,(short *)&DAT_0066a5f4);
    if (CONCAT31(extraout_var,bVar1) != 0) {
      bVar1 = gta2::CarSystemManager_greater_than(this_00,(short *)&DAT_0066a5f4);
      if (CONCAT31(extraout_var_00,bVar1) != 0) {
        psVar5 = (short *)gta2::sub_401C80(this_00,&local_18);
        this_00->index = *psVar5;
      }
    }
    bVar1 = gta2::CarSystemManager_less_than((struct CarSystemManager *)&local_14,(short *)&DAT_0066a5f4);
    if (CONCAT31(extraout_var_01,bVar1) != 0) {
      bVar1 = gta2::CarSystemManager_less_than(this_00,(short *)&DAT_0066a5f4);
      if (CONCAT31(extraout_var_02,bVar1) != 0) {
        psVar5 = (short *)gta2::sub_401C80(this_00,&local_18);
        this_00->index = *psVar5;
      }
    }
    FUN_004928a0(self);
  }
  return;
}


// 0x00495700: GameObject::sub_495700
// IDA: GameObject::sub_495700
// Ghidra: GameObject::FUN_00495700
byte gta2::GameObject_sub_495700(struct GameObject *self)
{
  int *this_00;
  int iVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined4 uVar5;
  byte bVar6;
  bool bVar7;
  int iVar8;
  undefined4 uVar9;
  struct CarSystemManager *this_01;
  undefined3 extraout_var;
  int iVar10;
  short *psVar11;
  undefined4 uStack_4;
  
  iVar10 = _DAT_0066a798;
  uVar5 = _DAT_0066a634;
  uVar9 = _DAT_0066a574;
  iVar1 = self->S7[0].doorState;
  iVar8 = iVar1 + -1;
  bVar6 = (byte)iVar8;
  uStack_4 = self;
  switch(iVar1) {
  case 1:
    FUN_004955f0(self);
    uVar2 = DAT_0066a798_1;
    uVar3 = uRam0066a79a;
    uVar4 = uRam0066a79b;
    self->S7[2].ID = DAT_0066a798;
    self->S7[2].field4_0xd = uVar2;
    self->S7[2].field5_0xe = uVar3;
    self->S7[2].field6_0xf = uVar4;
    BYTE_0066a3c1 = 1;
    BYTE_0066a3c2 = 1;
    DAT_0066a3c3 = 0;
    return bVar6;
  default:
    return bVar6;
  case 3:
    if (*(short *)((int)&self->S7[3].PedInDoor + 2) != 0) {
      uVar2 = DAT_0066a574_1;
      uVar3 = uRam0066a576;
      uVar4 = uRam0066a577;
      self->S7[2].ID = DAT_0066a574;
      self->S7[2].field4_0xd = uVar2;
      self->S7[2].field5_0xe = uVar3;
      self->S7[2].field6_0xf = uVar4;
      FUN_004955f0(self);
      BYTE_0066a3c1 = 1;
      BYTE_0066a3c2 = 1;
      DAT_0066a3c3 = 0;
      return (byte)uVar9;
    }
    uVar2 = DAT_0066a798_1;
    uVar3 = uRam0066a79a;
    uVar4 = uRam0066a79b;
    self->S7[2].ID = DAT_0066a798;
    self->S7[2].field4_0xd = uVar2;
    self->S7[2].field5_0xe = uVar3;
    self->S7[2].field6_0xf = uVar4;
    break;
  case 4:
    if (*(short *)((int)&self->S7[3].PedInDoor + 2) != 0) {
      uVar2 = DAT_0066a428_1;
      uVar3 = uRam0066a42a;
      uVar4 = uRam0066a42b;
      self->S7[2].ID = DAT_0066a428;
      self->S7[2].field4_0xd = uVar2;
      self->S7[2].field5_0xe = uVar3;
      self->S7[2].field6_0xf = uVar4;
      FUN_004955f0(self);
      BYTE_0066a3c1 = 1;
      BYTE_0066a3c2 = 1;
      DAT_0066a3c3 = 0;
      return bVar6;
    }
    uVar2 = DAT_0066a798_1;
    uVar3 = uRam0066a79a;
    uVar4 = uRam0066a79b;
    self->S7[2].ID = DAT_0066a798;
    self->S7[2].field4_0xd = uVar2;
    self->S7[2].field5_0xe = uVar3;
    self->S7[2].field6_0xf = uVar4;
    iVar8 = iVar10;
    break;
  case 7:
    if (*(short *)((int)&self->S7[3].PedInDoor + 2) == 0) {
      self->PhysicsFlags = 0;
      *(undefined1 *)&self->CollisionData = 0;
      self->S7[0].doorState = 1;
      uVar2 = DAT_0066a798_1;
      uVar3 = uRam0066a79a;
      uVar4 = uRam0066a79b;
      self->S7[2].ID = DAT_0066a798;
      self->S7[2].field4_0xd = uVar2;
      self->S7[2].field5_0xe = uVar3;
      self->S7[2].field6_0xf = uVar4;
    }
    else {
      self->PhysicsFlags = 2;
      uVar9 = _DAT_0066a634;
      DAT_0066a634 = (undefined1)uVar5;
      DAT_0066a634_1 = SUB41(uVar5,1);
      uVar2 = DAT_0066a634_1;
      uRam0066a636 = SUB41(uVar5,2);
      uVar3 = uRam0066a636;
      uRam0066a637 = SUB41(uVar5,3);
      uVar4 = uRam0066a637;
      self->S7[2].ID = DAT_0066a634;
      _DAT_0066a634 = uVar9;
      self->S7[2].field4_0xd = uVar2;
      self->S7[2].field5_0xe = uVar3;
      self->S7[2].field6_0xf = uVar4;
      *(undefined1 *)&self->CollisionData = 0;
    }
    DAT_0066a3c3 = 0;
    BYTE_0066a3c1 = 1;
    BYTE_0066a3c2 = 1;
    return bVar6;
  case 8:
  case 9:
    if (*(short *)((int)&self->S7[3].PedInDoor + 2) == 0) {
      *(undefined2 *)((int)&self->S7[3].PedInDoor + 2) = 100;
      bVar6 = gta2::CarSystemManager_FUN_0040e490((struct CarSystemManager *)&self->S7[3].doorState);
      self->S7[0].doorState = 1;
      self->PhysicsFlags = 0;
    }
    BYTE_0066a3c2 = 0;
    DAT_0066a3c3 = 0;
    BYTE_0066a3c1 = 1;
    return bVar6;
  case 0x19:
    FUN_004920a0(self);
    psVar11 = (short *)&DAT_0066a4d0;
    this_00 = &self->S7[3].doorState;
    this_01 = (struct CarSystemManager *)
              gta2::sub_40EAB0((Sprite *)this_00,(undefined2 *)((int)&uStack_4 + 2),
                         (struct CarSystemManager *)this_00,(int)&self->S7[0].PedInDoor
                        );
    bVar7 = gta2::CarSystemManager_less_than(this_01,psVar11);
    iVar1 = _DAT_0066a798;
    iVar10 = CONCAT31(extraout_var,bVar7);
    if (CONCAT31(extraout_var,bVar7) != 0) {
      self->S7[0].doorState = 1;
      iVar10 = _DAT_0066a798;
      DAT_0066a798 = (undefined1)iVar1;
      DAT_0066a798_1 = SUB41(iVar1,1);
      uVar2 = DAT_0066a798_1;
      uRam0066a79a = SUB41(iVar1,2);
      uVar3 = uRam0066a79a;
      uRam0066a79b = SUB41(iVar1,3);
      uVar4 = uRam0066a79b;
      self->S7[2].ID = DAT_0066a798;
      _DAT_0066a798 = iVar10;
      self->S7[2].field4_0xd = uVar2;
      self->S7[2].field5_0xe = uVar3;
      self->S7[2].field6_0xf = uVar4;
      self->PhysicsFlags = 0;
      *(undefined2 *)((int)&self->S7[3].PedInDoor + 2) = 0;
      iVar10 = iVar1;
    }
    BYTE_0066a3c1 = 0;
    BYTE_0066a3c2 = 0;
    DAT_0066a3c3 = 0;
    return (byte)iVar10;
  case 0x24:
    self->S7[0].doorState = 1;
    return bVar6;
  }
  self->S7[0].doorState = 1;
  self->PhysicsFlags = 0;
  DAT_0066a3c3 = 0;
  BYTE_0066a3c1 = 1;
  BYTE_0066a3c2 = 1;
  return (byte)iVar8;
}


// 0x004958e0: GameObject::FUN_004958e0
// IDA: sub_4958E0
// Ghidra: GameObject::FUN_004958e0
byte gta2::GameObject_FUN_004958e0(struct GameObject *self)
{
  byte *this_00;
  struct Ped *this_01;
  byte in_AL;
  bool bVar2;
  uint uVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  byte bVar1;
  
  if ((self->ModelId != 9) && (self->S7[0].doorState != 0xf)) {
    gta2::GameObject_sub_491EC0(self);
    this_01 = (struct Ped *)self->ScriptRef;
    bVar1 = gta2::Ped_sub_433CA0(this_01);
    uVar3 = (uint)bVar1;
    if ((bVar1 != 0) &&
       (uVar3._0_1_ = this_01->CurrentAction, uVar3._1_1_ = this_01->DamageState
       , uVar3._2_1_ = this_01->uns60, uVar3._3_1_ = this_01->uns61,
       (uVar3 & 0x200) != 0)) {
      bVar1 = 4;
      if (self->PhysicsFlags == 4) {
        gta2::Ped_PedPunchPed(this_01);
        return bVar1;
      }
      self->PhysicsFlags = 4;
      *(undefined1 *)&self->CollisionData = 0;
      return 4;
    }
    in_AL = (byte)uVar3;
    if ((self->PhysicsFlags != 4) || (*(char *)&self->CollisionData == '\x06'))
    {
      this_00 = &self->S7[2].ID;
      bVar2 = gta2::Car_IsTrainOrTrainCarriage((struct Car *)this_00,(struct Car *)&DAT_0066a634);
      if (CONCAT31(extraout_var,bVar2) != 0) {
        bVar2 = gta2::Car_sub_403800((struct Car *)this_00,(int *)&DAT_0066a574);
        bVar2 = CONCAT31(extraout_var_00,bVar2) != 0;
        self->PhysicsFlags = (uint)bVar2;
        return bVar2;
      }
      self->PhysicsFlags = 2;
      in_AL = 0;
    }
  }
  return in_AL;
}


// 0x00495980: GameObject::sub_495980
// IDA: GameObject::sub_495980
// Ghidra: FUN_00495980
undefined1 gta2::GameObject_sub_495980(void *self,Car *param_1)
{
  uint uVar1;
  struct Car *pCVar2;
  byte bVar3;
  char cVar4;
  bool bVar5;
  undefined1 uVar6;
  int iVar7;
  void *this_00;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined3 extraout_var;
  struct Car *pCVar12;
  undefined1 *puVar13;
  undefined4 uVar14;
  undefined1 local_11;
  int local_10;
  int local_c;
  int local_8;
  SpawnPoint *local_4;
  
  iVar10 = *(int *)((int)self + 0x80);
  local_c = *(int *)(iVar10 + 0x14);
  local_10 = *(int *)(iVar10 + 0x18);
  local_4 = (SpawnPoint *)(iVar10 + 0x1c);
  local_8._0_1_ = local_4->field0_0x0;
  local_8._1_1_ = local_4->field1_0x1;
  local_8._2_1_ = local_4->field2_0x2;
  local_8._3_1_ = local_4->field3_0x3;
  iVar7 = DecoderFloat(&local_8);
  iVar7 = iVar7 + -1;
  this_00 = gta2::Player_sub_401B40(local_4,(GlassInfo *)&local_4,(struct S127 *)&DAT_0066a46c);
  iVar8 = DecoderFloat(this_00);
  iVar9 = DecoderFloat((void *)(iVar10 + 0x18));
  iVar10 = DecoderFloat((void *)(iVar10 + 0x14));
  bVar3 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct,iVar10,iVar9,iVar8);
  if (bVar3 != 0) {
    iVar7 = DecoderFloat(&local_8);
  }
  pCVar2 = param_1;
  puVar13 = &local_11;
  uVar14 = 0;
  pCVar12 = param_1;
  iVar10 = DecoderFloat(&local_8);
  iVar8 = DecoderFloat(&local_10);
  iVar9 = DecoderFloat(&local_c);
  cVar4 = FUN_004656d0(iVar9,iVar8,iVar10,pCVar12,puVar13,uVar14);
  iVar10 = local_8;
  if (cVar4 != '\0') {
    DAT_00593228 = pCVar2;
    return 0;
  }
  if (DAT_0066a3c7 != '\0') {
    gta2::SpriteS1_sub_420600(*(Sprite **)((int)self + 0x80),_DAT_0066a44c,
                        _DAT_0066a7a0,local_8);
    gta2::GameObject_sub_494180((struct GameObject *)self);
    cVar4 = gta2::SpriteS1_sub_4BD670(*(SpriteS1 **)((int)self + 0x80));
    if (cVar4 != '\0') {
      DAT_00593228 = pCVar2;
      gta2::SpriteS1_sub_420600(*(Sprite **)((int)self + 0x80),local_c,local_10,iVar10
                         );
      FUN_00492130();
      return 0;
    }
    gta2::SpriteS1_sub_420600(*(Sprite **)((int)self + 0x80),local_c,local_10,iVar10);
    gta2::GameObject_sub_494180((struct GameObject *)self);
  }
  switch(pCVar2) {
  case (struct Car *)0x1:
    iVar10 = DecoderFloat(&local_10);
    iVar10 = iVar10 + -1;
    iVar8 = DecoderFloat(&local_c);
    break;
  case (struct Car *)0x2:
    iVar10 = DecoderFloat(&local_10);
    iVar10 = iVar10 + 1;
    iVar8 = DecoderFloat(&local_c);
    break;
  case (struct Car *)0x3:
    iVar10 = DecoderFloat(&local_10);
    iVar8 = DecoderFloat(&local_c);
    iVar8 = iVar8 + 1;
    break;
  case (struct Car *)0x4:
    iVar10 = DecoderFloat(&local_10);
    iVar8 = DecoderFloat(&local_c);
    iVar8 = iVar8 + -1;
    break;
  default:
    goto switchD_00495ae7_caseD_4;
  }
  bVar3 = gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct,iVar8,iVar10,iVar7);
  if (bVar3 != 0) {
    if ((bVar3 != 0) && (bVar3 < 5)) {
      return 1;
    }
    return 0;
  }
switchD_00495ae7_caseD_4:
  uVar1 = *(uint *)((int)self + 0x58);
  if ((uVar1 & 1) != 0) {
    puVar11 = (undefined4 *)FUN_0042a630(&local_4,&local_8);
    param_1 = (struct Car *)*puVar11;
    bVar5 = gta2::Point2D_FUN_004037e0((Point2D *)&param_1,(struct SpriteS1 *)&DAT_0066a49c)
    ;
    if (CONCAT31(extraout_var,bVar5) != 0) {
      *(uint *)((int)self + 0x58) = uVar1 & 0xfffffffe;
      uVar6 = FUN_00492190(self,pCVar2);
      *(uint *)((int)self + 0x58) = *(uint *)((int)self + 0x58) | 1;
      return uVar6;
    }
    bVar5 = gta2::Ped_IsSearchType(*(Ped **)((int)self + 0x7c),
                               SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
    if (!bVar5) {
      return 0;
    }
  }
  return 1;
}


// 0x00495bf0: GameObject::sub_495BF0
// IDA: GameObject::sub_495BF0
// Ghidra: GameObject::FUN_00495bf0
char gta2::GameObject_sub_495BF0(struct GameObject *self,char param_1,char param_2)
{
  struct Player *pPVar1;
  undefined1 uVar2;
  struct Player *pPVar3;
  bool bVar4;
  bool bVar5;
  struct SpriteS1 *pSVar6;
  struct S127 *pSVar7;
  int iVar8;
  int iVar9;
  void *pvVar10;
  undefined4 *puVar11;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  char cVar12;
  char cVar13;
  undefined4 uVar14;
  struct Car *pCVar15;
  char local_18;
  undefined4 local_14;
  undefined4 local_10 [3];
  undefined1 local_4 [4];
  
  bVar5 = true;
  iVar8 = *(int *)&self->AIState;
  bVar4 = true;
  local_14 = *(undefined4 *)(iVar8 + 0x14);
  local_10[0] = *(undefined4 *)(iVar8 + 0x18);
  pPVar3 = *(Player **)(iVar8 + 0x1c);
  uVar2 = *(undefined1 *)((int)&self->S7[3].PedInDoor + 1);
  DAT_0066a3c7 = 1;
  gta2::sub_41FC20((struct CarSystemManager *)(local_10 + 2),&DAT_0066a3fc,
             (GlassInfo *)&DAT_0066a640,(struct Ped *)(local_10 + 1),
             (struct Ped *)(local_10 + 2));
  pSVar6 = gta2::S202_sub_401B20((Point2D *)(local_10 + 1),(struct SpriteS1 *)local_4,
                      (struct S127 *)&DAT_0066a480);
  _DAT_0066a44c = pSVar6->FirstElement;
  pSVar6 = gta2::S202_sub_401B20((Point2D *)(local_10 + 2),(struct SpriteS1 *)local_4,
                      (struct S127 *)&DAT_0066a74c);
  _DAT_0066a7a0 = pSVar6->FirstElement;
  pSVar7 = (struct S127 *)gta2::sub_401B90((struct Player *)&DAT_0066a780,local_4,
                              (int *)&DAT_0066a54c);
  pSVar6 = gta2::S202_sub_401B20((Point2D *)&DAT_0066a44c,(struct SpriteS1 *)(local_10 + 2),pSVar7
                     );
  iVar8 = DecoderFloat(pSVar6);
  iVar9 = FUN_00491ee0(&local_14);
  cVar12 = (char)iVar8 - (char)iVar9;
  if (cVar12 == '\0') {
    pSVar7 = (struct S127 *)gta2::sub_401B90((struct Player *)&DAT_0066a780,local_4,
                                (int *)&DAT_0066a54c);
    pvVar10 = gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a44c,(GlassInfo *)(local_10 + 2)
                         ,pSVar7);
    iVar8 = DecoderFloat(pvVar10);
    iVar9 = FUN_00491ee0(&local_14);
    cVar12 = (char)iVar8 - (char)iVar9;
    if (cVar12 == '\0') {
      bVar5 = false;
    }
  }
  pSVar7 = (struct S127 *)gta2::sub_401B90((struct Player *)&DAT_0066a780,local_4,
                              (int *)&DAT_0066a54c);
  pSVar6 = gta2::S202_sub_401B20((Point2D *)&DAT_0066a7a0,(struct SpriteS1 *)(local_10 + 2),pSVar7
                     );
  iVar8 = DecoderFloat(pSVar6);
  iVar9 = FUN_00491ee0(local_10);
  local_18 = (char)iVar8 - (char)iVar9;
  if (local_18 == '\0') {
    pSVar7 = (struct S127 *)gta2::sub_401B90((struct Player *)&DAT_0066a780,local_4,
                                (int *)&DAT_0066a54c);
    pvVar10 = gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a7a0,(GlassInfo *)(local_10 + 2)
                         ,pSVar7);
    iVar8 = DecoderFloat(pvVar10);
    iVar9 = FUN_00491ee0(local_10);
    local_18 = (char)iVar8 - (char)iVar9;
    if (local_18 == '\0') {
      bVar4 = false;
    }
  }
  if ((bVar5) || (bVar4)) {
    if (cVar12 != '\0') goto LAB_00495dd3;
  }
  else {
    iVar8 = *(int *)&self->AIState;
    iVar9 = FUN_00491ee0((void *)(iVar8 + 0x14));
    cVar12 = param_1 - (char)iVar9;
    iVar8 = FUN_00491ee0((void *)(iVar8 + 0x18));
    local_18 = param_2 - (char)iVar8;
    if (cVar12 != '\0') {
LAB_00495dd3:
      if (local_18 == '\0') {
        if (cVar12 != '\0') {
          if (cVar12 != -1) {
            cVar12 = FUN_00495980(self,(struct Car *)0x3);
            return cVar12;
          }
          cVar12 = FUN_00495980(self,(struct Car *)0x4);
          return cVar12;
        }
        goto LAB_004964e6;
      }
      pvVar10 = (void *)(*(int *)&self->AIState + 0x14);
      cVar13 = '\x01';
      if (cVar12 == -1) {
        if (local_18 == -1) {
          FUN_00491f00(pvVar10);
          if ((*(byte *)&self->MaxHealth & 1) != 0) {
            puVar11 = (undefined4 *)
                      gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct,(float10 *)&param_1,
                                 *(float10 **)(*(int *)&self->AIState + 0x14),
                                 *(float10 **)(*(int *)&self->AIState + 0x18));
            *(undefined4 *)(*(int *)&self->AIState + 0x1c) = *puVar11;
          }
          pPVar1 = (struct Player *)(*(int *)&self->AIState + 0x1c);
          bVar5 = gta2::Player_IsCurrentPlayer(pPVar1,(struct Player *)&DAT_0066a4d8);
          if (CONCAT31(extraout_var,bVar5) != 0) {
            pPVar1->CurrentPlayer = pPVar3;
          }
          cVar12 = FUN_00495980(self,(struct Car *)0x1);
          if ((cVar12 == '\0') &&
             (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
             cVar12 == '\0')) {
            DAT_00593228 = 1;
            cVar13 = '\0';
          }
          *(undefined4 *)(*(int *)&self->AIState + 0x14) = local_14;
          FUN_00491f00((void *)(*(int *)&self->AIState + 0x18));
          if ((*(byte *)&self->MaxHealth & 1) != 0) {
            puVar11 = (undefined4 *)
                      gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct,(float10 *)&param_1,
                                 *(float10 **)(*(int *)&self->AIState + 0x14),
                                 *(float10 **)(*(int *)&self->AIState + 0x18));
            *(undefined4 *)(*(int *)&self->AIState + 0x1c) = *puVar11;
          }
          pPVar1 = (struct Player *)(*(int *)&self->AIState + 0x1c);
          bVar5 = gta2::Player_IsCurrentPlayer(pPVar1,(struct Player *)&DAT_0066a4d8);
          if (CONCAT31(extraout_var_00,bVar5) != 0) {
            pPVar1->CurrentPlayer = pPVar3;
          }
          uVar14 = 4;
          cVar12 = FUN_00495980(self,(struct Car *)0x4);
          if ((cVar12 == '\0') &&
             (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
             cVar12 == '\0')) {
            DAT_00593228 = 4;
            cVar13 = '\0';
          }
          *(undefined4 *)(*(int *)&self->AIState + 0x14) = local_14;
          pCVar15 = (struct Car *)0x4;
          *(undefined4 *)(*(int *)&self->AIState + 0x18) = local_10[0];
          *(Player **)(*(int *)&self->AIState + 0x1c) = pPVar3;
          if (cVar13 != '\0') {
            cVar12 = FUN_00495980(self,(struct Car *)0x4);
            if ((cVar12 == '\0') &&
               (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
               cVar12 == '\0')) {
              cVar13 = '\0';
              DAT_00593228 = 4;
            }
            pCVar15 = (struct Car *)0x1;
            goto LAB_00495f8d;
          }
LAB_00495f28:
          _DAT_0066a44c = _DAT_0066a480;
          _DAT_0066a7a0 = _DAT_0066a74c;
          cVar12 = FUN_00495980(self,pCVar15);
          if ((cVar12 == '\0') &&
             (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
             cVar12 == '\0')) goto LAB_0049645f;
          DAT_00593228 = 1;
          pCVar15 = (struct Car *)0x1;
        }
        else {
          FUN_00491f00(pvVar10);
          if ((*(byte *)&self->MaxHealth & 1) != 0) {
            puVar11 = (undefined4 *)
                      gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct,(float10 *)&param_1,
                                 *(float10 **)(*(int *)&self->AIState + 0x14),
                                 *(float10 **)(*(int *)&self->AIState + 0x18));
            *(undefined4 *)(*(int *)&self->AIState + 0x1c) = *puVar11;
          }
          pPVar1 = (struct Player *)(*(int *)&self->AIState + 0x1c);
          bVar5 = gta2::Player_IsCurrentPlayer(pPVar1,(struct Player *)&DAT_0066a4d8);
          if (CONCAT31(extraout_var_01,bVar5) != 0) {
            pPVar1->CurrentPlayer = pPVar3;
          }
          cVar12 = FUN_00495980(self,(struct Car *)0x2);
          if ((cVar12 == '\0') &&
             (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
             cVar12 == '\0')) {
            DAT_00593228 = 2;
            cVar13 = '\0';
          }
          *(undefined4 *)(*(int *)&self->AIState + 0x14) = local_14;
          FUN_00491ef0((void *)(*(int *)&self->AIState + 0x18));
          if ((*(byte *)&self->MaxHealth & 1) != 0) {
            puVar11 = (undefined4 *)
                      gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct,(float10 *)&param_1,
                                 *(float10 **)(*(int *)&self->AIState + 0x14),
                                 *(float10 **)(*(int *)&self->AIState + 0x18));
            *(undefined4 *)(*(int *)&self->AIState + 0x1c) = *puVar11;
          }
          pPVar1 = (struct Player *)(*(int *)&self->AIState + 0x1c);
          bVar5 = gta2::Player_IsCurrentPlayer(pPVar1,(struct Player *)&DAT_0066a4d8);
          if (CONCAT31(extraout_var_02,bVar5) != 0) {
            pPVar1->CurrentPlayer = pPVar3;
          }
          uVar14 = 4;
          cVar12 = FUN_00495980(self,(struct Car *)0x4);
          if ((cVar12 == '\0') &&
             (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
             cVar12 == '\0')) {
            DAT_00593228 = 4;
            cVar13 = '\0';
          }
          *(undefined4 *)(*(int *)&self->AIState + 0x14) = local_14;
          pCVar15 = (struct Car *)0x4;
          *(undefined4 *)(*(int *)&self->AIState + 0x18) = local_10[0];
          *(Player **)(*(int *)&self->AIState + 0x1c) = pPVar3;
          if (cVar13 != '\0') goto LAB_00496478;
          _DAT_0066a44c = _DAT_0066a480;
          _DAT_0066a7a0 = _DAT_0066a74c;
          cVar12 = FUN_00495980(self,(struct Car *)0x4);
          if ((cVar12 == '\0') &&
             (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
             cVar12 == '\0')) {
            DAT_00593228 = 4;
            *(undefined1 *)((int)&self->S7[3].PedInDoor + 1) = uVar2;
            return '\0';
          }
LAB_00496433:
          DAT_00593228 = 2;
          pCVar15 = (struct Car *)0x2;
        }
        cVar13 = '\x01';
        cVar12 = FUN_00495980(self,pCVar15);
        if ((cVar12 != '\0') ||
           (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
           cVar12 != '\0')) {
LAB_0049645f:
          DAT_00593228 = uVar14;
          *(undefined1 *)((int)&self->S7[3].PedInDoor + 1) = uVar2;
          return cVar13;
        }
      }
      else if (local_18 == -1) {
        FUN_00491ef0(pvVar10);
        if ((*(byte *)&self->MaxHealth & 1) != 0) {
          puVar11 = (undefined4 *)
                    gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct,(float10 *)&param_1,
                               *(float10 **)(*(int *)&self->AIState + 0x14),
                               *(float10 **)(*(int *)&self->AIState + 0x18));
          *(undefined4 *)(*(int *)&self->AIState + 0x1c) = *puVar11;
        }
        pPVar1 = (struct Player *)(*(int *)&self->AIState + 0x1c);
        bVar5 = gta2::Player_IsCurrentPlayer(pPVar1,(struct Player *)&DAT_0066a4d8);
        if (CONCAT31(extraout_var_03,bVar5) != 0) {
          pPVar1->CurrentPlayer = pPVar3;
        }
        cVar12 = FUN_00495980(self,(struct Car *)0x1);
        if ((cVar12 == '\0') &&
           (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
           cVar12 == '\0')) {
          DAT_00593228 = 1;
          cVar13 = '\0';
        }
        *(undefined4 *)(*(int *)&self->AIState + 0x14) = local_14;
        FUN_00491f00((void *)(*(int *)&self->AIState + 0x18));
        if ((*(byte *)&self->MaxHealth & 1) != 0) {
          puVar11 = (undefined4 *)
                    gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct,(float10 *)&param_1,
                               *(float10 **)(*(int *)&self->AIState + 0x14),
                               *(float10 **)(*(int *)&self->AIState + 0x18));
          *(undefined4 *)(*(int *)&self->AIState + 0x1c) = *puVar11;
        }
        pPVar1 = (struct Player *)(*(int *)&self->AIState + 0x1c);
        bVar5 = gta2::Player_IsCurrentPlayer(pPVar1,(struct Player *)&DAT_0066a4d8);
        if (CONCAT31(extraout_var_04,bVar5) != 0) {
          pPVar1->CurrentPlayer = pPVar3;
        }
        uVar14 = 3;
        cVar12 = FUN_00495980(self,(struct Car *)0x3);
        if ((cVar12 == '\0') &&
           (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
           cVar12 == '\0')) {
          DAT_00593228 = 3;
          cVar13 = '\0';
        }
        *(undefined4 *)(*(int *)&self->AIState + 0x14) = local_14;
        pCVar15 = (struct Car *)0x3;
        *(undefined4 *)(*(int *)&self->AIState + 0x18) = local_10[0];
        *(Player **)(*(int *)&self->AIState + 0x1c) = pPVar3;
        if (cVar13 == '\0') goto LAB_00495f28;
        cVar12 = FUN_00495980(self,(struct Car *)0x3);
        if ((cVar12 == '\0') &&
           (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
           cVar12 == '\0')) {
          cVar13 = '\0';
          DAT_00593228 = 3;
        }
        cVar12 = FUN_00495980(self,(struct Car *)0x1);
        if ((cVar12 != '\0') ||
           (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
           cVar12 != '\0')) goto LAB_00495fb3;
        DAT_00593228 = 1;
      }
      else {
        FUN_00491ef0(pvVar10);
        if ((*(byte *)&self->MaxHealth & 1) != 0) {
          puVar11 = (undefined4 *)
                    gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct,(float10 *)&param_1,
                               *(float10 **)(*(int *)&self->AIState + 0x14),
                               *(float10 **)(*(int *)&self->AIState + 0x18));
          *(undefined4 *)(*(int *)&self->AIState + 0x1c) = *puVar11;
        }
        pPVar1 = (struct Player *)(*(int *)&self->AIState + 0x1c);
        bVar5 = gta2::Player_IsCurrentPlayer(pPVar1,(struct Player *)&DAT_0066a4d8);
        if (CONCAT31(extraout_var_05,bVar5) != 0) {
          pPVar1->CurrentPlayer = pPVar3;
        }
        cVar12 = FUN_00495980(self,(struct Car *)0x2);
        if ((cVar12 == '\0') &&
           (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
           cVar12 == '\0')) {
          DAT_00593228 = 2;
          cVar13 = '\0';
        }
        *(undefined4 *)(*(int *)&self->AIState + 0x14) = local_14;
        *(Player **)(*(int *)&self->AIState + 0x1c) = pPVar3;
        FUN_00491ef0((void *)(*(int *)&self->AIState + 0x18));
        puVar11 = (undefined4 *)
                  gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct,(float10 *)&param_1,
                             *(float10 **)(*(int *)&self->AIState + 0x14),
                             *(float10 **)(*(int *)&self->AIState + 0x18));
        *(undefined4 *)(*(int *)&self->AIState + 0x1c) = *puVar11;
        pPVar1 = (struct Player *)(*(int *)&self->AIState + 0x1c);
        bVar5 = gta2::Player_IsCurrentPlayer(pPVar1,(struct Player *)&DAT_0066a4d8);
        if (CONCAT31(extraout_var_06,bVar5) != 0) {
          pPVar1->CurrentPlayer = pPVar3;
        }
        uVar14 = 3;
        cVar12 = FUN_00495980(self,(struct Car *)0x3);
        if ((cVar12 == '\0') &&
           (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
           cVar12 == '\0')) {
          DAT_00593228 = 3;
          cVar13 = '\0';
        }
        *(undefined4 *)(*(int *)&self->AIState + 0x14) = local_14;
        pCVar15 = (struct Car *)0x3;
        *(undefined4 *)(*(int *)&self->AIState + 0x18) = local_10[0];
        *(Player **)(*(int *)&self->AIState + 0x1c) = pPVar3;
        if (cVar13 == '\0') {
          _DAT_0066a44c = _DAT_0066a480;
          _DAT_0066a7a0 = _DAT_0066a74c;
          cVar12 = FUN_00495980(self,(struct Car *)0x3);
          if (cVar12 == '\0') {
            cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct);
            cVar13 = '\0';
            if (cVar12 == '\0') goto LAB_0049645f;
          }
          goto LAB_00496433;
        }
LAB_00496478:
        cVar12 = FUN_00495980(self,pCVar15);
        if ((cVar12 == '\0') &&
           (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
           cVar12 == '\0')) {
          cVar13 = '\0';
          DAT_00593228 = uVar14;
        }
        pCVar15 = (struct Car *)0x2;
LAB_00495f8d:
        cVar12 = FUN_00495980(self,pCVar15);
        if ((cVar12 != '\0') ||
           (cVar12 = gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct),
           cVar12 != '\0')) goto LAB_00495fb3;
        DAT_00593228 = 2;
      }
      cVar13 = '\0';
LAB_00495fb3:
      *(undefined1 *)((int)&self->S7[3].PedInDoor + 1) = uVar2;
      return cVar13;
    }
    if (local_18 == '\0') {
      return '\x01';
    }
  }
  if (local_18 == -1) {
    cVar12 = FUN_00495980(self,(struct Car *)0x1);
    return cVar12;
  }
LAB_004964e6:
  cVar12 = FUN_00495980(self,(struct Car *)0x2);
  return cVar12;
}


// 0x00496800: GameObject::sub_496800
// IDA: GameObject::sub_496800
// Ghidra: GameObject::FUN_00496800
byte gta2::GameObject_sub_496800(struct GameObject *self)
{
  undefined1 uVar1;
  char cVar2;
  byte bVar3;
  uint uVar4;
  
  uVar4 = 7;
  if (self->PhysicsFlags != 7) {
    self->PhysicsFlags = 7;
    *(undefined1 *)&self->CollisionData = 0;
    uVar1 = gta2::Ped_GetAnimationState((struct Ped *)self->ScriptRef);
    cVar2 = FUN_004224a0(uVar1);
    if (cVar2 == '\0') {
      uVar4 = self->MaxHealth & 0xffffffef;
    }
    else {
      uVar4 = self->MaxHealth | 0x10;
    }
    self->MaxHealth = uVar4;
    self->BehaviorFlags = 0;
  }
  bVar3 = (byte)uVar4;
  if (self->S7[0].doorState == 0xf) {
    gta2::Ped_UpdatePedState((struct Ped *)self->ScriptRef,PEDSTATE_MOVE_TURN);
    bVar3 = gta2::Ped_sub_4332B0((struct Ped *)self->ScriptRef,0);
  }
  gta2::GameObject_sub_491E40(self);
  if (bVar3 != 0) {
    gta2::Ped_sub_433220((struct Ped *)self->ScriptRef);
    bVar3 = gta2::GameObject_sub_4938A0(self);
    return bVar3;
  }
  return 0;
}


// 0x00496880: GameObject::sub_496880
// IDA: GameObject::sub_496880
// Ghidra: ---
void gta2::GameObject_sub_496880(struct GameObject *self)
{
  struct Ped *Ped; // ecx
  int v3; // edx
  int v4; // eax
  struct SpriteS1 *v5; // ecx
  __int16 v6; // cx
  int Speed; // edx
  struct SpriteS1 *FirstElement; // edi
  struct SpriteS1 *SpriteS1; // edi
  int *v10; // ebx
  struct SpriteS1 *p_NextWeapon; // eax
  int *v12; // eax
  struct Ped *v13; // ecx
  int v14; // eax
  struct SpriteS1 *v15; // edi
  struct S900 *v16; // eax
  int PositionZ; // ecx
  int PositionY; // edx
  struct SpriteS1 *v19; // ecx
  struct Ped *v20; // eax
  struct Ped *v21; // edi
  int v22; // eax
  int v23; // eax
  struct SpriteS1 *v24; // eax
  struct Car *GetVehicle; // ebp
  int *v26; // ebx
  struct SpriteS1 *v27; // edi
  struct PublicTransport *v28; // ecx
  int v29; // eax
  int v30; // eax
  int v31; // eax
  struct SpriteS1 *v32; // eax
  struct SpriteS1 *v33; // edi
  struct PublicTransport *v34; // ecx
  int *v35; // ebx
  int v36; // edx
  struct Ped *v37; // ecx
  struct SpriteS1 *v38; // eax
  struct S900 *v39; // ecx
  int v40; // edi
  struct Ped *v41; // edi
  int _433B60; // eax
  struct SpriteS1 *v43; // ecx
  struct SpriteS1 *v44; // eax
  struct Ped *v45; // ecx
  struct SpriteS1 *v46; // edi
  struct SpriteS1 *v47; // eax
  struct SpriteS1 *v48; // ecx
  int v49; // eax
  struct Ped *v50; // ecx
  int v51; // eax
  struct Ped *v52; // ecx
  char v53; // al
  __int16 CigaretteIdleTimer; // ax
  void *v55; // ecx
  struct Ped *v56; // edx
  struct SpriteS1 **v57; // eax
  int *v58; // eax
  struct Ped *v59; // edi
  int *v60; // eax
  struct CarSystemManager *v61; // ecx
  int v62; // eax
  int v63; // eax
  struct SpriteS1 *v64; // edi
  int *v65; // ebx
  int *v66; // eax
  struct Ped *v67; // eax
  struct Ped *v68; // edx
  int v69; // [esp-8h] [ebp-54h]
  PublicTransport *v70[5]; // [esp-4h] [ebp-50h] BYREF
  struct SpriteS1 *a3; // [esp+10h] [ebp-3Ch] BYREF
  Weapon y; // [esp+14h] [ebp-38h] BYREF
  int v73; // [esp+44h] [ebp-8h] BYREF
  int v74; // [esp+48h] [ebp-4h] BYREF

  Ped = self->Ped_;
  y.SMG = 0;
  y.field_8 = 0;
  gta2::Ped_sub_403A40(Ped);
  v4 = self->field_C;
  if ( self->field_16 == 1 )
  {
    self->field_16 = 0;
    switch ( v4 )
    {
      case 17:
        self->field_6C = 8;
        self->field_68 = 0;
        break;
      case 19:
        Speed = self->Speed;
        self->field_6C = 11;
        self->Speed1 = Speed;
        self->field_94 = *(_DWORD *)&unk_66A4D8.Ammo;
        self->field_68 = 0;
        gta2::sub_4937D0((struct SpriteS1 *)unk_66A480.CurrentElement);
        v70[0] = (struct PublicTransport *)&y.field_8;
        gta2::sub_493810((struct SpriteS1 *)unk_66A74C);
        FirstElement = unk_66A510.FirstElement;
        *(_DWORD *)&y.Ammo = *(_DWORD *)&unk_66A4D8.Ammo;
        a3 = *(SpriteS1 **)&unk_66A4D8.Ammo;
        if ( SLOWORD(y.SMG) < 10 )
          *(_DWORD *)&y.Ammo = unk_66A510.FirstElement;
        if ( SLOWORD(y.SMG) > 54 )
          *(_DWORD *)&y.Ammo = gta2::JustCopyByPtrAtoC(&unk_66A510, (struct SpriteS1 *)&y.field_C)->FirstElement;
        if ( SLOWORD(y.field_8) < 10 )
          a3 = FirstElement;
        if ( SLOWORD(y.field_8) > 54 )
          a3 = gta2::JustCopyByPtrAtoC(&unk_66A510, (struct SpriteS1 *)&y.short)->FirstElement;
        SpriteS1 = self->SpriteS1_;
        v10 = (int *)gta2::S202_sub_401B20(
                       (struct S202 *)&SpriteS1->S3_arr5031[0].PositionY,
                       (struct SpriteS1 *)&y.Car,
                       (struct PublicTransport *)&a3);
        v70[0] = (struct PublicTransport *)&y;
        p_NextWeapon = (struct SpriteS1 *)&y.NextWeapon;
        goto LABEL_21;
      case 20:
        self->field_6C = 2;
        self->field_46 = 10;
        break;
      case 22:
        self->field_48 = gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) ? 20 : 60;
        if ( self->field_10 == 33 )
        {
          if ( self->field_6C == 15 )
            goto LABEL_11;
          self->field_6C = 15;
          goto LABEL_10;
        }
        if ( self->field_10 != 34 )
        {
          v5 = self->SpriteS1_;
          v70[0] = (struct PublicTransport *)6;
          self->field_6C = 10;
          gta2::SpriteS1_sub_40F7B0(v5, (int)v70[0]);
          break;
        }
        if ( self->field_6C != 16 )
        {
          v6 = *(_WORD *)gta2::sub_40E5A0((struct CarSystemManager *)&self->Rotation, (struct CarSystemManager *)&a3, &unk_66A5F4);
          self->field_6C = 16;
          self->Rotation = v6;
LABEL_10:
          self->field_68 = 0;
        }
LABEL_11:
        gta2::SpriteS1_sub_40F7B0(self->SpriteS1_, 6);
        break;
      case 24:
      case 25:
      case 26:
        v13 = self->Ped_;
        v14 = *(_DWORD *)&v13->field_123;
        if ( !v14 || !*(_DWORD *)(v14 + 16) || !*(_DWORD *)(v14 + 4) )
          goto LABEL_80;
        self->field_6C = 12;
        gta2::SpriteS1_sub_420600(
          self->SpriteS1_,
          *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v13->field_123 + 4) + 20),
          *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v13->field_123 + 4) + 24),
          *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v13->field_123 + 4) + 28));
        if ( self->field_C != 24 )
          self->Rotation = **(_WORD **)(*(_DWORD *)&self->Ped_->field_123 + 4);
        if ( !*(_DWORD *)(*(_DWORD *)(*(_DWORD *)&self->Ped_->field_123 + 16) + 52) )
          gta2::SpriteS1_sub_40F7B0(self->SpriteS1_, 6);
        self->CigaretteIdleTimer = 300;
        break;
      case 27:
        self->field_6C = 17;
        self->field_68 = 0;
        self->field_46 = 0;
        break;
      default:
        break;
    }
  }
  else
  {
    switch ( v4 )
    {
      case 17:
        LOBYTE(v3) = self->Ped_->field_1E8;
        if ( !gta2::Car_sub_425A40(self->GetVehicle, v3) )
          self->field_68 = 3;
        if ( self->field_68 == 3 )
        {
          if ( self->GetVehicle->Player_ )
          {
            v24 = gta2::JustCopyByPtrAtoC(&unk_66A6B8, (struct SpriteS1 *)&y.short);
            GetVehicle = self->GetVehicle;
            v26 = (int *)v24;
            gta2::Player_sub_4211A0(GetVehicle->Player_, &y.field_C);
            v27 = self->SpriteS1_;
            v70[0] = v28;
            y.field_8 = v29;
            gta2::bitShiftLeft1(v70, 0);
            HIWORD(v30) = HIWORD(*v26);
            LOWORD(v30) = v27->FirstElement;
            gta2::sub_4854C0(
              gObject,
              (struct S900 *)0x6E,
              v27->S3_arr5031[0].PositionX,
              v27->S3_arr5031[0].PositionY,
              v27->S3_arr5031[0].PositionZ,
              (__int16)GetVehicle->CarSprite->FirstElement,
              v30,
              *(Ped **)y.field_8,
              *v26,
              (int)v70[0]);
          }
          else
          {
            v32 = gta2::JustCopyByPtrAtoC(&unk_66A6B8, (struct SpriteS1 *)&y.TypeWeapon);
            v33 = self->SpriteS1_;
            v70[0] = v34;
            v35 = (int *)v32;
            gta2::bitShiftLeft1(v70, 0);
            LOWORD(v36) = v33->FirstElement;
            gta2::sub_4854C0(
              gObject,
              (struct S900 *)0x6E,
              v33->S3_arr5031[0].PositionX,
              v33->S3_arr5031[0].PositionY,
              v33->S3_arr5031[0].PositionZ,
              (__int16)self->GetVehicle->CarSprite->FirstElement,
              v36,
              (struct Ped *)unk_66A510.FirstElement,
              *v35,
              (int)v70[0]);
          }
          v37 = self->Ped_;
          v70[0] = (struct PublicTransport *)8;
          *(_DWORD *)&v37->field_123 = v31;
          self->Ped_->Flags = 0;
          self->Ped_->field_220 = 0;
          gta2::Ped_UpdatePedState(self->Ped_, (int)v70[0]);
          v38 = self->SpriteS1_;
          LOWORD(v39) = v38->FirstElement;
          gta2::Particles_sub_48C9C0(
            gParticles,
            v38->S3_arr5031[0].PositionX,
            v38->S3_arr5031[0].PositionY,
            v38->S3_arr5031[0].PositionZ,
            v39);
          gta2::Ped_sub_4332B0(self->Ped_, 25);
          self->field_C = 24;
          self->field_6C = 10;
        }
        break;
      case 19:
        v40 = *gta2::MapRelatedStruct_sub_469570(
                 gMapRelatedStruct,
                 &y.field_20,
                 (int *)unk_66A480.CurrentElement,
                 (struct SpriteS1 *)unk_66A74C,
                 (int)unk_66A754);
        y.field_8 = v40;
        if ( gta2::Player_sub_40CE70((struct Player *)&unk_66A754, &y.field_8)
          && (v70[0] = (struct PublicTransport *)gta2::S202_sub_401B20(
                                            (struct S202 *)&y.field_8,
                                            (struct SpriteS1 *)&y.Ped,
                                            (struct PublicTransport *)&unk_66A524),
              gta2::sub_4037E0(&unk_66A754)) )
        {
          self->SpriteS1_->S3_arr5031[0].PositionZ = v40;
          sub_433300(self->Ped_);
          v41 = self->Ped_;
          self->field_8 = gta2::Ped_GetPedState(v41);
          _433B60 = gta2::Ped_Get_433B60(v41);
          v43 = self->SpriteS1_;
          v70[0] = 0;
          self->field_C = _433B60;
          v44 = gta2::S56_sub_447740(gCheckpoint1, v43, (int)v70[0]);
          v45 = self->Ped_;
          v46 = v44;
          if ( self->field_6C == 12 )
          {
            gta2::Ped_sub_433DD0(v45, 27);
            if ( v46 )
            {
              v47 = gta2::JustCopyByPtrAtoC(&unk_66A3E0, (struct SpriteS1 *)&y.SoundWeapon);
              v48 = self->SpriteS1_;
              v49 = (int)v47->FirstElement;
              v70[0] = *(PublicTransport **)&unk_66A4D8.Ammo;
              v69 = v49;
              LOWORD(v49) = v48->FirstElement;
              gta2::sub_4854C0(
                gObject,
                (struct S900 *)0x6E,
                v48->S3_arr5031[0].PositionX,
                v48->S3_arr5031[0].PositionY,
                v48->S3_arr5031[0].PositionZ,
                (__int16)v48->FirstElement,
                v49,
                (struct Ped *)unk_66A3DC.FirstElement,
                v69,
                *(int *)&unk_66A4D8.Ammo);
              v50 = self->Ped_;
              v70[0] = (struct PublicTransport *)8;
              *(_DWORD *)&v50->field_123 = v51;
              gta2::Ped_UpdatePedState(self->Ped_, (int)v70[0]);
              gta2::Ped_sub_4332B0(self->Ped_, 26);
              gta2::Ped_sub_433B50(self->Ped_);
              return;
            }
            v52 = self->Ped_;
            if ( LOWORD(v52->TargetCarDoor1) )
            {
              gta2::GameObject_set_ped_state_1(self, 0);
              gta2::GameObject_sub_433A50(self, 0);
            }
            else
            {
              gta2::Ped_sub_4411B0(v52);
            }
          }
          else
          {
            gta2::Ped_sub_433DD0(v45, 26);
            if ( v46 )
              gta2::GameObject_sub_493710(self);
          }
        }
        else
        {
          gta2::sub_41FC20(&self->Rotation, &self->Rotation);
          gta2::Player_sub_40E530((struct Player *)&y.SMG, (struct Tango *)&unk_66A480);
          gta2::Player_sub_40E530((struct Player *)&y, (struct Tango *)&unk_66A74C);
          LOBYTE(v70[0]) = gta2::Weapon_sub_41C1E0(&y);
          v53 = gta2::Weapon_sub_41C1E0((struct Weapon *)&y.SMG);
          if ( gta2::GameObject_sub_495540(self, v53, (char)v70[0]) )
            gta2::SpriteS1_sub_420600(self->SpriteS1_, y.SMG, *(int *)&y.Ammo, self->SpriteS1_->S3_arr5031[0].PositionZ);
          v70[0] = (struct PublicTransport *)&unk_66A3DC;
          if ( gta2::sub_4037E0(&self->field_94) )
            gta2::Player_sub_40E530((struct Player *)&self->field_94, (struct Tango *)&unk_66A3E0);
          gta2::Weapon_UseAmmo((struct Weapon *)&self->SpriteS1_->S3_arr5031[0].PositionZ, &self->field_94);
          if ( gta2::Car_sub_403800((struct Car *)&self->Speed1, (int)&unk_66A46C) )
            gta2::Weapon_UseAmmo((struct Weapon *)&self->Speed1, &unk_66A6FC);
        }
        break;
      case 20:
        v15 = self->SpriteS1_;
        --self->field_46;
        v16 = (struct S900 *)gta2::sub_40E5A0((struct CarSystemManager *)v15, (struct CarSystemManager *)&a3, &unk_66A5F4);
        LOWORD(v16) = v16->Index;
        PositionZ = v15->S3_arr5031[0].PositionZ;
        PositionY = v15->S3_arr5031[0].PositionY;
        v70[0] = (struct PublicTransport *)1;
        gta2::Particles_sub_48D1F0(gParticles, v15->S3_arr5031[0].PositionX, PositionY, PositionZ, v16);
        if ( (self->field_46 & 1) == 0 )
        {
          v19 = self->SpriteS1_;
          v70[0] = 0;
          gta2::SpriteS1_sub_4BDDD0(v19, unk_66A590, (int)unk_66A590);
        }
        if ( !self->field_46 )
        {
          gta2::Ped_sub_4411B0(self->Ped_);
          gta2::Ped_UpdatePedState(self->Ped_, 9);
          gta2::Ped_sub_4332B0(self->Ped_, 15);
          sub_433300(self->Ped_);
          gta2::SpriteS1_sub_420660(self->SpriteS1_, *(int *)&unk_66A4D8.Ammo);
          LOBYTE(self->Ped_->PositionZ2) &= ~0x20u;
        }
        break;
      case 22:
        if ( !self->field_48 )
        {
          v20 = self->Ped_;
          if ( (v20->PositionX1 & 0x20) == 0 )
          {
            LOWORD(v20->XCoordinate) = 0;
            v21 = self->Ped_;
            if ( v21->Flags == 9 )
            {
              sub_433300(v21);
              if ( !gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY)
                && !gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT) )
              {
                gta2::Ped_PedSetObjective(self->Ped_, 28, 9999);
              }
            }
            else
            {
              if ( gta2::Ped_GetHealth(v21) )
              {
                gta2::Ped_UpdatePedState(v21, 0);
                gta2::Ped_sub_4332B0(self->Ped_, 0);
                sub_433300(self->Ped_);
              }
              else
              {
                gta2::Ped_sub_4411B0(v21);
              }
              self->field_6C = 0;
            }
            gta2::S56_sub_447480(gCheckpoint2, self->SpriteS1_);
            LOWORD(v22) = gta2::Car_sub_403820((struct Car *)&self->Car1, &unk_66A4D8);
            if ( v22 || (LOWORD(v23) = gta2::Car_sub_403820((struct Car *)&self->Car2, &unk_66A4D8), v23) )
            {
              SpriteS1 = self->SpriteS1_;
              v10 = (int *)gta2::S202_sub_401B20(
                             (struct S202 *)&SpriteS1->S3_arr5031[0].PositionY,
                             (struct SpriteS1 *)&y.NextWeapon,
                             (struct PublicTransport *)&self->Car2);
              v70[0] = (struct PublicTransport *)&self->Car1;
              p_NextWeapon = (struct SpriteS1 *)&y.Car;
LABEL_21:
              v12 = (int *)gta2::S202_sub_401B20((struct S202 *)&SpriteS1->S3_arr5031[0].PositionX, p_NextWeapon, v70[0]);
              gta2::SpriteS1_sub_420600(SpriteS1, *v12, *v10, SpriteS1->S3_arr5031[0].PositionZ);
            }
          }
        }
        break;
      case 24:
      case 25:
      case 26:
        CigaretteIdleTimer = self->CigaretteIdleTimer;
        if ( CigaretteIdleTimer )
          self->CigaretteIdleTimer = CigaretteIdleTimer - 1;
        if ( !self->CigaretteIdleTimer )
          self->field_C = 26;
        v55 = *(void **)&self->Ped_->field_123;
        if ( !v55 )
        {
          v13 = self->Ped_;
LABEL_80:
          gta2::Ped_sub_4411B0(v13);
          v56 = self->Ped_;
          self->field_8 = 9;
          self->field_C = 15;
          *(_DWORD *)&v56->field_214 = 9;
          *(_DWORD *)&self->Ped_->ObjectiveTimer = 15;
          return;
        }
        v57 = gta2::sub_4827D0(v55, (SpriteS1 **)&y.field_2C);
        if ( gta2::Player_IsCurrentPlayer((struct Player *)v57, (struct Player *)&unk_66A4D8) || !self->CigaretteIdleTimer )
        {
          switch ( self->field_C )
          {
            case 0x18:
              sub_433300(self->Ped_);
              v59 = self->Ped_;
              self->field_8 = gta2::Ped_GetPedState(v59);
              self->field_C = gta2::Ped_Get_433B60(v59);
              break;
            case 0x19:
              gta2::Ped_UpdatePedState(self->Ped_, 8);
              *(_DWORD *)&self->Ped_->ObjectiveTimer = 22;
              gta2::Ped_sub_433B50(self->Ped_);
              self->field_8 = 8;
              self->field_C = 22;
              break;
            case 0x1A:
              sub_433300(self->Ped_);
              gta2::Ped_sub_4411B0(self->Ped_);
              gta2::Ped_sub_433DD0(self->Ped_, 27);
              break;
          }
          v60 = *(int **)(*(_DWORD *)&self->Ped_->field_123 + 4);
          gta2::SpriteS1_sub_420600(self->SpriteS1_, v60[5], v60[6], v60[7]);
          v61 = (struct CarSystemManager *)self->Ped_;
          LOWORD(v61) = **(_WORD **)(v61[3].RecycledCars_1 + 4);
          gta2::SpriteS1_SetRotation(self->SpriteS1_, v61);
          if ( !*(_DWORD *)(*(_DWORD *)(*(_DWORD *)&self->Ped_->field_123 + 16) + 52) )
            gta2::SpriteS1_sub_40F7B0(self->SpriteS1_, 6);
          gta2::S63_sub_4827B0(*(EventHandler **)&self->Ped_->field_123);
          *(_DWORD *)&self->Ped_->field_123 = 0;
          gta2::GameObject_sub_494180(self);
          if ( gta2::GameObject_sub_491E40(self) )
          {
            gta2::Ped_sub_433220(self->Ped_);
            gta2::GameObject_sub_4938A0(self);
            return;
          }
          gta2::S56_sub_447480(gCheckpoint2, self->SpriteS1_);
          LOWORD(v62) = gta2::Car_sub_403820((struct Car *)&self->Car1, &unk_66A4D8);
          if ( v62 || (LOWORD(v63) = gta2::Car_sub_403820((struct Car *)&self->Car2, &unk_66A4D8), v63) )
          {
            v64 = self->SpriteS1_;
            v65 = (int *)gta2::S202_sub_401B20(
                           (struct S202 *)&v64->S3_arr5031[0].PositionY,
                           (struct SpriteS1 *)&v73,
                           (struct PublicTransport *)&self->Car2);
            v66 = (int *)gta2::S202_sub_401B20(
                           (struct S202 *)&v64->S3_arr5031[0].PositionX,
                           (struct SpriteS1 *)&v74,
                           (struct PublicTransport *)&self->Car1);
            gta2::SpriteS1_sub_420600(v64, *v66, *v65, v64->S3_arr5031[0].PositionZ);
          }
        }
        else
        {
          v58 = *(int **)(*(_DWORD *)&self->Ped_->field_123 + 4);
          gta2::SpriteS1_sub_420600(self->SpriteS1_, v58[5], v58[6], v58[7]);
          if ( self->field_C != 24 )
            self->Rotation = **(_WORD **)(*(_DWORD *)&self->Ped_->field_123 + 4);
          if ( !*(_DWORD *)(*(_DWORD *)(*(_DWORD *)&self->Ped_->field_123 + 16) + 52) )
            gta2::SpriteS1_sub_40F7B0(self->SpriteS1_, 6);
        }
        break;
      case 27:
        ++self->field_46;
        if ( gNetworkGame )
        {
          v67 = self->Ped_;
          if ( v67->PedId )
            LOBYTE(v67->ID) = 99;
        }
        else if ( self->field_46 == 5 )
        {
          gta2::Ped_sub_43D880(self->Ped_);
        }
        if ( self->field_46 > 0x64u )
        {
          if ( !gNetworkGame )
          {
            LOBYTE(self->Ped_->ID) = 0;
            self->Ped_->PedId = 0;
          }
          v68 = self->Ped_;
          self->field_8 = 0;
          self->field_C = 0;
          *(_DWORD *)&v68->ObjectiveTimer = 0;
          *(_DWORD *)&self->Ped_->field_214 = 0;
          LOBYTE(self->Ped_->PositionZ2) &= ~0x20u;
          if ( *(_DWORD *)&self->Ped_->isPlayer )
          {
            gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_SHOCKING);
            gta2::Player_SetPlayerState(*(Player **)&self->Ped_->isPlayer, 4);
          }
          gta2::Ped_sub_4411B0(self->Ped_);
          self->field_8 = 9;
          self->field_C = 15;
          self->field_6C = 21;
          self->field_10 = 1;
        }
        break;
      default:
        break;
    }
  }
  if ( LOWORD(self->Ped_->XCoordinate) < HIWORD(self->Ped_->XCoordinate) )
    --self->field_48;
}


// 0x00497410: GameObject::FUN_00497410
// IDA: sub_497410
// Ghidra: GameObject::FUN_00497410
byte gta2::GameObject_FUN_00497410(struct GameObject *self)
{
  undefined4 local_8;
  undefined4 local_4;
  
  local_8 = 0;
  local_4 = 0;
  gta2::sub_4937D0(self,_DAT_0066a480,(undefined2 *)&local_8);
  gta2::sub_493810(self,_DAT_0066a74c,(undefined2 *)&local_4);
  if ((((0x14 < (short)local_8) && ((short)local_8 < 0x2c)) &&
      (0x14 < (short)local_4)) && ((short)local_4 < 0x2c)) {
    return 1;
  }
  return 0;
}


// 0x00497a60: GameObject::GameObject
// IDA: GameObject::GameObject
// Ghidra: ---
void gta2::GameObject_GameObject(struct GameObject *self)
{
  __int16 *v2; // edi
  unsigned __int16 Index; // ax
  int v4; // ebp
  unsigned int v5; // edi
  int v6; // eax

  v2 = &self->field_14;
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&self->field_14);
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&self->field_28);
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&self->field_2A);
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&self->field_2C);
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&self->Rotation);
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&self->field_42);
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&self->field_74);
  gta2::Arsenal_Reset((struct Arsenal *)&self->Car);
  self->Remap = -1;
  self->NextGameObject1 = 0;
  self->field_4 = 0;
  self->field_6 = 0;
  self->field_8 = 11;
  self->field_C = 28;
  self->field_10 = 36;
  Index = unk_66A434.Index;
  self->field_16 = 0;
  *v2 = Index;
  self->field_18 = 0;
  self->ProbablyPhysics = 0;
  self->field_20 = 0;
  self->field_24 = 3;
  self->field_28 = unk_66A434.Index;
  self->field_2A = unk_66A434.Index;
  self->field_2C = unk_66A434.Index;
  self->field_30 = 4;
  self->short = 0;
  self->Speed = (int)unk_66A634.FirstElement;
  v4 = self->field_58;
  self->NextGameObject = unk_66A504;
  self->Rotation = unk_66A434.Index;
  self->field_42 = unk_66A434.Index;
  self->field_44 = 0;
  self->field_45 = 0;
  LOBYTE(self->field_5C) = 0;
  self->field_46 = 0;
  self->field_48 = 0;
  self->GameObject_ = 0;
  self->Ped_ = 0;
  self->SpriteS1_ = 0;
  self->field_68 = 0;
  self->field_69 = 0;
  self->field_74 = unk_66A434.Index;
  self->field_6A = 0;
  self->GetVehicle = 0;
  self->field_58 = v4 & 0xFFFFFFFE;
  gta2::Car_sub_4BF000((struct Car *)&self->Car);
  v5 = self->field_58 & 0xFFFFFFFB;
  self->field_8C = *(_DWORD *)&unk_66A4D8.Ammo;
  self->field_58 = v5;
  v6 = v5;
  self->field_6C = 18;
  self->field_70 = 0;
  self->field_71 = 0;
  self->Speed1 = *(_DWORD *)&unk_66A4D8.Ammo;
  LOBYTE(v6) = v5 & 0xFD;
  self->field_94 = *(_DWORD *)&unk_66A4D8.Ammo;
  self->field_58 = v6;
  self->deltaX = *(_DWORD *)&unk_66A4D8.Ammo;
  LOBYTE(v6) = v5 & 0xD5;
  self->deltaY = *(_DWORD *)&unk_66A4D8.Ammo;
  self->field_58 = v6;
  self->teleportX = *(_DWORD *)&unk_66A4D8.Ammo;
  self->teleportY = *(_DWORD *)&unk_66A4D8.Ammo;
  self->teleportZ = *(_DWORD *)&unk_66A4D8.Ammo;
  self->CigaretteIdleTimer = 0;
}


// 0x00497c20: GameObject::sub_497C20
// IDA: GameObject::sub_497C20
// Ghidra: ---
void gta2::GameObject_sub_497C20(struct GameObject *self)
{
  struct GameObject *v1; // eax
  int v3; // ecx
  unsigned __int16 Index; // dx
  int v5; // eax
  int v6; // eax
  unsigned int v7; // edi

  v1 = unk_66A3BC;
  self->NextGameObject1 = unk_66A3BC;
  unk_66A3BC = (struct GameObject *)((char *)&v1->NextGameObject1 + 1);
  gta2::GameObject_sub_493850(self);
  self->field_4 = 1;
  self->Remap = -1;
  self->field_6 = 0;
  self->field_8 = 11;
  self->field_C = 28;
  self->field_10 = 36;
  self->field_14 = unk_66A434.Index;
  self->field_16 = 0;
  self->field_18 = 0;
  self->ProbablyPhysics = 0;
  self->field_20 = 0;
  self->field_24 = 3;
  self->field_28 = unk_66A434.Index;
  self->field_2A = unk_66A434.Index;
  self->field_2C = unk_66A434.Index;
  self->field_30 = 4;
  self->short = 0;
  self->Speed = (int)unk_66A634.FirstElement;
  self->NextGameObject = unk_66A504;
  self->Rotation = unk_66A434.Index;
  self->field_42 = unk_66A434.Index;
  v3 = self->field_58;
  self->field_44 = 0;
  self->field_45 = 0;
  LOBYTE(self->field_5C) = 0;
  self->field_46 = 0;
  self->field_48 = 0;
  self->CigaretteIdleTimer = 500;
  self->GameObject_ = 0;
  self->Ped_ = 0;
  self->field_68 = 0;
  self->field_69 = 0;
  Index = unk_66A434.Index;
  self->field_58 = v3 & 0xFFFFFFFE;
  self->field_74 = Index;
  self->field_6A = 0;
  self->GetVehicle = 0;
  gta2::Car_sub_4BF000((struct Car *)&self->Car);
  v5 = *(_DWORD *)&unk_66A4D8.Ammo;
  self->field_6C = 18;
  self->field_8C = v5;
  v6 = self->field_58;
  LOBYTE(v6) = v6 & 0xFB;
  self->field_70 = 0;
  self->field_58 = v6;
  self->field_71 = 0;
  LOBYTE(v6) = v6 & 0xFD;
  self->Speed1 = *(_DWORD *)&unk_66A4D8.Ammo;
  self->field_94 = *(_DWORD *)&unk_66A4D8.Ammo;
  self->field_58 = v6;
  LOBYTE(v6) = v6 & 0xD7;
  self->deltaX = *(_DWORD *)&unk_66A4D8.Ammo;
  self->deltaY = *(_DWORD *)&unk_66A4D8.Ammo;
  self->field_58 = v6;
  self->teleportX = *(_DWORD *)&unk_66A4D8.Ammo;
  self->teleportY = *(_DWORD *)&unk_66A4D8.Ammo;
  v7 = v6 & 0xFFFFFFEF;
  self->teleportZ = *(_DWORD *)&unk_66A4D8.Ammo;
  self->field_58 = v6 & 0xFFFFFFEF;
  self->Car1 = *(Car **)&unk_66A4D8.Ammo;
  self->Car2 = *(Car **)&unk_66A4D8.Ammo;
  self->field_72 = gta2::Weapon_sub_41C1E0(&unk_66A4D8);
  self->field_73 = gta2::Weapon_sub_41C1E0(&unk_66A4D8);
  self->field_58 = v7 & 0xFFFFFF3F;
  self->field_60 = 0;

  self->field_64 = 0;
  self->field_55 = 0;
  LOBYTE(self->field_A0) = 0;
  self->field_B0 = -1;
}


// 0x004993b0: GameObject::FUN_004993b0
// IDA: sub_4993B0
// Ghidra: GameObject::FUN_004993b0
void gta2::GameObject_FUN_004993b0(struct GameObject *self,CollisionBox *param_1)
{
  int iVar1;
  struct CollisionBox *this_00;
  byte bVar2;
  char cVar3;
  bool bVar4;
  Point2D *this_01;
  undefined3 extraout_var;
  char *pcVar5;
  struct SpriteS1 *pSpriteS1;
  undefined1 local_1a;
  undefined1 local_19;
  Point2D local_18;
  
  this_00 = param_1;
  local_1a = 0;
  bVar2 = gta2::S63_sub_421080(param_1);
  if (((bVar2 != 0) &&
      (cVar3 = gta2::S63_sub_420FF0(this_00), cVar3 != '\0')) &&
     (cVar3 = gta2::S63_sub_420FF0(this_00),
     cVar3 == *(char *)(self->ScriptRef + 0x267))) {
    return;
  }
  bVar2 = gta2::S63_sub_482C90(this_00);
  if (bVar2 == 0) goto LAB_004994bb;
  bVar4 = gta2::Ped_IsSearchType((struct Ped *)self->ScriptRef,
                             SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
  if (bVar4) {
    bVar4 = self->S7[0].doorState == 0xf;
LAB_00499425:
    if (bVar4) goto LAB_004994bb;
  }
  else {
    iVar1 = this_00->EventHandler[0].NextElement[1].field14_0x20;
    bVar4 = iVar1 != 3;
    if (iVar1 != 0) goto LAB_00499425;
  }
  this_01 = &local_18;
  pSpriteS1 = (struct SpriteS1 *)&DAT_0066a464;
  gta2::S63_sub_482C80(this_00,(undefined4 *)this_01);
  bVar4 = gta2::Point2D_FUN_004037e0(this_01,pSpriteS1);
  if (CONCAT31(extraout_var,bVar4) != 0) {
    gta2::SpriteS1_sub_420600(*(Sprite **)&self->AIState,_DAT_0066a480,_DAT_0066a74c,
                        _DAT_0066a754);
    pcVar5 = (char *)FUN_004bd8a0(&local_18,this_00->Index,
                                  local_18.Array_24 + 0x10,
                                  CONCAT22((short)((uint)&param_1 >> 0x10),
                                           **(undefined2 **)&self->AIState),
                                  &local_19,&param_1,&local_1a);
    local_18.Array_24._8_4_ = *(undefined4 *)pcVar5;
    local_18.Array_24._12_4_ = *(undefined4 *)(pcVar5 + 4);
    gta2::S63_sub_4867E0(this_00,(int)self,(GlassInfo *)(local_18.Array_24 + 8));
    return;
  }
  *(undefined1 *)&self->Armor = 10;
LAB_004994bb:
  gta2::GameObject_FUN_004948c0(self,NULL,(int)this_00,0);
  return;
}


// 0x004994d0: GameObject::FUN_004994d0
// IDA: sub_4994D0
// Ghidra: GameObject::FUN_004994d0
void gta2::GameObject_FUN_004994d0(struct GameObject *self)
{
  int *pCarSystemManager;
  int iVar1;
  byte bVar2;
  bool bVar3;
  undefined3 extraout_var;
  uint uVar4;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  short *psVar5;
  undefined1 local_6 [2];
  struct Car *local_4;
  
  pCarSystemManager = &self->S7[3].doorState;
  bVar2 = gta2::SpriteS1_sub_472C00(self,(struct CarSystemManager *)pCarSystemManager);
  local_4 = (struct Car *)CONCAT31(extraout_var,bVar2);
  uVar4 = gta2::GameObject_sub_495220(self,local_4);
  if ((char)uVar4 != '\0') goto LAB_0049955e;
  switch(local_4) {
  case (struct Car *)0x1:
    psVar5 = (short *)&DAT_0066a6c8;
    goto LAB_0049953b;
  case (struct Car *)0x2:
    bVar3 = gta2::CarSystemManager_greater_than((struct CarSystemManager *)pCarSystemManager,
                       (short *)&DAT_0066a758);
    local_6[0] = CONCAT31(extraout_var_01,bVar3) != 0;
    break;
  case (struct Car *)0x3:
    bVar3 = gta2::CarSystemManager_greater_than((struct CarSystemManager *)pCarSystemManager,
                       (short *)&DAT_0066a718);
    local_6[0] = CONCAT31(extraout_var_00,bVar3) != 0;
    break;
  case (struct Car *)0x4:
    psVar5 = (short *)&DAT_0066a654;
LAB_0049953b:
    bVar3 = gta2::CarSystemManager_greater_than((struct CarSystemManager *)pCarSystemManager,psVar5);
    local_6[0] = CONCAT31(extraout_var_02,bVar3) != 0;
  }
  local_4 = (struct Car *)FUN_00491f10(local_6,&local_4,local_6);
LAB_0049955e:
  bVar2 = FUN_004725b0(local_6,(undefined2 *)local_6,&local_4);
  iVar1 = self->S7[0].doorState;
  *(undefined2 *)pCarSystemManager =
       *(undefined2 *)CONCAT31(extraout_var_03,bVar2);
  *(undefined2 *)((int)&self->S7[3].PedInDoor + 2) = 100;
  if (iVar1 != 0xf) {
    self->S7[0].doorState = 1;
  }
  return;
}


// 0x004995a0: GameObject::sub_4995A0
// IDA: GameObject::sub_4995A0
// Ghidra: ---
char gta2::GameObject_sub_4995A0(struct GameObject *self)
{
  char result; // al
  char v3; // al
  void *v4; // ecx
  struct SpriteS1 *SpriteS1; // esi
  struct SpriteS1 *v6; // eax
  struct SpriteS1 *p_TypeWeapon; // edx
  char v8; // al
  void *v9; // ecx
  struct SpriteS1 *v10; // esi
  struct SpriteS1 *v11; // eax
  char *v12; // ecx
  char v13; // al
  void *v14; // ecx
  int *v15; // edi
  int *v16; // eax
  char v17; // al
  void *v18; // ecx
  char v19; // al
  void *v20; // ecx
  char v21; // al
  void *v22; // ecx
  char v23; // al
  void *v24; // ecx
  char v25; // al
  void *v26; // ecx
  char v27; // al
  void *v28; // ecx
  char v29; // al
  void *v30; // ecx
  char v31; // al
  void *v32; // ecx
  char v33; // al
  void *v34; // ecx
  int *v35; // edi
  int *v36; // eax
  char v37; // [esp-8h] [ebp-A4h]
  char v38; // [esp-8h] [ebp-A4h]
  char v39; // [esp-8h] [ebp-A4h]
  char v40; // [esp-8h] [ebp-A4h]
  char v41; // [esp-8h] [ebp-A4h]
  char v42; // [esp-8h] [ebp-A4h]
  char v43; // [esp-8h] [ebp-A4h]
  char v44; // [esp-8h] [ebp-A4h]
  char v45; // [esp-8h] [ebp-A4h]
  char v46; // [esp-8h] [ebp-A4h]
  char v47; // [esp-8h] [ebp-A4h]
  char v48; // [esp-8h] [ebp-A4h]
  Weapon v49; // [esp+4h] [ebp-98h] BYREF
  int v50; // [esp+34h] [ebp-68h] BYREF
  char v51; // [esp+38h] [ebp-64h] BYREF
  char v52; // [esp+3Ch] [ebp-60h] BYREF
  int v53; // [esp+40h] [ebp-5Ch] BYREF
  int v54; // [esp+44h] [ebp-58h] BYREF
  int v55; // [esp+48h] [ebp-54h] BYREF
  int v56; // [esp+4Ch] [ebp-50h] BYREF
  int v57; // [esp+50h] [ebp-4Ch] BYREF
  char v58; // [esp+54h] [ebp-48h] BYREF
  int v59; // [esp+58h] [ebp-44h] BYREF
  int v60; // [esp+5Ch] [ebp-40h] BYREF
  int v61; // [esp+60h] [ebp-3Ch] BYREF
  int v62; // [esp+64h] [ebp-38h] BYREF
  char v63; // [esp+68h] [ebp-34h] BYREF
  int v64; // [esp+6Ch] [ebp-30h] BYREF
  int v65; // [esp+70h] [ebp-2Ch] BYREF
  int a2; // [esp+74h] [ebp-28h] BYREF
  int v67; // [esp+78h] [ebp-24h] BYREF
  int v68; // [esp+7Ch] [ebp-20h] BYREF
  char v69; // [esp+80h] [ebp-1Ch] BYREF
  char v70; // [esp+84h] [ebp-18h] BYREF
  int v71; // [esp+88h] [ebp-14h] BYREF
  int v72; // [esp+8Ch] [ebp-10h] BYREF
  int v73; // [esp+90h] [ebp-Ch] BYREF
  char v74; // [esp+94h] [ebp-8h] BYREF
  char v75; // [esp+98h] [ebp-4h] BYREF

  LOBYTE(v49.Ammo) = gta2::sub_40E4F0(&self->Rotation);
  result = dword_593228 - 1;
  switch ( dword_593228 )
  {
    case 1:
      result = v49.Ammo;
      switch ( LOBYTE(v49.Ammo) )
      {
        case 0:
        case 1:
        case 2:
        case 3:
          gta2::sub_41FC20(&v49, word_66A718);
          gta2::Player_sub_40E530((struct Player *)&v49, (struct Tango *)&unk_66A480);
          gta2::Player_sub_40E530((struct Player *)&v49.SMG, (struct Tango *)&unk_66A74C);
          unk_66A3FC = word_66A718[0];
          v39 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v49.SMG);
          v13 = gta2::Weapon_sub_41C1E0(&v49);
          if ( gta2::GameObject_sub_495BF0(self, v13, v39) )
          {
            gta2::sub_401B90(&self->Speed, &v68, &unk_66A54C);
            gta2::sub_41FC20(v14, word_66A718);
            SpriteS1 = self->SpriteS1_;
            v15 = (int *)gta2::S202_sub_401B20(
                           (struct S202 *)&SpriteS1->S3_arr5031[0].PositionY,
                           (struct SpriteS1 *)&v49.SoundWeapon,
                           (struct PublicTransport *)&v49.SMG);
            v16 = (int *)gta2::S202_sub_401B20(
                           (struct S202 *)&SpriteS1->S3_arr5031[0].PositionX,
                           (struct SpriteS1 *)&v62,
                           (struct PublicTransport *)&v49);
            goto LABEL_29;
          }
          gta2::sub_41FC20(&v49.SMG, word_66A758);
          gta2::Player_sub_40E530((struct Player *)&v49, (struct Tango *)&unk_66A480);
          gta2::Player_sub_40E530((struct Player *)&v49.SMG, (struct Tango *)&unk_66A74C);
          unk_66A3FC = word_66A758[0];
          v40 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v49.SMG);
          v17 = gta2::Weapon_sub_41C1E0(&v49);
          result = gta2::GameObject_sub_495BF0(self, v17, v40);
          if ( result )
          {
            gta2::sub_401B90(&self->Speed, &v50, &unk_66A54C);
            gta2::sub_41FC20(v18, word_66A758);
            v10 = self->SpriteS1_;
            v11 = gta2::S202_sub_401B20((struct S202 *)&v10->S3_arr5031[0].PositionY, (struct SpriteS1 *)&v72, (struct PublicTransport *)&v49.SMG);
            v12 = &v52;
            goto LABEL_32;
          }
          break;
        case 4:
        case 5:
        case 6:
        case 7:
          gta2::sub_41FC20(0, word_66A654);
          gta2::Player_sub_40E530((struct Player *)&v49, (struct Tango *)&unk_66A480);
          gta2::Player_sub_40E530((struct Player *)&v49.SMG, (struct Tango *)&unk_66A74C);
          unk_66A3FC = word_66A654[0];
          v37 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v49.SMG);
          v3 = gta2::Weapon_sub_41C1E0(&v49);
          if ( gta2::GameObject_sub_495BF0(self, v3, v37) )
          {
            gta2::sub_401B90(&self->Speed, &a2, &unk_66A54C);
            gta2::sub_41FC20(v4, word_66A654);
            SpriteS1 = self->SpriteS1_;
            v6 = gta2::S202_sub_401B20(
                   (struct S202 *)&SpriteS1->S3_arr5031[0].PositionY,
                   (struct SpriteS1 *)&v49.short,
                   (struct PublicTransport *)&v49.SMG);
            p_TypeWeapon = (struct SpriteS1 *)&v74;
            goto LABEL_28;
          }
          gta2::sub_41FC20(&v49.SMG, word_66A758);
          gta2::Player_sub_40E530((struct Player *)&v49, (struct Tango *)&unk_66A480);
          gta2::Player_sub_40E530((struct Player *)&v49.SMG, (struct Tango *)&unk_66A74C);
          unk_66A3FC = word_66A758[0];
          v38 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v49.SMG);
          v8 = gta2::Weapon_sub_41C1E0(&v49);
          result = gta2::GameObject_sub_495BF0(self, v8, v38);
          if ( result )
          {
            gta2::sub_401B90(&self->Speed, &v49.NextWeapon, &unk_66A54C);
            gta2::sub_41FC20(v9, word_66A758);
            v10 = self->SpriteS1_;
            v11 = gta2::S202_sub_401B20((struct S202 *)&v10->S3_arr5031[0].PositionY, (struct SpriteS1 *)&v60, (struct PublicTransport *)&v49.SMG);
            v12 = &v49.field_20;
            goto LABEL_32;
          }
          break;
        default:
          return result;
      }
      break;
    case 2:
      result = v49.Ammo;
      switch ( LOBYTE(v49.Ammo) )
      {
        case 0:
        case 1:
        case 2:
        case 3:
          gta2::sub_41FC20(0, word_66A718);
          gta2::Player_sub_40E530((struct Player *)&v49, (struct Tango *)&unk_66A480);
          gta2::Player_sub_40E530((struct Player *)&v49.SMG, (struct Tango *)&unk_66A74C);
          unk_66A3FC = word_66A718[0];
          v43 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v49.SMG);
          v23 = gta2::Weapon_sub_41C1E0(&v49);
          if ( gta2::GameObject_sub_495BF0(self, v23, v43) )
          {
            gta2::sub_401B90(&self->Speed, &v49.field_C, &unk_66A54C);
            gta2::sub_41FC20(v24, word_66A718);
            SpriteS1 = self->SpriteS1_;
            v6 = gta2::S202_sub_401B20(
                   (struct S202 *)&SpriteS1->S3_arr5031[0].PositionY,
                   (struct SpriteS1 *)&v49.Car,
                   (struct PublicTransport *)&v49.SMG);
            p_TypeWeapon = (struct SpriteS1 *)&v49.TypeWeapon;
            goto LABEL_28;
          }
          gta2::sub_41FC20(&v49.SMG, word_66A6C8);
          gta2::Player_sub_40E530((struct Player *)&v49, (struct Tango *)&unk_66A480);
          gta2::Player_sub_40E530((struct Player *)&v49.SMG, (struct Tango *)&unk_66A74C);
          unk_66A3FC = word_66A6C8[0];
          v44 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v49.SMG);
          v25 = gta2::Weapon_sub_41C1E0(&v49);
          result = gta2::GameObject_sub_495BF0(self, v25, v44);
          if ( result )
          {
            gta2::sub_401B90(&self->Speed, &v49.Ped, &unk_66A54C);
            gta2::sub_41FC20(v26, word_66A6C8);
            v10 = self->SpriteS1_;
            v11 = gta2::S202_sub_401B20(
                    (struct S202 *)&v10->S3_arr5031[0].PositionY,
                    (struct SpriteS1 *)&v49.field_2C,
                    (struct PublicTransport *)&v49.SMG);
            v12 = &v51;
            goto LABEL_32;
          }
          break;
        case 4:
        case 5:
        case 6:
        case 7:
          gta2::sub_41FC20(&v49, word_66A654);
          gta2::Player_sub_40E530((struct Player *)&v49, (struct Tango *)&unk_66A480);
          gta2::Player_sub_40E530((struct Player *)&v49.SMG, (struct Tango *)&unk_66A74C);
          unk_66A3FC = word_66A654[0];
          v45 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v49.SMG);
          v27 = gta2::Weapon_sub_41C1E0(&v49);
          if ( gta2::GameObject_sub_495BF0(self, v27, v45) )
          {
            gta2::sub_401B90(&self->Speed, &v53, &unk_66A54C);
            gta2::sub_41FC20(v28, word_66A654);
            SpriteS1 = self->SpriteS1_;
            v15 = (int *)gta2::S202_sub_401B20(
                           (struct S202 *)&SpriteS1->S3_arr5031[0].PositionY,
                           (struct SpriteS1 *)&v55,
                           (struct PublicTransport *)&v49.SMG);
            v16 = (int *)gta2::S202_sub_401B20(
                           (struct S202 *)&SpriteS1->S3_arr5031[0].PositionX,
                           (struct SpriteS1 *)&v57,
                           (struct PublicTransport *)&v49);
            goto LABEL_29;
          }
          gta2::sub_41FC20(&v49.SMG, word_66A6C8);
          gta2::Player_sub_40E530((struct Player *)&v49, (struct Tango *)&unk_66A480);
          gta2::Player_sub_40E530((struct Player *)&v49.SMG, (struct Tango *)&unk_66A74C);
          unk_66A3FC = word_66A6C8[0];
          v46 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v49.SMG);
          v29 = gta2::Weapon_sub_41C1E0(&v49);
          result = gta2::GameObject_sub_495BF0(self, v29, v46);
          if ( result )
          {
            gta2::sub_401B90(&self->Speed, &v59, &unk_66A54C);
            gta2::sub_41FC20(v30, word_66A6C8);
            v10 = self->SpriteS1_;
            v11 = gta2::S202_sub_401B20((struct S202 *)&v10->S3_arr5031[0].PositionY, (struct SpriteS1 *)&v61, (struct PublicTransport *)&v49.SMG);
            v12 = &v63;
            goto LABEL_32;
          }
          break;
        default:
          return result;
      }
      break;
    case 3:
      result = v49.Ammo;
      switch ( LOBYTE(v49.Ammo) )
      {
        case 0:
        case 1:
        case 6:
        case 7:
          gta2::sub_41FC20(&v49.SMG, word_66A758);
          gta2::Player_sub_40E530((struct Player *)&v49, (struct Tango *)&unk_66A480);
          gta2::Player_sub_40E530((struct Player *)&v49.SMG, (struct Tango *)&unk_66A74C);
          unk_66A3FC = word_66A758[0];
          v42 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v49.SMG);
          v21 = gta2::Weapon_sub_41C1E0(&v49);
          result = gta2::GameObject_sub_495BF0(self, v21, v42);
          if ( result )
          {
            gta2::sub_401B90(&self->Speed, &v56, &unk_66A54C);
            gta2::sub_41FC20(v22, word_66A758);
            v10 = self->SpriteS1_;
            v11 = gta2::S202_sub_401B20(
                    (struct S202 *)&v10->S3_arr5031[0].PositionY,
                    (struct SpriteS1 *)&v49.field_8,
                    (struct PublicTransport *)&v49.SMG);
            v12 = &v58;
            goto LABEL_32;
          }
          break;
        case 2:
        case 3:
        case 4:
        case 5:
          gta2::sub_41FC20(0, word_66A6C8);
          gta2::Player_sub_40E530((struct Player *)&v49, (struct Tango *)&unk_66A480);
          gta2::Player_sub_40E530((struct Player *)&v49.SMG, (struct Tango *)&unk_66A74C);
          unk_66A3FC = word_66A6C8[0];
          v41 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v49.SMG);
          v19 = gta2::Weapon_sub_41C1E0(&v49);
          result = gta2::GameObject_sub_495BF0(self, v19, v41);
          if ( result )
          {
            gta2::sub_401B90(&self->Speed, &v64, &unk_66A54C);
            gta2::sub_41FC20(v20, word_66A6C8);
            SpriteS1 = self->SpriteS1_;
            v6 = gta2::S202_sub_401B20(
                   (struct S202 *)&SpriteS1->S3_arr5031[0].PositionY,
                   (struct SpriteS1 *)&v54,
                   (struct PublicTransport *)&v49.SMG);
            p_TypeWeapon = (struct SpriteS1 *)&v70;
            goto LABEL_28;
          }
          break;
        default:
          return result;
      }
      break;
    case 4:
      result = v49.Ammo;
      switch ( LOBYTE(v49.Ammo) )
      {
        case 0:
        case 1:
        case 6:
        case 7:
          gta2::sub_41FC20(&v49.SMG, word_66A758);
          gta2::Player_sub_40E530((struct Player *)&v49, (struct Tango *)&unk_66A480);
          gta2::Player_sub_40E530((struct Player *)&v49.SMG, (struct Tango *)&unk_66A74C);
          unk_66A3FC = word_66A758[0];
          v48 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v49.SMG);
          v33 = gta2::Weapon_sub_41C1E0(&v49);
          result = gta2::GameObject_sub_495BF0(self, v33, v48);
          if ( result )
          {
            gta2::sub_401B90(&self->Speed, &v71, &unk_66A54C);
            gta2::sub_41FC20(v34, word_66A758);
            v10 = self->SpriteS1_;
            v11 = gta2::S202_sub_401B20((struct S202 *)&v10->S3_arr5031[0].PositionY, (struct SpriteS1 *)&v73, (struct PublicTransport *)&v49.SMG);
            v12 = &v75;
LABEL_32:
            v35 = (int *)v11;
            v36 = (int *)gta2::S202_sub_401B20(
                           (struct S202 *)&v10->S3_arr5031[0].PositionX,
                           (struct SpriteS1 *)v12,
                           (struct PublicTransport *)&v49);
            result = gta2::SpriteS1_sub_420600(v10, *v36, *v35, v10->S3_arr5031[0].PositionZ);
          }
          break;
        case 2:
        case 3:
        case 4:
        case 5:
          gta2::sub_41FC20(0, word_66A6C8);
          gta2::Player_sub_40E530((struct Player *)&v49, (struct Tango *)&unk_66A480);
          gta2::Player_sub_40E530((struct Player *)&v49.SMG, (struct Tango *)&unk_66A74C);
          unk_66A3FC = word_66A6C8[0];
          v47 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v49.SMG);
          v31 = gta2::Weapon_sub_41C1E0(&v49);
          result = gta2::GameObject_sub_495BF0(self, v31, v47);
          if ( result )
          {
            gta2::sub_401B90(&self->Speed, &v65, &unk_66A54C);
            gta2::sub_41FC20(v32, word_66A6C8);
            SpriteS1 = self->SpriteS1_;
            v6 = gta2::S202_sub_401B20(
                   (struct S202 *)&SpriteS1->S3_arr5031[0].PositionY,
                   (struct SpriteS1 *)&v67,
                   (struct PublicTransport *)&v49.SMG);
            p_TypeWeapon = (struct SpriteS1 *)&v69;
LABEL_28:
            v15 = (int *)v6;
            v16 = (int *)gta2::S202_sub_401B20(
                           (struct S202 *)&SpriteS1->S3_arr5031[0].PositionX,
                           p_TypeWeapon,
                           (struct PublicTransport *)&v49);
LABEL_29:
            result = gta2::SpriteS1_sub_420600(SpriteS1, *v16, *v15, SpriteS1->S3_arr5031[0].PositionZ);
          }
          break;
        default:
          return result;
      }
      break;
    default:
      return result;
  }
  return result;
}


// 0x00499f00: GameObject::FUN_00499f00
// IDA: ---
// Ghidra: GameObject::FUN_00499f00
void * gta2::GameObject_FUN_00499f00(struct GameObject *self,char param_1)
{
  undefined1 uVar1;
  bool bVar2;
  struct SpriteS1 *this_00;
  int iVar3;
  void *pvVar4;
  struct SpriteS1 *pSpriteS1;
  struct EventHandler *pEVar5;
  struct Car *pCar;
  struct CollisionBox *pCVar6;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  char cVar7;
  int iVar8;
  
  if (((*(char *)((int)&self->CollisionData + 1) != '\x01') ||
      (self->S7[1].doorState == 0)) ||
     (cVar7 = '\x01', self->S7[1].PedInDoor == (struct Ped *)0x3)) {
    cVar7 = param_1;
  }
  this_00 = gta2::SpriteS1_sub_4BDFE0(*(SpriteS1 **)&self->AIState,2);
  if (this_00 != NULL) {
    iVar3 = gta2::SpriteS1_getSpriteType(this_00);
    pvVar4 = (void *)(iVar3 + -1);
    switch(pvVar4) {
    case NULL:
    case (void *)0x3:
    case (void *)0x4:
      pCVar6 = (struct CollisionBox *)gta2::SpriteS1_sub_40FEC0(this_00);
      gta2::GameObject_FUN_004993b0(self,pCVar6);
      self->S7[1].doorState = 3;
      return pCVar6;
    case (void *)0x1:
      goto switchD_00499f49_caseD_2;
    case (void *)0x2:
      if (cVar7 != DAT_0059322c) {
        pvVar4 = (void *)gta2::Ped_sub_420B70((struct Ped *)self->ScriptRef);
        if ((int)pvVar4 < 2) {
          return pvVar4;
        }
        if (6 < (int)pvVar4) {
          return pvVar4;
        }
        pvVar4 = (void *)gta2::SpriteS1_GetGameObject(this_00);
        gta2::GameObject_FUN_00494280(self,(int)pvVar4);
      }
      self->S7[0].ID = 0;
      self->S7[0].field4_0xd = 0;
      self->S7[0].field5_0xe = 0;
      self->S7[0].field6_0xf = 0;
      return pvVar4;
    default:
      return pvVar4;
    }
  }
  iVar3 = self->S7[0].doorState;
  if (iVar3 != 10) {
    if (iVar3 != 0x1b) goto LAB_0049a02a;
    self->S7[1].AnimationFrame = 0;
    self->S7[1].doorState = 0;
  }
  self->S7[0].doorState = 1;
LAB_0049a02a:
  self->S7[0].ID = 0;
  self->S7[0].field4_0xd = 0;
  self->S7[0].field5_0xe = 0;
  self->S7[0].field6_0xf = 0;
  bVar2 = gta2::Player_IsCurrentPlayer((struct Player *)&self->S7[2].ID,(struct Player *)&DAT_0066a634);
  pvVar4 = (void *)CONCAT31(extraout_var,bVar2);
  if (pvVar4 == NULL) {
    bVar2 = gta2::Ped_IsSearchType((struct Ped *)self->ScriptRef,
                               SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
    pvVar4 = (void *)CONCAT31(extraout_var_00,bVar2);
    if (!bVar2) {
      return pvVar4;
    }
    if (self->ModelId != 0) {
      return pvVar4;
    }
  }
  self->S7[1].AnimationFrame = 0;
  self->S7[1].doorState = 0;
  *(undefined1 *)((int)&self->CollisionData + 1) = 0;
  pvVar4 = (void *)CONCAT22((short)((uint)pvVar4 >> 0x10),_DAT_0066a434);
  uVar1 = DAT_0066a434_1;
  self->S7[1].field5_0xe = DAT_0066a434;
  self->S7[1].field6_0xf = uVar1;
  return pvVar4;
switchD_00499f49_caseD_2:
  pSpriteS1 = gta2::SpriteS1_sub_4BDFE0(*(SpriteS1 **)&self->AIState,1);
  iVar3 = gta2::SpriteS1_getSpriteType(pSpriteS1);
  if (iVar3 != 1) {
    iVar8 = 0;
    iVar3 = 0;
    pCar = (struct Car *)gta2::SpriteS1_GetCar(this_00);
    pvVar4 = gta2::GameObject_FUN_004948c0(self,pCar,iVar3,iVar8);
    self->S7[1].doorState = 1;
    return pvVar4;
  }
  pEVar5 = gta2::SpriteS1_sub_40FEC0(pSpriteS1);
  if (pEVar5 == NULL) {
    return NULL;
  }
  pCVar6 = (struct CollisionBox *)gta2::SpriteS1_sub_40FEC0(pSpriteS1);
  gta2::GameObject_FUN_004993b0(self,pCVar6);
  self->S7[1].doorState = 3;
  return pCVar6;
}


// 0x0049a080: GameObject::FUN_0049a080
// IDA: sub_49A080
// Ghidra: GameObject::FUN_0049a080
undefined1 gta2::GameObject_FUN_0049a080(struct GameObject *self)
{
  int *piVar1;
  byte *this_00;
  byte *this_01;
  undefined2 uVar2;
  int iVar3;
  Sprite *pSVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  struct SpriteS1 *pSVar12;
  struct SpriteS1 *pSVar13;
  GlassInfo *pGVar14;
  struct CarSystemManager *this_02;
  struct CarSystemManager *this_03;
  struct CarSystemManager *this_04;
  undefined2 extraout_var;
  struct CarSystemManager *this_05;
  short *unaff_EBP;
  void *unaff_EDI;
  struct Ped *pPVar15;
  struct Ped *pPVar16;
  short *psVar17;
  undefined1 local_19;
  struct SpriteS1 *local_14;
  struct SpriteS1 *local_10;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  local_10 = _DAT_0066a4d8;
  local_19 = 0;
  if (self->S7[0].doorState == 0xf) {
    return 1;
  }
  iVar3._0_1_ = self->S7[0].ID;
  iVar3._1_1_ = self->S7[0].field4_0xd;
  iVar3._2_1_ = self->S7[0].field5_0xe;
  iVar3._3_1_ = self->S7[0].field6_0xf;
  if (iVar3 != 0) {
    piVar1 = &self->S7[3].doorState;
    *(undefined2 *)piVar1 = *(undefined2 *)&self->S7[1].ID;
    self->S7[1].PedInDoor = (struct Ped *)0x1;
    gta2::sub_41FC20((struct CarSystemManager *)&stack0xfffffff4,piVar1,
               (GlassInfo *)&self->S7[2].ID,(struct Ped *)&stack0xfffffff4,
               (struct Ped *)&local_10);
    pSVar4 = *(Sprite **)&self->AIState;
    local_14 = gta2::S202_sub_401B20((Point2D *)&pSVar4->field_0x18,
                          (struct SpriteS1 *)&stack0xffffffe8,(struct S127 *)&local_10);
    pSVar12 = gta2::S202_sub_401B20((Point2D *)&pSVar4->Point2D1,(struct SpriteS1 *)local_8,
                         (struct S127 *)&stack0xfffffff4);
    gta2::SpriteS1_sub_420600(pSVar4,(int)pSVar12->FirstElement,
                        (int)local_14->FirstElement,(int)pSVar4->Point2D);
    gta2::GameObject_FUN_00499f00(self,DAT_0059322c);
    iVar5._0_1_ = self->S7[0].ID;
    iVar5._1_1_ = self->S7[0].field4_0xd;
    iVar5._2_1_ = self->S7[0].field5_0xe;
    iVar5._3_1_ = self->S7[0].field6_0xf;
    if (iVar5 == 0) {
      return 1;
    }
    gta2::SpriteS1_sub_447E20(*(SpriteS1 **)&self->AIState,_DAT_0066a480,_DAT_0066a74c);
    gta2::CarSystemManager_FUN_0041fa70((struct CarSystemManager *)&self->S7[1].ID,
               (short *)&self->S7[1].field5_0xe);
    gta2::sub_41FC20((struct CarSystemManager *)&local_10,piVar1,(GlassInfo *)&self->S7[2].ID
               ,(struct Ped *)&stack0xfffffff4,(struct Ped *)&local_10);
    pSVar4 = *(Sprite **)&self->AIState;
    pSVar12 = gta2::S202_sub_401B20((Point2D *)&pSVar4->field_0x18,(struct SpriteS1 *)local_8,
                         (struct S127 *)&local_10);
    pSVar13 = gta2::S202_sub_401B20((Point2D *)&pSVar4->Point2D1,(struct SpriteS1 *)&local_14,
                         (struct S127 *)&stack0xfffffff4);
    gta2::SpriteS1_sub_420600(pSVar4,(int)pSVar13->FirstElement,
                        (int)pSVar12->FirstElement,(int)pSVar4->Point2D);
    gta2::GameObject_FUN_00499f00(self,DAT_0059322c);
    iVar6._0_1_ = self->S7[0].ID;
    iVar6._1_1_ = self->S7[0].field4_0xd;
    iVar6._2_1_ = self->S7[0].field5_0xe;
    iVar6._3_1_ = self->S7[0].field6_0xf;
    if (iVar6 == 0) {
      return 1;
    }
    gta2::SpriteS1_sub_447E20(*(SpriteS1 **)&self->AIState,_DAT_0066a480,_DAT_0066a74c);
    return 0;
  }
  pPVar16 = (struct Ped *)&local_10;
  pPVar15 = (struct Ped *)&stack0xfffffff4;
  this_00 = &self->S7[2].ID;
  piVar1 = &self->S7[3].doorState;
  pGVar14 = (GlassInfo *)
            gta2::WorldCoordinateToScreenCoord(this_00,local_8,(int *)&DAT_0066a54c);
  gta2::sub_41FC20(this_03,piVar1,pGVar14,pPVar15,pPVar16);
  pSVar4 = *(Sprite **)&self->AIState;
  local_14 = gta2::S202_sub_401B20((Point2D *)&pSVar4->field_0x18,(struct SpriteS1 *)local_8,
                        (struct S127 *)&local_10);
  pSVar12 = gta2::S202_sub_401B20((Point2D *)&pSVar4->Point2D1,(struct SpriteS1 *)&stack0xffffffe8
                       ,(struct S127 *)&stack0xfffffff4);
  gta2::SpriteS1_sub_420600(pSVar4,(int)pSVar12->FirstElement,
                      (int)local_14->FirstElement,(int)pSVar4->Point2D);
  gta2::GameObject_FUN_00499f00(self,DAT_0059322c);
  iVar7._0_1_ = self->S7[0].ID;
  iVar7._1_1_ = self->S7[0].field4_0xd;
  iVar7._2_1_ = self->S7[0].field5_0xe;
  iVar7._3_1_ = self->S7[0].field6_0xf;
  if (iVar7 == 0) {
    *(undefined1 *)((int)&self->CollisionData + 1) = 0;
  }
  else {
    gta2::SpriteS1_sub_447E20(*(SpriteS1 **)&self->AIState,_DAT_0066a480,_DAT_0066a74c);
    this_01 = &self->S7[1].ID;
    pPVar16 = (struct Ped *)&stack0xffffffe8;
    psVar17 = (short *)&DAT_0066a5f4;
    *(undefined2 *)piVar1 = *(undefined2 *)&self->S7[1].ID;
    this_02 = (struct CarSystemManager *)
              gta2::sub_40E5A0((struct CarSystemManager *)this_01,(struct Ped *)&local_14,
                         (short *)&self->S7[1].field5_0xe,pPVar16,
                         (short *)&DAT_0066a5f4);
    gta2::sub_40E5A0(this_02,pPVar16,psVar17,unaff_EDI,unaff_EBP);
    pPVar16 = (struct Ped *)&local_10;
    pPVar15 = (struct Ped *)&stack0xfffffff4;
    pGVar14 = (GlassInfo *)
              gta2::WorldCoordinateToScreenCoord(this_00,local_8,(int *)&DAT_0066a71c)
    ;
    gta2::sub_41FC20((struct CarSystemManager *)&stack0xffffffe8,
               (struct CarSystemManager *)&stack0xffffffe8,pGVar14,pPVar15,pPVar16);
    local_14 = gta2::S202_sub_401B20((Point2D *)(*(int *)&self->AIState + 0x18),
                          (struct SpriteS1 *)local_8,(struct S127 *)&local_10);
    pSVar12 = gta2::S202_sub_401B20((Point2D *)(*(int *)&self->AIState + 0x14),
                         (struct SpriteS1 *)local_4,(struct S127 *)&stack0xfffffff4);
    gta2::SpriteS1_sub_420600(*(Sprite **)&self->AIState,(int)pSVar12->FirstElement,
                        (int)local_14->FirstElement,
                        (int)(*(Sprite **)&self->AIState)->Point2D);
    gta2::GameObject_FUN_00499f00(self,DAT_0059322c);
    iVar8._0_1_ = self->S7[0].ID;
    iVar8._1_1_ = self->S7[0].field4_0xd;
    iVar8._2_1_ = self->S7[0].field5_0xe;
    iVar8._3_1_ = self->S7[0].field6_0xf;
    if ((iVar8 == 0) && (self->S7[1].PedInDoor != (struct Ped *)0x2)) {
      gta2::SpriteS1_sub_447E20(*(SpriteS1 **)&self->AIState,_DAT_0066a480,_DAT_0066a74c);
      psVar17 = (short *)gta2::sub_40E5A0((struct CarSystemManager *)&self->S7[1].field5_0xe,
                                    (struct Ped *)&local_14,(short *)&DAT_0066a5f4,
                                    unaff_EDI,unaff_EBP);
      gta2::CarSystemManager_FUN_0041fa70((struct CarSystemManager *)this_01,psVar17);
      pPVar16 = (struct Ped *)&local_10;
      pPVar15 = (struct Ped *)&stack0xfffffff4;
      *(undefined2 *)piVar1 = *(undefined2 *)this_01;
      self->S7[1].PedInDoor = (struct Ped *)0x2;
      pGVar14 = (GlassInfo *)
                gta2::WorldCoordinateToScreenCoord
                          (this_00,local_4,(int *)&DAT_0066a54c);
      gta2::sub_41FC20(this_04,piVar1,pGVar14,pPVar15,pPVar16);
      local_14 = gta2::S202_sub_401B20((Point2D *)(*(int *)&self->AIState + 0x18),
                            (struct SpriteS1 *)local_4,(struct S127 *)&local_10);
      pSVar12 = gta2::S202_sub_401B20((Point2D *)(*(int *)&self->AIState + 0x14),
                           (struct SpriteS1 *)local_8,(struct S127 *)&stack0xfffffff4);
      gta2::SpriteS1_sub_420600(*(Sprite **)&self->AIState,(int)pSVar12->FirstElement,
                          (int)local_14->FirstElement,
                          (int)(*(Sprite **)&self->AIState)->Point2D);
      gta2::GameObject_FUN_00499f00(self,DAT_0059322c);
      iVar9._0_1_ = self->S7[0].ID;
      iVar9._1_1_ = self->S7[0].field4_0xd;
      iVar9._2_1_ = self->S7[0].field5_0xe;
      iVar9._3_1_ = self->S7[0].field6_0xf;
      if (iVar9 == 0) {
        return 1;
      }
      gta2::SpriteS1_sub_447E20(*(SpriteS1 **)&self->AIState,_DAT_0066a480,_DAT_0066a74c);
      gta2::CarSystemManager_FUN_0041fa70((struct CarSystemManager *)this_01,(short *)&self->S7[1].field5_0xe);
      uVar2._0_1_ = self->S7[1].ID;
      uVar2._1_1_ = self->S7[1].field4_0xd;
      self->S7[1].PedInDoor = NULL;
      *(undefined2 *)piVar1 = uVar2;
      gta2::sub_41FC20((struct CarSystemManager *)CONCAT22(extraout_var,uVar2),piVar1,
                 (GlassInfo *)this_00,(struct Ped *)&stack0xfffffff4,(struct Ped *)&local_10);
      pSVar4 = *(Sprite **)&self->AIState;
      pSVar12 = gta2::S202_sub_401B20((Point2D *)&pSVar4->field_0x18,(struct SpriteS1 *)local_4,
                           (struct S127 *)&local_10);
      pSVar13 = gta2::S202_sub_401B20((Point2D *)&pSVar4->Point2D1,(struct SpriteS1 *)local_8,
                           (struct S127 *)&stack0xfffffff4);
      gta2::SpriteS1_sub_420600(pSVar4,(int)pSVar13->FirstElement,
                          (int)pSVar12->FirstElement,(int)pSVar4->Point2D);
      local_19 = 1;
      gta2::GameObject_FUN_00499f00(self,DAT_0059322c);
      iVar10._0_1_ = self->S7[0].ID;
      iVar10._1_1_ = self->S7[0].field4_0xd;
      iVar10._2_1_ = self->S7[0].field5_0xe;
      iVar10._3_1_ = self->S7[0].field6_0xf;
      if (iVar10 == 0) {
        return 1;
      }
      goto LAB_0049a526;
    }
  }
  gta2::SpriteS1_sub_447E20(*(SpriteS1 **)&self->AIState,_DAT_0066a480,_DAT_0066a74c);
  gta2::sub_41FC20(this_05,piVar1,(GlassInfo *)this_00,(struct Ped *)&stack0xfffffff4,
             (struct Ped *)&local_10);
  pSVar4 = *(Sprite **)&self->AIState;
  pSVar12 = gta2::S202_sub_401B20((Point2D *)&pSVar4->field_0x18,(struct SpriteS1 *)local_4,
                       (struct S127 *)&local_10);
  pSVar13 = gta2::S202_sub_401B20((Point2D *)&pSVar4->Point2D1,(struct SpriteS1 *)local_8,
                       (struct S127 *)&stack0xfffffff4);
  gta2::SpriteS1_sub_420600(pSVar4,(int)pSVar13->FirstElement,
                      (int)pSVar12->FirstElement,(int)pSVar4->Point2D);
  gta2::GameObject_FUN_00499f00(self,DAT_0059322c);
  iVar11._0_1_ = self->S7[0].ID;
  iVar11._1_1_ = self->S7[0].field4_0xd;
  iVar11._2_1_ = self->S7[0].field5_0xe;
  iVar11._3_1_ = self->S7[0].field6_0xf;
  if (iVar11 == 0) {
    return 1;
  }
LAB_0049a526:
  gta2::SpriteS1_sub_447E20(*(SpriteS1 **)&self->AIState,_DAT_0066a480,_DAT_0066a74c);
  return local_19;
}


// 0x0049a560: GameObject::sub_49A560
// IDA: GameObject::sub_49A560
// Ghidra: ---
void gta2::GameObject_sub_49A560(struct GameObject *self)
{
  char v2; // al
  struct SpriteS1 *v3; // eax
  int v4; // eax
  char v5; // bl
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  bool v10; // cl
  struct Ped *Ped; // eax
  struct Ped *field_1A0; // eax
  struct Ped *v13; // ecx
  struct Car *v14; // eax
  void *v15; // ecx
  struct SpriteS1 *v16; // eax
  int v17; // eax
  int v18; // eax
  struct Ped *v19; // eax
  int PositionX1; // ecx
  struct Ped *pPed_1; // ecx
  struct Ped *v22; // ecx
  struct Car *v23; // eax
  struct Ped *v24; // ecx
  int v25; // eax
  __int16 *p_Rotation; // edi
  _WORD *v27; // eax
  struct Car *v28; // eax
  int *p_Speed; // edi
  struct Car *pCar; // eax
  int v31; // eax
  struct Car *v32; // eax
  __int16 v33; // dx
  __int16 v34; // dx
  int v35; // eax
  char v36; // al
  __int16 Rotation; // ax
  char v38; // bl
  void *v39; // ecx
  int v40; // eax
  struct Ped *pPed; // edi
  int v42; // eax
  __int16 *v43; // edi
  char v44; // al
  char v45; // bl
  char v46; // al
  char v47; // bl
  char v48; // al
  char v49; // al
  struct SpriteS1 *SpriteS1; // edi
  int *v51; // ebp
  int *v52; // eax
  struct SpriteS1 *v53; // edi
  int v54; // eax
  struct SpriteS1 *v55; // edi
  int PositionY; // eax
  char v57; // bl
  char v58; // al
  char v59; // al
  struct SpriteS1 *v60; // edi
  struct SpriteS1 *v61; // eax
  int v62; // eax
  void *v63; // [esp-14h] [ebp-50h]
  int v64; // [esp-Ch] [ebp-48h]
  int v65; // [esp-Ch] [ebp-48h]
  struct GameObject *v66; // [esp-Ch] [ebp-48h]
  int v67; // [esp-Ch] [ebp-48h]
  int v68; // [esp-8h] [ebp-44h]
  int v69; // [esp-8h] [ebp-44h]
  int v70; // [esp-8h] [ebp-44h]
  int v71; // [esp-8h] [ebp-44h]
  int v72; // [esp-8h] [ebp-44h]
  char v73; // [esp-8h] [ebp-44h]
  char v74; // [esp-8h] [ebp-44h]
  char v75; // [esp-8h] [ebp-44h]
  char v76; // [esp-8h] [ebp-44h]
  int v77; // [esp-8h] [ebp-44h]
  struct SpriteS1 *v78; // [esp-8h] [ebp-44h]
  int v79; // [esp-8h] [ebp-44h]
  int v80; // [esp-4h] [ebp-40h]
  int v81; // [esp-4h] [ebp-40h]
  int v82; // [esp-4h] [ebp-40h]
  int v83; // [esp-4h] [ebp-40h]
  char v84; // [esp+Dh] [ebp-2Fh]
  char v85; // [esp+Eh] [ebp-2Eh]
  char v86[4]; // [esp+10h] [ebp-2Ch] BYREF
  AudioSourceParams a3; // [esp+14h] [ebp-28h] BYREF
  struct SpriteS1 *v88; // [esp+2Ch] [ebp-10h] BYREF
  struct SpriteS1 *v89; // [esp+30h] [ebp-Ch] BYREF
  struct GameObject *v90; // [esp+34h] [ebp-8h] BYREF
  struct SpriteS1 *v91; // [esp+38h] [ebp-4h] BYREF

  v85 = 0;
  v84 = 1;
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&a3.AudioSourceParams1);
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&a3.AudioSourceParams2);
  gta2::bitShiftLeft1(&v91, 0);
  a3.field = (int)v91;
  a3.AudioSourceParams = (struct AudioSourceParams *)v91;
  gta2::bitShiftLeft1(&v91, 0);
  unk_66A3C1 = 1;
  v89 = v91;
  v90 = (struct GameObject *)v91;
  a3.field_14 = (int)v91;
  v88 = v91;
  unk_66A3C2 = 1;
  unk_66A3C3 = 0;
  unk_66A3C4 = 0;
  v2 = self->field_58;
  self->CigaretteIdleTimer = 500;
  if ( (v2 & 1) == 0 )
  {
    v3 = sub_42A630((struct SpriteS1 *)&v91, (struct S202 *)&unk_66A754);
    if ( gta2::Player_IsCurrentPlayer((struct Player *)v3, (struct Player *)&unk_66A4D8) )
      goto LABEL_5;
  }
  v80 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A754);
  v68 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A74C);
  v4 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A480);
  v5 = gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct, v4, v68, v80);
  LOBYTE(a3.field_10) = v5;
  v81 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A754);
  v69 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A74C);
  v6 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A480);
  v7 = gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct, v6, v69, v81);
  if ( !v7 || !v5 )
  {
LABEL_5:
    v82 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A754) - 1;
    v70 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A74C);
    v8 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A480);
    v5 = gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct, v8, v70, v82);
    LOBYTE(a3.field_10) = v5;
    v83 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A754) - 1;
    v71 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A74C);
    v9 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A480);
    v7 = gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct, v9, v71, v83);
  }
  if ( v7 )
  {
    v10 = (*(_BYTE *)(v7 + 11) & 0xFC) != 0 && (*(_BYTE *)(v7 + 11) & 0xFC) != 0xFC;
    self->field_58 ^= (v10 ^ (unsigned __int8)self->field_58) & 1;
    if ( gta2::Style_sub_491F80(gStyle, *(_WORD *)(v7 + 8) & 0x3FF) && self->field_10 != 15 )
    {
      Ped = self->Ped_;
      if ( (Ped->PositionX1 & 0x8000000) == 0 )
      {
        LOWORD(Ped->XCoordinate) += 3;
        field_1A0 = (struct Ped *)self->Ped_->PedId;
        if ( field_1A0 )
        {
          if ( gta2::Character_FindPed(gCharacter, field_1A0) )
          {
            self->Ped_->field_22C = 2;
            LOBYTE(self->Ped_->ID) = 50;
          }
        }
      }
    }
  }
  if ( gta2::GameObject_sub_491E40(self) )
  {
    gta2::Ped_sub_433220(self->Ped_);
    gta2::GameObject_sub_4938A0(self);
    return;
  }
  if ( !v5 && (self->field_58 & 1) == 0 )
  {
    v13 = self->Ped_;
    if ( *(_DWORD *)&v13->isPlayer
      && ((v14 = gta2::Ped_sub_436200(v13, (struct Car *)&v91), gta2::sub_4037E0(v14)) || (self->field_58 & 8) != 0) )
    {
      v63 = gta2::sub_40E5A0((struct CarSystemManager *)&self->Rotation, (struct CarSystemManager *)v86, &unk_66A5F4);
      gta2::sub_41FC20(v15, v63);
    }
    else
    {
      gta2::sub_41FC20(&a3.AudioSourceParams, &self->Rotation);
    }
    gta2::Player_sub_40E530((struct Player *)&a3.AudioSourceParams, (struct Tango *)&unk_66A480);
    gta2::Player_sub_40E530((struct Player *)&a3, (struct Tango *)&unk_66A74C);
    v16 = sub_42A630((struct SpriteS1 *)&v91, (struct S202 *)&unk_66A754);
    v17 = gta2::Player_IsCurrentPlayer((struct Player *)v16, (struct Player *)&unk_66A4D8)
        ? gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A754) - 1
        : gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A754);
    v72 = v17;
    v64 = gta2::AudioSourceParams_sub_41F9D0(&a3);
    v18 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&a3.AudioSourceParams);
    v5 = gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct, v18, v64, v72);
    LOBYTE(a3.field_10) = v5;
    if ( !v5 )
    {
      if ( self->field_10 != 15 )
        goto LABEL_34;
      if ( self->field_68 == 7 || (self->Ped_->PositionX1 & 0x800) != 0 )
      {
        v19 = self->Ped_;
        self->field_10 = 1;
        PositionX1 = v19->PositionX1;
        BYTE1(PositionX1) &= ~8u;
        v19->PositionX1 = PositionX1;
LABEL_34:
        pPed_1 = self->Ped_;
        self->field_6C = 11;
        self->field_68 = 0;
        gta2::Ped_UpdatePedState(pPed_1, 8);
        gta2::Ped_sub_4332B0(self->Ped_, 19);
        v22 = self->Ped_;
        self->field_8 = 8;
        self->field_C = 19;
        if ( *(_DWORD *)&v22->isPlayer )
        {
          v23 = gta2::Ped_sub_436200(v22, (struct Car *)&v91);
          if ( gta2::sub_4037E0(v23) || (self->field_58 & 8) != 0 )
            self->Speed = (int)gta2::JustCopyByPtrAtoC(&self->Speed, (struct SpriteS1 *)&v91)->FirstElement;
        }
        self->Speed1 = self->Speed;
        self->field_94 = *(_DWORD *)&unk_66A4D8.Ammo;
        if ( gta2::Player_IsCurrentPlayer((struct Player *)&self->Speed, (struct Player *)&unk_66A634) )
          self->field_16 = 1;
        gta2::GameObject_sub_496880(self);
        return;
      }
    }
  }
  v24 = self->Ped_;
  self->field_44 = v5;
  if ( gta2::Ped_IsSearchType(v24, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
  {
    v25 = self->field_10;
    v91 = (struct SpriteS1 *)unk_66A5F8;
    if ( v25 )
      self->field_46 = 9999;
    p_Rotation = &self->Rotation;
    v27 = gta2::Ped_sub_436140(self->Ped_, v86);
    sub_41FA70((struct Ped *)&self->Rotation, v27);
    if ( self->field_10 == 15 )
    {
      gta2::Ped_sub_403A40(self->Ped_);
      if ( self->field_6C != 5 )
      {
        self->field_6C = 5;
        self->field_68 = 0;
      }
      v28 = gta2::Ped_sub_436200(self->Ped_, (struct Car *)&a3.field_10);
      p_Speed = &self->Speed;
      if ( gta2::Car_sub_403800(v28, (int)&unk_66A4D8) )
      {
        if ( gta2::Player_IsCurrentPlayer((struct Player *)&self->Speed, (struct Player *)&unk_66A634) )
          *p_Speed = (int)self->NextGameObject;
        else
          gta2::GameObject_sub_433970(self, (struct SpriteS1 *)self->NextGameObject);
      }
      else
      {
        *p_Speed = (int)unk_66A504;
      }
    }
    else
    {
      pCar = gta2::Ped_sub_436200(self->Ped_, (struct Car *)&a3.field_10);
      if ( gta2::Car_sub_403800(pCar, (int)&unk_66A4D8) )
      {
        p_Speed = &self->Speed;
        if ( gta2::Player_IsCurrentPlayer((struct Player *)&self->Speed, (struct Player *)&unk_66A634) )
        {
          v31 = self->field_58;
          LOBYTE(v31) = v31 & 0xF7;
          *p_Speed = (int)self->NextGameObject;
        }
        else
        {
          gta2::GameObject_sub_433970(self, (struct SpriteS1 *)self->NextGameObject);
          v31 = self->field_58;
          LOBYTE(v31) = v31 & 0xF7;
        }
        self->field_58 = v31;
      }
      else
      {
        v32 = gta2::Ped_sub_436200(self->Ped_, (struct Car *)&a3.field_10);
        if ( gta2::sub_4037E0(v32) )
        {
          v33 = *p_Rotation;
          self->field_58 |= 8u;
          LOWORD(a3.AudioSourceParams2) = v33;
          sub_41FA70((struct Ped *)&self->Rotation, &unk_66A5F4);
          p_Speed = &self->Speed;
          if ( gta2::Player_IsCurrentPlayer((struct Player *)&self->Speed, (struct Player *)&unk_66A634) )
          {
            v84 = 0;
            *p_Speed = (int)self->NextGameObject;
          }
          else
          {
            gta2::GameObject_sub_433970(self, (struct SpriteS1 *)self->NextGameObject);
            v84 = 0;
          }
        }
        else if ( self->field_6A )
        {
          unk_66A3C1 = 0;
          unk_66A3C2 = 0;
          v34 = *p_Rotation;
          *p_Rotation = self->field_74;
          p_Speed = &self->Speed;
          LOWORD(a3.AudioSourceParams2) = v34;
          v84 = 0;
          self->Speed = unk_66A574;
        }
        else
        {
          v35 = self->field_10;
          p_Speed = &self->Speed;
          self->Speed = (int)unk_66A634.FirstElement;
          if ( v35 )
            self->field_10 = 7;
        }
      }
    }
    if ( (self->Ped_->PositionX1 & 0x100) != 0 )
      *p_Speed = unk_66A574;
  }
  else
  {
    v36 = self->field_69;
    v91 = (struct SpriteS1 *)unk_66A5F8;
    if ( v36 || self->field_10 == 15 )
    {
      gta2::Ped_sub_403A40(self->Ped_);
      unk_66A3C1 = 0;
      unk_66A3C2 = 0;
      v38 = 0;
    }
    else
    {
      if ( self->field_6A )
      {
        unk_66A3C1 = 0;
        unk_66A3C2 = 0;
        Rotation = self->Rotation;
        self->Rotation = self->field_74;
        v38 = 0;
        LOWORD(a3.AudioSourceParams2) = Rotation;
        self->Speed = unk_66A574;
        v84 = 0;
      }
      else
      {
        v38 = 1;
      }
      if ( gta2::sub_4037E0(&self->Speed) )
      {
        LOWORD(a3.AudioSourceParams2) = self->Rotation;
        self->Rotation = *(_WORD *)gta2::sub_40E5A0((struct CarSystemManager *)&self->Rotation, (struct CarSystemManager *)v86, &unk_66A5F4);
        self->field_58 |= 8u;
        v84 = 0;
        self->Speed = *(_DWORD *)gta2::sub_403840(v39, (struct Player *)v86, &self->Speed);
      }
    }
    v40 = self->field_10;
    if ( v40 && v40 != 15 && self->field_8 != 9 )
    {
      if ( LOBYTE(a3.field_10) == 1 || LOBYTE(a3.field_10) == 3 )
      {
        pPed = self->Ped_;
        if ( !gta2::Ped_GetState(pPed) || gta2::Ped_GetState(pPed) == 8 )
          gta2::Ped_SetAnimationState(pPed, 17, 9999);
      }
      else if ( !self->field_C && v38 )
      {
        gta2::GameObject_sub_491FA0(self);
        gta2::GameObject_sub_495700(self);
      }
    }
  }
  if ( v84 )
    LOWORD(a3.AudioSourceParams2) = self->Rotation;
  if ( gta2::Player_IsCurrentPlayer((struct Player *)&self->Speed, (struct Player *)&unk_66A4D8) )
  {
    v42 = self->field_58;
    LOBYTE(v42) = v42 & 0xF7;
    self->field_58 = v42;
  }
  v43 = &self->Rotation;
  gta2::sub_41FC20(&a3.AudioSourceParams, &self->Rotation);
  gta2::Player_sub_40E530((struct Player *)&a3.AudioSourceParams, (struct Tango *)&unk_66A480);
  gta2::Player_sub_40E530((struct Player *)&a3, (struct Tango *)&unk_66A74C);
  gta2::Player_sub_40E530((struct Player *)&a3.AudioSourceParams, (struct Tango *)&self->Car1);
  gta2::Player_sub_40E530((struct Player *)&a3, (struct Tango *)&self->Car2);
  if ( sub_497410() )
    goto LABEL_102;
  if ( gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
  {
    v85 = 1;
    unk_66A3FC = *v43;
    v73 = gta2::Weapon_sub_41C1E0((struct Weapon *)&a3);
    v44 = gta2::Weapon_sub_41C1E0((struct Weapon *)&a3.AudioSourceParams);
    v45 = gta2::GameObject_sub_495BF0(self, v44, v73);
    if ( gta2::MapRelatedStruct_sub_462E80(gMapRelatedStruct) != 1 && !v45 )
    {
      gta2::GameObject_sub_4995A0(self);
      v85 = 0;
      goto LABEL_103;
    }
    goto LABEL_102;
  }
  v74 = gta2::Weapon_sub_41C1E0((struct Weapon *)&a3);
  v46 = gta2::Weapon_sub_41C1E0((struct Weapon *)&a3.AudioSourceParams);
  v47 = gta2::GameObject_sub_495540(self, v46, v74);
  if ( unk_66A3C1 )
    sub_495470((char *)self);
  if ( v47 == 1 )
  {
    v85 = 1;
    if ( unk_66A3C2 )
    {
      LOWORD(a3.AudioSourceParams1) = *v43;
      sub_40E490((__int16 *)&a3.AudioSourceParams1);
      sub_41FA70((struct Ped *)&a3.AudioSourceParams1, word_66A5C8);
      gta2::sub_41FC20(&a3.AudioSourceParams1, &a3.AudioSourceParams1);
      gta2::Player_sub_40E530((struct Player *)&v88, (struct Tango *)&unk_66A480);
      gta2::Player_sub_40E530((struct Player *)&a3.field_14, (struct Tango *)&unk_66A74C);
      v75 = gta2::Weapon_sub_41C1E0((struct Weapon *)&a3.field_14);
      v48 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v88);
      if ( gta2::GameObject_sub_495540(self, v48, v75) == 1 )
      {
        LOWORD(a3.AudioSourceParams1) = *v43;
        sub_40E490((__int16 *)&a3.AudioSourceParams1);
        sub_41FA70((struct Ped *)&a3.AudioSourceParams1, word_66A488);
        gta2::sub_41FC20(&v90, &a3.AudioSourceParams1);
        gta2::Player_sub_40E530((struct Player *)&v90, (struct Tango *)&unk_66A480);
        gta2::Player_sub_40E530((struct Player *)&v89, (struct Tango *)&unk_66A74C);
        v76 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v89);
        v49 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v90);
        if ( !gta2::GameObject_sub_495540(self, v49, v76) )
          sub_4923D0((int)self);
      }
      else
      {
        sub_4923A0((int)self);
      }
    }
LABEL_102:
    gta2::sub_41FC20(&a3.AudioSourceParams, &self->Rotation);
    gta2::Player_sub_40E530((struct Player *)&a3.AudioSourceParams, (struct Tango *)&self->Car1);
    gta2::Player_sub_40E530((struct Player *)&a3, (struct Tango *)&self->Car2);
    SpriteS1 = self->SpriteS1_;
    v51 = (int *)gta2::S202_sub_401B20((struct S202 *)&SpriteS1->S3_arr5031[0].PositionY, (struct SpriteS1 *)&v91, (struct PublicTransport *)&a3);
    v52 = (int *)gta2::S202_sub_401B20(
                   (struct S202 *)&SpriteS1->S3_arr5031[0].PositionX,
                   (struct SpriteS1 *)&v90,
                   (struct PublicTransport *)&a3.AudioSourceParams);
    gta2::SpriteS1_sub_420600(SpriteS1, *v52, *v51, SpriteS1->S3_arr5031[0].PositionZ);
    goto LABEL_103;
  }
  sub_4994D0((int)self);
LABEL_103:
  self->Car1 = *(Car **)&unk_66A4D8.Ammo;
  self->Car2 = *(Car **)&unk_66A4D8.Ammo;
  if ( v85 == 1 || (self->field_58 & 1) != 0 )
  {
    v53 = self->SpriteS1_;
    v77 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v53->S3_arr5031[0].PositionZ) - 1;
    v65 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v53->S3_arr5031[0].PositionY);
    v54 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v53->S3_arr5031[0].PositionX);
    unk_66A3C4 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct, v54, v65, v77);
    gta2::GameObject_sub_494180(self);
  }
  sub_499F00(self, unk_66A3C6);
  if ( !gta2::Ped_IsSearchType(self->Ped_, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) )
  {
    if ( self->field_69 )
    {
      if ( sub_49A080(self) == 1 )
      {
        v55 = self->SpriteS1_;
        PositionY = v55->S3_arr5031[0].PositionY;
        a3.AudioSourceParams = (struct AudioSourceParams *)v55->S3_arr5031[0].PositionX;
        a3.field = PositionY;
        v57 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v55->S3_arr5031[0].PositionX);
        LOBYTE(v90) = v57;
        LOBYTE(v91) = gta2::Weapon_sub_41C1E0((struct Weapon *)&v55->S3_arr5031[0].PositionY);
        if ( (unsigned __int8)gta2::Weapon_sub_41C1E0((struct Weapon *)&unk_66A480) != v57
          || (v58 = gta2::Weapon_sub_41C1E0((struct Weapon *)&unk_66A74C), v58 != (_BYTE)v91) )
        {
          gta2::SpriteS1_sub_420600(v55, unk_66A480.CurrentElement, (int)unk_66A74C, (int)unk_66A754);
          v59 = gta2::Weapon_sub_41C1E0(&unk_66A414);
          v78 = v91;
          v66 = v90;
          self->field_45 = v59;
          if ( sub_492420(self, (int)v66, v78) )
          {
            gta2::SpriteS1_sub_420600(self->SpriteS1_, (int)a3.AudioSourceParams, a3.field, (int)unk_66A754);
            v60 = self->SpriteS1_;
            v61 = gta2::Player_sub_401B40((struct Player *)&v60->S3_arr5031[0].PositionZ, (struct S202 *)&v91, (int)&unk_66A46C);
            v79 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v61);
            v67 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v60->S3_arr5031[0].PositionY);
            v62 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v60->S3_arr5031[0].PositionX);
            unk_66A3C4 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct, v62, v67, v79);
            gta2::GameObject_sub_494180(self);
          }
          else
          {
            self->field_69 = 0;
            LOBYTE(self->field_5C) = 10;
          }
        }
      }
    }
  }
  if ( !v84 )
    self->Rotation = a3.AudioSourceParams2;
  sub_4958E0((int)self);
}


// 0x0049b0d0: GameObject::sub_49B0D0
// IDA: GameObject::sub_49B0D0
// Ghidra: ---
void gta2::GameObject_sub_49B0D0(struct GameObject *self)
{
  int v2; // eax
  unsigned int v3; // ecx
  struct SpriteS1 *v4; // eax
  int v5; // eax
  char v6; // bl
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  bool v11; // cl
  struct Ped *Ped; // eax
  struct Ped *field_1A0; // eax
  struct SpriteS1 *v14; // eax
  int v15; // eax
  struct SpriteS1 *v16; // eax
  int v17; // eax
  int *p_Speed; // ebp
  unsigned int v19; // edi
  int v20; // ebx
  unsigned __int16 Rotation; // di
  int v22; // eax
  struct Ped *v23; // ecx
  char v24; // al
  int v25; // eax
  char v26; // bl
  struct S202 *v27; // eax
  struct S202 *v28; // eax
  int v29; // eax
  struct S202 *v30; // eax
  struct SpriteS1 *v31; // eax
  struct S202 *v32; // eax
  struct SpriteS1 *v33; // eax
  struct SpriteS1 *v34; // eax
  __int16 v35; // ax
  char v36; // bl
  char v37; // al
  int v38; // ecx
  int v39; // eax
  int v40; // eax
  unsigned __int16 Index; // bx
  struct CarSystemManager *p_Rotation; // ebp
  struct SpriteS1 *SpriteS1; // edi
  int *v44; // ebx
  int *v45; // eax
  struct CarSystemManager *v46; // ecx
  struct SpriteS1 *v47; // edi
  int v48; // eax
  struct SpriteS1 *v49; // edi
  struct CarSystemManager *PositionY; // edx
  char v51; // bl
  char v52; // al
  char v53; // al
  struct Player *pPlayer; // ecx
  signed __int16 v55; // ax
  int v56; // eax
  struct SpriteS1 *v57; // edi
  struct SpriteS1 *v58; // eax
  int v59; // eax
  int v60; // [esp-Ch] [ebp-4Ch]
  int v61; // [esp-Ch] [ebp-4Ch]
  int v62; // [esp-Ch] [ebp-4Ch]
  int v63; // [esp-Ch] [ebp-4Ch]
  int v64; // [esp-8h] [ebp-48h]
  int v65; // [esp-8h] [ebp-48h]
  int v66; // [esp-8h] [ebp-48h]
  int v67; // [esp-8h] [ebp-48h]
  int v68; // [esp-8h] [ebp-48h]
  int v69; // [esp-8h] [ebp-48h]
  int v70; // [esp-8h] [ebp-48h]
  int v71; // [esp-4h] [ebp-44h]
  int v72; // [esp-4h] [ebp-44h]
  int v73; // [esp-4h] [ebp-44h]
  char v74; // [esp+Ch] [ebp-34h]
  char v75; // [esp+Dh] [ebp-33h]
  char v76; // [esp+Eh] [ebp-32h]
  char v77; // [esp+Fh] [ebp-31h]
  S202 a2; // [esp+10h] [ebp-30h] BYREF
  int v79; // [esp+30h] [ebp-10h] BYREF
  int v80; // [esp+34h] [ebp-Ch] BYREF
  int v81; // [esp+38h] [ebp-8h] BYREF
  int v82; // [esp+3Ch] [ebp-4h] BYREF

  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&a2.S202);
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&a2.field_10);
  v75 = 0;
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&a2.field_1C);
  v74 = 0;
  self->CigaretteIdleTimer = 500;
  gta2::bitShiftLeft1(&a2.field_18, 0);
  v2 = a2.field_18;
  v3 = self->field_58 & 0xFFFFFFB7;
  a2.CarSystemManager = (struct CarSystemManager *)a2.field_18;
  self->field_58 = v3;
  a2.field_C = v2;
  unk_66A3C4 = 0;
  v76 = gta2::Weapon_sub_41C1E0((struct Weapon *)&unk_66A480);
  unk_66A554 = v76;
  v77 = gta2::Weapon_sub_41C1E0((struct Weapon *)&unk_66A74C);
  byte_66A72C = v77;
  if ( (self->field_58 & 1) == 0
    && (v4 = sub_42A630((struct SpriteS1 *)&a2.field_18, (struct S202 *)&unk_66A754),
        gta2::Player_IsCurrentPlayer((struct Player *)v4, (struct Player *)&unk_66A4D8))
    && gta2::Car_sub_403800((struct Car *)&unk_66A754, (int)&unk_66A4D8) )
  {
    v71 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A754) - 1;
    v64 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A74C);
    v5 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A480);
    v6 = gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct, v5, v64, v71);
    v7 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A754) - 1;
  }
  else
  {
    v72 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A754);
    v65 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A74C);
    v8 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A480);
    v6 = gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct, v8, v65, v72);
    v7 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A754);
  }
  v73 = v7;
  v66 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A74C);
  v9 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A480);
  v10 = gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct, v9, v66, v73);
  if ( v10 )
  {
    v11 = (*(_BYTE *)(v10 + 11) & 0xFC) != 0 && (*(_BYTE *)(v10 + 11) & 0xFC) != 0xFC;
    self->field_58 ^= (v11 ^ (unsigned __int8)self->field_58) & 1;
    if ( gta2::Style_sub_491F80(gStyle, *(_WORD *)(v10 + 8) & 0x3FF) && self->field_10 != 15 )
    {
      Ped = self->Ped_;
      if ( (Ped->PositionX1 & 0x8000000) == 0 )
      {
        LOWORD(Ped->XCoordinate) += 3;
        field_1A0 = (struct Ped *)self->Ped_->PedId;
        if ( field_1A0 )
        {
          if ( gta2::Character_FindPed(gCharacter, field_1A0) )
          {
            self->Ped_->field_22C = 2;
            LOBYTE(self->Ped_->ID) = 50;
          }
        }
      }
    }
  }
  if ( gta2::GameObject_sub_491E40(self) )
  {
    gta2::Ped_sub_433220(self->Ped_);
    gta2::GameObject_sub_4938A0(self);
    return;
  }
  if ( !v6 && (self->field_58 & 1) == 0 )
  {
    if ( self->field_10 == 15 )
    {
      v16 = gta2::Player_sub_401B40((struct Player *)&unk_66A754, (struct S202 *)&a2.field_18, (int)&unk_66A46C);
      v68 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v16);
      v61 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A74C);
      v17 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A480);
      if ( !gta2::MapRelatedStruct_sub_492140(gMapRelatedStruct, v17, v61, v68) )
        goto LABEL_28;
      gta2::GameObject_sub_493710(self);
    }
    else
    {
      v14 = gta2::Player_sub_401B40((struct Player *)&unk_66A754, (struct S202 *)&a2.field_18, (int)&unk_66A46C);
      v67 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v14);
      v60 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A74C);
      v15 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&unk_66A480);
      if ( !gta2::MapRelatedStruct_sub_492140(gMapRelatedStruct, v15, v60, v67) )
      {
        gta2::Ped_UpdatePedState(self->Ped_, 8);
        gta2::Ped_sub_4332B0(self->Ped_, 19);
        self->field_16 = 1;
        return;
      }
      gta2::GameObject_sub_493710(self);
      self->Speed = (int)unk_66A634.FirstElement;
    }
    self->field_58 |= 0x40u;
    sub_40E490(&self->Rotation);
  }
LABEL_28:
  p_Speed = &self->Speed;
  v19 = self->field_58 & 0xFFFFFFF7;
  self->field_58 = v19;
  if ( gta2::sub_4037E0(&self->Speed) )
  {
    self->field_58 = v19 | 8;
    self->Rotation = *(_WORD *)gta2::sub_40E5A0((struct CarSystemManager *)&self->Rotation, (struct CarSystemManager *)&a2, &unk_66A5F4);
    *p_Speed = (int)gta2::JustCopyByPtrAtoC(&self->Speed, (struct SpriteS1 *)&a2.field_18)->FirstElement;
  }
  self->field_44 = v6;
  a2.field_18 = self->field_58;
  v20 = (a2.field_18 >> 6) & 1;
  if ( v20 )
    Rotation = self->Rotation;
  else
    Rotation = *gta2::sub_492CC0(self->Ped_, &a2);
  v22 = self->field_10;
  LOWORD(a2.S202) = Rotation;
  if ( v22 == 10 )
  {
    if ( gta2::Car_sub_403800((struct Car *)&self->Speed, (int)&unk_66A574) )
      *p_Speed = unk_66A428;
    v74 = 1;
  }
  else
  {
    if ( v22 != 15 )
      goto LABEL_53;
    if ( self->field_6C == 5 )
    {
      if ( v20 )
        goto LABEL_53;
      v23 = self->Ped_;
      if ( (v23->PositionZ2 & 0x10) != 0 )
        Rotation = self->Rotation;
      else
        Rotation = *gta2::sub_492CC0(v23, &a2);
      LOWORD(a2.S202) = Rotation;
    }
    else
    {
      self->field_6C = 5;
      self->field_68 = 0;
      self->field_71 = 4;
    }
    if ( !v20 )
    {
      if ( (self->Ped_->PositionZ2 & 0x10) != 0 )
      {
        if ( gta2::sub_4037E0(&unk_66A564) )
        {
          *p_Speed = unk_66A798;
        }
        else if ( gta2::sub_4037E0(&unk_66A564) )
        {
          *p_Speed = unk_66A574;
        }
        else
        {
          *p_Speed = (int)unk_66A504;
        }
      }
      else
      {
        *p_Speed = (int)unk_66A504;
      }
    }
  }
LABEL_53:
  v24 = self->field_55;
  if ( v24 )
    self->field_55 = v24 - 1;
  LOWORD(v25) = gta2::Car_sub_403820((struct Car *)&self->Speed, &unk_66A634);
  if ( v25 )
  {
    if ( self->field_69 )
    {
      v74 = 1;
      *p_Speed = (int)unk_66A504;
    }
    if ( v20 || gta2::sub_492FD0(self->Ped_) )
      v74 = 1;
    LOWORD(a2.field_10) = Rotation;
    if ( SLOBYTE(a2.field_18) >= 0 )
    {
      if ( !self->field_6A )
        goto LABEL_69;
      if ( self->field_C == 3 )
        goto LABEL_70;
      v35 = self->Rotation;
      Rotation = self->field_74;
      *p_Speed = unk_66A574;
      *(_WORD *)&a2.field_1C = v35;
      v74 = 1;
    }
    else
    {
      v26 = self->field_73;
      gta2::S202_sub_40CE30(&a2, v26);
      gta2::S202_sub_401B20(v27, (struct SpriteS1 *)&a2.pPlayer, (struct PublicTransport *)&unk_66A65C);
      gta2::S202_sub_40CE30((struct S202 *)&v80, self->field_72);
      gta2::S202_sub_401B20(v28, (struct SpriteS1 *)&v79, (struct PublicTransport *)&unk_66A65C);
      a2.pPlayer = (struct Player *)gta2::sub_42A6B0(&v81, &v81)->Car;
      if ( gta2::sub_4037E0(&a2.pPlayer) )
      {
        v29 = a2.field_18;
        LOBYTE(v29) = a2.field_18 & 0x7F;
        self->field_58 = v29;
        goto LABEL_69;
      }
      gta2::S202_sub_40CE30((struct S202 *)&v79, self->field_72);
      v31 = gta2::S202_sub_401B20(v30, (struct SpriteS1 *)&v80, (struct PublicTransport *)&unk_66A65C);
      gta2::Player_sub_401B40((struct Player *)v31, (struct S202 *)&v81, (int)&unk_66A480);
      gta2::S202_sub_40CE30((struct S202 *)&v82, v26);
      v33 = gta2::S202_sub_401B20(v32, (struct SpriteS1 *)&a2.pPlayer, (struct PublicTransport *)&unk_66A65C);
      v34 = gta2::Player_sub_401B40((struct Player *)v33, (struct S202 *)&a2.field_18, (int)&unk_66A74C);
      Rotation = *sub_40E8D0((struct Ped *)&a2, (struct Car *)&a2, v34);
      LOWORD(a2.field_10) = Rotation;
    }
    LOWORD(a2.S202) = Rotation;
LABEL_69:
    if ( self->field_C != 3 )
    {
LABEL_73:
      gta2::sub_41FC20(&a2.S202, &a2.S202);
      gta2::Player_sub_40E530((struct Player *)&a2.field_C, (struct Tango *)&unk_66A480);
      gta2::Player_sub_40E530((struct Player *)&a2.CarSystemManager, (struct Tango *)&unk_66A74C);
      v36 = gta2::Weapon_sub_41C1E0((struct Weapon *)&a2.field_C);
      LOBYTE(a2.pPlayer) = v36;
      v37 = gta2::Weapon_sub_41C1E0((struct Weapon *)&a2.CarSystemManager);
      LOBYTE(a2.field_18) = v37;
      if ( v76 != v36 || v77 != v37 )
      {
        gta2::GameObject_sub_494180(self);
        if ( !sub_492420(self, (int)a2.pPlayer, (struct SpriteS1 *)a2.field_18) )
        {
          v38 = self->field_58;
          v39 = self->field_C;
          LOBYTE(v38) = v38 | 0x80;
          self->field_58 = v38;
          if ( v39 == 3 )
            gta2::sub_496500((int)self);
          else
            gta2::sub_492D00(self);
          Rotation = unk_66A3FC;
          LOWORD(a2.S202) = unk_66A3FC;
          LOWORD(a2.field_10) = unk_66A3FC;
        }
      }
      goto LABEL_80;
    }
LABEL_70:
    if ( self->field_55 && SLOBYTE(self->field_58) >= 0 )
    {
      Rotation = (unsigned __int16)self->SpriteS1_->FirstElement;
      LOWORD(a2.field_10) = Rotation;
      LOWORD(a2.S202) = Rotation;
    }
    goto LABEL_73;
  }
LABEL_80:
  v40 = self->field_10;
  if ( v40 == 28 || v40 == 29 || v74 )
  {
    p_Rotation = (struct CarSystemManager *)&self->Rotation;
  }
  else
  {
    Index = gta2::sub_4928B0((int)self, (struct CarSystemManager *)&a2, (__int16)a2.S202)->Index;
    LOWORD(a2.field_0) = Index;
    if ( (unsigned __int8)gta2::sub_492C30(self, Index) == 1 )
    {
      p_Rotation = (struct CarSystemManager *)&self->Rotation;
      v75 = 1;
      self->Rotation = Index;
      goto LABEL_89;
    }
    p_Rotation = (struct CarSystemManager *)&self->Rotation;
    if ( gta2::CarSystemManager_NotEqual((struct CarSystemManager *)&a2.field_10, (struct SpriteS1 *)&a2.S202) )
    {
      p_Rotation->Index = (unsigned __int16)a2.field_10;
      goto LABEL_89;
    }
  }
  p_Rotation->Index = Rotation;
LABEL_89:
  if ( (self->field_58 & 0x40) != 0 )
    self->Speed = (int)unk_66A504;
  gta2::sub_41FC20(&a2.CarSystemManager, p_Rotation);
  SpriteS1 = self->SpriteS1_;
  v44 = (int *)gta2::S202_sub_401B20(
                 (struct S202 *)&SpriteS1->S3_arr5031[0].PositionY,
                 (struct SpriteS1 *)&v82,
                 (struct PublicTransport *)&a2.CarSystemManager);
  v45 = (int *)gta2::S202_sub_401B20(
                 (struct S202 *)&SpriteS1->S3_arr5031[0].PositionX,
                 (struct SpriteS1 *)&v81,
                 (struct PublicTransport *)&a2.field_C);
  gta2::SpriteS1_sub_420600(SpriteS1, *v45, *v44, SpriteS1->S3_arr5031[0].PositionZ);
  LOWORD(v46) = p_Rotation->Index;
  gta2::SpriteS1_SetRotation(self->SpriteS1_, v46);
  if ( self->field_69 )
    v75 = 1;
  if ( gta2::sub_492FD0(self->Ped_) )
  {
    v75 = 1;
  }
  else if ( v75 != 1 && (self->field_58 & 1) == 0 )
  {
    goto LABEL_98;
  }
  v47 = self->SpriteS1_;
  v69 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v47->S3_arr5031[0].PositionZ) - 1;
  v62 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v47->S3_arr5031[0].PositionY);
  v48 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v47->S3_arr5031[0].PositionX);
  unk_66A3C4 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct, v48, v62, v69);
  gta2::GameObject_sub_494180(self);
LABEL_98:
  sub_499F00(self, unk_66A3C6);
  if ( self->field_69 )
  {
    if ( sub_49A080(self) == 1 )
    {
      v49 = self->SpriteS1_;
      PositionY = (struct CarSystemManager *)v49->S3_arr5031[0].PositionY;
      a2.field_C = v49->S3_arr5031[0].PositionX;
      a2.CarSystemManager = PositionY;
      LOBYTE(a2.pPlayer) = gta2::Weapon_sub_41C1E0((struct Weapon *)&v49->S3_arr5031[0].PositionX);
      v51 = gta2::Weapon_sub_41C1E0((struct Weapon *)&v49->S3_arr5031[0].PositionY);
      LOBYTE(a2.field_18) = v51;
      v52 = gta2::Weapon_sub_41C1E0((struct Weapon *)&unk_66A480);
      if ( v52 != LOBYTE(a2.pPlayer) || (unsigned __int8)gta2::Weapon_sub_41C1E0((struct Weapon *)&unk_66A74C) != v51 )
      {
        gta2::SpriteS1_sub_420600(v49, unk_66A480.CurrentElement, (int)unk_66A74C, (int)unk_66A754);
        v53 = gta2::Weapon_sub_41C1E0(&unk_66A414);
        pPlayer = a2.pPlayer;
        self->field_45 = v53;
        if ( sub_492420(self, (int)pPlayer, (struct SpriteS1 *)a2.field_18) )
        {
          gta2::SpriteS1_sub_420600(self->SpriteS1_, a2.field_C, (int)a2.CarSystemManager, (int)unk_66A754);
          if ( v75 == 1 || (self->field_58 & 1) != 0 )
          {
            v57 = self->SpriteS1_;
            v58 = gta2::Player_sub_401B40((struct Player *)&v57->S3_arr5031[0].PositionZ, (struct S202 *)&v82, (int)&unk_66A46C);
            v70 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v58);
            v63 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v57->S3_arr5031[0].PositionY);
            v59 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v57->S3_arr5031[0].PositionX);
            unk_66A3C4 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct, v59, v63, v70);
            gta2::GameObject_sub_494180(self);
          }
        }
        else
        {
          self->field_69 = 0;
          LOBYTE(self->field_5C) = 10;
          if ( unk_66A3C8 )
          {
            a2.field_18 = 4;
            v55 = gta2::Random_Random(&gRandom, (__int16 *)&a2.field_18);
            if ( v55 )
            {
              v56 = v55 - 1;
              if ( v56 )
              {
                if ( v56 == 1 )
                  p_Rotation->Index = unk_66A514;
                else
                  p_Rotation->Index = unk_66A73C;
              }
              else
              {
                p_Rotation->Index = unk_66A5F4.Index;
              }
            }
            else
            {
              p_Rotation->Index = unk_66A434.Index;
            }
          }
        }
      }
    }
    else
    {
      self->field_69 = 0;
      self->field_2A = unk_66A434.Index;
      LOBYTE(self->field_5C) = 10;
    }
  }
  if ( self->field_6A )
    p_Rotation->Index = *(_WORD *)&a2.field_1C;
  if ( (self->field_58 & 8) != 0 )
  {
    p_Rotation->Index = *(_WORD *)gta2::sub_40E5A0(p_Rotation, (struct CarSystemManager *)&a2, &unk_66A5F4);
    self->Speed = (int)gta2::JustCopyByPtrAtoC(&self->Speed, (struct SpriteS1 *)&v82)->FirstElement;
  }
  sub_4958E0((int)self);
}


// 0x0049bad0: GameObject::sub_49BAD0
// IDA: GameObject::sub_49BAD0
// Ghidra: GameObject::FUN_0049bad0
byte gta2::GameObject_sub_49BAD0(struct GameObject *self)
{
  byte *this_00;
  undefined2 uVar1;
  undefined2 *puVar2;
  undefined4 uVar3;
  byte bVar4;
  bool bVar5;
  undefined1 uVar6;
  char cVar7;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  struct SpriteS1 *pSVar8;
  struct SpriteS1 *pSVar9;
  uint uVar10;
  
  pSVar9 = (struct SpriteS1 *)self->S7[0].AnimationFrame;
  if (pSVar9 == (struct SpriteS1 *)0x4) {
    self->MaxHealth = self->MaxHealth & 0xffffff7f;
    gta2::GameObject_sub_49B0D0();
    bVar4 = gta2::Ped_sub_433CA0((struct Ped *)self->ScriptRef);
    pSVar9 = (struct SpriteS1 *)(uint)bVar4;
    if ((bVar4 == 0) && (self->S7[0].doorState != 0xf)) {
      this_00 = &self->S7[2].ID;
      bVar5 = gta2::Car_sub_403800((struct Car *)this_00,(int *)&DAT_0066a574);
      if (CONCAT31(extraout_var,bVar5) != 0) {
        self->PhysicsFlags = 1;
        return bVar5;
      }
      bVar5 = gta2::Car_IsTrainOrTrainCarriage((struct Car *)this_00,(struct Car *)&DAT_0066a634);
      if (CONCAT31(extraout_var_00,bVar5) != 0) {
        self->PhysicsFlags = 0;
        return bVar5;
      }
      pSVar9 = *(SpriteS1 **)&self->AIFlags;
      self->PhysicsFlags = 2;
      if (pSVar9 != NULL) {
        puVar2 = (undefined2 *)pSVar9->Matrix3DArray[1].PositionX;
        *(undefined2 *)&self->S7[3].doorState = *puVar2;
        return (byte)puVar2;
      }
    }
  }
  else if (pSVar9 == (struct SpriteS1 *)0x6) {
    uVar3._0_1_ = self->AIState;
    uVar3._1_1_ = self->AISubState;
    uVar3._2_1_ = self->AITarget;
    uVar3._3_1_ = self->AITimer;
    self->S7[0].doorState = 0x24;
    pSVar8 = gta2::S56_sub_447740(gCheckpoint,uVar3,0);
    pSVar9 = pSVar8;
    if ((pSVar8 != NULL) &&
       (pSVar9 = (struct SpriteS1 *)gta2::SpriteS1_getSpriteType(pSVar8),
       pSVar9 == (struct SpriteS1 *)0x2)) {
      pSVar8 = (struct SpriteS1 *)pSVar8->Matrix3DArray[0].Car;
      pSVar9 = (struct SpriteS1 *)gta2::Ped_GetCurrentCar((struct Ped *)self->ScriptRef);
      if (pSVar8 != pSVar9) {
        bVar5 = gta2::Car_sub_421720((struct Car *)pSVar8);
        pSVar9 = (struct SpriteS1 *)(uint)bVar5;
        if ((!bVar5) &&
           (pSVar9 = (struct SpriteS1 *)FUN_00435d90(pSVar8), (char)pSVar9 == '\0'))
        goto LAB_0049bc0f;
      }
    }
    if (self->PhysicsFlags != 6) {
      uVar1 = **(undefined2 **)(*(int *)&self->AIFlags + 0x50);
      self->PhysicsFlags = 6;
      *(undefined2 *)&self->S7[3].doorState = uVar1;
      *(undefined1 *)&self->CollisionData = 0;
      uVar6 = gta2::Ped_GetAnimationState((struct Ped *)self->ScriptRef);
      cVar7 = FUN_004224a0(uVar6);
      if (cVar7 != '\0') {
        uVar10 = self->MaxHealth | 0x10;
        self->MaxHealth = uVar10;
        self->BehaviorFlags = 0;
        return (byte)uVar10;
      }
      pSVar9 = (struct SpriteS1 *)(self->MaxHealth & 0xffffffef);
      self->BehaviorFlags = 0;
      self->MaxHealth = pSVar9;
    }
  }
LAB_0049bc0f:
  return (byte)pSVar9;
}


// 0x0049bc20: GameObject::sub_49BC20
// IDA: GameObject::sub_49BC20
// Ghidra: GameObject::FUN_0049bc20
byte gta2::GameObject_sub_49BC20(struct GameObject *self)
{
  byte *this_00;
  int iVar1;
  struct Car *this_01;
  byte bVar2;
  bool bVar3;
  undefined1 uVar4;
  char cVar5;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined4 *puVar6;
  undefined3 extraout_var_01;
  uint uVar7;
  undefined4 *puVar8;
  
  uVar7 = self->S7[0].AnimationFrame;
  if (uVar7 == 4) {
    self->MaxHealth = self->MaxHealth & 0xffffff7f;
    gta2::GameObject_sub_49B0D0();
    bVar2 = gta2::Ped_sub_433CA0((struct Ped *)self->ScriptRef);
    uVar7 = (uint)bVar2;
    if ((bVar2 == 0) && (self->S7[0].doorState != 0xf)) {
      this_00 = &self->S7[2].ID;
      bVar3 = gta2::Car_sub_403800((struct Car *)this_00,(int *)&DAT_0066a574);
      if (CONCAT31(extraout_var,bVar3) != 0) {
        self->PhysicsFlags = 1;
        return bVar3;
      }
      bVar3 = gta2::Car_IsTrainOrTrainCarriage((struct Car *)this_00,(struct Car *)&DAT_0066a634);
      if (CONCAT31(extraout_var_00,bVar3) != 0) {
        self->PhysicsFlags = 0;
        return bVar3;
      }
      iVar1 = *(int *)&self->AIFlags;
      self->PhysicsFlags = 2;
      *(undefined2 *)&self->S7[3].doorState = **(undefined2 **)(iVar1 + 0x50);
      return (byte)iVar1;
    }
  }
  else if ((uVar7 == 6) && (self->PhysicsFlags != 6)) {
    this_01 = *(Car **)&self->AIFlags;
    iVar1 = *(int *)&self->AIState;
    *(short *)&self->S7[3].doorState = (short)this_01->CarSprite->field0_0x0;
    puVar8 = (undefined4 *)(iVar1 + 0x18);
    puVar6 = (undefined4 *)(iVar1 + 0x14);
    uVar4 = gta2::Ped_GetAnimationState((struct Ped *)self->ScriptRef);
    gta2::Car_sub_422500(this_01,CONCAT31(extraout_var_01,uVar4),puVar6,puVar8);
    self->PhysicsFlags = 6;
    *(undefined1 *)&self->CollisionData = 0;
    uVar4 = gta2::Ped_GetAnimationState((struct Ped *)self->ScriptRef);
    cVar5 = FUN_004224a0(uVar4);
    uVar7 = (byte)-(cVar5 != '\0') & 3;
    self->BehaviorFlags = (byte)uVar7;
  }
  return (byte)uVar7;
}


// 0x0049bd10: GameObject::sub_49BD10
// IDA: GameObject::sub_49BD10
// Ghidra: GameObject::FUN_0049bd10
byte gta2::GameObject_sub_49BD10(struct GameObject *self)
{
  short sVar1;
  uint uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  bool bVar6;
  byte bVar7;
  byte bVar8;
  ushort uVar9;
  short *psVar10;
  struct Player *this_00;
  undefined3 extraout_var;
  int iVar11;
  int iVar12;
  int iVar13;
  struct Ped *pPVar14;
  undefined2 *puVar15;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  undefined3 extraout_var_08;
  uint uVar16;
  struct Player *pPlayer;
  struct GameObject *local_4;
  
  uVar3 = DAT_0066a634_1;
  uVar4 = uRam0066a636;
  uVar5 = uRam0066a637;
  self->S7[2].ID = DAT_0066a634;
  self->S7[2].field4_0xd = uVar3;
  self->S7[2].field5_0xe = uVar4;
  self->S7[2].field6_0xf = uVar5;
  local_4 = self;
  if (self->S7[0].doorState != 0xf) {
    gta2::GameObject_sub_491EC0(self);
  }
  bVar6 = gta2::Ped_IsSearchType((struct Ped *)self->ScriptRef,
                             SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
  if (bVar6) {
    psVar10 = (short *)FUN_00436140(&local_4);
    gta2::CarSystemManager_FUN_0041fa70((struct CarSystemManager *)&self->S7[3].doorState,psVar10);
    if (self->S7[0].doorState == 0xf) {
      gta2::GameObject_sub_49A560(self);
      gta2::GameObject_set_ped_state_1(self,0);
      bVar7 = gta2::GameObject_sub_433A50(self,0);
      return bVar7;
    }
    if ((*(byte *)&self->MaxHealth & 1) == 0) {
      pPlayer = (struct Player *)&DAT_0066a4d8;
      this_00 = (struct Player *)FUN_0042a630(&local_4,&DAT_0066a754);
      bVar6 = gta2::Player_IsCurrentPlayer(this_00,pPlayer);
      if (CONCAT31(extraout_var,bVar6) == 0) goto LAB_0049bde4;
      iVar11 = DecoderFloat(&DAT_0066a754);
      iVar11 = iVar11 + -1;
      iVar12 = DecoderFloat(&DAT_0066a74c);
      iVar13 = DecoderFloat(&DAT_0066a480);
      gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct,iVar13,iVar12,iVar11);
      iVar11 = DecoderFloat(&DAT_0066a754);
      iVar11 = iVar11 + -1;
    }
    else {
LAB_0049bde4:
      iVar11 = DecoderFloat(&DAT_0066a754);
      iVar12 = DecoderFloat(&DAT_0066a74c);
      iVar13 = DecoderFloat(&DAT_0066a480);
      gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct,iVar13,iVar12,iVar11);
      iVar11 = DecoderFloat(&DAT_0066a754);
    }
    iVar12 = DecoderFloat(&DAT_0066a74c);
    iVar13 = DecoderFloat(&DAT_0066a480);
    iVar11 = gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct,iVar13,iVar12,iVar11);
    if (((iVar11 != 0) &&
        (bVar7 = FUN_00491f80(gStyle,*(ushort *)(iVar11 + 8) & 0x3ff),
        bVar7 != 0)) && ((*(uint *)(self->ScriptRef + 0x21c) & 0x8000000) == 0))
    {
      psVar10 = (short *)(self->ScriptRef + 0x210);
      *psVar10 = *psVar10 + 3;
      iVar11 = *(int *)(self->ScriptRef + 0x204);
      if ((iVar11 != 0) &&
         (pPVar14 = gta2::Character_FindPed(gCharacter,iVar11), pPVar14 != NULL)) {
        *(undefined4 *)(self->ScriptRef + 0x290) = 2;
        *(undefined1 *)(self->ScriptRef + 0x264) = 0x32;
      }
    }
    if (self->PhysicsFlags != 4) {
      self->PhysicsFlags = 2;
    }
  }
  else {
    puVar15 = (undefined2 *)FUN_00492cc0(&local_4);
    *(undefined2 *)&self->S7[3].doorState = *puVar15;
  }
  iVar11 = self->S7[0].doorState;
  if (iVar11 == 0xf) {
    uVar3 = gS51_1_1;
    uVar4 = uRam0066a506;
    uVar5 = uRam0066a507;
    self->S7[2].ID = gS51_1;
    self->S7[2].field4_0xd = uVar3;
    self->S7[2].field5_0xe = uVar4;
    self->S7[2].field6_0xf = uVar5;
  }
  if (((*(char *)((int)&self->CollisionData + 2) == '\0') && (iVar11 != 0xf)) &&
     ((bVar6 = gta2::Car_IsTrainOrTrainCarriage((struct Car *)&self->Car,(struct Car *)&DAT_0066a4d8),
      CONCAT31(extraout_var_00,bVar6) == 0 &&
      (bVar6 = gta2::Car_IsTrainOrTrainCarriage((struct Car *)&self->s38,(struct Car *)&DAT_0066a4d8),
      CONCAT31(extraout_var_01,bVar6) == 0)))) {
    if (((*(byte *)&self->MaxHealth & 1) == 0) &&
       (((((bVar6 = gta2::Player_IsCurrentPlayer((struct Player *)&DAT_0066a754,(struct Player *)&DAT_0066a46c),
           CONCAT31(extraout_var_02,bVar6) != 0 ||
           (bVar6 = gta2::Player_IsCurrentPlayer((struct Player *)&DAT_0066a754,(struct Player *)&DAT_0066a54c),
           CONCAT31(extraout_var_03,bVar6) != 0)) ||
          (bVar6 = gta2::Player_IsCurrentPlayer((struct Player *)&DAT_0066a754,(struct Player *)&DAT_0066a468),
          CONCAT31(extraout_var_04,bVar6) != 0)) ||
         ((bVar6 = gta2::Player_IsCurrentPlayer((struct Player *)&DAT_0066a754,(struct Player *)&DAT_0066a71c),
          CONCAT31(extraout_var_05,bVar6) != 0 ||
          (bVar6 = gta2::Player_IsCurrentPlayer((struct Player *)&DAT_0066a754,(struct Player *)&DAT_0066a3f0),
          CONCAT31(extraout_var_06,bVar6) != 0)))) ||
        ((bVar6 = gta2::Player_IsCurrentPlayer((struct Player *)&DAT_0066a754,(struct Player *)&DAT_0066a794),
         CONCAT31(extraout_var_07,bVar6) != 0 ||
         (bVar6 = gta2::Player_IsCurrentPlayer((struct Player *)&DAT_0066a754,(struct Player *)&DAT_0066a41c),
         CONCAT31(extraout_var_08,bVar6) != 0)))))) {
      iVar11 = DecoderFloat(&DAT_0066a754);
      iVar11 = iVar11 + -1;
    }
    else {
      iVar11 = DecoderFloat(&DAT_0066a754);
    }
    iVar12 = DecoderFloat(&DAT_0066a74c);
    iVar13 = DecoderFloat(&DAT_0066a480);
    bVar8 = gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct,iVar13,iVar12,iVar11);
    bVar7 = bVar8;
    gta2::GameObject_sub_491E40(self);
    if (bVar7 != 0) {
      gta2::Ped_sub_433220((struct Ped *)self->ScriptRef);
      bVar7 = gta2::GameObject_sub_4938A0(self);
      return bVar7;
    }
    if (((bVar8 == 0) && ((*(byte *)&self->MaxHealth & 1) == 0)) &&
       (self->S7[0].doorState != 0xf)) {
      gta2::Ped_UpdatePedState((struct Ped *)self->ScriptRef,PEDSTATE_FALL);
      bVar7 = gta2::Ped_sub_4332B0((struct Ped *)self->ScriptRef,0x13);
      *(undefined1 *)((int)&self->S7[0].PedInDoor + 2) = 1;
      return bVar7;
    }
  }
  else {
    self->ModelId = 0;
    self->S7[0].AnimationFrame = 0;
    gta2::GameObject_sub_49A560(self);
    uVar16 = self->S7[0].doorState;
    self->ModelId = 7;
    self->S7[0].AnimationFrame = 0xe;
    if (uVar16 == 0xf) goto LAB_0049c10f;
  }
  iVar11 = self->S7[0].AnimationFrame;
  uVar16 = iVar11 - 8;
  if ((uVar16 != 0) && (uVar16 = iVar11 - 9, uVar16 != 0)) {
    uVar16 = iVar11 - 0xe;
    if (uVar16 == 0) {
      pPVar14 = (struct Ped *)self->ScriptRef;
      bVar7 = gta2::Ped_sub_433CA0(pPVar14);
      if (bVar7 == 1) {
        uVar2._0_1_ = pPVar14->CurrentAction;
        uVar2._1_1_ = pPVar14->DamageState;
        uVar2._2_1_ = pPVar14->uns60;
        uVar2._3_1_ = pPVar14->uns61;
        uVar16 = self->PhysicsFlags;
        if ((uVar2 & 0x200) != 0) {
          if (uVar16 != 4) {
            self->PhysicsFlags = 4;
            *(undefined1 *)&self->CollisionData = 0;
            return (byte)uVar16;
          }
          goto LAB_0049c10f;
        }
        if (uVar16 != 4) goto LAB_0049c09d;
      }
      else if (self->PhysicsFlags != 4) {
        bVar6 = gta2::Ped_IsSearchType(pPVar14,SEARCHTYPE_AREA_PLAYER_ONLY|
                                           SEARCHTYPE_LINE_OF_SIGHT);
        uVar9 = (ushort)bVar6;
        if (!bVar6) {
          bVar6 = gta2::Ped_IsSearchType((struct Ped *)self->ScriptRef,
                                     SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
          uVar9 = (ushort)bVar6;
          if (!bVar6) goto LAB_0049c0ff;
        }
        sVar1._0_1_ = self->S7[3].field5_0xe;
        sVar1._1_1_ = self->S7[3].field6_0xf;
        if (sVar1 == 0) {
          local_4 = (struct GameObject *)0x258;
          uVar9 = gta2::Random_Random((struct Random *)&gRandom,(short)&local_4);
          if ((uVar9 < 4) && (uVar9 = 0x23, self->S7[0].doorState != 0x23)) {
            self->S7[0].doorState = 0x23;
            *(undefined1 *)&self->CollisionData = 0;
            self->BehaviorFlags = 0;
          }
        }
LAB_0049c0ff:
        self->PhysicsFlags = 2;
        return (byte)uVar9;
      }
      uVar16 = (uint)*(byte *)&self->CollisionData;
      if (*(byte *)&self->CollisionData != 0) goto LAB_0049c10f;
    }
LAB_0049c09d:
    self->PhysicsFlags = 2;
    return (byte)uVar16;
  }
  self->PhysicsFlags = 9;
LAB_0049c10f:
  return (byte)uVar16;
}


// 0x0049c120: GameObject::sub_49C120
// IDA: GameObject::sub_49C120
// Ghidra: GameObject::FUN_0049c120
void gta2::GameObject_sub_49C120(struct GameObject *self)
{
  int *this_00;
  struct Car **pS127;
  undefined2 uVar1;
  void *pPed;
  SpawnPoint *this_01;
  Sprite *pSVar2;
  undefined4 uVar3;
  bool bVar4;
  short sVar5;
  undefined2 *puVar6;
  struct SpriteS1 *pSVar7;
  struct SpriteS1 *pSVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  short *unaff_ESI;
  void *unaff_EDI;
  undefined1 local_14 [4];
  struct SpriteS1 *local_10;
  undefined1 local_c [12];
  
  gta2::Ped_sub_403A40((struct Ped *)self->ScriptRef);
  if (*(char *)((int)&self->S7[0].PedInDoor + 2) == '\x01') {
    iVar10 = self->S7[0].doorState;
    if (iVar10 == 0x21) {
      if (self->PhysicsFlags == 0xf) goto LAB_0049c1cc;
      self->PhysicsFlags = 0xf;
    }
    else {
      if (iVar10 != 0x22) {
        if (self->PhysicsFlags != 0x15) {
          local_10 = (struct SpriteS1 *)0x3;
          sVar5 = gta2::Random_Random((struct Random *)&gRandom,(short)&local_10);
          if (sVar5 == 0) {
            self->PhysicsFlags = 0xe;
          }
          else if (sVar5 == 1) {
            self->PhysicsFlags = 0x13;
          }
          else if (sVar5 == 2) {
            self->PhysicsFlags = 0x14;
          }
        }
        goto LAB_0049c1cc;
      }
      if (self->PhysicsFlags == 0x10) goto LAB_0049c1cc;
      this_00 = &self->S7[3].doorState;
      puVar6 = (undefined2 *)
               gta2::sub_40E5A0((struct CarSystemManager *)this_00,(struct Ped *)local_14,
                          (short *)&DAT_0066a5f4,unaff_EDI,unaff_ESI);
      uVar1 = *puVar6;
      self->PhysicsFlags = 0x10;
      *(undefined2 *)this_00 = uVar1;
    }
    *(undefined1 *)&self->CollisionData = 0;
LAB_0049c1cc:
    pPed = (void *)self->ScriptRef;
    *(undefined1 *)((int)&self->S7[0].PedInDoor + 2) = 0;
    this_01 = *(SpawnPoint **)((int)pPed + 0x164);
    if ((this_01 != NULL) && (this_01->field0_0x0 != 0)) {
      gta2::S169_sub_404D40(this_01,pPed);
      *(undefined4 *)(self->ScriptRef + 0x164) = 0;
    }
    pSVar7 = *(SpriteS1 **)&self->AIState;
    *(undefined2 *)&self->S7[2].PedInDoor = 0;
    gta2::S56_sub_447480(gCheckpoint2,pSVar7);
    gta2::GameObject_sub_494180(self);
    pSVar2 = *(Sprite **)&self->AIState;
    pSVar7 = gta2::S202_sub_401B20((Point2D *)&pSVar2->field_0x18,(struct SpriteS1 *)&local_10,
                        (struct S127 *)&self->s38);
    pSVar8 = gta2::S202_sub_401B20((Point2D *)&pSVar2->Point2D1,(struct SpriteS1 *)local_14,
                        (struct S127 *)&self->Car);
    gta2::SpriteS1_sub_420600(pSVar2,(int)pSVar8->FirstElement,
                        (int)pSVar7->FirstElement,(int)pSVar2->Point2D);
    return;
  }
  switch(self->PhysicsFlags) {
  case 0xd:
  case 0xe:
  case 0x13:
  case 0x14:
    pS127 = &self->Car;
    bVar4 = gta2::Car_IsTrainOrTrainCarriage((struct Car *)pS127,(struct Car *)&DAT_0066a4d8);
    if ((CONCAT31(extraout_var,bVar4) != 0) ||
       (bVar4 = gta2::Car_IsTrainOrTrainCarriage((struct Car *)&self->s38,(struct Car *)&DAT_0066a4d8),
       CONCAT31(extraout_var_00,bVar4) != 0)) {
      *pS127 = (struct Car *)_DAT_0066a4d8;
      self->s38 = _DAT_0066a4d8;
      gta2::S56_sub_447480(gCheckpoint2,*(SpriteS1 **)&self->AIState);
      pSVar2 = *(Sprite **)&self->AIState;
      pSVar7 = gta2::S202_sub_401B20((Point2D *)&pSVar2->field_0x18,
                          (struct SpriteS1 *)(local_c + 4),(struct S127 *)&self->s38);
      pSVar8 = gta2::S202_sub_401B20((Point2D *)&pSVar2->Point2D1,(struct SpriteS1 *)(local_c + 8)
                          ,(struct S127 *)pS127);
      gta2::SpriteS1_sub_420600(pSVar2,(int)pSVar8->FirstElement,
                          (int)pSVar7->FirstElement,(int)pSVar2->Point2D);
    }
    break;
  case 0xf:
    iVar10 = *(int *)&self->AIState;
    iVar9 = DecoderFloat((void *)(iVar10 + 0x1c));
    if ((char)iVar9 != '\0') {
      iVar9 = DecoderFloat((void *)(iVar10 + 0x14));
      if (1 < (byte)iVar9) {
        iVar9 = DecoderFloat((void *)(iVar10 + 0x18));
        if (((1 < (byte)iVar9) &&
            (iVar9 = DecoderFloat((void *)(iVar10 + 0x14)), (byte)iVar9 < 0xfe))
           && (iVar10 = DecoderFloat((void *)(iVar10 + 0x18)),
              (byte)iVar10 < 0xfe)) {
          puVar11 = (undefined4 *)gta2::JustCopyByPtrAtoC(&DAT_0066a574,local_14);
          uVar3 = *puVar11;
          self->S7[2].ID = (char)uVar3;
          self->S7[2].field4_0xd = (char)((uint)uVar3 >> 8);
          self->S7[2].field5_0xe = (char)((uint)uVar3 >> 0x10);
          self->S7[2].field6_0xf = (char)((uint)uVar3 >> 0x18);
          gta2::GameObject_sub_49A560(self);
          return;
        }
      }
    }
    goto LAB_0049c347;
  case 0x10:
    iVar10 = *(int *)&self->AIState;
    iVar9 = DecoderFloat((void *)(iVar10 + 0x1c));
    if ((char)iVar9 != '\0') {
      iVar9 = DecoderFloat((void *)(iVar10 + 0x14));
      if (1 < (byte)iVar9) {
        iVar9 = DecoderFloat((void *)(iVar10 + 0x18));
        if (((1 < (byte)iVar9) &&
            (iVar9 = DecoderFloat((void *)(iVar10 + 0x14)), (byte)iVar9 < 0xfe))
           && (iVar10 = DecoderFloat((void *)(iVar10 + 0x18)),
              (byte)iVar10 < 0xfe)) {
          puVar11 = (undefined4 *)gta2::JustCopyByPtrAtoC(&DAT_0066a574,local_c);
          uVar3 = *puVar11;
          self->S7[2].ID = (char)uVar3;
          self->S7[2].field4_0xd = (char)((uint)uVar3 >> 8);
          self->S7[2].field5_0xe = (char)((uint)uVar3 >> 0x10);
          self->S7[2].field6_0xf = (char)((uint)uVar3 >> 0x18);
          gta2::GameObject_sub_49A560(self);
          return;
        }
      }
    }
LAB_0049c347:
    self->PhysicsFlags = 0xe;
    return;
  default:
    if (self->PhysicsFlags != 0x15) {
      local_10 = (struct SpriteS1 *)0x3;
      sVar5 = gta2::Random_Random((struct Random *)&gRandom,(short)&local_10);
      if (sVar5 == 0) {
        self->PhysicsFlags = 0xe;
      }
      else if (sVar5 == 1) {
        self->PhysicsFlags = 0x13;
      }
      else if (sVar5 == 2) {
        self->PhysicsFlags = 0x14;
      }
    }
    *(undefined1 *)&self->CollisionData = 0;
  }
  gta2::SpriteS1_sub_40F7B0(*(SpriteS1 **)&self->AIState,6);
  return;
}


// 0x0049c460: GameObject::sub_49C460
// IDA: GameObject::sub_49C460
// Ghidra: ---
char gta2::GameObject_sub_49C460(struct GameObject *self, SpriteS1 *a2)
{
  __int16 CigaretteIdleTimer; // ax
  char v5; // al
  int v6; // eax
  struct CarSystemManager *v7; // ecx
  struct SpriteS1 *p_Speed; // eax
  char result; // al

  if ( (char)++unk_66A3B8 > 20 )
    unk_66A3B8 = 0;
  CigaretteIdleTimer = self->CigaretteIdleTimer;
  if ( CigaretteIdleTimer )
    self->CigaretteIdleTimer = CigaretteIdleTimer - 1;
  unk_66A564 = (struct Car *)a2;
  v5 = self->field_5C;
  if ( v5 )
    LOBYTE(self->field_5C) = v5 - 1;
  sub_493550();
  unk_66A480.CurrentElement = self->SpriteS1_->S3_arr5031[0].PositionX;
  unk_66A74C = (void *)self->SpriteS1_->S3_arr5031[0].PositionY;
  unk_66A754 = (void *)self->SpriteS1_->S3_arr5031[0].PositionZ;
  gta2::S202_sub_40CE30((struct S202 *)&a2, self->field_45);
  *(_DWORD *)&unk_66A414.Ammo = a2;
  unk_66A3C5 = 0;
  unk_66A3C8 = 0;
  gta2::S56_sub_447C40(gCheckpoint1, self->SpriteS1_);
  if ( (self->field_58 & 0x20) != 0 )
  {
    gta2::SpriteS1_sub_420600(self->SpriteS1_, self->teleportX, self->teleportY, self->teleportZ);
    v6 = self->field_58;
    LOBYTE(v6) = v6 & 0xDF;
    self->field_58 = v6;
  }
  else
  {
    switch ( self->field_8 )
    {
      case 0:
        gta2::GameObject_sub_49A560(self);
        break;
      case 1:
        gta2::GameObject_sub_49B0D0(self);
        break;
      case 2:
        gta2::GameObject_sub_49B0D0_0(self);
        break;
      case 3:
        gta2::GameObject_sub_49BAD0(self);
        break;
      case 4:
        gta2::GameObject_sub_496800(self);
        break;
      case 5:
        gta2::GameObject_sub_49BC20(self);
        break;
      case 7:
        gta2::GameObject_sub_49BD10(self);
        break;
      case 8:
        gta2::GameObject_sub_496880(self);
        break;
      case 9:
        gta2::GameObject_sub_49C120(self);
        break;
      default:
        break;
    }
    if ( LOBYTE(self->field_A0) && self->field_8 != 9 )
      gta2::SpriteS1_sub_40F7B0(self->SpriteS1_, 34);
    if ( self->field_10 == 15 )
    {
      if ( self->field_6C != 5 && self->field_8 != 9 )
        gta2::GameObject_sub_493710(self);
    }
    else
    {
      LOBYTE(self->field_A0) = 0;
    }
    gta2::sub_497DF0((int)self);
    LOWORD(v7) = self->Rotation;
    gta2::SpriteS1_SetRotation(self->SpriteS1_, v7);
    if ( (self->field_58 & 8) != 0 )
      p_Speed = gta2::JustCopyByPtrAtoC(&self->Speed, (struct SpriteS1 *)&a2);
    else
      p_Speed = (struct SpriteS1 *)&self->Speed;
    gta2::sub_41E210(&self->deltaX, p_Speed, (int)&self->Rotation);
  }
  gta2::S56_sub_447C00(gCheckpoint1, self->SpriteS1_);
  if ( self->Car )
    gta2::Car_sub_4BEF70((struct Car *)&self->Car, self->SpriteS1_);
  result = self->field_6A;
  if ( result )
    self->field_6A = --result;
  return result;
}


// 0x004a5000: GameObject::FUN_004a5000
// IDA: ---
// Ghidra: GameObject::FUN_004a5000
byte gta2::GameObject_FUN_004a5000(struct GameObject *self)
{
  undefined4 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  
  uVar1 = _DAT_0066b2a8;
  uVar2 = DAT_0066b2a8_1;
  uVar3 = uRam0066b2aa;
  uVar4 = uRam0066b2ab;
  self->S7[2].ID = DAT_0066b2a8;
  self->S7[2].field4_0xd = uVar2;
  self->S7[2].field5_0xe = uVar3;
  self->S7[2].field6_0xf = uVar4;
  return (byte)uVar1;
}


// 0x004a5030: GameObject::sub_4A5030
// IDA: GameObject::sub_4A5030
// Ghidra: Ped::FUN_004a5030
byte gta2::GameObject_sub_4A5030(struct Ped *self)
{
  byte bVar1;
  
  bVar1 = gta2::GameObject_FUN_004a5000(self->GameObject_);
  return bVar1;
}



