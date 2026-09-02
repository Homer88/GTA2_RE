#ifndef __GTA2_TOOLS_GCI_FORMAT_H_
#define __GTA2_TOOLS_GCI_FORMAT_H_

#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// Формат файла характеристик машин .gci (текстовый).
// Подтверждён по bin/data/nyc.gci и исходнику u_caredit.pas:214 (индексы
// строк относительно строки {model}).
//
// Структура блока на одну машину (22 строки, индексы от строки {name}):
//    0 {name}          (имя машины для скриптов, напр. "Romero")
//    1 {model}         (номер модели, совпадает с CARI.model)
//    2 {turbo}         (0/1)
//    3 {value}         (целое значение)
//    4 {pad}           (выравнивание, 0)
//    5 f{mass}
//    6 f{front drive bias}
//    7 f{front mass bias}
//    8 f{brake friction}
//    9 f{turn in}
//   10 f{turn ratio}
//   11 f{rear end stability}
//   12 f{handbrake slide value}
//   13 f{thrust}
//   14 f{max_speed}
//   15 f{anti strength}
//   16 f{skid threshhold}
//   17 f{gear1 multiplier}
//   18 f{gear2 multiplier}
//   19 f{gear3 multiplier}
//   20 f{gear2 speed}
//   21 f{gear3 speed}
//
// Блок на машину занимает 22 строки (индексы 0..21 от строки {name}).
//
// Каждая строка - "значение {имя}". Числа плавают с признаком 'f' без него.
// ---------------------------------------------------------------------------

namespace gta2 {

// 16 вещественных параметров физики (индексы 5..20 в блоке).
struct CarPhysics {
	double mass;
	double front_drive_bias;
	double front_mass_bias;
	double brake_friction;
	double turn_in;
	double turn_ratio;
	double rear_end_stability;
	double handbrake_slide_value;
	double thrust;
	double max_speed;
	double anti_strength;
	double skid_threshhold;
	double gear1_multiplier;
	double gear2_multiplier;
	double gear3_multiplier;
	double gear2_speed;
	double gear3_speed;

	CarPhysics() { Clear(); }
	void Clear() {
		mass = front_drive_bias = front_mass_bias = 0;
		brake_friction = turn_in = turn_ratio = 0;
		rear_end_stability = handbrake_slide_value = 0;
		thrust = max_speed = anti_strength = skid_threshhold = 0;
		gear1_multiplier = gear2_multiplier = gear3_multiplier = 0;
		gear2_speed = gear3_speed = 0;
	}
};

// Полный блок описания одной машины в .gci.
struct GciCar {
	std::string name;      // строка {name}
	int model;             // {model}
	int turbo;             // {turbo}
	int value;             // {value}
	CarPhysics physics;    // все f-параметры

	// Дамп оригинальных строк блока (для побайтового сохранения без правок).
	std::vector<std::string> rawLines;

	GciCar() : model(0), turbo(0), value(0) {}
};

class GciFile {
public:
	GciFile() : m_ok(false) {}

	// Разбор текста .gci (UTF-8, символы CR/LF допускаются).
	// Пропускает комментарии вида {*******...} и пустые строки.
	bool ParseText(const std::string& text);

	// Сериализация в текст .gci. Если файл не менялся и ведётся без правок,
	// используется режим roundtrip: сохраняется исходный текст дословно.
	std::string SaveText() const;

	const std::vector<GciCar>& Cars() const { return m_cars; }
	std::vector<GciCar>&       Cars()       { return m_cars; }

	const GciCar* FindByModel(int model) const;
	GciCar*       FindByModel(int model);

	bool IsOk() const { return m_ok; }

	// Режим roundtrip: исходный текст сохраняется, пока не было правок.
	void SetDirty() { m_dirty = true; }
	bool IsDirty() const { return m_dirty; }

private:
	std::vector<GciCar> m_cars;
	std::string m_headerComments; // комментарий-заголовок в начале файла
	std::string m_rawText;        // исходный текст (для roundtrip без правок)
	bool m_ok;
	bool m_dirty;
};

// Разбор строки вида "значение {имя}" -> значение (возможно c префиксом 'f')
// и имя в {}. Возвращает false при ошибке.
bool ParseGciLine(const std::string& line, std::string& name, std::string& valueText);

} // namespace gta2

#endif // !__GTA2_TOOLS_GCI_FORMAT_H_
