#ifndef __REGISTRY__H__
#define __REGISTRY__H__


class Registry {

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
	BYTE ConfigureSetScreen(LPCSTR lpValueName, BYTE value);
	LSTATUS SetVideoName(LPCSTR lpValueName, LPBYTE lpData, DWORD dataSize);
	BYTE GetSound3DConfigure(LPCSTR lpValueName);
	LSTATUS SetSound3DConfigure(LPCSTR lpValueName, BYTE value);
	LSTATUS SetConfigureWindowSize(LPCSTR lpValueName, BYTE Data);
	bool OpenOrCreateTextKey(PHKEY phkResult);
	int SetTextConfig(LPCSTR lpValueName, BYTE value);
	bool OpenOrCreateLanguageKey(PHKEY phkResult);
	LSTATUS SetLanguage(LPCSTR lpValueName, BYTE Data);
	LSTATUS GetLanguage(LPCSTR lpValueName, char* Data, int size);

	bool OpenOrCreatePlayerName(PHKEY phkResult);
	LSTATUS SetPlayerName(LPCSTR lpValueName, BYTE Data);
	LSTATUS GetPlayerName(LPCSTR lpValueName, char* Data, int size);
	
};
extern Registry gRegistry;

#endif // !__REGISTRY__H__



