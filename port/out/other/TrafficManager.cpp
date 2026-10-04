#include "gta2_shim.h"

// Module: other, Class: TrafficManager
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x00474e50: TrafficManager::TrafficManager
// IDA: TrafficManager::TrafficManager
// Ghidra: ---
TrafficManager * gta2::TrafficManager_TrafficManager(struct TrafficManager *self)
{
  struct TrafficManager *result; // eax
  struct S32 *S32; // edx
  int Index; // esi

  result = self;
  LOBYTE(self->S32_[49].NextElement) = 0;
  S32 = self->S32_;
  Index = 50;
  do
  {
    S32[-1].NextElement = 0;
    S32->prev_field = 0;
    S32->currentData = 0;
    ++S32;
    --Index;
  }
  while ( Index );
  return result;
}


// 0x00474ea0: TrafficManager::sub_474EA0
// IDA: TrafficManager::sub_474EA0
// Ghidra: ---
char gta2::TrafficManager_sub_474EA0(struct TrafficManager *self, int a2)
{
  struct TrafficManager *v2; // eax
  int v3; // ecx
  struct S32 *v4; // edx

  v2 = gta2::TrafficManager_sub_474E80(self);
  if ( v2 )
  {
    v2->FirstElement = (struct S32 *)a2;
    v4 = *(S32 **)(a2 + 108);
    v2->S32_[0].currentData = 1;
    v2->S32_[0].prev_field = v4;
    LOBYTE(v2) = *(_BYTE *)(v3 + 600) + 1;
    *(_BYTE *)(v3 + 600) = (_BYTE)v2;
  }
  return (char)v2;
}



