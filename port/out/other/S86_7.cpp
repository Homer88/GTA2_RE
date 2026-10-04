#include "gta2_shim.h"

// Module: other, Class: S86_7
// Functions: 6
// Source: unified (IDA+Ghidra)

// 0x004c6170: S86_7::sub_4C6170
// IDA: S86_7::sub_4C6170
// Ghidra: ---
void gta2::S86_7_sub_4C6170(struct S86_7 *self)
{
  int v1; // esi
  void *v2; // ecx
  int v3; // edx
  int v4; // ecx

  v1 = 0;
  v2 = (void *)self->field_16F8;
  while ( v2 )
  {
    if ( gta2::sub_4C60F0(v2) )
    {
      if ( v1 )
      {
        *(_DWORD *)(v1 + 192) = *(_DWORD *)(v4 + 192);
        *(_DWORD *)(v4 + 192) = *(_DWORD *)(v3 + 5884);
        *(_DWORD *)(v3 + 5884) = v4;
        v2 = *(void **)(v1 + 192);
      }
      else
      {
        *(_DWORD *)(v3 + 5880) = *(_DWORD *)(*(_DWORD *)(v3 + 5880) + 192);
        *(_DWORD *)(v4 + 192) = *(_DWORD *)(v3 + 5884);
        *(_DWORD *)(v3 + 5884) = v4;
        v2 = *(void **)(v3 + 5880);
      }
    }
    else
    {
      v1 = v4;
      v2 = *(void **)(v4 + 192);
    }
  }
}


// 0x004c6250: S86_7::S86_7
// IDA: S86_7::S86_7
// Ghidra: ---
void gta2::S86_7_S86_7(struct S86_7 *self)
{
  int v2; // ecx
  int *v3; // edx

  v2 = 29;
  v3 = &self->field_C0;
  do
  {
    *v3 = (int)(v3 + 1);
    v3 += 49;
    --v2;
  }
  while ( v2 );
  self->field_16FC = self;
  self->field_16F4 = 0;
  self->field_16F8 = 0;
}


// 0x004c6e70: S86_7::PrintText_0
// IDA: S86_7::PrintText_0
// Ghidra: ---
int gta2::S86_7_PrintText_0(S86_7 *self, const wchar_t *text, int color, int duration, int style, int unknown)
{
  _BYTE *v6; // ecx
  int result; // eax

  result = (int)v6;
  *v6 = 0;
  return result;
}


// 0x004c8be0: S86_7::sub_4C8BE0
// IDA: S86_7::sub_4C8BE0
// Ghidra: ---
void gta2::S86_7_sub_4C8BE0(struct S86_7 *self, wchar_t *a2)
{
  _DWORD *v2; // esi

  v2 = (_DWORD *)self->field_16F8;
  if ( v2 )
  {
    while ( !gta2::sub_4C6110(v2, a2) )
    {
      v2 = (_DWORD *)v2[48];
      if ( !v2 )
        return;
    }
    gta2::sub_4C70F0(v2);
  }
}


// 0x004c8c20: S86_7::PrintText
// IDA: S86_7::PrintText
// Ghidra: ---
int gta2::S86_7_PrintText(struct S86_7 *self, unsigned __int16 *a2, __int16 a3, __int16 a4, __int16 a5, int a6)
{
  struct S86_7 **v7; // esi
  int v8; // ecx

  v7 = (S86_7 **)self->field_16FC;
  v8 = self->field_16F8;
  self->field_16FC = v7[48];
  v7[48] = (struct S86_7 *)v8;
  self->field_16F8 = (int)v7;
  gta2::Font_sub_4C8AA0(v7, (struct HudBrief *)a2, a3, a4, a5, a6);
  gta2::S86_7_sub_4C8BE0(self, (wchar_t *)v7);
  return (int)v7;
}


// 0x004c8c80: S86_7::sub_4C8C80
// IDA: S86_7::sub_4C8C80
// Ghidra: ---
void gta2::S86_7_sub_4C8C80(struct S86_7 *self)
{
  _DWORD *i; // esi

  for ( i = (_DWORD *)self->field_16F8; i; i = (_DWORD *)i[48] )
    gta2::sub_4C8B90(i);
}



