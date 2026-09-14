// sdtool - конвертер звуковых банков GTA2 (.sdt + .raw) <-> .wav
//
// Формат банка игры (подтверждён анализом bin\data\audio оригинальной GTA2):
//   <имя>.sdt - таблица звуков: массив записей по 24 байта
//       offset(4) | size(4) | sampleRate(4) | loopStart(4) | loopEnd(4) | 0xFFFFFFFF(4)
//   <имя>.raw  - сами данные: 16-бит знаковый PCM моно, звуки подряд.
//   (В GTA1 в записи было ещё имя 8 байт и запись была 20 байт; в GTA2 имени нет.)
//
// Команды:
//   sdtool list   <bank>                 - список звуков банка
//   sdtool info   <bank>                 - общая информация о банке
//   sdtool export <bank> <index> <out.wav> - выгрузить звук в .wav (16-бит PCM моно)
//   sdtool import <bank> <index> <in.wav>  - заменить звук из .wav (16-бит PCM, стерео -> моно)
//   sdtool add    <bank> <in.wav>          - добавить звук в конец банка
//   sdtool play   <bank> <index>           - прослушать звук (waveOut)
//   sdtool exportall <bank> <dir>          - выгрузить все звуки в папку
//
// bank задаётся без расширения, например "ste" (будет искать ste.sdt/ste.raw
// в data\audio и bin\data\audio относительно текущего каталога).
//
// Замечание: при import/add .sdt и .raw пересобираются заново - все звуки
// записываются подряд, смещения пересчитываются (сохраняется порядок).

#include <windows.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#pragma warning(disable : 4996) // fopen и т.п.

// ---------------------------------------------------------------------------
// Запись .sdt
// ---------------------------------------------------------------------------
struct SdtEntry
{
	unsigned long offset;     // смещение звука в .raw
	unsigned long size;       // размер данных в байтах
	unsigned long sampleRate; // частота дискретизации
	unsigned long loopStart;  // начало цикла (в байтах), 0 = нет
	unsigned long loopEnd;    // конец цикла (в байтах), 0 = нет
	unsigned long reserved;   // всегда 0xFFFFFFFF
};

static const unsigned long kSdtEntrySize = 24;
static const unsigned long kSdtReserved  = 0xFFFFFFFF;

// ---------------------------------------------------------------------------
// Поиск файла банка в возможных папках данных
// ---------------------------------------------------------------------------
static bool FindBankFile(const char* bank, const char* ext, std::string& out)
{
	const char* dirs[] = {
		"data\\audio\\",
		"bin\\data\\audio\\",
		"..\\bin\\data\\audio\\",
		"C:\\work\\GTA2_RE\\bin\\data\\audio\\"
	};
	for (int i = 0; i < 4; i++) {
		std::string p = std::string(dirs[i]) + bank + ext;
		FILE* f = fopen(p.c_str(), "rb");
		if (f) {
			fclose(f);
			out = p;
			return true;
		}
	}
	return false;
}

// ---------------------------------------------------------------------------
// Чтение/запись файлов
// ---------------------------------------------------------------------------
static bool ReadFile(const char* path, std::vector<unsigned char>& out)
{
	FILE* f = fopen(path, "rb");
	if (!f) return false;
	fseek(f, 0, SEEK_END);
	long sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (sz < 0) { fclose(f); return false; }
	out.resize((size_t)sz);
	bool ok = sz == 0 || fread(&out[0], 1, (size_t)sz, f) == (size_t)sz;
	fclose(f);
	return ok;
}

static bool WriteFile(const char* path, const void* data, size_t size)
{
	FILE* f = fopen(path, "wb");
	if (!f) return false;
	bool ok = size == 0 || fwrite(data, 1, size, f) == size;
	fclose(f);
	return ok;
}

