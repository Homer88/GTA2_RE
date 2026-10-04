#include "gta2_shim.h"

// Module: other, Class: DecalInfo
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004ab330: DecalInfo::S112_FUN_004ab330
// IDA: ---
// Ghidra: DecalInfo::S112_FUN_004ab330
{
  GlassInfo *pGVar1;
  SpawnPoint *pSVar2;
  byte bVar3;
  ushort uVar4;
  uint uVar5;
  struct Ped *pS49;
  
  pGVar1 = self->s110;
  self->select = 2;
  if (pGVar1->S169_ == (SpawnPoint *)0x0) {
    pS49 = pGVar1->pPed;
    if (pS49 == (struct Ped *)0x0) {
      pGVar1->field22_0x28 = 5;
      self->s110->field23_0x2c = 1;
    }
    else {
      uVar4 = gta2::Ped_S49_FUN_004039f0(pS49);
      if (0x1d < uVar4) {
        gta2::Ped_FUN_0043e650(pS49);
        self->s110->field22_0x28 = 5;
        self->s110->field23_0x2c = 1;
        return;
      }
    }
  }
  else {
    bVar3 = gta2::SpawnPoint_S169_FUN_00403c40(pGVar1->S169_);
    if (bVar3 != 0) {
      bVar3 = 0;
      pS49 = self->s110->pPed;
      while (pS49 != (struct Ped *)0x0) {
        gta2::Ped_SetDefault(pS49);
        gta2::Ped_FUN_0043e650(pS49);
        pSVar2 = self->s110->S169_;
        if (pSVar2 == (SpawnPoint *)0x0) break;
        uVar5 = (uint)bVar3;
        bVar3 = bVar3 + 1;
        pS49 = pSVar2->Ped_Arr9[uVar5];
      }
      gta2::S169_sub_403BE0(self->s110->S169_);
      self->s110->field22_0x28 = 5;
      self->s110->field23_0x2c = 1;
      return;
    }
  }
  return;
}



