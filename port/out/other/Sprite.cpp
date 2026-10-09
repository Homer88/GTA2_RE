#include "gta2_shim.h"

// Module: other, Class: Sprite
// Functions: 4
// Source: unified (IDA+Ghidra)

// 0x004b99d0: Sprite::FUN_004b99d0
// IDA: ---
// Ghidra: Sprite::FUN_004b99d0
void gta2::Sprite_FUN_004b99d0(Sprite *self)
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = self->field1_0x4;
  puVar3 = self->field3_0xc;
  for (iVar1 = 0x13; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return;
}


// 0x004bd250: Sprite::FUN_004bd250
// IDA: ---
// Ghidra: Sprite::FUN_004bd250
void gta2::Sprite_FUN_004bd250(Sprite *self)
{
  undefined4 in_EAX;
  undefined2 uVar1;
  
  uVar1 = (undefined2)((uint)in_EAX >> 0x10);
  gta2::SpriteS1_sub_4BCBD0((SpriteS1 *)self);
  if (*(char *)&((SpriteS1 *)self->field1_0x4)->Matrix3DArray[1].SpriteS3 ==
      '\0') {
    gta2::SpriteS1_sub_4BBD40((SpriteS1 *)self->field1_0x4,self->Point2D1,
               *(undefined4 *)&self->field_0x18,self->Point2D,
               CONCAT22(uVar1,(short)self->field0_0x0));
  }
  gta2::SpriteS3_sub_4BC580((SpriteS1 *)self->field1_0x4);
  gta2::MapRelatedStruct_IsMapEdge(gMapRelatedStruct,(char)self->Point2D);
  return;
}


// 0x004bdf20: Sprite::FUN_004bdf20
// IDA: sub_4BDF20
// Ghidra: Sprite::FUN_004bdf20
void gta2::Sprite_FUN_004bdf20(Sprite *self,undefined4 param_1,SpriteS1 *pSpriteS1)
{
  Sprite *this_00;
  Model *this_01;
  int *piVar1;
  int local_c [2];
  undefined1 local_4 [4];
  SpriteS1 *pSpriteS1_1;
  SpriteS1 *pSpriteS1_2;
  SpriteS1 *pSpriteS1_3;
  
  pSpriteS1_1 = pSpriteS1;
  piVar1 = local_c;
  pSpriteS1_2 = (SpriteS1 *)&pSpriteS1;
  local_c[0] = 2;
  pSpriteS1_3 = pSpriteS1;
  this_01 = (Model *)gta2::JustCopyByPtrAtoC(&param_1,local_4);
  pSpriteS1_2 = gta2::S122_sub_401BF0(this_01,pSpriteS1_2,piVar1);
  FUN_0041e210(local_c,(GlassInfo *)pSpriteS1_2,(Ped *)pSpriteS1_3);
  this_00 = _gS38_2;
  FUN_00447df0(pSpriteS1_1->Matrix3DArray[0].SpriteS3);
  FUN_004ba110(param_1);
  this_00->Point2D = (S127 *)pSpriteS1_1->Matrix3DArray[0].PositionZ;
  *(undefined2 *)&this_00->field0_0x0 =
       *(undefined2 *)&pSpriteS1_1->FirstElement;
  pSpriteS1_2 = gta2::S202_sub_401B20((Point2D *)&pSpriteS1_1->Matrix3DArray[0].PositionX,
                           (SpriteS1 *)&param_1,(S127 *)local_c);
  this_00->Point2D1 = (Point2D *)pSpriteS1_2->FirstElement;
  pSpriteS1_2 = gta2::S202_sub_401B20((Point2D *)&pSpriteS1_1->Matrix3DArray[0].PositionY,
                           (SpriteS1 *)&param_1,(S127 *)(local_c + 1));
  *(SpriteS1 **)&this_00->field_0x18 = pSpriteS1_2->FirstElement;
  gta2::SpriteS1_sub_4B99F0(this_00);
  gta2::SpriteS1_sub_4BCB40(this_00);
  gta2::sub_4BCAC0((SpriteS1 *)self,(VehiclePool *)this_00);
  return;
}


// 0x004be730: Sprite::Sprite_des_0
// IDA: Sprite::Sprite_des_0
// Ghidra: ---
void * gta2::Sprite_Sprite_des_0(SpriteEntry *self)
{
  void *result; // eax

  if ( gSpriteS1 )
    result = gta2::SpriteS1_SpriteS1_des(gSpriteS1, 1);
  gSpriteS1 = 0;
  if ( gSpriteS2 )
    result = gta2::SpriteS2_SpriteS2_des(gSpriteS2, 1);
  gSpriteS2 = 0;
  if ( gSpriteS3 )
    result = gta2::SpriteS3_SpriteS3_des(gSpriteS3, 1);
  gSpriteS3 = 0;
  if ( gSpriteS4 )
    result = gta2::SpriteS4_SpriteS4_Des(gSpriteS4, 1);
  gSpriteS4 = 0;
  unk_66FF18 = 0;
  return result;
}



