#include "gta2_shim.h"

// Module: other, Class: S68
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x004b98d0: S68::sub_4B98D0
// IDA: S68::sub_4B98D0
// Ghidra: ---
unsigned __int8 gta2::S68_sub_4B98D0(struct ScriptThread *self, int a2)
{
  unsigned __int8 result; // al
  int *i; // edx

  result = 1;
  for ( i = &self->field[0].field_0[2]; *i || *((_BYTE *)i + 4); i += 2 )
  {
    if ( ++result == 0xFF )
      return 0;
  }
  self->field[0].field_0[2 * result] = a2;
  return result;
}


// 0x004b9940: S68::sub_4B9940
// IDA: S68::sub_4B9940
// Ghidra: ---
char gta2::S68_sub_4B9940(struct ScriptThread *self, unsigned __int8 a2)
{
  char *v2; // ecx
  char result; // al

  v2 = (char *)&self->field[0].field_0[2 * a2 + 1];
  result = *v2;
  if ( *v2 )
    *v2 = --result;
  return result;
}


// 0x004b9960: S68::S68
// IDA: S68::S68
// Ghidra: ---
ScriptThread * gta2::S68_S68(struct ScriptThread *self)
{
  ScriptThread *result; // eax
  ScriptThread *v2; // edx
  int count; // esi

  result = self;
  v2 = self;
  count = 255;
  do
  {
    v2->field[0].field_0[0] = 0;
    LOBYTE(v2->field[0].field_0[1]) = 0;
    v2 = (ScriptThread *)((char *)v2 + 8);
    --count;
  }
  while ( count );
  return result;
}



