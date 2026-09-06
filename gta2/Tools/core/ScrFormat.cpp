#include "ScrFormat.h"

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
	const size_t n = m_data.size() / 12;
	v.reserve(n);
	for (size_t i = 0; i < n; i++) {
		size_t o = i * 12;
		ScriptLine l;
		l.offset = (uint32_t)o;
		l.uid    = rd16(m_data, o);
		l.type   = rd16(m_data, o + 2);
		l.p1     = rd16(m_data, o + 4);
		l.p2     = rd16(m_data, o + 6);
		l.p3     = rd16(m_data, o + 8);
		l.p4     = rd16(m_data, o + 10);
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