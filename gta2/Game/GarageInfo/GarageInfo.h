#ifndef __GARAGEINFO_H_
#define __GARAGEINFO_H_

class GarageInfo{

    public:

    // 0x0045D390
    int DestroyCarGenerators(void);
    // 0x004C6290
    int UpdateCarGen(void);
    // 0x004C62B0
    int UpdateCarGenerators(void);
    // 0x004C7120
    int S166_Set_004c7120(void);
    // 0x004C7160
    int S166_Get_004c7160(void);
    // 0x004C7170
    int S166_Get_004c7170(void);
    // 0x004C7250
    int GetPedType(void);
    // 0x004C9310
    int FindFreeCarGenerator(void);
    // 0x004C93B0
    int DestroyCarGenerator(void);
};

#endif // !__GARAGEINFO_H_
