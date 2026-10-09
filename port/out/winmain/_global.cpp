#include "gta2_shim.h"

// Module: winmain, Class: _global
// Functions: 53
// Source: unified (IDA+Ghidra)

// 0x003f1490: FUN_003f1490
// IDA: ---
// Ghidra: FUN_003f1490
void gta2::FUN_003f1490(void *param_1,size_t *param_2,void *param_3,size_t *param_4)
{
  void *in_EAX;
  void *self;
  char *unaff_retaddr;
  
  gta2::SaveGameData(param_1,"test\\replay.rep",in_EAX,param_2);
  gta2::SaveGameData(self,unaff_retaddr,param_3,param_4);
  gta2::FUN_0045f269();
  return;
}


// 0x003f14a8: FUN_003f14a8
// IDA: ---
// Ghidra: FUN_003f14a8
void gta2::FUN_003f14a8(void *param_1,size_t *param_2,void *param_3,size_t *param_4)
{
  void *self;
  char *unaff_retaddr;
  
  gta2::SaveGameData(param_1,"test\\replay.rep",param_1,param_2);
  gta2::SaveGameData(self,unaff_retaddr,param_3,param_4);
  gta2::FUN_0045faff();
  return;
}


// 0x003f1664: FUN_003f1664
// IDA: ---
// Ghidra: FUN_003f1664
void gta2::FUN_003f1664(void *self,undefined4 param_1,undefined4 param_2,undefined4 param_3 )
{
  DAT_00676204 = 0;
  gta2::FUN_004c257f(self,param_1,param_2,param_3);
  return;
}


// 0x00401000: sub_401000
// IDA: sub_401000
// Ghidra: ---
int gta2::sub_401000(void *a1, int a1a)
{
  void *v2; // eax
  int v3; // ecx
  int result; // eax

  v2 = (void *)dword_5D22D4;
  if ( dword_5D22D4 )
  {
    v3 = dword_5D22D8;
  }
  else
  {
    v2 = malloc(0x10000u);
    dword_5D22D4 = (int)v2;
    v3 = 0;
  }
  result = (int)v2 + v3;
  dword_5D22D8 = a1a + v3;
  if ( a1a + v3 == 256 )
    dword_5D22D4 = 0;
  return result;
}


// 0x00401050: sub_401050
// IDA: sub_401050
// Ghidra: ---
int gta2::sub_401050(int a1, int a2)
{
  int result; // eax
  int v3; // ecx
  int v4; // ecx

  result = a1;
  if ( !*(_WORD *)a1 )
  {
    v3 = *(_DWORD *)(a1 + 16);
    if ( v3 )
      *(_DWORD *)(a1 + 16) = a2 + v3;
    v4 = *(_DWORD *)(a1 + 24);
    if ( v4 )
      *(_DWORD *)(a1 + 24) = a2 + v4;
  }
  return result;
}


// 0x00401080: sub_401080
// IDA: sub_401080
// Ghidra: ---
int gta2::sub_401080(int a1, int a2)
{
  int result; // eax
  int v3; // esi
  unsigned __int16 v4; // ax
  int v5; // edx
  bool v6; // zf
  int v7; // ebx
  int v8; // ebp
  int v9; // eax

  result = *(_DWORD *)(a1 + 12);
  if ( result )
  {
    v3 = result + a2;
    *(_DWORD *)(a1 + 12) = result + a2;
    v4 = *(_WORD *)(result + a2);
    v5 = a2 + *(_DWORD *)(v3 + 8);
    v6 = *(_WORD *)v3 == 0;
    *(_DWORD *)(v3 + 8) = v5;
    v7 = v5;
    if ( !v6 )
    {
      v8 = v4;
      do
      {
        gta2::sub_401050(v7, a2);
        v7 += 32;
        --v8;
      }
      while ( v8 );
    }
    v9 = *(_DWORD *)(v3 + 16);
    if ( v9 )
      *(_DWORD *)(v3 + 16) = a2 + v9;
    result = *(_DWORD *)(v3 + 12);
    if ( result )
    {
      result += a2;
      *(_DWORD *)(v3 + 12) = result;
    }
  }
  return result;
}


// 0x004010e0: sub_4010E0
// IDA: sub_4010E0
// Ghidra: ---
unsigned int gta2::sub_4010E0(int a1, int a2, int a3)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  unsigned int result; // eax
  char v8; // cl
  unsigned int v9; // ebx
  int v10; // ebp

  v3 = *(_DWORD *)(a2 + 16);
  if ( v3 )
    *(_DWORD *)(a2 + 16) = a3 + v3;
  v4 = *(_DWORD *)(a2 + 24);
  if ( v4 )
    *(_DWORD *)(a2 + 24) = a3 + v4;
  v5 = *(_DWORD *)(a2 + 20);
  if ( v5 )
  {
    *(_DWORD *)(a2 + 20) = a3 + v5;
    gta2::sub_4010E0(a1, a3 + v5, a3);
  }
  v6 = *(_DWORD *)(a2 + 28);
  if ( v6 )
  {
    *(_DWORD *)(a2 + 28) = a3 + v6;
    gta2::sub_4010E0(a1, a3 + v6, a3);
  }
  result = *(_DWORD *)(a2 + 36);
  if ( result && (v8 = *(_BYTE *)(a2 + 1), result += a3, v9 = 0, *(_DWORD *)(a2 + 36) = result, v8) )
  {
    v10 = result;
    do
    {
      gta2::sub_401080(v10, a3);
      ++v9;
      result = *(unsigned __int8 *)(a2 + 1);
      v10 += 20;
    }
    while ( v9 < result );
    *(_DWORD *)(a2 + 60) = a1;
  }
  else
  {
    *(_DWORD *)(a2 + 60) = a1;
  }
  return result;
}


// 0x00401180: sub_401180
// IDA: sub_401180
// Ghidra: ---
float * gta2::sub_401180(float *a1, float *a2, float *a3)
{
  float *result; // eax

  result = a1;
  *a3 = *a1 * *a2 + a1[2] * a2[8] + a2[4] * a1[1];
  a3[1] = a2[9] * a1[2] + a2[5] * a1[1] + *a1 * a2[1];
  a3[2] = a2[2] * *a1 + a1[2] * a2[10] + a2[6] * a1[1];
  a3[3] = a2[11] * a1[2] + a2[3] * *a1 + a2[7] * a1[1] + a1[3];
  a3[4] = a1[4] * *a2 + a1[6] * a2[8] + a1[5] * a2[4];
  a3[5] = a1[5] * a2[5] + a1[4] * a2[1] + a1[6] * a2[9];
  a3[6] = a1[6] * a2[10] + a1[5] * a2[6] + a2[2] * a1[4];
  a3[7] = a2[11] * a1[6] + a1[5] * a2[7] + a2[3] * a1[4] + a1[7];
  a3[8] = a1[10] * a2[8] + a2[4] * a1[9] + a1[8] * *a2;
  a3[9] = a2[5] * a1[9] + a1[8] * a2[1] + a1[10] * a2[9];
  a3[10] = a1[10] * a2[10] + a2[2] * a1[8] + a2[6] * a1[9];
  a3[11] = a1[8] * a2[3] + a1[10] * a2[11] + a1[9] * a2[7] + a1[11];
  return result;
}


// 0x004012c0: sub_4012C0
// IDA: sub_4012C0
// Ghidra: ---
float * gta2::sub_4012C0(void *a1)
{
  gInt += 12;
  return gta2::sub_401180((float *)(4 * gInt + 5873344), (float *)a1, (float *)(4 * gInt + 5873392));
}


// 0x004012f0: gInt_sub_12
// IDA: gInt_sub_12
// Ghidra: ---
void gInt_sub_12()
{
  gInt -= 12;
}


// 0x00401300: sub_401300
// IDA: sub_401300
// Ghidra: ---
int gta2::sub_401300(int a1, int a2)
{
  int v4; // esi
  int v5; // ecx
  __int16 v6; // fps
  double v7; // st7
  bool v8; // c0
  char v9; // c2
  bool v10; // c3
  __int16 v11; // fps
  double v12; // st7
  bool v13; // c0
  char v14; // c2
  bool v15; // c3
  __int16 FPS; // fps
  bool v17; // c0
  char v18; // c2
  bool v19; // c3
  int result; // eax
  __int16 v21; // fps
  bool v22; // c0
  char v23; // c2
  bool v24; // c3
  float v25; // edx
  float v26; // [esp+18h] [ebp+8h]

  while ( 1 )
  {
    v4 = a1;
    v5 = a2;
    v26 = flt_595EE4[2 * ((a1 + a2) >> 1)];
    do
    {
      v7 = flt_595EE4[2 * v4];
      v8 = v7 < v26;
      v9 = 0;
      v10 = v7 == v26;
      if ( (v6 & 0x4100) == 0 )
      {
        do
        {
          v12 = flt_595EEC[2 * v4];
          v13 = v12 < v26;
          v14 = 0;
          v15 = v12 == v26;
          ++v4;
        }
        while ( (v11 & 0x4100) == 0 );
      }
      v17 = v26 < (double)flt_595EE4[2 * v5];
      v18 = 0;
      v19 = v26 == flt_595EE4[2 * v5];
      result = FPS & 0x4100;
      if ( (FPS & 0x4100) == 0 )
      {
        do
        {
          v22 = v26 < (double)flt_595EDC[2 * v5];
          v23 = 0;
          v24 = v26 == flt_595EDC[2 * v5--];
          result = v21 & 0x4100;
        }
        while ( (v21 & 0x4100) == 0 );
      }
      if ( v4 > v5 )
        break;
      result = dword_595EE0[2 * v4];
      v25 = flt_595EE4[2 * v4];
      dword_595EE0[2 * v4] = dword_595EE0[2 * v5];
      flt_595EE4[2 * v4] = flt_595EE4[2 * v5];
      dword_595EE0[2 * v5] = result;
      flt_595EE4[2 * v5] = v25;
      ++v4;
      --v5;
    }
    while ( v4 <= v5 );
    if ( a1 < v5 )
      result = gta2::sub_401300(a1, v5);
    if ( v4 >= a2 )
      break;
    a1 = v4;
  }
  return result;
}


