#include "gta2_shim.h"

// Module: other, Class: ScriptVar
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004c3500: ScriptVar::S70_FUN_004c3500
// IDA: ---
// Ghidra: ScriptVar::S70_FUN_004c3500
{
  ScriptCommand *pSVar1;
  byte bVar2;
  ScriptCommand *pS71_2;
  ScriptCommand *pS71;
  ScriptCommand *pS71_1;
  
  self->field3_0x4b8 = 0;
  pSVar1 = self->ScriptCommand1;
  pS71 = (ScriptCommand *)0x0;
  do {
    while( true ) {
      do {
        pS71_2 = pS71;
        pS71 = pSVar1;
        if (pS71 == (ScriptCommand *)0x0) {
          return;
        }
        self->field3_0x4b8 = self->field3_0x4b8 + 1;
        pSVar1 = pS71->ScriptCommand;
        bVar2 = gta2::ScriptCommand_S71_FUN_004c3300(pS71);
      } while (bVar2 == 0);
      if (pS71_2 != (ScriptCommand *)0x0) break;
LAB_004c3536:
      pS71_1 = self->ScriptCommand1;
      if (pS71_1 == pS71) {
        self->ScriptCommand1 = pS71->ScriptCommand;
        pS71->ScriptCommand = self->ScriptCommand;
        self->ScriptCommand = pS71;
        pS71 = pS71_2;
      }
      else {
        pS71_2 = pS71_1->ScriptCommand;
        while (pS71_2 != pS71) {
          pS71_1 = pS71_1->ScriptCommand;
          pS71_2 = pS71_1->ScriptCommand;
        }
        pS71_1->ScriptCommand = pS71->ScriptCommand;
        pS71->ScriptCommand = self->ScriptCommand;
        self->ScriptCommand = pS71;
        pS71 = pS71_1;
      }
    }
    if (pS71_2->ScriptCommand != pS71) {
      pS71_2 = (ScriptCommand *)0x0;
      goto LAB_004c3536;
    }
    pS71_2->ScriptCommand = pS71->ScriptCommand;
    pS71->ScriptCommand = self->ScriptCommand;
    self->ScriptCommand = pS71;
    pS71 = pS71_2;
  } while( true );
}



