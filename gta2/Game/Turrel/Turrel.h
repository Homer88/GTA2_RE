#ifndef __TURREL_H_
#define __TURREL_H_

class Turrel{

    public:

    // 0x00420350
    int Reset(void);
    // 0x00420360 undefined4 __thiscall
    int IsCurrentPlayer(void);
    // 0x004207D0 bool __thiscall
    bool IsWeaponPresent(void);
    // 0x004207E0
    int SetSelect(void);
    // 0x00420D80 void __fastcall
    void ClearData(int arg0);
    // 0x00420D90 void __thiscall
    void ResetTurret(void);
    // 0x00420DA0
    int S8(void);
    // 0x00420DC0 void __thiscall
    void SetFlag(int arg0);
    // 0x00420DE0
    int ClearFlag(void);
    // 0x00433820
    int GetCarBomb(void);
    // 0x0045AB30
    int S72(void);
    // 0x004740F0
    int ClearFlagInReg(void);
    // 0x00492130 void __fastcall
    void ClearSpecialFlag(int param_1);
    // 0x00492140
    int HasRegionAtPos(void);
    // 0x004B9E50
    int cSpriteReset(void);
    // 0x004BE7C0
    int SpriteContains(void);
    // 0x004BE7E0
    int UpdateSprites(void);
    // 0x004BE950
    int Update(void);
    // 0x004BEBC0
    int SetZOrder(void);
    // 0x004BED00
    int DeleteAllExcept(void);
    // 0x004BEDD0
    int AddSprite(void);
    // 0x004BF180
    int FreeTurrets(void);
    // 0x004C4F10 void __thiscall
    void SetCarModelId(int param_1);
    // 0x004C4F20 undefined4 __fastcall
    int GetCarWeapon(int param_1);
    // 0x004C4F30
    int SpriteInfoAddObject(void);
    // 0x004CC990
    int GetData(void);
    // 0x004CC9A0
    int GetWeapon(void);
    // 0x004CD7B0
    int CreateWeaponForTurret(void);
    // 0x004CD7F0
    int FindWeaponInPool(void);
    // 0x004D06E0
    int DeleteWeapon(void);
    // 0x004D0700
    int DeleteCarWeapons(void);
};

#endif // !__TURREL_H_
