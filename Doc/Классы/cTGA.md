# cTGA

- **Место**: `gta2/Engine/Res/`
- **Файлы**: `.cpp` 450 строк, `.h` 71 строк
- **Методов**: 15
- **Полностью реализовано**: 12
- **Частично (TODO/незавершено)**: 0
- **Заглушки**: 3
- **Объявлено, но не определено**: 0
- **Реализация в целом: ~80%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `cTGA()` | 4 | 10 |  |
| `Free()` | 20 | 12 |  |
| `IsCompressed()` | 58 | 6 |  |
| `Load(char *Filename)` | 65 | 112 |  |
| `Load16(FILE *fp)` | 178 | 35 |  |
| `LoadUncompressed(FILE *fp, long bytes_per_pixel)` | 214 | 19 |  |
| `LoadRLE(FILE *fp, long bytes_per_pixel)` | 234 | 48 |  |
| `LoadColormap(FILE *fp, WORD color_map_start, WORD color_map_length, BYTE color_map_bpp, BOOL rle)` | 283 | 44 |  |
| `Save(char *Filename)` | 328 | 50 |  |
| `FlipVertical()` | 379 | 22 |  |
| `FlipHorizontal()` | 402 | 20 |  |
| `ConvertTo32()` | 423 | 27 |  |

## Заглушки (мини-тела / return-заглушки)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `GetWidth()` | 33 | 4 |  |
| `GetHeight()` | 38 | 4 |  |
| `GetBPP()` | 43 | 4 |  |

## Свободные функции в .cpp (глобальные)

`GetData`, `GetPalette`
