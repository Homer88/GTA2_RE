#include "gta2_shim.h"

// Module: other, Class: CollisionBox
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x00482e80: CollisionBox::FUN_00482e80
// IDA: sub_482E80
// Ghidra: CollisionBox::FUN_00482e80
undefined4 gta2::CollisionBox_FUN_00482e80(struct CollisionBox *self,SpriteS1 *param_1)
{
  byte bVar1;
  char cVar2;
  char cVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  uint uVar4;
  undefined3 extraout_var_01;
  
  bVar1 = gta2::S63_sub_421080(self);
  uVar4 = CONCAT31(extraout_var,bVar1);
  if (bVar1 != 0) {
    cVar2 = gta2::S63_sub_420FF0(self);
    uVar4 = CONCAT31(extraout_var_00,cVar2);
    if ((cVar2 != '\0') && (param_1 != NULL)) {
      uVar4 = gta2::SpriteS1_GetGameObject(param_1);
      if (uVar4 != 0) {
        cVar2 = gta2::sub_420B50(*(Ped **)(uVar4 + 0x7c));
        cVar3 = gta2::S63_sub_420FF0(self);
        uVar4 = CONCAT31(extraout_var_01,cVar3);
        if (cVar2 == cVar3) {
          return CONCAT31(extraout_var_01,1);
        }
      }
    }
  }
  return uVar4 & 0xffffff00;
}


// 0x00483570: CollisionBox::FUN_00483570
// IDA: sub_483570
// Ghidra: CollisionBox::FUN_00483570
byte gta2::CollisionBox_FUN_00483570(struct CollisionBox *self,SpriteS1 *pSpriteS1)
{
  EventHandler *this_00;
  char cVar1;
  bool bVar2;
  void *this_01;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  TrafficLigthStruct *pS90;
  
  this_01 = (void *)gta2::SpriteS1_GetCar(pSpriteS1);
  if ((this_01 == NULL) || (cVar1 = FUN_00482d00(this_01), cVar1 == '\0')) {
    return 0;
  }
  this_00 = self->Index;
  bVar2 = FUN_0040e690(this_00,(short *)&DAT_006657f8______S38);
  pS90 = gTrafficLigthStruct;
  if ((CONCAT31(extraout_var,bVar2) != 0) &&
     (cVar1 = gta2::TrafficLigthStruct_sub_482D10(gTrafficLigthStruct),
     cVar1 != '\0')) {
    return 0;
  }
  bVar2 = FUN_0040e690(this_00,(short *)&DAT_00665ad0);
  if ((CONCAT31(extraout_var_00,bVar2) != 0) &&
     (cVar1 = gta2::TrafficLigthStruct_sub_482D20(pS90), cVar1 != '\0'
     )) {
    return 0;
  }
  return 1;
}


// 0x00483c80: CollisionBox::FUN_00483c80
// IDA: sub_483C80
// Ghidra: CollisionBox::FUN_00483c80
undefined4 gta2::CollisionBox_FUN_00483c80(struct CollisionBox *self)
{
  undefined1 uVar1;
  
  uVar1 = gta2::S63_GetIndex(self);
  switch(uVar1) {
  default:
    return 0x17;
  case 0x2e:
  case 0x30:
    return 0x16;
  }
}



