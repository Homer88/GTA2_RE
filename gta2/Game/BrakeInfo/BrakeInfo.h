#ifndef __BRAKEINFO_H_
#define __BRAKEINFO_H_

class BrakeInfo{

    public:

    // 0x004B8FB0 void __thiscall
    void Destroy(void);
    // 0x004B8FD0
    int GetS125(void);
    // 0x004B8FE0
    int Allocate(void);
    // 0x004B9000
    int Release(void);
    // 0x004B9050
    int RemoveExpired(void);
    // 0x004B90E0
    int CallMethod(void);
};

#endif // !__BRAKEINFO_H_
