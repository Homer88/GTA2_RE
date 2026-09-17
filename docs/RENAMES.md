# Сводный отчёт по переименованиям (dllLoad + ядро)

Дата: 2026-09-17. Все имена сверены с дампами:
- IDA-дамп `dump/IDA/gta2.exe.c` — имена функций и глобалов (эталон).
- Ghidra `dump/Ghidra/gta2.exe.h` (`fieldN_0xHH` / осмысленные глобалы) — смещения структур.

## 1. Функции-хуки

| Было (в проекте)                | Стало                              | Адрес     |
|---------------------------------|------------------------------------|-----------|
| `GetVersionLaunch`              | `GetVersionFiles`                  | 0x004D0920 |
| `GetDebugParam`                 | `fPlayReplay` (читает все debug-параметры) | 0x00451930 |
| `AllGtxFile` (опечатка)         | `AllGxtFile`                       | 0x00451800 |
| `sub_459540`                    | `Menu::SetPlayerNameFromMenu` (__fastcall) | 0x00459540 |
| `InitDiretX` (опечатка)         | `InitGraphicsAndInput` (инициализирует DirectDraw + DirectInput) | 0x004031C0 |
| `SetTypeWeapons`                | `Weapon::SetWeapon`                | 0x00433810 |
| `Weapon_FUN_004cca10`           | `Weapon::SetPed`                   | 0x004CCA10 |

Затронуто: `cWindow.{h,cpp}`, `cMenu.{h,cpp}`, `cDirectX.{h,cpp}`, `cWeapon.{h,cpp}`, `dllmain.cpp`
(в т.ч. трамплины-переменные `_GetVersionFiles`, `_fPlayReplay`, `_AllGxtFile`, `_SetPlayerNameFromMenu`, `_SetWeapon`, `_SetPed`
и строки `TraceEvent`).

## 2. Флаги (глобалы в .bss/DebugParams)

Все `bool*`, кроме `gCheatIs` (`int*`). Адреса в `0x005EADxx` / `0x005EAF50` проверены по асему дампа — соответствие 1:1.

| Было                      | Стало                  | Адрес      | Примечание / имя в дампе |
|---------------------------|------------------------|------------|--------------------------|
| `gActiveCheat`            | `gCheatIs`             | 0x005EAF50 | `int`; `gCheatActive = &gCheatIs` |
| `gByte2`                  | `gReplayActive`        | 0x005EAD92 | `unk_5EAD92` — гейт replay записи/воспроизведения |
| `gByte1`                  | `gReplayToFile`        | 0x005EADA3 | `unk_5EADA3` — запись кадров в replay.rep |
| `gTestFileGxt`            | `gAllGxtFile`          | 0x005EAD73 | `gAllGxtFile` |
| `gGoKillPhonesOnAnswer`   | `gDoKillPhonesOnAnswer`| 0x005EADB3 | `do_kill_phones_on_answer` (соответствует ключу registry) |
| `gSmallCar`               | `gFISHFLAP`            | 0x005EAD6D | чит FISHFLAP |
| `gGiveMoney20`            | `gDANISGOD`            | 0x005EAD97 | чит DANISGOD |
| `gFireGun`                | `gFLAMEON`             | 0x005EAD9B | чит FLAMEON (имя взято с `g`-префиксом, в cMenu.cpp есть enum-константа `FLAMEON=0x45EC2`) |
| `gDoubleDamage`           | `gSCHURULZ`            | 0x005EAD65 | чит SCHURULZ |
| `gInvisibility`           | `gHUNSRUS`             | 0x005EAD8E | чит HUNSRUS |
| `gJailFreeCard`           | `gFYOHZZ0`             | 0x005EAD83 | чит FYOHZZ0 |
| `gHealth99`               | `gHeats99`             | 0x005EAD8F | чит (имя из дампа, с опечаткой) |
| `gElectroGun`             | `gVOLTFEST`            | 0x005EAD70 | чит VOLTFEST |
| `gAllTower`               | `gUKGAMER`             | 0x005EAD5C | чит UKGAMER |
| `gPontMultiplaerX10`      | `gSEGARULZ`            | 0x005EAD7B | чит SEGARULZ |
| `gBonusAll`               | `gTUMYFROG`            | 0x005EAD6A | чит TUMYFROG |
| `gGiveBasikWeapon`        | `gDAVEMOON`            | 0x005EAD6E | чит DAVEMOON |
| `gElvis`                  | `gLASVEGAS`            | 0x005EAD9F | чит LASVEGAS |

Не переименованы (в дампе не именованы, роль подтверждена по асему):
- `gJailKey` (0x005EADA2) — jail-карта + SMG + респект; нигде не устанавливается (всегда false).
- `gNopCheat` (0x005EAD62) — только обнуляется.

Затронуто: `cWindow.cpp` (определения), `cGlobal.h` (extern), `cMenu.cpp` (PlayerCheat/InitDefautValue).

## 3. Ядро (gta2/)

- `Random`: `Random* gRandom` → объект `Random gRandom`; вызовы `gRandom->…` → `gRandom.…`; `Random::Restart()` вызывается в `Game::Game`.
- `Game::Game`: добавлен файл-скоп `DAT_005e7220` (глобал из дампа, снимает локальное затенение).

## 4. RTC#3 (баг hook persistence)

Причина: `DetourTransactionCommit` в `DLL_PROCESS_DETACH` — уже не актуально; фикс — `Registry::ReadKeyMap` с `hKey = NULL` и первые `DetourAttach/Commit` на загрузке DLL работают корректно (см. тред RTC#3).

## 5. Сборка

- Конфиг: **Debug | x86** (в sln `Debug|x86` → в vcxproj `Debug|Win32`; x64 не собирается — `_CONTEXT.Esp/Eip/Ebp` отсутствуют).
- Команда: `& D:\dev\VisualStudio\vs17\MSBuild\Current\Bin\MSBuild.exe C:\work\GTA2_RE\dllLoad\dllLoad.sln /m /p:Configuration=Debug /p:Platform=x86 /v:m`
- Выход: `dllLoad\Debug\dllLoad.dll`. Warning MSB8012: имя цели `dllLoad` vs `Link.OutputFile = c:\games\gta2\gta2-resurection.dll` — ожидаемо.

## 6. Анализ «пустых» полей структур (Ghidra)

Инструмент: `Temp\opencode\efs` (C#). Отчёт: `Temp\opencode\empty_report.txt`.

Подход: «пустое» поле = объявлено в Ghidra-структуре, но **ни разу не упомянуто через `.`/`->` во всём дампе** (`gta2.exe.c`). Всего уникальных обращений к полям в дампе — 1673.

| Структура      | Поля (всего) | Используется | Пусто (паддинг) |
|----------------|--------------|--------------|-----------------|
| `Menu`         | 8773         | 53           | 8720            |
| `PlayerData`   | 6226         | 18           | 6208            |
| `MapGm`        | 275          | 25           | 250             |
| `AudioManager` | 16597        | 74           | 16523           |
| `Replay`       | 432020       | 12           | 432008          |
| `Game`         | 21           | 14           | 7               |

Вывод: в своих классах можно смело опускать «пустые» поля — это развёрнутые Ghidra-паддинги
(в т.ч. крупные зарезервированные буферы, например `Menu[CCD4..EDD3]`, `AudioManager[14B4..444B]`,
`Replay[BBBC..7533B]` = LPBUFFER, который нигде не читается как поле). Списки используемых полей
со смещениями — в `empty_report.txt`.