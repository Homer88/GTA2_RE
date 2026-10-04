#include "gta2_shim.h"

// Module: other, Class: MapRelatedStruct
// Functions: 72
// Source: unified (IDA+Ghidra)

// 0x00464060: MapRelatedStruct::sub_464060
// IDA: MapRelatedStruct::sub_464060
// Ghidra: ---
int gta2::MapRelatedStruct_sub_464060(struct MapRelatedStruct *self, int a2, int a3, int a4, _DWORD *a5)
{
  unsigned int *v6; // eax
  unsigned int v7; // edi
  int v8; // edx
  int v9; // eax
  unsigned int v10; // edi
  unsigned int v11; // eax
  int result; // eax
  _DWORD *v13; // ecx

  v6 = (unsigned int *)gta2::Map_sub_42A830(self->Map_, a3, a2);
  v7 = gta2::MapRelatedStruct_sub_463AE0(self, *v6, a4);
  *(_DWORD *)gta2::Map_sub_42A830(self->Map_, a3, a2) = v7;
  gta2::S16_01_sub_463990(&self->S16_01_, a2, a3, v7);
  v8 = self->Map_->field_40008;
  v9 = *(unsigned __int8 *)(v8 + 4 * v7 + 1);
  v10 = v8 + 4 * v7;
  v11 = *(_DWORD *)(v10 + 4 * (a4 - v9) + 4);
  if ( v11 >= self->field_34C )
  {
    v13 = (_DWORD *)(self->Map_->field_4000C + 12 * v11);
    *v13 = *a5;
    result = a5[1];
    v13[1] = result;
    v13[2] = a5[2];
  }
  else
  {
    result = gta2::MapRelatedStruct_sub_463A00(self, a5);
    *(_DWORD *)(v10 + 4 * (a4 - *(unsigned __int8 *)(v10 + 1)) + 4) = result;
  }
  return result;
}


// 0x00464110: MapRelatedStruct::sub_464110
// IDA: MapRelatedStruct::sub_464110
// Ghidra: ---
S16_01 * gta2::MapRelatedStruct_sub_464110(struct MapRelatedStruct *self, int a2, int a3, int a4, char a5)
{
  unsigned int *v6; // eax
  struct S16_01 *result; // eax
  struct S16_01 *v8; // edi

  v6 = (unsigned int *)gta2::Map_sub_42A830(self->Map_, a3, a2);
  result = (struct S16_01 *)gta2::MapRelatedStruct_sub_463C30(self, *v6, a4, a5);
  v8 = result;
  if ( result != (struct S16_01 *)-1 )
  {
    *(_DWORD *)gta2::Map_sub_42A830(self->Map_, a3, a2) = result;
    return gta2::S16_01_sub_463990(&self->S16_01_, a2, a3, (int)v8);
  }
  return result;
}


// 0x00464160: MapRelatedStruct::sub_464160
// IDA: MapRelatedStruct::sub_464160
// Ghidra: MapRelatedStruct::FUN_00464160
void gta2::MapRelatedStruct_sub_464160(struct MapRelatedStruct *self,int param_1,int param_2)
{
  char *pcVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint *puVar7;
  struct Map *pMap;
  
  pMap = self->Map_;
  puVar7 = (uint *)gta2::Map_sub_42A830(pMap,param_2,param_1);
  uVar4 = *puVar7;
  iVar5 = pMap->field3_0x40008;
  bVar2 = *(byte *)(iVar5 + uVar4 * 4);
  bVar3 = *(byte *)(iVar5 + 1 + uVar4 * 4);
  if (((uint)bVar3 == bVar2 - 1) && (bVar3 != 0)) {
    if (uVar4 < (uint)self->field14_0x358) {
      iVar6 = self->field16_0x360;
      *(byte *)(iVar5 + 1 + iVar6 * 4) = bVar3 - 1;
      pcVar1 = (char *)(iVar5 + iVar6 * 4);
      *pcVar1 = *(char *)(iVar5 + iVar6 * 4) + -1;
      *(undefined4 *)(pcVar1 + 4) = *(undefined4 *)(iVar5 + 4 + uVar4 * 4);
      self->field16_0x360 = self->field16_0x360 + 2;
      return;
    }
    *(byte *)(iVar5 + 1 + uVar4 * 4) = bVar3 - 1;
    *(byte *)(iVar5 + uVar4 * 4) = bVar2 - 1;
    return;
  }
  gta2::MapRelatedStruct_sub_464110(self,param_1,param_2,(uint)bVar3,1);
  return;
}


// 0x00464210: MapRelatedStruct::sub_464210
// IDA: MapRelatedStruct::sub_464210
// Ghidra: ---
int gta2::MapRelatedStruct_sub_464210(struct MapRelatedStruct *self, int a2, int a3, int a4, int a5)
{
  int result; // eax
  int i; // edi
  int j; // esi

  result = a5;
  for ( i = a4; i <= a5; ++i )
  {
    for ( j = a2; j <= a3; ++j )
      gta2::MapRelatedStruct_sub_464160(self, j, i);
    result = a5;
  }
  return result;
}


// 0x00464250: MapRelatedStruct::sub_464250
// IDA: MapRelatedStruct::sub_464250
// Ghidra: ---
unsigned int gta2::MapRelatedStruct_sub_464250(Map **self, unsigned int a2, unsigned int a3, unsigned int a4)
{
  struct Map *v4; // esi

  v4 = *self;
  self[216] = (struct Map *)((char *)(*self)->File + (a2 >> 2));
  self[213] = (struct Map *)(v4->field_40004 + a3 / 0xC);
  self[201] = (struct Map *)(a4 >> 3);
  return sub_463940(v4, (int)(self + 1));
}


// 0x004642a0: MapRelatedStruct::sub_4642A0
// IDA: MapRelatedStruct::sub_4642A0
// Ghidra: ---
int gta2::MapRelatedStruct_sub_4642A0(
        struct MapRelatedStruct *self,
        _DWORD *a2,
        _DWORD *a3,
        _DWORD *a4,
        _DWORD *a5,
        _DWORD *a6,
        int *a7)
{
  int result; // eax

  *a2 = self->Map_->field_40008 + 4 * (int)self->Map_->File;
  *a3 = 4 * (self->field_360 - (unsigned int)self->Map_->File);
  *a4 = self->Map_->field_4000C + 12 * self->Map_->field_40004;
  *a5 = 12 * (self->field_354 - self->Map_->field_40004);
  *a6 = &self->S16_01_;
  result = 8 * self->S16_01_.field_320;
  *a7 = result;
  return result;
}


// 0x00464330: MapRelatedStruct::thunk_FUN_00464330
// IDA: sub_464330
// Ghidra: MapRelatedStruct::thunk_FUN_00464330
void gta2::MapRelatedStruct_thunk_FUN_00464330(struct MapRelatedStruct *self)
{
  char cVar1;
  ushort uVar2;
  void *pvVar3;
  char *pcVar4;
  void *pvVar5;
  int iVar6;
  int iVar7;
  void *extraout_EDX;
  void *extraout_EDX_00;
  uint uVar8;
  void *pvVar9;
  int iStack_10;
  void *pvStack_c;
  uint uStack_4;
  
  uStack_4 = 0;
  if (self->Buffer_ZONE == NULL) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(ushort *)self->count;
    if (uVar2 != 0) {
      pvVar3 = CreateBuffer((uint)uVar2);
      self->field4_0x330 = (int)pvVar3;
    }
  }
  pvStack_c = NULL;
  uVar8 = 0;
  if (uVar2 != 0) {
    iStack_10 = 0;
    do {
      pcVar4 = (char *)gta2::MapRelatedStruct_sub_462E40(self,pvStack_c);
      cVar1 = *pcVar4;
      if (((cVar1 == '\n') || (cVar1 == '\x01')) || (cVar1 == '\x0f')) {
        pvVar9 = NULL;
        pvVar3 = extraout_EDX;
        if ((short)extraout_EDX != 0) {
          do {
            cVar1 = *(char *)(((uint)pvVar9 & 0xffff) + self->field4_0x330);
            if (cVar1 != '\0') {
              pvVar5 = gta2::MapRelatedStruct_sub_462E40(self,pvVar9);
              pvVar3 = extraout_EDX_00;
              if ((pcVar4[5] == *(byte *)((int)pvVar5 + 5)) &&
                 (iVar7 = gta2::_strncmp(pcVar4 + 6,(char *)((int)pvVar5 + 6),
                                   (uint)(byte)pcVar4[5]), pvVar3 = pvStack_c,
                 iVar7 == 0)) {
                *(char *)(iStack_10 + self->field4_0x330) = cVar1;
                goto LAB_0046441b;
              }
            }
            pvVar9 = (void *)((int)pvVar9 + 1);
          } while ((ushort)pvVar9 < (ushort)pvVar3);
        }
        pvStack_c = pvVar3;
        uStack_4 = uStack_4 + 1;
        *(char *)(iStack_10 + self->field4_0x330) = (char)uStack_4;
      }
      else {
        *(undefined1 *)(iStack_10 + self->field4_0x330) = 0;
        pvStack_c = extraout_EDX;
      }
LAB_0046441b:
      pvStack_c = (void *)((int)pvStack_c + 1);
      iStack_10 = iStack_10 + 1;
      uVar8 = uStack_4;
    } while ((ushort)pvStack_c < uVar2);
  }
  pvVar3 = CreateBuffer(((uVar8 & 0xffff) + 1) * 0x16);
  iVar7 = 0;
  self->field5_0x334 = pvVar3;
  uVar8 = uVar8 + 1 & 0xffff;
  do {
    iVar6 = self->field5_0x334;
    *(undefined2 *)(iVar6 + iVar7) = 500;
    iVar6 = iVar6 + iVar7;
    iVar7 = iVar7 + 0x16;
    uVar8 = uVar8 - 1;
    *(undefined2 *)(iVar6 + 2) = 300;
    *(undefined2 *)(iVar6 + 4) = 300;
    *(undefined2 *)(iVar6 + 6) = 100;
    *(undefined2 *)(iVar6 + 8) = 0;
    *(undefined2 *)(iVar6 + 10) = 500;
    *(undefined2 *)(iVar6 + 0xc) = 0x32;
    *(undefined2 *)(iVar6 + 0xe) = 0x28;
    *(undefined2 *)(iVar6 + 0x10) = 10;
    *(undefined2 *)(iVar6 + 0x12) = 200;
    *(undefined2 *)(iVar6 + 0x14) = 0x28;
  } while (uVar8 != 0);
  return;
}


// 0x004644e0: MapRelatedStruct::sub_4644E0
// IDA: MapRelatedStruct::sub_4644E0
// Ghidra: ---
int gta2::MapRelatedStruct_sub_4644E0(struct MapRelatedStruct *self, unsigned int a2)
{
  unsigned int v3; // ecx
  int v4; // ebx
  FILE *i; // ebp
  int v6; // eax
  int result; // eax
  unsigned int v8; // edx
  FILE *Buffer_ZONE; // ecx
  int v10; // ebp

  v3 = 0;
  v4 = 0;
  for ( i = self->Buffer_ZONE; v3 < a2; ++v4 )
  {
    v6 = BYTE1(i[1]._Placeholder) + 6;
    v3 += v6;
    i = (FILE *)((char *)i + v6);
  }
  result = (int)gta2::createBuffer(4 * v4 + 4);
  self->count = result;
  v8 = 0;
  *(_WORD *)result = v4;
  Buffer_ZONE = self->Buffer_ZONE;
  if ( a2 )
  {
    v10 = 0;
    do
    {
      v10 += 4;
      *(_DWORD *)(self->count + v10) = Buffer_ZONE;
      result = BYTE1(Buffer_ZONE[1]._Placeholder) + 6;
      v8 += result;
      Buffer_ZONE = (FILE *)((char *)Buffer_ZONE + result);
    }
    while ( v8 < a2 );
  }
  return result;
}


// 0x00464550: MapRelatedStruct::sub_464550
// IDA: MapRelatedStruct::sub_464550
// Ghidra: ---
int gta2::MapRelatedStruct_sub_464550(struct MapRelatedStruct *self, int a2)
{
  FILE *Buffer_ANIM; // esi
  int result; // eax

  Buffer_ANIM = self->Buffer_ANIM;
  result = (int)Buffer_ANIM + a2;
  if ( Buffer_ANIM != (FILE *)((char *)Buffer_ANIM + a2) )
  {
    do
    {
      result = gta2::TileAnim_sub_4C3470(gTileAnim, (int)Buffer_ANIM);
      Buffer_ANIM = (FILE *)((char *)Buffer_ANIM + 2 * LOBYTE(Buffer_ANIM[1]._Placeholder) + 6);
    }
    while ( Buffer_ANIM != (FILE *)((char *)self->Buffer_ANIM + a2) );
  }
  return result;
}


// 0x00464590: MapRelatedStruct::sub_464590
// IDA: MapRelatedStruct::sub_464590
// Ghidra: ---
int gta2::MapRelatedStruct_sub_464590(struct MapRelatedStruct *self, SIZE_T dwBytes)
{
  FILE *Buffer; // eax
  SIZE_T v4; // ecx
  int result; // eax
  SIZE_T v6; // edx
  SIZE_T v7; // [esp-4h] [ebp-8h] BYREF

  Buffer = (FILE *)gta2::createBuffer(v7);
  self->Buffer_MOBJ = Buffer;
  gta2::FileMgr_Read(Buffer, &v7);
  v4 = v7;
  result = -1431655765 * v7;
  v6 = v7 / 6;
  self->field_344 = v7 / 6;
  if ( 6 * v6 != v4 )
    return gta2::debug_log(0x28u, "map.cpp", 6024);
  return result;
}


// 0x004645f0: MapRelatedStruct::sub_4645F0
// IDA: MapRelatedStruct::sub_4645F0
// Ghidra: ---
int gta2::MapRelatedStruct_sub_4645F0(struct MapRelatedStruct *self, SIZE_T dwBytes)
{
  FILE *Buffer; // eax
  SIZE_T v4; // ecx
  SIZE_T v5; // eax
  int result; // eax
  SIZE_T v7; // [esp-4h] [ebp-8h] BYREF

  Buffer = (FILE *)gta2::createBuffer(v7);
  self->Buffer_LGHT = Buffer;
  gta2::FileMgr_Read(Buffer, &v7);
  v4 = v7;
  v5 = v7 >> 4;
  self->field_348 = v7 >> 4;
  result = 16 * v5;
  if ( result != v4 )
    return gta2::debug_log(0x33u, "map.cpp", 6046);
  return result;
}


// 0x00464640: MapRelatedStruct::sub_464640
// IDA: MapRelatedStruct::sub_464640
// Ghidra: ---
int gta2::MapRelatedStruct_sub_464640(struct MapRelatedStruct *self, FileMgr *dwBytes)
{
  FILE *Buffer; // eax

  Buffer = (FILE *)gta2::createBuffer((SIZE_T)dwBytes);
  self->Buffer_ZONE = Buffer;
  gta2::FileMgr_Read(Buffer, (SIZE_T *)&dwBytes);
  return gta2::MapRelatedStruct_sub_4644E0(self, (unsigned int)dwBytes);
}


// 0x00464670: MapRelatedStruct::sub_464670
// IDA: MapRelatedStruct::sub_464670
// Ghidra: ---
int gta2::MapRelatedStruct_sub_464670(struct MapRelatedStruct *self, FileMgr *dwBytes)
{
  FILE *Buffer; // eax

  Buffer = (FILE *)gta2::createBuffer((SIZE_T)dwBytes);
  self->Buffer_ANIM = Buffer;
  gta2::FileMgr_Read(Buffer, (SIZE_T *)&dwBytes);
  return gta2::MapRelatedStruct_sub_464550(self, (int)dwBytes);
}


// 0x004646a0: MapRelatedStruct::sub_4646A0
// IDA: MapRelatedStruct::sub_4646A0
// Ghidra: ---
int gta2::MapRelatedStruct_sub_4646A0(struct MapRelatedStruct *self, int a2)
{
  struct Map *pMap; // eax
  struct Map *pMap1; // eax
  struct Map *pMap2; // eax
  int v6; // ecx
  FILE *v7; // eax
  int Placeholder; // ecx
  struct Map *v9; // ecx
  int v10; // eax
  void *Buffer; // eax
  struct Map *v12; // ecx
  int v13; // ecx
  int v14; // eax
  int result; // eax
  FILE *Map; // [esp-2Ch] [ebp-3Ch]
  FILE **p_File; // [esp-2Ch] [ebp-3Ch]
  SIZE_T v18; // [esp-18h] [ebp-28h] BYREF
  int v19; // [esp-14h] [ebp-24h] BYREF
  SIZE_T *v20; // [esp-10h] [ebp-20h]
  SIZE_T v21[2]; // [esp-Ch] [ebp-1Ch] BYREF
  int v22; // [esp-4h] [ebp-14h] BYREF
  int v23; // [esp+8h] [ebp-8h]

  pMap = (struct Map *)gta2::operator_new(0x40010u);
  if ( pMap )
    pMap1 = gta2::Map_Map(pMap);
  else
    pMap1 = 0;
  self->Map_ = pMap1;
  if ( !pMap1 )
    gta2::debug_log(0x20u, "map.cpp", 6147);
  Map = (FILE *)self->Map_;
  v18 = 0x40000;
  gta2::FileMgr_Read(Map, &v18);
  p_File = &self->Map_->File;
  v18 = 4;
  gta2::FileMgr_Read((FILE *)p_File, &v18);
  if ( (unsigned int)&self->Map_->File[256] > 0x20000 )
    gta2::debug_log(0x467u, "map.cpp", 6150);
  pMap2 = self->Map_;
  v6 = (int)&self->Map_->File[256];
  self->field_35C = v6;
  v19 = 4 * (int)pMap2->File;
  self->Map_->field_40008 = (int)gta2::createBuffer(4 * v6);
  gta2::FileMgr_Read((FILE *)self->Map_->field_40008, (SIZE_T *)&v19);
  v7 = (FILE *)self->Map_;
  v21[0] = 4;
  Placeholder = (int)v7[0x10000]._Placeholder;
  self->field_358 = Placeholder;
  self->field_360 = Placeholder;
  gta2::FileMgr_Read(v7 + 65537, v21);
  if ( (unsigned int)(self->Map_->field_40004 + 200) > 0x20000 )
    gta2::debug_log(0x469u, "map.cpp", 6161);
  v9 = self->Map_;
  v10 = self->Map_->field_40004 + 200;
  self->field_350 = v10;
  v22 = 12 * v9->field_40004;
  Buffer = gta2::createBuffer(12 * v10);
  v12 = self->Map_;
  v20 = (SIZE_T *)&v22;
  v12->field_4000C = (int)Buffer;
  gta2::FileMgr_Read((FILE *)self->Map_->field_4000C, v20);
  v13 = v22;
  v14 = self->Map_->field_40004;
  self->field_34C = v14;
  self->field_354 = v14;
  result = v23;
  if ( v23 != v13 + v21[1] + 262152 )
  {
    v21[0] = v23;
    return gta2::debug_log(0x409u, "map.cpp", 6170);
  }
  return result;
}


// 0x00464880: MapRelatedStruct::sub_464880
// IDA: MapRelatedStruct::sub_464880
// Ghidra: ---
unsigned __int8 gta2::MapRelatedStruct_sub_464880(struct MapRelatedStruct *self)
{
  struct JuncIds *pJuncIds; // esi
  unsigned __int8 result; // al
  int v3; // edi
  struct Data16 *v4; // esi
  unsigned __int16 v5; // ax
  unsigned __int16 v6; // ax
  unsigned __int16 v7; // ax
  unsigned __int16 v8; // ax
  int v9; // [esp-14h] [ebp-18h]
  int v10; // [esp-10h] [ebp-14h]
  int v11; // [esp-Ch] [ebp-10h]
  SIZE_T v12; // [esp+0h] [ebp-4h] BYREF

  pJuncIds = gJuncIds;
  v12 = 8720;
  gta2::FileMgr_Read((FILE *)gJuncIds->Arr_316_Data16, &v12);
  v12 = 4360;
  gta2::FileMgr_Read((FILE *)pJuncIds->Arr_0x884, &v12);
  v12 = 4360;
  gta2::FileMgr_Read((FILE *)pJuncIds->arr_0x884, &v12);
  v12 = 2;
  gta2::FileMgr_Read((FILE *)&pJuncIds->field_4, &v12);
  v12 = 2;
  gta2::FileMgr_Read((FILE *)&pJuncIds->field_CC62, &v12);
  v12 = 2;
  gta2::FileMgr_Read((FILE *)&pJuncIds->field_CC64, &v12);
  pJuncIds->Count = 0;
  result = log_routefinder;
  if ( log_routefinder )
  {
    v3 = 0;
    v4 = (struct Data16 *)((char *)&pJuncIds->Arr_316_Data16[0].field_4 + 2);
    do
    {
      LOBYTE(v5) = gta2::Data16_sub_40CE90((struct Data16 *)((char *)v4 - 2));
      v11 = v5;
      LOBYTE(v6) = gta2::Data16_sub_40CE90(v4);
      v10 = v6;
      LOBYTE(v7) = gta2::Data16_sub_40CE90((struct Data16 *)((char *)v4 - 4));
      v9 = v7;
      LOBYTE(v8) = gta2::Data16_sub_40CE90((struct Data16 *)((char *)v4 - 6));
      strcpy(
        gStr,
        "Junc: %d (%d, %d) n %d s %d w %d e %d",
        v3,
        BYTE2(v4->field_4),
        HIBYTE(v4->field_4),
        v8,
        v9,
        v10,
        v11);
      gta2::CopyBuffer(byte_5EA6B8, gStr);
      if ( v3 > 0 && !BYTE2(v4->field_4) && !HIBYTE(v4->field_4) )
        break;
      ++v3;
      ++v4;
    }
    while ( v3 < 545 );
    return (unsigned __int8)gta2::CopyBuffer(byte_5EA6B8, "     ");
  }
  return result;
}


// 0x00464890: MapRelatedStruct::sub_464890
// IDA: MapRelatedStruct::sub_464890
// Ghidra: ---
unsigned __int8 gta2::MapRelatedStruct_sub_464890(struct MapRelatedStruct *self, _BYTE *a2, FileMgr *dwBytes)
{
  struct FileMgr *v5; // ecx

  if ( !gta2::_strncmp(a2, "DMAP", 4) )
    return gta2::MapRelatedStruct_sub_4646A0(self, (int)dwBytes);
  if ( !gta2::_strncmp(a2, "ZONE", 4) )
    return gta2::MapRelatedStruct_sub_464640(self, dwBytes);
  if ( !gta2::_strncmp(a2, "MOBJ", 4) )
    return gta2::MapRelatedStruct_sub_464590(self, (SIZE_T)dwBytes);
  if ( !gta2::_strncmp(a2, "ANIM", 4) )
    return gta2::MapRelatedStruct_sub_464670(self, dwBytes);
  if ( !gta2::_strncmp(a2, "LGHT", 4) )
    return gta2::MapRelatedStruct_sub_4645F0(self, (SIZE_T)dwBytes);
  if ( !gta2::_strncmp(a2, "RGEN", 4) )
    return gta2::MapRelatedStruct_sub_464880(self);
  return gta2::FileMgr_SeekPosition(v5, (int)&dwBytes);
}


// 0x00464990: MapRelatedStruct::LoadMap
// IDA: MapRelatedStruct::LoadMap
// Ghidra: ---
_WORD * gta2::MapRelatedStruct_LoadMap(struct MapRelatedStruct *self, LPCSTR lpFileName)
{
  struct FileMgr *v3; // ecx
  _WORD *result; // eax
  unsigned int size; // [esp+4h] [ebp-14h] BYREF
  FILE v6[2]; // [esp+8h] [ebp-10h] BYREF
  char a1[4]; // [esp+10h] [ebp-8h] BYREF
  SIZE_T dwBytes; // [esp+14h] [ebp-4h]

  gta2::FileMgr_FileOpen(self, lpFileName);
  size = 6;
  gta2::FileMgr_Read(v6, &size);
  for ( size = 8; gta2::FileMgr_ReadLine((struct FileMgr *)a1, a1, (SIZE_T)&size); size = 8 )
  {
    if ( dwBytes )
      gta2::MapRelatedStruct_sub_464890(self, a1, (struct FileMgr *)dwBytes);
  }
  gta2::FileMgr_CloseFile(v3);
  result = gta2::MapRelatedStruct_sub_464980(self);
  if ( !self->Map_ )
    return (_WORD *)gta2::debug_log(0x84u, "map.cpp", 6329);
  return result;
}


// 0x00464a40: MapRelatedStruct::MapRelatedStruct
// IDA: MapRelatedStruct::MapRelatedStruct
// Ghidra: ---
MapRelatedStruct * gta2::MapRelatedStruct_MapRelatedStruct(struct MapRelatedStruct *self)
{
  struct MapRelatedStruct *result; // eax

  gta2::S16_01_S16_01(&self->S16_01_);
  self->Len = -1;
  self->field_369 = -1;
  self->Buffer_ZONE = 0;
  self->count = 0;
  self->Buffer_MOBJ = 0;
  self->field_344 = 0;
  self->Map_ = 0;
  self->field_330 = 0;
  self->field_334 = 0;
  self->Buffer_ANIM = 0;
  self->Buffer_LGHT = 0;
  self->field_348 = 0;
  self->field_350 = 0;
  self->field_34C = 0;
  self->field_354 = 0;
  self->field_358 = 0;
  self->field_35C = 0;
  self->field_360 = 0;
  self->field_364 = -1;
  self->field_36A = 0;
  self->field_36B = 0;
  self->field_36C = 0;
  self->field_366 = 0;
  self->field_36D = 0;
  self->field_36E = 0;
  self->field_36F = 0;
  gta2::S16_02_sub_44C840(&gS16_02);
  gta2::S16_02_sub_44C840(&gS16_02_1);
  unk_662B9C = 1;
  gS16_02_1.field = 3073;
  unk_662B96 = 3073;
  unk_662B98 = 3073;
  unk_662B9A = 3073;
  result = self;
  unk_662B9F = 3;
  return result;
}


// 0x00464b30: MapRelatedStruct::FUN_00464b30
// IDA: sub_464B30
// Ghidra: MapRelatedStruct::FUN_00464b30
void gta2::MapRelatedStruct_FUN_00464b30(struct MapRelatedStruct *self)
{
  void *pvVar1;
  
  if (self->Buffer_LGHT != NULL) {
    free(self->Buffer_LGHT);
  }
  self->Buffer_LGHT = NULL;
  if (self->Buffer_ZONE != NULL) {
    free(self->Buffer_ZONE);
  }
  self->Buffer_ZONE = NULL;
  if ((void *)self->count != NULL) {
    free((void *)self->count);
  }
  self->count = 0;
  if (self->Buffer_MOBJ != NULL) {
    free(self->Buffer_MOBJ);
  }
  self->Buffer_MOBJ = NULL;
  if (self->Map_ != NULL) {
    pvVar1 = (void *)self->Map_->field3_0x40008;
    if (pvVar1 != NULL) {
      free(pvVar1);
    }
    self->Map_->field3_0x40008 = 0;
    pvVar1 = (void *)self->Map_->BufferData;
    if (pvVar1 != NULL) {
      free(pvVar1);
    }
    self->Map_->BufferData = 0;
    free(self->Map_);
  }
  if ((void *)self->field4_0x330 != NULL) {
    free((void *)self->field4_0x330);
  }
  self->field4_0x330 = 0;
  if ((void *)self->field5_0x334 != NULL) {
    free((void *)self->field5_0x334);
  }
  self->field5_0x334 = 0;
  if (self->Buffer_ANIM != NULL) {
    free(self->Buffer_ANIM);
  }
  self->Buffer_ANIM = NULL;
  return;
}


// 0x00464c70: MapRelatedStruct::sub_464C70
// IDA: MapRelatedStruct::sub_464C70
// Ghidra: ---
int gta2::MapRelatedStruct_sub_464C70(struct MapRelatedStruct *self, const char *a2)
{
  struct MapRelatedStruct *v2; // edx
  unsigned int v3; // esi
  int result; // eax
  _WORD *count; // eax
  unsigned __int16 v6; // bp
  ushort v7; // bp
  unsigned int v8; // [esp+4h] [ebp-4h]

  v2 = self;
  v3 = strlen(a2);
  v8 = v3;
  if ( !v2->Buffer_ZONE )
    return 0;
  count = (_WORD *)v2->count;
  v2->field_364 = 0;
  if ( *count )
  {
    do
    {
      v6 = v2->field_364;
      result = (int)gta2::MapRelatedStruct_sub_462E40(v2, v6);
      if ( *(unsigned __int8 *)(result + 5) == v3 )
      {
        if ( !memcmp((const void *)(result + 6), a2, v3) )
          return result;
        v3 = v8;
      }
      v7 = v6 + 1;
      v2->field_364 = v7;
    }
    while ( v7 < *(_WORD *)v2->count );
  }
  return 0;
}


// 0x00464d00: MapRelatedStruct::sub_464D00
// IDA: MapRelatedStruct::sub_464D00
// Ghidra: FUN_00464d00
uint gta2::MapRelatedStruct_sub_464D00(MapRelatedStruct *param_1,char *param_2,byte param_3)
{
  void *pvVar1;
  int iVar2;
  struct MapRelatedStruct *pMVar3;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 uVar4;
  
  if (param_1->Buffer_ZONE == NULL) {
    return 0;
  }
  param_1->field17_0x364 = 0;
  pMVar3 = param_1;
  if (*(short *)param_1->count != 0) {
    do {
      pvVar1 = gta2::MapRelatedStruct_sub_462E40(param_1,(void *)CONCAT22((short)((uint)pMVar3 >> 0x10)
                                                   ,param_1->field17_0x364));
      uVar4 = extraout_var;
      if ((*(byte *)((int)pvVar1 + 5) == param_3) &&
         (iVar2 = __strnicmp((char *)((int)pvVar1 + 6),param_2,(uint)param_3),
         uVar4 = extraout_var_00, iVar2 == 0)) {
        return (uint)(ushort)param_1->field17_0x364;
      }
      param_1->field17_0x364 = param_1->field17_0x364 + 1;
      pMVar3 = (struct MapRelatedStruct *)CONCAT22(uVar4,param_1->field17_0x364);
    } while ((ushort)param_1->field17_0x364 < *(ushort *)param_1->count);
  }
  return 0xffffffff;
}


