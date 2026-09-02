#include "Sound.h"
#include <cstdio>
#include <cstring>
#include <string>

Sound gSound;

// Поиск файла в возможных папках данных (приложение может запускаться из разных мест).
static FILE* OpenDataFile(const char* name)
{
	const char* dirs[] = {
		"data\\audio\\",
		"bin\\data\\audio\\",
		"..\\bin\\data\\audio\\",
		"C:\\work\\GTA2_RE\\bin\\data\\audio\\"
	};
	for (int i = 0; i < 4; i++) {
		FILE* f = fopen((std::string(dirs[i]) + name).c_str(), "rb");
		if (f)
			return f;
	}
	return NULL;
}

Sound::Sound()
	: Sound3D(false), m_Init(false), m_Volume(127)
{
	memset(m_Voices, 0, sizeof(m_Voices));
	for (int i = 0; i < 8; i++) {
		m_Voices[i].sampleIndex = -1;
		m_Voices[i].loop2 = false;
		m_Voices[i].stopped = false;
	}
}

Sound::~Sound()
{
	Shutdown();
}

// Инициализация: проверяем, что есть хоть какое-то волновое устройство,
// способное играть 16-бит моно 22050 Гц (WAVE_FORMAT_QUERY ничего не открывает).
bool Sound::InitAudioSystem()
{
	WAVEFORMATEX wfx;
	memset(&wfx, 0, sizeof(wfx));
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 1;
	wfx.nSamplesPerSec = 22050;
	wfx.nAvgBytesPerSec = 22050 * 2;
	wfx.nBlockAlign = 2;
	wfx.wBitsPerSample = 16;
	m_Init = (waveOutOpen(NULL, WAVE_MAPPER, &wfx, 0, 0, WAVE_FORMAT_QUERY) == MMSYSERR_NOERROR);
	Sound3D = false;
	return m_Init;
}

void Sound::Shutdown()
{
	StopAll();
	SweepFinished();
	m_Entries.clear();
	m_Raw.clear();
	m_Init = false;
}

// Чтение банка: .sdt (24 байта на звук) и .raw (данные, сумма размеров равна размеру .raw).
int Sound::LoadBank(const char* name)
{
	m_Entries.clear();
	m_Raw.clear();
	if (!m_Init)
		return 0;

	std::string base = std::string(name) + ".sdt";
	FILE* fs = OpenDataFile(base.c_str());
	if (!fs)
		return 0;
	fseek(fs, 0, SEEK_END);
	long sdtSize = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	if (sdtSize <= 0 || sdtSize % 24) {
		fclose(fs);
		return 0;
	}
	std::vector<unsigned char> sdt((size_t)sdtSize);
	if (fread(&sdt[0], 1, (size_t)sdtSize, fs) != (size_t)sdtSize) {
		fclose(fs);
		return 0;
	}
	fclose(fs);

	std::string rawBase = std::string(name) + ".raw";
	FILE* fr = OpenDataFile(rawBase.c_str());
	if (!fr)
		return 0;
	fseek(fr, 0, SEEK_END);
	long rawSize = ftell(fr);
	fseek(fr, 0, SEEK_SET);
	if (rawSize <= 0) {
		fclose(fr);
		return 0;
	}
	m_Raw.resize((size_t)rawSize);
	if (fread(&m_Raw[0], 1, (size_t)rawSize, fr) != (size_t)rawSize) {
		fclose(fr);
		m_Raw.clear();
		return 0;
	}
	fclose(fr);

	// Разбираем таблицу .sdt; пропускаем записи, выходящие за пределы .raw.
	int n = sdtSize / 24;
	for (int i = 0; i < n; i++) {
		SdtEntry e;
		e.offset      = sdt[i * 24 + 0] | (sdt[i * 24 + 1] << 8) | (sdt[i * 24 + 2] << 16) | ((unsigned long)sdt[i * 24 + 3] << 24);
		e.size        = sdt[i * 24 + 4] | (sdt[i * 24 + 5] << 8) | (sdt[i * 24 + 6] << 16) | ((unsigned long)sdt[i * 24 + 7] << 24);
		e.sampleRate  = sdt[i * 24 + 8] | (sdt[i * 24 + 9] << 8) | (sdt[i * 24 + 10] << 16) | ((unsigned long)sdt[i * 24 + 11] << 24);
		e.loopStart   = sdt[i * 24 + 12] | (sdt[i * 24 + 13] << 8) | (sdt[i * 24 + 14] << 16) | ((unsigned long)sdt[i * 24 + 15] << 24);
		e.loopEnd     = sdt[i * 24 + 16] | (sdt[i * 24 + 17] << 8) | (sdt[i * 24 + 18] << 16) | ((unsigned long)sdt[i * 24 + 19] << 24);
		e.reserved    = sdt[i * 24 + 20] | (sdt[i * 24 + 21] << 8) | (sdt[i * 24 + 22] << 16) | ((unsigned long)sdt[i * 24 + 23] << 24);
		// Размер должен быть хотя бы 4 байта (маленькие записи 10-128 байт - это
		// настоящие короткие "клики"/высокие звуки, тоже играем).
		if (e.offset >= (unsigned long)rawSize || e.size < 4 ||
		    e.offset + e.size > (unsigned long)rawSize || e.sampleRate == 0)
			continue;
		m_Entries.push_back(e);
	}
	return (int)m_Entries.size();
}

