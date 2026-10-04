#include "gta2_shim.h"

// Module: other, Class: CarSystemManager
// Functions: 181
// Source: unified (IDA+Ghidra)

// 0x004764a0: CarSystemManager::sub_4764A0
// IDA: CarSystemManager::sub_4764A0
// Ghidra: FUN_004764a0
void gta2::CarSystemManager_sub_4764A0(CarSystemManager *param_1,int param_2,int param_3,int param_4, short param_5,byte param_6)
{
  gta2::CarSystemManager_ActualSpawnCar(param_1,param_2,param_3,param_4,param_5,param_6,_DAT_00664ebc);
  return;
}


// 0x00476610: CarSystemManager::sub_476610
// IDA: CarSystemManager::sub_476610
// Ghidra: ---
void gta2::CarSystemManager_sub_476610(struct CarSystemManager *self, Player **a2)
{
  self->Player_ = *a2;
  *(_DWORD *)&self->field_50 = a2[1];
}


// 0x00476630: CarSystemManager::sub_476630
// IDA: CarSystemManager::sub_476630
// Ghidra: ---
int gta2::CarSystemManager_sub_476630(struct CarSystemManager *self, int a2)
{
  int result; // eax

  result = a2;
  self->CarType = a2;
  return result;
}


// 0x00476640: CarSystemManager::sub_476640
// IDA: CarSystemManager::sub_476640
// Ghidra: FUN_00476640
undefined1 gta2::CarSystemManager_sub_476640(int param_1)
{
  return *(undefined1 *)(param_1 + 0x5c);
}


// 0x00476650: CarSystemManager::sub_476650
// IDA: CarSystemManager::sub_476650
// Ghidra: ---
int gta2::CarSystemManager_sub_476650(struct CarSystemManager *self, int a2)
{
  int result; // eax

  result = a2;
  self->Car = (struct Car *)a2;
  return result;
}


// 0x004c0a80: CarSystemManager::GetCar
// IDA: CarSystemManager::GetCar
// Ghidra: ---
Car * gta2::CarSystemManager_GetCar(struct CarSystemManager *self, int *x, SpriteS1 *y, __int16 rot, CarModel *pCarModel)
{
  struct SpriteS1 *v5; // edi
  int *MaxZForLocation; // eax

  v5 = y;
  MaxZForLocation = gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct, (int *)&y, x, (struct S202 *)y);
  return gta2::CarSystemManager_ActualSpawnCar(
           self,
           (int)x,
           (int)v5,
           *MaxZForLocation,
           rot,
           pCarModel,
           (struct Player *)unk_670F18.field_0);
}


// 0x004c39f0: CarSystemManager::sub_4C39F0
// IDA: CarSystemManager::sub_4C39F0
// Ghidra: ---
void gta2::CarSystemManager_sub_4C39F0(struct CarSystemManager *self)
{
  int v1; // edx

  v1 = -(self->field_24 != 1);
  self->field_20 = (self->field_20 != 4) + 3;
  self->field_24 = v1 + 2;
}


// 0x004e4df0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&stru_5D22FC.ID, a2);
}


// 0x004e4e10: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&stru_5D22FC.gap134[20], (__int16 *)&a2);
}


// 0x004e6c50: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_004e6c50
void gta2::CarSystemManager_sub_401C60(void)
{
  undefined4 local_4;
  
  local_4 = 0;
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)(gBufferSize + 0x13b8),(int)&local_4);
  return;
}


// 0x004e6c70: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_004e6c70
void gta2::CarSystemManager_sub_401C60(void)
{
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005d2e6c,0x56e510);
  return;
}


// 0x004ea000: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_5D3584, a2);
}


// 0x004ea020: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5D36CC, (__int16 *)&word_56E768);
}


// 0x004eb820: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5D3900, a2);
}


// 0x004eb840: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_5D5040, (__int16 *)&word_56E7C8);
}


// 0x004ec640: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_5D7EB4, a2);
}


// 0x004ec660: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5D7FF8, (__int16 *)&word_56E7E8);
}


// 0x004eddc0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5D8238, a2);
}


// 0x004edde0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5D837C, (__int16 *)&word_56E7F8);
}


// 0x004ef540: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5DC440, a2);
}


// 0x004ef560: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5DC584, (__int16 *)&word_56E808);
}


// 0x004f0d00: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5DC92C, a2);
}


// 0x004f0d20: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5DC8F8, (__int16 *)&word_56E818);
}


// 0x004f2510: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_004f2510
void gta2::CarSystemManager_sub_401C60(void)
{
  undefined4 local_4;
  
  local_4 = 0;
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)(gBaseNameBuffer + 0xb0),(int)&local_4);
  return;
}


