#ifndef __CARSPREFABS_H_
#define __CARSPREFABS_H_

class CarsPrefabs{

    public:

    // 0x0040F390 undefined4 * __fastcall
    void* InitSinTable(int arg0);
    // 0x0040F400 Ped * __thiscall
    void* GetDriver(void);
    // 0x0040F410 int __thiscall
    int GetOtherCar(int param_1,int param_2);
    // 0x0040F430 void __thiscall
    void LinkCars(int arg0,int param_2);
    // 0x0040F450 void __thiscall
    void AttachPlayers(void);
    // 0x0040F470 void __thiscall
    void RemovePlayers(void);
    // 0x0040F490
    int InitializeCarPrefab(void);
    // 0x0040F4B0 undefined4 __fastcall
    int GetMaxValue(int arg0);
    // 0x0040F4E0 bool __thiscall
    bool IsLessOrEqual(short arg0);
    // 0x0040F500
    int GetPrefabValue(void);
    // 0x0040F520
    int GetPrefabData(void);
    // 0x00420E40 void __fastcall
    void ClearList(int arg0);
    // 0x00420E50
    int GetCar(void);
    // 0x00420E60 void __fastcall
    void ClearCarList(int arg0);
    // 0x00420E70
    int S1(void);
    // 0x00420F20
    int AddCar(void);
    // 0x00420F30
    int RemoveCar(void);
    // 0x00424FF0
    int FindSpawnPoint(void);
    // 0x004253C0
    int S10(void);
    // 0x004253E0
    int S4(void);
    // 0x00425400
    int S5_Destruct(void);
    // 0x004254A0
    int GetCarEnd(void);
    // 0x00426AC0
    int ActualSpawnCar(void);
    // 0x00426D90
    int S2(void);
    // 0x00426DB0
    int S5(void);
    // 0x0042A2D0
    int UpdateCars(void);
    // 0x0045AD30
    int GetCarsCount(void);
};

#endif // !__CARSPREFABS_H_
