
#ifndef __WEAPON_H_
#define __WEAPON_H_
// Это список оружия 
typedef enum WeaponType
{
    PISTOL = 0,   // Пистолет
    SMG = 1,   // Узи / пистолет-пулемёт
    ROCKET = 2,   // Ракетница
    ElectorGun = 3,   // Электрошок
    Molotov = 4,   // Коктейль Молотова
    GRENADE = 5,   // Гранаты
    DR = 6,   // Дробовик (Sawn-off shotgun)
    Shoker = 7,   // Шокер / электро-палка
    FireGun = 8,   // Огнемёт (FlameThrower)
    SMG_G = 9,   // Узи-гранаты? (SMG + взрывной подтип)
    DoublePistolet = 10,  // Двойной пистолет
    L = 11,  // Пулемёт (M16 / L-оружие)
    WeaponType_12 = 12,  // Неизвестное оружие 12
    WeaponType_13 = 13,  // Неизвестное оружие 13
    WeaponType_14 = 14,  // Неизвестное оружие 14
    CAR_BOMB = 15,  // Бомба (устанавливаемая на машину)
    CAR_OIL = 16,  // Нефтяное пятно (обливание)
    CAR_MINE = 17,  // Мина (устанавливаемая на машину)
    CAR_MACHINE_GUN = 18,  // Пулемёт на турели
    TANK_MAIN_GUN = 19,  // Основное орудие танка
    WATER_CANNON = 20,  // Водомёт
    FIRE_TRUCK_GUN = 21,  // Орудие пожарной машины
    ARMY_GUN_JEEP = 22,  // Пулемёт армейского джипа
    CAR_BOMB_INSTANT = 23,  // Мгновенная взрывчатка
    WEAPON_24 = 24,  // Неизвестное оружие 24
    WEAPON_25 = 25,  // Неизвестное оружие 25
    WEAPON_26 = 26,  // Неизвестное оружие 26
    WEAPON_27 = 27,  // Неизвестное оружие 27
    NO_WEAPON = 28   // Нет оружия
}WeaponType;
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
    int SelectWeapon(int a, int b);
};

#endif // !__WEAPON_H_