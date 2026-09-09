#ifndef __VEHICLEPOOL_H_
#define __VEHICLEPOOL_H_

class VehiclePool{

    public:

    // 0x004BCA80 undefined4 __fastcall
    int IsVehicleControlledByPlayer(int arg0);
    // 0x004BE830 undefined1 __thiscall
    int IsVehicleSpawnable(void);
    // 0x004BE850 byte __thiscall
    unsigned char IsTruckType(void);
    // 0x004BE870
    int CreateVehicle(void);
    // 0x004BECB0
    int RemoveVehicle(void);
    // 0x004BEE10
    int GetVehicleFromPool(void);
};

#endif // !__VEHICLEPOOL_H_
