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
//   word  word0       — базовый uid таблицы смещений (bil=1129, …).
//                        В игре сохраняется в BaseScriptMaxPointers[scriptNum];
//                        это uid первой строки скрипта.
//   word  word1       — своя для каждой миссии; игра кладёт в arr_15[scriptNum]
//   dword dataLen     — размер области скрипт-данных (MissionScriptSize[n])
//   byte  objective[3072]  — «данные миссии»; в игре копируются в
//                            arr_23808[768*n] (0xC00 байт).
//                            Начало блока — таблица u16-смещений строк:
//                            objective[(uid - word0) * 2] = смещение строки
//                            внутри MAIN_BUFFER (0x6218…); 0 = строки нет.
//   byte  data[dataLen]    — скомпилированный скрипт: строки переменной длины.
//
// Размер файла == 8 + 3072 + dataLen (для всех 67 миссий совпадает точно).
// Конец последней строки данных == dataLen: Σ длин строк == dataLen.
// Именно через таблицу objective интерпретатор находит строку по uid:
// MissionManager_StartMission = MAIN_BUFFER + u16[OBJECTIVE_DATA_SIZE + uid*2].
// Смещения в objective абсолютные (MAIN_BUFFER > 0x6000); относительное
// смещение в Data() = значение − значение первого ненулевого индекса.
//
// Городские скрипты bin/data/*.scr (82656 байт каждый) этому контейнеру НЕ
// соответствуют (одноразмерные заглушки с другой раскладкой) — Parse() их
// отвергает, а Save() вернёт исходные байты без изменений.
// ---------------------------------------------------------------------------

namespace gta2 {

// Строка скрипт-данных миссии. Начало каждой строки — заголовок:
//   u16 uid      — идентификатор строки (совпадает с индексом таблицы)
//   u16 type     — opcode (0x29..0x1BE исполняет диспетчер; < 0x29 — спецкоды)
//   u16 nextUid  — uid следующей строки при chain==1 (переход; иначе uid+1)
//   u16 chain    — 1 => команда продолжается на nextUid (цепочка/переход);
//                  интерпретатор ProcessMissionLine циклит, пока u16+6 == 1
//   u8  params[] — остаток строки длиной size-8.
// Размер строки определяется разностью соседних ненулевых u16 таблицы
// objective (последней — до конца Data()) — см. Lines().
struct ScriptLine {
	uint32_t offset; // смещение строки от начала Data()
	uint16_t uid;    // слово 0 (идентификатор строки)
	uint16_t type;   // слово 1 (opcode)
	uint16_t nextUid;// слово 2 (следующий uid при chain==1)
	uint16_t chain;  // слово 3 (1 => переход на nextUid)
	size_t   size;   // длина строки в байтах (из таблицы смещений)
	std::vector<unsigned char> params; // байты после 8-байтового заголовка
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

	uint16_t Word0() const { return m_word0; }  // базовый uid таблицы смещений
	uint16_t Word1() const { return m_word1; }  // собственный uid/поток миссии

	const std::vector<unsigned char>& Objective() const { return m_objective; }
	std::vector<unsigned char>&       Objective()       { return m_objective; }

	const std::vector<unsigned char>& Data() const { return m_data; }
	std::vector<unsigned char>&       Data()       { return m_data; }

	// Разбиение скрипт-данных на строки по таблице смещений objective
	// (см. ScriptLine). Строки переменной длины; Σ размеров == Data().size().
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