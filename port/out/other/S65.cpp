#include "gta2_shim.h"

// Module: other, Class: S65
// Functions: 11
// Source: unified (IDA+Ghidra)

// 0x00482aa0: S65::S65
// IDA: S65::S65
// Ghidra: ---
void gta2::S65_S65(struct S65 *self)
{
  self->NextElement = 0;
  self->field_6 = 25443;
  self->field_4 = 99;
}


// 0x00482ac0: S65::S65_dec
// IDA: S65::S65_dec
// Ghidra: ---
void gta2::S65_S65_dec(struct S65 *self)
{
  self->NextElement = 0;
}


// 0x00482d30: S65::sub_482D30
// IDA: S65::sub_482D30
// Ghidra: FUN_00482d30
void gta2::S65_sub_482D30(DamageInfo *param_1,DamageInfo *param_2,undefined4 param_3, undefined4 param_4)
{
  gta2::S65_sub_4613B0(param_1);
  *(undefined4 *)&param_1->field_0x8 = param_3;
  param_1->S116_ = param_2;
  *(undefined4 *)&param_1->field_0xc = param_4;
  FUN_00461360();
  return;
}


// 0x0048a4d0: S65::sub_48A4D0
// IDA: S65::sub_48A4D0
// Ghidra: FUN_0048a4d0
byte gta2::S65_sub_48A4D0(void *self)
{
  switch(*(undefined4 *)((int)self + 0x10)) {
  case 3:
  case 4:
  case 5:
  case 0xc:
  case 0xd:
  case 0xe:
    return 1;
  default:
    return 0;
  }
}


// 0x0048e8b0: S65::sub_48E8B0
// IDA: S65::sub_48E8B0
// Ghidra: ---
void __userpurge gta2::S65_sub_48E8B0(S65 *self@<ecx>, CarSystemManager a1)
{
  struct S65 *v3; // ebp
  struct S900 *v4; // eax
  unsigned __int16 Index; // bx
  void *v6; // ecx
  struct SpriteS1 **v7; // eax
  struct Player *v8; // ecx
  __int16 NextElement; // ax
  struct Particle1 *v10; // eax
  struct Particle1 *v11; // esi
  struct SpriteS1 *SpriteS1; // ecx
  __int16 v13; // ax
  Player *v14[5]; // [esp-4h] [ebp-24h] BYREF
  int a3; // [esp+10h] [ebp-10h] BYREF
  int v16; // [esp+14h] [ebp-Ch] BYREF
  int a4; // [esp+18h] [ebp-8h] BYREF
  int a5; // [esp+1Ch] [ebp-4h]

  gta2::bitShiftLeft1(&a3, 0);
  gta2::bitShiftLeft1(&v16, 0);
  gta2::S103_sub_401D20((struct S103 *)&a4, &v16, &a3);
  v3 = (struct S65 *)a1.field_4;
  a4 = a1.field_4;
  a5 = a1.field_4;
  v4 = (struct S900 *)gta2::sub_40E5A0(&a1, (struct CarSystemManager *)&a1.field_4, &unk_66A090);
  gta2::Tango_sub_40F6B0((struct Tango *)&a4, v4);
  Index = a1.Index;
  v6 = *(void **)&self[2].field_4;
  v14[0] = (struct Player *)&unk_669F7C;
  self[1].NextElement = v3;
  self[1].field_4 = Index;
  v7 = gta2::sub_4827D0(v6, (SpriteS1 **)&a1);
  if ( gta2::Player_IsCurrentPlayer((struct Player *)v7, v14[0]) && HIWORD(self[3].NextElement) == 9999 )
    HIWORD(self[3].NextElement) = 20;
  NextElement = (__int16)self[3].NextElement;
  if ( NextElement )
  {
    LOWORD(self[3].NextElement) = NextElement - 1;
  }
  else
  {
    v14[0] = v8;
    *(_DWORD *)&a1.Index = v14;
    gta2::bitShiftLeft1(v14, 0);
    v10 = gta2::Particles_sub_48C930(gParticles, a4, a5, unk_66A0F0, a4, a5, (struct Particles *)v14[0]);
    v11 = v10;
    if ( v10 )
    {
      SpriteS1 = v10->SpriteS1_;
      v10->S65_ = self;
      v13 = self->field_6;
      v14[0] = (struct Player *)8;
      v11->field_44 = v13;
      v11->field_20 = (int)v3;
      LOWORD(v11->CarSystemManager_) = Index;
      v11->field_34 = 0;
      v11->field_46 = 0;
      v11->Select = 32;
      v11->field_2E = 32;
      gta2::SpriteS1_sub_4206F0(SpriteS1, (int)v14[0]);
      v11->field_38 = 5;
      gta2::SpriteS1_sub_4206C0(v11->SpriteS1_, *(_WORD *)(gCarSystemManager2.field_24 + 36004) + 96);
      gta2::SpriteS1_sub_420600(
        v11->SpriteS1_,
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&self[2].field_4 + 4) + 20),
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&self[2].field_4 + 4) + 24),
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&self[2].field_4 + 4) + 28));
      gta2::S56_sub_447BA0(gCheckpoint3, v11->SpriteS1_);
      *(_DWORD *)&a1.Index = 2;
      LOWORD(self[3].NextElement) = gta2::Random_Random(&gRandom, (__int16 *)&a1);
      gta2::SpriteS1_sub_4337D0(v11->SpriteS1_, 2, 20);
      gta2::SpriteS1_sub_4337F0(v11->SpriteS1_);
    }
  }
}


