#include "gta2_shim.h"

// Module: other, Class: Particle1
// Functions: 22
// Source: unified (IDA+Ghidra)

// 0x0048a1d0: Particle1::sub_48A1D0
// IDA: Particle1::sub_48A1D0
// Ghidra: Particle1::FUN_0048a1d0
undefined1 gta2::Particle1_sub_48A1D0(void)
{
  return 0;
}


// 0x0048a1e0: Particle1::sub_48A1E0
// IDA: Particle1::sub_48A1E0
// Ghidra: Particle1::FUN_0048a1e0
undefined1 gta2::Particle1_sub_48A1E0(void)
{
  return 0;
}


// 0x0048a1f0: Particle1::sub_48A1F0
// IDA: Particle1::sub_48A1F0
// Ghidra: ---
char gta2::Particle1_sub_48A1F0(struct Particle1 *self)
{
  int v2; // eax
  int v4; // [esp+4h] [ebp-4h] BYREF

  gta2::bitShiftLeft1(&v4, 0);
  self->field_8 = v4;
  gta2::bitShiftLeft1(&v4, 0);
  self->field_C = v4;
  gta2::bitShiftLeft1(&v4, 0);
  v2 = self->field_4;
  LOBYTE(v2) = v2 & 0xFE;
  self->field_10 = v4;
  self->S65_ = 0;
  self->field_4 = v2;
  return v2;
}


// 0x0048a920: Particle1::Particle1
// IDA: Particle1::Particle1
// Ghidra: ---
Particle1 * gta2::Particle1_Particle1(struct Particle1 *self)
{
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&self->CarSystemManager_);
  return self;
}


// 0x0048a970: Particle1::sub_48A970
// IDA: Particle1::sub_48A970
// Ghidra: Particle1::FUN_0048a970
byte gta2::Particle1_sub_48A970(struct Particle1 *self)
{
  undefined1 *this_00;
  bool bVar1;
  char cVar2;
  byte bVar3;
  short sVar4;
  struct SpriteS1 *pSVar5;
  undefined3 extraout_var;
  undefined4 *puVar6;
  undefined3 extraout_var_00;
  int iVar7;
  int iVar8;
  int iVar9;
  struct SpriteS1 *pSVar10;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  struct SpriteS1 *pSVar11;
  struct SpriteS1 *pSVar12;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  undefined3 extraout_var_08;
  undefined3 extraout_var_09;
  undefined3 extraout_var_10;
  undefined3 extraout_var_11;
  Sprite *pSVar13;
  struct S127 *pSVar14;
  undefined1 pCar [4];
  struct SpriteS1 *pSp;
  struct SpriteS1 *pSpriteS1;
  struct SpriteS1 *local_10;
  undefined1 local_c [4];
  struct SpriteS1 *local_8;
  SpawnPoint *local_4;
  
  gta2::bitShiftLeft1(&pSp,NULL);
  gta2::bitShiftLeft1(pCar,NULL);
  String_ParseLine(&local_8,(undefined4 *)pCar,&pSp);
  pSVar13 = self->Sprite;
  pSp = _DAT_00669e98;
  pSVar5 = gta2::S202_sub_401B20((Point2D *)&pSVar13->Point2D,(struct SpriteS1 *)&local_10,
                      (struct S127 *)&pSp);
  pSVar5 = pSVar5->FirstElement;
  pSp = pSVar5;
  gta2::S56_sub_447BD0(gCheckpoint3,pSVar13);
  if (*(short *)&self->field_0x2c == 0) {
    return 1;
  }
  bVar1 = gta2::Car_sub_403800((struct Car *)&pSp,(int *)&DAT_00669fa4);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    return 1;
  }
  puVar6 = (undefined4 *)FUN_0042a630(&local_10,&pSp);
  pCar = (undefined1  [4])*puVar6;
  bVar1 = gta2::Car_sub_403800((struct Car *)pCar,(int *)&DAT_0066a0d0);
  if (CONCAT31(extraout_var_00,bVar1) == 0) {
LAB_0048aaf7:
    pSpriteS1 = (struct SpriteS1 *)0x3;
    sVar4 = gta2::Random_Random((struct Random *)&gRandom,(short)&pSpriteS1);
    gta2::S202_sub_41F980((struct SpriteS1 *)&pSpriteS1,sVar4 + -1);
    pCar = (undefined1  [4])pSpriteS1;
    pSpriteS1 = (struct SpriteS1 *)0x64;
    pSVar10 = gta2::S122_sub_401BF0((struct Model *)pCar,(struct SpriteS1 *)&local_10,
                                 (int *)&pSpriteS1);
    pCar = (undefined1  [4])pSVar10->FirstElement;
    pSpriteS1 = (struct SpriteS1 *)0x3;
    sVar4 = gta2::Random_Random((struct Random *)&gRandom,(short)&pSpriteS1);
    gta2::S202_sub_41F980((struct SpriteS1 *)&pSpriteS1,sVar4 + -1);
    pSp = pSpriteS1;
    pSpriteS1 = (struct SpriteS1 *)0x64;
    pSVar10 = gta2::S122_sub_401BF0((struct Model *)&pSp,(struct SpriteS1 *)&local_10,
                                 (int *)&pSpriteS1);
    pSp = pSVar10->FirstElement;
  }
  else {
    pSVar13 = self->Sprite;
    iVar7 = DecoderFloat(&pSp);
    iVar8 = DecoderFloat(&pSVar13->field_0x18);
    iVar9 = DecoderFloat(&pSVar13->Point2D1);
    cVar2 = FUN_0048a350(iVar9,iVar8,iVar7);
    if (cVar2 == '\0') goto LAB_0048aaf7;
    pSVar5 = (struct SpriteS1 *)pSVar13->Point2D;
    pSp = (struct SpriteS1 *)0x3d;
    sVar4 = gta2::Random_Random((struct Random *)&gRandom,(short)&pSp);
    gta2::S202_sub_41F980((struct SpriteS1 *)&pSp,sVar4 + -0x1e);
    pCar = (undefined1  [4])pSp;
    pSp = (struct SpriteS1 *)0x64;
    pSVar10 = gta2::S122_sub_401BF0((struct Model *)pCar,(struct SpriteS1 *)&local_10,(int *)&pSp
                                );
    pCar = (undefined1  [4])pSVar10->FirstElement;
    pSp = (struct SpriteS1 *)0xa;
    sVar4 = gta2::Random_Random((struct Random *)&gRandom,(short)&pSp);
    gta2::S202_sub_41F980((struct SpriteS1 *)&pSp,sVar4 + -5);
    pSpriteS1 = (struct SpriteS1 *)0x64;
    pSVar10 = gta2::S122_sub_401BF0((struct Model *)&pSp,(struct SpriteS1 *)&local_10,
                                 (int *)&pSpriteS1);
    pSp = pSVar10->FirstElement;
    *(short *)&self->field_0x2c = *(short *)&self->field_0x2c + 1;
  }
  iVar7 = *(int *)&self->field_0x40;
  if (iVar7 == 0) {
    *(SpriteS1 **)&self->field_0x20 = _DAT_00669f7c;
  }
  else if (0x3c < *(ushort *)&self->field_0x2c) {
    if (*(int *)(*(int *)(iVar7 + 0x14) + 4) != 0) {
      bVar3 = FUN_004827d0(*(void **)(*(int *)(*(int *)(iVar7 + 0x14) + 4) + 8),
                           &local_10);
      iVar7 = *(int *)&self->field_0x40;
      *(undefined4 *)&self->field_0x20 =
           *(undefined4 *)CONCAT31(extraout_var_01,bVar3);
      *(undefined2 *)&self->CarSystemManager_ =
           *(undefined2 *)
            (*(int *)(*(int *)(*(int *)(*(int *)(iVar7 + 0x14) + 4) + 8) + 0x10)
            + 4);
    }
    if (*(short *)(iVar7 + 0x1a) == 1) {
      *(undefined4 *)&self->field_0x40 = 0;
    }
  }
  this_00 = &self->field_0x20;
  bVar1 = gta2::Player_IsCurrentPlayer((struct Player *)this_00,(struct Player *)&DAT_00669f7c);
  if (CONCAT31(extraout_var_02,bVar1) == 0) {
    puVar6 = (undefined4 *)
             gta2::WorldCoordinateToScreenCoord(this_00,local_c,(int *)&DAT_00669fd8);
    *(undefined4 *)this_00 = *puVar6;
    bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)this_00,(struct SpriteS1 *)&DAT_00669f7c);
    if (CONCAT31(extraout_var_07,bVar1) != 0) {
      *(SpriteS1 **)this_00 = _DAT_00669f7c;
    }
    local_10 = (struct SpriteS1 *)self->Sprite->Point2D1;
    pSpriteS1 = *(SpriteS1 **)&self->Sprite->field_0x18;
    local_4 = *(SpawnPoint **)this_00;
    local_8 = _DAT_00669f7c;
    FUN_0040f6b0(&local_8,(GlassInfo *)&self->CarSystemManager_);
    self->field11_0x14 = local_8;
    self->field12_0x18 = local_4;
    pSVar10 = gta2::S202_sub_401B20((Point2D *)pCar,(struct SpriteS1 *)local_c,
                         (struct S127 *)&self->field11_0x14);
    self->field8_0x8 = pSVar10->FirstElement;
    pSVar10 = gta2::S202_sub_401B20((Point2D *)&pSp,(struct SpriteS1 *)local_c,
                         (struct S127 *)&self->field12_0x18);
    self->field9_0xc = pSVar10->FirstElement;
    pSVar10 = gta2::S202_sub_401B20((Point2D *)&local_10,(struct SpriteS1 *)local_c,
                         (struct S127 *)&self->field8_0x8);
    pSVar10 = pSVar10->FirstElement;
    pSVar11 = gta2::S202_sub_401B20((Point2D *)&pSpriteS1,(struct SpriteS1 *)local_c,
                         (struct S127 *)&self->field9_0xc);
    pSVar11 = pSVar11->FirstElement;
    _DAT_00669f80 = pSVar10;
    _DAT_0066a1ec = pSVar11;
    bVar1 = gta2::Car_sub_403800((struct Car *)&DAT_00669f80,(int *)&DAT_00669f14);
    if (CONCAT31(extraout_var_08,bVar1) != 0) {
      pSVar12 = (struct SpriteS1 *)
                gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a18c,(GlassInfo *)local_c,
                           (struct S127 *)&DAT_00669f14);
      bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)&DAT_00669f80,pSVar12);
      if ((CONCAT31(extraout_var_09,bVar1) != 0) &&
         (bVar1 = gta2::Car_sub_403800((struct Car *)&DAT_0066a1ec,(int *)&DAT_00669f14),
         CONCAT31(extraout_var_10,bVar1) != 0)) {
        pSVar12 = (struct SpriteS1 *)
                  gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a18c,(GlassInfo *)local_c,
                             (struct S127 *)&DAT_00669f14);
        bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)&DAT_0066a1ec,pSVar12);
        if (CONCAT31(extraout_var_11,bVar1) != 0) {
          pSVar13 = self->Sprite;
          goto LAB_0048ae50;
        }
      }
    }
  }
  else {
    gta2::bitShiftLeft1(&pSpriteS1,NULL);
    puVar6 = (undefined4 *)gta2::JustCopyByPtrAtoC(&DAT_00669e98,&local_10);
    local_10 = (struct SpriteS1 *)*puVar6;
    pSVar14 = (struct S127 *)&pSpriteS1;
    pSVar10 = (struct SpriteS1 *)pCar;
    pSVar11 = gta2::S202_sub_401B20((Point2D *)&self->Sprite->Point2D1,(struct SpriteS1 *)local_c,
                         (struct S127 *)pCar);
    pSVar10 = gta2::S202_sub_401B20((Point2D *)pSVar11,pSVar10,pSVar14);
    pSVar10 = pSVar10->FirstElement;
    pSVar14 = (struct S127 *)&local_10;
    pSVar11 = (struct SpriteS1 *)&pSp;
    _DAT_00669f80 = pSVar10;
    pSVar12 = gta2::S202_sub_401B20((Point2D *)&self->Sprite->field_0x18,
                         (struct SpriteS1 *)local_c,(struct S127 *)&pSp);
    pSVar11 = gta2::S202_sub_401B20((Point2D *)pSVar12,pSVar11,pSVar14);
    pSVar11 = pSVar11->FirstElement;
    _DAT_0066a1ec = pSVar11;
    bVar1 = gta2::Car_sub_403800((struct Car *)&DAT_00669f80,(int *)&DAT_00669f14);
    if (CONCAT31(extraout_var_03,bVar1) != 0) {
      pSVar12 = (struct SpriteS1 *)
                gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a18c,(GlassInfo *)local_c,
                           (struct S127 *)&DAT_00669f14);
      bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)&DAT_00669f80,pSVar12);
      if ((CONCAT31(extraout_var_04,bVar1) != 0) &&
         (bVar1 = gta2::Car_sub_403800((struct Car *)&DAT_0066a1ec,(int *)&DAT_00669f14),
         CONCAT31(extraout_var_05,bVar1) != 0)) {
        pSVar12 = (struct SpriteS1 *)
                  gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a18c,(GlassInfo *)local_c,
                             (struct S127 *)&DAT_00669f14);
        bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)&DAT_0066a1ec,pSVar12);
        if (CONCAT31(extraout_var_06,bVar1) != 0) {
          pSVar13 = self->Sprite;
          goto LAB_0048ae50;
        }
      }
    }
  }
  pSVar13 = self->Sprite;
  pSVar11 = *(SpriteS1 **)&pSVar13->field_0x18;
  pSVar10 = (struct SpriteS1 *)pSVar13->Point2D1;
LAB_0048ae50:
  gta2::SpriteS1_sub_420600(pSVar13,(int)pSVar10,(int)pSVar11,(int)pSVar5);
  gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
  return 0;
}


