#pragma once


class Registry{

public:

	bool GetPlayReplay(LPCSTR lpValueName);
	bool GetDebugMode(PHKEY phkResult);
	BYTE GetReplaynum(LPCSTR lpValueName);
	LSTATUS SetDebugByteValue(LPCSTR lpValueName, BYTE value);
	bool GetParamDebug(LPCSTR lpValueName);
	bool SetShowPlayerName(LPCSTR lpValueName, BYTE value);
	bool GetNetworkKey(PHKEY phkResult);
	LSTATUS ReadKeyMap(LPCSTR lpValueName, LPBYTE lpData, DWORD dataSize);
	bool OpenOrCreateSoundKey(PHKEY phkResult);
	char ConfigureSoundSetting(LPCSTR lpValueName, BYTE value);
	bool OpenOrCreateScreenKey(PHKEY phkResult);
	BYTE* ConfigVideo(LPCSTR lpValueName, BYTE value);
	BYTE ConfigSetScreen(LPCSTR lpValueName, BYTE value);
	LSTATUS SetVideoName(LPCSTR lpValueName, LPBYTE lpData, DWORD dataSize);
	
	
};
