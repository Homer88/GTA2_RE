#include "gta2_shim.h"

// Module: other, Class: FileMgr
// Functions: 6
// Source: unified (IDA+Ghidra)

// 0x004cba00: FileMgr::Get_field_10
// IDA: FileMgr::Get_field_10
// Ghidra: ---
int gta2::FileMgr_Get_field_10(struct FileMgr *self)
{
  return self->field_10;
}


// 0x004cba10: FileMgr::GetFiled_14
// IDA: FileMgr::GetFiled_14
// Ghidra: ---
int gta2::FileMgr_GetFiled_14(struct FileMgr *self)
{
  return self->field_14;
}


// 0x004cba20: FileMgr::Get_field_1C
// IDA: FileMgr::Get_field_1C
// Ghidra: ---
int gta2::FileMgr_Get_field_1C(struct FileMgr *self)
{
  return self->field_1C;
}


// 0x004cba30: FileMgr::Get_field_20
// IDA: FileMgr::Get_field_20
// Ghidra: ---
int gta2::FileMgr_Get_field_20(struct FileMgr *self)
{
  return self->field_20;
}


// 0x004cba40: FileMgr::sub_4CBA40
// IDA: FileMgr::sub_4CBA40
// Ghidra: ---
void gta2::FileMgr_sub_4CBA40(struct FileMgr *self)
{
  self->field_24 = -1;
  self->field_25 = -15;
}


// 0x004d68de: FileMgr::WriteReadFile
// IDA: FileMgr::WriteReadFile
// Ghidra: ---
FILE * gta2::FileMgr_WriteReadFile(LPCSTR lpFileName, void *Mode)
{
  return gta2::_fsopen(lpFileName, Mode, 64);
}



