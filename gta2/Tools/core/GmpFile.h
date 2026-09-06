#ifndef __GTA2_TOOLS_GMP_FILE_H_
#define __GTA2_TOOLS_GMP_FILE_H_

#include <string>
#include <vector>
#include <cstdint>

#include "ZoneInfo.h"

// ---------------------------------------------------------------------------
// Полный формат карт GTA2 (.gmp). Описан в
//   SOFT/gta2formats/"GTA2 Map Format.doc" (DMA Design, v8.2, Aug 1999)
// и подтверждён по исходникам SOFT/gta1-gta2-tool-source-code/GTA2/,
// а также по дампу игрового кода (MapRelatedStruct, JuncIds).
//
// Контейнер:
//   "GBMP"                (4 байта, сигнатура)
//   version: word         (2 байта, LE)
//   далее секции:
//     name: char[4]       (имя секции: UMAP/DMAP/CMAP/ZONE/MOBJ/PSXM/ANIM/LGHT/RGEN...)
//     size: uint32 LE     (размер данных секции БЕЗ 8 байт заголовка)
//     data: size байт
//
// Секции (подробности — комментарии к структурам ниже):
//   UMAP — несжатая карта 256*256 блоков (Tblock_info, 12 байт)
//   DMAP — сжатая карта ПК (32-битные слова)
//   CMAP — сжатая карта PS2 (16-битные слова)
//   ZONE — зоны (Tmap_zone), см. ZoneInfo.h
//   MOBJ — объекты карты (Tmap_object, 6 байт)
//   PSXM — таблица соответствия тайлов PSX (1024 записи по 2 байта)
//   ANIM — анимации тайлов
//   LGHT — источники света (Tmap_light, 16 байт)
//   RGEN — дорожная сеть (junction'ы и сегменты)
//   EDIT — редакторские данные
// ---------------------------------------------------------------------------

namespace gta2 {

// ---------------------------------------------------------------------------
// Блок карты (Tblock_info, 12 байт). Одна запись тайловой сетки 256x256.
// ---------------------------------------------------------------------------
struct BlockInfo {
	uint16_t left;     // биты 0..3 = типа стены, бит 4 = facing, ...
	uint16_t right;
	uint16_t top;
	uint16_t bottom;
	uint16_t lid;      // "крышка" блока
	uint8_t  arrows;   // стрелки одностороннего движения
	uint8_t  slope;    // тип уклона

	BlockInfo() { Clear(); }
	void Clear() {
		left = right = top = bottom = lid = 0;
		arrows = slope = 0;
	}
	// Кодирование в 12 байт LE.
	std::vector<unsigned char> Encode() const;
};

// ---------------------------------------------------------------------------
// Объект карты (Tmap_object, 6 байт).
// ---------------------------------------------------------------------------
struct MapObject {
	uint16_t x, y;        // пиксельные координаты
	uint8_t  rotation;    // 0..7 (направление)
	uint8_t  type;        // тип объекта (см. gmp_records.pas: TObject_type)

	MapObject() { x = y = 0; rotation = type = 0; }
};

// ---------------------------------------------------------------------------
// Источник света (Tmap_light, 16 байт).
// ---------------------------------------------------------------------------
struct MapLight {
	uint8_t  a, r, g, b;  // альфа/цвет
	uint16_t x, y, z;     // позиция
	uint16_t radius;
	uint8_t  intensity;
	uint8_t  shape;
	uint8_t  on_time;
	uint8_t  off_time;

	MapLight() { a = r = g = b = 0; x = y = z = 0; radius = 0; intensity = shape = on_time = off_time = 0; }
};

// ---------------------------------------------------------------------------
// Узел дорожной сети (junction). На диске 16 байт (секция RGEN).
// Точная раскладка — по официальному документу "GTA2 Map Format.doc"
// (раздел "Junction List") и данным bil/ste/wil.gmp:
//   struct { link north; link south; link east; link west;
//            search_type junc_type; UInt8 min_x; UInt8 min_y;
//            UInt8 max_x; UInt8 max_y; } junction
//   north/south/east/west — связи с соседними узлами; в памяти link=4 байта,
//   на диске сжаты до 16 бит (нижние 9 = индекс узла, старшие = длина дороги).
//   search_type — какие стрелки/направления у этого узла (на диске байт 0x8).
//   junc_type   — тип узла (на диске байт 0x9).
//   (min_x,min_y)-(max_x,max_y) — прямоугольник, занимаемый узлом.
// Note: юнкция 0 — пустая/заглушка (забита нулями).
// ---------------------------------------------------------------------------
struct Junction {
	uint16_t north;       // 0x0 — связь на север (нижние 9 бит = индекс узла)
	uint16_t south;       // 0x2
	uint16_t west;        // 0x4
	uint16_t east;        // 0x6
	uint8_t  search_type; // 0x8 — тип стрелок узла
	uint8_t  junc_type;   // 0x9 — тип узла
	uint16_t field_A;     // 0xA — резерв (всегда 0)
	uint8_t  min_x;       // 0xC — верхний-левый угол прямоугольника узла
	uint8_t  min_y;       // 0xD
	uint8_t  max_x;       // 0xE — нижний-правый угол
	uint8_t  max_y;       // 0xF

