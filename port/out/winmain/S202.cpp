#include "gta2_shim.h"

// Module: winmain, Class: S202
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x00401ad0: S202::SetToNewVal
// IDA: S202::SetToNewVal
// Ghidra: ---
void gta2::S202_SetToNewVal(struct S202 *self, SpriteS1 *pSpriteNab)
{
  self->field_0 = (int)pSpriteNab;
}


// 0x00401b20: S202::sub_401B20
// IDA: S202::sub_401B20
// Ghidra: ---
SpriteS1 * gta2::S202_sub_401B20(struct S202 *self, SpriteS1 *pSpriteS1, PublicTransport *pPublicTransport)
{
  gta2::S202_SetToNewVal((S202 *)pSpriteS1, (SpriteS1 *)(self->field_0 + pPublicTransport->BaseCar_.field));
  return pSpriteS1;
}



