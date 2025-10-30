#include <Windows.h>

#include "cWeapon.h"



void SetTypeWeapons(Weapon* pWeapon, WeaponTypeModel param_1) {

	MessageBox(0, "Тип оружия", 0, 0);
	pWeapon->TypeWeapons = param_1;
}

void  Weapon_FUN_004cca10(Weapon* pWeapon, Ped* pPed)

{
	MessageBox(0, "Тип оружия1", 0, 0);
	pWeapon->CurrentPed = pPed;
	return;
}