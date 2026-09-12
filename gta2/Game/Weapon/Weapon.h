
#ifndef __WEAPON_H_
#define __WEAPON_H_


class Weapon{
    public:
    unsigned short Armo;

    // 0x0041CC90
    int GetTypeWeapon(void);
    // 0x00433810
    int SetTypeWeapons(void);
    // 0x004A4F80
    int GetArrmo(void);
    // 0x004A4F90
    int GiveWeaponInfiniti();
    // 0x004A4FA0
    int NotInfiniti(void);
    // 0x004A4FB0
    int GetArrmoDec(void);
    // 0x004A4FE0
    int GetArmo(void);
    // 0x004A4FF0
    int SetAmmo(void);
    // 0x004CC810
    int InitializeWeapon(void);
    // 0x004CC860
    int SetArrmo(void);
    // 0x004CC880
    int IsAtFullAmmo(void);
    // 0x004CC950
    int IsExplosiveWeapon(void);
    // 0x004CCA00
    int SetTypeWeapon_0(void);
    // 0x004CCA30
    int Decrement10Ammo(void);
    // 0x004CCA60
    int DecrArmor(void);
    // 0x004CCA80
    int Set_4CCA80(void);
    // 0x004CCB40
    int Reset(void);
    // 0x004CCB70
    int AddAmmo(void);
    // 0x004CD000
    int TimeToReload(void);
};

#endif // !__WEAPON_H_