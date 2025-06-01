#include <windows.h>
#include "Registry.h"
#include "DebugLogFile.h"

Registry gRegistry;

bool Registry::GetPlayReplay(LPCSTR lpValueName){
	bool v2= false; // bl
  HKEY hKey; // [esp-8h] [ebp-18h] BYREF
  BYTE Data; // [esp+0h] [ebp-10h] BYREF
  DWORD cbData=4; // [esp+8h] [ebp-8h]

	if (this->GetDebugMode(&hKey)){
     
		v2 = RegQueryValueExA(hKey, lpValueName, 0, 0, &Data, &cbData) == 0;
		}
	if ( RegCloseKey(hKey) )
		 DebugLog(0x2Au, "registry.cpp", 424);
	return v2;
}

bool Registry::GetDebugMode(PHKEY phkResult){

	if (!phkResult) return false;
	
	const char* DEBUG_KEY="SOFTWARE\\DMA Design Ltd\\GTA2\\Debug";

  if ( !RegOpenKeyExA(HKEY_CURRENT_USER, DEBUG_KEY, 0, 983103, phkResult) )
    return true;
  if ( RegCreateKeyExA(HKEY_CURRENT_USER,DEBUG_KEY, 0, NULL, 0, 983103, 0, phkResult,
         (LPDWORD)&phkResult) )
  {  
    DebugLog(0x2Bu, "registry.cpp", 232);
    return false;
  }


}

LSTATUS Registry::SetDebugByteValue(LPCSTR lpValueName, BYTE value){

	HKEY hKey = NULL;
	DWORD type = REG_SZ;
    
    // 1. Получаем ключ реестра для отладки
    this->GetDebugMode(&hKey);
    RegSetValueExA(hKey, lpValueName, 0, 4, &value,4 );
    return RegCloseKey(hKey);


}



bool Registry::GetParamDebug(LPCSTR lpValueName){
    HKEY hKey; // [esp-8h] [ebp-18h] BYREF
    BYTE Data; // [esp+0h] [ebp-10h] BYREF
    DWORD cbData = 4; // [esp+8h] [ebp-8h]

    if (this->GetDebugMode(&hKey)) {

        return  RegQueryValueExA(hKey, lpValueName, 0, 0, &Data, &cbData) == 0;
    }
    if (RegCloseKey(hKey))
        DebugLog(0x2Au, "registry.cpp", 424);
    return false;
}


BYTE  Registry::GetReplaynum(LPCSTR lpValueName) {
    HKEY hKey;
    BYTE Data[4];
	DWORD cbData=4;
    if (this->GetDebugMode(&hKey)){
		if (RegQueryValueExA(hKey, lpValueName, 0, 0, Data, &cbData)){
			Data[0] = 0;
			if (RegSetValueExA(hKey, lpValueName, 0, 4, Data, 4)){
				DebugLog(0x2E, "registry.cpp", 1040);
			}
		}
        RegCloseKey(hKey);
       return Data[0];
    }
    return 0;
}



bool Registry::SetShowPlayerName(LPCSTR lpValueName, BYTE value) {
    
    HKEY hKey;
    BYTE data[4];
    DWORD cdData = 4;
    this->GetNetworkKey(&hKey);

       
    if (RegQueryValueExA(hKey, lpValueName, 0, 0, data, &cdData)) {
        if (RegSetValueExA(hKey, lpValueName, 0, 4,&value , cdData)) {
            DebugLog(0x2E, "registry.cpp", 1051);
        }
    }
    if (RegCloseKey(hKey))
          DebugLog(0x2Au, "registry.cpp", 1058);
	return data[0] == 1 ? true : false;
}

bool Registry::GetNetworkKey(PHKEY phkResult) {

	if (!phkResult) return false;
	
	const char* NETWORK_KEY="SOFTWARE\\DMA Design Ltd\\GTA2\\Network";
	
	
    if (!RegOpenKeyExA(HKEY_CURRENT_USER, NETWORK_KEY, 0, 983103, phkResult))
        return true;
    if (RegCreateKeyExA(HKEY_CURRENT_USER,
        NETWORK_KEY, 0, NULL, 0,
        983103, 0, phkResult, (LPDWORD)&phkResult))
    {
        DebugLog(0x2Bu, "registry.cpp", 232); 
		return false;
    }
   

}

