#include "GmpFile.h"

#include <cstring>
#include <cstdio>
#include <map>

namespace gta2 {

// ---------------------------------------------------------------------------
// Вспомогательные функции чтения/записи little-endian.
// ---------------------------------------------------------------------------
static uint16_t rd16(const unsigned char* p) { return (uint16_t)(p[0] | (p[1] << 8)); }
static uint32_t rd32(const unsigned char* p) { return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24); }
static void wr16(std::vector<unsigned char>& v, uint16_t x) { v.push_back((unsigned char)(x & 0xFF)); v.push_back((unsigned char)((x >> 8) & 0xFF)); }
static void wr32(std::vector<unsigned char>& v, uint32_t x) { v.push_back((unsigned char)(x & 0xFF)); v.push_back((unsigned char)((x >> 8) & 0xFF)); v.push_back((unsigned char)((x >> 16) & 0xFF)); v.push_back((unsigned char)((x >> 24) & 0xFF)); }
static void wr16_at(unsigned char* p, uint16_t x) { p[0] = (unsigned char)(x & 0xFF); p[1] = (unsigned char)((x >> 8) & 0xFF); }

static void writeSection(std::vector<unsigned char>& out,
                         const std::string& name,
                         const std::vector<unsigned char>& data)
{
	out.insert(out.end(), name.begin(), name.end());
	wr32(out, (uint32_t)data.size());
	out.insert(out.end(), data.begin(), data.end());
}

// ---------------------------------------------------------------------------
// BlockInfo
// ---------------------------------------------------------------------------
std::vector<unsigned char> BlockInfo::Encode() const
{
	std::vector<unsigned char> out;
	wr16(out, left);
	wr16(out, right);
	wr16(out, top);
	wr16(out, bottom);
	wr16(out, lid);
	out.push_back(arrows);
	out.push_back(slope);
	return out;
}

// ---------------------------------------------------------------------------
// GmpFile
// ---------------------------------------------------------------------------
GmpFile::GmpFile()
{
	m_version = 0;
	m_ok = false;
	m_numJunctions = m_numH = m_numV = 0;
	m_cityDirty = false;
	for (int i = 0; i < SEC_COUNT; i++) m_has[i] = false;
}

// ---------------------------------------------------------------------------
// Разбор файла .gmp.
// ---------------------------------------------------------------------------
bool GmpFile::Parse(const unsigned char* data, size_t size)
{
	m_zones.clear();
	m_objects.clear();
	m_lights.clear();
	m_hSegments.clear();
	m_vSegments.clear();
	m_junctions.clear();
	m_umap.clear();
	m_city.clear();
	m_cityDirty = false;
	m_raw.clear();
	for (int i = 0; i < SEC_COUNT; i++) m_has[i] = false;
	m_error.clear();
	m_ok = false;

	size_t pos = 0;
	if (pos + 4 > size || data[0] != 'G' || data[1] != 'B' || data[2] != 'M' || data[3] != 'P') {
		m_error = "not a GTA2 .gmp file (missing 'GBMP' header)";
		return false;
	}
	pos += 4;
	if (pos + 2 > size) { m_error = "truncated version"; return false; }
	m_version = rd16(data + pos);
	pos += 2;

	while (pos + 8 <= size) {
		char name[5];
		std::memcpy(name, data + pos, 4);
		name[4] = 0;
		uint32_t secSize = rd32(data + pos + 4);
		size_t dataStart = pos + 8;
		size_t dataEnd = dataStart + secSize;
		if (dataEnd > size) {
			m_error = std::string("section '") + name + "' extends past end of file";
			return false;
		}
		if (!parseSection(data, size, dataStart, name, secSize))
			return false;
		pos = dataEnd;
	}

	m_ok = true;
	return true;
}

