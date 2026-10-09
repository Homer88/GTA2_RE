#include "gta2_shim.h"

// Module: other, Class: TextureManager
// Functions: 15
// Source: unified (IDA+Ghidra)

// 0x0046bb50: TextureManager::getTexture4M
// IDA: TextureManager::getTexture4M
// Ghidra: ---
void * gta2::TextureManager_getTexture4M(struct TextureManager *self, unsigned __int16 *index)
{
  return self->BufferTexture4M[*index];
}


// 0x004c2970: TextureManager::sub_4C2970
// IDA: TextureManager::sub_4C2970
// Ghidra: ---
__int16 gta2::TextureManager_sub_4C2970(struct TextureManager *self)
{
  __int16 result; // ax
  unsigned __int16 v3; // si
  int ColourBank; // eax
  int v5; // ecx

  result = gta2::Style_GetPalitrePal(gStyle);
  v3 = 0;
  self->PalitrePal = result;
  if ( result )
  {
    do
    {
      ColourBank = gta2::Style_GetColourBank(gStyle, v3);
      result = gta2::gbh_RegisterPalette(v5, v3++, ColourBank);
    }
    while ( v3 < (unsigned int)self->PalitrePal );
  }
  return result;
}


// 0x004c29c0: TextureManager::FreePalitre
// IDA: TextureManager::FreePalitre
// Ghidra: ---
int gta2::TextureManager_FreePalitre(struct TextureManager *self)
{
  unsigned __int16 i; // si
  int result; // eax

  for ( i = 0; i < (unsigned int)self->PalitrePal; ++i )
    result = gbh_FreePalette(i);
  self->PalitrePal = 0;
  return result;
}


// 0x004c2a00: TextureManager::sub_4C2A00
// IDA: TextureManager::sub_4C2A00
// Ghidra: FUN_004c2a00
undefined4 gta2::TextureManager_sub_4C2A00(int param_1,ushort param_2,short param_3)
{
  ushort uVar1;
  undefined4 uVar2;
  short sVar3;
  ushort id;
  undefined4 *puVar4;
  undefined2 extraout_var;
  undefined4 uVar5;
  undefined4 *puVar6;
  
  uVar1 = *(ushort *)(param_1 + 0x15d4);
  sVar3 = gta2::Style_GetGlobalSpriteId(gStyle,6,param_3);
  puVar4 = (undefined4 *)gta2::Style_GetSprite(gStyle,sVar3);
  uVar2 = *puVar4;
  id = gta2::Style_get_global_palette_id(gStyle,2,sVar3);
  sVar3 = gta2::Style_get_physical_palette(gStyle,id);
  _param_3 = CONCAT22(extraout_var,sVar3);
  *(short *)(param_1 + 0x15d4) = *(short *)(param_1 + 0x15d4) + param_2;
  if (param_2 != 0) {
    puVar6 = (undefined4 *)(param_1 + (uVar1 + 0x166) * 0xc);
    _param_3 = (uint)param_2;
    do {
      uVar5 = (*(code *)gbh_RegisterTexture)
                        (*(undefined1 *)(puVar4 + 1),
                         *(undefined1 *)((int)puVar4 + 5),uVar2,sVar3,0);
      *puVar6 = uVar5;
      puVar6[-1] = uVar2;
      puVar6 = puVar6 + 3;
      _param_3 = _param_3 - 1;
    } while (_param_3 != 0);
  }
  return CONCAT22((short)(_param_3 >> 0x10),uVar1);
}