// 0x0048ae70: Particle1::sub_48AE70
// IDA: Particle1::sub_48AE70
// Ghidra: Particle1::FUN_0048ae70
byte gta2::Particle1_sub_48AE70(struct Particle1 *self)
{
  undefined1 *this_00;
  char cVar1;
  char cVar2;
  bool bVar3;
  bool bVar4;
  short sVar5;
  undefined3 extraout_var;
  int iVar6;
  struct SpriteS1 *pSVar7;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  char *pcVar8;
  struct SpriteS1 *pSVar9;
  undefined3 extraout_var_02;
  struct SpriteS1 *pSVar10;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  byte bVar11;
  struct SpriteS1 **pS110;
  Sprite *pSVar12;
  char cVar13;
  struct S127 *pSVar14;
  int *piVar15;
  undefined1 local_58 [4];
  undefined1 local_54 [16];
  struct SpriteS1 *local_44;
  struct SpriteS1 *local_40;
  undefined1 local_3c [24];
  SpriteS1 *local_24 [2];
  SpriteS1 *local_1c [2];
  SpriteS1 *local_14 [2];
  struct SpriteS1 *local_c;
  struct SpriteS1 *local_8;
  struct SpriteS1 *local_4;
  
  local_54._8_4_ = _DAT_00669f7c;
  local_54._12_4_ = _DAT_00669f7c;
  bVar4 = true;
  gta2::bitShiftLeft1(local_54 + 4,NULL);
  gta2::bitShiftLeft1(local_54,NULL);
  String_ParseLine(&local_8,(undefined4 *)local_54,(undefined4 *)(local_54 + 4))
  ;
  gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
  if (*(short *)&self->field_0x2c == 0) {
    return 1;
  }
  iVar6 = *(int *)&self->field_0x40;
  if (iVar6 == 0) {
    cVar13 = DAT_00669f7c_1;
    cVar1 = cRam00669f7e;
    cVar2 = cRam00669f7f;
    self->field_0x20 = DAT_00669f7c;
    self->field_0x21 = cVar13;
    self->field_0x22 = cVar1;
    self->field_0x23 = cVar2;
  }
  else if (*(short *)(iVar6 + 6) == *(short *)&self->field_0x44) {
    if (*(int *)(iVar6 + 0x14) == 0) {
      *(undefined4 *)&self->field_0x40 = 0;
      cVar13 = DAT_00669f7c_1;
      cVar1 = cRam00669f7e;
      cVar2 = cRam00669f7f;
      self->field_0x20 = DAT_00669f7c;
      self->field_0x21 = cVar13;
      self->field_0x22 = cVar1;
      self->field_0x23 = cVar2;
    }
    else {
      if (*(int *)(*(int *)(iVar6 + 0x14) + 4) != 0) {
        bVar11 = FUN_004827d0(*(void **)(*(int *)(*(int *)(iVar6 + 0x14) + 4) +
                                        8),(undefined4 *)local_3c);
        iVar6 = *(int *)&self->field_0x40;
        *(undefined4 *)&self->field_0x20 =
             *(undefined4 *)CONCAT31(extraout_var,bVar11);
        *(undefined2 *)&self->CarSystemManager_ =
             *(undefined2 *)(*(int *)(*(int *)(iVar6 + 0x14) + 0x10) + 4);
      }
      if (*(short *)(iVar6 + 0x1a) == 1) {
        *(undefined4 *)&self->field_0x40 = 0;
      }
    }
  }
  else {
    *(undefined4 *)&self->field_0x40 = 0;
    cVar13 = DAT_00669f7c_1;
    cVar1 = cRam00669f7e;
    cVar2 = cRam00669f7f;
    self->field_0x20 = DAT_00669f7c;
    self->field_0x21 = cVar13;
    self->field_0x22 = cVar1;
    self->field_0x23 = cVar2;
  }
  pSVar12 = self->Sprite;
  local_58 = (undefined1  [4])_DAT_00669fcc;
  pSVar7 = gta2::S202_sub_401B20((Point2D *)&pSVar12->Point2D,(struct SpriteS1 *)local_3c,
                      (struct S127 *)local_58);
  local_54._4_4_ = pSVar7->FirstElement;
  bVar3 = gta2::Car_sub_403800((struct Car *)(local_54 + 4),(int *)&DAT_00669fa4);
  if (CONCAT31(extraout_var_00,bVar3) != 0) {
    return 1;
  }
  local_3c._0_4_ = *(undefined4 *)&pSVar12->field_0x18;
  local_40 = (struct SpriteS1 *)pSVar12->Point2D1;
  this_00 = &self->field_0x20;
  bVar3 = gta2::Player_IsCurrentPlayer((struct Player *)this_00,(struct Player *)&DAT_00669f7c);
  if (CONCAT31(extraout_var_01,bVar3) != 0) {
    gta2::bitShiftLeft1(local_54 + 0xc,NULL);
    local_54._8_4_ = local_54._12_4_;
    pcVar8 = (char *)gta2::JustCopyByPtrAtoC(&DAT_00669e98,&local_44);
    local_54._12_4_ = *(undefined4 *)pcVar8;
  }
  switch((*(ushort *)&self->field_0x2c & 0x3fc) >> 2) {
  case 2:
    local_54._0_4_ = (struct Ped *)0x2;
    sVar5 = gta2::Random_Random((struct Random *)&gRandom,(short)local_54);
    if (sVar5 != 0) {
      return 1;
    }
    gta2::SpriteS1_sub_4206C0(self->Sprite,gPathNode->a + 0x66);
    gta2::S202_sub_401B20((Point2D *)local_58,(struct SpriteS1 *)(local_3c + 4),
               (struct S127 *)&DAT_00669e90);
    gta2::bitShiftLeft1(local_58,NULL);
    local_8 = (struct SpriteS1 *)local_58;
    piVar15 = (int *)gta2::WorldCoordinateToScreenCoord
                               (this_00,local_3c + 8,(int *)&DAT_00669f3c);
    bVar4 = false;
    goto LAB_0048b0ab;
  case 3:
    gta2::SpriteS1_sub_4206C0(pSVar12,gPathNode->a + 0x65);
    gta2::S202_sub_401B20((Point2D *)local_58,(struct SpriteS1 *)(local_3c + 0xc),
               (struct S127 *)&DAT_00669e98);
    gta2::bitShiftLeft1(local_58,NULL);
    piVar15 = (int *)&DAT_0066a088;
    local_8 = (struct SpriteS1 *)local_58;
    pS110 = (SpriteS1 **)(local_3c + 0x10);
    break;
  case 4:
    gta2::SpriteS1_sub_4206C0(pSVar12,gPathNode->a + 100);
    gta2::S202_sub_401B20((Point2D *)local_58,(struct SpriteS1 *)(local_3c + 0x14),
               (struct S127 *)&DAT_0066a180);
    gta2::bitShiftLeft1(local_58,NULL);
    piVar15 = (int *)&DAT_0066a024;
    local_8 = (struct SpriteS1 *)local_58;
    pS110 = local_24;
    break;
  case 5:
    gta2::SpriteS1_sub_4206C0(pSVar12,gPathNode->a + 99);
    gta2::S202_sub_401B20((Point2D *)local_58,(struct SpriteS1 *)(local_24 + 1),
               (struct S127 *)&DAT_0066a150);
    gta2::bitShiftLeft1(local_58,NULL);
    piVar15 = (int *)&DAT_0066a024;
    local_8 = (struct SpriteS1 *)local_58;
    pS110 = local_1c;
    break;
  case 6:
    gta2::SpriteS1_sub_4206C0(pSVar12,gPathNode->a + 0x62);
    gta2::S202_sub_401B20((Point2D *)local_58,(struct SpriteS1 *)(local_1c + 1),
               (struct S127 *)&DAT_00669e98);
    gta2::bitShiftLeft1(local_58,NULL);
    piVar15 = (int *)&DAT_0066a024;
    local_8 = (struct SpriteS1 *)local_58;
    pS110 = local_14;
    break;
  case 7:
    gta2::SpriteS1_sub_4206C0(pSVar12,gPathNode->a + 0x61);
    gta2::S202_sub_401B20((Point2D *)local_58,(struct SpriteS1 *)(local_14 + 1),
               (struct S127 *)&DAT_0066a150);
    gta2::bitShiftLeft1(local_58,NULL);
    local_8 = (struct SpriteS1 *)local_58;
    piVar15 = (int *)&DAT_0066a024;
    pS110 = &local_c;
    break;
  default:
    local_44 = (struct SpriteS1 *)0x2;
    sVar5 = gta2::Random_Random((struct Random *)&gRandom,(short)&local_44);
    if (sVar5 != 0) {
      return 1;
    }
    goto LAB_0048b0b1;
  }
  local_58 = (undefined1  [4])local_8;
  piVar15 = (int *)gta2::WorldCoordinateToScreenCoord(this_00,pS110,piVar15);
LAB_0048b0ab:
  local_4 = (struct SpriteS1 *)*piVar15;
LAB_0048b0b1:
  FUN_0040f6b0(&local_8,(GlassInfo *)&self->CarSystemManager_);
  self->field11_0x14 = local_8;
  self->field12_0x18 = local_4;
  gta2::bitShiftLeft1(&local_44,NULL);
  local_58 = (undefined1  [4])local_44;
  gta2::bitShiftLeft1(&local_44,NULL);
  local_54._0_4_ = local_44;
  if (bVar4) {
    local_44 = (struct SpriteS1 *)0x3;
    sVar5 = gta2::Random_Random((struct Random *)&gRandom,(short)&local_44);
    gta2::S202_sub_41F980((struct SpriteS1 *)&local_44,sVar5 + -1);
    local_58 = (undefined1  [4])local_44;
    local_44 = (struct SpriteS1 *)0x64;
    pSVar7 = gta2::S122_sub_401BF0((struct Model *)local_58,(struct SpriteS1 *)&local_c,
                                (int *)&local_44);
    local_58 = (undefined1  [4])pSVar7->FirstElement;
    local_44 = (struct SpriteS1 *)0x3;
    sVar5 = gta2::Random_Random((struct Random *)&gRandom,(short)&local_44);
    gta2::S202_sub_41F980((struct SpriteS1 *)&local_44,sVar5 + -1);
    local_54._0_4_ = local_44;
    local_44 = (struct SpriteS1 *)0x64;
    pSVar7 = gta2::S122_sub_401BF0((struct Model *)local_54,(struct SpriteS1 *)&local_c,
                                (int *)&local_44);
    local_54._0_4_ = pSVar7->FirstElement;
  }
  pSVar14 = (struct S127 *)(local_54 + 8);
  pSVar7 = (struct SpriteS1 *)&local_c;
  pSVar9 = gta2::S202_sub_401B20((Point2D *)local_58,(struct SpriteS1 *)(local_14 + 1),
                      (struct S127 *)&self->field11_0x14);
  pSVar9 = gta2::S202_sub_401B20((Point2D *)pSVar9,pSVar7,pSVar14);
  pSVar14 = (struct S127 *)(local_54 + 0xc);
  pSVar7 = (struct SpriteS1 *)&local_c;
  self->field8_0x8 = pSVar9->FirstElement;
  pSVar9 = gta2::S202_sub_401B20((Point2D *)local_54,(struct SpriteS1 *)(local_14 + 1),
                      (struct S127 *)&self->field12_0x18);
  pSVar7 = gta2::S202_sub_401B20((Point2D *)pSVar9,pSVar7,pSVar14);
  self->field9_0xc = pSVar7->FirstElement;
  pSVar7 = gta2::S202_sub_401B20((Point2D *)&local_40,(struct SpriteS1 *)&local_c,
                      (struct S127 *)&self->field8_0x8);
  pSVar7 = pSVar7->FirstElement;
  pSVar9 = gta2::S202_sub_401B20((Point2D *)local_3c,(struct SpriteS1 *)&local_c,
                      (struct S127 *)&self->field9_0xc);
  pSVar9 = pSVar9->FirstElement;
  _DAT_00669f80 = pSVar7;
  _DAT_0066a1ec = pSVar9;
  bVar4 = gta2::Car_sub_403800((struct Car *)&DAT_00669f80,(int *)&DAT_00669f14);
  if (CONCAT31(extraout_var_02,bVar4) == 0) {
LAB_0048b3fa:
    pSVar12 = self->Sprite;
    pSVar9 = *(SpriteS1 **)&pSVar12->field_0x18;
    pSVar7 = (struct SpriteS1 *)pSVar12->Point2D1;
  }
  else {
    pSVar10 = (struct SpriteS1 *)
              gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a18c,(GlassInfo *)&local_c,
                         (struct S127 *)&DAT_00669f14);
    bVar4 = gta2::Point2D_FUN_004037e0((Point2D *)&DAT_00669f80,pSVar10);
    if ((CONCAT31(extraout_var_03,bVar4) == 0) ||
       (bVar4 = gta2::Car_sub_403800((struct Car *)&DAT_0066a1ec,(int *)&DAT_00669f14),
       CONCAT31(extraout_var_04,bVar4) == 0)) goto LAB_0048b3fa;
    pSVar10 = (struct SpriteS1 *)
              gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a18c,(GlassInfo *)&local_c,
                         (struct S127 *)&DAT_00669f14);
    bVar4 = gta2::Point2D_FUN_004037e0((Point2D *)&DAT_0066a1ec,pSVar10);
    if (CONCAT31(extraout_var_05,bVar4) == 0) goto LAB_0048b3fa;
    pSVar12 = self->Sprite;
  }
  gta2::SpriteS1_sub_420600(pSVar12,(int)pSVar7,(int)pSVar9,local_54._4_4_);
  switch(self->field_0x46) {
  case 0:
  case 1:
  case 2:
    cVar13 = '\n';
    bVar11 = 1;
    goto LAB_0048b43a;
  case 3:
    cVar13 = '\n';
    break;
  case 4:
    cVar13 = '\x0f';
    break;
  case 5:
    cVar13 = '\x14';
    break;
  case 6:
    cVar13 = '\x19';
    break;
  case 7:
    cVar13 = '\x1e';
    break;
  default:
    goto switchD_0048b419_caseD_8;
  }
  bVar11 = 2;
LAB_0048b43a:
  gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,bVar11,cVar13);
switchD_0048b419_caseD_8:
  gta2::SpriteS1_sub_4337F0(self->Sprite);
  if (*(int *)&self->field_0x40 != 0) {
    FUN_004be570(self->Sprite,
                 *(Sprite **)(*(int *)(*(int *)&self->field_0x40 + 0x14) + 4));
  }
  gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
  bVar11 = self->field_0x46 + 1;
  self->field_0x46 = bVar11;
  if (8 < bVar11) {
    self->field_0x46 = 0;
  }
  return 0;
}


// 0x0048b4d0: Particle1::sub_48B4D0
// IDA: Particle1::sub_48B4D0
// Ghidra: Particle1::FUN_0048b4d0
byte gta2::Particle1_sub_48B4D0(struct Particle1 *self)
{
  byte bVar1;
  
  gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
  bVar1 = self->field_0x46 + 1;
  self->field_0x46 = bVar1;
  if (7 < bVar1) {
    return 1;
  }
  gta2::SpriteS1_sub_4206C0(self->Sprite,gPathNode->a + (ushort)bVar1 + 0x67);
  gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,2,'\x14');
  gta2::SpriteS1_sub_4337F0(self->Sprite);
  gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
  return 0;
}


