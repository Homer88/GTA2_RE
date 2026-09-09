#ifndef __CARENGINES_H_
#define __CARENGINES_H_

class CarEngines{

    public:

    // 0x004327E0
    int GetEngineValue(void);
    // 0x00432800
    int State(void);
    // 0x00432810
    int ResetEngineArrays(void);
    // 0x00432CD0
    int InitCarPhysics(void);
    // 0x00432D10
    int CarInfo(void);
    // 0x00432EA0
    int BuildEngineState(void);
    // 0x00432FC0
    int LoadFromGci(void);
    // 0x00433000
    int FreeResources(void);
    // 0x00433050
    int ReloadGci(void);
    // 0x0045AB70
    int TrafficLigthStruct(void);
    // 0x0045ABB0
    int S97(void);
};

#endif // !__CARENGINES_H_
