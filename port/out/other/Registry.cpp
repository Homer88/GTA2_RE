#include "gta2_shim.h"

// Module: other, Class: Registry
// Functions: 26
// Source: unified (IDA+Ghidra)

// 0x004b4f90: Registry::OpenOrCreateSoundKey
// IDA: Registry::OpenOrCreateSoundKey
// Ghidra: ---
bool gta2::Registry_OpenOrCreateSoundKey(struct Registry *self, PHKEY param_1)
{
  PHKEY pHkey; // [esp-4h] [ebp-8h] BYREF

  if ( !RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\DMA Design Ltd\\GTA2\\Sound", 0, 0xF003Fu, pHkey) )
    return 1;
  if ( RegCreateKeyExA(
         HKEY_CURRENT_USER,
         "SOFTWARE\\DMA Design Ltd\\GTA2\\Sound",
         0,
         gSource,
         0,
         983103u,
         0,
         pHkey,
         (LPDWORD)&pHkey) )
  {
    gta2::debug_log(0x2Bu, "registry.cpp", 58);
  }
  return 0;
}


// 0x004b5000: Registry::GetSound3DConfigure
// IDA: Registry::GetSound3DConfigure
// Ghidra: ---
bool gta2::Registry_GetSound3DConfigure(struct Registry *self, LPCSTR param_2)
{
  bool v2; // bl
  HKEY v4; // [esp-8h] [ebp-18h] BYREF
  DWORD v5; // [esp-4h] [ebp-14h] BYREF
  BYTE v6[4]; // [esp+0h] [ebp-10h] BYREF
  DWORD cbData; // [esp+8h] [ebp-8h]

  v2 = 0;
  if ( gta2::Registry_OpenOrCreateSoundKey(self, &v4) )
  {
    v5 = 4;
    v2 = RegQueryValueExA(v4, (LPCSTR)cbData, 0, 0, v6, &v5) == 0;
  }
  if ( RegCloseKey(v4) )
    gta2::debug_log(0x2Au, "registry.cpp", 109);
  return v2;
}


// 0x004b5070: Registry::ConfigureSound
// IDA: Registry::ConfigureSound
// Ghidra: ---
int gta2::Registry_ConfigureSound(struct Registry *self, LPCSTR lpValueName, BYTE a3)
{
  const CHAR *plpValueName1; // esi
  HKEY hKEy; // [esp-14h] [ebp-24h] BYREF
  BYTE v6; // [esp-10h] [ebp-20h] BYREF
  DWORD v7[2]; // [esp-Ch] [ebp-1Ch] BYREF
  LPCSTR plpValueName; // [esp-4h] [ebp-14h]
  BYTE v9[4]; // [esp+0h] [ebp-10h] BYREF
  int Data; // [esp+8h] [ebp-8h]
  DWORD cbData; // [esp+Ch] [ebp-4h]

  gta2::Registry_OpenOrCreateSoundKey(self, &hKEy);
  plpValueName1 = plpValueName;
  v7[0] = 4;
  if ( RegQueryValueExA(hKEy, plpValueName, 0, 0, &v6, v7) )
  {
    if ( RegSetValueExA(hKEy, plpValueName1, 0, 4u, v9, 4u) )
      gta2::debug_log(0x2Eu, "registry.cpp", 138);
    plpValueName = (LPCSTR)cbData;
  }
  if ( RegCloseKey((HKEY)v7[1]) )
    gta2::debug_log(0x2Au, "registry.cpp", 146);
  return Data;
}


// 0x004b5110: Registry::sub_4B5110
// IDA: Registry::sub_4B5110
// Ghidra: ---
LSTATUS gta2::Registry_sub_4B5110(HKEY self, LPCSTR lpValueName, BYTE Data)
{
  LSTATUS result; // eax
  HKEY v4[3]; // [esp-18h] [ebp-1Ch] BYREF
  HKEY v5; // [esp-Ch] [ebp-10h] BYREF

  v4[0] = self;
  if ( gta2::Registry_OpenOrCreateSoundKey((Registry *)self, v4)
    && RegSetValueExA(v4[0], (LPCSTR)v4[2], 0, 4u, (const BYTE *)&v5, 4u) )
  {
    gta2::debug_log(0x2Eu, "registry.cpp", 169);
  }
  result = RegCloseKey(v5);
  if ( result )
    return gta2::debug_log(0x2Au, "registry.cpp", 175);
  return result;
}


// 0x004b5180: Registry::SetSound3DConfigure
// IDA: Registry::SetSound3DConfigure
// Ghidra: ---
LSTATUS gta2::Registry_SetSound3DConfigure(struct Registry *self, LPCSTR lpValueName, char a3)
{
  HKEY hKey; // [esp+0h] [ebp-8h] BYREF
  BYTE Data[4]; // [esp+4h] [ebp-4h] BYREF

  *(_DWORD *)Data = 0;
  if ( gta2::Registry_OpenOrCreateSoundKey(self, &hKey) )
  {
    if ( a3 )
    {
      RegSetValueExA(hKey, lpValueName, 0, 4u, Data, 4u);
      return RegCloseKey(hKey);
    }
    RegDeleteValueA(hKey, lpValueName);
  }
  return RegCloseKey(hKey);
}


// 0x004b51f0: Registry::GetDebugMode
// IDA: Registry::GetDebugMode
// Ghidra: ---
bool gta2::Registry_GetDebugMode(struct Registry *self, PHKEY phkResult)
{
  PHKEY v3; // [esp-4h] [ebp-8h] BYREF

  if ( !RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\DMA Design Ltd\\GTA2\\Debug", 0, 983103u, v3) )
    return 1;
  if ( RegCreateKeyExA(
         HKEY_CURRENT_USER,
         "SOFTWARE\\DMA Design Ltd\\GTA2\\Debug",
         0,
         gSource,
         0,
         983103u,
         0,
         v3,
         (LPDWORD)&v3) )
  {
    gta2::debug_log(0x2Bu, "registry.cpp", 232);
  }
  return 0;
}


// 0x004b5260: Registry::OpenOrCreateLanguageKey
// IDA: Registry::OpenOrCreateLanguageKey
// Ghidra: ---
bool gta2::Registry_OpenOrCreateLanguageKey(void *self, PHKEY phkResult)
{
  PHKEY v3; // [esp-4h] [ebp-8h] BYREF

  if ( !RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\DMA Design Ltd\\GTA2\\Option", 0, 983103u, v3) )
    return 1;
  if ( RegCreateKeyExA(
         HKEY_CURRENT_USER,
         "SOFTWARE\\DMA Design Ltd\\GTA2\\Option",
         0,
         gSource,
         0,
         0xF003Fu,
         0,
         v3,
         (LPDWORD)&v3) )
  {
    gta2::debug_log(0x2Bu, "registry.cpp", 265);
  }
  return 0;
}


// 0x004b52d0: Registry::sub_4B52D0
// IDA: Registry::sub_4B52D0
// Ghidra: ---
char gta2::Registry_sub_4B52D0(struct Registry *self, PHKEY phkResult)
{
  PHKEY v3; // [esp-4h] [ebp-8h] BYREF

  if ( !RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\DMA Design Ltd\\GTA2\\Control", 0, 0xF003Fu, v3) )
    return 1;
  if ( RegCreateKeyExA(
         HKEY_CURRENT_USER,
         "SOFTWARE\\DMA Design Ltd\\GTA2\\Control",
         0,
         gSource,
         0,
         0xF003Fu,
         0,
         v3,
         (LPDWORD)&v3) )
  {
    gta2::debug_log(0x2Bu, "registry.cpp", 298);
  }
  return 0;
}


// 0x004b5340: Registry::OpenOrCreateScreenKey
// IDA: Registry::OpenOrCreateScreenKey
// Ghidra: ---
char gta2::Registry_OpenOrCreateScreenKey(PHKEY phkResult)
{
  PHKEY v2; // [esp-4h] [ebp-8h] BYREF

  if ( !RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\DMA Design Ltd\\GTA2\\Screen", 0, 0xF003Fu, v2) )
    return 1;
  if ( RegCreateKeyExA(
         HKEY_CURRENT_USER,
         "SOFTWARE\\DMA Design Ltd\\GTA2\\Screen",
         0,
         gSource,
         0,
         0xF003Fu,
         0,
         v2,
         (LPDWORD)&v2) )
  {
    gta2::debug_log(0x2Bu, "registry.cpp", 331);
  }
  return 0;
}


// 0x004b53b0: Registry::GetPlayReplay
// IDA: Registry::GetPlayReplay
// Ghidra: ---
bool gta2::Registry_GetPlayReplay(struct Registry *self, LPCSTR lpValueName)
{
  bool v2; // bl
  HKEY v4; // [esp-8h] [ebp-18h] BYREF
  DWORD v5; // [esp-4h] [ebp-14h] BYREF
  BYTE v6[4]; // [esp+0h] [ebp-10h] BYREF
  DWORD cbData; // [esp+8h] [ebp-8h]

  v2 = 0;
  if ( gta2::Registry_GetDebugMode(self, &v4) )
  {
    v5 = 4;
    v2 = RegQueryValueExA(v4, (LPCSTR)cbData, 0, 0, v6, &v5) == 0;
  }
  if ( RegCloseKey(v4) )
    gta2::debug_log(0x2Au, "registry.cpp", 424);
  return v2;
}


// 0x004b5420: Registry::ReadKeyMap
// IDA: Registry::ReadKeyMap
// Ghidra: ---
LSTATUS gta2::Registry_ReadKeyMap(struct Registry *self, LPCSTR lpValueName, LPBYTE lpData, DWORD dataSize)
{
  LSTATUS result; // eax
  HKEY hKey; // [esp-Ch] [ebp-14h] BYREF
  DWORD v6[4]; // [esp-8h] [ebp-10h] BYREF
  _UNKNOWN *retaddr; // [esp+8h] [ebp+0h]

  if ( gta2::Registry_GetDebugMode(self, &hKey) )
  {
    v6[0] = (unsigned __int16)retaddr;
    RegQueryValueExA(hKey, (LPCSTR)v6[2], 0, 0, (LPBYTE)v6[3], v6);
  }
  result = RegCloseKey(hKey);
  if ( result )
    return gta2::debug_log(0x2Au, "registry.cpp", 531);
  return result;
}


// 0x004b5490: Registry::GetLanguage
// IDA: Registry::GetLanguage
// Ghidra: ---
LSTATUS gta2::Registry_GetLanguage(struct Registry *self, LPCSTR lpValueName, HKEY hKey, int a3)
{
  HKEY _HKEY; // esi
  LSTATUS result; // eax
  LPDWORD v6; // [esp-8h] [ebp-10h] BYREF
  LPCSTR v7; // [esp+0h] [ebp-8h]
  HKEY cbData; // [esp+4h] [ebp-4h] BYREF
  LPDWORD retaddr; // [esp+8h] [ebp+0h]

  _HKEY = cbData;
  *(_BYTE *)cbData = 0;
  if ( gta2::Registry_OpenOrCreateLanguageKey(self, &cbData) )
  {
    v6 = (LPDWORD)(unsigned __int16)retaddr;
    RegQueryValueExA(cbData, v7, 0, 0, (LPBYTE)_HKEY, (LPDWORD)&v6);
  }
  result = RegCloseKey(cbData);
  if ( result )
    return gta2::debug_log(0x2Au, "registry.cpp", 586);
  return result;
}


// 0x004b5500: Registry::sub_4B5500
// IDA: Registry::sub_4B5500
// Ghidra: ---
int gta2::Registry_sub_4B5500(struct Registry *self, LPCSTR lpValueName, BYTE a3)
{
  const CHAR *v3; // esi
  HKEY v5; // [esp-14h] [ebp-24h] BYREF
  BYTE v6; // [esp-10h] [ebp-20h] BYREF
  DWORD v7[2]; // [esp-Ch] [ebp-1Ch] BYREF
  LPCSTR v8; // [esp-4h] [ebp-14h]
  BYTE v9[4]; // [esp+0h] [ebp-10h] BYREF
  int Data; // [esp+8h] [ebp-8h]
  DWORD cbData; // [esp+Ch] [ebp-4h]

  gta2::Registry_OpenOrCreateLanguageKey(self, &v5);
  v3 = v8;
  v7[0] = 4;
  if ( RegQueryValueExA(v5, v8, 0, 0, &v6, v7) )
  {
    if ( RegSetValueExA(v5, v3, 0, 4u, v9, 4u) )
      gta2::debug_log(0x2Eu, "registry.cpp", 622);
    v8 = (LPCSTR)cbData;
  }
  if ( RegCloseKey((HKEY)v7[1]) )
    gta2::debug_log(0x2Au, "registry.cpp", 629);
  return Data;
}


// 0x004b55a0: Registry::sub_4B55A0
// IDA: Registry::sub_4B55A0
// Ghidra: ---
HKEY gta2::Registry_sub_4B55A0(struct Registry *self, int a2, BYTE a3)
{
  HKEY v4; // [esp-18h] [ebp-28h] BYREF
  BYTE v5; // [esp-14h] [ebp-24h] BYREF
  char v6; // [esp-10h] [ebp-20h] BYREF
  HKEY v7[2]; // [esp-Ch] [ebp-1Ch] BYREF
  unsigned __int8 v8; // [esp-4h] [ebp-14h]
  HKEY hKey[2]; // [esp+0h] [ebp-10h] BYREF
  DWORD cbData; // [esp+Ch] [ebp-4h]

  gta2::Registry_sub_4B52D0(self, &v4);
  v7[0] = (HKEY)4;
  strcpy(&v6, "%d", v8);
  if ( RegQueryValueExA(v4, &v6, 0, 0, &v5, (LPDWORD)v7) )
  {
    if ( RegSetValueExA(v4, &v6, 0, 4u, (const BYTE *)hKey, 4u) )
      gta2::debug_log(0x2Eu, "registry.cpp", 667);
    v7[1] = (HKEY)cbData;
  }
  if ( RegCloseKey(v7[0]) )
    gta2::debug_log(0x2Au, "registry.cpp", 674);
  return hKey[1];
}


// 0x004b5660: Registry::ConfigSetScreen
// IDA: Registry::ConfigSetScreen
// Ghidra: ---
int gta2::Registry_ConfigSetScreen(void *self, LPCSTR lpValueName, BYTE a2)
{
  const CHAR *v3; // esi
  HKEY hKey; // [esp-14h] [ebp-24h] BYREF
  BYTE Data_1[4]; // [esp-10h] [ebp-20h] BYREF
  DWORD v7[2]; // [esp-Ch] [ebp-1Ch] BYREF
  LPCSTR v8; // [esp-4h] [ebp-14h]
  BYTE v9[4]; // [esp+0h] [ebp-10h] BYREF
  int Data; // [esp+8h] [ebp-8h]
  DWORD cbData; // [esp+Ch] [ebp-4h]

  gta2::Registry_OpenOrCreateScreenKey(&hKey);
  v3 = v8;
  v7[0] = 4;
  if ( RegQueryValueExA(hKey, v8, 0, 0, Data_1, v7) )
  {
    if ( RegSetValueExA(hKey, v3, 0, 4u, v9, 4u) )
      gta2::debug_log(46u, "registry.cpp", 709);
    v8 = (LPCSTR)cbData;
  }
  if ( RegCloseKey((HKEY)v7[1]) )
    gta2::debug_log(0x2Au, "registry.cpp", 716);
  return Data;
}


// 0x004b5700: Registry::ConfigureWindowSize
// IDA: Registry::ConfigureWindowSize
// Ghidra: ---
LSTATUS gta2::Registry_ConfigureWindowSize(struct Registry *self, LPCSTR lpValueName, BYTE Data)
{
  LSTATUS result; // eax
  HKEY v4[3]; // [esp-18h] [ebp-1Ch] BYREF
  HKEY v5; // [esp-Ch] [ebp-10h] BYREF

  v4[0] = (HKEY)self;
  gta2::Registry_OpenOrCreateScreenKey(v4);
  if ( RegSetValueExA(v4[0], (LPCSTR)v4[2], 0, 4u, (const BYTE *)&v5, 4u) )
    gta2::debug_log(0x2Eu, "registry.cpp", 743);
  result = RegCloseKey(v5);
  if ( result )
    return gta2::debug_log(0x2Au, "registry.cpp", 745);
  return result;
}


// 0x004b5770: Registry::VideoGraphics
// IDA: Registry::VideoGraphics
// Ghidra: ---
LSTATUS gta2::Registry_VideoGraphics(struct Registry *self, LPCSTR lpValueName, LPBYTE lpData, int a4)
{
  const BYTE *v4; // esi
  const CHAR *v5; // edi
  LSTATUS result; // eax
  HKEY hKey; // [esp-10h] [ebp-20h] BYREF
  DWORD v8; // [esp-Ch] [ebp-1Ch] BYREF
  CHAR *lpValueName_1; // [esp-4h] [ebp-14h]
  LPBYTE v10; // [esp+0h] [ebp-10h]
  unsigned __int16 v11; // [esp+4h] [ebp-Ch]

  gta2::Registry_OpenOrCreateScreenKey(&hKey);
  v4 = v10;
  v5 = lpValueName_1;
  v8 = v11;
  if ( RegQueryValueExA(hKey, lpValueName_1, 0, 0, v10, &v8)
    && RegSetValueExA(hKey, v5, 0, 1u, v4, strlen((const char *)v4) + 1) )
  {
    gta2::debug_log(0x2Eu, "registry.cpp", 781);
  }
  result = RegCloseKey((HKEY)lpValueName_1);
  if ( result )
    return gta2::debug_log(0x2Au, "registry.cpp", 787);
  return result;
}


// 0x004b58e0: Registry::GetNetworkKey
// IDA: Registry::GetNetworkKey
// Ghidra: ---
char gta2::Registry_GetNetworkKey(struct Registry *self, PHKEY phkResult)
{
  int v2; // eax
  char v3; // cl
  unsigned int v4; // eax
  char *v5; // edi
  DWORD v8; // [esp-Ch] [ebp-114h] BYREF
  CHAR v9[8]; // [esp-8h] [ebp-110h] BYREF
  PHKEY v10; // [esp+100h] [ebp-8h]

  v2 = 0;
  do
  {
    v3 = byte_574564[v2];
    v9[v2++] = v3;
  }
  while ( v3 );
  v4 = strlen("\\Network") + 1;
  v5 = (char *)&v8 + 3;
  while ( *++v5 )
    ;
  qmemcpy(v5, "\\Network", v4);
  if ( RegCreateKeyExA(hKey, v9, 0, gSource, 0, 983103u, 0, v10, &v8) )
    gta2::debug_log(0x2Bu, "registry.cpp", 910);
  return 1;
}


// 0x004b5980: Registry::sub_4B5980
// IDA: Registry::sub_4B5980
// Ghidra: ---
LPCSTR gta2::Registry_sub_4B5980(struct Registry *self, HKEY hKey, LPCSTR pProtocol)
{
  DWORD cbData; // [esp+0h] [ebp-4h] BYREF

  cbData = 4;
  if ( RegQueryValueExA(hKey, pProtocol, 0, (LPDWORD)&hKey, (LPBYTE)&pProtocol, &cbData) )
    return 0;
  else
    return pProtocol;
}


// 0x004b5ae0: Registry::SetShowPlayerName
// IDA: Registry::SetShowPlayerName
// Ghidra: ---
int gta2::Registry_SetShowPlayerName(struct Registry *self, LPCSTR lpValueName, BYTE a3)
{
  const CHAR *v3; // esi
  HKEY hKey; // [esp-14h] [ebp-24h] BYREF
  BYTE v6; // [esp-10h] [ebp-20h] BYREF
  DWORD v7[2]; // [esp-Ch] [ebp-1Ch] BYREF
  LPCSTR v8; // [esp-4h] [ebp-14h]
  BYTE v9[4]; // [esp+0h] [ebp-10h] BYREF
  int Data; // [esp+8h] [ebp-8h]
  DWORD cbData; // [esp+Ch] [ebp-4h]

  gta2::Registry_GetNetworkKey(self, &hKey);
  v3 = v8;
  v7[0] = 4;
  if ( RegQueryValueExA(hKey, v8, 0, 0, &v6, v7) )
  {
    if ( RegSetValueExA(hKey, v3, 0, 4u, v9, 4u) )
      gta2::debug_log(0x2Eu, "registry.cpp", 1051);
    v8 = (LPCSTR)cbData;
  }
  if ( RegCloseKey((HKEY)v7[1]) )
    gta2::debug_log(0x2Au, "registry.cpp", 1058);
  return Data;
}


// 0x004b5b80: Registry::sub_4B5B80
// IDA: Registry::sub_4B5B80
// Ghidra: ---
LSTATUS gta2::Registry_sub_4B5B80(struct Registry *self, LPCSTR lpValueName, BYTE Data)
{
  LSTATUS result; // eax
  HKEY v4[3]; // [esp-18h] [ebp-1Ch] BYREF
  HKEY v5; // [esp-Ch] [ebp-10h] BYREF

  v4[0] = (HKEY)self;
  if ( gta2::Registry_GetNetworkKey(self, v4) && RegSetValueExA(v4[0], (LPCSTR)v4[2], 0, 4u, (const BYTE *)&v5, 4u) )
    gta2::debug_log(0x2Eu, "registry.cpp", 1080);
  result = RegCloseKey(v5);
  if ( result )
    return gta2::debug_log(0x2Au, "registry.cpp", 1086);
  return result;
}


// 0x004b5bf0: Registry::GetNamePlayer
// IDA: Registry::GetNamePlayer
// Ghidra: ---
char gta2::Registry_GetNamePlayer(struct Registry *self, PHKEY a2)
{
  PHKEY v3; // [esp-4h] [ebp-8h] BYREF

  if ( !RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\DMA Design Ltd\\GTA2\\Player", 0, 0xF003Fu, v3) )
    return 1;
  if ( RegCreateKeyExA(
         HKEY_CURRENT_USER,
         "SOFTWARE\\DMA Design Ltd\\GTA2\\Player",
         0,
         gSource,
         0,
         0xF003Fu,
         0,
         v3,
         (LPDWORD)&v3) )
  {
    gta2::debug_log(0x2Bu, "registry.cpp", 1110);
  }
  return 0;
}


// 0x004b5c60: Registry::sub_4B5C60
// IDA: Registry::sub_4B5C60
// Ghidra: ---
int gta2::Registry_sub_4B5C60(struct Registry *self, LPCSTR lpValueName)
{
  PHKEY v3; // [esp-Ch] [ebp-18h] BYREF
  Registry v4; // [esp-8h] [ebp-14h] BYREF
  HKEY hKey; // [esp+4h] [ebp-8h]

  if ( gta2::Registry_GetNamePlayer(&v4, v3) )
  {
    v4.field_4 = 4;
    if ( RegQueryValueExA((HKEY)v4.field_0, (LPCSTR)hKey, 0, 0, (LPBYTE)&v3, (LPDWORD)&v4.field_4) )
      v3 = 0;
  }
  else
  {
    v3 = 0;
    if ( RegSetValueExA((HKEY)v4.field_0, (LPCSTR)hKey, 0, 4u, (const BYTE *)&v3, 4u) )
      gta2::debug_log(0x2Eu, "registry.cpp", 1143);
  }
  if ( RegCloseKey((HKEY)v4.field_0) )
    gta2::debug_log(0x2Au, "registry.cpp", 1149);
  return *(_DWORD *)&v4.field_8;
}


// 0x004b5d10: Registry::GetPlayerName
// IDA: Registry::GetPlayerName
// Ghidra: ---
LSTATUS gta2::Registry_GetPlayerName(struct Registry *self, LPCSTR lpValueName, BYTE Data)
{
  LSTATUS result; // eax
  Registry v4; // [esp-18h] [ebp-1Ch] BYREF
  HKEY v5; // [esp-Ch] [ebp-10h] BYREF

  if ( gta2::Registry_GetNamePlayer(&v4, (PHKEY)self)
    && RegSetValueExA((HKEY)v4.field_0, *(LPCSTR *)&v4.field_8, 0, 4u, (const BYTE *)&v5, 4u) )
  {
    gta2::debug_log(0x2Eu, "registry.cpp", 1171);
  }
  result = RegCloseKey(v5);
  if ( result )
    return gta2::debug_log(0x2Au, "registry.cpp", 1177);
  return result;
}


// 0x004b5d80: Registry::UseNet
// IDA: Registry::UseNet
// Ghidra: ---
bool gta2::Registry_UseNet(struct Registry *self, HKEY hKey, char *pText, int a3, LPBYTE lpData)
{
  DWORD cbData; // [esp+10h] [ebp-108h] BYREF
  CHAR ValueName[260]; // [esp+14h] [ebp-104h] BYREF

  strcpy(ValueName, (char *)&gTextUse, pText);
  cbData = (DWORD)gta2::Registry_sub_4B5980(self, hKey, ValueName);
  if ( cbData != a3 )
    return 0;
  strcpy(ValueName, (char *)off_574658, pText);
  return RegQueryValueExA(hKey, ValueName, 0, 0, lpData, &cbData) == 0;
}


// 0x004b5e20: Registry::UseConnectConfig
// IDA: Registry::UseConnectConfig
// Ghidra: ---
LPCSTR gta2::Registry_UseConnectConfig(struct Registry *self, HKEY hKey, char *pText)
{
  CHAR ValueName[260]; // [esp+4h] [ebp-104h] BYREF

  strcpy(ValueName, (char *)&gTextUse, pText);
  return gta2::Registry_sub_4B5980(self, hKey, ValueName);
}



