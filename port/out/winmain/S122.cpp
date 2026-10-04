#include "gta2_shim.h"

// Module: winmain, Class: S122
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x00401bf0: S122::sub_401BF0
// IDA: S122::sub_401BF0
// Ghidra: ---
void gta2::S122_sub_401BF0(S122 *self, int WindowHeight, int WindowWidth)
{
  gta2::S202_SetToNewVal((S202 *)WindowHeight, (SpriteS1 *)(*(_DWORD *)&self->field0 / *(_DWORD *)WindowWidth));
}



