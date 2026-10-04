#include "gta2_shim.h"

// Module: winmain, Class: CarSystemManager
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x00401c10: CarSystemManager::Clamp
// IDA: CarSystemManager::Clamp
// Ghidra: ---
void gta2::CarSystemManager_Clamp(CarSystemManager *self)
{
  __int16 Index; // ax
  __int16 v2; // ax

  if ( (self->Index & 0x8000u) != 0 )
  {
    Index = self->Index;
    do
      Index += 1440;
    while ( Index < 0 );
    self->Index = Index;
  }
  if ( (__int16)self->Index >= 1440 )
  {
    v2 = self->Index;
    do
      v2 -= 1440;
    while ( v2 >= 1440 );
    self->Index = v2;
  }
}


// 0x00401c40: CarSystemManager::sub_401C40
// IDA: CarSystemManager::sub_401C40
// Ghidra: ---
CarSystemManager * gta2::CarSystemManager_sub_401C40(CarSystemManager *self, Game *pGame)
{
  self->Index = gta2::Game_ShiftId(pGame);
  gta2::CarSystemManager_Clamp(self);
  return self;
}


// 0x00401c60: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
Ped * gta2::CarSystemManager_sub_401C60(CarSystemManager *self, __int16 *a2)
{
  self->Index = *a2;
  gta2::CarSystemManager_Clamp(self);
  return (Ped *)self;
}



