#ifndef __CARSYSTEMMANAGER_H_
#define __CARSYSTEMMANAGER_H_

class CarSystemManager{

    public:

    // 0x00401C10
    int ClampValues(void);
    // 0x00401C40
    int AddCarToSystem(void);
    // 0x00401C60
    int CarPool_Get(void);
    // 0x00401C80
    int PedPool_Get(void);
    // 0x0040E590
    int SetIndexDefautCarManager(void);
    // 0x0040E5A0
    int GetCarFromPool(void);
    // 0x0040E670
    int greater_than(void);
    // 0x0041E0F0
    int less_than(void);
    // 0x00420A10
    int SetupCarLists(void);
    // 0x00420C00
    int UpdateFreeShopping(void);
    // 0x00420CE0
    int CanAddCar(void);
    // 0x004212D0
    int GetIndexedValue(void);
    // 0x00421960
    int GetDummyDriver(void);
    // 0x00426E10
    int SpawnCar(void);
    // 0x00426E40
    int SpawnCarAtPos(void);
    // 0x00428EC0
    int CreateCarWithTurret(void);
    // 0x00428F70
    int CarSystemManagerInitialiseCar(void);
    // 0x00447CB0
    int PrepareArray(void);
    // 0x00447D30
    int AdvanceIndex(void);
    // 0x004C39F0
    int CycleMode(void);
};

#endif // !__CARSYSTEMMANAGER_H_
