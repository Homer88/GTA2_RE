#include "gta2_shim.h"

// Module: other, Class: S167
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x004c7100: S167::S167
// IDA: S167::S167
// Ghidra: ---
S167 * gta2::S167_S167(struct S167 *self)
{
  struct S167 *result; // eax

  result = self;
  self->field_0 = -1;
  self->field_4 = 0;
  self->Sound = 0;
  return result;
}


// 0x004c7180: S167::sub_4C7180
// IDA: S167::sub_4C7180
// Ghidra: FUN_004c7180
void gta2::S167_sub_4C7180(void *self,int param_1)
{
                              // WARNING: Load size is inaccurate
  *(int *)self = *self + param_1;
  return;
}



