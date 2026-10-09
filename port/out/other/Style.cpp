#include "gta2_shim.h"

// Module: other, Class: Style
// Functions: 55
// Source: unified (IDA+Ghidra)

// 0x00491f80: Style::sub_491F80
// IDA: Style::sub_491F80
// Ghidra: FUN_00491f80
byte gta2::Style_sub_491F80(void *self,uint param_1)
{
  return *(int *)((int)self + (param_1 & 0xffff) * 4 + 0x6c) == 5;
}


// 0x0049e540: Style::sub_49E540
// IDA: Style::sub_49E540
// Ghidra: FUN_0049e540
undefined4 gta2::Style_sub_49E540(int param_1,uint param_2)
{
  char cVar1;
  
  if (*(int *)(param_1 + 0x6c + (param_2 & 0xffff) * 4) == 4) {
    cVar1 = FUN_004bf690(param_2);
    if (cVar1 != '\0') {
      return 1;
    }
  }
  return 0;
}


// 0x0049e570: Style::sub_49E570
// IDA: Style::sub_49E570
// Ghidra: FUN_0049e570
undefined4 gta2::Style_sub_49E570(int param_1,uint param_2)
{
  char cVar1;
  
  if (*(int *)(param_1 + 0x6c + (param_2 & 0xffff) * 4) == 4) {
    cVar1 = FUN_004bf690(param_2);
    if (cVar1 == '\0') {
      return 1;
    }
  }
  return 0;
}


// 0x004b9f20: Style::sub_4B9F20
// IDA: Style::sub_4B9F20
// Ghidra: ---
int gta2::Style_sub_4B9F20(Style *self, void *a2)
{
  int v2; // eax

  LOWORD(v2) = self->field_4;
  return v2 - 1;
}


// 0x004bf1f0: Style::GetCarModelById
// IDA: Style::GetCarModelById
// Ghidra: ---
int gta2::Style_GetCarModelById(Style *self, unsigned __int8 CarType)
{
  return self->pCar_5C->Car[CarType];
}


// 0x004bf210: Style::sub_4BF210
// IDA: Style::sub_4BF210
// Ghidra: ---
int gta2::Style_sub_4BF210(Style *self, unsigned __int8 a2)
{
  int v2; // eax

  v2 = self->pCar_5C->Car[a2];
  return *(unsigned __int8 *)(v2 + 4) + v2 + 14;
}


// 0x004bf230: Style::sub_4BF230
// IDA: Style::sub_4BF230
// Ghidra: FUN_004bf230
uint gta2::Style_sub_4BF230(int param_1,ushort param_2,byte param_3)
{
  uint uVar1;
  int iVar2;
  
  if (((param_2 < **(ushort **)(param_1 + 0x54)) &&
      (iVar2 = *(int *)(*(ushort **)(param_1 + 0x54) + (uint)param_2 * 2 + 2),
      iVar2 != 0)) && (param_3 < *(byte *)(iVar2 + 2))) {
    uVar1 = iVar2 + 4 + (uint)param_3 * 8;
    return uVar1 & -(uint)(*(short *)(uVar1 + 4) != 0);
  }
  return 0;
}


// 0x004bf280: Style::GetSprite
// IDA: Style::GetSprite
// Ghidra: ---
int gta2::Style_GetSprite(Style *self, unsigned __int16 a2)
{
  return self->field_20 + 8 * a2;
}


// 0x004bf2a0: Style::GetGlobalSpriteId
// IDA: Style::GetGlobalSpriteId
// Ghidra: ---
unsigned __int16 gta2::Style_GetGlobalSpriteId(Style *self, int sprite_type, __int16 spriteId)
{
  unsigned __int16 result; // ax

  switch ( sprite_type )
  {
    case 2:
      result = spriteId + self->field_14->field_0;
      break;
    case 3:
      result = spriteId + self->field_14->field_2;
      break;
    case 4:
    case 8:
      result = spriteId + self->field_14->field_4;
      break;
    case 5:
      result = spriteId + self->field_14->field_6;
      break;
    case 6:
      result = spriteId + self->field_14->field_8;
      break;
    case 7:
      result = spriteId + self->field_14->field_A;
      break;
    default:
      result = spriteId;
      break;
  }
  return result;
}


