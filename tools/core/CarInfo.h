#ifndef __GTA2_TOOLS_CAR_INFO_H_
#define __GTA2_TOOLS_CAR_INFO_H_

#include <vector>
#include <cstddef>

// ---------------------------------------------------------------------------
// Параметры машины из секции CARI файла .sty (стиль/графика).
// Формат подтверждён по битам bin/data/bil.sty (0x62E2B9) и исходникам
// SOFT/gta1-gta2-tool-source-code/GTA2/gta2 sty tool/filerecords.pas:27.
//
// Tcar_info packed record (переменной длины):
//   model/ sprite/ w/ h/ num_remaps/ passengers/ wreck/ rating: byte;
//   front_wheel_offset, rear_wheel_offset:   shortint;
//   front_window_offset, rear_window_offset: shortint;
//   info_flags, info_flags_2: byte;                  // 14 фикс. байт
//   remap[num_remaps]: byte;                          // [переменные]
//   num_doors: byte;                                  // 1 байт
//   door[num_doors]: { rx, ry: shortint };            // по 2 байта
// ---------------------------------------------------------------------------

namespace gta2 {

// Точка двери (смещение в пикселях относительно центра машины).
struct CarDoor {
	signed char rx; // после загрузки может быть < 0 (правая сторона)
	signed char ry;
};

struct CarInfo {
	unsigned char model;
	unsigned char sprite;
	unsigned char w;
	unsigned char h;
	unsigned char num_remaps;
	unsigned char passengers;
	unsigned char wreck;
	unsigned char rating;
	signed char front_wheel_offset;
	signed char rear_wheel_offset;
	signed char front_window_offset;
	signed char rear_window_offset;
	unsigned char info_flags;
	unsigned char info_flags_2;

	std::vector<unsigned char> remap; // индекс спрайтов перекраски (num_remaps шт.)
	unsigned char num_doors;
	std::vector<CarDoor> door;        // двери (num_doors шт.)

	CarInfo() { Clear(); }

	void Clear() {
		model = sprite = w = h = num_remaps = passengers = 0;
		wreck = rating = 0;
		front_wheel_offset = rear_wheel_offset = 0;
		front_window_offset = rear_window_offset = 0;
		info_flags = info_flags_2 = 0;
		remap.clear();
		num_doors = 0;
		door.clear();
	}

	// Сериализация одной записи в байты (без переменных частей).
	size_t FixedRecordSize() const { return 14; }
};

// Список машин из пакета CARI.
class CarInfoList {
public:
	CarInfoList() : m_ok(false) {}

	// Разбор бинарного пакета CARI (данные после заголовка секции).
	bool Parse(const unsigned char* data, size_t size);

	// Сериализация пакета CARI в байты (заголовок секции не включается).
	std::vector<unsigned char> Save() const;

	const std::vector<CarInfo>& Cars() const { return m_cars; }
	std::vector<CarInfo>&       Cars()       { return m_cars; }

	bool IsOk() const { return m_ok; }

private:
	std::vector<CarInfo> m_cars;
	bool m_ok;
};

// Раскодирование/кодирование флагов info_flags/info_flags_2 (16 бит) в биты.
// Бит 0..7  -> info_flags;  бит 8..15 -> info_flags_2 (мл. бит = проверка 8).
inline bool CarFlagBit(unsigned char flags, int bit) { return (flags & (1 << bit)) != 0; }
inline unsigned char SetCarFlagBit(unsigned char flags, int bit, bool on)
{
	return on ? (unsigned char)(flags | (1 << bit))
	          : (unsigned char)(flags & ~(1 << bit));
}

} // namespace gta2

#endif // !__GTA2_TOOLS_CAR_INFO_H_