// 0x004013e0: sub_4013E0
// IDA: sub_4013E0
// Ghidra: ---
int sub_4013E0()
{
  int v0; // edi
  int v1; // ecx
  int v2; // esi
  float *v3; // edx
  __int16 v4; // fps
  double v5; // st7
  bool v6; // c0
  char v7; // c2
  bool v8; // c3
  double v9; // st7
  float *v10; // edx
  __int16 v11; // fps
  double v12; // st7
  bool v13; // c0
  char v14; // c2
  bool v15; // c3
  double v16; // st7
  float *v17; // edx
  __int16 v18; // fps
  double v19; // st7
  bool v20; // c0
  char v21; // c2
  bool v22; // c3
  double v23; // st7
  float *v24; // edx
  __int16 v25; // fps
  double v26; // st7
  bool v27; // c0
  char v28; // c2
  bool v29; // c3
  double v30; // st7
  float *v31; // edx
  __int16 v32; // fps
  double v33; // st7
  bool v34; // c0
  char v35; // c2
  bool v36; // c3
  double v37; // st7

  v0 = dword_5CC2C0;
  v1 = 0;
  if ( dword_5CC2C0 >= 4 )
  {
    v2 = 3;
    do
    {
      v3 = (float *)dword_595EE0[2 * v1];
      if ( v3[10] >= (double)v3[18] )
        v5 = v3[18];
      else
        v5 = v3[10];
      v6 = v5 < v3[2];
      v7 = 0;
      v8 = v5 == v3[2];
      if ( (v4 & 0x4100) != 0 )
      {
        if ( v3[10] >= (double)v3[18] )
          v9 = v3[18];
        else
          v9 = v3[10];
      }
      else
      {
        v9 = v3[2];
      }
      v10 = (float *)dword_595EE8[2 * v1];
      flt_595EE4[2 * v1] = -v9;
      if ( v10[10] >= (double)v10[18] )
        v12 = v10[18];
      else
        v12 = v10[10];
      v13 = v12 < v10[2];
      v14 = 0;
      v15 = v12 == v10[2];
      if ( (v11 & 0x4100) != 0 )
      {
        if ( v10[10] >= (double)v10[18] )
          v16 = v10[18];
        else
          v16 = v10[10];
      }
      else
      {
        v16 = v10[2];
      }
      v17 = (float *)dword_595EF0[2 * v1];
      flt_595EEC[2 * v1] = -v16;
      if ( v17[10] >= (double)v17[18] )
        v19 = v17[18];
      else
        v19 = v17[10];
      v20 = v19 < v17[2];
      v21 = 0;
      v22 = v19 == v17[2];
      if ( (v18 & 0x4100) != 0 )
      {
        if ( v17[10] >= (double)v17[18] )
          v23 = v17[18];
        else
          v23 = v17[10];
      }
      else
      {
        v23 = v17[2];
      }
      v24 = (float *)dword_595EF8[2 * v1];
      flt_595EF4[2 * v1] = -v23;
      if ( v24[10] >= (double)v24[18] )
        v26 = v24[18];
      else
        v26 = v24[10];
      v27 = v26 < v24[2];
      v28 = 0;
      v29 = v26 == v24[2];
      if ( (v25 & 0x4100) != 0 )
      {
        if ( v24[10] >= (double)v24[18] )
          v30 = v24[18];
        else
          v30 = v24[10];
      }
      else
      {
        v30 = v24[2];
      }
      flt_595EFC[2 * v1] = -v30;
      v2 += 4;
      v1 += 4;
    }
    while ( v2 < v0 );
  }
  for ( ; v1 < v0; ++v1 )
  {
    v31 = (float *)dword_595EE0[2 * v1];
    if ( v31[10] >= (double)v31[18] )
      v33 = v31[18];
    else
      v33 = v31[10];
    v34 = v33 < v31[2];
    v35 = 0;
    v36 = v33 == v31[2];
    if ( (v32 & 0x4100) != 0 )
    {
      if ( v31[10] >= (double)v31[18] )
        v37 = v31[18];
      else
        v37 = v31[10];
    }
    else
    {
      v37 = v31[2];
    }
    flt_595EE4[2 * v1] = -v37;
  }
  return gta2::sub_401300(0, v0 - 1);
}


// 0x004015a0: sub_4015A0
// IDA: sub_4015A0
// Ghidra: ---
_WORD * gta2::sub_4015A0(_WORD *self, int a2)
{
  _WORD *result; // eax
  int *v3; // edx

  result = self;
  *self = *(_WORD *)(a2 + 2);
  self[1] = *(_WORD *)(a2 + 4);
  self[2] = *(_WORD *)(a2 + 6);
  self[3] = *(_WORD *)(a2 + 8);
  self[4] = *(_WORD *)(a2 + 10);
  self[5] = *(_WORD *)(a2 + 12);
  self[6] = *(_WORD *)(a2 + 14);
  v3 = *(int **)(a2 + 16);
  if ( v3 )
  {
    *((float *)self + 4) = (double)*v3 * 0.000015258789;
    *((float *)self + 5) = (double)*(int *)(*(_DWORD *)(a2 + 16) + 4) * 0.000015258789;
    *((float *)self + 6) = (double)*(int *)(*(_DWORD *)(a2 + 16) + 8) * 0.000015258789;
    *((float *)self + 7) = (double)*(int *)(*(_DWORD *)(a2 + 16) + 12) * 0.000015258789;
    *((float *)self + 8) = (double)*(int *)(*(_DWORD *)(a2 + 16) + 16) * 0.000015258789;
    *((float *)self + 9) = (double)*(int *)(*(_DWORD *)(a2 + 16) + 20) * 0.000015258789;
  }
  else
  {
    *((_DWORD *)self + 9) = 0;
    *((_DWORD *)self + 8) = 0;
    *((_DWORD *)self + 7) = 0;
    *((_DWORD *)self + 6) = 0;
    *((_DWORD *)self + 5) = 0;
    *((_DWORD *)self + 4) = 0;
  }
  self[7] = *(_WORD *)(a2 + 20);
  *((_DWORD *)self + 10) = *(_DWORD *)(a2 + 28);
  return result;
}


// 0x00401690: sub_401690
// IDA: sub_401690
// Ghidra: ---
_DWORD * gta2::sub_401690(void *self, int a2, _DWORD *a3)
{
  _DWORD *v4; // ecx
  int v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // eax
  int v8; // esi
  unsigned __int16 *v9; // ebp
  unsigned __int16 v10; // ax
  int v11; // esi
  void *v12; // eax
  int v13; // eax
  void *v14; // eax
  int v15; // ecx
  int i; // [esp+20h] [ebp+4h]

  *((_DWORD *)self + 9) = 0;
  *((_DWORD *)self + 32) = a2;
  *(_DWORD *)self = a3[17];
  *((_DWORD *)self + 1) = a3[18];
  *((_DWORD *)self + 2) = a3[19];
  *((_DWORD *)self + 3) = a3[21];
  *((_DWORD *)self + 4) = a3[20];
  *((_DWORD *)self + 5) = a3[22];
  *((_DWORD *)self + 6) = a3[23];
  *((_DWORD *)self + 7) = a3[24];
  *((_DWORD *)self + 8) = a3[25];
  v4 = (_DWORD *)((char *)self + 108);
  *(unsigned __int8 *)&v4[0] = (unsigned __int8)a3[1];
  *(unsigned __int8 *)&v4[1] = (unsigned __int8)a3[2];
  v5 = a3[3];
  *((_DWORD *)self + 11) = 0;
  v4[2] = v5;
  *((_DWORD *)self + 10) = 1065353216;
  *((_DWORD *)self + 12) = 0;
  *((_DWORD *)self + 13) = 0;
  *((_DWORD *)self + 14) = 0;
  *((_DWORD *)self + 15) = 1065353216;
  *((_DWORD *)self + 16) = 0;
  *((_DWORD *)self + 17) = 0;
  *((_DWORD *)self + 18) = 0;
  *((_DWORD *)self + 19) = 0;
  *((_DWORD *)self + 20) = 1065353216;
  *((_DWORD *)self + 21) = 0;
  if ( a3[5] )
  {
    v6 = gta2::operator_new(0x84u);
    if ( v6 )
      *((_DWORD *)self + 30) = (int)(intptr_t)gta2::sub_401690(v6, a2, (_DWORD *)a3[5]);
    else
      *((_DWORD *)self + 30) = 0;
  }
  else
  {
    *((_DWORD *)self + 30) = 0;
  }
  if ( a3[7] )
  {
    v7 = gta2::operator_new(0x84u);
    if ( v7 )
      *((_DWORD *)self + 31) = (int)(intptr_t)gta2::sub_401690(v7, a2, (_DWORD *)a3[7]);
    else
      *((_DWORD *)self + 31) = 0;
  }
  else
  {
    *((_DWORD *)self + 31) = 0;
  }
  v8 = a3[9];
  if ( v8 )
  {
    v9 = *(unsigned __int16 **)(v8 + 12);
    v10 = *v9;
    *((_DWORD *)self + 22) = *v9;
    *((_DWORD *)self + 23) = v9[1];
    *((_DWORD *)self + 24) = v9[2];
    *((_DWORD *)self + 25) = (int)(intptr_t)malloc(4 * (size_t)v10);
    v11 = 0;
    for ( i = *((_DWORD *)v9 + 2); v11 < *((_DWORD *)self + 22); i += 32 )
    {
      v12 = gta2::operator_new(0x2Cu);
      if ( v12 )
        v13 = (int)(intptr_t)(void *)gta2::sub_4015A0((_WORD *)(intptr_t)v12, i);
      else
        v13 = 0;
      *(_DWORD *)(intptr_t)(*((_DWORD *)self + 25) + 4 * v11++) = (int)(intptr_t)(void *)v13;
    }
    v14 = malloc(12 * *((_DWORD *)self + 23));
    v15 = *((_DWORD *)self + 23);
    *((_DWORD *)self + 26) = (int)(intptr_t)v14;
    qmemcpy((void *)(intptr_t)v14, *((const void **)v9 + 3), 12 * (size_t)v15);
  }
  else
  {
    *((_DWORD *)self + 22) = 0;
    *((_DWORD *)self + 23) = 0;
    *((_DWORD *)self + 24) = 0;
  }
  return (_DWORD *)self;
}
// 0x004018a0: deconst_4018A0
// IDA: deconst_4018A0
// Ghidra: ---
LPVOID gta2::deconst_4018A0(LPVOID lpMem, char a2)
{
  if ( (a2 & 1) != 0 )
    free(lpMem);
  return lpMem;
}


