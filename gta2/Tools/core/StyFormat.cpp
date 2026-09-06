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

int StyFile::NumTiles() const
{
	const StySection* t = FindSection("TILE");
	if (!t) return 0;
	return (int)(t->data.size() / 4096);
}

bool StyFile::RenderTile(int tileIdx, std::vector<unsigned char>& rgba) const
{
	const StySection* t = FindSection("TILE");
	const StySection* px = FindSection("PALX");
	const StySection* pp = FindSection("PPAL");
	if (!t || !px || !pp) return false;
	if (tileIdx < 0 || (size_t)tileIdx * 4096 > t->data.size()) return false;

	rgba.assign(64 * 64 * 4, 0);
	unsigned int palIdx = 0;
	if ((size_t)tileIdx * 2 + 2 <= px->data.size()) {
		palIdx = px->data[tileIdx * 2] | (px->data[tileIdx * 2 + 1] << 8);
	}
	if ((size_t)(palIdx / 64) * 65536 > pp->data.size()) return true;

	const unsigned char* tile = t->data.data() + (size_t)tileIdx * 4096;
	for (int y = 0; y < 64; y++) {
		for (int x = 0; x < 64; x++) {
			unsigned char c = tile[y * 64 + x];
			if (c == 0) continue; // прозрачный
			// Цвета в PPAL разложены по 64 палитрам в блоке:
			// off = блок(64 палитры) + цвет*256 + (палитра в блоке)*4
			size_t off = (size_t)(palIdx / 64) * 65536 + (size_t)c * 256 + (size_t)(palIdx % 64) * 4;
			if (off + 4 > pp->data.size()) continue;
			unsigned char* dst = &rgba[(size_t)(y * 64 + x) * 4];
			dst[0] = pp->data[off + 2]; // R
			dst[1] = pp->data[off + 1]; // G
			dst[2] = pp->data[off];     // B
			dst[3] = 255;
		}
	}
	return true;
}

bool StyFile::RenderSprite(int spriteIdx, std::vector<unsigned char>& rgba, int& w, int& h) const
{
	const StySection* sprx = FindSection("SPRX");
	const StySection* sprg = FindSection("SPRG");
	const StySection* pp   = FindSection("PPAL");
	const StySection* px   = FindSection("PALX");
	const StySection* palb = FindSection("PALB");
	if (!sprx || !sprg || !pp || !px || !palb) return false;

	const size_t rec = 8;
	if ((size_t)spriteIdx * rec + rec > sprx->data.size()) return false;

	// SPRX: offset(u32) + Width(u8) + Height(u8) + Pad(u16).
	size_t off = (size_t)spriteIdx * rec;
	unsigned int o = sprx->data[off]
		| ((unsigned int)sprx->data[off + 1] << 8)
		| ((unsigned int)sprx->data[off + 2] << 16)
		| ((unsigned int)sprx->data[off + 3] << 24);
	w = sprx->data[off + 4];
	h = sprx->data[off + 5];

	// Палитра спрайта: PALB.pals(0) + spriteIdx -> PALX -> PPAL.
	unsigned int palIdx = 0;
	unsigned int palBase = 0;
	if (palb->data.size() >= 2) palBase = palb->data[0] | (palb->data[1] << 8);
	unsigned int pl = palBase + (unsigned int)spriteIdx;
	if ((size_t)pl * 2 + 2 <= px->data.size()) {
		palIdx = px->data[pl * 2] | (px->data[pl * 2 + 1] << 8);
	}
	if ((size_t)(palIdx / 64) * 65536 + 65536 > pp->data.size()) return false;

	rgba.assign((size_t)w * h * 4, 0);
	// Каждая строка спрайта — первые w байт 256-байтовой строки SPRG.
	for (int y = 0; y < h; y++) {
		size_t src = o + (size_t)y * 256;
		if (src + w > sprg->data.size()) continue;
		for (int x = 0; x < w; x++) {
			unsigned char c = sprg->data[src + x];
			if (c == 0) continue; // прозрачный
			// Цвет из физической палитры palIdx (PPAL транспонирован: блок из
			// 64 палитр, затем цвет, затем палитра в блоке):
			//   off = (palIdx/64)*65536 + c*256 + (palIdx%64)*4   (B,G,R,A)
			size_t coff = (size_t)(palIdx / 64) * 65536 + (size_t)c * 256
				+ (size_t)(palIdx % 64) * 4;
			if (coff + 4 > pp->data.size()) continue;
			unsigned char* dst = &rgba[((size_t)y * w + x) * 4];
			dst[0] = pp->data[coff + 2]; // R
			dst[1] = pp->data[coff + 1]; // G
			dst[2] = pp->data[coff];     // B
			dst[3] = 255;
		}
	}
	return true;
}

int StyFile::MapObjectSpriteBase() const
{
	const StySection* sprb = FindSection("SPRB");
	if (!sprb || sprb->data.size() < 12) return -1;
	// tSprb: iCar,iPed,iCode_Obj,iMap_Obj,iUser,iFont (слов по 2 байта).
	return (int)(sprb->data[6] | (sprb->data[7] << 8));
}

int StyFile::NumSprites() const
{
	const StySection* sprx = FindSection("SPRX");
	if (!sprx) return 0;
	return (int)(sprx->data.size() / 8);
}

int StyFile::MapObjectSpriteOffset(int type) const
{
	const StySection* obji = FindSection("OBJI");
	if (!obji || type < 0) return -1;
	const size_t rec = 2;
	int off = 0;
	for (int i = 0; (size_t)i * rec + rec <= obji->data.size(); i++) {
		if (i == type) return off;
		off += obji->data[(size_t)i * rec + 1]; // второй байт записи = число спрайтов
	}
	return -1;
}

int StyFile::MapObjectSpriteIndex(int type) const
{
	int base = MapObjectSpriteBase();
	int off = MapObjectSpriteOffset(type);
	if (base < 0 || off < 0) return -1;
	return base + off;
}

} // namespace gta2
