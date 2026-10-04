#include "gta2_shim.h"

// Module: other, Class: Text
// Functions: 12
// Source: unified (IDA+Ghidra)

// 0x004c2060: Text::sub_4C2060
// IDA: Text::sub_4C2060
// Ghidra: FUN_004c2060
void gta2::Text_sub_4C2060(size_t *param_1,uint param_2)
{
  void *pvVar1;
  
  param_1[1] = param_2 / 0xc;
  pvVar1 = gta2::operator_new((param_2 / 0xc) * 0xc);
  *param_1 = (size_t)pvVar1;
  if (pvVar1 == NULL) {
    gta2::DebugLog(0x20,"text.cpp",0x7a);
  }
  gta2::FileMgr_Read((struct FileMgr *)&stack0x00000010,*param_1);
  return;
}


// 0x004c20b0: Text::sub_4C20B0
// IDA: Text::sub_4C20B0
// Ghidra: ---
int gta2::Text_sub_4C20B0(struct Text *self, int a2)
{
  int result; // eax
  size_t i; // edx
  int v4; // edi

  result = (int)self->Base;
  for ( i = 0; i < self->Num; *(_DWORD *)(result - 12) = a2 + v4 )
  {
    v4 = *(_DWORD *)result;
    result += 12;
    ++i;
  }
  return result;
}


// 0x004c2120: Text::_Bsearch
// IDA: Text::_Bsearch
// Ghidra: ---
void * gta2::Text__Bsearch(struct Text *self, const void *pKey)
{
  void *v2; // eax

  v2 = bsearch(pKey, self->Base, self->Num, 0xCu, (_CoreCrtNonSecureSearchSortCompareFunction)CompareFunction);
  if ( v2 )
    return *(void **)v2;
  else
    return " ";
}


// 0x004c21a0: Text::ConvertToUpper
// IDA: Text::ConvertToUpper
// Ghidra: ---
wchar_t gta2::Text_ConvertToUpper(struct Text *self, wchar_t CodeByte)
{
  wchar_t result; // ax

  result = CodeByte;
  switch ( self->Language )
  {
    case 'e':
      if ( CodeByte >= 97u && CodeByte <= 122u )
        goto LABEL_4;
      break;
    case 'f':
      if ( (unsigned int)CodeByte >= 'a' && (unsigned int)CodeByte <= 'z' )
        goto LABEL_4;
      if ( CodeByte >= 0x80u && CodeByte <= 255u )
        result = FontJapan[CodeByte];
      break;
    case 'g':
    case 'i':
    case 's':
      if ( CodeByte >= 97u && CodeByte <= 122u )
      {
LABEL_4:
        result = CodeByte - 32;
      }
      else if ( CodeByte >= 128u && CodeByte <= 0xFFu )
      {
        result = FontEnglish[CodeByte];
      }
      break;
    default:
      return result;
  }
  return result;
}


// 0x004c2250: Text::ConvertWordsToBig
// IDA: Text::ConvertWordsToBig
// Ghidra: ---
wchar_t * gta2::Text_ConvertWordsToBig(struct Text *self, wchar_t *a2)
{
  wchar_t *i; // esi

  for ( i = a2; *i; ++i )
    *i = gta2::Text_ConvertToUpper(self, *i);
  return a2;
}


// 0x004c2330: Text::sub_4C2330
// IDA: Text::sub_4C2330
// Ghidra: ---
int gta2::Text_sub_4C2330(struct Text *self, char *a2, int size)
{
  struct FileMgr *v5; // ecx

  if ( !gta2::_strncmp(a2, "TKEY", 4) )
    return gta2::Text_sub_4C2060(self, size);
  if ( !gta2::_strncmp(a2, "TDAT", 4) )
    return gta2::sub_4C2150(&self->AutoClass4, size);
  return gta2::FileMgr_SeekPosition(v5, (int)&size);
}


// 0x004c23b0: Text::NetWorkNameShow
// IDA: Text::NetWorkNameShow
// Ghidra: ---
char * gta2::Text_NetWorkNameShow(struct Text *self, char *PlayerName)
{
  wchar_t *v2; // eax

  v2 = (wchar_t *)gta2::Text__Bsearch(self, PlayerName);
  return gta2::ConvertWCharToChar(v2);
}


