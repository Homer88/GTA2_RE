#include "gta2_shim.h"

// Module: other, Class: PlayerData
// Functions: 10
// Source: unified (IDA+Ghidra)

// 0x004a87b0: PlayerData::sub_4A87B0
// IDA: PlayerData::sub_4A87B0
// Ghidra: ---
int gta2::PlayerData_sub_4A87B0(struct PlayerData *self)
{
  gta2::Construct_0(self->PlayerSlotSave_, 164, 8, PlayerSlotSave::PlayerSlotSave_des);
  return gta2::Construct_0(self->S151_arr, 240, 12, S151::S151_des);
}


// 0x004a88c0: PlayerData::FUN_004a88c0
// IDA: ---
// Ghidra: PlayerData::FUN_004a88c0
byte gta2::PlayerData_FUN_004a88c0(struct PlayerData *self,uint param_1)
{
  byte bVar1;
  undefined3 extraout_var;
  char local_27c [356];
  FileSave local_118 [11];
  
  gta2::FindFile_Plyslot(self,param_1,local_27c);
  bVar1 = gta2::Menu_FindFirstFile(local_27c,local_118);
  if ((HANDLE)CONCAT31(extraout_var,bVar1) == (HANDLE)0xffffffff) {
    return 0;
  }
  gta2::Crt_FindClose((HANDLE)CONCAT31(extraout_var,bVar1));
  return 1;
}


// 0x004a89e0: PlayerData::WriteFileNamePlayer
// IDA: PlayerData::WriteFileNamePlayer
// Ghidra: ---
int gta2::PlayerData_WriteFileNamePlayer(struct PlayerData *self, unsigned __int16 pPlayerSlotSave)
{
  int v3; // ebp
  char *v4; // ecx
  char *v5; // eax
  char *v6; // ecx
  __int16 *v7; // eax
  int v8; // esi
  char v9; // dl
  _DWORD *v10; // eax
  int a3; // [esp+Ch] [ebp-168h] BYREF
  CHAR FileName[356]; // [esp+10h] [ebp-164h] BYREF

  gta2::FindFile_Plyslot(pPlayerSlotSave, FileName);
  v3 = 3;
  a3 = 126;
  v4 = (char *)self + 164 * pPlayerSlotSave;
  v5 = v4 + 10032;
  v6 = v4 + 9896;
  self->field = *(_DWORD *)v5;
  self->field_4 = *((_DWORD *)v5 + 1);
  self->field_8 = *((_DWORD *)v5 + 2);
  self->field_C = *((_DWORD *)v5 + 3);
  self->field_10 = *((_WORD *)v5 + 8);
  v7 = &self->gap12;
  do
  {
    v8 = 4;
    do
    {
      v9 = *(v6 - 8);
      v6 += 12;
      *(_BYTE *)v7 = v9;
      v10 = (_DWORD *)((char *)v7 + 1);
      *v10++ = *((_DWORD *)v6 - 4);
      *v10 = *((_DWORD *)v6 - 3);
      v7 = (__int16 *)(v10 + 1);
      --v8;
    }
    while ( v8 );
    --v3;
  }
  while ( v3 );
  return gta2::WriteSub_402CF0(FileName, self, &a3);
}


// 0x004a8a90: PlayerData::sub_4A8A90
// IDA: PlayerData::sub_4A8A90
// Ghidra: ---
void gta2::PlayerData_sub_4A8A90(struct PlayerData *self, unsigned __int8 PlayerArena, unsigned __int8 a3)
{
  byte PlayerSlotSave; // al

  PlayerSlotSave = gta2::MapGm_GetPlayerSlotSave(&gMapGm);
  self->PlayerSlotSave_[PlayerSlotSave].ArenaSlots[PlayerArena].SubSlot[a3].BonusStage[0][0] = 1;
  if ( !gNetworkGame )
    gta2::PlayerData_WriteFileNamePlayer(self, PlayerSlotSave);
}


// 0x004a8b60: PlayerData::ReadHiscores
// IDA: PlayerData::ReadHiscores
// Ghidra: ---
void gta2::PlayerData_ReadHiscores(struct PlayerData *self, char *a2)
{
  strcpy(a2, "player\\hiscores.hsc");
}


