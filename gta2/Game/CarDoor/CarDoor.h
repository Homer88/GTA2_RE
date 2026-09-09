#ifndef __CARDOOR_H_
#define __CARDOOR_H_

class CarDoor{

    public:

    // 0x0041F660 void __thiscall
    void InitDoorState(int arg0,unsigned int param_2);
    // 0x0041F680 byte __fastcall
    unsigned char UpdateDoorState(int param_1);
    // 0x0041F6C0
    int DoorSetAjar(void);
    // 0x00421310
    int S7(void);
    // 0x00421340 void __thiscall
    void ResetDoorState(void);
    // 0x00421360
    int IsDoorClosed(void);
    // 0x00421380
    int SetPedInDoor(void);
    // 0x00421390 void __fastcall
    void GetTurrel(int param_1);
    // 0x00421A00
    int Open(void);
    // 0x00421A80
    int Close(void);
};

#endif // !__CARDOOR_H_