// 0x0048eb00: S65::sub_48EB00
// IDA: S65::sub_48EB00
// Ghidra: DamageInfo::FUN_0048eb00
void gta2::S65_sub_48EB00(DamageInfo *self)
{
  undefined2 *puVar1;
  struct Particle *this_00;
  bool bVar2;
  short sVar3;
  undefined2 extraout_var;
  undefined4 *puVar5;
  undefined2 extraout_var_00;
  void *pvVar6;
  undefined2 *puVar7;
  struct SpriteS1 *pSVar8;
  struct Particle1 *pPVar9;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  int *piVar4;
  
  this_00 = gParticle;
  bVar2 = gta2::Particle_IsNotEmpty(gParticle);
  if ((bVar2) && (0x52 < (ushort)self->select2)) {
    if (0x5a < (ushort)self->select2) {
      puVar1 = (undefined2 *)((int)&self->field22_0x20 + 2);
      local_14 = 8;
      sVar3 = gta2::Random_Random((struct Random *)&gRandom,(short)&local_14);
      piVar4 = (int *)CONCAT22(extraout_var,sVar3);
      gta2::Decoder_SetValue(&local_c,sVar3);
      puVar5 = (undefined4 *)
               gta2::WorldCoordinateToScreenCoord
                         (&self->field23_0x24,&local_10,piVar4);
      local_c = *puVar5;
      local_10 = 0x168;
      sVar3 = gta2::Random_Random((struct Random *)&gRandom,(short)&local_10);
      piVar4 = (int *)CONCAT22(extraout_var_00,sVar3);
      gta2::Decoder_SetValue(local_8,sVar3);
      pvVar6 = gta2::WorldCoordinateToScreenCoord(&DAT_0066a17c,local_4,piVar4);
      puVar7 = (undefined2 *)FUN_0040f540(&local_14,(int)pvVar6);
      *puVar1 = *puVar7;
      gta2::sub_41FC20((struct CarSystemManager *)&local_c,puVar1,(GlassInfo *)&local_c,
                 (struct Ped *)&DAT_00669f80,(struct Ped *)&DAT_0066a1ec);
      pSVar8 = gta2::S202_sub_401B20((Point2D *)
                          (*(int *)(*(int *)&self->field_0x14 + 4) + 0x14),
                          (struct SpriteS1 *)local_4,(struct S127 *)&DAT_00669f80);
      _DAT_00669f80 = pSVar8->FirstElement;
      pSVar8 = gta2::S202_sub_401B20((Point2D *)
                          (*(int *)(*(int *)&self->field_0x14 + 4) + 0x18),
                          (struct SpriteS1 *)local_4,(struct S127 *)&DAT_0066a1ec);
      _DAT_0066a1ec = pSVar8->FirstElement;
      pPVar9 = gta2::Particle_sub_48A900(gParticle);
      pPVar9->field_0x46 = 0;
      *(undefined4 *)&pPVar9->field_0x38 = 0x12;
      pSVar8 = gta2::SpriteS1_sub_421000(gSpriteS1);
      pPVar9->Sprite = (Sprite *)pSVar8;
      gta2::SpriteS1_sub_4206F0((Sprite *)pSVar8,8);
      gta2::SpriteS1_sub_4337F0(pPVar9->Sprite);
      gta2::SpriteS1_sub_4206C0(pPVar9->Sprite,gPathNode->a + 0x14);
      gta2::SpriteS1_sub_420600(pPVar9->Sprite,(int)_DAT_00669f80,(int)_DAT_0066a1ec,
                          *(int *)(*(int *)(*(int *)&self->field_0x14 + 4) +
                                  0x1c));
      gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)pPVar9->Sprite);
      pPVar9->field_0x48 = 1;
      return;
    }
    _DAT_00669f80 =
         *(SpriteS1 **)(*(int *)(*(int *)&self->field_0x14 + 4) + 0x14);
    _DAT_0066a1ec =
         *(SpriteS1 **)(*(int *)(*(int *)&self->field_0x14 + 4) + 0x18);
    pPVar9 = gta2::Particle_sub_48A900(this_00);
    pPVar9->field_0x46 = 0;
    *(undefined4 *)&pPVar9->field_0x38 = 0x12;
    pSVar8 = gta2::SpriteS1_sub_421000(gSpriteS1);
    pPVar9->Sprite = (Sprite *)pSVar8;
    gta2::SpriteS1_sub_4206F0((Sprite *)pSVar8,8);
    gta2::SpriteS1_sub_4337F0(pPVar9->Sprite);
    gta2::SpriteS1_sub_4206C0(pPVar9->Sprite,gPathNode->a + 0x14);
    gta2::SpriteS1_sub_420600(pPVar9->Sprite,(int)_DAT_00669f80,(int)_DAT_0066a1ec,
                        *(int *)(*(int *)(*(int *)&self->field_0x14 + 4) + 0x1c)
                       );
    gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)pPVar9->Sprite);
    gta2::SpriteS1_sub_4BDEF0(pPVar9->Sprite,_DAT_0066a0f4,0);
    pPVar9->field_0x48 = 5;
  }
  return;
}


// 0x0048ed40: S65::sub_48ED40
// IDA: S65::sub_48ED40
// Ghidra: DamageInfo::FUN_0048ed40
void gta2::S65_sub_48ED40(DamageInfo *self)
{
  undefined2 *puVar1;
  struct Particle *this_00;
  bool bVar2;
  short sVar3;
  undefined2 extraout_var;
  undefined4 *puVar5;
  undefined2 extraout_var_00;
  void *pvVar6;
  undefined2 *puVar7;
  struct SpriteS1 *pSVar8;
  struct Particle1 *pPVar9;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  int *piVar4;
  
  this_00 = gParticle;
  bVar2 = gta2::Particle_IsNotEmpty(gParticle);
  if (bVar2) {
    if (8 < (ushort)self->select2) {
      puVar1 = (undefined2 *)((int)&self->field22_0x20 + 2);
      local_14 = 0x30;
      sVar3 = gta2::Random_Random((struct Random *)&gRandom,(short)&local_14);
      piVar4 = (int *)CONCAT22(extraout_var,sVar3);
      gta2::Decoder_SetValue(&local_c,sVar3);
      puVar5 = (undefined4 *)
               gta2::WorldCoordinateToScreenCoord
                         (&self->field23_0x24,&local_10,piVar4);
      local_c = *puVar5;
      local_10 = 0x168;
      sVar3 = gta2::Random_Random((struct Random *)&gRandom,(short)&local_10);
      piVar4 = (int *)CONCAT22(extraout_var_00,sVar3);
      gta2::Decoder_SetValue(local_8,sVar3);
      pvVar6 = gta2::WorldCoordinateToScreenCoord(&DAT_0066a17c,local_4,piVar4);
      puVar7 = (undefined2 *)FUN_0040f540(&local_14,(int)pvVar6);
      *puVar1 = *puVar7;
      gta2::sub_41FC20((struct CarSystemManager *)&local_c,puVar1,(GlassInfo *)&local_c,
                 (struct Ped *)&DAT_00669f80,(struct Ped *)&DAT_0066a1ec);
      pSVar8 = gta2::S202_sub_401B20((Point2D *)
                          (*(int *)(*(int *)&self->field_0x14 + 4) + 0x14),
                          (struct SpriteS1 *)local_4,(struct S127 *)&DAT_00669f80);
      _DAT_00669f80 = pSVar8->FirstElement;
      pSVar8 = gta2::S202_sub_401B20((Point2D *)
                          (*(int *)(*(int *)&self->field_0x14 + 4) + 0x18),
                          (struct SpriteS1 *)local_4,(struct S127 *)&DAT_0066a1ec);
      _DAT_0066a1ec = pSVar8->FirstElement;
      pPVar9 = gta2::Particle_sub_48A900(gParticle);
      pPVar9->field_0x46 = 0;
      *(undefined4 *)&pPVar9->field_0x38 = 0x13;
      pSVar8 = gta2::SpriteS1_sub_421000(gSpriteS1);
      pPVar9->Sprite = (Sprite *)pSVar8;
      gta2::SpriteS1_sub_4206F0((Sprite *)pSVar8,8);
      gta2::SpriteS1_sub_4337F0(pPVar9->Sprite);
      *(DamageInfo **)&pPVar9->field_0x40 = self;
      gta2::SpriteS1_sub_4206C0(pPVar9->Sprite,gPathNode->a + 0x14);
      gta2::SpriteS1_sub_420600(pPVar9->Sprite,(int)_DAT_00669f80,(int)_DAT_0066a1ec,
                          *(int *)(*(int *)(*(int *)&self->field_0x14 + 4) +
                                  0x1c));
      gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)pPVar9->Sprite);
      pSVar8 = gta2::S202_sub_401B20((Point2D *)&DAT_00669f14,(struct SpriteS1 *)local_4,
                          (struct S127 *)&DAT_0066a0ec);
      gta2::SpriteS1_sub_4BDEF0(pPVar9->Sprite,pSVar8->FirstElement,0);
      pPVar9->field_0x48 = 1;
      return;
    }
    _DAT_00669f80 =
         *(SpriteS1 **)(*(int *)(*(int *)&self->field_0x14 + 4) + 0x14);
    _DAT_0066a1ec =
         *(SpriteS1 **)(*(int *)(*(int *)&self->field_0x14 + 4) + 0x18);
    pPVar9 = gta2::Particle_sub_48A900(this_00);
    pPVar9->field_0x46 = 0;
    *(undefined4 *)&pPVar9->field_0x38 = 0x13;
    pSVar8 = gta2::SpriteS1_sub_421000(gSpriteS1);
    pPVar9->Sprite = (Sprite *)pSVar8;
    gta2::SpriteS1_sub_4206F0((Sprite *)pSVar8,8);
    gta2::SpriteS1_sub_4337F0(pPVar9->Sprite);
    gta2::SpriteS1_sub_4206C0(pPVar9->Sprite,gPathNode->a + 0x14);
    gta2::SpriteS1_sub_420600(pPVar9->Sprite,(int)_DAT_00669f80,(int)_DAT_0066a1ec,
                        *(int *)(*(int *)(*(int *)&self->field_0x14 + 4) + 0x1c)
                       );
    gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)pPVar9->Sprite);
    pPVar9->field_0x48 = 5;
  }
  return;
}