// 0x0048b540: Particle1::sub_48B540
// IDA: Particle1::sub_48B540
// Ghidra: Particle1::FUN_0048b540
byte gta2::Particle1_sub_48B540(struct Particle1 *self)
{
  byte bVar1;
  bool bVar2;
  short sVar3;
  undefined3 extraout_var;
  int iVar4;
  struct SpriteS1 *pSVar5;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int *piVar6;
  struct PathNode *pPVar7;
  struct S127 *pSVar8;
  void *this_00;
  struct SpriteS1 *pSVar9;
  undefined3 extraout_var_02;
  struct SpriteS1 *pSVar10;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined1 *puVar11;
  Sprite *pSVar12;
  undefined1 *puVar13;
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  struct SpriteS1 *local_34;
  struct Player *local_30;
  struct Player *local_2c;
  Matrix3D *local_28;
  struct Ped *local_24;
  Point2D local_20;
  struct SpriteS1 *local_8;
  Matrix3D *local_4;
  
  local_30 = _DAT_00669f7c;
  local_2c = _DAT_00669f7c;
  gta2::bitShiftLeft1(&local_34,NULL);
  gta2::bitShiftLeft1(local_38,NULL);
  String_ParseLine(&local_8,(undefined4 *)local_38,&local_34);
  self->field_0x46 = self->field_0x46 + '\x01';
  gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
  if ((self->field_0x46 == '\x10') || (*(short *)&self->field_0x2c == 0)) {
    return 1;
  }
  iVar4 = *(int *)&self->field_0x40;
  if (iVar4 == 0) {
    *(Player **)&self->field_0x20 = _DAT_00669f7c;
  }
  else if (*(short *)(iVar4 + 6) == *(short *)&self->field_0x44) {
    if (*(int *)(iVar4 + 0x14) == 0) {
      *(undefined4 *)&self->field_0x40 = 0;
      *(Player **)&self->field_0x20 = _DAT_00669f7c;
    }
    else {
      if (*(int *)(*(int *)(iVar4 + 0x14) + 4) != 0) {
        bVar1 = FUN_004827d0(*(void **)(*(int *)(*(int *)(iVar4 + 0x14) + 4) + 8
                                       ),(undefined4 *)&local_20);
        iVar4 = *(int *)&self->field_0x40;
        *(undefined4 *)&self->field_0x20 =
             *(undefined4 *)CONCAT31(extraout_var,bVar1);
        *(undefined2 *)&self->CarSystemManager_ =
             *(undefined2 *)(*(int *)(*(int *)(iVar4 + 0x14) + 0x10) + 4);
      }
      if (*(short *)(iVar4 + 0x1a) == 1) {
        *(undefined4 *)&self->field_0x40 = 0;
      }
    }
  }
  else {
    *(undefined4 *)&self->field_0x40 = 0;
    *(Player **)&self->field_0x20 = _DAT_00669f7c;
  }
  pSVar12 = self->Sprite;
  local_34 = _DAT_00669e98;
  pSVar5 = gta2::S202_sub_401B20((Point2D *)&pSVar12->Point2D,(struct SpriteS1 *)&local_20,
                      (struct S127 *)&local_34);
  local_34 = pSVar5->FirstElement;
  bVar2 = gta2::Player_sub_40CE70((struct Player *)&local_34,(struct Player *)&DAT_00669fa4);
  if (CONCAT31(extraout_var_00,bVar2) != 0) {
    return 1;
  }
  local_20.Array_24._0_4_ = *(undefined4 *)&pSVar12->field_0x18;
  local_24 = (struct Ped *)pSVar12->Point2D1;
  puVar11 = &self->field_0x20;
  bVar2 = gta2::Point2D_FUN_004037e0((Point2D *)puVar11,(struct SpriteS1 *)&DAT_0066a180);
  if (CONCAT31(extraout_var_01,bVar2) != 0) {
    gta2::bitShiftLeft1(&local_2c,NULL);
    local_30 = local_2c;
    piVar6 = (int *)gta2::JustCopyByPtrAtoC(&DAT_00669e90,&local_28);
    local_2c = (struct Player *)*piVar6;
  }
  bVar1 = self->field_0x46;
  if ((bVar1 == 0) || (4 < bVar1)) {
    gta2::SpriteS1_sub_4206C0(pSVar12,gPathNode->a + (ushort)bVar1 + 0x93);
    gta2::bitShiftLeft1(local_38,NULL);
    local_8 = (struct SpriteS1 *)local_38;
    piVar6 = NULL;
    gta2::bitShiftLeft1((undefined1 *)((int)&local_20 + 0xc),
                  (void *)((byte)self->field_0x46 / 10));
    puVar13 = (undefined1 *)((int)&local_20 + 0x10);
    this_00 = gta2::WorldCoordinateToScreenCoord
                        (puVar11,(undefined1 *)((int)&local_20 + 0x14),
                         (int *)&DAT_00669f98);
    piVar6 = (int *)gta2::WorldCoordinateToScreenCoord(this_00,puVar13,piVar6);
    local_4 = (Matrix3D *)*piVar6;
  }
  else {
    pPVar7 = gPathNode;
    gta2::SpriteS1_sub_4206C0(pSVar12,gPathNode->a + (ushort)bVar1 + 0x93);
    gta2::bitShiftLeft1(local_38,NULL);
    piVar6 = (int *)CONCAT31((int3)((uint)pPVar7 >> 8),self->field_0x46);
    local_8 = (struct SpriteS1 *)local_38;
    gta2::FUN_0040ce30(&local_28,self->field_0x46);
    pSVar8 = (struct S127 *)gta2::WorldCoordinateToScreenCoord(&DAT_00669e94,local_3c,piVar6)
    ;
    piVar6 = (int *)gta2::Player_sub_401B40((SpawnPoint *)&DAT_00669f14,
                               (GlassInfo *)((int)&local_20 + 4),pSVar8);
    piVar6 = (int *)gta2::WorldCoordinateToScreenCoord
                              (puVar11,(undefined1 *)((int)&local_20 + 8),piVar6
                              );
    local_4 = (Matrix3D *)*piVar6;
  }
  FUN_0040f6b0(&local_8,(GlassInfo *)&self->CarSystemManager_);
  self->field11_0x14 = local_8;
  self->field12_0x18 = local_4;
  local_38 = (undefined1  [4])0x3;
  sVar3 = gta2::Random_Random((struct Random *)&gRandom,(short)local_38);
  gta2::S202_sub_41F980((struct SpriteS1 *)local_38,sVar3 + -1);
  local_3c = local_38;
  local_38 = (undefined1  [4])0x1e;
  pSVar5 = gta2::S122_sub_401BF0((struct Model *)local_3c,
                              (struct SpriteS1 *)((int)&local_20 + 0x14),
                              (int *)local_38);
  local_3c = (undefined1  [4])pSVar5->FirstElement;
  local_38 = (undefined1  [4])0x3;
  sVar3 = gta2::Random_Random((struct Random *)&gRandom,(short)local_38);
  gta2::S202_sub_41F980((struct SpriteS1 *)local_38,sVar3 + -1);
  local_28 = (Matrix3D *)0x1e;
  pSVar5 = gta2::S122_sub_401BF0((struct Model *)local_38,
                              (struct SpriteS1 *)((int)&local_20 + 0x14),
                              (int *)&local_28);
  local_38 = (undefined1  [4])pSVar5->FirstElement;
  pSVar8 = (struct S127 *)&local_30;
  pSVar5 = (struct SpriteS1 *)((int)&local_20 + 0x14);
  pSVar9 = gta2::S202_sub_401B20((Point2D *)local_3c,(struct SpriteS1 *)((int)&local_20 + 0x10),
                      (struct S127 *)&self->field11_0x14);
  pSVar9 = gta2::S202_sub_401B20((Point2D *)pSVar9,pSVar5,pSVar8);
  pSVar8 = (struct S127 *)&local_2c;
  pSVar5 = (struct SpriteS1 *)((int)&local_20 + 0x14);
  self->field8_0x8 = pSVar9->FirstElement;
  pSVar9 = gta2::S202_sub_401B20((Point2D *)local_38,(struct SpriteS1 *)((int)&local_20 + 0x10),
                      (struct S127 *)&self->field12_0x18);
  pSVar5 = gta2::S202_sub_401B20((Point2D *)pSVar9,pSVar5,pSVar8);
  self->field9_0xc = pSVar5->FirstElement;
  pSVar5 = gta2::S202_sub_401B20((Point2D *)&local_24,(struct SpriteS1 *)((int)&local_20 + 0x14),
                      (struct S127 *)&self->field8_0x8);
  pSVar5 = pSVar5->FirstElement;
  pSVar9 = gta2::S202_sub_401B20(&local_20,(struct SpriteS1 *)((int)&local_20 + 0x14),
                      (struct S127 *)&self->field9_0xc);
  pSVar9 = pSVar9->FirstElement;
  _DAT_00669f80 = pSVar5;
  _DAT_0066a1ec = pSVar9;
  bVar2 = gta2::Car_sub_403800((struct Car *)&DAT_00669f80,(int *)&DAT_00669f14);
  if (CONCAT31(extraout_var_02,bVar2) != 0) {
    pSVar10 = (struct SpriteS1 *)
              gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a18c,
                         (GlassInfo *)((int)&local_20 + 0x14),
                         (struct S127 *)&DAT_00669f14);
    bVar2 = gta2::Point2D_FUN_004037e0((Point2D *)&DAT_00669f80,pSVar10);
    if ((CONCAT31(extraout_var_03,bVar2) != 0) &&
       (bVar2 = gta2::Car_sub_403800((struct Car *)&DAT_0066a1ec,(int *)&DAT_00669f14),
       CONCAT31(extraout_var_04,bVar2) != 0)) {
      pSVar10 = (struct SpriteS1 *)
                gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a18c,
                           (GlassInfo *)((int)&local_20 + 0x14),
                           (struct S127 *)&DAT_00669f14);
      bVar2 = gta2::Point2D_FUN_004037e0((Point2D *)&DAT_0066a1ec,pSVar10);
      if (CONCAT31(extraout_var_05,bVar2) != 0) {
        pSVar12 = self->Sprite;
        goto LAB_0048b958;
      }
    }
  }
  pSVar12 = self->Sprite;
  pSVar9 = *(SpriteS1 **)&pSVar12->field_0x18;
  pSVar5 = (struct SpriteS1 *)pSVar12->Point2D1;
LAB_0048b958:
  gta2::SpriteS1_sub_420600(pSVar12,(int)pSVar5,(int)pSVar9,(int)local_34);
  gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,2,'\x0f');
  gta2::SpriteS1_sub_4337F0(self->Sprite);
  puVar11 = (undefined1 *)((int)&local_20 + 0x14);
  piVar6 = (int *)&DAT_00669e94;
  puVar13 = puVar11;
  gta2::FUN_0040ce30((undefined1 *)((int)&local_20 + 0x10),self->field_0x46);
  pSVar8 = (struct S127 *)gta2::WorldCoordinateToScreenCoord(puVar11,puVar13,piVar6);
  pSVar5 = gta2::S202_sub_401B20((Point2D *)&DAT_00669f14,
                      (struct SpriteS1 *)((int)&local_20 + 0xc),pSVar8);
  gta2::SpriteS1_sub_4BDEF0(self->Sprite,pSVar5->FirstElement,0);
  if (*(int *)&self->field_0x40 != 0) {
    FUN_004be570(self->Sprite,
                 *(Sprite **)(*(int *)(*(int *)&self->field_0x40 + 0x14) + 4));
  }
  gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
  return 0;
}


// 0x0048b9f0: Particle1::sub_48B9F0
// IDA: Particle1::sub_48B9F0
// Ghidra: Particle1::FUN_0048b9f0
byte gta2::Particle1_sub_48B9F0(struct Particle1 *self)
{
  undefined1 *this_00;
  byte bVar1;
  bool bVar2;
  short sVar3;
  undefined3 extraout_var;
  int iVar4;
  struct SpriteS1 *pSVar5;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int *piVar6;
  struct PathNode *pPVar7;
  struct S127 *pSVar8;
  void *this_01;
  struct SpriteS1 *pSVar9;
  undefined3 extraout_var_02;
  struct SpriteS1 *pSVar10;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  Sprite *pSVar11;
  undefined1 *pS110;
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  struct SpriteS1 *local_34;
  struct Player *local_30;
  struct Player *local_2c;
  Matrix3D *local_28;
  struct Ped *local_24;
  Point2D local_20;
  struct SpriteS1 *local_8;
  Matrix3D *local_4;
  
  local_30 = _DAT_00669f7c;
  local_2c = _DAT_00669f7c;
  gta2::bitShiftLeft1(&local_34,NULL);
  gta2::bitShiftLeft1(local_38,NULL);
  String_ParseLine(&local_8,(undefined4 *)local_38,&local_34);
  self->field_0x46 = self->field_0x46 + '\x01';
  gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
  if ((self->field_0x46 == '\x10') || (*(short *)&self->field_0x2c == 0)) {
    return 1;
  }
  iVar4 = *(int *)&self->field_0x40;
  if (iVar4 == 0) {
    *(Player **)&self->field_0x20 = _DAT_00669f7c;
  }
  else if (*(short *)(iVar4 + 6) == *(short *)&self->field_0x44) {
    if (*(int *)(iVar4 + 0x14) == 0) {
      *(undefined4 *)&self->field_0x40 = 0;
      *(Player **)&self->field_0x20 = _DAT_00669f7c;
    }
    else {
      if (*(int *)(*(int *)(iVar4 + 0x14) + 4) != 0) {
        bVar1 = FUN_004827d0(*(void **)(*(int *)(*(int *)(iVar4 + 0x14) + 4) + 8
                                       ),(undefined4 *)&local_20);
        iVar4 = *(int *)&self->field_0x40;
        *(undefined4 *)&self->field_0x20 =
             *(undefined4 *)CONCAT31(extraout_var,bVar1);
        *(undefined2 *)&self->CarSystemManager_ =
             *(undefined2 *)(*(int *)(*(int *)(iVar4 + 0x14) + 0x10) + 4);
      }
      if (*(short *)(iVar4 + 0x1a) == 1) {
        *(undefined4 *)&self->field_0x40 = 0;
      }
    }
  }
  else {
    *(undefined4 *)&self->field_0x40 = 0;
    *(Player **)&self->field_0x20 = _DAT_00669f7c;
  }
  pSVar11 = self->Sprite;
  local_34 = _DAT_00669fcc;
  pSVar5 = gta2::S202_sub_401B20((Point2D *)&pSVar11->Point2D,(struct SpriteS1 *)&local_20,
                      (struct S127 *)&local_34);
  local_34 = pSVar5->FirstElement;
  bVar2 = gta2::Player_sub_40CE70((struct Player *)&local_34,(struct Player *)&DAT_00669fa4);
  if (CONCAT31(extraout_var_00,bVar2) != 0) {
    return 1;
  }
  local_20.Array_24._0_4_ = *(undefined4 *)&pSVar11->field_0x18;
  local_24 = (struct Ped *)pSVar11->Point2D1;
  this_00 = &self->field_0x20;
  bVar2 = gta2::Point2D_FUN_004037e0((Point2D *)this_00,(struct SpriteS1 *)&DAT_0066a180);
  if (CONCAT31(extraout_var_01,bVar2) != 0) {
    gta2::bitShiftLeft1(&local_2c,NULL);
    local_30 = local_2c;
    piVar6 = (int *)gta2::JustCopyByPtrAtoC(&DAT_00669e90,&local_28);
    local_2c = (struct Player *)*piVar6;
  }
  bVar1 = self->field_0x46;
  if ((bVar1 == 0) || (4 < bVar1)) {
    gta2::SpriteS1_sub_4206C0(pSVar11,gPathNode->a + (ushort)bVar1 + 0x93);
    gta2::bitShiftLeft1(local_38,NULL);
    local_8 = (struct SpriteS1 *)local_38;
    piVar6 = NULL;
    gta2::bitShiftLeft1((undefined1 *)((int)&local_20 + 0xc),
                  (void *)((byte)self->field_0x46 / 10));
    pS110 = (undefined1 *)((int)&local_20 + 0x10);
    this_01 = gta2::WorldCoordinateToScreenCoord
                        (this_00,(undefined1 *)((int)&local_20 + 0x14),
                         (int *)&DAT_00669f3c);
    piVar6 = (int *)gta2::WorldCoordinateToScreenCoord(this_01,pS110,piVar6);
    local_4 = (Matrix3D *)*piVar6;
  }
  else {
    pPVar7 = gPathNode;
    gta2::SpriteS1_sub_4206C0(pSVar11,gPathNode->a + (ushort)bVar1 + 0x93);
    gta2::bitShiftLeft1(local_38,NULL);
    piVar6 = (int *)CONCAT31((int3)((uint)pPVar7 >> 8),self->field_0x46);
    local_8 = (struct SpriteS1 *)local_38;
    gta2::FUN_0040ce30(&local_28,self->field_0x46);
    pSVar8 = (struct S127 *)gta2::WorldCoordinateToScreenCoord(&DAT_00669e94,local_3c,piVar6)
    ;
    piVar6 = (int *)gta2::Player_sub_401B40((SpawnPoint *)&DAT_00669f14,
                               (GlassInfo *)((int)&local_20 + 4),pSVar8);
    piVar6 = (int *)gta2::WorldCoordinateToScreenCoord
                              (this_00,(undefined1 *)((int)&local_20 + 8),piVar6
                              );
    local_4 = (Matrix3D *)*piVar6;
  }
  FUN_0040f6b0(&local_8,(GlassInfo *)&self->CarSystemManager_);
  self->field11_0x14 = local_8;
  self->field12_0x18 = local_4;
  local_38 = (undefined1  [4])0x3;
  sVar3 = gta2::Random_Random((struct Random *)&gRandom,(short)local_38);
  gta2::S202_sub_41F980((struct SpriteS1 *)local_38,sVar3 + -1);
  local_3c = local_38;
  local_38 = (undefined1  [4])0x32;
  pSVar5 = gta2::S122_sub_401BF0((struct Model *)local_3c,
                              (struct SpriteS1 *)((int)&local_20 + 0x14),
                              (int *)local_38);
  local_3c = (undefined1  [4])pSVar5->FirstElement;
  local_38 = (undefined1  [4])0x3;
  sVar3 = gta2::Random_Random((struct Random *)&gRandom,(short)local_38);
  gta2::S202_sub_41F980((struct SpriteS1 *)local_38,sVar3 + -1);
  local_28 = (Matrix3D *)0x32;
  pSVar5 = gta2::S122_sub_401BF0((struct Model *)local_38,
                              (struct SpriteS1 *)((int)&local_20 + 0x14),
                              (int *)&local_28);
  local_38 = (undefined1  [4])pSVar5->FirstElement;
  pSVar8 = (struct S127 *)&local_30;
  pSVar5 = (struct SpriteS1 *)((int)&local_20 + 0x14);
  pSVar9 = gta2::S202_sub_401B20((Point2D *)local_3c,(struct SpriteS1 *)((int)&local_20 + 0x10),
                      (struct S127 *)&self->field11_0x14);
  pSVar9 = gta2::S202_sub_401B20((Point2D *)pSVar9,pSVar5,pSVar8);
  pSVar8 = (struct S127 *)&local_2c;
  pSVar5 = (struct SpriteS1 *)((int)&local_20 + 0x14);
  self->field8_0x8 = pSVar9->FirstElement;
  pSVar9 = gta2::S202_sub_401B20((Point2D *)local_38,(struct SpriteS1 *)((int)&local_20 + 0x10),
                      (struct S127 *)&self->field12_0x18);
  pSVar5 = gta2::S202_sub_401B20((Point2D *)pSVar9,pSVar5,pSVar8);
  self->field9_0xc = pSVar5->FirstElement;
  pSVar5 = gta2::S202_sub_401B20((Point2D *)&local_24,(struct SpriteS1 *)((int)&local_20 + 0x14),
                      (struct S127 *)&self->field8_0x8);
  pSVar5 = pSVar5->FirstElement;
  pSVar9 = gta2::S202_sub_401B20(&local_20,(struct SpriteS1 *)((int)&local_20 + 0x14),
                      (struct S127 *)&self->field9_0xc);
  pSVar9 = pSVar9->FirstElement;
  _DAT_00669f80 = pSVar5;
  _DAT_0066a1ec = pSVar9;
  bVar2 = gta2::Car_sub_403800((struct Car *)&DAT_00669f80,(int *)&DAT_00669f14);
  if (CONCAT31(extraout_var_02,bVar2) != 0) {
    pSVar10 = (struct SpriteS1 *)
              gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a18c,
                         (GlassInfo *)((int)&local_20 + 0x14),
                         (struct S127 *)&DAT_00669f14);
    bVar2 = gta2::Point2D_FUN_004037e0((Point2D *)&DAT_00669f80,pSVar10);
    if ((CONCAT31(extraout_var_03,bVar2) != 0) &&
       (bVar2 = gta2::Car_sub_403800((struct Car *)&DAT_0066a1ec,(int *)&DAT_00669f14),
       CONCAT31(extraout_var_04,bVar2) != 0)) {
      pSVar10 = (struct SpriteS1 *)
                gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a18c,
                           (GlassInfo *)((int)&local_20 + 0x14),
                           (struct S127 *)&DAT_00669f14);
      bVar2 = gta2::Point2D_FUN_004037e0((Point2D *)&DAT_0066a1ec,pSVar10);
      if (CONCAT31(extraout_var_05,bVar2) != 0) {
        pSVar11 = self->Sprite;
        goto LAB_0048be09;
      }
    }
  }
  pSVar11 = self->Sprite;
  pSVar9 = *(SpriteS1 **)&pSVar11->field_0x18;
  pSVar5 = (struct SpriteS1 *)pSVar11->Point2D1;
