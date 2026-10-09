#include "gta2_shim.h"

// Module: other, Class: S103
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004a1cf0: S103::sub_4A1CF0
// IDA: S103::sub_4A1CF0
// Ghidra: ---
ushort gta2::S103_sub_4A1CF0(struct S103 *self)
{
  gta2::S103_sub_41E1E0((S103 *)&self->S104_.S63);
  LOWORD(self->S104_.field_58) = unk_66AC08;
  gta2::S103_sub_41E1E0((S103 *)&self->S104_.S63_2);
  self->S104_.field_5C = 0;
  gta2::Player_sub_4A1BE0((Player *)self);
  return gta2::S103_sub_41E1E0(self);
}



