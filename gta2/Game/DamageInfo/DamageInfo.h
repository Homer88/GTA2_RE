#ifndef __DAMAGEINFO_H_
#define __DAMAGEINFO_H_

class DamageInfo{

    public:

    // 0x0045B2C0
    int IsDamagedRaw(void);
    // 0x0045B2D0
    int SetDamageFlags(void);
    // 0x0045B2F0
    int ResetDamage(void);
    // 0x0045B300
    int SetDamageType(void);
    // 0x0045B310
    int IsDamaged(void);
    // 0x0045B320
    int InvalidateMemory(void);
    // 0x0045B330
    int UpdateDamageTimer(void);
    // 0x004613B0
    int DrawToBuffer(void);
    // 0x0048A510
    int ClearRenderQueue(void);
    // 0x00491240
    int ProcessHeavyDamage(void);
};

#endif // !__DAMAGEINFO_H_