LAB_0048be09:
  gta2::SpriteS1_sub_420600(pSVar11,(int)pSVar5,(int)pSVar9,(int)local_34);
  gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,2,'\x0f');
  gta2::SpriteS1_sub_4337F0(self->Sprite);
  if (*(int *)&self->field_0x40 != 0) {
    FUN_004be570(self->Sprite,
                 *(Sprite **)(*(int *)(*(int *)&self->field_0x40 + 0x14) + 4));
  }
  gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
  return 0;
}


// 0x0048be60: Particle1::sub_48BE60
// IDA: Particle1::sub_48BE60
// Ghidra: Particle1::FUN_0048be60
byte gta2::Particle1_sub_48BE60(struct Particle1 *self)
{
  byte bVar1;
  
  gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
  if (*(short *)&self->field_0x2c == 0) {
    return 1;
  }
  if (self->field_0x48 == '\0') {
    self->field_0x48 = 3;
    bVar1 = self->field_0x46 + 1;
    self->field_0x46 = bVar1;
    if (5 < bVar1) {
      self->field_0x46 = 5;
    }
  }
  else {
    self->field_0x48 = self->field_0x48 + -1;
  }
  gta2::SpriteS1_sub_4206C0(self->Sprite,
                   (ushort)(byte)self->field_0x46 + gPathNode->a + 0xbf);
  gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
  return 0;
}


// 0x0048bee0: Particle1::sub_48BEE0
// IDA: Particle1::sub_48BEE0
// Ghidra: Particle1::FUN_0048bee0
byte gta2::Particle1_sub_48BEE0(struct Particle1 *self)
{
  bool bVar1;
  int iVar2;
  struct Car *this_00;
  struct Model *pMVar3;
  struct SpriteS1 *pSVar4;
  struct SpriteS1 *pSVar5;
  struct SpriteS1 *pS127;
  struct SpriteS1 *pSVar6;
  undefined4 *puVar7;
  void *pvVar8;
  struct SpriteS1 *pSVar9;
  byte bVar10;
  struct SpriteS1 **ppSVar11;
  struct S127 *pSVar12;
  struct SpriteS1 *local_34;
  struct SpriteS1 *local_30;
  short local_2c;
  struct SpriteS1 *local_28;
  undefined1 local_24 [4];
  undefined1 local_20 [8];
  struct SpriteS1 *local_18;
  struct SpriteS1 *local_14;
  struct SpriteS1 *local_10;
  struct SpriteS1 *local_c;
  undefined1 local_8 [8];
  
  gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&local_2c);
  _DAT_00669f80 = self->Sprite->Point2D1;
  _DAT_0066a1ec = *(undefined4 *)&self->Sprite->field_0x18;
  pSVar9 = *(SpriteS1 **)&self->field_0x28;
  iVar2 = gta2::SpriteS1_getSpriteType(pSVar9);
  if (iVar2 == 2) {
    this_00 = (struct Car *)gta2::SpriteS1_GetCar(pSVar9);
    if (this_00 != NULL) {
      bVar1 = gta2::Car_GetMask(this_00);
      if (!bVar1) {
        bVar10 = self->field_0x46 + 1;
        self->field_0x46 = bVar10;
        if (bVar10 != 5) {
          local_2c = *(short *)&pSVar9->FirstElement;
          pSVar12 = (struct S127 *)&DAT_00669eb0;
          local_30 = (struct SpriteS1 *)0x2;
          if (bVar10 < 4) {
            pSVar5 = (struct SpriteS1 *)&local_28;
            ppSVar11 = &local_30;
            pSVar4 = (struct SpriteS1 *)&local_34;
            pMVar3 = (struct Model *)FUN_0048a930(local_24);
            pSVar4 = gta2::S122_sub_401BF0(pMVar3,pSVar4,(int *)ppSVar11);
            pSVar5 = gta2::S202_sub_401B20((Point2D *)pSVar4,pSVar5,pSVar12);
            local_30 = pSVar5->FirstElement;
            pSVar5 = (struct SpriteS1 *)local_20;
            pSVar12 = (struct S127 *)&DAT_0066a178;
            ppSVar11 = &local_34;
            pSVar4 = (struct SpriteS1 *)(local_20 + 4);
            local_34 = (struct SpriteS1 *)0x2;
            pMVar3 = (struct Model *)FUN_0048a950(local_24);
            pSVar4 = gta2::S122_sub_401BF0(pMVar3,pSVar4,(int *)ppSVar11);
            pSVar5 = gta2::S202_sub_401B20((Point2D *)pSVar4,pSVar5,pSVar12);
            local_34 = pSVar5->FirstElement;
          }
          else {
            pSVar5 = (struct SpriteS1 *)(local_20 + 4);
            ppSVar11 = &local_30;
            pSVar4 = (struct SpriteS1 *)local_20;
            pMVar3 = (struct Model *)FUN_0048a930(local_24);
            pSVar4 = gta2::S122_sub_401BF0(pMVar3,pSVar4,(int *)ppSVar11);
            pSVar5 = gta2::S202_sub_401B20((Point2D *)pSVar4,pSVar5,pSVar12);
            local_30 = pSVar5->FirstElement;
            pSVar5 = (struct SpriteS1 *)&local_18;
            pSVar12 = (struct S127 *)&DAT_00669e94;
            local_34 = (struct SpriteS1 *)0x1;
            local_28 = (struct SpriteS1 *)0x2;
            pS127 = FUN_00401bd0(&DAT_00669ee4,(struct SpriteS1 *)(local_20 + 4),
                                 (int *)&local_34);
            pSVar4 = (struct SpriteS1 *)&local_10;
            ppSVar11 = &local_28;
            pSVar6 = (struct SpriteS1 *)local_8;
            pMVar3 = (struct Model *)FUN_0048a950(local_20);
            pSVar6 = gta2::S122_sub_401BF0(pMVar3,pSVar6,(int *)ppSVar11);
            pSVar4 = gta2::S202_sub_401B20((Point2D *)pSVar6,pSVar4,(struct S127 *)pS127);
            pSVar5 = gta2::S202_sub_401B20((Point2D *)pSVar4,pSVar5,pSVar12);
            local_34 = pSVar5->FirstElement;
          }
          if (*(int *)&self->field_0x38 == 0x28) {
            FUN_00432860(&local_10,&local_30,&local_34);
            FUN_0040f6b0(&local_10,(GlassInfo *)&local_2c);
          }
          else {
            ppSVar11 = &local_34;
            puVar7 = (undefined4 *)gta2::JustCopyByPtrAtoC(&local_30,local_8);
            FUN_00432860(&local_10,puVar7,ppSVar11);
            FUN_0040f6b0(&local_10,(GlassInfo *)&local_2c);
          }
          iVar2 = gta2::SpriteS1_sub_4207B0(pSVar9,local_8);
          FUN_0040f680(&local_10,iVar2);
          gta2::SpriteS1_sub_4206C0(self->Sprite,gPathNode->a + (ushort)bVar10 + 200);
          gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,2,'\x14');
          gta2::SpriteS1_SetRotation(self->Sprite,**(short **)&self->field_0x28);
          iVar2 = *(int *)(*(int *)&self->field_0x28 + 0x1c);
LAB_0048c235:
          gta2::SpriteS1_sub_420600(self->Sprite,(int)local_10,(int)local_c,iVar2);
          gta2::SpriteS1_sub_4337F0(self->Sprite);
          gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
          return 0;
        }
      }
    }
  }
  else {
    iVar2 = gta2::SpriteS1_GetGameObject(pSVar9);
    if ((iVar2 != 0) && (*(Ped **)(iVar2 + 0x7c) != NULL)) {
      pvVar8 = gta2::Ped_Get_433B40(*(Ped **)(iVar2 + 0x7c));
      if ((char)pvVar8 != '\0') {
        bVar10 = self->field_0x46 + 1;
        self->field_0x46 = bVar10;
        if (bVar10 != 4) {
          if ((*(byte *)(iVar2 + 0x58) & 8) == 0) {
            puVar7 = (undefined4 *)gta2::JustCopyByPtrAtoC(&DAT_00669e90,local_8);
            local_14 = _DAT_00669f98;
          }
          else {
            puVar7 = (undefined4 *)gta2::JustCopyByPtrAtoC(&DAT_00669e90,local_8);
            local_14 = _DAT_0066a168;
          }
          local_18 = (struct SpriteS1 *)*puVar7;
          FUN_0040f6b0(&local_18,(GlassInfo *)pSVar9);
          puVar7 = (undefined4 *)
                   FUN_0040f5c0(&local_18,local_8,(struct SpriteS1 *)(iVar2 + 0x98));
          local_18 = (struct SpriteS1 *)*puVar7;
          local_14 = (struct SpriteS1 *)puVar7[1];
          gta2::SpriteS1_sub_4206C0(self->Sprite,gPathNode->a + (ushort)bVar10 + 0xc5);
          gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,2,'\x14');
          iVar2 = *(int *)&self->field_0x28;
          pSVar9 = gta2::S202_sub_401B20((Point2D *)(iVar2 + 0x18),(struct SpriteS1 *)local_8,
                              (struct S127 *)&local_14);
          pSVar5 = gta2::S202_sub_401B20((Point2D *)(iVar2 + 0x14),(struct SpriteS1 *)&local_10,
                              (struct S127 *)&local_18);
          iVar2 = *(int *)(iVar2 + 0x1c);
          local_c = pSVar9->FirstElement;
          local_10 = pSVar5->FirstElement;
          goto LAB_0048c235;
        }
      }
    }
  }
  return 1;
}


// 0x0048c270: Particle1::sub_48C270
// IDA: Particle1::sub_48C270
// Ghidra: Particle1::FUN_0048c270
byte gta2::Particle1_sub_48C270(struct Particle1 *self)
{
  undefined4 *pS127;
  bool bVar1;
  struct SpriteS1 *pSVar2;
  struct SpriteS1 *pSVar3;
  struct SpriteS1 *pSVar4;
  undefined3 extraout_var;
  Sprite *pSVar5;
  struct S127 *pSVar6;
  struct SpriteS1 *local_14;
  struct SpriteS1 *local_10;
  struct SpriteS1 *local_c;
  
  pSVar3 = _DAT_00669e90;
  local_10 = _DAT_00669f7c;
  local_c = _DAT_00669f7c;
  gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
  if (*(ushort *)&self->field_0x2c == 0) {
    return 1;
  }
  pS127 = &self->field8_0x8;
  if (*(ushort *)&self->field_0x2e >> 1 < *(ushort *)&self->field_0x2c) {
    pSVar2 = gta2::S202_sub_401B20((Point2D *)pS127,(struct SpriteS1 *)&local_14,
                        (struct S127 *)&self->field11_0x14);
    *pS127 = pSVar2->FirstElement;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&self->field9_0xc,(struct SpriteS1 *)&local_14,
                        (struct S127 *)&self->field12_0x18);
    local_14 = pSVar3;
    pSVar5 = self->Sprite;
    self->field9_0xc = pSVar2->FirstElement;
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&pSVar5->Point2D,(struct SpriteS1 *)&stack0xfffffff8
                        ,(struct S127 *)&local_14);
  }
  else {
    pSVar2 = gta2::S202_sub_401B20((Point2D *)pS127,(struct SpriteS1 *)&stack0xfffffff8,
                        (struct S127 *)&self->field11_0x14);
    *pS127 = pSVar2->FirstElement;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&self->field9_0xc,
                        (struct SpriteS1 *)&stack0xfffffff8,(struct S127 *)&self->field12_0x18
                       );
    local_14 = pSVar3;
    pSVar5 = self->Sprite;
    self->field9_0xc = pSVar2->FirstElement;
    pSVar3 = (struct SpriteS1 *)
             gta2::Player_sub_401B40((SpawnPoint *)&pSVar5->Point2D,
                        (GlassInfo *)&stack0xfffffff8,(struct S127 *)&local_14);
  }
  local_14 = pSVar3->FirstElement;
  pSVar6 = (struct S127 *)&local_10;
  pSVar3 = (struct SpriteS1 *)&stack0xfffffff8;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&pSVar5->Point2D1,(struct SpriteS1 *)&stack0xfffffffc,
                      (struct S127 *)pS127);
  pSVar3 = gta2::S202_sub_401B20((Point2D *)pSVar2,pSVar3,pSVar6);
  pSVar2 = pSVar3->FirstElement;
  pSVar6 = (struct S127 *)&local_c;
  pSVar3 = (struct SpriteS1 *)&local_10;
  _DAT_00669f80 = pSVar2;
  pSVar4 = gta2::S202_sub_401B20((Point2D *)&self->Sprite->field_0x18,
                      (struct SpriteS1 *)&stack0xfffffffc,(struct S127 *)&self->field9_0xc);
  pSVar3 = gta2::S202_sub_401B20((Point2D *)pSVar4,pSVar3,pSVar6);
  pSVar3 = pSVar3->FirstElement;
  _DAT_0066a1ec = pSVar3;
  bVar1 = gta2::Car_sub_403800((struct Car *)&local_14,(int *)&DAT_00669fa4);
  pSVar4 = _DAT_00669fa4;
  if (CONCAT31(extraout_var,bVar1) == 0) {
    pSVar4 = local_14;
  }
  gta2::SpriteS1_sub_420600(self->Sprite,(int)pSVar2,(int)pSVar3,(int)pSVar4);
  gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
  return 0;
}


// 0x0048c3e0: Particle1::sub_48C3E0
// IDA: Particle1::sub_48C3E0
// Ghidra: Particle1::FUN_0048c3e0
byte gta2::Particle1_sub_48C3E0(struct Particle1 *self)
{
  undefined4 *pS127;
  bool bVar1;
  struct SpriteS1 *pSVar2;
  struct SpriteS1 *pSVar3;
  undefined3 extraout_var;
  Sprite *pSVar4;
  struct S127 *pSVar5;
  struct SpriteS1 *local_14;
  struct SpriteS1 *local_10;
  struct SpriteS1 *local_c;
  
  pSVar3 = _DAT_00669e94;
  local_10 = _DAT_00669f7c;
  local_c = _DAT_00669f7c;
  self->field_0x46 = self->field_0x46 + '\x01';
  gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
  if (self->field_0x46 == '\x0f') {
    return 1;
  }
  pS127 = &self->field8_0x8;
  if (*(ushort *)&self->field_0x2e >> 1 < *(ushort *)&self->field_0x2c) {
    pSVar2 = gta2::S202_sub_401B20((Point2D *)pS127,(struct SpriteS1 *)&local_14,
                        (struct S127 *)&self->field11_0x14);
    *pS127 = pSVar2->FirstElement;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&self->field9_0xc,(struct SpriteS1 *)&local_14,
                        (struct S127 *)&self->field12_0x18);
    local_14 = pSVar3;
    pSVar4 = self->Sprite;
    self->field9_0xc = pSVar2->FirstElement;
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&pSVar4->Point2D,(struct SpriteS1 *)&stack0xfffffff8
                        ,(struct S127 *)&local_14);
  }
  else {
    pSVar2 = gta2::S202_sub_401B20((Point2D *)pS127,(struct SpriteS1 *)&stack0xfffffff8,
                        (struct S127 *)&self->field11_0x14);
    *pS127 = pSVar2->FirstElement;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&self->field9_0xc,
                        (struct SpriteS1 *)&stack0xfffffff8,(struct S127 *)&self->field12_0x18
                       );
    local_14 = pSVar3;
    pSVar4 = self->Sprite;
    self->field9_0xc = pSVar2->FirstElement;
    pSVar3 = (struct SpriteS1 *)
             gta2::Player_sub_401B40((SpawnPoint *)&pSVar4->Point2D,
                        (GlassInfo *)&stack0xfffffff8,(struct S127 *)&local_14);
  }
  local_14 = pSVar3->FirstElement;
  pSVar5 = (struct S127 *)&local_10;
  pSVar3 = (struct SpriteS1 *)&stack0xfffffff8;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&pSVar4->Point2D1,(struct SpriteS1 *)&stack0xfffffffc,
                      (struct S127 *)pS127);
  pSVar3 = gta2::S202_sub_401B20((Point2D *)pSVar2,pSVar3,pSVar5);
  _DAT_00669f80 = pSVar3->FirstElement;
  pSVar5 = (struct S127 *)&local_c;
  pSVar3 = (struct SpriteS1 *)&local_10;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&self->Sprite->field_0x18,
                      (struct SpriteS1 *)&stack0xfffffffc,(struct S127 *)&self->field9_0xc);
  pSVar3 = gta2::S202_sub_401B20((Point2D *)pSVar2,pSVar3,pSVar5);
  _DAT_0066a1ec = pSVar3->FirstElement;
  bVar1 = gta2::Car_sub_403800((struct Car *)&local_14,(int *)&DAT_00669fa4);
  pSVar3 = _DAT_00669fa4;
  if (CONCAT31(extraout_var,bVar1) == 0) {
    pSVar3 = local_14;
  }
  gta2::SpriteS1_sub_4206C0(self->Sprite,
                   gPathNode->a + (ushort)(byte)self->field_0x46 + 0x83);
  gta2::SpriteS1_sub_420600(self->Sprite,(int)_DAT_00669f80,(int)_DAT_0066a1ec,
                      (int)pSVar3);
  gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
  gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,2,'\x14');
  return 0;
}


