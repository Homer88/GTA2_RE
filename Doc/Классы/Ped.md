# Ped

- **Место**: `gta2/Game/Ped/`
- **Файлы**: `.cpp` 1769 строк, `.h` 604 строк
- **Методов**: 246
- **Полностью реализовано**: 7
- **Частично (TODO/незавершено)**: 0
- **Заглушки**: 209
- **Объявлено, но не определено**: 30
- **Реализация в целом: ~3%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `SetHealth(unsigned short Health)` | 80 | 4 |  |
| `GetActionParam()` | 185 | 4 |  |
| `GetCurrentAction()` | 194 | 4 |  |
| `IsPlayerControlled()` | 339 | 3 |  |
| `SetPoliceNoStar()` | 379 | 4 |  |
| `SetPoliceStarLevel(unsigned short CopLevel)` | 788 | 29 |  |
| `HealPed()` | 958 | 12 |  |

## Заглушки (мини-тела / return-заглушки)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `FindNearestPlayer()` | 8 | 3 |  |
| `SetSearchMode()` | 16 | 3 |  |
| `SetAIController()` | 24 | 3 |  |
| `SetAssignedCarIndex()` | 32 | 3 |  |
| `ClearFlags()` | 40 | 3 |  |
| `UpdateState()` | 48 | 3 |  |
| `SetCurrentOccupation()` | 56 | 3 |  |
| `GetOccupation()` | 64 | 3 |  |
| `GetCurrentState()` | 72 | 3 |  |
| `SetTargetCarDoorIndex()` | 89 | 3 |  |
| `GetFlags1()` | 97 | 3 |  |
| `GetFlags2()` | 105 | 3 |  |
| `GetDamageState()` | 113 | 3 |  |
| `GetSub_4039F0()` | 121 | 3 |  |
| `GetPositionX()` | 129 | 3 |  |
| `GetPositionY()` | 137 | 3 |  |
| `ResetSpecialParam()` | 145 | 3 |  |
| `ResetToDefaults()` | 153 | 3 |  |
| `SetFlags()` | 161 | 3 |  |
| `GetAnimationState()` | 169 | 3 |  |
| `SetAnimationState()` | 177 | 3 |  |
| `EnterCar()` | 203 | 3 |  |
| `SetAsDriver()` | 211 | 3 |  |
| `GetPassenger()` | 219 | 3 |  |
| `SetLinkedPedestrian()` | 227 | 3 |  |
| `SetTargetVehicle()` | 235 | 3 |  |
| `GetCurrentCar()` | 243 | 3 |  |
| `GetCarStateTimer()` | 251 | 3 |  |
| `GetActionState()` | 259 | 3 |  |
| `SetVehicleDamageState()` | 267 | 3 |  |
| `SetExitAnimationState()` | 275 | 3 |  |
| `GetDeadPed()` | 283 | 3 |  |
| `GetExitAnimState()` | 291 | 3 |  |
| `IsInsideVehicle()` | 299 | 3 |  |
| `GetStance()` | 307 | 3 |  |
| `GetPositionZ()` | 315 | 3 |  |
| `GetCarPlayers()` | 323 | 3 |  |
| `GetPosition()` | 331 | 3 |  |
| `GetAndResetFlag()` | 347 | 3 |  |
| `GetMissionThreadId()` | 355 | 3 |  |
| `GetIdPlayer()` | 363 | 3 |  |
| `GetSearchType()` | 371 | 3 |  |
| `CarSystemManager_SelectTraffic()` | 388 | 3 |  |
| `GetOccupationPolice()` | 396 | 3 |  |
| `Set_4331D0()` | 404 | 3 |  |
| `IsCriminal()` | 412 | 3 |  |
| `RemoveGameObject()` | 420 | 3 |  |
| `SpawnMarker()` | 428 | 3 |  |
| `TransitionState()` | 436 | 3 |  |
| `SetState()` | 444 | 3 |  |
| `IsSearchingPlayer()` | 452 | 3 |  |
| `HasSearchType()` | 460 | 3 |  |
| `SetOccupationAGENT()` | 468 | 3 |  |
| `IsTileRoad()` | 476 | 3 |  |
| `HasArrowYMinus()` | 484 | 3 |  |
| `IsTileSolid()` | 492 | 3 |  |
| `HasArrowYPlus()` | 500 | 3 |  |
| `HasArrowXMinus()` | 508 | 3 |  |
| `HasBidirectionalArrow()` | 516 | 3 |  |
| `ProcessCommand()` | 524 | 3 |  |
| `SetIdleAction()` | 532 | 3 |  |
| `Get_433B40()` | 540 | 3 |  |
| `DisableGameObject()` | 548 | 3 |  |
| `GetHealthPlayer()` | 556 | 3 |  |
| `SetParam()` | 564 | 3 |  |
| `GetRemap()` | 572 | 3 |  |
| `SetFlag()` | 580 | 3 |  |
| `SetGraphicType()` | 588 | 3 |  |
| `IncrementCounter()` | 596 | 3 |  |
| `SetLinkedPed()` | 604 | 3 |  |
| `SetRemap_0()` | 612 | 3 |  |
| `SetActionState()` | 620 | 3 |  |
| `GetOCcupationIsElvis()` | 628 | 3 |  |
| `GetPedFromSprite()` | 636 | 3 |  |
| `IsInAction()` | 644 | 3 |  |
| `GetPoliceStar()` | 652 | 3 |  |
| `SetNextAction()` | 660 | 3 |  |
| `ResetPedState()` | 668 | 3 |  |
| `UpdateIdleTimer()` | 676 | 3 |  |
| `ProcessCarDamage()` | 684 | 3 |  |
| `GetCarSearchRange()` | 692 | 3 |  |
| `UpdateRecovery()` | 700 | 3 |  |
| `ProcessAI()` | 708 | 3 |  |
| `GetInCar()` | 716 | 3 |  |
| `StopAtObstacle()` | 724 | 3 |  |
| `ReleaseCarriedPed()` | 732 | 3 |  |
| `StopCarryingPed()` | 740 | 3 |  |
| `StartCarExit()` | 748 | 3 |  |
| `MakeCarDriveable()` | 756 | 3 |  |
| `StartExitAnim()` | 764 | 3 |  |
| `GetSprite()` | 772 | 3 |  |
| `GetCopStars()` | 780 | 3 |  |
| `HandleWantedEvent()` | 822 | 3 |  |
| `GetCombatWeapon()` | 830 | 3 |  |
| `GetCopWeapon()` | 838 | 3 |  |
| `UpdateGangRespect()` | 846 | 3 |  |
| `UpdateWantedLevel()` | 854 | 3 |  |
| `GroupChangeLeader()` | 862 | 3 |  |
| `ReleasePedFromPlayer()` | 870 | 3 |  |
| `IsInTrain()` | 878 | 3 |  |
| `BasicCleanup()` | 886 | 3 |  |
| `CleanupAndUpdateOccupationCounts()` | 894 | 3 |  |
| `SetPedTeleportTarget()` | 902 | 3 |  |
| `ProcessDamage()` | 910 | 3 |  |
| `EnableInvisibility()` | 918 | 3 |  |
| `DisableInvisibility()` | 926 | 3 |  |
| `SetSpriteFlags()` | 934 | 3 |  |
| `ClearCarDoorTarget()` | 942 | 3 |  |
| `SetSpriteDoorFlag()` | 950 | 3 |  |
| `CreatePlayer()` | 975 | 3 |  |
| `PutPedInCarRelated()` | 983 | 3 |  |
| `SetPedPosition()` | 991 | 3 |  |
| `SetDoubleDamage()` | 999 | 3 |  |
| `DropWeaponPickup()` | 1007 | 3 |  |
| `FaceTargetPosition()` | 1015 | 3 |  |
| `RemoveActiveWeapon()` | 1023 | 3 |  |
| `RemoveSpareWeapon()` | 1031 | 3 |  |
| `UpdateSpriteDrawState()` | 1039 | 3 |  |
| `EngagePed()` | 1047 | 3 |  |
| `ShouldAttackPed()` | 1055 | 3 |  |
| `IsTargetInView()` | 1063 | 3 |  |
| `GetTargetPed()` | 1071 | 3 |  |
| `CheckObjectiveCar()` | 1079 | 3 |  |
| `ApplyKnockback()` | 1087 | 3 |  |
| `ProcessCollision()` | 1095 | 3 |  |
| `UpdateCarDamageState2()` | 1103 | 3 |  |
| `UpdateCarDamageState()` | 1111 | 3 |  |
| `ReleaseCarriedPedOnHit()` | 1119 | 3 |  |
| `UpdateCarriedPed()` | 1127 | 3 |  |
| `DragCarriedPed()` | 1135 | 3 |  |
| `ProcessEnterCar()` | 1143 | 3 |  |
| `AbortEnterCar()` | 1151 | 3 |  |
| `MoveToTarget()` | 1159 | 3 |  |
| `WalkToTarget()` | 1167 | 3 |  |
| `ProcFollowPath()` | 1175 | 3 |  |
| `ProcCrossRoad()` | 1183 | 3 |  |
| `ProcCrossStreet1()` | 1191 | 3 |  |
| `ProcCrossStreet2()` | 1199 | 3 |  |
| `ProcCrossStreet3()` | 1207 | 3 |  |
| `ProcCrossStreet4()` | 1215 | 3 |  |
| `ProcBoardTrain()` | 1223 | 3 |  |
| `ProcChasePlayer()` | 1231 | 3 |  |
| `GetCopLevel()` | 1239 | 3 |  |
| `GiveWeapon()` | 1247 | 3 |  |
| `CopyPed()` | 1255 | 3 |  |
| `ReleaseCarDoor()` | 1263 | 3 |  |
| `PlacePedOnTile()` | 1271 | 3 |  |
| `PlayRandomGesture(int arg0)` | 1279 | 3 |  |
| `ProcSpawnTrainRider()` | 1287 | 3 |  |
| `CleanupPed()` | 1295 | 3 |  |
| `SetObjective()` | 1303 | 3 |  |
| `SetRampageCriminal()` | 1311 | 3 |  |
| `AreAnyPedActive()` | 1319 | 3 |  |
| `ProcGetInCar()` | 1327 | 3 |  |
| `ProcEnterCar()` | 1335 | 3 |  |
| `SetNPCWeapon()` | 1343 | 3 |  |
| `ReportKill()` | 1351 | 3 |  |
| `PlacePed()` | 1359 | 3 |  |
| `EnterCarAsPassenger()` | 1367 | 3 |  |
| `ComputeFacingRotation()` | 1375 | 3 |  |
| `CleanUp()` | 1383 | 3 |  |
| `ProcMugger()` | 1391 | 3 |  |
| `ProcTrainAgent()` | 1399 | 3 |  |
| `ProcCop()` | 1407 | 3 |  |
| `AbandonVehicle()` | 1415 | 3 |  |
| `SearchForPed()` | 1423 | 3 |  |
| `SyncWithGameObject()` | 1431 | 3 |  |
| `ProcessCombat()` | 1439 | 3 |  |
| `ProcessCar()` | 1447 | 3 |  |
| `ProcGetOnPublicTransport()` | 1455 | 3 |  |
| `CopyPedAttributes()` | 1463 | 3 |  |
| `GroupCreate()` | 1471 | 3 |  |
| `KillPed()` | 1479 | 3 |  |
| `TakeDamage()` | 1487 | 3 |  |
| `HandleDamage()` | 1495 | 3 |  |
| `ResetPed()` | 1503 | 3 |  |
| `ProcCarThief()` | 1511 | 3 |  |
| `ProcTaxiPassenger()` | 1519 | 3 |  |
| `ProcBusPassenger()` | 1527 | 3 |  |
| `ProcDriver()` | 1535 | 3 |  |
| `ProcessByOccupation()` | 1543 | 3 |  |
| `ProcessByState()` | 1551 | 3 |  |
| `ProcAttackTarget()` | 1559 | 3 |  |
| `ProcExitCar()` | 1567 | 3 |  |
| `ProcExitToTaxi()` | 1575 | 3 |  |
| `ProcWalk()` | 1583 | 3 |  |
| `ProcWalkIdle()` | 1591 | 3 |  |
| `ProcWalkPlayer()` | 1599 | 3 |  |
| `ProcWalkArea()` | 1607 | 3 |  |
| `CreateGroup()` | 1615 | 3 |  |
| `ProcDie()` | 1623 | 3 |  |
| `PunchPed()` | 1631 | 3 |  |
| `ProcessByAction()` | 1639 | 3 |  |
| `ProcGunCombat()` | 1647 | 3 |  |
| `Process()` | 1655 | 3 |  |
| `ProcessStateAction()` | 1663 | 3 |  |
| `Tick()` | 1671 | 3 |  |
| `GetNearestPassenger()` | 1679 | 3 |  |
| `getCarDamageState()` | 1687 | 3 |  |
| `IsCarIndexUnassigned()` | 1695 | 3 |  |
| `SetupTrace()` | 1703 | 3 |  |
| `SetMoneyValue()` | 1711 | 3 |  |
| `SetZone()` | 1719 | 3 |  |
| `IsTargetCarDoor()` | 1727 | 3 |  |
| `SetHealthFullPlayer()` | 1735 | 3 |  |
| `SetStatusFlag()` | 1743 | 3 |  |
| `SetCar()` | 1751 | 3 |  |
| `SetCar2()` | 1759 | 3 |  |
| `ShowMessageToPlayer()` | 1767 | 3 |  |

## Объявлены в .h, но не определены

- `AppendActionKeys()`
- `CheckStandingSurface()`
- `ClearTarget()`
- `EnterAsPassenger()`
- `EnterCarDoor()`
- `FetchActionState()`
- `FindCarToEnter()`
- `GetCarAngle()`
- `GetCarDoorPed()`
- `GetCarIndex()`
- `GetCarPosZ()`
- `GetCarYaw()`
- `GetGroundContactFlags()`
- `IsBlockedBySprite()`
- `IsCarDoorOccupied()`
- `IsCarried()`
- `IsInCarSeat()`
- `IsPathBlocked()`
- `IsSamePlayer()`
- `IsVisibleToPlayer()`
- `PlacePedAtPosition()`
- `SetActionParam()`
- `SetActionParam2()`
- `SetActionParam3()`
- `SetAiCheckCar()`
- `SetAiCheckCarChase()`
- `SetCarSpeed()`
- `SpawnPedGroup()`
- `SpawnPedGroupFour()`
- `UpdateFacing()`