// 0x004f2530: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_004f2530
void gta2::CarSystemManager_sub_401C60(void)
{
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e227c,0x56e990);
  return;
}


// 0x004f3cf0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E263C, a2);
}


// 0x004f3d10: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_5E2608, (__int16 *)&word_56E9A0);
}


// 0x004f5450: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E2868, a2);
}


// 0x004f5470: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E29AC, (__int16 *)&word_56E9B0);
}


// 0x004f6bf0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E2BFC, a2);
}


// 0x004f6c10: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E2D40, (__int16 *)&word_56E9C0);
}


// 0x004f8370: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E2F7C, a2);
}


// 0x004f8390: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E30C0, (__int16 *)&word_56E9D0);
}


// 0x004f9af0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E330C, a2);
}


// 0x004f9b10: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E3450, (__int16 *)&dword_56E9E0);
}


// 0x004fbbb0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_5E3990, a2);
}


// 0x004fbbd0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E3ADC, (__int16 *)&word_56EAF0);
}


// 0x004fd3d0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E3D30, a2);
}


// 0x004fd3f0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_5E3E88, (__int16 *)&word_56EB00);
}


// 0x004fece0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_004fece0
void gta2::CarSystemManager_sub_401C60(void)
{
  undefined4 local_4;
  
  local_4 = 0;
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&PTR_005e4d14,(int)&local_4)
  ;
  return;
}


// 0x004fed00: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_5E4E74, (__int16 *)&dword_56EB10);
}


// 0x005006c0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_005006c0
void gta2::CarSystemManager_sub_401C60(void)
{
  undefined4 local_4;
  
  local_4 = 0;
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&IndexCarManager,(int)&local_4);
  return;
}


// 0x005006e0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_005006e0
void gta2::CarSystemManager_sub_401C60(void)
{
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e5248,0x56eb60);
  return;
}


// 0x00501e50: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_00501e50
void gta2::CarSystemManager_sub_401C60(void)
{
  undefined4 local_4;
  
  local_4 = 0;
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e54e8,(int)&local_4)
  ;
  return;
}


// 0x00501e70: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_00501e70
void gta2::CarSystemManager_sub_401C60(void)
{
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e5620,0x56eb70);
  return;
}


// 0x005035f0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_005035f0
void gta2::CarSystemManager_sub_401C60(void)
{
  undefined4 local_4;
  
  local_4 = 0;
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e59c0,(int)&local_4)
  ;
  return;
}


// 0x00503610: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_00503610
void gta2::CarSystemManager_sub_401C60(void)
{
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e598c,0x56eb88);
  return;
}


// 0x00504d50: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_00504d50
void gta2::CarSystemManager_sub_401C60(void)
{
  undefined4 local_4;
  
  local_4 = 0;
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&gRotation,(int)&local_4);
  return;
}


// 0x00504d70: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_00504d70
void gta2::CarSystemManager_sub_401C60(void)
{
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e5db0,0x56eb98);
  return;
}


// 0x00506610: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_00506610
void gta2::CarSystemManager_sub_401C60(void)
{
  undefined4 local_4;
  
  local_4 = 0;
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e6018,(int)&local_4)
  ;
  return;
}


// 0x00506630: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_00506630
void gta2::CarSystemManager_sub_401C60(void)
{
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e615c,0x56ec30);
  return;
}


// 0x00507d90: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_00507d90
void gta2::CarSystemManager_sub_401C60(void)
{
  undefined4 local_4;
  
  local_4 = 0;
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e6388,(int)&local_4)
  ;
  return;
}


// 0x00507db0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_00507db0
void gta2::CarSystemManager_sub_401C60(void)
{
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e64a8,0x56ec40);
  return;
}


// 0x00509240: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_00509240
void gta2::CarSystemManager_sub_401C60(void)
{
  undefined4 local_4;
  
  local_4 = 0;
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e66f8,(int)&local_4)
  ;
  return;
}


// 0x00509260: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_00509260
void gta2::CarSystemManager_sub_401C60(void)
{
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e6840,0x56ec50);
  return;
}


// 0x0050a9d0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_0050a9d0
void gta2::CarSystemManager_sub_401C60(void)
{
  undefined4 local_4;
  
  local_4 = 0;
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e7254,(int)&local_4)
  ;
  return;
}


// 0x0050a9f0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_0050a9f0
void gta2::CarSystemManager_sub_401C60(void)
{
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e7328,0x56ec80);
  return;
}


