# WinApi

- **Место**: `gta2/Engine/ultil/`
- **Файлы**: `.cpp` 574 строк, `.h` 46 строк
- **Методов**: 18
- **Полностью реализовано**: 14
- **Частично (TODO/незавершено)**: 1
- **Заглушки**: 3
- **Объявлено, но не определено**: 0
- **Реализация в целом: ~81%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `Convertor_wchar_t_ToChar(wchar_t* Text)` | 56 | 12 |  |
| `CopyWideString(wchar_t* dest, wchar_t* source)` | 68 | 10 |  |
| `GetVersion(DWORD *pMajorVersion, DWORD *pMinorVersion)` | 80 | 50 |  |
| `InitTimer()` | 132 | 4 |  |
| `GetDebugParam()` | 137 | 95 |  |
| `AllGtxFile()` | 233 | 35 |  |
| `FindGraphicDevice()` | 269 | 15 |  |
| `DefautInitParam()` | 311 | 75 |  |
| `ConfigureVideoWindow()` | 389 | 43 |  |
| `SetShowCursor()` | 432 | 6 |  |
| `SetVideoPlayer()` | 439 | 35 | 0xffffffff |
| `SetGamma()` | 475 | 6 |  |
| `VideoCheck()` | 487 | 29 |  |
| `VideoCheck1()` | 519 | 48 |  |

## Частично реализованные (есть TODO/не завершены)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `ConfigureVideoDevice()` | 287 | 23 |  |

## Заглушки (мини-тела / return-заглушки)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `WinApi()` | 53 | 2 |  |
| `SetVideoGamma(int Gamma)` | 481 | 3 |  |
| `DirectInput2()` | 570 | 1 |  |