// ---------------------------------------------------------------------------
// Загрузка банка (sdt + raw), аккуратная проверка записей
// ---------------------------------------------------------------------------
static int LoadBank(const std::vector<unsigned char>& sdt,
                    const std::vector<unsigned char>& raw,
                    std::vector<SdtEntry>& entries)
{
	entries.clear();
	if (sdt.size() % kSdtEntrySize)
		return -1; // битый .sdt
	size_t n = sdt.size() / kSdtEntrySize;
	for (size_t i = 0; i < n; i++) {
		const unsigned char* e = &sdt[i * kSdtEntrySize];
		SdtEntry en;
		en.offset     = e[0] | (e[1] << 8) | (e[2] << 16) | ((unsigned long)e[3] << 24);
		en.size       = e[4] | (e[5] << 8) | (e[6] << 16) | ((unsigned long)e[7] << 24);
		en.sampleRate = e[8] | (e[9] << 8) | (e[10] << 16) | ((unsigned long)e[11] << 24);
		en.loopStart  = e[12] | (e[13] << 8) | (e[14] << 16) | ((unsigned long)e[15] << 24);
		en.loopEnd    = e[16] | (e[17] << 8) | (e[18] << 16) | ((unsigned long)e[19] << 24);
		en.reserved   = e[20] | (e[21] << 8) | (e[22] << 16) | ((unsigned long)e[23] << 24);
		if (en.offset > raw.size() || en.size < 4 ||
		    en.offset + en.size > raw.size() || en.sampleRate == 0) {
			// пропускаем битые, но сообщаем о них
			en.size = 0;
		}
		entries.push_back(en);
	}
	return (int)n;
}

// ---------------------------------------------------------------------------
// Запись .sdt по пересчитанным записям
// ---------------------------------------------------------------------------
static void SaveSdt(const std::vector<SdtEntry>& entries, std::vector<unsigned char>& out)
{
	out.resize(entries.size() * kSdtEntrySize);
	for (size_t i = 0; i < entries.size(); i++) {
		unsigned char* e = &out[i * kSdtEntrySize];
		const SdtEntry& en = entries[i];
		e[0]  = (unsigned char)(en.offset & 0xFF);
		e[1]  = (unsigned char)((en.offset >> 8) & 0xFF);
		e[2]  = (unsigned char)((en.offset >> 16) & 0xFF);
		e[3]  = (unsigned char)((en.offset >> 24) & 0xFF);
		e[4]  = (unsigned char)(en.size & 0xFF);
		e[5]  = (unsigned char)((en.size >> 8) & 0xFF);
		e[6]  = (unsigned char)((en.size >> 16) & 0xFF);
		e[7]  = (unsigned char)((en.size >> 24) & 0xFF);
		e[8]  = (unsigned char)(en.sampleRate & 0xFF);
		e[9]  = (unsigned char)((en.sampleRate >> 8) & 0xFF);
		e[10] = (unsigned char)((en.sampleRate >> 16) & 0xFF);
		e[11] = (unsigned char)((en.sampleRate >> 24) & 0xFF);
		e[12] = (unsigned char)(en.loopStart & 0xFF);
		e[13] = (unsigned char)((en.loopStart >> 8) & 0xFF);
		e[14] = (unsigned char)((en.loopStart >> 16) & 0xFF);
		e[15] = (unsigned char)((en.loopStart >> 24) & 0xFF);
		e[16] = (unsigned char)(en.loopEnd & 0xFF);
		e[17] = (unsigned char)((en.loopEnd >> 8) & 0xFF);
		e[18] = (unsigned char)((en.loopEnd >> 16) & 0xFF);
		e[19] = (unsigned char)((en.loopEnd >> 24) & 0xFF);
		e[20] = (unsigned char)(kSdtReserved & 0xFF);
		e[21] = (unsigned char)((kSdtReserved >> 8) & 0xFF);
		e[22] = (unsigned char)((kSdtReserved >> 16) & 0xFF);
		e[23] = (unsigned char)((kSdtReserved >> 24) & 0xFF);
	}
}

// ---------------------------------------------------------------------------
// Сборка .raw: все звуки подряд (порядок сохраняется, смещения пересчитываются)
// ---------------------------------------------------------------------------
static void RebuildRaw(const std::vector<SdtEntry>& entries,
                       const std::vector<std::vector<unsigned char> >& datas,
                       std::vector<unsigned char>& raw)
{
	raw.clear();
	for (size_t i = 0; i < entries.size(); i++) {
		raw.insert(raw.end(), datas[i].begin(), datas[i].end());
	}
}