// 0x00464da0: MapRelatedStruct::sub_464DA0
// IDA: MapRelatedStruct::sub_464DA0
// Ghidra: ---
char * gta2::MapRelatedStruct_sub_464DA0(struct MapRelatedStruct *self, char a2)
{
  struct MapRelatedStruct *v2; // edx
  _WORD *count; // eax
  unsigned __int16 v5; // si
  unsigned __int16 v6; // di
  int v7; // ecx
  ushort v8; // di
  __int16 v9; // ax
  unsigned __int16 a2a[40]; // [esp+0h] [ebp-50h]

  v2 = self;
  if ( !self->Buffer_ZONE )
    return 0;
  count = (_WORD *)self->count;
  v5 = 0;
  self->field_36C = 0;
  self->Len = a2;
  self->field_364 = 0;
  if ( !*count )
    return 0;
  do
  {
    v6 = v2->field_364;
    if ( *gta2::MapRelatedStruct_sub_462E40(v2, v6) == a2 )
    {
      v7 = v5++;
      a2a[v7] = v6;
      if ( v5 >= 0x28u )
        break;
    }
    v8 = v6 + 1;
    v2->field_364 = v8;
  }
  while ( v8 < *(_WORD *)v2->count );
  if ( !v5 )
    return 0;
  v9 = ++word_663290[0];
  if ( word_663290[0] >= (int)v5 )
  {
    v9 = 0;
    word_663290[0] = 0;
  }
  return gta2::MapRelatedStruct_sub_462E40(v2, a2a[v9]);
}


// 0x00464e70: MapRelatedStruct::sub_464E70
// IDA: MapRelatedStruct::sub_464E70
// Ghidra: ---
char * gta2::MapRelatedStruct_sub_464E70(struct MapRelatedStruct *self, char a2)
{
  struct MapRelatedStruct *v2; // edx
  char *result; // eax
  _WORD *count; // ecx
  unsigned __int16 v5; // si
  ushort v6; // si

  v2 = self;
  result = 0;
  if ( self->Buffer_ZONE )
  {
    count = (_WORD *)self->count;
    v2->field_36C = 0;
    v2->Len = a2;
    v2->field_364 = 0;
    if ( *count )
    {
      while ( 1 )
      {
        v5 = v2->field_364;
        result = gta2::MapRelatedStruct_sub_462E40(v2, v5);
        if ( *result == a2 )
          break;
        v6 = v5 + 1;
        v2->field_364 = v6;
        if ( v6 >= *(_WORD *)v2->count )
          return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  return result;
}


// 0x00464fe0: MapRelatedStruct::sub_464FE0
// IDA: MapRelatedStruct::sub_464FE0
// Ghidra: ---
char * gta2::MapRelatedStruct_sub_464FE0(struct MapRelatedStruct *self, unsigned __int8 a2, unsigned __int8 a3, char a4)
{
  _WORD *count; // edx
  ushort v7; // bp
  char *v8; // edi
  ushort v9; // bp

  if ( !self->Buffer_ZONE )
    return 0;
  count = (_WORD *)self->count;
  self->field_36A = a2;
  self->Len = a4;
  self->field_36B = a3;
  self->field_36C = 1;
  self->field_364 = 0;
  if ( !*count )
    return 0;
  while ( 1 )
  {
    v7 = self->field_364;
    v8 = gta2::MapRelatedStruct_sub_462E40(self, v7);
    if ( *v8 == a4 && gta2::sub_463020(v8, a2, a3) )
      break;
    v9 = v7 + 1;
    self->field_364 = v9;
    if ( v9 >= *(_WORD *)self->count )
      return 0;
  }
  return v8;
}


// 0x00465090: MapRelatedStruct::sub_465090
// IDA: MapRelatedStruct::sub_465090
// Ghidra: ---
char * gta2::MapRelatedStruct_sub_465090(struct MapRelatedStruct *self, unsigned __int8 a2, unsigned __int8 a3)
{
  _WORD *count; // ecx
  ushort v6; // bp
  char *v7; // edi
  char v8; // al
  ushort v9; // bp

  if ( !self->Buffer_ZONE )
    return 0;
  count = (_WORD *)self->count;
  self->field_36A = a2;
  self->field_36B = a3;
  self->field_364 = 0;
  if ( !*count )
    return 0;
  while ( 1 )
  {
    v6 = self->field_364;
    v7 = gta2::MapRelatedStruct_sub_462E40(self, v6);
    v8 = *v7;
    if ( (*v7 == 10 || v8 == 1 || v8 == 15) && gta2::sub_463020(v7, a2, a3) )
      break;
    v9 = v6 + 1;
    self->field_364 = v9;
    if ( v9 >= *(_WORD *)self->count )
      return 0;
  }
  return v7;
}


// 0x00465130: MapRelatedStruct::sub_465130
// IDA: MapRelatedStruct::sub_465130
// Ghidra: FUN_00465130
void * gta2::MapRelatedStruct_sub_465130(MapRelatedStruct *param_1,byte param_2,byte param_3)
{
  byte bVar1;
  void *self;
  int unaff_EDI;
  void *pvVar2;
  
  if (param_1->Buffer_ZONE == NULL) {
    return NULL;
  }
  param_1->field21_0x36a = param_2;
  param_1->field22_0x36b = param_3;
  param_1->field23_0x36c = 1;
  param_1->field17_0x364 = 0;
  if (*(short *)param_1->count != 0) {
    do {
      pvVar2 = (void *)CONCAT22((short)((uint)unaff_EDI >> 0x10),
                                param_1->field17_0x364);
      self = gta2::MapRelatedStruct_sub_462E40(param_1,pvVar2);
      bVar1 = FUN_00463020(self,param_2,param_3);
      if (bVar1 != 0) {
        return self;
      }
      unaff_EDI = (int)pvVar2 + 1;
      param_1->field17_0x364 = (ushort)unaff_EDI;
    } while ((ushort)unaff_EDI < *(ushort *)param_1->count);
  }
  return NULL;
}


// 0x004651c0: MapRelatedStruct::sub_4651C0
// IDA: MapRelatedStruct::sub_4651C0
// Ghidra: ---
char * gta2::MapRelatedStruct_sub_4651C0(struct MapRelatedStruct *self)
{
  unsigned __int16 v3; // bp
  char Len; // bl
  void *v5; // edi

  if ( !self->Buffer_ZONE )
    return 0;
  v3 = ++self->field_364;
  if ( v3 >= *(_WORD *)self->count )
    return 0;
  Len = self->Len;
  while ( 1 )
  {
    v5 = gta2::MapRelatedStruct_sub_462E40(self, v3);
    if ( *(_BYTE *)v5 == Len && (!self->field_36C || gta2::sub_463020(v5, self->field_36A, self->field_36B)) )
      break;
    self->field_364 = ++v3;
    if ( v3 >= *(_WORD *)self->count )
      return 0;
  }
  return (char *)v5;
}


// 0x00465250: MapRelatedStruct::sub_465250
// IDA: MapRelatedStruct::sub_465250
// Ghidra: ---
int gta2::MapRelatedStruct_sub_465250(struct MapRelatedStruct *self, unsigned __int8 a2, unsigned __int8 a3)
{
  if ( gta2::MapRelatedStruct_sub_465090(self, a2, a3) )
    return gta2::MapRelatedStruct_sub_462C60(self);
  else
    return self->field_334;
}


// 0x00465280: MapRelatedStruct::sub_465280
// IDA: MapRelatedStruct::sub_465280
// Ghidra: FUN_00465280
void gta2::MapRelatedStruct_sub_465280(int param_1,int param_2,short param_3,short param_4,short param_5, short param_6,short param_7,short param_8,short param_9, short param_10,short param_11,short param_12,short param_13)
{
  short *psVar1;
  
  psVar1 = (short *)(*(int *)(param_1 + 0x334) +
                    (uint)*(byte *)(*(int *)(param_1 + 0x330) + param_2) * 0x16)
  ;
  if (param_3 != -1) {
    *psVar1 = param_3;
  }
  if (param_4 != -1) {
    psVar1[1] = param_4;
  }
  if (param_5 != -1) {
    psVar1[2] = param_5;
  }
  if (param_6 != -1) {
    psVar1[3] = param_6;
  }
  if (param_7 != -1) {
    psVar1[4] = param_7;
  }
  if (param_8 != -1) {
    psVar1[5] = param_8;
  }
  if (param_9 != -1) {
    psVar1[6] = param_9;
  }
  if (param_10 != -1) {
    psVar1[7] = param_10;
  }
  if (param_11 != -1) {
    psVar1[8] = param_11;
  }
  if (param_12 != -1) {
    psVar1[9] = param_12;
  }
  if (param_13 != -1) {
    psVar1[10] = param_13;
  }
  return;
}


// 0x00465350: MapRelatedStruct::sub_465350
// IDA: MapRelatedStruct::sub_465350
// Ghidra: FUN_00465350
Gang * gta2::MapRelatedStruct_sub_465350(MapRelatedStruct *param_1)
{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined3 extraout_var;
  struct Gang *pGVar4;
  
  bVar1 = 0xe;
  iVar2 = DecoderFloat(&stack0x00000008);
  iVar3 = DecoderFloat(&stack0x00000004);
  bVar1 = gta2::MapRelatedStruct_sub_464FE0(param_1,iVar3,iVar2,bVar1);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    pGVar4 = gta2::Gangs_GetGangByName(gGangs,(char *)(CONCAT31(extraout_var,bVar1) + 6));
    return pGVar4;
  }
  return NULL;
}


// 0x00465390: MapRelatedStruct::sub_465390
// IDA: MapRelatedStruct::sub_465390
// Ghidra: ---
char * gta2::MapRelatedStruct_sub_465390(struct MapRelatedStruct *self)
{
  char *result; // eax

  for ( result = gta2::MapRelatedStruct_sub_464E70(self, 14); result; result = gta2::MapRelatedStruct_sub_4651C0(self) )
    gta2::Gangs_AddNewGang(gGangs, (int)result);
  return result;
}


// 0x004653c0: MapRelatedStruct::sub_4653C0
// IDA: MapRelatedStruct::sub_4653C0
// Ghidra: ---
int gta2::MapRelatedStruct_sub_4653C0(struct MapRelatedStruct *self, int a2, int a3, int a4)
{
  struct Map *Map; // esi
  unsigned __int8 *v5; // ecx
  int v6; // edx

  Map = self->Map_;
  v5 = (unsigned __int8 *)(Map->field_40008 + 4 * *(_DWORD *)gta2::Map_sub_42A830(self->Map_, a3, a2));
  if ( a4 >= *v5 )
    return 0;
  v6 = v5[1];
  if ( a4 < v6 )
    return 0;
  else
    return Map->field_4000C + 12 * *(_DWORD *)&v5[4 * (a4 - v6) + 4];
}


// 0x00465410: MapRelatedStruct::sub_465410
// IDA: MapRelatedStruct::sub_465410
// Ghidra: FUN_00465410
undefined * gta2::MapRelatedStruct_sub_465410(void *self,int param_1,int param_2,int param_3)
{
  byte *pbVar1;
  undefined *puVar2;
  struct Map *this_00;
  int *piVar3;
  byte bVar4;
  
                              // WARNING: Load size is inaccurate
  this_00 = *self;
  piVar3 = (int *)gta2::Map_sub_42A830(this_00,param_2,param_1);
  pbVar1 = (byte *)(this_00->field3_0x40008 + *piVar3 * 4);
  if ((param_3 < (int)(uint)*pbVar1) && ((int)(uint)pbVar1[1] <= param_3)) {
    puVar2 = (undefined *)
             (this_00->BufferData +
             *(int *)(pbVar1 + (param_3 - (uint)pbVar1[1]) * 4 + 4) * 0xc);
    bVar4 = puVar2[0xb] & 0xfc;
    if ((bVar4 < 0xd4) || (0xf4 < bVar4)) {
      if (bVar4 < 0xc4) {
        return puVar2;
      }
      if (0xd0 < bVar4) {
        return puVar2;
      }
      return &gS16_02_1;
    }
  }
  return NULL;
}


// 0x00465490: MapRelatedStruct::sub_465490
// IDA: MapRelatedStruct::sub_465490
// Ghidra: ---
int gta2::MapRelatedStruct_sub_465490(struct MapRelatedStruct *self, int a2, int a3, int a4)
{
  int v4; // edx
  int v5; // eax
  struct Map *Map; // esi
  int v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // edx

  v4 = a2;
  if ( a2 >= 0 )
  {
    if ( a2 > 255 )
      v4 = 255;
  }
  else
  {
    v4 = 0;
  }
  v5 = a3;
  if ( a3 >= 0 )
  {
    if ( a3 > 255 )
      v5 = 255;
  }
  else
  {
    v5 = 0;
  }
  Map = self->Map_;
  v7 = *(_DWORD *)gta2::Map_sub_42A830(self->Map_, v5, v4);
  v8 = Map->field_40008;
  v9 = *(unsigned __int8 *)(v8 + 4 * v7);
  v10 = v8 + 4 * v7;
  if ( a4 >= v9 )
    return 0;
  v11 = *(unsigned __int8 *)(v10 + 1);
  if ( a4 < v11 )
    return 0;
  else
    return Map->field_4000C + 12 * *(_DWORD *)(v10 + 4 * (a4 - v11) + 4);
}


// 0x00465510: MapRelatedStruct::sub_465510
// IDA: MapRelatedStruct::sub_465510
// Ghidra: FUN_00465510
int gta2::MapRelatedStruct_sub_465510(MapRelatedStruct *param_1)
{
  ushort uVar1;
  int iVar2;
  int iVar3;
  void *self;
  int iVar4;
  ushort *puVar5;
  struct MapRelatedStruct *local_4;
  
  local_4 = param_1;
  iVar2 = DecoderFloat(&stack0x0000000c);
  iVar3 = DecoderFloat(&stack0x00000008);
  self = gta2::Player_sub_401B40((SpawnPoint *)&stack0x00000004,(GlassInfo *)&local_4,
                    (struct S127 *)&DAT_00662c98);
  iVar4 = DecoderFloat(self);
  iVar2 = gta2::MapRelatedStruct_sub_4653C0(param_1,iVar4,iVar3,iVar2);
  if ((iVar2 == 0) || (uVar1 = *(ushort *)(iVar2 + 2), uVar1 == 0)) {
    iVar2 = DecoderFloat(&stack0x0000000c);
    iVar3 = DecoderFloat(&stack0x00000008);
    iVar4 = DecoderFloat(&stack0x00000004);
    puVar5 = (ushort *)gta2::MapRelatedStruct_sub_4653C0(param_1,iVar4,iVar3,iVar2);
    if ((puVar5 == NULL) || (uVar1 = *puVar5, uVar1 == 0)) {
      return 0;
    }
  }
  iVar2 = gta2::Style_sub_462FD0(gStyle,uVar1 & 0x3ff);
  return iVar2;
}


// 0x004655b0: MapRelatedStruct::sub_4655B0
// IDA: MapRelatedStruct::sub_4655B0
// Ghidra: FUN_004655b0
int gta2::MapRelatedStruct_sub_4655B0(MapRelatedStruct *param_1)
{
  ushort uVar1;
  int iVar2;
  void *self;
  int iVar3;
  int iVar4;
  struct MapRelatedStruct *local_4;
  
  local_4 = param_1;
  iVar2 = DecoderFloat(&stack0x0000000c);
  self = gta2::Player_sub_401B40((SpawnPoint *)&stack0x00000008,(GlassInfo *)&local_4,
                    (struct S127 *)&DAT_00662c98);
  iVar3 = DecoderFloat(self);
  iVar4 = DecoderFloat(&stack0x00000004);
  iVar2 = gta2::MapRelatedStruct_sub_4653C0(param_1,iVar4,iVar3,iVar2);
  if ((iVar2 == 0) || (uVar1 = *(ushort *)(iVar2 + 6), uVar1 == 0)) {
    iVar2 = DecoderFloat(&stack0x0000000c);
    iVar3 = DecoderFloat(&stack0x00000008);
    iVar4 = DecoderFloat(&stack0x00000004);
    iVar2 = gta2::MapRelatedStruct_sub_4653C0(param_1,iVar4,iVar3,iVar2);
    if ((iVar2 == 0) || (uVar1 = *(ushort *)(iVar2 + 4), uVar1 == 0)) {
      return 0;
    }
  }
  iVar2 = gta2::Style_sub_462FD0(gStyle,uVar1 & 0x3ff);
  return iVar2;
}


// 0x00465650: MapRelatedStruct::sub_465650
// IDA: MapRelatedStruct::sub_465650
// Ghidra: FUN_00465650
int gta2::MapRelatedStruct_sub_465650(void)
{
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar2;
  int iVar3;
  int iVar4;
  
  bVar1 = gta2::Player_sub_40CE70((struct Player *)&stack0x0000000c,(struct Player *)&DAT_00662cfc);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)&stack0x0000000c,(struct SpriteS1 *)&DAT_00662c3c);
    if (CONCAT31(extraout_var_00,bVar1) != 0) {
      iVar2 = DecoderFloat(&stack0x0000000c);
      iVar3 = DecoderFloat(&stack0x00000008);
      iVar4 = DecoderFloat(&stack0x00000004);
      iVar2 = gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct,iVar4,iVar3,iVar2);
      if ((iVar2 != 0) && (*(ushort *)(iVar2 + 8) != 0)) {
        iVar2 = gta2::Style_sub_462FD0(gStyle,*(ushort *)(iVar2 + 8) & 0x3ff);
        return iVar2;
      }
    }
  }
  return 0;
}


// 0x004656d0: MapRelatedStruct::sub_4656D0
// IDA: MapRelatedStruct::sub_4656D0
// Ghidra: FUN_004656d0
undefined4 gta2::MapRelatedStruct_sub_4656D0(void *param_1,int param_2,int param_3,int param_4, undefined4 param_5,undefined1 *param_6,char param_7)
{
  int iVar1;
  byte bVar2;
  undefined *puVar3;
  undefined *puVar4;
  byte bVar5;
  byte *local_8;
  byte *local_4;
  
  local_8 = NULL;
  local_4 = NULL;
  *(undefined1 *)((int)param_1 + 0x36e) = 0;
  puVar3 = FUN_00465410(param_1,param_2,param_3,param_4);
  if (puVar3 == NULL) {
    if ((0 < param_4) &&
       (puVar4 = FUN_00465410(param_1,param_2,param_3,param_4 + -1),
       puVar4 != NULL)) {
      local_4 = &DAT_00662db0 + (uint)((byte)puVar4[0xb] >> 2) * 0xc;
    }
  }
  else {
    local_4 = &DAT_00662db0 + (uint)((byte)puVar3[0xb] >> 2) * 0xc;
  }
  switch(param_5) {
  case 1:
    if (puVar3 != NULL) {
      if (param_3 == 0) {
        return 1;
      }
      iVar1 = (uint)((byte)puVar3[0xb] >> 2) * 0xc;
      local_8 = &DAT_00662db0 + iVar1;
      if (local_8 != NULL) {
        bVar2 = *local_8;
        if (bVar2 == 1) {
          if ((&DAT_00662db2)[iVar1] == '\0') {
            param_3 = param_3 + -1;
            puVar3 = FUN_00465410(param_1,param_2,param_3,param_4 + 1);
            if (puVar3 != NULL) {
              bVar2 = puVar3[7];
LAB_00465a25:
              if ((bVar2 & 4) != 0) {
                return 1;
              }
            }
LAB_00465a2b:
            puVar3 = FUN_00465410(param_1,param_2,param_3,param_4 + 1);
            if (puVar3 != NULL) {
              if (param_7 == '\0') {
                return 0;
              }
              *param_6 = 1;
              return 0;
            }
            puVar3 = FUN_00465410(param_1,param_2,param_3,param_4);
            if (puVar3 != NULL) {
              if ((puVar3[0xb] & 3) == 0) {
                *(undefined1 *)((int)param_1 + 0x36e) = 1;
                return 1;
              }
LAB_00465dac:
              if (param_7 == '\0') {
                return 0;
              }
              *param_6 = 1;
              return 0;
            }
            goto LAB_00465924;
          }
        }
        else if ((bVar2 < 3) || (4 < bVar2)) {
          if ((puVar3[5] & 4) != 0) {
            return 1;
          }
        }
        else {
          if ((param_3 < 1) ||
             (puVar4 = FUN_00465410(param_1,param_2,param_3 + -1,param_4),
             puVar4 == NULL)) goto LAB_00465924;
          bVar2 = puVar4[0xb];
          if ((((bVar2 & 0xfc) != 0) &&
              ((((bVar2 & 0xfc) < 0xb4 && ((bVar2 & 3) != 0)) &&
               ((&DAT_00662db2)[(uint)(bVar2 >> 2) * 0xc] !=
                (&DAT_00662db2)[iVar1])))) &&
             (*local_8 != (&DAT_00662db0)[(uint)(bVar2 >> 2) * 0xc])) {
            *(undefined1 *)((int)param_1 + 0x36e) = 1;
            return 1;
          }
        }
        if ((puVar3[5] & 4) != 0) {
          return 1;
        }
      }
    }
    param_3 = param_3 + -1;
    puVar3 = FUN_00465410(param_1,param_2,param_3,param_4);
    if (puVar3 != NULL) {
      if ((puVar3[7] & 4) != 0) {
        return 1;
      }
      bVar2 = puVar3[0xb];
      if ((((bVar2 & 0xfc) != 0) && ((bVar2 & 0xfc) < 0xb4)) &&
         ((bVar2 & 3) != 0)) {
        bVar5 = (&DAT_00662db0)[(uint)(bVar2 >> 2) * 0xc];
        puVar3 = &DAT_00662db0 + (uint)(bVar2 >> 2) * 0xc;
        switch(bVar5) {
        case 1:
        case 2:
          goto switchD_0046575a_caseD_4;
        case 3:
        case 4:
          goto switchD_00465edb_caseD_1;
        default:
          return 1;
        }
      }
    }
    break;
  case 2:
    if (puVar3 != NULL) {
      if (param_3 == 0xff) {
        return 1;
      }
      iVar1 = (uint)((byte)puVar3[0xb] >> 2) * 0xc;
      local_8 = &DAT_00662db0 + iVar1;
      if (local_8 != NULL) {
        bVar2 = *local_8;
        if (bVar2 == 2) {
          if ((&DAT_00662db2)[iVar1] == '\0') {
            param_3 = param_3 + 1;
            puVar3 = FUN_00465410(param_1,param_2,param_3,param_4 + 1);
            if (puVar3 != NULL) {
              bVar2 = puVar3[5];
              goto LAB_00465a25;
            }
            goto LAB_00465a2b;
          }
        }
        else if ((bVar2 < 3) || (4 < bVar2)) {
          if ((puVar3[7] & 4) != 0) {
            return 1;
          }
        }
        else {
          puVar4 = FUN_00465410(param_1,param_2,param_3 + 1,param_4);
          if (puVar4 == NULL) goto LAB_00465924;
          bVar2 = puVar4[0xb];
          if (((((bVar2 & 0xfc) != 0) && ((bVar2 & 0xfc) < 0xb4)) &&
              ((bVar2 & 3) != 0)) &&
             (((&DAT_00662db2)[(uint)(bVar2 >> 2) * 0xc] !=
               (&DAT_00662db2)[iVar1] &&
              (*local_8 != (&DAT_00662db0)[(uint)(bVar2 >> 2) * 0xc])))) {
            *(undefined1 *)((int)param_1 + 0x36e) = 1;
            return 1;
          }
        }
      }
      if ((puVar3[7] & 4) != 0) {
        return 1;
      }
    }
    param_3 = param_3 + 1;
    puVar3 = FUN_00465410(param_1,param_2,param_3,param_4);
    if (puVar3 != NULL) {
      if ((puVar3[5] & 4) != 0) {
        return 1;
      }
      bVar2 = puVar3[0xb];
      if ((((bVar2 & 0xfc) != 0) && ((bVar2 & 0xfc) < 0xb4)) &&
         ((bVar2 & 3) != 0)) {
        bVar5 = (&DAT_00662db0)[(uint)(bVar2 >> 2) * 0xc];
        puVar3 = &DAT_00662db0 + (uint)(bVar2 >> 2) * 0xc;
        switch(bVar5) {
        case 1:
        case 2:
          goto switchD_0046575a_caseD_4;
        case 3:
        case 4:
          goto switchD_00465edb_caseD_1;
        default:
          return 1;
        }
      }
    }
    break;
  case 3:
    if (puVar3 != NULL) {
      if (param_2 == 0xff) {
        return 1;
      }
      iVar1 = (uint)((byte)puVar3[0xb] >> 2) * 0xc;
      local_8 = &DAT_00662db0 + iVar1;
      if (local_8 != NULL) {
        bVar2 = *local_8;
        if (bVar2 == 0) {
LAB_00465c25:
          if ((puVar3[3] & 4) != 0) {
            return 1;
          }
        }
        else if (bVar2 < 3) {
          puVar4 = FUN_00465410(param_1,param_2 + 1,param_3,param_4);
          if (puVar4 == NULL) goto LAB_00465924;
          bVar2 = puVar4[0xb];
          if (((((bVar2 & 0xfc) != 0) && ((bVar2 & 0xfc) < 0xb4)) &&
              ((bVar2 & 3) != 0)) &&
             (((&DAT_00662db2)[(uint)(bVar2 >> 2) * 0xc] !=
               (&DAT_00662db2)[iVar1] &&
              (*local_8 != (&DAT_00662db0)[(uint)(bVar2 >> 2) * 0xc])))) {
            *(undefined1 *)((int)param_1 + 0x36e) = 1;
            return 1;
          }
        }
        else {
          if (bVar2 != 4) goto LAB_00465c25;
          if ((&DAT_00662db2)[iVar1] == '\0') {
            param_2 = param_2 + 1;
            puVar3 = FUN_00465410(param_1,param_2,param_3,param_4 + 1);
            if ((puVar3 != NULL) && ((puVar3[1] & 4) != 0)) {
              return 1;
            }
            puVar3 = FUN_00465410(param_1,param_2,param_3,param_4 + 1);
            if (puVar3 == NULL) {
              puVar3 = FUN_00465410(param_1,param_2,param_3,param_4);
              if (puVar3 != NULL) {
                if ((puVar3[0xb] & 3) == 0) {
                  *(undefined1 *)((int)param_1 + 0x36e) = 1;
                  return 1;
                }
LAB_00465de7:
                if (param_7 == '\0') {
                  return 0;
                }
                *param_6 = 1;
                return 0;
              }
              goto LAB_00465924;
            }
            goto LAB_00465dac;
          }
        }
        if ((puVar3[3] & 4) != 0) {
          return 1;
        }
      }
    }
    puVar3 = FUN_00465410(param_1,param_2 + 1,param_3,param_4);
    if (puVar3 != NULL) {
      if ((puVar3[1] & 4) != 0) {
        return 1;
      }
      bVar2 = puVar3[0xb];
      if ((((bVar2 & 0xfc) != 0) && ((bVar2 & 0xfc) < 0xb4)) &&
         ((bVar2 & 3) != 0)) {
        bVar5 = (&DAT_00662db0)[(uint)(bVar2 >> 2) * 0xc];
        puVar3 = &DAT_00662db0 + (uint)(bVar2 >> 2) * 0xc;
        switch(bVar5) {
        case 1:
        case 2:
switchD_00465edb_caseD_1:
          if (local_8 == NULL) {
            return 1;
          }
          if (puVar3[2] == local_8[2]) {
            return 0;
          }
          if (*local_8 == bVar5) {
            return 0;
          }
          return 1;
        case 3:
        case 4:
          goto switchD_0046575a_caseD_4;
        default:
          return 1;
        }
      }
    }
    if (param_4 < 1) goto LAB_00465cf7;
    puVar3 = FUN_00465410(param_1,param_2 + 1,param_3,param_4 + -1);
    if ((puVar3 == NULL) || (bVar2 = puVar3[0xb], (bVar2 & 3) == 0))
    goto LAB_00465cf9;
    if ((bVar2 & 0xfc) == 0) {
      return 0;
    }
    if (0xb3 < (bVar2 & 0xfc)) {
      return 0;
    }
    bVar2 = (&DAT_00662db0)[(uint)(bVar2 >> 2) * 0xc];
    if ((2 < bVar2) && (bVar2 < 5)) {
      *param_6 = 0xff;
      return 0;
    }
    goto LAB_00465914;
  case 4:
    if (puVar3 != NULL) {
      if (param_2 == 0) {
        return 1;
      }
      iVar1 = (uint)((byte)puVar3[0xb] >> 2) * 0xc;
      local_8 = &DAT_00662db0 + iVar1;
      if (local_8 != NULL) {
        bVar2 = *local_8;
        if (bVar2 == 0) {
LAB_00465e6d:
          if ((puVar3[1] & 4) != 0) {
            return 1;
          }
        }
        else if (bVar2 < 3) {
          puVar4 = FUN_00465410(param_1,param_2 + -1,param_3,param_4);
          if (puVar4 == NULL) goto LAB_00465924;
          bVar2 = puVar4[0xb];
          if (((((bVar2 & 0xfc) != 0) && ((bVar2 & 0xfc) < 0xb4)) &&
              ((bVar2 & 3) != 0)) &&
             (((&DAT_00662db2)[(uint)(bVar2 >> 2) * 0xc] !=
               (&DAT_00662db2)[iVar1] &&
              (*local_8 != (&DAT_00662db0)[(uint)(bVar2 >> 2) * 0xc])))) {
            *(undefined1 *)((int)param_1 + 0x36e) = 1;
            return 1;
          }
        }
        else {
          if (bVar2 != 3) goto LAB_00465e6d;
          if ((&DAT_00662db2)[iVar1] == '\0') {
            param_2 = param_2 + -1;
            puVar3 = FUN_00465410(param_1,param_2,param_3,param_4 + 1);
            if ((puVar3 != NULL) && ((puVar3[3] & 4) != 0)) {
              return 1;
            }
            puVar3 = FUN_00465410(param_1,param_2,param_3,param_4 + 1);
            if (puVar3 != NULL) goto LAB_00465dac;
            puVar3 = FUN_00465410(param_1,param_2,param_3,param_4);
            if ((puVar3 != NULL) && ((puVar3[0xb] & 3) != 0)) goto LAB_00465de7;
            goto LAB_00465924;
          }
        }
        if ((puVar3[1] & 4) != 0) {
          return 1;
        }
      }
    }
    puVar3 = FUN_00465410(param_1,param_2 + -1,param_3,param_4);
    if (puVar3 != NULL) {
      if ((puVar3[3] & 4) != 0) {
        return 1;
      }
      bVar2 = puVar3[0xb];
      if ((((bVar2 & 0xfc) != 0) && ((bVar2 & 0xfc) < 0xb4)) &&
         ((bVar2 & 3) != 0)) {
        bVar5 = (&DAT_00662db0)[(uint)(bVar2 >> 2) * 0xc];
        puVar3 = &DAT_00662db0 + (uint)(bVar2 >> 2) * 0xc;
        switch(bVar5) {
        case 1:
        case 2:
          goto switchD_00465edb_caseD_1;
        case 3:
        case 4:
          goto switchD_0046575a_caseD_4;
        default:
          return 1;
        }
      }
    }
    if (param_4 < 1) goto LAB_00465cf7;
    puVar3 = FUN_00465410(param_1,param_2 + -1,param_3,param_4 + -1);
    if ((puVar3 != NULL) && (bVar2 = puVar3[0xb], (bVar2 & 3) != 0)) {
      if ((bVar2 & 0xfc) == 0) {
        return 0;
      }
      if (0xb3 < (bVar2 & 0xfc)) {
        return 0;
      }
      bVar2 = (&DAT_00662db0)[(uint)(bVar2 >> 2) * 0xc];
      if ((2 < bVar2) && (bVar2 < 5)) {
        *(undefined1 *)((int)param_1 + 0x36e) = 1;
        goto LAB_00465f75;
      }
      goto LAB_00465914;
    }
    goto LAB_00465cf9;
  default:
    goto switchD_0046575a_caseD_4;
  }
  if (param_4 < 1) {
LAB_00465cf7:
    puVar3 = NULL;
  }
  else {
    puVar3 = FUN_00465410(param_1,param_2,param_3,param_4 + -1);
    if ((puVar3 != NULL) && (bVar2 = puVar3[0xb], (bVar2 & 3) != 0)) {
      if ((bVar2 & 0xfc) == 0) {
        return 0;
      }
      if (0xb3 < (bVar2 & 0xfc)) {
        return 0;
      }
      bVar2 = (&DAT_00662db0)[(uint)(bVar2 >> 2) * 0xc];
      if ((bVar2 != 0) && (bVar2 < 3)) {
LAB_00465f75:
        *param_6 = 0xff;
        return 0;
      }
LAB_00465914:
      if ((local_4 != NULL) && (*local_4 == bVar2)) {
        return 0;
      }
LAB_00465924:
      *(undefined1 *)((int)param_1 + 0x36e) = 1;
      return 1;
    }
  }
LAB_00465cf9:
  *(undefined1 *)((int)param_1 + 0x36e) = 1;
  if ((puVar3 == NULL) || (puVar3[10] == '\0')) {
    return 1;
  }
  *(undefined1 *)((int)param_1 + 0x36f) = 1;
switchD_0046575a_caseD_4:
  return 0;
}


