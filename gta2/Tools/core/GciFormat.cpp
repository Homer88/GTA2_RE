#include "GciFormat.h"

#include <cstdlib>
#include <cstring>

namespace gta2 {

namespace {

std::string Trim(const std::string& s)
{
	size_t b = s.find_first_not_of(" \t\r\n");
	if (b == std::string::npos) return std::string();
	size_t e = s.find_last_not_of(" \t\r\n");
	return s.substr(b, e - b + 1);
}

// Пропускает BOM и возвращает строки текста (без CR).
std::vector<std::string> SplitLines(const std::string& text)
{
	std::vector<std::string> lines;
	std::string cur;
	for (size_t i = 0; i < text.size(); i++) {
		char c = text[i];
		if (c == '\n') {
			if (!cur.empty() && cur[cur.size() - 1] == '\r')
				cur.erase(cur.size() - 1);
			lines.push_back(cur);
			cur.clear();
		} else if (c != '\r') {
			cur.push_back(c);
		}
	}
	if (!cur.empty())
		lines.push_back(cur);
	return lines;
}

// Форматирование числа с сохранением min 3 знаков после запятой (как в gci).
std::string FormatNumber(double v)
{
	char buf[64];
	// Сохраняем 3 знака (в оригинале значения вида 16.500).
	int n = std::snprintf(buf, sizeof(buf), "%.3f", v);
	// Убираем лишние нули в конце, но не раньше 2 знаков: 16.500 -> 16.500
	// (оригинал не усекает), поэтому оставляем как есть.
	(void)n;
	return std::string(buf);
}

} // namespace

bool ParseGciLine(const std::string& line, std::string& name, std::string& valueText)
{
	// Ищем последнюю '{' ... '}'.
	size_t ob = line.rfind('{');
	size_t cb = line.rfind('}');
	if (ob == std::string::npos || cb == std::string::npos || cb < ob)
		return false;
	name = Trim(line.substr(ob + 1, cb - ob - 1));
	valueText = Trim(line.substr(0, ob));
	return true;
}

bool GciFile::ParseText(const std::string& text)
{
	m_cars.clear();
	m_rawText = text;
	m_ok = false;
	m_dirty = false;

	std::vector<std::string> lines = SplitLines(text);
	size_t i = 0;

	// Собираем комментарий-заголовок (строки {****} в начале).
	std::string header;
	while (i < lines.size()) {
		std::string t = Trim(lines[i]);
		if (t.empty()) { if (!header.empty()) header += "\n"; i++; continue; }
		if (t.size() >= 4 && t[0] == '{' && t[t.size()-1] == '}' &&
		    t.find('*') != std::string::npos) {
			header += lines[i];
			header += "\n";
			i++;
			continue;
		}
		break;
	}
	m_headerComments = header;

	while (i < lines.size()) {
		std::string t = Trim(lines[i]);
		if (t.empty()) { i++; continue; }

		GciCar car;
		std::string block[22];
		int blockLen = 0;
		// Блок: 22 строки от {name} до {gear3 speed} (индексы 0..21).
		while (i < lines.size() && blockLen < 22) {
			std::string line = lines[i];
			std::string tt = Trim(line);
			if (tt.empty()) { i++; continue; }
			block[blockLen] = line;
			blockLen++;
			i++;
		}
		if (blockLen < 22) { m_cars.clear(); return false; }

		// Парсим блок.
		for (int k = 0; k < 22; k++)
			car.rawLines.push_back(block[k]);

		// {name} (индекс 0).
		{
			std::string nm, vv;
			if (!ParseGciLine(block[0], nm, vv)) { m_cars.clear(); return false; }
			car.name = nm;
		}
		// model (1), turbo (2), value (3) — целые, pad (4) пропускаем.
		{
			std::string nm, vv;
			if (!ParseGciLine(block[1], nm, vv)) { m_cars.clear(); return false; }
			car.model = std::atoi(vv.c_str());
		}
		{
			std::string nm, vv;
			if (!ParseGciLine(block[2], nm, vv)) { m_cars.clear(); return false; }
			car.turbo = std::atoi(vv.c_str());
		}
		{
			std::string nm, vv;
			if (!ParseGciLine(block[3], nm, vv)) { m_cars.clear(); return false; }
			car.value = std::atoi(vv.c_str());
		}

		// Физика: индексы 5..21 -> 17 параметров (мл. 5=mass, 21=gear3 speed).
		double* dest[17] = {
			&car.physics.mass, &car.physics.front_drive_bias, &car.physics.front_mass_bias,
			&car.physics.brake_friction, &car.physics.turn_in, &car.physics.turn_ratio,
			&car.physics.rear_end_stability, &car.physics.handbrake_slide_value,
			&car.physics.thrust, &car.physics.max_speed, &car.physics.anti_strength,
			&car.physics.skid_threshhold, &car.physics.gear1_multiplier,
			&car.physics.gear2_multiplier, &car.physics.gear3_multiplier,
			&car.physics.gear2_speed, &car.physics.gear3_speed
		};
		for (int p = 0; p < 17; p++) {
			std::string nm, vv;
			if (!ParseGciLine(block[5 + p], nm, vv)) { m_cars.clear(); return false; }
			if (!vv.empty() && (vv[0] == 'f' || vv[0] == 'F'))
				vv = vv.substr(1);
			*dest[p] = std::atof(vv.c_str());
		}

		m_cars.push_back(car);
	}

	m_ok = true;
	return true;
}

std::string GciFile::SaveText() const
{
	if (!m_dirty && !m_rawText.empty())
		return m_rawText;

	std::string out;
	if (!m_headerComments.empty())
		out += m_headerComments;

	for (size_t i = 0; i < m_cars.size(); i++) {
		const GciCar& c = m_cars[i];
		if (i > 0) out += "\n";
		out += "{" + c.name + "}\n";
		out += std::to_string(c.model) + " {model}\n";
		out += std::to_string(c.turbo) + " {turbo}\n";
		out += std::to_string(c.value) + " {value}\n";
		out += "0 {pad}\n";
		out += "f" + FormatNumber(c.physics.mass) + " {mass}\n";
		out += "f" + FormatNumber(c.physics.front_drive_bias) + " {front drive bias}\n";
		out += "f" + FormatNumber(c.physics.front_mass_bias) + " {front mass bias}\n";
		out += "f" + FormatNumber(c.physics.brake_friction) + " {brake friction}\n";
		out += "f" + FormatNumber(c.physics.turn_in) + " {turn in}\n";
		out += "f" + FormatNumber(c.physics.turn_ratio) + " {turn ratio}\n";
		out += "f" + FormatNumber(c.physics.rear_end_stability) + " {rear end stability}\n";
		out += "f" + FormatNumber(c.physics.handbrake_slide_value) + " {handbrake slide value}\n";
		out += "f" + FormatNumber(c.physics.thrust) + " {thrust}\n";
		out += "f" + FormatNumber(c.physics.max_speed) + " {max_speed}\n";
		out += "f" + FormatNumber(c.physics.anti_strength) + " {anti strength}\n";
		out += "f" + FormatNumber(c.physics.skid_threshhold) + " {skid threshhold}\n";
		out += "f" + FormatNumber(c.physics.gear1_multiplier) + " {gear1 multiplier}\n";
		out += "f" + FormatNumber(c.physics.gear2_multiplier) + " {gear2 multiplier}\n";
		out += "f" + FormatNumber(c.physics.gear3_multiplier) + " {gear3 multiplier}\n";
		out += "f" + FormatNumber(c.physics.gear2_speed) + " {gear2 speed}\n";
		out += "f" + FormatNumber(c.physics.gear3_speed) + " {gear3 speed}\n";
	}
	return out;
}

const GciCar* GciFile::FindByModel(int model) const
{
	for (size_t i = 0; i < m_cars.size(); i++)
		if (m_cars[i].model == model)
			return &m_cars[i];
	return NULL;
}

GciCar* GciFile::FindByModel(int model)
{
	for (size_t i = 0; i < m_cars.size(); i++)
		if (m_cars[i].model == model)
			return &m_cars[i];
	return NULL;
}

} // namespace gta2
