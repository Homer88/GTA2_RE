
#ifndef __FIREINFO_H_
#define __FIREINFO_H_


class FireInfo{
    public:

    // 0x0044A3A0
    int S105_FindCar(void);
    // 0x0044A970
    int AddFire(void);
    // 0x0045ACD0
    int Destroy(void);


// ==== импорт имён из gm ====
    // 2 функций
    // 0x0044A420: FireInfo::StartFire
    void StartFire();
    // 0x0044A9C0: FireInfo::AllocateSmoke
    void AllocateSmoke();
};
#endif // !__FIREINFO_H_