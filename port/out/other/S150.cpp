#include "gta2_shim.h"

// Module: other, Class: S150
// Functions: 5
// Source: unified (IDA+Ghidra)

// 0x004a8910: S150::sub_4A8910
// IDA: S150::sub_4A8910
// Ghidra: ---
int gta2::S150_sub_4A8910(struct PlayerData *self, unsigned __int16 a2)
{
  FILE *v2; // ebx
  FILE *v3; // esi
  int v4; // edi
  FILE *v5; // esi
  int v6; // edi
  struct FileMgr *v7; // ecx
  FileMgr v9; // [esp+10h] [ebp-16Ch] BYREF

  v2 = (FILE *)((char *)self + 164 * a2);
  gta2::FindFile_Plyslot(a2, (char *)&v9.field_8);
  gta2::FileMgr_FileOpen(&v9.field_8, (LPCSTR)&v9.field_8);
  v3 = v2 + 2508;
  v4 = 9;
  do
  {
    v9.File1 = (FILE *)2;
    gta2::FileMgr_Read(v3, (SIZE_T *)&v9.File1);
    v3 = (FILE *)((char *)v3 + 2);
    --v4;
  }
  while ( v4 );
  v5 = v2 + 2474;
  v9.File1 = (FILE *)3;
  do
  {
    v6 = 4;
    do
    {
      v9.FILE = (FILE *)1;
      gta2::FileMgr_Read(v5 - 2, (SIZE_T *)&v9);
      v9.FILE = (FILE *)4;
      gta2::FileMgr_Read(v5 - 1, (SIZE_T *)&v9);
      v9.FILE = (FILE *)4;
      gta2::FileMgr_Read(v5, (SIZE_T *)&v9);
      v5 += 3;
      --v6;
    }
    while ( v6 );
    --v9.File1;
  }
  while ( v9.File1 );
  return gta2::FileMgr_CloseFile(v7);
}


// 0x004a8b00: S150::sub_4A8B00
// IDA: S150::sub_4A8B00
// Ghidra: ---
byte gta2::S150_sub_4A8B00(struct PlayerData *self)
{
  byte pPlayerSlotSave; // al
  int v3; // esi
  struct PlayerSlotSave *v4; // ecx
  int v5; // edx

  pPlayerSlotSave = gta2::MapGm_GetPlayerSlotSave(&gMapGm);
  v3 = 3;
  v4 = &self->PlayerSlotSave_[pPlayerSlotSave];
  do
  {
    v5 = 4;
    do
    {
      v4->ArenaSlots_[0].SubSlot[0].BonusStage[0][0] = 1;
      v4 = (struct PlayerSlotSave *)((char *)v4 + 12);
      --v5;
    }
    while ( v5 );
    --v3;
  }
  while ( v3 );
  if ( !gNetworkGame )
    return gta2::PlayerData_WriteFileNamePlayer(self, pPlayerSlotSave);
  return pPlayerSlotSave;
}


// 0x004a8cb0: S150::sub_4A8CB0
// IDA: S150::sub_4A8CB0
// Ghidra: ---
int gta2::S150_sub_4A8CB0(struct PlayerData *self)
{
  int *v2; // edi
  byte *arr_0x28; // ebx
  struct S151 *S151_arr; // esi
  int v5; // ebp
  struct FileMgr *v6; // ecx
  FileMgr v8; // [esp+10h] [ebp-108h] BYREF

  gta2::PlayerData_ReadHiscores(self, (char *)&v8.field_8);
  gta2::FileMgr_FileOpen(&v8.field_8, (LPCSTR)&v8.field_8);
  v8.File1 = (FILE *)240;
  gta2::FileMgr_Read((FILE *)&self->S151_, (SIZE_T *)&v8.File1);
  v2 = self->field_1884;
  arr_0x28 = self->arr_0x28;
  S151_arr = self->S151_arr;
  v8.File1 = (FILE *)3;
  do
  {
    v5 = 4;
    do
    {
      v8.FILE = (FILE *)240;
      gta2::FileMgr_Read((FILE *)S151_arr++, (SIZE_T *)&v8);
      --v5;
    }
    while ( v5 );
    v8.FILE = (FILE *)40;
    gta2::FileMgr_Read((FILE *)arr_0x28, (SIZE_T *)&v8);
    v8.FILE = (FILE *)4;
    gta2::FileMgr_Read((FILE *)v2 - 3, (SIZE_T *)&v8);
    v8.FILE = (FILE *)4;
    gta2::FileMgr_Read((FILE *)v2++, (SIZE_T *)&v8);
    arr_0x28 += 40;
    --v8.File1;
  }
  while ( v8.File1 );
  return gta2::FileMgr_CloseFile(v6);
}


// 0x004a9050: S150::sub_4A9050
// IDA: S150::sub_4A9050
// Ghidra: ---
char gta2::S150_sub_4A9050(struct PlayerData *self)
{
  _FILETIME *v1; // esi
  void *v2; // eax
  CHAR FileName[356]; // [esp+0h] [ebp-27Ch] BYREF
  int v5[70]; // [esp+164h] [ebp-118h] BYREF

  gta2::PlayerData_ReadHiscores(self, FileName);
  v2 = (void *)gta2::sub_4D75CC(v1, FileName, (FileSave *)v5);
  if ( v2 == (void *)-1 )
    return 0;
  gta2::sub_4D7549(v2);
  return 1;
}


// 0x004a9290: S150::cFile
// IDA: S150::cFile
// Ghidra: ---
PlayerData * gta2::S150_cFile(struct PlayerData *self)
{
  int *v2; // edx
  byte *arr_0x28; // ebx
  int count; // ebp
  unsigned __int16 i; // di

  gta2::Construct(self->S151_arr, 240, 12, S151::S151, S151::S151_des);
  gta2::S151_S151(&self->S151_);
  gta2::S151_S151(&self->S151_1);
  gta2::S151_S151((struct S151 *)&self->S151_2);
  gta2::Construct(self->PlayerSlotSave_, 164, 8, S152::S152, PlayerSlotSave::PlayerSlotSave_des);
  v2 = self->field_1884;
  arr_0x28 = self->arr_0x28;
  count = 3;
  do
  {
    ++v2;
    memset(arr_0x28, 0, 0x28u);
    *(v2 - 4) = 0;
    *(v2 - 1) = 0;
    arr_0x28 += 40;
    --count;
  }
  while ( count );
  for ( i = 0; i < 8u; ++i )
  {
    if ( findFilePis((_FILETIME *)self, i) )
      gta2::S150_sub_4A8910(self, i);
    else
      gta2::PlayerData_WriteFileNamePlayer(self, i);
  }
  if ( gta2::S150_sub_4A9050(self) )
  {
    gta2::S150_sub_4A8CB0(self);
  }
  else
  {
    gta2::sub_4A8ED0(self);
    gta2::PlayerData_sub_4A8D80(self);
  }
  gta2::PlayerData_sub_4A8B80(self);
  return self;
}



