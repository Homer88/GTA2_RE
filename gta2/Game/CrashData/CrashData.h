
#ifndef __CRASHDATA_H_
#define __CRASHDATA_H_


class CrashData{
    public:

    // 0x0044C870
    int IsCarInvolved(void);
    // 0x004769E0 void __thiscall
    void SetTarget3(int param_2,int param_3);  // (gm) старый: SetCrashData -> SetTarget3
    // 0x00476A00 void __thiscall
    void SetSecondary(int param_2);  // (gm) старый: SetCrashDamage -> SetSecondary
    // 0x00476A10 void __thiscall
    void SetField24(int param_1,int param_2);  // (gm) старый: SetCrashField24 -> SetField24
    // 0x00476A20 void __thiscall
    void SetTextPos(int param_1,int param_2);  // (gm) старый: SetCrashBounds -> SetTextPos
    // 0x00476A30 void __thiscall
    void DrawText(void);  // (gm) старый: ClearCrashObjects -> DrawText
    // 0x00476A60 void __thiscall
    void UpdateBoth(void);  // (gm) старый: RemoveCrashObjects -> UpdateBoth
    // 0x00476A90 undefined4 __thiscall
    int GetValue(void);  // (gm) старый: GetCrashField20 -> GetValue
    // 0x00476AA0 void __thiscall
    void SetActiveFlag(void);
    // 0x00476AB0 void __thiscall
    void SetInactive(void);  // (gm) старый: ClearActiveFlag -> SetInactive
    // 0x00476AD0
    int SetActive(void);
    // 0x004895E0 void __fastcall
    void ResetBuffer8(int arg0);  // (gm) старый: ShutdownCrashCar -> ResetBuffer8
    // 0x004895F0 void __thiscall
    void ResetBufferState(void);  // (gm) старый: ClearCrashActive -> ResetBufferState
    // 0x00489680
    int ProcessCrash(void);
    // 0x00489B10 void __fastcall
    void ParkVehicleUpdate(int param_1);  // (gm) старый: ProcessParkingCrash -> ParkVehicleUpdate
    // 0x00489BC0
    int AddCrash(void);
    // 0x00493540
    int IsCarEqual(void);
};

#endif // !__CRASHDATA_H_