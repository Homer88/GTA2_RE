#include "gta2_shim.h"

// Module: other, Class: S29
// Functions: 7
// Source: unified (IDA+Ghidra)

// 0x00474fa0: S29::S29
// IDA: S29::S29
// Ghidra: ---
S29 * gta2::S29_S29(struct S29 *self)
{
  struct S29 *result; // eax

  result = self;
  self->S34 = 0;
  self->Index = 0;
  return result;
}


// 0x00474fb0: S29::sub_474FB0
// IDA: S29::sub_474FB0
// Ghidra: ---
Viewport * gta2::S29_sub_474FB0(struct S29 *self, Viewport *a2)
{
  struct Viewport *result; // eax

  result = a2;
  a2->NextElement = self->S34;
  self->S34 = a2;
  ++self->Index;
  return result;
}


// 0x00474fd0: S29::sub_474FD0
// IDA: S29::sub_474FD0
// Ghidra: FUN_00474fd0
void gta2::S29_sub_474FD0(void *self)
{
  int iVar1;
  
                              // WARNING: Load size is inaccurate
  iVar1 = *self;
  if (iVar1 != 0) {
    *(undefined4 *)self = *(undefined4 *)(iVar1 + 8);
    *(undefined4 *)(iVar1 + 8) = 0;
    *(char *)((int)self + 4) = *(char *)((int)self + 4) + -1;
  }
  return;
}


// 0x00474ff0: S29::sub_474FF0
// IDA: S29::sub_474FF0
// Ghidra: FUN_00474ff0
void gta2::S29_sub_474FF0(void *self,byte param_1)
{
  byte bVar1;
  void *extraout_ECX;
  
  bVar1 = *(byte *)((int)self + 4);
  while (param_1 < bVar1) {
    FUN_00474fd0(self);
    self = extraout_ECX;
    bVar1 = *(byte *)((int)extraout_ECX + 4);
  }
  return;
}


// 0x00476dc0: S29::S29_DEs
// IDA: S29::S29_DEs
// Ghidra: ---
Viewport * gta2::S29_S29_DEs(struct S29 *self)
{
  struct Viewport *result; // eax
  struct Viewport *pS34; // [esp-4h] [ebp-8h]

  for ( ; self->S34; result = self->S34 )
  {
    pS34 = self->S34;
    self->S34 = self->S34->NextElement;
    gta2::S33_S33_sub_476780(gCamera, pS34);
    --self->Index;
  }
  return result;
}


// 0x00476df0: S29::sub_476DF0
// IDA: S29::sub_476DF0
// Ghidra: FUN_00476df0
void gta2::S29_sub_476DF0(void *self)
{
  gta2::Camera_CameraPopViewport(gCamera);
  return;
}


// 0x0047bf60: S29::S29_Des
// IDA: S29::S29_Des
// Ghidra: ---
S29 * gta2::S29_S29_Des(struct S29 *self, char a2)
{
  gta2::S29_S29_DEs(self);
  if ( (a2 & 1) != 0 )
    free(self);
  return self;
}



