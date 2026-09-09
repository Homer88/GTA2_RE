#ifndef __TRAFFICCAR_H_
#define __TRAFFICCAR_H_

class TrafficCar{

    public:

    // 0x0041D800
    int gci_load_file(void);
    // 0x0041D8A0
    int Init(void);
    // 0x0041D900 void __thiscall
    void ResetFlag(void);
};

#endif // !__TRAFFICCAR_H_
