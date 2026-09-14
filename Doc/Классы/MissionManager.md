# MissionManager

- **Место**: `gta2/Game/MissionManager/`
- **Файлы**: `.cpp` 1214 строк, `.h` 189 строк
- **Методов**: 61
- **Полностью реализовано**: 23
- **Частично (TODO/незавершено)**: 0
- **Заглушки**: 23
- **Объявлено, но не определено**: 15
- **Реализация в целом: ~38%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `MissionManagerDes()` | 110 | 1 |  |
| `MissionManager_Des(char a2)` | 113 | 7 |  |
| `FindByName(const char* a2)` | 189 | 14 |  |
| `GetMissionStatus()` | 215 | 4 |  |
| `sub_475A40(char a2)` | 223 | 4 |  |
| `ExtractFileNameWithoutExtension()` | 289 | 23 |  |
| `StartMission(unsigned __int16 a2)` | 416 | 7 |  |
| `sub_476240(int a2, int a3)` | 427 | 12 |  |
| `AddRuntimeTimer(int a2, int a3, __int16 a4)` | 443 | 18 |  |
| `FindData(int a2, int a3)` | 465 | 12 |  |
| `sub_476370(int a2, int a3, __int16 a4)` | 481 | 18 |  |
| `RemoveData(int a2, int a3)` | 503 | 12 |  |
| `FindDataById(int a2)` | 519 | 12 |  |
| `sub_47F230(__int16 a2, unsigned __int16 a3)` | 895 | 22 |  |
| `loadScript(char* ScriptName)` | 921 | 34 |  |
| `ActivateMissionTarget(int a2, int a3)` | 983 | 20 |  |
| `UnregisterTarget(int a2)` | 1007 | 7 |  |
| `StartNextMission()` | 1043 | 21 |  |
| `GetOpcodeParamType(unsigned int opcode)` | 1092 | 54 |  |
| `ListAddFront(void* node)` | 1150 | 6 |  |
| `SetCarFlag_0x8d()` | 1160 | 4 |  |
| `CheckMissionZone(unsigned int op, int x, int y)` | 1178 | 18 | 0x00466910 |
| `GiveWeaponOpcode(void* self)` | 1203 | 12 |  |

## Заглушки (мини-тела / return-заглушки)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `MissionManager_1()` | 160 | 6 |  |
| `FindMission(__int16 a2)` | 170 | 15 |  |
| `IsGameLoaded()` | 207 | 4 |  |
| `CopyMapDetails()` | 231 | 15 |  |
| `SetupMissionText(unsigned __int16 a2)` | 250 | 35 |  |
| `LoadLanguageFile(FileMgr* a2)` | 316 | 42 |  |
| `LoadScriptFiles()` | 362 | 50 |  |
| `AddOrCheckMissionTarget(int a2, char a3, char a4)` | 535 | 26 |  |
| `sub_4764D0(int a2, char a3)` | 565 | 33 |  |
| `UpdateMissionItem(int a2, int a3, char a4)` | 602 | 36 |  |
| `FindMissionItem(int a2, char a3, char a4)` | 642 | 17 |  |
| `sub_4799D0()` | 663 | 34 |  |
| `SetMissionGradeLetter(void* a1, void* a2)` | 701 | 23 |  |
| `sub_47EDB0(int a2)` | 728 | 24 |  |
| `BuildActiveMissionList()` | 756 | 26 |  |
| `RestoreMissionValues()` | 786 | 20 |  |
| `SaveFile(char* pSaveFileName)` | 810 | 36 |  |
| `LoadMissionMap(char* SaveFileName)` | 850 | 31 |  |
| `ContinueQueuedMissionLine(__int16 a3, char a2)` | 885 | 6 |  |
| `sub_47F340(int a2, int a3)` | 959 | 20 |  |
| `ClearMissionLineFlags()` | 1018 | 21 |  |
| `ProcessMissionQueue()` | 1068 | 20 |  |
| `PopViewport()` | 1168 | 4 |  |

## Объявлены в .h, но не определены

- `CheckCarAvailability()`
- `CheckGangWar()`
- `CheckMissionCondition()`
- `CheckMissionState()`
- `CheckPedInVehicle()`
- `DrawMissionGraphic()`
- `ExecuteArithmetic()`
- `GetMarkerSprite()`
- `GivePlayerMoney()`
- `IsMissionTarget()`
- `PlacePedInCar()`
- `ProcessAnimationEvent()`
- `SavePlayerMoney()`
- `SetPedDestination()`
- `SpawnRewardObject()`
