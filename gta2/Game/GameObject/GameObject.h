#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_

class GameObject{

    public:

    // 0x00403900
    int GetVehicle(void);
    // 0x00403910
    int LinkTo(void);
    // 0x004338E0
    int SetPed(void);
    // 0x00433910
    int set_ped_state_1(void);
    // 0x00433920
    int SetSpeed(void);
    // 0x00433A40
    int GetRotation(void);
    // 0x00433A50
    int SetAnimationFrame(void);
    // 0x00433A80
    int GetDoorState(void);
    // 0x00433AC0
    int RefreshSprite(void);
    // 0x00491E40
    int Destroy(void);
    // 0x00493690
    int DropObject(void);
    // 0x00493850
    int AllocateSprite(void);
    // 0x004938A0
    int ApplyEffect(void);
    // 0x00494180
    int UpdateHeight(void);
    // 0x00496880
    int UpdatePed(void);
    // 0x004995A0
    int FindPath(void);
    // 0x0049A560
    int ProcessPedestrian(void);
    // 0x0049B0D0
    int ProcessVehicle(void);
};

#endif // !__GAMEOBJECT_H_