bool GmpFile::parseSection(const unsigned char* data, size_t size, size_t pos,
                           const char* name, size_t secSize)
{
	const unsigned char* d = data + pos;

	if (std::strcmp(name, "UMAP") == 0) { m_has[SEC_UMAP] = true; parseUMAP(d, secSize); }
	else if (std::strcmp(name, "DMAP") == 0) { m_has[SEC_DMAP] = true; parseDMAP(d, secSize); }
	else if (std::strcmp(name, "CMAP") == 0) { m_has[SEC_CMAP] = true; parseCMAP(d, secSize); }
	else if (std::strcmp(name, "ZONE") == 0) { m_has[SEC_ZONE] = true; parseZones(d, secSize); }
	else if (std::strcmp(name, "MOBJ") == 0) { m_has[SEC_MOBJ] = true; parseMobj(d, secSize); }
	else if (std::strcmp(name, "PSXM") == 0) { m_has[SEC_PSXM] = true; }
	else if (std::strcmp(name, "ANIM") == 0) { m_has[SEC_ANIM] = true; }
	else if (std::strcmp(name, "LGHT") == 0) { m_has[SEC_LGHT] = true; parseLght(d, secSize); }
	else if (std::strcmp(name, "RGEN") == 0) { m_has[SEC_RGEN] = true; parseRgen(d, secSize); }
	else if (std::strcmp(name, "EDIT") == 0) { m_has[SEC_EDIT] = true; }

	// Сохраняем порядок секций. Для редактируемых (UMAP/ZONE/RGEN) храним
	// маркер с пустыми данными — при Save() на это место подставится
	// пересобранная секция. Прочие храним в сыром виде (побайтовый раунд-трип).
	bool editable = std::strcmp(name, "UMAP") == 0
	             || std::strcmp(name, "ZONE") == 0
	             || std::strcmp(name, "RGEN") == 0;
	std::vector<unsigned char> blob;
	if (!editable) {
		blob.assign(d, d + secSize);
	}
	m_raw.push_back(std::make_pair(std::string(name), blob));
	return true;
}

// ---------------------------------------------------------------------------
// UMAP: несжатая карта 256*256 BlockInfo (12 байт каждая), 8 слоёв by z.
// Документ: struct map { block_info city_scape[8][256][256]; };
// ---------------------------------------------------------------------------
void GmpFile::parseUMAP(const unsigned char* d, size_t n)
{
	// m_city[z*65536 + y*256 + x]
	m_city.assign((size_t)8 * 256 * 256, BlockInfo());
	for (size_t z = 0; z < 8; z++) {
		size_t zBase = z * 256 * 256;
		for (size_t y = 0; y < 256; y++) {
			for (size_t x = 0; x < 256; x++) {
				size_t idx = zBase + y * 256 + x;
				size_t off = idx * 12;
				if (off + 12 > n) break;
				BlockInfo& b = m_city[idx];
				b.left    = rd16(d + off + 0);
				b.right   = rd16(d + off + 2);
				b.top     = rd16(d + off + 4);
				b.bottom  = rd16(d + off + 6);
				b.lid     = rd16(d + off + 8);
				b.arrows  = d[off + 10];
				b.slope   = d[off + 11];
			}
			if (z*65536 + y*256 > n/12) break;
		}
	}
	buildTopViewFromCity();
}

