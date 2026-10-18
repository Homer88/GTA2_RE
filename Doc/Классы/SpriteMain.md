# SpriteMain

- **Место**: `gta2/Engine/SpriteMain/`
- **Файлы**: `.cpp` 128 строк, `.h` 54 строк
- **Методов**: 18
- **Полностью реализовано**: 1
- **Частично (TODO/незавершено)**: 0
- **Заглушки**: 12
- **Объявлено, но не определено в .cpp**: 5
- **Реализация в целом: ~6%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `void SpriteMain::SetPosition(int x, int y, int z)` | 37 | 5 |  |

## Заглушки (однострочные / return-заглушки)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `int SpriteMain::SetPosition(void)` | 32 | 3 |  |
| `int SpriteMain::SetRotation(void)` | 46 | 3 | 0x00420690 |
| `int SpriteMain::SetFrame(void)` | 54 | 3 | 0x004206C0 |
| `int SpriteMain::SetType(void)` | 62 | 3 | 0x004206F0 |
| `int SpriteMain::SetCar(void)` | 70 | 3 | 0x00420710 |
| `int SpriteMain::SetObject(void)` | 78 | 3 | 0x00483E50 |
| `int SpriteMain::ResetState(void)` | 86 | 3 | 0x004B99F0 |
| `int SpriteMain::SetSize(void)` | 94 | 3 | 0x004BAB10 |
| `int SpriteMain::DrawArrow(void)` | 102 | 3 | 0x004BCB40 |
| `int SpriteMain::Draw(void)` | 110 | 3 | 0x004BD290 |
| `int SpriteMain::CopySpriteData(void)` | 118 | 3 | 0x004BDDB0 |
| `int SpriteMain::DrawSprite(void)` | 126 | 3 | 0x004BDEF0 |

## Объявлено в .h, без определения в .cpp (5)

| метод | строка в .h |
|---|---|
| `void HasGameObject()` | 42 |
| `void IsOnMapTile()` | 44 |
| `void AddToVisibleList()` | 46 |
| `void GetRenderCoords()` | 48 |
| `void MergeDrawSortKey()` | 50 |
