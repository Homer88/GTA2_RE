#include "gta2_shim.h"

// Module: other, Class: S17
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x0046bc70: S17::MatrixTransform3Advanced
// IDA: S17::MatrixTransform3Advanced
// Ghidra: ---
void gta2::S17_MatrixTransform3Advanced(struct EntityManager *self, int *a1, int *a2, int *a3, float *a4)
{
  struct CameraOrPhysics *v6; // edi
  struct CameraOrPhysics *v7; // edi
  float a3a; // [esp+24h] [ebp+Ch]
  float a3b; // [esp+24h] [ebp+Ch]
  float a4a; // [esp+28h] [ebp+10h]
  float a4b; // [esp+28h] [ebp+10h]

  gta2::sub_46BBF0(*a2, *a1, *a2, (struct S900 *)*a3);
  a4a = 8.0 - gta2::Float10_EncodedFloatToRegularFloat(a3);
  a4b = 1.0 / (gta2::Float10_EncodedFloatToRegularFloat(&gCameraOrPhysics->cameraPosTarget_[3].field_24) + a4a);
  a4[2] = a4b;
  v6 = gCameraOrPhysics;
  a3a = gta2::Float10_EncodedFloatToRegularFloat((int *)&gCameraOrPhysics->cameraPosTarget_[2].Car);
  *a4 = gta2::Float10_EncodedFloatToRegularFloat(a1) * a3a * a4b + (double)(unsigned int)v6->cameraPosTarget_[2].Player;
  v7 = gCameraOrPhysics;
  a3b = gta2::Float10_EncodedFloatToRegularFloat((int *)&gCameraOrPhysics->cameraPosTarget_[2].Car);
  a4[1] = gta2::Float10_EncodedFloatToRegularFloat(a2) * a3b * a4b + (double)(unsigned int)v7->cameraPosTarget_[2].field_20;
}