// ---------------------------------------------------------------------------
// Сжатая карта. Подробности формата (официальный документ DMA v8.2):
//   struct {
//     UInt32 base[256][256];       // смещения колонок (dword offset в column)
//     UInt32 column_words;         // число слов в column
//     UInt32 column[N];            // колонки
//     UInt32 num_blocks;           // число блоков
//     block_info block[M];         // 12 байт каждая
//   } compressed_map;
//   Каждая колонка (col_info):
//     UInt8 height;                // верхний уровень (bounded блоки лежат в [offset, height))
//     UInt8 offset;                // нижний уровень
//     UInt16 pad;
//     UInt32 blockd[height-offset];// номера block_info для уровней z = offset..height-1
//   Т.е. слово колонки = 1 + (height-offset).
//   Для клетки (x,y): idx = base[y*256+x]; блоки z<offset или z>=height — пустые.
//   Порядок колонок в column не совпадает с (x,y); смещения даёт base.
//   CMAP аналогичен, но все поля/sлова — 16-битные.
// ---------------------------------------------------------------------------
void GmpFile::decodeCompressedMap(const unsigned char* d, size_t n, bool isDmap)
{
	int ws = isDmap ? 4 : 2;
	size_t baseBytes = (size_t)256 * 256 * ws;
	if (n < baseBytes + ws) return;                  // нет base + column_words

	size_t cwOff = baseBytes;
	size_t colWords = isDmap ? (size_t)rd32(d + cwOff) : (size_t)rd16(d + cwOff);
	size_t colOff = cwOff + ws;
	size_t nbOff = colOff + colWords * ws;
	if (nbOff + ws > n) return;
	size_t numBlocks = isDmap ? (size_t)rd32(d + nbOff) : (size_t)rd16(d + nbOff);
	size_t blockOff = nbOff + ws;

	// Город: m_city[z*65536 + y*256 + x]
	m_city.assign((size_t)8 * 256 * 256, BlockInfo());
	for (size_t y = 0; y < 256; y++) {
		for (size_t x = 0; x < 256; x++) {
			size_t bOff = ((size_t)y * 256 + x) * ws;
			if (bOff + ws > baseBytes) continue;
			size_t idx = isDmap ? (size_t)rd32(d + bOff) : (size_t)rd16(d + bOff);
			size_t cp = colOff + idx * ws;
			if (cp + 1 >= nbOff) continue;
			uint8_t height = d[cp];
			uint8_t offset = d[cp + 1];
			if (offset > 7 || height < offset || height > 8) continue;
			for (int z = offset; z < (int)height; z++) {
				size_t bnp = cp + ws + (size_t)(z - offset) * ws;
				if (bnp + ws > nbOff) break;
				size_t bn = isDmap ? (size_t)rd32(d + bnp) : (size_t)rd16(d + bnp);
				if (bn >= numBlocks) continue;
				size_t bp = blockOff + bn * 12;
				if (bp + 12 > n) break;
				BlockInfo& blk = m_city[(size_t)z * 256 * 256 + (size_t)y * 256 + x];
				blk.left   = rd16(d + bp + 0);
				blk.right  = rd16(d + bp + 2);
				blk.top    = rd16(d + bp + 4);
				blk.bottom = rd16(d + bp + 6);
				blk.lid    = rd16(d + bp + 8);
				blk.arrows = d[bp + 10];
				blk.slope  = d[bp + 11];
			}
		}
	}
	buildTopViewFromCity();
}

void GmpFile::parseDMAP(const unsigned char* d, size_t n) { decodeCompressedMap(d, n, true); }
void GmpFile::parseCMAP(const unsigned char* d, size_t n) { decodeCompressedMap(d, n, false); }

// ---------------------------------------------------------------------------
// Проверка «пустого» блока: все поля равны нулю.
// ---------------------------------------------------------------------------
static bool isEmptyBlock(const BlockInfo& b)
{
	return !b.left && !b.right && !b.top && !b.bottom && !b.lid && !b.arrows && !b.slope;
}

// ---------------------------------------------------------------------------
// Запись блока (правка тайла).
// ---------------------------------------------------------------------------
void GmpFile::SetBlock(int z, int x, int y, const BlockInfo& b)
{
	if (z < 0 || z >= 8 || x < 0 || x >= 256 || y < 0 || y >= 256) return;
	if (m_city.size() < (size_t)8 * 256 * 256) return;
	m_city[(size_t)z * 65536 + (size_t)y * 256 + (size_t)x] = b;
	m_cityDirty = true;
	buildTopViewFromCity();
}

