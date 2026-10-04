#include "gta2_shim.h"

// Module: other, Class: RenderManager
// Functions: 4
// Source: unified (IDA+Ghidra)

// 0x004c4b40: RenderManager::sub_4C4B40
// IDA: RenderManager::sub_4C4B40
// Ghidra: ---
RenderManager * gta2::RenderManager_sub_4C4B40(struct RenderManager *self)
{
  unsigned int v1; // edx

  v1 = self->field_2EE0;
  if ( v1 >= 0x3E8 )
    return 0;
  self->field_2EE0 = v1 + 1;
  return (struct RenderManager *)((char *)self + 12 * v1);
}


// 0x004c4b70: RenderManager::Set_sub_4C4B70
// IDA: RenderManager::Set_sub_4C4B70
// Ghidra: ---
void gta2::RenderManager_Set_sub_4C4B70(struct RenderManager *self)
{
  self->field_2EE0 = 0;
}


// 0x004c4d80: RenderManager::RenderManager_des
// IDA: RenderManager::RenderManager_des
// Ghidra: ---
RenderManager * gta2::RenderManager_RenderManager_des(struct RenderManager *self, char a2)
{
  if ( (a2 & 1) != 0 )
    free(self);
  return self;
}


// 0x004c4dc0: RenderManager::RenderManager
// IDA: RenderManager::RenderManager
// Ghidra: ---
RenderManager * gta2::RenderManager_RenderManager(struct RenderManager *self)
{
  struct RenderManager *pS20; // eax
  int count; // ecx

  pS20 = self;
  count = 1000;
  do
  {
    pS20->ARR_1000[0].FirstElement = 0;
    pS20 = (struct RenderManager *)((char *)pS20 + 12);
    --count;
  }
  while ( count );
  gta2::RenderManager_Set_sub_4C4B70(self);
  return self;
}



