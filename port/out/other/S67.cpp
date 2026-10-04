#include "gta2_shim.h"

// Module: other, Class: S67
// Functions: 4
// Source: unified (IDA+Ghidra)

// 0x00482b10: S67::S67_Des
// IDA: S67::S67_Des
// Ghidra: ---
void gta2::S67_S67_Des(_DWORD *self)
{
  self[2] = 0;
}


// 0x00482b20: S67::sub_482B20
// IDA: S67::sub_482B20
// Ghidra: FUN_00482b20
void gta2::S67_sub_482B20(void *self)
{
  void *local_4;
  
  _DAT_00665770 = _DAT_00665770 + 1;
  local_4 = self;
  gta2::bitShiftLeft1(&local_4,NULL);
  *(void **)((int)self + 0xc) = local_4;
  *(undefined2 *)((int)self + 4) = _DAT_006657f8______S38;
  gta2::bitShiftLeft1(&local_4,NULL);
  *(undefined2 *)((int)self + 0x28) = 0;
  *(void **)((int)self + 0x18) = local_4;
  *(undefined1 *)((int)self + 0x38) = 0;
  *(undefined4 *)((int)self + 0x34) = 2;
  *(undefined4 *)((int)self + 0x24) = 0;
  *(undefined1 *)((int)self + 0x2f) = 0;
  *(undefined1 *)((int)self + 0x30) = 0;
  return;
}


// 0x00482ba0: S67::sub_482BA0
// IDA: S67::sub_482BA0
// Ghidra: FUN_00482ba0
void gta2::S67_sub_482BA0(int param_1,undefined4 *param_2)
{
  undefined4 local_8;
  undefined4 local_4;
  
  FUN_0041e210(&local_8,(GlassInfo *)(param_1 + 0xc),(struct Ped *)(param_1 + 4));
  *param_2 = local_8;
  param_2[1] = local_4;
  return;
}


// 0x00484020: S67::S67
// IDA: S67::S67
// Ghidra: ---
void gta2::S67_S67(struct S67 *self)
{
  gta2::Arsenal_Reset((struct Arsenal *)self);
  gta2::CarSystemManager_SetIndexDefautCarManager((struct CarSystemManager *)&self->field_4);
  self->NextElement = 0;
  self->field_1C = unk_665AA0;
  self->field_18 = unk_665AA0;
  self->field_10 = unk_665AA0;
  self->field_C = unk_665AA0;
  self->field_4 = word_6657F8[0];
  self->field_28 = 0;
  self->field_20 = 0;
  self->field_2C = 0;
  self->field_2A = 0;
  self->field_38 = 0;
  self->field_2E = 0;
  self->field_2F = 0;
  self->field_34 = 2;
}



