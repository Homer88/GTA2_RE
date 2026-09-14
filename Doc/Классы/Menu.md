# Menu

- **Место**: `gta2/Game/Menu/`
- **Файлы**: `.cpp` 2018 строк, `.h` 380 строк
- **Методов**: 97
- **Полностью реализовано**: 15
- **Частично (TODO/незавершено)**: 15
- **Заглушки**: 66
- **Объявлено, но не определено**: 1
- **Реализация в целом: ~23%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `clearArrayTail()` | 695 | 11 |  |
| `PrintCentr(const wchar_t* text, float x, float y)` | 707 | 9 |  |
| `FindBackground(int iMenuBackground, byte* LeftPicture, byte* RightPicture)` | 725 | 93 |  |
| `PlayMenuCreate()` | 901 | 128 |  |
| `CompliteGameMenuCreate()` | 1030 | 28 |  |
| `AreaCompliteMenuCreate()` | 1061 | 83 |  |
| `ResumeLoadSaveCreate()` | 1146 | 64 |  |
| `YouAreDead_RIP()` | 1211 | 58 |  |
| `HighScoresForAreaCreate()` | 1271 | 52 |  |
| `PlayVideoMovieMenuCreate()` | 1329 | 14 |  |
| `PlayVideoMovieIntroMenuCreate()` | 1343 | 15 |  |
| `BonusStageCMenuCreate()` | 1360 | 56 |  |
| `NetworkGameMenuCreate()` | 1417 | 72 |  |
| `NiceTryMenuCreate()` | 1494 | 23 |  |
| `CodeDebugMenuCreate()` | 1518 | 36 |  |

## Частично реализованные (есть TODO/не завершены)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `UpdateMenuFrame()` | 422 | 39 | 0x00456E80 |
| `ReleaseInputDevice()` | 473 | 13 | 0x00451FB0 |
| `SetFrontendKeysEnabled(bool enabled)` | 509 | 5 | 0x00456C7D |
| `SetPlayerName()` | 516 | 6 | 0x00452490 |
| `SetPlayerNameFromMenu()` | 524 | 10 | 0x0045862F |
| `ValidatePlayerName(const char* name)` | 535 | 7 | 0x0045867E |
| `LoadPlayerProfile(int slot)` | 550 | 5 | 0x004586DC |
| `FindLastActiveArenaSlot(PlayerSlotSlave* PlayerSlotSave)` | 562 | 5 | 0x00458A43 |
| `NewGame()` | 582 | 81 | 0x00455F90 |
| `GettingSaveFile(byte Index, char* FileNameSave)` | 670 | 12 | 0x004528A0 |
| `GetSaveFile(unsigned char SlotSave)` | 683 | 5 | 0x00458F39 |
| `LoadTextMenu()` | 825 | 74 |  |
| `PlayerCheat(wchar_t * PlayerName)` | 1735 | 124 | 0x004590F0 |
| `SpecialFunction6()` | 1886 | 46 | 0x0045A4A4 |
| `MenuDelete(byte status)` | 2008 | 7 | 0x0045731E |

