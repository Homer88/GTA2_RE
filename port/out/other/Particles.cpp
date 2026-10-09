#include "gta2_shim.h"

// Module: other, Class: Particles
// Functions: 14
// Source: unified (IDA+Ghidra)

// 0x0048c930: Particles::sub_48C930
// IDA: Particles::sub_48C930
// Ghidra: ---
Particle1 * gta2::Particles_sub_48C930(
        struct Particles *self,
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        Particles *pParticles)
{
  Particle *pS98; // esi
  struct Particle1 *pS99; // esi
  unsigned __int16 v9; // ax
  struct SpriteS1 *pSpriteNab; // eax

  pS98 = unk_669E70;
  if ( !gta2::Particle_IsNotEmpty(unk_669E70) || !gta2::SpriteS1_IsNotEmpty(gSpriteS1) )
    return 0;
  pS99 = gta2::Particle_sub_48A900(pS98);
  pS99->field_8 = a1;
  pS99->field_14 = a4;
  v9 = unk_669E80;
  pS99->field_C = a2;
  pS99->field_10 = a3;
  pS99->field_18 = a5;
  pS99->Particles_ = pParticles;
  *(_DWORD *)&pS99->gap0 = v9;
  pSpriteNab = gta2::SpriteS1_sub_421000(gSpriteS1);
  ++unk_669E80;
  pS99->SpriteS1_ = pSpriteNab;
  return pS99;
}


// 0x0048c9c0: Particles::sub_48C9C0
// IDA: Particles::sub_48C9C0
// Ghidra: Particles::FUN_0048c9c0
void gta2::Particles_sub_48C9C0(undefined4 param_1,int param_2,int param_3,int param_4)
{
  short sVar1;
  undefined2 extraout_var;
  undefined4 *puVar2;
  Point2D *this_00;
  struct SpriteS1 *pSVar3;
  short *psVar4;
  CarSystemManager *this_01;
  GlassInfo *pGVar5;
  undefined4 *puVar6;
  struct Particle1 *pPVar7;
  undefined4 extraout_ECX;
  S127 *pS127;
  SpawnPoint **pS110;
  undefined1 *puVar8;
  Ped *pPed;
  int *piVar9;
  undefined4 uVar10;
  undefined1 local_56 [2];
  undefined1 local_54 [4];
  undefined4 local_50;
  short local_4c;
  struct SpriteS1 *local_48;
  struct SpriteS1 *local_44;
  undefined1 *local_40;
  undefined1 local_3c [8];
  SpawnPoint *local_34;
  SpawnPoint *local_30;
  undefined1 local_2c [8];
  undefined1 local_24 [4];
  undefined1 local_20 [8];
  undefined1 local_18 [8];
  struct SpriteS1 *local_10;
  Ped *local_c;
  void *self;
  undefined2 extraout_var_00;
  
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&local_4c);
  gta2::bitShiftLeft1(&local_48,NULL);
  gta2::bitShiftLeft1(&local_50,NULL);
  String_ParseLine(&local_10,&local_50,&local_48);
  if (gSkipParticles == false) {
    gta2::bitShiftLeft1(&local_48,NULL);
    pS110 = &local_30;
    piVar9 = (int *)&DAT_0066a1a8;
    local_10 = local_48;
    local_48 = (SpriteS1 *)0x32;
    sVar1 = gta2::Random_Random((Random *)&gRandom,(short)&local_48);
    self = (void *)CONCAT22(extraout_var,sVar1);
    gta2::bitShiftLeft1(&local_34,(void *)(sVar1 + 0x19));
    puVar2 = (undefined4 *)gta2::WorldCoordinateToScreenCoord(self,pS110,piVar9);
    local_c = (Ped *)*puVar2;
    FUN_0040f6b0(&local_10,(GlassInfo *)&stack0x00000010);
    local_48 = (SpriteS1 *)0x6;
    local_34 = (SpawnPoint *)0xf;
    local_30 = (SpawnPoint *)0xf;
    do {
      gta2::bitShiftLeft1(&local_44,NULL);
      puVar8 = local_2c;
      piVar9 = (int *)&DAT_00669f44;
      local_10 = local_44;
      pSVar3 = (SpriteS1 *)(local_2c + 4);
      pS127 = (S127 *)&DAT_00669f00;
      local_40 = (undefined1 *)0x64;
      sVar1 = gta2::Random_Random((Random *)&gRandom,(short)&local_40);
      this_00 = (Point2D *)CONCAT22(extraout_var_00,sVar1);
      gta2::Decoder_SetValue(local_24,sVar1);
      pSVar3 = gta2::S202_sub_401B20(this_00,pSVar3,pS127);
      puVar2 = (undefined4 *)gta2::WorldCoordinateToScreenCoord(pSVar3,puVar8,piVar9);
      local_c = (Ped *)*puVar2;
      local_40 = (undefined1 *)0x10;
      sVar1 = gta2::Random_Random((Random *)&gRandom,(short)&local_40);
      gta2::Decoder_SetValue(local_3c,sVar1);
      psVar4 = (short *)FUN_00401cb0(&DAT_0066a030,local_56,
                                     (GlassInfo *)local_3c);
      local_4c = *psVar4;
      gta2::bitShiftLeft1(local_3c + 4,(void *)0x8);
      psVar4 = (short *)FUN_00401cb0(&DAT_0066a030,local_54,
                                     (GlassInfo *)(local_3c + 4));
      pPed = (Ped *)(local_54 + 2);
      this_01 = (CarSystemManager *)
                gta2::sub_40E5A0((CarSystemManager *)&local_4c,(Ped *)&local_50,
                           (short *)&stack0x00000010,pPed,psVar4);
      pGVar5 = (GlassInfo *)
               gta2::SpriteS1_sub_40E5D0(this_01,pPed,(int)psVar4);
      FUN_0040f6b0(&local_10,pGVar5);
      puVar8 = local_20;
      pSVar3 = gta2::S122_sub_401BF0((Model *)&local_c,(SpriteS1 *)(local_20 + 4),
                                  (int *)&local_34);
      puVar2 = (undefined4 *)gta2::JustCopyByPtrAtoC(pSVar3,puVar8);
      puVar8 = local_18;
      pSVar3 = gta2::S122_sub_401BF0((Model *)&local_10,(SpriteS1 *)(local_18 + 4),
                                  (int *)&local_30);
      puVar6 = (undefined4 *)gta2::JustCopyByPtrAtoC(pSVar3,puVar8);
      local_40 = &stack0xffffff9c;
      uVar10 = extraout_ECX;
      gta2::bitShiftLeft1(&stack0xffffff9c,NULL);
      pPVar7 = gta2::Particles_sub_48C930(gParticles,local_10,local_c,_DAT_0066a0f0,*puVar6,
                          *puVar2,uVar10);
      if (pPVar7 != NULL) {
        *(undefined4 *)&pPVar7->field_0x34 = 1;
        *(undefined4 *)&pPVar7->field_0x38 = 1;
        *(undefined2 *)&pPVar7->field_0x2c = 0xf;
        *(undefined2 *)&pPVar7->field_0x2e = 0xf;
        gta2::SpriteS1_sub_4206F0(pPVar7->Sprite,8);
        gta2::SpriteS1_sub_4206C0(pPVar7->Sprite,gPathNode->a + 0x10);
        gta2::SpriteS1_sub_420600(pPVar7->Sprite,param_2,param_3,param_4);
        gta2::S56_sub_447BA0(gCheckpoint3,(SpriteS1 *)pPVar7->Sprite);
      }
      local_48 = (SpriteS1 *)&local_48[-1].Matrix3DArray[0x13a6].field_0x3b;
    } while (local_48 != NULL);
  }
  return;
}


