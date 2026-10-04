#include "gta2_shim.h"

// Module: other, Class: RouteInfo
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x00487fa0: RouteInfo::FUN_00487fa0
// IDA: sub_487FA0
// Ghidra: RouteInfo::FUN_00487fa0
void gta2::RouteInfo_FUN_00487fa0(RouteInfo *self)
{
  undefined4 *pSpriteS1;
  bool bVar1;
  short sVar2;
  int iVar3;
  struct SpriteS1 *pSVar4;
  struct Model *this_00;
  undefined3 extraout_var;
  struct SpriteS1 *pSpriteS1_00;
  int *piVar5;
  struct Model *pMVar6;
  int local_c;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  if (self->field14_0x28 == 1) {
    self->field0_0x0 = _DAT_00665bc8;
    pSVar4 = _DAT_00665bc8;
  }
  else {
    sVar2 = gta2::Style_GetGlobalSpriteId(gStyle,self->field14_0x28,self->field8_0x1e);
    iVar3 = gta2::Style_GetSprite(gStyle,sVar2);
    piVar5 = &local_c;
    pSVar4 = (struct SpriteS1 *)local_8;
    local_c = 0x40;
    pSpriteS1_00 = pSVar4;
    gta2::FUN_0040ce30(local_4,*(byte *)(iVar3 + 4));
    pSVar4 = gta2::S122_sub_401BF0((struct Model *)pSVar4,pSpriteS1_00,piVar5);
    this_00 = (struct Model *)&local_c;
    self->field0_0x0 = pSVar4->FirstElement;
    pSVar4 = (struct SpriteS1 *)local_4;
    local_c = 0x40;
    pMVar6 = this_00;
    gta2::FUN_0040ce30(local_8,*(byte *)(iVar3 + 5));
    pSVar4 = gta2::S122_sub_401BF0(this_00,pSVar4,(int *)pMVar6);
    pSVar4 = pSVar4->FirstElement;
  }
  pSpriteS1 = &self->field1_0x4;
  *pSpriteS1 = pSVar4;
  self->field2_0x8 = _DAT_00665b9c;
  bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)self,(struct SpriteS1 *)pSpriteS1);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    self->field3_0xc = self->field0_0x0;
    return;
  }
  self->field3_0xc = *pSpriteS1;
  return;
}


// 0x00488060: RouteInfo::FUN_00488060
// IDA: sub_488060
// Ghidra: RouteInfo::FUN_00488060
void * gta2::RouteInfo_FUN_00488060(RouteInfo *self,undefined2 param_1)
{
  int iVar1;
  void *pvVar2;
  
  if (self->field14_0x28 == 4) {
    self->field16_0x30 = 5;
    self->field7_0x1c = param_1;
    pvVar2 = NULL;
  }
  else {
    iVar1 = self->field14_0x28 + -5;
    pvVar2 = (void *)CONCAT22((short)((uint)iVar1 >> 0x10),param_1);
    self->field7_0x1c = param_1;
    if (iVar1 == 0) {
      self->field16_0x30 = 6;
      return pvVar2;
    }
  }
  return pvVar2;
}



