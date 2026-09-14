# MapGm

- **Место**: `gta2/Engine/MapGm/`
- **Файлы**: `.cpp` 199 строк, `.h` 183 строк
- **Методов**: 21
- **Полностью реализовано**: 6
- **Частично (TODO/незавершено)**: 0
- **Заглушки**: 3
- **Объявлено, но не определено**: 12
- **Реализация в целом: ~29%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `ResetSettings()` | 20 | 26 |  |
| `SetField23(char value)` | 50 | 5 |  |
| `SetString(unsigned short index, wchar_t* Source)` | 59 | 4 |  |
| `Get_45E7A0(unsigned short index)` | 67 | 4 |  |
| `GetScoreRow(unsigned char a2, unsigned char a3)` | 75 | 6 |  |
| `DecodeBonusStage(unsigned char bonusStage, unsigned char* playerArenaOut, unsigned char* out4)` | 179 | 5 |  |

## Заглушки (мини-тела / return-заглушки)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `LoadFileResurce()` | 85 | 60 |  |
| `LoadFromBuffer(void* player)` | 151 | 8 |  |
| `RegisterKill(unsigned char id, unsigned char a3)` | 164 | 11 |  |

## Объявлены в .h, но не определены

- `IsNotMode3()`
- `MapGm_GetBonusStage(MapGm*)`
- `MapGm_GetGang(MapGm*)`
- `MapGm_GetMapName(MapGm*)`
- `MapGm_GetPlayerArena(MapGm*)`
- `MapGm_GetPlayerSlotSave(MapGm*)`
- `MapGm_GetScriptName(MapGm*)`
- `MapGm_GetSpecialTokens(MapGm*)`
- `MapGm_GetStyleFile(MapGm*)`
- `MapGm_sub_45E700(MapGm*)`
- `SetAwardValue2()`
- `sub_476B10(MapGm*, int)`
