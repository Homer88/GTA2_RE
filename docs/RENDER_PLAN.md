# План по рендеру (зафиксировано 2026-09-30)

## Решение: чинить существующий, не писать с нуля

Причина: ABI уже закрыт и проверен (42/42 `d3ddll`, 22/22 `dmavideo`), но за
сигнатурами стоит полноценный растеризатор (текстуры, палитра, shade-таблицы,
кеш, треугольники, тайлы, линии, 3D-свет). Свой рендер — недели, починка — дни.

Рабочая схема:
- `dmavideo.dll` — **наша**: окно, режимы, surface. Единственный владелец перечисления.
- `d3ddll.dll` — **ретрайлный** (80 384 Б, оригинал), отрисовку не трогаем.

## Что уже сделано и проверено

1. Экспорт-контракт точный: `d3ddll/Exports.def` 42/42, `dmavideo/Exports.def` 22/22.
2. `AddFallbackModes()` — при пустом перечислении DirectDraw подсовывает
   640x480 / 800x600 / 1024x768 x16/x32. Устраняет ошибку `16x16x16`.
3. Перевод 16bpp -> 32bpp в `Vid_CheckMode`: под RDP 16-битной поверхности не
   существует, игра теперь получает `640x480x32`.
4. Хардкод: при провале поиска режима `Vid_CheckMode` больше не возвращает 0.
5. Логгер `VLog` -> `C:\games\GTA2 _old\vid.log` (аргументы и результат каждого `Vid_*`).
   Это самый полезный инструмент — логи дали больше, чем статический анализ.

## Точка отказа (локализована по логу)

```
Vid_SetMode(modeId=-2)   <- оконная попытка, возвращает ошибку
Vid_SetMode(modeId=-2)   <- вторая оконная попытка
Vid_CheckMode(640x480x16) -> translate -> 32bpp
Vid_SetMode(modeId=5)    <- 640x480x32, ПАДЕНИЕ здесь
```

`modeId = -2` — оконный режим, числовой индекс — полноэкранный. Игра пробует окно,
наша функция возвращает ошибку, игра откатывается в полноэкранный режим, где
640x480x32 под RDP не создаётся -> падение. Побочно это же объясняет, почему
игра переписывает `start_mode` обратно в `1`.

## Следующий шаг (главный блокер)

Реализовать в `dmavideo` оконную ветку `Vid_SetMode` при `modeId == -2`:
- создать DIB back-buffer 640x480x32;
- `CreateClipper` + `SetHWnd(hWnd)`;
- блит в окно в `Vid_FlipBuffers`;
- возвращать 0 (успех).

Пока эта ветка возвращает ошибку, остальное бесполезно: игра откатывается
в полноэкранный `Vid_SetMode(modeId=5)` = 640x480x32, который под RDP не
создаётся, и падает внутри `dmavideo` до того, как дело доходит до `d3ddll`.
Лог обрывается сразу после строки `Vid_SetMode ... before: fullscreen=0`.

## Починка d3ddll (сделано 2026-09-30)

`d3ddll/d3ddll.cpp`, `gbh_InitDLL`:
- убран жёсткий путь `C:\Program Files (x86)\Rockstar Games\GTA2\_d3ddll.dll`;
  теперь ищется `_d3ddll.dll` рядом с самим драйвером
  (`GetModuleHandleExA(FROM_ADDRESS|UNCHANGED_REFCOUNT)` + `GetModuleFileNameA`);
- `PopulateS3DFunctions` только при непустом `hOld` (раньше заполняла `gFuncs`
  мусором при `NULL`);
- `RebasePtrs` / `GetProcAddress` только при непустом `hOld` — иначе указатели
  превращались в `0x1840` / `0x5A10`, и вызов уходил в область PE-заголовков;
- проверки на `pVideoDriver` / `initDLL` и на `gFuncs.pgbh_InitDLL`.

