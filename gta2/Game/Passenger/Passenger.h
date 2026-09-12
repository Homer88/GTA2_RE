
#ifndef __PASSENGER_H_
#define __PASSENGER_H_


class Passenger{
    public:

    // 0x00420EA0
    int Destructor(void);
    // 0x00435F70
    int RemovePassenger(void);
    // 0x00445F10
    int Add(void);
    // 0x00445F80
    int AddUnique(void);
    // 0x00446010
    int Remove(void);
    // 0x004460D0
    int ClearAll(void);
    // 0x00446120
    int RemoveAll(void);
    // 0x00505CC0
    int Initialise(void);


// ==== импорт имён из gm ====
    // 8 функций
    // 0x00445BD0: Passenger::SyncGroupToLeader
    void SyncGroupToLeader();
    // 0x00445E40: Passenger::EnterCars
    void EnterCars();
    // 0x00445E90: Passenger::MarkForKill
    void MarkForKill();
    // 0x00445EC0: Passenger::HasSearchingPlayer
    void HasSearchingPlayer();
    // 0x00445F30: Passenger::AddPed
    void AddPed();
    // 0x00445FC0: Passenger::RemovePed
    void RemovePed();
    // 0x00446060: Passenger::RemoveDeadPeds
    void RemoveDeadPeds();
    // 0x00446160: Passenger::ClearPeds
    void ClearPeds();
};
#endif // !__PASSENGER_H_