#include "gta2_shim.h"

// Module: other, Class: Taxi
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x004c0980: Taxi::sub_4C0980
// IDA: Taxi::sub_4C0980
// Ghidra: ---
void gta2::Taxi_sub_4C0980(struct Taxi *self)
{
  *self = 0;
}


// 0x004c09b0: Taxi::sub_4C09B0
// IDA: Taxi::sub_4C09B0
// Ghidra: ---
Taxi * gta2::Taxi_sub_4C09B0(struct Taxi *self)
{
  gta2::Taxi_sub_4C0980(self);
  return self;
}


// 0x004c09c0: Taxi::Taxi
// IDA: Taxi::Taxi
// Ghidra: ---
Taxi * gta2::Taxi_Taxi(struct Taxi *self)
{
  struct S85 *pS85; // eax
  struct S85 *pS85_1; // eax

  gta2::Taxi_sub_4C09B0(self);
  if ( !gS85 )
  {
    pS85 = (struct S85 *)gta2::operator_new(0x324u);
    if ( pS85 )
      pS85_1 = gta2::S85_S85(pS85);
    else
      pS85_1 = 0;
    gS85 = pS85_1;
    if ( !pS85_1 )
      gta2::debug_log(0x20u, "taxi.cpp", 29);
  }
  return self;
}



