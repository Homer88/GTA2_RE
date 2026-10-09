#include "gta2_shim.h"

// Module: other, Class: GarageInfo
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004c8e30: GarageInfo::FUN_004c8e30
// IDA: sub_4C8E30
// Ghidra: GarageInfo::FUN_004c8e30
void gta2::GarageInfo_FUN_004c8e30(GarageInfo *self,SpriteS1 *param_1,SpriteS1 *param_2)
{
  SpriteS1 *pSVar1;
  int iVar2;
  SpriteS1 *extraout_ECX;
  Hud *this_00;
  SpriteS1 *extraout_ECX_00;
  Hud *pHVar3;
  SpriteS1 *extraout_ECX_01;
  Hud *this_01;
  undefined2 extraout_var;
  SpriteS1 *pSVar4;
  SpriteS1 *extraout_ECX_02;
  Hud *extraout_ECX_03;
  SpriteS1 *extraout_ECX_04;
  Hud *extraout_ECX_05;
  SpriteS1 *extraout_ECX_06;
  Hud *this_02;
  SpriteS1 *extraout_ECX_07;
  Hud *this_03;
  int iVar5;
  undefined1 *puVar6;
  void *id2;
  SpriteS1 *pSVar7;
  
  iVar5 = self->CarGenerator[0].field0_0x0 / 0x1e;
  iVar2 = iVar5 / 0x3c;
  iVar5 = iVar5 % 0x3c;
  puVar6 = (undefined1 *)((int)&param_2->FirstElement + 3);
  pSVar7 = (SpriteS1 *)0xa;
  gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffc8,(int)puVar6);
  pSVar1 = param_1;
  pSVar4 = extraout_ECX;
  gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffc4,
             (int)&param_1[-1].Matrix3DArray[0x13a6].field_0x2f);
  gta2::Hud_DrawSprite(this_00,6,(void *)(iVar2 / 10 + 0x7b),pSVar4,pSVar7);
  pSVar4 = (SpriteS1 *)&param_1;
  param_1 = (SpriteS1 *)0x2;
  gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffc8,(int)puVar6);
  pSVar7 = extraout_ECX_00;
  gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffc4,
             (int)((int)&pSVar1[-1].Matrix3DArray[0x13a6].field19_0x34 + 2));
  pHVar3 = (Hud *)(iVar2 % 10 + 0x7b);
  gta2::Hud_DrawSprite(pHVar3,6,pHVar3,pSVar7,pSVar4);
  if (self->CarGenerator[0].field0_0x0 % 0xf < 8) {
    pSVar7 = (SpriteS1 *)0xf;
    param_1 = (SpriteS1 *)0x2;
    gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffc8,(int)puVar6);
    pSVar4 = extraout_ECX_01;
    gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffc4,
               (int)&pSVar1[-1].Matrix3DArray[0x13a6].field_0x3b);
    gta2::Hud_DrawSprite(this_01,6,(void *)0x79,pSVar4,pSVar7);
    if (299 < self->CarGenerator[0].field0_0x0) goto LAB_004c8fa5;
    pSVar4 = (SpriteS1 *)CONCAT22(extraout_var,_DAT_00672f98);
    param_1 = (SpriteS1 *)0x2;
    gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffc8,
               (int)((int)&param_2->Matrix3DArray[0].SpriteS3 + 2));
    pSVar7 = extraout_ECX_02;
    gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffc4,
               (int)&pSVar1->Matrix3DArray[0].PositionX);
    id2 = (void *)0x85;
    pHVar3 = extraout_ECX_03;
  }
  else {
    pSVar4 = (SpriteS1 *)&param_2;
    param_2 = (SpriteS1 *)0x2;
    gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffc8,(int)puVar6);
    pSVar7 = extraout_ECX_04;
    gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffc4,
               (int)&pSVar1[-1].Matrix3DArray[0x13a6].field_0x3b);
    id2 = (void *)0x78;
    pHVar3 = extraout_ECX_05;
  }
  gta2::Hud_DrawSprite(pHVar3,6,id2,pSVar7,pSVar4);
LAB_004c8fa5:
  param_1 = (SpriteS1 *)(iVar5 / 10);
  param_2 = (SpriteS1 *)0x2;
  pSVar7 = (SpriteS1 *)0xa;
  gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffc8,(int)puVar6);
  pSVar4 = extraout_ECX_06;
  gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffc4,(int)pSVar1->Matrix3DArray);
  gta2::Hud_DrawSprite(this_02,6,&param_1->Matrix3DArray[1].field_0x3b,pSVar4,pSVar7)
  ;
  pSVar4 = (SpriteS1 *)&param_2;
  param_2 = (SpriteS1 *)0x2;
  gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffc8,(int)puVar6);
  pSVar7 = extraout_ECX_07;
  gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffc4,
             (int)((int)&pSVar1->Matrix3DArray[0].Car + 3));
  gta2::Hud_DrawSprite(this_03,6,(void *)(iVar5 % 10 + 0x7b),pSVar7,pSVar4);
  return;
}