// 0x00465fe0: MapRelatedStruct::sub_465FE0
// IDA: MapRelatedStruct::sub_465FE0
// Ghidra: ---
char gta2::MapRelatedStruct_sub_465FE0(struct MapRelatedStruct *self, AudioSourceParams *arg0)
{
  int v2; // eax
  int v3; // edi
  int v4; // esi
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int v9; // [esp+10h] [ebp-38h]
  S202 a2; // [esp+18h] [ebp-30h] BYREF
  int v12[2]; // [esp+38h] [ebp-10h] BYREF
  int v13[2]; // [esp+40h] [ebp-8h] BYREF

  gta2::AudioSourceParams_sub_4BA5E0(arg0);
  v2 = gta2::sub_463760(arg0);
  v3 = dword_662BAC;
  v9 = v2;
  if ( (int)dword_662BAC > a5 )
    return 0;
  while ( 1 )
  {
    v4 = ::arg0;
    if ( ::arg0 <= dword_662BF8 )
      break;
LABEL_15:
    if ( ++v3 > a5 )
      return 0;
  }
  v5 = ::arg0 + 1;
  while ( 1 )
  {
    v6 = gta2::MapRelatedStruct_sub_4653C0(self, v4, v3, v9);
    if ( v6 )
    {
      v7 = *(_BYTE *)(v6 + 11) & 0xFC;
      if ( v7 >= 180 && v7 <= 208 )
      {
        if ( v7 == 180 || v7 == 192 || v7 == 196 || v7 == 208 )
        {
          gta2::S202_sub_41F980((struct S202 *)&a2.field_10, v3 + 1);
          gta2::S202_sub_41F980((struct S202 *)&a2.pPlayer, v4);
          gta2::Weapon_sub_432860((struct Weapon *)v13, &a2.pPlayer, &a2.field_10);
          gta2::S202_sub_41F980((struct S202 *)&a2.field_18, v3);
          gta2::S202_sub_41F980((struct S202 *)&a2.field_1C, v5);
          gta2::Weapon_sub_432860((struct Weapon *)v12, &a2.field_1C, &a2.field_18);
        }
        else
        {
          gta2::S202_sub_41F980(&a2, v3);
          gta2::S202_sub_41F980((struct S202 *)&a2.S202, v4);
          gta2::Weapon_sub_432860((struct Weapon *)v13, &a2.S202, &a2);
          gta2::S202_sub_41F980((struct S202 *)&a2.CarSystemManager, v3 + 1);
          gta2::S202_sub_41F980((struct S202 *)&a2.field_C, v5);
          gta2::Weapon_sub_432860((struct Weapon *)v12, &a2.field_C, &a2.CarSystemManager);
        }
        if ( sub_463690(arg0, (int)v13, (int)v12) )
          return 1;
      }
    }
    ++v4;
    ++v5;
    if ( v4 > dword_662BF8 )
      goto LABEL_15;
  }
}


// 0x00466170: MapRelatedStruct::sub_466170
// IDA: MapRelatedStruct::sub_466170
// Ghidra: FUN_00466170
byte gta2::MapRelatedStruct_sub_466170(int param_1)
{
  byte bVar1;
  int iVar2;
  Point2D *self;
  struct SpriteS1 *pSVar3;
  struct SpriteS1 *pSVar4;
  struct MapRelatedStruct *in_ECX;
  undefined4 *puVar5;
  struct SpriteS1 *extraout_ECX;
  uint select;
  struct SpriteS1 **ppSVar6;
  int iVar7;
  int iVar8;
  struct SpriteS1 *pSVar9;
  struct SpriteS1 *pS127;
  int local_40;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  struct SpriteS1 *local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  struct SpriteS1 *local_1c;
  undefined1 local_18 [8];
  undefined1 local_10 [12];
  struct SpriteS1 *pS38;
  
  iVar7 = _DAT_00662bac;
  if (_DAT_00662bac <= _DAT_00662bfc) {
    do {
      iVar8 = _DAT_00662bd4;
      local_40 = _DAT_00662bd4;
      if (_DAT_00662bd4 <= _DAT_00662bf8) {
        do {
          local_40 = local_40 + 1;
          iVar2 = gta2::MapRelatedStruct_sub_4653C0(in_ECX,iVar8,iVar7,param_1);
          if (((iVar2 != 0) &&
              (select = *(byte *)(iVar2 + 0xb) & 0xfc, 0xb3 < select)) &&
             (select < 0xd1)) {
            if (((select == 0xb4) || (select == 0xc0)) ||
               ((select == 0xc4 || (select == 0xd0)))) {
              gta2::S202_sub_41F980((struct SpriteS1 *)&local_28,iVar7 + 1);
              gta2::S202_sub_41F980((struct SpriteS1 *)&local_24,iVar8);
              FUN_00432860(local_10,&local_24,&local_28);
              gta2::S202_sub_41F980((struct SpriteS1 *)&local_20,iVar7);
              gta2::S202_sub_41F980((struct SpriteS1 *)&local_1c,local_40);
              puVar5 = &local_20;
              ppSVar6 = &local_1c;
            }
            else {
              gta2::S202_sub_41F980((struct SpriteS1 *)&local_38,iVar7);
              gta2::S202_sub_41F980((struct SpriteS1 *)&local_34,iVar8);
              FUN_00432860(local_10,&local_34,&local_38);
              gta2::S202_sub_41F980((struct SpriteS1 *)&local_30,iVar7 + 1);
              gta2::S202_sub_41F980((struct SpriteS1 *)&local_2c,local_40);
              puVar5 = &local_30;
              ppSVar6 = &local_2c;
            }
            FUN_00432860(local_18,ppSVar6,puVar5);
            bVar1 = gta2::FUN_004bb9c0(_DAT_00662bf0,(int)local_10,(int)local_18);
            if (bVar1 != 0) {
              self = (Point2D *)gta2::sub_4828F0(gObject,select);
              pS38 = *(SpriteS1 **)(self->Array_24 + 4);
              pSVar4 = (struct SpriteS1 *)&local_1c;
              pSVar9 = (struct SpriteS1 *)&DAT_00663164;
              gta2::S202_sub_41F980((struct SpriteS1 *)&local_20,iVar7);
              pSVar3 = gta2::S202_sub_401B20(self,pSVar4,(struct S127 *)pSVar9);
              pSVar4 = (struct SpriteS1 *)&local_24;
              pS127 = (struct SpriteS1 *)&DAT_00663164;
              pSVar9 = pSVar4;
              gta2::S202_sub_41F980((struct SpriteS1 *)&local_28,iVar8);
              pSVar9 = gta2::S202_sub_401B20((Point2D *)pSVar4,pSVar9,(struct S127 *)pS127);
              local_2c = (struct SpriteS1 *)&stack0xffffffac;
              pSVar4 = extraout_ECX;
              gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffac,param_1);
              gta2::SpriteS1_sub_420600((Sprite *)pS38,(int)pSVar9->FirstElement,
                                  (int)pSVar3->FirstElement,(int)pSVar4);
              gta2::SpriteS1_sub_4BCB40((Sprite *)pS38);
              FUN_0040fee0(&PTR_005e6874,pS38);
              return 1;
            }
          }
          iVar8 = iVar8 + 1;
        } while (iVar8 <= _DAT_00662bf8);
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 <= _DAT_00662bfc);
  }
  return 0;
}


// 0x00466380: MapRelatedStruct::sub_466380
// IDA: MapRelatedStruct::sub_466380
// Ghidra: FUN_00466380
undefined4 gta2::MapRelatedStruct_sub_466380(void *param_1,int param_2,int param_3,int param_4,int param_5, int param_6)
{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  bool bVar4;
  
  if (param_4 <= param_5) {
    do {
      bVar4 = SBORROW4(param_2,param_3);
      iVar1 = param_2 - param_3;
      iVar3 = param_2;
      if (param_2 <= param_3) {
        do {
          if (((bVar4 != iVar1 < 0) &&
              (((puVar2 = FUN_00465410(param_1,iVar3,param_4,param_6),
                puVar2 != NULL && ((puVar2[3] & 4) != 0)) ||
               ((puVar2 = FUN_00465410(param_1,iVar3 + 1,param_4,param_6),
                puVar2 != NULL && ((puVar2[1] & 4) != 0)))))) ||
             ((param_4 < param_5 &&
              (((puVar2 = FUN_00465410(param_1,iVar3,param_4,param_6),
                puVar2 != NULL && ((puVar2[7] & 4) != 0)) ||
               ((puVar2 = FUN_00465410(param_1,iVar3,param_4 + 1,param_6),
                puVar2 != NULL && ((puVar2[5] & 4) != 0)))))))) {
            return 1;
          }
          iVar3 = iVar3 + 1;
          bVar4 = SBORROW4(iVar3,param_3);
          iVar1 = iVar3 - param_3;
        } while (iVar3 <= param_3);
      }
      param_4 = param_4 + 1;
    } while (param_4 <= param_5);
  }
  return 0;
}


// 0x00466430: MapRelatedStruct::sub_466430
// IDA: MapRelatedStruct::sub_466430
// Ghidra: FUN_00466430
uint gta2::MapRelatedStruct_sub_466430(void *param_1,int param_2,int param_3,int param_4,uint param_5, int param_6)
{
  int iVar1;
  char cVar2;
  byte bVar3;
  undefined *puVar4;
  undefined3 extraout_var;
  ushort *puVar5;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 uVar6;
  struct SpriteS1 *extraout_ECX;
  struct SpriteS1 *extraout_ECX_00;
  struct SpriteS1 *extraout_ECX_01;
  struct SpriteS1 *extraout_ECX_02;
  struct SpriteS1 *extraout_ECX_03;
  struct SpriteS1 *extraout_ECX_04;
  struct SpriteS1 *extraout_ECX_05;
  struct SpriteS1 *extraout_ECX_06;
  struct SpriteS1 *extraout_ECX_07;
  struct SpriteS1 *extraout_ECX_08;
  struct SpriteS1 *extraout_ECX_09;
  struct SpriteS1 *extraout_ECX_10;
  int iVar7;
  bool bVar8;
  struct SpriteS1 *pSVar9;
  struct SpriteS1 *pSVar10;
  struct SpriteS1 *pSVar11;
  
  if (param_4 <= (int)param_5) {
    do {
      bVar8 = SBORROW4(param_2,param_3);
      iVar1 = param_2 - param_3;
      iVar7 = param_2;
      if (param_2 <= param_3) {
        do {
          if (bVar8 != iVar1 < 0) {
            puVar4 = FUN_00465410(param_1,iVar7,param_4,param_6);
            if ((puVar4 != NULL) &&
               ((*(ushort *)(puVar4 + 2) & (ushort)_DAT_00662bec) != 0)) {
              cVar2 = FUN_004634b0();
              if (cVar2 == '\0') {
                pSVar11 = extraout_ECX;
                gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffec,iVar7 + 1);
                pSVar10 = extraout_ECX_00;
                gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_4 + 1)
                ;
                pSVar9 = extraout_ECX_01;
                gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_4);
                bVar8 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar9,(int)pSVar10,
                                     (int)pSVar11);
                uVar6 = extraout_var;
                if (bVar8) goto LAB_00466610;
              }
            }
            puVar5 = (ushort *)FUN_00465410(param_1,iVar7 + 1,param_4,param_6);
            if ((puVar5 != NULL) && ((*puVar5 & (ushort)_DAT_00662bec) != 0)) {
              cVar2 = FUN_004634b0();
              if (cVar2 == '\0') {
                pSVar11 = extraout_ECX_02;
                gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffec,iVar7 + 1);
                pSVar10 = extraout_ECX_03;
                gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_4 + 1)
                ;
                pSVar9 = extraout_ECX_04;
                gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_4);
                bVar8 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar9,(int)pSVar10,
                                     (int)pSVar11);
                uVar6 = extraout_var_00;
                if (bVar8) goto LAB_00466610;
              }
            }
          }
          if (param_4 < (int)param_5) {
            puVar4 = FUN_00465410(param_1,iVar7,param_4,param_6);
            if ((puVar4 != NULL) &&
               ((*(ushort *)(puVar4 + 6) & (ushort)_DAT_00662bec) != 0)) {
              cVar2 = FUN_00463480();
              if (cVar2 == '\0') {
                pSVar11 = extraout_ECX_05;
                gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffec,param_4 + 1)
                ;
                pSVar10 = extraout_ECX_06;
                gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,iVar7 + 1);
                pSVar9 = extraout_ECX_07;
                gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,iVar7);
                bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar9,pSVar10,pSVar11);
                uVar6 = extraout_var_01;
                if (bVar3 != 0) goto LAB_00466610;
              }
            }
            puVar4 = FUN_00465410(param_1,iVar7,param_4 + 1,param_6);
            if ((puVar4 != NULL) &&
               ((*(ushort *)(puVar4 + 4) & (ushort)_DAT_00662bec) != 0)) {
              cVar2 = FUN_00463480();
              if (cVar2 == '\0') {
                pSVar11 = extraout_ECX_08;
                gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffec,param_4 + 1)
                ;
                pSVar10 = extraout_ECX_09;
                gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,iVar7 + 1);
                pSVar9 = extraout_ECX_10;
                gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,iVar7);
                bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar9,pSVar10,pSVar11);
                uVar6 = extraout_var_02;
                if (bVar3 != 0) {
LAB_00466610:
                  return CONCAT31(uVar6,1);
                }
              }
            }
          }
          iVar7 = iVar7 + 1;
          bVar8 = SBORROW4(iVar7,param_3);
          iVar1 = iVar7 - param_3;
        } while (iVar7 <= param_3);
      }
      param_4 = param_4 + 1;
    } while (param_4 <= (int)param_5);
  }
  return param_5 & 0xffffff00;
}


// 0x00466620: MapRelatedStruct::sub_466620
// IDA: MapRelatedStruct::sub_466620
// Ghidra: FUN_00466620
undefined1 gta2::MapRelatedStruct_sub_466620(MapRelatedStruct *param_1,char param_2)
{
  byte bVar1;
  bool bVar2;
  int iVar3;
  struct Car *self;
  undefined3 extraout_var;
  uint uVar4;
  int iVar5;
  int iVar6;
  struct Car *pCVar7;
  undefined1 local_5;
  undefined1 local_4 [4];
  
  iVar3 = DecoderFloat(&param_2);
  pCVar7 = (struct Car *)&DAT_00662cfc;
  local_5 = 0;
  self = (struct Car *)FUN_0042a630(local_4,&param_2);
  bVar2 = gta2::Car_IsTrainOrTrainCarriage(self,pCVar7);
  param_2 = CONCAT31(extraout_var,bVar2) != 0;
  iVar6 = _DAT_00662bac;
  if (_DAT_00662bac <= _DAT_00662bfc) {
    do {
      iVar5 = _DAT_00662bd4;
      if (_DAT_00662bd4 <= _DAT_00662bf8) {
        do {
          gMaxZForTile = (void *)gta2::MapRelatedStruct_sub_4653C0(param_1,iVar5,iVar6,iVar3);
          if (gMaxZForTile != NULL) {
            bVar1 = *(byte *)((int)gMaxZForTile + 0xb);
            if ((((bVar1 & 0xfc) == 0) || (0xb3 < (bVar1 & 0xfc))) ||
               ((bVar1 & 3) == 0)) {
              if ((param_2 != '\0') && ((bVar1 & 0xfc) == 0xfc)) {
                return 2;
              }
            }
            else if (param_2 == '\0') {
              uVar4 = (uint)(bVar1 >> 2);
              _DAT_00662be0 = &DAT_00662db0 + uVar4 * 0xc;
              if ((uint)(byte)(&DAT_00662db2)[uVar4 * 0xc] ==
                  (byte)(&DAT_00662db1)[uVar4 * 0xc] - 1) {
                local_5 = 1;
              }
            }
            else {
              local_5 = 1;
            }
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 <= _DAT_00662bf8);
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 <= _DAT_00662bfc);
  }
  return local_5;
}


// 0x00466910: MapRelatedStruct::sub_466910
// IDA: MapRelatedStruct::sub_466910
// Ghidra: ---
int gta2::MapRelatedStruct_sub_466910(struct MapRelatedStruct *self, int a2, int a3, _DWORD *a4)
{
  struct Map *Map; // esi
  int v5; // edx
  int v6; // eax
  int v7; // ecx
  unsigned __int8 *v8; // eax
  int v9; // ebp
  int v10; // ecx
  int v11; // edi
  unsigned __int8 *i; // esi
  int result; // eax

  Map = self->Map_;
  v5 = *(_DWORD *)gta2::Map_sub_42A830(self->Map_, a3, a2);
  v6 = Map->field_40008;
  v7 = *(unsigned __int8 *)(v6 + 4 * v5 + 1);
  v8 = (unsigned __int8 *)(v6 + 4 * v5);
  v9 = v7;
  v10 = *v8 - v7 - 1;
  if ( v10 < 0 )
    return 0;
  v11 = Map->field_4000C;
  for ( i = &v8[4 * v10 + 4]; ; i -= 4 )
  {
    result = v11 + 12 * *(_DWORD *)i;
    dword_662B90 = result;
    if ( (*(_BYTE *)(result + 11) & 3) != 0 )
      break;
    if ( --v10 < 0 )
      return 0;
  }
  if ( (*(_BYTE *)(result + 11) & 3) != 2 )
    return 0;
  *a4 = v10 + v9;
  return result;
}


// 0x00466990: MapRelatedStruct::FindMaxZForTile
// IDA: MapRelatedStruct::FindMaxZForTile
// Ghidra: ---
_WORD * gta2::MapRelatedStruct_FindMaxZForTile(struct MapRelatedStruct *self, int a2, int a3, _DWORD *a4)
{
  struct Map *Map; // esi
  int v5; // edx
  int v6; // eax
  int v7; // ecx
  unsigned __int8 *v8; // eax
  int v9; // edi
  int v10; // ecx
  int v11; // esi
  unsigned __int8 *i; // edx
  bool v13; // zf
  _WORD *result; // eax

  Map = self->Map_;
  v5 = *(_DWORD *)gta2::Map_sub_42A830(self->Map_, a3, a2);
  v6 = Map->field_40008;
  v7 = *(unsigned __int8 *)(v6 + 4 * v5 + 1);
  v8 = (unsigned __int8 *)(v6 + 4 * v5);
  v9 = v7;
  v10 = *v8 - v7 - 1;
  if ( v10 < 0 )
    return 0;
  v11 = Map->field_4000C;
  for ( i = &v8[4 * v10 + 4]; ; i -= 4 )
  {
    v13 = (*(_BYTE *)(v11 + 12 * *(_DWORD *)i + 11) & 3) == 0;
    result = (_WORD *)(v11 + 12 * *(_DWORD *)i);
    dword_662B90 = result;
    if ( !v13 )
      break;
    if ( --v10 < 0 )
      return 0;
  }
  *a4 = v10 + v9;
  return result;
}


// 0x00466a00: MapRelatedStruct::sub_466A00
// IDA: MapRelatedStruct::sub_466A00
// Ghidra: ---
_WORD * gta2::MapRelatedStruct_sub_466A00(struct MapRelatedStruct *self, int a2, int a3, int *a4)
{
  struct Map *Map; // esi
  int v5; // edx
  int v6; // eax
  int v7; // ecx
  unsigned __int8 *v8; // edx
  int v9; // eax
  int v10; // edi
  int v11; // ecx
  int v12; // ecx
  int v13; // esi
  unsigned __int8 *i; // edx
  bool v15; // zf
  _WORD *result; // eax

  Map = self->Map_;
  v5 = *(_DWORD *)gta2::Map_sub_42A830(self->Map_, a3, a2);
  v6 = Map->field_40008;
  v7 = *(unsigned __int8 *)(v6 + 4 * v5 + 1);
  v8 = (unsigned __int8 *)(v6 + 4 * v5);
  v9 = *a4;
  v10 = v7;
  if ( *a4 < v7 )
    return 0;
  v11 = *v8;
  v12 = v9 < v11 ? v9 - v10 : v11 - v10 - 1;
  if ( v12 < 0 )
    return 0;
  v13 = Map->field_4000C;
  for ( i = &v8[4 * v12 + 4]; ; i -= 4 )
  {
    v15 = (*(_BYTE *)(v13 + 12 * *(_DWORD *)i + 11) & 3) == 0;
    result = (_WORD *)(v13 + 12 * *(_DWORD *)i);
    dword_662B90 = result;
    if ( !v15 )
      break;
    if ( --v12 < 0 )
      return 0;
  }
  *a4 = v12 + v10;
  return result;
}


// 0x00466af0: MapRelatedStruct::sub_466AF0
// IDA: MapRelatedStruct::sub_466AF0
// Ghidra: FUN_00466af0
undefined4 gta2::MapRelatedStruct_sub_466AF0(MapRelatedStruct *param_1)
{
  char cVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  struct MapRelatedStruct *local_4;
  
  local_4 = param_1;
  pvVar2 = gta2::Player_sub_401B40((SpawnPoint *)&stack0x0000000c,(GlassInfo *)&local_4,
                      (struct S127 *)&DAT_00662c98);
  iVar3 = DecoderFloat(pvVar2);
  iVar4 = DecoderFloat(&stack0x00000008);
  iVar5 = DecoderFloat(&stack0x00000004);
  pvVar2 = (void *)gta2::MapRelatedStruct_sub_4653C0(param_1,iVar5,iVar4,iVar3);
  gMaxZForTile = pvVar2;
  if (pvVar2 != NULL) {
    cVar1 = FUN_00462fb0(*(ushort *)((int)pvVar2 + 8) & 0x3ff);
    if (cVar1 != '\0') {
      return 7;
    }
    if ((*(byte *)((int)pvVar2 + 0xb) & 3) != 0) {
      return 0;
    }
  }
  return 5;
}


// 0x00466b70: MapRelatedStruct::sub_466B70
// IDA: MapRelatedStruct::sub_466B70
// Ghidra: FUN_00466b70
uint gta2::MapRelatedStruct_sub_466B70(MapRelatedStruct *param_1,undefined4 param_2,SpriteS1 *param_3, SpriteS1 *param_4)
{
  undefined *puVar1;
  byte bVar2;
  struct SpriteS1 *pSVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  void *pvVar9;
  Point2D *self;
  struct SpriteS1 *pSVar10;
  undefined3 extraout_var;
  struct S127 *pSVar11;
  undefined1 *pS110;
  int *piVar12;
  undefined1 local_8 [8];
  
  pSVar3 = param_4;
  iVar5 = DecoderFloat(param_4);
  iVar6 = DecoderFloat(&param_3);
  iVar7 = DecoderFloat(&param_2);
  gMaxZForTile = (void *)gta2::MapRelatedStruct_sub_4653C0(param_1,iVar7,iVar6,iVar5)
  ;
  pvVar9 = gMaxZForTile;
  if (gMaxZForTile == NULL) {
switchD_00466bdc_caseD_0:
    return (uint)pvVar9 & 0xffffff00;
  }
  bVar2 = *(byte *)((int)gMaxZForTile + 0xb);
  pvVar9 = (void *)CONCAT31((int3)((uint)gMaxZForTile >> 8),bVar2);
  if ((bVar2 & 3) == 0) goto switchD_00466bdc_caseD_0;
  pvVar9 = (void *)(uint)(byte)(&DAT_00662db0)[(uint)(bVar2 >> 2) * 0xc];
  iVar5 = (uint)(bVar2 >> 2) * 0xc;
  puVar1 = &DAT_00662db0 + iVar5;
  _DAT_00662be0 = puVar1;
  switch(pvVar9) {
  case NULL:
    goto switchD_00466bdc_caseD_0;
  case (void *)0x1:
    pSVar11 = (struct S127 *)FUN_0042a630(&param_2,&param_3);
    puVar8 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)&DAT_00662c98,(GlassInfo *)&param_3,
                        pSVar11);
    param_3 = (struct SpriteS1 *)*puVar8;
    break;
  case (void *)0x2:
    puVar8 = (undefined4 *)FUN_0042a630(&param_4,&param_3);
    param_3 = (struct SpriteS1 *)*puVar8;
    break;
  case (void *)0x3:
    pSVar11 = (struct S127 *)FUN_0042a630(local_8,&param_2);
    puVar8 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)&DAT_00662c98,(GlassInfo *)(local_8 + 4),
                        pSVar11);
    goto LAB_00466c51;
  case (void *)0x4:
    puVar8 = (undefined4 *)FUN_0042a630(&param_4,&param_2);
LAB_00466c51:
    param_3 = (struct SpriteS1 *)*puVar8;
  }
  pSVar11 = (struct S127 *)(iVar5 + 0x662db4);
  pSVar10 = (struct SpriteS1 *)&param_3;
  piVar12 = (int *)&param_3;
  pS110 = (undefined1 *)&param_2;
  pvVar9 = (void *)FUN_004634e0(&param_4,CONCAT31((int3)((uint)pSVar10 >> 8),
                                                  (&DAT_00662db1)[iVar5]));
  self = (Point2D *)gta2::WorldCoordinateToScreenCoord(pvVar9,pS110,piVar12);
  pSVar10 = gta2::S202_sub_401B20(self,pSVar10,pSVar11);
  param_3 = pSVar10->FirstElement;
  bVar4 = gta2::Player_IsCurrentPlayer((struct Player *)&param_3,(struct Player *)&DAT_00662cfc);
  if (CONCAT31(extraout_var,bVar4) != 0) {
    param_3 = _DAT_006631ec;
  }
  pSVar11 = (struct S127 *)FUN_00462ea0(&param_2,&param_2,(uint *)pSVar3);
  pSVar10 = gta2::S202_sub_401B20((Point2D *)&param_3,(struct SpriteS1 *)&param_4,pSVar11);
  pSVar10 = pSVar10->FirstElement;
  *(SpriteS1 **)&pSVar3->FirstElement = pSVar10;
  return CONCAT31((int3)((uint)pSVar10 >> 8),*puVar1);
}


// 0x00466cf0: MapRelatedStruct::sub_466CF0
// IDA: MapRelatedStruct::sub_466CF0
// Ghidra: ---
bool gta2::MapRelatedStruct_sub_466CF0(struct MapRelatedStruct *self, int a2, int a3, int a4)
{
  int v4; // eax
  char v5; // al
  bool result; // al

  v4 = gta2::MapRelatedStruct_sub_4653C0(self, a2, a3, a4);
  result = 0;
  if ( v4 )
  {
    v5 = *(_BYTE *)(v4 + 11);
    if ( (v5 & 0xFC) != 0 && (v5 & 0xFCu) < 0xB4 && (v5 & 3) != 0 )
      return 1;
  }
  return result;
}


