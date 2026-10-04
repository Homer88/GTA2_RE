#include "gta2_shim.h"

// Module: other, Class: AudioSourceParams
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x004ba5e0: AudioSourceParams::sub_4BA5E0
// IDA: AudioSourceParams::sub_4BA5E0
// Ghidra: ---
void gta2::AudioSourceParams_sub_4BA5E0(struct AudioSourceParams *self)
{
  arg0 = gta2::AudioSourceParams_sub_41F9D0(self);
  dword_662BF8 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&self->AudioSourceParams_);
  dword_662BAC = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&self->AudioSourceParams1);
  a5 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&self->AudioSourceParams2);
}


// 0x004ba720: AudioSourceParams::sub_4BA720
// IDA: AudioSourceParams::sub_4BA720
// Ghidra: ---
char gta2::AudioSourceParams_sub_4BA720(struct AudioSourceParams *self)
{
  struct SpriteS1 *v2; // eax
  struct AudioSourceParams *v3; // eax
  int v4; // edi
  struct SpriteS1 *v5; // eax
  struct AudioSourceParams *v6; // eax
  int v7; // ebx
  struct SpriteS1 *v8; // eax
  struct AudioSourceParams *v9; // eax
  int v10; // eax
  int WindowWidth; // [esp+Ch] [ebp-Ch] BYREF
  int WindowHeight; // [esp+10h] [ebp-8h] BYREF
  int v14; // [esp+14h] [ebp-4h] BYREF

  gta2::AudioSourceParams_sub_4BA5E0(self);
  WindowWidth = 2;
  v2 = gta2::S202_sub_401B20((struct S202 *)self, (struct SpriteS1 *)&v14, (struct PublicTransport *)&self->AudioSourceParams_);
  gta2::S122_sub_401BF0((struct S122 *)v2, (int)&WindowHeight, (int)&WindowWidth);
  v4 = gta2::AudioSourceParams_sub_41F9D0(v3);
  WindowWidth = 2;
  v5 = gta2::S202_sub_401B20(
         (struct S202 *)&self->AudioSourceParams1,
         (struct SpriteS1 *)&WindowHeight,
         (struct PublicTransport *)&self->AudioSourceParams2);
  gta2::S122_sub_401BF0((struct S122 *)v5, (int)&v14, (int)&WindowWidth);
  v7 = gta2::AudioSourceParams_sub_41F9D0(v6);
  WindowWidth = 2;
  v8 = gta2::S202_sub_401B20((struct S202 *)&self->field_10, (struct SpriteS1 *)&WindowHeight, (struct PublicTransport *)&self->field_14);
  gta2::S122_sub_401BF0((struct S122 *)v8, (int)&v14, (int)&WindowWidth);
  v10 = gta2::AudioSourceParams_sub_41F9D0(v9);
  return gta2::MapRelatedStruct_sub_46B440(gMapRelatedStruct, v4, v7, v10, 0, 1024);
}


// 0x004ba7e0: AudioSourceParams::sub_4BA7E0
// IDA: AudioSourceParams::sub_4BA7E0
// Ghidra: FUN_004ba7e0
void gta2::AudioSourceParams_sub_4BA7E0(SpriteS1 *param_1,SpriteS1 *param_2,SpriteS3 *param_3)
{
  struct Car **pSpriteS1;
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  struct SpriteS3 **ppSVar2;
  
  bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)&param_2,param_1);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    bVar1 = gta2::Car_sub_403800((struct Car *)&param_2,(int *)param_1->Matrix3DArray);
    if (CONCAT31(extraout_var_00,bVar1) != 0) {
      param_1->Matrix3DArray[0].SpriteS1 = param_2;
    }
  }
  else {
    param_1->FirstElement = param_2;
  }
  pSpriteS1 = &param_1->Matrix3DArray[0].Car;
  bVar1 = gta2::Point2D_FUN_004037e0((Point2D *)&param_3,(struct SpriteS1 *)pSpriteS1);
  if (CONCAT31(extraout_var_01,bVar1) != 0) {
    *pSpriteS1 = (struct Car *)param_3;
    return;
  }
  ppSVar2 = &param_1->Matrix3DArray[0].SpriteS3;
  bVar1 = gta2::Car_sub_403800((struct Car *)&param_3,(int *)ppSVar2);
  if (CONCAT31(extraout_var_02,bVar1) != 0) {
    *ppSVar2 = param_3;
  }
  return;
}



