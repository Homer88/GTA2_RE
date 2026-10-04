#include "gta2_shim.h"

// Module: other, Class: ScriptThread
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004b9920: ScriptThread::S68_FUN_004b9920
// IDA: ---
// Ghidra: ScriptThread::S68_FUN_004b9920
{
  self[(uint)param_1 * 8 + 4] =
       (ScriptThread)((char)self[(uint)param_1 * 8 + 4] + '\x01');
  return;
}



