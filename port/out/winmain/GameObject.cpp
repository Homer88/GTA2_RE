#include "gta2_shim.h"

// Module: winmain, Class: GameObject
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x00403900: GameObject::GetCar
// IDA: GameObject::GetCar
// Ghidra: ---
Car * gta2::GameObject_GetCar(struct GameObject *self)
{
  return self->GetVehicle;
}



