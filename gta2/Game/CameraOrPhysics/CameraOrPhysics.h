#ifndef __CAMERAORPHYSICS_H_
#define __CAMERAORPHYSICS_H_

class CameraOrPhysics{

    public:

    // 0x0040FE50
    int SetPararm(void);
    // 0x0040FE60
    int DMAudio(void);
    // 0x0041E010
    int SetFollowTarget(void);
    // 0x0041E410
    int UpdateCurrentState(void);
    // 0x0041EA10
    int ProcessActions(void);
    // 0x0041EAC0
    int thunk_FUN_0041e7a0(void);
    // 0x0041F410
    int FocusOnObject(void);
    // 0x00433E90
    int IsActive(void);
    // 0x00475B60
    int ResetAccuracy(void);
};

#endif // !__CAMERAORPHYSICS_H_
