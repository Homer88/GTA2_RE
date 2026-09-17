# Menu.cpp Progress Summary

## Goal
- Fill ~48 empty Menu.cpp functions with dump implementations from `dump\IDA\gta2.exe.c`, keeping existing field names and .h declarations unchanged.

## IMPORTANT (2026-09-17)
- **`dump\IDA\Menu_Functions_Extracted.txt` не существует** — источник теперь `dump\IDA\gta2.exe.c`.
- **Комментарии-адреса в старом `Menu.h` в основном НЕВЕРНЫ.** Авторитетная карта `адрес → Menu::функция`
  (77 функций, извлечённая из дампа) — в **`ADDRESSES.md`**. Перед портом сверяться с ней.
  Ключевые расхождения: `~Menu` = Menu_Des @0x00456D90 (не 0x00481C30); `SaveGame` @0x00455C90
  (не 0x00452940 — это `GetSaveFile`); `InitializeState` @0x004587B0 (не 0x00456F80);
  `SetFrontendState` @0x00451F60, а 0x00453A30 = `SetFrontendKeysEnabled`; `CheckSaveFile` @0x00452810
  имеет сигнатуру (Menu*, ushort, ushort, char*, char*, char*) — копирует 3 строки, а не проверяет файл.

## Constraints & Preferences
- Field names NOT to be changed — user's `*Array` suffixes (`MenuEntryArray`, `GUIArray`, `MenuItemArray`, etc.) stay as-is.
- Insert dump code verbatim, adapting only field accesses to user naming. Do NOT adapt logic or fix compilation errors.
- Add `extern` declarations for all missing global variables/functions referenced by dump code.
- Keep function signatures as declared in user's .h (even if they mismatch dump signatures).
- C++98, CMake build.

## Progress

### Done (~38 functions filled)
- Special functions: `SpecialFunction1`–`SpecialFunction7`
- Init/cleanup: `CloseBinkResources`, `SetFrontendState` (both overloads), `SetFrontendKeysEnabled`
- Display: `MenuShowJapanText`, `DrawMenuBackground`, `DrawMenuElements`, `UpdateGUI`
- Settings: `AudioOptions`, `VideoOptions`, `ApplySettings`, `ResetSettings`, `SaveSettings`
- Navigation: `SelectMission`, `ShowStatistics`, `Gallery`, `ShowCredits`, `ConfirmExit`, `NavigatePages`, `GoBack`, `SwitchPage`, `WorldMap`, `ShowAwards`
- Logic: `MainMenuLogic`, `PauseMenu`, `OptionsMenu`, `CheckConditions`, `MultiplayerMenu`, `ServerSettings`
- Loading: `LoadGame`, `GetSaveFile`, `GettingSaveFile`, `LoadTexture`, `PreIntro`, `Intro_BIK`
- Input: `InitDevice`
- Player: `SetPlayerName`, `SetPlayerNameFromMenu`, `ValidatePlayerName`, `getPlayerProfileName`, `LoadPlayerProfile`, `SelectPlayerSlot`, `NewGame` (partial)

### Remaining (~19 TODO/stub/partial)  — адреса сверены с ADDRESSES.md
| Function | Dump адрес/размер | Notes |
|---|---|---|
| `InitializeState` | 0x004587B0 / 0x933 | Huge, in gta2.exe.c |
| `CleanupResources` | 0x00457920 / 0xC5B | Huge, in gta2.exe.c |
| `UpdateState` | 0x00456F80 (= sub_456F80) | обёртка: getPlayerProfileName+WriteFileNamePlayer+UpdateMenuFrame |
| `UpdateMenuFrame` | 0x00456E80 / 0xF9 | Partially written (сверено с дампом 72432+; в дампе `PlayerSlotSave[0]` через (this+slot)) |
| `RenderMenu` | 0x00456FB0 / 0x18B | In dump, different sig |
| `SaveGame` | 0x00455C90 / 0x104 | Not filled |
| `PrintCentr` | 0x004521B0 | sig: (Menu*, ushort x, ushort y) |
| `ApplyMoneyCheatIfApplicable` | 0x00452200 / 0x17B | In dump, sig mismatch (retaddr) |
| `PlayerList` | 0x004568C0 / 0x16B | sig: (Menu*, KeyCode_1, ushort, ushort, int, int) |
| `HandleMenuEvent` | 0x00457140 / 0x60B | In dump, different purpose (renders stats) |
| `ActivateElement(int)` | 0x00453310 / 0xBC | No dump equivalent |
| `PlayerCheat` | 0x004590F0 / 0x44E | Partially written |
| `SetDifficulty` | 0x00453590 / 0x2C4 | Stub |
| `SelectCharacter` | 0x00453870 / 0x6E | Stub; тело дампа известно (70308+: скан AAA[] и ArenaSlots) |
| Constructor `Menu()` | 0x00456A60 / 0x32E | In dump (72263+), создаёт Text/Style/TextureManager, Construct MenuPageArray/MenuDataBlock/MenuSlotConfig |
| Destructor `~Menu()` | 0x00456D90 (Menu_Des) / 0xF0 | Освобождает gTextureManager/gStyle/gText + gbh_FreeImageTable + деструкторы вложенных |
| `MenuDelete` | 0x00457900 / 0x1E | Уже реализован верно (Menu_Des+free) |
| `StartGTAManager` | — | В дампе отсутствует |
| `CheckSaveFile` | 0x00452810 | СИГНАТУРА НЕ ТА: в дампе копирует 3 строки (a2,a3,a4,a5,a6); «проверка файла» — это GetSaveFile @0x00452940 |
