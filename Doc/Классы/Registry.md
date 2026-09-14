# Registry

- **Место**: `gta2/Engine/Registry/`
- **Файлы**: `.cpp` 476 строк, `.h` 45 строк
- **Методов**: 25
- **Полностью реализовано**: 25
- **Частично (TODO/незавершено)**: 0
- **Заглушки**: 0
- **Объявлено, но не определено**: 0
- **Реализация в целом: ~100%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `GetPlayReplay(LPCSTR lpValueName)` | 7 | 15 |  |
| `GetDebugMode(PHKEY phkResult)` | 23 | 50 |  |
| `SetDebugByteValue(LPCSTR lpValueName, BYTE value)` | 74 | 12 |  |
| `GetParamDebug(LPCSTR lpValueName)` | 89 | 14 |  |
| `GetReplayNum(LPCSTR lpValueName)` | 105 | 16 |  |
| `SetShowPlayerName(LPCSTR lpValueName, BYTE value)` | 124 | 17 |  |
| `GetNetworkKey(PHKEY phkResult)` | 142 | 19 |  |
| `ReadKeyMap(LPCSTR lpValueName, LPBYTE lpData, DWORD dataSize)` | 162 | 15 |  |
| `OpenOrCreateSoundKey(PHKEY phkResult)` | 180 | 15 |  |
| `ConfigureSoundSetting(LPCSTR lpValueName, BYTE value)` | 198 | 17 |  |
| `OpenOrCreateScreenKey(PHKEY phkResult)` | 216 | 15 |  |
| `ConfigVideo(LPCSTR lpValueName, BYTE value)` | 231 | 18 |  |
| `ConfigureSetScreen(LPCSTR lpValueName, BYTE value)` | 251 | 19 |  |
| `SetVideoName(LPCSTR lpValueName, LPBYTE lpData, DWORD dataSize)` | 273 | 16 |  |
| `GetSound3DConfigure(LPCSTR lpValueName)` | 294 | 15 |  |
| `SetSound3DConfigure(LPCSTR lpValueName, BYTE value)` | 311 | 16 |  |
| `SetConfigureWindowSize(LPCSTR lpValueName, BYTE Data)` | 328 | 12 |  |
| `OpenOrCreateTextKey(PHKEY phkResult)` | 341 | 14 |  |
| `SetTextConfig(LPCSTR lpValueName, BYTE value)` | 355 | 18 |  |
| `OpenOrCreateLanguageKey(PHKEY phkResult)` | 377 | 12 |  |
| `SetLanguage(LPCSTR lpValueName, BYTE Data)` | 389 | 19 |  |
| `GetLanguage(LPCSTR lpValueName, char* Data, int size)` | 408 | 19 |  |
| `OpenOrCreatePlayerName(PHKEY phkResult)` | 429 | 11 |  |
| `SetPlayerName(LPCSTR lpValueName, BYTE Data)` | 441 | 16 |  |
| `GetPlayerName(LPCSTR lpValueName, char* Data, int size)` | 457 | 20 |  |