	Junction() { north = south = west = east = 0; search_type = junc_type = 0; field_A = 0; min_x = min_y = max_x = max_y = 0; }

	// Индекс соседней юнкции (нижние 9 бит связи).
	uint16_t northIndex() const { return north & 0x1FF; }
	uint16_t southIndex() const { return south & 0x1FF; }
	uint16_t westIndex()  const { return west  & 0x1FF; }
	uint16_t eastIndex()  const { return east  & 0x1FF; }
};

// ---------------------------------------------------------------------------
// Сегмент дорожной сети. На диске 8 байт. Подтверждён данными: H-сегменты
// (горизонтальные, y ~ const) и V-сегменты (вертикальные, x ~ const) каждый
// описывают дорогу между двумя юнкциями и её ограничивающий прямоугольник.
//   545 записей по 8 байт = 4360 байт (по горизонтальным и вертикальным).
// ---------------------------------------------------------------------------
struct Segment {
	uint16_t junction1;              // 0x0 — индекс первой юнкции (Tsegment: junction_num1)
	uint16_t junction2;              // 0x2 — индекс второй юнкции (junction_num2)
	uint8_t  min_x, min_y, max_x, max_y;  // 0x4..0x7 — ограничивающий прямоугольник ребра

	Segment() { junction1 = junction2 = 0; min_x = min_y = max_x = max_y = 0; }
};

// ---------------------------------------------------------------------------
// Полный .gmp со всеми секциями.
// ---------------------------------------------------------------------------
class GmpFile {
public:
	enum Section {
		SEC_UMAP = 0,
		SEC_DMAP,
		SEC_CMAP,
		SEC_ZONE,
		SEC_MOBJ,
		SEC_PSXM,
		SEC_ANIM,
		SEC_LGHT,
		SEC_RGEN,
		SEC_EDIT,
		SEC_COUNT
	};

	GmpFile();

	// Разбор полного файла .gmp.
	bool Parse(const unsigned char* data, size_t size);

	// Сериализация обратно (побайтовый раунд-трип).
	std::vector<unsigned char> Save() const;

	// Доступ к секциям.
	const std::vector<ZoneInfo>&    Zones()    const { return m_zones; }
	std::vector<ZoneInfo>&          Zones()          { return m_zones; }
	const std::vector<MapObject>&   Objects()  const { return m_objects; }
	std::vector<MapObject>&         Objects()        { return m_objects; }
	const std::vector<MapLight>&    Lights()   const { return m_lights; }
	std::vector<MapLight>&          Lights()         { return m_lights; }
	const std::vector<Segment>&     HSegments() const { return m_hSegments; }
	const std::vector<Segment>&     VSegments() const { return m_vSegments; }
	const std::vector<Junction>&    Junctions() const { return m_junctions; }
	std::vector<Junction>&          Junctions()       { return m_junctions; }

	// Счётчики секций RGEN (фактическое число узлов/сегментов).
	uint16_t NumJunctions() const { return m_numJunctions; }
	uint16_t NumHSegments() const { return m_numH; }
	uint16_t NumVSegments() const { return m_numV; }

	// Признаки наличия секций.
	bool HasSection(Section s) const { return m_has[s]; }

	unsigned short Version() const { return m_version; }
	bool IsOk() const { return m_ok; }
	const std::string& Error() const { return m_error; }

	// Несжатая карта (UMAP): 256*256 BlockInfo.
	const std::vector<BlockInfo>&  TileMap() const { return m_umap; }
	std::vector<BlockInfo>&        TileMap()       { return m_umap; }
	// true, если UMAP был прочитан (несжатая карта).
	bool HasTileMap() const { return !m_umap.empty(); }