void Sound::GetSampleInfo(int index, int& size, int& rate, int& loopStart, int& loopEnd) const
{
	size = 0; rate = 0; loopStart = 0; loopEnd = 0;
	if (index < 0 || index >= (int)m_Entries.size())
		return;
	const SdtEntry& e = m_Entries[index];
	size = (int)e.size;
	rate = (int)e.sampleRate;
	loopStart = (int)e.loopStart;
	loopEnd = (int)e.loopEnd;
}

// Поиск свободного голоса. Если все заняты (одновременно звучат 8 звуков) - NULL.
Sound::Voice* Sound::FindFreeVoice()
{
	for (int i = 0; i < 8; i++)
		if (!m_Voices[i].active)
			return &m_Voices[i];
	return NULL;
}

// Callback волнового устройства (вызывается на отдельном потоке winmm).
// Закрывать устройство и чистить данные здесь НЕЛЬЗЯ: waveOutClose/Reset внутри
// callback на некоторых драйверах дают самодедлок. Callback только:
//   - помечает обычный завершившийся голос свободным (закрытие сделает Update),
//   - у двухфазного цикла переключает буфер на область loopStart..loopEnd
//     (waveOutWrite безопасен, устройство остаётся открытым).
// Если голос остановлен через StopAll (stopped) - устройство уже закрыто, ничего
// не делаем (callback приходит после waveOutReset).
void CALLBACK Sound::WaveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwUser,
                                 DWORD_PTR /*dwParam1*/, DWORD_PTR /*dwParam2*/)
{
if (uMsg != WOM_DONE)
		return;
	Voice* v = (Voice*)dwUser;
	if (!v || v->stopped)
		return;

	// Первый проход двухфазного цикла закончился: начинаем бесконечный цикл области.
	if (v->loop2 && !v->loopPcm.empty() && v->hdr.dwLoops != 0xFFFFFFFF) {
		waveOutUnprepareHeader(hwo, &v->hdr, sizeof(v->hdr));
		v->hdr.lpData = (LPSTR)(&v->loopPcm[0]);
		v->hdr.dwBufferLength = (DWORD)(v->loopPcm.size() * 2);
		v->hdr.dwBytesRecorded = 0;
		v->hdr.dwLoops = 0xFFFFFFFF; // зациклить бесконечно
		v->hdr.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
		MMRESULT res = waveOutPrepareHeader(hwo, &v->hdr, sizeof(v->hdr));
		if (res == MMSYSERR_NOERROR)
			res = waveOutWrite(hwo, &v->hdr, sizeof(v->hdr));
		if (res != MMSYSERR_NOERROR) {
			// Устройство закроет SweepFinished() в Update() - сюда закрывать нельзя.
			v->active = false;
			v->sampleIndex = -1;
		}
		return;
	}

	// Штатное завершение обычного звука: голос сразу свободен для пула,
	// закрытие устройства сделает SweepFinished() в Update().
	v->active = false;
	v->sampleIndex = -1;
}

