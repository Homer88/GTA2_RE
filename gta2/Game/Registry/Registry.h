#ifndef __REGISTRY_H_
#define __REGISTRY_H_

class Registry{

    public:

    // 0x003F13CC
    int GetrRplayNum(void);
    // 0x003F1422
    int LoadSettings(void);
    // 0x003F1458
    int GetReplayNum(void);
    // 0x00405A60
    int GetDialogHandle(void);
    // 0x00405A80
    int S14(void);
    // 0x00406250
    int SetCurrentDialog(void);
    // 0x00406270
    int RegNetwork(void);
    // 0x00406320
    int GetPlayerNameNetwork(void);
    // 0x00407930
    int FindMapFiles(void);
    // 0x0045196F
    int _RegPararm_Cheat(void);
    // 0x004B4F90
    int OpenOrCreateSoundKey(void);
    // 0x004B5000
    int GetSound3DConfigure(void);
    // 0x004B5070
    int ConfigureSound(void);
    // 0x004B5110
    int SetSoundConfig(void);
    // 0x004B5180
    int SetSound3DConfigure(void);
    // 0x004B5260
    int OpenOrCreateTextKey(void);
    // 0x004B52D0
    int OpenOrCreateControlKey(void);
    // 0x004B5340
    int OpenOrCreateScreenKey(void);
    // 0x004B53B0
    int GetPplayReplay(void);
    // 0x004B5420
    int ReadKeyMap(void);
    // 0x004B5490
    int RegConfigureLanguage(void);
    // 0x004B5500
    int SetTextConfig(void);
    // 0x004B55A0
    int RegistryGetControlConfig(void);
    // 0x004B5660
    int ConfigSetScreen(void);
    // 0x004B5700
    int ConfigureWindowSize(void);
    // 0x004B5770
    int VideoGraphics(void);
    // 0x004B58E0
    int GetNetworkKey(void);
    // 0x004B5980
    int ReadInt(void);
    // 0x004B5AE0
    int RegistryGetNetworkConfig(void);
    // 0x004B5B80
    int WriteInt(void);
    // 0x004B5BF0
    int GetNamePlayer(void);
    // 0x004B5C60
    int ReadByte(void);
    // 0x004B5D80
    int UseNet(void);
    // 0x004B5E20
    int UseConnectConfig(void);
};

#endif // !__REGISTRY_H_
