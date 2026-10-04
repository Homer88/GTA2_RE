#include "gta2_shim.h"

// Module: other, Class: S101
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x0048a2c0: S101::S101
// IDA: S101::S101
// Ghidra: ---
void gta2::S101_S101(int self)
{
  unsigned __int16 *v2; // edi

  v2 = (unsigned __int16 *)(self + 12);
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)(self + 12));
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)(self + 32));
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)(self + 34));
  *(_BYTE *)(self + 4) = 0;
  *(_DWORD *)(self + 16) = 0;
  *(_DWORD *)(self + 20) = 0;
  *(_WORD *)(self + 24) = 0;
  *(_WORD *)(self + 26) = 0;
  *(_DWORD *)(self + 8) = unk_669F7C;
  *(_WORD *)(self + 32) = unk_669EE0.Index;
  *(_WORD *)(self + 34) = unk_669EE0.Index;
  *(_DWORD *)(self + 36) = unk_669F7C;
  *(_DWORD *)(self + 40) = unk_669F7C;
  *v2 = unk_669EE0.Index;
  *(_DWORD *)(self + 28) = 0;
  *(_WORD *)(self + 6) = 0;
  *(_DWORD *)(self + 44) = 0;
}


// 0x0048a380: S101::S101_des
// IDA: S101::S101_des
// Ghidra: ---
int gta2::S101_S101_des(_DWORD *self)
{
  int result; // eax

  result = 0;
  self[5] = 0;
  self[7] = 0;
  return result;
}



