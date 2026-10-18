# Car

- **Место**: `gta2/Game/Car/`
- **Файлы**: `.cpp` 278 строк, `.h` 496 строк
- **Размер структуры**: 0xB8 (184 байта), ~75% полей осмысленных (см. `Doc/Car/layouts.txt`)
- **Методов**: 139
- **Полностью реализовано**: 32
- **Частично (TODO/незавершено)**: 0
- **Заглушки**: 9
- **Объявлено, но не определено**: 98
- **Реализация в целом: ~23%** (полные + 0.5*частичные)
- **В бинаре gta2.exe**: 296 методов `Car::` (для сравнения)
- **Деструктор**: `~Car()` реализован (Car.cpp:21, обнуляет `LastCar`)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `Car::Car()` | 17 | 3 | 0x004267B0 |
| `void Car::AddRoofGun()` | 44 | 5 | 0x0041FDF0 |
| `int Car::SetTrafficCarType(void *param1 )` | 60 | 3 | 0x00424630 |
| `short Car::CollisionOnCar(int Damage)` | 68 | 8 | 0x00427180 |
| `bool Car::GetFullDamage()` | 80 | 3 | 0x0040F890 |
| `void * Car::GetEngineData(int pararm)` | 84 | 3 | 0x0041F730 |
| `bool Car::IsDriverPlayer()` | 95 | 5 | 0x004118D0 |
| `bool Car::isFileTruck()` | 102 | 3 | 0x004118F0 |
| `bool Car::isGunJeep()` | 106 | 3 | 0x00411910 |
| `bool Car::isTank()` | 110 | 3 | 0x00411900 |
| `bool Car::IsTrainOrTrainCarriage()` | 116 | 7 | 0x00403BA0 |
| `char Car::UpdateDamageCooldown()` | 130 | 10 | 0x004209F0 |
| `void Car::SetMask()` | 143 | 7 | 0x004215F0 |
| `void Car::SetHornDefault()` | 151 | 3 | 0x00421460 |
| `bool Car::isEDSELFBI()` | 155 | 3 | 0x00411920 |
| `int Car::GetCarModel()` | 160 | 3 | 0x00411940 |
| `bool Car::isCopCar()` | 165 | 6 | 0x00421790 |
| `bool Car::isMask7()` | 174 | 3 | 0x004214D0 |
| `bool Car::isMedicCar()` | 180 | 3 | 0x00421780 |
| `bool Car::isSWATVAN()` | 185 | 3 | 0x004217A0 |
| `bool Car::isGT24640()` | 190 | 3 | 0x004217D0 |
| `bool Car::isTVVAN()` | 195 | 3 | 0x004217E0 |
| `Player* Car::GetPlayer()` | 201 | 3 | 0x00421870 |
| `void Car::SetSound( int a2)` | 205 | 4 | 0x00421950 |
| `char Car::HandleMaskTransition()` | 210 | 19 | 0x004241C0 |
| `void Car::isMask4()` | 234 | 6 | 0x00421470 |
| `void Car::isMask3()` | 241 | 5 | 0x00421490 |
| `bool Car::isMask()` | 247 | 6 | 0x004214B0 |
| `bool Car::isJeep()` | 255 | 4 | 0x004217B0 |
| `bool Car::isAPC()` | 260 | 4 | 0x004217C0 |
| `bool Car::isTaxi()` | 265 | 6 | 0x004217F0 |
| `void* Car::GetInfoByTypeCar()` | 274 | 5 | 0x0041F700 |

## Заглушки (пустые тела)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `void Car::DestroyAllTurrets()` | 27 | 2 | 0x004BF000 |
| `void Car::sub_421460()` | 31 | 2 | 0x00421460 |
| `void Car::Reset()` | 34 | 2 |  |
| `void Car::AddRoofAntenna()` | 39 | 2 | 0x00425FD0 |
| `void Car::AddRoofTankTurret()` | 52 | 2 | 0x0041FDA0 |
| `void Car::AddRoofWaterGun()` | 56 | 2 | 0x0041FD50 |
| `void Car::ChangeTrafficType(void *param1 )` | 64 | 2 | 0x00420840 |
| `void Car::ExplodeCar(int a)` | 90 | 2 | 0x00426FA0 |
| `void Car::SetPosition(int X, int Y, int Z)` | 124 | 2 | 0x004207F0 |

`sub_421460` — устаревший дубль `SetHornDefault` (одна и та же функция бинаря 0x00421460, в .h объявлены оба: строки 209 и 232); `Reset` — адрес в дампе не установлен (функция отсутствует в gta2.exe под этим именем, тело пустое).

## Объявлено в .h, без определения в .cpp (98)

