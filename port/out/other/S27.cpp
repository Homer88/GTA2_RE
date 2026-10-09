#include "gta2_shim.h"

// Module: other, Class: S27
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x0047f4d0: S27::sub_47F4D0
// IDA: S27::sub_47F4D0
// Ghidra: ---
unsigned __int8 gta2::S27_sub_47F4D0(struct MissionScriptObjects *self)
{
  MissionScriptObjectData *i; // esi
  unsigned __int8 result; // al

  for ( i = self->MissionScriptObjectDataNextElement; i; i = i->NextElement )
    result = gta2::sub_476E10(i);
  return result;
}



