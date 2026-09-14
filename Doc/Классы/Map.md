# Map

- **Место**: `gta2/Engine/Map/`
- **Файлы**: `.cpp` 135 строк, `.h` 54 строк
- **Методов**: 12
- **Полностью реализовано**: 10
- **Частично (TODO/незавершено)**: 0
- **Заглушки**: 2
- **Объявлено, но не определено**: 0
- **Реализация в целом: ~83%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `Map()` | 6 | 7 |  |
| `GetMapCellPtr(int a2, int a3)` | 18 | 4 |  |
| `GridAt(int x, int y)` | 27 | 4 |  |
| `GetGridTile(int x, int y)` | 36 | 4 |  |
| `SetGridTile(int x, int y, int tileIndex)` | 45 | 4 |  |
| `GetTileMinHeight(int tileIndex)` | 54 | 4 |  |
| `GetTileMaxHeight(int tileIndex)` | 63 | 4 |  |
| `FindTileForMaxZ(int x, int y, int* outZ = 0)` | 73 | 25 |  |
| `GetTileDataRef(int tileIndex, int zLevel)` | 103 | 6 |  |
| `GetTileData(int dataRef)` | 114 | 4 |  |

## Заглушки (мини-тела / return-заглушки)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `GetTileCount()` | 123 | 4 |  |
| `GetTileDataCount()` | 132 | 4 |  |