// Закрытие устройств завершившихся голосов. Вызывается только из главного
// потока (Update, PlaySample, StopAll) - внутри callback звук не закрываем.
void Sound::SweepFinished()
{
	for (int i = 0; i < 8; i++) {
		Voice& v = m_Voices[i];
		if (v.active)
			continue;
		if (v.hWaveOut) {
			waveOutUnprepareHeader(v.hWaveOut, &v.hdr, sizeof(v.hdr));
			waveOutClose(v.hWaveOut);
			v.hWaveOut = NULL;
		}
		v.hdr.lpData = NULL;
		v.pcm.clear();
		v.loopPcm.clear();
		v.sampleIndex = -1;
		v.stopped = false;
	}
}

bool Sound::PlaySample(int index, bool loop)
{
	if (!m_Init || index < 0 || index >= (int)m_Entries.size())
		return false;
	const SdtEntry& e = m_Entries[index];
	if (e.size < 4)
		return false;

	SweepFinished(); // освободить завершившиеся голоса перед поиском свободного
	Voice* v = FindFreeVoice();
	if (!v)
		return false; // все голоса заняты - звук пропускаем (как и в оригинале при переполнении)

	// Формат звука из таблицы .sdt: 16-бит PCM моно, часота из записи.
	WAVEFORMATEX wfx;
	memset(&wfx, 0, sizeof(wfx));
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 1;
	wfx.nSamplesPerSec = e.sampleRate;
	wfx.nAvgBytesPerSec = e.sampleRate * 2;
	wfx.nBlockAlign = 2;
	wfx.wBitsPerSample = 16;

	MMRESULT res = waveOutOpen(&v->hWaveOut, WAVE_MAPPER, &wfx,
	                           (DWORD_PTR)Sound::WaveOutProc, (DWORD_PTR)v, CALLBACK_FUNCTION);
	if (res != MMSYSERR_NOERROR)
		return false;

	// Копия данных (PCM 16-бит моно).
	const short* src = (const short*)(&m_Raw[e.offset]);
	v->pcm.assign(src, src + e.size / 2);

	// Двухфазное зацикливание: loopStart/loopEnd - байтовые смещения в сэмпле
	// (0 = начало/конец). Если область цикла существует, первый проход играет
	// от начала до loopEnd, затем бесконечно повторяется loopStart..loopEnd.
	unsigned long firstLen = e.size;
	v->loopPcm.clear();
	v->loop2 = false;
	if (loop && (e.loopStart != 0 || e.loopEnd != 0)) {
		unsigned long ls = e.loopStart;
		unsigned long le = e.loopEnd ? e.loopEnd : e.size;
		if (le > e.size)
			le = e.size;
		ls &= ~1UL; // 16-бит сэмплы - выравниваем на чётное
		le &= ~1UL;
		if (ls < le) {
			v->loop2 = true;
			v->loopPcm.assign(src + ls / 2, src + le / 2);
			firstLen = le < firstLen ? le : firstLen;
		}
	}

	memset(&v->hdr, 0, sizeof(v->hdr));
	v->hdr.lpData = (LPSTR)(&v->pcm[0]);
	v->hdr.dwBufferLength = (DWORD)firstLen;
	if (loop && !v->loop2) {
		v->hdr.dwLoops = 0xFFFFFFFF; // зациклить весь сэмпл бесконечно
		v->hdr.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
	}

	res = waveOutPrepareHeader(v->hWaveOut, &v->hdr, sizeof(v->hdr));
	if (res != MMSYSERR_NOERROR) {
		waveOutClose(v->hWaveOut);
		v->hWaveOut = NULL;
		return false;
	}
	res = waveOutWrite(v->hWaveOut, &v->hdr, sizeof(v->hdr));
	if (res != MMSYSERR_NOERROR) {
		waveOutUnprepareHeader(v->hWaveOut, &v->hdr, sizeof(v->hdr));
		waveOutClose(v->hWaveOut);
		v->hWaveOut = NULL;
		return false;
	}

	// Громкость на голос (0..0xFFFF на каждый канал; для моно достаточно младшего).
	DWORD vol = (DWORD)(m_Volume * 0xFFFF / 127);
	waveOutSetVolume(v->hWaveOut, vol | (vol << 16));

	v->active = true;
	v->stopped = false;
	v->sampleIndex = index;
	return true;
}

