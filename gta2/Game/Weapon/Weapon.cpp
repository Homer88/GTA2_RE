#include "Weapon.h"

typedef enum WeaponType {
    Pistol = 0,
    SNG = 1,
    RPG = 2,
    ElectroGun = 3,
    Molotov = 4,
    Granata = 5,
    ShotGun = 6,
    Shoker = 7,
    FireGun = 8,
    SMG_S = 9,
    DualPistol = 10,
    L = 11,
    L2 = 12,
    L3 = 13,
    L4 = 14 /* 0 */,
    CAR_BOMB = 15,
    CAR_OIL = 16,
    CAR_MINE = 17,
    CAR_MACHINE_GUN = 18,
    TANK_MAIN_GUN = 19,
    WATER_CANNON = 20,
    FIRE_TRUCK_GUN = 21,
    ARMY_GUN_JEEP = 22,
    CAR_BOMB_INSTANT = 23,
    WEAPON_24 = 24,
    WEAPON_25 = 25,
    WEAPON_26 = 26,
    WEAPON_27 = 27,
    NO_WEAPON = 28,
}WeaponType;


    // 0x0041CC90


int Weapon::GetTypeWeapon(void){
        return 0;
    }


    // 0x00433810


int Weapon::SetTypeWeapons(void){
        return 0;
    }


    // 0x004A4F80


int Weapon::GetArrmo(void){
        return 0;
    }


    // 0x004A4F90


int Weapon::GiveWeaponInfiniti(){
    this->Armo = 65535;
        return 0;
    }


    // 0x004A4FA0


int Weapon::NotInfiniti(void){
        return 0;
    }


    // 0x004A4FB0


int Weapon::GetArrmoDec(void){
        return 0;
    }


    // 0x004A4FE0


int Weapon::GetArmo(void){
        return 0;
    }


    // 0x004A4FF0


int Weapon::SetAmmo(void){
        return 0;
    }


    // 0x004CC810


int Weapon::InitializeWeapon(void){
        return 0;
    }


    // 0x004CC860


int Weapon::SetArrmo(void){
        return 0;
    }


    // 0x004CC880


int Weapon::IsAtFullAmmo(void){
        return 0;
    }


    // 0x004CC950


int Weapon::IsExplosiveWeapon(void){
        return 0;
    }


    // 0x004CCA00


int Weapon::SetTypeWeapon_0(void){
        return 0;
    }


    // 0x004CCA30


int Weapon::Decrement10Ammo(void){
        return 0;
    }


    // 0x004CCA60


int Weapon::DecrArmor(void){
        return 0;
    }


    // 0x004CCA80


int Weapon::Set_4CCA80(void){
        return 0;
    }


    // 0x004CCB40


int Weapon::Reset(void){
        return 0;
    }


    // 0x004CCB70


int Weapon::AddAmmo(void){
        return 0;
    }


    // 0x004CD000


int Weapon::TimeToReload(void){
        return 0;
    }
