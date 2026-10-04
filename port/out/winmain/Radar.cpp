#include "gta2_shim.h"

// Module: winmain, Class: Radar
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x00401b60: Radar::AddBlip
// IDA: Radar::AddBlip
// Ghidra: ---
SpriteS1 * gta2::Radar_AddBlip(Radar *self, SpriteS1 *a2, PublicTransport *a3)
{
  SpriteS1 *v3; // eax

  LOBYTE(self) = 14;
  v3 = (SpriteS1 *)gta2::Tango_sub_4D6230((Tango *)self);
  gta2::S202_SetToNewVal((S202 *)a2, v3);
  return a2;
}



