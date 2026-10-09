#include "gta2_shim.h"

// Module: other, Class: S86_2_1
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004c6f40: S86_2_1::S86_2_1
// IDA: S86_2_1::S86_2_1
// Ghidra: ---
S86_2_1 * gta2::S86_2_1_S86_2_1(struct S86_2_1 *self)
{
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&self->m_nPointRotation);
  self->Gang_ = 0;
  self->m_bVisible = 0;
  self->ArrowVisible = 0;
  gta2::ArrowTrace_ArrowTrace(&self->m_ArrowTrace);
  gta2::ArrowTrace_ArrowTrace(&self->m_SecondArrowTrace);
  self->ArrowTrace_ = &self->m_ArrowTrace;
  LOBYTE(self->field_26) = 0;
  self->field_2E = 0;
  return self;
}



