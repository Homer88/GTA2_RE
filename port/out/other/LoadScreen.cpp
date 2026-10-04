#include "gta2_shim.h"

// Module: other, Class: LoadScreen
// Functions: 7
// Source: unified (IDA+Ghidra)

// 0x004af290: LoadScreen::FUN_004af290
// IDA: sub_4AF290
// Ghidra: LoadScreen::FUN_004af290
{
  if (!gSkipTrains) {
    self->field60_0x50 = (self->Car->Driver != (struct Ped *)0x0) + 2;
  }
  return;
}


// 0x004af2b0: LoadScreen::FUN_004af2b0
// IDA: sub_4AF2B0
// Ghidra: LoadScreen::FUN_004af2b0
{
  struct Car *pCVar1;
  char cVar2;
  struct Car *this_00;
  byte bVar3;
  short *psVar4;
  uint local_4;
  
  pCVar1 = self->trainComponents[0].linkedCar;
  if (!gSkipTrains) {
    this_00 = self->Car;
    if ((31999 < this_00->Damage) && (self->field52_0x42 == -1)) {
      self->field52_0x42 = 10;
    }
    if ((self->field42_0x38 == '\x01') && (31999 < pCVar1->Damage)) {
      self->field52_0x42 = 10;
    }
    if (('\0' < (char)self->field52_0x42) &&
       (cVar2 = self->field52_0x42 + -1, self->field52_0x42 = cVar2,
       cVar2 == '\0')) {
      if (31999 < this_00->Damage) {
        this_00 = pCVar1;
      }
      gta2::Car_Car_CollisionOnCar(this_00,32000,&DAT_0066bb90);
    }
    bVar3 = 0;
    local_4 = 0;
    if (self->field53_0x43 != 0) {
      psVar4 = &pCVar1->Damage;
      do {
        if ((*(char *)((int)(self->trainComponents + 10) + local_4) == -1) &&
           (31999 < *psVar4)) {
          if (bVar3 == 0) {
            if ((int)local_4 < (int)(self->field53_0x43 - 1)) {
              *(undefined1 *)((int)(self->trainComponents + 10) + local_4 + 1) =
                   10;
            }
            else {
              self->field52_0x42 = 10;
            }
          }
          else {
            *(undefined1 *)((int)(self->trainComponents + 9) + local_4 + 3) = 10
            ;
          }
          *(undefined1 *)((int)(self->trainComponents + 10) + local_4) = 0;
        }
        if (('\0' < *(char *)((int)(self->trainComponents + 10) + local_4)) &&
           (cVar2 = *(char *)((int)(self->trainComponents + 10) + local_4) + -1,
           *(char *)((int)(self->trainComponents + 10) + local_4) = cVar2,
           cVar2 == '\0')) {
          gta2::Car_Car_CollisionOnCar(self->trainComponents[local_4].linkedCar,32000,
                     &DAT_0066bb90);
          if (bVar3 != 0) {
            *(undefined1 *)((int)(self->trainComponents + 9) + local_4 + 3) = 10
            ;
          }
          if ((int)local_4 < (int)(self->field53_0x43 - 1)) {
            *(undefined1 *)((int)(self->trainComponents + 10) + local_4 + 1) =
                 10;
          }
          if (bVar3 == 0) {
            self->field52_0x42 = 10;
          }
        }
        psVar4 = psVar4 + 0x5e;
        bVar3 = bVar3 + 1;
        local_4 = (uint)bVar3;
      } while (bVar3 < self->field53_0x43);
    }
  }
  return;
}


