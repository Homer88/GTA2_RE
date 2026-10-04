#include "gta2_shim.h"

// Module: other, Class: Arsenal
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x004d0740: Arsenal::Arsenal
// IDA: Arsenal::Arsenal
// Ghidra: ---
Arsenal * gta2::Arsenal_Arsenal(struct Arsenal *self)
{
  struct WeaponDatabase *v2; // eax
  struct WeaponDatabase *v3; // eax

  gta2::Arsenal_Reset(self);
  if ( !gWeaponDatabase )
  {
    v2 = (struct WeaponDatabase *)gta2::operator_new(0x2FDCu);
    if ( v2 )
      v3 = gta2::WeaponDatabase_WeaponDatabase(v2);
    else
      v3 = 0;
    gWeaponDatabase = v3;
    if ( !v3 )
      gta2::debug_log(0x20u, "weapon.cpp", 2428);
  }
  self->Count = 0;
  gta2::Turrel_SetSelect(self);
  return self;
}


// 0x004ffc50: Arsenal::Reset
// IDA: Arsenal::Reset
// Ghidra: FUN_004ffc50
void gta2::Arsenal_Reset(void)
{
  gta2::Arsenal_Reset((Turrel *)&gTurrel);
  return;
}


// 0x004ffc60: Arsenal::Reset
// IDA: Arsenal::Reset
// Ghidra: ---
  return gta2::Arsenal_Reset((struct Arsenal *)&gTurrel_0);
}



