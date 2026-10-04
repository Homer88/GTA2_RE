#include "gta2_shim.h"

// Module: other, Class: S64
// Functions: 5
// Source: unified (IDA+Ghidra)

// 0x00483ed0: S64::sub_483ED0
// IDA: S64::sub_483ED0
// Ghidra: FUN_00483ed0
void gta2::S64_sub_483ED0(undefined4 *param_1)
{
  *param_1 = 0;
  _eh_vector_destructor_iterator_(param_1 + 1,8,0x44d,S65::~S65);
  return;
}


// 0x00483f60: S64::S64
// IDA: S64::S64
// Ghidra: ---
TriggerVolume * gta2::S64_S64(struct TriggerVolume *self)
{
  struct S65 *pS65; // edi
  struct S65 *v3; // eax
  int count; // edx

  pS65 = self->S65_;
  gta2::Construct(self->S65_, 8, 1101, S65::S65, S65::S65_dec);
  v3 = pS65;
  count = 1100;
  do
  {
    --count;
    v3->NextElement = v3 + 1;
    ++v3;
  }
  while ( count );
  self->FirstElement = pS65;
  self->S65_[1100].NextElement = 0;
  return self;
}


// 0x00483fa0: S64::sub_483FA0
// IDA: S64::sub_483FA0
// Ghidra: ---
S65 * gta2::S64_sub_483FA0(struct TriggerVolume *self)
{
  struct S65 *FirstElement; // esi

  FirstElement = self->FirstElement;
  self->FirstElement = self->FirstElement->NextElement;
  gta2::sub_482AD0((int)FirstElement);
  return FirstElement;
}


// 0x00483fc0: S64::sub_483FC0
// IDA: S64::sub_483FC0
// Ghidra: ---
S65 * gta2::S64_sub_483FC0(struct TriggerVolume *self, S65 *a2)
{
  struct S65 *result; // eax

  sub_482AF0();
  result = self->FirstElement;
  a2->NextElement = self->FirstElement;
  self->FirstElement = a2;
  return result;
}


// 0x00484840: S64::S64_des
// IDA: S64::S64_des
// Ghidra: ---
TriggerVolume * gta2::S64_S64_des(struct TriggerVolume *self, char a2)
{
  gta2::S64_sub_483ED0(self);
  if ( (a2 & 1) != 0 )
    free(self);
  return self;
}



