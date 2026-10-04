#include "gta2_shim.h"

// Module: other, Class: S151
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x004a8600: S151::sub_4A8600
// IDA: S151::sub_4A8600
// Ghidra: ---
wchar_t * gta2::S151_sub_4A8600(struct S151 *self)
{
  int v2; // edi
  wchar_t *result; // eax

  v2 = 10;
  do
  {
    result = CopyWideString(self->ALAN, gText_Menu);
    self->field_14 = 0;
    self = (struct S151 *)((char *)self + 24);
    --v2;
  }
  while ( v2 );
  return result;
}


// 0x004a8630: S151::sub_4A8630
// IDA: S151::sub_4A8630
// Ghidra: ---
char gta2::S151_sub_4A8630(struct S151 *self, unsigned __int16 *PlayerName, char *a3)
{
  unsigned __int16 v4; // bx
  __int16 i; // si
  char *v6; // edi
  char *v7; // eax
  int *v8; // esi
  int v9; // edi

  v4 = 10;
  for ( i = 9; i != -1; --i )
  {
    v6 = a3;
    v7 = *(char **)&self->ALAN[12 * i + 10];
    if ( a3 > v7 )
      v4 = i;
    if ( a3 == v7 && !gta2::wcscmp(PlayerName, &self->ALAN[12 * i]) )
      return 0;
  }
  if ( v4 == 10 )
    return 0;
  if ( v4 < 9u )
  {
    v8 = &self->field_D4;
    v9 = (unsigned __int16)(9 - v4);
    do
    {
      gta2::wcsncpy((wchar_t *)v8 + 2, (const wchar_t *)v8 - 10, 9u);
      v8[6] = *v8;
      v8 -= 6;
      --v9;
    }
    while ( v9 );
    v6 = a3;
  }
  gta2::wcsncpy(&self->ALAN[12 * v4], PlayerName, 9u);
  *(_DWORD *)&self->ALAN[12 * v4 + 10] = v6;
  return 1;
}


// 0x004a8f70: S151::S151
// IDA: S151::S151
// Ghidra: ---
void gta2::S151_S151(struct S151 *self)
{
  gta2::S151_sub_4A8600(self);
}



