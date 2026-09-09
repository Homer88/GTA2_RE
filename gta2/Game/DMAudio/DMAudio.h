#ifndef __DMAUDIO_H_
#define __DMAUDIO_H_

class DMAudio{

    public:

    // 0x00410500
    int Initialise(void);
    // 0x00410510
    int Shutdown(void);
    // 0x00410520
    int PollAllSamples(void);
    // 0x00410530
    int AddAudioObject(void);
    // 0x00410540
    int FreeSample(void);
    // 0x00410550
    int LoadSTY(void);
    // 0x00410560
    int Service(void);
    // 0x00410570
    int S157(void);
    // 0x004105A0
    int SetEventListener(void);
    // 0x004105B0
    int PlayVocal(void);
    // 0x004105C0
    int SFXVol(void);
    // 0x00410600
    int SetCDVol(void);
    // 0x00410630
    int GetCDVol(void);
    // 0x00410640
    int ShutdownAudioStream(void);
    // 0x00410650
    int ResetChannels(void);
    // 0x00410660
    int IsInitialised(void);
    // 0x00410670
    int Init3DSound(void);
    // 0x00410680
    int Get3DSound(void);
    // 0x004106D0
    int CameraOrPhysicsReset(void);
    // 0x00410750
    int PlaySound(void);
};

#endif // !__DMAUDIO_H_
