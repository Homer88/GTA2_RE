#include "gta2_shim.h"

// Module: other, Class: AutoClass4
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004c2420: AutoClass4::AutoClass4
// IDA: AutoClass4::AutoClass4
// Ghidra: ---
AutoClass4 * gta2::AutoClass4_AutoClass4(AutoClass4 *self)
{
  AutoClass4 *result; // eax

  result = self;
  *(_DWORD *)self = 0;
  *((_DWORD *)self + 1) = 0;
  return result;
}