// 0x004af8a0: LoadScreen::FUN_004af8a0
// IDA: sub_4AF8A0
// Ghidra: LoadScreen::FUN_004af8a0
{
  struct Car *pCVar1;
  struct Car *pCVar2;
  struct Player *this_00;
  byte bVar3;
  undefined4 uVar4;
  
  if (!gSkipTrains) {
    pCVar1 = self->Car;
    self->Car = self->trainComponents[self->field53_0x43 - 1].linkedCar;
    self->trainComponents[self->field53_0x43 - 1].linkedCar = pCVar1;
    gta2::CarsPrefabs_S5_FUN_00420f20(gCarsPrefabs,self->Car);
    gta2::CarsPrefabs_S5_FUN_00420f30(gCarsPrefabs,
               self->trainComponents[self->field53_0x43 - 1].linkedCar);
    pCVar2 = self->trainComponents[self->field53_0x43 - 1].linkedCar;
    if (pCVar2->Player_ != (struct Player *)0x0) {
      gta2::Car_Car_FUN_00423a50(pCVar2);
    }
    gta2::LinkedList_S1_FUN_004a1be0((LinkedList *)
               (self->trainComponents[self->field53_0x43 - 1].linkedCar)->Player_
              );
    if (self->Car->Player_ != (struct Player *)0x0) {
      gta2::Car_Car_FUN_00423a50(self->Car);
    }
    gta2::Player_FUN_0049ee10(self->Car->Player_,self->Car->CarSprite);
    self->Car->Driver = pCVar1->Driver;
    if (self->Car->Player_ != (struct Player *)0x0) {
      gta2::Car_Car_FUN_00423a50(self->Car);
    }
    pCVar2 = self->Car;
    bVar3 = gta2::Car_IsDriverPlayer(pCVar2);
    this_00 = pCVar2->Player_;
    if (bVar3 == 0) {
      gta2::Player_SetAttackChanged(this_00);
    }
    else {
      gta2::Player_Player_FUN_004212b0(this_00);
    }
    pCVar1->Driver = (struct Ped *)0x0;
    gta2::Car_CarMakeDriveable2(self->Car);
    gta2::Car_CarMakeDriveable3((struct Car *)self->Car->EngineStruct_,self->Car);
    gta2::Car_Car_FUN_004266f0(pCVar1);
    pCVar1 = self->Car;
    uVar4 = gta2::Ped_sub_420B70(pCVar1->Driver);
    gta2::Car_CarMakeDriveable1(pCVar1,uVar4);
  }
  return;
}


// 0x004af9a0: LoadScreen::FUN_004af9a0
// IDA: sub_4AF9A0
// Ghidra: LoadScreen::FUN_004af9a0
{
  if (!gSkipTrains) {
    switch(self->field60_0x50) {
    case 0:
      self->field60_0x50 = 1;
      return;
    case 1:
      FUN_004af8a0(self);
      self->field60_0x50 = 2;
      return;
    case 2:
      self->field60_0x50 = 3;
      return;
    case 3:
      self->field60_0x50 = 4;
      return;
    case 4:
      self->field60_0x50 = 5;
    }
  }
  return;
}


// 0x004afa10: LoadScreen::FUN_004afa10
// IDA: sub_4AFA10
// Ghidra: LoadScreen::FUN_004afa10
{
  if (!gSkipTrains) {
    switch(self->field60_0x50) {
    case 1:
      self->field60_0x50 = 0;
      return;
    case 2:
      FUN_004af8a0(self);
      self->field60_0x50 = 1;
      return;
    case 3:
      self->field60_0x50 = 2;
      return;
    case 4:
      self->field60_0x50 = 3;
      return;
    case 5:
      self->field60_0x50 = 4;
    }
  }
  return;
}


// 0x004afa80: LoadScreen::FUN_004afa80
// IDA: sub_4AFA80
// Ghidra: LoadScreen::FUN_004afa80
{
  if (!gSkipTrains) {
    if (self->field60_0x50 < 2) {
      self->field1_0x1 = 1;
      FUN_004af8a0(self);
    }
    self->field60_0x50 = 2;
  }
  return;
}


// 0x004afaf0: LoadScreen::FUN_004afaf0
// IDA: sub_4AFAF0
// Ghidra: LoadScreen::FUN_004afaf0
{
  struct Car *this_00;
  int iVar1;
  int iVar2;
  TrainComponent *pTVar3;
  
  if (!gSkipTrains) {
    pTVar3 = self->trainComponents;
    iVar2 = 2;
    do {
      this_00 = pTVar3->linkedCar;
      if ((this_00 != (struct Car *)0x0) &&
         (iVar1 = gta2::Car_GetModelCar(this_00), iVar1 == 0x3b)) {
        FUN_0041f8a0(this_00);
      }
      pTVar3 = pTVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}



