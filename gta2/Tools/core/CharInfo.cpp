#include "CharInfo.h"
#include <sstream>
#include <cstring>
#include <cstdio>

namespace gta2 {

// Имена профессий по индексу Occupation (из кода игры + значений реверса).
// Неизвестные значения -> "Occupation_N", дефолты по образцу гражданского.
const char* const kOccupationNames[0x2D] = {
	"Civilian",              //  0 OCC_CIVILIAN
	"Occupation_1",          //  1 (не преследует игрока вне полиции)
	"Occupation_2",          //  2
	"CivilianDefault",       //  3 OCC_CIVILIAN_DEFAULT
	"DriverPassenger",       //  4 OCC_DRIVER_PASSENGER
	"Occupation_5",          //  5
	"Occupation_6",          //  6
	"Occupation_7",          //  7
	"Agent",                 //  8 OCC_AGENT_8
	"Agent2",                //  9 OCC_AGENT_9
	"Occupation_10",         // 10
	"Occupation_11",         // 11
	"Occupation_12",         // 12
	"Occupation_13",         // 13
	"Occupation_14",         // 14
	"Mugger",                // 15 OCC_MUGGER
	"CartThief",             // 16 OCC_CAR_THIEF
	"Occupation_17",         // 17
	"Occupation_18",         // 18
	"Occupation_19",         // 19
	"Occupation_20",         // 20
	"Occupation_21",         // 21
	"Elvis",                 // 22 OCC_ELVIS
	"Occupation_23",         // 23
	"Police24",              // 24 OCC_POLICE_24
	"Police25",              // 25 OCC_POLICE_25
	"Police26",              // 26 OCC_POLICE_26
	"Police27",              // 27 OCC_POLICE_27
	"Police28",              // 28 OCC_POLICE_28
	"Police29",              // 29 OCC_POLICE_29
	"Police30",              // 30 OCC_POLICE_30
	"Police31",              // 31 OCC_POLICE_31
	"Occupation_32",         // 32
	"Occupation_33",         // 33
	"Occupation_34",         // 34
	"Occupation_35",         // 35
	"Occupation_36",         // 36
	"PoliceCivilian",        // 37 OCC_POLICE_CIVILIAN
	"Occupation_38",         // 38
	"Occupation_39",         // 39
	"Occupation_40",         // 40
	"Occupation_41",         // 41
	"Special42",             // 42 OCC_SPECIAL_42
	"Special43",             // 43 OCC_SPECIAL_43
	"Special44",             // 44 OCC_SPECIAL_44
};

// ---------------------------------------------------------------------------
// Настройки по умолчанию для одной профессии.
// ---------------------------------------------------------------------------
static void DefaultChar(CharParams& c, int occupation, const char* name,
	int health, int speed, int sprite, int remap, int weapon,
	int isPolice, int isCriminal, int isAgent)
{
	c.name = name;
	c.occupation = occupation;
	c.health = health;
	c.speed = speed;
	c.sprite = sprite;
	c.remap = remap;
	c.weapon = weapon;
	c.is_police = isPolice;
	c.is_criminal = isCriminal;
	c.is_agent = isAgent;
}

// ---------------------------------------------------------------------------
// Загрузка значений по умолчанию.
// Здоровье/скорость/спрайт по образцу штатных пешеходов игры (Health short,
// полиция быстрее гражданских и вооружена пистолетом).
// ---------------------------------------------------------------------------
void CharInfoFile::LoadDefaults()
{
	m_chars.clear();

	CharParams c;

	// Гражданские (0, 3): без оружия, обычная скорость.
	DefaultChar(c, OCC_CIVILIAN, "Civilian",         100, 32, 0, 0, 0, 0, 0, 0);
	m_chars.push_back(c);
	DefaultChar(c, OCC_CIVILIAN_DEFAULT, "CivilianDefault", 100, 32, 0, 0, 0, 0, 0, 0);
	m_chars.push_back(c);

	// Водитель/пассажир (4).
	DefaultChar(c, OCC_DRIVER_PASSENGER, "DriverPassenger", 100, 34, 0, 0, 0, 0, 0, 0);
	m_chars.push_back(c);

	// Агенты (8, 9): участвуют в миссиях, вооружены пистолетом.
	DefaultChar(c, OCC_AGENT_8, "Agent",    100, 34, 0, 0, 0, 0, 0, 1);
	m_chars.push_back(c);
	DefaultChar(c, OCC_AGENT_9, "Agent2",   100, 34, 0, 0, 0, 0, 0, 1);
	m_chars.push_back(c);

	// Уголовники: громила, угонщик, элвис.
	DefaultChar(c, OCC_MUGGER,    "Mugger",    100, 32, 0, 0, 0, 0, 1, 0);
	m_chars.push_back(c);
	DefaultChar(c, OCC_CAR_THIEF, "CartThief", 100, 34, 0, 0, 0, 0, 1, 0);
	m_chars.push_back(c);
	DefaultChar(c, OCC_ELVIS,     "Elvis",     100, 32, 0, 0, 0, 0, 1, 0);
	m_chars.push_back(c);

	// Полиция (24..31): выше скорость, вооружена пистолетом (weapon 0).
	for (int i = OCC_POLICE_24; i <= OCC_POLICE_31; i++) {
		DefaultChar(c, i, kOccupationNames[i], 100, 36, 0, 0, 0, 1, 0, 0);
		m_chars.push_back(c);
	}

	// Полиция-гражданский и спец. классы.
	DefaultChar(c, OCC_POLICE_CIVILIAN, "PoliceCivilian", 100, 36, 0, 0, 0, 1, 0, 0);
	m_chars.push_back(c);
	DefaultChar(c, OCC_SPECIAL_42, "Special42", 100, 34, 0, 0, 0, 0, 0, 0);
	m_chars.push_back(c);
	DefaultChar(c, OCC_SPECIAL_43, "Special43", 100, 34, 0, 0, 0, 0, 0, 0);
	m_chars.push_back(c);
	DefaultChar(c, OCC_SPECIAL_44, "Special44", 100, 34, 0, 0, 0, 0, 0, 0);
	m_chars.push_back(c);

	m_ok = true;
	m_dirty = false;
}

// ---------------------------------------------------------------------------
// Парсинг строки.
// ---------------------------------------------------------------------------
static bool ParseCharLine(const std::string& line, CharParams& c)
{
	if (line.empty() || line[0] == '#') return false;

	std::istringstream iss(line);
	std::string name;
	int occ, health, speed, sprite, remap, weapon, police, criminal, agent;

	if (!(iss >> name >> occ >> health >> speed >> sprite
	          >> remap >> weapon >> police >> criminal >> agent))
		return false;

	c.name = name;
	c.occupation = occ;
	c.health = health;
	c.speed = speed;
	c.sprite = sprite;
	c.remap = remap;
	c.weapon = weapon;
	c.is_police = police;
	c.is_criminal = criminal;
	c.is_agent = agent;
	return true;
}

bool CharInfoFile::ParseText(const std::string& text)
{
	m_chars.clear();
	std::istringstream iss(text);
	std::string line;

	while (std::getline(iss, line)) {
		if (!line.empty() && line.back() == '\r')
			line.pop_back();

		CharParams c;
		if (ParseCharLine(line, c))
			m_chars.push_back(c);
	}

	m_ok = true;
	m_dirty = false;
	return true;
}

// ---------------------------------------------------------------------------
// Сериализация
// ---------------------------------------------------------------------------
std::string CharInfoFile::SaveText() const
{
	std::ostringstream oss;
	oss << "# GTA2 Character Parameters\n";
	oss << "# name  occupation  health  speed  sprite  remap  weapon  is_police  is_criminal  is_agent\n";
	oss << "#\n";
	oss << "# occupation: числовое значение из struct Ped (Occupation int)\n";
	oss << "#   0 - гражданский, 3 - default, 4 - водитель/пассажир,\n";
	oss << "#   8/9 - агент, 0x0F - MUGGER, 0x10 - угонщик, 0x16 - ELVIS,\n";
	oss << "#   0x18..0x1F - полиция, 0x2A..0x2C - спец.\n";
	oss << "# weapon: индекс WeaponType (0 = пистолет)\n";
	oss << "\n";

	for (size_t i = 0; i < m_chars.size(); i++) {
		const CharParams& c = m_chars[i];
		oss << c.name
		    << " " << c.occupation
		    << " " << c.health
		    << " " << c.speed
		    << " " << c.sprite
		    << " " << c.remap
		    << " " << c.weapon
		    << " " << c.is_police
		    << " " << c.is_criminal
		    << " " << c.is_agent
		    << "\n";
	}

	return oss.str();
}

// ---------------------------------------------------------------------------
// Поиск по профессии
// ---------------------------------------------------------------------------
const CharParams* CharInfoFile::FindByOccupation(int occupation) const
{
	for (size_t i = 0; i < m_chars.size(); i++) {
		if (m_chars[i].occupation == occupation)
			return &m_chars[i];
	}
	return NULL;
}

CharParams* CharInfoFile::FindByOccupation(int occupation)
{
	for (size_t i = 0; i < m_chars.size(); i++) {
		if (m_chars[i].occupation == occupation)
			return &m_chars[i];
	}
	return NULL;
}

} // namespace gta2