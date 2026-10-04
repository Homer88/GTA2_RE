#include "gta2_shim.h"

// Module: winmain, Class: Car
// Functions: 4
// Source: unified (IDA+Ghidra)

// 0x00403800: Car::sub_403800
// IDA: Car::sub_403800
// Ghidra: ---
AudioManager * gta2::Car_sub_403800(Car *self, void *a2)
{
  return (AudioManager *)((int)self->Car > *(_DWORD *)a2);
}


// 0x00403820: Car::sub_403820
// IDA: Car::sub_403820
// Ghidra: ---
__int16 gta2::Car_sub_403820(Car *self, void *a2)
{
  return self->Car != *(void **)a2;
}


// 0x00403ba0: Car::IsTrainOrTrainCarriage
// IDA: Car::IsTrainOrTrainCarriage
// Ghidra: ---
bool gta2::Car_IsTrainOrTrainCarriage(Car *self)
{
  CarModel CarType; // eax

  CarType = self->CarType;
  return CarType == TRAIN || CarType == TRAINCAB || CarType == TRAINFB || CarType == BOXCAR;
}


// 0x00403bc0: Car::isSWATVANOrBankVan
// IDA: Car::isSWATVANOrBankVan
// Ghidra: ---
bool gta2::Car_isSWATVANOrBankVan(Car *self)
{
  CarModel CarType; // eax

  CarType = self->CarType;
  return CarType == SWATVAN || CarType == BANKVAN;
}



