#include "gta2_shim.h"

// Module: other, Class: VehiclePool
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004be870: VehiclePool::S46_1_FUN_004be870
// IDA: sub_4BE870
// Ghidra: VehiclePool::S46_1_FUN_004be870
{
  SpriteS1 *this_00;
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char cVar4;
  EventHandler *pS63;
  Car *pCar;
  GameObject *this_01;
  undefined2 extraout_var;
  undefined4 uVar5;
  
  this_00 = (SpriteS1 *)self->Head;
  pS63 = gta2::SpriteS1_SpriteS1_FUN_0040fec0(this_00);
  if (pS63 == (EventHandler *)0x0) {
    pCar = (Car *)gta2::SpriteS1_GetCar(this_00);
    if (pCar == (Car *)0x0) {
      cVar4 = '\0';
      uVar5 = _DAT_006703b0;
      this_01 = (GameObject *)gta2::SpriteS1_SpriteS1_FUN_0040fea0(this_00);
      gta2::GameObject_FUN_0049c460(this_01,uVar5);
    }
    else {
      uVar5._0_1_ = self->Reserved1;
      uVar5._1_1_ = self->Reserved2;
      uVar5._2_1_ = self->Reserved3;
      uVar5._3_1_ = self->Reserved4;
      uVar3._0_1_ = self->Flags;
      uVar3._1_1_ = self->LockState;
      uVar3._2_1_ = self->AccessType;
      uVar3._3_1_ = self->PoolType;
      cVar4 = FUN_00429ff0(pSprite,uVar3,uVar5,
                           CONCAT22(extraout_var,
                                    *(undefined2 *)&self->CarSystemManager_));
      if (cVar4 != '\0') {
        gta2::CarsPrefabs_InsertCarAtFront(gCarsPrefabs,pCar);
        return cVar4;
      }
    }
  }
  else {
    uVar1._0_1_ = self->Reserved1;
    uVar1._1_1_ = self->Reserved2;
    uVar1._2_1_ = self->Reserved3;
    uVar1._3_1_ = self->Reserved4;
    uVar2._0_1_ = self->Flags;
    uVar2._1_1_ = self->LockState;
    uVar2._2_1_ = self->AccessType;
    uVar2._3_1_ = self->PoolType;
    cVar4 = gta2::FUN_00486130(pSprite,uVar2,uVar1,
                         *(undefined2 *)&self->CarSystemManager_);
    if (cVar4 != '\0') {
      gta2::CollisionBox_S61_FUN_00484db0(_gObject,pS63);
      return cVar4;
    }
  }
  return cVar4;
}