// 0x0048ef90: S65::sub_48EF90
// IDA: S65::sub_48EF90
// Ghidra: DamageInfo::FUN_0048ef90
void gta2::S65_sub_48EF90(DamageInfo *self)
{
  undefined2 *puVar1;
  struct Particle *this_00;
  bool bVar2;
  short sVar3;
  undefined2 extraout_var;
  undefined4 *puVar5;
  undefined2 extraout_var_00;
  void *pvVar6;
  undefined2 *puVar7;
  struct SpriteS1 *pSVar8;
  struct Particle1 *pPVar9;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  int *piVar4;
  
  this_00 = gParticle;
  bVar2 = gta2::Particle_IsNotEmpty(gParticle);
  if (bVar2) {
    if (8 < (ushort)self->select2) {
      puVar1 = (undefined2 *)((int)&self->field22_0x20 + 2);
      local_14 = 0x50;
      sVar3 = gta2::Random_Random((struct Random *)&gRandom,(short)&local_14);
      piVar4 = (int *)CONCAT22(extraout_var,sVar3);
      gta2::Decoder_SetValue(&local_c,sVar3);
      puVar5 = (undefined4 *)
               gta2::WorldCoordinateToScreenCoord
                         (&self->field23_0x24,&local_10,piVar4);
      local_c = *puVar5;
      local_10 = 0x168;
      sVar3 = gta2::Random_Random((struct Random *)&gRandom,(short)&local_10);
      piVar4 = (int *)CONCAT22(extraout_var_00,sVar3);
      gta2::Decoder_SetValue(local_8,sVar3);
      pvVar6 = gta2::WorldCoordinateToScreenCoord(&DAT_0066a17c,local_4,piVar4);
      puVar7 = (undefined2 *)FUN_0040f540(&local_14,(int)pvVar6);
      *puVar1 = *puVar7;
      gta2::sub_41FC20((struct CarSystemManager *)&local_c,puVar1,(GlassInfo *)&local_c,
                 (struct Ped *)&DAT_00669f80,(struct Ped *)&DAT_0066a1ec);
      pSVar8 = gta2::S202_sub_401B20((Point2D *)
                          (*(int *)(*(int *)&self->field_0x14 + 4) + 0x14),
                          (struct SpriteS1 *)local_4,(struct S127 *)&DAT_00669f80);
      _DAT_00669f80 = pSVar8->FirstElement;
      pSVar8 = gta2::S202_sub_401B20((Point2D *)
                          (*(int *)(*(int *)&self->field_0x14 + 4) + 0x18),
                          (struct SpriteS1 *)local_4,(struct S127 *)&DAT_0066a1ec);
      _DAT_0066a1ec = pSVar8->FirstElement;
      pPVar9 = gta2::Particle_sub_48A900(gParticle);
      pPVar9->field_0x46 = 0;
      *(undefined4 *)&pPVar9->field_0x38 = 0x14;
      pSVar8 = gta2::SpriteS1_sub_421000(gSpriteS1);
      pPVar9->Sprite = (Sprite *)pSVar8;
      gta2::SpriteS1_sub_4206F0((Sprite *)pSVar8,8);
      gta2::SpriteS1_sub_4337F0(pPVar9->Sprite);
      gta2::SpriteS1_sub_4206C0(pPVar9->Sprite,gPathNode->a + 0x38);
      gta2::SpriteS1_sub_420600(pPVar9->Sprite,(int)_DAT_00669f80,(int)_DAT_0066a1ec,
                          *(int *)(*(int *)(*(int *)&self->field_0x14 + 4) +
                                  0x1c));
      gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)pPVar9->Sprite);
      pPVar9->field_0x48 = 1;
      return;
    }
    _DAT_00669f80 =
         *(SpriteS1 **)(*(int *)(*(int *)&self->field_0x14 + 4) + 0x14);
    _DAT_0066a1ec =
         *(SpriteS1 **)(*(int *)(*(int *)&self->field_0x14 + 4) + 0x18);
    pPVar9 = gta2::Particle_sub_48A900(this_00);
    pPVar9->field_0x46 = 0;
    *(undefined4 *)&pPVar9->field_0x38 = 0x14;
    pSVar8 = gta2::SpriteS1_sub_421000(gSpriteS1);
    pPVar9->Sprite = (Sprite *)pSVar8;
    gta2::SpriteS1_sub_4206F0((Sprite *)pSVar8,8);
    gta2::SpriteS1_sub_4337F0(pPVar9->Sprite);
    gta2::SpriteS1_sub_4206C0(pPVar9->Sprite,gPathNode->a + 0x38);
    gta2::SpriteS1_sub_420600(pPVar9->Sprite,(int)_DAT_00669f80,(int)_DAT_0066a1ec,
                        *(int *)(*(int *)(*(int *)&self->field_0x14 + 4) + 0x1c)
                       );
    gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)pPVar9->Sprite);
    pPVar9->field_0x48 = 5;
  }
  return;
}


