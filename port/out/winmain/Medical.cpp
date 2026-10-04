#include "gta2_shim.h"

// Module: winmain, Class: Medical
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x00404c40: Medical::sub_404C40
// IDA: Medical::sub_404C40
// Ghidra: Police::FUN_00404c40
AIController * gta2::Medical_sub_404C40(struct Police *self)
{
  bool bVar1;
  SpawnPoint *pS169;
  int iVar2;
  AIController *pAutoClass4;
  
  iVar2 = 0;
  pS169 = (SpawnPoint *)&gSpawnPoint;
  do {
    bVar1 = gta2::S169_GetInUse((struct S169 *)pS169);
    if (!bVar1) {
      pAutoClass4 = (AIController *)(&gSpawnPoint + iVar2 * 0x11);
      gta2::S169_S169((struct S169 *)pAutoClass4);
      gta2::S169_SetInUse((struct S169 *)pAutoClass4);
      return pAutoClass4;
    }
    pS169 = (SpawnPoint *)&pS169->field21_0x44;
    iVar2 = iVar2 + 1;
  } while ((int)pS169 < 0x5d2e18);
  return NULL;
}



