
#ifndef __PEDMANAGER_H_
#define __PEDMANAGER_H_
#include "../global.h"
#include "../Ped/Ped.h"

class PedManager{
    public:
        Ped* FirstElement;
        Ped* NextPed;
        Ped ArrayPed[200];
        short PedInUse;
        PedManager();
        ~PedManager();
    // 0x00403890
    int GetPed(void);
    // 0x00435530
    int GetNextPed(void);
    // 0x0043DB40
    int SpawnPedAtPosition(void);
    // 0x00445960
    int UpdatePeds(void);
};

#endif // !__PEDMANAGER_H_