// ---------------------------------------------------------------------------
// Кодирование m_city в сжатую карту (DMAP: 32-битные слова, CMAP: 16-битные).
// Формат — зеркально декодеру.
//   base[256][256] -> смещение колонки (в словах)
//   column:  (UInt8 height, UInt8 offset, UInt16 pad) + blockd[height-offset]
//   block[]: 12-байтные block_info; индекс 0 = пустой блок.
// Порядок колонок произвольный; одинаковые колонки совмещаются.
// Возвращает false, если колонки/блоки не влезают в разрядность счётчиков.
// ---------------------------------------------------------------------------
bool GmpFile::encodeCompressedMap(bool isDmap, std::vector<unsigned char>& out,
                                  size_t* colWords, size_t* numBlocks) const
{
	const size_t WS  = isDmap ? 4 : 2;
	const uint32_t WMAX = isDmap ? 0xFFFFFFFFu : 0xFFFFu;

	if (m_city.size() < (size_t)8 * 256 * 256) return false;

	auto putWord = [&](std::vector<unsigned char>& v, uint64_t x) {
		if (WS == 4) wr32(v, (uint32_t)x);
		else wr16(v, (uint16_t)x);
	};

	// ---- Таблица блоков: индекс 0 = пустой блок, далее уникальные ----
	std::map<std::string, int> bmap;
	std::vector<BlockInfo> blocks;
	blocks.push_back(BlockInfo());
	auto blockIndex = [&](const BlockInfo& b) -> int {
		if (isEmptyBlock(b)) return 0;
		std::vector<unsigned char> key = b.Encode();
		std::string k(key.begin(), key.end());
		std::map<std::string, int>::iterator it = bmap.find(k);
		if (it != bmap.end()) return it->second;
		int id = (int)blocks.size();
		if (WS == 2 && id > 0xFFFE) return -1;         // не влезает в 16 бит
		bmap[k] = id;
		blocks.push_back(b);
		return id;
	};

	// ---- Колонки: одинаковые (o,h, блоки) совмещаем ----
	std::map<std::string, size_t> cmap;        // сериализованная колонка -> offset (слова)
	std::vector<unsigned char> columnBytes;    // вся область column
	size_t totalColWords = 0;
	std::vector<uint32_t> base;
	base.resize((size_t)256 * 256);

	for (size_t y = 0; y < 256; y++) {
		for (size_t x = 0; x < 256; x++) {
			// Диапазон непустых уровней: [o, h).
			int o = 8, h = 0;
			for (int z = 0; z < 8; z++) {
				if (!isEmptyBlock(m_city[(size_t)z * 65536 + y * 256 + x])) {
					if (z < o) o = z;
					if (z + 1 > h) h = z + 1;
				}
			}
			if (h == 0) o = 0; // пустая клетка: пустая колонка (0,0)

			std::vector<unsigned char> col;
			std::vector<unsigned char> header;
			putWord(header, (uint64_t)((unsigned)h | ((unsigned)o << 8)));
			col.insert(col.end(), header.begin(), header.end());
			std::vector<uint32_t> idxs;
			for (int z = o; z < h; z++) {
				int bi = blockIndex(m_city[(size_t)z * 65536 + y * 256 + x]);
				if (bi < 0) return false;               // индекс блока > 16 бит
				idxs.push_back((uint32_t)bi);
			}
			for (size_t i = 0; i < idxs.size(); i++) {
				std::vector<unsigned char> w;
				putWord(w, idxs[i]);
				col.insert(col.end(), w.begin(), w.end());
			}

			std::string k(col.begin(), col.end());
			std::map<std::string, size_t>::iterator it = cmap.find(k);
			size_t off;
			if (it != cmap.end()) {
				off = it->second;
			} else {
				// Новый колонка: слово [height,offset] + height-offset слов блоков.
				size_t words = 1 + (h - o);
				if (totalColWords + words > WMAX) return false;
				off = totalColWords;
				cmap[k] = off;
				totalColWords += words;
				columnBytes.insert(columnBytes.end(), col.begin(), col.end());
			}
			base[y * 256 + x] = (uint32_t)off;
		}
	}

	size_t blockCount = blocks.size();
	if (isDmap) {
		if (blockCount > 0xFFFFFFFFu) return false;
	} else {
		if (blockCount > 0x10000u) return false;   // счётчик uint16: макс 0xFFFF
		if (totalColWords > 0xFFFFu) return false;
	}

	// ---- Сборка ----
	out.clear();
	out.reserve((size_t)256 * 256 * WS + totalColWords * WS + blockCount * 12);
	for (size_t i = 0; i < base.size(); i++) putWord(out, base[i]);
	putWord(out, totalColWords);
	out.insert(out.end(), columnBytes.begin(), columnBytes.end());
	putWord(out, blockCount);
	for (size_t i = 0; i < blocks.size(); i++) {
		std::vector<unsigned char> e = blocks[i].Encode();
		out.insert(out.end(), e.begin(), e.end());
	}
	if (colWords) *colWords = totalColWords;
	if (numBlocks) *numBlocks = blockCount;
	return true;
}