// 0x0048c590: Particle1::sub_48C590
// IDA: Particle1::sub_48C590
// Ghidra: Particle1::FUN_0048c590
byte gta2::Particle1_sub_48C590(struct Particle1 *self)
{
  undefined4 *pS127;
  bool bVar1;
  struct SpriteS1 *pSVar2;
  struct SpriteS1 *pSVar3;
  undefined3 extraout_var;
  short sVar4;
  Sprite *pSVar5;
  struct S127 *pSVar6;
  struct SpriteS1 *local_14;
  struct SpriteS1 *local_10;
  struct SpriteS1 *local_c;
  
  pSVar3 = _DAT_00669e90;
  local_10 = _DAT_00669f7c;
  local_c = _DAT_00669f7c;
  gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
  if (*(ushort *)&self->field_0x2c == 0) {
    return 1;
  }
  pS127 = &self->field8_0x8;
  if (*(ushort *)&self->field_0x2e >> 1 < *(ushort *)&self->field_0x2c) {
    pSVar2 = gta2::S202_sub_401B20((Point2D *)pS127,(struct SpriteS1 *)&local_14,
                        (struct S127 *)&self->field11_0x14);
    *pS127 = pSVar2->FirstElement;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&self->field9_0xc,(struct SpriteS1 *)&local_14,
                        (struct S127 *)&self->field12_0x18);
    local_14 = pSVar3;
    pSVar5 = self->Sprite;
    self->field9_0xc = pSVar2->FirstElement;
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&pSVar5->Point2D,(struct SpriteS1 *)&stack0xfffffff8
                        ,(struct S127 *)&local_14);
  }
  else {
    pSVar2 = gta2::S202_sub_401B20((Point2D *)pS127,(struct SpriteS1 *)&stack0xfffffff8,
                        (struct S127 *)&self->field11_0x14);
    *pS127 = pSVar2->FirstElement;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&self->field9_0xc,
                        (struct SpriteS1 *)&stack0xfffffff8,(struct S127 *)&self->field12_0x18
                       );
    local_14 = pSVar3;
    pSVar5 = self->Sprite;
    self->field9_0xc = pSVar2->FirstElement;
    pSVar3 = (struct SpriteS1 *)
             gta2::Player_sub_401B40((SpawnPoint *)&pSVar5->Point2D,
                        (GlassInfo *)&stack0xfffffff8,(struct S127 *)&local_14);
  }
  local_14 = pSVar3->FirstElement;
  pSVar6 = (struct S127 *)&local_10;
  pSVar3 = (struct SpriteS1 *)&stack0xfffffff8;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&pSVar5->Point2D1,(struct SpriteS1 *)&stack0xfffffffc,
                      (struct S127 *)pS127);
  pSVar3 = gta2::S202_sub_401B20((Point2D *)pSVar2,pSVar3,pSVar6);
  _DAT_00669f80 = pSVar3->FirstElement;
  pSVar6 = (struct S127 *)&local_c;
  pSVar3 = (struct SpriteS1 *)&local_10;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&self->Sprite->field_0x18,
                      (struct SpriteS1 *)&stack0xfffffffc,(struct S127 *)&self->field9_0xc);
  pSVar3 = gta2::S202_sub_401B20((Point2D *)pSVar2,pSVar3,pSVar6);
  _DAT_0066a1ec = pSVar3->FirstElement;
  switch(*(undefined2 *)&self->field_0x2c) {
  case 0:
  case 1:
    sVar4 = gPathNode->a + 0x82;
    break;
  case 2:
  case 3:
    sVar4 = gPathNode->a + 0x81;
    break;
  case 4:
    sVar4 = gPathNode->a + 0x80;
    break;
  case 5:
  case 6:
    gta2::SpriteS1_sub_4206C0(self->Sprite,gPathNode->a + 0x7f);
  default:
    goto switchD_0048c6c2_caseD_7;
  }
  gta2::SpriteS1_sub_4206E0(self->Sprite,sVar4);
switchD_0048c6c2_caseD_7:
  bVar1 = gta2::Car_sub_403800((struct Car *)&local_14,(int *)&DAT_00669fa4);
  pSVar3 = _DAT_00669fa4;
  if (CONCAT31(extraout_var,bVar1) == 0) {
    pSVar3 = local_14;
  }
  gta2::SpriteS1_sub_420600(self->Sprite,(int)_DAT_00669f80,(int)_DAT_0066a1ec,
                      (int)pSVar3);
  gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
  return 0;
}


// 0x0048c790: Particle1::sub_48C790
// IDA: Particle1::sub_48C790
// Ghidra: Particle1::FUN_0048c790
byte gta2::Particle1_sub_48C790(struct Particle1 *self)
{
  Sprite *this_00;
  char cVar1;
  
  gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
  cVar1 = self->field_0x46 + '\x01';
  self->field_0x46 = cVar1;
  if (cVar1 == '\x05') {
    return 1;
  }
  this_00 = self->Sprite;
  if (cVar1 == '\x01') {
    gta2::SpriteS1_sub_4206C0(this_00,*(short *)&this_00->field_0x22);
  }
  else {
    gta2::SpriteS1_sub_4206E0(this_00,*(short *)&this_00->field_0x22 + 4);
  }
  gta2::SpriteS1_sub_4337F0(self->Sprite);
  gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
  return 0;
}


// 0x0048c800: Particle1::sub_48C800
// IDA: Particle1::sub_48C800
// Ghidra: Particle1::FUN_0048c800
byte gta2::Particle1_sub_48C800(struct Particle1 *self)
{
  byte bVar1;
  struct SpriteS1 **this_00;
  struct S127 *pS127;
  struct SpriteS1 *pSVar2;
  undefined1 *pS110;
  struct SpriteS1 **ppSVar3;
  struct SpriteS1 *local_c;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  self->field_0x46 = self->field_0x46 + '\x01';
  gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
  bVar1 = self->field_0x46;
  if (bVar1 < 0x1a) {
    if (bVar1 < 0x14) {
      if (bVar1 < 0x11) {
        if (bVar1 < 0xc) {
          bVar1 = 0;
          local_c = _DAT_00669e98;
        }
        else {
          bVar1 = 1;
          local_c = _DAT_0066a15c;
        }
      }
      else {
        local_c = _DAT_0066a15c;
        bVar1 = 2;
      }
    }
    else {
      bVar1 = 3;
      local_c = _DAT_0066a0f8;
    }
    gta2::SpriteS1_sub_4206E0(self->Sprite,gPathNode->a + (ushort)bVar1 + 0x25);
    gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
    gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,2,'\n');
    gta2::SpriteS1_sub_4337F0(self->Sprite);
    this_00 = &local_c;
    pS110 = local_8;
    ppSVar3 = this_00;
    gta2::FUN_0040ce30(local_4,self->field_0x46);
    pS127 = (struct S127 *)gta2::WorldCoordinateToScreenCoord(this_00,pS110,(int *)ppSVar3);
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_00669f14,(struct SpriteS1 *)&local_c,pS127);
    gta2::SpriteS1_sub_4BDEF0(self->Sprite,pSVar2->FirstElement,0);
    return 0;
  }
  return 1;
}


// 0x0048c8f0: Particle1::sub_48C8F0
// IDA: Particle1::sub_48C8F0
// Ghidra: ---
SpriteS1 * gta2::Particle1_sub_48C8F0(struct Particle1 *self)
{
  struct SpriteS1 *SpriteS1; // ecx
  struct SpriteS1 *result; // eax

  SpriteS1 = self->SpriteS1_;
  if ( SpriteS1 )
  {
    gta2::SpriteS1_sub_433800(SpriteS1);
    gta2::SpriteS1_sub_4337D0(self->SpriteS1_, 0, 0);
    result = gta2::SpriteS1_SpriteS1_Des(gSpriteS1, self->SpriteS1_);
    self->SpriteS1_ = 0;
  }
  return result;
}


// 0x0048f230: Particle1::sub_48F230
// IDA: Particle1::sub_48F230
// Ghidra: Particle1::FUN_0048f230
byte gta2::Particle1_sub_48F230(struct Particle1 *self)
{
  byte bVar1;
  bool bVar2;
  short sVar3;
  int iVar4;
  undefined4 *puVar5;
  struct Player *this_00;
  undefined3 extraout_var;
  struct Particle1 *pPVar6;
  undefined2 *puVar7;
  struct Ped *this_01;
  struct CarSystemManager *this_02;
  struct Ped *pPVar8;
  undefined1 *puVar9;
  Point2D *this_03;
  struct SpriteS1 *pSVar10;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  short *unaff_ESI;
  struct Car *pCVar11;
  void *unaff_EDI;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined1 *pS110;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined1 **ppuVar16;
  undefined4 uVar17;
  struct S127 *pS127;
  int *piVar18;
  undefined4 uVar19;
  short *psVar20;
  undefined2 local_56;
  undefined1 local_54 [16];
  undefined1 *local_44;
  undefined1 local_40 [8];
  undefined1 local_38 [16];
  Matrix3D *local_28;
  int local_24;
  struct SpriteS1 *local_20;
  struct SpriteS1 *local_1c;
  SpawnPoint *local_18;
  struct Player *local_14;
  int local_10;
  int local_c;
  
  self->field_0x46 = self->field_0x46 + '\x01';
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)(local_54 + 8))
  ;
  gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
  if (self->field_0x46 == '\x06') {
    return 1;
  }
  pSVar10 = *(SpriteS1 **)&self->field_0x28;
  iVar4 = gta2::SpriteS1_getSpriteType(pSVar10);
  if (iVar4 != 4) {
    return 1;
  }
  FUN_00432860(&local_20,&self->Sprite->Point2D1,
               (undefined4 *)&self->Sprite->field_0x18);
  FUN_00432860(&local_10,&pSVar10->Matrix3DArray[0].PositionX,
               &pSVar10->Matrix3DArray[0].PositionY);
  puVar5 = (undefined4 *)
           FUN_0040f600(&local_10,&local_28,(GlassInfo *)&local_20);
  local_18 = (SpawnPoint *)*puVar5;
  local_14 = (struct Player *)puVar5[1];
  gta2::Player_FUN_0040f790((struct Player *)&local_18,&local_56);
  ppuVar16 = &local_44;
  piVar18 = (int *)&DAT_00669f64;
  this_00 = (struct Player *)FUN_0048a270();
  puVar5 = (undefined4 *)gta2::sub_401B90(this_00,ppuVar16,piVar18);
  local_54._4_4_ = *puVar5;
  bVar2 = gta2::Car_IsTrainOrTrainCarriage((struct Car *)(local_54 + 4),(struct Car *)&DAT_00669f7c);
  if (CONCAT31(extraout_var,bVar2) != 0) {
    FUN_0048a250(&local_18,local_54 + 4);
    local_38._4_4_ = local_1c;
    local_38._12_4_ = local_1c;
    local_38._0_4_ = local_20;
    local_38._8_4_ = local_20;
    local_54._0_4_ = (struct Car *)0x1;
    iVar4 = DecoderFloat(local_54 + 4);
    if (0 < iVar4) {
      do {
        FUN_0040f680(local_38 + 8,(int)&local_18);
        piVar18 = (int *)FUN_0040f600(local_38 + 8,local_40,
                                      (GlassInfo *)local_38);
        local_28 = (Matrix3D *)*piVar18;
        local_24 = piVar18[1];
        FUN_0048a250(&local_28,&DAT_00669ff0);
        FUN_0040f680(&local_28,(int)local_38);
        local_44 = &stack0xffffff94;
        uVar19 = extraout_ECX;
        gta2::bitShiftLeft1(&stack0xffffff94,NULL);
        local_44 = &stack0xffffff90;
        uVar17 = extraout_ECX_00;
        gta2::bitShiftLeft1(&stack0xffffff90,NULL);
        local_44 = &stack0xffffff8c;
        uVar15 = extraout_ECX_01;
        gta2::bitShiftLeft1(&stack0xffffff8c,NULL);
        local_44 = &stack0xffffff88;
        uVar14 = extraout_ECX_02;
        gta2::bitShiftLeft1(&stack0xffffff88,NULL);
        local_44 = &stack0xffffff84;
        uVar13 = extraout_ECX_03;
        gta2::bitShiftLeft1(&stack0xffffff84,NULL);
        local_44 = &stack0xffffff80;
        uVar12 = extraout_ECX_04;
        gta2::bitShiftLeft1(&stack0xffffff80,NULL);
        pPVar6 = gta2::Particles_sub_48C930(gParticles,uVar12,uVar13,uVar14,uVar15,uVar17,uVar19
                           );
        if (pPVar6 != NULL) {
          *(undefined4 *)&pPVar6->field_0x34 = 0;
          *(undefined4 *)&pPVar6->field_0x38 = 0x2b;
          *(undefined2 *)&pPVar6->field_0x2c = 0x32;
          pPVar6->field_0x46 = 0;
          *(undefined2 *)&pPVar6->field_0x2e = 0x32;
          gta2::SpriteS1_sub_4206F0(pPVar6->Sprite,8);
          gta2::SpriteS1_sub_4206C0(pPVar6->Sprite,gPathNode->a + 0x68);
          gta2::SpriteS1_sub_420600(pPVar6->Sprite,(int)local_28,local_24,
                              (int)self->Sprite->Point2D);
          gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)pPVar6->Sprite,2,'\x14');
          gta2::SpriteS1_sub_4337F0(pPVar6->Sprite);
          gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)pPVar6->Sprite);
        }
        pCVar11 = (struct Car *)((int)(Turrel **)local_54._0_4_ + 1);
        local_38._0_4_ = local_38._8_4_;
        local_38._4_4_ = local_38._12_4_;
        local_54._0_4_ = pCVar11;
        iVar4 = DecoderFloat(local_54 + 4);
      } while ((int)pCVar11 <= iVar4);
    }
  }
  local_54._4_4_ = (struct Ped *)0x10;
  local_44 = *(undefined1 **)(*(int *)&self->field_0x28 + 0x14);
  local_54._12_4_ = *(undefined4 *)(*(int *)&self->field_0x28 + 0x18);
  sVar3 = gta2::Random_Random((struct Random *)&gRandom,(short)local_54 + 4);
  gta2::bitShiftLeft1(local_54,(void *)(sVar3 + -8));
  puVar7 = (undefined2 *)
           FUN_00401cb0(&DAT_0066a030,&local_56,(GlassInfo *)local_54);
  bVar1 = self->field_0x46;
  local_54._8_2_ = *puVar7;
  switch(bVar1) {
  case 1:
  case 2:
  case 3:
    this_01 = (struct Ped *)gta2::sub_40E5A0(*(CarSystemManager **)&self->field_0x28,
                                (struct Ped *)&local_56,(short *)&DAT_0066a090,
                                unaff_EDI,unaff_ESI);
    puVar9 = local_54 + 8;
    piVar18 = (int *)&DAT_00669e90;
    pPVar8 = this_01;
    gta2::FUN_0040ce30(local_40,bVar1);
    pSVar10 = (struct SpriteS1 *)gta2::WorldCoordinateToScreenCoord(this_01,puVar9,piVar18);
    break;
  case 4:
  case 5:
    psVar20 = (short *)(local_54 + 8);
    pPVar8 = (struct Ped *)local_54;
    this_02 = (struct CarSystemManager *)
              gta2::sub_40E5A0(*(CarSystemManager **)&self->field_0x28,
                         (struct Ped *)(local_54 + 4),(short *)&DAT_0066a090,pPVar8,
                         psVar20);
    pPVar8 = (struct Ped *)gta2::sub_40E5A0(this_02,pPVar8,psVar20,unaff_EDI,unaff_ESI);
    pSVar10 = (struct SpriteS1 *)local_38;
    pS127 = (struct S127 *)&DAT_00669e98;
    puVar9 = local_38 + 8;
    piVar18 = (int *)&DAT_00669e90;
    pS110 = puVar9;
    gta2::FUN_0040ce30(&local_28,bVar1);
    this_03 = (Point2D *)gta2::WorldCoordinateToScreenCoord(puVar9,pS110,piVar18);
    pSVar10 = gta2::S202_sub_401B20(this_03,pSVar10,pS127);
    break;
  default:
    goto switchD_0048f4ff_caseD_5;
  }
  FUN_0041e210(&local_20,(GlassInfo *)pSVar10,pPVar8);
switchD_0048f4ff_caseD_5:
  FUN_00432860(&local_10,&local_44,(undefined4 *)(local_54 + 0xc));
  FUN_0040f680(&local_10,(int)&local_20);
  iVar4 = gta2::SpriteS1_getSpriteType(*(SpriteS1 **)&self->field_0x28);
  if (iVar4 != 4) {
    return 1;
  }
  gta2::SpriteS1_sub_4206C0(self->Sprite,gPathNode->a + (ushort)bVar1 + 0xa3);
  gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,2,'\x14');
  gta2::SpriteS1_sub_4337F0(self->Sprite);
  gta2::SpriteS1_sub_420600(self->Sprite,local_10,local_c,(int)self->Sprite->Point2D);
  gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
  return 0;
}