// 0x0048cc50: Particles::sub_48CC50
// IDA: Particles::sub_48CC50
// Ghidra: FUN_0048cc50
void gta2::Particles_sub_48CC50(int param_1,int param_2,int param_3)
{
  struct Particle1 *pPVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 extraout_var;
  undefined4 uVar5;
  
  gta2::bitShiftLeft1(&stack0xfffffff0,NULL);
  uVar4 = extraout_ECX;
  uVar5 = extraout_var;
  gta2::bitShiftLeft1(&stack0xffffffec,NULL);
  uVar3 = extraout_ECX_00;
  gta2::bitShiftLeft1(&stack0xffffffe8,NULL);
  uVar2 = extraout_ECX_01;
  gta2::bitShiftLeft1(&stack0xffffffe4,NULL);
  pPVar1 = gta2::Particles_sub_48C930(gParticles,param_1,param_2,uVar2,uVar3,uVar4,uVar5);
  if (pPVar1 != NULL) {
    *(undefined4 *)&pPVar1->field_0x34 = 1;
    *(undefined4 *)&pPVar1->field_0x38 = 0x27;
    *(undefined2 *)&pPVar1->field_0x2c = 800;
    pPVar1->field_0x46 = 0;
    pPVar1->field_0x48 = 3;
    *(undefined2 *)&pPVar1->field_0x2e = 800;
    gta2::SpriteS1_sub_4206F0(pPVar1->Sprite,8);
    gta2::SpriteS1_sub_4206C0(pPVar1->Sprite,gPathNode->a + 0xbf);
    gta2::SpriteS1_sub_420600(pPVar1->Sprite,param_1,param_2,param_3);
    gta2::SpriteS1_sub_40F7B0((SpriteS1 *)pPVar1->Sprite,2);
    gta2::S56_sub_447BA0(gCheckpoint3,(SpriteS1 *)pPVar1->Sprite);
  }
  return;
}


// 0x0048cd10: Particles::sub_48CD10
// IDA: Particles::sub_48CD10
// Ghidra: FUN_0048cd10
void gta2::Particles_sub_48CD10(SpriteS1 *param_1)
{
  undefined4 *pS127;
  struct SpriteS1 *self;
  int iVar1;
  struct Particle1 *pPVar2;
  Model *pMVar3;
  struct SpriteS1 *pSVar4;
  struct SpriteS1 *pSVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  struct SpriteS1 *extraout_ECX;
  struct SpriteS1 *extraout_ECX_00;
  struct SpriteS1 *extraout_ECX_01;
  struct SpriteS1 *extraout_ECX_02;
  struct SpriteS1 *extraout_ECX_03;
  struct SpriteS1 *extraout_ECX_04;
  struct SpriteS1 *extraout_ECX_05;
  struct SpriteS1 *extraout_ECX_06;
  struct SpriteS1 *extraout_ECX_07;
  struct SpriteS1 *extraout_ECX_08;
  struct SpriteS1 *pSVar8;
  struct SpriteS1 *pSVar9;
  struct SpriteS1 *local_28;
  undefined1 local_24 [12];
  struct SpriteS1 *local_18;
  struct SpriteS1 *local_14;
  struct SpriteS1 *local_10;
  struct SpriteS1 *local_c;
  struct SpriteS1 *local_8;
  struct SpriteS1 *local_4;
  
  gta2::bitShiftLeft1(local_24,NULL);
  gta2::bitShiftLeft1(&local_28,NULL);
  String_ParseLine(&local_8,&local_28,(undefined4 *)local_24);
  self = param_1;
  if (gSkipParticles == false) {
    iVar1 = gta2::SpriteS1_getSpriteType(param_1);
    if (iVar1 == 2) {
      gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&param_1);
      local_24._0_4_ = &stack0xffffffc4;
      pSVar8 = extraout_ECX_00;
      gta2::bitShiftLeft1(&stack0xffffffc4,NULL);
      local_24._0_4_ = &stack0xffffffc0;
      pSVar4 = extraout_ECX_01;
      gta2::bitShiftLeft1(&stack0xffffffc0,NULL);
      local_24._0_4_ = &stack0xffffffbc;
      pSVar5 = extraout_ECX_02;
      gta2::bitShiftLeft1(&stack0xffffffbc,NULL);
      pPVar2 = gta2::Particles_sub_48C930(gParticles,local_8,local_4,_DAT_0066a0f0,pSVar5,pSVar4
                          ,pSVar8);
      pSVar5 = extraout_ECX_03;
      if (pPVar2 != NULL) {
        *(uint *)&pPVar2->field_0x4 = *(uint *)&pPVar2->field_0x4 | 1;
        gta2::SpriteS1_sub_4206F0(pPVar2->Sprite,8);
        gta2::SpriteS1_sub_4206C0(pPVar2->Sprite,gPathNode->a + 0xc5);
        *(undefined4 *)&pPVar2->field_0x34 = 0;
        *(undefined4 *)&pPVar2->field_0x38 = 0x28;
        pPVar2->field_0x46 = 0;
        pPVar2->field_0x48 = 0;
        pSVar5 = (SpriteS1 *)&local_28;
        param_1 = (SpriteS1 *)
                  CONCAT22(param_1._2_2_,*(undefined2 *)&self->FirstElement);
        pSVar9 = (SpriteS1 *)&DAT_00669eb0;
        pSVar4 = (SpriteS1 *)local_24;
        pSVar8 = (SpriteS1 *)(local_24 + 4);
        local_24._0_4_ = (SpriteS1 *)0x2;
        pMVar3 = (Model *)FUN_0048a930(local_24 + 8);
        pSVar4 = gta2::S122_sub_401BF0(pMVar3,pSVar8,(int *)pSVar4);
        pSVar5 = gta2::S202_sub_401B20((Point2D *)pSVar4,pSVar5,(S127 *)pSVar9);
        local_24._0_4_ = pSVar5->FirstElement;
        pSVar5 = (SpriteS1 *)&local_18;
        pSVar9 = (SpriteS1 *)&DAT_0066a178;
        pSVar4 = (SpriteS1 *)&local_28;
        pSVar8 = (SpriteS1 *)&local_10;
        local_28 = (SpriteS1 *)0x2;
        pMVar3 = (Model *)FUN_0048a950(local_24 + 8);
        pSVar4 = gta2::S122_sub_401BF0(pMVar3,pSVar8,(int *)pSVar4);
        pSVar5 = gta2::S202_sub_401B20((Point2D *)pSVar4,pSVar5,(S127 *)pSVar9);
        local_28 = pSVar5->FirstElement;
        FUN_00432860(&local_10,(undefined4 *)local_24,&local_28);
        FUN_0040f6b0(&local_10,(GlassInfo *)&param_1);
        iVar1 = gta2::SpriteS1_sub_4207B0(self,&local_18);
        FUN_0040f680(&local_10,iVar1);
        *(SpriteS1 **)&pPVar2->field_0x28 = self;
        gta2::SpriteS1_SetRotation(pPVar2->Sprite,*(short *)&self->FirstElement);
        gta2::SpriteS1_sub_420600(pPVar2->Sprite,(int)local_10,(int)local_c,
                            self->Matrix3DArray[0].PositionZ);
        gta2::S56_sub_447BA0(gCheckpoint3,(SpriteS1 *)pPVar2->Sprite);
        gta2::SpriteS1_sub_4337F0(pPVar2->Sprite);
        pSVar5 = extraout_ECX_04;
      }
      local_10 = (SpriteS1 *)&stack0xffffffc4;
      gta2::bitShiftLeft1(&stack0xffffffc4,NULL);
      local_10 = (SpriteS1 *)&stack0xffffffc0;
      pSVar8 = extraout_ECX_05;
      gta2::bitShiftLeft1(&stack0xffffffc0,NULL);
      local_10 = (SpriteS1 *)&stack0xffffffbc;
      pSVar4 = extraout_ECX_06;
      gta2::bitShiftLeft1(&stack0xffffffbc,NULL);
      pPVar2 = gta2::Particles_sub_48C930(gParticles,local_8,local_4,_DAT_0066a0f0,pSVar4,pSVar8
                          ,pSVar5);
      if (pPVar2 == NULL) {
        return;
      }
      *(uint *)&pPVar2->field_0x4 = *(uint *)&pPVar2->field_0x4 | 1;
      gta2::SpriteS1_sub_4206F0(pPVar2->Sprite,8);
      gta2::SpriteS1_sub_4206C0(pPVar2->Sprite,gPathNode->a + 0xc5);
      *(undefined4 *)&pPVar2->field_0x34 = 0;
      *(undefined4 *)&pPVar2->field_0x38 = 0x29;
      pPVar2->field_0x46 = 0;
      pPVar2->field_0x48 = 0;
      pSVar5 = (SpriteS1 *)&local_10;
      param_1 = (SpriteS1 *)
                CONCAT22(param_1._2_2_,*(undefined2 *)&self->FirstElement);
      pSVar9 = (SpriteS1 *)&DAT_00669eb0;
      pSVar4 = (SpriteS1 *)local_24;
      pSVar8 = (SpriteS1 *)&local_18;
      local_24._0_4_ = (SpriteS1 *)0x2;
      pMVar3 = (Model *)FUN_0048a930(local_24 + 8);
      pSVar4 = gta2::S122_sub_401BF0(pMVar3,pSVar8,(int *)pSVar4);
      pSVar5 = gta2::S202_sub_401B20((Point2D *)pSVar4,pSVar5,(S127 *)pSVar9);
      local_24._0_4_ = pSVar5->FirstElement;
      pSVar5 = (SpriteS1 *)(local_24 + 4);
      pSVar9 = (SpriteS1 *)&DAT_0066a178;
      pSVar4 = (SpriteS1 *)&local_28;
      pSVar8 = (SpriteS1 *)&local_8;
      local_28 = (SpriteS1 *)0x2;
      pMVar3 = (Model *)FUN_0048a950(&local_10);
      pSVar4 = gta2::S122_sub_401BF0(pMVar3,pSVar8,(int *)pSVar4);
      pSVar5 = gta2::S202_sub_401B20((Point2D *)pSVar4,pSVar5,(S127 *)pSVar9);
      local_28 = pSVar5->FirstElement;
      pSVar5 = (SpriteS1 *)&local_28;
      puVar6 = (undefined4 *)gta2::JustCopyByPtrAtoC(local_24,&local_8);
      FUN_00432860(&local_10,puVar6,&pSVar5->FirstElement);
      FUN_0040f6b0(&local_10,(GlassInfo *)&param_1);
      iVar1 = gta2::SpriteS1_sub_4207B0(self,&local_8);
      FUN_0040f680(&local_10,iVar1);
      gta2::SpriteS1_SetRotation(pPVar2->Sprite,*(short *)&self->FirstElement);
      pSVar5 = local_10;
      pSVar4 = (SpriteS1 *)self->Matrix3DArray[0].PositionZ;
    }
    else {
      param_1 = (SpriteS1 *)&stack0xffffffc4;
      pSVar8 = extraout_ECX;
      gta2::bitShiftLeft1(&stack0xffffffc4,NULL);
      param_1 = (SpriteS1 *)&stack0xffffffc0;
      pSVar4 = extraout_ECX_07;
      gta2::bitShiftLeft1(&stack0xffffffc0,NULL);
      param_1 = (SpriteS1 *)&stack0xffffffbc;
      pSVar5 = extraout_ECX_08;
      gta2::bitShiftLeft1(&stack0xffffffbc,NULL);
      pPVar2 = gta2::Particles_sub_48C930(gParticles,local_8,local_4,_DAT_0066a0f0,pSVar5,pSVar4
                          ,pSVar8);
      if (pPVar2 == NULL) {
        return;
      }
      *(uint *)&pPVar2->field_0x4 = *(uint *)&pPVar2->field_0x4 | 1;
      gta2::SpriteS1_sub_4206F0(pPVar2->Sprite,8);
      gta2::SpriteS1_sub_4206C0(pPVar2->Sprite,gPathNode->a + 0xc5);
      *(undefined4 *)&pPVar2->field_0x34 = 0;
      *(undefined4 *)&pPVar2->field_0x38 = 0x28;
      gta2::sub_41FC20((CarSystemManager *)&param_1,self,(GlassInfo *)&DAT_00669e94,
                 (Ped *)&param_1,(Ped *)local_24);
      pPVar2->field_0x46 = 0;
      pPVar2->field_0x48 = 0;
      puVar6 = &self->Matrix3DArray[0].PositionX;
      pSVar5 = gta2::S202_sub_401B20((Point2D *)&param_1,(SpriteS1 *)&local_8,
                          (S127 *)puVar6);
      _DAT_00669f80 = pSVar5->FirstElement;
      pS127 = &self->Matrix3DArray[0].PositionY;
      pSVar5 = gta2::S202_sub_401B20((Point2D *)local_24,(SpriteS1 *)&param_1,(S127 *)pS127
                         );
      _DAT_0066a1ec = pSVar5->FirstElement;
      param_1 = (SpriteS1 *)self->Matrix3DArray[0].PositionZ;
      puVar7 = (undefined4 *)gta2::JustCopyByPtrAtoC(&DAT_0066a180,&local_8);
      local_18 = (SpriteS1 *)*puVar7;
      pSVar5 = gta2::S202_sub_401B20((Point2D *)&DAT_00669e94,(SpriteS1 *)&local_8,
                          (S127 *)&DAT_0066a150);
      local_14 = pSVar5->FirstElement;
      FUN_0040f6b0(&local_18,(GlassInfo *)self);
      iVar1 = gta2::SpriteS1_GetGameObject(self);
      puVar7 = (undefined4 *)
               FUN_0040f5c0(&local_18,&local_8,(SpriteS1 *)(iVar1 + 0x98));
      local_18 = (SpriteS1 *)*puVar7;
      local_14 = (SpriteS1 *)puVar7[1];
      gta2::SpriteS1_SetRotation(pPVar2->Sprite,*(short *)&self->FirstElement);
      pSVar5 = gta2::S202_sub_401B20((Point2D *)pS127,(SpriteS1 *)&local_8,
                          (S127 *)&local_14);
      pSVar4 = gta2::S202_sub_401B20((Point2D *)puVar6,(SpriteS1 *)&local_10,
                          (S127 *)&local_18);
      local_c = pSVar5->FirstElement;
      pSVar5 = pSVar4->FirstElement;
      pSVar4 = param_1;
    }
    gta2::SpriteS1_sub_420600(pPVar2->Sprite,(int)pSVar5,(int)local_c,(int)pSVar4);
    *(SpriteS1 **)&pPVar2->field_0x28 = self;
    gta2::S56_sub_447BA0(gCheckpoint3,(SpriteS1 *)pPVar2->Sprite);
    gta2::SpriteS1_sub_4337F0(pPVar2->Sprite);
  }
  return;
}