// ---------------------------------------------------------------------------
// Чтение .wav -> PCM 16-бит моно + частота
// (поддерживаются 8/16 бит, моно/стерео; левый канал при стерео)
// ---------------------------------------------------------------------------
static bool ReadWavPcm(const char* path, std::vector<short>& pcm, int& rate)
{
	pcm.clear();
	rate = 0;

	FILE* f = fopen(path, "rb");
	if (!f) return false;
	fseek(f, 0, SEEK_END);
	long sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (sz < 44) { fclose(f); return false; }
	std::vector<unsigned char> d((size_t)sz);
	if (fread(&d[0], 1, (size_t)sz, f) != (size_t)sz) { fclose(f); return false; }
	fclose(f);

	if (d[0] != 'R' || d[1] != 'I' || d[2] != 'F' || d[3] != 'F' ||
	    d[8] != 'W' || d[9] != 'A' || d[10] != 'V' || d[11] != 'E')
		return false;

	long pos = 12;
	int  tag = 0, channels = 0, sampleRate = 0, bits = 0;
	long dataOff = -1, dataSize = 0;

	while (pos + 8 <= sz) {
		unsigned long id = (unsigned long)(d[pos] | (d[pos + 1] << 8) | (d[pos + 2] << 16) | ((unsigned int)d[pos + 3] << 24));
		long ckSize = (long)(d[pos + 4] | (d[pos + 5] << 8) | (d[pos + 6] << 16) | ((unsigned int)d[pos + 7] << 24));
		long body = pos + 8;
		if (id == 0x20746D66UL) { // "fmt "
			tag = (short)(d[body] | (d[body + 1] << 8));
			channels = (short)(d[body + 2] | (d[body + 3] << 8));
			sampleRate = (int)((unsigned int)(d[body + 4] | (d[body + 5] << 8) | (d[body + 6] << 16) | ((unsigned int)d[body + 7] << 24)));
			bits = (short)(d[body + 14] | (d[body + 15] << 8));
		} else if (id == 0x61746164UL) { // "data"
			dataOff = body;
			dataSize = ckSize;
		}
		pos = body + ckSize + (ckSize & 1);
	}
	if (dataOff < 0 || dataSize < 4)
		return false;
	if (tag != 0x0001) // только несжатый PCM
		return false;
	if (channels < 1 || channels > 2 || (bits != 8 && bits != 16))
		return false;

	rate = sampleRate;
	if (bits == 16) {
		for (long i = dataOff; i + 1 < dataOff + dataSize && i + 1 < sz; i += 2 * channels) {
			short s = (short)(d[i] | (d[i + 1] << 8));
			pcm.push_back(s);
		}
	} else { // 8-бит беззнаковый -> 16-бит знаковый
		for (long i = dataOff; i < dataOff + dataSize && i < sz; i += channels) {
			int s = (int)d[i] - 128;
			pcm.push_back((short)(s << 8));
		}
	}
	return !pcm.empty();
}

