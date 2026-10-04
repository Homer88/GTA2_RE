#include "gta2_shim.h"

// Module: other, Class: Teleporter
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004b5ed0: Teleporter::S170_FUN_004b5ed0
// IDA: sub_4B5ED0
// Ghidra: Teleporter::S170_FUN_004b5ed0
{
  LSTATUS LVar1;
  undefined1 uStack_d;
  BYTE aBStack_c [4];
  HKEY local_8;
  DWORD local_4;
  
  LVar1 = RegCreateKeyExA((HKEY)0x80000001,"Software\\Aureal\\A3D",0,(LPSTR)0x0,
                          0,0x20006,(LPSECURITY_ATTRIBUTES)0x0,&local_8,&local_4
                         );
  if (LVar1 == 0) {
    aBStack_c[0] = '\0';
    aBStack_c[1] = '\0';
    aBStack_c[2] = '\0';
    aBStack_c[3] = '\0';
    LVar1 = RegSetValueExA(local_8,"SplashScreen",0,4,aBStack_c,4);
    if (LVar1 != 0) {
      uStack_d = 0;
    }
    aBStack_c[0] = '\0';
    aBStack_c[1] = '\0';
    aBStack_c[2] = '\0';
    aBStack_c[3] = '\0';
    LVar1 = RegSetValueExA(local_8,"SplashAudio",0,4,aBStack_c,4);
    if (LVar1 != 0) {
      uStack_d = 0;
    }
    RegCloseKey(local_8);
    return uStack_d;
  }
  return 0;
}