// 0x0048d1f0: Particles::sub_48D1F0
// IDA: Particles::sub_48D1F0
// Ghidra: ---
_DWORD * gta2::Particles_sub_48D1F0(struct Particles *self, int arg0, int x, __int16 arg8, S900 *a5)
{
  _DWORD *result; // eax
  signed __int16 v6; // ax
  Tango *v7; // eax
  struct SpriteS1 *v8; // ebp
  unsigned __int16 v9; // ax
  unsigned __int16 v10; // ax
  S202 *v11; // eax
  struct SpriteS1 *v12; // eax
  unsigned __int16 v13; // ax
  struct SpriteS1 *v14; // eax
  S900 *v15; // eax
  void *v16; // eax
  int *v17; // esi
  void *v18; // eax
  struct SpriteS1 *v19; // eax
  struct SpriteS1 *v20; // ecx
  int *v21; // edi
  struct Particle1 *v22; // eax
  struct Particle1 *v23; // esi
  struct SpriteS1 *SpriteS1; // ecx
  struct SpriteS1 *v25; // ecx
  __int16 *v26; // [esp-8h] [ebp-70h]
  int v27; // [esp-8h] [ebp-70h]
  SpriteS1 *v28[4]; // [esp-4h] [ebp-6Ch] BYREF
  __int16 v29; // [esp+Eh] [ebp-5Ah] BYREF
  __int16 v30; // [esp+10h] [ebp-58h] BYREF
  __int16 v31; // [esp+12h] [ebp-56h] BYREF
  int v32; // [esp+14h] [ebp-54h] BYREF
  _WORD a2[2]; // [esp+18h] [ebp-50h] BYREF
  __int16 a3; // [esp+1Ch] [ebp-4Ch] BYREF
  int a1; // [esp+20h] [ebp-48h] BYREF
  __int16 v36[2]; // [esp+24h] [ebp-44h] BYREF
  __int16 v37[2]; // [esp+28h] [ebp-40h] BYREF
  Tango *v38; // [esp+2Ch] [ebp-3Ch] BYREF
  int v39; // [esp+30h] [ebp-38h] BYREF
  int v40; // [esp+34h] [ebp-34h] BYREF
  int v41; // [esp+38h] [ebp-30h] BYREF
  int v42; // [esp+3Ch] [ebp-2Ch] BYREF
  int WindowWidth; // [esp+40h] [ebp-28h] BYREF
  int v44; // [esp+44h] [ebp-24h] BYREF
  _BYTE v45[4]; // [esp+48h] [ebp-20h] BYREF
  char v46; // [esp+50h] [ebp-18h] BYREF
  _BYTE v47[4]; // [esp+54h] [ebp-14h] BYREF
  int WindowHeight; // [esp+58h] [ebp-10h] BYREF
  Tango *pTango; // [esp+5Ch] [ebp-Ch] BYREF
  int FirstElement; // [esp+60h] [ebp-8h] BYREF
  int v51; // [esp+64h] [ebp-4h] BYREF

  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&a3);
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)a2);
  gta2::bitShiftLeft1(&a1, 0);
  gta2::bitShiftLeft1(&v32, 0);
  gta2::S103_sub_401D20((S103 *)&pTango, &v32, &a1);
  if ( !skip_particles )
  {
    gta2::bitShiftLeft1(&a1, 0);
    pTango = (Tango *)a1;
    a1 = 50;
    v6 = gta2::Random_Random(&gRandom, (__int16 *)&a1);
    LOWORD(v7) = gta2::bitShiftLeft1(&v41, v6 + 25);
    FirstElement = (int)gta2::Radar_AddBlip(v7, (SpriteS1 *)&v42, (PublicTransport *)&unk_66A1A8)->FirstElement;
    gta2::Tango_sub_40F6B0((Tango *)&pTango, (S900 *)&arg8);
    v8 = (SpriteS1 *)x;
    v41 = 15;
    v42 = 15;
    a1 = 6;
    do
    {
      if ( (_BYTE)a5 )
      {
        *(_DWORD *)v36 = 360;
        v9 = gta2::Random_Random(&gRandom, v36);
        gta2::sub_401AE0(v37, v9);
        a2[0] = *gta2::sub_401CB0(&unk_66A030, (CarSystemManager *)&x, v37);
      }
      else
      {
        a2[0] = arg8;
      }
      gta2::bitShiftLeft1(&v38, 0);
      pTango = v38;
      *(_DWORD *)v36 = 100;
      v10 = gta2::Random_Random(&gRandom, v36);
      gta2::sub_401AE0(v45, v10);
      v12 = gta2::S202_sub_401B20(v11, (SpriteS1 *)&v44, (PublicTransport *)&unk_669F00);
      FirstElement = (int)gta2::Radar_AddBlip((Tango *)v12, (SpriteS1 *)&WindowWidth, (PublicTransport *)&unk_669F44)->FirstElement;
      *(_DWORD *)v36 = 16;
      v13 = gta2::Random_Random(&gRandom, v36);
      gta2::sub_401AE0(&v39, v13);
      a3 = *gta2::sub_401CB0(&unk_66A030, (CarSystemManager *)&v29, &v39);
      gta2::bitShiftLeft1(&v40, 8);
      v26 = gta2::sub_401CB0(&unk_66A030, (CarSystemManager *)&v30, &v40);
      v14 = (SpriteS1 *)gta2::sub_40E5A0((CarSystemManager *)&a3, (CarSystemManager *)&v32, a2);
      v15 = (S900 *)gta2::SpriteS1_sub_40E5D0(v14, (CarSystemManager *)&v31, v26);
      gta2::Tango_sub_40F6B0((Tango *)&FirstElement, v15);
      v28[0] = (SpriteS1 *)&v46;
      gta2::S122_sub_401BF0((S122 *)&v51, (int)v47, (int)&v42);
      v17 = (int *)gta2::JustCopyByPtrAtoC(v16, v28[0]);
      v28[0] = (SpriteS1 *)&WindowHeight;
      gta2::S122_sub_401BF0((S122 *)&FirstElement, (int)&pTango, (int)&WindowWidth);
      v19 = gta2::JustCopyByPtrAtoC(v18, v28[0]);
      v28[0] = v20;
      v21 = (int *)v19;
      *(_DWORD *)v37 = v28;
      gta2::bitShiftLeft1(v28, 0);
      v22 = gta2::Particles_sub_48C930(gParticles, FirstElement, v51, unk_66A0F0, *v21, *v17, (Particles *)v28[0]);
      v23 = v22;
      if ( v22 )
      {
        SpriteS1 = v22->SpriteS1_;
        v28[0] = (SpriteS1 *)8;
        v22->field_34 = 0;
        v22->field_38 = 35;
        v22->Select = 15;
        v22->field_2E = 15;
        gta2::SpriteS1_sub_4206F0(SpriteS1, (int)v28[0]);
        gta2::SpriteS1_sub_4206C0(v23->SpriteS1_, *(_WORD *)(gCarSystemManager2.field_24 + 36004) + 132);
        v28[0] = v8;
        v27 = x;
        v25 = v23->SpriteS1_;
        v23->field_46 = 0;
        v23->field_48 = 6;
        gta2::SpriteS1_sub_420600(v25, arg0, v27, (int)v28[0]);
        gta2::S56_sub_447BA0(gCheckpoint3, v23->SpriteS1_);
      }
      result = (_DWORD *)--*(_DWORD *)v36;
    }
    while ( *(_DWORD *)v36 );
  }
  return result;
}


