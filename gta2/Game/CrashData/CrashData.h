#ifndef __CRASHDATA_H_
#define __CRASHDATA_H_

class CrashData{

    public:

    // 0x0044C870
    int IsCarInvolved(void);
    // 0x004769E0 void __thiscall
    void SetCrashData(int param_2,int param_3);
    // 0x00476A00 void __thiscall
    void SetCrashDamage(int param_2);
    // 0x00476A10 void __thiscall
    void SetCrashField24(int param_1,int param_2);
    // 0x00476A20 void __thiscall
    void SetCrashBounds(int param_1,int param_2);
    // 0x00476A30 void __thiscall
    void ClearCrashObjects(void);
    // 0x00476A60 void __thiscall
    void RemoveCrashObjects(void);
    // 0x00476A90 undefined4 __thiscall
    int GetCrashField20(void);
    // 0x00476AA0 void __thiscall
    void SetActiveFlag(void);
    // 0x00476AB0 void __thiscall
    void ClearActiveFlag(void);
    // 0x00476AD0
    int SetActive(void);
    // 0x004895E0 void __fastcall
    void ShutdownCrashCar(int arg0);
    // 0x004895F0 void __thiscall
    void ClearCrashActive(void);
    // 0x00489680
    int ProcessCrash(void);
    // 0x00489B10 void __fastcall
    void ProcessParkingCrash(int param_1);
    // 0x00489BC0
    int AddCrash(void);
    // 0x00493540
    int IsCarEqual(void);
};

#endif // !__CRASHDATA_H_
