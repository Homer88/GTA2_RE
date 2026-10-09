#include "gta2_shim.h"

// Module: other, Class: MissionManager
// Functions: 40
// Source: unified (IDA+Ghidra)

// 0x00474f00: MissionManager::sub_474F00
// IDA: MissionManager::sub_474F00
// Ghidra: ---
_WORD * gta2::MissionManager_sub_474F00(MissionManager *self, __int16 a2)
{
  void *v2; // ecx
  int v3; // edx
  _WORD *result; // eax

  v2 = self->EVENT_LOG_SIZE[1];
  v3 = 0;
  result = (_WORD *)*((_DWORD *)v2 + 1);
  if ( !result )
    return 0;
  while ( *result != a2 )
  {
    result = (_WORD *)*((_DWORD *)v2 + (unsigned __int16)++v3 + 1);
    if ( !result )
      return 0;
  }
  return result;
}


// 0x00474f30: MissionManager::sub_474F30
// IDA: MissionManager::sub_474F30
// Ghidra: FUN_00474f30
int gta2::MissionManager_sub_474F30(int param_1,char *param_2)
{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  iVar1 = *(int *)(*(int *)(param_1 + 0x13350) + 4);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    iVar2 = __strnicmp(param_2,(char *)(iVar1 + 9),(uint)*(byte *)(iVar1 + 8));
    if (iVar2 == 0) break;
    uVar3 = uVar3 + 1;
    iVar1 = *(int *)(*(int *)(param_1 + 0x13350) + 4 + (uVar3 & 0xffff) * 4);
  }
  return iVar1;
}


// 0x00475a20: MissionManager::sub_475A20
// IDA: MissionManager::sub_475A20
// Ghidra: ---
bool gta2::MissionManager_sub_475A20(MissionManager *self)
{
  return self->Bool_A;
}


// 0x00475a30: MissionManager::sub_475A30
// IDA: MissionManager::sub_475A30
// Ghidra: ---
char gta2::MissionManager_sub_475A30(MissionManager *self)
{
  return self->field_C1E2D;
}


// 0x00475a40: MissionManager::sub_475A40
// IDA: MissionManager::sub_475A40
// Ghidra: ---
void gta2::MissionManager_sub_475A40(MissionManager *self, char a2)
{
  self->field_C1E2D = a2;
}


// 0x00475ca0: MissionManager::sub_475CA0
// IDA: MissionManager::sub_475CA0
// Ghidra: ---
int gta2::MissionManager_sub_475CA0(MissionManager *self)
{
  int result; // eax

  strcpy(unk_664590, gta2::MapGm_GetMapName(&gMapGm));
  strcpy(byte_6645A9, gta2::MapGm_GetStyleFile(&gMapGm));
  strcpy(byte_6645C2, gta2::MapGm_GetScriptName(&gMapGm));
  unk_6645A8 = 10;
  unk_6645C1 = 10;
  unk_6645DA = 10;
  unk_6645DB = gta2::MapGm_GetPlayerArena(&gMapGm);
  unk_6645DC = gta2::MapGm_GetBonusStage(&gMapGm);
  LOBYTE(result) = gta2::MapGm_GetGang(&gMapGm);
  unk_6645DD = result;
  return result;
}


