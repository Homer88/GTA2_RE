#include "gta2_shim.h"

// Module: other, Class: S166
// Functions: 15
// Source: unified (IDA+Ghidra)

// 0x004c6290: S166::sub_4C6290
// IDA: S166::sub_4C6290
// Ghidra: ---
int gta2::S166_sub_4C6290(struct S166 *self)
{
  int result; // eax

  result = self->S167_[0].field_0;
  if ( self->S167_[0].field_0 >= 0 )
  {
    self->S167_[0].field_0 = --result;
    if ( result == -1 )
      self->S167_[0].field_4 = 0;
  }
  return result;
}


// 0x004c62b0: S166::sub_4C62B0
// IDA: S166::sub_4C62B0
// Ghidra: ---
int gta2::S166_sub_4C62B0(S166 *a1)
{
  int result; // eax
  int v2; // ecx
  int v3; // edx

  do
  {
    result = gta2::S166_sub_4C6290(a1);
    a1 = (struct S166 *)(v2 + 12);
  }
  while ( v3 != 1 );
  return result;
}


// 0x004c7120: S166::sub_4C7120
// IDA: S166::sub_4C7120
// Ghidra: ---
void gta2::S166_sub_4C7120(struct S166 *self, int a2)
{
  self->S167_[0].field_0 = a2;
}


// 0x004c7160: S166::sub_4C7160
// IDA: S166::sub_4C7160
// Ghidra: ---
bool gta2::S166_sub_4C7160(struct S166 *self)
{
  return self->S167_[0].field_4 == 0;
}


// 0x004c7170: S166::sub_4C7170
// IDA: S166::sub_4C7170
// Ghidra: ---
bool gta2::S166_sub_4C7170(struct S166 *self)
{
  return self->S167_[0].field_0 < 0;
}


// 0x004c7250: S166::sub_4C7250
// IDA: S166::sub_4C7250
// Ghidra: ---
int gta2::S166_sub_4C7250(struct S166 *self, __int16 param_1)
{
  unsigned __int16 GlobalSpriteId; // ax

  GlobalSpriteId = gta2::Style_GetGlobalSpriteId(gStyle, 6, param_1);
  return (unsigned __int8)gta2::sub_4C6C90(gStyle, GlobalSpriteId);
}


