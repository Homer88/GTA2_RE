#include "gta2_shim.h"

// Module: other, Class: StreamWriter
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x004d4ac8: StreamWriter::FUN_004d4ac8
// IDA: ---
// Ghidra: StreamWriter::FUN_004d4ac8
int * gta2::StreamWriter_FUN_004d4ac8(void *self)
{
  void *this_00;
  undefined4 *puVar1;
  int *extraout_ECX;
  int unaff_EBP;
  
  FUN_004d8770();
  *(undefined4 *)(unaff_EBP + -0x10) = 0;
  *(int **)(unaff_EBP + -0x14) = extraout_ECX;
  if (*(int *)(unaff_EBP + 8) != 0) {
    *extraout_ECX = (int)&DAT_00578698;
    FUN_004d48d0(extraout_ECX + 2);
    *(undefined4 *)(unaff_EBP + -4) = 0;
    *(undefined4 *)(unaff_EBP + -0x10) = 1;
  }
  this_00 = gta2::operator_new(0x38);
  *(void **)(unaff_EBP + 8) = this_00;
  *(undefined4 *)(unaff_EBP + -4) = 1;
  if (this_00 == NULL) {
    puVar1 = NULL;
  }
  else {
    puVar1 = FUN_004d5465(this_00);
  }
  *(undefined1 *)(unaff_EBP + -4) = 0;
  FUN_004d4fa2(puVar1,0);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  *(undefined ***)((int)extraout_ECX + *(int *)(*extraout_ECX + 4)) =
       &PTR_ofstream_00578694;
  *(undefined4 *)(*(int *)(*extraout_ECX + 4) + 0x1c + (int)extraout_ECX) = 1;
  return extraout_ECX;
}


// 0x004d4d97: StreamWriter::FUN_004d4d97
// IDA: sub_4D4D97
// Ghidra: StreamWriter::FUN_004d4d97
void gta2::StreamWriter_FUN_004d4d97(void *self,LPCSTR param_1,uint param_2,uint param_3)
{
  uint *puVar1;
  void *this_00;
  int *piVar2;
  
                              // WARNING: Load size is inaccurate
  this_00 = *(void **)(*(int *)(*self + 4) + 4 + (int)self);
  if ((*(int *)((int)this_00 + 0x30) == -1) &&
     (piVar2 = FUN_004d584e(this_00,param_1,param_2 | 2,param_3), piVar2 != NULL
     )) {
    return;
  }
                              // WARNING: Load size is inaccurate
  puVar1 = (uint *)(*(int *)(*self + 4) + 8 + (int)self);
  *puVar1 = *puVar1 | 2;
  return;
}