	// -----------------------------------------------------------------------
	// Полная (8-слойная) карта города. Заполняется из UMAP, либо декодером
	// сжатых карт DMAP/CMAP (см. parseDMAP/parseCMAP). Плоское представление:
	//   index = z*256*256 + y*256 + x   (z = 0..7).
	// -----------------------------------------------------------------------
	const std::vector<BlockInfo>&  City() const { return m_city; }
	bool HasCity() const { return !m_city.empty(); }
	// Блок на уровне z в координатах (x,y). Если карта отсутствует или
	// координаты за пределами 0..255 — возвращается пустой (все нули) блок.
	const BlockInfo& Block(int z, int x, int y) const;
	// Запись блока (правка тайла). Координаты вне диапазона игнорируются;
	// после записи пересобирается «верхний» вид и карта помечается изменённой.
	void SetBlock(int z, int x, int y, const BlockInfo& b);
	// Помечает карту изменённой вручную (вызов Save() перекомпрессирует DMAP/CMAP).
	void MarkCityDirty() { m_cityDirty = true; }

	// -----------------------------------------------------------------------
	// Статистика сжатия для полосы занятости памяти (порт городов на PSX/PS2).
	// Лимиты: DMAP (ПК)  — 0xFFFFFFFF слов и 0x1000000 блоков (недостижимы);
	//         CMAP (PSX) — 0xFFFF слов и 0xFFFF блоков в области column.
	// -----------------------------------------------------------------------
	struct CompressionStats {
		size_t dmapColWords, dmapBlocks;   // DMAP: words в column / блоков в таблице
		size_t cmapColWords, cmapBlocks;   // CMAP: то же для 16-битного представления
		bool   hasCity;                    // карта загружена/доступна
		bool   dmapFits, cmapFits;         // помещается ли в формат
		CompressionStats() : dmapColWords(0), dmapBlocks(0),
		                    cmapColWords(0), cmapBlocks(0),
		                    hasCity(false), dmapFits(false), cmapFits(false) {}
	};
	// Пересчитывает статистику заново (вызывает кодер для DMAP и CMAP).
	CompressionStats ComputeCompressionStats() const;

private:
	bool parseSection(const unsigned char* data, size_t size, size_t pos,
	                  const char* name, size_t secSize);

	void parseUMAP(const unsigned char* d, size_t n);
	void parseDMAP(const unsigned char* d, size_t n);
	void parseCMAP(const unsigned char* d, size_t n);
	void parseZones(const unsigned char* d, size_t n);
	void parseMobj(const unsigned char* d, size_t n);
	void parsePsxm(const unsigned char* d, size_t n);
	void parseAnim(const unsigned char* d, size_t n);
	void parseLght(const unsigned char* d, size_t n);
	void parseRgen(const unsigned char* d, size_t n);

	void buildUMAP(std::vector<unsigned char>& out) const;
	void buildZones(std::vector<unsigned char>& out) const;
	void buildMobj(std::vector<unsigned char>& out) const;
	void buildLght(std::vector<unsigned char>& out) const;
	void buildRgen(std::vector<unsigned char>& out) const;

	// Заполняет m_umap (видимый "верхний" слой) из m_city: для каждой клетки
	// берётся самый верхний блок (z=7..0) с любым ненулевым полем.
	void buildTopViewFromCity();

	// Декодирование сжатой карты (DMAP/CMAP) в m_city. ws = 4 (DMAP) или 2 (CMAP).
	void decodeCompressedMap(const unsigned char* d, size_t n, bool isDmap);
	// Кодирование m_city в сжатую карту (DMAP/CMAP). Возвращает false, если
	// счётчики не влезают в разрядность (актуально для 16-битной CMAP).
	// Опционально возвращает число слов в области column и число уникальных
	// блоков (для полосы занятости памяти).
	bool encodeCompressedMap(bool isDmap, std::vector<unsigned char>& out,
	                         size_t* colWords = 0, size_t* numBlocks = 0) const;

	// Сохранение "сырых" секций, которые не редактируются (для раунд-трипа).
	std::vector<std::pair<std::string, std::vector<unsigned char>>> m_raw;

	std::vector<ZoneInfo>  m_zones;
	std::vector<MapObject> m_objects;
	std::vector<MapLight>  m_lights;
	std::vector<Segment>   m_hSegments;
	std::vector<Segment>   m_vSegments;
	std::vector<Junction>  m_junctions;
	std::vector<BlockInfo> m_umap;   // "верхний" (видимый) слой 256x256
	std::vector<BlockInfo> m_city;   // полная карта z*65536 + y*256 + x
	bool m_cityDirty;                // карта редактировалась (нужна перекомпрессия DMAP/CMAP)

	uint16_t m_numJunctions;
	uint16_t m_numH;
	uint16_t m_numV;

	bool m_has[SEC_COUNT];
	unsigned short m_version;
	bool m_ok;
	std::string m_error;
};

} // namespace gta2

#endif // !__GTA2_TOOLS_GMP_FILE_H_
