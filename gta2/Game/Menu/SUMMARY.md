# Menu.cpp Progress Summary

## Goal
- Fill ~48 empty Menu.cpp functions with dump implementations from `dump\IDA\Menu_Functions_Extracted.txt`, keeping existing field names and .h declarations unchanged.

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

### Remaining (~19 TODO/stub/partial)
| Function | Dump size | Notes |
|---|---|---|
| `InitializeState` | 0x933B | Huge, in extracted file |
| `CleanupResources` | 0xC5B | Huge, in extracted file |
| `UpdateState` | 0x103 | Not in extracted dump |
| `UpdateMenuFrame` | 0xF9 | Partially written |
| `RenderMenu` | 0x18B | In dump, different sig |
| `SaveGame` | 0x104 | Not filled |
| `PrintCentr` | — | In `gta2.exe.c`, sig mismatch |
| `ApplyMoneyCheatIfApplicable` | 0x17B | In dump, sig mismatch (retaddr) |
| `PlayerList` | 0x16B | In `gta2.exe.c`, sig mismatch |
| `HandleMenuEvent` | 0x60B | In dump, different purpose (renders stats) |
| `ActivateElement(int)` | 0xBC | No dump equivalent |
| `PlayerCheat` | 0x44E | Partially written |
| `SetDifficulty` | 0x2C4 | Stub |
| `SelectCharacter` | 0x6E | Stub |
| Constructor `Menu()` | 0x32E | In dump, huge |
| Destructor `~Menu()` | 0xF0 | Stub |
| `MenuDelete` | 0x1E | Stub |
| `StartGTAManager` | — | Stub |
| `CheckSaveFile` | — | Stub (returns false) |
