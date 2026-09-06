#ifndef __GTA2_TOOLS_SCR_FORMAT_H_
#define __GTA2_TOOLS_SCR_FORMAT_H_

#include <cstdint>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// Миссийные скрипты GTA2 (.scr).
//
// Формат установлен по реальным файлам bin/data/{bil,ste,wil}/*.scr
// (67 миссий трёх регионов) и подтверждён игровым кодом
// (MissionManager::sub_476070 / часть загрузки миссии в gta2.exe):
//
//   word  word0       — константа региона (bil=1129, ste=1660, wil=1371);
//                        в игре сохраняется в BaseScriptMaxPointers[scriptNum]
//   word  word1       — своя для каждой миссии; игра кладёт в arr_15[scriptNum]
//   dword dataLen     — размер области скрипт-данных (MissionScriptSize[n])
//   byte  objective[3072]  — данные миссии (768 dword); в игре копируются в
//                            arr_23808[768*n] (0xC00 байт)
//   byte  data[dataLen]    — скомпилированный скрипт (команды/строки/записи)
//
// Размер файла == 8 + 3072 + dataLen (для всех 67 миссий совпадает точно).
// Скрипт-данные начинаются с таблицы 12-байтовых записей (поэтому
// partOfLoadScrip возвращает длину, кратную 12).
//
// Городские скрипты bin/data/*.scr (82656 байт каждый) этому контейнеру НЕ
// соответствуют (одноразмерные заглушки с другой раскладкой) — Parse() их
// отвергает, а Save() вернёт исходные байты без изменений.
// ---------------------------------------------------------------------------

namespace gta2 {

// Запись скрипт-данных миссии. Скрипт-данные (Data()) разбиваются на строго
// 12-байтовые записи (подтверждено по всем 67 миссиям: dataLen кратен 12,
// uid каждого ненулевого слова 0 лежит на границе записи). Запись может быть
// ячейкой логической строки, а не самой строкой: интерпретатор привязывает
// начало «строки» через таблицу u16-смещений OBJECTIVE_DATA_SIZE и допускает
// записи переменной длины, поэтому при параметрах длиннее слов p1..p4 далее
// следуют записи-продолжения.
struct ScriptLine {
	uint32_t offset; // смещение записи от начала Data()
	uint16_t uid;    // слово 0
	uint16_t type;   // слово 1 (opcode/тип строки)
	uint16_t p1;     // слово 2
	uint16_t p2;     // слово 3
	uint16_t p3;     // слово 4
	uint16_t p4;     // слово 5
};

class ScrFormat {
public:
	static const size_t kHeaderSize    = 8;
	static const size_t kObjectiveSize = 3072;

	ScrFormat();

	// Разбор .scr. Возвращает false, если контейнер не похож на миссийный
	// (тогда скрипт хранится как есть и доступен через Raw()).
	bool Parse(const unsigned char* data, size_t size);

	// Сериализация обратно (побайтовый раунд-трип).
	std::vector<unsigned char> Save() const;

	bool IsMission() const { return m_mission; }

	uint16_t Word0() const { return m_word0; }  // константа региона
	uint16_t Word1() const { return m_word1; }  // номер миссии/потока

	const std::vector<unsigned char>& Objective() const { return m_objective; }
	std::vector<unsigned char>&       Objective()       { return m_objective; }

	const std::vector<unsigned char>& Data() const { return m_data; }
	std::vector<unsigned char>&       Data()       { return m_data; }

	// Разбиение скрипт-данных на 12-байтовые записи (см. ScriptLine).
	std::vector<ScriptLine> Lines() const;

	// Сырые байты (для не-миссийных .scr, либо весь файл до Parse()).
	const std::vector<unsigned char>& Raw() const { return m_raw; }

	size_t DataSize() const { return m_data.size(); }
	bool IsOk() const { return m_ok; }
	const std::string& Error() const { return m_error; }

private:
	bool m_mission;
	uint16_t m_word0;
	uint16_t m_word1;
	std::vector<unsigned char> m_objective; // 3072 байта данных миссии
	std::vector<unsigned char> m_data;      // скомпилированный скрипт
	std::vector<unsigned char> m_raw;       // исходные байты файла
	bool m_ok;
	std::string m_error;
};

} // namespace gta2

#endif // !__GTA2_TOOLS_SCR_FORMAT_H_