// ---------------------------------------------------------------------------
// Статистика сжатия: вызывает кодер для обеих разрядностей и возвращает
// занятость областей column и число уникальных блоков.
// ---------------------------------------------------------------------------
GmpFile::CompressionStats GmpFile::ComputeCompressionStats() const
{
	CompressionStats s;
	if (m_city.size() < (size_t)8 * 256 * 256) return s;
	s.hasCity = true;
	std::vector<unsigned char> tmp;
	s.dmapFits = encodeCompressedMap(true,  tmp, &s.dmapColWords, &s.dmapBlocks);
	s.cmapFits = encodeCompressedMap(false, tmp, &s.cmapColWords, &s.cmapBlocks);
	return s;
}

// ---------------------------------------------------------------------------
// "Вид сверху": первый (z=7..0) непустой блок каждой клетки.
// ---------------------------------------------------------------------------
void GmpFile::buildTopViewFromCity()
{
	if (m_city.size() < (size_t)8 * 256 * 256) return;
	m_umap.assign((size_t)256 * 256, BlockInfo());
	for (size_t y = 0; y < 256; y++) {
		for (size_t x = 0; x < 256; x++) {
			const BlockInfo* pick = 0;
			for (int z = 7; z >= 0; z--) {
				const BlockInfo& b = m_city[(size_t)z * 256 * 256 + (size_t)y * 256 + x];
				if (b.left || b.right || b.top || b.bottom || b.lid || b.arrows) {
					pick = &b;
					break;
				}
			}
			if (pick)
				m_umap[(size_t)y * 256 + x] = *pick;
		}
	}
}

const BlockInfo& GmpFile::Block(int z, int x, int y) const
{
	static const BlockInfo empty;
	if (z < 0 || z > 7 || x < 0 || x > 255 || y < 0 || y > 255) return empty;
	if (m_city.size() < (size_t)8 * 256 * 256) return empty;
	return m_city[(size_t)z * 256 * 256 + (size_t)y * 256 + x];
}

void GmpFile::buildUMAP(std::vector<unsigned char>& out) const
{
	// Полная карта (8 слоёв, как в документе: block_info city_scape[8][256][256]).
	if (m_city.size() >= (size_t)8 * 256 * 256) {
		for (size_t i = 0; i < m_city.size(); i++) {
			std::vector<unsigned char> e = m_city[i].Encode();
			out.insert(out.end(), e.begin(), e.end());
		}
		return;
	}
	// Старый путь (нет распакованной карты) — один слой.
	for (size_t i = 0; i < m_umap.size(); i++) {
		std::vector<unsigned char> e = m_umap[i].Encode();
		out.insert(out.end(), e.begin(), e.end());
	}
}

// ---------------------------------------------------------------------------
// ZONE: записи Tmap_zone (переменной длины) — см. ZoneInfo.h.
// ---------------------------------------------------------------------------
void GmpFile::parseZones(const unsigned char* d, size_t n)
{
	size_t p = 0;
	while (p + 6 <= n) {
		ZoneInfo z;
		z.zone_type = d[p + 0];
		z.x = d[p + 1];
		z.y = d[p + 2];
		z.w = d[p + 3];
		z.h = d[p + 4];
		unsigned int nl = d[p + 5];
		size_t recEnd = p + 6 + nl;
		if (recEnd > n) break;
		z.name.assign(reinterpret_cast<const char*>(d + p + 6), nl);
		m_zones.push_back(z);
		p = recEnd;
	}
}