// 0x0050b9d0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_0050b9d0
void gta2::CarSystemManager_sub_401C60(void)
{
  undefined4 local_4;
  
  local_4 = 0;
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e74f4,(int)&local_4)
  ;
  return;
}


// 0x0050b9f0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_0050b9f0
void gta2::CarSystemManager_sub_401C60(void)
{
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e7654,0x56ec90);
  return;
}


// 0x0050dd00: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_0050dd00
void gta2::CarSystemManager_sub_401C60(void)
{
  undefined4 local_4;
  
  local_4 = 0;
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e7a48,(int)&local_4)
  ;
  return;
}


// 0x0050dd20: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_0050dd20
void gta2::CarSystemManager_sub_401C60(void)
{
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_005e7b8c,0x56eca8);
  return;
}


// 0x0050f4a0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E7F2C, a2);
}


// 0x0050f4c0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E7EF8, (__int16 *)&word_56ECB8);
}


// 0x00510c90: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E8154, a2);
}


// 0x00510cb0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E8280, (__int16 *)&word_56ECC8);
}


// 0x00512b90: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E8604, a2);
}


// 0x00512bb0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E86E8, (__int16 *)&word_56ECE8);
}


// 0x00513cf0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E89D8, a2);
}


// 0x00513d10: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E89B0, (__int16 *)&word_56ECF8);
}


// 0x00515290: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_5E8BDC, a2);
}


// 0x005152b0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_5E8D20, (__int16 *)&word_56ED10);
}


// 0x00516a30: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_5E9168, a2);
}


// 0x00516a50: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_5E9134, (__int16 *)&word_56ED28);
}


// 0x00518230: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E93D4, a2);
}


// 0x00518250: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5E9518, (__int16 *)&word_56EE48);
}


// 0x005199d0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EA7D0, a2);
}


// 0x005199f0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EA7A8, (__int16 *)&word_56F000);
}


// 0x0051afb0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EAA28, a2);
}


// 0x0051afd0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EAB6C, (__int16 *)&word_572DC0);
}


// 0x0051d0a0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EB320, a2);
}


// 0x0051d0c0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EB2EC, (__int16 *)&word_573328);
}


// 0x0051e8b0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EB554, a2);
}


// 0x0051e8d0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EB6A4, (__int16 *)&dword_5736D0);
}


// 0x005200e0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EB8DC, a2);
}


// 0x00520100: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EB9C0, (__int16 *)&word_573848);
}


// 0x00521220: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EBB8C, a2);
}


// 0x00521240: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EBCD0, (__int16 *)&word_573860);
}


// 0x005229c0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EC068, a2);
}


// 0x005229e0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EC034, (__int16 *)&word_573870);
}


// 0x00524130: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EC80C, a2);
}


// 0x00524150: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_5EC960, (__int16 *)&word_5738E0);
}


// 0x00525970: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_661EDC, a2);
}


// 0x00525990: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_661FC4, (__int16 *)&word_573968);
}


// 0x005273f0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_6622EC, a2);
}


// 0x00527410: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_6623C0, (__int16 *)&word_573A80);
}


// 0x00528d70: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_662944, a2);
}


// 0x00528d90: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_662910, (__int16 *)&word_573AB0);
}


// 0x0052a570: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_662C64, a2);
}


// 0x0052a590: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_662DA8, (__int16 *)&word_573C48);
}


// 0x0052c260: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_663418, a2);
}


// 0x0052c280: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_663568, (__int16 *)&word_573C90);
}


// 0x0052d890: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_66378C, a2);
}


// 0x0052d8b0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_663874, (__int16 *)&word_573CA8);
}


// 0x0052ea00: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_663E40, a2);
}


// 0x0052ea20: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_663F84, (__int16 *)&word_573D00);
}


// 0x00530180: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_6641B8, a2);
}


// 0x005301a0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_6642E4, (__int16 *)&word_573D18);
}


// 0x00531740: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_664530, a2);
}


// 0x00531760: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_664E00, (__int16 *)&word_573F40);
}


// 0x00532fa0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_6650C4, a2);
}


// 0x00532fc0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_6651F0, (__int16 *)&word_574010);
}


// 0x00534560: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_665404, a2);
}


// 0x00534580: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66554C, (__int16 *)&word_574028);
}


// 0x00535d90: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)word_6657F8, a2);
}


// 0x00535db0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_665944, (__int16 *)&word_574048);
}


// 0x00537560: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_665B84, a2);
}


// 0x00537580: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&stru_669178.field_20, (__int16 *)&word_574060);
}


// 0x0053d1f0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_669C98, a2);
}


