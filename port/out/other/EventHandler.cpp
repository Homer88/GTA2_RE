#include "gta2_shim.h"

// Module: other, Class: EventHandler
// Functions: 4
// Source: unified (IDA+Ghidra)

// 0x00483a00: EventHandler::FUN_00483a00
// IDA: sub_483A00
// Ghidra: EventHandler::FUN_00483a00
void gta2::EventHandler_FUN_00483a00(struct EventHandler *self)
{
  gta2::sub_45B2F0(self->DamageInfo);
  return;
}


// 0x00483a10: EventHandler::FUN_00483a10
// IDA: sub_483A10
// Ghidra: EventHandler::FUN_00483a10
void gta2::EventHandler_FUN_00483a10(struct EventHandler *self)
{
  gta2::sub_45B300(self->DamageInfo);
  return;
}


// 0x00484710: EventHandler::FUN_00484710
// IDA: ---
// Ghidra: EventHandler::FUN_00484710
void * gta2::EventHandler_FUN_00484710(struct EventHandler *self)
{
  void *pvVar1;
  
  pvVar1 = *(void **)(self->Struc___ + 0x34);
  if ((-1 < (int)pvVar1) && ((int)pvVar1 < 2)) {
    if (self->DamageType != 0x94) {
      gta2::S63_sub_4827B0((CollisionBox *)self);
      return pvVar1;
    }
    pvVar1 = gta2::S63_sub_483C20(self,1);
  }
  return pvVar1;
}


// 0x004be850: EventHandler::FUN_004be850
// IDA: sub_4BE850
// Ghidra: EventHandler::FUN_004be850
byte gta2::EventHandler_FUN_004be850(struct EventHandler *self)
{
  if ((0x11e < (int)self->DamageType) && ((int)self->DamageType < 0x126)) {
    return 1;
  }
  return 0;
}