// 0x0048d4e0: Particles::sub_48D4E0
// IDA: Particles::sub_48D4E0
// Ghidra: ---
void gta2::Particles_sub_48D4E0(struct Particles *self, SpriteS1 *pSpriteS1)
{
  void *v3; // eax
  struct SpriteS1 *v4; // ecx
  S202 *v5; // ecx
  struct SpriteS1 *v6; // ecx
  void *v7; // ecx
  struct SpriteS1 *v8; // ecx
  S202 *v9; // ecx
  struct Particle1 *v10; // eax
  struct Particle1 *v11; // esi
  int v12; // ecx
  SpriteS3 **v13; // edi
  struct SpriteS1 *v14; // eax
  Car *GameObject; // ebx
  CarSystemManager **v16; // eax
  _WORD *v17; // eax
  _DWORD *v18; // eax
  _DWORD *v19; // eax
  struct SpriteS1 **v20; // eax
  void *v21; // ecx
  struct SpriteS1 *v22; // edx
  struct SpriteS1 *v23; // eax
  struct SpriteS1 *SpriteS1; // ecx
  struct SpriteS1 *v25; // eax
  S202 *v26; // edx
  struct SpriteS1 *v27; // ecx
  struct SpriteS1 *v28; // [esp-10h] [ebp-48h] BYREF
  S202 *v29; // [esp-Ch] [ebp-44h] BYREF
  struct SpriteS1 *v30; // [esp-8h] [ebp-40h] BYREF
  void *v31[5]; // [esp-4h] [ebp-3Ch] BYREF
  S202 a2; // [esp+10h] [ebp-28h] BYREF
  struct SpriteS1 *FirstElement; // [esp+30h] [ebp-8h] BYREF
  struct SpriteS1 *a3; // [esp+34h] [ebp-4h] BYREF

  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&a2.S202);
  if ( !skip_particles )
  {
    if ( !self->pS63 )
    {
      LOWORD(v3) = unk_669EE0.Index;
      v31[0] = v3;
      v30 = v4;
      a2.field_C = (int)&v30;
      gta2::bitShiftLeft1(&v30, 0);
      v29 = v5;
      a2.field_C = (int)&v29;
      gta2::bitShiftLeft1(&v29, 0);
      v28 = v6;
      a2.field_C = (int)&v28;
      gta2::bitShiftLeft1(&v28, 0);
      self->pS63 = gta2::Object_SpawnObject(gObject, 194, (int)v28, (int)v29, (int)v30, (int)v31[0]);
    }
    gta2::bitShiftLeft1(&a2, 0);
    gta2::bitShiftLeft1(&a2.field_C, 0);
    v31[0] = v7;
    a2.field_10 = (Weapon *)v31;
    gta2::bitShiftLeft1(v31, 0);
    v30 = v8;
    a2.field_10 = (Weapon *)&v30;
    gta2::bitShiftLeft1(&v30, 0);
    v29 = v9;
    a2.field_10 = (Weapon *)&v29;
    gta2::bitShiftLeft1(&v29, 0);
    v10 = gta2::Particles_sub_48C930(gParticles, a2.field_0, a2.field_C, unk_66A0F0, (int)v29, (int)v30, (Particles *)v31[0]);
    v11 = v10;
    if ( v10 )
    {
      v12 = v10->field_4;
      v31[0] = (void *)8;
      v10->field_4 = v12 | 1;
      gta2::SpriteS1_sub_4206F0(v10->SpriteS1_, (int)v31[0]);
      gta2::SpriteS1_sub_4206C0(v11->SpriteS1_, gPathNode->field_8CA4 + 73);
      v13 = (SpriteS3 **)gta2::Radar_AddBlip((Radar *)&unk_669EE4, (SpriteS1 *)&a2.field_10, (PublicTransport *)&unk_669F78);
      v14 = gta2::Radar_AddBlip((Radar *)&unk_669EE4, (SpriteS1 *)&a2.field_C, (PublicTransport *)&unk_669F78);
      gta2::SpriteS1_sub_4BCB90(v11->SpriteS1_, v14->FirstElement, *v13, (EventHandler *)unk_66A0F4.field_0);
      v31[0] = &a2;
      v30 = (SpriteS1 *)&a2.field_C;
      v29 = &unk_669E94;
      v28 = pSpriteS1;
      v11->field_34 = 0;
      v11->field_38 = 31;
      gta2::sub_41FC20(&a2.field_C, v28);
      v31[0] = &pSpriteS1->S3_arr5031[0].PositionX;
      v30 = (SpriteS1 *)&a2.field_10;
      v11->Select = 100;
      v11->field_46 = 0;
      v11->field_48 = 0;
      unk_669F80.Car = gta2::S202_sub_401B20((S202 *)&a2.field_C, v30, (PublicTransport *)v31[0])->FirstElement;
      unk_66A1EC.Car = gta2::S202_sub_401B20(
                         &a2,
                         (SpriteS1 *)&a2.field_10,
                         (PublicTransport *)&pSpriteS1->S3_arr5031[0].PositionY)->FirstElement;
      a2.field_C = pSpriteS1->S3_arr5031[0].PositionZ;
      if ( gta2::SpriteS1_getSpriteType(pSpriteS1) == 2 )
      {
        GameObject = (Car *)pSpriteS1->S3_arr5031[0].GameObject;
        v16 = (CarSystemManager **)gta2::Car_sub_4BE980(GameObject, 114);
        if ( v16 )
        {
          LOWORD(a2.S202) = *(_WORD *)gta2::sub_40E5A0(*v16, (CarSystemManager *)&a2, &unk_66A090);
          gta2::bitShiftLeft1(&a2, 0);
          gta2::Weapon_sub_432860((Weapon *)&a2.field_18, &a2, &unk_669FF8);
          gta2::Tango_sub_40F6B0((Tango *)&a2.field_18, (S900 *)&a2.S202);
          gta2::bitShiftLeft1(&a2, 0);
          v31[0] = &unk_66A06C;
        }
        else
        {
          v17 = (_WORD *)*gta2::Car_sub_4BE980(GameObject, 248);
          v31[0] = 0;
          LOWORD(a2.S202) = *v17;
          gta2::bitShiftLeft1(&a2, 0);
          gta2::Weapon_sub_432860((Weapon *)&a2.field_18, &a2, &unk_669F34);
          gta2::Tango_sub_40F6B0((Tango *)&a2.field_18, (S900 *)&a2.S202);
          gta2::bitShiftLeft1(&a2, 0);
          v31[0] = &unk_66A1C0;
        }
        gta2::Weapon_sub_432860((Weapon *)&FirstElement, &a2, v31[0]);
        gta2::SpriteS1_SetRotation(v11->SpriteS1_, (CarSystemManager *)a2.S202);
        gta2::Tango_sub_40F6B0((Tango *)&FirstElement, (S900 *)pSpriteS1);
        v18 = gta2::SpriteS1_sub_4207B0(pSpriteS1, &a2.field_10);
        v19 = gta2::S103_sub_40F5C0((S103 *)&FirstElement, &a2.S202, v18);
        gta2::Tango_sub_40F680((Tango *)&a2.field_18, (int)v19);
        gta2::Player_sub_4A0D10((Player *)pSpriteS1->S3_arr5031[0].GameObject->field_58, &FirstElement, (Ped *)&a2.field_18);
        v31[0] = (void *)a2.field_C;
        v30 = *(SpriteS1 **)&a2.field_1C;
        v29 = (S202 *)a2.field_18;
      }
      else
      {
        FirstElement = gta2::JustCopyByPtrAtoC(&unk_66A180, (SpriteS1 *)&a2.field_10)->FirstElement;
        a3 = gta2::S202_sub_401B20(&unk_669E94, (SpriteS1 *)&a2.field_10, (PublicTransport *)&unk_66A150)->FirstElement;
        gta2::Tango_sub_40F6B0((Tango *)&FirstElement, (S900 *)pSpriteS1);
        v20 = (SpriteS1 **)gta2::S103_sub_40F5C0(
                             (S103 *)&FirstElement,
                             &a2.field_10,
                             &pSpriteS1->S3_arr5031[0].GameObject->deltaX);
        LOWORD(v21) = pSpriteS1->FirstElement;
        v22 = *v20;
        v23 = v20[1];
        v31[0] = v21;
        SpriteS1 = v11->SpriteS1_;
        FirstElement = v22;
        a3 = v23;
        gta2::SpriteS1_SetRotation(SpriteS1, (CarSystemManager *)v31[0]);
        a2.S202 = (S202 *)gta2::S202_sub_401B20(
                            (S202 *)&pSpriteS1->S3_arr5031[0].PositionY,
                            (SpriteS1 *)&a2.field_10,
                            (PublicTransport *)&a3);
        v25 = gta2::S202_sub_401B20(
                (S202 *)&pSpriteS1->S3_arr5031[0].PositionX,
                (SpriteS1 *)&a2,
                (PublicTransport *)&FirstElement);
        v31[0] = (void *)a2.field_C;
        v26 = (S202 *)v25->FirstElement;
        v30 = (SpriteS1 *)a2.S202->field_0;
        v29 = v26;
      }
      gta2::SpriteS1_sub_420600(v11->SpriteS1_, (int)v29, (int)v30, (int)v31[0]);
      v27 = v11->SpriteS1_;
      v11->SpriteS1_1 = pSpriteS1;
      if ( gta2::SpriteS1_sub_4BD670(v27) )
        v11->Select = 0;
      gta2::S56_sub_447BA0(gCheckpoint3, v11->SpriteS1_);
      gta2::SpriteS1_sub_4337F0(v11->SpriteS1_);
    }
  }
}


