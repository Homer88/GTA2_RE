
#ifndef __PARTICLE1_H_
#define __PARTICLE1_H_


class Particle1{
    public:

    // 0x0048A920
    int S99(void);
    // 0x0048C8F0
    int ReleaseSprite(void);


// ==== импорт имён из gm ====
    // 3 функций
    // 0x0048D8B0: Particle1::SpawnObject
    void SpawnObject();
    // 0x0048EA50: Particle1::SpawnVehiclePuff
    void SpawnVehiclePuff();
    // 0x0048F1C0: Particle1::Free
    void Free();
};
#endif // !__PARTICLE1_H_