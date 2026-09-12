
#ifndef __TRAFFICCAR_H_
#define __TRAFFICCAR_H_


class TrafficCar{
    public:

    // 0x0041D800
    int gci_load_file(void);
    // 0x0041D8A0
    int Init(void);
    // 0x0041D900 void __thiscall
    void ClearField2B(void);  // (gm) старый: ResetFlag -> ClearField2B


// ==== импорт имён из gm ====
    // 3 функций
    // 0x0041D910: TrafficCar::PoolDestructor
    void PoolDestructor();
    // 0x0041D950: TrafficCar::FindFreeSlot
    void FindFreeSlot();
    // 0x0041D980: TrafficCar::Deploy
    void Deploy();
};
#endif // !__TRAFFICCAR_H_