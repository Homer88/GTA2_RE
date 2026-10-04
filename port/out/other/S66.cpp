#include "gta2_shim.h"

// Module: other, Class: S66
// Functions: 5
// Source: unified (IDA+Ghidra)

// 0x00483ef0: S66::sub_483EF0
// IDA: S66::sub_483EF0
// Ghidra: FUN_00483ef0
void gta2::S66_sub_483EF0(undefined4 *param_1)
{
  *param_1 = 0;
  _eh_vector_destructor_iterator_(param_1 + 1,0x3c,0x181,S67::~S67);
  return;
}


// 0x00483fe0: S66::NextElement
// IDA: S66::NextElement
// Ghidra: ---
S67 * gta2::S66_NextElement(struct S66 *self)
{
  struct S67 *FirstElement; // esi

  FirstElement = self->FirstElement;
  self->FirstElement = self->FirstElement->NextElement;
  gta2::S67_sub_482B20(FirstElement);
  return FirstElement;
}


// 0x00484000: S66::sub_484000
// IDA: S66::sub_484000
// Ghidra: ---
S67 * gta2::S66_sub_484000(struct S66 *self, S67 *a2)
{
  struct S67 *result; // eax

  sub_482B80(a2);
  result = self->FirstElement;
  a2->NextElement = self->FirstElement;
  self->FirstElement = a2;
  return result;
}


// 0x00484860: S66::S66_des
// IDA: S66::S66_des
// Ghidra: ---
S66 * gta2::S66_S66_des(struct S66 *self, char a2)
{
  gta2::S66_sub_483EF0(self);
  if ( (a2 & 1) != 0 )
    free(self);
  return self;
}


// 0x004848c0: S66::S66
// IDA: S66::S66
// Ghidra: ---
S66 * gta2::S66_S66(struct S66 *self)
{
  struct S67 *pS67; // esi
  struct S67 *p_NextElement; // eax
  int count; // ecx

  pS67 = self->S67_;
  gta2::Construct(self->S67_, 60, 385, S67::S67, S67::S67_Des);
  p_NextElement = (struct S67 *)&pS67->NextElement;
  count = 384;
  do
  {
    p_NextElement->field = (int)&p_NextElement->field_34;
    ++p_NextElement;
    --count;
  }
  while ( count );
  self->S67_[384].NextElement = 0;
  self->FirstElement = pS67;
  return self;
}