bool Sound::PlayPcm(const std::vector<short>& pcm, int rate)
{
	if (!m_Init || rate <= 0 || pcm.empty())
		return false;

	SweepFinished(); // освободить завершившиеся голоса перед поиском свободного
	Voice* v = FindFreeVoice();
	if (!v)
		return false;

	WAVEFORMATEX wfx;
	memset(&wfx, 0, sizeof(wfx));
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 1;
	wfx.nSamplesPerSec = rate;
	wfx.nAvgBytesPerSec = rate * 2;
	wfx.nBlockAlign = 2;
	wfx.wBitsPerSample = 16;

	MMRESULT res = waveOutOpen(&v->hWaveOut, WAVE_MAPPER, &wfx,
	                           (DWORD_PTR)Sound::WaveOutProc, (DWORD_PTR)v, CALLBACK_FUNCTION);
	if (res != MMSYSERR_NOERROR)
		return false;

	v->pcm = pcm;
	v->loopPcm.clear();
	v->loop2 = false;

	memset(&v->hdr, 0, sizeof(v->hdr));
	v->hdr.lpData = (LPSTR)(&v->pcm[0]);
	v->hdr.dwBufferLength = (DWORD)(v->pcm.size() * 2);

	res = waveOutPrepareHeader(v->hWaveOut, &v->hdr, sizeof(v->hdr));
	if (res != MMSYSERR_NOERROR) {
		waveOutClose(v->hWaveOut);
		v->hWaveOut = NULL;
		return false;
	}
	res = waveOutWrite(v->hWaveOut, &v->hdr, sizeof(v->hdr));
	if (res != MMSYSERR_NOERROR) {
		waveOutUnprepareHeader(v->hWaveOut, &v->hdr, sizeof(v->hdr));
		waveOutClose(v->hWaveOut);
		v->hWaveOut = NULL;
		return false;
	}

	DWORD vol = (DWORD)(m_Volume * 0xFFFF / 127);
	waveOutSetVolume(v->hWaveOut, vol | (vol << 16));

	v->active = true;
	v->stopped = false;
	v->sampleIndex = -1;
	return true;
}

void Sound::StopAll()
{
	for (int i = 0; i < 8; i++) {
		Voice& v = m_Voices[i];
		if (!v.active || !v.hWaveOut)
			continue;
		v.stopped = true; // callback (WOM_DONE после Reset) ничего не трогает - закрываем сами
		waveOutReset(v.hWaveOut); // немедленно остановить воспроизведение
		waveOutUnprepareHeader(v.hWaveOut, &v.hdr, sizeof(v.hdr));
		waveOutClose(v.hWaveOut);
		v.hWaveOut = NULL;
		v.hdr.lpData = NULL;
		v.pcm.clear();
		v.loopPcm.clear();
		v.sampleIndex = -1;
		v.active = false;
	}
	SweepFinished();
}

bool Sound::IsPlaying() const
{
	for (int i = 0; i < 8; i++)
		if (m_Voices[i].active)
			return true;
	return false;
}

