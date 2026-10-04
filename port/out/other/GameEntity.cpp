#include "gta2_shim.h"

// Module: other, Class: GameEntity
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004a1d60: GameEntity::GameEntity
// IDA: GameEntity::GameEntity
// Ghidra: ---
void gta2::GameEntity_GameEntity(struct GameEntity *self)
{
  gta2::Construct(self->S41_Arr4, 8, 4, S41::S41, S41::S41_Dec);
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&self->special_buffer);
  self->FirstElement = 0;
  gta2::S103_sub_4A1CF0((struct S103 *)self);
}



