#include "gta2_shim.h"

// Module: winmain, Class: FileMgr
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x00402eb0: FileMgr::CloseFile
// IDA: FileMgr::CloseFile
// Ghidra: ---
int gta2::FileMgr_CloseFile(struct FileMgr *self)
{
  int result; // eax

  result = *(_DWORD *)&stru_5D22FC.gap2D8[32];
  if ( *(_DWORD *)&stru_5D22FC.gap2D8[32] )
  {
    result = fclose(*(FILE **)&stru_5D22FC.gap2D8[28]);
    *(_DWORD *)&stru_5D22FC.gap2D8[32] = 0;
    if ( result )
      return (int)(intptr_t)gta2::debug_log(0x11u, "File.cpp", 350);
  }
  return result;
}


// 0x00402f60: FileMgr::Seek
// IDA: FileMgr::Seek
// Ghidra: ---
int gta2::FileMgr_Seek(struct FileMgr *self, int size)
{
  int result; // eax

  if ( !*(_DWORD *)&stru_5D22FC.gap2D8[32] )
    gta2::debug_log(0x15u, "File.cpp", 421);
  result = gta2::_fseek(*(FILE **)&stru_5D22FC.gap2D8[28], *(_DWORD *)size, 1);
  if ( result )
    return gta2::error(0xEu, 0, 0);
  return result;
}


// 0x00403160: FileMgr::FileOpen
// IDA: FileMgr::FileOpen
// Ghidra: ---
FILE * gta2::FileMgr_FileOpen(void *self, LPCSTR lpFileName)
{
  FILE *result; // eax
  const char *v3; // [esp-8h] [ebp-8h]

  if ( *(_DWORD *)&stru_5D22FC.gap2D8[32] )
    gta2::FileMgr_CloseFile((FileMgr *)self);
  gta2::FileMgr_SetFilePath(v3);
  result = gta2::FileMgr_WriteReadFile(v3, "rb");
  *(_DWORD *)&stru_5D22FC.gap2D8[28] = (int)(intptr_t)result;
  if ( !result )
    result = (FILE *)gta2::debug_log(0x10u, "File.cpp", 328);
  *(_DWORD *)&stru_5D22FC.gap2D8[32] = 1;
  return result;
}