// 0x0048f650: Particle1::sub_48F650
// IDA: Particle1::sub_48F650
// Ghidra: Particle1::FUN_0048f650
byte gta2::Particle1_sub_48F650(struct Particle1 *self)
{
  undefined1 *puVar1;
  Point2D **this_00;
  int iVar2;
  bool bVar3;
  bool bVar4;
  short sVar5;
  undefined3 extraout_var;
  struct SpriteS1 *pSVar6;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int *piVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  struct Particle1 *pPVar10;
  struct SpriteS1 *pSVar11;
  undefined3 extraout_var_06;
  struct SpriteS1 *pSVar12;
  undefined3 extraout_var_07;
  undefined3 extraout_var_08;
  undefined3 extraout_var_09;
  byte bVar13;
  undefined4 extraout_ECX;
  Matrix3D *extraout_ECX_00;
  struct SpriteS3 *extraout_ECX_01;
  struct Car *extraout_ECX_02;
  struct SpriteS1 *extraout_ECX_03;
  struct SpriteS1 *extraout_ECX_04;
  Sprite *pSVar14;
  struct Car *pCVar15;
  struct SpriteS3 *pSVar16;
  Matrix3D *pMVar17;
  undefined4 uVar18;
  struct S127 *pSVar19;
  undefined1 local_64 [8];
  undefined1 local_5c [8];
  undefined1 local_54 [8];
  struct SpriteS1 *local_4c;
  struct Car *local_48;
  SpriteS1 *local_44 [2];
  undefined1 local_3c [8];
  undefined1 local_34 [8];
  undefined1 local_2c [8];
  undefined1 local_24 [16];
  undefined1 local_14 [12];
  struct SpriteS1 *local_8;
  struct SpriteS1 *local_4;
  
  local_54._4_4_ = _DAT_00669f7c;
  local_4c = _DAT_00669f7c;
  bVar4 = true;
  gta2::bitShiftLeft1(local_54,NULL);
  gta2::bitShiftLeft1(local_5c + 4,NULL);
  String_ParseLine(&local_8,(undefined4 *)(local_5c + 4),(undefined4 *)local_54)
  ;
  gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
  if (*(short *)&self->field_0x2c == 0) {
    return 1;
  }
  iVar8 = *(int *)&self->field_0x40;
  if (iVar8 == 0) {
    *(SpriteS1 **)&self->field_0x20 = _DAT_00669f7c;
  }
  else if (*(short *)(iVar8 + 6) == *(short *)&self->field_0x44) {
    iVar2 = *(int *)(iVar8 + 0x14);
    if (iVar2 == 0) {
      *(undefined4 *)&self->field_0x40 = 0;
      *(SpriteS1 **)&self->field_0x20 = _DAT_00669f7c;
    }
    else {
      if (*(int *)(iVar2 + 4) != 0) {
        bVar13 = FUN_004827d0(*(void **)(*(int *)(iVar2 + 4) + 8),local_44);
        iVar8 = *(int *)&self->field_0x40;
        *(undefined4 *)&self->field_0x20 =
             *(undefined4 *)CONCAT31(extraout_var,bVar13);
        *(undefined2 *)&self->CarSystemManager_ =
             *(undefined2 *)
              (*(int *)(*(int *)(*(int *)(*(int *)(iVar8 + 0x14) + 4) + 8) +
                       0x10) + 4);
      }
      if (*(short *)(iVar8 + 0x1a) == 1) {
        *(undefined4 *)&self->field_0x40 = 0;
      }
    }
  }
  else {
    *(undefined4 *)&self->field_0x40 = 0;
  }
  pSVar14 = self->Sprite;
  puVar1 = &self->field_0x20;
  *(SpriteS1 **)puVar1 = _DAT_00669f7c;
  local_64._0_4_ = _DAT_00669fcc;
  pSVar6 = gta2::S202_sub_401B20((Point2D *)&pSVar14->Point2D,(struct SpriteS1 *)local_44,
                      (struct S127 *)local_64);
  local_64._4_4_ = pSVar6->FirstElement;
  bVar3 = gta2::Player_sub_40CE70((struct Player *)(local_64 + 4),(struct Player *)&DAT_00669fa4);
  if (CONCAT31(extraout_var_00,bVar3) != 0) {
    return 1;
  }
  local_54[0] = pSVar14->field_0x18;
  local_54[1] = pSVar14->field_0x19;
  local_54[2] = pSVar14->field_0x1a;
  local_54[3] = pSVar14->field_0x1b;
  local_5c._4_4_ = pSVar14->Point2D1;
  bVar3 = gta2::Player_IsCurrentPlayer((struct Player *)puVar1,(struct Player *)&DAT_00669f7c);
  if (CONCAT31(extraout_var_01,bVar3) != 0) {
    gta2::bitShiftLeft1(&local_4c,NULL);
    local_54._4_4_ = local_4c;
    piVar7 = (int *)gta2::JustCopyByPtrAtoC(&DAT_00669e98,local_44);
    local_4c = (struct SpriteS1 *)*piVar7;
  }
  switch((*(ushort *)&self->field_0x2c & 0x3fc) >> 2) {
  case 2:
    local_5c._0_4_ = 2;
    sVar5 = gta2::Random_Random((struct Random *)&gRandom,(short)local_5c);
    if (sVar5 != 0) {
      return 1;
    }
    gta2::SpriteS1_sub_4206C0(self->Sprite,gPathNode->a + 0x66);
    gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,1,'\x19');
    gta2::SpriteS1_sub_433800((struct SpriteS1 *)self->Sprite);
    gta2::S202_sub_401B20((Point2D *)local_64,(struct SpriteS1 *)(local_44 + 1),
               (struct S127 *)&DAT_00669e90);
    gta2::bitShiftLeft1(local_64,NULL);
    local_8 = (struct SpriteS1 *)local_64._0_4_;
    puVar9 = (undefined4 *)
             gta2::WorldCoordinateToScreenCoord(puVar1,local_3c,(int *)&DAT_00669f3c);
    local_4 = (struct SpriteS1 *)*puVar9;
    bVar4 = false;
    break;
  case 3:
    gta2::SpriteS1_sub_4206C0(pSVar14,gPathNode->a + 0x65);
    gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,1,'\x19');
    gta2::SpriteS1_sub_433800((struct SpriteS1 *)self->Sprite);
    gta2::S202_sub_401B20((Point2D *)local_64,(struct SpriteS1 *)(local_3c + 4),
               (struct S127 *)&DAT_00669e98);
    gta2::bitShiftLeft1(local_64,NULL);
    local_8 = (struct SpriteS1 *)local_64._0_4_;
    puVar9 = (undefined4 *)
             gta2::WorldCoordinateToScreenCoord(puVar1,local_34,(int *)&DAT_0066a088);
    local_4 = (struct SpriteS1 *)*puVar9;
    break;
  case 4:
    gta2::SpriteS1_sub_4206C0(pSVar14,gPathNode->a + 100);
    gta2::S202_sub_401B20((Point2D *)local_64,(struct SpriteS1 *)(local_34 + 4),
               (struct S127 *)&DAT_0066a180);
    gta2::bitShiftLeft1(local_64,NULL);
    local_8 = (struct SpriteS1 *)local_64._0_4_;
    puVar9 = (undefined4 *)
             gta2::WorldCoordinateToScreenCoord(puVar1,local_2c,(int *)&DAT_0066a024);
    local_4 = (struct SpriteS1 *)*puVar9;
    break;
  case 5:
    gta2::SpriteS1_sub_4206C0(pSVar14,gPathNode->a + 99);
    gta2::S202_sub_401B20((Point2D *)local_64,(struct SpriteS1 *)(local_2c + 4),
               (struct S127 *)&DAT_0066a150);
    gta2::bitShiftLeft1(local_64,NULL);
    local_8 = (struct SpriteS1 *)local_64._0_4_;
    puVar9 = (undefined4 *)
             gta2::WorldCoordinateToScreenCoord(puVar1,local_24,(int *)&DAT_0066a024);
    local_4 = (struct SpriteS1 *)*puVar9;
    break;
  case 6:
    gta2::SpriteS1_sub_4206C0(pSVar14,gPathNode->a + 0x62);
    gta2::S202_sub_401B20((Point2D *)local_64,(struct SpriteS1 *)(local_24 + 4),
               (struct S127 *)&DAT_00669e98);
    gta2::bitShiftLeft1(local_64,NULL);
    local_8 = (struct SpriteS1 *)local_64._0_4_;
    gta2::bitShiftLeft1(local_64,NULL);
    local_4 = (struct SpriteS1 *)local_64._0_4_;
    if (*(int *)&self->field_0x40 != 0) {
      iVar8 = *(int *)(*(int *)(*(int *)&self->field_0x40 + 0x14) + 4);
LAB_0048fa3e:
      local_4 = (struct SpriteS1 *)local_64._0_4_;
      if (iVar8 != 0) {
        local_5c._4_4_ = *(undefined4 *)(iVar8 + 0x14);
        local_54._0_4_ = *(undefined4 *)(iVar8 + 0x18);
        local_64._4_4_ = *(undefined4 *)(iVar8 + 0x1c);
      }
    }
    goto LAB_0048fa57;
  case 7:
    gta2::SpriteS1_sub_4206C0(pSVar14,gPathNode->a + 0x61);
    gta2::S202_sub_401B20((Point2D *)local_64,(struct SpriteS1 *)(local_24 + 8),
               (struct S127 *)&DAT_0066a150);
    gta2::bitShiftLeft1(local_64,NULL);
    local_8 = (struct SpriteS1 *)local_64._0_4_;
    gta2::bitShiftLeft1(local_64,NULL);
    local_4 = (struct SpriteS1 *)local_64._0_4_;
    if (*(int *)&self->field_0x40 != 0) {
      iVar8 = *(int *)(*(int *)(*(int *)&self->field_0x40 + 0x14) + 4);
      goto LAB_0048fa3e;
    }
LAB_0048fa57:
    bVar4 = false;
    local_64._0_4_ = local_4;
    break;
  default:
    local_48 = (struct Car *)0x2;
    sVar5 = gta2::Random_Random((struct Random *)&gRandom,(short)&local_48);
    if (sVar5 != 0) {
      return 1;
    }
    gta2::SpriteS1_sub_4206C0(self->Sprite,gPathNode->a + 0x67);
    gta2::S202_sub_401B20((Point2D *)local_64,(struct SpriteS1 *)(local_24 + 0xc),
               (struct S127 *)&DAT_00669e90);
    gta2::bitShiftLeft1(local_64,NULL);
    local_8 = (struct SpriteS1 *)local_64._0_4_;
    puVar9 = (undefined4 *)
             gta2::sub_401B90((struct Player *)puVar1,local_14,(int *)&DAT_00669ff0);
    local_4 = (struct SpriteS1 *)*puVar9;
    bVar4 = false;
    local_44[0] = (struct SpriteS1 *)0x7;
    sVar5 = gta2::Random_Random((struct Random *)&gRandom,(short)local_44);
    if (sVar5 == 4) {
      pSVar14 = self->Sprite;
      this_00 = &pSVar14->Point2D1;
      bVar3 = gta2::Car_sub_403800((struct Car *)this_00,(int *)&DAT_00669f14);
      if (CONCAT31(extraout_var_02,bVar3) != 0) {
        pSVar6 = (struct SpriteS1 *)
                 gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a18c,
                            (GlassInfo *)(local_14 + 4),(struct S127 *)&DAT_00669f14);
        bVar3 = gta2::Point2D_FUN_004037e0((Point2D *)this_00,pSVar6);
        if (CONCAT31(extraout_var_03,bVar3) != 0) {
          puVar1 = &pSVar14->field_0x18;
          bVar3 = gta2::Car_sub_403800((struct Car *)puVar1,(int *)&DAT_00669f14);
          if (CONCAT31(extraout_var_04,bVar3) != 0) {
            pSVar6 = (struct SpriteS1 *)
                     gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a18c,
                                (GlassInfo *)(local_14 + 8),
                                (struct S127 *)&DAT_00669f14);
            bVar3 = gta2::Point2D_FUN_004037e0((Point2D *)puVar1,pSVar6);
            if (CONCAT31(extraout_var_05,bVar3) != 0) {
              local_64._0_4_ = &stack0xffffff88;
              uVar18 = extraout_ECX;
              gta2::bitShiftLeft1(&stack0xffffff88,NULL);
              local_64._0_4_ = &stack0xffffff84;
              pMVar17 = extraout_ECX_00;
              gta2::bitShiftLeft1(&stack0xffffff84,NULL);
              local_64._0_4_ = &stack0xffffff80;
              pSVar16 = extraout_ECX_01;
              gta2::bitShiftLeft1(&stack0xffffff80,NULL);
              local_64._0_4_ = &stack0xffffff7c;
              pCVar15 = extraout_ECX_02;
              gta2::bitShiftLeft1(&stack0xffffff7c,NULL);
              local_64._0_4_ = &stack0xffffff78;
              pSVar11 = extraout_ECX_03;
              gta2::bitShiftLeft1(&stack0xffffff78,NULL);
              local_64._0_4_ = &stack0xffffff74;
              pSVar6 = extraout_ECX_04;
              gta2::bitShiftLeft1(&stack0xffffff74,NULL);
              pPVar10 = gta2::Particles_sub_48C930(gParticles,pSVar6,pSVar11,pCVar15,pSVar16,
                                   pMVar17,uVar18);
              if (pPVar10 != NULL) {
                *(undefined4 *)&pPVar10->field_0x34 = 1;
                *(undefined4 *)&pPVar10->field_0x38 = 6;
                *(undefined2 *)&pPVar10->field_0x2c = 100;
                *(undefined2 *)&pPVar10->field_0x2e = 100;
                gta2::SpriteS1_sub_4206F0(pPVar10->Sprite,8);
                *(undefined4 *)&pPVar10->field_0x38 = 6;
                gta2::SpriteS1_sub_4206C0(pPVar10->Sprite,gPathNode->a);
                pSVar14 = self->Sprite;
                gta2::SpriteS1_sub_420600(pPVar10->Sprite,(int)pSVar14->Point2D1,
                                    *(int *)&pSVar14->field_0x18,
                                    (int)pSVar14->Point2D);
                gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)pPVar10->Sprite);
              }
            }
          }
        }
      }
    }
  }
  FUN_0040f6b0(&local_8,(GlassInfo *)&self->CarSystemManager_);
  self->field12_0x18 = local_4;
  self->field11_0x14 = local_8;
  gta2::bitShiftLeft1(local_44,NULL);
  local_64._0_4_ = local_44[0];
  gta2::bitShiftLeft1(local_44,NULL);
  local_5c._0_4_ = local_44[0];
  if (bVar4) {
    local_44[0] = (struct SpriteS1 *)0x3;
    sVar5 = gta2::Random_Random((struct Random *)&gRandom,(short)local_44);
    gta2::S202_sub_41F980((struct SpriteS1 *)local_44,sVar5 + -1);
    local_64._0_4_ = local_44[0];
    local_44[0] = (struct SpriteS1 *)0x64;
    pSVar6 = gta2::S122_sub_401BF0((struct Model *)local_64,(struct SpriteS1 *)(local_14 + 8),
                                (int *)local_44);
    local_64._0_4_ = pSVar6->FirstElement;
    local_44[0] = (struct SpriteS1 *)0x3;
    sVar5 = gta2::Random_Random((struct Random *)&gRandom,(short)local_44);
    gta2::S202_sub_41F980((struct SpriteS1 *)local_44,sVar5 + -1);
    local_5c._0_4_ = local_44[0];
    local_44[0] = (struct SpriteS1 *)0x64;
    pSVar6 = gta2::S122_sub_401BF0((struct Model *)local_5c,(struct SpriteS1 *)(local_14 + 8),
                                (int *)local_44);
    local_5c._0_4_ = pSVar6->FirstElement;
  }
  pSVar19 = (struct S127 *)(local_54 + 4);
  pSVar6 = (struct SpriteS1 *)(local_14 + 8);
  pSVar11 = gta2::S202_sub_401B20((Point2D *)local_64,(struct SpriteS1 *)(local_14 + 4),
                       (struct S127 *)&self->field11_0x14);
  pSVar11 = gta2::S202_sub_401B20((Point2D *)pSVar11,pSVar6,pSVar19);
  pSVar19 = (struct S127 *)&local_4c;
  pSVar6 = (struct SpriteS1 *)(local_14 + 8);
  self->field8_0x8 = pSVar11->FirstElement;
  pSVar11 = gta2::S202_sub_401B20((Point2D *)local_5c,(struct SpriteS1 *)(local_14 + 4),
                       (struct S127 *)&self->field12_0x18);
  pSVar6 = gta2::S202_sub_401B20((Point2D *)pSVar11,pSVar6,pSVar19);
  self->field9_0xc = pSVar6->FirstElement;
  pSVar6 = gta2::S202_sub_401B20((Point2D *)(local_5c + 4),(struct SpriteS1 *)(local_14 + 8),
                      (struct S127 *)&self->field8_0x8);
  pSVar6 = pSVar6->FirstElement;
  pSVar11 = gta2::S202_sub_401B20((Point2D *)local_54,(struct SpriteS1 *)(local_14 + 8),
                       (struct S127 *)&self->field9_0xc);
  pSVar11 = pSVar11->FirstElement;
  _DAT_00669f80 = pSVar6;
  _DAT_0066a1ec = pSVar11;
  bVar4 = gta2::Car_sub_403800((struct Car *)&DAT_00669f80,(int *)&DAT_00669f14);
  if (CONCAT31(extraout_var_06,bVar4) != 0) {
    pSVar12 = (struct SpriteS1 *)
              gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a18c,(GlassInfo *)(local_14 + 8)
                         ,(struct S127 *)&DAT_00669f14);
    bVar4 = gta2::Point2D_FUN_004037e0((Point2D *)&DAT_00669f80,pSVar12);
    if ((CONCAT31(extraout_var_07,bVar4) != 0) &&
       (bVar4 = gta2::Car_sub_403800((struct Car *)&DAT_0066a1ec,(int *)&DAT_00669f14),
       CONCAT31(extraout_var_08,bVar4) != 0)) {
      pSVar12 = (struct SpriteS1 *)
                gta2::Player_sub_401B40((SpawnPoint *)&DAT_0066a18c,
                           (GlassInfo *)(local_14 + 8),(struct S127 *)&DAT_00669f14);
      bVar4 = gta2::Point2D_FUN_004037e0((Point2D *)&DAT_0066a1ec,pSVar12);
      if (CONCAT31(extraout_var_09,bVar4) != 0) {
        pSVar14 = self->Sprite;
        goto LAB_0048fe2d;
      }
    }
  }
  pSVar14 = self->Sprite;
  pSVar11 = *(SpriteS1 **)&pSVar14->field_0x18;
  pSVar6 = (struct SpriteS1 *)pSVar14->Point2D1;