// 0x00475d30: MissionManager::sub_475D30
// IDA: MissionManager::sub_475D30
// Ghidra: FUN_00475d30
void gta2::MissionManager_sub_475D30(int param_1,uint param_2)
{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 *puVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  
  uVar8 = 0;
  param_2 = param_2 & 0xffff;
  iVar7 = *(int *)(param_1 + 0x1334c);
  if (param_2 != 0) {
    do {
      iVar3 = *(byte *)(iVar7 + 8) + 9;
      uVar8 = uVar8 + iVar3;
      iVar7 = iVar7 + iVar3;
    } while (uVar8 < param_2);
  }
  puVar4 = (undefined4 *)CreateBuffer(4000);
  *(undefined4 **)(param_1 + 0x13350) = puVar4;
  for (iVar7 = 1000; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  iVar7 = *(int *)(param_1 + 0x1334c);
  iVar3 = 0;
  uVar8 = 0;
  if (param_2 != 0) {
    do {
      pcVar5 = (char *)(iVar7 + 9);
      do {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      uVar2 = FUN_00464d00((char *)(iVar7 + 9),(int)pcVar5 - (iVar7 + 10));
      *(undefined2 *)(iVar7 + 2) = uVar2;
      *(int *)(*(int *)(param_1 + 0x13350) + 4 + iVar3 * 4) = iVar7;
      iVar6 = *(byte *)(iVar7 + 8) + 9;
      uVar8 = uVar8 + iVar6;
      iVar7 = iVar7 + iVar6;
      iVar3 = iVar3 + 1;
    } while (uVar8 < param_2);
    **(undefined2 **)(param_1 + 0x13350) = (short)iVar3;
    return;
  }
  **(undefined2 **)(param_1 + 0x13350) = 0;
  return;
}


// 0x00475e00: MissionManager::ExtractFileNameWithoutExtension
// IDA: MissionManager::ExtractFileNameWithoutExtension
// Ghidra: ---
char * gta2::MissionManager_ExtractFileNameWithoutExtension(MissionManager *self)
{
  char *result; // eax
  char *Name; // edi
  size_t v4; // ecx

  result = gta2::strrchr(self->pathToScriptFile, '\\');
  if ( result )
  {
    Name = self->Name;
    ++result;
    *(_DWORD *)self->Name = 0;
    self->field_460 = 0;
    self->field_464 = 0;
    v4 = strlen(result);
    if ( v4 )
    {
      while ( result[v4] != '.' )
      {
        if ( !--v4 )
          return result;
      }
      return strncpy(Name, result, v4);
    }
  }
  return result;
}


// 0x00475e90: MissionManager::sub_475E90
// IDA: MissionManager::sub_475E90
// Ghidra: ---
__int16 gta2::MissionManager_sub_475E90(MissionManager *self, FileMgr *a2)
{
  void *v3; // ecx
  FileMgr *v4; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // edx
  int size; // [esp+Ch] [ebp-8h] BYREF
  FILE v10; // [esp+10h] [ebp-4h] BYREF
  FILE *v11; // [esp+1Ch] [ebp+8h]

  size = 0;
  if ( gMissionManager->shouldBeEqTo1 )
  {
    v6 = gta2::MissionManager_sub_474F30(gMissionManager, (const char *)a2);
    v7 = *(unsigned __int16 *)(v6 + 2);
    LOWORD(v8) = *((_WORD *)gMissionManager->BaseScriptMaxPointers + v7);
    size = v8;
    LOWORD(v11->_Placeholder) = *((_WORD *)gMissionManager->arr_15 + v7);
    qmemcpy(
      (char *)gMissionManager->OBJECTIVE_DATA_SIZE + 2 * (unsigned __int16)v8,
      &gMissionManager->arr_23808[768 * v7],
      0xC00u);
    qmemcpy(
      (char *)gMissionManager->Script
    + *((unsigned __int16 *)gMissionManager->OBJECTIVE_DATA_SIZE + (unsigned __int16)size),
      &gMissionManager->EVENT_LOG_SIZE[5000 * *(__int16 *)(v6 + 2) + 2],
      gMissionManager->MissionScriptSize[*(__int16 *)(v6 + 2)]);
  }
  else
  {
    strcpy(gStr, "data\\");
    strcat(gStr, (const char *)a2);
    gta2::FileMgr_SetFilePath(gStr);
    gta2::FileMgr_FileOpen(v3, gStr);
    a2 = (FileMgr *)2;
    gta2::FileMgr_Read((FILE *)&size, (SIZE_T *)&a2);
    a2 = (FileMgr *)2;
    gta2::FileMgr_Read(v11, (SIZE_T *)&a2);
    a2 = (FileMgr *)4;
    gta2::FileMgr_Read(&v10, (SIZE_T *)&a2);
    a2 = (FileMgr *)3072;
    gta2::FileMgr_Read((FILE *)((char *)self->OBJECTIVE_DATA_SIZE + 2 * (unsigned __int16)size), (SIZE_T *)&a2);
    partOfLoadScrip(
      (char *)self->Script + *((unsigned __int16 *)self->OBJECTIVE_DATA_SIZE + (unsigned __int16)size),
      (int *)&v10);
    gta2::FileMgr_CloseFile(v4);
  }
  return size;
}


// 0x00476070: MissionManager::sub_476070
// IDA: MissionManager::sub_476070
// Ghidra: FUN_00476070
void gta2::MissionManager_sub_476070(int param_1)
{
  int iVar1;
  int *piVar2;
  char cVar3;
  int iVar4;
  ushort *puVar5;
  char *pcVar6;
  FileMgr *self;
  FileMgr *this_00;
  uint uVar7;
  undefined2 local_14 [2];
  uint local_10;
  uint local_c;
  int local_8;
  int local_4;
  
  local_10 = 0;
  local_c = 0;
  puVar5 = *(ushort **)(param_1 + 0x13350);
  if (*puVar5 != 0) {
    do {
      iVar4 = *(int *)(puVar5 + (local_c & 0xffff) * 2 + 2);
      if (*(char *)(iVar4 + 4) == '\x15') {
        iVar1 = iVar4 + 10;
        pcVar6 = (char *)(iVar4 + 9);
        do {
          cVar3 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar3 != '\0');
        pcVar6[iVar4 + (6 - iVar1)] = 'S';
        pcVar6[iVar4 + (7 - iVar1)] = 'C';
        pcVar6[iVar4 + (8 - iVar1)] = 'R';
        if (*(int *)(param_1 + 0x2f4) == 1) {
          strcpy((char *)&gLanguage,"data\\%s\\",(char *)(param_1 + 0x45c));
          gta2::_strncat((char *)&gLanguage,(char *)(iVar4 + 9),
                   (uint)*(byte *)(iVar4 + 8));
          gta2::FileMgr_FileOpen(self,(char *)&gLanguage);
          local_8 = 2;
          gta2::FileMgr_Read((FileMgr *)&local_8,(size_t)local_14);
          uVar7 = local_10 & 0xffff;
          *(undefined2 *)(param_1 + 0xc1d72 + uVar7 * 2) = local_14[0];
          local_8 = 2;
          gta2::FileMgr_Read((FileMgr *)&local_8,(size_t)local_14);
          *(undefined2 *)(param_1 + 0xc1d34 + uVar7 * 2) = local_14[0];
          local_8 = 4;
          gta2::FileMgr_Read((FileMgr *)&local_8,(size_t)&local_4);
          piVar2 = (int *)(param_1 + 0xc1db0 + uVar7 * 4);
          *piVar2 = local_4;
          local_8 = 0xc00;
          gta2::FileMgr_Read((FileMgr *)&local_8,uVar7 * 0xc00 + 0xaa934 + param_1);
          FUN_00403040(uVar7 * 20000 + 0x13354 + param_1,piVar2);
          gta2::FileMgr_CloseFile(this_00);
          *(short *)(iVar4 + 2) = (short)local_10;
          local_10 = local_10 + 1;
        }
      }
      puVar5 = *(ushort **)(param_1 + 0x13350);
      local_c = local_c + 1;
    } while ((ushort)local_c < *puVar5);
  }
  return;
}


// 0x00476200: MissionManager::StartMission
// IDA: MissionManager::StartMission
// Ghidra: ---
MissionManager * gta2::MissionManager_StartMission(MissionManager *self, unsigned __int16 a2)
{
  if ( *((_WORD *)self->OBJECTIVE_DATA_SIZE + a2) )
    return (MissionManager *)((char *)self->Script + *((unsigned __int16 *)self->OBJECTIVE_DATA_SIZE + a2));
  else
    return 0;
}


// 0x00476240: MissionManager::sub_476240
// IDA: MissionManager::sub_476240
// Ghidra: ---
int * gta2::MissionManager_sub_476240(MissionManager *self, int a2, int a3)
{
  int *result; // eax
  int v4; // ecx

  result = self->arr_96;
  v4 = 0;
  while ( *result != a2 || result[1] != a3 )
  {
    result += 3;
    if ( (unsigned __int16)++v4 >= 0x20u )
      return 0;
  }
  return result;
}


// 0x00476280: MissionManager::sub_476280
// IDA: MissionManager::sub_476280
// Ghidra: FUN_00476280
void gta2::MissionManager_sub_476280(void *self,undefined4 param_1,undefined4 param_2,short param_3)
{
  undefined4 *puVar1;
  ushort uVar2;
  
  puVar1 = (undefined4 *)((int)self + 4);
  uVar2 = 0;
  do {
    if (*(short *)(puVar1 + 2) == 0) break;
    puVar1 = puVar1 + 3;
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x20);
  *puVar1 = param_1;
  puVar1[1] = param_2;
  *(short *)(puVar1 + 2) = param_3;
                              // WARNING: Load size is inaccurate
  *(short *)self = *self + 1;
  return;
}


// 0x00476320: MissionManager::sub_476320
// IDA: MissionManager::sub_476320
// Ghidra: MissionManager::FUN_00476320
int * gta2::MissionManager_sub_476320(MissionManager *self,int param_1,int param_2)
{
  uint32_t *puVar1;
  ushort uVar2;
  
  puVar1 = self->runtime_cache;
  uVar2 = 0;
  while ((*puVar1 != param_1 || (puVar1[1] != param_2))) {
    puVar1 = puVar1 + 3;
    uVar2 = uVar2 + 1;
    if (0x13 < uVar2) {
      return NULL;
    }
  }
  return (int *)puVar1;
}


// 0x00476370: MissionManager::sub_476370
// IDA: MissionManager::sub_476370
// Ghidra: ---
int * gta2::MissionManager_sub_476370(MissionManager *self, int a2, int a3, __int16 a4)
{
  int *result; // eax
  int v5; // edx

  result = self->RuntimeCache;
  v5 = 0;
  do
  {
    if ( !*((_WORD *)result + 4) )
      break;
    result += 3;
    ++v5;
  }
  while ( (unsigned __int16)v5 < 0x14u );
  *result = a2;
  result[1] = a3;
  *((_WORD *)result + 4) = a4;
  ++self->field_184;
  return result;
}


// 0x004763b0: MissionManager::sub_4763B0
// IDA: MissionManager::sub_4763B0
// Ghidra: MissionManager::FUN_004763b0
void gta2::MissionManager_sub_4763B0(MissionManager *self,int param_1,int param_2)
{
  int *piVar1;
  
  piVar1 = gta2::MissionManager_sub_476320(self,param_1,param_2);
  if (piVar1 != NULL) {
    *piVar1 = 0;
    piVar1[1] = 0;
    *(undefined2 *)(piVar1 + 2) = 0;
    self->field4_0x184 = self->field4_0x184 + -1;
  }
  return;
}


// 0x004763e0: MissionManager::sub_4763E0
// IDA: MissionManager::sub_4763E0
// Ghidra: MissionManager::FUN_004763e0
int gta2::MissionManager_sub_4763E0(MissionManager *self,int param_1)
{
  uint32_t *puVar1;
  ushort uVar2;
  
  puVar1 = self->runtime_cache;
  uVar2 = 0;
  do {
    if (puVar1[1] == param_1) {
      return (int)puVar1;
    }
    puVar1 = puVar1 + 3;
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x14);
  return 0;
}


// 0x00476400: MissionManager::sub_476400
// IDA: MissionManager::sub_476400
// Ghidra: FUN_00476400
undefined4 gta2::MissionManager_sub_476400(void *self,int param_2,char param_3,char param_4)
{
  char cVar1;
  byte bVar2;
  int *piVar3;
  int *piVar4;
  
  piVar4 = NULL;
  piVar3 = (int *)((int)self + 0x27c);
  bVar2 = 0;
  do {
    if (((*piVar3 == 0) && ((char)piVar3[1] == '\0')) && (piVar4 == NULL)) {
      piVar4 = piVar3;
    }
    if (*piVar3 == param_2) {
      if (((char)piVar3[1] == param_3) || ((char)piVar3[1] == '\x17')) {
        if (param_4 == '\0') {
          cVar1 = FUN_004759a0((int)piVar3);
        }
        else {
          cVar1 = FUN_004759c0(piVar3);
        }
        if (cVar1 != '\0') {
          return 1;
        }
      }
    }
    piVar3 = piVar3 + 2;
    bVar2 = bVar2 + 1;
    if (0xe < bVar2) {
      if (piVar4 != NULL) {
        *(char *)(piVar4 + 1) = param_3;
        *piVar4 = param_2;
        *(char *)((int)piVar4 + 6) = (param_4 != '\0') * '\x02' + '\x02';
        *(short *)((int)self + 0x278) = *(short *)((int)self + 0x278) + 1;
      }
      return 0;
    }
  } while( true );
}


// 0x004764d0: MissionManager::sub_4764D0
// IDA: MissionManager::sub_4764D0
// Ghidra: ---
char gta2::MissionManager_sub_4764D0(MissionManager *self, int a2, char a3)
{
  int v4; // ebp
  int *arr_30; // esi
  char result; // al

  v4 = 15;
  arr_30 = self->arr_30;
  do
  {
    result = a2;
    if ( *arr_30 != a2 )
      goto LABEL_8;
    if ( !a3 )
    {
      result = sub_4759A0(arr_30);
      if ( !result )
        goto LABEL_8;
LABEL_7:
      *arr_30 = 0;
      *((_BYTE *)arr_30 + 4) = 0;
      *((_BYTE *)arr_30 + 5) = 0;
      *((_BYTE *)arr_30 + 6) = 0;
      --self->field_278;
      goto LABEL_8;
    }
    result = sub_4759C0(arr_30);
    if ( result )
      goto LABEL_7;
LABEL_8:
    arr_30 += 2;
    --v4;
  }
  while ( v4 );
  return result;
}


// 0x00476530: MissionManager::sub_476530
// IDA: MissionManager::sub_476530
// Ghidra: ---
char gta2::MissionManager_sub_476530(MissionManager *self, int a2, int a3, char a4)
{
  int *arr_30; // esi
  char result; // al
  char v6; // bl
  char v7; // cl
  char v8; // al

  arr_30 = self->arr_30;
  result = gta2::sub_44AB80(a3);
  v6 = result;
  v7 = 0;
  while ( 1 )
  {
    if ( *arr_30 == a2 )
    {
      result = *((_BYTE *)arr_30 + 4);
      if ( result == 23 || result == v6 )
        break;
    }
    arr_30 += 2;
    if ( (unsigned __int8)++v7 >= 0xFu )
      return result;
  }
  if ( !a4 )
  {
    result = sub_4759A0(arr_30);
    if ( !result )
      return result;
    goto LABEL_11;
  }
  result = sub_4759C0(arr_30);
  if ( result )
  {
LABEL_11:
    v8 = *((_BYTE *)arr_30 + 6);
    *((_BYTE *)arr_30 + 5) = v6;
    result = v8 | 1;
    *((_BYTE *)arr_30 + 6) = result;
  }
  return result;
}


// 0x004765a0: MissionManager::sub_4765A0
// IDA: MissionManager::sub_4765A0
// Ghidra: FUN_004765a0
undefined1 gta2::MissionManager_sub_4765A0(void *self,int param_2,char param_3,char param_4)
{
  char cVar1;
  undefined1 uVar2;
  byte bVar3;
  int *piVar4;
  
  bVar3 = 0;
  piVar4 = (int *)((int)self + 0x27c);
  do {
    if ((*piVar4 == param_2) &&
       (((char)piVar4[1] == param_3 || ((char)piVar4[1] == '\x17')))) {
      if (param_4 == '\0') {
        cVar1 = FUN_004759a0((int)piVar4);
      }
      else {
        cVar1 = FUN_004759c0(piVar4);
      }
      if (cVar1 != '\0') {
        uVar2 = FUN_00475980(piVar4);
        return uVar2;
      }
    }
    piVar4 = piVar4 + 2;
    bVar3 = bVar3 + 1;
    if (0xe < bVar3) {
      return 0;
    }
  } while( true );
}


// 0x004799d0: MissionManager::sub_4799D0
// IDA: MissionManager::sub_4799D0
// Ghidra: ---
_DWORD gta2::MissionManager_sub_4799D0(MissionManager *a1)
{
  MissionScriptObjectData *v1; // ecx
  MissionManager *v2; // esi
  int *v3; // edi
  _DWORD *started; // ebp
  void *v5; // eax
  void *v6; // eax
  SpriteS1 *v7; // eax
  int *v8; // ebx
  int *v9; // eax
  int v10; // eax
  int result; // eax
  MissionManager *v12; // [esp-4h] [ebp-2Ch]
  MissionScriptObjectData *v13; // [esp+10h] [ebp-18h]
  _BYTE a2[4]; // [esp+18h] [ebp-10h] BYREF
  char v15; // [esp+1Ch] [ebp-Ch] BYREF
  char v16; // [esp+20h] [ebp-8h] BYREF
  char v17; // [esp+24h] [ebp-4h] BYREF

  v2 = dword_6644CC;
  v13 = v1;
  v3 = &dword_6644CC->arr_96[6];
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  v5 = gta2::sub_401B90(v3, a2, &unk_664DC4);
  gta2::Player_sub_401B40((Player *)&v2->arr_96[3], (S202 *)&v15, (int)v5);
  v6 = gta2::sub_401B90(&v2->arr_96[5], &v16, &unk_664DC4);
  v7 = gta2::Player_sub_401B40((Player *)&v2->arr_96[2], (S202 *)&v17, (int)v6);
  gta2::AudioSourceParams_sub_463710(&gMissionManager->S9, v7->FirstElement);
  v8 = (int *)gta2::S202_sub_401B20((S202 *)&v2->arr_96[4], (SpriteS1 *)&v17, (PublicTransport *)&unk_664E08);
  v9 = (int *)gta2::Player_sub_401B40((Player *)&v2->arr_96[4], (S202 *)&v16, (int)&unk_664E08);
  gta2::AudioSourceParams_sub_41E370(&gMissionManager->S9, *v9, *v8);
  v10 = started[2];
  if ( v10 && *(_DWORD *)(v10 + 136) != 6 )
  {
    if ( gta2::SpriteS1_sub_4BB020(*(SpriteS1 **)(v10 + 80), (Ped *)&gMissionManager->S9)
      || gta2::sub_4BA6C0(&gMissionManager->S9, *(SpriteS1 **)(started[2] + 80)) )
    {
      v12 = dword_6644CC;
      v13->field_8 = 1;
      gta2::MissionScriptObjectData_sub_476E50(v13, v12);
      return result;
    }
    v2 = dword_6644CC;
  }
  v13->field_8 = 0;
  gta2::MissionScriptObjectData_sub_476E50(v13, v2);
  return result;
}


// 0x0047ed20: MissionManager::sub_47ED20
// IDA: MissionManager::sub_47ED20
// Ghidra: FUN_0047ed20
void gta2::MissionManager_sub_47ED20(uint param_1,undefined4 param_2)
{
  byte *pbVar1;
  byte bVar2;
  undefined4 uVar3;
  
  bVar2 = 0;
  pbVar1 = (byte *)gMissionManager->field49_0x340;
  do {
    if (param_1 == *pbVar1) {
      FUN_00476950(param_2,s_ABCDEFGHI___abcdefg_005931fc[bVar2]);
      if ((byte)s_ABCDEFGHI___abcdefg_005931fc[bVar2] < 0x5b) {
        uVar3 = 3;
      }
      else {
        uVar3 = 1;
      }
      FUN_00476930(param_2,uVar3);
      break;
    }
    pbVar1 = pbVar1 + 1;
    bVar2 = bVar2 + 1;
  } while (bVar2 < 0x13);
  if (bVar2 == 0x13) {
    FUN_00476930(param_2,3);
    FUN_00476950(param_2,0x41);
  }
  return;
}


// 0x0047edb0: MissionManager::sub_47EDB0
// IDA: MissionManager::sub_47EDB0
// Ghidra: ---
char gta2::MissionManager_sub_47EDB0(MissionManager *self, int a2)
{
  MissionManager *started; // esi
  int *v4; // eax
  int *v5; // ebx
  S202 *v6; // eax
  SpriteS1 *v7; // ebp
  S202 *v8; // eax
  SpriteS1 *v9; // eax
  MissionManager *v10; // eax
  int v12; // [esp-14h] [ebp-3Ch]
  int FirstElement; // [esp-10h] [ebp-38h]
  int v14; // [esp-Ch] [ebp-34h]
  int v15; // [esp-8h] [ebp-30h]
  int v16; // [esp-4h] [ebp-2Ch]
  int v17; // [esp+10h] [ebp-18h] BYREF
  int v18; // [esp+14h] [ebp-14h] BYREF
  char v19; // [esp+18h] [ebp-10h] BYREF
  int v20; // [esp+1Ch] [ebp-Ch] BYREF
  char v21; // [esp+20h] [ebp-8h] BYREF
  int v22; // [esp+24h] [ebp-4h] BYREF

  started = gta2::MissionManager_StartMission(self, a2);
  a2 = 3;
  v17 = 1;
  gta2::S202_sub_40CE30((S202 *)&v18, BYTE2(started->arr_96[2]));
  v5 = v4;
  gta2::S202_sub_40CE30((S202 *)&v20, BYTE1(started->arr_96[2]));
  v7 = gta2::S202_sub_401B20(v6, (SpriteS1 *)&v19, (PublicTransport *)&unk_664E08);
  gta2::S202_sub_40CE30((S202 *)&v22, started->arr_96[2]);
  v9 = gta2::S202_sub_401B20(v8, (SpriteS1 *)&v21, (PublicTransport *)&unk_664E08);
  v16 = unk_664E08.field_0;
  v15 = unk_664E08.field_0;
  v14 = *v5;
  FirstElement = (int)v7->FirstElement;
  v12 = (int)v9->FirstElement;
  v10 = gta2::MissionManager_StartMission(self, HIWORD(started->arr_96[1]));
  return gta2::MissionObjective_sub_4C4F30(gMissionObjective, &v17, &a2, v10->arr_96[1], v12, FirstElement, v14, v15, v16);
}


// 0x0047ee70: MissionManager::sub_47EE70
// IDA: MissionManager::sub_47EE70
// Ghidra: ---
void gta2::MissionManager_sub_47EE70(MissionManager *self)
{
  unsigned __int16 v1; // di
  unsigned __int16 v2; // si
  int *OBJECTIVE_DATA_SIZE; // ebx
  _WORD *started; // eax
  __int16 v5; // dx
  int v6; // edx

  v1 = 0;
  v2 = 0;
  OBJECTIVE_DATA_SIZE = self->OBJECTIVE_DATA_SIZE;
  do
  {
    if ( *(_WORD *)OBJECTIVE_DATA_SIZE )
    {
      started = gta2::MissionManager_StartMission(self, v2);
      v5 = started[1];
      if ( v5 == 275 || v5 == 276 )
      {
        v6 = 4 * v1++;
        *(_WORD *)((char *)&unk_6646C4 + v6) = *started;
        *(_WORD *)((char *)&unk_6646C6 + v6) = started[4];
      }
    }
    ++v2;
    OBJECTIVE_DATA_SIZE = (int *)((char *)OBJECTIVE_DATA_SIZE + 2);
  }
  while ( v2 < 0x1770u );
  unk_6646BA = v1;
  if ( v1 < 0x12Cu )
    memset((void *)(4 * v1 + 6702788), 0, 4 * (300 - v1));
}


// 0x0047ef10: MissionManager::sub_47EF10
// IDA: MissionManager::sub_47EF10
// Ghidra: FUN_0047ef10
void gta2::MissionManager_sub_47EF10(void *self)
{
  ushort uVar1;
  void *pvVar2;
  MissionManager *extraout_ECX;
  ushort *puVar3;
  ushort *extraout_EDX;
  int iVar4;
  
  puVar3 = (ushort *)&DAT_006646c4;
  iVar4 = 300;
  do {
    if (*puVar3 != 0) {
      uVar1 = puVar3[1];
      pvVar2 = gta2::MissionManager_StartMission((MissionManager *)self,*puVar3);
      *(int *)((int)pvVar2 + 8) = (int)(short)uVar1;
      self = extraout_ECX;
      puVar3 = extraout_EDX;
    }
    puVar3 = puVar3 + 2;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}


// 0x0047ef40: MissionManager::SaveFile
// IDA: MissionManager::SaveFile
// Ghidra: ---
int gta2::MissionManager_SaveFile(MissionManager *self, char *pSaveFileName)
{
  LPCSTR FileName; // ebx
  byte PlayerSlotSave; // al
  int result; // eax
  int v6; // [esp+8h] [ebp-18h] BYREF
  int v7; // [esp+Ch] [ebp-14h] BYREF
  int a3; // [esp+10h] [ebp-10h] BYREF
  int v9; // [esp+14h] [ebp-Ch] BYREF
  int v10; // [esp+18h] [ebp-8h] BYREF
  int v11; // [esp+1Ch] [ebp-4h] BYREF

  FileName = pSaveFileName;
  if ( !pSaveFileName || !*pSaveFileName )
  {
    PlayerSlotSave = gta2::MapGm_GetPlayerSlotSave(&gMapGm);
    strcpy(gStr, "player\\plyslot%d.svg", PlayerSlotSave);
    FileName = gStr;
  }
  gta2::MissionManager_sub_47EE70(self);
  gta2::Player_sub_4A6B20(gGame->PlayerMain, (int)&dword_6645E4);
  gta2::Object_sub_483D90(gObject, (int)byte_664B74);
  qmemcpy(unk_664CA0, &gObject->S63[0].S63_1, 50u);
  unk_664CD4 = gta2::MapGm_GetSpecialTokens(&gMapGm);
  gta2::MapRelatedStruct_sub_4642A0(gMapRelatedStruct, &v9, &pSaveFileName, &v10, &v6, &v11, &v7);
  gta2::MissionManager_sub_475CA0(self);
  a3 = 1864;
  gta2::WriteSub_402CF0(FileName, unk_664590, &a3);
  a3 = 4;
  gta2::ARWBinarySub_402DA0(FileName, (int)&pSaveFileName, (int)&a3);
  if ( pSaveFileName )
    gta2::ARWBinarySub_402DA0(FileName, v9, (int)&pSaveFileName);
  a3 = 4;
  gta2::ARWBinarySub_402DA0(FileName, (int)&v6, (int)&a3);
  if ( v6 )
    gta2::ARWBinarySub_402DA0(FileName, v10, (int)&v6);
  a3 = 4;
  gta2::ARWBinarySub_402DA0(FileName, (int)&v7, (int)&a3);
  result = v7;
  if ( v7 )
    return gta2::ARWBinarySub_402DA0(FileName, v11, (int)&v7);
  return result;
}


// 0x0047f0b0: MissionManager::sub_47F0B0
// IDA: MissionManager::sub_47F0B0
// Ghidra: ---
int gta2::MissionManager_sub_47F0B0(MissionManager *self, char *SaveFileName)
{
  void *v3; // ecx
  FileMgr *v4; // ecx
  S63_1 *p_S63_1; // edi
  int result; // eax
  FILE v7; // [esp+Ch] [ebp-18h] BYREF
  FILE v8; // [esp+10h] [ebp-14h] BYREF
  int size; // [esp+14h] [ebp-10h] BYREF
  FILE *v10; // [esp+18h] [ebp-Ch] BYREF
  FILE *v11; // [esp+1Ch] [ebp-8h] BYREF
  FileMgr *v12; // [esp+20h] [ebp-4h] BYREF

  gta2::MapRelatedStruct_sub_4642A0(gMapRelatedStruct, &v10, &size, &v11, &v8, &v12, (int *)&v7);
  gta2::FileMgr_FileOpen(v3, SaveFileName);
  SaveFileName = (char *)1864;
  gta2::FileMgr_Read((FILE *)unk_664590, (SIZE_T *)&SaveFileName);
  SaveFileName = (char *)4;
  gta2::FileMgr_Read((FILE *)&size, (SIZE_T *)&SaveFileName);
  if ( size )
    gta2::FileMgr_Read(v10, (SIZE_T *)&size);
  SaveFileName = (char *)4;
  gta2::FileMgr_Read(&v8, (SIZE_T *)&SaveFileName);
  if ( v8._Placeholder )
    gta2::FileMgr_Read(v11, (SIZE_T *)&v8);
  SaveFileName = (char *)4;
  gta2::FileMgr_Read(&v7, (SIZE_T *)&SaveFileName);
  if ( v7._Placeholder )
    gta2::FileMgr_Read((FILE *)v12, (SIZE_T *)&v7);
  gta2::MapRelatedStruct_sub_464250(
    &gMapRelatedStruct->Map_,
    size,
    (unsigned int)v8._Placeholder,
    (unsigned int)v7._Placeholder);
  gta2::FileMgr_CloseFile(v4);
  gta2::MissionManager_sub_47EF10(self);
  gta2::Object_sub_485640(gObject, byte_664B74);
  p_S63_1 = (S63_1 *)&gObject->S63[0].S63_1;
  qmemcpy(&gObject->S63[0].S63_1, unk_664CA0, 48u);
  p_S63_1->field_30 = unk_664CA0[24];
  result = gta2::MapGm_sub_476B10(&gMapGm, unk_664CD4);
  self->Bool_A = 1;
  return result;
}


// 0x0047f200: MissionManager::sub_47F200
// IDA: MissionManager::sub_47F200
// Ghidra: FUN_0047f200
undefined4 gta2::MissionManager_sub_47F200(void *self,undefined2 param_1,undefined1 param_2)
{
  MissionManager *this_00;
  undefined4 extraout_ECX;
  
  this_00 = (MissionManager *)gta2::MissionScriptObjects_RemoveFirstElement(gAnimation);
  gta2::MissionScriptObjectData_sub_475B70(this_00,param_2,param_1);
  return extraout_ECX;
}


// 0x0047f230: MissionManager::sub_47F230
// IDA: MissionManager::sub_47F230
// Ghidra: ---
_WORD * gta2::MissionManager_sub_47F230(MissionManager *self, __int16 a2, unsigned __int16 a3)
{
  unsigned __int16 v3; // dx
  _WORD *result; // eax
  __int16 v5; // dx

  if ( skip_mission )
    return 0;
  v3 = 0;
  if ( 6000 - a3 <= 0 )
    return 0;
  while ( 1 )
  {
    result = gta2::MissionManager_StartMission(self, v3 + a3);
    if ( result )
    {
      if ( result[1] == a2 )
        break;
    }
    v3 = v5 + 1;
    if ( v3 >= 6000 - a3 )
      return 0;
  }
  return result;
}


// 0x0047f280: MissionManager::loadScript
// IDA: MissionManager::loadScript
// Ghidra: ---
unsigned __int8 gta2::MissionManager_loadScript(MissionManager *self, char *ScriptName)
{
  unsigned __int8 result; // al
  char *pScriptName; // eax
  int index; // edx
  char v6; // cl
  void *v7; // ecx
  FileMgr *v8; // ecx
  void *v9; // [esp-Ch] [ebp-14h]
  int size; // [esp+4h] [ebp-4h] BYREF

  result = skip_mission;
  if ( !skip_mission )
  {
    pScriptName = ScriptName;
    index = self->pathToScriptFile - ScriptName;
    do
    {
      v6 = *pScriptName;
      pScriptName[index] = *pScriptName;
      ++pScriptName;
    }
    while ( v6 );
    gta2::FileMgr_SetFilePath(self->pathToScriptFile);
    gta2::FileMgr_FileOpen(v7, self->pathToScriptFile);
    ScriptName = (char *)12000;
    gta2::FileMgr_Read((FILE *)self->OBJECTIVE_DATA_SIZE, (SIZE_T *)&ScriptName);
    ScriptName = (char *)65536;
    gta2::FileMgr_Read((FILE *)self->Script, (SIZE_T *)&ScriptName);
    ScriptName = (char *)2;
    gta2::FileMgr_Read((FILE *)&size, (SIZE_T *)&ScriptName);
    v9 = self->EVENT_LOG_SIZE[0];
    ScriptName = (char *)5118;
    partOfLoadScrip(v9, (int *)&ScriptName);
    gta2::FileMgr_CloseFile(v8);
    gta2::MissionManager_sub_475D30(self, size);
    gta2::MissionManager_ExtractFileNameWithoutExtension(self);
    return (unsigned __int8)gta2::MissionManager_sub_476070(self);
  }
  return result;
}


// 0x0047f340: MissionManager::sub_47F340
// IDA: MissionManager::sub_47F340
// Ghidra: ---
char gta2::MissionManager_sub_47F340(MissionManager *self, int a2, int a3)
{
  int *v4; // eax
  int *v5; // edi
  MissionManager *started; // ebx
  void *v7; // ecx
  int v8; // eax
  __int16 v9; // cx
  char result; // al

  v4 = gta2::MissionManager_sub_476240(self, a2, a3);
  v5 = v4;
  if ( !v4 )
    return 0;
  started = gta2::MissionManager_StartMission(self, *((_WORD *)v4 + 4));
  v8 = gta2::MissionManager_sub_47F200(v7, HIWORD(started->arr_96[2]), 0);
  started->arr_96[1] = v8;
  if ( !v8 )
    return 0;
  v9 = *(_WORD *)(v8 + 282);
  result = 1;
  LOWORD(started->arr_96[2]) = v9;
  *v5 = 0;
  v5[1] = 0;
  *((_WORD *)v5 + 4) = 0;
  --self->field_0;
  return result;
}


// 0x0047f3b0: MissionManager::sub_47F3B0
// IDA: MissionManager::sub_47F3B0
// Ghidra: FUN_0047f3b0
undefined4 gta2::MissionManager_sub_47F3B0(MissionManager *param_1,int param_2,int param_3)
{
  int *piVar1;
  void *pvVar2;
  int iVar3;
  void *self;
  
  piVar1 = gta2::MissionManager_sub_476320(param_1,param_2,param_3);
  if (piVar1 != NULL) {
    pvVar2 = gta2::MissionManager_StartMission(param_1,*(ushort *)(piVar1 + 2));
    if (*(short *)((int)pvVar2 + 2) == 0xa8) {
      *(undefined1 *)((int)pvVar2 + 0x12) = 1;
      return 1;
    }
    if (*(short *)((int)pvVar2 + 2) == 0xd5) {
      iVar3 = FUN_0047f200(self,*(undefined2 *)((int)pvVar2 + 0xe),0);
      *(int *)((int)pvVar2 + 8) = iVar3;
      if (iVar3 != 0) {
        *(undefined2 *)((int)pvVar2 + 0xc) = *(undefined2 *)(iVar3 + 0x11a);
      }
      return 1;
    }
  }
  return 0;
}


// 0x0047f420: MissionManager::sub_47F420
// IDA: MissionManager::sub_47F420
// Ghidra: ---
int * gta2::MissionManager_sub_47F420(MissionManager *self, int a2)
{
  int *result; // eax

  result = (int *)gta2::MissionManager_sub_4763E0(self, a2);
  if ( result )
    return gta2::MissionManager_sub_4763B0(self, *result, a2);
  return result;
}


// 0x00481200: MissionManager::sub_481200
// IDA: MissionManager::sub_481200
// Ghidra: ---
int gta2::MissionManager_sub_481200(MissionManager *self)
{
  char v2; // bl
  int *arr2_15; // edi
  MissionManager *started; // esi
  int result; // eax
  int v6; // [esp+10h] [ebp-4h]

  v2 = 0;
  arr2_15 = self->arr2_15;
  v6 = 32;
  do
  {
    if ( ((1 << v2) & unk_6646BC) != 0 )
    {
      started = gta2::MissionManager_StartMission(self, *(_WORD *)arr2_15);
      gta2::S63_sub_483C60((EventHandler *)started->arr_96[1], 174);
      gta2::MissionManager_sub_47F420(gMissionManager, *(_DWORD *)(started->arr_96[1] + 20));
    }
    ++v2;
    arr2_15 = (int *)((char *)arr2_15 + 2);
    result = --v6;
  }
  while ( v6 );
  return result;
}


// 0x00481890: MissionManager::sub_481890
// IDA: MissionManager::sub_481890
// Ghidra: ---
Player * gta2::MissionManager_sub_481890(MissionManager *self)
{
  Player *result; // eax
  MissionScriptObjectData *pMissionScriptObjectData; // edi
  __int16 *v4; // esi

  LOBYTE(result) = skip_mission;
  if ( !skip_mission )
  {
    pMissionScriptObjectData = gta2::MissionScriptObjects_RemoveFirstElement(gMissionScriptObjects);
    v4 = gta2::MissionManager_sub_47F230(self, 59, 0);
    if ( v4 )
    {
      gta2::MissionScriptObjectDatar_sub_481400(pMissionScriptObjectData);
      gta2::MissionScriptObjectData_sub_475B70(pMissionScriptObjectData, 0, *v4);
      return gta2::Game_GetPlayer1(gGame);
    }
    else
    {
      return (Player *)gta2::debug_log(0x41u, "miss2.cpp", 12774);
    }
  }
  return result;
}


// 0x00481900: MissionManager::sub_481900
// IDA: MissionManager::sub_481900
// Ghidra: ---
void gta2::MissionManager_sub_481900(MissionManager *self)
{
  if ( skip_mission )
  {
    gCarSystemManager->field_5C = 0;
  }
  else
  {
    if ( byte_5931F4 )
    {
      if ( do_miss_logging )
      {
        gta2::MissionScriptObjects_sub_47F4D0(gMissionScriptObjects);
        gta2::sub_461590(dword_664D18, &dword_56EC54);
      }
    }
    gta2::MissionScriptObjects_sub_481380(gMissionScriptObjects);
    gCarSystemManager->field_5C = 0;
  }
}


// 0x00481960: MissionManager::MissionManager
// IDA: MissionManager::MissionManager
// Ghidra: ---
MissionManager * gta2::MissionManager_MissionManager(MissionManager *self)
{
  MissionScriptObjects *pS27; // eax
  MissionScriptObjects *ppS27; // eax
  TrafficManager *pS31; // eax
  TrafficManager *ppS31; // eax

  self->EVENT_LOG_SIZE[1] = 0;
  if ( !skip_mission )
  {
    memset(self->Script, 0, sizeof(self->Script));
    if ( !gMissionScriptObjects )
    {
      pS27 = (MissionScriptObjects *)gta2::operator_new(0x8ECu);
      if ( pS27 )
        ppS27 = gta2::MissionScriptObjects_MissionScriptObjects(pS27);
      else
        ppS27 = 0;
      gMissionScriptObjects = ppS27;
    }
  }
  self->EVENT_LOG_SIZE[0] = gta2::createBuffer(5120u);
  memset(self->pathToScriptFile, 0, sizeof(self->pathToScriptFile));
  memset(self->Script, 0, sizeof(self->Script));
  memset(self->OBJECTIVE_DATA_SIZE, 0, sizeof(self->OBJECTIVE_DATA_SIZE));
  memset(self->EVENT_LOG_SIZE[0], 0, 5120u);
  self->field_0 = 0;
  memset(self->arr_96, 0, sizeof(self->arr_96));
  self->field_184 = 0;
  memset(self->RuntimeCache, 0, sizeof(self->RuntimeCache));
  self->field_278 = 0;
  memset(self->arr_30, 0, sizeof(self->arr_30));
  memset(unk_664590, 0, 0x748u);
  pS31 = (TrafficManager *)gta2::operator_new(604u);
  if ( pS31 )
    ppS31 = gta2::TrafficManager_TrafficManager(pS31);
  else
    ppS31 = 0;
  gTrafficManager = ppS31;
  if ( !ppS31 )
    gta2::debug_log(0x20u, "miss2.cpp", 13630);
  memset(&self->EVENT_LOG_SIZE[2], 0, 620000u);
  memset(self->arr_23808, 0, sizeof(self->arr_23808));
  memset(self->arr_15, 0, sizeof(self->arr_15));
  self->Byte_a = 0;
  memset(self->BaseScriptMaxPointers, 0, sizeof(self->BaseScriptMaxPointers));
  self->field_C1DAE = 0;
  memset(self->MissionScriptSize, 0, sizeof(self->MissionScriptSize));
  self->MissionPtrMaybe = 0;
  self->shouldBeEqTo1 = 1;
  self->Bool_A = 0;
  self->Health = 0;
  self->field_314 = 0;
  self->field_318 = 0;
  self->field_31C = 0;
  self->field_320 = 0;
  self->field_324 = 0;
  self->field_328 = 0;
  self->field_32C = 0;
  self->field_330 = 0;
  self->field_334 = 0;
  self->field_338 = 0;
  self->field_33C = 0;
  self->field_340 = 0;
  self->field_348 = 0;
  self->field_34C = 0;
  self->int_A = 0;
  self->Gang_ = Yakuza;
  self->field_C1E70 = 87;
  self->field_356 = 0;
  self->field_358 = 0;
  self->field_35A = 0;
  self->field_355 = 0;
  self->field_C1E2E = 0;
  self->field_C1E2D = 0;
  self->field_468 = 0;
  if ( do_miss_logging )
    sub_461690(dword_664D18, "test\\MISS_LOG.TXT", 1);
  *(_DWORD *)self->Name = 0;
  unk_6644B0 = 0;
  unk_6644B4 = 0;
  self->field_460 = 0;
  self->field_464 = 0;
  memset(self->arr2_15, 0, sizeof(self->arr2_15));
  self->field_C1E6E = 0;
  self->field_C1E2F = 0;
  self->field_C1E31 = 0;
  memset(self->arr_12, 0, sizeof(self->arr_12));
  self->field_C1EA4 = 0;
  return self;
}


// 0x00481c30: MissionManager::MissionManagerDes
// IDA: MissionManager::MissionManagerDes
// Ghidra: ---
void gta2::MissionManager_MissionManagerDes(MissionManager *self)
{
  int *v2; // edx

  if ( gMissionScriptObjects )
  {
    gta2::MissionScriptObjects_MissionScriptObjects_des(gMissionScriptObjects, 1);
    gMissionScriptObjects = 0;
  }
  v2 = (int *)self->EVENT_LOG_SIZE[1];
  if ( v2 )
  {
    memset(v2 + 1, 0, 3996u);
    gta2::free_0(self->EVENT_LOG_SIZE[1]);
    self->EVENT_LOG_SIZE[1] = 0;
  }
  if ( self->EVENT_LOG_SIZE[0] )
  {
    gta2::free_0(self->EVENT_LOG_SIZE[0]);
    self->EVENT_LOG_SIZE[0] = 0;
  }
  memset(unk_664590, 0, 0x748u);
  if ( gTrafficManager )
  {
    free(gTrafficManager);
    gTrafficManager = 0;
  }
  self->field_328 = 0;
  self->field_32C = 0;
  self->field_330 = 0;
  self->field_334 = 0;
  self->field_340 = 0;
  self->field_338 = 0;
  self->field_33C = 0;
  self->field_348 = 0;
  self->field_34C = 0;
  self->int_A = 0;
  unk_6644B4 = 0;
  unk_6644B0 = 0;
}


// 0x004c7350: MissionManager::MissionManager_1
// IDA: MissionManager::MissionManager_1
// Ghidra: ---
char gta2::MissionManager_MissionManager_1(MissionManager *self)
{
  MissionManager *MissionPtrMaybe; // eax

  MissionPtrMaybe = self->MissionPtrMaybe;
  return MissionPtrMaybe && *(_DWORD *)&MissionPtrMaybe->field_0;
}