// 0x0048d8b0: Particles::sub_48D8B0
// IDA: Particles::sub_48D8B0
// Ghidra: FUN_0048d8b0
void gta2::Particles_sub_48D8B0(int param_1,SpriteS1 *param_2)
{
  Car *self;
  struct SpriteS1 *this_00;
  char cVar1;
  void *pvVar2;
  struct Particle1 *pPVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  struct SpriteS1 *pSVar6;
  int iVar7;
  int *piVar8;
  undefined2 *puVar9;
  int extraout_ECX;
  int extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  short *unaff_ESI;
  void *unaff_EDI;
  int y;
  undefined4 uVar10;
  int z;
  undefined4 uVar11;
  short rot;
  undefined4 uVar12;
  undefined4 local_c;
  undefined1 *local_8;
  struct SpriteS1 *local_4;
  
  if (!gSkipParticles) {
    if (*(int *)(param_1 + 4) == 0) {
      local_8 = &stack0xffffffdc;
      z = param_1;
      rot = _DAT_00669ee0;
      gta2::bitShiftLeft1(&stack0xffffffdc,NULL);
      local_8 = &stack0xffffffd8;
      y = extraout_ECX;
      gta2::bitShiftLeft1(&stack0xffffffd8,NULL);
      local_8 = &stack0xffffffd4;
      iVar7 = extraout_ECX_00;
      gta2::bitShiftLeft1(&stack0xffffffd4,NULL);
      pvVar2 = gta2::Object_SpawnObject(gObject,0xc6,iVar7,y,z,rot);
      *(void **)(param_1 + 4) = pvVar2;
    }
    gta2::bitShiftLeft1(&local_8,NULL);
    gta2::bitShiftLeft1(&local_c,NULL);
    local_4 = (SpriteS1 *)&stack0xffffffe0;
    uVar12 = extraout_ECX_01;
    gta2::bitShiftLeft1(&stack0xffffffe0,NULL);
    local_4 = (SpriteS1 *)&stack0xffffffdc;
    uVar11 = extraout_ECX_02;
    gta2::bitShiftLeft1(&stack0xffffffdc,NULL);
    local_4 = (SpriteS1 *)&stack0xffffffd8;
    uVar10 = extraout_ECX_03;
    gta2::bitShiftLeft1(&stack0xffffffd8,NULL);
    pPVar3 = gta2::Particles_sub_48C930(gParticles,local_8,local_c,_DAT_0066a0f0,uVar10,uVar11,
                        uVar12);
    if (pPVar3 != NULL) {
      *(uint *)&pPVar3->field_0x4 = *(uint *)&pPVar3->field_0x4 | 1;
      gta2::SpriteS1_sub_4206F0(pPVar3->Sprite,8);
      gta2::SpriteS1_sub_4206C0(pPVar3->Sprite,gPathNode->a + 0x6f);
      puVar4 = (undefined4 *)
               gta2::WorldCoordinateToScreenCoord
                         (&DAT_00669ee4,&local_4,(int *)&DAT_00669f78);
      puVar5 = (undefined4 *)
               gta2::WorldCoordinateToScreenCoord
                         (&DAT_00669ee4,&local_8,(int *)&DAT_00669f78);
      gta2::SpriteS1_sub_4BCB90(pPVar3->Sprite,*puVar5,*puVar4,_DAT_0066a0f4);
      this_00 = param_2;
      *(undefined4 *)&pPVar3->field_0x34 = 0;
      *(undefined4 *)&pPVar3->field_0x38 = 0x22;
      gta2::sub_41FC20((CarSystemManager *)&param_2,param_2,(GlassInfo *)&DAT_00669e94
                 ,(Ped *)&param_2,(Ped *)&local_8);
      *(undefined2 *)&pPVar3->field_0x2c = 100;
      pPVar3->field_0x46 = 0;
      pPVar3->field_0x48 = 0;
      pSVar6 = gta2::S202_sub_401B20((Point2D *)&param_2,(SpriteS1 *)&local_4,
                          (S127 *)&this_00->Matrix3DArray[0].PositionX);
      _DAT_00669f80 = pSVar6->FirstElement;
      pSVar6 = gta2::S202_sub_401B20((Point2D *)&local_8,(SpriteS1 *)&param_2,
                          (S127 *)&this_00->Matrix3DArray[0].PositionY);
      _DAT_0066a1ec = pSVar6->FirstElement;
      local_8 = (undefined1 *)this_00->Matrix3DArray[0].PositionZ;
      iVar7 = gta2::SpriteS1_getSpriteType(this_00);
      if (iVar7 == 2) {
        self = this_00->Matrix3DArray[0].Car;
        piVar8 = gta2::Car_sub_4BE980(self,0x72);
        if (piVar8 == NULL) {
          piVar8 = gta2::Car_sub_4BE980(self,0xf8);
          param_2 = (SpriteS1 *)CONCAT22(param_2._2_2_,*(undefined2 *)*piVar8);
          pSVar6 = param_2;
        }
        else {
          puVar9 = (undefined2 *)
                   gta2::sub_40E5A0((CarSystemManager *)*piVar8,(Ped *)&param_2,
                              (short *)&DAT_0066a090,unaff_EDI,unaff_ESI);
          param_2 = (SpriteS1 *)CONCAT22(param_2._2_2_,*puVar9);
          pSVar6 = param_2;
        }
      }
      else {
        pSVar6 = (SpriteS1 *)(uint)*(ushort *)&this_00->FirstElement;
      }
      gta2::SpriteS1_SetRotation(pPVar3->Sprite,(short)pSVar6);
      gta2::SpriteS1_sub_420600(pPVar3->Sprite,(int)_DAT_00669f80,(int)_DAT_0066a1ec,
                          (int)local_8);
      *(SpriteS1 **)&pPVar3->field_0x28 = this_00;
      cVar1 = gta2::SpriteS1_sub_4BD670((SpriteS1 *)pPVar3->Sprite);
      if (cVar1 != '\0') {
        *(undefined2 *)&pPVar3->field_0x2c = 0;
      }
      gta2::S56_sub_447BA0(gCheckpoint3,(SpriteS1 *)pPVar3->Sprite);
      gta2::SpriteS1_sub_4337F0(pPVar3->Sprite);
    }
  }
  return;
}


