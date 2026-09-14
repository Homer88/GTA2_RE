# Car

- **Место**: `gta2/Game/Car/`
- **Файлы**: `.cpp` 275 строк, `.h` 497 строк
- **Методов**: 137
- **Полностью реализовано**: 30
- **Частично (TODO/незавершено)**: 0
- **Заглушки**: 10
- **Объявлено, но не определено**: 97
- **Реализация в целом: ~22%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `AddRoofGun()` | 41 | 7 |  |
| `CollisionOnCar(int Damage)` | 65 | 11 |  |
| `GetFullDamage()` | 77 | 3 |  |
| `IsDriverPlayer()` | 92 | 6 |  |
| `isFileTruck()` | 99 | 3 |  |
| `isGunJeep()` | 103 | 3 |  |
| `isTank()` | 107 | 4 |  |
| `IsTrainOrTrainCarriage()` | 113 | 8 |  |
| `SetPosition(int X, int Y, int Z)` | 121 | 5 |  |
| `UpdateDamageCooldown()` | 127 | 12 |  |
| `SetMask()` | 140 | 7 |  |
| `SetHornDefault()` | 148 | 4 |  |
| `isEDSELFBI()` | 152 | 4 |  |
| `GetCarModel()` | 157 | 4 |  |
| `isCopCar()` | 162 | 8 |  |
| `isMask7()` | 171 | 4 |  |
| `isMedicCar()` | 177 | 4 |  |
| `isSWATVAN()` | 182 | 3 |  |
| `isGT24640()` | 187 | 4 |  |
| `isTVVAN()` | 192 | 4 |  |
| `GetPlayer()` | 198 | 4 |  |
| `SetSound(int a2)` | 202 | 4 |  |
| `HandleMaskTransition()` | 207 | 22 |  |
| `isMask4()` | 231 | 6 |  |
| `isMask3()` | 238 | 5 |  |
| `isMask()` | 244 | 7 |  |
| `isJeep()` | 252 | 4 |  |
| `isAPC()` | 257 | 4 |  |
| `isTaxi()` | 262 | 7 |  |
| `GetInfoByTypeCar()` | 271 | 5 |  |

## Заглушки (мини-тела / return-заглушки)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `DestroyAllTurrets()` | 24 | 3 |  |
| `sub_421460()` | 28 | 3 |  |
| `Reset()` | 31 | 3 |  |
| `AddRoofAntenna()` | 36 | 3 |  |
| `AddRoofTankTurret()` | 49 | 3 |  |
| `AddRoofWaterGun()` | 53 | 3 |  |
| `SetTrafficCarType(void*)` | 57 | 3 |  |
| `ChangeTrafficType(void*)` | 61 | 3 |  |
| `GetEngineData(int param)` | 81 | 5 |  |
| `ExplodeCar(int a)` | 87 | 3 |  |

## Объявлены в .h, но не определены

- `AddDrivenCar()`
- `AddTrafficCar()`
- `AddTurret()`
- `ApplySteeringInput()`
- `CanBeDrivenByPed()`
- `CanPedEnterCar()`
- `CheckDoorEntry()`
- `CheckLineOfSight()`
- `CheckPlayerDriveable(int arg0)`
- `ClearFieldAD()`
- `ClearFlag1()`
- `ClearFlag100()`
- `ClearFlag200()`
- `ClearFlag2000()`
- `ClearFlag4()`
- `ClearFlag400()`
- `ClearFlag8()`
- `ClearFlagBit1()`
- `ClearStateFlags()`
- `ConsumePendingEvent0xac()`
- `ConsumePendingEvent0xb4()`
- `DeactivateTrafficCar()`
- `DecideTurnDirection()`
- `EncodeCoord16(unsigned int param_1)`
- `EncodePositionValue(int param_1)`
- `FollowPath(int arg0)`
- `GetCarName()`
- `GetCarSpritePtr()`
- `GetCarValue(int arg0)`
- `GetDisplayValue()`
- `GetEngineSoundValue()`
- `GetEngineState()`
- `GetEventFlag()`
- `GetField0x24()`
- `GetField0x28()`
- `GetField0x60()`
- `GetField0x84()`
- `GetField0x88()`
- `GetField0x9c()`
- `GetRemapColor()`
- `GetScreenPosition()`
- `GetScreenPositionOffset()`
- `GetSpawnPoint()`
- `GetSpeedPair()`
- `GetTurretWeaponIndex()`
- `GetVelocity()`
- `HasAttachmentAt0x84()`
- `HasDriver(int arg0)`
- `HornOff(int arg0)`
- `IndicatorLeftOn()`
- `IndicatorRightOn()`
- `IsCarState4()`
- `IsFlag1()`
- `IsFlag2()`
- `IsFlag32()`
- `IsFlag4()`
- `IsFlag8()`
- `IsIdleStopped()`
- `IsMySprite()`
- `IsObjectAttached()`
- `IsSpecialModel()`
- `IsTimerElapsed()`
- `IsValidParkingVehicle()`
- `RandomRemap()`
- `ResetInput()`
- `ScaleTurretAndPassengers(int* param_1)`
- `SetAlarmTimer()`
- `SetBrakingOff()`
- `SetBrakingOn()`
- `SetField74()`
- `SetFieldA6()`
- `SetFlag1()`
- `SetFlag2()`
- `SetFlag200()`
- `SetFlag4()`
- `SetFlag80()`
- `SetHazardLights()`
- `SetIndicatorLeft()`
- `SetIndicatorRight()`
- `SetLightMode()`
- `SetLocksDoor5()`
- `SetStateOne()`
- `SetStateTwo()`
- `ShouldRemoveCar()`
- `SirenOn()`
- `SirenPhase1(int arg0)`
- `SirenPhase2(int arg0)`
- `SirenPhase3(int arg0)`
- `SirenPhase4(int arg0)`
- `SpawnAttachedObject(int arg1)`
- `UpdateAI()`
- `UpdateCarLights()`
- `UpdateDoors()`
- `UpdateSecondaryLights(int arg0)`
- `UpdateSiren()`
- `UpdateSirenPhase(int arg0)`
- `UpdateTrafficControl()`
