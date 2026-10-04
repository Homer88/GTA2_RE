#include "gta2_shim.h"

// Module: other, Class: S290
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x004ebcd0: S290::S290_sin
// IDA: S290::S290_sin
// Ghidra: ---
  return gta2::S290_S290_sin(&unk_5D3938);
}


// 0x004ebce0: S290::S290
// IDA: S290::S290
// Ghidra: FUN_004ebce0
void gta2::S290_S290(void)
{
  gta2::S290_S290((struct S290 *)&gS290);
  return;
}



