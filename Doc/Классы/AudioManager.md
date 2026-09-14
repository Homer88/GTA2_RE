# AudioManager

- **Место**: `gta2/Engine/AudioManager/`
- **Файлы**: `.cpp` 850 строк, `.h` 261 строк
- **Методов**: 120
- **Полностью реализовано**: 3
- **Частично (TODO/незавершено)**: 0
- **Заглушки**: 100
- **Объявлено, но не определено**: 17
- **Реализация в целом: ~2%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `InitArray()` | 8 | 14 |  |
| `ExtractBaseName(char* FileName)` | 398 | 17 |  |
| `PlayStream(char* FileName)` | 508 | 7 |  |

## Заглушки (мини-тела / return-заглушки)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `DefauntParam()` | 23 | 3 |  |
| `SetupEngineRevSound()` | 30 | 3 |  |
| `PlayEngineSound()` | 38 | 3 |  |
| `SetupEngineAccelSound()` | 46 | 3 |  |
| `PlayEngineGearSound()` | 54 | 3 |  |
| `InitSoundInstance()` | 62 | 3 |  |
| `SetupCarEngineSound()` | 70 | 3 |  |
| `InitSoundInstance2()` | 78 | 3 |  |
| `InitSoundSample()` | 86 | 3 |  |
| `SetupCarSirenSound()` | 94 | 3 |  |
| `InitSoundSample2()` | 102 | 3 |  |
| `InitSoundSample3()` | 110 | 3 |  |
| `SetCarEmergencySound()` | 118 | 3 |  |
| `SetCarEngineSound()` | 126 | 3 |  |
| `SetCarIdleSound()` | 134 | 3 |  |
| `SetEngineSoundHz()` | 142 | 3 |  |
| `StartAmbientSound()` | 150 | 3 |  |
| `StopAmbientSound()` | 158 | 3 |  |
| `SetAmbientSound()` | 166 | 3 |  |
| `IsSoundInRange()` | 174 | 3 |  |
| `UpdateSoundVolume()` | 182 | 3 |  |
| `ComputeSoundScreenPos()` | 190 | 3 |  |
| `GetSoundId()` | 198 | 3 |  |
| `PlayRadio()` | 206 | 3 |  |
| `UpdateVehicleSound()` | 214 | 3 |  |
| `PlayWarningSound()` | 222 | 3 |  |
| `SetCarEngineSoundTurret()` | 230 | 3 |  |
| `PlayCarEngineSoundLocal()` | 238 | 3 |  |
| `SetCarEngineVoice()` | 246 | 3 |  |
| `SetCarEngineModelSound()` | 254 | 3 |  |
| `ComputeSoundIndexForCar()` | 262 | 3 |  |
| `UpdateCarSounds()` | 270 | 3 |  |
| `ProcessState4Sound(int arg0,int arg1)` | 278 | 3 |  |
| `PlayCarModelSound()` | 286 | 3 |  |
| `PlayVehicleEngineSound()` | 294 | 3 |  |
| `PlayCarSound()` | 302 | 3 |  |
| `SetEngineSoundByModel()` | 310 | 3 |  |
| `PlayEngineSoundValidated()` | 318 | 3 |  |
| `PlayIdleSound()` | 326 | 3 |  |
| `PlaySpecialSound1()` | 334 | 3 |  |
| `PlaySpecialSound2()` | 342 | 3 |  |
| `SetupCarSound()` | 350 | 3 |  |
| `HandleEventType()` | 358 | 3 |  |
| `ProcessEventList()` | 366 | 3 |  |
| `DispatchElementSfx()` | 374 | 3 |  |
| `ProcessElement()` | 382 | 3 |  |
| `Shutdown()` | 390 | 3 |  |
| `SetSFXVol()` | 420 | 3 |  |
| `IsInitialised()` | 428 | 3 |  |
| `GetRandomPitchOffset()` | 436 | 3 |  |
| `ResetElement()` | 444 | 3 |  |
| `AgeSoundElements()` | 452 | 3 |  |
| `AddChannel()` | 460 | 3 |  |
| `CalcSampleVolume()` | 468 | 3 |  |
| `SetSfxPosition()` | 476 | 3 |  |
| `ResetChannelSlots()` | 484 | 3 |  |
| `RefreshRandomSeeds()` | 492 | 3 |  |
| `StopStream()` | 500 | 3 |  |
| `ResetChannelLists()` | 520 | 3 |  |
| `CalcVolume()` | 528 | 3 |  |
| `Calc3DPan()` | 536 | 3 |  |
| `ProcessAllElements()` | 544 | 3 |  |
| `QueueSoundEffect()` | 552 | 3 |  |
| `MaintainActiveSfx()` | 560 | 3 |  |
| `UpdateSfxChannels()` | 568 | 3 |  |
| `Update3DVolumes()` | 576 | 3 |  |
| `AllocateSoundElement()` | 584 | 3 |  |
| `UpdateSfx()` | 592 | 3 |  |
| `PlayRandomSfx()` | 600 | 3 |  |
| `SetupObjectSfx()` | 608 | 3 |  |
| `SetupSpriteSfx()` | 616 | 3 |  |
| `RouteObjectSfx()` | 624 | 3 |  |
| `HandlePedSpeech()` | 632 | 3 |  |
| `AddPedSfx()` | 640 | 3 |  |
| `ResetRadioQueue()` | 648 | 3 |  |
| `QueueRadioPhrase()` | 656 | 3 |  |
| `PlayNextRadioPhrase()` | 664 | 3 |  |
| `GetRadioQueueSpace()` | 672 | 3 |  |
| `QueueStaticResponse()` | 680 | 3 |  |
| `GetMapDistrict()` | 688 | 3 |  |
| `ResetRadio()` | 696 | 3 |  |
| `QueueDirectionPhrase()` | 704 | 3 |  |
| `QueueVehiclePhrase()` | 712 | 3 |  |
| `QueuePatrolPhrase()` | 720 | 3 |  |
| `UpdatePoliceRadio()` | 728 | 3 |  |
| `AddWeaponSfx()` | 736 | 3 |  |
| `UpdateMusicStream()` | 744 | 3 |  |
| `UpdateSoundCounters()` | 752 | 3 |  |
| `ResetAudioState()` | 760 | 3 |  |
| `FindBufferBySound()` | 768 | 3 |  |
| `UpdateEngineSound()` | 776 | 3 |  |
| `SelectNextSound()` | 784 | 3 |  |
| `IsSpecialCarModel()` | 792 | 3 |  |
| `IsTransportOrCargo()` | 800 | 3 |  |
| `UpdateStreamPlayback()` | 808 | 3 |  |
| `SelectCarSound()` | 816 | 3 |  |
| `UpdateCarSoundVolume()` | 824 | 3 |  |
| `SetEngineSoundState()` | 832 | 3 |  |
| `TickStreams()` | 840 | 3 |  |
| `InitializeStreams()` | 848 | 3 |  |

## Объявлены в .h, но не определены

- `PlayScreechSound()`
- `ProcessAttachmentSound()`
- `ProcessCarAmbientSound()`
- `ProcessCarSound()`
- `ProcessEngineDamageSound()`
- `ProcessIfActive()`
- `ProcessMissionSound()`
- `ProcessPedImpactSound()`
- `ProcessPlayerEventSound()`
- `ProcessTurretActiveSound()`
- `ProcessTurretAimSound()`
- `ProcessTurretAmbientSound()`
- `ProcessTurretFireSound()`
- `ProcessTurretLoopSound()`
- `ProcessTurretShotSound()`
- `ProcessTurretSound()`
- `UpdateCarAudio()`
