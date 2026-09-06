#ifndef __GTA2_TOOLS_ZONE_INFO_H_
#define __GTA2_TOOLS_ZONE_INFO_H_

#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// Зоны карты GTA2 из файла .gmp (секция ZONE).
// Формат подтверждён по исходникам SOFT/gta1-gta2-tool-source-code/GTA2/
// "zone editor"/Unit1.pas (Tmap_zone) и MapRelatedStruct из дампа.
//
// Структура файла .gmp:
//   "GBMP"                  (4 байта, сигнатура)
//   version: word           (2 байта, номер версии)
//   далее последовательность секций:
//     header: char[4]       (имя секции, напр. "ZONE", "UMAP", ...)
//     size:   uint32        (размер данных секции, без 8 байт заголовка)
//     data:   size байт
//   Секции: UMAP, CMAP, DMAP, ZONE, MOBJ, PSXM, ANIM, LGHT, RGEN (и THSR, EDIT).
//
// Секция ZONE содержит записи зон вида:
//   Tmap_zone (packed, переменной длины):
//     zone_type:   byte     (тип зоны: спавн/территория/путь и т.д.)
//     x, y:        byte     (верхний-левый угол, в клетках тайловой сетки)
//     w, h:        byte     (ширина и высота, размер зоны) [w включён в x+w]
//     name_length: byte     (длина имени зоны)
//     name:        char[name_length]  (имя зоны, без завершающего нуля)
//   Общий размер записи = 6 + name_length байт.
// ---------------------------------------------------------------------------

namespace gta2 {

// Запись зоны (соответствует Tmap_zone из zone editor).
struct ZoneInfo {
	unsigned char zone_type;   // тип зоны (0-255)
	unsigned char x;           // левый-верхний X (клетка)
	unsigned char y;           // левый-верхний Y (клетка)
	unsigned char w;           // ширина (клетки)
	unsigned char h;           // высота (клетки)
	std::string   name;        // имя зоны (до name_length байт)

	ZoneInfo() { Clear(); }

	void Clear() {
		zone_type = 0;
		x = y = 0;
		w = h = 0;
		name.clear();
	}

	// Кодирование записи в байты: 6 фикс. + name_length.
	std::vector<unsigned char> Encode() const;
};

// Список зон + доступ к прочим секциям .gmp (для сохранения с прежним порядком).
class ZoneFile {
public:
	ZoneFile() : m_ok(false) {}

	// Разбор бинарного .gmp (полный файл: GBMP + все секции).
	// Извлекает секцию ZONE в m_zones и сохраняет остальные секции
	// в их исходном виде, чтобы при сохранении не потерять данные.
	bool Parse(const unsigned char* data, size_t size);

	// Сериализация всего .gmp обратно в байты (GBMP + секции, ZONE новый).
	std::vector<unsigned char> Save() const;

	const std::vector<ZoneInfo>& Zones() const { return m_zones; }
	std::vector<ZoneInfo>&       Zones()       { return m_zones; }

	// Версия файла .gmp (прочитанная из заголовка).
	unsigned short Version() const { return m_version; }

	bool IsOk() const { return m_ok; }
	const std::string& Error() const { return m_error; }

private:
	std::vector<ZoneInfo> m_zones;
	// Копии прочих секций: (имя, data).
	std::vector<std::pair<std::string, std::vector<unsigned char>>> m_other;
	unsigned short m_version;
	bool m_ok;
	std::string m_error;
};

} // namespace gta2

#endif // !__GTA2_TOOLS_ZONE_INFO_H_
