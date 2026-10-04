#include "gta2_shim.h"

// Module: other, Class: S25
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x004768c0: S25::sub_4768C0
// IDA: S25::sub_4768C0
// Ghidra: ---
int gta2::S25_sub_4768C0(struct MissionObjective *self, unsigned __int8 a2, int a3)
{
  int result; // eax

  result = 3 * a2;
  *(_DWORD *)&self->gap4[24 * a2 + 16] = a3;
  return result;
}


// 0x004c4ee0: S25::sub_4C4EE0
// IDA: S25::sub_4C4EE0
// Ghidra: ---
_WORD * gta2::S25_sub_4C4EE0(struct MissionObjective *self)
{
  _WORD *result; // eax
  unsigned __int8 i; // dl

  *(_WORD *)&self->gap133[221] = 0;
  result = &self->gap4[4];
  for ( i = 0; i < 0x16u; ++i )
  {
    *((_BYTE *)result + 8) = i;
    *(_DWORD *)result = 0;
    *((_DWORD *)result + 1) = 0;
    *((_DWORD *)result - 2) = 0;
    *((_DWORD *)result + 3) = 1;
    result += 12;
  }
  return result;
}