LAB_0048fe2d:
  gta2::SpriteS1_sub_420600(pSVar14,(int)pSVar6,(int)pSVar11,local_64._4_4_);
  gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,2,'\x14');
  gta2::SpriteS1_sub_4337F0(self->Sprite);
  gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
  bVar13 = self->field_0x46 + 1;
  self->field_0x46 = bVar13;
  if (8 < bVar13) {
    self->field_0x46 = 0;
  }
  return 0;
}


// 0x0048fe90: Particle1::sub_48FE90
// IDA: Particle1::sub_48FE90
// Ghidra: Particle1::FUN_0048fe90
byte gta2::Particle1_sub_48FE90(struct Particle1 *self)
{
  struct SpriteS1 *this_00;
  struct SpriteS1 *this_01;
  struct Car *pCVar1;
  bool bVar2;
  short sVar3;
  int iVar4;
  void *pvVar5;
  undefined2 *puVar6;
  GlassInfo *pGVar7;
  undefined3 extraout_var;
  Turrel *Z;
  struct CarSystemManager *this_02;
  struct CarSystemManager *this_03;
  struct CarSystemManager *this_04;
  struct Ped *pPVar8;
  struct Ped *pPVar9;
  GameState local_14;
  undefined1 local_10 [4];
  Turrel *local_c;
  struct Passenger *local_8;
  undefined1 local_4 [4];
  
  gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
  if (*(short *)&self->field_0x2c == 0) {
    return 1;
  }
  _DAT_00669f80 = self->Sprite->Point2D1;
  _DAT_0066a1ec = *(int *)&self->Sprite->field_0x18;
  this_00 = (struct SpriteS1 *)self->Sprite;
  this_01 = *(SpriteS1 **)&self->field_0x28;
  local_c = (Turrel *)this_00->Matrix3DArray[0].PositionZ;
  iVar4 = gta2::SpriteS1_getSpriteType(this_01);
  if (iVar4 == 3) {
    pCVar1 = this_01->Matrix3DArray[0].Car;
    if (((struct Ped *)pCVar1->PhysicsBitmask != NULL) &&
       (pvVar5 = gta2::Ped_Get_433B40((struct Ped *)pCVar1->PhysicsBitmask),
       (char)pvVar5 != '\0')) {
      if (*(int *)&self->field_0x38 == 9) {
        if (pCVar1->ID_Object != 2) {
          return 1;
        }
        gta2::SpriteS1_sub_4206C0((Sprite *)this_00,gPathNode->a + 3);
        if (*(char *)&pCVar1->field14_0x68 != '\x05') {
          gta2::SpriteS1_SpriteS1EmitParticles(*(undefined4 *)&self->field_0x28,0);
        }
      }
      else {
        if (*(ushort *)&self->field_0x2c < 0x3c) {
          if (*(ushort *)&self->field_0x2c < 0x29) {
            pPVar9 = (struct Ped *)&local_8;
            pPVar8 = (struct Ped *)&local_14;
            pGVar7 = (GlassInfo *)
                     gta2::WorldCoordinateToScreenCoord
                               (&DAT_00669fcc,local_4,(int *)&DAT_00669f14);
            gta2::sub_41FC20(this_03,this_00,pGVar7,pPVar8,pPVar9)
            ;
            gta2::SpriteS1_sub_4206C0((Sprite *)this_00,gPathNode->a + 0x11);
            gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,1,'\x05');
            gta2::Player_sub_40E530((Point2D *)&local_c,(int *)&DAT_00669ec8);
          }
          else {
            local_8 = (struct Passenger *)0x8;
            sVar3 = gta2::Random_Random((struct Random *)&gRandom,(short)&local_8);
            gta2::bitShiftLeft1(local_10,(void *)((sVar3 + -4) / 2));
            puVar6 = (undefined2 *)FUN_0040f540(&local_14,(int)local_10);
            local_14._0_2_ = *puVar6;
            pPVar9 = (struct Ped *)&local_8;
            pPVar8 = (struct Ped *)&local_14;
            pGVar7 = (GlassInfo *)
                     gta2::WorldCoordinateToScreenCoord
                               (&DAT_00669fcc,local_4,(int *)&DAT_00669f10);
            pvVar5 = gta2::sub_40E5A0(*(CarSystemManager **)&self->field_0x28,
                                (struct Ped *)local_10,(short *)&local_14,pGVar7,
                                (short *)pPVar8);
            gta2::sub_41FC20(this_02,pvVar5,pGVar7,pPVar8,pPVar9);
            gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,1,'\n');
            gta2::SpriteS1_sub_4206C0(self->Sprite,gPathNode->a + 0x11);
            gta2::Player_sub_40E530((Point2D *)&local_c,(int *)&DAT_00669ec8);
          }
        }
        else {
          pPVar9 = (struct Ped *)&local_8;
          pPVar8 = (struct Ped *)&local_14;
          pGVar7 = (GlassInfo *)
                   gta2::WorldCoordinateToScreenCoord
                             (&DAT_00669fcc,local_4,(int *)&DAT_00669f10);
          gta2::sub_41FC20(this_04,this_01,pGVar7,pPVar8,pPVar9);
          gta2::SpriteS1_sub_4337D0(this_00,1,'\x14');
          gta2::SpriteS1_sub_4206C0(self->Sprite,gPathNode->a + 0x11);
        }
        gta2::Player_sub_40E530((Point2D *)&DAT_00669f80,(int *)&local_14);
        gta2::Player_sub_40E530((Point2D *)&DAT_0066a1ec,(int *)&local_8);
      }
      bVar2 = gta2::Car_sub_403800((struct Car *)&local_c,(int *)&DAT_00669fa4);
      Z = _DAT_00669fa4;
      if (CONCAT31(extraout_var,bVar2) == 0) {
        Z = local_c;
      }
      gta2::SpriteS1_sub_420600(self->Sprite,(int)_DAT_00669f80,_DAT_0066a1ec,(int)Z);
      gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
      return 0;
    }
  }
  return 1;
}


// 0x00490130: Particle1::sub_490130
// IDA: Particle1::sub_490130
// Ghidra: Particle1::FUN_00490130
uint gta2::Particle1_sub_490130(struct Particle1 *self)
{
  undefined4 X;
  char cVar1;
  undefined1 uVar2;
  byte bVar3;
  short sVar4;
  int iVar5;
  struct Player *pSprite;
  undefined3 uVar13;
  undefined2 extraout_var_00;
  int *piVar7;
  void *pvVar8;
  ushort *puVar9;
  Sprite *pSVar10;
  struct SpriteS1 *pSpriteS1;
  struct SpriteS1 *pSVar11;
  uint uVar12;
  undefined3 extraout_var;
  struct Ped *extraout_ECX;
  struct Ped *this_00;
  SpawnPoint *this_01;
  ushort uVar14;
  struct Player *pPVar15;
  short *unaff_ESI;
  void *unaff_EDI;
  GlassInfo *pGVar16;
  struct Ped *pPVar17;
  undefined4 uVar18;
  struct S127 *pS127;
  undefined4 *puVar19;
  struct Ped *pPVar20;
  undefined4 local_50;
  struct S127 *local_4c;
  ushort local_48;
  undefined2 uStack_46;
  undefined1 local_44 [20];
  Point2D local_30;
  struct Car *local_18;
  int local_14;
  undefined4 local_10 [3];
  struct S127 *pSVar6;
  struct EventHandler *pEventHandler;
  
  pPVar15 = NULL;
  this_01 = NULL;
  local_44._4_4_ = NULL;
  local_44._8_4_ = NULL;
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&local_30);
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&local_48);
  pSprite = (struct Player *)self->Sprite;
  gta2::S56_sub_447BD0(gCheckpoint3,(Sprite *)pSprite);
  if (*(short *)&self->field_0x2c == 0) goto LAB_0049074e;
  _DAT_00669f80 = self->Sprite->Point2D1;
  _DAT_0066a1ec = *(uint *)&self->Sprite->field_0x18;
  pSpriteS1 = *(SpriteS1 **)&self->field_0x28;
  local_4c = self->Sprite->Point2D;
  local_44._12_4_ = _DAT_0066a1ec;
  local_44._16_4_ = _DAT_00669f80;
  iVar5 = gta2::SpriteS1_getSpriteType(pSpriteS1);
  if (iVar5 == 2) {
    this_01 = (SpawnPoint *)pSpriteS1->Matrix3DArray[0].Car;
    pSprite = NULL;
    if ((this_01 == NULL) ||
       (pSprite = *(Player **)&this_01->field_0x54, pSprite == NULL))
    goto LAB_0049074e;
    if ((*(uint *)&pSprite->field_0x21c & 0x800) == 0) {
      *(uint *)&self->field_0x4 = *(uint *)&self->field_0x4 & 0xfffffffe;
    }
    pSprite = this_01->Player_;
    local_44._8_4_ = this_01;
    if (pSprite == NULL) goto LAB_0049074e;
  }
  else {
    pSprite = (struct Player *)(iVar5 + -3);
    if ((((pSprite != NULL) ||
         (pSprite = (struct Player *)pSpriteS1->Matrix3DArray[0].Car, pSprite == NULL))
        || (pPVar20 = *(Ped **)&pSprite->Tango1, pPVar20 == NULL)) ||
       (local_44._4_4_ = pSprite, pSprite = (struct Player *)gta2::Ped_Get_433B40(pPVar20),
       (char)pSprite == '\0')) goto LAB_0049074e;
    pSprite = *(Player **)&pPVar20->CurrentAction;
    if (((uint)pSprite & 0x800) == 0) {
      pSprite = (struct Player *)(*(uint *)&self->field_0x4 & 0xfffffffe);
      *(Player **)&self->field_0x4 = pSprite;
    }
    local_48 = *(short *)&pSpriteS1->FirstElement;
    pPVar15 = (struct Player *)local_44._4_4_;
  }
  uVar13 = (undefined3)((uint)pSprite >> 8);
  if (self->field_0x48 == '\0') {
    bVar3 = self->field_0x46 + 1;
    pSprite = (struct Player *)CONCAT31(uVar13,bVar3);
    self->field_0x46 = bVar3;
    if (0xf < bVar3) {
LAB_0049074e:
      return CONCAT31((int3)((uint)pSprite >> 8),1);
    }
    if (3 < bVar3) {
      self->field_0x48 = 1;
    }
  }
  else {
    cVar1 = self->field_0x48 + -1;
    pSprite = (struct Player *)CONCAT31(uVar13,cVar1);
    self->field_0x48 = cVar1;
  }
  local_44._2_2_ = (undefined2)((uint)pSprite >> 0x10);
  local_44._0_2_ = ZEXT12((byte)self->field_0x46);
  pGVar16 = (GlassInfo *)(local_30.Array_24 + 4);
  pS127 = (struct S127 *)&DAT_0066a1a0;
  sVar4 = gta2::Random_Random((struct Random *)&gRandom,(short)local_44);
  pSVar6 = (struct S127 *)CONCAT22(extraout_var_00,sVar4);
  gta2::Decoder_SetValue(local_30.Array_24 + 8,sVar4);
  pSpriteS1 = (struct SpriteS1 *)(local_30.Array_24 + 0x10);
  pSVar11 = pSpriteS1;
  gta2::FUN_0040ce30(&local_18,self->field_0x46);
  pSpriteS1 = gta2::S202_sub_401B20((Point2D *)pSpriteS1,pSVar11,pSVar6);
  piVar7 = (int *)gta2::Player_sub_401B40((SpawnPoint *)pSpriteS1,pGVar16,pS127);
  pvVar8 = gta2::WorldCoordinateToScreenCoord(&DAT_0066a148,local_10,piVar7);
  piVar7 = (int *)FUN_0040f540(&local_50,(int)pvVar8);
  local_30.Array_24._0_2_ = (undefined2)*piVar7;
  if (pPVar15 == NULL) {
    gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)local_44);
    piVar7 = gta2::Car_sub_4BE980((struct Car *)this_01,0x72);
    if (piVar7 == NULL) {
      piVar7 = gta2::Car_sub_4BE980((struct Car *)this_01,0xf8);
      uVar14 = *(ushort *)*piVar7;
      local_44._0_2_ = uVar14;
      gta2::bitShiftLeft1(&local_50,NULL);
      FUN_00432860(local_10,&local_50,(undefined4 *)&DAT_00669f34);
      FUN_0040f6b0(local_10,(GlassInfo *)local_44);
      gta2::bitShiftLeft1(local_44,NULL);
      puVar19 = (undefined4 *)&DAT_0066a1c0;
    }
    else {
      puVar9 = (ushort *)
               gta2::sub_40E5A0((struct CarSystemManager *)*piVar7,(struct Ped *)&local_50,
                          (short *)&DAT_0066a090,unaff_EDI,unaff_ESI);
      uVar14 = *puVar9;
      local_44._0_2_ = uVar14;
      gta2::bitShiftLeft1(&local_50,NULL);
      FUN_00432860(local_10,&local_50,(undefined4 *)&DAT_00669ff8);
      FUN_0040f6b0(local_10,(GlassInfo *)local_44);
      gta2::bitShiftLeft1(local_44,NULL);
      puVar19 = (undefined4 *)&DAT_0066a06c;
    }
    FUN_00432860(&local_18,(undefined4 *)local_44,puVar19);
    pSpriteS1 = *(SpriteS1 **)&this_01->field_0x50;
    FUN_0040f6b0(&local_18,(GlassInfo *)pSpriteS1);
    pSpriteS1 = (struct SpriteS1 *)
                gta2::SpriteS1_sub_4207B0(pSpriteS1,local_30.Array_24 + 0x10);
    pvVar8 = FUN_0040f5c0(&local_18,local_30.Array_24 + 8,pSpriteS1);
    FUN_0040f680(local_10,(int)pvVar8);
    piVar7 = (int *)gta2::Player_sub_4A0D10(this_01->Player_,local_30.Array_24 + 0x10,
                               (GlassInfo *)local_10);
    local_48 = uVar14;
  }
  else {
    gta2::Ped_sub_435C20(*(Ped **)&pPVar15->Tango1,local_10);
  }
  local_18 = (struct Car *)*piVar7;
  local_14 = piVar7[1];
  bVar3 = 0xc;
  if (((self->field_0x4 & 1) == 0) || (0xc < (byte)self->field_0x46)) {
    pSVar10 = self->Sprite;
    this_00 = (struct Ped *)local_44;
    pPVar17 = (struct Ped *)&local_30;
    pGVar16 = (GlassInfo *)&DAT_00669e94;
    pPVar20 = this_00;
  }
  else {
    pPVar20 = (struct Ped *)local_44;
    pPVar17 = (struct Ped *)&local_30;
    pGVar16 = (GlassInfo *)&DAT_00669e94;
    pSVar10 = (Sprite *)
              gta2::sub_40E5A0((struct CarSystemManager *)&local_48,(struct Ped *)&local_50,
                         (short *)&local_30,&DAT_00669e94,(short *)pPVar17);
    this_00 = extraout_ECX;
  }
  gta2::sub_41FC20((struct CarSystemManager *)this_00,pSVar10,pGVar16,pPVar17,pPVar20);
  pSpriteS1 = gta2::S202_sub_401B20(&local_30,(struct SpriteS1 *)local_10,(struct S127 *)&local_18);
  gta2::Player_sub_40E530((Point2D *)&DAT_00669f80,(int *)pSpriteS1);
  pSpriteS1 = gta2::S202_sub_401B20((Point2D *)local_44,(struct SpriteS1 *)local_10,
                         (struct S127 *)&local_14);
  gta2::Player_sub_40E530((Point2D *)&DAT_0066a1ec,(int *)pSpriteS1);
  if (*(int *)&self->field_0x38 == 0x1f) {
    gta2::SpriteS1_sub_4206C0(self->Sprite,
                     gPathNode->a + (ushort)(byte)self->field_0x46 + 0x49);
    bVar3 = 0xe;
  }
  else {
    gta2::SpriteS1_sub_4206C0(self->Sprite,
                     gPathNode->a + (ushort)(byte)self->field_0x46 + 0x6f);
  }
  gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,2,'\x14');
  pSVar6 = local_4c;
  gta2::SpriteS1_sub_420600(self->Sprite,(int)_DAT_00669f80,_DAT_0066a1ec,
                      (int)local_4c);
  if ((((byte)self->field_0x46 < 2) || (bVar3 <= (byte)self->field_0x46)) ||
     ((pSpriteS1 = gta2::SpriteS1_sub_4BDFE0((struct SpriteS1 *)self->Sprite,2),
      pSpriteS1 == NULL || (pSpriteS1 == *(SpriteS1 **)&self->field_0x28))))
  goto LAB_004906f7;
  if (*(int *)&self->field_0x38 != 0x1f) {
    self->field_0x46 = bVar3;
    pSVar11 = gta2::S202_sub_401B20((Point2D *)&local_4c,(struct SpriteS1 *)local_10,
                         (struct S127 *)&DAT_00669e98);
    X = local_44._16_4_;
    uVar18 = local_44._12_4_;
    gta2::SpriteS1_sub_420600(self->Sprite,local_44._16_4_,local_44._12_4_,
                        (int)pSVar11->FirstElement);
    uVar12 = gta2::General_GetCycle(gGeneral);
    if ((uVar12 & 1) == 0) {
      gta2::Particles_sub_48D1F0(gParticles,X,uVar18,local_4c,_local_48,0);
    }
    gta2::SpriteS1_sub_420600(gParticles->S63_->Sprite,X,uVar18,(int)local_4c);
    if ((struct Player *)local_44._4_4_ == NULL) {
      if ((SpawnPoint *)local_44._8_4_ != NULL) {
        uVar2 = gta2::sub_420B50(*(Ped **)(local_44._8_4_ + 0x54));
        pEventHandler = gParticles->S63_;
        goto LAB_00490666;
      }
    }
    else {
      uVar2 = gta2::sub_420B50(*(Ped **)(local_44._4_4_ + 0x7c));
      pEventHandler = gParticles->S63_;
LAB_00490666:
      gta2::S63_sub_482790(pEventHandler,uVar2);
    }
    bVar3 = gta2::SpriteS1_is_object(pSpriteS1);
    if (bVar3 == 0) {
      gta2::S63_sub_486390(gParticles->S63_,pSpriteS1);
    }
    iVar5 = gta2::SpriteS1_getSpriteType(pSpriteS1);
    if (iVar5 == 3) {
      pSVar11 = gta2::S202_sub_401B20((Point2D *)&DAT_00669e94,(struct SpriteS1 *)local_10,
                           (struct S127 *)&DAT_00669e90);
      FUN_00493390(_local_48,pSVar11->FirstElement,_DAT_00669f7c,0);
      iVar5 = (pSpriteS1->Matrix3DArray[0].Car)->PhysicsBitmask;
      if (iVar5 != 0) {
        if (*(int *)&self->field_0x38 == 0x1f) {
          iVar5 = *(int *)(iVar5 + 0x200);
          uVar18 = 0xc2;
        }
        else {
          iVar5 = *(int *)(iVar5 + 0x200);
          uVar18 = 0xc6;
        }
        gta2::MissionManager_sub_476530(gMissionManager,iVar5,uVar18,'\x01');
      }
    }
    goto LAB_004906f7;
  }
  pSVar11 = gta2::S202_sub_401B20((Point2D *)&local_4c,(struct SpriteS1 *)local_10,
                       (struct S127 *)&DAT_00669e98);
  uVar18 = local_44._16_4_;
  gta2::SpriteS1_sub_420600(self->Sprite,local_44._16_4_,local_44._12_4_,
                      (int)pSVar11->FirstElement);
  if ((byte)self->field_0x46 < 10) {
    self->field_0x46 = 10;
  }
  gta2::SpriteS1_sub_420600(gParticles->EventHandler->Sprite,uVar18,local_44._12_4_,
                      (int)pSVar6);
  if ((struct Player *)local_44._4_4_ == NULL) {
    if ((SpawnPoint *)local_44._8_4_ != NULL) {
      uVar2 = gta2::sub_420B50(*(Ped **)(local_44._8_4_ + 0x54));
      pEventHandler = gParticles->EventHandler;
      goto LAB_004905ae;
    }
  }
  else {
    uVar2 = gta2::sub_420B50(*(Ped **)(local_44._4_4_ + 0x7c));
    pEventHandler = gParticles->EventHandler;
LAB_004905ae:
    gta2::S63_sub_482790(pEventHandler,uVar2);
  }
  bVar3 = gta2::SpriteS1_is_object(pSpriteS1);
  if (bVar3 == 0) {
    gta2::S63_sub_486390(gParticles->EventHandler,pSpriteS1);
  }