void GmpFile::buildZones(std::vector<unsigned char>& out) const
{
	for (size_t i = 0; i < m_zones.size(); i++) {
		std::vector<unsigned char> e = m_zones[i].Encode();
		out.insert(out.end(), e.begin(), e.end());
	}
}

// ---------------------------------------------------------------------------
// MOBJ: объекты карты (Tmap_object, 6 байт).
// ---------------------------------------------------------------------------
void GmpFile::parseMobj(const unsigned char* d, size_t n)
{
	const size_t rec = 6;
	size_t cnt = n / rec;
	for (size_t i = 0; i < cnt; i++) {
		const unsigned char* p = d + i * rec;
		MapObject o;
		o.x        = rd16(p + 0);
		o.y        = rd16(p + 2);
		o.rotation = p[4];
		o.type     = p[5];
		m_objects.push_back(o);
	}
}

// ---------------------------------------------------------------------------
// LGHT: источники света (Tmap_light, 16 байт).
// ---------------------------------------------------------------------------
void GmpFile::parseLght(const unsigned char* d, size_t n)
{
	const size_t rec = 16;
	size_t cnt = n / rec;
	for (size_t i = 0; i < cnt; i++) {
		const unsigned char* p = d + i * rec;
		MapLight l;
		l.a = p[0]; l.r = p[1]; l.g = p[2]; l.b = p[3];
		l.x = rd16(p + 4);
		l.y = rd16(p + 6);
		l.z = rd16(p + 8);
		l.radius = rd16(p + 10);
		l.intensity = p[12];
		l.shape     = p[13];
		l.on_time   = p[14];
		l.off_time  = p[15];
		m_lights.push_back(l);
	}
}

// ---------------------------------------------------------------------------
// RGEN: дорожная сеть.
//   Дисковый формат:
//     545 junction'ов по 16 байт = 8720 байт
//     545 горизонтальных сегментов по 8 байт = 4360 байт
//     545 вертикальных сегментов по 8 байт = 4360 байт
//     num_junctions, num_h, num_v: uint16
//   Итого 17446 байт (как в bil/ste/wil.gmp).
// ---------------------------------------------------------------------------
void GmpFile::parseRgen(const unsigned char* d, size_t n)
{
	// Юнкции.
	const size_t juncRec = 16;
	size_t juncCnt = n >= juncRec ? (size_t)((n - 6) / juncRec) : 0;
	if (juncCnt > 545) juncCnt = 545;
	m_junctions.resize(juncCnt);
	for (size_t i = 0; i < juncCnt; i++) {
		const unsigned char* p = d + i * juncRec;
		Junction& j = m_junctions[i];
		j.north = rd16(p + 0);
		j.south = rd16(p + 2);
		j.west  = rd16(p + 4);
		j.east  = rd16(p + 6);
		j.search_type = p[8];
		j.junc_type   = p[9];
		j.field_A = rd16(p + 10);
		j.min_x = p[12];
		j.min_y = p[13];
		j.max_x = p[14];
		j.max_y = p[15];
	}

	// Сегменты (8 байт).
	const size_t segRec = 8;
	size_t hOff = juncCnt * juncRec;
	size_t vOff = hOff + 545 * segRec;
	const size_t maxSeg = 545;
	size_t hCnt = 0, vCnt = 0;
	for (size_t i = 0; i < maxSeg; i++) {
		size_t off = hOff + i * segRec;
		if (off + segRec + 545 * segRec + 6 > n) break;
		Segment s;
		s.junction1 = rd16(d + off);
		s.junction2 = rd16(d + off + 2);
		s.min_x = d[off + 4]; s.min_y = d[off + 5];
		s.max_x = d[off + 6]; s.max_y = d[off + 7];
		m_hSegments.push_back(s);
		hCnt++;
	}
	for (size_t i = 0; i < maxSeg; i++) {
		size_t off = vOff + i * segRec;
		if (off + segRec + 6 > n) break;
		Segment s;
		s.junction1 = rd16(d + off);
		s.junction2 = rd16(d + off + 2);
		s.min_x = d[off + 4]; s.min_y = d[off + 5];
		s.max_x = d[off + 6]; s.max_y = d[off + 7];
		m_vSegments.push_back(s);
		vCnt++;
	}

	// Счётчики в конце.
	size_t cntOff = n >= 6 ? n - 6 : 0;
	m_numJunctions = rd16(d + cntOff + 0);
	m_numH         = rd16(d + cntOff + 2);
	m_numV         = rd16(d + cntOff + 4);
}

