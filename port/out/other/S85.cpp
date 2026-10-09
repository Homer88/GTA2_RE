#include "gta2_shim.h"

// Module: other, Class: S85
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x004c0940: S85::sub_4C0940
// IDA: S85::sub_4C0940
// Ghidra: FUN_004c0940
void gta2::S85_sub_4C0940(undefined4 *param_1)
{
  *param_1 = 0;
  return;
}


// 0x004c0950: S85::S85
// IDA: S85::S85
// Ghidra: ---
S85 * gta2::S85_S85(struct S85 *self)
{
  S85 *result; // eax
  int count; // ecx
  char *v3; // edx

  result = self;
  count = 99;
  v3 = &result->field_8;
  do
  {
    *(_DWORD *)v3 = v3 + 4;
    v3 += 8;
    --count;
  }
  while ( count );
  *(_DWORD *)&result->field0 = &result->field_4;
  result->field_320 = 0;
  return result;
}


// 0x004c0990: S85::S85_Des
// IDA: S85::S85_Des
// Ghidra: ---
S85 * gta2::S85_S85_Des(struct S85 *self, char a2)
{
  gta2::S85_sub_4C0940(self);
  if ( (a2 & 1) != 0 )
    free(self);
  return self;
}



