#ifndef __GTA2_TOOLS_WEAPON_INFO_H_
#define __GTA2_TOOLS_WEAPON_INFO_H_

#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// Параметры оружия GTA2.
// Хранятся в двух таблицах в бинарнике игры (byte_575904 и таблица подбора),
// но для моддинга вынесены в редактируемый текстовый формат .gwn (GTA2 Weapon).
//
// Формат текстового файла:
//   Строка на каждое оружие (28 типов):
//     {name} {max_ammo} {ammo_per_pickup} {reload_time_smg} {reload_time_normal}
//     {fire_smg} {fire_normal} {is_explosive} {is_car_weapon}
//
//   max_ammo        - макс. отображаемое кол-во патронов (raw = value * 10)
//   ammo_per_pickup - кол-во патронов за подбор (raw = value * 10)
//   reload_time_smg - кадры перезарядки в режиме SMG (fast fire)
//   fire_normal     - кадры перезарядки в обычном режиме
//   is_explosive    - взрывное оружие (1/0)
//   is_car_weapon   - оружие транспорта (1/0)
// ---------------------------------------------------------------------------

namespace gta2 {

// Имена всех 28 типов оружия (соответствуют enum WeaponType).
extern const char* const kWeaponTypeNames[29];

struct WeaponParams {
	std::string name;           // имя типа оружия
	int max_ammo;               // макс. отображаемое кол-во (0..99)
	int ammo_per_pickup;        // патроны за подбор (0..99)
	int reload_time_smg;        // кадры перезарядки (SMG режим)
	int reload_time_normal;     // кадры перезарядки (обычный режим)
	int fire_smg;               // кадры выстрела (SMG)
	int fire_normal;            // кадры выстрела (обычный)
	int is_explosive;           // взрывное (0/1)
	int is_car_weapon;          // оружие транспорта (0/1)

	WeaponParams() { Clear(); }
	void Clear() {
		name.clear();
		max_ammo = 99;
		ammo_per_pickup = 10;
		reload_time_smg = 5;
		reload_time_normal = 20;
		fire_smg = 5;
		fire_normal = 20;
		is_explosive = 0;
		is_car_weapon = 0;
	}
};

class WeaponInfoFile {
public:
	WeaponInfoFile() : m_ok(false), m_dirty(false) {}

	// Разбор текстового файла .gwn.
	bool ParseText(const std::string& text);

	// Сериализация в текст.
	std::string SaveText() const;

	// Доступ к записям (всегда 28 записей, индекс = WeaponType).
	const std::vector<WeaponParams>& Weapons() const { return m_weapons; }
	std::vector<WeaponParams>&       Weapons()       { return m_weapons; }

	const WeaponParams* FindByName(const char* name) const;
	WeaponParams*       FindByName(const char* name);

	bool IsOk() const { return m_ok; }
	bool IsDirty() const { return m_dirty; }
	void SetDirty() { m_dirty = true; }

	// Создать файл с параметрами по умолчанию (из оригинального бинарника).
	void LoadDefaults();

private:
	std::vector<WeaponParams> m_weapons;
	bool m_ok;
	bool m_dirty;
};

} // namespace gta2

#endif // !__GTA2_TOOLS_WEAPON_INFO_H_
