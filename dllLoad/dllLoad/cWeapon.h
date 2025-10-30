#ifndef __WEAPON__H__
#define __WEAPON__H__

#include <assert.h>

#include "cCar.h"
#include "cPed.h"

enum WeaponTypeModel {
	Pistolet = 0x0,
	SMG = 0x1,
	RPG = 0x2,
	ElectroGun = 0x3,
	Molotov = 0x4,
	Granata = 0x5,
	ShortGun = 0x6,
	Shocker = 0x7,
	FireGun = 0x8,
	SMG_S = 0x9,
	DualPistol = 0xa
};


struct Weapon {
	unsigned short armo;
	char uns1;
	char uns2;
	int	 TypeWeapons;
	void* uns3;
	void* uns4;
	short uns5;
	char uns6;
	char uns7;
	Car*	structCar;
	Weapon* NetxWeapon;
	int		WeaponType;
	char	uns8;
	char	uns9;
	char	uns10;
	char	uns11;
	struct  Ped* CurrentPed;
	int		Sound;
	char	uns12;
	char	uns13;
	char	uns14;
	char	uns15;

};
static_assert (sizeof(Weapon) == 0x30, "ERROR SIZE WEAPON");

void SetTypeWeapons (Weapon* pWeapon, WeaponTypeModel param_1);

void Weapon_FUN_004cca10 (Weapon* pWeapon, struct Ped* pPed);


#endif // !__Weapon__H__
