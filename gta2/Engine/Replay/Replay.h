
#ifndef __REPLAY_H_
#define __REPLAY_H_


class Replay{
    public:

    // 0x003F154C
    int PlaySegment(void);
    // 0x003F1574
    int StartPlayback(void);
    // 0x003F158C
    int ProcessReplayData(void);
    // 0x0044AA60
    int IsPlayingBack(void);
    // 0x0044AA80
    int GetTotalFrames(void);
    // 0x0044C050
    int GetButton(void);
    // 0x0045AD90
    int ClearControls(void);
    // 0x0045ED00
    int SetPararam0x4(void);
    // 0x0045ED10
    int SetButton(void);
    // 0x0045ED30
    int ClearButton(void);
    // 0x0045EEC0
    int WriteHeader(void);
    // 0x0045F270
    int ReadHeader(void);
    // 0x0045F600
    int GetNextDataAttractAtt(void);
    // 0x0045F640
    int OpenReplayFile(void);
    // 0x0045F900
    int DisplayDebug(void);
    // 0x0045F970
    int IsPlaybackMode(void);
    // 0x0045F990
    int DisplayStatus(void);
    // 0x0045FA00
    int Reset(void);
    // 0x0045FA50
    int WriteFrame(void);
    // 0x0045FB10
    int SaveReplay(void);
    // 0x0045FD10
    int GetBufferState(void);
    // 0x004D09B0
    int SetEnabled(void);


// ==== импорт имён из gm ====
    // 1 функций
    // 0x0045F9F0: Replay::ClearControlFlag
    void ClearControlFlag();
};
#endif // !__REPLAY_H_