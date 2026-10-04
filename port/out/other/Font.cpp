#include "gta2_shim.h"

// Module: other, Class: Font
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x004c8aa0: Font::sub_4C8AA0
// IDA: Font::sub_4C8AA0
// Ghidra: ---
int gta2::Font_sub_4C8AA0(void *self, HudBrief *a2, __int16 a3, __int16 a4, __int16 a5, size_t a6)
{
  __int16 v7; // ax
  int v8; // eax
  int v9; // eax
  size_t v10; // eax

  *((_WORD *)self + 86) = a5;
  gta2::HudBrief_sub_4C2450((struct HudBrief *)self, (wchar_t *)self, (int)a2, 640);
  v7 = *((_WORD *)self + 86);
  if ( v7 == unk_670674 || v7 == unk_670678 )
    gta2::Text_ConvertWordsToBig(gText, (wchar_t *)self);
  LOWORD(v8) = a3;
  *((_DWORD *)self + 44) = 2;
  *((_WORD *)self + 90) = 0;
  if ( a3 == -1 )
  {
    LOWORD(v9) = gta2::Font_GetStringWidth((wchar_t *)self, *((_WORD *)self + 86));
    v8 = (640 - v9) / 2;
  }
  *((_WORD *)self + 84) = v8;
  LOWORD(v8) = a4;
  if ( a4 == -1 )
    v8 = (480 - gta2::Font_GetNumberLines((wchar_t *)self, *((_WORD *)self + 86))) / 2;
  *((_WORD *)self + 85) = v8;
  v10 = a6;
  if ( a6 == -2 )
    v10 = gHud->TextSpeed * gta2::_wcslen((const wchar_t *)self);
  *((_DWORD *)self + 41) = v10;
  return gta2::sub_4C70E0(self);
}


// 0x004cb0c0: Font::GetStringWidth
// IDA: Font::GetStringWidth
// Ghidra: ---
ushort gta2::Font_GetStringWidth(wchar_t *str, __int16 style)
{
  wchar_t *v2; // edi
  int v3; // esi
  int v4; // ebp
  unsigned __int16 v5; // bx
  unsigned __int16 v6; // ax
  ushort result; // ax

  v2 = str;
  v3 = 0;
  v4 = 0;
  *(_DWORD *)&v5 = (unsigned __int16)gta2::Style_sub_4BF5D0(gStyle, &style);
  if ( !*str )
    return v4;
  do
  {
    v6 = *v2;
    if ( *v2 == 32 )
    {
      v3 += *(_DWORD *)&v5;
    }
    else if ( v6 == 10 )
    {
      if ( v3 > v4 )
        v4 = v3;
      v3 = 0;
    }
    else if ( v6 != 35 )
    {
      v3 += gta2::Style_sub_4BF570(gStyle, (wchar_t *)&style, v2);
    }
    ++v2;
  }
  while ( *v2 );
  result = v3;
  if ( v3 <= v4 )
    return v4;
  return result;
}


// 0x004cc0c0: Font::GetNumberLines
// IDA: Font::GetNumberLines
// Ghidra: ---
int gta2::Font_GetNumberLines(wchar_t *str, __int16 style)
{
  int result; // eax
  int v3; // esi
  wchar_t *v4; // edx
  wchar_t i; // cx

  result = gta2::Font_GetCharHeight(style);
  v3 = result;
  v4 = str;
  for ( i = *str; i; ++v4 )
  {
    if ( i == 10 )
      result += v3;
    i = v4[1];
  }
  return result;
}



