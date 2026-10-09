#include "gta2_shim.h"

// Module: other, Class: S115
// Functions: 6
// Source: unified (IDA+Ghidra)

// 0x00464c40: S115::sub_464C40
// IDA: S115::sub_464C40
// Ghidra: FUN_00464c40
int gta2::S115_sub_464C40(int *param_1)
{
  int iVar1;
  
  iVar1 = *param_1;
  *param_1 = *(int *)(iVar1 + 0x1c);
  *(undefined4 *)(iVar1 + 0x1c) = 0;
  FUN_00463f50();
  return iVar1;
}


// 0x00469010: S115::sub_469010
// IDA: S115::sub_469010
// Ghidra: FUN_00469010
DamageInfo * gta2::S115_sub_469010(DamageInfo *param_1,undefined4 param_2,undefined4 param_3, undefined4 param_4,undefined4 param_5,uint param_6)
{
  DamageInfo *self;
  
  self = (DamageInfo *)FUN_00464c40();
  *(undefined4 *)&self->field_0x8 = param_2;
  self->S116_ = param_1;
  *(undefined4 *)&self->field_0xc = param_3;
  self->select = param_4;
  *(undefined4 *)self = 0x10000;
  FUN_00463f10(self,param_5);
  gta2::S116_sub_45B2D0(self,param_6);
  self->field_0x18 = (char)param_6;
  FUN_00461360();
  return self;
}


// 0x00469070: S115::sub_469070
// IDA: S115::sub_469070
// Ghidra: FUN_00469070
void gta2::S115_sub_469070(DamageInfo *param_1,undefined1 param_2,undefined1 param_3, undefined1 param_4)
{
  param_1->field_0x16 = param_4;
  param_1->field_0x14 = param_2;
  param_1->field_0x15 = param_3;
  param_1->field_0x17 = param_3;
  gta2::S116_sub_45B2D0(param_1,0);
  FUN_00464c60(param_1);
  return;
}


// 0x0047f450: S115::sub_47F450
// IDA: S115::sub_47F450
// Ghidra: ---
void gta2::S115_sub_47F450(struct S115 *self, _DWORD *a2)
{
  int v3; // esi
  int v4; // edi
  S116 *FirstElement; // edx

  v3 = self->field_4;
  v4 = 0;
  if ( v3 )
  {
    while ( (_DWORD *)v3 != a2 )
    {
      v4 = v3;
      v3 = *(_DWORD *)(v3 + 28);
      if ( !v3 )
        return;
    }
    gta2::sub_45B320((void *)v3);
    if ( v4 )
    {
      *(_DWORD *)(v4 + 28) = *(_DWORD *)(v3 + 28);
      *(_DWORD *)(v3 + 28) = self->FirstElement;
    }
    else
    {
      FirstElement = self->FirstElement;
      self->field_4 = *(_DWORD *)(v3 + 28);
      *(_DWORD *)(v3 + 28) = FirstElement;
    }
    self->FirstElement = (S116 *)v3;
  }
}


// 0x0047f4b0: S115::sub_47F4B0
// IDA: S115::sub_47F4B0
// Ghidra: ---
S116 * gta2::S115_sub_47F4B0(struct S115 *self, S116 *a2)
{
  S116 *result; // eax

  gta2::sub_45B320(a2);
  result = self->FirstElement;
  a2->NextElement = self->FirstElement;
  self->FirstElement = a2;
  return result;
}


// 0x0047f4f0: S115::sub_47F4F0
// IDA: S115::sub_47F4F0
// Ghidra: ---
void gta2::S115_sub_47F4F0(struct S115 *self, S65 *a2)
{
  gta2::S65_sub_4613B0(a2);
  if ( LOBYTE(a2[2].field_4) )
    gta2::S115_sub_47F450(self, a2);
  else
    gta2::S115_sub_47F4B0(self, (S116 *)a2);
}



