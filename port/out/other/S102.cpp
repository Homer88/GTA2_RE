#include "gta2_shim.h"

// Module: other, Class: S102
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x0048a5a0: S102::sub_48A5A0
// IDA: S102::sub_48A5A0
// Ghidra: ---
int gta2::S102_sub_48A5A0(struct S102 *self)
{
  unsigned __int8 v2; // dl
  unsigned __int8 v3; // cl
  S101 *v4; // eax
  int result; // eax
  unsigned __int8 v6; // [esp+13h] [ebp-9h]
  unsigned __int8 v7; // [esp+14h] [ebp-8h]
  unsigned __int8 v8; // [esp+18h] [ebp-4h]

  v2 = 0;
  v3 = 0;
  v6 = 99;
  v8 = 99;
  v7 = 0;
  do
  {
    if ( *(&self->S101_[40].field + v7) == 1 )
    {
      v4 = &self->S101_[v7];
      switch ( *(_DWORD *)&v4->field_10 )
      {
        case 2:
        case 3:
        case 4:
        case 0x15:
        case 0x1F:
        case 0x22:
          goto LABEL_12;
        case 5:
        case 0x1C:
        case 0x1D:
        case 0x1E:
          v2 = 2;
          goto LABEL_13;
        case 0xC:
        case 0xE:
        case 0xF:
          v2 = 5;
          goto LABEL_13;
        case 0xD:
          v2 = 4;
          goto LABEL_13;
        case 0x10:
        case 0x11:
          v2 = 6;
          goto LABEL_13;
        case 0x12:
        case 0x21:
          if ( *(_WORD *)&v4->field_1A >= 0x52u )
            goto LABEL_12;
          v2 = 3;
          goto LABEL_13;
        case 0x13:
        case 0x14:
        case 0x20:
          if ( *(_WORD *)&v4->field_1A < 0x32u )
            goto LABEL_11;
LABEL_12:
          if ( v2 != 1 )
            goto LABEL_13;
          goto LABEL_17;
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x19:
LABEL_11:
          v2 = 3;
LABEL_13:
          if ( v2 < v6 )
          {
            v6 = v2;
            v8 = v3;
          }
          break;
        default:
LABEL_17:
          result = v7;
          *(_WORD *)&self->S101_[v7].field_1A = 0;
          return result;
      }
    }
    v7 = ++v3;
  }
  while ( v3 < 0x28u );
  result = v8;
  *(_WORD *)&self->S101_[v8].field_1A = 0;
  return result;
}


// 0x0048a6c0: S102::sub_48A6C0
// IDA: S102::sub_48A6C0
// Ghidra: ---
S101 * gta2::S102_sub_48A6C0(struct S102 *self)
{
  char v1; // bl
  S101 *result; // eax
  S101 *v4; // edi
  __int16 v5; // ax
  unsigned __int8 v6; // [esp+10h] [ebp-4h]

  v1 = 0;
  v6 = 0;
  while ( *(&self->S101_[40].field + v6) )
  {
    v6 = ++v1;
    if ( (unsigned __int8)v1 >= 0x14u )
    {
      gta2::S102_sub_48A5A0(self);
      v1 = 0;
      v6 = 0;
      while ( *(&self->S101_[40].field + v6) )
      {
        v6 = ++v1;
        if ( (unsigned __int8)v1 >= 0x28u )
          return 0;
      }
      break;
    }
  }
  v4 = &self->S101_[v6];
  gta2::sub_48A550(v4);
  v5 = word_593220;
  v4->field_4 = v1;
  *(_WORD *)&v4->field_6 = v5;
  word_593220 = v5 + 1;
  *(_DWORD *)&v4->field = 0;
  result = v4;
  *(&self->S101_[40].field + v6) = 1;
  return result;
}


// 0x0048a7b0: S102::S102
// IDA: S102::S102
// Ghidra: ---
S102 * gta2::S102_S102(struct S102 *self)
{
  char v2; // al
  char *v3; // edx
  char *v4; // ecx
  S102 *result; // eax

  gta2::Construct(self, 48, 40, S101::S101, S101::S101_des);
  v2 = 0;
  v3 = &self->field_780;
  v4 = &self->S101_[0].field_4;
  do
  {
    *v4 = v2;
    *v3 = 0;
    ++v2;
    v4 += 48;
    ++v3;
  }
  while ( (unsigned __int8)v2 < 40u );
  result = self;
  unk_669E80 = 0;
  return result;
}



