#ifndef __GTA2_TOOLS_STY_FORMAT_H_
#define __GTA2_TOOLS_STY_FORMAT_H_

#include <string>
#include <vector>
#include <cstddef>

// ---------------------------------------------------------------------------
// Формат файла стилей .sty (графика: тайлы, спрайты, палитры, машины).
// Подтверждён по битам bin/data/bil.sty и исходникам:
//   SOFT/gta2-file-editor/clsSTY.cls
//   SOFT/gta1-gta2-tool-source-code/GTA2/gta2 sty tool/Unit1.pas, filerecords.pas
//
// Заголовок:
//   0x00 "GBST"        магик (4 байта)
//   0x04 word = 0x02BC (700)  версия формата
//
// Далее идут секции:
//   "XXXX" (char name[4]) + u32 size + size байт данных.
//
// Известные секции (порядок в бил.стиле):
//   TILE  - тайлы (NumOfTiles * 4096 байт, по 64x64 индексов палитры)
//   PPAL  - физические палитры (NumOfPals * 1024, по 256x64 RGBA)
//   SPRB  - базы спрайтов (Tsprite_base, 12 байт: 6 word)
//   FONB  - базы шрифтов (word font_count + word base[])
//   DELX  - дельты, таблица смещений спрайтов-дельт
//   DELS  - дельты, данные
//   PALX  - индексы виртуальных палитр (word[] -> индекс в PPAL)
//   OBJI  - информация объектов (как есть)
//   RECY  - список перерабатываемых моделей (byte[])
//   SPRG  - растровые данные спрайтов (256-пиксельные строки)
//   SPRX  - таблица спрайтов (Tsprite_entry, по 8 байт)
//   PALB  - базы палитр (Tpalette_base, 16 байт: 8 word)
//   CARI  - параметры машин (CarInfoList)
//   SPEC  - поверхности тайлов (word[])
//
// Парсер хранит все секции как есть (имя + байты) и позволяет заменить
// любую секцию (например CARI) перед сохранением. Это гарантирует побайтовую
// идентичность файла при отсутствии правок.
// ---------------------------------------------------------------------------

namespace gta2 {

struct StySection {
	char name[4];
	std::vector<unsigned char> data;

	bool Is(const char* n) const {
		return name[0] == n[0] && name[1] == n[1] && name[2] == n[2] && name[3] == n[3];
	}
};

class StyFile {
public:
	StyFile();

	// Разбор .sty из байтов (полный файл, включая заголовок).
	bool Parse(const unsigned char* data, size_t size);

	// Сборка .sty в байты (заголовок + секции). Порядок и содержимое секций
	// сохраняются; бинарно идентично оригиналу, если ничего не редактировали.
	std::vector<unsigned char> Save() const;

	// Доступ к секциям.
	size_t SectionCount() const { return m_sections.size(); }
	const StySection* SectionAt(size_t index) const { return &m_sections[index]; }
	const StySection* FindSection(const char* name) const;
	StySection*       MutableSection(const char* name);

	// Заменить/добавить секцию. Если name уже есть - заменяет данные,
	// иначе добавляет в конец (для новых). Возвращает указатель на секцию.
	StySection* SetSection(const char* name, const std::vector<unsigned char>& data);

	bool IsOk() const { return m_ok; }
	unsigned short Version() const { return m_version; }
	void SetVersion(unsigned short v) { m_version = v; }

	// Помечает файл изменённым (нужно при SetSection при желании сохранить
	// порядок — здесь порядок не изменяется, только содержимое).
	void SetDirty() { m_ok = true; }

private:
	unsigned char m_magic[4];   // "GBST"
	unsigned short m_version;   // слово версии
	std::vector<StySection> m_sections;
	bool m_ok;
};

} // namespace gta2

#endif // !__GTA2_TOOLS_STY_FORMAT_H_