// 0x00466e20: MapRelatedStruct::sub_466E20
// IDA: MapRelatedStruct::sub_466E20
// Ghidra: ---
_DWORD * gta2::MapRelatedStruct_sub_466E20(struct MapRelatedStruct *self, _DWORD *arg0, int *arg4, SpriteS1 *a3, int a2)
{
  struct SpriteS1 *v6; // eax
  int v7; // eax
  struct SpriteS1 *v8; // edi
  int *v9; // ebx
  int v10; // eax
  int v11; // eax
  _DWORD *result; // eax
  int v13; // eax
  int v14; // eax
  char v15; // cl
  struct SpriteS1 **v16; // eax
  _DWORD *v17; // eax
  int v18; // [esp-8h] [ebp-18h]
  int v19; // [esp-8h] [ebp-18h]
  int v20; // [esp-4h] [ebp-14h]
  struct SpriteS1 *FirstElement; // [esp+Ch] [ebp-4h] BYREF

  v6 = sub_42A630((struct SpriteS1 *)&FirstElement, (struct S202 *)&a2);
  LOWORD(v7) = gta2::Car_sub_403820((struct Car *)v6, &unk_662CFC);
  v8 = a3;
  v9 = arg4;
  if ( v7
    && (v20 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&a2),
        v18 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&a3),
        v10 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&arg4),
        gta2::MapRelatedStruct_sub_466CF0(self, v10, v18, v20))
    && (FirstElement = gta2::sub_462EA0((struct SpriteS1 *)&FirstElement, &a2)->FirstElement,
        gta2::MapRelatedStruct_sub_466B70(self, v9, (struct S202 *)v8),
        LOBYTE(v11) = gta2::Player_CheckCondition((struct Player *)&FirstElement, &a2),
        v11) )
  {
    result = arg0;
    *arg0 = FirstElement;
  }
  else
  {
    a2 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&a2) - 1;
    v19 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&a3);
    v13 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&arg4);
    v14 = gta2::MapRelatedStruct_sub_4635F0(self, v13, v19, &a2);
    dword_662B90 = (_WORD *)v14;
    if ( v14 )
    {
      v15 = *(_BYTE *)(v14 + 11);
      if ( (v15 & 0xFC) != 0 && (v15 & 0xFCu) < 0xB4 && (v15 & 3) != 0 )
      {
        gta2::S202_sub_41F980((struct S202 *)&a2, a2);
        FirstElement = *v16;
        gta2::MapRelatedStruct_sub_466B70(self, v9, (struct S202 *)v8);
        *arg0 = FirstElement;
        return arg0;
      }
      else
      {
        gta2::S202_sub_41F980((struct S202 *)&a2, a2 + 1);
        *arg0 = *v17;
        return arg0;
      }
    }
    else
    {
      gta2::bitShiftLeft1(arg0, 1);
      return arg0;
    }
  }
  return result;
}


// 0x00466f70: MapRelatedStruct::sub_466F70
// IDA: MapRelatedStruct::sub_466F70
// Ghidra: ---
_DWORD * gta2::MapRelatedStruct_sub_466F70(struct MapRelatedStruct *self, _DWORD *arg0, S202 *a2)
{
  int v4; // eax
  int v5; // eax
  char v7; // al
  int *v8; // eax
  _DWORD *v9; // eax
  int v10; // [esp-8h] [ebp-10h]
  int v11; // [esp+4h] [ebp-4h] BYREF
  S202 a3; // [esp+14h] [ebp+Ch] BYREF

  v10 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&a3);
  v4 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&a2);
  v5 = gta2::MapRelatedStruct_sub_463570(self, v4, v10, &v11);
  dword_662B90 = (_WORD *)v5;
  if ( v5 )
  {
    v7 = *(_BYTE *)(v5 + 11);
    if ( (v7 & 0xFC) != 0 && (v7 & 0xFCu) < 0xB4 && (v7 & 3) != 0 )
    {
      gta2::S202_sub_41F980((struct S202 *)&v11, v11);
      v11 = *v8;
      gta2::MapRelatedStruct_sub_466B70(self, &a2->field_0, (struct S202 *)a3.field_0);
      *arg0 = v11;
      return arg0;
    }
    else
    {
      gta2::S202_sub_41F980(&a3, v11 + 1);
      *arg0 = *v9;
      return arg0;
    }
  }
  else
  {
    gta2::bitShiftLeft1(arg0, 0);
    return arg0;
  }
}


// 0x00467110: MapRelatedStruct::sub_467110
// IDA: MapRelatedStruct::sub_467110
// Ghidra: ---
int gta2::MapRelatedStruct_sub_467110(struct MapRelatedStruct *self, int *arg0, SpriteS1 *a3, int *a4, Player *pPlayer)
{
  int *field; // ebp
  int v7; // eax
  struct SpriteS1 *FirstElement; // ebx
  struct SpriteS1 *v9; // eax
  int v10; // eax
  int v11; // edi
  int v12; // eax
  struct CarSystemManager *v13; // eax
  int v14; // eax
  struct CarSystemManager *v15; // edx
  struct SpriteS1 *v16; // ebp
  struct CarSystemManager *v17; // ebx
  int v18; // ebp
  struct SpriteS1 *v19; // edi
  struct SpriteS1 *v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  BOOL v24; // eax
  struct SpriteS1 *v25; // eax
  struct SpriteS1 *v26; // eax
  int v27; // eax
  int v28; // eax
  struct SpriteS1 *v29; // eax
  int v30; // eax
  int v31; // eax
  struct CarSystemManager *v32; // edx
  int v33; // ebx
  struct CarSystemManager *v34; // eax
  struct SpriteS1 *v35; // eax
  struct SpriteS1 *v36; // eax
  struct SpriteS1 *v37; // eax
  int v38; // eax
  int v39; // eax
  int v40; // eax
  BOOL v41; // eax
  struct SpriteS1 *v42; // eax
  int v43; // eax
  int v44; // eax
  struct SpriteS1 *v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // ebx
  BOOL v49; // eax
  struct SpriteS1 *v50; // eax
  int v51; // eax
  int v52; // eax
  struct SpriteS1 *v53; // eax
  int v54; // eax
  int v55; // eax
  struct CarSystemManager *v56; // ecx
  struct CarSystemManager *v57; // eax
  struct SpriteS1 *v58; // eax
  struct SpriteS1 *v59; // eax
  struct SpriteS1 *v60; // eax
  int v61; // eax
  int v62; // eax
  struct SpriteS1 *v63; // eax
  int v64; // eax
  int v65; // eax
  int v66; // ebx
  struct SpriteS1 *v67; // eax
  int v68; // eax
  int v69; // eax
  int v70; // eax
  struct SpriteS1 *v71; // eax
  int v72; // eax
  int v73; // eax
  struct SpriteS1 *v74; // eax
  int v75; // eax
  bool v76; // zf
  struct SpriteS1 *v77; // eax
  int v78; // eax
  int v79; // eax
  struct S202 *v80; // eax
  struct SpriteS1 *v81; // eax
  int v82; // eax
  int v83; // eax
  int v84; // eax
  int v85; // ecx
  int result; // eax
  S202 v87; // [esp-Ch] [ebp-80h] BYREF
  unsigned __int16 v88; // [esp+14h] [ebp-60h] BYREF
  unsigned __int16 v89; // [esp+16h] [ebp-5Eh] BYREF
  AudioSourceParams v90; // [esp+18h] [ebp-5Ch] BYREF
  S202 pS202; // [esp+30h] [ebp-44h] BYREF
  S202 v92; // [esp+50h] [ebp-24h] BYREF
  _BYTE v93[4]; // [esp+70h] [ebp-4h] BYREF

  v7 = *a4;
  FirstElement = a3->FirstElement;
  v87.field_1D = 0;
  v90.field = *arg0;
  field = (int *)v90.field;
  v90.AudioSourceParams = (int)FirstElement;
  v90.AudioSourceParams1 = v7;
  gta2::MapRelatedStruct_sub_467020(self, (int *)v90.field, FirstElement, &v90.AudioSourceParams1, (void *)1, 0);
  v9 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, &pS202, (int)&unk_662C98);
  v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v9);
  v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
  v10 = gta2::AudioSourceParams_sub_41F9D0(&v90);
  v11 = gta2::MapRelatedStruct_sub_4653C0(self, v10, (int)v87.S202, (int)v87.CarSystemManager);
  if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
  {
    v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams1);
    v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
    v12 = gta2::AudioSourceParams_sub_41F9D0(&v90);
    v11 = gta2::MapRelatedStruct_sub_4653C0(self, v12, (int)v87.S202, (int)v87.CarSystemManager);
  }
  v90.AudioSourceParams2 = gta2::MapRelatedStruct_sub_4633A0(self, v11, 1);
  v13 = (struct CarSystemManager *)gta2::sub_4725B0((unsigned __int16 *)&v87.field_1E, &v90.AudioSourceParams2);
  LOWORD(v13) = v13->Index;
  v87.CarSystemManager = v13;
  v87.S202 = (struct S202 *)FirstElement;
  v87.field_0 = (int)field;
  v90.field_10 = (int)*gta2::sub_463150((SpriteS1 **)&pS202, v87);
  if ( gta2::Car_sub_403800((struct Car *)&v90.field_10, (int)&unk_6630B0) )
  {
    switch ( v90.AudioSourceParams2 )
    {
      case 1:
        goto LABEL_5;
      case 2:
        goto LABEL_9;
      case 3:
        goto LABEL_6;
      case 4:
        goto LABEL_10;
      default:
        break;
    }
  }
  else
  {
    v87.CarSystemManager = (struct CarSystemManager *)&unk_6630B0;
    if ( gta2::sub_4037E0(&v90.field_10) )
    {
      switch ( v90.AudioSourceParams2 )
      {
        case 1:
LABEL_9:
          v90.AudioSourceParams2 = 3;
          break;
        case 2:
LABEL_5:
          v90.AudioSourceParams2 = 4;
          break;
        case 3:
LABEL_10:
          v90.AudioSourceParams2 = 2;
          break;
        case 4:
LABEL_6:
          v90.AudioSourceParams2 = 1;
          break;
        default:
          break;
      }
    }
  }
  LOWORD(v14) = gta2::Car_sub_403820((struct Car *)&v90.field_10, &unk_6630B0);
  v87.CarSystemManager = (struct CarSystemManager *)&v90.AudioSourceParams2;
  v87.S202 = (struct S202 *)&v87.field_1E;
  if ( v14 )
  {
    LOWORD(v15) = *gta2::sub_4725B0((unsigned __int16 *)v87.S202, &v87.CarSystemManager->Index);
    v87.CarSystemManager = v15;
    v87.S202 = (struct S202 *)FirstElement;
    v87.field_0 = (int)field;
    v90.field_10 = (int)*gta2::sub_463210((SpriteS1 **)&pS202, v87);
    v90.field_10 = (int)gta2::Player_sub_401B40((struct Player *)&v90.field_10, &pS202, (int)&unk_6630B0)->FirstElement;
    if ( !gta2::Car_sub_403800((struct Car *)&v90.field_10, (int)&unk_662CFC) )
      goto LABEL_46;
    if ( !gta2::Player_sub_40CE70((struct Player *)&pPlayer, &v90.field_10) )
    {
      v87.CarSystemManager = (struct CarSystemManager *)v90.AudioSourceParams2;
      v87.S202 = (struct S202 *)pPlayer;
      sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
      field = (int *)v90.field;
      FirstElement = (struct SpriteS1 *)v90.AudioSourceParams;
      pPlayer = (struct Player *)unk_662CFC;
      goto LABEL_46;
    }
    sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
    v16 = gta2::Player_sub_401B40((struct Player *)&pPlayer, &pS202, (int)&v90.field_10)->FirstElement;
    pPlayer = (struct Player *)v16;
    v17 = (struct CarSystemManager *)gta2::MapRelatedStruct_sub_4633A0(self, v11, 1);
    v90.AudioSourceParams2 = (int)v17;
    if ( !gta2::Player_sub_40CE70((struct Player *)&pPlayer, &unk_6630B0) )
    {
      v87.CarSystemManager = (struct CarSystemManager *)v90.AudioSourceParams2;
      v87.S202 = (struct S202 *)v16;
      sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
      field = (int *)v90.field;
      FirstElement = (struct SpriteS1 *)v90.AudioSourceParams;
      pPlayer = (struct Player *)unk_662CFC;
      goto LABEL_46;
    }
    v18 = v11;
    sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
    v19 = gta2::Player_sub_401B40((struct Player *)&pPlayer, &pS202, (int)&unk_6630B0)->FirstElement;
    pPlayer = (struct Player *)v19;
    v20 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, &pS202, (int)&unk_662C98);
    v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v20);
    v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
    v21 = gta2::AudioSourceParams_sub_41F9D0(&v90);
    v22 = gta2::MapRelatedStruct_sub_4653C0(self, v21, (int)v87.S202, (int)v87.CarSystemManager);
    if ( (*(_BYTE *)(v22 + 11) & 0xFC) == 0xFC )
    {
      v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams1);
      v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
      v23 = gta2::AudioSourceParams_sub_41F9D0(&v90);
      v22 = gta2::MapRelatedStruct_sub_4653C0(self, v23, (int)v87.S202, (int)v87.CarSystemManager);
    }
    if ( v22 )
    {
      if ( gta2::MapRelatedStruct_sub_4632E0(self, v22, (int)v17, 1) )
        goto LABEL_24;
      v17 = (struct CarSystemManager *)v90.AudioSourceParams2;
    }
    v24 = gta2::Player_sub_40CE70((struct Player *)&pPlayer, &unk_662C98);
    v87.CarSystemManager = v17;
    if ( v24 )
    {
      sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
      v25 = gta2::Player_sub_401B40((struct Player *)&pPlayer, &pS202, (int)&unk_662C98)->FirstElement;
    }
    else
    {
      v87.S202 = (struct S202 *)v19;
      sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
      v25 = (struct SpriteS1 *)unk_662CFC;
    }
    pPlayer = (struct Player *)v25;
LABEL_24:
    v26 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, &pS202, (int)&unk_662C98);
    v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v26);
    v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
    v27 = gta2::AudioSourceParams_sub_41F9D0(&v90);
    v11 = gta2::MapRelatedStruct_sub_4653C0(self, v27, (int)v87.S202, (int)v87.CarSystemManager);
    if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
    {
      v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams1);
      v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
      v28 = gta2::AudioSourceParams_sub_41F9D0(&v90);
      v11 = gta2::MapRelatedStruct_sub_4653C0(self, v28, (int)v87.S202, (int)v87.CarSystemManager);
    }
    FirstElement = (struct SpriteS1 *)v90.AudioSourceParams;
    v76 = v11 == v18;
    field = (int *)v90.field;
    if ( !v76 )
    {
      gta2::MapRelatedStruct_sub_467020(
        self,
        (int *)v90.field,
        (struct SpriteS1 *)v90.AudioSourceParams,
        &v90.AudioSourceParams1,
        (void *)1,
        0);
      v29 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, &pS202, (int)&unk_662C98);
      v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v29);
      v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
      v30 = gta2::AudioSourceParams_sub_41F9D0(&v90);
      v11 = gta2::MapRelatedStruct_sub_4653C0(self, v30, (int)v87.S202, (int)v87.CarSystemManager);
      if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
        goto LABEL_28;
    }
    goto LABEL_46;
  }
  LOWORD(v32) = *gta2::sub_4725B0((unsigned __int16 *)v87.S202, &v87.CarSystemManager->Index);
  v87.CarSystemManager = v32;
  v87.S202 = (struct S202 *)FirstElement;
  v87.field_0 = (int)field;
  v90.field_10 = (int)*gta2::sub_463210((SpriteS1 **)&pS202, v87);
  if ( gta2::Car_sub_403800((struct Car *)&v90.field_10, (int)&unk_662CFC) )
  {
    gta2::MapRelatedStruct_sub_467020(self, field, FirstElement, &v90.AudioSourceParams1, (void *)1, (void *)1);
    v33 = v11;
    gta2::Player_sub_401B40((struct Player *)&unk_662C98, &pS202, (int)&v90.field_10);
    v34 = (struct CarSystemManager *)gta2::sub_4725B0(&v88, &v90.AudioSourceParams2);
    v35 = (struct SpriteS1 *)gta2::sub_40E5A0(v34, (struct CarSystemManager *)&v87.field_1E, &unk_663108);
    gta2::SpriteS1_sub_472C00(v35);
    sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
    v36 = gta2::Player_sub_401B40((struct Player *)&unk_662C98, &pS202, (int)&v90.field_10);
    pPlayer = (struct Player *)gta2::S202_sub_401B20((struct S202 *)&pPlayer, (struct SpriteS1 *)&v90.field_14, (struct PublicTransport *)v36)->FirstElement;
    v37 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, &pS202, (int)&unk_662C98);
    v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v37);
    v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
    v38 = gta2::AudioSourceParams_sub_41F9D0(&v90);
    v39 = gta2::MapRelatedStruct_sub_4653C0(self, v38, (int)v87.S202, (int)v87.CarSystemManager);
    if ( !v39 )
      goto LABEL_37;
    if ( (*(_BYTE *)(v39 + 11) & 0xFC) == 0xFC )
    {
      v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams1);
      v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
      v40 = gta2::AudioSourceParams_sub_41F9D0(&v90);
      v39 = gta2::MapRelatedStruct_sub_4653C0(self, v40, (int)v87.S202, (int)v87.CarSystemManager);
    }
    if ( !v39 || !gta2::MapRelatedStruct_sub_4632E0(self, v39, v90.AudioSourceParams2, 1) )
    {
LABEL_37:
      v41 = gta2::Player_sub_40CE70((struct Player *)&pPlayer, &unk_662C98);
      v87.CarSystemManager = (struct CarSystemManager *)v90.AudioSourceParams2;
      if ( v41 )
      {
        sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
        pPlayer = (struct Player *)gta2::Player_sub_401B40((struct Player *)&pPlayer, &pS202, (int)&unk_662C98)->FirstElement;
      }
      else
      {
        v87.S202 = (struct S202 *)pPlayer;
        sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
        pPlayer = (struct Player *)unk_662CFC;
      }
    }
    v42 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, &pS202, (int)&unk_662C98);
    v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v42);
    v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
    v43 = gta2::AudioSourceParams_sub_41F9D0(&v90);
    v11 = gta2::MapRelatedStruct_sub_4653C0(self, v43, (int)v87.S202, (int)v87.CarSystemManager);
    if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
    {
      v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams1);
      v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
      v44 = gta2::AudioSourceParams_sub_41F9D0(&v90);
      v11 = gta2::MapRelatedStruct_sub_4653C0(self, v44, (int)v87.S202, (int)v87.CarSystemManager);
    }
    field = (int *)v90.field;
    v87.CarSystemManager = 0;
    v76 = v11 == v33;
    FirstElement = (struct SpriteS1 *)v90.AudioSourceParams;
    v87.S202 = (struct S202 *)1;
    v87.field_0 = (int)&v90.AudioSourceParams1;
    if ( v76 )
    {
      gta2::MapRelatedStruct_sub_467020(
        self,
        (int *)v90.field,
        (struct SpriteS1 *)v90.AudioSourceParams,
        (void *)v87.field_0,
        v87.S202,
        v87.CarSystemManager);
    }
    else
    {
      gta2::MapRelatedStruct_sub_467020(
        self,
        (int *)v90.field,
        (struct SpriteS1 *)v90.AudioSourceParams,
        (void *)v87.field_0,
        v87.S202,
        v87.CarSystemManager);
      v45 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, &pS202, (int)&unk_662C98);
      v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v45);
      v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
      v46 = gta2::AudioSourceParams_sub_41F9D0(&v90);
      v11 = gta2::MapRelatedStruct_sub_4653C0(self, v46, (int)v87.S202, (int)v87.CarSystemManager);
      if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
      {
LABEL_28:
        v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams1);
        v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
        v31 = gta2::AudioSourceParams_sub_41F9D0(&v90);
        v11 = gta2::MapRelatedStruct_sub_4653C0(self, v31, (int)v87.S202, (int)v87.CarSystemManager);
      }
    }
  }
LABEL_46:
  LOWORD(v47) = gta2::Car_sub_403820((struct Car *)&pPlayer, &unk_662CFC);
  if ( v47 )
  {
    do
    {
      if ( !gta2::MapRelatedStruct_sub_4632E0(self, v11, v90.AudioSourceParams2, 1) || v87.field_1D )
      {
        v87.field_1D = 0;
        v66 = v11;
        if ( gta2::Player_sub_40CE70((struct Player *)&pPlayer, &unk_662C98) )
        {
          sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
          v67 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, (struct S202 *)&v92.CarSystemManager, (int)&unk_662C98);
          v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v67);
          v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
          v68 = gta2::AudioSourceParams_sub_41F9D0(&v90);
          v69 = gta2::MapRelatedStruct_sub_4653C0(self, v68, (int)v87.S202, (int)v87.CarSystemManager);
          if ( (*(_BYTE *)(v69 + 11) & 0xFC) == 0xFC )
          {
            v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams1);
            v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
            v70 = gta2::AudioSourceParams_sub_41F9D0(&v90);
            v69 = gta2::MapRelatedStruct_sub_4653C0(self, v70, (int)v87.S202, (int)v87.CarSystemManager);
          }
          v90.AudioSourceParams2 = gta2::MapRelatedStruct_sub_4633A0(self, v69, 1);
          sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
          pPlayer = (struct Player *)gta2::Player_sub_401B40((struct Player *)&pPlayer, (struct S202 *)&v92.field_C, (int)&unk_662C98)->FirstElement;
          v71 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, (struct S202 *)&v92.field_10, (int)&unk_662C98);
          v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v71);
          v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
          v72 = gta2::AudioSourceParams_sub_41F9D0(&v90);
          v11 = gta2::MapRelatedStruct_sub_4653C0(self, v72, (int)v87.S202, (int)v87.CarSystemManager);
          if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
          {
            v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams1);
            v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
            v73 = gta2::AudioSourceParams_sub_41F9D0(&v90);
            v11 = gta2::MapRelatedStruct_sub_4653C0(self, v73, (int)v87.S202, (int)v87.CarSystemManager);
          }
          field = (int *)v90.field;
          v76 = v11 == v66;
          FirstElement = (struct SpriteS1 *)v90.AudioSourceParams;
          if ( v76 )
            goto LABEL_80;
          gta2::MapRelatedStruct_sub_467020(
            self,
            (int *)v90.field,
            (struct SpriteS1 *)v90.AudioSourceParams,
            &v90.AudioSourceParams1,
            (void *)1,
            0);
          v74 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, (struct S202 *)&v92.pPlayer, (int)&unk_662C98);
          v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v74);
          v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
          v75 = gta2::AudioSourceParams_sub_41F9D0(&v90);
          v11 = gta2::MapRelatedStruct_sub_4653C0(self, v75, (int)v87.S202, (int)v87.CarSystemManager);
          v76 = (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC;
        }
        else
        {
          if ( gta2::Car_sub_403800((struct Car *)&pPlayer, (int)&unk_6630B0) )
          {
            sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
            v77 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, (struct S202 *)&v92.field_18, (int)&unk_662C98);
            v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v77);
            v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
            v78 = gta2::AudioSourceParams_sub_41F9D0(&v90);
            v11 = gta2::MapRelatedStruct_sub_4653C0(self, v78, (int)v87.S202, (int)v87.CarSystemManager);
            if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
            {
              v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams1);
              v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
              v79 = gta2::AudioSourceParams_sub_41F9D0(&v90);
              v11 = gta2::MapRelatedStruct_sub_4653C0(self, v79, (int)v87.S202, (int)v87.CarSystemManager);
            }
            v90.AudioSourceParams2 = gta2::MapRelatedStruct_sub_4633A0(self, v11, 1);
            v80 = (struct S202 *)gta2::Player_sub_401B40((struct Player *)&pPlayer, (struct S202 *)&v92.field_1C, (int)&unk_6630B0)->FirstElement;
          }
          else
          {
            v80 = (struct S202 *)pPlayer;
          }
          v87.S202 = v80;
          sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
          gta2::bitShiftLeft1(&pS202, 0);
          field = (int *)v90.field;
          v76 = v11 == v66;
          FirstElement = (struct SpriteS1 *)v90.AudioSourceParams;
          pPlayer = (struct Player *)pS202.field_0;
          if ( v76 )
            goto LABEL_80;
          gta2::MapRelatedStruct_sub_467020(
            self,
            (int *)v90.field,
            (struct SpriteS1 *)v90.AudioSourceParams,
            &v90.AudioSourceParams1,
            (void *)1,
            0);
          v81 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, (struct S202 *)v93, (int)&unk_662C98);
          v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v81);
          v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
          v82 = gta2::AudioSourceParams_sub_41F9D0(&v90);
          v11 = gta2::MapRelatedStruct_sub_4653C0(self, v82, (int)v87.S202, (int)v87.CarSystemManager);
          v76 = (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC;
        }
        if ( v76 )
        {
          v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams1);
          v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
          v83 = gta2::AudioSourceParams_sub_41F9D0(&v90);
          v11 = gta2::MapRelatedStruct_sub_4653C0(self, v83, (int)v87.S202, (int)v87.CarSystemManager);
        }
      }
      else
      {
        v48 = v11;
        v49 = gta2::Player_sub_40CE70((struct Player *)&pPlayer, &unk_662C98);
        v87.CarSystemManager = (struct CarSystemManager *)v90.AudioSourceParams2;
        if ( v49 )
        {
          sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
          pPlayer = (struct Player *)gta2::Player_sub_401B40((struct Player *)&pPlayer, (struct S202 *)&pS202.S202, (int)&unk_662C98)->FirstElement;
        }
        else
        {
          v87.S202 = (struct S202 *)pPlayer;
          sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
          pPlayer = (struct Player *)unk_662CFC;
        }
        v50 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, (struct S202 *)&pS202.CarSystemManager, (int)&unk_662C98);
        v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v50);
        v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
        v51 = gta2::AudioSourceParams_sub_41F9D0(&v90);
        v11 = gta2::MapRelatedStruct_sub_4653C0(self, v51, (int)v87.S202, (int)v87.CarSystemManager);
        if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
        {
          v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams1);
          v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
          v52 = gta2::AudioSourceParams_sub_41F9D0(&v90);
          v11 = gta2::MapRelatedStruct_sub_4653C0(self, v52, (int)v87.S202, (int)v87.CarSystemManager);
        }
        field = (int *)v90.field;
        v76 = v11 == v48;
        FirstElement = (struct SpriteS1 *)v90.AudioSourceParams;
        if ( !v76 )
        {
          gta2::MapRelatedStruct_sub_467020(
            self,
            (int *)v90.field,
            (struct SpriteS1 *)v90.AudioSourceParams,
            &v90.AudioSourceParams1,
            (void *)1,
            0);
          v53 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, (struct S202 *)&pS202.field_C, (int)&unk_662C98);
          v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v53);
          v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
          v54 = gta2::AudioSourceParams_sub_41F9D0(&v90);
          v11 = gta2::MapRelatedStruct_sub_4653C0(self, v54, (int)v87.S202, (int)v87.CarSystemManager);
          if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
          {
            v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams1);
            v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
            v55 = gta2::AudioSourceParams_sub_41F9D0(&v90);
            v11 = gta2::MapRelatedStruct_sub_4653C0(self, v55, (int)v87.S202, (int)v87.CarSystemManager);
          }
        }
        if ( !gta2::MapRelatedStruct_sub_4632E0(self, v11, v90.AudioSourceParams2, 1) )
        {
          v90.field_14 = v11;
          LOWORD(v56) = *gta2::sub_4725B0(&v88, &v90.AudioSourceParams2);
          v87.CarSystemManager = v56;
          v87.S202 = (struct S202 *)FirstElement;
          v87.field_0 = (int)field;
          v90.field_10 = (int)*gta2::sub_463210((SpriteS1 **)&pS202.field_10, v87);
          gta2::Player_sub_401B40((struct Player *)&unk_662C98, (struct S202 *)&pS202.pPlayer, (int)&v90.field_10);
          v57 = (struct CarSystemManager *)gta2::sub_4725B0(&v89, &v90.AudioSourceParams2);
          v58 = (struct SpriteS1 *)gta2::sub_40E5A0(v57, (struct CarSystemManager *)&v87.field_1E, &unk_663108);
          gta2::SpriteS1_sub_472C00(v58);
          sub_4630D0((struct SpriteS1 *)&v90, (struct SpriteS1 *)&v90.AudioSourceParams);
          v59 = gta2::Player_sub_401B40((struct Player *)&unk_662C98, (struct S202 *)&pS202.field_18, (int)&v90.field_10);
          pPlayer = (struct Player *)gta2::S202_sub_401B20((struct S202 *)&pPlayer, (struct SpriteS1 *)&pS202.field_1C, (struct PublicTransport *)v59)->FirstElement;
          v60 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, &v92, (int)&unk_662C98);
          v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v60);
          v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
          v61 = gta2::AudioSourceParams_sub_41F9D0(&v90);
          v11 = gta2::MapRelatedStruct_sub_4653C0(self, v61, (int)v87.S202, (int)v87.CarSystemManager);
          if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
          {
            v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams1);
            v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
            v62 = gta2::AudioSourceParams_sub_41F9D0(&v90);
            v11 = gta2::MapRelatedStruct_sub_4653C0(self, v62, (int)v87.S202, (int)v87.CarSystemManager);
          }
          field = (int *)v90.field;
          FirstElement = (struct SpriteS1 *)v90.AudioSourceParams;
          if ( v11 != v90.field_14 )
          {
            gta2::MapRelatedStruct_sub_467020(
              self,
              (int *)v90.field,
              (struct SpriteS1 *)v90.AudioSourceParams,
              &v90.AudioSourceParams1,
              (void *)1,
              0);
            v63 = gta2::Player_sub_401B40((struct Player *)&v90.AudioSourceParams1, (struct S202 *)&v92.S202, (int)&unk_662C98);
            v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v63);
            v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
            v64 = gta2::AudioSourceParams_sub_41F9D0(&v90);
            v11 = gta2::MapRelatedStruct_sub_4653C0(self, v64, (int)v87.S202, (int)v87.CarSystemManager);
            if ( (*(_BYTE *)(v11 + 11) & 0xFC) == 0xFC )
            {
              v87.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams1);
              v87.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v90.AudioSourceParams);
              v65 = gta2::AudioSourceParams_sub_41F9D0(&v90);
              v11 = gta2::MapRelatedStruct_sub_4653C0(self, v65, (int)v87.S202, (int)v87.CarSystemManager);
            }
          }
          v87.field_1D = 1;
        }
      }
LABEL_80:
      LOWORD(v84) = gta2::Car_sub_403820((struct Car *)&pPlayer, &unk_662CFC);
    }
    while ( v84 );
  }
  v87.CarSystemManager = (struct CarSystemManager *)v90.AudioSourceParams1;
  *arg0 = (int)field;
  a3->FirstElement = FirstElement;
  v85 = *gta2::MapRelatedStruct_sub_466E20(self, &pPlayer, field, FirstElement, (int)v87.CarSystemManager);
  result = v90.AudioSourceParams2;
  *a4 = v85;
  return result;
}