// 0x004018c0: sub_4018C0
// IDA: sub_4018C0
// Ghidra: ---
float * gta2::sub_4018C0(void *self, int a2)
{
  float *result; // eax
  int v3; // esi
  float *v4; // edx
  double v5; // st7
  double v6; // st6
  double v7; // st5
  float v8; // [esp+4h] [ebp-30h]
  float v9; // [esp+8h] [ebp-2Ch]
  float v10; // [esp+Ch] [ebp-28h]
  float v11; // [esp+14h] [ebp-20h]
  float v12; // [esp+18h] [ebp-1Ch]
  float v13; // [esp+1Ch] [ebp-18h]
  float v14; // [esp+24h] [ebp-10h]
  float v15; // [esp+28h] [ebp-Ch]
  float v16; // [esp+2Ch] [ebp-8h]

  result = (float *)*((_DWORD *)self + 26);
  v3 = 0;
  v8 = *((float *)self + 10) * *((float *)self + 6);
  v9 = *((float *)self + 11) * *((float *)self + 7);
  v10 = *((float *)self + 12) * *((float *)self + 8);
  v11 = *((float *)self + 14) * *((float *)self + 6);
  v12 = *((float *)self + 15) * *((float *)self + 7);
  v13 = *((float *)self + 16) * *((float *)self + 8);
  v14 = *((float *)self + 18) * *((float *)self + 6);
  v15 = *((float *)self + 19) * *((float *)self + 7);
  v16 = *((float *)self + 20) * *((float *)self + 8);
  if ( *((int *)self + 23) > 0 )
  {
    v4 = (float *)&unk_5CC2CC;
    do
    {
      v5 = *result;
      v6 = result[1];
      v7 = result[2];
      result += 3;
      ++v3;
      v4 += 3;
      *(v4 - 4) = v10 * v7 + v6 * v9 + v5 * v8;
      *(v4 - 3) = v13 * v7 + v6 * v12 + v5 * v11;
      *(v4 - 2) = v7 * v16 + v6 * v15 + v5 * v14;
    }
    while ( v3 < *((_DWORD *)self + 23) );
  }
  return result;
}


// 0x004019a0: sub_4019A0
// IDA: sub_4019A0
// Ghidra: ---
int gta2::sub_4019A0(void *self, int a2)
{
  long double v2; // st7
  long double v3; // rt0
  long double v4; // st6
  long double v5; // st6
  long double v6; // st6
  double v7; // st7
  int result; // eax
  float v9; // [esp+0h] [ebp-1Ch]
  float v10; // [esp+4h] [ebp-18h]
  float v11; // [esp+8h] [ebp-14h]
  float v12; // [esp+Ch] [ebp-10h]
  float v13; // [esp+10h] [ebp-Ch]
  float v14; // [esp+14h] [ebp-8h]
  float v15; // [esp+14h] [ebp-8h]
  float v16; // [esp+18h] [ebp-4h]

  v2 = *((float *)self + 4) * 0.017453292;
  v3 = sin(v2);
  v13 = cos(v2);
  v4 = *((float *)self + 3) * 0.017453292;
  v10 = sin(v4);
  v9 = cos(v4);
  v5 = *((float *)self + 5) * 0.017453292;
  v11 = sin(v5);
  v12 = cos(v5);
  v6 = v11 * v3;
  v14 = v12 * v3;
  *((float *)self + 10) = v12 * v9 + v6 * v10;
  *((float *)self + 11) = v6 * v9 - v12 * v10;
  *((float *)self + 12) = v11 * v13;
  v16 = *(float *)self;
  *((float *)self + 13) = v16;
  *((float *)self + 14) = v10 * v13;
  *((float *)self + 15) = v9 * v13;
  *((float *)self + 16) = -v3;
  v7 = *((float *)self + 1);
  *((float *)self + 17) = *((float *)self + 1);
  *((float *)self + 18) = v14 * v10 - v11 * v9;
  *((float *)self + 19) = v14 * v9 + v11 * v10;
  result = a2;
  *((float *)self + 20) = v12 * v13;
  v15 = *((float *)self + 2);
  *((float *)self + 21) = v15;
  if ( a2 )
  {
    *((float *)self + 13) = v16 * *((float *)self + 6);
    *((float *)self + 17) = v7 * *((float *)self + 7);
    *((float *)self + 21) = v15 * *((float *)self + 8);
  }
  return result;
}


// 0x00401ae0: sub_401AE0
// IDA: sub_401AE0
// Ghidra: ---
void gta2::sub_401AE0(void *self, __int16 a2)
{
  *(_DWORD *)self = (unsigned int)(_DWORD)(a2 << 14);
}


// 0x00401af0: bitShiftLeft1
// IDA: bitShiftLeft1
// Ghidra: ---
ushort gta2::bitShiftLeft1(void *self, int a2)
{
  ushort result; // ax

  result = *(ushort *)self;
  *(_DWORD *)self = (unsigned int)(_DWORD)(a2 << 14);
  return result;
}


// 0x00401b90: sub_401B90
// IDA: sub_401B90
// Ghidra: ---
void * gta2::sub_401B90(void *self, void *a2, _DWORD *a3)
{
  SpriteS1 *v3; // eax

  v3 = (SpriteS1 *)gta2::sub_4D6260((__int64)*(int *)self << 14, (int)*a3);
  gta2::S202_SetToNewVal((S202 *)a2, v3);
  return a2;
}


// 0x00401bd0: sub_401BD0
// IDA: sub_401BD0
// Ghidra: FUN_00401bd0
SpriteS1 * gta2::sub_401BD0(void *self,SpriteS1 *s110,int *param_2)
{
                              // WARNING: Load size is inaccurate
  gta2::S202_SetToNewVal((S202 *)s110,(SpriteS1 *)(*param_2 * *(_DWORD *)self));
  return s110;
}


// 0x00401c80: sub_401C80
// IDA: sub_401C80
// Ghidra: ---
Ped * gta2::sub_401C80(void *self, Ped *pPed)
{
  int v2; // eax
  __int16 a2[2]; // [esp+4h] [ebp-4h] BYREF

  LOWORD(v2) = -*(_WORD *)self;
  *(_DWORD *)a2 = v2;
  gta2::CarSystemManager_sub_401C60((CarSystemManager *)pPed, a2);
  return pPed;
}


// 0x00401cb0: sub_401CB0
// IDA: sub_401CB0
// Ghidra: FUN_00401cb0
CarSystemManager * gta2::sub_401CB0(void *self,CarSystemManager *param_1,GlassInfo *param_2)
{
  void *pvVar1;
  GlassInfo **pS110;
  GlassInfo *pGVar2;
  void *local_4;
  
                              // WARNING: Load size is inaccurate
  pvVar1 = (void *)CONCAT22((short)((uint)param_2 >> 0x10),*(_DWORD *)self);
  pS110 = &param_2;
  pGVar2 = param_2;
  local_4 = self;
  gta2::Decoder_SetValue(&local_4,*(_DWORD *)self);
  pvVar1 = gta2::WorldCoordinateToScreenCoord(pvVar1,pS110,(int *)pGVar2);
  gta2::CarSystemManager_sub_401C40(param_1, (Game *)pvVar1);
  return param_1;
}


// 0x00401cf0: constructor
// IDA: constructor
// Ghidra: ---
int gta2::constructor(void *a1, int a2, int a3, void *a4)
{
  int result; // eax
  int v6; // edi

  result = a3 - 1;
  if ( a3 - 1 >= 0 )
  {
    v6 = a3;
    do
    {
      result = ((int (__thiscall *)(void *))a4)(a1);
      a1 = (char *)a1 + a2;
      --v6;
    }
    while ( v6 );
  }
  return result;
}


