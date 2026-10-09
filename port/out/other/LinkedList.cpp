#include "gta2_shim.h"

// Module: other, Class: LinkedList
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004a3120: LinkedList::S1_FUN_004a3120
// IDA: ---
// Ghidra: LinkedList::S1_FUN_004a3120
{
  int iVar1;
  
  iVar1 = _DAT_0066ac4c;
  _DAT_0066afc0 = _DAT_0066ac4c;
  S1_FUN_0049def0(self);
  gta2::Player_cPlayer_FUN_004a2e30((Player *)self,iVar1);
  return;
}