// 0x004c9040: S166::sub_4C9040
// IDA: S166::sub_4C9040
// Ghidra: GarageInfo::FUN_004c9040
void gta2::S166_sub_4C9040(GarageInfo *self,byte param_1,byte param_2)
{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  int3 extraout_var;
  int3 extraout_var_00;
  int3 extraout_var_01;
  undefined3 extraout_var_02;
  int3 extraout_var_03;
  int3 extraout_var_04;
  int3 extraout_var_05;
  GarageInfo *pGVar4;
  GarageInfo *this_00;
  struct SpriteS1 *extraout_ECX;
  struct SpriteS1 *extraout_ECX_00;
  struct Hud *pHud1;
  undefined2 extraout_var_06;
  struct SpriteS1 *pSVar5;
  struct SpriteS1 *extraout_ECX_01;
  struct Hud *pHud;
  GarageInfo *this_01;
  GarageInfo *this_02;
  undefined2 extraout_var_07;
  struct SpriteS1 *extraout_ECX_02;
  struct Hud *this_03;
  undefined2 extraout_var_08;
  struct SpriteS1 *extraout_ECX_03;
  struct Hud *this_04;
  struct SpriteS1 *extraout_ECX_04;
  struct SpriteS1 *extraout_ECX_05;
  struct Hud *this_05;
  GarageInfo *this_06;
  struct SpriteS1 *extraout_ECX_06;
  struct SpriteS1 *extraout_ECX_07;
  struct Hud *this_07;
  undefined2 extraout_var_09;
  struct SpriteS1 *extraout_ECX_08;
  struct Hud *this_08;
  int iVar6;
  undefined3 in_stack_00000005;
  undefined3 in_stack_00000009;
  struct SpriteS1 *pSVar7;
  
  iVar6 = self->CarGenerator[0].field0_0x0;
  if (iVar6 < 0) {
    pGVar4 = self;
    if (self->CarGenerator[0].field1_0x4 == 0) {
      return;
    }
  }
  else {
    pGVar4 = (GarageInfo *)self->CarGenerator[0].field1_0x4;
    if (pGVar4 != NULL) {
      uVar1 = gta2::S166_sub_4C7250(pGVar4,0x75);
      uVar2 = gta2::S166_sub_4C7250(this_01,0x76);
      uVar3 = gta2::S166_sub_4C7250(this_02,0x77);
      pSVar5 = (struct SpriteS1 *)CONCAT22(extraout_var_07,_DAT_00672f98);
      iVar6 = CONCAT31(extraout_var_03,uVar3) - ((int)extraout_var_03 >> 0x17)
              >> 1;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffd0,
                 (int)_param_2 +
                 (-iVar6 - (CONCAT31(extraout_var_01,uVar1) -
                            ((int)extraout_var_01 >> 0x17) >> 1)));
      pSVar7 = extraout_ECX_02;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffcc,(int)_param_1);
      gta2::Hud_DrawSprite(this_03,6,(void *)0x75,pSVar7,pSVar5);
      pSVar5 = (struct SpriteS1 *)CONCAT22(extraout_var_08,_DAT_00672f98);
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffd0,(int)_param_2);
      pSVar7 = extraout_ECX_03;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffcc,(int)_param_1);
      gta2::Hud_DrawSprite(this_04,6,(void *)0x77,pSVar7,pSVar5);
      pSVar5 = extraout_ECX_04;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffd0,
                 (int)_param_2->Matrix3DArray +
                 CONCAT31(extraout_var_02,uVar2) / 2 + iVar6 + -4);
      pSVar7 = extraout_ECX_05;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffcc,(int)_param_1);
      gta2::Hud_DrawSprite(this_05,6,(void *)0x76,pSVar7,pSVar5);
      gta2::Hud_DrawSprite(self,_param_1,
                 (int)((int)&_param_2[-1].Matrix3DArray[0x13a6].field19_0x34 + 2
                      ));
      gta2::GarageInfo_FUN_004c8e30(self,_param_1,
                 (struct SpriteS1 *)((int)&_param_2->Matrix3DArray[0].SpriteS1 + 2));
      return;
    }
    pGVar4 = NULL;
    if (-1 < iVar6) {
      uVar1 = gta2::S166_sub_4C7250(NULL,0x75);
      uVar2 = gta2::S166_sub_4C7250(this_06,0x76);
      pSVar5 = extraout_ECX_06;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffd0,
                 (int)_param_2 -
                 (CONCAT31(extraout_var_04,uVar1) -
                  ((int)extraout_var_04 >> 0x17) >> 1));
      pSVar7 = extraout_ECX_07;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffcc,(int)_param_1);
      gta2::Hud_DrawSprite(this_07,6,(void *)0x75,pSVar7,pSVar5);
      pSVar5 = (struct SpriteS1 *)CONCAT22(extraout_var_09,_DAT_00672f98);
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffd0,
                 (int)_param_2->Matrix3DArray +
                 (CONCAT31(extraout_var_05,uVar2) -
                  ((int)extraout_var_05 >> 0x17) >> 1) + -4);
      pSVar7 = extraout_ECX_08;
      gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffcc,(int)_param_1);
      gta2::Hud_DrawSprite(this_08,6,(void *)0x76,pSVar7,pSVar5);
      gta2::GarageInfo_FUN_004c8e30(self,_param_1,_param_2);
      return;
    }
  }
  uVar1 = gta2::S166_sub_4C7250(pGVar4,0x75);
  uVar2 = gta2::S166_sub_4C7250(this_00,0x76);
  pSVar5 = extraout_ECX;
  gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffd0,
             (int)_param_2 -
             (CONCAT31(extraout_var,uVar1) - ((int)extraout_var >> 0x17) >> 1));
  pSVar7 = extraout_ECX_00;
  gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffcc,(int)_param_1);
  gta2::Hud_DrawSprite(pHud1,6,(void *)0x75,pSVar7,pSVar5);
  pSVar5 = (struct SpriteS1 *)CONCAT22(extraout_var_06,_DAT_00672f98);
  gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffd0,
             (int)_param_2->Matrix3DArray +
             (CONCAT31(extraout_var_00,uVar2) - ((int)extraout_var_00 >> 0x17)
             >> 1) + -4);
  pSVar7 = extraout_ECX_01;
  gta2::S202_sub_41F980((struct SpriteS1 *)&stack0xffffffcc,(int)_param_1);
  gta2::Hud_DrawSprite(pHud,6,(void *)0x76,pSVar7,pSVar5);
  gta2::Hud_DrawSprite(self,_param_1,(int)_param_2);
  return;
}