// ---------------------------------------------------------------------------
// Запись .wav из PCM 16-бит моно
// ---------------------------------------------------------------------------
static bool WriteWav(const char* path, const short* pcm, size_t count, int rate)
{
	unsigned char h[44];
	memset(h, 0, sizeof(h));
	h[0] = 'R'; h[1] = 'I'; h[2] = 'F'; h[3] = 'F';
	unsigned long riffSize = (unsigned long)(36 + count * 2);
	h[4] = (unsigned char)(riffSize & 0xFF);
	h[5] = (unsigned char)((riffSize >> 8) & 0xFF);
	h[6] = (unsigned char)((riffSize >> 16) & 0xFF);
	h[7] = (unsigned char)((riffSize >> 24) & 0xFF);
	h[8] = 'W'; h[9] = 'A'; h[10] = 'V'; h[11] = 'E';
	h[12] = 'f'; h[13] = 'm'; h[14] = 't'; h[15] = ' ';
	h[16] = 16; // Subchunk1Size
	h[20] = 1;  // AudioFormat = PCM
	h[22] = 1;  // NumChannels = моно
	h[24] = (unsigned char)(rate & 0xFF);
	h[25] = (unsigned char)((rate >> 8) & 0xFF);
	h[26] = (unsigned char)((rate >> 16) & 0xFF);
	h[27] = (unsigned char)((rate >> 24) & 0xFF);
	unsigned long byteRate = (unsigned long)rate * 2;
	h[28] = (unsigned char)(byteRate & 0xFF);
	h[29] = (unsigned char)((byteRate >> 8) & 0xFF);
	h[30] = (unsigned char)((byteRate >> 16) & 0xFF);
	h[31] = (unsigned char)((byteRate >> 24) & 0xFF);
	h[32] = 2;  // BlockAlign
	h[34] = 16; // BitsPerSample
	h[36] = 'd'; h[37] = 'a'; h[38] = 't'; h[39] = 'a';
	unsigned long dataSize = (unsigned long)(count * 2);
	h[40] = (unsigned char)(dataSize & 0xFF);
	h[41] = (unsigned char)((dataSize >> 8) & 0xFF);
	h[42] = (unsigned char)((dataSize >> 16) & 0xFF);
	h[43] = (unsigned char)((dataSize >> 24) & 0xFF);

	FILE* f = fopen(path, "wb");
	if (!f) return false;
	bool ok = fwrite(h, 1, 44, f) == 44;
	if (ok && count)
		ok = fwrite(pcm, 2, count, f) == count;
	fclose(f);
	return ok;
}