// 0x00490d60: S65::sub_490D60
// IDA: S65::sub_490D60
// Ghidra: DamageInfo::FUN_00490d60
void gta2::S65_sub_490D60(DamageInfo *self,ushort param_1)
{
  DamageInfo *pConditionValue;
  struct SpriteS1 *pSVar1;
  byte bVar2;
  bool bVar3;
  char cVar4;
  short sVar5;
  struct S127 *pSVar6;
  undefined4 *puVar7;
  struct SpriteS1 *pSVar8;
  struct SpriteS1 *this_00;
  int iVar9;
  int *piVar10;
  void *pvVar11;
  undefined2 *puVar12;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined4 uVar13;
  struct Car *pCar;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  struct Ped *pPVar14;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  GlassInfo *pGVar15;
  struct Player *this_01;
  uint uVar16;
  undefined1 local_54 [8];
  struct VehiclePool *pS46;
  struct SpriteS1 *pSStack_48;
  undefined1 auStack_44 [12];
  undefined1 local_38 [56];
  
  gta2::Arsenal_Reset((Turrel *)&pS46);
  FUN_0048a420(local_54 + 4);
  FUN_0048a390(auStack_44 + 4);
  iVar9 = *(int *)&self->field_0x14;
  pConditionValue = self + 1;
  *(undefined4 *)pConditionValue = auStack_44._4_4_;
  pSVar6 = (struct S127 *)gta2::WorldCoordinateToScreenCoord
                             (pConditionValue,auStack_44 + 4,
                              (int *)&DAT_00669ff0);
  puVar7 = (undefined4 *)
           gta2::Player_sub_401B40((SpawnPoint *)(*(int *)(iVar9 + 4) + 0x14),
                      (GlassInfo *)auStack_44,pSVar6);
  uVar13 = *puVar7;
  pSVar6 = (struct S127 *)gta2::WorldCoordinateToScreenCoord
                             (pConditionValue,auStack_44 + 4,
                              (int *)&DAT_00669ff0);
  pSVar8 = gta2::S202_sub_401B20((Point2D *)(*(int *)(iVar9 + 4) + 0x14),
                      (struct SpriteS1 *)auStack_44,pSVar6);
  pSStack_48 = pSVar8->FirstElement;
  pSVar6 = (struct S127 *)gta2::WorldCoordinateToScreenCoord
                             (pConditionValue,auStack_44 + 4,
                              (int *)&DAT_00669ff0);
  puVar7 = (undefined4 *)
           gta2::Player_sub_401B40((SpawnPoint *)(*(int *)(iVar9 + 4) + 0x18),
                      (GlassInfo *)auStack_44,pSVar6);
  auStack_44._0_4_ = *puVar7;
  pSVar6 = (struct S127 *)gta2::WorldCoordinateToScreenCoord
                             (pConditionValue,auStack_44 + 4,
                              (int *)&DAT_00669ff0);
  pSVar8 = gta2::S202_sub_401B20((Point2D *)(*(int *)(iVar9 + 4) + 0x18),
                      (struct SpriteS1 *)local_54,pSVar6);
  auStack_44._4_4_ = pSVar8->FirstElement;
  puVar7 = (undefined4 *)
           gta2::Player_sub_401B40((SpawnPoint *)(*(int *)(iVar9 + 4) + 0x1c),
                      (GlassInfo *)local_54,(struct S127 *)(local_54 + 4));
  local_54._0_4_ = *puVar7;
  pSVar8 = gta2::S202_sub_401B20((Point2D *)(*(int *)(iVar9 + 4) + 0x1c),
                      (struct SpriteS1 *)(auStack_44 + 8),(struct S127 *)(local_54 + 4));
  pSVar8 = pSVar8->FirstElement;
  if ((self->select2 == 99) && (DAT_00669e82 == '\x01')) {
    FUN_0048ea50(self);
  }
  gta2::Point2D_Set((Point2D *)(local_38 + 0x20),uVar13,pSStack_48,auStack_44._0_4_,
               auStack_44._4_4_);
  gta2::Point2D_Set2((Point2D *)(local_38 + 0x20),local_54._0_4_,pSVar8);
  iVar9 = *(int *)&self->field_0x14;
  gta2::Checkpoint_FUN_00447c80(gCheckpoint,(Point2D *)(local_38 + 0x20),0,0,
             *(undefined4 *)(iVar9 + 4),&pS46);
  if ((char)iVar9 != '\0') {
    while (pS46 != NULL) {
      pSVar8 = (struct SpriteS1 *)
               gta2::Car_sub_4BEE10((struct VehiclePool *)&pS46);
      this_00 = (struct SpriteS1 *)gta2::SpriteS1_GetGameObject(pSVar8);
      auStack_44._4_4_ = this_00;
      if (this_00 == NULL) {
        pCar = (struct Car *)gta2::SpriteS1_GetCar(pSVar8);
        if (pCar == NULL) {
          if ((0x32 < param_1) && (param_1 < 0x3c)) {
            uVar16 = (uint)*(byte *)(*(int *)&self->field_0x14 + 0x26);
            gta2::SpriteS1_sub_40FEC0(pSVar8);
            FUN_004856e0(uVar16);
          }
        }
        else if (((param_1 < 0x33) || (0x3b < param_1)) &&
                ((param_1 < 0x51 || (0x59 < param_1)))) {
          if (param_1 == 99) {
            iVar9 = *(int *)(*(int *)&self->field_0x14 + 4);
            bVar2 = FUN_0042a6b0(local_38 + 0x14,(undefined4 *)(local_38 + 0x14)
                                 ,(GlassInfo *)
                                  &pSVar8->Matrix3DArray[0].PositionX,
                                 &pSVar8->Matrix3DArray[0].PositionY,
                                 (GlassInfo *)(iVar9 + 0x14),
                                 (GlassInfo *)(iVar9 + 0x18));
            local_54._4_4_ = *(undefined4 *)CONCAT31(extraout_var_04,bVar2);
            bVar3 = gta2::Player_CheckCondition((struct Player *)(local_54 + 4),(int *)pConditionValue);
            if (CONCAT31(extraout_var_05,bVar3) != 0) {
              pGVar15 = (GlassInfo *)
                        gta2::SpriteS1_sub_4207B0(*(SpriteS1 **)(*(int *)&self->field_0x14 + 4)
                                   ,local_38 + 0x18);
              gta2::Car_sub_426580(pCar,pGVar15);
            }
          }
        }
        else {
          bVar3 = gta2::Car_GetFullDamage(pCar);
          if (((!bVar3) && (bVar3 = gta2::Car_IsTrainOrTrainCarriage(pCar), !bVar3))
             && (cVar4 = FUN_00425d60(self->select), cVar4 == '\0')) {
            iVar9 = *(int *)(*(int *)&self->field_0x14 + 4);
            bVar2 = FUN_0042a6b0(local_38 + 0x10,(undefined4 *)(local_38 + 0x10)
                                 ,(GlassInfo *)
                                  &pSVar8->Matrix3DArray[0].PositionX,
                                 &pSVar8->Matrix3DArray[0].PositionY,
                                 (GlassInfo *)(iVar9 + 0x14),
                                 (GlassInfo *)(iVar9 + 0x18));
            local_54._4_4_ = *(undefined4 *)CONCAT31(extraout_var_02,bVar2);
            bVar3 = gta2::Player_CheckCondition((struct Player *)(local_54 + 4),(int *)pConditionValue);
            if (CONCAT31(extraout_var_03,bVar3) == 0) {
              gta2::Car_sub_426F00(pCar);
            }
            else {
              pPVar14 = (struct Ped *)gta2::S68_sub_420F10(gScriptThread,
                                          *(byte *)(*(int *)&self->field_0x14 +
                                                   0x26));
              if (pPVar14 == NULL) {
                pCar->lastDamagingPed = (struct Ped *)self[1].S116;
              }
              else {
                pCar->lastDamagingPed = pPVar14;
              }
              pCar->DamageType = 4;
              pCar->Mask = 0x32;
              sVar5 = gta2::Car_CollisionOnCar(pCar,32000,&DAT_00669ebc);
              if (((pCar->lastDamagingPed != NULL) && (0 < sVar5)) &&
                 ((pPVar14 = gta2::Character_FindPed(gCharacter,
                                                (int)pCar->lastDamagingPed),
                  pPVar14 != NULL &&
                  (bVar3 = gta2::Ped_IsSearchType(pPVar14,
                                        SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY),
                  bVar3)))) {
                gta2::PlayerStats_sub_4B89B0((SaveSlotAnimatedValue *)&pPVar14->isPlayer->Money,
                           pCar,1);
              }
            }
          }
        }
      }
      else if ((0x32 < param_1) && (iVar9 = FUN_0048a4c0(this_00), iVar9 != 8))
      {
        iVar9 = gta2::S68_sub_420F10(gScriptThread,
                           *(byte *)(*(int *)&self->field_0x14 + 0x26));
        if (iVar9 == 0) {
          *(DamageInfo **)
           &(this_00->Matrix3DArray[2].SpriteS1)->Matrix3DArray[8].Remap =
               self[1].S116;
        }
        else {
          pSVar1 = this_00->Matrix3DArray[2].SpriteS1;
          pSVar1->Matrix3DArray[8].Remap = (short)iVar9;
          pSVar1->Matrix3DArray[8].field9_0x22 = (short)((uint)iVar9 >> 0x10);
        }
        local_54._4_4_ = &pSVar8->Matrix3DArray[0].PositionX;
        puVar7 = &pSVar8->Matrix3DArray[0].PositionY;
        (this_00->Matrix3DArray[2].SpriteS1)->Matrix3DArray[10].field19_0x34 = 4
        ;
        *(undefined1 *)
         &(this_00->Matrix3DArray[2].SpriteS1)->Matrix3DArray[10].SpriteS3 =
             0x32;
        iVar9 = *(int *)&self->field_0x14;
        piVar10 = (int *)gta2::Player_sub_401B40((SpawnPoint *)local_54._4_4_,
                                    (GlassInfo *)(auStack_44 + 8),
                                    (struct S127 *)(*(int *)(iVar9 + 4) + 0x14));
        pvVar11 = gta2::Player_sub_401B40((SpawnPoint *)puVar7,(GlassInfo *)local_38,
                             (struct S127 *)(*(int *)(iVar9 + 4) + 0x18));
        puVar12 = gta2::Player_FUN_0040e8d0(this_01,(undefined2 *)local_54,pvVar11,piVar10);
        auStack_44._0_2_ = *puVar12;
        iVar9 = *(int *)(*(int *)&self->field_0x14 + 4);
        pvVar11 = (void *)(iVar9 + 0x18);
        bVar2 = FUN_0042a6b0(pvVar11,(undefined4 *)(local_38 + 4),
                             (GlassInfo *)local_54._4_4_,puVar7,
                             (GlassInfo *)(iVar9 + 0x14),(GlassInfo *)pvVar11);
        local_54._4_4_ = *(undefined4 *)CONCAT31(extraout_var,bVar2);
        bVar3 = gta2::Car_sub_403800((struct Car *)(local_54 + 4),(int *)pConditionValue);
        if (CONCAT31(extraout_var_00,bVar3) == 0) {
          pSVar8 = (struct SpriteS1 *)
                   gta2::WorldCoordinateToScreenCoord
                             (pConditionValue,local_38 + 0xc,
                              (int *)&DAT_0066a0ec);
          bVar3 = gta2::Point2D_FUN_004037e0((Point2D *)(local_54 + 4),pSVar8);
          if (CONCAT31(extraout_var_01,bVar3) == 0) {
            pSStack_48 = (struct SpriteS1 *)CONCAT31(pSStack_48._1_3_,1);
            uVar13 = _DAT_00669e94;
          }
          else {
            pSStack_48 = (struct SpriteS1 *)CONCAT31(pSStack_48._1_3_,2);
            uVar13 = _DAT_00669f98;
          }
          FUN_00493390(auStack_44._0_4_,_DAT_0066a144,uVar13,pSStack_48);
        }
        else if (param_1 < 0x46) {
          pSVar8 = gta2::S202_sub_401B20((Point2D *)&DAT_00669e94,
                              (struct SpriteS1 *)(local_38 + 8),(struct S127 *)&DAT_00669e90);
          FUN_00493390(auStack_44._0_4_,pSVar8->FirstElement,_DAT_00669f7c,0);
        }
      }
    }
  }
  return;
}


