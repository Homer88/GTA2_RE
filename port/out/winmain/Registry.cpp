#include "gta2_shim.h"

// Module: winmain, Class: Registry
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x003f13cc: Registry::GetReplayNum
// IDA: Registry::GetReplayNum
// Ghidra: ---
int gta2::Registry_GetReplayNum(struct Registry *self, LPCSTR lpValueName)
{
  int result; // eax
  HKEY hKey; // [esp+0h] [ebp-Ch] BYREF
  int Data; // [esp+4h] [ebp-8h] BYREF
  DWORD cbData; // [esp+8h] [ebp-4h] BYREF

  LOBYTE(result) = gta2::Registry_GetDebugMode(self, &hKey);
  if ( result )
  {
    cbData = 4;
    RegQueryValueExA(hKey, lpValueName, 0, 0, (LPBYTE)&Data, &cbData);
    RegCloseKey(hKey);
    return Data;
  }
  return result;
}


// 0x003f1458: Registry::SetDebugByteValue
// IDA: Registry::SetDebugByteValue
// Ghidra: ---
LSTATUS gta2::Registry_SetDebugByteValue(struct Registry *self, LPCSTR lpValueName, BYTE Data)
{
  HKEY hKey; // [esp+0h] [ebp-4h] BYREF

  gta2::Registry_GetDebugMode(self, &hKey);
  RegSetValueExA(hKey, lpValueName, 0, 4u, &Data, 4u);
  return RegCloseKey(hKey);
}



