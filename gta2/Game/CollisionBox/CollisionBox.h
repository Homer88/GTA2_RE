
#ifndef __COLLISIONBOX_H_
#define __COLLISIONBOX_H_


class EventHandler;
class SpriteS1;

// Partial IDA layout. Full pool array not represented; use guarded alloc for MOBJ debug spawn.
class CollisionBox {
public:
    EventHandler* FirstElement = nullptr; // +0
    EventHandler* pS63 = nullptr;         // +4

    EventHandler* CollisionBoxAllocHandler();      // 0x4829A0
    EventHandler* CollisionBoxAllocHandlerClear(); // 0x4829C0
    EventHandler* InitFromSpawn(EventHandler* eh, void* nodeId, int x, int y, int z, void* rot); // 0x483990
    int CollisionBoxDeleteHandler(EventHandler* eh); // 0x484D60
    EventHandler* ReleaseHandler(EventHandler* eh);  // 0x484DB0

    int GetOwnerID(void);
    int IsSpecialType(void);
    int IsUsable(void);
    int GetFlag(void);
    int SyncCarPosition(void);
    int HandleExplosion(void);
    int AddToCheckpoints(void);
    int RemoveFromCheckpoints(void);
    int RequestRemoval(void);
    int GetS63(void);
    int SpriteS1SetLinks(void);
    int UpdateCarDoor(void);
    int Deactivate(void);
    int SetActive(void);
    int GetTileStyle(void);
    int FreeCollisionBox(void);
    int AttemptEnterCar(void);
    int Cleanup(void);
    int CreateEvent(void);
    int UpdateAnimTimer(void);
    int UpdateAnimation(void);
    int UpdateByType(void);
    int UpdateObject(void);
    void SpawnPedOnCollision();
};

extern CollisionBox* gCollisionBox;
#endif // !__COLLISIONBOX_H_