
#ifndef __DECALINFO_H_
#define __DECALINFO_H_


class DecalInfo{
    public:

    // 0x0045B230
    int S111(void);
    // 0x004A9720
    int Register(void);
    // 0x004A9930
    int Unregister(void);
    // 0x004AB060
    int SpawnPedGroup(void);
    // 0x004AB330
    int HandlePedExit(void);
    // 0x004AB400
    int HandleCarExit(void);
    // 0x004AB610
    int BreakGlass(void);
    // 0x004AB930
    int CanBePointedAt(void);
    // 0x004AB9D0
    int ReleasePed(void);
    // 0x004ABA30
    int StopPed(void);
    // 0x004AD600
    int ProcessUpdate(void);
};

#endif // !__DECALINFO_H_