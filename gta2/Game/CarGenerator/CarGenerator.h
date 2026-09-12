
#ifndef __CARGENERATOR_H_
#define __CARGENERATOR_H_


class CarGenerator{
    public:

    // 0x0045AFD0 void __thiscall
    void SetSpawnState(int param_1);  // (gm) старый: SetMaxCars -> SetSpawnState
    // 0x0045AFF0
    int Reset(void);
    // 0x0045B000
    int ResetTimer(void);
    // 0x004C70E0 void __thiscall
    void ResetGeneratorState(void);
};

#endif // !__CARGENERATOR_H_