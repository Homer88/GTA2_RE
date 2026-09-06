# GTA2_RE - Лог работы

## Текущее состояние (04.09.2026)

### Полный парсер .gmp (GmpFile) + расширенный MapEditor

- Создан **`gta2/Tools/core/GmpFile.h` / `GmpFile.cpp`** — парсер всего контейнера `.gmp`
  (замена узкого ZoneInfo на полный разбор всех секций):
  - Структуры: `BlockInfo` (12 байт), `MapObject` (6 байт), `MapLight` (16 байт),
    `Junction` (16 байт), `Segment` (8 байт)
  - Секции: UMAP (несжатая карта 256x256), DMAP/CMAP (сжатые, хранятся сырыми),
    ZONE, MOBJ, PSXM, ANIM, LGHT, RGEN, EDIT
  - Порядок секций сохраняется (маркеры редактируемых секций в m_raw,
    при Save() подставляются пересобранные UMAP/ZONE/RGEN)
- **RGEN расшифрован**: 545 junction'ов × 16 байт = 8720 + 545 h-сегментов × 8 = 4360
  + 545 v-сегментов × 8 = 4360 + 3×uint16 счётчиков = 17446 байт (все 4 файла).
- **Junction (Data16, 16 байт)**: раскладка сверена с официальным документом
  "GTA2 Map Format.doc" (раздел "Junction List"):
  `link north/south/east/west` (на диске 16 бит: нижние 9 = индекс узла,
  старшие = длина дороги; в памяти link = 4 байта) + `search_type` (байт 0x8) +
  `junc_type` (байт 0x9) + `min_x/min_y/max_x/max_y` (прямоугольник узла).
  Юнкция 0 — пустая/заглушка. Сегменты массивы паддятся до 545 (по документу).
  Структура с именованными полями, а не сырыми байтами.
- **Segment (8 байт)**: junction_num1/junction_num2 (uint16) + min_x/min_y/max_x/max_y
  (ограничивающий прямоугольник ребра). Подтверждено данными: H-сегменты
  горизонтальные (y~const), V-сегменты вертикальные (x~const).
- Имена структур `JuncIds`/`Data16`/`S92` уточнены по дампу (Ghidra + IDA) —
  смещения согласованы с загрузчиком `JuncIds::JuncIdsLoad`.
- **Round-trip байт-точный** на всех 4 реальных файлах:
  `bil` (zones=189, obj=0, lights=1646, junc=330/h=353/v=359),
  `ste` (113, 10, 1743, 268/324/336), `wil` (175, 0, 1982, 312/366/365),
  `lorne2e` (5, 0, 46, 36/57/57) — Parse→Save IDENTICAL.
  - Найден и исправлен баг: счётчики RGEN читались в uint8 (обрезая 330→74);
    переведены на uint16.
- **MapEditor** расширен до вкладок: Zones, Objects, Lights, Road + общий канвас
  (режимы отрисовки зон/объектов/светов/узлов дорог).
- `MapEditor.exe` собирается чисто (MinGW, CMAKE_AUTOMOC).

### Изменённые файлы

| Файл | Описание |
|------|----------|
| `gta2/Tools/core/GmpFile.h` | Полный формат .gmp: структуры + GmpFile (новый) |
| `gta2/Tools/core/GmpFile.cpp` | Разбор/сериализация всех секций .gmp, round-trip байт-точный |
| `gta2/Tools/core/GmpFile.h` | Junction с именованными полями (north/south/west/east/x/y), Segment подтверждён |
| `gta2/Tools/core/CMakeLists.txt` | Подключены GmpFile.cpp/h |
| `gta2/Tools/MapEditor/MainWindow.h/.cpp` | Вкладки Zones/Objects/Lights/Road (Qt), переход на GmpFile |
| `gta2/Tools/MapEditor/CMakeLists.txt` | Сборка MainWindow |
| `gta2/Tools/core/ZoneInfo.h` | Формат .gmp: ZoneInfo + ZoneFile (ранее) |
| `gta2/Tools/core/ZoneInfo.cpp` | Разбор/сериализация ZONE, round-trip байт-точный |



### Изменённые файлы (не закоммичено)

| Файл | Описание |
|------|----------|
| `gta2/Game/CMakeLists.txt` | Обновление сборки игры |
| `gta2/Game/Menu/Menu.cpp` | Меню (48 функций заполнены) |
| `gta2/Tools/CarEditor/CMakeLists.txt` | Сборка редактора машин |
| `gta2/Tools/CarEditor/main.cpp` | Точка входа редактора |
| `gta2/Tools/core/CMakeLists.txt` | Сборка core библиотеки |
| `gta2/Tools/core/GciFormat.cpp` | Формат .gci файлов |