// 0x004c2ac0: TextureManager::sub_4C2AC0
// IDA: TextureManager::sub_4C2AC0
// Ghidra: ---
int gta2::TextureManager_sub_4C2AC0(struct TextureManager *self, int sprite_type, __int16 spriteId, int a4, __int16 a5)
{
  int result; // eax

  switch ( a4 )
  {
    case 2:
      result = gta2::S89_sub_4C2920(self->S89_, sprite_type, spriteId);
      break;
    case 3:
      result = gta2::S89_sub_4C2950(&self->S89_[1], spriteId, a5);
      break;
    case 4:
      result = gta2::S89_sub_4C2950(&self->S89_[2], spriteId, a5);
      break;
    case 5:
      result = gta2::S89_sub_4C2950(&self->S89_[3], spriteId, a5);
      break;
    case 6:
      result = gta2::S89_sub_4C2950(&self->S89_[4], spriteId, a5);
      break;
    case 7:
      result = gta2::S89_sub_4C2950(&self->S89_[6], spriteId, a5);
      break;
    case 8:
      result = gta2::S89_sub_4C2950(&self->S89_[5], spriteId, a5);
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


// 0x004c2ba0: TextureManager::sub_4C2BA0
// IDA: TextureManager::sub_4C2BA0
// Ghidra: ---
GLuint * gta2::TextureManager_sub_4C2BA0(struct TextureManager *self, unsigned __int16 a2)
{
  return self->Buffer_Arr48[a2];
}


// 0x004c2bc0: TextureManager::sub_4C2BC0
// IDA: TextureManager::sub_4C2BC0
// Ghidra: FUN_004c2bc0
int gta2::TextureManager_sub_4C2BC0(int param_1,uint param_2,ushort param_3,short param_4)
{
  int *piVar1;
  int iVar2;
  
  param_2 = param_2 & 0xffff;
  iVar2 = *(int *)(param_1 + 0x10c8 + param_2 * 0xc);
  piVar1 = (int *)(param_1 + 0x10c4 + param_2 * 0xc);
  if ((param_4 != *(short *)(param_1 + 0x10cc + param_2 * 0xc)) ||
     (param_3 != *(ushort *)((int)piVar1 + 10))) {
    *(short *)(piVar1 + 2) = param_4;
    *(ushort *)((int)piVar1 + 10) = param_3;
    (*(code *)gbh_LockTexture)(iVar2);
    *(uint *)(iVar2 + 0x14) = (uint)param_3 * 0x100 + *piVar1;
    *(short *)(iVar2 + 0x10) = param_4;
    (*(code *)gbh_UnlockTexture)(iVar2);
  }
  return iVar2;
}


// 0x004c2c30: TextureManager::sub_4C2C30
// IDA: TextureManager::sub_4C2C30
// Ghidra: FUN_004c2c30
void gta2::TextureManager_sub_4C2C30(int param_1,uint param_2,ushort param_3)
{
  undefined4 uVar1;
  short sVar2;
  
  uVar1 = *(undefined4 *)(param_1 + ((param_2 & 0xffff) + 0x166) * 0xc);
  sVar2 = gta2::Style_get_physical_palette(gStyle,param_3);
  (*(code *)gbh_LockTexture)(uVar1);
  (*(code *)gbh_AssignPalette)(uVar1,sVar2);
  (*(code *)gbh_UnlockTexture)(uVar1);
  return;
}


// 0x004c2c80: TextureManager::sub_4C2C80
// IDA: TextureManager::sub_4C2C80
// Ghidra: FUN_004c2c80
void gta2::TextureManager_sub_4C2C80(int param_1,ushort param_2,undefined2 param_3,undefined4 param_4, ushort param_5)
{
  int iVar1;
  short sVar2;
  
  sVar2 = gta2::Style_get_physical_palette(gStyle,param_5);
  iVar1 = *(int *)(param_1 + 0x1004 + (uint)param_2 * 4);
  (*(code *)gbh_LockTexture)(iVar1);
  *(ushort *)(iVar1 + 0xe) = param_2;
  *(undefined2 *)(iVar1 + 0x10) = param_3;
  (*(code *)gbh_AssignPalette)(iVar1,sVar2);
  (*(code *)gbh_UnlockTexture)(iVar1);
  return;
}


// 0x004c2ce0: TextureManager::sub_4C2CE0
// IDA: TextureManager::sub_4C2CE0
// Ghidra: FUN_004c2ce0
undefined4 gta2::TextureManager_sub_4C2CE0(int param_1,undefined2 param_2,undefined4 param_3, undefined4 param_4,ushort param_5)
{
  short sVar1;
  undefined2 unaff_retaddr;
  
  sVar1 = gta2::Style_get_physical_palette(gStyle,param_5);
  (*(code *)gbh_LockTexture)(*(undefined4 *)(param_1 + 0x1544));
  *(undefined4 *)(*(int *)(param_1 + 0x1544) + 0x14) = param_3;
  *(undefined2 *)(*(int *)(param_1 + 0x1544) + 0xe) = unaff_retaddr;
  *(undefined2 *)(*(int *)(param_1 + 0x1544) + 0x10) = param_2;
  (*(code *)gbh_AssignPalette)(*(undefined4 *)(param_1 + 0x1544),sVar1);
  (*(code *)gbh_UnlockTexture)(*(undefined4 *)(param_1 + 0x1544));
  return *(undefined4 *)(param_1 + 0x1544);
}


// 0x004c2d60: TextureManager::TextureManager_des
// IDA: TextureManager::TextureManager_des
// Ghidra: ---
void gta2::TextureManager_TextureManager_des(struct TextureManager *self)
{
  GLuint **pTextureManager; // esi
  int index; // ebp
  GLuint *Buffer_Arr48; // esi
  int v5; // ebp
  GLuint *pGLuint; // esi
  int v7; // ebp

  if ( self->TexturesInitialised )
  {
    pTextureManager = (GLuint **)self;
    index = 1024;
    do
    {
      if ( *pTextureManager )
      {
        gta2::gbh_FreeTexture(*pTextureManager);
        *pTextureManager = 0;
      }
      ++pTextureManager;
      --index;
    }
    while ( index );
  }
  if ( self->field_1000 )
  {
    Buffer_Arr48 = (GLuint *)self->Buffer_Arr48;
    v5 = 48;
    do
    {
      if ( *Buffer_Arr48 )
      {
        gta2::gbh_FreeTexture((GLuint *)*Buffer_Arr48);
        *Buffer_Arr48 = 0;
      }
      ++Buffer_Arr48;
      --v5;
    }
    while ( v5 );
  }
  pGLuint = (GLuint *)&self->Arr_96_S88[0].GLuint;
  v7 = 96;
  do
  {
    if ( *pGLuint )
    {
      gta2::gbh_FreeTexture((GLuint *)*pGLuint);
      *pGLuint = 0;
    }
    pGLuint += 3;
    --v7;
  }
  while ( v7 );
  if ( self->Texture )
  {
    gta2::gbh_FreeTexture(self->Texture);
    self->Texture = 0;
  }
  gta2::TextureManager_FreePalitre(self);
  gta2::S89_sub_4C28D0(&self->S89_[6]);
  gta2::S89_sub_4C28D0(&self->S89_[5]);
  gta2::S89_sub_4C28D0(&self->S89_[4]);
  gta2::S89_sub_4C28D0(&self->S89_[3]);
  gta2::S89_sub_4C28D0(&self->S89_[2]);
  gta2::S89_sub_4C28D0(&self->S89_[1]);
  gta2::S89_sub_4C28D0(self->S89_);
}


// 0x004c2f90: TextureManager::sub_4C2F90
// IDA: TextureManager::sub_4C2F90
// Ghidra: ---
__int16 gta2::TextureManager_sub_4C2F90(struct TextureManager *self)
{
  GLuint *v2; // eax
  unsigned __int16 GlobalSpriteId; // ax
  unsigned __int16 global_palette_id; // ax
  unsigned __int16 v5; // si
  int v6; // eax
  unsigned __int16 v8; // [esp+4h] [ebp-8h]
  unsigned __int16 pIndex; // [esp+8h] [ebp-4h] OVERLAPPED BYREF

  v8 = 64;
  LOWORD(v2) = gta2::Style_sub_4BF330(gStyle, 2);
  if ( (_WORD)v2 )
  {
    self->field_1000 = 1;
    GlobalSpriteId = gta2::Style_GetGlobalSpriteId(gStyle, 2, 0);
    global_palette_id = gta2::Style_get_global_palette_id(gStyle, 2, GlobalSpriteId);
    *(_DWORD *)&v5 = 0;
    gta2::Style_get_physical_palette(gStyle, global_palette_id);
    do
    {
      if ( *(_DWORD *)&v5 == 32 )
        v8 = 128;
      *(_DWORD *)&pIndex = *(_DWORD *)&v5;
      v6 = gta2::SpriteS3_sub_4C2EF0(gSpriteS3, &pIndex);
      v2 = (GLuint *)gta2::gbh_RegisterTexture(v8, v8, v6);
      self->Buffer_Arr48[(*(_DWORD *)&v5)++] = v2;
    }
    while ( *(_DWORD *)&v5 < 48u );
  }
  return (__int16)v2;
}


// 0x004c3040: TextureManager::sub_4C3040
// IDA: TextureManager::sub_4C3040
// Ghidra: ---
char gta2::TextureManager_sub_4C3040(struct TextureManager *self)
{
  void *v2; // eax
  unsigned __int16 i; // si
  Style *pStyle; // ebx
  int v5; // ebp

  LOBYTE(v2) = gta2::Style_has_tiles(gStyle);
  if ( (_BYTE)v2 )
  {
    self->TexturesInitialised = 1;
    for ( i = 0; i < 0x400u; ++i )
    {
      pStyle = gStyle;
      v5 = gta2::Style_sub_4C2EB0(gStyle, i);
      gta2::Style_get_physical_palette(pStyle, i);
      v2 = (void *)gta2::gbh_RegisterTexture(64, 64, v5);
      self->BufferTexture4M[0] = v2;
      self = (TextureManager *)((char *)self + 4);
    }
  }
  return (char)v2;
}


// 0x004c30a0: TextureManager::sub_4C30A0
// IDA: TextureManager::sub_4C30A0
// Ghidra: ---
int gta2::TextureManager_sub_4C30A0(struct TextureManager *self)
{
  __int16 v2; // ax
  int result; // eax

  gta2::TextureManager_sub_4C2970(self);
  gta2::TextureManager_sub_4C3040(self);
  v2 = gta2::Style_sub_4BF3A0(gStyle, 2);
  gta2::S89_sub_4C2710(self->S89_, v2, 1, 0, 2);
  gta2::S89_sub_4C2780(self->S89_);
  gta2::S89_sub_4C2F30(&self->S89_[1], 2, 3);
  gta2::S89_sub_4C27F0(&self->S89_[1]);
  gta2::S89_sub_4C2F30(&self->S89_[2], 3, 4);
  gta2::S89_sub_4C27F0(&self->S89_[2]);
  gta2::S89_sub_4C2F30(&self->S89_[3], 4, 5);
  gta2::S89_sub_4C27F0(&self->S89_[3]);
  gta2::S89_sub_4C2F30(&self->S89_[4], 5, 6);
  gta2::S89_sub_4C27F0(&self->S89_[4]);
  gta2::S89_sub_4C2F30(&self->S89_[5], 7, 8);
  gta2::S89_sub_4C27F0(&self->S89_[5]);
  gta2::S89_sub_4C2F30(&self->S89_[6], 6, 7);
  gta2::S89_sub_4C27F0(&self->S89_[6]);
  gta2::TextureManager_sub_4C2F90(self);
  result = gta2::gbh_RegisterTexture(128, 128, 0);
  self->Texture = (GLuint *)result;
  return result;
}


// 0x004c3190: TextureManager::TextureManager
// IDA: TextureManager::TextureManager
// Ghidra: ---
TextureManager * gta2::TextureManager_TextureManager(struct TextureManager *self)
{
  gta2::constructor(self->Arr_96_S88, 12, 96, S88::S88);
  gta2::S89_S89(self->S89_);
  gta2::S89_S89(&self->S89_[1]);
  gta2::S89_S89(&self->S89_[2]);
  gta2::S89_S89(&self->S89_[3]);
  gta2::S89_S89(&self->S89_[4]);
  gta2::S89_S89(&self->S89_[5]);
  gta2::S89_S89(&self->S89_[6]);
  self->field_1000 = 0;
  self->TexturesInitialised = 0;
  self->field_15D4 = 0;
  self->PalitrePal = 0;
  memset(self, 0, 4096u);
  memset(self->Buffer_Arr48, 0, sizeof(self->Buffer_Arr48));
  self->Texture = 0;
  return self;
}



