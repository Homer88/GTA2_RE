
#ifndef __VEHICLEPOOL_H_
#define __VEHICLEPOOL_H_


class VehiclePool{
    public:

    // 0x004BCA80 undefined4 __fastcall
    int IsOwnedByOtherPlayer(int arg0);  // (gm) старый: IsVehicleControlledByPlayer -> IsOwnedByOtherPlayer
    // 0x004BE830 undefined1 __thiscall
    int IsObjectTracked(void);  // (gm) старый: IsVehicleSpawnable -> IsObjectTracked
    // 0x004BE850 byte __thiscall
    unsigned char IsSpecialObject(void);  // (gm) старый: IsTruckType -> IsSpecialObject
    // 0x004BE870
    int CreateVehicle(void);
    // 0x004BECB0
    int RemoveVehicle(void);
    // 0x004BEE10
    int GetVehicleFromPool(void);


// ==== импорт имён из gm ====
    // 1 функций
    // 0x004BEC60: VehiclePool::RemoveByNode
    void RemoveByNode();
};
#endif // !__VEHICLEPOOL_H_