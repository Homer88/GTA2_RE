#include "gta2_shim.h"

// Module: other, Class: S108
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x00476920: S108::sub_476920
// IDA: S108::sub_476920
// Ghidra: FUN_00476920
void gta2::S108_sub_476920(int param_1,undefined2 param_2)
{
  *(undefined2 *)(param_1 + 0x1c) = param_2;
  return;
}



