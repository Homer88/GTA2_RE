
#ifndef __CARDOOR_H_
#define __CARDOOR_H_


class CarDoor{
    public:
			CarDoor();
			~CarDoor();
    // 0x0041F660 void __thiscall
    void StartAnimation(int arg0,unsigned int param_2);  // (gm) старый: InitDoorState -> StartAnimation
    // 0x0041F680 byte __fastcall
    unsigned char UpdateAnimation(int param_1);  // (gm) старый: UpdateDoorState -> UpdateAnimation
    // 0x0041F6C0
    int DoorSetAjar(void);
    // 0x00421310
    int S7(void);
    // 0x00421340 void __thiscall
    void Reset(void);  // (gm) старый: ResetDoorState -> Reset
    // 0x00421360
    int IsDoorClosed(void);
    // 0x00421380
    int SetPedInDoor(void);
    // 0x00421390 void __fastcall
    void HornOn(int param_1);  // (gm) старый: GetTurrel -> HornOn
    // 0x00421A00
    int Open(void);
    // 0x00421A80
    int Close(void);
};

#endif // !__CARDOOR_H_