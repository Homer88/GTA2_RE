#include "gta2_shim.h"

// Module: other, Class: ObjectModel
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x00474490: ObjectModel::FUN_00474490
// IDA: sub_474490
// Ghidra: ObjectModel::FUN_00474490
int gta2::ObjectModel_FUN_00474490(ObjectModel *self)
{
  return (int)self->next / 0x1e;
}



