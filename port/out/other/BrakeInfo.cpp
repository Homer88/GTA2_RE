#include "gta2_shim.h"

// Module: other, Class: BrakeInfo
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x004b9000: BrakeInfo::FUN_004b9000
// IDA: sub_4B9000
// Ghidra: BrakeInfo::FUN_004b9000
{
  struct S125 *pSVar1;
  struct S125 *pSVar2;
  struct S125 *pSVar3;
  
  pSVar3 = (struct S125 *)0x0;
  pSVar1 = self->s125;
  if (self->s125 != (struct S125 *)0x0) {
    while (pSVar2 = pSVar1, pSVar2 != pS125) {
      pSVar1 = pSVar2->s125;
      pSVar3 = pSVar2;
      if (pSVar2->s125 == (struct S125 *)0x0) {
        return;
      }
    }
    if (pSVar3 != (struct S125 *)0x0) {
      pSVar3->s125 = pSVar2->s125;
      pSVar2->s125 = self->Begin;
      self->Begin = pSVar2;
      return;
    }
    self->s125 = pSVar2->s125;
    pSVar2->s125 = self->Begin;
    self->Begin = pSVar2;
  }
  return;
}


// 0x004b9050: BrakeInfo::S124_FUN_004b9050
// IDA: ---
// Ghidra: BrakeInfo::S124_FUN_004b9050
{
  byte bVar1;
  struct S125 *pS125_3;
  struct S125 *pS125;
  struct S125 *pS125_1;
  struct S125 *pS125_2;
  
  self->count = 0;
  pS125 = self->s125;
  pS125_2 = (struct S125 *)0x0;
  do {
    while( true ) {
      do {
        pS125_3 = pS125_2;
        pS125_2 = pS125;
        if (pS125_2 == (struct S125 *)0x0) {
          return;
        }
        self->count = self->count + 1;
        pS125 = pS125_2->s125;
        bVar1 = gta2::S125_S125_FUN_004b8f70(pS125_2);
      } while (bVar1 == 0);
      if (pS125_3 != (struct S125 *)0x0) break;
LAB_004b9086:
      pS125_1 = self->s125;
      if (pS125_1 == pS125_2) {
        self->s125 = pS125_2->s125;
        pS125_2->s125 = self->Begin;
        self->Begin = pS125_2;
        pS125_2 = pS125_3;
      }
      else {
        pS125_3 = pS125_1->s125;
        while (pS125_3 != pS125_2) {
          pS125_1 = pS125_1->s125;
          pS125_3 = pS125_1->s125;
        }
        pS125_1->s125 = pS125_2->s125;
        pS125_2->s125 = self->Begin;
        self->Begin = pS125_2;
        pS125_2 = pS125_1;
      }
    }
    if (pS125_3->s125 != pS125_2) {
      pS125_3 = (struct S125 *)0x0;
      goto LAB_004b9086;
    }
    pS125_3->s125 = pS125_2->s125;
    pS125_2->s125 = self->Begin;
    self->Begin = pS125_2;
    pS125_2 = pS125_3;
  } while( true );
}



