#ifndef __SAVESLOTANIMATEDVALUE_H_
#define __SAVESLOTANIMATEDVALUE_H_

class SaveSlotAnimatedValue{

    public:

    // 0x0041DC30
    int GetHealth(void);
    // 0x0044B1D0
    int Lives(void);
    // 0x0044B390
    int Animate(void);
    // 0x0045B0A0
    int GetAccurcy(void);
    // 0x004B7490
    int SaveSlotAnimatedValueInitPlayer(void);
    // 0x004B74D0
    int ValueGet(void);
    // 0x004B85B0
    int ValueLogCarEvent(void);
    // 0x004B8870
    int CarDestroyed(void);
    // 0x004B89B0
    int AddCarDamageMoney(void);
    // 0x004B8A60
    int GiveMoney20(void);
};

#endif // !__SAVESLOTANIMATEDVALUE_H_
