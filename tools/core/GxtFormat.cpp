#include "GxtFormat.h"

#include <algorithm>
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

std::wstring ReadUtf16Le(const unsigned char* d, size_t size, size_t off)
{
	std::wstring s;
	for (size_t p = off; p + 1 < size; p += 2) {
		unsigned short u = (unsigned short)(d[p] | (d[p + 1] << 8));
		if (u == 0)
			break;
		s.push_back((wchar_t)u);
	}
	return s;
}

void AppendPrintedKey(std::vector<unsigned char>& v, const std::string& key)
{
	char out8[8];
	std::memset(out8, 0, sizeof(out8));
	for (size_t k = 0; k < key.size() && k < 8; k++)
		out8[k] = key[k];
	v.insert(v.end(), out8, out8 + 8);
}

} // namespace

bool GxtFile::Load(const unsigned char* data, size_t size)
{
	m_strings.clear();
	m_keyBlob.clear();
	m_strBlob.clear();
	m_ok = false;
	m_dirty = true;

	if (!data || size < 8) return false;
	// Магик: "GBL" + буква языка (E/F/G/I/S). Проверяем первые три байта.
	if (std::memcmp(data, "GBL", 3) != 0) return false;
	std::memcpy(m_magic, data, 4);
	m_version = (unsigned short)(data[4] | (data[5] << 8));

	// Поиск блоков TKEY и TDAT (имена + размеры данных).
	size_t pos = 6;
	size_t tkeyData = 0, tkeyBytes = 0, tdatData = 0, tdatBytes = 0;
	bool hasTkey = false, hasTdat = false;
	while (pos + 8 <= size) {
		char name[5];
		name[0] = (char)data[pos];
		name[1] = (char)data[pos + 1];
		name[2] = (char)data[pos + 2];
		name[3] = (char)data[pos + 3];
		name[4] = '\0';
		unsigned int bsize = 0;
		if (!ReadU32(data, size, pos + 4, bsize)) return false;
		if (std::strcmp(name, "TKEY") == 0) {
			tkeyData = pos + 8;
			tkeyBytes = bsize;
			hasTkey = true;
		} else if (std::strcmp(name, "TDAT") == 0) {
			tdatData = pos + 8;
			tdatBytes = bsize;
			hasTdat = true;
		}
		pos += 8 + (size_t)bsize;
	}
	if (!hasTkey || !hasTdat) return false;
	if (tkeyBytes % 12 != 0) return false;
	if (tkeyData + tkeyBytes > size) return false;
	if (tdatData + tdatBytes != size) return false; // TDAT - последний блок

	m_keyBlob.assign(data + tkeyData, data + tkeyData + tkeyBytes);
	m_strBlob.assign(data + tdatData, data + tdatData + tdatBytes);

	// Записи TKEY: по 12 байт [u32 offset][char key[8]].
	size_t recCount = tkeyBytes / 12;
	m_strings.reserve(recCount);
	for (size_t i = 0; i < recCount; i++) {
		size_t p = tkeyData + i * 12;
		unsigned int off = 0;
		if (!ReadU32(data, size, p, off)) { m_strings.clear(); return false; }
		size_t abs = tdatData + (size_t)off;
		if (abs >= size) { m_strings.clear(); return false; }

		GxtString s;
		char key[9];
		std::memset(key, 0, sizeof(key));
		for (int k = 0; k < 8; k++)
			key[k] = (char)data[p + 4 + (size_t)k];
		s.key = key; // c-строка: обрезается по первому нулю

		s.text = ReadUtf16Le(data, size, abs);
		m_strings.push_back(s);
	}

	m_ok = true;
	m_dirty = false;
	return true;
}

std::vector<unsigned char> GxtFile::Save() const
{
	std::vector<unsigned char> out;

	// Заголовок: магик + версия.
	out.insert(out.end(), m_magic, m_magic + 4);
	WriteU16(out, m_version);

	if (!m_dirty && !m_keyBlob.empty()) {
		// Файл не менялся — переписываем исходные блоки дословно.
		const char tkeyTag[8] = { 'T', 'K', 'E', 'Y' };
		out.insert(out.end(), tkeyTag, tkeyTag + 4);
		WriteU32(out, (unsigned int)m_keyBlob.size());
		out.insert(out.end(), m_keyBlob.begin(), m_keyBlob.end());
		const char tdatTag[8] = { 'T', 'D', 'A', 'T' };
		out.insert(out.end(), tdatTag, tdatTag + 4);
		WriteU32(out, (unsigned int)m_strBlob.size());
		out.insert(out.end(), m_strBlob.begin(), m_strBlob.end());
		return out;
	}

	// Файл изменён: ключи сортируем (как в оригинале), строки пакуем плотно.
	std::vector<GxtString> sorted = m_strings;
	std::stable_sort(sorted.begin(), sorted.end(),
	                 [](const GxtString& a, const GxtString& b) { return a.key < b.key; });

	out.push_back('T'); out.push_back('K'); out.push_back('E'); out.push_back('Y');
	WriteU32(out, (unsigned int)(sorted.size() * 12));

	unsigned int dataBytes = 0;
	for (size_t i = 0; i < sorted.size(); i++)
		dataBytes += (unsigned int)(2 + sorted[i].text.size() * 2);

	unsigned int runOff = 0;
	std::vector<unsigned int> offs(sorted.size());
	for (size_t i = 0; i < sorted.size(); i++) {
		WriteU32(out, runOff);
		AppendPrintedKey(out, sorted[i].key);
		offs[i] = runOff;
		runOff += (unsigned int)(2 + sorted[i].text.size() * 2);
	}

	out.push_back('T'); out.push_back('D'); out.push_back('A'); out.push_back('T');
	WriteU32(out, dataBytes);
	for (size_t i = 0; i < sorted.size(); i++) {
		const std::wstring& t = sorted[i].text;
		for (size_t k = 0; k < t.size(); k++) WriteU16(out, (unsigned short)t[k]);
		WriteU16(out, 0);
	}

	return out;
}

const GxtString* GxtFile::Find(const std::string& key) const
{
	for (size_t i = 0; i < m_strings.size(); i++)
		if (m_strings[i].key == key)
			return &m_strings[i];
	return NULL;
}

bool GxtFile::SetText(size_t index, const std::wstring& text)
{
	if (index >= m_strings.size())
		return false;
	if (m_strings[index].text == text)
		return true;
	m_strings[index].text = text;
	m_dirty = true;
	return true;
}

bool GxtFile::Add(const std::string& key, const std::wstring& text)
{
	if (key.empty() || key.size() > 8 || Find(key) != NULL)
		return false;
	GxtString s;
	s.key = key;
	s.text = text;
	m_strings.push_back(s);
	m_dirty = true;
	return true;
}

bool GxtFile::Remove(size_t index)
{
	if (index >= m_strings.size())
		return false;
	m_strings.erase(m_strings.begin() + index);
	m_dirty = true;
	return true;
}

} // namespace gta2