#include "gta2_shim.h"

// Module: winmain, Class: S103
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x00401d20: S103::sub_401D20
// IDA: S103::sub_401D20
// Ghidra: ---
void gta2::S103_sub_401D20(struct S103 *self, _DWORD *a2, _DWORD *a3)
{
  self->S104_.Weapon_ = (Weapon *)*a2;
  self->S104_.field_4 = (void *)*a3;
}



