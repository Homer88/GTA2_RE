#pragma once

#include "global.h"

enum  WeaponType  
{
  Pistolet = 0u,
  SMG = 1u,
  ROCKET = 2u,
  ElectorGun = 3u,
  Molotov = 4u,
  GRENADE = 5u,
  DR = 6u,
  Shoker = 7u,
  FireGun = 8u,
  SMG_G = 9u,
  DoublePistolet = 10u,
  L = 11u,
  TANK_MAIN_GUN = 19u,
  FIRE_TRUCK_GUN = 20u,
  ARMY_GUN_JEEP = 22u,
};



class Weapon{
    public:
		__int16 Ammo;
  char TimeToReload;
  char field_3;
  int SMG;
  int field_8;
  int field_C;
  short phsort;
  char field_12;
  char field_13;
  Car *Car;
  Weapon *NextWeapon;
  WeaponType TypeWeapon;
  char field_20;
  char field_21;
  char field_22;
  char field_23;
  Ped *Ped;
  int SoundWeapon;
  char field_2C;
  char field_2D;
  char field_2E;
  char field_2F;
        Weapon();
        ~Weapon(); 
};
