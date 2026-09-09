#ifndef __CHARACTER_H_
#define __CHARACTER_H_

class Character{

    public:

    // 0x00420C30
    int CharIsValidPedIndex(void);
    // 0x00420C40
    int CarSystemManagerUnderCarLimit(void);
    // 0x0043AE10
    int FindPed(void);
    // 0x0043AE40 void __fastcall
    void IsPedNearToPlayer(int arg0);
    // 0x0043DBD0
    int CreatePedInCar(void);
    // 0x0043DC60
    int CharCreateDriver(void);
    // 0x0043DD80
    int CharCreateDummyDriver(void);
    // 0x0043DE10
    int CharCreatePed(void);
    // 0x0043DEB0
    int CreateRandomPedInCar(void);
    // 0x0043DF60
    int CreatePed(void);
    // 0x0043DFB0
    int ClonePed(void);
    // 0x0043E270
    int CreateDriver(void);
    // 0x00440CC0
    int Control(void);
    // 0x004416B0
    int Characte(void);
    // 0x004462F0
    int IsPedRelatedByGangOrOccupation(void);
};

#endif // !__CHARACTER_H_
