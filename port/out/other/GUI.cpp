#include "gta2_shim.h"

// Module: other, Class: GUI
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004c5fd0: GUI::SetInteface
// IDA: GUI::SetInteface
// Ghidra: ---
void gta2::GUI_SetInteface(struct GUI *self)
{
  self->Interface = 0;
}



