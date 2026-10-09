#include "gta2_shim.h"

// Module: other, Class: Particle
// Functions: 5
// Source: unified (IDA+Ghidra)

// 0x0048a8e0: Particle::sub_48A8E0
// IDA: Particle::sub_48A8E0
// Ghidra: FUN_0048a8e0
void gta2::Particle_sub_48A8E0(undefined4 *param_1)
{
  *param_1 = 0;
  param_1[1] = 0;
  return;
}


// 0x0048a8f0: Particle::IsNotEmpty
// IDA: Particle::IsNotEmpty
// Ghidra: ---
bool gta2::Particle_IsNotEmpty(struct Particle *self)
{
  return self->FirstElement != 0;
}


// 0x0048a900: Particle::sub_48A900
// IDA: Particle::sub_48A900
// Ghidra: ---
Particle1 * gta2::Particle_sub_48A900(struct Particle *self)
{
  struct Particle1 *Particle1; // edx
  struct Particle1 *FirstElement; // esi

  Particle1 = self->Particle1_;
  FirstElement = self->FirstElement;
  self->FirstElement = self->FirstElement->Particle1_;
  FirstElement->Particle1_ = Particle1;
  self->Particle1_ = FirstElement;
  gta2::Particle1_sub_48A1F0(FirstElement);
  return FirstElement;
}


// 0x0048f1c0: Particle::sub_48F1C0
// IDA: Particle::sub_48F1C0
// Ghidra: FUN_0048f1c0
void * gta2::Particle_sub_48F1C0(void *param_1,byte param_2)
{
  FUN_0048a8e0();
  if ((param_2 & 1) != 0) {
    free(param_1);
  }
  return param_1;
}


// 0x0048f1e0: Particle::Particle
// IDA: Particle::Particle
// Ghidra: ---
Particle * gta2::Particle_Particle(struct Particle *self)
{
  struct Particle1 *Particle1_ARR; // edi
  struct Particle1 **p_Particle1; // eax
  int count; // ecx

  Particle1_ARR = self->Particle1_ARR;
  gta2::constructor(self->Particle1_ARR, 76, 500, Particle1::Particle1);
  p_Particle1 = &Particle1_ARR->Particle1_;
  count = 499;
  do
  {
    *p_Particle1 = (Particle1 *)(p_Particle1 + 4);
    p_Particle1 += 19;
    --count;
  }
  while ( count );
  self->FirstElement = Particle1_ARR;
  self->Particle1_ARR[499].Particle1 = 0;
  self->Particle1_ = 0;
  self->field_9478 = 0;
  return self;
}