// 0x0048db00: Particles::sub_48DB00
// IDA: Particles::sub_48DB00
// Ghidra: FUN_0048db00
void gta2::Particles_sub_48DB00(int param_1,int param_2,int param_3)
{
  short sVar1;
  short *psVar2;
  undefined2 extraout_var;
  struct SpriteS1 *pSVar3;
  Ped *pPed;
  CarSystemManager *this_00;
  GlassInfo *pGVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  struct Particle1 *pPVar7;
  undefined4 extraout_ECX;
  Ped *pPed_00;
  S127 *pS127;
  undefined1 *puVar8;
  int *piVar9;
  undefined4 uVar10;
  byte local_6a [2];
  undefined1 local_68 [2];
  undefined1 local_66 [6];
  undefined1 local_60 [2];
  undefined1 local_5e [2];
  undefined4 local_5c;
  undefined4 local_58;
  short local_54;
  short local_50 [2];
  struct SpriteS1 *local_4c;
  undefined1 *local_48;
  undefined1 local_44 [8];
  undefined1 local_3c [8];
  SpawnPoint *local_34;
  SpawnPoint *local_30;
  undefined1 local_2c [8];
  undefined1 local_24 [4];
  undefined1 local_20 [8];
  undefined1 local_18 [8];
  struct SpriteS1 *local_10;
  Ped *local_c;
  Point2D *self;
  
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&local_54);
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)local_50);
  gta2::bitShiftLeft1(&local_58,NULL);
  gta2::bitShiftLeft1(&local_5c,NULL);
  String_ParseLine(&local_10,&local_5c,&local_58);
  psVar2 = gta2::Player_FUN_0040f790((Player *)&stack0x00000010,(undefined2 *)local_6a);
  local_50[0] = *psVar2;
  local_6a[0] = 0;
  local_34 = (SpawnPoint *)0xf;
  local_30 = (SpawnPoint *)0xf;
  do {
    gta2::bitShiftLeft1(&local_4c,NULL);
    puVar8 = local_2c;
    piVar9 = (int *)&DAT_00669f44;
    local_10 = local_4c;
    pSVar3 = (SpriteS1 *)(local_2c + 4);
    pS127 = (S127 *)&DAT_00669f00;
    local_48 = (undefined1 *)0x64;
    sVar1 = gta2::Random_Random((Random *)&gRandom,(short)&local_48);
    self = (Point2D *)CONCAT22(extraout_var,sVar1);
    gta2::Decoder_SetValue(local_24,sVar1);
    pSVar3 = gta2::S202_sub_401B20(self,pSVar3,pS127);
    piVar9 = (int *)gta2::WorldCoordinateToScreenCoord(pSVar3,puVar8,piVar9);
    local_c = (Ped *)*piVar9;
    if (local_6a[0] < 4) {
      local_48 = (undefined1 *)0x20;
      sVar1 = gta2::Random_Random((Random *)&gRandom,(short)&local_48);
      gta2::Decoder_SetValue(local_44,sVar1);
      psVar2 = (short *)FUN_00401cb0(&DAT_0066a030,local_68,
                                     (GlassInfo *)local_44);
      local_54 = *psVar2;
      gta2::bitShiftLeft1(local_44 + 4,(void *)0x10);
      psVar2 = (short *)FUN_00401cb0(&DAT_0066a030,local_66,
                                     (GlassInfo *)(local_44 + 4));
      pPed = (Ped *)(local_66 + 2);
      pPed_00 = (Ped *)(local_66 + 4);
    }
    else {
      local_48 = (undefined1 *)0x168;
      sVar1 = gta2::Random_Random((Random *)&gRandom,(short)&local_48);
      gta2::Decoder_SetValue(local_3c,sVar1);
      psVar2 = (short *)FUN_00401cb0(&DAT_0066a030,local_60,
                                     (GlassInfo *)local_3c);
      local_54 = *psVar2;
      gta2::bitShiftLeft1(local_3c + 4,(void *)0xb4);
      psVar2 = (short *)FUN_00401cb0(&DAT_0066a030,local_5e,
                                     (GlassInfo *)(local_3c + 4));
      pPed = (Ped *)&local_5c;
      pPed_00 = (Ped *)&local_58;
    }
    this_00 = (CarSystemManager *)
              gta2::sub_40E5A0((CarSystemManager *)&local_54,pPed_00,local_50,pPed,
                         psVar2);
    pGVar4 = (GlassInfo *)
             gta2::SpriteS1_sub_40E5D0(this_00,pPed,(int)psVar2);
    FUN_0040f6b0(&local_10,pGVar4);
    puVar8 = local_20;
    pSVar3 = gta2::S122_sub_401BF0((Model *)&local_c,(SpriteS1 *)(local_20 + 4),
                                (int *)&local_34);
    puVar5 = (undefined4 *)gta2::JustCopyByPtrAtoC(pSVar3,puVar8);
    puVar8 = local_18;
    pSVar3 = gta2::S122_sub_401BF0((Model *)&local_10,(SpriteS1 *)(local_18 + 4),
                                (int *)&local_30);
    puVar6 = (undefined4 *)gta2::JustCopyByPtrAtoC(pSVar3,puVar8);
    local_48 = &stack0xffffff84;
    uVar10 = extraout_ECX;
    gta2::bitShiftLeft1(&stack0xffffff84,NULL);
    pPVar7 = gta2::Particles_sub_48C930(gParticles,local_10,local_c,_DAT_0066a0f0,*puVar6,
                        *puVar5,uVar10);
    if (pPVar7 != NULL) {
      *(undefined4 *)&pPVar7->field_0x34 = 1;
      *(undefined4 *)&pPVar7->field_0x38 = 7;
      *(undefined2 *)&pPVar7->field_0x2c = 7;
      *(undefined2 *)&pPVar7->field_0x2e = 7;
      gta2::SpriteS1_sub_4206F0(pPVar7->Sprite,8);
      gta2::SpriteS1_sub_4206C0(pPVar7->Sprite,gPathNode->a + 0x7f);
      gta2::SpriteS1_sub_420600(pPVar7->Sprite,param_1,param_2,param_3);
      gta2::SpriteS1_sub_4337F0(pPVar7->Sprite);
      gta2::S56_sub_447BA0(gCheckpoint3,(SpriteS1 *)pPVar7->Sprite);
    }
    local_6a[0] = local_6a[0] + 1;
  } while (local_6a[0] < 6);
  return;
}