// 0x004a8b80: PlayerData::sub_4A8B80
// IDA: PlayerData::sub_4A8B80
// Ghidra: ---
wchar_t * gta2::PlayerData_sub_4A8B80(struct PlayerData *self)
{
  wchar_t *result; // eax

  gta2::wcsncpy(self->S151_1.ALAN, L"ALAN", 9u);
  self->S151_1.field_14 = 1000000;
  gta2::wcsncpy(self->S151_1.BRIAN, L"BRIAN", 9u);
  self->S151_1.field_2C = 500000;
  gta2::wcsncpy(self->S151_1.COLIN, L"COLIN", 9u);
  self->S151_1.field_44 = 400000;
  gta2::wcsncpy(self->S151_1.DAVE, L"DAVE", 9u);
  self->S151_1.field_5C = 300000;
  gta2::wcsncpy(self->S151_1.ERIC, L"ERIC", 9u);
  self->S151_1.field_74 = 250000;
  gta2::wcsncpy(self->S151_1.FRANK, L"FRANK", 9u);
  self->S151_1.field_8C = 200000;
  gta2::wcsncpy(self->S151_1.Graeme, aGraeme, 9u);
  self->S151_1.field_A4 = 100000;
  gta2::wcsncpy(self->S151_1.HECTOR, L"HECTOR", 9u);
  self->S151_1.field_BC = 50000;
  gta2::wcsncpy(self->S151_1.IMOGEN, L"IMOGEN", 9u);
  self->S151_1.field_D4 = 25000;
  result = gta2::wcsncpy(self->S151_1.JACKSON, L"JACKSON", 9u);
  self->S151_1.field_EC = 10000;
  return result;
}


// 0x004a8d80: PlayerData::sub_4A8D80
// IDA: PlayerData::sub_4A8D80
// Ghidra: ---
int gta2::PlayerData_sub_4A8D80(struct PlayerData *self)
{
  S151 *pS151; // eax
  int *v3; // ebx
  S151 *S151_arr; // edx
  S151 *p1S151; // edi
  S151 *arr0x28; // edi
  wchar_t *v7; // eax
  byte *v8; // esi
  int v9; // ecx
  bool v10; // zf
  int Index; // [esp+10h] [ebp-110h] BYREF
  byte *arr_0x28; // [esp+14h] [ebp-10Ch]
  int index1; // [esp+18h] [ebp-108h]
  int v15; // [esp+1Ch] [ebp-104h]
  CHAR FileName[256]; // [esp+20h] [ebp-100h] BYREF

  gta2::PlayerData_ReadHiscores(self, FileName);
  pS151 = &self->s151;
  qmemcpy(self, &self->S151_, 240u);
  Index = 240;
  v3 = self->field_1884;
  arr_0x28 = self->arr_0x28;
  S151_arr = self->S151_arr;
  v15 = 3;
  do
  {
    index1 = 4;
    Index += 960;
    do
    {
      p1S151 = pS151++;
      qmemcpy(p1S151, S151_arr++, sizeof(S151));
      --index1;
    }
    while ( index1 );
    arr0x28 = pS151;
    v7 = &pS151->BRIAN[8];
    qmemcpy(arr0x28, arr_0x28, 0x28u);
    v8 = arr_0x28;
    *(_DWORD *)v7 = *(v3 - 3);
    v9 = *v3;
    v7 += 2;
    ++v3;
    *(_DWORD *)v7 = v9;
    pS151 = (S151 *)(v7 + 2);
    Index += 48;
    v10 = v15 == 1;
    arr_0x28 = v8 + 40;
    --v15;
  }
  while ( !v10 );
  return gta2::WriteSub_402CF0(FileName, self, &Index);
}


// 0x004a8f50: PlayerData::PlayerData_Des
// IDA: PlayerData::PlayerData_Des
// Ghidra: ---
void gta2::PlayerData_PlayerData_Des(struct PlayerData *self, char a2)
{
  gta2::PlayerData_sub_4A87B0(self);
  if ( (a2 & 1) != 0 )
    free(self);
}


