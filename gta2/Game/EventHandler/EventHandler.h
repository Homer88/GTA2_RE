#ifndef __EVENTHANDLER_H_
#define __EVENTHANDLER_H_

class EventHandler{

    public:

    // 0x004210B0
    int IsUncollidable(void);
    // 0x00425760
    int IsCarFlagSet(void);
    // 0x00482490
    int Reset(void);
    // 0x00482560
    int ClearCheckpoints(void);
    // 0x00482790
    int SetOwnerID(void);
    // 0x00482BE0
    int UpdateSpriteFrame(void);
    // 0x00483BA0
    int KnockDoor(void);
    // 0x00483C40
    int UpdateEvents(void);
    // 0x00483D50
    int UpdateWeapon(void);
    // 0x00484910
    int Destroy(void);
    // 0x00484DD0
    int ApplyCollision(void);
    // 0x00485C90
    int SpawnExplosionFX(void);
    // 0x00486390
    int HandleImpact(void);
    // 0x004932D0
    int HandlePedImpact(void);
};

#endif // !__EVENTHANDLER_H_