// 0x0048ddc0: Particles::sub_48DDC0
// IDA: Particles::sub_48DDC0
// Ghidra: FUN_0048ddc0
void gta2::Particles_sub_48DDC0(int param_1,int param_2,int param_3,undefined4 param_4)
{
  short sVar1;
  undefined2 extraout_var;
  struct SpriteS1 *pSVar2;
  short *psVar3;
  struct Particle1 *pPVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  S127 *pS127;
  undefined4 uVar5;
  undefined1 *pS110;
  undefined4 uVar6;
  int *piVar7;
  undefined4 uVar8;
  undefined4 local_1c;
  short local_18;
  SpawnPoint *local_14;
  undefined1 local_10 [4];
  Ped *local_c;
  SpawnPoint *local_8;
  int local_4;
  Point2D *self;
  
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&local_18);
  gta2::bitShiftLeft1(&local_1c,NULL);
  gta2::bitShiftLeft1(&local_14,NULL);
  String_ParseLine(&local_8,&local_14,&local_1c);
  if (gSkipParticles == false) {
    local_14 = (SpawnPoint *)0x3;
    gta2::Random_Random((Random *)&gRandom,(short)&local_14);
    gta2::bitShiftLeft1(&local_14,NULL);
    pS110 = local_10;
    piVar7 = (int *)&DAT_00669ec4;
    local_8 = local_14;
    pSVar2 = (SpriteS1 *)&local_1c;
    pS127 = (S127 *)&DAT_00669f00;
    local_14 = (SpawnPoint *)0x64;
    sVar1 = gta2::Random_Random((Random *)&gRandom,(short)&local_14);
    self = (Point2D *)CONCAT22(extraout_var,sVar1);
    gta2::Decoder_SetValue(&local_c,sVar1);
    pSVar2 = gta2::S202_sub_401B20(self,pSVar2,pS127);
    piVar7 = (int *)gta2::WorldCoordinateToScreenCoord(pSVar2,pS110,piVar7);
    local_4 = *piVar7;
    local_14 = (SpawnPoint *)0x168;
    sVar1 = gta2::Random_Random((Random *)&gRandom,(short)&local_14);
    gta2::Decoder_SetValue(local_10,sVar1);
    psVar3 = (short *)FUN_00401cb0(&DAT_0066a030,&local_1c,(GlassInfo *)local_10
                                  );
    local_18 = *psVar3;
    FUN_0040f6b0(&local_8,(GlassInfo *)&local_18);
    local_c = (Ped *)&stack0xffffffdc;
    uVar8 = extraout_ECX;
    gta2::bitShiftLeft1(&stack0xffffffdc,NULL);
    local_c = (Ped *)&stack0xffffffd8;
    uVar6 = extraout_ECX_00;
    gta2::bitShiftLeft1(&stack0xffffffd8,NULL);
    local_c = (Ped *)&stack0xffffffd4;
    uVar5 = extraout_ECX_01;
    gta2::bitShiftLeft1(&stack0xffffffd4,NULL);
    pPVar4 = gta2::Particles_sub_48C930(gParticles,local_8,local_4,_DAT_0066a0f0,uVar5,uVar6,
                        uVar8);
    if (pPVar4 != NULL) {
      *(undefined2 *)&pPVar4->field_0x2e = *(undefined2 *)&pPVar4->field_0x2c;
      *(undefined4 *)&pPVar4->field_0x34 = 0;
      *(undefined4 *)&pPVar4->field_0x38 = 0x25;
      pPVar4->field_0x46 = 0;
      gta2::SpriteS1_sub_4206F0(pPVar4->Sprite,8);
      gta2::SpriteS1_sub_4337F0(pPVar4->Sprite);
      gta2::SpriteS1_sub_420600(pPVar4->Sprite,param_1,param_2,param_3);
      gta2::SpriteS1_SetRotation(pPVar4->Sprite,(short)param_4);
      param_3 = 4;
      sVar1 = gta2::Random_Random((Random *)&gRandom,(short)&param_3);
      gta2::SpriteS1_sub_4206C0(pPVar4->Sprite,sVar1 + gPathNode->a + 0xaf);
      gta2::SpriteS1_sub_4337D0((SpriteS1 *)pPVar4->Sprite,2,'\x14');
      gta2::SpriteS1_sub_4337F0(pPVar4->Sprite);
      gta2::S56_sub_447BA0(gCheckpoint3,(SpriteS1 *)pPVar4->Sprite);
    }
  }
  return;
}


// 0x0048dfc0: Particles::sub_48DFC0
// IDA: Particles::sub_48DFC0
// Ghidra: FUN_0048dfc0
void gta2::Particles_sub_48DFC0(int param_1)
{
  Particle *self;
  bool bVar1;
  struct Particle1 *pPVar2;
  struct SpriteS1 *this_00;
  
  self = gParticle;
  bVar1 = gta2::Particle_IsNotEmpty(gParticle);
  if (bVar1) {
    pPVar2 = gta2::Particle_sub_48A900(self);
    if (pPVar2 != NULL) {
      *(int *)&pPVar2->field_0x28 = param_1;
      *(undefined4 *)&pPVar2->field_0x34 = 0;
      pPVar2->field_0x46 = 0;
      this_00 = gta2::SpriteS1_sub_421000(gSpriteS1);
      pPVar2->Sprite = (Sprite *)this_00;
      gta2::SpriteS1_sub_4206F0((Sprite *)this_00,8);
      *(undefined4 *)&pPVar2->field_0x38 = 0x26;
      gta2::SpriteS1_sub_4206C0(pPVar2->Sprite,gPathNode->a + 0xa4);
      gta2::SpriteS1_sub_4337F0(pPVar2->Sprite);
      gta2::SpriteS1_sub_420600(pPVar2->Sprite,*(int *)(param_1 + 0x14),
                          *(int *)(param_1 + 0x18),*(int *)(param_1 + 0x1c));
      gta2::S56_sub_447BA0(gCheckpoint3,(SpriteS1 *)pPVar2->Sprite);
      return;
    }
  }
  return;
}


