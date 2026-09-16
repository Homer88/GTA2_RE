# AudioManager

- **Место**: `gta2/Engine/AudioManager/`
- **Файлы**: `.cpp` 851 строк, `.h` 261 строк
- **Методов**: 120
- **Полностью реализовано**: 3
- **Частично (TODO/незавершено)**: 0
- **Заглушки**: 100
- **Объявлено, но не определено**: 17
- **Реализация в целом: ~2%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `InitArray()` | 9 | 14 |  |
| `ExtractBaseName(char* FileName)` | 399 | 17 |  |
| `PlayStream(char* FileName)` | 509 | 7 |  |

## Заглушки (мини-тела / return-заглушки)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `DefauntParam()` | 24 | 3 |  |
| `SetupEngineRevSound()` | 31 | 3 |  |
| `PlayEngineSound()` | 39 | 3 |  |
| `SetupEngineAccelSound()` | 47 | 3 |  |
| `PlayEngineGearSound()` | 55 | 3 |  |
| `InitSoundInstance()` | 63 | 3 |  |
| `SetupCarEngineSound()` | 71 | 3 |  |
| `InitSoundInstance2()` | 79 | 3 |  |
| `InitSoundSample()` | 87 | 3 |  |
| `SetupCarSirenSound()` | 95 | 3 |  |
| `InitSoundSample2()` | 103 | 3 |  |
| `InitSoundSample3()` | 111 | 3 |  |
| `SetCarEmergencySound()` | 119 | 3 |  |
| `SetCarEngineSound()` | 127 | 3 |  |
| `SetCarIdleSound()` | 135 | 3 |  |
| `SetEngineSoundHz()` | 143 | 3 |  |
| `StartAmbientSound()` | 151 | 3 |  |
| `StopAmbientSound()` | 159 | 3 |  |
| `SetAmbientSound()` | 167 | 3 |  |
| `IsSoundInRange()` | 175 | 3 |  |
| `UpdateSoundVolume()` | 183 | 3 |  |
| `ComputeSoundScreenPos()` | 191 | 3 |  |
| `GetSoundId()` | 199 | 3 |  |
| `PlayRadio()` | 207 | 3 |  |
| `UpdateVehicleSound()` | 215 | 3 |  |
| `PlayWarningSound()` | 223 | 3 |  |
| `SetCarEngineSoundTurret()` | 231 | 3 |  |
| `PlayCarEngineSoundLocal()` | 239 | 3 |  |
| `SetCarEngineVoice()` | 247 | 3 |  |
| `SetCarEngineModelSound()` | 255 | 3 |  |
| `ComputeSoundIndexForCar()` | 263 | 3 |  |
| `UpdateCarSounds()` | 271 | 3 |  |
| `ProcessState4Sound(int arg0,int arg1)` | 279 | 3 |  |
| `PlayCarModelSound()` | 287 | 3 |  |
| `PlayVehicleEngineSound()` | 295 | 3 |  |
| `PlayCarSound()` | 303 | 3 |  |
| `SetEngineSoundByModel()` | 311 | 3 |  |
| `PlayEngineSoundValidated()` | 319 | 3 |  |
| `PlayIdleSound()` | 327 | 3 |  |
| `PlaySpecialSound1()` | 335 | 3 |  |
| `PlaySpecialSound2()` | 343 | 3 |  |
| `SetupCarSound()` | 351 | 3 |  |
| `HandleEventType()` | 359 | 3 |  |
| `ProcessEventList()` | 367 | 3 |  |
| `DispatchElementSfx()` | 375 | 3 |  |
| `ProcessElement()` | 383 | 3 |  |
| `Shutdown()` | 391 | 3 |  |
| `SetSFXVol()` | 421 | 3 |  |
| `IsInitialised()` | 429 | 3 |  |
| `GetRandomPitchOffset()` | 437 | 3 |  |
| `ResetElement()` | 445 | 3 |  |
| `AgeSoundElements()` | 453 | 3 |  |
| `AddChannel()` | 461 | 3 |  |
| `CalcSampleVolume()` | 469 | 3 |  |
| `SetSfxPosition()` | 477 | 3 |  |
| `ResetChannelSlots()` | 485 | 3 |  |
| `RefreshRandomSeeds()` | 493 | 3 |  |
| `StopStream()` | 501 | 3 |  |
| `ResetChannelLists()` | 521 | 3 |  |
| `CalcVolume()` | 529 | 3 |  |
| `Calc3DPan()` | 537 | 3 |  |
| `ProcessAllElements()` | 545 | 3 |  |
| `QueueSoundEffect()` | 553 | 3 |  |
| `MaintainActiveSfx()` | 561 | 3 |  |
| `UpdateSfxChannels()` | 569 | 3 |  |
| `Update3DVolumes()` | 577 | 3 |  |
| `AllocateSoundElement()` | 585 | 3 |  |
| `UpdateSfx()` | 593 | 3 |  |
| `PlayRandomSfx()` | 601 | 3 |  |
| `SetupObjectSfx()` | 609 | 3 |  |
| `SetupSpriteSfx()` | 617 | 3 |  |
| `RouteObjectSfx()` | 625 | 3 |  |
| `HandlePedSpeech()` | 633 | 3 |  |
| `AddPedSfx()` | 641 | 3 |  |
| `ResetRadioQueue()` | 649 | 3 |  |
| `QueueRadioPhrase()` | 657 | 3 |  |
| `PlayNextRadioPhrase()` | 665 | 3 |  |
| `GetRadioQueueSpace()` | 673 | 3 |  |
| `QueueStaticResponse()` | 681 | 3 |  |
| `GetMapDistrict()` | 689 | 3 |  |
| `ResetRadio()` | 697 | 3 |  |
| `QueueDirectionPhrase()` | 705 | 3 |  |
| `QueueVehiclePhrase()` | 713 | 3 |  |
| `QueuePatrolPhrase()` | 721 | 3 |  |
| `UpdatePoliceRadio()` | 729 | 3 |  |
| `AddWeaponSfx()` | 737 | 3 |  |
| `UpdateMusicStream()` | 745 | 3 |  |
| `UpdateSoundCounters()` | 753 | 3 |  |
| `ResetAudioState()` | 761 | 3 |  |
| `FindBufferBySound()` | 769 | 3 |  |
| `UpdateEngineSound()` | 777 | 3 |  |
| `SelectNextSound()` | 785 | 3 |  |
| `IsSpecialCarModel()` | 793 | 3 |  |
| `IsTransportOrCargo()` | 801 | 3 |  |
| `UpdateStreamPlayback()` | 809 | 3 |  |
| `SelectCarSound()` | 817 | 3 |  |
| `UpdateCarSoundVolume()` | 825 | 3 |  |
| `SetEngineSoundState()` | 833 | 3 |  |
| `TickStreams()` | 841 | 3 |  |
| `InitializeStreams()` | 849 | 3 |  |

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
