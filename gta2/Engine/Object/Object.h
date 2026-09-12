
#ifndef __OBJECT_H_
#define __OBJECT_H_


class Object{
    public:
     // 0x004828F0
    int GetSelectionData(void);
    // 0x00483D90
    int CollectGameObjectData(void);
    // 0x00484AD0
    int SetCollisionIndex(void);
    // 0x00484CF0
    int ExitInGameMenu(void);
    // 0x00485540
    int SpawnPedObject(void);
    // 0x00485640
    int SpawnTrains(void);
    // 0x00485E40
    int SpawnPickupObjects(void);
    // 0x00485ED0
    int CreateInitialObjects(void);
    // 0x00484E00
    int SpawnObject(int Type, int x, int y, int z, short rot);
    int SpawnObject(int a, int x, int y, int z);
    // 0x00487ED0
    int RemoveDeadObjects(void);
};

#endif // !__OBJECT_H_