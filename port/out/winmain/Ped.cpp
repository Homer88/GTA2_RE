#include "gta2_shim.h"

// Module: winmain, Class: Ped
// Functions: 40
// Source: unified (IDA+Ghidra)

// 0x00403920: Ped::SetSearchType
// IDA: Ped::SetSearchType
// Ghidra: ---
void gta2::Ped_SetSearchType(struct Ped *self, SearchType type)
{
  self->field_1D4 = type;
}


// 0x00403930: Ped::sub_403930
// IDA: Ped::sub_403930
// Ghidra: ---
void gta2::Ped_sub_403930(struct Ped *self, S169 *a2)
{
  *(void **)&self->field_103 = a2;
}


// 0x00403940: Ped::SetCarId
// IDA: Ped::SetCarId
// Ghidra: ---
void gta2::Ped_SetCarId(struct Ped *self, char a2)
{
  self->field_1D8 = a2;
}


// 0x00403950: Ped::sub_403950
// IDA: Ped::sub_403950
// Ghidra: ---
void gta2::Ped_sub_403950(struct Ped *self)
{
  unsigned int Flags; // eax

  Flags = self->PositionX1;
  LOBYTE(Flags) = Flags | 4;
  self->PositionX1 = Flags;
}


// 0x00403960: Ped::sub_403960
// IDA: Ped::sub_403960
// Ghidra: ---
void gta2::Ped_sub_403960(struct Ped *self)
{
  unsigned int Flags; // eax

  Flags = self->PositionX1;
  LOBYTE(Flags) = Flags & 251;
  self->PositionX1 = Flags;
}


// 0x00403970: Ped::SetCurrentOccupation
// IDA: Ped::SetCurrentOccupation
// Ghidra: ---
void gta2::Ped_SetCurrentOccupation(struct Ped *self, ALL_PED occupation)
{
  self->OCCUPATION = (Occupation)occupation;
}


// 0x00403980: Ped::GetCurrentOccupation
// IDA: Ped::GetCurrentOccupation
// Ghidra: ---
ALL_PED gta2::Ped_GetCurrentOccupation(struct Ped *self)
{
  return (ALL_PED)self->OCCUPATION;
}


// 0x00403990: Ped::GetPedState
// IDA: Ped::GetPedState
// Ghidra: ---
int gta2::Ped_GetPedState(struct Ped *self)
{
  return self->field_214;
}


// 0x004039a0: Ped::SetHealth
// IDA: Ped::SetHealth
// Ghidra: ---
void gta2::Ped_SetHealth(struct Ped *self, __int16 HealthPlayer)
{
  HIWORD(self->PositionY) = HealthPlayer;
}


// 0x004039b0: Ped::SetTargetCarDoor
// IDA: Ped::SetTargetCarDoor
// Ghidra: ---
void gta2::Ped_SetTargetCarDoor(struct Ped *self, int a2)
{
  self->PositionZ1 = a2;
}


// 0x004039c0: Ped::GetTargetCarDoor
// IDA: Ped::GetTargetCarDoor
// Ghidra: ---
int gta2::Ped_GetTargetCarDoor(struct Ped *self)
{
  return self->PositionZ1;
}


// 0x004039d0: Ped::GetExitAnim
// IDA: Ped::GetExitAnim
// Ghidra: ---
unsigned __int8 gta2::Ped_GetExitAnim(struct Ped *self)
{
  return self->PedId;
}


// 0x004039e0: Ped::GetDamageState
// IDA: Ped::GetDamageState
// Ghidra: ---
char gta2::Ped_GetDamageState(struct Ped *self)
{
  return self->PedId;
}


// 0x004039f0: Ped::GetSub_4039F0
// IDA: Ped::GetSub_4039F0
// Ghidra: ---
unsigned __int16 gta2::Ped_GetSub_4039F0(struct Ped *self)
{
  return self->PedId;
}


// 0x00403a00: Ped::GetXCoordinate
// IDA: Ped::GetXCoordinate
// Ghidra: ---
int gta2::Ped_GetXCoordinate(struct Ped *self, void *X)
{
  int result; // eax

  result = (int)(intptr_t)X;
  *(_DWORD *)X = (int)(intptr_t)self->Driver;
  return result;
}


// 0x00403a10: Ped::GetYCoordinate
// IDA: Ped::GetYCoordinate
// Ghidra: ---
void gta2::Ped_GetYCoordinate(struct Ped *self, void *Y)
{
  *(_DWORD *)Y = (int)(intptr_t)self->LinkedPed;
}


// 0x00403a20: Ped::SetSub_403A20
// IDA: Ped::SetSub_403A20
// Ghidra: ---
void gta2::Ped_SetSub_403A20(struct Ped *self)
{
  self->X = 0;
}


// 0x00403a30: Ped::SetDefault
// IDA: Ped::SetDefault
// Ghidra: ---
void gta2::Ped_SetDefault(struct Ped *self)
{
  self->field_103 = 0;
  self->field_1D8 = 0;
}


// 0x00403a40: Ped::sub_403A40
// IDA: Ped::sub_403A40
// Ghidra: ---
void gta2::Ped_sub_403A40(struct Ped *self)
{
  unsigned int Flags; // eax

  Flags = self->PositionX1;
  BYTE1(Flags) &= ~8u;
  self->PositionX1 = Flags;
}