void Sound::SetVolume(char vol)
{
	if (vol < 0)
		vol = 0;
	if (vol > 127)
		vol = 127;
	m_Volume = vol;
	DWORD v = (DWORD)(m_Volume * 0xFFFF / 127);
	for (int i = 0; i < 8; i++)
		if (m_Voices[i].active && m_Voices[i].hWaveOut)
			waveOutSetVolume(m_Voices[i].hWaveOut, v | (v << 16));
}

void Sound::Update()
{
	// Закрываем устройства завершившихся голосов: сам callback (WOM_DONE) это
	// делать не может (waveOutClose из callback на некоторых драйверах - дедлок).
	SweepFinished();
}

// ---------------------------------------------------------------------------
// Чтение *.wav игры: 16-бит PCM или IMA ADPCM (формат Vocals GTA2: 22050 Гц,
// моно, blockAlign 512, samplesPerBlock 1017). На выходе всегда 16-бит PCM моно.
// ---------------------------------------------------------------------------

// Таблицы IMA ADPCM (стандартные для всех IMA-декодеров).
static const int ImaIndexTable[16] = {
	-1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8
};
static const int ImaStepTable[89] = {
	7, 8, 9, 10, 11, 12, 13, 14, 16, 17,
	19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
	50, 55, 60, 66, 73, 80, 88, 97, 107, 118,
	130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
	337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
	876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066,
	2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
	5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
	15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767
};

// Декодер IMA ADPCM канала внутри блока (Vocals GTA2). Каждый блок:
//   4 байта заголовка на канал (предиктор 16-бит + индекс шага + резерв),
//   затем per-канальные НЕПРЕРЫВНЫЕ данные: (blockAlign-4*channels)/channels байт,
//   из которых реально значащих (samplesPerBlock-1)/2 байт (последний блок файла
//   дополнен нулями до blockAlign). Обновляет декодированные сэмплы канала в out.
static void ImaAdpcmDecodeRun(const unsigned char* data, int runBytes, int samplesPerBlock,
                              std::vector<short>& out)
{
	int predictor = (short)(data[0] | (data[1] << 8));
	int stepIndex = data[2];
	if (stepIndex < 0)
		stepIndex = 0;
	if (stepIndex > 88)
		stepIndex = 88;
	out.push_back((short)predictor);

	// Реально значащих байт данных канала: (samplesPerBlock-1)/2, не больше runBytes-4.
	int dataBytes = runBytes - 4;
	int maxData = (samplesPerBlock - 1) / 2;
	if (dataBytes > maxData)
		dataBytes = maxData;
	if (dataBytes < 0)
		dataBytes = 0;

	int s = 1;
	for (int b = 0; b < dataBytes; b++) {
		int code = data[4 + b];
		for (int nib = 0; nib < 2 && s < samplesPerBlock; nib++) {
			int nb = (nib == 0) ? (code & 0x0F) : ((code >> 4) & 0x0F);
			int step = ImaStepTable[stepIndex];
			int diff = step >> 3;
			if (nb & 1) diff += step >> 2;
			if (nb & 2) diff += step >> 1;
			if (nb & 4) diff += step;
			if (nb & 8) diff = -diff;
			predictor += diff;
			if (predictor > 32767) predictor = 32767;
			else if (predictor < -32768) predictor = -32768;
			stepIndex += ImaIndexTable[nb];
			if (stepIndex < 0) stepIndex = 0;
			if (stepIndex > 88) stepIndex = 88;
			out.push_back((short)predictor);
			s++;
		}
	}
}