// 0x00401d50: sub_401D50
// IDA: sub_401D50
// Ghidra: ---
int gta2::sub_401D50(void *self, int a2, int a3, char a4, char *a5)
{
  int v5; // ebx
  int v6; // ebp
  char v7; // di
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  int v10; // esi
  int *v11; // ebx
  unsigned int v12; // edi
  int v13; // ecx
  int *v14; // edi
  int v15; // eax
  int v16; // edi
  _DWORD *v17; // eax
  _DWORD *v18; // eax
  int v19; // edx
  int v20; // edx
  int v21; // edi
  unsigned __int16 *v22; // ecx
  int v23; // eax
  SIZE_T v24; // edi
  int v25; // esi
  void *v26; // ecx
  int v27; // edi
  int v28; // eax
  _DWORD *v29; // ecx
  int v30; // edx
  int v31; // edi
  int v32; // edx
  int v33; // ecx
  int v34; // eax
  unsigned __int16 v35; // di
  _WORD *v36; // eax
  void *v37; // eax
  int v38; // ecx
  int v39; // ecx
  void *v40; // eax
  int result; // eax
  int v42; // [esp+8h] [ebp-67Ch]
  int v43; // [esp+18h] [ebp-66Ch]
  int v44; // [esp+1Ch] [ebp-668h]
  _DWORD **v45; // [esp+20h] [ebp-664h]
  int v46; // [esp+20h] [ebp-664h]
  int v47; // [esp+24h] [ebp-660h]
  int v48; // [esp+28h] [ebp-65Ch]
  signed int v49; // [esp+28h] [ebp-65Ch]
  char Buffer[4]; // [esp+2Ch] [ebp-658h] BYREF
  int v51; // [esp+30h] [ebp-654h]
  SIZE_T dwBytes; // [esp+38h] [ebp-64Ch]
  DWORD v53; // [esp+3Ch] [ebp-648h]
  DWORD nNumberOfBytesToRead; // [esp+40h] [ebp-644h]
  int v55; // [esp+44h] [ebp-640h]
  int v56; // [esp+4Ch] [ebp-638h]
  LONG Offset; // [esp+50h] [ebp-634h]
  LONG lDistanceToMove; // [esp+58h] [ebp-62Ch]
  LONG v59; // [esp+68h] [ebp-61Ch]
  _WORD v60[752]; // [esp+78h] [ebp-60Ch] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v61; // [esp+678h] [ebp-Ch]
  void *v62; // [esp+67Ch] [ebp-8h]
  int v63; // [esp+680h] [ebp-4h]

  v63 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v62 = &loc_4E39AE;
  v61 = ExceptionList;
  v44 = v5;
  v43 = v6;
  v10 = gta2::sub_4D935C((LPCSTR)a2, 0x8000, v7);
  gta2::_ReadFile1(v10, (unsigned int)Buffer, 0x4Cu);
  v11 = (int *)malloc(nNumberOfBytesToRead + v55 + v53 + v56 + 4 * v51 + 76);
  v12 = (unsigned int)&v11[v51 + 19];
  gta2::_lseek(v10, 0, 0);
  gta2::_ReadFile1(v10, (unsigned int)v11, 4 * v51 + 76);
  if ( lDistanceToMove )
  {
    gta2::_lseek(v10, lDistanceToMove, 0);
    gta2::_ReadFile1(v10, v12, nNumberOfBytesToRead);
    v11[11] = v12;
    v12 += nNumberOfBytesToRead;
  }
  if ( Offset )
  {
    gta2::_lseek(v10, Offset, 0);
    gta2::_ReadFile1(v10, v12, v53);
    v13 = v12 - Offset;
    v47 = 0;
    v48 = v12 - Offset;
    if ( v11[1] > 0 )
    {
      v14 = v11 + 18;
      while ( 1 )
      {
        v42 = v13 + *v14;
        *v14 = v42;
        gta2::sub_4010E0((int)v11, v42, v13);
        ++v14;
        if ( ++v47 >= v11[1] )
          break;
        v13 = v48;
      }
    }
  }
  v15 = v11[1];
  *(_DWORD *)self = v15;
  *((_DWORD *)self + 4) = (int)(intptr_t)malloc(4 * (size_t)v15);
  v16 = 0;
  if ( *(int *)self > 0 )
  {
    v45 = (_DWORD **)(v11 + 18);
    do
    {
      v17 = gta2::operator_new(0x84u);
      v63 = 0;
      if ( v17 )
        v18 = gta2::sub_401690(v17, (int)self, *v45);
      else
        v18 = 0;
      v19 = *((_DWORD *)self + 4);
      v63 = -1;
      *(_DWORD *)(v19 + 4 * v16++) = (int)(intptr_t)v18;
      ++v45;
    }
    while ( v16 < *(_DWORD *)self );
  }
  v49 = nNumberOfBytesToRead >> 5;
  *((_DWORD *)self + 1) = nNumberOfBytesToRead >> 5;
  memset(v60, 0, 0x200u);
  v20 = 0;
  if ( v49 > 0 )
  {
    v21 = *((_DWORD *)self + 1);
    v22 = (unsigned __int16 *)(v11[11] + 4);
    do
    {
      if ( v20 < *(v22 - 1) )
        v20 = *(v22 - 1);
      v23 = *v22;
      if ( v20 < v23 )
        v20 = *v22;
      v22 += 16;
      --v21;
      v60[v23] = 1;
    }
    while ( v21 );
  }
  v46 = v20 + 1;
  v24 = (v20 + 1) << 16;
  *((_DWORD *)self + 3) = (int)(intptr_t)malloc((size_t)v24);
  gta2::_lseek(v10, v59, 0);
  gta2::_ReadFile1(v10, *((_DWORD *)self + 3), v24);
  v25 = 0;
  if ( v46 > 0 )
  {
    do
    {
      if ( v60[v25] )
      {
        v26 = (void *)*((_DWORD *)self + 3);
        v27 = (int)v26 + 4 * *(unsigned __int8 *)(v11[11] + 18) - 4;
        v28 = gta2::sub_401000(v26, 4);
        *(_DWORD *)&v60[2 * v25 + 256] = v28;
        v29 = (_DWORD *)v28;
        v30 = v27 - v28;
        v31 = 256;
        do
        {
          *v29 = *(_DWORD *)((char *)v29 + v30);
          v29 += 64;
          --v31;
        }
        while ( v31 );
        gta2::gbh_RegisterPalette(v29, &word_58F510, &v28);
        v25 = v44;
        v32 = 0;
        if ( *((int *)self + 1) > 0 )
        {
          v33 = 0;
          do
          {
            v34 = v11[11];
            v35 = *(_WORD *)(v33 + v34 + 4);
            v36 = (_WORD *)(v33 + v34 + 4);
            if ( v35 == v44 )
              *v36 = word_58F510;
            ++v32;
            v33 += 32;
          }
          while ( v32 < *((_DWORD *)self + 1) );
        }
        --word_58F510;
      }
      v44 = ++v25;
      v46 += 0x4000;
    }
    while ( v25 < v43 );
  }
  v37 = malloc(dwBytes);
  v38 = *((_DWORD *)self + 1);
  *((_DWORD *)self + 2) = (int)(intptr_t)v37;
  if ( v38 > 0 )
  {
    do
    {
      v39 = v11[11];
      v40 = (void *)gta2::gbh_RegisterTexture(
                      *(unsigned __int16 *)(v39 + 14),
                      *(unsigned __int16 *)(v39 + 16),
                      *((_DWORD *)self + 3)
                    + *(unsigned __int8 *)(v39 + 12)
                    + ((*(unsigned __int8 *)(v39 + 13) + (*(unsigned __int16 *)(v39 + 2) << 8)) << 8));
      qmemcpy(*((void **)self + 2), v40, 0x20u);
      gta2::gbh_FreeTexture((GLuint *)v40);
    }
    while ( *((int *)self + 1) > 1 );
  }
  gta2::free_0(v11);
  result = (int)self;
  flt_599EF0[0] = 1.0;
  flt_599EF4[0] = 0.0;
  flt_599EF8[0] = 0.0;
  flt_599EFC[0] = 0.0;
  flt_599F00[0] = 0.0;
  flt_599F04[0] = 1.0;
  flt_599F08[0] = 0.0;
  flt_599F0C[0] = 0.0;
  flt_599F10[0] = 0.0;
  flt_599F14[0] = 0.0;
  flt_599F18[0] = 1.0;
  flt_599F1C[0] = 0.0;
  gInt = 0;
  return result;
}