### Новые файлы (не закоммичено)

| Файл | Описание |
|------|----------|
| `gta2/Game/Car/CarPhysics.h` | Структура физики машины (72 байта) + CarPhysicsManager |
| `gta2/Game/Weapons/weapon.cpp` | Таблицы данных оружия (макс. патроны, патроны за подбор) |
| `gta2/Game/Weapons/weapon.h` | Заголовок системы оружия: Weapon (0x30), WeaponDatabase (0x2FDC), Arsenal (0x8), enum WeaponType (29) |
| `gta2/Game/Weapons/CMakeLists.txt` | Сборка модуля Weapons (создан заново, ранее отсутствовал) |
| `gta2/Tools/CarEditor/MainWindow.cpp` | GUI редактора машин (Qt) |
| `gta2/Tools/CarEditor/MainWindow.h` | Заголовок главного окна |

---

## Что сделано ранее

### Структуры (из done.md)
- **S1 (GameEntity)** - 0xB0 байт, тесты пройдены
- **S2 (ActiveCarsPool)** - 0xD264, адрес 0x0066ab7c
- **S3 (CarTransforms)** - 0x3C
- **S4 (CarColorsPalette)** - 0xE0C4
- **S8 (CarAudioSettings)** - 0x14
- **S10 (CarPhysicsWorld)** - 0x8F74
- **S13 (General)** - 0x8
- **S14 (Text)** - 0x14
- **S15 (Style)** - 0x106c
- **S16 (MapRelatedStruct)** - 0x370, ~110 функций заполнены из IDA dump
- **S21 (CameraManager)** - 0xfa4
- **S23 (CarSystemManager)** - 0x6c
- **S26 (MissionManager)** - 0xC1EA8, 41 функция заполнена
- **S72 (Arsenal)** - 0x8
- **S73 (WeaponDatabase)** - 0x2FDC
- **S75 (Door)** - 0x4D4
- **S133 (Menu)** - 0x1EB40

### Модули
- **Menu.cpp** - 48 функций, все тела заполнены
- **Bink** - обёртка для Bink Video (Bink.h/.cpp, глобальный gBink)
- **MissionManager** - 41 метод из IDA dump

---

## Что делаем сейчас

### 1. CarPhysics (Car/CarPhysics.h)
Новая структура для физических параметров машин:
- Загружается из .gci файла (формат Sony_2D_style_cars)
- 72 байта на запись: model(1) + turbo(1) + value(1) + pad(1) + 17 float параметров
- Параметры: mass, front_drive_bias, front_mass_bias, brake_friction, turn_in, turn_ratio, rear_end_stability, handbrake_slide_value, thrust, max_speed, anti_strength, skid_threshhold, gear multipliers, gear speeds
- CarPhysicsManager управляет массивом записей

### 2. Weapons (Game/Weapons/)
Новая система оружия:
- weapon.h — **полностью заполнен**: struct Weapon (S74, 0x30 байт, все 24 поля с типом и назначением), WeaponDatabase (S73, 0x2FDC), Arsenal (S72, 0x8), enum WeaponType (29 значений), документация всех 42 функций Weapon + 7 функций пула + Turrel/Arsenal
- weapon.cpp — **две хардкодных таблицы из бинарника**: kMaxAmmo[28] (0x00575904, макс. отображаемые патроны) и kAmmoPerPickup[28] (0x00575920, патроны за подбор)
- weapon.h/weapon.cpp компилируются под C++98 (проверено MinGW g++ -fsyntax-only)
- CMakeLists.txt создан заново по образцу Gang.h-модуля (file(GLOB))
- Связано с S72 (Arsenal), S73 (WeaponDatabase), S74 (Weapon)
- Примечание: сборка корня на текущем CMake не идёт (cmake_minimum_required(3.0) устарел для CMake>=3.5 во всех модулях — предсуществующая проблема окружения, не связана с этим изменением)

### 3. CarEditor (Tools/CarEditor/)
Qt-based GUI редактор машин:
- MainWindow.h/cpp - главное окно
- Левая панель: список машин (модель: имя)
- Правая панель: свойства выбранной машины
- Редактирование графики из CARI секции .sty
- Редактирование физики из .gci файла
- Сохранение: CARI -> .sty, физика -> .gci текст

---

## Правила проекта
- Вставлять код из dump'а дословно, адаптируя только имена
- Не исправлять логику или ошибки компиляции
- Не добавлять комментарии除非 спросят
- C++98, CMake сборка

---

## Источники
- `dump/IDA/Menu_Functions_Extracted.txt` (основной)
- `dump/IDA/gta2.exe.c` (запасной)
- `gta2/old/` (ручной RE код)
