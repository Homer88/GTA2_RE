#include "gta2_shim.h"

// Module: winmain, Class: MissionScriptObjectData
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x003f10b0: MissionScriptObjectData::sub_3F10B0
// IDA: MissionScriptObjectData::sub_3F10B0
// Ghidra: ---
int gta2::MissionScriptObjectData_sub_3F10B0(MissionScriptObjectData *self)
{
  int v1; // eax

  return (int)gta2::MissionManager_StartMission(gMissionManager, *(_WORD *)(v1 + 8));
}



