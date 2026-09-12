
#ifndef __TURREL_H_
#define __TURREL_H_


class Turrel{
    public:

    // 0x00420350
    int Reset(void);
    // 0x00420360 undefined4 __thiscall
    int IsOwnedByCurrentPlayer(void);  // (gm) старый: IsCurrentPlayer -> IsOwnedByCurrentPlayer
    // 0x004207D0 bool __thiscall
    bool IsVisible(void);  // (gm) старый: IsWeaponPresent -> IsVisible
    // 0x004207E0
    int SetSelect(void);
    // 0x00420D80 void __fastcall
    void TurrelZeroInit(int arg0);  // (gm) старый: ClearData -> TurrelZeroInit
    // 0x00420D90 void __thiscall
    void ClearValue(void);  // (gm) старый: ResetTurret -> ClearValue
    // 0x00420DA0
    int S8(void);
    // 0x00420DC0 void __thiscall
    void SetCarBit(int arg0);  // (gm) old: SetFlag -> SetCarBit (sets bit by type)
    // 0x00420DE0
    int ClearFlag(void);
    // 0x00433820
    int GetCarBomb(void);
    // 0x0045AB30
    int S72(void);
    // 0x004740F0
    int ClearFlagInReg(void);
    // 0x00492130 void __fastcall
    void ClearStateFlag(int param_1);  // (gm) старый: ClearSpecialFlag -> ClearStateFlag
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
    void SetState(int param_1);  // (gm) старый: SetCarModelId -> SetState
    // 0x004C4F20 undefined4 __fastcall
    int GetState(int param_1);  // (gm) старый: GetCarWeapon -> GetState
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


// ==== импорт имён из gm ====
    // 4 функций
    // 0x004BE920: Turrel::RemoveObject
    void RemoveObject();
    // 0x004BEA60: Turrel::SetSpriteTime
    void SetSpriteTime();
    // 0x004BEA90: Turrel::GetSpriteByType
    void GetSpriteByType();
    // 0x004BED60: Turrel::AttachEventHandler
    void AttachEventHandler();
};
#endif // !__TURREL_H_