| метод | строка в .h |
|---|---|
| `void Repair() {}` | 233 |
| `void ConsumePendingEvent0xac()` | 245 |
| `int IsCarState4()` | 248 |
| `void ConsumePendingEvent0xb4()` | 251 |
| `int IsObjectAttached()` | 254 |
| `int IsMySprite()` | 257 |
| `void EncodePositionValue(int param_1)` | 260 |
| `void EncodeCoord16(unsigned int param_1)` | 263 |
| `int GetCarSpritePtr()` | 266 |
| `void ScaleTurretAndPassengers(int* param_1)` | 269 |
| `void ClearFlag2000()` | 272 |
| `void GetField0x60()` | 280 |
| `void GetEventFlag()` | 282 |
| `void GetField0x84()` | 284 |
| `void GetField0x88()` | 286 |
| `void IsIdleStopped()` | 288 |
| `void HasAttachmentAt0x84()` | 290 |
| `void GetField0x24()` | 292 |
| `void GetField0x28()` | 294 |
| `void IsTimerElapsed()` | 296 |
| `void GetVelocity()` | 298 |
| `void SetField74()` | 300 |
| `void GetSpeedPair()` | 302 |
| `void ClearFieldAD()` | 304 |
| `void SetHazardLights()` | 306 |
| `void SetIndicatorLeft()` | 308 |
| `void SetIndicatorRight()` | 310 |
| `void SetFieldA6()` | 312 |
| `void GetEngineSoundValue()` | 314 |
| `void GetScreenPosition()` | 316 |
| `void GetCarName()` | 318 |
| `void GetScreenPositionOffset()` | 320 |
| `void GetDisplayValue()` | 322 |
| `void GetRemapColor()` | 324 |
| `void RandomRemap()` | 326 |
| `void IndicatorLeftOn()` | 328 |
| `void IndicatorRightOn()` | 330 |
| `void CheckLineOfSight()` | 332 |
| `void ApplySteeringInput()` | 334 |
| `void UpdateCarLights()` | 336 |
| `void AddDrivenCar()` | 338 |
| `void AddTrafficCar()` | 340 |
| `void CanPedEnterCar()` | 342 |
| `void ShouldRemoveCar()` | 344 |
| `void GetEngineState()` | 346 |
| `void CanBeDrivenByPed()` | 348 |
| `void SetBrakingOn()` | 350 |
| `void SetBrakingOff()` | 352 |
| `void ResetInput()` | 354 |
| `void SetStateOne()` | 356 |
| `void SetStateTwo()` | 358 |
| `void ClearStateFlags()` | 360 |
| `void IsFlag1()` | 362 |
| `void IsFlag2()` | 364 |
| `void IsFlag4()` | 366 |
| `void IsFlag8()` | 368 |
| `void IsFlag32()` | 370 |
| `void SetFlag1()` | 372 |
| `void SetFlag2()` | 374 |
| `void SetFlag4()` | 376 |
| `void ClearFlag1()` | 378 |
| `void ClearFlagBit1()` | 380 |
| `void ClearFlag4()` | 382 |
| `void ClearFlag8()` | 384 |
| `void DecideTurnDirection()` | 386 |
| `void UpdateTrafficControl()` | 388 |
| `void SetAlarmTimer()` | 390 |
| `void IsValidParkingVehicle()` | 392 |
| `void IsSpecialModel()` | 394 |
| `void SetLocksDoor5()` | 396 |
| `void SetFlag80()` | 398 |
| `void SetFlag200()` | 400 |
| `void ClearFlag100()` | 402 |
| `void ClearFlag200()` | 404 |
| `void ClearFlag400()` | 406 |
| `void SetLightMode()` | 408 |
| `void CheckDoorEntry()` | 410 |
| `void GetTurretWeaponIndex()` | 412 |
| `void AddTurret()` | 414 |
| `int GetField0x9c()` | 436 |
| `int GetSpawnPoint()` | 439 |
| `int GetCarValue(int arg0)` | 442 |
| `int HasDriver(int arg0)` | 445 |
| `void UpdateDoors()` | 448 |
| `void SpawnAttachedObject(int arg1)` | 451 |
| `void DeactivateTrafficCar()` | 454 |
| `void HornOff(int arg0)` | 457 |
| `int CheckPlayerDriveable(int arg0)` | 460 |
| `void SirenOn()` | 463 |
| `void SirenPhase1(int arg0)` | 466 |
| `void SirenPhase2(int arg0)` | 469 |
| `void SirenPhase3(int arg0)` | 472 |
| `void SirenPhase4(int arg0)` | 475 |
| `void UpdateSiren()` | 478 |
| `void UpdateSirenPhase(int arg0)` | 481 |
| `void UpdateSecondaryLights(int arg0)` | 484 |
| `void FollowPath(int arg0)` | 487 |
| `void UpdateAI()` | 490 |

## Хуки-трейсеры (dllLoad)

- **296 observer-хуков** на все `Car::` из бинаря: `dllLoad/cCarTrace.h`, `dllLoad/cCarTrace.cpp` (сгенерированы `dump/scripts/gen_car_trace.py`)
- Подключение: `dllmain.cpp` (`DetourAttach(&_Car_XXXXXX, ...)`), выключается переменной окружения `GTA2_NOCARTRACE=1`
- Кольцевой буфер 32768 записей сбрасывается в `C:\games\gta2\car_trace.log` из фонового треда (каждые 2 с)
- Смещения полей: `Doc/Car/layouts.txt` (структура 0xB8); пересечений адресов с существующими DetourAttach нет (`Doc/check_car_overlap.py` — 0)
- **Статус**: собрано (MSBuild Win32 Release), задеплоено в `C:\games\gta2\gta2-resurection.dll`, проверено ин-гейм — 296 хуков отрабатывают, `self==0x0`: 0, крашей нет
