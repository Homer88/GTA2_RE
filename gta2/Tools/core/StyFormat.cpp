#include "StyFormat.h"

#include <cstring>

namespace gta2 {

namespace {

bool ReadU32(const unsigned char* d, size_t size, size_t off, unsigned int& out)
{
	if (off + 4 > size) return false;
	out = (unsigned int)(d[off] | (d[off + 1] << 8) | (d[off + 2] << 16) |
	                     ((unsigned int)d[off + 3] << 24));
	return true;
}

void WriteU16(std::vector<unsigned char>& v, unsigned short x)
{
	v.push_back((unsigned char)(x & 0xFF));
	v.push_back((unsigned char)((x >> 8) & 0xFF));
}

void WriteU32(std::vector<unsigned char>& v, unsigned int x)
{
	v.push_back((unsigned char)(x & 0xFF));
	v.push_back((unsigned char)((x >> 8) & 0xFF));
	v.push_back((unsigned char)((x >> 16) & 0xFF));
	v.push_back((unsigned char)((x >> 24) & 0xFF));
}

} // namespace

StyFile::StyFile()
{
	m_magic[0] = 'G'; m_magic[1] = 'B'; m_magic[2] = 'S'; m_magic[3] = 'T';
	m_version = 0x02BC; // 700
	m_ok = false;
}

bool StyFile::Parse(const unsigned char* data, size_t size)
{
	m_sections.clear();
	m_ok = false;

	if (!data || size < 6) return false;
	if (std::memcmp(data, "GBST", 4) != 0) return false;
	std::memcpy(m_magic, data, 4);
	m_version = (unsigned short)(data[4] | (data[5] << 8));

	size_t pos = 6;
	while (pos + 8 <= size) {
		char name[5];
		name[0] = (char)data[pos];
		name[1] = (char)data[pos + 1];
		name[2] = (char)data[pos + 2];
		name[3] = (char)data[pos + 3];
		name[4] = '\0';
		unsigned int bsize = 0;
		if (!ReadU32(data, size, pos + 4, bsize)) { m_sections.clear(); return false; }

		size_t dataOff = pos + 8;
		if (dataOff + bsize > size) { m_sections.clear(); return false; }

		StySection s;
		s.name[0] = name[0]; s.name[1] = name[1];
		s.name[2] = name[2]; s.name[3] = name[3];
		s.data.assign(data + dataOff, data + dataOff + bsize);
		m_sections.push_back(s);

		pos = dataOff + bsize;
	}

	m_ok = true;
	return true;
}

std::vector<unsigned char> StyFile::Save() const
{
	std::vector<unsigned char> out;
	out.insert(out.end(), m_magic, m_magic + 4);
	WriteU16(out, m_version);
	for (size_t i = 0; i < m_sections.size(); i++) {
		const StySection& s = m_sections[i];
		out.insert(out.end(), s.name, s.name + 4);
		WriteU32(out, (unsigned int)s.data.size());
		out.insert(out.end(), s.data.begin(), s.data.end());
	}
	return out;
}

const StySection* StyFile::FindSection(const char* name) const
{
	for (size_t i = 0; i < m_sections.size(); i++)
		if (m_sections[i].Is(name))
			return &m_sections[i];
	return NULL;
}

StySection* StyFile::MutableSection(const char* name)
{
	for (size_t i = 0; i < m_sections.size(); i++)
		if (m_sections[i].Is(name))
			return &m_sections[i];
	return NULL;
}

StySection* StyFile::SetSection(const char* name, const std::vector<unsigned char>& data)
{
	StySection* s = MutableSection(name);
	if (s) {
		s->data = data;
		return s;
	}
	StySection n;
	n.name[0] = name[0]; n.name[1] = name[1];
	n.name[2] = name[2]; n.name[3] = name[3];
	n.data = data;
	m_sections.push_back(n);
	return &m_sections.back();
}

} // namespace gta2
