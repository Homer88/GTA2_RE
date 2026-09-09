#ifndef __LOADSCREEN_H_
#define __LOADSCREEN_H_

class LoadScreen{

    public:

    // 0x004AF290
    int SetTurnState(void);
    // 0x004AF8A0
    int ReverseTrain(void);
    // 0x004AF9A0
    int AdvanceTurnState(void);
    // 0x004AFA10
    int RegressTurnState(void);
    // 0x004AFA80
    int ForceReverse(void);
    // 0x004AFAB0
    int UpdateTrainComponents(void);
    // 0x004AFAF0
    int UpdateTrainCars(void);
    // 0x004AFB30
    int SpawnPassengers(void);
};

#endif // !__LOADSCREEN_H_
