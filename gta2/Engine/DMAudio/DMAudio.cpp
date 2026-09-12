// DMAudio - публичный интерфейс звука игры (реконструкция).
// Соответствует классу DMAudio из оригинального GTA2.exe (адреса sub_4105xx):
//   Initialise - инициализация аудио-системы (SoundCard::InitializeAudioSystem),
//   AddAudioObject - создание звукового объекта по типу (2 = 2D), возвращает "частоту",
//   FreeSample - установка частоты дискретизации,
//   PollAllSamples - обновление каждый кадр (фронтенд вызывает при !skip_audio).
// Само воспроизведение делает движок gSound (Engine\Sound, WinAPI waveOut) -
// замена Miles Sound System, которой в сборке нет.
//
// Глобальные флаги:
//   skip_audio  - выключить весь звук (глобальный флаг оригинала; фронтенд
//                 вызывает DMAudio::PollAllSamples только при !skip_audio),
//   gSampleRate - "частота" звукового объекта (в оригинале сюда ложился слот
//                 объекта, созданного в AddAudioObject - имя поля осталось).

#include "../Registry/Registry.h"
#include "DMAudio.h"
#include "../Sound/Sound.h"

DMAudio gDMAudio;


int  skip_audio;   // 0 = звук включён
int  gSampleRate;  // результат создания звукового объекта (см. суб_410530)

// Инициализация аудио-системы (аналог DMAudio::Initialise: создаёт SoundCard и
// аудио-объект, если его ещё нет). Движок gSound проверяет доступность волны.
void DMAudio::InitAudioManager()
{
	if (!gSound.InitAudioSystem())
		skip_audio = 1;
}

void DMAudio::InitAudioManager3D()
{
	InitAudioManager();
	gSound.Sound3D = true;
}

void DMAudio::SetCDVol(char CDvol)
{
	this->_CDvol = CDvol;
}

void DMAudio::SetSFXVol(char SFXVol)
{
	this->_SFXVol = SFXVol;
	gSound.SetVolume(SFXVol);
}

// Включение/выключение 3D-звука. У нас 3D нет - только фиксируем запрос
// (в оригинале тут Init3DAudioWithDirectSound и откат на 2D при неудаче).
void DMAudio::Init3DSound(int Vol3D)
{
	bool want = (Vol3D != 0);
	if (gSound.Sound3D == want)
		return;
	gSound.Sound3D = want;
	gRegistry->SetSound3DConfigure("do_3d_sound", (BYTE)gSound.Sound3D);
}

bool DMAudio::Get3DSound()
{
	return gSound.Sound3D;
}

// Закрытие аудио-системы (аналог DMAudio::IsInitialised: AIL_waveOutClose + release).
int DMAudio::IsInitialised()
{
	gSound.Shutdown();
	return 0;
}

// Создание звукового объекта: *pAudioObject = тип звука (2 - обычный 2D-звук,
// 1 - 3D). Возвращает "частоту дискретизации" созданного объекта (в оригинале -
// номер слота в AudioManager; игра кладёт его в gSampleRate).
int DMAudio::AddAudioObject(int* pAudioObject)
{
	if (!pAudioObject)
		return 0;
	gSound.InitAudioSystem();
	gSound.Sound3D = (*pAudioObject == 1);
	return 22050;
}

// Установка частоты дискретизации (оригинал: AudioManager::StopStream).
int DMAudio::FreeSample(int SampleRate)
{
	gSampleRate = SampleRate;
	return 0;
}

// Обновление аудио каждый кадр (оригинал: AudioManager::Update - перекачивает
// буферы/освобождает голоса). Вызывается фронтендом при !skip_audio.
int DMAudio::PollAllSamples()
{
	gSound.Update();
	return 0;
}