// 0x00467f80: MapRelatedStruct::sub_467F80
// IDA: MapRelatedStruct::sub_467F80
// Ghidra: ---
int gta2::MapRelatedStruct_sub_467F80(struct MapRelatedStruct *self, int **arg0, SpriteS1 **a3, int *a4, Player *a5)
{
  int *field; // ebp
  struct SpriteS1 *v7; // ebx
  struct SpriteS1 *v8; // eax
  int v9; // eax
  int v10; // edi
  int v11; // eax
  struct CarSystemManager *v12; // edx
  int v13; // eax
  struct CarSystemManager *v14; // ecx
  BOOL v15; // eax
  struct SpriteS1 *v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  char v20; // al
  struct CarSystemManager *v21; // edi
  BOOL v22; // eax
  struct SpriteS1 *v23; // eax
  int v24; // eax
  int v25; // eax
  struct SpriteS1 *v26; // eax
  int v27; // eax
  int v28; // eax
  struct CarSystemManager *v29; // ecx
  int v30; // ebx
  struct CarSystemManager *v31; // eax
  struct SpriteS1 *v32; // eax
  struct SpriteS1 *v33; // eax
  struct SpriteS1 *v34; // eax
  int v35; // eax
  int v36; // eax
  int v37; // eax
  BOOL v38; // eax
  struct SpriteS1 *v39; // eax
  int v40; // eax
  int v41; // eax
  struct SpriteS1 *v42; // eax
  int v43; // eax
  int v44; // eax
  BOOL v45; // eax
  struct SpriteS1 *v46; // eax
  int v47; // eax
  int v48; // eax
  int v49; // eax
  struct SpriteS1 *v50; // eax
  int v51; // eax
  int v52; // eax
  int v53; // eax
  struct CarSystemManager *v54; // edx
  struct CarSystemManager *v55; // eax
  struct SpriteS1 *v56; // eax
  struct CarSystemManager *v57; // eax
  struct SpriteS1 *v58; // eax
  struct SpriteS1 *v59; // eax
  struct SpriteS1 *v60; // eax
  int v61; // eax
  int v62; // eax
  struct SpriteS1 *v63; // eax
  int v64; // eax
  int v65; // eax
  struct CarSystemManager *v66; // ebp
  struct SpriteS1 *v67; // eax
  struct SpriteS1 *v68; // eax
  int v69; // eax
  int v70; // eax
  struct SpriteS1 *v71; // eax
  struct SpriteS1 *v72; // ecx
  struct SpriteS1 *v73; // eax
  struct SpriteS1 *v74; // eax
  int v75; // eax
  int v76; // eax
  struct SpriteS1 *v77; // eax
  struct SpriteS1 *v78; // eax
  int v79; // eax
  int v80; // ebx
  struct SpriteS1 *FirstElement; // edi
  BOOL v82; // eax
  struct SpriteS1 *v83; // eax
  struct SpriteS1 *v84; // eax
  int v85; // eax
  int v86; // eax
  struct SpriteS1 *v87; // eax
  int v88; // eax
  bool v89; // zf
  struct SpriteS1 *v90; // eax
  int v91; // eax
  int v92; // eax
  struct S202 *v93; // eax
  struct SpriteS1 *v94; // eax
  int v95; // eax
  int v96; // eax
  int v97; // eax
  S202 v99; // [esp-Ch] [ebp-BCh] BYREF
  AudioSourceParams v100; // [esp+14h] [ebp-9Ch] BYREF
  struct SpriteS1 *v101; // [esp+2Ch] [ebp-84h] BYREF
  CarSystemManager pCarSystemManager; // [esp+32h] [ebp-7Eh] BYREF
  char v103; // [esp+A0h] [ebp-10h] BYREF
  _BYTE v104[4]; // [esp+A4h] [ebp-Ch] BYREF
  char v105; // [esp+A8h] [ebp-8h] BYREF
  _BYTE v106[4]; // [esp+ACh] [ebp-4h] BYREF

  field = *arg0;
  v100.AudioSourceParams = *a4;
  *(_DWORD *)&pCarSystemManager.field_2 = v100.AudioSourceParams;
  v7 = *a3;
  HIBYTE(v100.field_10) = 0;
  v100.field = (int)field;
  *(Weapon **)((char *)&pCarSystemManager.Weapon_ + 2) = (struct Weapon *)field;
  *(_DWORD *)&v99.field_1C = v7;
  *(int *)((char *)&pCarSystemManager.field_4 + 2) = (int)v7;
  gta2::MapRelatedStruct_sub_467020(self, field, v7, &v100.AudioSourceParams, 0, 0);
  v8 = gta2::Player_sub_401B40((struct Player *)&v100.AudioSourceParams, (struct S202 *)&v100.AudioSourceParams2, (int)&unk_662C98);
  v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v8);
  v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
  v9 = gta2::AudioSourceParams_sub_41F9D0(&v100);
  v10 = gta2::MapRelatedStruct_sub_4653C0(self, v9, (int)v99.S202, (int)v99.CarSystemManager);
  if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
  {
    v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v100.AudioSourceParams);
    v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
    v11 = gta2::AudioSourceParams_sub_41F9D0(&v100);
    v10 = gta2::MapRelatedStruct_sub_4653C0(self, v11, (int)v99.S202, (int)v99.CarSystemManager);
  }
  v100.AudioSourceParams1 = gta2::MapRelatedStruct_sub_4633A0(self, v10, 0);
  LOWORD(v12) = *gta2::sub_4725B0(&pCarSystemManager.Index, &v100.AudioSourceParams1);
  v99.CarSystemManager = v12;
  v99.S202 = (struct S202 *)v7;
  v99.field_0 = (int)field;
  v101 = *gta2::sub_463150((SpriteS1 **)&v100.AudioSourceParams2, v99);
  if ( gta2::Car_sub_403800((struct Car *)&v101, (int)&unk_6630B0) )
  {
    switch ( v100.AudioSourceParams1 )
    {
      case 1:
        goto LABEL_5;
      case 2:
        goto LABEL_9;
      case 3:
        goto LABEL_6;
      case 4:
        goto LABEL_10;
      default:
        break;
    }
  }
  else
  {
    v99.CarSystemManager = (struct CarSystemManager *)&unk_6630B0;
    if ( gta2::sub_4037E0(&v101) )
    {
      switch ( v100.AudioSourceParams1 )
      {
        case 1:
LABEL_9:
          v100.AudioSourceParams1 = 4;
          break;
        case 2:
LABEL_5:
          v100.AudioSourceParams1 = 3;
          break;
        case 3:
LABEL_10:
          v100.AudioSourceParams1 = 1;
          break;
        case 4:
LABEL_6:
          v100.AudioSourceParams1 = 2;
          break;
        default:
          break;
      }
    }
  }
  LOWORD(v13) = gta2::Car_sub_403820((struct Car *)&v101, &unk_6630B0);
  v99.CarSystemManager = (struct CarSystemManager *)&v100.AudioSourceParams1;
  v99.S202 = (struct S202 *)&pCarSystemManager;
  if ( v13 )
  {
    v101 = (struct SpriteS1 *)v10;
    LOWORD(v14) = *gta2::sub_4725B0((unsigned __int16 *)v99.S202, &v99.CarSystemManager->Index);
    v99.CarSystemManager = v14;
    v99.S202 = (struct S202 *)v7;
    v99.field_0 = (int)field;
    v100.field_14 = (int)*gta2::sub_463210((SpriteS1 **)&v100.AudioSourceParams2, v99);
    if ( gta2::Car_sub_403800((struct Car *)&v100.field_14, (int)&unk_662CFC) )
    {
      v15 = gta2::Player_sub_40CE70((struct Player *)&a5, &v100.field_14);
      v99.CarSystemManager = (struct CarSystemManager *)v100.AudioSourceParams1;
      if ( v15 )
      {
        sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
        a5 = (struct Player *)gta2::Player_sub_401B40((struct Player *)&a5, (struct S202 *)&v100.AudioSourceParams2, (int)&v100.field_14)->FirstElement;
      }
      else
      {
        v99.S202 = (struct S202 *)a5;
        sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
        a5 = (struct Player *)unk_662CFC;
      }
      field = (int *)v100.field;
      v7 = *(SpriteS1 **)&v99.field_1C;
    }
    v16 = gta2::Player_sub_401B40((struct Player *)&v100.AudioSourceParams, (struct S202 *)&v100.AudioSourceParams2, (int)&unk_662C98);
    v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v16);
    v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
    v17 = gta2::AudioSourceParams_sub_41F9D0(&v100);
    v18 = gta2::MapRelatedStruct_sub_4653C0(self, v17, (int)v99.S202, (int)v99.CarSystemManager);
    if ( (*(_BYTE *)(v18 + 11) & 0xFC) == 0xFC )
    {
      v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v100.AudioSourceParams);
      v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
      v19 = gta2::AudioSourceParams_sub_41F9D0(&v100);
      v18 = gta2::MapRelatedStruct_sub_4653C0(self, v19, (int)v99.S202, (int)v99.CarSystemManager);
    }
    v20 = gta2::MapRelatedStruct_sub_4632E0(self, v18, v100.AudioSourceParams1, 0);
    v21 = (struct CarSystemManager *)v100.AudioSourceParams1;
    if ( !v20 )
    {
      v22 = gta2::Player_sub_40CE70((struct Player *)&a5, &unk_662C98);
      v99.CarSystemManager = v21;
      if ( v22 )
      {
        sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
        a5 = (struct Player *)gta2::Player_sub_401B40((struct Player *)&a5, (struct S202 *)&v100.AudioSourceParams2, (int)&unk_662C98)->FirstElement;
      }
      else
      {
        v99.S202 = (struct S202 *)a5;
        sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
        a5 = (struct Player *)unk_662CFC;
      }
      field = (int *)v100.field;
      v7 = *(SpriteS1 **)&v99.field_1C;
    }
    v23 = gta2::Player_sub_401B40((struct Player *)&v100.AudioSourceParams, (struct S202 *)&v100.AudioSourceParams2, (int)&unk_662C98);
    v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v23);
    v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
    v24 = gta2::AudioSourceParams_sub_41F9D0(&v100);
    v10 = gta2::MapRelatedStruct_sub_4653C0(self, v24, (int)v99.S202, (int)v99.CarSystemManager);
    if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
    {
      v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v100.AudioSourceParams);
      v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
      v25 = gta2::AudioSourceParams_sub_41F9D0(&v100);
      v10 = gta2::MapRelatedStruct_sub_4653C0(self, v25, (int)v99.S202, (int)v99.CarSystemManager);
    }
    if ( (struct SpriteS1 *)v10 != v101 )
    {
      gta2::MapRelatedStruct_sub_467020(self, field, v7, &v100.AudioSourceParams, 0, 0);
      v26 = gta2::Player_sub_401B40((struct Player *)&v100.AudioSourceParams, (struct S202 *)&v100.AudioSourceParams2, (int)&unk_662C98);
      v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v26);
      v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
      v27 = gta2::AudioSourceParams_sub_41F9D0(&v100);
      v10 = gta2::MapRelatedStruct_sub_4653C0(self, v27, (int)v99.S202, (int)v99.CarSystemManager);
      if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
        goto LABEL_28;
    }
  }
  else
  {
    LOWORD(v29) = *gta2::sub_4725B0((unsigned __int16 *)v99.S202, &v99.CarSystemManager->Index);
    v99.CarSystemManager = v29;
    v99.S202 = (struct S202 *)v7;
    v99.field_0 = (int)field;
    v100.field_14 = (int)*gta2::sub_463210((SpriteS1 **)&v100.AudioSourceParams2, v99);
    if ( gta2::Car_sub_403800((struct Car *)&v100.field_14, (int)&unk_662CFC) )
    {
      gta2::MapRelatedStruct_sub_467020(self, field, v7, &v100.AudioSourceParams, 0, (void *)1);
      v30 = v10;
      gta2::Player_sub_401B40((struct Player *)&unk_662C98, (struct S202 *)&v100.AudioSourceParams2, (int)&v100.field_14);
      v31 = (struct CarSystemManager *)gta2::sub_4725B0((unsigned __int16 *)&pCarSystemManager.field_10, &v100.AudioSourceParams1);
      v32 = (struct SpriteS1 *)gta2::sub_40E5A0(v31, &pCarSystemManager, &unk_663108);
      gta2::SpriteS1_sub_472C00(v32);
      sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
      v33 = gta2::Player_sub_401B40((struct Player *)&unk_662C98, (struct S202 *)&v100.AudioSourceParams2, (int)&v100.field_14);
      a5 = (struct Player *)gta2::S202_sub_401B20((struct S202 *)&a5, (struct SpriteS1 *)&v101, (struct PublicTransport *)v33)->FirstElement;
      v34 = gta2::Player_sub_401B40((struct Player *)&v100.AudioSourceParams, (struct S202 *)&v100.AudioSourceParams2, (int)&unk_662C98);
      v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v34);
      v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
      v35 = gta2::AudioSourceParams_sub_41F9D0(&v100);
      v36 = gta2::MapRelatedStruct_sub_4653C0(self, v35, (int)v99.S202, (int)v99.CarSystemManager);
      if ( !v36 )
        goto LABEL_35;
      if ( (*(_BYTE *)(v36 + 11) & 0xFC) == 0xFC )
      {
        v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v100.AudioSourceParams);
        v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
        v37 = gta2::AudioSourceParams_sub_41F9D0(&v100);
        v36 = gta2::MapRelatedStruct_sub_4653C0(self, v37, (int)v99.S202, (int)v99.CarSystemManager);
      }
      if ( !v36 || !gta2::MapRelatedStruct_sub_4632E0(self, v36, v100.AudioSourceParams1, 0) )
      {
LABEL_35:
        v38 = gta2::Player_sub_40CE70((struct Player *)&a5, &unk_662C98);
        v99.CarSystemManager = (struct CarSystemManager *)v100.AudioSourceParams1;
        if ( v38 )
        {
          sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
          a5 = (struct Player *)gta2::Player_sub_401B40((struct Player *)&a5, (struct S202 *)&v100.AudioSourceParams2, (int)&unk_662C98)->FirstElement;
        }
        else
        {
          v99.S202 = (struct S202 *)a5;
          sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
          a5 = (struct Player *)unk_662CFC;
        }
      }
      v39 = gta2::Player_sub_401B40((struct Player *)&v100.AudioSourceParams, (struct S202 *)&v100.AudioSourceParams2, (int)&unk_662C98);
      v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v39);
      v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
      v40 = gta2::AudioSourceParams_sub_41F9D0(&v100);
      v10 = gta2::MapRelatedStruct_sub_4653C0(self, v40, (int)v99.S202, (int)v99.CarSystemManager);
      if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
      {
        v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v100.AudioSourceParams);
        v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
        v41 = gta2::AudioSourceParams_sub_41F9D0(&v100);
        v10 = gta2::MapRelatedStruct_sub_4653C0(self, v41, (int)v99.S202, (int)v99.CarSystemManager);
      }
      field = (int *)v100.field;
      v99.CarSystemManager = 0;
      v89 = v10 == v30;
      v7 = *(SpriteS1 **)&v99.field_1C;
      v99.S202 = 0;
      v99.field_0 = (int)&v100.AudioSourceParams;
      if ( v89 )
      {
        gta2::MapRelatedStruct_sub_467020(
          self,
          (int *)v100.field,
          *(SpriteS1 **)&v99.field_1C,
          (void *)v99.field_0,
          v99.S202,
          v99.CarSystemManager);
      }
      else
      {
        gta2::MapRelatedStruct_sub_467020(
          self,
          (int *)v100.field,
          *(SpriteS1 **)&v99.field_1C,
          (void *)v99.field_0,
          v99.S202,
          v99.CarSystemManager);
        v42 = gta2::Player_sub_401B40((struct Player *)&v100.AudioSourceParams, (struct S202 *)&v100.AudioSourceParams2, (int)&unk_662C98);
        v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v42);
        v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
        v43 = gta2::AudioSourceParams_sub_41F9D0(&v100);
        v10 = gta2::MapRelatedStruct_sub_4653C0(self, v43, (int)v99.S202, (int)v99.CarSystemManager);
        if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
        {
LABEL_28:
          v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v100.AudioSourceParams);
          v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
          v28 = gta2::AudioSourceParams_sub_41F9D0(&v100);
          v10 = gta2::MapRelatedStruct_sub_4653C0(self, v28, (int)v99.S202, (int)v99.CarSystemManager);
        }
      }
    }
  }
  LOWORD(v44) = gta2::Car_sub_403820((struct Car *)&a5, &unk_662CFC);
  if ( v44 )
  {
    do
    {
      if ( !gta2::MapRelatedStruct_sub_4632E0(self, v10, v100.AudioSourceParams1, 0) || HIBYTE(v100.field_10) )
      {
        v66 = 0;
        HIBYTE(v100.field_10) = 0;
        switch ( v100.AudioSourceParams1 )
        {
          case 1:
          case 2:
            v67 = gta2::Player_sub_401B40(
                    (struct Player *)&pCarSystemManager.field_2,
                    (struct S202 *)((char *)&pCarSystemManager.field_44 + 2),
                    (int)&unk_662C98);
            v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v67);
            v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)((char *)&pCarSystemManager.field_4 + 2));
            v68 = gta2::S202_sub_401B20(
                    (struct S202 *)((char *)&pCarSystemManager.Weapon_ + 2),
                    (struct SpriteS1 *)&v103,
                    (struct PublicTransport *)&unk_662C98);
            v69 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v68);
            v70 = gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct, v69, (int)v99.S202, (int)v99.CarSystemManager);
            v10 = v70;
            if ( !v70
              || (v66 = (struct CarSystemManager *)gta2::MapRelatedStruct_sub_4633A0(self, v70, 0), v66 != (struct CarSystemManager *)3) )
            {
              v71 = gta2::Player_sub_401B40(
                      (struct Player *)&pCarSystemManager.field_2,
                      (struct S202 *)((char *)&pCarSystemManager.Player + 2),
                      (int)&unk_662C98);
              v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v71);
              v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)((char *)&pCarSystemManager.field_4
                                                                                   + 2));
              v72 = gta2::Player_sub_401B40(
                      (struct Player *)((char *)&pCarSystemManager.Weapon_ + 2),
                      (struct S202 *)((char *)&pCarSystemManager.field_20 + 2),
                      (int)&unk_662C98);
              goto LABEL_72;
            }
            break;
          case 3:
          case 4:
            v73 = gta2::Player_sub_401B40(
                    (struct Player *)&pCarSystemManager.field_2,
                    (struct S202 *)((char *)&pCarSystemManager.RecycledCars + 2),
                    (int)&unk_662C98);
            v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v73);
            v74 = gta2::S202_sub_401B20(
                    (struct S202 *)((char *)&pCarSystemManager.field_4 + 2),
                    (struct SpriteS1 *)((char *)&pCarSystemManager.field_30 + 2),
                    (struct PublicTransport *)&unk_662C98);
            v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v74);
            v75 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)((char *)&pCarSystemManager.Weapon_ + 2));
            v76 = gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct, v75, (int)v99.S202, (int)v99.CarSystemManager);
            v10 = v76;
            if ( !v76
              || (v66 = (struct CarSystemManager *)gta2::MapRelatedStruct_sub_4633A0(self, v76, 0), v66 != (struct CarSystemManager *)2) )
            {
              v77 = gta2::Player_sub_401B40(
                      (struct Player *)&pCarSystemManager.field_2,
                      (struct S202 *)((char *)&pCarSystemManager.field_38 + 2),
                      (int)&unk_662C98);
              v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v77);
              v78 = gta2::Player_sub_401B40(
                      (struct Player *)((char *)&pCarSystemManager.field_4 + 2),
                      (struct S202 *)((char *)&pCarSystemManager.RecycledCars_1 + 2),
                      (int)&unk_662C98);
              v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v78);
              v72 = (struct SpriteS1 *)((char *)&pCarSystemManager.Weapon_ + 2);
LABEL_72:
              v79 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v72);
              v10 = gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct, v79, (int)v99.S202, (int)v99.CarSystemManager);
              v66 = (struct CarSystemManager *)gta2::MapRelatedStruct_sub_4633A0(self, v10, 0);
            }
            break;
          default:
            break;
        }
        v80 = v10;
        if ( gta2::Player_sub_40CE70((struct Player *)&a5, &unk_662C98) )
        {
          sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
          v100.AudioSourceParams1 = (int)v66;
          sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
          FirstElement = gta2::Player_sub_401B40(
                           (struct Player *)&a5,
                           (struct S202 *)((char *)&pCarSystemManager.field_48 + 2),
                           (int)&unk_662C98)->FirstElement;
          a5 = (struct Player *)FirstElement;
          v82 = gta2::Player_sub_40CE70((struct Player *)&a5, &unk_662C98);
          v99.CarSystemManager = v66;
          if ( v82 )
          {
            sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
            v83 = gta2::Player_sub_401B40((struct Player *)&a5, (struct S202 *)&pCarSystemManager.field_52, (int)&unk_662C98)->FirstElement;
          }
          else
          {
            v99.S202 = (struct S202 *)FirstElement;
            sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
            v83 = (struct SpriteS1 *)unk_662CFC;
          }
          a5 = (struct Player *)v83;
          v84 = gta2::Player_sub_401B40(
                  (struct Player *)&v100.AudioSourceParams,
                  (struct S202 *)((char *)&pCarSystemManager.CarType + 2),
                  (int)&unk_662C98);
          v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v84);
          v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
          v85 = gta2::AudioSourceParams_sub_41F9D0(&v100);
          v10 = gta2::MapRelatedStruct_sub_4653C0(self, v85, (int)v99.S202, (int)v99.CarSystemManager);
          if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
          {
            v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v100.AudioSourceParams);
            v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
            v86 = gta2::AudioSourceParams_sub_41F9D0(&v100);
            v10 = gta2::MapRelatedStruct_sub_4653C0(self, v86, (int)v99.S202, (int)v99.CarSystemManager);
          }
          field = (int *)v100.field;
          v89 = v10 == v80;
          v7 = *(SpriteS1 **)&v99.field_1C;
          if ( v89 )
            goto LABEL_90;
          gta2::MapRelatedStruct_sub_467020(
            self,
            (int *)v100.field,
            *(SpriteS1 **)&v99.field_1C,
            &v100.AudioSourceParams,
            0,
            0);
          v87 = gta2::Player_sub_401B40(
                  (struct Player *)&v100.AudioSourceParams,
                  (struct S202 *)((char *)&pCarSystemManager.field_60 + 2),
                  (int)&unk_662C98);
          v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v87);
          v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
          v88 = gta2::AudioSourceParams_sub_41F9D0(&v100);
          v10 = gta2::MapRelatedStruct_sub_4653C0(self, v88, (int)v99.S202, (int)v99.CarSystemManager);
          v89 = (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC;
        }
        else
        {
          if ( gta2::Car_sub_403800((struct Car *)&a5, (int)&unk_6630B0) )
          {
            sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
            v90 = gta2::Player_sub_401B40(
                    (struct Player *)&v100.AudioSourceParams,
                    (struct S202 *)&pCarSystemManager.field_6A,
                    (int)&unk_662C98);
            v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v90);
            v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
            v91 = gta2::AudioSourceParams_sub_41F9D0(&v100);
            v10 = gta2::MapRelatedStruct_sub_4653C0(self, v91, (int)v99.S202, (int)v99.CarSystemManager);
            if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
            {
              v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v100.AudioSourceParams);
              v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
              v92 = gta2::AudioSourceParams_sub_41F9D0(&v100);
              v10 = gta2::MapRelatedStruct_sub_4653C0(self, v92, (int)v99.S202, (int)v99.CarSystemManager);
            }
            v100.AudioSourceParams1 = (int)v66;
            v93 = (struct S202 *)gta2::Player_sub_401B40((struct Player *)&a5, (struct S202 *)v104, (int)&unk_6630B0)->FirstElement;
          }
          else
          {
            v93 = (struct S202 *)a5;
          }
          v99.S202 = v93;
          sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
          gta2::bitShiftLeft1(&v100.AudioSourceParams2, 0);
          field = (int *)v100.field;
          v89 = v10 == v80;
          v7 = *(SpriteS1 **)&v99.field_1C;
          a5 = (struct Player *)v100.AudioSourceParams2;
          if ( v89 )
            goto LABEL_90;
          gta2::MapRelatedStruct_sub_467020(
            self,
            (int *)v100.field,
            *(SpriteS1 **)&v99.field_1C,
            &v100.AudioSourceParams,
            0,
            0);
          v94 = gta2::Player_sub_401B40(
                  (struct Player *)&v100.AudioSourceParams,
                  (struct S202 *)((char *)&pCarSystemManager.ID + 2),
                  (int)&unk_662C98);
          v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v94);
          v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
          v95 = gta2::AudioSourceParams_sub_41F9D0(&v100);
          v10 = gta2::MapRelatedStruct_sub_4653C0(self, v95, (int)v99.S202, (int)v99.CarSystemManager);
          v89 = (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC;
        }
        if ( v89 )
        {
          v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v100.AudioSourceParams);
          v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
          v96 = gta2::AudioSourceParams_sub_41F9D0(&v100);
          v10 = gta2::MapRelatedStruct_sub_4653C0(self, v96, (int)v99.S202, (int)v99.CarSystemManager);
        }
      }
      else
      {
        v101 = (struct SpriteS1 *)v10;
        *(Weapon **)((char *)&pCarSystemManager.Weapon_ + 2) = (struct Weapon *)field;
        *(int *)((char *)&pCarSystemManager.field_4 + 2) = (int)v7;
        *(_DWORD *)&pCarSystemManager.field_2 = v100.AudioSourceParams;
        v45 = gta2::Player_sub_40CE70((struct Player *)&a5, &unk_662C98);
        v99.CarSystemManager = (struct CarSystemManager *)v100.AudioSourceParams1;
        if ( v45 )
        {
          sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
          a5 = (struct Player *)gta2::Player_sub_401B40(
                           (struct Player *)&a5,
                           (struct S202 *)((char *)&pCarSystemManager.field_2C + 2),
                           (int)&unk_662C98)->FirstElement;
        }
        else
        {
          v99.S202 = (struct S202 *)a5;
          sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
          a5 = (struct Player *)unk_662CFC;
        }
        v46 = gta2::Player_sub_401B40((struct Player *)&v100.AudioSourceParams, (struct S202 *)v106, (int)&unk_662C98);
        v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v46);
        v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
        v47 = gta2::AudioSourceParams_sub_41F9D0(&v100);
        v48 = gta2::MapRelatedStruct_sub_4653C0(self, v47, (int)v99.S202, (int)v99.CarSystemManager);
        field = (int *)v100.field;
        v7 = *(SpriteS1 **)&v99.field_1C;
        v10 = v48;
        if ( !v48 )
          goto LABEL_59;
        if ( (*(_BYTE *)(v48 + 11) & 0xFC) == 0xFC )
        {
          v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v100.AudioSourceParams);
          v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
          v49 = gta2::AudioSourceParams_sub_41F9D0(&v100);
          v10 = gta2::MapRelatedStruct_sub_4653C0(self, v49, (int)v99.S202, (int)v99.CarSystemManager);
        }
        if ( (struct SpriteS1 *)v10 != v101 )
        {
          gta2::MapRelatedStruct_sub_467020(self, field, v7, &v100.AudioSourceParams, 0, 0);
          v50 = gta2::Player_sub_401B40(
                  (struct Player *)&v100.AudioSourceParams,
                  (struct S202 *)((char *)&pCarSystemManager.field_24 + 2),
                  (int)&unk_662C98);
          v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v50);
          v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
          v51 = gta2::AudioSourceParams_sub_41F9D0(&v100);
          v52 = gta2::MapRelatedStruct_sub_4653C0(self, v51, (int)v99.S202, (int)v99.CarSystemManager);
          v10 = v52;
          if ( !v52 )
            goto LABEL_59;
          if ( (*(_BYTE *)(v52 + 11) & 0xFC) == 0xFC )
          {
            v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v100.AudioSourceParams);
            v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
            v53 = gta2::AudioSourceParams_sub_41F9D0(&v100);
            v10 = gta2::MapRelatedStruct_sub_4653C0(self, v53, (int)v99.S202, (int)v99.CarSystemManager);
          }
        }
        if ( !v10 || !gta2::MapRelatedStruct_sub_4632E0(self, v10, v100.AudioSourceParams1, 0) )
        {
LABEL_59:
          v101 = (struct SpriteS1 *)v10;
          LOWORD(v54) = *gta2::sub_4725B0((unsigned __int16 *)&pCarSystemManager.field_10, &v100.AudioSourceParams1);
          v99.CarSystemManager = v54;
          v99.S202 = (struct S202 *)v7;
          v99.field_0 = (int)field;
          v100.field_14 = (int)*gta2::sub_463210((SpriteS1 **)((char *)&pCarSystemManager.SpriteS1_0 + 2), v99);
          v55 = (struct CarSystemManager *)gta2::sub_4725B0(
                                      (unsigned __int16 *)&pCarSystemManager.field_1C,
                                      &v100.AudioSourceParams1);
          v56 = (struct SpriteS1 *)gta2::sub_40E5A0(v55, &pCarSystemManager, &unk_663108);
          gta2::SpriteS1_sub_472C00(v56);
          sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
          gta2::Player_sub_401B40(
            (struct Player *)&unk_662C98,
            (struct S202 *)((char *)&pCarSystemManager.field_1C + 2),
            (int)&v100.field_14);
          v57 = (struct CarSystemManager *)gta2::sub_4725B0((unsigned __int16 *)&pCarSystemManager.ID, &v100.AudioSourceParams1);
          v58 = (struct SpriteS1 *)gta2::sub_40E5A0(v57, (struct CarSystemManager *)&pCarSystemManager.field_12, &unk_663108);
          gta2::SpriteS1_sub_472C00(v58);
          sub_4630D0((struct SpriteS1 *)&v100, (struct SpriteS1 *)&v99.field_1C);
          v99.CarSystemManager = (struct CarSystemManager *)gta2::Player_sub_401B40(
                                                       (struct Player *)&unk_662C98,
                                                       (struct S202 *)&pCarSystemManager.field_56,
                                                       (int)&v100.field_14);
          v59 = gta2::S202_sub_401B20((struct S202 *)&a5, (struct SpriteS1 *)&v105, (struct PublicTransport *)&unk_662C98);
          a5 = (struct Player *)gta2::S202_sub_401B20(
                           (struct S202 *)v59,
                           (struct SpriteS1 *)((char *)&pCarSystemManager.UnitCars + 2),
                           (struct PublicTransport *)v99.CarSystemManager)->FirstElement;
          v100.AudioSourceParams = *(_DWORD *)&pCarSystemManager.field_2;
          v60 = gta2::Player_sub_401B40(
                  (struct Player *)&v100.AudioSourceParams,
                  (struct S202 *)((char *)&pCarSystemManager.MissionCars + 2),
                  (int)&unk_662C98);
          v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v60);
          v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
          v61 = gta2::AudioSourceParams_sub_41F9D0(&v100);
          v10 = gta2::MapRelatedStruct_sub_4653C0(self, v61, (int)v99.S202, (int)v99.CarSystemManager);
          if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
          {
            v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v100.AudioSourceParams);
            v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
            v62 = gta2::AudioSourceParams_sub_41F9D0(&v100);
            v10 = gta2::MapRelatedStruct_sub_4653C0(self, v62, (int)v99.S202, (int)v99.CarSystemManager);
          }
          field = (int *)v100.field;
          v7 = *(SpriteS1 **)&v99.field_1C;
          if ( (struct SpriteS1 *)v10 != v101 )
          {
            gta2::MapRelatedStruct_sub_467020(
              self,
              (int *)v100.field,
              *(SpriteS1 **)&v99.field_1C,
              &v100.AudioSourceParams,
              0,
              0);
            v63 = gta2::Player_sub_401B40(
                    (struct Player *)&v100.AudioSourceParams,
                    (struct S202 *)&pCarSystemManager.field_5E,
                    (int)&unk_662C98);
            v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v63);
            v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
            v64 = gta2::AudioSourceParams_sub_41F9D0(&v100);
            v10 = gta2::MapRelatedStruct_sub_4653C0(self, v64, (int)v99.S202, (int)v99.CarSystemManager);
            if ( (*(_BYTE *)(v10 + 11) & 0xFC) == 0xFC )
            {
              v99.CarSystemManager = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v100.AudioSourceParams);
              v99.S202 = (struct S202 *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&v99.field_1C);
              v65 = gta2::AudioSourceParams_sub_41F9D0(&v100);
              v10 = gta2::MapRelatedStruct_sub_4653C0(self, v65, (int)v99.S202, (int)v99.CarSystemManager);
            }
          }
          HIBYTE(v100.field_10) = 1;
        }
      }