// 0x00403a50: Ped::sub_403A50
// IDA: Ped::sub_403A50
// Ghidra: ---
void gta2::Ped_sub_403A50(struct Ped *self, GameObject *a2)
{
  self->GameObject2->NextGameObject = a2;
}


// 0x00403a60: Ped::GetAnimationState
// IDA: Ped::GetAnimationState
// Ghidra: ---
char gta2::Ped_GetAnimationState(struct Ped *self)
{
  return self->field_1E8;
}


// 0x00403a70: Ped::SetAnimationState_0
// IDA: Ped::SetAnimationState_0
// Ghidra: ---
char gta2::Ped_SetAnimationState_0(struct Ped *self, char a2)
{
  char result; // al

  result = a2;
  self->field_1E8 = a2;
  return result;
}


// 0x00403a80: Ped::GetState
// IDA: Ped::GetState
// Ghidra: ---
int gta2::Ped_GetState(struct Ped *self)
{
  return self->field_1F4;
}


// 0x00403a90: Ped::GetCurrentAction
// IDA: Ped::GetCurrentAction
// Ghidra: ---
int gta2::Ped_GetCurrentAction(struct Ped *self)
{
  return self->CurrentAction1;
}


// 0x00403aa0: Ped::SetCurrentCar
// IDA: Ped::SetCurrentCar
// Ghidra: ---
int gta2::Ped_SetCurrentCar(struct Ped *self, Car *a2)
{
  int result; // eax

  result = (int)a2;
  *(Car **)&self->field_EF = a2;
  return result;
}


// 0x00403ab0: Ped::GetVehicle
// IDA: Ped::GetVehicle
// Ghidra: ---
Car * gta2::Ped_GetVehicle(struct Ped *self)
{
  return *(Car **)&self->field_EF;
}


// 0x00403ac0: Ped::SetDriverPed
// IDA: Ped::SetDriverPed
// Ghidra: ---
void gta2::Ped_SetDriverPed(struct Ped *self, Ped *a2)
{
  *(Ped **)&self->field_E7 = a2;
}


// 0x00403ad0: Ped::GetDriver
// IDA: Ped::GetDriver
// Ghidra: ---
Ped * gta2::Ped_GetDriver(struct Ped *self)
{
  return *(Ped **)&self->field_E7;
}


// 0x00403ae0: Ped::SetPed2
// IDA: Ped::SetPed2
// Ghidra: ---
void gta2::Ped_SetPed2(struct Ped *self, Ped *a2)
{
  *(Ped **)&self->field_EB = a2;
}


// 0x00403af0: Ped::GetLinkedPed
// IDA: Ped::GetLinkedPed
// Ghidra: ---
Ped * gta2::Ped_GetLinkedPed(struct Ped *self)
{
  return *(Ped **)&self->field_EB;
}


// 0x00403b00: Ped::SetCarPed
// IDA: Ped::SetCarPed
// Ghidra: ---
void gta2::Ped_SetCarPed(struct Ped *self, Car *pCar)
{
  *(Car **)&self->field_F3 = pCar;
}


// 0x00403b10: Ped::GetCurrentCar
// IDA: Ped::GetCurrentCar
// Ghidra: ---
Car * gta2::Ped_GetCurrentCar(struct Ped *self)
{
  return *(Car **)&self->field_F3;
}


// 0x00403b20: Ped::Get_sub_403B20
// IDA: Ped::Get_sub_403B20
// Ghidra: ---
__int16 gta2::Ped_Get_sub_403B20(struct Ped *self)
{
  return self->PedId;
}


// 0x00403b30: Ped::Get_sub_403B30
// IDA: Ped::Get_sub_403B30
// Ghidra: ---
__int16 gta2::Ped_Get_sub_403B30(struct Ped *self)
{
  return self->Camer_Z_View;
}


// 0x00403b40: Ped::sub_403B40
// IDA: Ped::sub_403B40
// Ghidra: ---
void gta2::Ped_sub_403B40(struct Ped *self, char a2)
{
  self->field_10B = a2;
}


// 0x00403b50: Ped::SetExitAnimState
// IDA: Ped::SetExitAnimState
// Ghidra: ---
void gta2::Ped_SetExitAnimState(struct Ped *self, char a2)
{
  self->field_10B = a2;
}


// 0x00403b60: Ped::GetDeadPed
// IDA: Ped::GetDeadPed
// Ghidra: ---
bool gta2::Ped_GetDeadPed(struct Ped *self)
{
  return self->field_214 == PEDSTATE_DEAD;
}


// 0x00403b70: Ped::GetGameObject
// IDA: Ped::GetGameObject
// Ghidra: ---
bool gta2::Ped_GetGameObject(struct Ped *self)
{
  return self->GameObject2 != 0;
}


// 0x00403b80: Ped::IsInCar
// IDA: Ped::IsInCar
// Ghidra: ---
bool gta2::Ped_IsInCar(struct Ped *self)
{
  return self->field_10B != 0;
}


// 0x00403b90: Ped::IsCrouching
// IDA: Ped::IsCrouching
// Ghidra: ---
unsigned __int8 gta2::Ped_IsCrouching(struct Ped *self)
{
  return (self->PositionX1 >> 2) & 1;
}