LAB_004906f7:
  cVar1 = gta2::SpriteS1_sub_4BD670((struct SpriteS1 *)self->Sprite);
  uVar12 = CONCAT31(extraout_var,cVar1);
  if (cVar1 != '\0') {
    pSpriteS1 = gta2::S202_sub_401B20((Point2D *)&local_4c,(struct SpriteS1 *)local_10,
                           (struct S127 *)&DAT_00669e98);
    uVar12 = local_44._12_4_;
    gta2::SpriteS1_sub_420600(self->Sprite,local_44._16_4_,local_44._12_4_,
                        (int)pSpriteS1->FirstElement);
    if ((byte)self->field_0x46 < 10) {
      self->field_0x46 = 10;
    }
  }
  gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
  return uVar12 & 0xffffff00;
}


// 0x00490760: Particle1::sub_490760
// IDA: Particle1::sub_490760
// Ghidra: Particle1::FUN_00490760
byte gta2::Particle1_sub_490760(struct Particle1 *self)
{
  bool bVar1;
  char cVar2;
  byte bVar3;
  struct SpriteS1 *pSVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  struct SpriteS1 *pSVar5;
  undefined3 extraout_var_02;
  undefined4 uVar6;
  struct SpriteS1 *pSVar7;
  Sprite *pSprite;
  
  *(short *)&self->field_0x2c = *(short *)&self->field_0x2c + -1;
  switch(*(undefined4 *)&self->field_0x38) {
  case 1:
    bVar3 = gta2::Particle1_sub_48C270(self);
    return bVar3;
  default:
    return 0;
  case 3:
  case 0xc:
    bVar3 = gta2::Particle1_sub_48AE70(self);
    return bVar3;
  case 4:
    bVar3 = gta2::Particle1_sub_48B540(self);
    return bVar3;
  case 5:
    bVar3 = gta2::Particle1_sub_48F650(self);
    return bVar3;
  case 6:
  case 0xf:
  case 0x10:
  case 0x11:
    bVar3 = gta2::Particle1_sub_48A970(self);
    return bVar3;
  case 7:
    bVar3 = gta2::Particle1_sub_48C590(self);
    return bVar3;
  case 8:
    return 1;
  case 9:
  case 10:
    bVar3 = gta2::Particle1_sub_48FE90(self);
    return bVar3;
  case 0xd:
  case 0xe:
  case 0x24:
    bVar3 = gta2::Particle1_sub_48B9F0(self);
    return bVar3;
  case 0x12:
  case 0x21:
    cVar2 = self->field_0x48;
    if (cVar2 != '\0') goto LAB_00490a37;
    bVar3 = self->field_0x46 + 1;
    self->field_0x46 = bVar3;
    if ((bVar3 < 6) || (10 < bVar3)) {
      self->field_0x48 = 1;
    }
    gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
    if (0xf < (byte)self->field_0x46) {
      return 1;
    }
    gta2::SpriteS1_sub_4206C0(self->Sprite,
                     gPathNode->a + (ushort)(byte)self->field_0x46 + 0x14);
    pSprite = self->Sprite;
    pSVar7 = (struct SpriteS1 *)&DAT_00669fa4;
    pSVar4 = gta2::S202_sub_401B20((Point2D *)&pSprite->Point2D,
                        (struct SpriteS1 *)&stack0xffffffd4,(struct S127 *)&DAT_0066a184);
    bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)pSVar4,pSVar7);
    if (CONCAT31(extraout_var,bVar1) != 0) {
      pSVar4 = gta2::S202_sub_401B20((Point2D *)&pSprite->Point2D,
                          (struct SpriteS1 *)&stack0xffffffd8,(struct S127 *)&DAT_00669e94);
      gta2::SpriteS1_sub_420600(pSprite,(int)pSprite->Point2D1,
                          *(int *)&pSprite->field_0x18,(int)pSVar4->FirstElement
                         );
    }
    gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
    if (self->field_0x46 != '\x02') goto LAB_00490b62;
    cVar2 = '\x14';
    break;
  case 0x13:
  case 0x20:
    cVar2 = self->field_0x48;
    if (cVar2 == '\0') {
      bVar3 = self->field_0x46 + 1;
      self->field_0x46 = bVar3;
      if ((bVar3 < 6) || (10 < bVar3)) {
        self->field_0x48 = 1;
      }
      gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
      if ((byte)self->field_0x46 < 0x10) {
        gta2::SpriteS1_sub_4206C0(self->Sprite,
                         gPathNode->a + (ushort)(byte)self->field_0x46 + 0x14);
        pSprite = self->Sprite;
        pSVar7 = (struct SpriteS1 *)&DAT_00669fa4;
        pSVar4 = gta2::S202_sub_401B20((Point2D *)&pSprite->Point2D,
                            (struct SpriteS1 *)&stack0xffffffdc,(struct S127 *)&DAT_0066a184);
        bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)pSVar4,pSVar7);
        if (CONCAT31(extraout_var_00,bVar1) != 0) {
          pSVar4 = gta2::S202_sub_401B20((Point2D *)&pSprite->Point2D,
                              (struct SpriteS1 *)&stack0xffffffe0,(struct S127 *)&DAT_00669e94
                             );
          gta2::SpriteS1_sub_420600(pSprite,(int)pSprite->Point2D1,
                              *(int *)&pSprite->field_0x18,
                              (int)pSVar4->FirstElement);
        }
        gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
        if (self->field_0x46 == '\x02') {
          gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,2,'\x14');
        }
        gta2::SpriteS1_sub_4337F0(self->Sprite);
        pSVar4 = gta2::S202_sub_401B20((Point2D *)&DAT_00669f14,
                            (struct SpriteS1 *)&stack0xffffffe4,(struct S127 *)&DAT_0066a0ec);
        gta2::SpriteS1_sub_4BDEF0(self->Sprite,pSVar4->FirstElement,0);
        return 0;
      }
      return 1;
    }
    goto LAB_00490a37;
  case 0x14:
    cVar2 = self->field_0x48;
    if (cVar2 == '\0') {
      bVar3 = self->field_0x46 + 1;
      self->field_0x46 = bVar3;
      if ((bVar3 < 6) || (10 < bVar3)) {
        self->field_0x48 = 1;
      }
      gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
      if (0xf < (byte)self->field_0x46) {
        return 1;
      }
      gta2::SpriteS1_sub_4206C0(self->Sprite,
                       gPathNode->a + (ushort)(byte)self->field_0x46 + 0x38);
      pSprite = self->Sprite;
      pSVar7 = (struct SpriteS1 *)&DAT_00669fa4;
      pSVar4 = gta2::S202_sub_401B20((Point2D *)&pSprite->Point2D,
                          (struct SpriteS1 *)&stack0xffffffe8,(struct S127 *)&DAT_0066a184);
      bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)pSVar4,pSVar7);
      if (CONCAT31(extraout_var_01,bVar1) != 0) {
        pSVar4 = gta2::S202_sub_401B20((Point2D *)&pSprite->Point2D,
                            (struct SpriteS1 *)&stack0xffffffec,(struct S127 *)&DAT_00669e94);
        gta2::SpriteS1_sub_420600(pSprite,(int)pSprite->Point2D1,
                            *(int *)&pSprite->field_0x18,
                            (int)pSVar4->FirstElement);
      }
      gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
      if (self->field_0x46 == '\x02') {
        gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,2,'\x14');
      }
      gta2::SpriteS1_sub_4337F0(self->Sprite);
      gta2::SpriteS1_sub_4BDEF0(self->Sprite,_DAT_00669ff0,0);
      return 0;
    }
LAB_00490a37:
    self->field_0x48 = cVar2 + -1;
    return 0;
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
    cVar2 = self->field_0x48;
    if (cVar2 != '\0') goto LAB_00490a37;
    gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
    bVar3 = self->field_0x46 + 1;
    self->field_0x48 = 1;
    self->field_0x46 = bVar3;
    if (0xc < bVar3) {
      return 1;
    }
    gta2::SpriteS1_sub_4206C0(self->Sprite,gPathNode->a + (ushort)bVar3 + 0x93);
    gta2::sub_41FC20((struct CarSystemManager *)&self->CarSystemManager_,
               &self->CarSystemManager_,(GlassInfo *)&self->field_0x20,
               (struct Ped *)&DAT_00669f80,(struct Ped *)&DAT_0066a1ec);
    pSVar4 = gta2::S202_sub_401B20((Point2D *)&self->Sprite->Point2D1,
                        (struct SpriteS1 *)&stack0xfffffff0,(struct S127 *)&DAT_00669f80);
    pSVar4 = pSVar4->FirstElement;
    _DAT_00669f80 = pSVar4;
    pSVar7 = gta2::S202_sub_401B20((Point2D *)&self->Sprite->field_0x18,
                        (struct SpriteS1 *)&stack0xfffffff4,(struct S127 *)&DAT_0066a1ec);
    pSVar7 = pSVar7->FirstElement;
    pSprite = self->Sprite;
    _DAT_0066a1ec = pSVar7;
    if ((byte)self->field_0x46 < 9) {
      pSVar5 = gta2::S202_sub_401B20((Point2D *)&pSprite->Point2D,
                          (struct SpriteS1 *)&stack0xfffffff8,(struct S127 *)&DAT_00669e94);
      pSVar5 = pSVar5->FirstElement;
    }
    else {
      pSVar5 = gta2::S202_sub_401B20((Point2D *)&pSprite->Point2D,
                          (struct SpriteS1 *)&stack0xfffffffc,(struct S127 *)&DAT_00669e90);
      pSVar5 = pSVar5->FirstElement;
    }
    gta2::SpriteS1_sub_420600(pSprite,(int)pSVar4,(int)pSVar7,(int)pSVar5);
    pSprite = self->Sprite;
    bVar1 = gta2::Car_sub_403800((struct Car *)&pSprite->Point2D,(int *)&DAT_00669fa4);
    if (CONCAT31(extraout_var_02,bVar1) != 0) {
      gta2::SpriteS1_sub_420660(pSprite,_DAT_00669fa4);
    }
    gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
    cVar2 = '\n';
    break;
  case 0x1a:
    gta2::S56_sub_447BD0(gCheckpoint3,self->Sprite);
    if (*(short *)&self->field_0x2c == 0) {
      return 1;
    }
    gta2::SpriteS1_sub_4206C0(self->Sprite,gPathNode->a);
    gta2::S56_sub_447BA0(gCheckpoint3,(struct SpriteS1 *)self->Sprite);
    gta2::SpriteS1_sub_4337F0(self->Sprite);
    return 0;
  case 0x1d:
  case 0x1e:
    bVar3 = gta2::Particle1_sub_48C800(self);
    return bVar3;
  case 0x1f:
  case 0x22:
    uVar6 = gta2::Particle1_sub_490130(self);
    return (byte)uVar6;
  case 0x23:
    bVar3 = gta2::Particle1_sub_48C3E0(self);
    return bVar3;
  case 0x25:
    bVar3 = gta2::Particle1_sub_48C790(self);
    return bVar3;
  case 0x26:
    bVar3 = gta2::Particle1_sub_48F230(self);
    return bVar3;
  case 0x27:
    bVar3 = gta2::Particle1_sub_48BE60(self);
    return bVar3;
  case 0x28:
  case 0x29:
    bVar3 = gta2::Particle1_sub_48BEE0(self);
    return bVar3;
  case 0x2a:
    bVar3 = gta2::Particle1_sub_48A1D0(self);
    return bVar3;
  case 0x2b:
    bVar3 = gta2::Particle1_sub_48B4D0(self);
    return bVar3;
  case 0x2c:
    bVar3 = gta2::Particle1_sub_48A1E0(self);
    return bVar3;
  }
  gta2::SpriteS1_sub_4337D0((struct SpriteS1 *)self->Sprite,2,cVar2);
LAB_00490b62:
  gta2::SpriteS1_sub_4337F0(self->Sprite);
  return 0;
}



