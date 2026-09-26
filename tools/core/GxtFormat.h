#ifndef __GTA2_TOOLS_GXT_FORMAT_H_
#define __GTA2_TOOLS_GXT_FORMAT_H_

#include <string>
#include <vector>
#include <cstddef>

// ---------------------------------------------------------------------------
// Формат текстов игры .gxt (подтверждён по байтам bin/data/e.gxt, f.gxt,
// g.gxt, i.gxt, s.gxt, bob_*.gxt):
//
//   0x00 "GBLE"                магик (4 байта)
//   0x04 word = 0x0064 (100)   версия формата
//   0x06 "TKEY"                имя первого блока
//   0x0A u32 ksz               размер данных блока TKEY в байтах
//   0x0E данные TKEY: n записей по 12 байт:
//          u32  off            смещение строки от начала данных TDAT
//          char key[8]         имя ключа (дополнено нулями)
//   0x0E+ksz "TDAT"            имя второго блока
//           u32 tdatSize       размер строковых данных
//           UTF-16LE строки с терминирующим 0x0000 (tdatSize байт)
//
// Ключи в файле отсортированы по возрастанию (по байтам), т.к. загрузчик
// игры, вероятно, ищет двоичным поиском. Записи всегда 12 байт: первое
// поле 0x0E заголовка внутри TKEY - это offset первой строки.
// ---------------------------------------------------------------------------

namespace gta2 {

struct GxtString {
	std::string key;      // 1..8 букв/цифр латиницей
	std::wstring text;    // текст строки (UTF-16)
};

class GxtFile {
public:
	GxtFile() : m_version(0x64), m_ok(false), m_dirty(true) {
		m_magic[0] = 'G'; m_magic[1] = 'B'; m_magic[2] = 'L'; m_magic[3] = 'E';
	}

	// Разбор файла. При успехе возвращает true, m_ok=true.
	bool Load(const unsigned char* data, size_t size);

	// Сборка .gxt в байты. Если файл не менялся (чистый load->save), то
	// сохраняются исходные смещения и порядок - файл выходит побайтово
	// идентичным оригиналу. После правок смещения пересчитываются плотно.
	std::vector<unsigned char> Save() const;

	const std::vector<GxtString>& Strings() const { return m_strings; }
	size_t Size() const { return m_strings.size(); }

	// Поиск по ключу (линейный, для редактора — объём небольшой).
	const GxtString* Find(const std::string& key) const;

	// Редактирование (помечает проект «изменён»).
	bool SetText(size_t index, const std::wstring& text);
	bool Add(const std::string& key, const std::wstring& text);
	bool Remove(size_t index);

	bool IsOk() const { return m_ok; }
	bool IsDirty() const { return m_dirty; }
	void ClearDirty() { m_dirty = false; }
	// Буква языка из магика (E/F/G/I/S).
	char Language() const { return (char)m_magic[3]; }

private:
	unsigned char m_magic[4]; // "GBL" + буква языка (E/F/G/I/S)
	unsigned short m_version; // слово версии из заголовка
	std::vector<GxtString> m_strings;
	// Исходные блоки TKEY/TDAT: при непустом файле и без правок Save()
	// записывает их дословно, гарантируя побайтовую идентичность.
	std::vector<unsigned char> m_keyBlob;
	std::vector<unsigned char> m_strBlob;
	bool m_ok;
	bool m_dirty;
};

} // namespace gta2

#endif // !__GTA2_TOOLS_GXT_FORMAT_H_