Сборка: `D3DDLL.dll` 117 760 Б, 42 экспорта. Линковать нужно с `advapi32.lib`
(иначе LNK2019 по `__imp__Reg*` из `CheckIfSpecialFindGfxEnabled`).

**Важно:** починка реальна и нужна, но она НЕ устранила падение игры.
Падение происходит в `dmavideo` на полноэкранной ветке и воспроизводится
так же с ретрайлной `d3ddll.dll`. То есть главный блокер — не инициализация
`d3ddll`, а невозможность удержать игру в оконном режиме.

## Воссоздание exe (приоритет)

Правки внесены, компилируются, но exe не пересобран:
- `gta2/Engine/Movie/Movie.cpp` — фасад драйвера: `LoadLibraryA("dmavideo.dll")`,
  обнулённый буфер состояния `0x400` через `LocalAlloc` (структура `Video`
  не дублируется — драйвер проставляет поля сам), резолв 9 экспортов из 22,
  форвард `CheckMode` / `SetMode` / `Vid_FlipBuffers` / `Vid_ClearScreen`,
  лог в `C:\games\GTA2 _old\movie.log`;
- `gta2/Engine/Movie/Movie.h` — добавлены `void* pVideoState; void* pVideoDll;`;
- `gta2/Engine/ultil/WinApi.cpp` — `ConfigureVideoDevice()` создаёт `gMovie`
  (раньше он был `nullptr` и просто игнорировался).

Осталось: `WinApi::VideoCheck1()` (закомментированный `SetMode`),
убрать возврат в fullscreen (WinApi.cpp:461-462), собрать порт.
Сборку CMake починить: кэш создан по `n:\GTA2_RE\build`.

## Отложено: свой рендер

Когда дойдём до написания своих рендеров — цели:
- RDP (программный, без GPU);
- Linux;
- общий программный бэкенд как основа.

Тогда реализуются все 42 `gbh_*` поверх своего буфера вместо DirectDraw.
Референс для сверки — ретрайлные `d3ddll.dll` / `dmavideo.dll` из
`C:\games\original\Grand Theft Auto 2` (рабочая пара).

## Состояние окружения

- `C:\games\GTA2 _old\gta2.exe` + ретрайлные DLL = работает (55+ с, без падения).
- `gta2-resurected.exe` (порт) падает в своём коде: видеослой не реализован,
  `gMovie == nullptr`, `WinApi::VideoCheck1` с `Vid_SetMode` закомментирован.
- `dllLoad`-хук работает по адресам ретрайл-`gta2.exe` и в порт не подключается.
- Видеокарта: при подключённой Intel сессия RDP использует
  `Microsoft Remote Display Adapter` 3840x2160; DirectDraw тогда отдаёт
  1920x1080x32, без карты — ни одного пригодного режима.
- Звук: при подключённой карте пропадает. Проверять в RDP-клиенте
  «Воспроизведение звука: На этом компьютере» + галочка «Удалённое воспроизведение аудио».
- Наша пересобранная `d3ddll.dll` не используется: причина падения —
  инициализация указателей от несуществующего
  `C:\Program Files (x86)\Rockstar Games\GTA2\_d3ddll.dll` (наша выдумка,
  игра никаких путей не знает). Сохранена как `d3ddll.dll.ours`.

## Сборка

CMake-кэш сломан (создан по `n:\`), собираем напрямую:

```
call D:\dev\VisualStudio\vs17\VC\Auxiliary\Build\vcvars32.bat
cl /nologo /c /D_M_IX86 /D_CRT_SECURE_NO_WARNINGS /I C:\work\GTA2_RE /Fobuild_manual\dmavideo.obj dmavideo\dmavideo.cpp
link /nologo /DLL /OUT:build_manual\DMAVIDEO.dll /DEF:dmavideo\Exports.def build_manual\dmavideo.obj user32.lib gdi32.lib
```
