#include "ZoneInfo.h"

#include <cstring>
#include <cstdio>

namespace gta2 {

// ---------------------------------------------------------------------------
// Кодирование одной записи зоны (Tmap_zone): 6 фикс. байт + name.
// ---------------------------------------------------------------------------
std::vector<unsigned char> ZoneInfo::Encode() const
{
	std::vector<unsigned char> out;
	out.push_back(zone_type);
	out.push_back(x);
	out.push_back(y);
	out.push_back(w);
	out.push_back(h);
	// name_length не должен превышать 255.
	size_t nl = name.size();
	if (nl > 255) nl = 255;
	out.push_back(static_cast<unsigned char>(nl));
	for (size_t i = 0; i < nl; i++)
		out.push_back(static_cast<unsigned char>(name[i]));
	return out;
}

// ---------------------------------------------------------------------------
// Вспомогательные функции сериализации секций.
// ---------------------------------------------------------------------------
static void writeSection(std::vector<unsigned char>& out,
                         const std::string& name,
                         const std::vector<unsigned char>& data)
{
	out.insert(out.end(), name.begin(), name.end());
	unsigned int sz = static_cast<unsigned int>(data.size());
	for (int i = 0; i < 4; i++)
		out.push_back(static_cast<unsigned char>((sz >> (8 * i)) & 0xFF));
	out.insert(out.end(), data.begin(), data.end());
}

static void buildZoneSection(const std::vector<ZoneInfo>& zones,
                             std::vector<unsigned char>& out)
{
	std::vector<unsigned char> zoneData;
	for (size_t i = 0; i < zones.size(); i++) {
		std::vector<unsigned char> rec = zones[i].Encode();
		zoneData.insert(zoneData.end(), rec.begin(), rec.end());
	}
	writeSection(out, std::string("ZONE"), zoneData);
}

// ---------------------------------------------------------------------------
// Разбор файла .gmp (GBMP + секции). Извлекает секцию ZONE.
// ---------------------------------------------------------------------------
bool ZoneFile::Parse(const unsigned char* data, size_t size)
{
	m_zones.clear();
	m_other.clear();
	m_error.clear();
	m_ok = false;

	size_t pos = 0;

	// Сигнатура GBMP.
	if (pos + 4 > size || data[pos + 0] != 'G' || data[pos + 1] != 'B'
	                  || data[pos + 2] != 'M' || data[pos + 3] != 'P') {
		m_error = "not a GTA2 .gmp file (missing 'GBMP' header)";
		return false;
	}
	pos += 4;

	// Версия (слово, little-endian).
	if (pos + 2 > size) { m_error = "truncated version"; return false; }
	m_version = static_cast<unsigned short>(data[pos] | (data[pos + 1] << 8));
	pos += 2;

	bool foundZone = false;

	while (pos + 8 <= size) {
		// Имя секции (4 байта) + размер данных (4 байта LE).
		std::string secName(reinterpret_cast<const char*>(data + pos), 4);
		unsigned int secSize = 0;
		for (int i = 0; i < 4; i++)
			secSize |= static_cast<unsigned int>(data[pos + 4 + i]) << (8 * i);
		size_t dataStart = pos + 8;
		size_t dataEnd = dataStart + secSize;

		if (dataEnd > size) {
			m_error = "section '" + secName + "' extends past end of file";
			return false;
		}

		if (secName == "ZONE") {
			foundZone = true;
			// Сохраняем маркер секции ZONE (позицию), чтобы при сохранении
			// пересобранная секция ZONE встала на своё исходное место.
			m_other.push_back(std::make_pair(secName, std::vector<unsigned char>()));
			// Читаем записи зон до конца секции.
			size_t p = dataStart;
			const size_t readTo = dataEnd;
			while (p + 6 <= readTo) {
				ZoneInfo z;
				z.zone_type = data[p + 0];
				z.x         = data[p + 1];
				z.y         = data[p + 2];
				z.w         = data[p + 3];
				z.h         = data[p + 4];
				unsigned int nl = data[p + 5];
				size_t recEnd = p + 6 + nl;
				if (recEnd > readTo) {
					m_error = "zone record overruns ZONE section";
					return false;
				}
				z.name.assign(reinterpret_cast<const char*>(data + p + 6), nl);
				m_zones.push_back(z);
				p = recEnd;
			}
			pos = dataEnd;
		} else {
			// Прочие секции: копируем как есть.
			std::vector<unsigned char> blob(data + dataStart, data + dataEnd);
			m_other.push_back(std::make_pair(secName, blob));
			pos = dataEnd;
		}
	}

	if (!foundZone) {
		m_error = "no ZONE section found";
		return false;
	}

	m_ok = true;
	return true;
}

// ---------------------------------------------------------------------------
// Сериализация .gmp обратно в байты.
// Секция ZONE заменяется текущим набором зон; порядок прочих секций
// сохраняется прежним (из исходного файла).
// ---------------------------------------------------------------------------
std::vector<unsigned char> ZoneFile::Save() const
{
	std::vector<unsigned char> out;

	// Сигнатура + версия.
	const char magic[4] = { 'G', 'B', 'M', 'P' };
	out.insert(out.end(), magic, magic + 4);
	out.push_back(static_cast<unsigned char>(m_version & 0xFF));
	out.push_back(static_cast<unsigned char>((m_version >> 8) & 0xFF));

	bool zoneWritten = false;
	for (size_t i = 0; i < m_other.size(); i++) {
		if (m_other[i].first == "ZONE") {
			if (!zoneWritten) {
				// Пересобранную секцию ZONE пишем на место исходного маркера.
				buildZoneSection(m_zones, out);
				zoneWritten = true;
			}
			// Старые/дублирующие маркеры ZONE пропускаем.
			continue;
		}
		writeSection(out, m_other[i].first, m_other[i].second);
	}
	// Если ZONE не было в исходнике (быть не должно), добавляем в конец.
	if (!zoneWritten)
		buildZoneSection(m_zones, out);

	return out;
}

} // namespace gta2
