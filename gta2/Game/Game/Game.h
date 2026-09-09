#ifndef __GAME_H_
#define __GAME_H_

class Game{

    public:

    // 0x003F113C
    int GetCurrentPlayerSlot(void);
    // 0x003F11A8
    int FindNextActivePlayer(void);
    // 0x003F1208
    int SwitchToNextPlayer(void);
    // 0x003F12A8
    int CycleToNextPlayer(void);
    // 0x003F1314
    int CheckPlayerLimit(void);
    // 0x003F1338
    int ValidatePlayerAction(void);
    // 0x003F135C
    int _ShouldPauseGame(void);
    // 0x00416BC0
    int GetIsUserPaused(void);
    // 0x004219E0
    int GetPlayerSlotByIndex(void);
    // 0x0045A460
    int GetFrameTimeStep(void);
    // 0x0045A4D0
    int Over(void);
    // 0x0045A540
    int SetSkipPolice(void);
    // 0x0045A5A0
    int RenderFrame(void);
    // 0x0045A650
    int UpdatePlayers(void);
    // 0x0045A690
    int SetArmor(void);
    // 0x0045A6E0
    int SetStatusMode2(void);
    // 0x0045A6F0
    int IsInCar(void);
    // 0x0045A700
    int EndGameSession(void);
    // 0x0045A800
    int GetFirstActiveCamera(void);
    // 0x0045A850
    int GetNextActiveCamera(void);
    // 0x0045A910
    int GetNextPlayer(void);
    // 0x0045ACF0
    int is1(void);
    // 0x0045B469
    int LoadResources(void);
    // 0x0045B5F0
    int StartGameSession(void);
    // 0x0045B750
    int DrawDebugCounters(void);
    // 0x0045BA10
    int DrawDebugOverlay(void);
    // 0x0045BA60
    int SetStatusMode1(void);
    // 0x0045BAA0
    int SwitchUserPause(void);
    // 0x0045BAB0
    int GetNextInactivePlayer(void);
    // 0x0045BB00
    int UpdateVisionForAllCameras(void);
    // 0x0045BC90
    int IsPointVisibleToAnyPlayer(void);
    // 0x0045BD00
    int IsCarOccupiedByAnyPlayer(void);
    // 0x0045C1F0
    int Tick(void);
    // 0x0045C3B0
    int Frame(void);
    // 0x0045D3D0
    int Destr(void);
    // 0x00476790
    int GetIDs(void);
    // 0x004A4750
    int ToggleField30(void);
    // 0x004C7380 void * __thiscall
    void* GetPlayerById(int arg0);
    // 0x004D09C0
    int GetState(void);
};

#endif // !__GAME_H_
