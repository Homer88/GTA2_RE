#include "ScrFormat.h"

#include <utility>

namespace gta2 {

namespace {
uint16_t rd16(const std::vector<unsigned char>& d, size_t o)
{
	return (uint16_t)(d[o] | (d[o + 1] << 8));
}
} // namespace

ScrFormat::ScrFormat()
	: m_mission(false), m_word0(0), m_word1(0), m_ok(false)
{
}

bool ScrFormat::Parse(const unsigned char* data, size_t size)
{
	m_raw.assign(data, data + size);
	m_ok = true;
	m_mission = false;

	if (size < kHeaderSize + kObjectiveSize)
		return true; // файл слишком мал для миссии — остаётся сырым

	uint16_t word0 = (uint16_t)(data[0] | (data[1] << 8));
	uint16_t word1 = (uint16_t)(data[2] | (data[3] << 8));
	uint32_t dataLen = (uint32_t)(data[4] | (data[5] << 8) |
	                              (data[6] << 16) | (uint32_t)(data[7] << 24));

	// Проверка контейнера: размер файла == 8 + 3072 + dataLen.
	if ((size_t)dataLen != size - kHeaderSize - kObjectiveSize)
		return true; // не миссийная раскладка — сырые байты

	m_word0 = word0;
	m_word1 = word1;
	m_objective.assign(data + kHeaderSize, data + kHeaderSize + kObjectiveSize);
	m_data.assign(data + kHeaderSize + kObjectiveSize, data + kHeaderSize + kObjectiveSize + dataLen);
	m_mission = true;
	return true;
}

std::vector<ScriptLine> ScrFormat::Lines() const
{
	std::vector<ScriptLine> v;
	if (!m_mission) return v;

	// Таблица смещений: objective[u16 * 2], индекс = uid - word0;
	// значение = абсолютное смещение строки в MAIN_BUFFER; 0 = строки нет.
	std::vector<std::pair<uint16_t, size_t>> tab; // (uid, абсолютное смещение)
	for (size_t i = 0; i < kObjectiveSize / 2; i++) {
		uint16_t off = rd16(m_objective, i * 2);
		if (off != 0)
			tab.push_back(std::make_pair((uint16_t)(m_word0 + i), (size_t)off));
	}
	if (tab.empty()) return v;

	const size_t base = tab[0].second;
	v.reserve(tab.size());
	for (size_t i = 0; i < tab.size(); i++) {
		const size_t rel = tab[i].second - base;
		if (rel >= m_data.size()) continue;
		size_t len = (i + 1 < tab.size()) ? (tab[i + 1].second - tab[i].second)
		                                  : (m_data.size() - rel);
		if (rel + len > m_data.size())
			len = m_data.size() - rel;

		ScriptLine l;
		l.offset  = (uint32_t)rel;
		l.uid     = tab[i].first;
		l.type    = rd16(m_data, rel + 2);
		l.nextUid = rd16(m_data, rel + 4);
		l.chain   = rd16(m_data, rel + 6);
		l.size    = len;
		if (len > 8) {
			l.params.assign(m_data.begin() + rel + 8,
			                m_data.begin() + rel + len);
		}
		v.push_back(l);
	}
	return v;
}

std::vector<unsigned char> ScrFormat::Save() const
{
	std::vector<unsigned char> out;
	if (!m_mission) {
		out = m_raw;
		return out;
	}

	out.reserve(kHeaderSize + kObjectiveSize + m_data.size());

	auto putWord = [&](uint16_t v) {
		out.push_back((unsigned char)(v & 0xFF));
		out.push_back((unsigned char)((v >> 8) & 0xFF));
	};
	auto putDword = [&](uint32_t v) {
		out.push_back((unsigned char)(v & 0xFF));
		out.push_back((unsigned char)((v >> 8) & 0xFF));
		out.push_back((unsigned char)((v >> 16) & 0xFF));
		out.push_back((unsigned char)((v >> 24) & 0xFF));
	};

	putWord(m_word0);
	putWord(m_word1);
	putDword((uint32_t)m_data.size());

	std::vector<unsigned char> obj = m_objective;
	obj.resize(kObjectiveSize, 0);
	out.insert(out.end(), obj.begin(), obj.end());
	out.insert(out.end(), m_data.begin(), m_data.end());
	return out;
}

} // namespace gta2