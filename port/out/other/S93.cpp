#include "gta2_shim.h"

// Module: other, Class: S93
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x00491d00: S93::sub_491D00
// IDA: S93::sub_491D00
// Ghidra: FUN_00491d00
int gta2::S93_sub_491D00(int param_1,byte *param_2)
{
  byte bVar1;
  undefined4 local_4;
  
  bVar1 = 0;
  local_4 = 0;
  do {
    if (*(char *)(local_4 + 0x1d4c + param_1) == '\0') {
      *param_2 = bVar1;
      *(undefined1 *)(local_4 + 0x1d4c + param_1) = 1;
      return param_1 + local_4 * 0x96;
    }
    bVar1 = bVar1 + 1;
    local_4 = (uint)bVar1;
  } while (bVar1 < 0x32);
  return 0;
}


// 0x00491da0: S93::S93
// IDA: S93::S93
// Ghidra: ---
S93_1 * gta2::S93_S93(struct S93_1 *self)
{
  gta2::Construct(self, 150, 50, S94::S94, S94::S94_Des);
  memset(self->?, 0, sizeof(self->?));
  self->? = 0;
  return self;
}