bool Sound::WavToPcm(const char* path, std::vector<short>& pcm, int& rate)
{
	pcm.clear();
	rate = 0;

	FILE* f = fopen(path, "rb");
	if (!f)
		return false;
	fseek(f, 0, SEEK_END);
	long sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (sz < 44) {
		fclose(f);
		return false;
	}
	std::vector<unsigned char> d((size_t)sz);
	if (fread(&d[0], 1, (size_t)sz, f) != (size_t)sz) {
		fclose(f);
		return false;
	}
	fclose(f);

	// Заголовок "RIFF"...."WAVE" и обход чанков (чанки выровнены по 16 бит).
	if (d[0] != 'R' || d[1] != 'I' || d[2] != 'F' || d[3] != 'F' ||
	    d[8] != 'W' || d[9] != 'A' || d[10] != 'V' || d[11] != 'E')
		return false;

	long pos = 12;
	int  tag = 0, channels = 0, sampleRate = 0, bits = 0, blockAlign = 0, samplesPerBlock = 0;
	int  factSamples = 0;
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
			blockAlign = (short)(d[body + 12] | (d[body + 13] << 8));
			if (ckSize > 16 && body + 18 <= sz) // cbSize (+ samplesPerBlock после него)
				samplesPerBlock = (short)(d[body + 18] | (d[body + 19] << 8));
		} else if (id == 0x74636166UL) { // "fact": реальное число сэмплов на канал
			if (ckSize >= 4)
				factSamples = (int)(d[body] | (d[body + 1] << 8) | (d[body + 2] << 16) | ((unsigned int)d[body + 3] << 24));
		} else if (id == 0x61746164UL) { // "data"
			dataOff = body;
			dataSize = ckSize;
		}
		// остальные чанки пропускаем; чанки выровнены по 16 бит.
		pos = body + ckSize + (ckSize & 1);
	}
	if (dataOff < 0 || dataSize < 0)
		return false;

	if (sampleRate == 0)
		return false;
	rate = sampleRate;

	if (tag == 0x0001) { // WAVE_FORMAT_PCM: 16-бит моно/стерео
		if (bits != 16)
			return false;
		int step = 2 * channels;
		for (long i = dataOff; i + 1 < dataOff + dataSize && i + 1 < sz; i += step) {
			short s = (short)(d[i] | (d[i + 1] << 8));
			pcm.push_back(s); // стерео сжимаем в моно (берём левый канал)
		}
		return !pcm.empty();
	}
	if (tag == 0x0011) { // WAVE_FORMAT_IMA_ADPCM (Vocals GTA2, 22050 Гц)
		if (samplesPerBlock <= 0)
			samplesPerBlock = 1017;
		long avail = dataOff + dataSize < sz ? dataSize : sz - dataOff;
		if (avail < 4)
			return false;

		// Каждому каналу - свой поток сэмплов; на выходе - моно (микс каналов).
		int ch = channels > 0 ? channels : 1;
		int perChanData = (blockAlign - 4 * ch) / ch; // байт данных канала в блоке
		if (perChanData < 0)
			perChanData = 0;
		std::vector<std::vector<short> > chanPcm(ch);

		long pos = dataOff;
		long end = dataOff + avail;
		while (pos + 4 * ch <= end) {
			int limit = (int)(end - pos);
			int bytes = blockAlign < limit ? blockAlign : limit;
			if (bytes < 4 * ch)
				break;
			int runData = bytes - 4 * ch;
			if (runData > perChanData)
				runData = perChanData; // последний блок может быть обрезан
			for (int c = 0; c < ch; c++)
				ImaAdpcmDecodeRun(&d[pos + c * 4], 4 + runData, samplesPerBlock, chanPcm[c]);
			pos += bytes;
		}

		// fact = реальное число сэмплов на канал: последний блок файла дополнен
		// нулями до blockAlign, лишние сэмплы обрезаем.
		for (int c = 0; c < ch; c++)
			if (factSamples > 0 && factSamples < (int)chanPcm[c].size())
				chanPcm[c].resize(factSamples);

		// Можем выдать моно: усредняем каналы, чтобы не терять громкость.
		if (ch == 1) {
			pcm.swap(chanPcm[0]);
		} else {
			size_t n = chanPcm[0].size();
			pcm.resize(n);
			for (size_t i = 0; i < n; i++) {
				int s = chanPcm[0][i] + chanPcm[1][i];
				pcm[i] = (short)(s / 2);
			}
		}
		return !pcm.empty();
	}
	return false; // прочие форматы (MP3 и т.п.) не поддерживаем
}