## Заглушки (мини-тела / return-заглушки)

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `InitializeState()` | 393 | 4 | 0x00456F80 |
| `CleanupResources()` | 398 | 4 | 0x004578B3 |
| `CloseBinkResources()` | 403 | 4 | 0x00481D30 |
| `SetFrontendState()` | 409 | 4 | 0x00453A30 |
| `SetFrontendState(int state)` | 409 | 4 | 0x00453A30 |
| `UpdateState()` | 417 | 4 | 0x00456F60 |
| `RenderMenu()` | 462 | 4 | 0x00457199 |
| `InitDevice()` | 468 | 4 | 0x00453D80 |
| `ReadDeviceState()` | 487 | 5 | 0x00456AB3 |
| `ProcessInput()` | 493 | 4 | 0x00456B01 |
| `HandleKeyPress()` | 498 | 5 | 0x00456C53 |
| `SwitchPage()` | 504 | 4 |  |
| `SwitchPage(int pageIndex)` | 504 | 4 |  |
| `getPlayerProfileName()` | 543 | 6 | 0x004586B6 |
| `SelectPlayerSlot()` | 556 | 5 | 0x00458937 |
| `SaveGame()` | 569 | 4 | 0x00452940 |
| `LoadGame()` | 574 | 4 | 0x00458C41 |
| `CheckSaveFile(const char* filename)` | 664 | 5 | 0x00458E15 |
| `SaveSettings()` | 689 | 4 | 0x00458F87 |
| `LoadTexture(unsigned short ID)` | 717 | 1 |  |
| `LoadTexturesFromTable(void* table)` | 719 | 1 |  |
| `DrawMenuBackground()` | 819 | 1 |  |
| `DrawMenuElements(unsigned char PlayerArena)` | 821 | 1 |  |
| `UpdateGUI(unsigned char PlayerArena)` | 823 | 1 |  |
| `BonusStageAMenuCreate()` | 1324 | 3 |  |
| `BonusStageBMenuCreate()` | 1358 | 1 |  |
| `OptionsMenuCreate()` | 1489 | 4 |  |
| `NetworkServerMenuCreate()` | 1554 | 3 |  |
| `NetworkClientMenuCreate()` | 1557 | 3 |  |
| `ActivateElement()` | 1574 | 4 | 0x00456D2A |
| `ActivateElement(int elementIndex)` | 1574 | 4 | 0x00456D2A |
| `HandleMenuEvent(int event)` | 1583 | 4 | 0x00456DE6 |
| `NavigatePages(int direction)` | 1588 | 4 | 0x00456DF0 |
| `GoBack()` | 1593 | 4 | 0x00456E56 |
| `MainMenuLogic()` | 1600 | 4 | 0x00457F00 |
| `PauseMenu()` | 1605 | 4 | 0x00458050 |
| `OptionsMenu()` | 1610 | 4 | 0x004581F9 |
| `PlayerList()` | 1615 | 4 | 0x004584C4 |
| `MultiplayerMenu(PlayerSlotSlave* PlayerSlotSave)` | 1620 | 5 | 0x0045862F |
| `ServerSettings()` | 1626 | 4 | 0x00458709 |
| `ApplyMoneyCheatIfApplicable()` | 1632 | 4 | 0x00458800 |
| `SetDifficulty(int difficulty)` | 1637 | 4 | 0x0045897B |
| `SelectCharacter(int characterIndex)` | 1642 | 4 | 0x00458C3F |
| `ConfigureControls(int config)` | 1647 | 4 | 0x00458CAD |
| `AudioOptions()` | 1652 | 4 | 0x00458CE5 |
| `VideoOptions()` | 1657 | 4 | 0x00458D0D |
| `ApplySettings()` | 1662 | 4 | 0x00458D51 |
| `ResetSettings()` | 1667 | 4 | 0x00458DA4 |
| `Intro_BIK()` | 1673 | 4 | 0x00458F03 |
| `PreIntro()` | 1678 | 4 | 0x00458F26 |
| `SelectMission()` | 1683 | 4 | 0x00458F68 |
| `WorldMap()` | 1688 | 4 | 0x00458FCE |
| `ShowStatistics()` | 1693 | 4 | 0x004590C7 |
| `ShowAwards(char)` | 1698 | 5 | 0x0045912D |
| `Gallery()` | 1704 | 4 | 0x00459266 |
| `ShowCredits()` | 1709 | 5 | 0x00459290 |
| `ConfirmExit()` | 1715 | 4 | 0x004592BA |
| `CheckConditions()` | 1721 | 4 | 0x004593FB |
| `ShowJapanText()` | 1726 | 4 | 0x00453D40 |
| `SpecialFunction1()` | 1860 | 4 | 0x004598C6 |
| `SpecialFunction2()` | 1865 | 4 | 0x00459987 |
| `SpecialFunction3()` | 1870 | 4 | 0x00459A80 |
| `SpecialFunction4()` | 1875 | 4 | 0x0045A09D |
| `SpecialFunction5()` | 1880 | 4 | 0x0045A273 |
| `SpecialFunction7()` | 1933 | 4 | 0x0045A559 |
| `StartGTAManager()` | 2016 | 3 |  |

## Объявлены в .h, но не определены

- `HandleMenu()`
