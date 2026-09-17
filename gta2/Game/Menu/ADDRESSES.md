# Menu — авторитетная карта «адрес → функция» (из IDA-дампа)

Источник: `dump\IDA\gta2.exe.c` (строки `//----- (0x...)` + следующее определение `Menu::`).

> ВАЖНО: комментарии-адреса в старом `Menu.h` в основном НЕВЕРНЫ (многим функциям были
> присвоены адреса *других* функций). Эта таблица — источник истины. Неисправленные
> комментарии в `Menu.h` брать в работу нельзя.

| Адрес       | Имя в дампе               | Примечание (сигнатура дампа/различие) |
|-------------|---------------------------|----------------------------------------|
| 0x00451F60 | SetFrontendState          | |
| 0x00451FB0 | ReleaseInputDevice        | |
| 0x00452000 | ReadDeviceState           | (в .h ошибочно 0x00456AB3) |
| 0x00452050 | ProcessInput              | (в .h ошибочно 0x00456B01) |
| 0x004521B0 | PrintCentr                | sig: (Menu*, ushort, ushort) |
| 0x00452200 | ApplyMoneyCheatIfApplicable | retaddr-хак |
| 0x00452490 | SetPlayerName             | |
| 0x004524C0 | ValidatePlayerName        | |
| 0x00452500 | getPlayerProfileName      | |
| 0x00452530 | LoadPlayerProfile         | |
| 0x004527A0 | SaveSettings              | (в .h ошибочно 0x00458F87) |
| 0x00452810 | CheckSaveFile             | sig: (Menu*, ushort ushort, char* a4, char* a5, char* a6) — копирует 3 строки, НЕ проверка файла. В .h сигнатура не совпадает |
| 0x004528A0 | GettingSaveFile           | ✓ совпадает |
| 0x00452940 | GetSaveFile               | (в .h была помечена как SaveGame!) |
| 0x00452990 | Intro_BIK                 | |
| 0x004529C0 | PreIntro                  | |
| 0x00452D50 | LoadTexture               | (в .h ошибочно 0x00457367) |
| 0x00452E20 | LoadTexturesFromTable     | (в .h ошибочно 0x00457433) |
| 0x00452E80 | FindBackground            | |
| 0x00453020 | DrawMenuBackground        | |
| 0x004531E0 | DrawMenuElements          | |
| 0x00453230 | UpdateGUI                 | |
| 0x004532B0 | HandleKeyPress            | |
| 0x004532E0 | SwitchPage                | sig: (Menu*) bool |
| 0x00453310 | ActivateElement           | |
| 0x00453430 | FindLastActiveArenaSlot   | |
| 0x00453480 | SelectPlayerSlot          | |
| 0x00453590 | SetDifficulty             | (в .h ошибочно 0x0045897B) |
| 0x00453870 | SelectCharacter           | (в .h ошибочно 0x00458C3F) |
| 0x004538E0 | sub_4538E0                | возвращает 1 |
| 0x004538F0 | ConfigureControls         | |
| 0x00453930 | AudioOptions              | |
| 0x00453960 | VideoOptions              | |
| 0x00453A30 | SetFrontendKeysEnabled    | (в .h ошибочно приписана SetFrontendState(int)) |
| 0x00453D40 | MenuShowJapanText         | (в проекте названа ShowJapanText) |
| 0x00453D80 | InitDevice                | ✓ |
| 0x00453E20 | LoadTextMenu              | ✓ |
| 0x00455340 | MainMenuLogic             | (в .h ошибочно 0x00457F00) |
| 0x004556A0 | PauseMenu                 | (в .h ошибочно 0x00458050) |
| 0x00455850 | OptionsMenu               | (в .h ошибочно 0x004581F9) |
| 0x00455C20 | LoadGame                  | (в .h ошибочно 0x00458C41) |
| 0x00455C90 | SaveGame                  | (в .h была помечена 0x00452940 = адрес GetSaveFile) |
| 0x00455F90 | NewGame                   | ✓ |
| 0x00456110 | SelectMission             | |
| 0x00456180 | WorldMap                 | |
| 0x00456280 | ShowStatistics            | |
| 0x004562F0 | ShowAwards                | |
| 0x00456430 | Gallery                   | |
| 0x00456460 | ShowCredits               | |
| 0x00456490 | ConfirmExit               | |
| 0x004565E0 | MultiplayerMenu           | sig: (Menu*, PlayerSlotSave*) |
| 0x00456820 | ServerSettings            | |
| 0x004568C0 | PlayerList                | sig: (Menu*, KeyCode_1, ushort, ushort, int, int) |
| 0x00456A60 | Menu                      | конструктор (в .h ошибочно 0x00456F00) |
| 0x00456D90 | Menu_Des                  | деструктор (в .h ошибочно 0x00481C30 — это адрес CloseBinkResources) |
| 0x00456E80 | UpdateMenuFrame           | ✓ |
| 0x00456F80 | sub_456F80                | обёртка: getPlayerProfileName + WriteFileNamePlayer + UpdateMenuFrame |
| 0x00456FB0 | RenderMenu                | (в .h ошибочно 0x00457199) |
| 0x00457140 | HandleMenuEvent           | (в .h ошибочно 0x00456DE6; в дампе рендерит статистику) |
| 0x00457750 | NavigatePages             | |
| 0x004577C0 | GoBack                    | |
| 0x00457900 | MenuDelete                | (в .h ошибочно 0x0045731E) |
| 0x00457920 | CleanupResources          | (в .h ошибочно 0x004578B3) |
| 0x00458590 | CheckConditions           | |
| 0x004585F0 | ApplySettings             | |
| 0x00458650 | ResetSettings             | |
| 0x004587B0 | InitializeState           | (в .h ошибочно 0x00456F80 = адрес sub_456F80) |
| 0x004590F0 | PlayerCheat               | ✓ (в .h ещё есть 0x004590F0 комментарий с подписью 0x44E) |
| 0x00459540 | SetPlayerNameFromMenu     | ✓ |
| 0x00459590 | SpecialFunction1          | |
| 0x00459660 | SpecialFunction2          | |
| 0x004597C0 | SpecialFunction3          | |
| 0x00459E30 | SpecialFunction4          | |
| 0x0045A010 | SpecialFunction5          | |
| 0x0045A250 | SpecialFunction6          | |
| 0x0045A320 | SpecialFunction7          | |
| 0x00481D30 | CloseBinkResources        | ✓ |

Примечания:
- `Menu::Menu` (конструктор, 0x00456A60) создаёт `Text`/`Style`/`TextureManager` через `operator_new`
  (размеры 0x14/0x106C/0x15D8), вызывает `Construct(MenuPageArray, 3018, 17, MenuPage::MenuPage, ...)`,
  `Construct(MenuDataBlock, 4, 8, S138::S138, ...)`, `MenuSlotConfig::MenuSlotConfig`, `ResolveColorSettings()`,
  `gbh_SetAmbient(1.0f)`.
- `Menu::Menu_Des` (0x00456D90): `ReleaseInputDevice` + free `gTextureManager`/`gStyle`/`gText` +
  `gbh_FreeImageTable()` + деструкторы `MenuSlotConfig`/`MenuDataBlock`/`MenuPageArray`.
- В дампе нет отдельной `Menu::UpdateState`; «UpdateState @0x00456F60» в старом .h — на самом деле
  `sub_456F80` @0x00456F80.
- `StartGTAManager` в дампе отсутствует (адрес 0x004D0820 — вне Menu).