// 0x004a8f90: PlayerData::sub_4A8F90
// IDA: PlayerData::sub_4A8F90
// Ghidra: ---
int gta2::PlayerData_sub_4A8F90(struct PlayerData *self, Player *pPlayer)
{
  byte PlayerSlotSave; // bl
  unsigned __int8 BonusStage; // al
  SubSlots *v5; // esi
  unsigned int Health; // eax
  _BYTE PlayerArena[4]; // [esp+Ch] [ebp-8h] BYREF
  unsigned __int8 a4[4]; // [esp+10h] [ebp-4h] BYREF

  PlayerSlotSave = gta2::MapGm_GetPlayerSlotSave(&gMapGm);
  a4[0] = PlayerSlotSave;
  if ( gta2::MapGm_GetGang(&gMapGm) )
  {
    BonusStage = gta2::MapGm_GetBonusStage(&gMapGm);
    gta2::MapGm_DecodeBonusStage(&gMapGm, BonusStage, PlayerArena, (unsigned __int8)a4);
  }
  else
  {
    PlayerArena[0] = gta2::MapGm_GetPlayerArena(&gMapGm);
    a4[0] = 0;
  }
  v5 = &self->PlayerSlotSave_[PlayerSlotSave].ArenaSlots[PlayerArena[0]].SubSlot[a4[0]];
  Health = gta2::PlayerStats_GetHealth((PlayerStats *)&pPlayer->Money);
  if ( Health > *(_DWORD *)&v5->BonusStage[1][0] )
    *(_DWORD *)&v5->BonusStage[1][0] = Health;
  *(_DWORD *)&v5->BonusStage[2][0] = Health;
  return gta2::PlayerData_WriteFileNamePlayer(self, PlayerSlotSave);
}


// 0x004a90a0: PlayerData::sub_4A90A0
// IDA: PlayerData::sub_4A90A0
// Ghidra: ---
char gta2::PlayerData_sub_4A90A0(struct PlayerData *self)
{
  unsigned __int8 BonusStage; // al
  byte PlayerSlotSave; // al
  int v4; // esi
  PlayerSlotSave *pPlayerSlotSave; // edi
  unsigned __int16 *PlayerName; // ebx
  char *v7; // eax
  unsigned __int8 v8; // bl
  byte *v9; // edi
  unsigned int v10; // eax
  unsigned int _45E5C0; // eax
  unsigned int _45E5E0; // eax
  char result; // al
  char v14; // [esp+5h] [ebp-Bh]
  char v15; // [esp+6h] [ebp-Ah]
  char v16; // [esp+7h] [ebp-9h]
  unsigned __int8 a4[4]; // [esp+8h] [ebp-8h] BYREF
  unsigned __int8 PlayerArena[4]; // [esp+Ch] [ebp-4h] BYREF

  v14 = 0;
  if ( gta2::MapGm_GetGang(&gMapGm) )
  {
    BonusStage = gta2::MapGm_GetBonusStage(&gMapGm);
    gta2::MapGm_DecodeBonusStage(&gMapGm, BonusStage, PlayerArena, (unsigned __int8)a4);
  }
  else
  {
    PlayerArena[0] = gta2::MapGm_GetPlayerArena(&gMapGm);
    a4[0] = 0;
  }
  PlayerSlotSave = gta2::MapGm_GetPlayerSlotSave(&gMapGm);
  v4 = PlayerArena[0];
  pPlayerSlotSave = &self->PlayerSlotSave_[PlayerSlotSave];
  PlayerName = self->PlayerSlotSave_[PlayerSlotSave].PlayerName;
  v15 = gta2::S151_sub_4A8630(
          &self->S151_arr[4 * PlayerArena[0] + a4[0]],
          PlayerName,
          *(char **)&pPlayerSlotSave->ArenaSlots_[PlayerArena[0]].SubSlot[a4[0]].BonusStage[2][0]);
  v7 = (char *)gta2::PlayerSlotSave_sub_4A8780(pPlayerSlotSave);
  v16 = gta2::S151_sub_4A8630(&self->S151_, PlayerName, v7);
  if ( !a4[0] )
  {
    v8 = 0;
    PlayerArena[0] = 0;
    v9 = &self->arr_0x28[40 * v4];
    do
    {
      v10 = gta2::MapGm_sub_45E590(&gMapGm, PlayerArena[0]);
      if ( v10 > *(_DWORD *)v9 )
      {
        *(_DWORD *)v9 = v10;
        v14 = 1;
      }
      ++v8;
      v9 += 4;
      PlayerArena[0] = v8;
    }
    while ( v8 < 0xAu );
    _45E5C0 = gta2::MapGm_Get_45E5C0(&gMapGm);
    if ( _45E5C0 > self->field_1878[v4] )
    {
      self->field_1878[v4] = _45E5C0;
      v14 = 1;
    }
    _45E5E0 = gta2::MapGm_Get_45E5E0(&gMapGm);
    if ( _45E5E0 > self->field_1884[v4] )
    {
      self->field_1884[v4] = _45E5E0;
      v14 = 1;
    }
  }
  if ( v15 )
    return gta2::PlayerData_sub_4A8D80(self);
  if ( v16 )
    return gta2::PlayerData_sub_4A8D80(self);
  result = v14;
  if ( v14 )
    return gta2::PlayerData_sub_4A8D80(self);
  return result;
}



