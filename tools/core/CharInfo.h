#ifndef __GTA2_TOOLS_CHAR_INFO_H_
#define __GTA2_TOOLS_CHAR_INFO_H_

#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// Параметры персонажей/пешеходов GTA2.
//
// В игре пешеход определяется структурой Ped (дамп: struct Ped, Ghidra
// gta2.exe.h:6914): Health (short), Occupation (int), SpriteS1*, Remap,
// PoliceStar, PositionX/Y/Z, SelectedWeapon/Weapon1. Профессия - это int
// (Occupation), значения извлечены из кода (gta2.exe.c):
//   0             гражданский
//   3             гражданский (default)
//   4             водитель/пассажир
//   8, 9          агент (GCI)
//   0x0F (15)     MUGGER
//   0x10 (16)     CARTHIEF (угонщик)
//   0x16 (22)     ELVIS
//   0x18..0x1F    полиция (24..31)
//   0x25 (37)     полиция/гражданский-связанный
//   0x2A..0x2C    спец. (такси-пассажир/группа)
// (Диапазоны могут дополняться по мере реверса.)
//
// Для моддинга параметры вынесены в редактируемый текстовый формат .gch
// (GTA2 CHaracter), по образцу .gwn (оружие).
//
// Формат текстового файла, строка на персонажа:
//   {name} {occupation} {health} {speed} {sprite} {remap} {weapon}
//          {is_police} {is_criminal} {is_agent}
// ---------------------------------------------------------------------------

namespace gta2 {

// Значения профессий, подтверждённые в коде игры (см. реестр форматов).
enum Occupation {
	OCC_CIVILIAN          = 0,
	OCC_CIVILIAN_DEFAULT  = 3,
	OCC_DRIVER_PASSENGER  = 4,
	OCC_AGENT_8           = 8,
	OCC_AGENT_9           = 9,
	OCC_MUGGER            = 0x0F,
	OCC_CAR_THIEF         = 0x10,
	OCC_ELVIS             = 0x16,
	OCC_POLICE_24         = 0x18,
	OCC_POLICE_25         = 0x19,
	OCC_POLICE_26         = 0x1A,
	OCC_POLICE_27         = 0x1B,
	OCC_POLICE_28         = 0x1C,
	OCC_POLICE_29         = 0x1D,
	OCC_POLICE_30         = 0x1E,
	OCC_POLICE_31         = 0x1F,
	OCC_POLICE_CIVILIAN   = 0x25,
	OCC_SPECIAL_42        = 0x2A,
	OCC_SPECIAL_43        = 0x2B,
	OCC_SPECIAL_44        = 0x2C
};

// Имена всех известных профессий (индекс = Occupation).
extern const char* const kOccupationNames[0x2D];

// Параметры персонажа.
struct CharParams {
	std::string name;       // имя профессии для редактора
	int occupation;         // Occupation (числовое значение из игры)
	int health;             // Health (short в struct Ped)
	int speed;              // скорость движения (усл. единицы)
	int sprite;             // индекс спрайта пешехода (SpriteS1*)
	int remap;              // remap спрайта (byte Remap)
	int weapon;             // стартовое оружие (индекс WeaponType)
	int is_police;          // принадлежность полиции (0/1)
	int is_criminal;        // разыскиваемый персонаж (0/1)
	int is_agent;           // агент миссии (0/1)

	CharParams() { Clear(); }
	void Clear() {
		name.clear();
		occupation = 0;
		health = 100;
		speed = 32;
		sprite = 0;
		remap = 0;
		weapon = 0;
		is_police = 0;
		is_criminal = 0;
		is_agent = 0;
	}
};

// Файл параметров персонажей (.gch).
class CharInfoFile {
public:
	CharInfoFile() : m_ok(false), m_dirty(false) {}

	// Разбор текстового файла .gch.
	bool ParseText(const std::string& text);

	// Сериализация в текст.
	std::string SaveText() const;

	const std::vector<CharParams>& Chars() const { return m_chars; }
	std::vector<CharParams>&       Chars()       { return m_chars; }

	const CharParams* FindByOccupation(int occupation) const;
	CharParams*       FindByOccupation(int occupation);

	bool IsOk() const { return m_ok; }
	bool IsDirty() const { return m_dirty; }
	void SetDirty() { m_dirty = true; }

	// Создать список с параметрами по умолчанию (из оригинального кода).
	void LoadDefaults();

private:
	std::vector<CharParams> m_chars;
	bool m_ok;
	bool m_dirty;
};

} // namespace gta2

#endif // !__GTA2_TOOLS_CHAR_INFO_H_