
#ifndef __PEDMANAGER_H_
#define __PEDMANAGER_H_
class Ped;


class PedManager{
    public:
        Ped* FirstPed;
        Ped* NextPed; //возможно имя currentPed
        Ped ArrayPed[200];
        short PedInUse;
        PedManager();
        ~PedManager();
    // 0x00403890
    Ped* GetPed(void);
    // 0x00435530
    Ped* GetNextPed(void);
    // 0x0043DB40
    int SpawnPedAtPosition(void);
    // 0x00445960
    int UpdatePeds(void);
};

#endif // !__PEDMANAGER_H_