#include "gta2_shim.h"

// Module: other, Class: S109
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x004c5430: S109::sub_4C5430
// IDA: S109::sub_4C5430
// Ghidra: ---
S110 * gta2::S109_sub_4C5430(struct S109 *self)
{
  unsigned __int8 v1; // bl
  unsigned __int8 v3; // [esp+4h] [ebp-4h]

  v1 = 0;
  v3 = 0;
  while ( self->S110_[v3].field_1E )
  {
    v3 = ++v1;
    if ( v1 >= 10u )
      return 0;
  }
  return &self->S110_[v3];
}


// 0x004c5db0: S109::sub_4C5DB0
// IDA: S109::sub_4C5DB0
// Ghidra: ---
void gta2::S109_sub_4C5DB0(struct S109 *self)
{
  char *v1; // esi
  int v2; // edi

  v1 = &self->S110_[0].field_1E;
  v2 = 10;
  do
  {
    if ( *v1 )
    {
      if ( gta2::sub_4C5CA0(v1 - 30) )
        *v1 = 0;
    }
    v1 += 48;
    --v2;
  }
  while ( v2 );
}