void GmpFile::buildRgen(std::vector<unsigned char>& out) const
{
	// Юнкции (записываем все сохранённые, дополняя до 545).
	const size_t juncRec = 16;
	const size_t maxJ = 545;
	for (size_t i = 0; i < maxJ; i++) {
		unsigned char rec[16] = { 0 };
		if (i < m_junctions.size()) {
			const Junction& j = m_junctions[i];
			wr16_at(rec + 0, j.north);
			wr16_at(rec + 2, j.south);
			wr16_at(rec + 4, j.west);
			wr16_at(rec + 6, j.east);
			rec[8]  = j.search_type;
			rec[9]  = j.junc_type;
			wr16_at(rec + 10, j.field_A);
			rec[12] = j.min_x;
			rec[13] = j.min_y;
			rec[14] = j.max_x;
			rec[15] = j.max_y;
		}
		out.insert(out.end(), rec, rec + 16);
	}
	// Сегменты (всегда по 545 каждого типа, как в игре).
	const size_t segRec = 8;
	const size_t maxSeg = 545;
	for (size_t i = 0; i < maxSeg; i++) {
		unsigned char rec[8];
		if (i < m_hSegments.size()) {
			rec[0] = (unsigned char)(m_hSegments[i].junction1 & 0xFF);
			rec[1] = (unsigned char)(m_hSegments[i].junction1 >> 8);
			rec[2] = (unsigned char)(m_hSegments[i].junction2 & 0xFF);
			rec[3] = (unsigned char)(m_hSegments[i].junction2 >> 8);
			rec[4] = m_hSegments[i].min_x; rec[5] = m_hSegments[i].min_y;
			rec[6] = m_hSegments[i].max_x; rec[7] = m_hSegments[i].max_y;
		} else {
			std::memset(rec, 0, 8);
		}
		out.insert(out.end(), rec, rec + 8);
	}
	for (size_t i = 0; i < maxSeg; i++) {
		unsigned char rec[8];
		if (i < m_vSegments.size()) {
			rec[0] = (unsigned char)(m_vSegments[i].junction1 & 0xFF);
			rec[1] = (unsigned char)(m_vSegments[i].junction1 >> 8);
			rec[2] = (unsigned char)(m_vSegments[i].junction2 & 0xFF);
			rec[3] = (unsigned char)(m_vSegments[i].junction2 >> 8);
			rec[4] = m_vSegments[i].min_x; rec[5] = m_vSegments[i].min_y;
			rec[6] = m_vSegments[i].max_x; rec[7] = m_vSegments[i].max_y;
		} else {
			std::memset(rec, 0, 8);
		}
		out.insert(out.end(), rec, rec + 8);
	}
	// Счётчики.
	wr16(out, m_numJunctions);
	wr16(out, m_numH);
	wr16(out, m_numV);
}

// ---------------------------------------------------------------------------
// MOBJ: объекты карты (Tmap_object, 6 байт: x,y word; rotation; object_type).
// ---------------------------------------------------------------------------
void GmpFile::buildMobj(std::vector<unsigned char>& out) const
{
	for (size_t i = 0; i < m_objects.size(); i++) {
		const MapObject& o = m_objects[i];
		wr16(out, o.x);
		wr16(out, o.y);
		out.push_back(o.rotation);
		out.push_back(o.type);
	}
}

// ---------------------------------------------------------------------------
// LGHT: источники света (Tmap_light, 16 байт).
// ---------------------------------------------------------------------------
void GmpFile::buildLght(std::vector<unsigned char>& out) const
{
	for (size_t i = 0; i < m_lights.size(); i++) {
		const MapLight& l = m_lights[i];
		out.push_back(l.a); out.push_back(l.r); out.push_back(l.g); out.push_back(l.b);
		wr16(out, l.x); wr16(out, l.y); wr16(out, l.z);
		wr16(out, l.radius);
		out.push_back(l.intensity);
		out.push_back(l.shape);
		out.push_back(l.on_time);
		out.push_back(l.off_time);
	}
}