// ---------------------------------------------------------------------------
// Прослушивание (waveOut, 16-бит моно)
// ---------------------------------------------------------------------------
static bool PlayPcmShort(const short* pcm, size_t count, int rate)
{
	WAVEFORMATEX wfx;
	memset(&wfx, 0, sizeof(wfx));
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 1;
	wfx.nSamplesPerSec = rate;
	wfx.nAvgBytesPerSec = rate * 2;
	wfx.nBlockAlign = 2;
	wfx.wBitsPerSample = 16;

	HWAVEOUT hwo = NULL;
	if (waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		return false;

	WAVEHDR hdr;
	memset(&hdr, 0, sizeof(hdr));
	hdr.lpData = (LPSTR)pcm;
	hdr.dwBufferLength = (DWORD)(count * 2);

	MMRESULT res = waveOutPrepareHeader(hwo, &hdr, sizeof(hdr));
	if (res == MMSYSERR_NOERROR) {
		res = waveOutWrite(hwo, &hdr, sizeof(hdr));
		if (res == MMSYSERR_NOERROR) {
			while (waveOutUnprepareHeader(hwo, &hdr, sizeof(hdr)) == WAVERR_STILLPLAYING) {
				Sleep(10);
			}
		} else {
			waveOutUnprepareHeader(hwo, &hdr, sizeof(hdr));
		}
	}
	waveOutClose(hwo);
	return res == MMSYSERR_NOERROR;
}

// ---------------------------------------------------------------------------
// Печать справки
// ---------------------------------------------------------------------------
static void PrintUsage()
{
	printf("sdtool - конвертер звуковых банков GTA2 (.sdt/.raw) <-> .wav\n");
	printf("\n");
	printf("Использование:\n");
	printf("  sdtool list       <bank>                     список звуков банка\n");
	printf("  sdtool info       <bank>                     информация о банке\n");
	printf("  sdtool export     <bank> <index> <out.wav>   выгрузить звук в .wav\n");
	printf("  sdtool import     <bank> <index> <in.wav>    заменить звук из .wav\n");
	printf("  sdtool add        <bank> <in.wav>            добавить звук в конец\n");
	printf("  sdtool play       <bank> <index>             прослушать звук\n");
	printf("  sdtool exportall  <bank> <dir>               выгрузить все звуки в папку\n");
	printf("\n");
	printf("bank - имя банка без расширения (ste, bil, wil, fstyle, level000, ...),\n");
	printf("ищется в data\\audio и bin\\data\\audio.\n");
	printf("index - номер звука (0-based), см. вывод list.\n");
	printf("\n");
	printf("Примеры:\n");
	printf("  sdtool list ste\n");
	printf("  sdtool export ste 12 ste_12.wav\n");
	printf("  sdtool import ste 12 new.wav\n");
	printf("  sdtool add vol1 new.wav\n");
	printf("  sdtool play ste 12\n");
}

// ---------------------------------------------------------------------------
// Разбор аргументов командной строки
// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	if (argc < 3) {
		PrintUsage();
		return 1;
	}

	std::string cmd = argv[1];
	std::string bank = argv[2];

	std::string sdtPath, rawPath;
	if (!FindBankFile(bank.c_str(), ".sdt", sdtPath) ||
	    !FindBankFile(bank.c_str(), ".raw", rawPath)) {
		printf("Ошибка: банк '%s' не найден (нужны %s.sdt и %s.raw в data\\audio).\n",
		       bank.c_str(), bank.c_str(), bank.c_str());
		return 1;
	}

	std::vector<unsigned char> sdt, raw;
	if (!ReadFile(sdtPath.c_str(), sdt) || !ReadFile(rawPath.c_str(), raw)) {
		printf("Ошибка: не удалось прочитать банк '%s'.\n", bank.c_str());
		return 1;
	}

	std::vector<SdtEntry> entries;
	int n = LoadBank(sdt, raw, entries);
	if (n < 0) {
		printf("Ошибка: %s.sdt повреждён (размер не кратен 24).\n", bank.c_str());
		return 1;
	}

	int badCount = 0;
	for (int i = 0; i < n; i++)
		if (entries[i].size == 0)
			badCount++;

	if (cmd == "list") {
		printf("Банк %s: %d звуков (%s + %s)\n", bank.c_str(), n,
		       sdtPath.c_str(), rawPath.c_str());
		if (badCount)
			printf("  (WARNING: %d записей выходят за пределы .raw и будут пропущены)\n", badCount);
		printf("%-5s %-10s %-9s %-8s %-5s %-5s %-9s\n",
		       "#", "offset", "size", "rate", "loopS", "loopE", "dur_ms");
		for (int i = 0; i < n; i++) {
			if (entries[i].size == 0)
				continue;
			const SdtEntry& e = entries[i];
			unsigned long dur = e.size ? (unsigned long)((double)e.size / 2.0 / e.sampleRate * 1000.0) : 0;
			printf("%-5d %-10lu %-9lu %-8lu %-5lu %-5lu %-9lu\n",
			       i, e.offset, e.size, e.sampleRate, e.loopStart, e.loopEnd, dur);
		}
		return 0;
	}

	if (cmd == "info") {
		printf("Банк: %s\n", bank.c_str());
		printf("  .sdt : %s (%u байт, %d записей)\n", sdtPath.c_str(), (unsigned)sdt.size(), n);
		printf("  .raw : %s (%u байт)\n", rawPath.c_str(), (unsigned)raw.size());
		if (badCount)
			printf("  WARNING: %d записей выходят за пределы .raw.\n", badCount);
		return 0;
	}

	if (cmd == "export") {
		if (argc < 5) { printf("Ошибка: нужно указать index и имя .wav.\n"); return 1; }
		int idx = atoi(argv[3]);
		if (idx < 0 || idx >= n || entries[idx].size == 0) {
			printf("Ошибка: нет звука с индексом %d.\n", idx);
			return 1;
		}
		const SdtEntry& e = entries[idx];
		const short* src = (const short*)&raw[e.offset];
		size_t count = e.size / 2;
		if (e.size % 2) count++; // нечётный размер - дописываем 0
		if (!WriteWav(argv[4], src, count, (int)e.sampleRate)) {
			printf("Ошибка: не удалось записать %s.\n", argv[4]);
			return 1;
		}
		printf("Экспортирован звук %d (%lu байт, %lu Гц) -> %s\n",
		       idx, e.size, e.sampleRate, argv[4]);
		return 0;
	}

	if (cmd == "import" || cmd == "add") {
		if (cmd == "import" && argc < 5) { printf("Ошибка: нужно указать index и .wav.\n"); return 1; }
		if (cmd == "add" && argc < 4)    { printf("Ошибка: нужно указать .wav.\n"); return 1; }

		int idx = n;
		if (cmd == "import") {
			idx = atoi(argv[3]);
			if (idx < 0 || idx >= n) {
				printf("Ошибка: нет звука с индексом %d.\n", idx);
				return 1;
			}
		}
		const char* wavFile = (cmd == "import") ? argv[4] : argv[3];

		std::vector<short> pcm;
		int rate = 0;
		if (!ReadWavPcm(wavFile, pcm, rate)) {
			printf("Ошибка: %s - не удалось прочитать (поддерживаются только несжатые PCM WAV 8/16 бит).\n", wavFile);
			return 1;
		}

		// Данные всех звуков в память
		std::vector<std::vector<unsigned char> > datas;
		datas.resize((size_t)n);
		for (int i = 0; i < n; i++) {
			if (entries[i].size > 0 && entries[i].offset < raw.size())
				datas[i].assign(&raw[entries[i].offset], &raw[entries[i].offset] + entries[i].size);
		}

		// Новый звук
		std::vector<unsigned char> newData((size_t)pcm.size() * 2);
		memcpy(&newData[0], &pcm[0], newData.size());

		if (cmd == "import") {
			datas[idx].swap(newData);
		} else {
			SdtEntry ne;
			memset(&ne, 0, sizeof(ne));
			ne.size = (unsigned long)newData.size();
			ne.sampleRate = (unsigned long)rate;
			ne.reserved = kSdtReserved;
			entries.push_back(ne);
			datas.push_back(newData);
		}

		// Пересчитываем смещения и размеры
		std::vector<unsigned char> newRaw;
		unsigned long off = 0;
		for (size_t i = 0; i < entries.size(); i++) {
			entries[i].offset = off;
			entries[i].size = (unsigned long)datas[i].size();
			entries[i].reserved = kSdtReserved;
			off += (unsigned long)datas[i].size();
			newRaw.insert(newRaw.end(), datas[i].begin(), datas[i].end());
		}

		std::vector<unsigned char> newSdt;
		SaveSdt(entries, newSdt);

		if (!WriteFile(sdtPath.c_str(), &newSdt[0], newSdt.size()) ||
		    !WriteFile(rawPath.c_str(), &newRaw[0], newRaw.size())) {
			printf("Ошибка: не удалось записать банк.\n");
			return 1;
		}

		printf("%s: звук номер %d (%d сэмплов, %d Гц) сохранён в банк %s.\n",
		       (cmd == "import") ? "Заменён" : "Добавлен",
		       idx, (int)pcm.size(), rate, bank.c_str());
		return 0;
	}

	if (cmd == "play") {
		if (argc < 4) { printf("Ошибка: нужно указать index.\n"); return 1; }
		int idx = atoi(argv[3]);
		if (idx < 0 || idx >= n || entries[idx].size == 0) {
			printf("Ошибка: нет звука с индексом %d.\n", idx);
			return 1;
		}
		const SdtEntry& e = entries[idx];
		const short* src = (const short*)&raw[e.offset];
		size_t count = e.size / 2;
		printf("Играю звук %d (%lu байт, %lu Гц)...\n", idx, e.size, e.sampleRate);
		if (!PlayPcmShort(src, count, (int)e.sampleRate)) {
			printf("Ошибка: waveOut недоступен.\n");
			return 1;
		}
		return 0;
	}

	if (cmd == "exportall") {
		if (argc < 4) { printf("Ошибка: нужно указать папку.\n"); return 1; }
		CreateDirectoryA(argv[3], NULL);
		int ok = 0, failed = 0;
		for (int i = 0; i < n; i++) {
			if (entries[i].size == 0)
				continue;
			char outPath[512];
			_snprintf(outPath, sizeof(outPath), "%s\\%s_%04d.wav", argv[3], bank.c_str(), i);
			const SdtEntry& e = entries[i];
			const short* src = (const short*)&raw[e.offset];
			size_t count = e.size / 2;
			if (e.size % 2) count++;
			if (WriteWav(outPath, src, count, (int)e.sampleRate))
				ok++;
			else
				failed++;
		}
		printf("Экспортировано %d звуков в %s%s\n", ok, argv[3],
		       failed ? ", ошибок: 1+" : "");
		return failed ? 1 : 0;
	}

	printf("Неизвестная команда: %s\n", cmd.c_str());
	PrintUsage();
	return 1;
}