// 0x0053d210: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_669C64, (__int16 *)&word_574070);
}


// 0x0053e970: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_669EE0, a2);
}


// 0x0053e990: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_66A030, (__int16 *)&word_574088);
}


// 0x00540b10: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_66A434, a2);
}


// 0x00540b30: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_66A594, (__int16 *)&word_5740A8);
}


// 0x005424d0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66A844, a2);
}


// 0x005424f0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66A988, (__int16 *)&word_5740B8);
}


// 0x00543c50: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66AC08, a2);
}


// 0x00543c70: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66ADCC, (__int16 *)&word_5740C8);
}


// 0x00545960: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66B0C4, a2);
}


// 0x00545980: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66B20C, (__int16 *)&word_574308);
}


// 0x005471d0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_66B460, a2);
}


// 0x005471f0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66B5A4, (__int16 *)&word_574428);
}


// 0x00548950: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_66B804, a2);
}


// 0x00548970: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66B948, (__int16 *)&word_5744F8);
}


// 0x0054a100: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66BD10, a2);
}


// 0x0054a120: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66BCDC, (__int16 *)&word_574508);
}


// 0x0054b900: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66BF48, a2);
}


// 0x0054b920: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66C08C, (__int16 *)&word_574550);
}


// 0x0054d080: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66C2DC, a2);
}


// 0x0054d0a0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_66C428, (__int16 *)&word_574560);
}


// 0x0054f1e0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66C808, a2);
}


// 0x0054f200: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66C94C, (__int16 *)&word_574690);
}


// 0x00550980: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66F2A8, a2);
}


// 0x005509a0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66F3F0, (__int16 *)&word_575370);
}


// 0x005521c0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: FUN_005521c0
void gta2::CarSystemManager_sub_401C60(void)
{
  undefined4 local_4;
  
  local_4 = 0;
  gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&DAT_0066f7a0,(int)&local_4)
  ;
  return;
}


// 0x005521e0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66F76C, (__int16 *)&word_5753D8);
}


// 0x005543c0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66FB54, a2);
}


// 0x005543e0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_66FC74, (__int16 *)&word_5753E8);
}


// 0x00555870: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)unk_66FF7C, a2);
}


// 0x00555890: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_6700D0, (__int16 *)&word_5753F8);
}


// 0x00557090: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_670318, a2);
}


// 0x005570b0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_67045C, (__int16 *)&word_575440);
}


// 0x00558810: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_6706B8, a2);
}


// 0x00558830: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_67078C, (__int16 *)&word_575450);
}


// 0x00559830: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_670A94, a2);
}


// 0x00559850: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_670A60, (__int16 *)&word_5754F0);
}


// 0x0055af90: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_670D14, a2);
}


// 0x0055afb0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_670E5C, (__int16 *)&word_575508);
}


// 0x0055c7c0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_67159C, a2);
}


// 0x0055c7e0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_6716C8, (__int16 *)&word_575530);
}


// 0x0055dd80: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_6719BC, a2);
}


// 0x0055dda0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_671AA0, (__int16 *)&word_575580);
}


// 0x0055eec0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_671C50, a2);
}


// 0x0055eee0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_671D34, (__int16 *)&word_575590);
}


// 0x00560000: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_671EEC, a2);
}


// 0x00560020: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_672018, (__int16 *)&word_5755B0);
}


// 0x005615d0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_672230, a2);
}


// 0x005615f0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_67237C, (__int16 *)&word_5755F0);
}


// 0x00562e60: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_6725C0, a2);
}


// 0x00562e80: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_6726A4, (__int16 *)&word_575650);
}


// 0x00563fa0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_672868, a2);
}


// 0x00563fc0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&unk_6729AC, (__int16 *)&word_575660);
}


// 0x00565720: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_672BEC, a2);
}


// 0x00565740: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_672D30, (__int16 *)&word_575670);
}


// 0x00566ea0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_672F98, a2);
}


// 0x00566ec0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_6730EC, (__int16 *)&word_575680);
}


// 0x005686e0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_673600, a2);
}


// 0x00568700: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_673754, (__int16 *)&word_5757F0);
}


// 0x00569f00: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_6739B0, a2);
}


// 0x00569f20: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_673B18, (__int16 *)&word_575900);
}


// 0x0056b890: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60(&unk_673FB0, a2);
}


// 0x0056b8b0: CarSystemManager::sub_401C60
// IDA: CarSystemManager::sub_401C60
// Ghidra: ---
  return gta2::CarSystemManager_sub_401C60((struct CarSystemManager *)&stru_6740B8.Player, (__int16 *)&word_575950);
}



