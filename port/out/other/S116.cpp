#include "gta2_shim.h"

// Module: other, Class: S116
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x0048a510: S116::sub_48A510
// IDA: S116::sub_48A510
// Ghidra: ---
int gta2::S116_sub_48A510(struct S116 *self)
{
  int result; // eax
  bool v2; // zf

  result = 0;
  v2 = self->Next == 0;
  HIWORD(self->field_4) = 0;
  if ( v2 )
    *(&gS102->S101_[40].field + LOBYTE(self->field_4)) = 0;
  else
    *(&gS100->S101_[20].field + LOBYTE(self->field_4)) = 0;
  return result;
}