LABEL_90:
      LOWORD(v97) = gta2::Car_sub_403820((struct Car *)&a5, &unk_662CFC);
    }
    while ( v97 );
  }
  v99.CarSystemManager = (struct CarSystemManager *)v100.AudioSourceParams;
  *arg0 = field;
  *a3 = v7;
  *a4 = *gta2::MapRelatedStruct_sub_466E20(
           self,
           (int *)((char *)&pCarSystemManager.ID + 2),
           field,
           v7,
           (int)v99.CarSystemManager);
  return sub_42A660(&v100.AudioSourceParams1);
}


// 0x00469110: MapRelatedStruct::sub_469110
// IDA: MapRelatedStruct::sub_469110
// Ghidra: ---
char * gta2::MapRelatedStruct_sub_469110(
        struct MapRelatedStruct *self,
        unsigned __int8 arg0,
        unsigned __int8 a2,
        char a4)
{
  char *v5; // ebx
  _WORD *count; // ecx
  int v8; // eax
  char *v9; // eax
  char *v10; // esi
  unsigned __int16 v11; // dx
  int v12; // edx
  int v13; // esi
  char *v14; // eax
  int v15; // edx
  char *v16; // [esp+8h] [ebp-28h]
  void *Car; // [esp+14h] [ebp-1Ch] BYREF
  int v18; // [esp+18h] [ebp-18h]
  int v19; // [esp+1Ch] [ebp-14h] BYREF
  int v20; // [esp+20h] [ebp-10h] BYREF
  int v21; // [esp+24h] [ebp-Ch] BYREF
  int v22; // [esp+28h] [ebp-8h] BYREF
  char v23[4]; // [esp+2Ch] [ebp-4h] BYREF

  v5 = 0;
  v16 = 0;
  if ( !self->Buffer_ZONE )
    return 0;
  count = (_WORD *)self->count;
  LOWORD(v8) = 0;
  v18 = 0;
  if ( !*count )
    goto LABEL_17;
  do
  {
    v9 = gta2::MapRelatedStruct_sub_462E40(self, v8);
    v10 = v9;
    if ( *v9 == a4 && !gta2::sub_4690B0(v9) )
    {
      gta2::S202_sub_40CE30((struct S202 *)&v19, a2);
      gta2::S202_sub_40CE30((struct S202 *)&v20, arg0);
      gta2::S202_sub_40CE30((struct S202 *)&v21, v10[2]);
      gta2::S202_sub_40CE30((struct S202 *)&v22, v10[1]);
      Car = gta2::sub_42A6B0(&v22, v23)->Car;
      if ( gta2::sub_4037E0(&Car) )
      {
        if ( gta2::Car_sub_403800((struct Car *)&Car, (int)&unk_662CF8) )
        {
          v5 = v16;
          if ( !v16 )
            v5 = v10;
          v16 = v10;
        }
      }
      else if ( gta2::sub_4037E0(&Car) )
      {
        v5 = v10;
      }
    }
    v8 = v18 + 1;
    v11 = *(_WORD *)self->count;
    v18 = v8;
  }
  while ( v8 < v11 );
  if ( v5 )
    return v5;
  if ( !v16 )
  {
LABEL_17:
    LOWORD(v12) = 0;
    v13 = *(unsigned __int16 *)self->count;
    if ( (_WORD)v13 )
    {
      do
      {
        v14 = gta2::MapRelatedStruct_sub_462E40(self, v12);
        if ( *v14 == a4 )
          v16 = v14;
        v12 = v15 + 1;
      }
      while ( v12 < v13 );
    }
  }
  return v16;
}


// 0x004692b0: MapRelatedStruct::sub_4692B0
// IDA: MapRelatedStruct::sub_4692B0
// Ghidra: ---
unsigned int gta2::MapRelatedStruct_sub_4692B0(struct MapRelatedStruct *self)
{
  unsigned int result; // eax
  FILE *Buffer_LGHT; // esi
  struct SpriteS1 *FirstElement; // edi
  struct SpriteS1 *v4; // ebx
  struct SpriteS1 *v5; // ebp
  int v6; // eax
  char v7; // cl
  unsigned int v8; // edx
  int v9; // [esp+0h] [ebp-1Ch] BYREF
  unsigned int v10; // [esp+4h] [ebp-18h]
  struct MapRelatedStruct *v11; // [esp+8h] [ebp-14h]
  char v12[4]; // [esp+Ch] [ebp-10h] BYREF
  char v13[4]; // [esp+10h] [ebp-Ch] BYREF
  char v14[4]; // [esp+14h] [ebp-8h] BYREF
  char v15[4]; // [esp+18h] [ebp-4h] BYREF

  result = self->field_348;
  v11 = self;
  if ( result )
  {
    Buffer_LGHT = self->Buffer_LGHT;
    v10 = 0;
    do
    {
      FirstElement = sub_462ED0((struct SpriteS1 *)v12, (__int16 *)&Buffer_LGHT[1])->FirstElement;
      v4 = sub_462ED0((struct SpriteS1 *)v13, (__int16 *)&Buffer_LGHT[1]._Placeholder + 1)->FirstElement;
      v5 = sub_462ED0((struct SpriteS1 *)v14, (__int16 *)&Buffer_LGHT[2])->FirstElement;
      v9 = (int)sub_462ED0((struct SpriteS1 *)v15, (__int16 *)&Buffer_LGHT[2]._Placeholder + 1)->FirstElement;
      if ( gta2::Player_IsCurrentPlayer((struct Player *)&v9, (struct Player *)&unk_662C3C) )
        gta2::Weapon_UseAmmo((struct Weapon *)&v9, &unk_6630B8);
      v6 = gta2::S115_sub_469010(
             gS115,
             (int)FirstElement,
             (int)v4,
             (int)v5,
             (int)Buffer_LGHT->_Placeholder,
             v9,
             (unsigned __int8)Buffer_LGHT[3]._Placeholder);
      v7 = BYTE2(Buffer_LGHT[3]._Placeholder);
      if ( v7 )
        gta2::S115_sub_469070(gS115, v6, v7, HIBYTE(Buffer_LGHT[3]._Placeholder), BYTE1(Buffer_LGHT[3]._Placeholder));
      result = v10 + 1;
      Buffer_LGHT += 4;
      v8 = v11->field_348;
      v10 = result;
    }
    while ( result < v8 );
  }
  return result;
}


// 0x00469400: MapRelatedStruct::sub_469400
// IDA: MapRelatedStruct::sub_469400
// Ghidra: ---
char gta2::MapRelatedStruct_sub_469400(struct MapRelatedStruct *self, _BYTE *a1, _BYTE *a2, _BYTE *a3, char a4)
{
  int v5; // ebx
  int v6; // esi
  int v7; // eax
  int v8; // ecx
  int v9; // edi
  int v10; // edi
  int v11; // edi
  int v12; // edi
  char result; // al

  v5 = (unsigned __int8)*a1;
  unk_662B80 = v5;
  unk_662BB4 = (unsigned __int8)*a2;
  v6 = 1;
  unk_662BB8 = (unsigned __int8)*a3;
  while ( 2 )
  {
    v7 = 3;
LABEL_3:
    v8 = v7 - 1;
    switch ( v7 )
    {
      case 1:
        v12 = 0;
        if ( !(_WORD)v6 )
          goto LABEL_19;
        do
        {
          --unk_662BB4;
          if ( gta2::sub_4693A0(v8, a4) )
            goto LABEL_22;
          ++v12;
        }
        while ( (unsigned __int16)v12 < (unsigned __int16)v6 );
LABEL_19:
        ++v6;
        continue;
      case 2:
        v10 = 0;
        if ( !(_WORD)v6 )
          goto LABEL_11;
        while ( 1 )
        {
          ++unk_662BB4;
          if ( gta2::sub_4693A0(v8, a4) )
            break;
          if ( (unsigned __int16)++v10 >= (unsigned __int16)v6 )
          {
LABEL_11:
            v7 = 4;
            ++v6;
            goto LABEL_3;
          }
        }
        *a1 = v5;
        *a2 = unk_662BB4;
        result = unk_662BB8;
        *a3 = unk_662BB8;
        return result;
      case 3:
        v9 = 0;
        if ( !(_WORD)v6 )
          goto LABEL_7;
        while ( 1 )
        {
          unk_662B80 = ++v5;
          if ( gta2::sub_4693A0(v8, a4) )
            break;
          if ( (unsigned __int16)++v9 >= (unsigned __int16)v6 )
          {
LABEL_7:
            v7 = 2;
            goto LABEL_3;
          }
        }
LABEL_22:
        *a1 = v5;
        *a2 = unk_662BB4;
        result = (char)a3;
        *a3 = unk_662BB8;
        return result;
      case 4:
        v11 = 0;
        if ( !(_WORD)v6 )
          goto LABEL_15;
        break;
      default:
        goto LABEL_3;
    }
    break;
  }
  while ( 1 )
  {
    unk_662B80 = --v5;
    if ( gta2::sub_4693A0(v8, a4) )
      break;
    if ( (unsigned __int16)++v11 >= (unsigned __int16)v6 )
    {
LABEL_15:
      v7 = 1;
      goto LABEL_3;
    }
  }
  result = (char)a2;
  *a1 = v5;
  *a2 = unk_662BB4;
  *a3 = unk_662BB8;
  return result;
}


// 0x00469570: MapRelatedStruct::sub_469570
// IDA: MapRelatedStruct::sub_469570
// Ghidra: FUN_00469570
undefined4 * gta2::MapRelatedStruct_sub_469570(Player *param_1,undefined4 *param_2,undefined4 param_3, undefined4 param_4,SpriteS1 *param_5)
{
  undefined4 uVar1;
  undefined4 uVar2;
  bool bVar3;
  byte bVar4;
  struct Car *self;
  undefined3 extraout_var;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined3 extraout_var_00;
  void *this_00;
  struct Car *pCVar9;
  int *piVar10;
  struct Player *local_4;
  
  pCVar9 = (struct Car *)&DAT_00662cfc;
  local_4 = param_1;
  self = (struct Car *)FUN_0042a630(&local_4,&param_5);
  bVar3 = gta2::Car_IsTrainOrTrainCarriage(self,pCVar9);
  uVar2 = param_4;
  uVar1 = param_3;
  if (CONCAT31(extraout_var,bVar3) != 0) {
    iVar5 = DecoderFloat(&param_5);
    iVar6 = DecoderFloat(&param_4);
    iVar7 = DecoderFloat(&param_3);
    bVar4 = gta2::MapRelatedStruct_sub_466CF0((struct MapRelatedStruct *)param_1,iVar7,iVar6,iVar5);
    if (bVar4 != 0) {
      puVar8 = (undefined4 *)
               FUN_00462ea0(this_00,(uint *)&local_4,(uint *)&param_5);
      local_4 = (struct Player *)*puVar8;
      FUN_00466b70(uVar1,uVar2,&local_4);
      bVar3 = gta2::Player_CheckCondition((struct Player *)&local_4,(int *)&param_5);
      if (CONCAT31(extraout_var_00,bVar3) != 0) {
        *param_2 = local_4;
        return param_2;
      }
    }
  }
  iVar5 = DecoderFloat(&param_5);
  piVar10 = (int *)&param_5;
  param_5 = (struct SpriteS1 *)(iVar5 - 1);
  iVar5 = DecoderFloat(&param_4);
  iVar6 = DecoderFloat(&param_3);
  gMaxZForTile = (void *)gta2::MapRelatedStruct_sub_466A00((struct MapRelatedStruct *)param_1,iVar6,iVar5,
                                    piVar10);
  if (gMaxZForTile == NULL) {
    *param_2 = _DAT_00662c98;
    return param_2;
  }
  bVar4 = *(byte *)((int)gMaxZForTile + 0xb);
  puVar8 = (undefined4 *)
           (CONCAT31((int3)((uint)gMaxZForTile >> 8),bVar4) & 0xfffffffc);
  if ((((bVar4 & 0xfc) != 0) && ((bVar4 & 0xfc) < 0xb4)) && ((bVar4 & 3) != 0))
  {
    gta2::S202_sub_41F980((struct SpriteS1 *)&param_5,(int)param_5);
    local_4 = (struct Player *)*puVar8;
    FUN_00466b70(uVar1,uVar2,&local_4);
    *param_2 = local_4;
    return param_2;
  }
  gta2::S202_sub_41F980((struct SpriteS1 *)&param_5,(int)((int)&param_5->FirstElement + 1));
  *param_2 = *puVar8;
  return param_2;
}


// 0x004696c0: MapRelatedStruct::sub_4696C0
// IDA: MapRelatedStruct::sub_4696C0
// Ghidra: FUN_004696c0
void gta2::MapRelatedStruct_sub_4696C0(MapRelatedStruct *param_1,char *param_2,undefined4 param_3, undefined4 param_4,SpriteS1 *param_5)
{
  undefined4 uVar1;
  undefined4 uVar2;
  bool bVar3;
  byte bVar4;
  struct SpriteS1 *pSVar5;
  undefined3 extraout_var;
  int iVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  undefined3 extraout_var_00;
  void *self;
  Point2D *this_00;
  struct SpriteS1 *pSVar10;
  undefined3 extraout_var_01;
  struct S127 *pS127;
  undefined1 local_1c [4];
  Player *local_18 [2];
  uint local_10 [3];
  uint local_4;
  
  pSVar10 = param_5;
  local_1c = (undefined1  [4])param_5;
  pSVar5 = gta2::S202_sub_401B20((Point2D *)&param_5,(struct SpriteS1 *)(local_18 + 1),
                      (struct S127 *)&DAT_00662c98);
  bVar3 = gta2::Point2D_FUN_004037e0((Point2D *)local_1c,pSVar5);
  uVar2 = param_4;
  uVar1 = param_3;
  iVar6 = CONCAT31(extraout_var,bVar3);
  do {
    if (iVar6 == 0) {
      *(SpriteS1 **)param_2 = param_5;
      return;
    }
    iVar6 = DecoderFloat(local_1c);
    iVar7 = DecoderFloat(&param_4);
    iVar8 = DecoderFloat(&param_3);
    gMaxZForTile = (void *)gta2::MapRelatedStruct_sub_4653C0(param_1,iVar8,iVar7,iVar6);
    if ((gMaxZForTile == NULL) ||
       ((*(byte *)((int)gMaxZForTile + 0xb) & 3) == 0)) {
      self = gta2::Player_sub_401B40((SpawnPoint *)local_1c,(GlassInfo *)(local_10 + 1),
                        (struct S127 *)&DAT_00662c98);
      iVar6 = DecoderFloat(self);
      iVar7 = DecoderFloat(&param_4);
      iVar8 = DecoderFloat(&param_3);
      gMaxZForTile = (void *)gta2::MapRelatedStruct_sub_4653C0(param_1,iVar8,iVar7,iVar6);
      if (((gMaxZForTile != NULL) &&
          ((*(byte *)((int)gMaxZForTile + 0xb) & 3) != 0)) &&
         ((bVar4 = *(byte *)((int)gMaxZForTile + 0xb) & 0xfc, bVar4 == 0 ||
          (0xb3 < bVar4)))) {
        *(SpriteS1 **)param_2 = pSVar10;
        return;
      }
    }
    else {
      bVar4 = *(byte *)((int)gMaxZForTile + 0xb) & 0xfc;
      if ((bVar4 != 0) && (bVar4 < 0xb4)) {
        pcVar9 = (char *)FUN_00462ea0(local_1c,local_10,(uint *)local_1c);
        local_18[0] = *(Player **)pcVar9;
        FUN_00466b70(uVar1,uVar2,local_18);
        bVar3 = gta2::Player_sub_40CE70((struct Player *)local_18,(struct Player *)local_1c);
        if (CONCAT31(extraout_var_00,bVar3) != 0) {
          *(Player **)param_2 = local_18[0];
          return;
        }
      }
    }
    pSVar10 = (struct SpriteS1 *)(local_10 + 2);
    pS127 = (struct S127 *)&DAT_00662c98;
    this_00 = (Point2D *)FUN_00462ea0(pSVar10,&local_4,(uint *)local_1c);
    pSVar10 = gta2::S202_sub_401B20(this_00,pSVar10,pS127);
    pSVar10 = pSVar10->FirstElement;
    local_1c = (undefined1  [4])pSVar10;
    pSVar5 = gta2::S202_sub_401B20((Point2D *)&param_5,(struct SpriteS1 *)(local_18 + 1),
                        (struct S127 *)&DAT_00662c98);
    bVar3 = gta2::Point2D_FUN_004037e0((Point2D *)local_1c,pSVar5);
    iVar6 = CONCAT31(extraout_var_01,bVar3);
  } while( true );
}


// 0x00469850: MapRelatedStruct::sub_469850
// IDA: MapRelatedStruct::sub_469850
// Ghidra: FUN_00469850
undefined4 * gta2::MapRelatedStruct_sub_469850(Player *param_1,undefined4 *param_2,undefined4 param_3, undefined4 param_4,SpriteS1 *param_5)
{
  undefined4 uVar1;
  undefined4 uVar2;
  bool bVar3;
  byte bVar4;
  struct Car *self;
  undefined3 extraout_var;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined3 extraout_var_00;
  void *this_00;
  struct Car *pCVar9;
  int *piVar10;
  struct Player *local_4;
  
  pCVar9 = (struct Car *)&DAT_00662cfc;
  local_4 = param_1;
  self = (struct Car *)FUN_0042a630(&local_4,&param_5);
  bVar3 = gta2::Car_IsTrainOrTrainCarriage(self,pCVar9);
  uVar2 = param_4;
  uVar1 = param_3;
  if (CONCAT31(extraout_var,bVar3) != 0) {
    iVar5 = DecoderFloat(&param_5);
    iVar6 = DecoderFloat(&param_4);
    iVar7 = DecoderFloat(&param_3);
    bVar4 = gta2::MapRelatedStruct_sub_466CF0((struct MapRelatedStruct *)param_1,iVar7,iVar6,iVar5);
    if (bVar4 != 0) {
      puVar8 = (undefined4 *)
               FUN_00462ea0(this_00,(uint *)&local_4,(uint *)&param_5);
      local_4 = (struct Player *)*puVar8;
      FUN_00466b70(uVar1,uVar2,&local_4);
      bVar3 = gta2::Player_CheckCondition((struct Player *)&local_4,(int *)&param_5);
      if (CONCAT31(extraout_var_00,bVar3) != 0) {
        *param_2 = local_4;
        return param_2;
      }
    }
  }
  iVar5 = DecoderFloat(&param_5);
  piVar10 = (int *)&param_5;
  param_5 = (struct SpriteS1 *)(iVar5 - 1);
  iVar5 = DecoderFloat(&param_4);
  iVar6 = DecoderFloat(&param_3);
  gMaxZForTile = (void *)gta2::MapRelatedStruct_sub_466A00((struct MapRelatedStruct *)param_1,iVar6,iVar5,
                                    piVar10);
  if (gMaxZForTile == NULL) {
    *param_2 = _DAT_00662cfc;
    return param_2;
  }
  bVar4 = *(byte *)((int)gMaxZForTile + 0xb);
  puVar8 = (undefined4 *)
           (CONCAT31((int3)((uint)gMaxZForTile >> 8),bVar4) & 0xfffffffc);
  if ((((bVar4 & 0xfc) != 0) && ((bVar4 & 0xfc) < 0xb4)) && ((bVar4 & 3) != 0))
  {
    gta2::S202_sub_41F980((struct SpriteS1 *)&param_5,(int)param_5);
    local_4 = (struct Player *)*puVar8;
    FUN_00466b70(uVar1,uVar2,&local_4);
    *param_2 = local_4;
    return param_2;
  }
  gta2::S202_sub_41F980((struct SpriteS1 *)&param_5,(int)((int)&param_5->FirstElement + 1));
  *param_2 = *puVar8;
  return param_2;
}


// 0x004699a0: MapRelatedStruct::sub_4699A0
// IDA: MapRelatedStruct::sub_4699A0
// Ghidra: FUN_004699a0
uint * gta2::MapRelatedStruct_sub_4699A0(MapRelatedStruct *param_1,uint *param_2,undefined4 param_3, undefined4 param_4,SpriteS1 *param_5,SpriteS1 *param_6)
{
  undefined4 uVar1;
  undefined4 uVar2;
  struct SpriteS1 *pSVar3;
  bool bVar4;
  byte bVar5;
  struct Car *self;
  undefined3 extraout_var;
  int iVar6;
  int iVar7;
  int iVar8;
  uint *puVar9;
  undefined3 extraout_var_00;
  void *this_00;
  struct Car *pCVar10;
  int *piVar11;
  
  pSVar3 = param_6;
  pCVar10 = (struct Car *)&DAT_00662cfc;
  *(undefined1 *)&param_6->FirstElement = 0;
  self = (struct Car *)FUN_0042a630(&param_6,&param_5);
  bVar4 = gta2::Car_IsTrainOrTrainCarriage(self,pCVar10);
  uVar2 = param_4;
  uVar1 = param_3;
  if (CONCAT31(extraout_var,bVar4) != 0) {
    iVar6 = DecoderFloat(&param_5);
    iVar7 = DecoderFloat(&param_4);
    iVar8 = DecoderFloat(&param_3);
    bVar5 = gta2::MapRelatedStruct_sub_466CF0(param_1,iVar8,iVar7,iVar6);
    if (bVar5 != 0) {
      puVar9 = (uint *)FUN_00462ea0(this_00,(uint *)&param_6,(uint *)&param_5);
      param_6 = (struct SpriteS1 *)*puVar9;
      FUN_00466b70(uVar1,uVar2,&param_6);
      bVar4 = gta2::Player_CheckCondition((struct Player *)&param_6,(int *)&param_5);
      if (CONCAT31(extraout_var_00,bVar4) != 0) {
        *param_2 = (uint)param_6;
        return param_2;
      }
      *(undefined1 *)&pSVar3->FirstElement = 1;
    }
  }
  iVar6 = DecoderFloat(&param_5);
  piVar11 = (int *)&param_5;
  param_5 = (struct SpriteS1 *)(iVar6 - 1);
  iVar6 = DecoderFloat(&param_4);
  iVar7 = DecoderFloat(&param_3);
  gMaxZForTile = (void *)gta2::MapRelatedStruct_sub_466A00(param_1,iVar7,iVar6,piVar11);
  if (gMaxZForTile == NULL) {
    *param_2 = _DAT_00662c98;
    return param_2;
  }
  bVar5 = *(byte *)((int)gMaxZForTile + 0xb);
  puVar9 = (uint *)CONCAT31((int3)((uint)gMaxZForTile >> 8),bVar5);
  if ((((bVar5 & 0xfc) != 0) && ((bVar5 & 0xfc) < 0xb4)) && ((bVar5 & 3) != 0))
  {
    gta2::S202_sub_41F980((struct SpriteS1 *)&param_5,(int)param_5);
    param_6 = (struct SpriteS1 *)*puVar9;
    FUN_00466b70(uVar1,uVar2,&param_6);
    *param_2 = (uint)param_6;
    return param_2;
  }
  gta2::S202_sub_41F980((struct SpriteS1 *)&param_5,(int)((int)&param_5->FirstElement + 1));
  *param_2 = *puVar9;
  return param_2;
}


// 0x00469c20: MapRelatedStruct::sub_469C20
// IDA: MapRelatedStruct::sub_469C20
// Ghidra: FUN_00469c20
uint gta2::MapRelatedStruct_sub_469C20(MapRelatedStruct *param_1,undefined4 param_2,undefined4 param_3)
{
  undefined4 uVar1;
  undefined4 uVar2;
  bool bVar3;
  byte bVar4;
  undefined3 extraout_var;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined3 uVar9;
  void *pvVar8;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  void *self;
  struct Player *local_8;
  struct Player *local_4;
  
  FUN_00462ea0(&local_4,(uint *)&local_4,(uint *)&stack0x0000000c);
  FUN_00462ea0(self,(uint *)&local_8,(uint *)&stack0x00000010);
  bVar3 = gta2::Player_IsCurrentPlayer((struct Player *)&local_4,(struct Player *)&local_8);
  if (CONCAT31(extraout_var,bVar3) == 0) {
    iVar5 = DecoderFloat(&local_8);
    iVar6 = DecoderFloat(&param_3);
    iVar7 = DecoderFloat(&param_2);
    gMaxZForTile = (void *)gta2::MapRelatedStruct_sub_4653C0(param_1,iVar7,iVar6,iVar5);
    uVar2 = param_3;
    uVar1 = param_2;
    if ((((gMaxZForTile != NULL) &&
         ((*(byte *)((int)gMaxZForTile + 0xb) & 3) != 0)) &&
        (bVar4 = *(byte *)((int)gMaxZForTile + 0xb) & 0xfc, bVar4 != 0)) &&
       (bVar4 < 0xb4)) {
      FUN_00466b70(param_2,param_3,&local_8);
      bVar3 = gta2::Player_sub_40CE70((struct Player *)&stack0x00000010,(struct Player *)&local_8);
      pvVar8 = (void *)CONCAT31(extraout_var_01,bVar3);
      if (pvVar8 != NULL) goto LAB_00469db2;
    }
    iVar5 = DecoderFloat(&local_4);
    iVar6 = DecoderFloat(&param_3);
    iVar7 = DecoderFloat(&param_2);
    gMaxZForTile = (void *)gta2::MapRelatedStruct_sub_4653C0(param_1,iVar7,iVar6,iVar5);
    pvVar8 = gMaxZForTile;
    if (gMaxZForTile == NULL) goto LAB_00469cc9;
    bVar4 = *(byte *)((int)gMaxZForTile + 0xb);
    uVar9 = (undefined3)((uint)gMaxZForTile >> 8);
    pvVar8 = (void *)CONCAT31(uVar9,bVar4);
    if ((bVar4 & 3) == 0) goto LAB_00469cc9;
    pvVar8 = (void *)(CONCAT31(uVar9,bVar4) & 0xfffffffc);
    if (((bVar4 & 0xfc) == 0) || (0xb3 < (bVar4 & 0xfc))) goto LAB_00469db2;
    local_8 = local_4;
    FUN_00466b70(uVar1,uVar2,&local_8);
  }
  else {
    iVar5 = DecoderFloat(&local_4);
    iVar6 = DecoderFloat(&param_3);
    iVar7 = DecoderFloat(&param_2);
    gMaxZForTile = (void *)gta2::MapRelatedStruct_sub_4653C0(param_1,iVar7,iVar6,iVar5);
    pvVar8 = gMaxZForTile;
    if (gMaxZForTile == NULL) goto LAB_00469cc9;
    bVar4 = *(byte *)((int)gMaxZForTile + 0xb);
    uVar9 = (undefined3)((uint)gMaxZForTile >> 8);
    pvVar8 = (void *)CONCAT31(uVar9,bVar4);
    if ((bVar4 & 3) == 0) goto LAB_00469cc9;
    pvVar8 = (void *)(CONCAT31(uVar9,bVar4) & 0xfffffffc);
    if (((bVar4 & 0xfc) == 0) || (0xb3 < (bVar4 & 0xfc))) goto LAB_00469cc9;
    local_8 = local_4;
    FUN_00466b70(param_2,param_3,&local_8);
    bVar3 = gta2::Player_sub_40CE70((struct Player *)&stack0x00000010,(struct Player *)&local_8)
    ;
    pvVar8 = (void *)CONCAT31(extraout_var_00,bVar3);
    if ((void *)CONCAT31(extraout_var_00,bVar3) == NULL) goto LAB_00469cc9;
  }
  bVar3 = gta2::Player_CheckCondition((struct Player *)&stack0x0000000c,(int *)&local_8);
  pvVar8 = (void *)CONCAT31(extraout_var_02,bVar3);
  if (pvVar8 != NULL) {
LAB_00469db2:
    return CONCAT31((int3)((uint)pvVar8 >> 8),1);
  }
LAB_00469cc9:
  return (uint)pvVar8 & 0xffffff00;
}


