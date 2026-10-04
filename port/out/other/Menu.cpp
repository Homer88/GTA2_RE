#include "gta2_shim.h"

// Module: other, Class: Menu
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x00481d30: Menu::CloseBinkResources
// IDA: Menu::CloseBinkResources
// Ghidra: ---
void gta2::Menu_CloseBinkResources(struct Menu *self)
{
  if ( gBinkBuffer )
  {
    BinkBufferClose(gBinkBuffer);
    gBinkBuffer = 0;
    unk_665078 = 0;
  }
  if ( gBink )
  {
    BinkGetSummary(gBink, &unk_665000);
    BinkClose(gBink);
    gBink = 0;
  }
}



