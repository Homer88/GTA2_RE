#include "gta2_shim.h"

// Module: other, Class: Tango
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x0049e3a0: Tango::sub_49E3A0
// IDA: Tango::sub_49E3A0
// Ghidra: Car::FUN_0049e3a0
Car * gta2::Tango_sub_49E3A0(Car *self,int *param_1)
{
  gta2::Tango_sub_41E0D0(self,param_1);
  gta2::Tango_sub_41E0D0((Car *)&self->Passengers,param_1);
  return self;
}


// 0x0049e3c0: Tango::sub_49E3C0
// IDA: Tango::sub_49E3C0
// Ghidra: ---
int gta2::Tango_sub_49E3C0(struct Tango *self)
{
  Tango **p_Tango; // edi
  S202 *v3; // eax
  SpriteS1 *v4; // eax
  int result; // eax
  PublicTransport *v6; // [esp-8h] [ebp-1Ch]
  char v7[4]; // [esp+8h] [ebp-Ch] BYREF
  int v8; // [esp+Ch] [ebp-8h] BYREF
  char v9[4]; // [esp+10h] [ebp-4h] BYREF

  p_Tango = &self->Tango_;
  v6 = (PublicTransport *)gta2::sub_403840(self, (Player *)v7, &self->Tango_);
  v3 = (S202 *)gta2::sub_403840(&v8, (Player *)v9, self);
  v4 = gta2::S202_sub_401B20(v3, (SpriteS1 *)&v8, v6);
  result = gta2::sub_4037E0(v4);
  if ( result )
  {
    result = unk_66ACDC;
    self->field = unk_66ACDC;
    *p_Tango = (Tango *)unk_66ACDC;
  }
  return result;
}


// 0x004d6230: Tango::sub_4D6230
// IDA: Tango::sub_4D6230
// Ghidra: ---
void * gta2::Tango_sub_4D6230(struct Tango *self)
{
  __int64 v1; // rax

  if ( (unsigned __int8)self >= 0x40u )
  {
    LODWORD(v1) = SHIDWORD(v1) >> 31;
  }
  else if ( (unsigned __int8)self >= 0x20u )
  {
    LODWORD(v1) = SHIDWORD(v1) >> ((unsigned __int8)self & 0x1F);
  }
  else
  {
    v1 >>= (unsigned __int8)self & 0x1F;
  }
  return (void *)v1;
}



