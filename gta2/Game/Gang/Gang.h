
#ifndef __GANG_H_
#define __GANG_H_
#include "../Weapon/Weapon.h"
typedef enum GANG {
    Yakuza = 0u,
    Zaibatsu_Corporation = 1u,
    Loonies = 2u,
    GANG_3 = 3u,
    GANG_4 = 4u,
    GANG_5 = 5u,
    GANG_6 = 6u,
    GANG_7 = 7u,
    GANG_8 = 8u,
    GANG_9 = 9u,
    GANG_10 = 10u,
}GANG;

class Gang{
    public:

        bool  Status;
        int CurrentGang;
        char NameGang[10];
        char remap;
        char pad;
        bool MaxOut;
        char Reting;
        int Prestige;
        char WarMaskGang[10];
        int X;
        int Y;
        int Z;
        int NextGang;
        bool Visible;
        char field_13A;
        char field_13B;
        int  CarType;
        char CarRemap;
        Weapon* Weapon3;
        Weapon* Weapon2;
        Weapon* Weapon1;
        Gang();
        ~Gang();

       
    // 0x00433B30
    int Get_Pararam0x111(void);
    // 0x0045D920 undefined * __thiscall
    void* SetCurrentGangName(void);
    // 0x0045DA80
    int DecreaseRespect(void);
    int IncreaseRespect(int ID, int count);
    // 0x0045DAC0
    int getWarMaskGang(void);
    int GetRespect(int ID);
    // 0x0045DB40
    int SetName(void);
    // 0x0045DD50
    int GetVisibleGang(void);
    // 0x0045DE10
    int UpdateRespect(void);
    // 0x0045DEA0
    int ChangeRespect(void);
    // 0x00475900
    int Set_475900(void);
    int  SetRespect(int id, char CountRespect);


// ==== импорт имён из gm ====
    // 10 функций
    // 0x0045D9E0: Gang::GetRespectForGang
    void GetRespectForGang();
    // 0x0045DAE0: Gang::IsPlayerHated
    void IsPlayerHated();
    // 0x004C54C0: Gang::UpdatePed
    void UpdatePed();
    // 0x004C54F0: Gang::IsPedClear
    void IsPedClear();
    // 0x004C5510: Gang::SpawnNextPed
    void SpawnNextPed();
    // 0x004C55D0: Gang::ProcessPeds
    void ProcessPeds();
    // 0x004C5A00: Gang::UpdatePedStates
    void UpdatePedStates();
    // 0x004C5CA0: Gang::UpdateCar
    void UpdateCar();
    // 0x004C5E00: Gang::UpdateCountdown
    void UpdateCountdown();
    // 0x004C5F10: Gang::GetSpawnCount
    void GetSpawnCount();
};
#endif // !__GANG_H_