// 0x00469dc0: MapRelatedStruct::sub_469DC0
// IDA: MapRelatedStruct::sub_469DC0
// Ghidra: FUN_00469dc0
undefined4 gta2::MapRelatedStruct_sub_469DC0(MapRelatedStruct *param_1,undefined4 param_2,SpriteS1 *param_3, undefined4 param_4,undefined4 param_5,Player *param_6)
{
  undefined4 uVar1;
  struct Player *pPVar2;
  bool bVar3;
  byte bVar4;
  undefined3 extraout_var;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  struct SpriteS1 *pSVar8;
  void *self;
  struct Player *local_8;
  struct Player *local_4;
  
  FUN_00462ea0(&local_8,(uint *)&local_8,&param_4);
  FUN_00462ea0(self,(uint *)&local_4,&param_5);
  bVar3 = gta2::Player_IsCurrentPlayer((struct Player *)&local_8,(struct Player *)&local_4);
  if (CONCAT31(extraout_var,bVar3) == 0) {
    iVar5 = DecoderFloat(&local_4);
    iVar6 = DecoderFloat(&param_3);
    iVar7 = DecoderFloat(&param_2);
    gMaxZForTile = (void *)gta2::MapRelatedStruct_sub_4653C0(param_1,iVar7,iVar6,iVar5);
    pPVar2 = param_6;
    pSVar8 = param_3;
    uVar1 = param_2;
    if ((((gMaxZForTile != NULL) &&
         ((*(byte *)((int)gMaxZForTile + 0xb) & 3) != 0)) &&
        (bVar4 = *(byte *)((int)gMaxZForTile + 0xb) & 0xfc, bVar4 != 0)) &&
       (bVar4 < 0xb4)) {
      param_6->CurrentPlayer = local_4;
      FUN_00466b70(param_2,param_3,param_6);
      bVar3 = gta2::Player_sub_40CE70((struct Player *)&param_5,pPVar2);
      if (CONCAT31(extraout_var_02,bVar3) != 0) {
        return 1;
      }
    }
    iVar5 = DecoderFloat(&local_8);
    iVar6 = DecoderFloat(&param_3);
    iVar7 = DecoderFloat(&param_2);
    gMaxZForTile = (void *)gta2::MapRelatedStruct_sub_4653C0(param_1,iVar7,iVar6,iVar5);
    if ((gMaxZForTile != NULL) &&
       ((*(byte *)((int)gMaxZForTile + 0xb) & 3) != 0)) {
      bVar4 = *(byte *)((int)gMaxZForTile + 0xb) & 0xfc;
      if ((bVar4 == 0) || (0xb3 < bVar4)) {
        pSVar8 = gta2::S202_sub_401B20((Point2D *)&local_8,(struct SpriteS1 *)&param_3,
                            (struct S127 *)&DAT_00662c98);
        pPVar2->CurrentPlayer = (struct Player *)pSVar8->FirstElement;
      }
      else {
        pPVar2->CurrentPlayer = local_8;
        FUN_00466b70(uVar1,pSVar8,pPVar2);
        bVar3 = gta2::Player_CheckCondition((struct Player *)&param_4,(int *)pPVar2);
        if (CONCAT31(extraout_var_03,bVar3) == 0) {
          return 0;
        }
      }
      return 1;
    }
  }
  else {
    iVar5 = DecoderFloat(&local_8);
    iVar6 = DecoderFloat(&param_3);
    iVar7 = DecoderFloat(&param_2);
    gMaxZForTile = (void *)gta2::MapRelatedStruct_sub_4653C0(param_1,iVar7,iVar6,iVar5);
    pPVar2 = param_6;
    if (((gMaxZForTile != NULL) &&
        ((*(byte *)((int)gMaxZForTile + 0xb) & 3) != 0)) &&
       ((bVar4 = *(byte *)((int)gMaxZForTile + 0xb) & 0xfc, bVar4 != 0 &&
        (bVar4 < 0xb4)))) {
      param_6->CurrentPlayer = local_8;
      FUN_00466b70(param_2,param_3,param_6);
      bVar3 = gta2::Player_sub_40CE70((struct Player *)&param_5,pPVar2);
      if ((CONCAT31(extraout_var_00,bVar3) != 0) &&
         (bVar3 = gta2::Player_CheckCondition((struct Player *)&param_4,(int *)pPVar2),
         CONCAT31(extraout_var_01,bVar3) != 0)) {
        return CONCAT31(extraout_var_01,1);
      }
    }
  }
  return 0;
}


// 0x00469f90: MapRelatedStruct::sub_469F90
// IDA: MapRelatedStruct::sub_469F90
// Ghidra: FUN_00469f90
undefined4 gta2::MapRelatedStruct_sub_469F90(undefined4 param_1,uint param_2,SpriteS1 *param_3,SpriteS1 *param_4 ,SpriteS1 *param_5,int param_6,SpriteS1 *param_7,undefined4 param_8, SpriteS1 *param_9)
{
  undefined4 *self;
  struct SpriteS1 *this_00;
  bool bVar1;
  byte bVar2;
  char cVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int *piVar6;
  void *pvVar7;
  undefined2 *puVar8;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar9;
  undefined3 extraout_var_01;
  struct SpriteS1 *pSVar10;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  int iVar11;
  int iVar12;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  struct Player *this_01;
  struct SpriteS1 *pSVar13;
  GlassInfo local_30;
  
  this_00 = gObject->SpriteS1_;
  gta2::Player_sub_401B40((SpawnPoint *)&param_9,&local_30,(struct S127 *)&param_6);
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&param_9);
  puVar4 = (undefined4 *)
           gta2::Player_sub_401B40((SpawnPoint *)&param_8,(GlassInfo *)&local_30.pPed,
                      (struct S127 *)&param_5);
  puVar5 = (undefined4 *)
           gta2::Player_sub_401B40((SpawnPoint *)&param_7,(GlassInfo *)&local_30.SpawnPoint,
                      (struct S127 *)&param_4);
  String_ParseLine(&local_30.field19_0x28,puVar5,puVar4);
  FUN_004637b0(&PTR_005e6874);
  piVar6 = (int *)gta2::Player_sub_401B40((SpawnPoint *)&param_7,
                             (GlassInfo *)&local_30.SpawnPoint,(struct S127 *)&param_4)
  ;
  pvVar7 = gta2::Player_sub_401B40((SpawnPoint *)&param_8,(GlassInfo *)&local_30.pPed,
                      (struct S127 *)&param_5);
  puVar8 = gta2::Player_FUN_0040e8d0(this_01,(undefined2 *)&param_7,pvVar7,piVar6);
  param_9 = (struct SpriteS1 *)CONCAT22(param_9._2_2_,*puVar8);
  piVar6 = gta2::Player_sub_41E260((struct Player *)&local_30.field19_0x28,(int *)&param_7);
  pSVar10 = (struct SpriteS1 *)*piVar6;
  param_7 = pSVar10;
  gta2::SpriteS1_sub_420600((Sprite *)this_00,(int)param_4,(int)param_5,param_6);
  gta2::SpriteS1_SetRotation((Sprite *)this_00,(short)param_9);
  gta2::SpriteS1_sub_4BCB90((Sprite *)this_00,param_1,param_2,param_3);
  bVar1 = gta2::Car_IsTrainOrTrainCarriage((struct Car *)&param_7,(struct Car *)&DAT_00662cfc);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    param_5 = _DAT_00662cfc;
    pSVar13 = _DAT_00662cfc;
  }
  else {
    piVar6 = (int *)gta2::sub_401B90((struct Player *)&param_7,&param_5,(int *)&param_2);
    param_5 = (struct SpriteS1 *)*piVar6;
    piVar6 = (int *)gta2::sub_401B90((struct Player *)&param_7,&param_4,(int *)&param_5);
    pSVar13 = (struct SpriteS1 *)*piVar6;
    piVar6 = (int *)gta2::sub_401B90((struct Player *)&local_30,&param_4,(int *)&param_5);
    param_4 = (struct SpriteS1 *)*piVar6;
  }
  bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)&param_5,(struct SpriteS1 *)&DAT_00662c98);
  param_7 = pSVar13;
  if (CONCAT31(extraout_var_00,bVar1) != 0) {
    param_5 = _DAT_00662c98;
    param_4 = (struct SpriteS1 *)local_30.car;
    param_7 = pSVar10;
  }
  gta2::sub_41FC20((struct CarSystemManager *)&param_9,(struct CarSystemManager *)&param_9,
             (GlassInfo *)&param_7,(struct Ped *)&param_6,(struct Ped *)&param_8);
  param_2 = CONCAT31(param_2._1_3_,1);
  iVar9 = DecoderFloat(&param_5);
  if (0 < iVar9) {
    puVar4 = &this_00->Matrix3DArray[0].PositionY;
    puVar5 = &this_00->Matrix3DArray[0].PositionX;
    self = &this_00->Matrix3DArray[0].PositionZ;
    do {
      piVar6 = (int *)FUN_00469570(&param_1,*puVar5,*puVar4,*self);
      param_7 = (struct SpriteS1 *)*piVar6;
      bVar1 = gta2::Player_IsCurrentPlayer((struct Player *)&param_4,(struct Player *)&DAT_00662cfc);
      if (CONCAT31(extraout_var_01,bVar1) == 0) {
        bVar1 = gta2::Car_sub_403800((struct Car *)&param_4,(int *)&DAT_00662cfc);
        if (CONCAT31(extraout_var_02,bVar1) == 0) {
          param_9 = gta2::S202_sub_401B20((Point2D *)self,(struct SpriteS1 *)&local_30.count,
                               (struct S127 *)&param_4);
          param_3 = gta2::S202_sub_401B20((Point2D *)puVar4,
                               (struct SpriteS1 *)&local_30.field17_0x20,
                               (struct S127 *)&param_8);
          pSVar10 = gta2::S202_sub_401B20((Point2D *)puVar5,
                               (struct SpriteS1 *)&local_30.field18_0x24,
                               (struct S127 *)&param_6);
          gta2::SpriteS1_sub_420600((Sprite *)this_00,(int)pSVar10->FirstElement,
                              (int)param_3->FirstElement,
                              (int)param_9->FirstElement);
          iVar9 = DecoderFloat(self);
          iVar11 = DecoderFloat(puVar4);
          iVar12 = DecoderFloat(puVar5);
          bVar2 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct,iVar12,iVar11,iVar9);
          if (bVar2 == 0) {
            bVar1 = gta2::Car_sub_403800((struct Car *)&param_7,self);
            if (CONCAT31(extraout_var_06,bVar1) != 0) {
              gta2::SpriteS1_sub_420600((Sprite *)this_00,*puVar5,*puVar4,(int)param_7
                                 );
              return 0;
            }
          }
          else {
            iVar9 = DecoderFloat(self);
            iVar11 = DecoderFloat(puVar4);
            iVar12 = DecoderFloat(puVar5);
            bVar2 = gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct,iVar12,iVar11,iVar9);
            if (bVar2 != 0) {
              piVar6 = (int *)FUN_00469570(&local_30.field19_0x28,*puVar5,
                                           *puVar4,*self);
              param_7 = (struct SpriteS1 *)*piVar6;
              bVar1 = gta2::Car_sub_403800((struct Car *)&param_7,self);
              if (CONCAT31(extraout_var_05,bVar1) != 0) {
                return 0;
              }
            }
          }
        }
        else {
          param_7 = gta2::S202_sub_401B20((Point2D *)self,(struct SpriteS1 *)&local_30.field_0xc,
                               (struct S127 *)&param_4);
          param_9 = gta2::S202_sub_401B20((Point2D *)puVar4,
                               (struct SpriteS1 *)&local_30.field_0x10,(struct S127 *)&param_8
                              );
          pSVar10 = gta2::S202_sub_401B20((Point2D *)puVar5,
                               (struct SpriteS1 *)&local_30.field11_0x14,
                               (struct S127 *)&param_6);
          gta2::SpriteS1_sub_420600((Sprite *)this_00,(int)pSVar10->FirstElement,
                              (int)param_9->FirstElement,
                              (int)param_7->FirstElement);
          param_7 = (struct SpriteS1 *)*self;
          bVar1 = gta2::Car_sub_403800((struct Car *)&param_7,(int *)&DAT_00662c50);
          if (CONCAT31(extraout_var_03,bVar1) != 0) {
            return 0;
          }
          bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)self,(struct SpriteS1 *)&DAT_00662c50);
          if (CONCAT31(extraout_var_04,bVar1) == 0) {
LAB_0046a297:
            iVar9 = DecoderFloat(self);
            iVar11 = DecoderFloat(puVar4);
            iVar12 = DecoderFloat(puVar5);
            bVar2 = gta2::MapRelatedStruct_sub_466CF0(gMapRelatedStruct,iVar12,iVar11,iVar9);
            if (bVar2 == 0) {
              return 0;
            }
          }
          else {
            pSVar10 = gta2::S202_sub_401B20((Point2D *)self,
                                 (struct SpriteS1 *)&local_30.field12_0x18,
                                 (struct S127 *)&DAT_00663164);
            iVar9 = DecoderFloat(pSVar10);
            iVar11 = DecoderFloat(puVar4);
            iVar12 = DecoderFloat(puVar5);
            bVar2 = gta2::MapRelatedStruct_sub_420420(gMapRelatedStruct,iVar12,iVar11,iVar9);
            if (bVar2 != 0) goto LAB_0046a297;
          }
          gta2::SpriteS1_sub_420600((Sprite *)this_00,*puVar5,*puVar4,(int)param_7);
        }
      }
      else {
        param_7 = gta2::S202_sub_401B20((Point2D *)self,(struct SpriteS1 *)&local_30.SpawnPoint,
                             (struct S127 *)&param_4);
        param_9 = gta2::S202_sub_401B20((Point2D *)puVar4,(struct SpriteS1 *)&local_30.pPed,
                             (struct S127 *)&param_8);
        pSVar10 = gta2::S202_sub_401B20((Point2D *)puVar5,(struct SpriteS1 *)&local_30,
                             (struct S127 *)&param_6);
        gta2::SpriteS1_sub_420600((Sprite *)this_00,(int)pSVar10->FirstElement,
                            (int)param_9->FirstElement,
                            (int)param_7->FirstElement);
      }
      cVar3 = gta2::SpriteS1_sub_4BD670(this_00);
      if (cVar3 != '\0') {
        return 0;
      }
      param_2 = CONCAT31(param_2._1_3_,(char)param_2 + '\x01');
      iVar9 = DecoderFloat(&param_5);
    } while ((int)(param_2 & 0xff) <= iVar9);
  }
  return 1;
}


// 0x0046a420: MapRelatedStruct::FindMaxZForLocation
// IDA: MapRelatedStruct::FindMaxZForLocation
// Ghidra: ---
int * gta2::MapRelatedStruct_FindMaxZForLocation(struct MapRelatedStruct *self, int *arg0, int *a2, S202 *pS202)
{
  int v5; // eax
  _WORD *MaxZForTile; // eax
  char v8; // al
  int *v9; // eax
  int *v10; // eax
  int v11; // [esp-8h] [ebp-10h]
  int a4; // [esp+4h] [ebp-4h] BYREF

  v11 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&pS202);
  v5 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&a2);
  MaxZForTile = gta2::MapRelatedStruct_FindMaxZForTile(self, v5, v11, &a4);
  dword_662B90 = MaxZForTile;
  if ( MaxZForTile )
  {
    v8 = *((_BYTE *)MaxZForTile + 11);
    if ( (v8 & 0xFC) != 0 && (v8 & 0xFCu) < 0xB4 && (v8 & 3) != 0 )
    {
      gta2::S202_sub_41F980((struct S202 *)&a4, a4);
      a4 = *v9;
      gta2::MapRelatedStruct_sub_466B70(self, a2, pS202);
      *arg0 = a4;
      return arg0;
    }
    else
    {
      gta2::S202_sub_41F980((struct S202 *)&pS202, a4 + 1);
      *arg0 = *v10;
      return arg0;
    }
  }
  else
  {
    gta2::bitShiftLeft1(arg0, 0);
    return arg0;
  }
}


// 0x0046a4d0: MapRelatedStruct::sub_46A4D0
// IDA: MapRelatedStruct::sub_46A4D0
// Ghidra: ---
int gta2::MapRelatedStruct_sub_46A4D0(struct MapRelatedStruct *self)
{
  int result; // eax
  FILE *Buffer_MOBJ; // esi
  int *FirstElement; // edi
  struct SpriteS1 *v5; // ebx
  int *MaxZForLocation; // eax
  unsigned int v7; // ecx
  char v8[2]; // [esp+Ah] [ebp-16h] BYREF
  unsigned int v9; // [esp+Ch] [ebp-14h]
  int a5; // [esp+10h] [ebp-10h]
  char v11[4]; // [esp+14h] [ebp-Ch] BYREF
  char v12[4]; // [esp+18h] [ebp-8h] BYREF
  char v13[4]; // [esp+1Ch] [ebp-4h] BYREF

  v9 = 0;
  result = self->field_344;
  Buffer_MOBJ = self->Buffer_MOBJ;
  if ( result )
  {
    do
    {
      FirstElement = (int *)sub_462ED0((struct SpriteS1 *)v11, (__int16 *)Buffer_MOBJ)->FirstElement;
      v5 = sub_462ED0((struct SpriteS1 *)v12, (__int16 *)&Buffer_MOBJ->_Placeholder + 1)->FirstElement;
      LOWORD(a5) = *(_WORD *)&sub_462EF0((struct Ped *)v8, (struct SpriteS1 *)v8)->S200_[0].A;
      MaxZForLocation = gta2::MapRelatedStruct_FindMaxZForLocation(self, (int *)v13, FirstElement, (struct S202 *)v5);
      gta2::Object_SpawnObject(gObject, BYTE1(Buffer_MOBJ[1]._Placeholder), (int)FirstElement, (int)v5, *MaxZForLocation, a5);
      v7 = self->field_344;
      result = v9 + 1;
      Buffer_MOBJ = (FILE *)((char *)Buffer_MOBJ + 6);
      ++v9;
    }
    while ( v9 < v7 );
  }
  return result;
}