LSTATUS Registry::ReadKeyMap(LPCSTR lpValueName, LPBYTE lpData, DWORD dataSize){
	
	HKEY hKey;
	
	if (this->GetDebugMode(&hKey)){
		RegQueryValueExA(hKey,lpValueName,NULL,0, lpData, &dataSize);
	}
	LSTATUS result=RegCloseKey(hKey);
	if (result)
	{
		DebugLog(0x2Au, "registry.cpp", 531);
	}
	return result;
	
}



bool Registry::OpenOrCreateSoundKey(PHKEY phkResult){
	
	if (!phkResult) return false;
	
	const char* SOUND_KEY="SOFTWARE\\DMA Design Ltd\\GTA2\\Sound";
	if (!RegOpenKeyExA(HKEY_CURRENT_USER, SOUND_KEY, 0, 983103, phkResult))
		return true;
	if (RegCreateKeyExA(HKEY_CURRENT_USER,SOUND_KEY, 0, NULL, 0,
		983103,0,phkResult,(LPDWORD)&phkResult))
	{
		DebugLog(0x2Bu, "registry.cpp", 232);
		return false;
	}
	
}



char Registry::ConfigureSoundSetting(LPCSTR lpValueName, BYTE value){
	
	HKEY hKey;
	BYTE data[4];
	DWORD cdData[4];
	if (!this->OpenOrCreateSoundKey(&hKey)) return 0;
	
	if (RegQueryValueExA(hKey,lpValueName,0,0,data,cdData))
		if (RegSetValueExA(hKey,lpValueName,0,4,&value,4)){
			DebugLog(0x2Eu, "registry.cpp", 138);
		}
		else {data[0]=value;}
	if (RegCloseKey(hKey))
		DebugLog(0x2Au, "registry.cpp", 146);
	return data[0];
	
}

bool Registry::OpenOrCreateScreenKey(PHKEY phkResult) {
	if (!phkResult) return false;

	const char* SCREEN_KEY = "SOFTWARE\\DMA Design Ltd\\GTA2\\Screen";

	if (!RegOpenKeyExA(HKEY_CURRENT_USER, SCREEN_KEY, 0, 983103, phkResult))
		return true;
	if (RegCreateKeyExA(HKEY_CURRENT_USER, SCREEN_KEY, 0, NULL, 0,
		983103, 0, phkResult, (LPDWORD)&phkResult))
	{
		DebugLog(0x2Bu, "registry.cpp", 331);
		return false;
	}

}
BYTE* Registry::ConfigVideo(LPCSTR lpValueName, BYTE value) {

	HKEY hKey;
	BYTE Data[20];
	DWORD cdData[4];
	DWORD type = REG_SZ;


	this->OpenOrCreateScreenKey(&hKey);

	if (!RegQueryValueExA(hKey, lpValueName, 0, 0, Data, NULL))
		if (RegSetValueExA(hKey, lpValueName, 0, type, &value, 4))
			DebugLog(0x2Eu, "registry.cpp", 709);
	if (RegCloseKey(hKey))
		DebugLog(0x2Au, "registry.cpp", 716);
	return Data;

}


BYTE Registry::ConfigSetScreen(LPCSTR lpValueName, BYTE value) {
	HKEY hKey;
	BYTE Data[4];
	DWORD cdData[4];
	DWORD type = REG_DWORD;


	this->OpenOrCreateScreenKey(&hKey);

	if (RegQueryValueExA(hKey, lpValueName, 0, 0, Data, cdData))
		if (RegSetValueExA(hKey, lpValueName, 0, type, &value, 4)) {
			DebugLog(0x2Eu, "registry.cpp", 709);
			Data[0] = value;
		}
			
	if (RegCloseKey(hKey))
		DebugLog(0x2Au, "registry.cpp", 716);
	return Data[0];
}



LSTATUS Registry::SetVideoName(LPCSTR lpValueName, LPBYTE lpData, DWORD dataSize){
	HKEY hKey;
	
	
	this->OpenOrCreateScreenKey(&hKey);
	if (RegQueryValueExA(hKey, lpValueName, 0, 0, lpData, &dataSize))
		if (RegSetValueExA(hKey, lpValueName, 0, 1, lpData, strlen((const char*)lpData) + 1))
			DebugLog(0x2Eu, "registry.cpp", 781);
	LSTATUS result = RegCloseKey(hKey);
	if (result)
		DebugLog(0x2Au, "registry.cpp", 787);
	return result;
	

	
}