// 0x004c23f0: Text::Clear
// IDA: Text::Clear
// Ghidra: ---
void gta2::Text_Clear(struct Text *self)
{
  self->Base = 0;
  self->Num = 0;
}


// 0x004c2400: Text::Base_Des
// IDA: Text::Base_Des
// Ghidra: ---
void gta2::Text_Base_Des(struct Text *self)
{
  if ( self->Base )
    j__free(self->Base);
  self->Base = 0;
}


// 0x004c2540: Text::Load
// IDA: Text::Load
// Ghidra: ---
int gta2::Text_Load(struct Text *self)
{
  void *v2; // ecx
  struct FileMgr *v3; // ecx
  struct FileMgr *v4; // ecx
  int v6; // ecx
  _BYTE *v7; // edi
  bool v8; // zf
  void *v9; // [esp-18h] [ebp-50h]
  unsigned int size; // [esp+8h] [ebp-30h] BYREF
  char BigReg[8]; // [esp+Ch] [ebp-2Ch] BYREF
  FILE v12[2]; // [esp+14h] [ebp-24h] BYREF
  char a1[4]; // [esp+1Ch] [ebp-1Ch] BYREF
  int v14; // [esp+20h] [ebp-18h]

  strcpy(gFileGTX, "data\\%c.gxt", self->Language);
  strcpy(BigReg, "GBL%c", self->Language - 32);
  if ( unk_676204 == 1 )
  {
    v9 = v2;
    qmemcpy(gFileGCI, "data\\nyc.gci", 12u);
    qmemcpy(FileName, "data\\nyc.gci", 12u);
    if ( gNetworkGame == 1 )
    {
      v6 = 254;
      v7 = &unk_673E30;
      do
      {
        if ( !v6 )
          break;
        v8 = *v7++ == 0;
        --v6;
      }
      while ( !v8 );
      qmemcpy(&unk_676DE1, &unk_673E30, v7 - (_BYTE *)&unk_673E30);
      GetPrivateProfileStringA("MapFiles", "GCIFile", "nyc.gci", ReturnedString, 254u, FileName);
      GetPrivateProfileStringA("MapFiles", "GXTFile", "e.gxt", gLanguage_0, 254u, FileName);
      if ( *(_DWORD *)gLanguage_0 == 2020028005 && word_676CE1 == 116 )
      {
        v2 = v9;
        gLanguage_0[0] = self->Language;
      }
      else
      {
        v2 = v9;
        self->Language = 'e';
        BigReg[3] = 'E';
      }
    }
  }
  unk_676204 = 0;
  gta2::FileMgr_FileOpen(v2, gFileGTX);
  size = 6;
  gta2::FileMgr_Read(v12, &size);
  gta2::Chunk1(v12, BigReg);
  gta2::Chunk(v12, 100);
  size = 8;
  if ( gta2::FileMgr_ReadLine(v3, a1, (SIZE_T)&size) )
  {
    do
    {
      if ( v14 )
        gta2::Text_sub_4C2330(self, a1, v14);
      size = 8;
    }
    while ( gta2::FileMgr_ReadLine(v4, a1, (SIZE_T)&size) );
  }
  gta2::FileMgr_CloseFile(v4);
  return gta2::Text_sub_4C20B0(self, self->AutoClass4);
}


// 0x004c2620: Text::Text
// IDA: Text::Text
// Ghidra: ---
Text * gta2::Text_Text(struct Text *self)
{
  gta2::Text_Clear(self);
  gta2::AutoClass4_AutoClass4(&self->AutoClass4);
  gta2::Registry_GetLanguage(&Registry, "language", (HKEY)gStr, 256);
  if ( gStr[0] == 'e' || gStr[0] == 'f' || gStr[0] == 'g' || gStr[0] == 'i' || gStr[0] == 's' || gStr[0] == 'j' )
  {
    self->Language = gStr[0];
    return self;
  }
  else
  {
    self->Language = 'e';
    return self;
  }
}


// 0x004c26c0: Text::Text_des_0
// IDA: Text::Text_des_0
// Ghidra: ---
void gta2::Text_Text_des_0(struct Text *self)
{
  gta2::sub_4C2430(&self->AutoClass4);
  gta2::Text_Base_Des(self);
}