// 0x0046a570: MapRelatedStruct::sub_46A570
// IDA: MapRelatedStruct::sub_46A570
// Ghidra: FUN_0046a570
undefined4 gta2::MapRelatedStruct_sub_46A570(void *self,int param_1,int param_2,int param_3,int param_4, int param_5,int param_6,int param_7)
{
  int iVar1;
  char cVar2;
  byte bVar3;
  bool bVar4;
  byte puVar10;
  undefined4 uVar5;
  struct SpriteS1 *pSVar6;
  struct SpriteS1 *pSVar7;
  int iVar8;
  uint uVar9;
  undefined2 *puVar11;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  uint uVar12;
  undefined3 extraout_var_08;
  undefined3 extraout_var_09;
  undefined3 extraout_var_10;
  undefined3 extraout_var_11;
  undefined3 extraout_var_12;
  undefined3 extraout_var_13;
  undefined3 extraout_var_14;
  undefined3 extraout_var_15;
  undefined3 extraout_var_16;
  undefined3 extraout_var_17;
  undefined3 extraout_var_18;
  undefined3 extraout_var_19;
  undefined3 extraout_var_20;
  undefined3 extraout_var_21;
  undefined3 extraout_var_22;
  undefined3 extraout_var_23;
  undefined3 extraout_var_24;
  undefined3 extraout_var_25;
  undefined3 extraout_var_26;
  struct SpriteS1 *extraout_ECX;
  struct SpriteS1 *extraout_ECX_00;
  struct SpriteS1 *extraout_ECX_01;
  struct SpriteS1 *extraout_ECX_02;
  struct SpriteS1 *extraout_ECX_03;
  struct SpriteS1 *extraout_ECX_04;
  struct SpriteS1 *extraout_ECX_05;
  undefined2 uVar14;
  struct SpriteS1 *extraout_ECX_06;
  struct SpriteS1 *extraout_ECX_07;
  struct SpriteS1 *extraout_ECX_08;
  struct SpriteS1 *extraout_ECX_09;
  struct SpriteS1 *extraout_ECX_10;
  struct SpriteS1 *extraout_ECX_11;
  struct SpriteS1 *extraout_ECX_12;
  struct SpriteS1 *extraout_ECX_13;
  struct SpriteS1 *extraout_ECX_14;
  struct SpriteS1 *extraout_ECX_15;
  struct SpriteS1 *extraout_ECX_16;
  struct SpriteS1 *extraout_ECX_17;
  struct SpriteS1 *extraout_ECX_18;
  struct SpriteS1 *extraout_ECX_19;
  struct SpriteS1 *extraout_ECX_20;
  struct SpriteS1 *extraout_ECX_21;
  struct SpriteS1 *extraout_ECX_22;
  struct SpriteS1 *extraout_ECX_23;
  undefined2 extraout_var_27;
  struct SpriteS1 *extraout_ECX_24;
  struct SpriteS1 *extraout_ECX_25;
  struct SpriteS1 *extraout_ECX_26;
  struct SpriteS1 *extraout_ECX_27;
  struct SpriteS1 *extraout_ECX_28;
  struct SpriteS1 *extraout_ECX_29;
  struct SpriteS1 *extraout_ECX_30;
  struct SpriteS1 *extraout_ECX_31;
  struct SpriteS1 *extraout_ECX_32;
  undefined2 extraout_var_28;
  struct SpriteS1 *extraout_ECX_33;
  struct SpriteS1 *extraout_ECX_34;
  struct SpriteS1 *extraout_ECX_35;
  struct SpriteS1 *extraout_ECX_36;
  struct SpriteS1 *extraout_ECX_37;
  struct SpriteS1 *extraout_ECX_38;
  struct SpriteS1 *extraout_ECX_39;
  struct SpriteS1 *extraout_ECX_40;
  struct SpriteS1 *extraout_ECX_41;
  undefined2 extraout_var_29;
  struct SpriteS1 *extraout_ECX_42;
  struct SpriteS1 *extraout_ECX_43;
  struct SpriteS1 *extraout_ECX_44;
  struct SpriteS1 *extraout_ECX_45;
  struct SpriteS1 *extraout_ECX_46;
  struct SpriteS1 *extraout_ECX_47;
  undefined2 extraout_var_30;
  struct SpriteS1 *extraout_ECX_48;
  struct SpriteS1 *extraout_ECX_49;
  struct SpriteS1 *extraout_ECX_50;
  struct SpriteS1 *extraout_ECX_51;
  struct SpriteS1 *extraout_ECX_52;
  struct SpriteS1 *extraout_ECX_53;
  struct SpriteS1 *extraout_ECX_54;
  struct SpriteS1 *extraout_ECX_55;
  struct SpriteS1 *extraout_ECX_56;
  undefined2 extraout_var_31;
  struct SpriteS1 *extraout_ECX_57;
  struct SpriteS1 *extraout_ECX_58;
  struct SpriteS1 *extraout_ECX_59;
  struct SpriteS1 *extraout_ECX_60;
  struct SpriteS1 *extraout_ECX_61;
  ushort *puVar15;
  ushort *puVar16;
  struct SpriteS1 *pSVar17;
  ushort *puVar13;
  undefined3 extraout_var;
  
  _DAT_00662bf4 = (struct SpriteS1 *)param_7;
  _DAT_00662bd8 = (struct SpriteS1 *)param_7;
  _DAT_00662bd0 = (struct SpriteS1 *)param_7;
  _DAT_00662bbc = (struct SpriteS1 *)param_7;
  puVar15 = _DAT_00662bf0;
  if ((_DAT_00662bf0 != NULL) &&
     (uVar5 = gta2::FUN_00469b00(self,*(undefined4 *)(_DAT_00662bf0 + 10),
                           *(undefined4 *)(_DAT_00662bf0 + 0xc)),
     puVar15 = _DAT_00662bf0, (char)uVar5 == '\0')) {
    pSVar6 = (struct SpriteS1 *)DecoderFloat(_DAT_00662bf0 + 0xe);
    pSVar7 = (struct SpriteS1 *)DecoderFloat(puVar15 + 0xc);
    iVar8 = DecoderFloat(puVar15 + 10);
    bVar3 = gta2::MapRelatedStruct_sub_466CF0((struct MapRelatedStruct *)self,iVar8,(int)pSVar7,(int)pSVar6);
    if (bVar3 == 0) {
      uVar5 = FUN_00466430(param_1,param_2);
      return uVar5;
    }
  }
  gMaxZForTile = FUN_00465410(self,param_5,param_6,param_7);
  if ((undefined *)gMaxZForTile == NULL) {
    gMaxZForTile = &gS16_02;
  }
  uVar9 = (uint)(*(byte *)((int)gMaxZForTile + 0xb) >> 2);
  cVar2 = (&DAT_00662db0)[uVar9 * 0xc];
  iVar8 = uVar9 * 0xc;
  _DAT_00662be0 = &DAT_00662db0 + iVar8;
  if ((cVar2 == '\0') || ((&DAT_00662db2)[iVar8] != '\0')) {
    param_7._0_1_ = '\0';
  }
  else {
    switch(cVar2) {
    case '\x01':
      _DAT_00662bf4 = (struct SpriteS1 *)((int)&_DAT_00662bf4->FirstElement + 1);
      break;
    case '\x02':
      _DAT_00662bd8 = (struct SpriteS1 *)((int)&_DAT_00662bd8->FirstElement + 1);
      break;
    case '\x03':
      _DAT_00662bbc = (struct SpriteS1 *)((int)&_DAT_00662bbc->FirstElement + 1);
      break;
    case '\x04':
      _DAT_00662bd0 = (struct SpriteS1 *)((int)&_DAT_00662bd0->FirstElement + 1);
    }
    _DAT_00662be8 =
         (undefined2 *)
         gta2::MapRelatedStruct_sub_4653C0((struct MapRelatedStruct *)self,param_5,param_6,param_7 + 1);
    param_7._0_1_ = cVar2;
  }
  uVar9 = _DAT_00662bec;
  if (param_3 < param_6) {
    if ((char)param_7 == '\x01') {
      if ((_DAT_00662be8 != NULL) &&
         ((_DAT_00662be8[2] & (ushort)_DAT_00662bec) != 0)) {
        puVar11 = _DAT_00662be8;
        if (puVar15 == NULL) {
LAB_0046a71a:
          return CONCAT31((int3)((uint)puVar11 >> 8),1);
        }
        pSVar17 = (struct SpriteS1 *)param_6;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_6);
        pSVar7 = extraout_ECX;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_5 + 1);
        pSVar6 = extraout_ECX_00;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_5);
        bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar6,pSVar7,pSVar17);
        puVar11 = (undefined2 *)CONCAT31(extraout_var,bVar3);
        puVar15 = _DAT_00662bf0;
        if (bVar3 != 0) goto LAB_0046a71a;
      }
    }
    else {
      pSVar6 = (struct SpriteS1 *)
               (CONCAT22((short)((uint)param_6 >> 0x10),
                         *(undefined2 *)((int)gMaxZForTile + 4)) & _DAT_00662bec
               );
      if ((short)pSVar6 != 0) {
        cVar2 = *_DAT_00662be0;
        puVar13 = (ushort *)CONCAT31((int3)((uint)gMaxZForTile >> 8),cVar2);
        if ((cVar2 != '\x03') && (cVar2 != '\x04')) {
          if (puVar15 == NULL) goto LAB_0046af57;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_6);
          pSVar17 = extraout_ECX_01;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_5 + 1);
          pSVar7 = extraout_ECX_02;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_5);
          bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar7,pSVar17,pSVar6);
          puVar13 = (ushort *)CONCAT31(extraout_var_00,bVar3);
          puVar15 = _DAT_00662bf0;
          if (bVar3 != 0) goto LAB_0046af57;
        }
      }
    }
    uVar9 = _DAT_00662bec;
    _DAT_00662b84 =
         (ushort *)FUN_00465410(self,param_5,param_6 + -1,(int)_DAT_00662bf4);
    if (_DAT_00662b84 != NULL) {
      if ((_DAT_00662b84[3] & (ushort)uVar9) != 0) {
        puVar13 = _DAT_00662b84;
        if (puVar15 == NULL) goto LAB_0046af57;
        pSVar17 = extraout_ECX_03;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_6);
        pSVar7 = extraout_ECX_04;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_5 + 1);
        pSVar6 = extraout_ECX_05;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_5);
        bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar6,pSVar7,pSVar17);
        puVar13 = (ushort *)CONCAT31(extraout_var_01,bVar3);
        puVar15 = _DAT_00662bf0;
        uVar9 = _DAT_00662bec;
        if (bVar3 != 0) goto LAB_0046af57;
      }
      _DAT_00662ba4 =
           (struct SpriteS1 *)
           (&DAT_00662db0 +
           (uint)(*(byte *)((int)_DAT_00662b84 + 0xb) >> 2) * 0xc);
    }
  }
  pSVar6 = (struct SpriteS1 *)param_4;
  if (param_6 < param_4) {
    uVar14 = (undefined2)((uint)param_4 >> 0x10);
    if ((char)param_7 == '\x02') {
      if ((_DAT_00662be8 != NULL) &&
         (pSVar6 = (struct SpriteS1 *)(CONCAT22(uVar14,_DAT_00662be8[3]) & uVar9),
         (short)pSVar6 != 0)) {
        puVar11 = _DAT_00662be8;
        if (puVar15 == NULL) {
LAB_0046a881:
          return CONCAT31((int3)((uint)puVar11 >> 8),1);
        }
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_6 + 1);
        pSVar17 = extraout_ECX_06;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_5 + 1);
        pSVar7 = extraout_ECX_07;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_5);
        bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar7,pSVar17,pSVar6);
        puVar11 = (undefined2 *)CONCAT31(extraout_var_02,bVar3);
        puVar15 = _DAT_00662bf0;
        uVar9 = _DAT_00662bec;
        if (bVar3 != 0) goto LAB_0046a881;
      }
    }
    else {
      pSVar6 = (struct SpriteS1 *)
               (CONCAT22(uVar14,*(undefined2 *)((int)gMaxZForTile + 6)) & uVar9)
      ;
      if ((short)pSVar6 != 0) {
        cVar2 = *_DAT_00662be0;
        puVar13 = (ushort *)CONCAT31((int3)((uint)gMaxZForTile >> 8),cVar2);
        if ((cVar2 != '\x03') && (cVar2 != '\x04')) {
          if (puVar15 == NULL) goto LAB_0046af57;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_6 + 1);
          pSVar17 = extraout_ECX_08;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_5 + 1);
          pSVar7 = extraout_ECX_09;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_5);
          bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar7,pSVar17,pSVar6);
          puVar13 = (ushort *)CONCAT31(extraout_var_03,bVar3);
          puVar15 = _DAT_00662bf0;
          uVar9 = _DAT_00662bec;
          if (bVar3 != 0) goto LAB_0046af57;
        }
      }
    }
    _DAT_00662b8c =
         (ushort *)FUN_00465410(self,param_5,param_6 + 1,(int)_DAT_00662bd8);
    pSVar6 = extraout_ECX_10;
    if (_DAT_00662b8c != NULL) {
      if ((_DAT_00662b8c[2] & (ushort)uVar9) != 0) {
        puVar13 = _DAT_00662b8c;
        if (puVar15 == NULL) goto LAB_0046af57;
        pSVar17 = extraout_ECX_10;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_6 + 1);
        pSVar7 = extraout_ECX_11;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_5 + 1);
        pSVar6 = extraout_ECX_12;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_5);
        bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar6,pSVar7,pSVar17);
        puVar13 = (ushort *)CONCAT31(extraout_var_04,bVar3);
        puVar15 = _DAT_00662bf0;
        uVar9 = _DAT_00662bec;
        if (bVar3 != 0) goto LAB_0046af57;
      }
      pSVar6 = NULL;
      _DAT_00662ba0 =
           &DAT_00662db0 +
           (uint)(*(byte *)((int)_DAT_00662b8c + 0xb) >> 2) * 0xc;
    }
  }
  if (param_1 < param_5) {
    if ((char)param_7 == '\x03') {
      if ((_DAT_00662be8 != NULL) &&
         (pSVar6 = (struct SpriteS1 *)
                   (CONCAT22((short)((uint)pSVar6 >> 0x10),*_DAT_00662be8) &
                   uVar9), (short)pSVar6 != 0)) {
        puVar11 = _DAT_00662be8;
        if (puVar15 == NULL) {
LAB_0046a9e4:
          return CONCAT31((int3)((uint)puVar11 >> 8),1);
        }
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_5);
        pSVar17 = extraout_ECX_13;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_6 + 1);
        pSVar7 = extraout_ECX_14;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_6);
        bVar4 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar7,(int)pSVar17,(int)pSVar6)
        ;
        puVar11 = (undefined2 *)CONCAT31(extraout_var_05,bVar4);
        puVar15 = _DAT_00662bf0;
        uVar9 = _DAT_00662bec;
        if (bVar4) goto LAB_0046a9e4;
      }
    }
    else {
                              // WARNING: Load size is inaccurate
      if ((*gMaxZForTile & (ushort)uVar9) != 0) {
        cVar2 = *_DAT_00662be0;
        puVar13 = (ushort *)CONCAT31((int3)((uint)_DAT_00662be0 >> 8),cVar2);
        if ((cVar2 != '\x01') && (cVar2 != '\x02')) {
          if (puVar15 == NULL) goto LAB_0046af57;
          pSVar17 = (struct SpriteS1 *)gMaxZForTile;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_5);
          pSVar7 = extraout_ECX_15;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_6 + 1);
          pSVar6 = extraout_ECX_16;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_6);
          bVar4 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar6,(int)pSVar7,
                               (int)pSVar17);
          puVar13 = (ushort *)CONCAT31(extraout_var_06,bVar4);
          puVar15 = _DAT_00662bf0;
          uVar9 = _DAT_00662bec;
          if (bVar4) goto LAB_0046af57;
        }
      }
    }
    _DAT_00662b88 =
         (ushort *)FUN_00465410(self,param_5 + -1,param_6,(int)_DAT_00662bbc);
    if (_DAT_00662b88 != NULL) {
      if ((_DAT_00662b88[1] & (ushort)uVar9) != 0) {
        puVar13 = _DAT_00662b88;
        if (puVar15 == NULL) goto LAB_0046af57;
        pSVar17 = extraout_ECX_17;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_5);
        pSVar7 = extraout_ECX_18;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_6 + 1);
        pSVar6 = extraout_ECX_19;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_6);
        bVar4 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar6,(int)pSVar7,(int)pSVar17)
        ;
        puVar13 = (ushort *)CONCAT31(extraout_var_07,bVar4);
        puVar15 = _DAT_00662bf0;
        uVar9 = _DAT_00662bec;
        if (bVar4) goto LAB_0046af57;
      }
      _DAT_00662bcc =
           (struct SpriteS1 *)
           (&DAT_00662db0 +
           (uint)(*(byte *)((int)_DAT_00662b88 + 0xb) >> 2) * 0xc);
    }
    puVar16 = _DAT_00662b88;
    if (param_3 < param_6) {
      if (((_DAT_00662b84 != NULL) && ((int)_DAT_00662bbc <= (int)_DAT_00662bf4)
          ) && (uVar12 = CONCAT22((short)((uint)_DAT_00662b84 >> 0x10),
                                  *_DAT_00662b84) & uVar9, (short)uVar12 != 0))
      {
        cVar2 = *(char *)&_DAT_00662ba4->FirstElement;
        if ((cVar2 != '\x01') && (cVar2 != '\x02')) {
          puVar13 = (ushort *)CONCAT31((int3)(uVar12 >> 8),cVar2);
          if (puVar15 == NULL) goto LAB_0046af57;
          pSVar17 = _DAT_00662ba4;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_5);
          pSVar7 = extraout_ECX_20;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_6);
          pSVar6 = extraout_ECX_21;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_6 + -1);
          bVar4 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar6,(int)pSVar7,
                               (int)pSVar17);
          puVar13 = (ushort *)CONCAT31(extraout_var_08,bVar4);
          puVar15 = _DAT_00662bf0;
          uVar9 = _DAT_00662bec;
          if (bVar4) goto LAB_0046af57;
        }
      }
      if (_DAT_00662b88 == NULL) {
LAB_0046ac02:
        pSVar6 = _DAT_00662bf4;
        if ((int)_DAT_00662bf4 <= (int)_DAT_00662bbc) {
          pSVar6 = _DAT_00662bbc;
        }
      }
      else {
        pSVar6 = _DAT_00662bf4;
        if ((int)_DAT_00662bf4 <= (int)_DAT_00662bbc) {
          uVar12 = CONCAT22((short)((uint)_DAT_00662bf4 >> 0x10),
                            _DAT_00662b88[2]) & uVar9;
          if ((short)uVar12 != 0) {
            cVar2 = *(char *)&_DAT_00662bcc->FirstElement;
            if ((cVar2 != '\x03') && (cVar2 != '\x04')) {
              puVar13 = (ushort *)CONCAT31((int3)(uVar12 >> 8),cVar2);
              if (puVar15 == NULL) goto LAB_0046af57;
              pSVar17 = _DAT_00662bcc;
              gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_6);
              pSVar7 = extraout_ECX_22;
              gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_5);
              pSVar6 = extraout_ECX_23;
              gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_5 + -1);
              bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar6,pSVar7,pSVar17);
              puVar13 = (ushort *)CONCAT31(extraout_var_09,bVar3);
              puVar15 = _DAT_00662bf0;
              uVar9 = _DAT_00662bec;
              if (bVar3 != 0) goto LAB_0046af57;
            }
          }
          goto LAB_0046ac02;
        }
      }
      puVar16 = _DAT_00662b88;
      _DAT_00662c00 =
           (ushort *)FUN_00465410(self,param_5 + -1,param_6 + -1,(int)pSVar6);
      if (_DAT_00662c00 != NULL) {
        pSVar6 = (struct SpriteS1 *)
                 (CONCAT22(extraout_var_27,_DAT_00662c00[1]) & uVar9);
        if ((short)pSVar6 != 0) {
          puVar13 = _DAT_00662c00;
          if (puVar15 == NULL) goto LAB_0046af57;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_5);
          pSVar17 = extraout_ECX_24;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_6);
          pSVar7 = extraout_ECX_25;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_6 + -1);
          bVar4 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar7,(int)pSVar17,
                               (int)pSVar6);
          puVar13 = (ushort *)CONCAT31(extraout_var_10,bVar4);
          pSVar6 = extraout_ECX_26;
          puVar15 = _DAT_00662bf0;
          uVar9 = _DAT_00662bec;
          puVar16 = _DAT_00662b88;
          if (bVar4) goto LAB_0046af57;
        }
        if ((_DAT_00662c00 != NULL) &&
           (pSVar6 = (struct SpriteS1 *)
                     (CONCAT22((short)((uint)pSVar6 >> 0x10),_DAT_00662c00[3]) &
                     uVar9), (short)pSVar6 != 0)) {
          puVar13 = _DAT_00662c00;
          if (puVar15 == NULL) goto LAB_0046af57;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_6);
          pSVar17 = extraout_ECX_27;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_5);
          pSVar7 = extraout_ECX_28;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_5 + -1);
          bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar7,pSVar17,pSVar6);
          puVar13 = (ushort *)CONCAT31(extraout_var_11,bVar3);
          puVar15 = _DAT_00662bf0;
          uVar9 = _DAT_00662bec;
          puVar16 = _DAT_00662b88;
          if (bVar3 != 0) goto LAB_0046af57;
        }
      }
    }
    if (param_6 < param_4) {
      if (((_DAT_00662b8c != NULL) && ((int)_DAT_00662bbc <= (int)_DAT_00662bd8)
          ) && ((*_DAT_00662b8c & (ushort)uVar9) != 0)) {
        cVar2 = *_DAT_00662ba0;
        puVar13 = (ushort *)CONCAT31((int3)((uint)_DAT_00662ba0 >> 8),cVar2);
        if ((cVar2 != '\x01') && (cVar2 != '\x02')) {
          if (puVar15 == NULL) goto LAB_0046af57;
          pSVar17 = _DAT_00662bbc;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_5);
          pSVar7 = extraout_ECX_29;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_6 + 2);
          pSVar6 = extraout_ECX_30;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_6 + 1);
          bVar4 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar6,(int)pSVar7,
                               (int)pSVar17);
          puVar13 = (ushort *)CONCAT31(extraout_var_12,bVar4);
          puVar15 = _DAT_00662bf0;
          uVar9 = _DAT_00662bec;
          puVar16 = _DAT_00662b88;
          if (bVar4) goto LAB_0046af57;
        }
      }
      if (puVar16 == NULL) {
LAB_0046ae0a:
        pSVar6 = _DAT_00662bd8;
        if ((int)_DAT_00662bd8 <= (int)_DAT_00662bbc) {
          pSVar6 = _DAT_00662bbc;
        }
      }
      else {
        pSVar6 = _DAT_00662bd8;
        if ((int)_DAT_00662bd8 <= (int)_DAT_00662bbc) {
          pSVar6 = (struct SpriteS1 *)
                   (CONCAT22((short)((uint)_DAT_00662bbc >> 0x10),puVar16[3]) &
                   uVar9);
          if ((short)pSVar6 != 0) {
            cVar2 = *(char *)&_DAT_00662bcc->FirstElement;
            puVar13 = (ushort *)CONCAT31((int3)((uint)_DAT_00662bd8 >> 8),cVar2)
            ;
            if ((cVar2 != '\x03') && (cVar2 != '\x04')) {
              if (puVar15 == NULL) goto LAB_0046af57;
              gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_6 + 1);
              pSVar17 = extraout_ECX_31;
              gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_5);
              pSVar7 = extraout_ECX_32;
              gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_5 + -1);
              bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar7,pSVar17,pSVar6);
              puVar13 = (ushort *)CONCAT31(extraout_var_13,bVar3);
              puVar15 = _DAT_00662bf0;
              uVar9 = _DAT_00662bec;
              if (bVar3 != 0) goto LAB_0046af57;
            }
          }
          goto LAB_0046ae0a;
        }
      }
      iVar8 = param_6 + 1;
      puVar13 = (ushort *)FUN_00465410(self,param_5 + -1,iVar8,(int)pSVar6);
      _DAT_00662ba8 = puVar13;
      if (puVar13 != NULL) {
        pSVar6 = (struct SpriteS1 *)(CONCAT22(extraout_var_28,puVar13[1]) & uVar9);
        if ((short)pSVar6 != 0) {
          if (puVar15 == NULL) goto LAB_0046af57;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_5);
          pSVar17 = extraout_ECX_33;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_6 + 2);
          pSVar7 = extraout_ECX_34;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,iVar8);
          bVar4 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar7,(int)pSVar17,
                               (int)pSVar6);
          puVar13 = (ushort *)CONCAT31(extraout_var_14,bVar4);
          pSVar6 = extraout_ECX_35;
          puVar15 = _DAT_00662bf0;
          uVar9 = _DAT_00662bec;
          if (bVar4) goto LAB_0046af57;
        }
        if ((_DAT_00662ba8 != NULL) &&
           (pSVar6 = (struct SpriteS1 *)
                     (CONCAT22((short)((uint)pSVar6 >> 0x10),_DAT_00662ba8[2]) &
                     uVar9), (short)pSVar6 != 0)) {
          puVar13 = _DAT_00662ba8;
          if (puVar15 == NULL) goto LAB_0046af57;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,iVar8);
          pSVar17 = extraout_ECX_36;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_5);
          pSVar7 = extraout_ECX_37;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_5 + -1);
          bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar7,pSVar17,pSVar6);
          puVar13 = (ushort *)CONCAT31(extraout_var_15,bVar3);
          puVar15 = _DAT_00662bf0;
          uVar9 = _DAT_00662bec;
          if (bVar3 != 0) goto LAB_0046af57;
        }
      }
    }
  }
  puVar13 = (ushort *)param_2;
  if (param_2 <= param_5) goto LAB_0046b421;
  if ((char)param_7 == '\x04') {
    if ((_DAT_00662be8 != NULL) &&
       (puVar13 = (ushort *)
                  (CONCAT22((short)((uint)_DAT_00662be8 >> 0x10),
                            _DAT_00662be8[1]) & uVar9), (short)puVar13 != 0)) {
      if (puVar15 == NULL) goto LAB_0046af57;
      pSVar17 = (struct SpriteS1 *)param_5;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_5 + 1);
      pSVar7 = extraout_ECX_38;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_6 + 1);
      pSVar6 = extraout_ECX_39;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_6);
      bVar4 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar6,(int)pSVar7,(int)pSVar17);
      puVar13 = (ushort *)CONCAT31(extraout_var_16,bVar4);
      uVar9 = _DAT_00662bec;
      if (bVar4) goto LAB_0046af57;
    }
  }
  else {
    uVar12 = CONCAT22((short)((uint)param_2 >> 0x10),
                      *(undefined2 *)((int)gMaxZForTile + 2)) & uVar9;
    if ((short)uVar12 != 0) {
      cVar2 = *_DAT_00662be0;
      puVar13 = (ushort *)CONCAT31((int3)(uVar12 >> 8),cVar2);
      if ((cVar2 != '\x01') && (cVar2 != '\x02')) {
        if (puVar15 == NULL) goto LAB_0046af57;
        pSVar17 = (struct SpriteS1 *)param_5;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_5 + 1);
        pSVar7 = extraout_ECX_40;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_6 + 1);
        pSVar6 = extraout_ECX_41;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_6);
        bVar4 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar6,(int)pSVar7,(int)pSVar17)
        ;
        puVar13 = (ushort *)CONCAT31(extraout_var_17,bVar4);
        uVar9 = _DAT_00662bec;
        if (bVar4) goto LAB_0046af57;
      }
    }
  }
  iVar8 = param_5 + 1;
  _DAT_00662c04 =
       (undefined2 *)FUN_00465410(self,iVar8,param_6,(int)_DAT_00662bd0);
  if (_DAT_00662c04 != NULL) {
    pSVar6 = (struct SpriteS1 *)(CONCAT22(extraout_var_29,*_DAT_00662c04) & uVar9);
    if ((short)pSVar6 != 0) {
      puVar13 = _DAT_00662bf0;
      if (_DAT_00662bf0 == NULL) goto LAB_0046af57;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,iVar8);
      pSVar17 = extraout_ECX_42;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_6 + 1);
      pSVar7 = extraout_ECX_43;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_6);
      bVar4 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar7,(int)pSVar17,(int)pSVar6);
      puVar13 = (ushort *)CONCAT31(extraout_var_18,bVar4);
      uVar9 = _DAT_00662bec;
      if (bVar4) goto LAB_0046af57;
    }
    _DAT_00662bdc =
         &DAT_00662db0 + (uint)(*(byte *)((int)_DAT_00662c04 + 0xb) >> 2) * 0xc;
  }
  puVar11 = _DAT_00662c04;
  if (param_3 < param_6) {
    if ((((_DAT_00662b84 != NULL) && ((int)_DAT_00662bd0 <= (int)_DAT_00662bf4))
        && ((_DAT_00662b84[1] & (ushort)uVar9) != 0)) &&
       ((*(char *)&_DAT_00662ba4->FirstElement != '\x01' &&
        (*(char *)&_DAT_00662ba4->FirstElement != '\x02')))) {
      puVar13 = _DAT_00662bf0;
      if (_DAT_00662bf0 == NULL) goto LAB_0046af57;
      pSVar17 = _DAT_00662ba4;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,iVar8);
      pSVar7 = extraout_ECX_44;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_6);
      pSVar6 = extraout_ECX_45;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_6 + -1);
      bVar4 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar6,(int)pSVar7,(int)pSVar17);
      puVar13 = (ushort *)CONCAT31(extraout_var_19,bVar4);
      uVar9 = _DAT_00662bec;
      if (bVar4) goto LAB_0046af57;
    }
    if (_DAT_00662c04 == NULL) {
LAB_0046b15b:
      pSVar6 = _DAT_00662bf4;
      if ((int)_DAT_00662bf4 <= (int)_DAT_00662bd0) {
        pSVar6 = _DAT_00662bd0;
      }
    }
    else {
      pSVar6 = _DAT_00662bf4;
      if ((int)_DAT_00662bf4 <= (int)_DAT_00662bd0) {
        if ((((_DAT_00662c04[2] & (ushort)uVar9) != 0) &&
            (*_DAT_00662bdc != '\x03')) && (*_DAT_00662bdc != '\x04')) {
          puVar13 = _DAT_00662bf0;
          if (_DAT_00662bf0 == NULL) goto LAB_0046af57;
          pSVar17 = _DAT_00662bd0;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_6);
          pSVar7 = extraout_ECX_46;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_5 + 2);
          pSVar6 = extraout_ECX_47;
          gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,iVar8);
          bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar6,pSVar7,pSVar17);
          puVar13 = (ushort *)CONCAT31(extraout_var_20,bVar3);
          uVar9 = _DAT_00662bec;
          if (bVar3 != 0) goto LAB_0046af57;
        }
        goto LAB_0046b15b;
      }
    }
    puVar11 = _DAT_00662c04;
    _DAT_00662be4 =
         (undefined2 *)FUN_00465410(self,iVar8,param_6 + -1,(int)pSVar6);
    if (_DAT_00662be4 != NULL) {
      pSVar6 = (struct SpriteS1 *)(CONCAT22(extraout_var_30,*_DAT_00662be4) & uVar9);
      if ((short)pSVar6 != 0) {
        puVar13 = _DAT_00662bf0;
        if (_DAT_00662bf0 == NULL) goto LAB_0046af57;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,iVar8);
        pSVar17 = extraout_ECX_48;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_6);
        pSVar7 = extraout_ECX_49;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_6 + -1);
        bVar4 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar7,(int)pSVar17,(int)pSVar6)
        ;
        puVar13 = (ushort *)CONCAT31(extraout_var_21,bVar4);
        pSVar6 = extraout_ECX_50;
        uVar9 = _DAT_00662bec;
        puVar11 = _DAT_00662c04;
        if (bVar4) goto LAB_0046af57;
      }
      if ((_DAT_00662be4 != NULL) && ((_DAT_00662be4[3] & (ushort)uVar9) != 0))
      {
        puVar13 = _DAT_00662bf0;
        if (_DAT_00662bf0 == NULL) goto LAB_0046af57;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_6);
        pSVar17 = extraout_ECX_51;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_5 + 2);
        pSVar7 = extraout_ECX_52;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,iVar8);
        bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar7,pSVar17,pSVar6);
        puVar13 = (ushort *)CONCAT31(extraout_var_22,bVar3);
        uVar9 = _DAT_00662bec;
        puVar11 = _DAT_00662c04;
        if (bVar3 != 0) goto LAB_0046af57;
      }
    }
  }
  puVar13 = (ushort *)param_4;
  if (param_4 <= param_6) goto LAB_0046b421;
  if ((((_DAT_00662b8c != NULL) && ((int)_DAT_00662bd0 <= (int)_DAT_00662bd8))
      && ((_DAT_00662b8c[1] & (ushort)uVar9) != 0)) &&
     ((*_DAT_00662ba0 != '\x01' && (*_DAT_00662ba0 != '\x02')))) {
    puVar13 = _DAT_00662bf0;
    if (_DAT_00662bf0 == NULL) goto LAB_0046af57;
    pSVar17 = _DAT_00662bd0;
    gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,iVar8);
    pSVar7 = extraout_ECX_53;
    gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_6 + 2);
    pSVar6 = extraout_ECX_54;
    gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,param_6 + 1);
    bVar4 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar6,(int)pSVar7,(int)pSVar17);
    puVar13 = (ushort *)CONCAT31(extraout_var_23,bVar4);
    uVar9 = _DAT_00662bec;
    puVar11 = _DAT_00662c04;
    if (bVar4) goto LAB_0046af57;
  }
  if (puVar11 == NULL) {
LAB_0046b34c:
    pSVar6 = _DAT_00662bd8;
    if ((int)_DAT_00662bd8 <= (int)_DAT_00662bd0) {
      pSVar6 = _DAT_00662bd0;
    }
  }
  else {
    pSVar6 = _DAT_00662bd8;
    if ((int)_DAT_00662bd8 <= (int)_DAT_00662bd0) {
      pSVar6 = (struct SpriteS1 *)
               (CONCAT22((short)((uint)_DAT_00662bd0 >> 0x10),puVar11[3]) &
               uVar9);
      if ((((short)pSVar6 != 0) && (*_DAT_00662bdc != '\x03')) &&
         (*_DAT_00662bdc != '\x04')) {
        puVar13 = _DAT_00662bf0;
        if (_DAT_00662bf0 == NULL) goto LAB_0046af57;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,param_6 + 1);
        pSVar17 = extraout_ECX_55;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_5 + 2);
        pSVar7 = extraout_ECX_56;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,iVar8);
        bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar7,pSVar17,pSVar6);
        puVar13 = (ushort *)CONCAT31(extraout_var_24,bVar3);
        uVar9 = _DAT_00662bec;
        if (bVar3 != 0) goto LAB_0046af57;
      }
      goto LAB_0046b34c;
    }
  }
  iVar1 = param_6 + 1;
  _DAT_00662bb0 = (ushort *)FUN_00465410(self,iVar8,iVar1,(int)pSVar6);
  puVar13 = _DAT_00662bb0;
  if (_DAT_00662bb0 != NULL) {
    pSVar6 = (struct SpriteS1 *)(CONCAT22(extraout_var_31,*_DAT_00662bb0) & uVar9);
    if ((short)pSVar6 != 0) {
      puVar13 = _DAT_00662bf0;
      if (_DAT_00662bf0 == NULL) goto LAB_0046af57;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,iVar8);
      pSVar17 = extraout_ECX_57;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_6 + 2);
      pSVar7 = extraout_ECX_58;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,iVar1);
      bVar4 = gta2::FUN_004bb910(_DAT_00662bf0,(int)pSVar7,(int)pSVar17,(int)pSVar6);
      puVar13 = (ushort *)CONCAT31(extraout_var_25,bVar4);
      pSVar6 = extraout_ECX_59;
      uVar9 = _DAT_00662bec;
      if (bVar4) goto LAB_0046af57;
    }
    puVar13 = _DAT_00662bb0;
    if ((_DAT_00662bb0 != NULL) && ((_DAT_00662bb0[2] & (ushort)uVar9) != 0)) {
      puVar13 = _DAT_00662bf0;
      if (_DAT_00662bf0 != NULL) {
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe8,iVar1);
        pSVar17 = extraout_ECX_60;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe4,param_5 + 2);
        pSVar7 = extraout_ECX_61;
        gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffe0,iVar8);
        bVar3 = gta2::FUN_004bb860(_DAT_00662bf0,pSVar7,pSVar17,pSVar6);
        puVar13 = (ushort *)CONCAT31(extraout_var_26,bVar3);
        if (bVar3 == 0) goto LAB_0046b421;
      }
LAB_0046af57:
      return CONCAT31((int3)((uint)puVar13 >> 8),1);
    }
  }
LAB_0046b421:
  return (uint)puVar13 & 0xffffff00;
}


// 0x0046b440: MapRelatedStruct::sub_46B440
// IDA: MapRelatedStruct::sub_46B440
// Ghidra: FUN_0046b440
undefined4 gta2::MapRelatedStruct_sub_46B440(void *param_1,int param_2,int param_3,int param_4, undefined4 param_5,undefined2 param_6)
{
  int iVar1;
  undefined4 uVar2;
  
  _DAT_00662bf0 = param_5;
  _DAT_00662bec = param_6;
  if (((_DAT_00662bf8 - _DAT_00662bd4 < 3) && (param_2 <= _DAT_00662bd4 + 1)) &&
     (_DAT_00662bf8 + -1 <= param_2)) {
    if (((2 < _DAT_00662bfc - _DAT_00662bac) || (_DAT_00662bac + 1 < param_3))
       || (iVar1 = _DAT_00662bf8, param_3 < _DAT_00662bfc + -1)) {
      uVar2 = FUN_0046a570(param_1,_DAT_00662bd4,_DAT_00662bf8,param_3 + -1,
                           param_3 + 1,param_2,param_3,param_4);
      if ((char)uVar2 != '\0') {
        return 1;
      }
      if (_DAT_00662bfc == param_3 + 2) {
        uVar2 = FUN_0046a570(param_1,_DAT_00662bd4,_DAT_00662bf8,
                             _DAT_00662bfc + -1,_DAT_00662bfc,param_2,
                             _DAT_00662bfc + -1,_DAT_00662bd8);
        return uVar2;
      }
      uVar2 = FUN_0046a570(param_1,_DAT_00662bd4,_DAT_00662bf8,_DAT_00662bac,
                           _DAT_00662bac + 1,param_2,_DAT_00662bac + 1,
                           _DAT_00662bf4);
      return uVar2;
    }
  }
  else {
    uVar2 = FUN_0046a570(param_1,param_2 + -1,param_2 + 1,_DAT_00662bac,
                         _DAT_00662bfc,param_2,param_3,param_4);
    if ((char)uVar2 != '\0') {
      return 1;
    }
    if (_DAT_00662bf8 == param_2 + 2) {
      uVar2 = FUN_0046a570(param_1,_DAT_00662bf8 + -1,_DAT_00662bf8,
                           _DAT_00662bac,_DAT_00662bfc,_DAT_00662bf8 + -1,
                           param_3,_DAT_00662bd0);
      return uVar2;
    }
    param_2 = _DAT_00662bd4 + 1;
    iVar1 = param_2;
    param_4 = _DAT_00662bbc;
  }
  uVar2 = FUN_0046a570(param_1,_DAT_00662bd4,iVar1,_DAT_00662bac,_DAT_00662bfc,
                       param_2,param_3,param_4);
  return uVar2;
}


// 0x0048a350: MapRelatedStruct::sub_48A350
// IDA: MapRelatedStruct::sub_48A350
// Ghidra: FUN_0048a350
bool gta2::MapRelatedStruct_sub_48A350(MapRelatedStruct *param_1,uint param_2,uint param_3,byte param_4)
{
  int iVar1;
  
  iVar1 = gta2::MapRelatedStruct_sub_42A850(param_1,param_2,param_3,param_4);
  if (iVar1 != 0) {
    return (*(byte *)(iVar1 + 0xb) & 3) != 0;
  }
  return false;
}


// 0x00492130: MapRelatedStruct::sub_492130
// IDA: MapRelatedStruct::sub_492130
// Ghidra: FUN_00492130
void gta2::MapRelatedStruct_sub_492130(int param_1)
{
  *(undefined1 *)(param_1 + 0x36e) = 0;
  return;
}


// 0x00492140: MapRelatedStruct::sub_492140
// IDA: MapRelatedStruct::sub_492140
// Ghidra: FUN_00492140
undefined4 gta2::MapRelatedStruct_sub_492140(MapRelatedStruct *param_1,int param_2,int param_3,int param_4)
{
  int iVar1;
  
  iVar1 = gta2::MapRelatedStruct_sub_4653C0(param_1,param_2,param_3,param_4);
  if ((iVar1 != 0) && (*(char *)(iVar1 + 10) != '\0')) {
    return 1;
  }
  return 0;
}


// 0x0049ebe0: MapRelatedStruct::sub_49EBE0
// IDA: MapRelatedStruct::sub_49EBE0
// Ghidra: FUN_0049ebe0
undefined1 gta2::MapRelatedStruct_sub_49EBE0(MapRelatedStruct *param_1,int param_2,int param_3,int param_4, undefined1 *param_5,undefined1 *param_6)
{
  char cVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = gta2::MapRelatedStruct_sub_4653C0(param_1,param_2,param_3,param_4);
  if (iVar2 != 0) {
    cVar1 = FUN_0049e540(*(ushort *)(iVar2 + 8) & 0x3ff);
    if (cVar1 != '\0') {
      return 7;
    }
    if ((*(byte *)(iVar2 + 0xb) & 3) != 0) {
      cVar1 = FUN_0049e570(*(ushort *)(iVar2 + 8) & 0x3ff);
      if (cVar1 != '\0') {
        return 9;
      }
      uVar3 = (uint)(*(byte *)(iVar2 + 0xb) >> 2);
      iVar2 = uVar3 * 0xc;
      *param_5 = (&DAT_00662db1)[uVar3 * 0xc];
      *param_6 = (&DAT_00662db2)[iVar2];
      return (&DAT_00662db0)[iVar2];
    }
  }
  return 5;
}


// 0x004b9f40: MapRelatedStruct::sub_4B9F40
// IDA: MapRelatedStruct::sub_4B9F40
// Ghidra: FUN_004b9f40
undefined4 gta2::MapRelatedStruct_sub_4B9F40(MapRelatedStruct *param_1,int param_2,int param_3,int param_4)
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = gta2::MapRelatedStruct_sub_4653C0(param_1,param_2,param_3,param_4);
  if (iVar1 != 0) {
    uVar2 = FUN_0049e540(*(ushort *)(iVar1 + 8) & 0x3ff);
    return uVar2;
  }
  return 0;
}



