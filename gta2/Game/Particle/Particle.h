
#ifndef __PARTICLE_H_
#define __PARTICLE_H_


class Particle{
    public:

    // 0x0048A900
    int AllocParticle(void);
    // 0x0048F1E0
    int S98(void);


// ==== импорт имён из gm ====
    // 1 функций
    // 0x00491C20: Particle::Shutdown
    void Shutdown();
};
#endif // !__PARTICLE_H_