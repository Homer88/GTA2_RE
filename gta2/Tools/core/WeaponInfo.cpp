#include "WeaponInfo.h"
#include <sstream>
#include <cstring>
#include <cstdio>

namespace gta2 {

// 28 типов оружия + "NO_WEAPON" (индекс 28, но в таблицах не участвует).
const char* const kWeaponTypeNames[29] = {
	"Pistolet",          // 0
	"SMG",               // 1
	"ROCKET",            // 2
	"ElectorGun",        // 3
	"Molotov",           // 4
	"GRENADE",           // 5
	"DR",                // 6  (дробовик / shotgun)
	"Shoker",            // 7
	"FireGun",           // 8
	"SMG_G",             // 9
	"DoublePistolet",    // 10
	"L",                 // 11
	"WeaponType_12",     // 12
	"WeaponType_13",     // 13
	"WeaponType_14",     // 14
	"CAR_BOMB",          // 15
	"CAR_OIL",           // 16
	"CAR_MINE",          // 17
	"CAR_MACHINE_GUN",   // 18
	"TANK_MAIN_GUN",     // 19
	"WATER_CANNON",      // 20
	"FIRE_TRUCK_GUN",    // 21
	"ARMY_GUN_JEEP",     // 22
	"CAR_BOMB_INSTANT",  // 23
	"WEAPON_24",         // 24
	"WEAPON_25",         // 25
	"WEAPON_26",         // 26
	"WEAPON_27",         // 27
	"NO_WEAPON"          // 28
};

// Оригинальные значения из бинарника GTA2.
// byte_575904[28] = max displayed ammo (raw = value * 10).
static const int kDefaultMaxAmmo[28] = {
	99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99,  1, 99, 99, 99, 99,
	99, 99, 99,  1,  0,  0,  0,  0
};

// Таблица подбора: ammo_per_pickup (raw = value * 10).
static const int kDefaultAmmoPerPickup[28] = {
	10, 10,  5, 20,  5,  5, 10, 20, 20, 10,
	10,  0,  0,  0,  0,  1,  5,  5, 10, 50,
	50, 20, 50,  1,  0,  0,  0,  0
};

// Время перезарядки и стрельбы, извлечено из дампа (кадры).
// SMG mode = fast fire, normal = single shot.
static const int kDefaultReloadSmg[28] = {
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5
};

static const int kDefaultReloadNormal[28] = {
	20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
	20, 20, 20, 20, 20, 20, 20, 20, 40, 50,
	50, 20, 50, 20, 20, 20, 20, 20
};

static const int kDefaultFireSmg[28] = {
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5
};

static const int kDefaultFireNormal[28] = {
	20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
	20, 20, 20, 20, 20, 20, 20, 20, 40, 50,
	50, 20, 50, 20, 20, 20, 20, 20
};

// Взрывные типы: ROCKET(2), Molotov(4), CAR_BOMB(15), CAR_MINE(17), TANK_MAIN_GUN(19).
static bool IsExplosiveDefault(int type) {
	return type == 2 || type == 4 || type == 15 || type == 17 || type == 19;
}

// Оружие транспорта: CAR_MACHINE_GUN(18), TANK_MAIN_GUN(19), FIRE_TRUCK_GUN(21), ARMY_GUN_JEEP(22).
static bool IsCarWeaponDefault(int type) {
	return type == 18 || type == 19 || type == 21 || type == 22;
}

// Типы, для которых max_ammo = 0 (не используются как пехотное оружие).
static bool IsUnusedType(int type) {
	return type >= 11 && type <= 14;
}

// ---------------------------------------------------------------------------
// Загрузка значений по умолчанию
// ---------------------------------------------------------------------------
void WeaponInfoFile::LoadDefaults()
{
	m_weapons.resize(28);
	for (int i = 0; i < 28; i++) {
		WeaponParams& w = m_weapons[i];
		w.name = kWeaponTypeNames[i];
		w.max_ammo = kDefaultMaxAmmo[i];
		w.ammo_per_pickup = kDefaultAmmoPerPickup[i];
		w.reload_time_smg = kDefaultReloadSmg[i];
		w.reload_time_normal = kDefaultReloadNormal[i];
		w.fire_smg = kDefaultFireSmg[i];
		w.fire_normal = kDefaultFireNormal[i];
		w.is_explosive = IsExplosiveDefault(i) ? 1 : 0;
		w.is_car_weapon = IsCarWeaponDefault(i) ? 1 : 0;
	}
	m_ok = true;
	m_dirty = false;
}

// ---------------------------------------------------------------------------
// Парсинг строки: {name} {max_ammo} {ammo_per_pickup} {reload_smg} {reload_normal}
//                  {fire_smg} {fire_normal} {is_explosive} {is_car_weapon}
// ---------------------------------------------------------------------------
static bool ParseWeaponLine(const std::string& line, WeaponParams& w)
{
	if (line.empty() || line[0] == '#') return false;

	std::istringstream iss(line);
	std::string name;
	int maxAmmo, ammoPickup, reloadSmg, reloadNormal, fireSmg, fireNormal, explosive, carWeapon;

	if (!(iss >> name >> maxAmmo >> ammoPickup >> reloadSmg >> reloadNormal
	          >> fireSmg >> fireNormal >> explosive >> carWeapon))
		return false;

	w.name = name;
	w.max_ammo = maxAmmo;
	w.ammo_per_pickup = ammoPickup;
	w.reload_time_smg = reloadSmg;
	w.reload_time_normal = reloadNormal;
	w.fire_smg = fireSmg;
	w.fire_normal = fireNormal;
	w.is_explosive = explosive;
	w.is_car_weapon = carWeapon;
	return true;
}

bool WeaponInfoFile::ParseText(const std::string& text)
{
	m_weapons.clear();
	std::istringstream iss(text);
	std::string line;

	while (std::getline(iss, line)) {
		// Убираем CR
		if (!line.empty() && line.back() == '\r')
			line.pop_back();

		WeaponParams w;
		if (ParseWeaponLine(line, w))
			m_weapons.push_back(w);
	}

	// Дополняем до 28 записей значениями по умолчанию
	if ((int)m_weapons.size() < 28) {
		WeaponInfoFile defaults;
		defaults.LoadDefaults();
		while ((int)m_weapons.size() < 28) {
			int idx = (int)m_weapons.size();
			m_weapons.push_back(defaults.Weapons()[idx]);
		}
	}

	m_ok = true;
	m_dirty = false;
	return true;
}

// ---------------------------------------------------------------------------
// Сериализация
// ---------------------------------------------------------------------------
std::string WeaponInfoFile::SaveText() const
{
	std::ostringstream oss;
	oss << "# GTA2 Weapon Parameters\n";
	oss << "# name  max_ammo  ammo_per_pickup  reload_smg  reload_normal  fire_smg  fire_normal  is_explosive  is_car_weapon\n";
	oss << "#\n";
	oss << "# max_ammo / ammo_per_pickup: отображаемое значение (raw = value * 10)\n";
	oss << "# reload/fire: кадры (frames)\n";
	oss << "\n";

	int count = (int)m_weapons.size();
	if (count > 28) count = 28;

	for (int i = 0; i < count; i++) {
		const WeaponParams& w = m_weapons[i];
		oss << w.name
		    << " " << w.max_ammo
		    << " " << w.ammo_per_pickup
		    << " " << w.reload_time_smg
		    << " " << w.reload_time_normal
		    << " " << w.fire_smg
		    << " " << w.fire_normal
		    << " " << w.is_explosive
		    << " " << w.is_car_weapon
		    << "\n";
	}

	return oss.str();
}

// ---------------------------------------------------------------------------
// Поиск по имени
// ---------------------------------------------------------------------------
const WeaponParams* WeaponInfoFile::FindByName(const char* name) const
{
	for (size_t i = 0; i < m_weapons.size(); i++) {
		if (m_weapons[i].name == name)
			return &m_weapons[i];
	}
	return NULL;
}

WeaponParams* WeaponInfoFile::FindByName(const char* name)
{
	for (size_t i = 0; i < m_weapons.size(); i++) {
		if (m_weapons[i].name == name)
			return &m_weapons[i];
	}
	return NULL;
}

} // namespace gta2
