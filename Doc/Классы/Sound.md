# Sound

- **Место**: `gta2/Engine/Sound/`
- **Файлы**: `.cpp` 591 строк, `.h` 104 строк
- **Методов**: 15
- **Полностью реализовано**: 14
- **Частично (TODO/незавершено)**: 0
- **Заглушки**: 1
- **Объявлено, но не определено**: 0
- **Реализация в целом: ~93%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `Sound()` | 25 | 10 |  |
| `InitAudioSystem()` | 43 | 14 |  |
| `Shutdown()` | 58 | 8 |  |
| `LoadBank(const char* name)` | 68 | 63 |  |
| `GetSampleInfo(int index, int& size, int& rate, int& loopStart, int& loopEnd)` | 132 | 11 |  |
| `FindFreeVoice()` | 145 | 7 |  |
| `WaveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwUser,
	                                 DWORD_PTR dwParam1, DWORD_PTR dwParam2)` | 161 | 33 | 0xFFFFFFFF |
| `SweepFinished()` | 197 | 18 |  |
| `PlaySample(int index, bool loop)` | 216 | 83 | 0xFFFFFFFF |
| `PlayPcm(const std::vector<short>& pcm, int rate)` | 300 | 54 |  |
| `StopAll()` | 355 | 19 |  |
| `IsPlaying()` | 375 | 7 |  |
| `SetVolume(char vol)` | 383 | 12 |  |
| `WavToPcm(const char* path, std::vector<short>& pcm, int& rate)` | 471 | 121 | 0x20746D66 |

## Заглушки (мини-тела / return-заглушки)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `Update()` | 396 | 6 |  |