// 0x0048e060: Particles::sub_48E060
// IDA: Particles::sub_48E060
// Ghidra: ---
void gta2::Particles_sub_48E060(struct Particles *self, Ped *a2)
{
  Particles *v2; // ecx
  int v3; // ecx
  S202 *v4; // ecx
  struct Particle1 *v5; // eax
  struct Particle1 *v6; // esi
  char v7; // bl
  __int16 Select; // ax
  struct SpriteS1 *SpriteS1; // ecx
  char **v10; // ecx
  Ped *v11; // eax
  void *v12; // ecx
  struct SpriteS1 *FirstElement; // ebp
  struct SpriteS1 *v14; // ecx
  S202 *v15; // [esp-10h] [ebp-2Ch] BYREF
  char **v16; // [esp-Ch] [ebp-28h] BYREF
  Particles *v17[5]; // [esp-8h] [ebp-24h] BYREF
  void *v18; // [esp+Ch] [ebp-10h] BYREF
  int a2a; // [esp+10h] [ebp-Ch] BYREF
  int a1; // [esp+14h] [ebp-8h]
  char *retaddr; // [esp+1Ch] [ebp+0h] BYREF
  SpriteS1 pCarSystemManager; // [esp+24h] [ebp+8h] BYREF

  if ( !skip_particles )
  {
    gta2::bitShiftLeft1(&a2a, 0);
    gta2::bitShiftLeft1(&v18, 0);
    v17[0] = v2;
    a1 = (int)v17;
    gta2::bitShiftLeft1(v17, 0);
    v16 = (char **)v3;
    a1 = (int)&v16;
    gta2::bitShiftLeft1(&v16, 0);
    v15 = v4;
    a1 = (int)&v15;
    gta2::bitShiftLeft1(&v15, 0);
    v5 = gta2::Particles_sub_48C930(gParticles, a2a, (int)v18, unk_66A0F0, (int)v15, (int)v16, v17[0]);
    v6 = v5;
    if ( v5 )
    {
      v7 = (char)a2;
      v5->field_34 = 1;
      if ( v7 )
      {
        v5->field_38 = 9;
        v5->Select = 80;
      }
      else
      {
        v5->field_38 = 10;
        v5->Select = 70;
      }
      Select = v5->Select;
      SpriteS1 = v6->SpriteS1_;
      v17[0] = (Particles *)8;
      v6->field_2E = Select;
      gta2::SpriteS1_sub_4206F0(SpriteS1, (int)v17[0]);
      gta2::SpriteS1_sub_4206C0(v6->SpriteS1_, *(_WORD *)(gCarSystemManager2.field_24 + 36004) + 3);
      if ( v7 )
      {
        v10 = &retaddr;
        v17[0] = (Particles *)&v18;
        v16 = &retaddr;
        v15 = &unk_66A070;
      }
      else
      {
        v17[0] = (Particles *)&v18;
        v16 = &retaddr;
        v15 = &unk_669E90;
      }
      gta2::sub_41FC20(v10, retaddr);
      unk_669F80.Car = retaddr;
      v17[0] = (Particles *)&v18;
      unk_66A1EC.Car = v18;
      v16 = &retaddr;
      v15 = &unk_66A150;
      v11 = gta2::SpriteS1_sub_40E5D0((SpriteS1 *)retaddr, (CarSystemManager *)&a2, &unk_66A1BC);
      gta2::sub_41FC20(v12, v11);
      gta2::Player_sub_40E530((Player *)&a2, (Tango *)&unk_669F80);
      gta2::Player_sub_40E530((Player *)&a2a, (Tango *)&unk_66A1EC);
      FirstElement = gta2::S202_sub_401B20((S202 *)&a2, &pCarSystemManager, (PublicTransport *)(retaddr + 20))->FirstElement;
      unk_669F80.Car = FirstElement;
      unk_66A1EC.Car = gta2::S202_sub_401B20((S202 *)&a2a, &pCarSystemManager, (PublicTransport *)(retaddr + 24))->FirstElement;
      gta2::SpriteS1_sub_420600(v6->SpriteS1_, (int)FirstElement, (int)unk_66A1EC.Car, *((_DWORD *)retaddr + 7));
      v14 = v6->SpriteS1_;
      v6->SpriteS1_1 = (SpriteS1 *)retaddr;
      gta2::S56_sub_447BA0(gCheckpoint3, v14);
      if ( v7 )
        gta2::SpriteS1_sub_4337F0(v6->SpriteS1_);
    }
  }
}


// 0x00491b90: Particles::Particles
// IDA: Particles::Particles
// Ghidra: ---
Particles * gta2::Particles_Particles(struct Particles *self)
{
  Particle *v2; // eax
  Particle *pParticle; // eax

  if ( !unk_669E70 )
  {
    v2 = (Particle *)gta2::operator_new(0x947Cu);
    if ( v2 )
      pParticle = gta2::Particle_Particle(v2);
    else
      pParticle = 0;
    unk_669E70 = pParticle;
    if ( !pParticle )
      gta2::debug_log(0x20u, "particle.cpp", 4167);
  }
  self->pS63 = 0;
  self->field_4.NextElement = 0;
  return self;
}


// 0x00491c20: Particles::sub_491C20
// IDA: Particles::sub_491C20
// Ghidra: FUN_00491c20
void gta2::Particles_sub_491C20(undefined4 *param_1)
{
  if (gParticle != NULL) {
    FUN_0048f1c0(1);
    gParticle = NULL;
  }
  *param_1 = 0;
  param_1[1] = 0;
  return;
}


// 0x00491ce0: Particles::sub_491CE0
// IDA: Particles::sub_491CE0
// Ghidra: ---
void gta2::Particles_sub_491CE0(struct Particles *self)
{
  Particle *pParticle; // ebx
  struct Particle1 *Particle1; // esi
  struct Particle1 *v3; // edi
  struct Particle1 *v4; // ebp
  struct Particle1 *v5; // eax
  struct Particle1 *FirstElement; // eax

  pParticle = unk_669E70;
  Particle1 = unk_669E70->Particle1_;
  v3 = 0;
  unk_669E70->field_9478 = 0;
  if ( Particle1 )
  {
    do
    {
      ++pParticle->field_9478;
      v4 = Particle1->Particle1_;
      if ( gta2::Particle1_sub_490760(Particle1) )
      {
        gta2::Particle1_sub_48C8F0(Particle1);
        if ( !v3 )
          goto LABEL_6;
        if ( v3->Particle1_ != Particle1 )
        {
          v3 = 0;
LABEL_6:
          v5 = pParticle->Particle1_;
          if ( v5 == Particle1 )
          {
            FirstElement = pParticle->FirstElement;
            pParticle->Particle1_ = Particle1->Particle1_;
            Particle1->Particle1_ = FirstElement;
            pParticle->FirstElement = Particle1;
          }
          else
          {
            v3 = pParticle->Particle1_;
            if ( v5->Particle1_ != Particle1 )
            {
              do
                v3 = v3->Particle1_;
              while ( v3->Particle1_ != Particle1 );
            }
            v3->Particle1_ = Particle1->Particle1_;
            Particle1->Particle1_ = pParticle->FirstElement;
            pParticle->FirstElement = Particle1;
          }
          goto LABEL_13;
        }
        v3->Particle1_ = Particle1->Particle1_;
        Particle1->Particle1_ = pParticle->FirstElement;
        pParticle->FirstElement = Particle1;
      }
      else
      {
        v3 = Particle1;
      }
LABEL_13:
      Particle1 = v4;
    }
    while ( v4 );
  }
}



