
#ifndef __POLICE_H_
#define __POLICE_H_


class Police{
    public:

    // 0x004A9430
    int Reset(void);
    // 0x004A9500
    int UpdateCopTarget(void);
    // 0x004A9590
    int IsPedWanted(void);
    // 0x004A9610
    int IsWanted(void);
    // 0x004A9670
    int UpdateCriminalPed(void);
    // 0x004A9A90
    int TriggerRiot(void);
    // 0x004A9AE0
    int GetFreeDecalSlot(void);
    // 0x004A9D60
    int AddCriminal(void);
    // 0x004A9E80
    int UpdateCriminalState(void);
    // 0x004A9EF0
    int CreateStain(void);
    // 0x004AA030
    int ProcessCriminals(void);
    // 0x004AA710
    int PoliceSetupPolicePed(void);
    // 0x004AA7B0
    int SpawnPoliceCar(void);
    // 0x004AAB90
    int _2(void);
    // 0x004AAD40
    int UpdateCriminalPosition(void);
    // 0x004AADD0 void __fastcall
    void SpawnPoliceDriver(int arg0);  // (gm) старый: PoliceCreateCopCarCrew -> SpawnPoliceDriver


// ==== импорт имён из gm ====
    // 3 функций
    // 0x004AACA0: Police::UpdateCrimeReport
    void UpdateCrimeReport();
    // 0x004ABAE0: Police::ReturnStolenCar
    void ReturnStolenCar();
    // 0x004ABD70: Police::ReleaseBlockedCars
    void ReleaseBlockedCars();
};
#endif // !__POLICE_H_