
#ifndef __CARSYSTEMMANAGER_H_
#define __CARSYSTEMMANAGER_H_


class CarSystemManager{
    public:
        int field_0;       // 0x00
        int Index;         // 0x04
        int field_2;
        
      CarSystemManager();
      ~CarSystemManager();
    // 0x00401C10
    int ClampValues();
    // 0x00401C40
    int AddCarToSystem();
    // 0x00401C60
    int CarPool_Get();
    // 0x00401C80
    int PedPool_Get();
    // 0x0040E590
    int SetIndexDefautCarManager();
    // 0x0040E5A0
    int GetCarFromPool();
    // 0x0040E670
    int greater_than();
    // 0x0041E0F0
    int less_than();
    // 0x00420A10
    int SetupCarLists();
    // 0x00420C00
    int UpdateFreeShopping();
    // 0x00420CE0
    int CanAddCar();
    // 0x004212D0
    int GetIndexedValue();
    // 0x00421960
    int GetDummyDriver();
    // 0x00426E10
    int SpawnCar();
    // 0x00426E40
    int SpawnCarAtPos();
    // 0x00428EC0
    int CreateCarWithTurret();
    // 0x00428F70
    int InitialiseCar();
    // 0x00447CB0
    int PrepareArray();
    // 0x00447D30
    int AdvanceIndex();
    // 0x004C39F0
    int CycleMode();


// ==== импорт имён из gm ====
    // 7 функций
    // 0x00476660: CarSystemManager::GetCarAttr
    void GetCarAttr();
    // 0x00476680: CarSystemManager::ClearCarSlot
    void ClearCarSlot();
    // 0x00476B20: CarSystemManager::ResetIndex
    void ResetIndex();
    // 0x00476B30: CarSystemManager::InitCarSystems
    void InitCarSystems();
    // 0x00476B80: CarSystemManager::InitCarPools
    void InitCarPools();
    // 0x0047F520: CarSystemManager::InitializeAll
    void InitializeAll();
    // 0x004955F0: CarSystemManager::SpawnAtWorldPos
    void SpawnAtWorldPos();
};
#endif // !__CARSYSTEMMANAGER_H_