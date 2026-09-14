# SoundCard

- **Место**: `gta2/Engine/SoundCard/`
- **Файлы**: `.cpp` 512 строк, `.h` 127 строк
- **Методов**: 57
- **Полностью реализовано**: 1
- **Частично (TODO/незавершено)**: 0
- **Заглушки**: 56
- **Объявлено, но не определено**: 0
- **Реализация в целом: ~2%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `LoadSounds(char* baseName)` | 413 | 51 |  |

## Заглушки (мини-тела / return-заглушки)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `AcquireSampleHandle()` | 13 | 3 |  |
| `ReleaseSampleHandle()` | 21 | 3 |  |
| `ReleaseAllSampleHandles()` | 29 | 3 |  |
| `GetHZ()` | 37 | 3 |  |
| `GetSampleVolume()` | 45 | 3 |  |
| `GetSampleLoopA()` | 53 | 3 |  |
| `GetSampleLoopB()` | 61 | 3 |  |
| `GetSampleLength()` | 69 | 3 |  |
| `SetSampleAddress()` | 77 | 3 |  |
| `SetSampleVolume()` | 85 | 3 |  |
| `SetSamplePan()` | 93 | 3 |  |
| `SetSamplePlaybackRate()` | 101 | 3 |  |
| `SetSampleLoopBlock()` | 109 | 3 |  |
| `SetSampleLoopCount()` | 117 | 3 |  |
| `SoundCardIsSampleStopped()` | 125 | 3 |  |
| `StartSample()` | 133 | 3 |  |
| `StopSample()` | 141 | 3 |  |
| `SoundCardSet3DSampleInfo()` | 149 | 3 |  |
| `Set3DSampleVolume()` | 157 | 3 |  |
| `Set3DPosition()` | 165 | 3 |  |
| `SoundCardSet3DSampleDistances()` | 173 | 3 |  |
| `Set3DSamplePlaybackRate()` | 181 | 3 |  |
| `Set3DSampleLoopBlock()` | 189 | 3 |  |
| `Set3DSampleLoopCount()` | 197 | 3 |  |
| `Is3DSampleStopped()` | 205 | 3 |  |
| `Start3DSample()` | 213 | 3 |  |
| `CheckAndStop3DSample()` | 221 | 3 |  |
| `SetEAXEnvironment()` | 229 | 3 |  |
| `Open3DProviderForListener()` | 237 | 3 |  |
| `Shutdown3DAudio()` | 245 | 3 |  |
| `Enumerate3DAudioProviders()` | 253 | 3 |  |
| `ReacquireStream()` | 261 | 3 |  |
| `StreamStatus()` | 269 | 3 |  |
| `SetStreamVolume()` | 277 | 3 |  |
| `SoundCardOpenStream()` | 285 | 3 |  |
| `CloseStream()` | 293 | 3 |  |
| `FadeOutAndCloseStream()` | 301 | 3 |  |
| `Get_isStreamActive()` | 309 | 3 |  |
| `CloseStreamByIndex()` | 317 | 3 |  |
| `SetStreamVolume_0()` | 325 | 3 |  |
| `AIL_set_stream_playback_rate()` | 333 | 3 |  |
| `AIL_stream_playback_rate()` | 341 | 3 |  |
| `SetStreamPosition()` | 349 | 3 |  |
| `GetStreamPosition()` | 357 | 3 |  |
| `SoundCardGetStreamLength()` | 365 | 3 |  |
| `SetSampleVolume_0()` | 373 | 3 |  |
| `SoundCardPlaySample()` | 381 | 3 |  |
| `GetSampleStatus()` | 389 | 3 |  |
| `PlayRandomSample()` | 397 | 3 |  |
| `EndSample()` | 405 | 3 |  |
| `InitializeAudioStream()` | 469 | 3 |  |
| `Reset3DAudioSystem()` | 477 | 3 |  |
| `ReinitializeAudioSystem()` | 485 | 3 |  |
| `CloseAudioSystem()` | 493 | 3 |  |
| `InitializeAudioSystem()` | 501 | 3 |  |
| `Initialize3DAudioWithDirectSound()` | 509 | 3 |  |
