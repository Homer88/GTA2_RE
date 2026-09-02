#ifndef __SOUND_H_
#define __SOUND_H_

#include <windows.h>
#include <mmsystem.h>
#include <vector>

// Движок звука реконструкции GTA2.
//
// Что умеет (и откуда взяты форматы — из анализа bin\data\audio оригинальной игры):
//   - Читает звуковые банки data\audio\<имя>.sdt (таблица звуков) + <имя>.raw
//     (сами данные - 16-битный знаковый PCM моно, частота у каждого звука своя).
//     .sdt = массив записей по 24 байта: offset(4) | size(4) | sampleRate(4) |
//     loopStart(4) | loopEnd(4) | 0xFFFFFFFF(4). Размеры сходятся с .raw до байта.
//   - Воспроизводит звуки через WinAPI waveOut (замена Miles Sound System: каждый
//     играющий звук - отдельная волна-устройство). Поддерживает честное
//     зацикливание по полям loopStart/loopEnd из .sdt, остановку и громкость.
//   - Декодирует Vocals\*.wav (формат игры GTA2: IMA ADPCM, 22050 Гц, моно)
//     в PCM - метод WavToPcm().
//
// Воспроизведение 2D (без позиционирования в 3D): в оригинале 3D-звук делал
// DirectSound через MSS, у нас пока всегда моно-выход waveOut.

class Sound {
public:
	Sound();
	~Sound();

	// Инициализация подсистемы: проверяем, что волновое устройство доступно
	// (аналог SoundCard::InitializeAudioSystem в оригинале).
	bool InitAudioSystem();
	void Shutdown();

	// Загрузка банка data\audio\<name>.sdt/.raw. Возвращает число звуков (0 - ошибка).
	int  LoadBank(const char* name);
	int  GetSampleCount() const { return (int)m_Entries.size(); }
	void GetSampleInfo(int index, int& size, int& rate, int& loopStart, int& loopEnd) const;

	// Воспроизвести звук банка по индексу. loop=true - зациклить (как у городских
	// звуков природы/двигателей). Цикл честный: сначала звук проигрывается от
	// начала до loopEnd, затем бесконечно повторяется область loopStart..loopEnd
	// (поля .sdt, байтовые смещения; 0 = начало/конец сэмпла). Если области цикла
	// нет (loopStart==loopEnd==0) - зацикливается весь сэмпл. Если все голоса
	// заняты - не играет.
	bool PlaySample(int index, bool loop);

	// Воспроизвести готовый PCM (16-бит моно, rate Гц) один раз без остановки.
	// Используется для Vocals (после декодирования через WavToPcm) и прочих
	// внешних данных.
	bool PlayPcm(const std::vector<short>& pcm, int rate);

	void StopAll();         // остановить все играющие звуки
	bool IsPlaying() const; // есть ли активные голоса
	void SetVolume(char vol); // громкость звуков 0..127 (SFXVol из реестра)

	// Обновление каждый кадр (аналог DMAudio::sub_410520): здесь закрываются
	// устройства голосов, завершившихся в callback'е waveOut (сам callback этого
	// делать не может - waveOutClose из callback на некоторых драйверах даёт дедлок).
	void Update();

	// Декодирование .wav в PCM (16-бит моно): либо обычный PCM, либо IMA ADPCM
	// (именно такой формат у Vocals GTA2). rate - частота на выходе.
	static bool WavToPcm(const char* path, std::vector<short>& pcm, int& rate);

	bool Sound3D; // запрошен ли 3D-звук (у нас всегда запасной 2D-путь)

private:
	struct SdtEntry { // запись таблицы .sdt (24 байта)
		unsigned long offset;     // смещение звука в .raw
		unsigned long size;       // размер данных в байтах
		unsigned long sampleRate; // частота дискретизации
		unsigned long loopStart;  // начало цикла (в сэмплах), 0 = нет
		unsigned long loopEnd;    // конец цикла (в сэмплах)
		unsigned long reserved;   // всегда 0xFFFFFFFF
	};

	struct Voice { // один играющий звук (одно waveOut-устройство)
		HWAVEOUT hWaveOut;
		WAVEHDR  hdr;
		std::vector<short> pcm;      // данные звука (16-бит моно)
		std::vector<short> loopPcm;  // область цикла [loopStart..loopEnd), спец.фаза 2
		bool     loop2;              // двухфазное зацикливание (сначала начало, затем область)
		bool     stopped;            // голос останавливается (StopAll) - не продолжать в callback
		int      sampleIndex;        // индекс в банке, -1 если вне банка
		bool     active;
	};

	// Callback волны: по завершении звука либо переводит двухфазный цикл на
	// область loopStart..loopEnd, либо помечает голос свободным (закрытие
	// устройства делает главный поток через SweepFinished).
	static void CALLBACK WaveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwUser,
	                                 DWORD_PTR dwParam1, DWORD_PTR dwParam2);
	Voice* FindFreeVoice(); // свободный голос или NULL
	void   SweepFinished(); // закрыть устройства завершившихся голосов (главный поток)

	std::vector<unsigned char> m_Raw;     // данные текущего банка (.raw)
	std::vector<SdtEntry>      m_Entries; // таблица звуков (.sdt)
	Voice   m_Voices[8];                  // пул голосов
	bool    m_Init;
	char    m_Volume;                     // 0..127
};

extern Sound gSound;
#endif // !__SOUND_H_