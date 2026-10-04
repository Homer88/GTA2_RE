#include "gta2_shim.h"

// Module: other, Class: S36
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x004c3680: S36::sub_4C3680
// IDA: S36::sub_4C3680
// Ghidra: ---
void gta2::S36_sub_4C3680(struct Radar *self)
{
  self->DeltaTime += timeGetTime() - self->Time;
}


// 0x004c36a0: S36::S36
// IDA: S36::S36
// Ghidra: ---
Radar * gta2::S36_S36(struct Radar *self)
{
  struct Radar *result; // eax

  result = self;
  self->field_0 = 0;
  self->DeltaTime = 0;
  self->Time = 0;
  return result;
}



