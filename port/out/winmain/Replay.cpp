#include "gta2_shim.h"

// Module: winmain, Class: Replay
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x003f154c: Replay::PlayReplay
// IDA: Replay::PlayReplay
// Ghidra: ---
int gta2::Replay_PlayReplay(void *self, LPCSTR lpFileName)
{
  FILE *v2; // eax

  gta2::FileMgr_SetFilePath(lpFileName);
  v2 = gta2::FileMgr_WriteReadFile(lpFileName, "wb");
  return fclose(v2);
}


// 0x003f1574: Replay::StartPlayReplay
// IDA: Replay::StartPlayReplay
// Ghidra: ---
int gta2::Replay_StartPlayReplay(Replay *self)
{
  void *v1; // ecx

  gta2::Replay_PlayReplay(self, gTestReplayRep);
  return gta2::Replay_PlayReplay(v1, aTestReplay0Rep);
}



