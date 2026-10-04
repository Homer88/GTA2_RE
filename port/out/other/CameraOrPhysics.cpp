#include "gta2_shim.h"

// Module: other, Class: CameraOrPhysics
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x00475b60: CameraOrPhysics::ResetAccuracy
// IDA: CameraOrPhysics::ResetAccuracy
// Ghidra: ---
void gta2::CameraOrPhysics_ResetAccuracy(struct CameraOrPhysics *self)
{
  self->cameraPosTarget_[1].field_10 = 1;
}


// 0x004a5070: CameraOrPhysics::sub_4A5070
// IDA: CameraOrPhysics::sub_4A5070
// Ghidra: CameraOrPhysics::FUN_004a5070
void gta2::CameraOrPhysics_sub_4A5070(struct CameraOrPhysics *self)
{
  self->m_nAccuracy = 2;
  self->field34_0x3d = 0;
  self->field35_0x3e = 0;
  self->field36_0x3f = 0;
  return;
}


// 0x004b90e0: CameraOrPhysics::WorldToScreen2D
// IDA: CameraOrPhysics::WorldToScreen2D
// Ghidra: ---
CarTransforms * gta2::CameraOrPhysics_WorldToScreen2D(
        void *self,
        int a2,
        int a2_4,
        int a2_8,
        int *a2_12,
        int *a2_16)
{
  struct SpriteS1 *v7; // eax
  struct SpriteS1 *v8; // eax
  struct PublicTransport *v9; // eax
  struct SpriteS1 *v10; // eax
  struct SpriteS1 *v11; // eax
  struct SpriteS1 *v12; // eax
  int *v13; // eax
  struct PublicTransport *v14; // eax
  struct SpriteS1 *v15; // eax
  struct SpriteS1 *v16; // eax
  struct SpriteS1 *v17; // eax
  struct SpriteS1 *FirstElement; // edx
  struct CarTransforms *result; // eax
  struct PublicTransport *v20; // [esp-4h] [ebp-1Ch]
  struct PublicTransport *v21; // [esp-4h] [ebp-1Ch]
  struct PublicTransport *v22; // [esp-4h] [ebp-1Ch]
  char v23; // [esp+8h] [ebp-10h] BYREF
  int v24; // [esp+Ch] [ebp-Ch] BYREF
  char v25; // [esp+10h] [ebp-8h] BYREF
  char v26; // [esp+14h] [ebp-4h] BYREF

  v20 = (struct PublicTransport *)((char *)self + 160);
  v7 = gta2::Player_sub_401B40((struct Player *)&unk_66F610, (struct S202 *)&v24, (int)&a2_8);
  v8 = gta2::S202_sub_401B20((struct S202 *)v7, (struct SpriteS1 *)&v23, v20);
  gta2::sub_401B90(&dword_66F668, &a2_8, v8);
  gta2::sub_40CE00(&v24, *((_DWORD *)self + 28));
  v21 = v9;
  v10 = gta2::Player_sub_401B40((struct Player *)&a2, (struct S202 *)&v26, (int)self + 152);
  v11 = gta2::Radar_AddBlip((struct Tango *)v10, (struct SpriteS1 *)&v23, (struct PublicTransport *)((char *)self + 96));
  v12 = gta2::Radar_AddBlip((struct Tango *)v11, (struct SpriteS1 *)&v25, (struct PublicTransport *)&a2_8);
  v13 = (int *)gta2::S202_sub_401B20((struct S202 *)v12, (struct SpriteS1 *)&a2, v21);
  *a2_12 = *v13;
  gta2::sub_40CE00(&a2, *((_DWORD *)self + 29));
  v22 = v14;
  v15 = gta2::Player_sub_401B40((struct Player *)&a2_4, (struct S202 *)&v25, (int)self + 156);
  v16 = gta2::Radar_AddBlip((struct Tango *)v15, (struct SpriteS1 *)&v26, (struct PublicTransport *)((char *)self + 96));
  v17 = gta2::Radar_AddBlip((struct Tango *)v16, (struct SpriteS1 *)&a2_4, (struct PublicTransport *)&a2_8);
  FirstElement = gta2::S202_sub_401B20((struct S202 *)v17, (struct SpriteS1 *)&a2_12, v22)->FirstElement;
  result = (struct CarTransforms *)a2_16;
  *a2_16 = (int)FirstElement;
  return result;
}