// 0x00402180: sub_402180
// IDA: sub_402180
// Ghidra: FUN_00402180
void gta2::sub_402180(void *self)
{
  void *this_00;
  int iVar1;
  
  if (*(void **)((int)self + 0x78) != NULL) {
    gta2::FUN_004021e0(*(void **)((int)self + 0x78),1);
  }
  if (*(void **)((int)self + 0x7c) != NULL) {
    gta2::FUN_004021e0(*(void **)((int)self + 0x7c),1);
  }
  iVar1 = 0;
  if (0 < *(int *)((int)self + 0x58)) {
    do {
      this_00 = *(void **)(*(int *)((int)self + 100) + iVar1 * 4);
      if (this_00 != NULL) {
        gta2::Pool_Allocate(this_00,1);
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < *(int *)((int)self + 0x58));
  }
  free(*(void **)((int)self + 0x68));
  *(undefined4 *)((int)self + 0x68) = 0;
  return;
}


// 0x004021e0: sub_4021E0
// IDA: sub_4021E0
// Ghidra: FUN_004021e0
void * gta2::sub_4021E0(void *self,byte param_1)
{
  gta2::FUN_00402180(self);
  if ((param_1 & 1) != 0) {
    free(self);
  }
  return self;
}


// 0x00402200: sub_402200
// IDA: sub_402200
// Ghidra: FUN_00402200
void gta2::sub_402200(void *self,float *param_1,float param_2,float param_3,float param_4 )
{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  float *this_00;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  do {
    this_00 = (float *)self;
    fVar1 = param_2 + this_00[3];
    this_00[3] = fVar1;
    if (360.0 < fVar1) {
      this_00[3] = fVar1 - 360.0;
    }
    if (this_00[3] < 0.0 != (this_00[3] != this_00[3])) {
      this_00[3] = this_00[3] + 360.0;
    }
    fVar1 = param_3 + this_00[4];
    this_00[4] = fVar1;
    if (360.0 < fVar1) {
      this_00[4] = fVar1 - 360.0;
    }
    if (this_00[4] < 0.0 != (this_00[4] != this_00[4])) {
      this_00[4] = this_00[4] + 360.0;
    }
    fVar1 = param_4 + this_00[5];
    this_00[5] = fVar1;
    if (360.0 < fVar1) {
      this_00[5] = fVar1 - 360.0;
    }
    if (this_00[5] < 0.0 != (this_00[5] != this_00[5])) {
      this_00[5] = this_00[5] + 360.0;
    }
    if (param_1 != NULL) {
      fVar1 = *this_00;
      fVar2 = this_00[1];
      fVar3 = this_00[2];
      *this_00 = fVar1 * param_1[10] +
                 fVar2 * param_1[0xb] + fVar3 * param_1[0xc];
      this_00[1] = fVar1 * param_1[0xe] +
                   fVar2 * param_1[0xf] + fVar3 * param_1[0x10];
      this_00[2] = fVar1 * param_1[0x12] +
                   fVar2 * param_1[0x13] + fVar3 * param_1[0x14];
    }
    gta2::Pool_Init(this_00,(int)param_1);
    gta2::Renderer_SetTransform(this_00 + 10);
    gta2::Pool_Free(this_00);
    puVar6 = (undefined4 *)&DAT_005cc2c8;
    puVar7 = (undefined4 *)(intptr_t)this_00[0x1a];
    for (uVar4 = (int)this_00[0x17] * 3 & 0x3fffffff; uVar4 != 0;
        uVar4 = uVar4 - 1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
    this_00[3] = 0.0;
    this_00[4] = 0.0;
    this_00[5] = 0.0;
    if ((void *)(intptr_t)this_00[0x1e] != NULL) {
      gta2::FUN_00402200((void *)(intptr_t)this_00[0x1e],this_00,param_2,param_3,param_4);
    }
    gta2::Renderer_Reset();
    self = (void *)(intptr_t)this_00[0x1f];
    param_1 = this_00;
  } while ((void *)(intptr_t)this_00[0x1f] != NULL);
  return;
}


// 0x004023a0: sub_4023A0
// IDA: sub_4023A0
// Ghidra: ---
int gta2::sub_4023A0(void *self, float a2, float a3, float a4)
{
  flt_599EFC[0] = 0.0;
  flt_599F0C[0] = 0.0;
  flt_599F1C[0] = 0.0;
  gta2::sub_402200(self, 0, a2, a3, a4);
  return 0;
}


// 0x004023e0: sub_4023E0
// IDA: sub_4023E0
// Ghidra: FUN_004023e0
void gta2::sub_4023E0(void *self)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float *pfVar26;
  int iVar27;
  float *pfVar28;
  float10 fVar29;
  CameraOrPhysics *pCameraOrPhysics;
  
  pCameraOrPhysics = gCameraOrPhysics;
  iVar27 = 0;
  fVar1 = *(float *)((int)self + 0x18);
  fVar2 = *(float *)(&DAT_00599ef0 + gBufferSize[0xdd8] * 4);
  pfVar26 = *(float **)((int)self + 0x68);
  fVar3 = *(float *)(&DAT_00599ef4 + gBufferSize[0xdd8] * 4);
  fVar4 = *(float *)((int)self + 0x1c);
  fVar5 = *(float *)(&DAT_00599ef8 + gBufferSize[0xdd8] * 4);
  fVar6 = *(float *)((int)self + 0x20);
  fVar7 = *(float *)(&DAT_00599efc + gBufferSize[0xdd8] * 4);
  fVar8 = *(float *)(&DAT_00599f00 + gBufferSize[0xdd8] * 4);
  fVar9 = *(float *)((int)self + 0x18);
  fVar10 = *(float *)(&DAT_00599f04 + gBufferSize[0xdd8] * 4);
  fVar11 = *(float *)((int)self + 0x1c);
  fVar12 = *(float *)(&DAT_00599f08 + gBufferSize[0xdd8] * 4);
  fVar13 = *(float *)((int)self + 0x20);
  fVar14 = *(float *)(&DAT_00599f0c + gBufferSize[0xdd8] * 4);
  fVar15 = *(float *)(&DAT_00599f10 + gBufferSize[0xdd8] * 4);
  fVar16 = *(float *)((int)self + 0x18);
  fVar17 = *(float *)(&DAT_00599f14 + gBufferSize[0xdd8] * 4);
  fVar18 = *(float *)((int)self + 0x1c);
  fVar19 = *(float *)(&DAT_00599f18 + gBufferSize[0xdd8] * 4);
  fVar20 = *(float *)((int)self + 0x20);
  fVar21 = *(float *)(&DAT_00599f1c + gBufferSize[0xdd8] * 4);
  pfVar28 = (float *)(&DAT_005cc2c8 + gBufferSize[0xdd4] * 0xc);
  if (0 < *(int *)((int)self + 0x5c)) {
    do {
      fVar22 = *pfVar26;
      fVar23 = pfVar26[1];
      fVar24 = pfVar26[2];
      pfVar26 = pfVar26 + 3;
      if (fVar22 < _DAT_00599ee0) {
        _DAT_00599ee0 = fVar22;
      }
      if (fVar23 < _DAT_00599ee4) {
        _DAT_00599ee4 = fVar23;
      }
      if (fVar24 < _DAT_00599ee8) {
        _DAT_00599ee8 = fVar24;
      }
      if (_DAT_005cc2b0 < fVar22 != ((_DAT_005cc2b0 != _DAT_005cc2b0) || (fVar22 != fVar22))) {
        _DAT_005cc2b0 = fVar22;
      }
      if (_DAT_005cc2b4 < fVar23 != ((_DAT_005cc2b4 != _DAT_005cc2b4) || (fVar23 != fVar23))) {
        _DAT_005cc2b4 = fVar23;
      }
      if (_DAT_005cc2b8 < fVar24 != ((_DAT_005cc2b8 != _DAT_005cc2b8) || (fVar24 != fVar24))) {
        _DAT_005cc2b8 = fVar24;
      }
      fVar25 = -1.0 / (fVar22 * fVar15 * fVar16 +
                       fVar23 * fVar17 * fVar18 + fVar24 * fVar19 * fVar20 +
                      fVar21);
      pfVar28[2] = fVar25;
      fVar29 = gta2::PedStats_EncodedFloatToRegularFloat(&pCameraOrPhysics->HalfWidth);
      *pfVar28 = (float)((float10)(uint)pCameraOrPhysics->ScreenY +
                        -(((float10)fVar22 * (float10)(fVar1 * fVar2) +
                           (float10)fVar23 * (float10)(fVar3 * fVar4) +
                           (float10)fVar24 * (float10)(fVar5 * fVar6) +
                          (float10)fVar7) * fVar29 * (float10)fVar25));
      fVar29 = gta2::PedStats_EncodedFloatToRegularFloat(&pCameraOrPhysics->HalfWidth);
      iVar27 = iVar27 + 1;
      pfVar28[1] = (float)((float10)(uint)pCameraOrPhysics->ScreenH +
                          -(((float10)fVar22 * (float10)(fVar8 * fVar9) +
                             (float10)fVar23 * (float10)(fVar10 * fVar11) +
                             (float10)fVar24 * (float10)(fVar12 * fVar13) +
                            (float10)fVar14) * fVar29 * (float10)fVar25));
      pfVar28 = pfVar28 + 3;
    } while (iVar27 < *(int *)((int)self + 0x5c));
  }
  return;
}


// 0x00402660: sub_402660
// IDA: sub_402660
// Ghidra: ---
int gta2::sub_402660(void *self, void *a2)
{
  int v2; // ebx
  int v5; // eax
  int v6; // ebp
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // ebp
  int v11; // eax
  int v12; // ebp
  double v13; // st7
  int v14; // eax
  double v15; // st6
  double v16; // st6
  __int16 v17; // fps
  double v18; // st7
  bool v19; // c0
  char v20; // c2
  bool v21; // c3
  int v22; // ebx
  void *v23; // ecx
  int result; // eax
  int v25; // [esp+14h] [ebp+4h]

  v2 = dword_5D22C8;
  while ( 1 )
  {
    *((_DWORD *)self + 7) = dword_5CC2BC;
    *((_DWORD *)self + 6) = dword_5CC2BC;
    *((_DWORD *)self + 8) = dword_5CC2BC;
    gta2::sub_4019A0(self, (int)a2);
    gta2::sub_4012C0((char *)self + 40);
    gta2::sub_4023E0(self);
    v5 = 0;
    v25 = 0;
    if ( *((int *)self + 22) > 0 )
    {
      v6 = dword_5CC2C0;
      v7 = 100 * dword_5CC2C0 + 5874360;
      while ( 1 )
      {
        v8 = *(_DWORD *)(*((_DWORD *)self + 25) + 4 * v5);
        dword_595EE0[2 * v6] = v7 - 8;
        *(_DWORD *)(v7 + 88) = *(_DWORD *)(*((_DWORD *)self + 32) + 8) + 32 * *(unsigned __int16 *)(v8 + 14);
        v9 = 12 * (v2 + *(__int16 *)(v8 + 2)) + 6079176;
        *(_DWORD *)(v7 - 8) = dword_5CC2C8[3 * v2 + 3 * *(__int16 *)(v8 + 2)];
        v10 = *(_DWORD *)(v9 + 4);
        *(float *)v7 = -*(float *)(v9 + 8);
        *(_DWORD *)(v7 - 4) = v10;
        *(_DWORD *)(v7 + 16) = *(_DWORD *)(v8 + 16);
        *(_DWORD *)(v7 + 20) = *(_DWORD *)(v8 + 20);
        v11 = 12 * (v2 + *(__int16 *)(v8 + 4)) + 6079176;
        *(_DWORD *)(v7 + 24) = dword_5CC2C8[3 * v2 + 3 * *(__int16 *)(v8 + 4)];
        v12 = *(_DWORD *)(v11 + 4);
        *(float *)(v7 + 32) = -*(float *)(v11 + 8);
        *(_DWORD *)(v7 + 28) = v12;
        *(_DWORD *)(v7 + 48) = *(_DWORD *)(v8 + 24);
        *(_DWORD *)(v7 + 52) = *(_DWORD *)(v8 + 28);
        v13 = *(float *)&dword_5CC2C8[3 * v2 + 3 * *(__int16 *)(v8 + 6)];
        v14 = 12 * (v2 + *(__int16 *)(v8 + 6)) + 6079176;
        *(float *)(v7 + 56) = *(float *)&dword_5CC2C8[3 * v2 + 3 * *(__int16 *)(v8 + 6)];
        v15 = *(float *)(v14 + 4);
        *(float *)(v7 + 60) = *(float *)(v14 + 4);
        *(float *)(v7 + 64) = -*(float *)(v14 + 8);
        v16 = v15 - *(float *)(v7 + 28);
        *(_DWORD *)(v7 + 80) = *(_DWORD *)(v8 + 32);
        *(_DWORD *)(v7 + 84) = *(_DWORD *)(v8 + 36);
        v18 = v16 * (*(float *)(v7 + 24) - *(float *)(v7 - 8))
            - (v13 - *(float *)(v7 + 24)) * (*(float *)(v7 + 28) - *(float *)(v7 - 4));
        v19 = v18 < 0.0;
        v20 = 0;
        v21 = v18 == 0.0;
        if ( (v17 & 0x100) == 0
          && *(_WORD *)(32 * *(unsigned __int16 *)(v8 + 14) + *(_DWORD *)(*((_DWORD *)self + 32) + 8) + 14) )
        {
          v7 += 100;
          ++dword_5CC2C0;
        }
        v5 = ++v25;
        if ( v25 >= *((_DWORD *)self + 22) )
          break;
        v6 = dword_5CC2C0;
      }
    }
    v22 = *((_DWORD *)self + 23) + v2;
    v23 = (void *)*((_DWORD *)self + 30);
    dword_5D22C8 = v22;
    if ( v23 )
    {
      gta2::sub_402660(v23, self);
      v22 = dword_5D22C8;
    }
    v2 = v22 - *((_DWORD *)self + 23);
    dword_5D22C8 = v2;
    gInt_sub_12();
    result = *((_DWORD *)self + 31);
    if ( !result )
      break;
    a2 = self;
    self = (void *)*((_DWORD *)self + 31);
  }
  return result;
}


// 0x00402840: sub_402840
// IDA: sub_402840
// Ghidra: ---
int gta2::sub_402840(void *self)
{
  int v2; // esi
  CameraOrPhysics *v3; // ebx
  double v4; // st7
  __int16 v5; // fps
  bool v6; // c0
  char v7; // c2
  bool v8; // c3
  double v9; // st6
  __int16 v10; // fps
  bool v11; // c0
  char v12; // c2
  bool v13; // c3
  __int16 v14; // fps
  bool v15; // c0
  char v16; // c2
  bool v17; // c3
  int result; // eax
  float v19; // [esp+Ch] [ebp-8h]
  float v20; // [esp+10h] [ebp-4h]

  v2 = 0;
  flt_599EE0 = 0.0;
  flt_599EE4 = 0.0;
  flt_599EE8 = 0.0;
  flt_5CC2B0 = 0.0;
  flt_5CC2B4 = 0.0;
  flt_5CC2B8 = 0.0;
  *((_DWORD *)self + 2) = 1086324736;
  v3 = gCameraOrPhysics;
  dword_5D22C8 = 0;
  dword_5CC2C0 = 0;
  flt_599EFC[0] = -gta2::Float10_EncodedFloatToRegularFloat((int *)&gCameraOrPhysics->cameraPosTarget_[3].Player);
  flt_599F0C[0] = -gta2::Float10_EncodedFloatToRegularFloat(&v3->cameraPosTarget_[3].field_20);
  flt_599F1C[0] = gta2::Float10_EncodedFloatToRegularFloat(&v3->cameraPosTarget_[3].field_24);
  gta2::sub_402660(self, 0);
  v20 = flt_5CC2B0 - flt_599EE0;
  v19 = flt_5CC2B4 - flt_599EE4;
  v4 = flt_5CC2B8 - flt_599EE8;
  v6 = v19 < v4;
  v7 = 0;
  v8 = v19 == v4;
  if ( (v5 & 0x4100) != 0 )
    v9 = v4;
  else
    v9 = v19;
  v11 = v20 < v9;
  v12 = 0;
  v13 = v20 == v9;
  if ( (v10 & 0x4100) != 0 )
  {
    v15 = v19 < v4;
    v16 = 0;
    v17 = v19 == v4;
    if ( (v14 & 0x4100) == 0 )
      v4 = v19;
  }
  else
  {
    v4 = v20;
  }
  *(float *)&dword_5CC2BC = 1.0 / v4;
  result = sub_4013E0();
  if ( dword_5CC2C0 > 0 )
  {
    do
    {
      gta2::gbh_DrawTriangle(16389, *(_DWORD *)(dword_595EE0[2 * v2] + 96), dword_595EE0[2 * v2], 255);
      result = dword_5CC2C0;
      ++v2;
    }
    while ( v2 < dword_5CC2C0 );
  }
  return result;
}


// 0x00402980: fread
// IDA: fread
// Ghidra: ---
size_t fread(const void *lpBuffer, size_t a2, size_t a3, FILE *a4)
{
  FILE *v4; // eax
  size_t v5; // edx
  size_t v6; // ecx

  return gta2::_fread(lpBuffer, v5, v6, v4);
}


// 0x004029a0: Write1Kb_File
// IDA: Write1Kb_File
// Ghidra: FUN_004029a0
int gta2::Write1Kb_File(const void *Buffer,size_t param_2,size_t param_3,FILE *param_4)
{
  return gta2::FID_conflict___fwrite_lk(Buffer,param_2,param_3,param_4);
}


// 0x004029c0: sub_4029C0
// IDA: sub_4029C0
// Ghidra: FUN_004029c0
long sub_4029C0(FILE *param_1)
{
  long _Offset;
  int iVar1;
  long lVar2;
  
  _Offset = gta2::_ftell(param_1);
  if (_Offset == -1) {
    gta2::DebugLog(0xd,"File.cpp",0x38);
  }
  iVar1 = gta2::_fseek(param_1,0,2);
  if (iVar1 != 0) {
    gta2::DebugLog(0xe,"File.cpp",0x3a);
  }
  lVar2 = gta2::_ftell(param_1);
  if (lVar2 == -1) {
    gta2::DebugLog(0xd,"File.cpp",0x3c);
  }
  iVar1 = gta2::_fseek(param_1,_Offset,0);
  if (iVar1 != 0) {
    gta2::DebugLog(0xe,"File.cpp",0x3e);
  }
  return lVar2;
}


// 0x00402a60: sub_402A60
// IDA: sub_402A60
// Ghidra: ---
char gta2::sub_402A60(char a1)
{
  sprintf(gStr, "%c:", a1);
  return 1;
}


// 0x00402a80: sub_402A80
// IDA: sub_402A80
// Ghidra: ---
FILE * gta2::sub_402A80(LPCSTR lpFileName, int a2)
{
  const CHAR *v2; // edi
  FILE *v3; // esi
  int v4; // eax
  FILE *result; // eax
  const CHAR *v6; // [esp-24h] [ebp-2Ch]
  int v7; // [esp-14h] [ebp-1Ch]

  v2 = v6;
  v3 = gta2::FileMgr_WriteReadFile(v6, "rb");
  if ( !v3 )
    gta2::debug_log(0x48u, "File.cpp", 109);
  if ( sub_4029C0(v3) != v7 )
    gta2::debug_log(0x48u, "File.cpp", 113);
  v4 = fclose(v3);
  *(_DWORD *)&stru_5D22FC.gap2D8[32] = 0;
  if ( v4 )
    gta2::debug_log(0x48u, "File.cpp", 118);
  result = gta2::FileMgr_WriteReadFile(v2, "wb");
  if ( result )
    return (FILE *)gta2::debug_log(0x48u, "File.cpp", 122);
  return result;
}


// 0x00402b20: ReadFileContent
// IDA: ReadFileContent
// Ghidra: ---
void * gta2::ReadFileContent(LPCSTR lpFileName)
{
  FILE *file; // esi
  void *Buffer; // esi
  FILE *v3; // edi
  const char *v5; // [esp-30h] [ebp-38h]
  SIZE_T *v6; // [esp-20h] [ebp-28h]
  size_t v7; // [esp-1Ch] [ebp-24h]
  size_t v8; // [esp-18h] [ebp-20h]
  FILE *v9; // [esp-14h] [ebp-1Ch]

  gta2::FileMgr_SetFilePath(v5);
  file = gta2::FileMgr_WriteReadFile(v5, "rb");
  if ( !file )
    gta2::debug_log(0x10u, "File.cpp", 146);
  *v6 = sub_4029C0(file);
  if ( fclose(file) )
    gta2::debug_log(0x11u, "File.cpp", 150);
  Buffer = gta2::createBuffer(*v6);
  v3 = gta2::FileMgr_WriteReadFile(v5, "rb");
  if ( !v3 )
  {
    gta2::free_0(Buffer);
    gta2::debug_log(0x10u, "File.cpp", 156);
  }
  if ( fread(Buffer, v7, v8, v9) != 1 )
  {
    gta2::free_0(Buffer);
    fclose(v3);
    gta2::debug_log(0xFu, "File.cpp", 163);
  }
  if ( fclose(v3) )
  {
    gta2::free_0(Buffer);
    gta2::debug_log(0x11u, "File.cpp", 169);
  }
  return Buffer;
}


// 0x00402c20: sub_402C20
// IDA: sub_402C20
// Ghidra: ---
unsigned int gta2::sub_402C20(LPCSTR lpFileName, int a2, int a3)
{
  FILE *v3; // esi
  unsigned int v4; // edi
  const char *v6; // [esp-24h] [ebp-2Ch]
  size_t v7; // [esp-1Ch] [ebp-24h]
  size_t v8; // [esp-18h] [ebp-20h]
  FILE *v9; // [esp-14h] [ebp-1Ch]
  unsigned int *v10; // [esp-10h] [ebp-18h]
  const void *v11; // [esp-8h] [ebp-10h]

  gta2::FileMgr_SetFilePath(v6);
  v3 = gta2::FileMgr_WriteReadFile(v6, "rb");
  if ( !v3 )
    gta2::debug_log(0x10u, "File.cpp", 197);
  v4 = sub_4029C0(v3);
  if ( v4 > *v10 )
  {
    fclose(v3);
    gta2::debug_log(0x3FEu, "File.cpp", 203);
  }
  if ( fread(v11, v7, v8, v9) != 1 )
  {
    fclose(v3);
    gta2::debug_log(0xFu, "File.cpp", 209);
  }
  if ( fclose(v3) )
    gta2::debug_log(0x11u, "File.cpp", 213);
  return v4;
}


// 0x00402cf0: WriteSub_402CF0
// IDA: WriteSub_402CF0
// Ghidra: ---
int gta2::WriteSub_402CF0(LPCSTR lpFileName, void *NameMap, int *a3)
{
  FILE *v3; // esi
  int result; // eax
  const char *v5; // [esp-24h] [ebp-2Ch]
  _DWORD *v6; // [esp-1Ch] [ebp-24h]
  size_t v7; // [esp-18h] [ebp-20h]
  size_t v8; // [esp-14h] [ebp-1Ch]
  FILE *v9; // [esp-10h] [ebp-18h]
  const void *v10; // [esp-8h] [ebp-10h]

  gta2::FileMgr_SetFilePath(v5);
  if ( !*v6 )
    gta2::debug_log(0x13u, "File.cpp", 233);
  v3 = gta2::FileMgr_WriteReadFile(v5, "wb");
  if ( !v3 )
    gta2::debug_log(0x10u, "File.cpp", 236);
  if ( gta2::Write1Kb_File(v10, v7, v8, v9) != 1 )
  {
    fclose(v3);
    gta2::debug_log(0x14u, "File.cpp", 242);
  }
  result = fclose(v3);
  if ( result )
    return (int)(intptr_t)gta2::debug_log(0x11u, "File.cpp", 246);
  return result;
}


// 0x00402da0: ARWBinarySub_402DA0
// IDA: ARWBinarySub_402DA0
// Ghidra: ---
int gta2::ARWBinarySub_402DA0(LPCSTR lpFileName, int a2, int a3)
{
  FILE *v3; // esi
  int result; // eax
  const char *v5; // [esp-24h] [ebp-2Ch]
  _DWORD *v6; // [esp-1Ch] [ebp-24h]
  size_t v7; // [esp-18h] [ebp-20h]
  size_t v8; // [esp-14h] [ebp-1Ch]
  FILE *v9; // [esp-10h] [ebp-18h]
  const void *v10; // [esp-8h] [ebp-10h]

  gta2::FileMgr_SetFilePath(v5);
  if ( !*v6 )
    gta2::debug_log(0x13u, "File.cpp", 266);
  v3 = gta2::FileMgr_WriteReadFile(v5, "ab");
  if ( !v3 )
    gta2::debug_log(0x10u, "File.cpp", 269);
  if ( gta2::Write1Kb_File(v10, v7, v8, v9) != 1 )
  {
    fclose(v3);
    gta2::debug_log(0x14u, "File.cpp", 275);
  }
  result = fclose(v3);
  if ( result )
    return (int)(intptr_t)gta2::debug_log(0x11u, "File.cpp", 279);
  return result;
}


// 0x00402e50: sub_402E50
// IDA: sub_402E50
// Ghidra: ---
int gta2::sub_402E50(LPCSTR lpFileName)
{
  FILE *v1; // esi
  int result; // eax
  const char *v3; // [esp-10h] [ebp-14h]

  gta2::FileMgr_SetFilePath(v3);
  v1 = gta2::FileMgr_WriteReadFile(v3, "wb");
  if ( !v1 )
    gta2::debug_log(0x10u, "File.cpp", 301);
  result = fclose(v1);
  if ( result )
    return (int)(intptr_t)gta2::debug_log(0x11u, "File.cpp", 305);
  return result;
}


// 0x00402ef0: sub_402EF0
// IDA: sub_402EF0
// Ghidra: ---
bool sub_402EF0()
{
  return (*(_BYTE *)(*(_DWORD *)&stru_5D22FC.gap2D8[28] + 12) & 0x10) != 0;
}


// 0x00402f00: CloseFileStream
// IDA: CloseFileStream
// Ghidra: ---
int CloseFileStream()
{
  int result; // eax

  result = *(_DWORD *)&stru_5D22FC.gap2D8[32];
  if ( *(_DWORD *)&stru_5D22FC.gap2D8[32] )
  {
    result = fclose(*(FILE **)&stru_5D22FC.gap2D8[28]);
    *(_DWORD *)&stru_5D22FC.gap2D8[32] = 0;
  }
  return result;
}


// 0x00402f30: error
// IDA: error
// Ghidra: ---
int gta2::error(UINT uExitCode, int a2, int a3)
{
  UINT v4; // [esp-8h] [ebp-8h]

  CloseFileStream();
  return (int)(intptr_t)gta2::debug_log(v4, "File.cpp", 403);
}


// 0x00403040: FUN_00403040
// IDA: ---
// Ghidra: FUN_00403040
uint FUN_00403040(size_t param_1,uint *param_2)
{
  long _Offset;
  int iVar1;
  long lVar2;
  void *unaff_ESI;
  size_t unaff_EDI;
  
  if (gBufferSize[0x1159] == 0) {
    gta2::DebugLog(0x15,"File.cpp",0x1ec);
  }
  _Offset = gta2::_ftell((FILE *)gBufferSize[0x1158]);
  if (_Offset == -1) {
    gta2::ErrorLine(0xd);
  }
  iVar1 = gta2::_fseek((FILE *)gBufferSize[0x1158],0,2);
  if (iVar1 != 0) {
    gta2::ErrorLine(0xe);
  }
  lVar2 = gta2::_ftell((FILE *)gBufferSize[0x1158]);
  if (lVar2 == -1) {
    gta2::ErrorLine(0xd);
  }
  iVar1 = gta2::_fseek((FILE *)gBufferSize[0x1158],_Offset,0);
  if (iVar1 != 0) {
    gta2::ErrorLine(0xe);
  }
  if (*param_2 < (uint)(lVar2 - _Offset)) {
    gta2::ErrorLine(0x3fe);
  }
  iVar1 = gBufferSize[0x1158];
  gta2::Fread((void *)0x1,param_1,unaff_EDI,unaff_ESI);
  if (iVar1 != 1) {
    gta2::ErrorLine(0xf);
  }
  return lVar2 - _Offset;
}


// 0x00403130: GetNextSignificantChar
// IDA: GetNextSignificantChar
// Ghidra: ---
char gta2::GetNextSignificantChar(FILE *Stream)
{
  char result; // al

  while ( 1 )
  {
    result = gta2::getc(Stream);
    if ( ((int)Stream[3]._Placeholder & 0x10) != 0 || result == 10 )
      break;
    if ( result != ' ' && result != '\r' && result != '\t' )
      return result;
  }
  return 0;
}


// 0x004031c0: InitGraphicsAndInput
// IDA: InitGraphicsAndInput
// Ghidra: ---
void gta2::InitGraphicsAndInput(HINSTANCE pInstance, _DWORD *a2)
{
  int v2; // esi
  unsigned int v3; // eax
  HMODULE LibraryA; // eax
  HMODULE v5; // esi
  FARPROC DirectInputCreateA; // ebx
  HMODULE v7; // eax
  HMODULE v8; // esi
  int (__stdcall *DirectDrawCreate)(void *, LPDIRECTDRAW *, struct IUnknown *); // eax
  void *v10; // eax
  HMODULE v11; // eax
  HMODULE v12; // ebp
  FARPROC ProcAddress; // edi
  int (__stdcall ***v14)(_DWORD, void *, char *); // eax
  int (__stdcall ***v15)(_DWORD, void *, _DWORD *); // eax
  int v16; // [esp+44h] [ebp-124h]
  void *v17; // [esp+54h] [ebp-114h] BYREF
  int v18; // [esp+58h] [ebp-110h]
  int (__stdcall ***v19)(_DWORD, void *, int *); // [esp+5Ch] [ebp-10Ch] BYREF
  int v20; // [esp+60h] [ebp-108h]
  int v21; // [esp+64h] [ebp-104h] BYREF
  char v22[4]; // [esp+68h] [ebp-100h] BYREF
  _DWORD v23[63]; // [esp+6Ch] [ebp-FCh] BYREF

  v17 = 0;
  v19 = 0;
  v18 = 0;
  v20 = 0;
  v21 = 0;
  v23[26] = 148;
  if ( !GetVersionExA((LPOSVERSIONINFOA)&v23[26]) )
  {
    *(_DWORD *)pInstance = 0;
    *a2 = 0;
    return;
  }
  v16 = v2;
  if ( v23[30] == 2 )
  {
    v3 = v23[27];
    *a2 = 2;
    if ( v3 < 4 )
    {
      *a2 = 0;
      return;
    }
    if ( v3 == 4 )
    {
      *(_DWORD *)pInstance = 512;
      LibraryA = LoadLibraryA("DINPUT.DLL");
      v5 = LibraryA;
      if ( !LibraryA )
      {
        OutputDebugStringA("Couldn't LoadLibrary DInput\r\n");
        return;
      }
      DirectInputCreateA = GetProcAddress(LibraryA, "DirectInputCreateA");
      FreeLibrary(v5);
      if ( DirectInputCreateA )
      {
        *(_DWORD *)pInstance = 768;
        return;
      }
      goto LABEL_24;
    }
  }
  else
  {
    *a2 = 1;
  }
  v7 = LoadLibraryA("DDRAW.DLL");
  v8 = v7;
  if ( !v7 )
  {
    *(_DWORD *)pInstance = 0;
    *a2 = 0;
    FreeLibrary(0);
    return;
  }
  DirectDrawCreate = (int (__stdcall *)(void *, LPDIRECTDRAW *, struct IUnknown *))GetProcAddress(v7, "DirectDrawCreate");
  if ( !DirectDrawCreate )
  {
    *(_DWORD *)pInstance = 0;
    *a2 = 0;
    FreeLibrary(v8);
    OutputDebugStringA("Couldn't LoadLibrary DDraw\r\n");
    return;
  }
  if ( DirectDrawCreate(0, (LPDIRECTDRAW *)&v17, 0) < 0 )
  {
    *(_DWORD *)pInstance = 0;
    *a2 = 0;
    FreeLibrary(v8);
    OutputDebugStringA("Couldn't create DDraw\r\n");
    return;
  }
  v10 = v17;
  *(_DWORD *)pInstance = 256;
  if ( (*(int (__stdcall **)(void *, void *, void *, int))v10)(v10, &unk_577C74, &v19, v16) < 0 )
  {
    (*(void (__cdecl **)(int))(*(_DWORD *)v18 + 8))(v18);
    FreeLibrary(v8);
    OutputDebugStringA("Couldn't QI DDraw2\r\n");
    return;
  }
  (*(void (__stdcall **)(int))(*(_DWORD *)v20 + 8))(v20);
  *(_DWORD *)pInstance = 512;
  v11 = LoadLibraryA("DINPUT.DLL");
  v12 = v11;
  if ( !v11 )
  {
    OutputDebugStringA("Couldn't LoadLibrary DInput\r\n");
    (*(void (__cdecl **)(int))(*(_DWORD *)v18 + 8))(v18);
    FreeLibrary(v8);
    return;
  }
  ProcAddress = GetProcAddress(v11, "DirectInputCreateA");
  FreeLibrary(v12);
  if ( !ProcAddress )
  {
    FreeLibrary(v8);
    (*(void (__cdecl **)(int))(*(_DWORD *)v18 + 8))(v18);
LABEL_24:
    OutputDebugStringA("Couldn't GetProcAddress DInputCreate\r\n");
    return;
  }
  *(_DWORD *)pInstance = 768;
  memset(v23, 0, 0x6Cu);
  v23[0] = 108;
  v23[1] = 1;
  v23[26] = 512;
  if ( (*(int (__stdcall **)(int, _DWORD, int))(*(_DWORD *)v18 + 80))(v18, 0, 8) >= 0 )
  {
    if ( (*(int (__stdcall **)(int, _DWORD *, int (__stdcall ****)(_DWORD, void *, int *), _DWORD))(*(_DWORD *)v18 + 24))(
           v18,
           v23,
           &v19,
           0) >= 0 )
    {
      if ( (*(int (__stdcall **)(void *, void *, void *))v19)(v19, &unk_577C24, &v21) < 0
        || (v14 = (int (__stdcall ***)(_DWORD, void *, char *))v19,
            *(_DWORD *)pInstance = 1280,
            (*(int (__stdcall **)(void *, void *, void *))v14)(v14, &unk_577C14, v22) < 0) )
      {
        (*(void (__cdecl **)(int))(*(_DWORD *)v18 + 8))(v18);
        FreeLibrary(v8);
      }
      else
      {
        v15 = (int (__stdcall ***)(_DWORD, void *, _DWORD *))v19;
        *(_DWORD *)pInstance = 1536;
        ((void (__cdecl *)(int (__stdcall ***)(_DWORD, void *, _DWORD *)))(*v15)[2])(v15);
        (*(void (__stdcall **)(void *))((_DWORD **)v17)[2])(v17);
        FreeLibrary(v8);
        gta2::sub_44DB50();
        if ( unk_5E96FC == 1537 )
          *(_DWORD *)pInstance = 1537;
      }
    }
    else
    {
      (*(void (__cdecl **)(int))(*(_DWORD *)v18 + 8))(v18);
      FreeLibrary(v8);
      *(_DWORD *)pInstance = 0;
      OutputDebugStringA("Couldn't CreateSurface\r\n");
    }
  }
  else
  {
    (*(void (__cdecl **)(int))(*(_DWORD *)v18 + 8))(v18);
    FreeLibrary(v8);
    *(_DWORD *)pInstance = 0;
    OutputDebugStringA("Couldn't Set coop level\r\n");
  }
}


// 0x004035a0: SetgByte5
// IDA: SetgByte5
// Ghidra: ---
void SetgByte5(void *self)
{
  gByte5 = 1;
}


// 0x00403780: JustCopyByPtrAtoC
// IDA: JustCopyByPtrAtoC
// Ghidra: ---
SpriteS1 * gta2::JustCopyByPtrAtoC(void *self, void *a2)
{
  gta2::S202_SetToNewVal((S202 *)a2, (SpriteS1 *)(intptr_t)(-(*(_DWORD *)self)));
  return (SpriteS1 *)a2;
}


// 0x00403870: sub_403870
// IDA: sub_403870
// Ghidra: FUN_00403870
void gta2::sub_403870(void *self)
{
  SpawnPoint **pAutoClass4;
  int extraout_EDX;
  int iVar1;
  
  SetgByte5(self);
  pAutoClass4 = (SpawnPoint **)(intptr_t)&gSpawnPoint;
  iVar1 = 20;
  do {
    gta2::S169_S169((struct S169 *)pAutoClass4);
    pAutoClass4 = (SpawnPoint **)(intptr_t)(extraout_EDX + 0x44);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// 0x004038c0: sub_4038C0
// IDA: sub_4038C0
// Ghidra: ---
int gta2::sub_4038C0(struct S801 *self)
{
  int v1; // edx

  gta2::S169_S169((S169 *)self);
  return v1;
}


// 0x00403d50: sub_403D50
// IDA: sub_403D50
// Ghidra: FUN_00403d50
void gta2::sub_403D50(int param_1)
{
  char cVar1;
  int iVar2;
  
  gta2::Ped_SetDefault(*(Ped **)(param_1 + 0x2c));
  gta2::Ped_sub_4411B0(*(Ped **)(param_1 + 0x2c));
  cVar1 = '\0';
  if (*(char *)(param_1 + 0x34) != '\0') {
    iVar2 = 0;
    do {
      gta2::Ped_SetDefault(*(Ped **)(param_1 + 4 + iVar2 * 4));
      gta2::Ped_sub_4411B0(*(Ped **)(param_1 + 4 + iVar2 * 4));
      cVar1 = cVar1 + '\x01';
      iVar2 = (int)cVar1;
    } while (iVar2 < (int)(uint)*(byte *)(param_1 + 0x34));
  }
  *(undefined1 *)(param_1 + 0x40) = 0;
  return;
}



