// 0x00491240: S65::sub_491240
// IDA: S65::sub_491240
// Ghidra: ---
__int16 gta2::S65_sub_491240(struct S65 *self)
{
  bool v2; // bl
  int *v3; // eax
  int *v4; // edi
  int *v5; // eax
  struct SpriteS1 *v6; // ecx
  int *v7; // ebp
  int v8; // ebp
  struct SpriteS1 *FirstElement; // eax
  int *v10; // ecx
  int v11; // ecx
  int v12; // eax
  int v13; // edi
  struct SpriteS1 *v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  struct EventHandler *v19; // eax
  struct EventHandler *v20; // ebp
  int v21; // ecx
  struct SpriteS1 *v22; // ecx
  _DWORD *v23; // edi
  struct SpriteS1 *v24; // eax
  struct Tango *v25; // eax
  struct S131 *v26; // eax
  _DWORD *v27; // eax
  int v28; // eax
  int v29; // edx
  __int16 result; // ax
  int v31; // [esp-18h] [ebp-34h] BYREF
  int v32; // [esp-14h] [ebp-30h] BYREF
  struct SpriteS1 *v33; // [esp-10h] [ebp-2Ch] BYREF
  int v34; // [esp-Ch] [ebp-28h] BYREF
  struct SpriteS1 *v35; // [esp-8h] [ebp-24h] BYREF
  int v36; // [esp-4h] [ebp-20h]
  int v37; // [esp+10h] [ebp-Ch] BYREF
  int v38; // [esp+14h] [ebp-8h] BYREF
  char a2; // [esp+18h] [ebp-4h] BYREF

  v2 = 1;
  if ( HIWORD(self[3].NextElement) < 0x5Au )
    v2 = gta2::Game_sub_45BC10(
           gGame,
           *(Player **)(*(_DWORD *)(*(_DWORD *)&self[2].field_4 + 4) + 20),
           *(Player **)(*(_DWORD *)(*(_DWORD *)&self[2].field_4 + 4) + 24)) != 0;
  unk_669E82 = 0;
  if ( v2 )
  {
    switch ( (unsigned int)self[2].NextElement )
    {
      case 0x12u:
      case 0x21u:
        gta2::S65_sub_48EB00(self);
        break;
      case 0x13u:
      case 0x20u:
        gta2::S65_sub_48ED40((int)self);
        goto LABEL_8;
      case 0x14u:
        gta2::S65_sub_48EF90((int)self);
LABEL_8:
        unk_669E82 = 1;
        break;
      default:
        break;
    }
    switch ( HIWORD(self[3].NextElement) )
    {
      case ';':
      case 'E':
      case 'O':
      case 'Y':
        LOWORD(v3) = gta2::bitShiftLeft1(&v37, 145);
        v4 = v3;
        LOWORD(v5) = gta2::bitShiftLeft1(&v38, 113);
        LOWORD(v6) = unk_669EE0.Index;
        v7 = v5;
        v36 = *(_DWORD *)&self[5].field_4;
        v35 = (struct SpriteS1 *)5;
        v34 = (int)v6;
        v33 = v6;
        gta2::bitShiftLeft1(&v33, 2);
        v8 = gta2::Object_sub_485540(gObject, *v7, *v4, (int)v33, v34, (int)v35, v36);
        if ( v8 )
        {
          FirstElement = gta2::JustCopyByPtrAtoC(&unk_669FCC, (struct SpriteS1 *)&a2)->FirstElement;
          v10 = *(int **)(*(_DWORD *)&self[2].field_4 + 4);
          v36 = unk_66A184;
          v35 = FirstElement;
          LOWORD(FirstElement) = unk_669EE0.Index;
          gta2::sub_4854C0(
            gObject,
            (struct S900 *)0x7F,
            v10[5],
            v10[6],
            v10[7],
            HIWORD(self[4].NextElement),
            (int)FirstElement,
            (struct Ped *)unk_66A144.field_0,
            (int)v35,
            unk_66A184);
          LOWORD(v11) = unk_669EE0.Index;
          v13 = v12;
          v36 = v11;
          v35 = (struct SpriteS1 *)v11;
          gta2::bitShiftLeft1(&v35, 0);
          v34 = (int)v14;
          gta2::bitShiftLeft1(&v34, 0);
          gta2::SpriteS1_sub_4B9D50(*(SpriteS1 **)(v13 + 4), *(_DWORD *)(v8 + 4), (struct SpriteS1 *)v34, (int)v35, v36);
          v36 = 255;
          v35 = (struct SpriteS1 *)v15;
          gta2::bitShiftLeft1(&v35, 3);
          v34 = 16744448;
          v33 = (struct SpriteS1 *)v16;
          gta2::bitShiftLeft1(&v33, 2);
          v32 = v17;
          gta2::bitShiftLeft1(&v32, 138);
          v31 = v18;
          gta2::bitShiftLeft1(&v31, 94);
          v19 = gta2::Object_sub_485370(gObject, v31, v32, (int)v33, v34, (int)v35, v36);
          v20 = v19;
          LOWORD(v19) = unk_669EE0.Index;
          v36 = (int)v19;
          v35 = (struct SpriteS1 *)v21;
          gta2::bitShiftLeft1(&v35, 0);
          v34 = (int)v22;
          gta2::bitShiftLeft1(&v34, 0);
          gta2::SpriteS1_sub_4B9D50(*(SpriteS1 **)(v13 + 4), (int)v20->SpriteS1_, (struct SpriteS1 *)v34, (int)v35, v36);
        }
        break;
      default:
        break;
    }
  }
  v23 = &self[4].field_4;
  if ( HIWORD(self[3].NextElement) <= 0x1Eu )
  {
    if ( gta2::Car_sub_403800((struct Car *)&self[4].field_4, (int)&unk_66A17C) )
      *v23 = unk_66A17C.field_0;
    v27 = gta2::sub_401B90(&unk_669FCC, &a2, &unk_669FF0);
    gta2::Weapon_UseAmmo((struct Weapon *)&self[4].field_4, v27);
  }
  else
  {
    v24 = gta2::Radar_AddBlip((struct Tango *)&unk_66A17C, (struct SpriteS1 *)&a2, (struct PublicTransport *)&unk_669FF0);
    if ( gta2::Car_sub_403800((struct Car *)&self[4].field_4, (int)v24) )
      *v23 = gta2::Radar_AddBlip((struct Tango *)&unk_66A17C, (struct SpriteS1 *)&a2, (struct PublicTransport *)&unk_669FF0)->FirstElement;
    v25 = (struct Tango *)gta2::sub_401B90(&unk_669FCC, &a2, &unk_669FF0);
    gta2::Player_sub_40E530((struct Player *)&self[4].field_4, v25);
  }
  LOWORD(v26) = HIWORD(self[3].NextElement);
  if ( (unsigned __int16)v26 > 0x32u )
    gta2::S65_sub_490D60(self, v26);
  if ( HIWORD(self[3].NextElement) == 99 )
  {
    v28 = *(_DWORD *)(*(_DWORD *)&self[2].field_4 + 4);
    v29 = *(_DWORD *)(v28 + 20);
    v36 = *(_DWORD *)(v28 + 24);
    v35 = (struct SpriteS1 *)v29;
    v34 = v36;
    gta2::bitShiftLeft1(&v34, 8);
    gta2::Game_sub_45BB00(gGame, v34, (int)v35, v36);
  }
  result = HIWORD(self[3].NextElement);
  if ( result != 9999 )
    HIWORD(self[3].NextElement) = --result;
  if ( HIWORD(self[3].NextElement) > 0x270Fu )
    HIWORD(self[3].NextElement) = 1;
  return result;
}