// ---------------------------------------------------------------------------
// Сериализация .gmp. Секции сохраняются в каноническом порядке;
// "сырые" (нередактируемые) секции переписаны без изменений.
// ---------------------------------------------------------------------------
std::vector<unsigned char> GmpFile::Save() const
{
	std::vector<unsigned char> out;
	const char magic[4] = { 'G', 'B', 'M', 'P' };
	out.insert(out.end(), magic, magic + 4);
	wr16(out, m_version);

	// Пересобираем редактируемые секции.
	std::vector<unsigned char> u, z, o, l, r;
	buildUMAP(u);
	buildZones(z);
	buildMobj(o);
	buildLght(l);
	buildRgen(r);

	// Если карта редактировалась — перекомпрессируем DMAP/CMAP из m_city.
	std::vector<unsigned char> dmapBlob, cmapBlob;
	bool dmapOk = false, cmapOk = false;
	if (m_cityDirty && !m_city.empty()) {
		dmapOk = encodeCompressedMap(true,  dmapBlob);
		cmapOk = encodeCompressedMap(false, cmapBlob);
	}

	// Проходим секции в исходном порядке; для редактируемых подставляем
	// пересобранные данные вместо маркеров, остальные пишем как есть.
	std::vector<std::string> written;
	for (size_t i = 0; i < m_raw.size(); i++) {
		const std::string& name = m_raw[i].first;
		if (name == "UMAP" && m_has[SEC_UMAP]) { writeSection(out, "UMAP", u); written.push_back("UMAP"); }
		else if (name == "ZONE" && m_has[SEC_ZONE]) { writeSection(out, "ZONE", z); written.push_back("ZONE"); }
		else if (name == "MOBJ" && m_has[SEC_MOBJ]) { writeSection(out, "MOBJ", o); written.push_back("MOBJ"); }
		else if (name == "LGHT" && m_has[SEC_LGHT]) { writeSection(out, "LGHT", l); written.push_back("LGHT"); }
		else if (name == "RGEN" && m_has[SEC_RGEN]) { writeSection(out, "RGEN", r); written.push_back("RGEN"); }
		else if (name == "DMAP") {
			if (m_cityDirty && dmapOk) writeSection(out, "DMAP", dmapBlob);
			else writeSection(out, name, m_raw[i].second);
		}
		else if (name == "CMAP") {
			// Отредактированная карта пишется заново; если 16-битная CMAP не
			// влезает — опускаем (ПК-игра читает DMAP, который в смежном блоке).
			if (m_cityDirty) {
				if (cmapOk) writeSection(out, "CMAP", cmapBlob);
				else if (dmapOk && !m_has[SEC_DMAP]) writeSection(out, "DMAP", dmapBlob);
			} else {
				writeSection(out, name, m_raw[i].second);
			}
		}
		else { writeSection(out, name, m_raw[i].second); }
	}

	// Если редактируемая секция создана заново (не было в исходном файле),
	// дописываем её в конец, чтобы новые зоны/объекты/света не терялись.
	const char* extra[5] = { "UMAP", "ZONE", "MOBJ", "LGHT", "RGEN" };
	const bool hasExtra[5] = { m_has[SEC_UMAP], m_has[SEC_ZONE], m_has[SEC_MOBJ], m_has[SEC_LGHT], m_has[SEC_RGEN] };
	const std::vector<unsigned char>* data[5] = { &u, &z, &o, &l, &r };
	for (int i = 0; i < 5; i++) {
		if (!hasExtra[i]) continue;
		bool found = false;
		for (size_t k = 0; k < written.size(); k++)
			if (written[k] == extra[i]) { found = true; break; }
		if (!found) writeSection(out, extra[i], *data[i]);
	}

	return out;
}

} // namespace gta2