// 0x004bf330: Style::sub_4BF330
// IDA: Style::sub_4BF330
// Ghidra: ---
__int16 gta2::Style_sub_4BF330(Style *self, int a2)
{
  __int16 result; // ax

  switch ( a2 )
  {
    case 2:
      result = *(_WORD *)self->field_18;
      break;
    case 3:
      result = *(_WORD *)(self->field_18 + 2);
      break;
    case 4:
    case 8:
      result = *(_WORD *)(self->field_18 + 4);
      break;
    case 5:
      result = *(_WORD *)(self->field_18 + 6);
      break;
    case 6:
      result = *(_WORD *)(self->field_18 + 8);
      break;
    case 7:
      result = *(_WORD *)(self->field_18 + 10);
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


// 0x004bf3a0: Style::sub_4BF3A0
// IDA: Style::sub_4BF3A0
// Ghidra: ---
__int16 gta2::Style_sub_4BF3A0(Style *self, int a2)
{
  __int16 result; // ax

  switch ( a2 )
  {
    case 1:
      result = self->S15_0002_->field_0;
      break;
    case 2:
      result = self->S15_0002_->field_2;
      break;
    case 3:
      result = self->S15_0002_->field_4;
      break;
    case 4:
      result = self->S15_0002_->field_6;
      break;
    case 5:
      result = self->S15_0002_->field_8;
      break;
    case 6:
      result = self->S15_0002_->field_A;
      break;
    case 7:
      result = self->S15_0002_->field_C;
      break;
    case 8:
      result = self->S15_0002_->field_E;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


// 0x004bf430: Style::get_global_palette_id
// IDA: Style::get_global_palette_id
// Ghidra: ---
__int16 gta2::Style_get_global_palette_id(Style *self, int palette_type, __int16 palette_id)
{
  __int16 result; // ax

  switch ( palette_type )
  {
    case 1:
      result = palette_id + *(_WORD *)self->field_C;
      break;
    case 2:
      result = palette_id + *(_WORD *)(self->field_C + 2);
      break;
    case 3:
      result = palette_id + *(_WORD *)(self->field_C + 4);
      break;
    case 4:
      result = palette_id + *(_WORD *)(self->field_C + 6);
      break;
    case 5:
      result = palette_id + *(_WORD *)(self->field_C + 8);
      break;
    case 6:
      result = palette_id + *(_WORD *)(self->field_C + 10);
      break;
    case 7:
      result = palette_id + *(_WORD *)(self->field_C + 12);
      break;
    case 8:
      result = palette_id + *(_WORD *)(self->field_C + 14);
      break;
    default:
      result = palette_id;
      break;
  }
  return result;
}


// 0x004bf4e0: Style::GetColourBank
// IDA: Style::GetColourBank
// Ghidra: ---
int gta2::Style_GetColourBank(Style *self, __int16 a2)
{
  return self->field_2C + 4 * ((a2 & 0x3F) + ((a2 & 0xFFC0) << 8));
}


// 0x004bf530: Style::get_physical_palette
// IDA: Style::get_physical_palette
// Ghidra: ---
__int16 gta2::Style_get_physical_palette(Style *self, unsigned __int16 a2)
{
  return *((_WORD *)&self->field_28->_Placeholder + a2);
}


// 0x004bf550: Style::GetSpriteID
// IDA: Style::GetSpriteID
// Ghidra: ---
__int16 gta2::Style_GetSpriteID(Style *self, unsigned __int16 a2, __int16 a3)
{
  return a3 + *((_WORD *)&self->Car->Car + a2 + 1);
}


// 0x004bf570: Style::sub_4BF570
// IDA: Style::sub_4BF570
// Ghidra: ---
ushort gta2::Style_sub_4BF570(Style *self, wchar_t *style, unsigned __int16 *a3)
{
  if ( *style == word_67065C[0] )
    return 16;
  if ( *style == word_670650 )
    return 32;
  return *(unsigned __int8 *)(self->field_20
                            + 8
                            * (*a3
                             + (unsigned __int16)self->field_14->field_A
                             + *((unsigned __int16 *)&self->Car->Car + *style + 1))
                            - 260);
}


// 0x004bf5d0: Style::sub_4BF5D0
// IDA: Style::sub_4BF5D0
// Ghidra: ---
__int16 gta2::Style_sub_4BF5D0(Style *self, _WORD *a2)
{
  if ( *a2 == word_67065C[0] )
    return 16;
  if ( *a2 == word_670650 )
    return 32;
  return *(unsigned __int8 *)(self->field_20
                            + 8
                            * ((unsigned __int16)self->field_14->field_A
                             + *((unsigned __int16 *)&self->Car->Car + (unsigned __int16)*a2 + 1))
                            + 620);
}


// 0x004bf630: Style::sub_4BF630
// IDA: Style::sub_4BF630
// Ghidra: ---
__int16 gta2::Style_sub_4BF630(Style *self, _WORD *style)
{
  if ( *style == word_67065C[0] )
    return 17;
  if ( *style == word_670650 )
    return 34;
  return *(unsigned __int8 *)(self->field_20
                            + 8
                            * ((unsigned __int16)self->field_14->field_A
                             + *((unsigned __int16 *)&self->Car->Car + (unsigned __int16)*style + 1))
                            + 261);
}


// 0x004bf690: Style::sub_4BF690
// IDA: Style::sub_4BF690
// Ghidra: FUN_004bf690
bool gta2::Style_sub_4BF690(int param_1,ushort param_2)
{
  return *(ushort *)(*(int *)(param_1 + 0x40) + (uint)param_2 * 2) != param_2;
}


// 0x004bf6b0: Style::get_tile_by_id
// IDA: Style::get_tile_by_id
// Ghidra: FUN_004bf6b0
undefined2 gta2::Style_get_tile_by_id(int param_1,uint param_2)
{
  return *(undefined2 *)(*(int *)(param_1 + 0x40) + (param_2 & 0xffff) * 2);
}


// 0x004bf6d0: Style::sub_4BF6D0
// IDA: Style::sub_4BF6D0
// Ghidra: FUN_004bf6d0
uint gta2::Style_sub_4BF6D0(int param_1)
{
  uint uVar1;
  short *psVar2;
  
  uVar1 = 0x3ff;
  psVar2 = (short *)(*(int *)(param_1 + 0x40) + 0x7fe);
  do {
    if (*psVar2 == 0) {
      return uVar1;
    }
    uVar1 = uVar1 + 0xffff;
    psVar2 = psVar2 + -1;
  } while (0x3df < (ushort)uVar1);
  return uVar1 & 0xffff0000;
}


// 0x004bf740: Style::GetPalitrePal
// IDA: Style::GetPalitrePal
// Ghidra: ---
unsigned __int16 gta2::Style_GetPalitrePal(Style *self)
{
  return self->PalitrePal;
}


// 0x004bf750: Style::get_obji_by_idx
// IDA: Style::get_obji_by_idx
// Ghidra: ---
int gta2::Style_get_obji_by_idx(Style *self, unsigned __int16 a2)
{
  if ( a2 < self->field_6 )
    return self->field_24 + 2 * a2;
  else
    return 0;
}


// 0x004bf770: Style::ChangeTileByIdx
// IDA: Style::ChangeTileByIdx
// Ghidra: ---
void gta2::Style_ChangeTileByIdx(Style *self, unsigned __int16 a2, __int16 a3)
{
  *((_WORD *)&self->S1501_->field + a2) = a3;
}


// 0x004bf7f0: Style::sub_4BF7F0
// IDA: Style::sub_4BF7F0
// Ghidra: ---
int gta2::Style_sub_4BF7F0(Style *self)
{
  int v2; // eax
  int v3; // ecx
  int result; // eax
  int v5; // ecx

  self->S1501_ = (S1501 *)gta2::operator_new(2048u);
  v2 = 0;
  v3 = 0;
  do
  {
    v3 += 2;
    *(_WORD *)((char *)self->S1501_ + v3 - 2) = v2++;
  }
  while ( (unsigned __int16)v2 < 992u );
  result = 1984;
  v5 = 32;
  do
  {
    result += 2;
    --v5;
    *(_WORD *)((char *)self->S1501_ + result - 2) = 0;
  }
  while ( v5 );
  return result;
}


// 0x004bf840: Style::sub_4BF840
// IDA: Style::sub_4BF840
// Ghidra: ---
char * gta2::Style_sub_4BF840(Style *self, unsigned int a2)
{
  unsigned int v3; // ebp
  int v4; // ebx
  int i; // edx
  int v6; // eax
  int v7; // ecx
  char *result; // eax
  int v9; // ecx
  char *j; // ebp
  unsigned int v11; // edi
  _WORD *v12; // eax
  __int16 *v13; // esi
  __int16 v14; // dx
  int v15; // esi
  unsigned int v16; // [esp+10h] [ebp-4h]

  v3 = 0;
  v4 = 0;
  for ( i = self->field_4C; v3 < a2; i += v7 )
  {
    v6 = *(unsigned __int8 *)(i + 2);
    v7 = 2 * v6 + 4;
    self->delx3 += 8 * v6 + 4;
    v3 += v7;
  }
  result = (char *)gta2::createBuffer(self->delx3);
  v9 = self->field_4C;
  self->field_50 = (int)result;
  v16 = 0;
  for ( j = result; v16 < a2; v16 += v15 )
  {
    v11 = 0;
    *(_WORD *)j = *(_WORD *)v9;
    j[2] = *(_BYTE *)(v9 + 2);
    j[3] = 0;
    if ( *(_BYTE *)(v9 + 2) )
    {
      v12 = j + 8;
      v13 = (__int16 *)(v9 + 4);
      do
      {
        v14 = *v13;
        *((_DWORD *)v12 - 1) = v4;
        *v12 = v14;
        ++v13;
        v4 += (unsigned __int16)*v12;
        ++v11;
        v12 += 4;
      }
      while ( v11 < *(unsigned __int8 *)(v9 + 2) );
    }
    j += 8 * (unsigned __int8)j[2] + 4;
    v15 = 2 * *(unsigned __int8 *)(v9 + 2) + 4;
    result = (char *)(v15 + v16);
    v9 += v15;
  }
  return result;
}


// 0x004bf900: Style::sub_4BF900
// IDA: Style::sub_4BF900
// Ghidra: ---
int gta2::Style_sub_4BF900(Style *self)
{
  unsigned int v1; // ebp
  int result; // eax
  int v3; // edx
  unsigned int v4; // esi
  _DWORD *v5; // eax

  v1 = 0;
  result = self->delx3;
  v3 = self->field_50;
  if ( result )
  {
    do
    {
      v4 = 0;
      if ( *(_BYTE *)(v3 + 2) )
      {
        v5 = (_DWORD *)(v3 + 4);
        do
        {
          *v5 += self->field_48;
          ++v4;
          v5 += 2;
        }
        while ( v4 < *(unsigned __int8 *)(v3 + 2) );
      }
      result = 8 * *(unsigned __int8 *)(v3 + 2) + 4;
      v3 += result;
      v1 += result;
    }
    while ( v1 < self->delx3 );
  }
  return result;
}


// 0x004bf980: Style::sub_4BF980
// IDA: Style::sub_4BF980
// Ghidra: ---
int gta2::Style_sub_4BF980(Style *self)
{
  unsigned int v2; // ebx
  unsigned int v3; // edx
  int delx3; // eax
  int v5; // ecx
  unsigned __int16 v6; // bp
  unsigned int v7; // edi
  int v8; // eax
  _WORD *Buffer; // eax
  unsigned int i; // eax
  int result; // eax
  unsigned __int16 *v12; // edi

  v2 = 0;
  v3 = 0;
  delx3 = self->delx3;
  v5 = self->field_50;
  v6 = 0;
  if ( delx3 )
  {
    v7 = delx3;
    do
    {
      if ( *(_WORD *)v5 >= v6 )
        v6 = *(_WORD *)v5;
      v8 = 8 * *(unsigned __int8 *)(v5 + 2) + 4;
      v3 += v8;
      v5 += v8;
    }
    while ( v3 < v7 );
  }
  Buffer = gta2::createBuffer(4 * v6 + 8);
  self->field_54 = (int)Buffer;
  *Buffer = v6 + 1;
  for ( i = 0; i < *(unsigned __int16 *)self->field_54; *(_DWORD *)(self->field_54 + 4 * i) = 0 )
    ++i;
  result = self->delx3;
  v12 = (unsigned __int16 *)self->field_50;
  if ( result )
  {
    do
    {
      if ( *(_DWORD *)(self->field_54 + 4 * *v12 + 4) )
        gta2::debug_log(0x3EAu, "style.cpp", 1000);
      *(_DWORD *)(self->field_54 + 4 * *v12 + 4) = v12;
      if ( *v12 >= v6 )
        v6 = *v12;
      result = 8 * *((unsigned __int8 *)v12 + 2) + 4;
      v12 = (unsigned __int16 *)((char *)v12 + result);
      v2 += result;
    }
    while ( v2 < self->delx3 );
  }
  return result;
}


// 0x004bfa60: Style::read_delx_records_REAL
// IDA: Style::read_delx_records_REAL
// Ghidra: ---
void gta2::Style_read_delx_records_REAL(Style *self, FileMgr *dwBytes)
{
  FILE *Buffer; // eax

  Buffer = (FILE *)gta2::createBuffer((SIZE_T)dwBytes);
  self->field_4C = (int)Buffer;
  gta2::FileMgr_Read(Buffer, (SIZE_T *)&dwBytes);
  gta2::Style_sub_4BF840(self, (unsigned int)dwBytes);
  gta2::Style_sub_4BF980(self);
  gta2::free_0((void *)self->field_4C);
  self->field_4C = 0;
}


// 0x004bfab0: Style::read_dels_records_REAL
// IDA: Style::read_dels_records_REAL
// Ghidra: ---
int gta2::Style_read_dels_records_REAL(Style *self, FileMgr *dwBytes)
{
  FILE *Buffer; // eax

  Buffer = (FILE *)gta2::createBuffer((SIZE_T)dwBytes);
  self->field_48 = (int)Buffer;
  return gta2::FileMgr_Read(Buffer, (SIZE_T *)&dwBytes);
}


// 0x004bfad0: Style::read_tile_chunk_REAL
// IDA: Style::read_tile_chunk_REAL
// Ghidra: ---
int gta2::Style_read_tile_chunk_REAL(Style *self, SIZE_T a2)
{
  FILE *v3; // eax

  v3 = (FILE *)gta2::sub_4059F0(a2, (int)&self->field_44);
  self->Tiles = (int)v3;
  gta2::FileMgr_Read(v3, &a2);
  return gta2::Style_sub_4BF7F0(self);
}


// 0x004bfb00: Style::read_ovly_records_REAL_
// IDA: Style::read_ovly_records_REAL_
// Ghidra: ---
int gta2::Style_read_ovly_records_REAL_(Style *self, LONG size)
{
  return gta2::FileMgr_SeekPosition((FileMgr *)self, (int)&size);
}


// 0x004bfb10: Style::read_psxt_records_REAL
// IDA: Style::read_psxt_records_REAL
// Ghidra: ---
int gta2::Style_read_psxt_records_REAL(Style *self, LONG size)
{
  return gta2::FileMgr_SeekPosition((FileMgr *)self, (int)&size);
}


// 0x004bfb20: Style::read_sprg_records_REAL
// IDA: Style::read_sprg_records_REAL
// Ghidra: ---
int gta2::Style_read_sprg_records_REAL(Style *self, int a2)
{
  FILE *v3; // eax

  v3 = (FILE *)gta2::sub_4059F0(a2, (int)&self->field_38);
  self->field_34 = (int)v3;
  return gta2::FileMgr_Read(v3, (SIZE_T *)&a2);
}


// 0x004bfb50: Style::read_ppal_records_REAL
// IDA: Style::read_ppal_records_REAL
// Ghidra: ---
unsigned int gta2::Style_read_ppal_records_REAL(Style *self, unsigned int a2)
{
  FILE *v3; // eax
  unsigned int result; // eax

  v3 = (FILE *)gta2::sub_4059F0(a2, (int)&self->field_30);
  self->field_2C = (int)v3;
  gta2::FileMgr_Read(v3, &a2);
  result = a2 >> 10;
  self->PalitrePal = a2 >> 10;
  return result;
}


// 0x004bfb80: Style::read_palx_records_REAL
// IDA: Style::read_palx_records_REAL
// Ghidra: ---
int gta2::Style_read_palx_records_REAL(Style *self, int a2)
{
  FILE *v3; // eax
  int v5; // [esp-10h] [ebp-14h]

  if ( v5 != 0x8000 )
    gta2::debug_log(0x409u, "style.cpp", 1161);
  v3 = (FILE *)gta2::operator_new(0x8000u);
  self->field_28 = v3;
  if ( !v3 )
    gta2::debug_log(0x20u, "style.cpp", 1163);
  return gta2::FileMgr_Read(self->field_28, (SIZE_T *)&a2);
}


// 0x004bfbe0: Style::read_obji_records_REAL
// IDA: Style::read_obji_records_REAL
// Ghidra: Style::FUN_004bfbe0
void gta2::Style_read_obji_records_REAL(Style *self,size_t size,int param_2,undefined4 param_3, uint pSize)
{
  void *size_00;
  
  size_00 = CreateBuffer(size);
  self->Size = size_00;
  gta2::FileMgr_Read((FileMgr *)&size,(size_t)size_00);
  if (0xffff < size >> 1) {
    gta2::DebugLog(0x3fc,"style.cpp",0x49d);
    size = pSize;
  }
  self->field3_0x6 = (ushort)(size >> 1);
  if ((size >> 1 & 0xffff) * 2 != size) {
    param_2 = 0x49f;
    size = (size_t)s_style_cpp_00575454;
    gta2::DebugLog(0x29,"style.cpp",0x49f);
  }
  return;
}


// 0x004bfc60: Style::read_sprx_records_REAL
// IDA: Style::read_sprx_records_REAL
// Ghidra: Style::FUN_004bfc60
void gta2::Style_read_sprx_records_REAL(Style *self,size_t siZe,undefined4 param_2, undefined4 param_3,uint param_4)
{
  void *size;
  
  size = CreateBuffer(siZe + 8);
  self->SPRX = (int)size;
  gta2::FileMgr_Read((FileMgr *)&siZe,(size_t)size);
  if (0xffff < siZe >> 3) {
    gta2::DebugLog(0x3ed,"style.cpp",0x4b2);
    siZe = param_4;
  }
  self->field2_0x4 = (short)(siZe >> 3) + 1;
  return;
}


// 0x004bfdd0: Style::read_fonb_chunk_REAL
// IDA: Style::read_fonb_chunk_REAL
// Ghidra: Style::FUN_004bfdd0
void gta2::Style_read_fonb_chunk_REAL(Style *self,size_t size,undefined4 param_2, undefined4 param_3,size_t pSize)
{
  short sVar1;
  struct Car *pCVar2;
  void *extraout_ECX;
  void *this_00;
  undefined4 unaff_retaddr;
  
  if (size < 2) {
    gta2::DebugLog(0x409,"style.cpp",0x4f8);
    size = pSize;
  }
  pCVar2 = (Car *)CreateBuffer(size);
  self->ColorCar = pCVar2;
  gta2::FileMgr_Read((FileMgr *)&pSize,(size_t)pCVar2);
  this_00 = (void *)((uint)*(ushort *)&self->ColorCar->Turret * 2 + 2);
  if ((void *)pSize != this_00) {
    gta2::DebugLog(0x409,"style.cpp",0x4fb);
    this_00 = extraout_ECX;
  }
  pCVar2 = self->ColorCar;
  sVar1 = gta2::FUN_004bf790(this_00,unaff_retaddr);
  self->field1_0x2 = sVar1;
  gta2::SpriteSx_BuildCumulativeTable((void *)((int)&pCVar2->Turret + 2));
  gta2::sub_4BFCC0(self,*(short *)&self->ColorCar->Turret);
  return;
}


// 0x004bfe70: Style::read_sprb_records_REAL
// IDA: Style::read_sprb_records_REAL
// Ghidra: ---
int gta2::Style_read_sprb_records_REAL(Style *self, int a2)
{
  _DWORD *v3; // eax
  S15_001 *v4; // eax
  int v6; // [esp-1Ch] [ebp-20h]
  int v7; // [esp+0h] [ebp-4h]

  if ( v6 != 12 )
    gta2::debug_log(0x409u, "style.cpp", 1293);
  v3 = gta2::operator_new(0xCu);
  self->field_18 = (int)v3;
  if ( !v3 )
    gta2::debug_log(0x20u, "style.cpp", 1295);
  v4 = (S15_001 *)gta2::operator_new(0xCu);
  self->field_14 = v4;
  if ( !v4 )
    gta2::debug_log(0x20u, "style.cpp", 1297);
  gta2::FileMgr_Read((FILE *)self->field_18, (SIZE_T *)&a2);
  *self->field_14 = *(S15_001 *)self->field_18;
  return gta2::sub_4BF7B0(self->field_14, v7);
}


// 0x004bff20: Style::read_palb_chunk_REAL
// IDA: Style::read_palb_chunk_REAL
// Ghidra: ---
void gta2::Style_read_palb_chunk_REAL(Style *self, int chunk_size)
{
  struct S15_0002 *v3; // eax
  _DWORD *v4; // eax
  struct S15_0002 *S15_0002; // edx
  _DWORD *v6; // eax
  void *v7; // esi
  int v8; // [esp-18h] [ebp-20h]
  int v9; // [esp+0h] [ebp-8h]

  if ( v8 != 16 )
    gta2::debug_log(0x409u, "style.cpp", 1315);
  v3 = (S15_0002 *)gta2::operator_new(0x10u);
  self->S15_0002_ = v3;
  if ( !v3 )
    gta2::debug_log(0x20u, "style.cpp", 1317);
  v4 = gta2::operator_new(0x10u);
  self->field_C = (int)v4;
  if ( !v4 )
    gta2::debug_log(0x20u, "style.cpp", 1319);
  gta2::FileMgr_Read((FILE *)self->S15_0002_, (SIZE_T *)&chunk_size);
  S15_0002 = self->S15_0002_;
  v6 = (_DWORD *)self->field_C;
  *v6 = *(_DWORD *)&S15_0002->field_0;
  v6[1] = *(_DWORD *)&S15_0002->field_4;
  v6[2] = *(_DWORD *)&S15_0002->field_8;
  v6[3] = *(_DWORD *)&S15_0002->field_C;
  v7 = (void *)self->field_C;
  self->field = sub_4BF790(8u, (int)v7);
  gta2::sub_4BF7B0(v7, v9);
}


// 0x004bffe0: Style::isCarRecyclable
// IDA: Style::isCarRecyclable
// Ghidra: ---
bool gta2::Style_isCarRecyclable(Style *self, CarModel CarModel)
{
  char *recy; // eax
  int v3; // edx
  unsigned __int8 v5; // bl

  recy = self->recy;
  v3 = 0;
  if ( !recy )
    return 1;
  if ( (unsigned __int8)*recy < (unsigned __int8)CarModel )
  {
    do
      v5 = recy[++v3];
    while ( v5 < (unsigned __int8)CarModel );
  }
  return recy[v3] == (char)CarModel;
}


// 0x004c0010: Style::read_recy_chunk_REAL_
// IDA: Style::read_recy_chunk_REAL_
// Ghidra: ---
int gta2::Style_read_recy_chunk_REAL_(Style *self, SIZE_T dwBytes)
{
  char *Buffer; // eax
  __int16 v4; // cx

  Buffer = (char *)gta2::createBuffer(dwBytes);
  v4 = dwBytes;
  self->recy = Buffer;
  self->n_recy = v4;
  return gta2::FileMgr_Read((FILE *)Buffer, &dwBytes);
}


// 0x004c0040: Style::sub_4C0040
// IDA: Style::sub_4C0040
// Ghidra: Style::FUN_004c0040
void gta2::Style_sub_4C0040(Style *self,int param_1)
{
  FileMgr *this_00;
  short sVar1;
  FileMgr *extraout_ECX;
  FileMgr *extraout_ECX_00;
  uint local_8;
  int local_4;
  
  local_4 = 2;
  gta2::FileMgr_Read((FileMgr *)&local_8,(size_t)&local_8);
  sVar1 = (short)local_8;
  this_00 = extraout_ECX;
  while (sVar1 != 0) {
    self->arr1024[local_8 & 0xffff] = param_1;
    gta2::FileMgr_Read(this_00,(size_t)&local_8);
    this_00 = extraout_ECX_00;
    sVar1 = (short)local_8;
  }
  return;
}


// 0x004c00a0: Style::read_spec_records_REAL
// IDA: Style::read_spec_records_REAL
// Ghidra: ---
int gta2::Style_read_spec_records_REAL(Style *self)
{
  gta2::Style_sub_4C0040(self, 2);
  gta2::Style_sub_4C0040(self, 3);
  gta2::Style_sub_4C0040(self, 4);
  gta2::Style_sub_4C0040(self, 5);
  gta2::Style_sub_4C0040(self, 6);
  gta2::Style_sub_4C0040(self, 7);
  gta2::Style_sub_4C0040(self, 8);
  gta2::Style_sub_4C0040(self, 9);
  return gta2::Style_sub_4C0040(self, 10);
}


// 0x004c0100: Style::sub_4C0100
// IDA: Style::sub_4C0100
// Ghidra: ---
unsigned int gta2::Style_sub_4C0100(Style *self)
{
  int v1; // edx
  int v2; // edi
  _DWORD *v3; // edx
  unsigned int result; // eax

  if ( self->field_50 && self->field_48 )
    gta2::Style_sub_4BF900(self);
  result = self->field_20;
  if ( result )
  {
    result = self->field_34;
    if ( result )
    {
      for ( result = 0; result < self->field_4; *v3 = self->field_34 + v2 )
      {
        v1 = self->field_20;
        v2 = *(_DWORD *)(v1 + 8 * result);
        v3 = (_DWORD *)(v1 + 8 * result++);
      }
    }
  }
  return result;
}


// 0x004c0130: Style::Style_Des
// IDA: Style::Style_Des
// Ghidra: ---
void gta2::Style_Style_Des(Style *self)
{
  S15_001 *v2; // eax
  void *v3; // ecx
  void *v4; // edx
  struct S15_0002 *S15_0002; // eax
  struct Car *Car; // eax
  void *v7; // eax
  void *v8; // eax
  FILE *v9; // ecx
  void *v10; // eax
  void *v11; // eax
  void *v12; // eax
  void *v13; // eax
  void *v14; // eax
  void *v15; // eax
  S284 *pCar_5C; // edx
  void *v17; // eax
  void *v18; // eax
  struct S1501 *S1501; // eax

  if ( self->recy )
    gta2::free_0(self->recy);
  v2 = self->field_14;
  self->recy = 0;
  free(v2);
  v3 = (void *)self->field_18;
  self->field_14 = 0;
  free(v3);
  v4 = (void *)self->field_C;
  self->field_18 = 0;
  free(v4);
  S15_0002 = self->S15_0002_;
  self->field_C = 0;
  free(S15_0002);
  Car = self->Car;
  self->S15_0002_ = 0;
  if ( Car )
    gta2::free_0(Car);
  v7 = (void *)self->field_20;
  self->Car = 0;
  if ( v7 )
    gta2::free_0(v7);
  v8 = (void *)self->field_24;
  self->field_20 = 0;
  if ( v8 )
    gta2::free_0(v8);
  v9 = self->field_28;
  self->field_24 = 0;
  free(v9);
  v10 = (void *)self->field_30;
  self->field_28 = 0;
  if ( v10 )
    gta2::free_0(v10);
  v11 = (void *)self->field_44;
  self->field_2C = 0;
  self->field_30 = 0;
  if ( v11 )
    gta2::free_0(v11);
  v12 = (void *)self->field_38;
  self->Tiles = 0;
  self->field_44 = 0;
  if ( v12 )
    gta2::free_0(v12);
  v13 = (void *)self->field_48;
  self->field_34 = 0;
  self->field_38 = 0;
  if ( v13 )
    gta2::free_0(v13);
  v14 = (void *)self->field_50;
  self->field_48 = 0;
  if ( v14 )
    gta2::free_0(v14);
  v15 = (void *)self->field_58;
  self->field_50 = 0;
  if ( v15 )
    gta2::free_0(v15);
  pCar_5C = self->pCar_5C;
  self->field_58 = 0;
  free(pCar_5C);
  v17 = (void *)self->field_4C;
  self->pCar_5C = 0;
  if ( v17 )
    gta2::free_0(v17);
  v18 = (void *)self->field_54;
  self->field_4C = 0;
  if ( v18 )
    gta2::free_0(v18);
  S1501 = self->S1501_;
  self->field_54 = 0;
  free(S1501);
  self->S1501_ = 0;
}


// 0x004c03d0: Style::InitSpecArray
// IDA: Style::InitSpecArray
// Ghidra: ---
Style * gta2::Style_InitSpecArray(Style *self)
{
  memset32(self, 1, 0x400u);
  return self;
}


// 0x004c0410: Style::sub_4C0410
// IDA: Style::sub_4C0410
// Ghidra: Style::FUN_004c0410
void gta2::Style_sub_4C0410(Style *self,size_t size,int param_2,undefined4 param_3, uint pSize)
{
  char cVar1;
  S371 *pS371;
  S371 *p1S371;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  S372 *pS372;
  
  uVar4 = 0;
  pS372 = self->CARI;
  uVar5 = 0;
  pS371 = (S371 *)gta2::operator_new(0x404);
  if (pS371 == NULL) {
    p1S371 = NULL;
  }
  else {
    p1S371 = gta2::sub_4C03F0(pS371);
  }
  self->S371 = p1S371;
  if (p1S371 == NULL) {
    gta2::DebugLog(0x20,"style.cpp",0x339);
  }
  if (pSize != 0) {
    do {
      if (0xff < uVar4) {
        gta2::DebugLog(0x22,"style.cpp",0x33d);
      }
      if (((128 < *(byte *)((int)&pS372->count + 2)) ||
          (128 < *(byte *)((int)&pS372->count + 3))) ||
         (64 < *(byte *)&pS372->Next)) {
        gta2::DebugLog(0x453,"style.cpp",0x33e);
      }
      cVar1 = *(char *)((int)&pS372->count + 1);
      if ((cVar1 != '\0') && (cVar1 != '\x01')) {
        gta2::DebugLog(0x453,"style.cpp",0x33f);
      }
      self->S371->S372_Arary_256[(byte)pS372->count] = pS372;
      cVar1 = *(char *)((int)&pS372->count + 1);
      if (cVar1 != '\0') {
        size = (uint)CONCAT11(cVar1,size._2_1_ + size._3_1_) << 0x10;
      }
      uVar2 = (uint)*(byte *)&pS372->Next;
      *(char *)((int)&pS372->count + 1) = size._2_1_;
      if (5 < *(byte *)((int)&pS372[1].Next + uVar2 + 2)) {
        gta2::DebugLog(0x453,"style.cpp",0x34e);
      }
      iVar3 = (uint)*(byte *)((int)&pS372[1].Next + uVar2 + 2) * 2 + uVar2 + 0xf
      ;
      uVar5 = uVar5 + iVar3;
      pS372 = (S372 *)((int)&pS372[1].Next + iVar3 + -0xc);
      uVar4 = uVar4 + 1;
      self = (Style *)param_2;
    } while (uVar5 < pSize);
    *(char *)(*(int *)(param_2 + 0x5c) + 0x400) = (char)uVar4;
    return;
  }
  *(undefined1 *)&self->S371->count = 0;
  return;
}


// 0x004c0580: Style::read_cari_records_REAL
// IDA: Style::read_cari_records_REAL
// Ghidra: ---
_DWORD * gta2::Style_read_cari_records_REAL(Style *self, FileMgr *dwBytes)
{
  FILE *Buffer; // eax

  Buffer = (FILE *)gta2::createBuffer((SIZE_T)dwBytes);
  self->field_58 = (int)Buffer;
  gta2::FileMgr_Read(Buffer, (SIZE_T *)&dwBytes);
  return gta2::Style_sub_4C0410(self, (unsigned int)dwBytes);
}


// 0x004c05b0: Style::parse_chunk
// IDA: Style::parse_chunk
// Ghidra: ---
void gta2::Style_parse_chunk(Style *self, char *chunk_type, int chunk_size)
{
  FileMgr *v4; // ecx

  if ( !gta2::_strncmp(chunk_type, "PALB", 4) )
  {
    gta2::Style_read_palb_chunk_REAL(self, chunk_size);
  }
  else if ( !gta2::_strncmp(chunk_type, "SPRB", 4) )
  {
    gta2::Style_read_sprb_records_REAL(self, chunk_size);
  }
  else if ( !gta2::_strncmp(chunk_type, "FONB", 4) )
  {
    gta2::Style_read_fonb_chunk_REAL(self, chunk_size);
  }
  else if ( !gta2::_strncmp(chunk_type, "SPRX", 4) )
  {
    gta2::Style_read_sprx_records_REAL(self, chunk_size);
  }
  else if ( !gta2::_strncmp(chunk_type, "OBJI", 4) )
  {
    gta2::Style_read_obji_records_REAL(self, chunk_size);
  }
  else if ( !gta2::_strncmp(chunk_type, "PALX", 4) )
  {
    gta2::Style_read_palx_records_REAL(self, chunk_size);
  }
  else if ( !gta2::_strncmp(chunk_type, "PPAL", 4) )
  {
    gta2::Style_read_ppal_records_REAL(self, chunk_size);
  }
  else if ( !gta2::_strncmp(chunk_type, "SPRG", 4) )
  {
    gta2::Style_read_sprg_records_REAL(self, chunk_size);
  }
  else if ( !gta2::_strncmp(chunk_type, "TILE", 4) )
  {
    gta2::Style_read_tile_chunk_REAL(self, chunk_size);
  }
  else if ( !gta2::_strncmp(chunk_type, "DELS", 4) )
  {
    gta2::Style_read_dels_records_REAL(self, (FileMgr *)chunk_size);
  }
  else if ( !gta2::_strncmp(chunk_type, "DELX", 4) )
  {
    gta2::Style_read_delx_records_REAL(self, (FileMgr *)chunk_size);
  }
  else if ( !gta2::_strncmp(chunk_type, "CARI", 4) )
  {
    gta2::Style_read_cari_records_REAL(self, (FileMgr *)chunk_size);
  }
  else if ( !gta2::_strncmp(chunk_type, "PSXT", 4) )
  {
    gta2::Style_read_psxt_records_REAL(self, chunk_size);
  }
  else if ( !gta2::_strncmp(chunk_type, "OVLY", 4) )
  {
    gta2::Style_read_ovly_records_REAL_(self, chunk_size);
  }
  else if ( !gta2::_strncmp(chunk_type, "SPEC", 4) )
  {
    gta2::Style_read_spec_records_REAL(self);
  }
  else if ( !gta2::_strncmp(chunk_type, "RECY", 4) )
  {
    gta2::Style_read_recy_chunk_REAL_(self, chunk_size);
  }
  else
  {
    gta2::FileMgr_SeekPosition(v4, (int)&chunk_size);
  }
}


// 0x004c0820: Style::LoadFstyle
// IDA: Style::LoadFstyle
// Ghidra: ---
unsigned int gta2::Style_LoadFstyle(Style *self, LPCSTR lpFileName)
{
  FileMgr *v3; // ecx
  unsigned int size; // [esp+4h] [ebp-14h] BYREF
  FILE v6[2]; // [esp+8h] [ebp-10h] BYREF
  char a1[4]; // [esp+10h] [ebp-8h] BYREF
  SIZE_T chunk_size; // [esp+14h] [ebp-4h]

  gta2::FileMgr_FileOpen(self, lpFileName);
  size = 6;
  gta2::FileMgr_Read(v6, &size);
  gta2::Chunk1(v6, "GBST");
  gta2::Chunk(v6, 700);
  for ( size = 8; gta2::FileMgr_ReadLine((FileMgr *)a1, a1, (SIZE_T)&size); size = 8 )
  {
    if ( chunk_size )
      gta2::Style_parse_chunk(self, a1, chunk_size);
  }
  gta2::FileMgr_CloseFile(v3);
  return gta2::Style_sub_4C0100(self);
}


// 0x004c08d0: Style::Style
// IDA: Style::Style
// Ghidra: ---
Style * gta2::Style_Style(Style *self)
{
  gta2::Style_InitSpecArray((Style *)self->arr1024);
  self->recy = 0;
  self->n_recy = 0;
  self->field_14 = 0;
  self->field_C = 0;
  self->Car = 0;
  self->field_20 = 0;
  self->field_24 = 0;
  self->field_6 = 0;
  self->field_28 = 0;
  self->field_2C = 0;
  self->field_30 = 0;
  self->Tiles = 0;
  self->field_44 = 0;
  self->field_34 = 0;
  self->field_38 = 0;
  self->field_48 = 0;
  self->field_50 = 0;
  self->field_58 = 0;
  self->pCar_5C = 0;
  self->field_4C = 0;
  self->delx3 = 0;
  self->field_54 = 0;
  self->field_4 = 0;
  self->field = 0;
  self->field_2 = 0;
  self->S1501_ = 0;
  self->PalitrePal = 0;
  self->ColourDepth = 0;
  self->S15_0002_ = 0;
  self->field_18 = 0;
  return self;
}


// 0x004c2eb0: Style::sub_4C2EB0
// IDA: Style::sub_4C2EB0
// Ghidra: ---
int gta2::Style_sub_4C2EB0(Style *self, unsigned __int16 a2)
{
  int v2; // eax

  v2 = a2;
  LOBYTE(v2) = a2 & 0xFC;
  return self->Tiles + (((a2 & 3) + (v2 << 6)) << 6);
}


// 0x004c2ee0: Style::has_tiles
// IDA: Style::has_tiles
// Ghidra: ---
bool gta2::Style_has_tiles(Style *self)
{
  return self->Tiles != 0;
}