// 0x00491550: S65::sub_491550
// IDA: S65::sub_491550
// Ghidra: ---
char gta2::S65_sub_491550(struct S65 *self, char arg0)
{
  int v3; // edi
  _DWORD *v4; // eax
  int v5; // eax
  int v6; // ebp
  _DWORD *v7; // eax
  struct Particle *pS98; // edi
  struct S131 *pS131; // eax
  struct Particle1 *v10; // edi
  unsigned __int16 v11; // ax
  struct PublicTransport *v12; // eax
  struct SpriteS1 *v13; // eax
  struct CarSystemManager *v14; // eax
  __int16 v15; // dx
  struct SpriteS1 *FirstElement; // edx
  struct SpriteS1 *p_RecycledCars_1; // eax
  unsigned __int16 v18; // ax
  struct PublicTransport *v19; // eax
  struct SpriteS1 *v20; // eax
  struct CarSystemManager *v21; // eax
  __int16 v22; // dx
  unsigned __int16 v23; // ax
  struct PublicTransport *v24; // eax
  struct SpriteS1 *v25; // eax
  struct CarSystemManager *v26; // eax
  __int16 v27; // dx
  unsigned __int16 v28; // ax
  struct PublicTransport *v29; // eax
  struct SpriteS1 *v30; // eax
  struct CarSystemManager *v31; // eax
  __int16 v32; // dx
  struct SpriteS1 *pSpriteS1; // eax
  int v34; // eax
  unsigned __int16 v35; // ax
  struct PublicTransport *v36; // eax
  int v37; // ebp
  struct Player *pPlayer; // eax
  BOOL v39; // eax
  int v40; // ecx
  _DWORD *v41; // ecx
  int v42; // eax
  int v43; // edx
  struct Car *v44; // eax
  void *v46; // [esp-Ch] [ebp-9Ch] BYREF
  struct Car *v47; // [esp-8h] [ebp-98h]
  int p_ID; // [esp-4h] [ebp-94h]
  char i; // [esp+13h] [ebp-7Dh]
  __int16 v50; // [esp+14h] [ebp-7Ch] BYREF
  __int16 a4; // [esp+16h] [ebp-7Ah] BYREF
  __int16 a2; // [esp+18h] [ebp-78h] BYREF
  __int16 v53; // [esp+1Ah] [ebp-76h] BYREF
  CarSystemManager pCarSystemManager; // [esp+1Ch] [ebp-74h] BYREF
  char v55; // [esp+88h] [ebp-8h] BYREF
  char v56; // [esp+8Ch] [ebp-4h] BYREF

  p_ID = 254;
  v3 = *(_DWORD *)&self[2].field_4;
  LOWORD(v4) = gta2::bitShiftLeft1(&pCarSystemManager.field_20, 254);
  v5 = gta2::Player_sub_40CE70((struct Player *)(*(_DWORD *)(v3 + 4) + 20), v4);
  if ( !v5 )
  {
    v6 = *(_DWORD *)(v3 + 4);
    LOBYTE(v5) = gta2::Player_CheckCondition((struct Player *)(v6 + 20), &unk_669F14.CurrentElement);
    if ( !v5 )
    {
      LOWORD(v7) = gta2::bitShiftLeft1(&pCarSystemManager.field_20, 254);
      v5 = gta2::Player_sub_40CE70((struct Player *)(v6 + 24), v7);
      if ( !v5 )
      {
        LOBYTE(v5) = gta2::Player_CheckCondition((struct Player *)(v6 + 24), &unk_669F14.CurrentElement);
        if ( !v5 )
        {
          pS98 = unk_669E70;
          unk_669E82 = 0;
          for ( i = 0; (unsigned __int8)i < 2u; ++i )
          {
            if ( gta2::Particle_IsNotEmpty(pS98) )
            {
              v10 = gta2::Particle_sub_48A900(pS98);
              v10->field_46 = 0;
              switch ( arg0 )
              {
                case 0:
                  p_ID = (int)&pCarSystemManager.field_10;
                  v10->field_38 = 24;
                  *(_DWORD *)&pCarSystemManager.field_10 = 45;
                  v11 = gta2::Random_Random(&gRandom, (__int16 *)p_ID);
                  gta2::sub_401AE0(&pCarSystemManager.field_24, v11);
                  v13 = gta2::Radar_AddBlip((struct Tango *)&unk_66A17C, (struct SpriteS1 *)&pCarSystemManager.RecycledCars, v12);
                  p_ID = (int)sub_40F540((struct Ped *)&v50, (int)v13);
                  v14 = (struct CarSystemManager *)gta2::sub_40E5A0(
                                              (struct CarSystemManager *)&unk_669FFC,
                                              (struct CarSystemManager *)&a2,
                                              &unk_669EEC);
                  v15 = *(_WORD *)gta2::sub_40E5A0(v14, (struct CarSystemManager *)&a4, (void *)p_ID);
                  p_ID = (int)&unk_66A1EC;
                  v47 = &unk_669F80;
                  v46 = &unk_669FCC;
                  HIWORD(self[4].NextElement) = v15;
                  gta2::sub_41FC20((char *)&self[4].NextElement + 2, (char *)&self[4].NextElement + 2);
                  FirstElement = gta2::S202_sub_401B20(
                                   (struct S202 *)(*(_DWORD *)(*(_DWORD *)&self[2].field_4 + 4) + 20),
                                   (struct SpriteS1 *)&pCarSystemManager.field_2C,
                                   (struct PublicTransport *)&unk_669F80)->FirstElement;
                  p_RecycledCars_1 = (struct SpriteS1 *)&pCarSystemManager.field_30;
                  goto LABEL_12;
                case 1:
                  p_ID = (int)&pCarSystemManager.ID;
                  v10->field_38 = 25;
                  pCarSystemManager.ID = 90;
                  v18 = gta2::Random_Random(&gRandom, (__int16 *)p_ID);
                  gta2::sub_401AE0(&pCarSystemManager.UnitCars, v18);
                  v20 = gta2::Radar_AddBlip((struct Tango *)&unk_66A17C, (struct SpriteS1 *)&pCarSystemManager.field_38, v19);
                  p_ID = (int)sub_40F540((struct Ped *)&v53, (int)v20);
                  v21 = (struct CarSystemManager *)gta2::sub_40E5A0(
                                              &unk_66A164,
                                              (struct CarSystemManager *)&pCarSystemManager.field_2,
                                              &unk_669EEC);
                  v22 = *(_WORD *)gta2::sub_40E5A0(v21, &pCarSystemManager, (void *)p_ID);
                  p_ID = (int)&unk_66A1EC;
                  v47 = &unk_669F80;
                  v46 = &unk_669FCC;
                  HIWORD(self[4].NextElement) = v22;
                  gta2::sub_41FC20((char *)&self[4].NextElement + 2, (char *)&self[4].NextElement + 2);
                  FirstElement = gta2::S202_sub_401B20(
                                   (struct S202 *)(*(_DWORD *)(*(_DWORD *)&self[2].field_4 + 4) + 20),
                                   (struct SpriteS1 *)&pCarSystemManager.MissionCars,
                                   (struct PublicTransport *)&unk_669F80)->FirstElement;
                  p_RecycledCars_1 = (struct SpriteS1 *)&pCarSystemManager.RecycledCars_1;
                  goto LABEL_12;
                case 2:
                  p_ID = (int)&pCarSystemManager.field_18;
                  v10->field_38 = 23;
                  *(_DWORD *)&pCarSystemManager.field_18 = 90;
                  v23 = gta2::Random_Random(&gRandom, (__int16 *)p_ID);
                  gta2::sub_401AE0(&pCarSystemManager.field_44, v23);
                  v25 = gta2::Radar_AddBlip((struct Tango *)&unk_66A17C, (struct SpriteS1 *)&pCarSystemManager.field_48, v24);
                  p_ID = (int)sub_40F540((struct Ped *)&pCarSystemManager.field_4, (int)v25);
                  v26 = (struct CarSystemManager *)gta2::sub_40E5A0(
                                              &unk_66A0A0,
                                              (struct CarSystemManager *)&pCarSystemManager.Weapon_,
                                              &unk_669EEC);
                  v27 = *(_WORD *)gta2::sub_40E5A0(
                                    v26,
                                    (struct CarSystemManager *)((char *)&pCarSystemManager.field_4 + 2),
                                    (void *)p_ID);
                  p_ID = (int)&unk_66A1EC;
                  v47 = &unk_669F80;
                  v46 = &unk_669FCC;
                  HIWORD(self[4].NextElement) = v27;
                  gta2::sub_41FC20((char *)&self[4].NextElement + 2, (char *)&self[4].NextElement + 2);
                  FirstElement = gta2::S202_sub_401B20(
                                   (struct S202 *)(*(_DWORD *)(*(_DWORD *)&self[2].field_4 + 4) + 20),
                                   (struct SpriteS1 *)&pCarSystemManager.Player,
                                   (struct PublicTransport *)&unk_669F80)->FirstElement;
                  p_RecycledCars_1 = (struct SpriteS1 *)&pCarSystemManager.field_50;
                  goto LABEL_12;
                case 3:
                  p_ID = (int)&pCarSystemManager.field_1C;
                  v10->field_38 = 22;
                  pCarSystemManager.field_1C = 90;
                  v28 = gta2::Random_Random(&gRandom, (__int16 *)p_ID);
                  gta2::sub_401AE0(&pCarSystemManager.field_54, v28);
                  v30 = gta2::Radar_AddBlip((struct Tango *)&unk_66A17C, (struct SpriteS1 *)&pCarSystemManager.CarType, v29);
                  p_ID = (int)sub_40F540((struct Ped *)((char *)&pCarSystemManager.Weapon_ + 2), (int)v30);
                  v31 = (struct CarSystemManager *)gta2::sub_40E5A0(
                                              (struct CarSystemManager *)&unk_669F84,
                                              (struct CarSystemManager *)((char *)&pCarSystemManager.Car + 2),
                                              &unk_669EEC);
                  v32 = *(_WORD *)gta2::sub_40E5A0(v31, (struct CarSystemManager *)&pCarSystemManager.Car, (void *)p_ID);
                  p_ID = (int)&unk_66A1EC;
                  v47 = &unk_669F80;
                  v46 = &unk_669FCC;
                  HIWORD(self[4].NextElement) = v32;
                  gta2::sub_41FC20((char *)&self[4].NextElement + 2, (char *)&self[4].NextElement + 2);
                  FirstElement = gta2::S202_sub_401B20(
                                   (struct S202 *)(*(_DWORD *)(*(_DWORD *)&self[2].field_4 + 4) + 20),
                                   (struct SpriteS1 *)&pCarSystemManager.field_5C,
                                   (struct PublicTransport *)&unk_669F80)->FirstElement;
                  p_RecycledCars_1 = (struct SpriteS1 *)&pCarSystemManager.field_60;
LABEL_12:
                  unk_669F80.Car = FirstElement;
                  unk_66A1EC.Car = gta2::S202_sub_401B20(
                                     (struct S202 *)(*(_DWORD *)(*(_DWORD *)&self[2].field_4 + 4) + 24),
                                     p_RecycledCars_1,
                                     (struct PublicTransport *)&unk_66A1EC)->FirstElement;
                  break;
                default:
                  break;
              }
              pSpriteS1 = gta2::SpriteS1_sub_421000(gSpriteS1);
              p_ID = 8;
              v10->SpriteS1_ = pSpriteS1;
              v34 = gta2::SpriteS1_sub_4206F0(pSpriteS1, p_ID);
              v10->field_48 = 0;
              v10->field_46 = 0;
              LOWORD(v10->CarSystemManager_) = HIWORD(self[4].NextElement);
              LOWORD(v34) = HIWORD(self[3].NextElement);
              if ( (unsigned __int16)v34 <= 0x1Du )
                i = 4;
              pCarSystemManager.field_20 = v34;
              v35 = gta2::Random_Random(&gRandom, (__int16 *)&pCarSystemManager.field_20);
              gta2::sub_401AE0(&pCarSystemManager.SpriteS1_0, v35);
              v10->field_20 = (int)gta2::Radar_AddBlip((struct Tango *)&unk_66A1A8, (struct SpriteS1 *)&pCarSystemManager.bool, v36)->FirstElement;
              gta2::SpriteS1_sub_4206C0(v10->SpriteS1_, *(_WORD *)(gCarSystemManager2.field_24 + 36004) + 40);
              v37 = *(_DWORD *)&self[2].field_4;
              p_ID = (int)&unk_669EB8;
              pPlayer = (struct Player *)gta2::S202_sub_401B20(
                                    (struct S202 *)(*(_DWORD *)(v37 + 4) + 28),
                                    (struct SpriteS1 *)&v55,
                                    (struct PublicTransport *)&unk_669F14);
              v39 = gta2::Player_sub_40CE70(pPlayer, &unk_669EB8);
              v40 = *(_DWORD *)(v37 + 4);
              if ( v39 )
                p_ID = *(_DWORD *)(v40 + 28);
              else
                p_ID = (int)gta2::S202_sub_401B20((struct S202 *)(v40 + 28), (struct SpriteS1 *)&v56, (struct PublicTransport *)&unk_669F14)->FirstElement;
              gta2::SpriteS1_sub_420600(v10->SpriteS1_, (int)unk_669F80.Car, (int)unk_66A1EC.Car, p_ID);
              gta2::S56_sub_447BA0(gCheckpoint3, v10->SpriteS1_);
              gta2::SpriteS1_sub_4337F0(v10->SpriteS1_);
              pS98 = unk_669E70;
            }
          }
          if ( HIWORD(self[3].NextElement) == 99 )
          {
            v41 = *(_DWORD **)&self[2].field_4;
            v42 = v41[1];
            v43 = *(_DWORD *)(v42 + 24);
            v44 = *(Car **)(v42 + 20);
            p_ID = v43;
            v47 = v44;
            v46 = v41;
            gta2::bitShiftLeft1(&v46, 8);
            pS131 = gta2::Game_sub_45BB00(gGame, (int)v46, (int)v47, p_ID);
          }
          LOWORD(pS131) = HIWORD(self[3].NextElement);
          if ( (unsigned __int16)pS131 > 0x32u )
            gta2::S65_sub_490D60(self, pS131);
          LOWORD(v5) = HIWORD(self[3].NextElement);
          if ( (_WORD)v5 != 9999 )
          {
            if ( (unsigned __int16)v5 > 0x3Cu )
            {
              LOWORD(v5) = v5 - 1;
              HIWORD(self[3].NextElement) = v5;
            }
            if ( HIWORD(self[3].NextElement) > 0x270Fu )
              HIWORD(self[3].NextElement) = 1;
          }
        }
      }
    }
  }
  return v5;
}



