#include "gta2_shim.h"

// Module: other, Class: ScriptCommand
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004c32e0: ScriptCommand::FUN_004c32e0
// IDA: sub_4C32E0
// Ghidra: ScriptCommand::FUN_004c32e0
void gta2::ScriptCommand_FUN_004c32e0(ScriptCommand *self)
{
  self->count = self->field2_0x4;
  self->count1 = self->field0_0x0;
  gta2::TileAnim2_sub_4C3260(self);
  return;
}