// 0x004c92a0: S166::sub_4C92A0
// IDA: S166::sub_4C92A0
// Ghidra: ---
int gta2::S166_sub_4C92A0(struct S166 *self)
{
  int v2; // esi
  struct S166 *v3; // ecx
  int v4; // esi
  struct S166 *v5; // ecx
  int v6; // esi
  int v7; // kr00_4
  int v8; // eax
  int v9; // ebx
  int result; // eax
  int v11; // [esp+10h] [ebp-4h]

  v2 = gta2::S166_sub_4C7250(self, 119);
  v4 = gta2::S166_sub_4C7250(v3, 118) + v2;
  v6 = gta2::S166_sub_4C7250(v5, 117) + v4;
  v7 = gta2::sub_4C7220(117);
  v8 = -(gta2::MapGm_GetGang(&gMapGm) != 0);
  v11 = 4;
  LOBYTE(v8) = v8 & 0xBC;
  v9 = v8 + 104;
  do
  {
    gta2::S166_sub_4C9040(self, (struct SpriteS1 *)(v7 / 2 + 3), v9);
    v9 += v6;
    self = (struct S166 *)((char *)self + 12);
    result = --v11;
  }
  while ( v11 );
  return result;
}


// 0x004c9310: S166::sub_4C9310
// IDA: S166::sub_4C9310
// Ghidra: ---
int gta2::S166_sub_4C9310(struct S166 *self, int a2)
{
  int v2; // esi

  v2 = 0;
  while ( !gta2::S166_sub_4C7170(self) || !gta2::S166_sub_4C7160(self) )
  {
    ++v2;
    self = (struct S166 *)((char *)self + 12);
    if ( v2 >= 4 )
      return -1;
  }
  gta2::S166_sub_4C7120(self, 30 * a2);
  return v2;
}


// 0x004c9360: S166::sub_4C9360
// IDA: S166::sub_4C9360
// Ghidra: GarageInfo::FUN_004c9360
int gta2::S166_sub_4C9360(GarageInfo *self,undefined4 param_2)
{
  byte bVar1;
  bool bVar2;
  CarGenerator *this_00;
  int iVar3;
  int iVar4;
  
  iVar4 = -1;
  iVar3 = 0;
  this_00 = self->CarGenerator;
  do {
    bVar1 = gta2::GarageInfo_Get_004c7160((GarageInfo *)this_00);
    if (bVar1 != 0) {
      bVar2 = gta2::GarageInfo_Get_004c7170((GarageInfo *)this_00);
      if ((!bVar2) || (iVar4 == -1)) {
        iVar4 = iVar3;
      }
    }
    iVar3 = iVar3 + 1;
    this_00 = this_00 + 1;
  } while (iVar3 < 4);
  FUN_004c7130(self->CarGenerator + iVar4,param_2);
  return iVar4;
}


// 0x004c93b0: S166::sub_4C93B0
// IDA: S166::sub_4C93B0
// Ghidra: ---
int gta2::S166_sub_4C93B0(struct S166 *self, int a2)
{
  return (int)gta2::S167_sub_45B010(&self->S167_[a2]);
}


// 0x004c93d0: S166::sub_4C93D0
// IDA: S166::sub_4C93D0
// Ghidra: FUN_004c93d0
void gta2::S166_sub_4C93D0(void *self,int param_2)
{
  gta2::S167_sub_45AFF0((CarGenerator *)((int)self + param_2 * 0xc));
  return;
}


// 0x004c93f0: S166::sub_4C93F0
// IDA: S166::sub_4C93F0
// Ghidra: ---
void gta2::S166_sub_4C93F0(struct S166 *self, int arg0, int a2)
{
  gta2::S167_sub_4C7180(&self->S167_[arg0], a2);
}


// 0x004c9410: S166::sub_4C9410
// IDA: S166::sub_4C9410
// Ghidra: FUN_004c9410
void gta2::S166_sub_4C9410(void *self)
{
  int in_stack_00000004;
  
  gta2::S167_sub_45B000((CarGenerator *)((int)self + in_stack_00000004 * 0xc));
  return;
}


// 0x004ca660: S166::S166
// IDA: S166::S166
// Ghidra: ---
S166 * gta2::S166_S166(struct S166 *self)
{
  gta2::Construct(self, 12, 4, S167::S167, S167::S167_Des);
  return self;
}



