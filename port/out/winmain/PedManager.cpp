#include "gta2_shim.h"

// Module: winmain, Class: PedManager
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x00403890: PedManager::sub_403890
// IDA: PedManager::sub_403890
// Ghidra: ---
Ped * gta2::PedManager_sub_403890(struct PedManager *self)
{
  Ped *NextPed; // edx
  Ped *FirstElement; // esi

  NextPed = self->NextPed;
  FirstElement = self->FirstElement;
  self->FirstElement = *(Ped **)&self->FirstElement->field_FF;
  *(Ped **)&FirstElement->field_FF = NextPed;
  self->NextPed = FirstElement;
  gta2::Ped_sub_435B80(FirstElement);
  return FirstElement;
}




