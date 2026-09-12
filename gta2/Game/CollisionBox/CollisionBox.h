
#ifndef __COLLISIONBOX_H_
#define __COLLISIONBOX_H_


class CollisionBox{
    public:

    // 0x00420FF0
    int GetOwnerID(void);
    // 0x00421060
    int IsSpecialType(void);
    // 0x00421080
    int IsUsable(void);
    // 0x004340A0
    int GetFlag(void);
    // 0x004825A0
    int SyncCarPosition(void);
    // 0x004825C0
    int HandleExplosion(void);
    // 0x00482630
    int AddToCheckpoints(void);
    // 0x004826A0
    int RemoveFromCheckpoints(void);
    // 0x004827B0
    int RequestRemoval(void);
    // 0x00482970
    int GetS63(void);
    // 0x00482980
    int SpriteS1SetLinks(void);
    // 0x00482ED0
    int UpdateCarDoor(void);
    // 0x00482F60
    int Deactivate(void);
    // 0x00483C50
    int SetActive(void);
    // 0x00483CC0
    int GetTileStyle(void);
    // 0x00483EA0
    int FreeCollisionBox(void);
    // 0x00484740
    int AttemptEnterCar(void);
    // 0x00484760
    int Cleanup(void);
    // 0x00484880
    int CreateEvent(void);
    // 0x00485FD0
    int UpdateAnimTimer(void);
    // 0x00486060
    int UpdateAnimation(void);
    // 0x00487D70
    int UpdateByType(void);
    // 0x00487E80
    int UpdateObject(void);


// ==== импорт имён из gm ====
    // 1 функций
    // 0x004856E0: CollisionBox::SpawnPedOnCollision
    void SpawnPedOnCollision();
};
#endif // !__COLLISIONBOX_H_