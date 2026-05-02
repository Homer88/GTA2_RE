# GTA2.exe.c - Разбиение на модули

## Структура

Создано **20 модулей** из файла `re_file/Ghidra/gta2.exe.c` (189,619 строк).

### Модули

| № | Модуль | Диапазон адресов | Файлы |
|---|--------|------------------|-------|
| 1 | gta2_winmain | 0x401000 - 0x405000 | .c, .h |
| 2 | gta2_game | 0x405000 - 0x40A000 | .c, .h |
| 3 | gta2_player | 0x40A000 - 0x410000 | .c, .h |
| 4 | gta2_ped | 0x410000 - 0x416000 | .c, .h |
| 5 | gta2_car | 0x416000 - 0x41C000 | .c, .h |
| 6 | gta2_menu | 0x41C000 - 0x420000 | .c, .h |
| 7 | gta2_hud | 0x420000 - 0x424000 | .c, .h |
| 8 | gta2_map | 0x424000 - 0x42A000 | .c, .h |
| 9 | gta2_audio | 0x42A000 - 0x42F000 | .c, .h |
| 10 | gta2_video | 0x42F000 - 0x435000 | .c, .h |
| 11 | gta2_weapon | 0x435000 - 0x43A000 | .c, .h |
| 12 | gta2_gang | 0x43A000 - 0x43F000 | .c, .h |
| 13 | gta2_collision | 0x43F000 - 0x445000 | .c, .h |
| 14 | gta2_sprite | 0x445000 - 0x44A000 | .c, .h |
| 15 | gta2_mission | 0x44A000 - 0x450000 | .c, .h |
| 16 | gta2_replay | 0x450000 - 0x455000 | .c, .h |
| 17 | gta2_registry | 0x455000 - 0x45A000 | .c, .h |
| 18 | gta2_file | 0x45A000 - 0x45F000 | .c, .h |
| 19 | gta2_debug | 0x45F000 - 0x464000 | .c, .h |
| 20 | gta2_other | 0x464000 - конец | .c, .h |

## Как заполнить модули кодом

### Автоматический способ (рекомендуется)

Используй скрипт `extract_functions.ps1` для автоматического извлечения функций по диапазонам адресов:

```powershell
.\extract_functions.ps1
```

### Ручной способ

1. Открой `re_file/Ghidra/gta2.exe.c`
2. Найди функцию по адресу (например, `FUN_00401050`)
3. Скопируй всю функцию от `void FUN_...` до закрывающей `}`
4. Вставь в соответствующий `.c` файл модуля

### Пример

**Исходный код (gta2.exe.c):**
```c
void FUN_00401050(short *param_1,int param_2)
{
  // ... код ...
  return;
}
```

**Вставь в gta2_winmain.c:**
```c
void FUN_00401050(short *param_1, int param_2)
{
  // ... код ...
  return;
}
```

## Статус заполнения

- [ ] gta2_winmain.c
- [ ] gta2_game.c
- [ ] gta2_player.c
- [ ] gta2_ped.c
- [ ] gta2_car.c
- [ ] gta2_menu.c
- [ ] gta2_hud.c
- [ ] gta2_map.c
- [ ] gta2_audio.c
- [ ] gta2_video.c
- [ ] gta2_weapon.c
- [ ] gta2_gang.c
- [ ] gta2_collision.c
- [ ] gta2_sprite.c
- [ ] gta2_mission.c
- [ ] gta2_replay.c
- [ ] gta2_registry.c
- [ ] gta2_file.c
- [ ] gta2_debug.c
- [ ] gta2_other.c

## Примечания

1. **Функции перемешаны** - в оригинальном файле функции из разных диапазонов адресов перемешаны, поэтому ручной подбор может быть трудоёмким

2. **Классы и методы** - методы классов (Game::, Player::, и т.д.) уже сгруппированы по имени класса

3. **Глобальные переменные** - остаются в `gta2.exe.h`, не нужно дублировать

4. **Ссылки между модулями** - если функция из одного модуля вызывает функцию из другого, добавь `#include` соответствующего заголовка

## Компиляция

После заполнения всех модулей создай `CMakeLists.txt` или `.sln` проект с перечислением всех `.c` файлов.

Пример CMakeLists.txt:
```cmake
cmake_minimum_required(VERSION 3.10)
project(GTA2_RE)

set(SOURCES
    gta2_winmain.c
    gta2_game.c
    gta2_player.c
    gta2_ped.c
    gta2_car.c
    gta2_menu.c
    gta2_hud.c
    gta2_map.c
    gta2_audio.c
    gta2_video.c
    gta2_weapon.c
    gta2_gang.c
    gta2_collision.c
    gta2_sprite.c
    gta2_mission.c
    gta2_replay.c
    gta2_registry.c
    gta2_file.c
    gta2_debug.c
    gta2_other.c
)

add_executable(gta2_re ${SOURCES})
target_include_directories(gta2_re PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
```

## Следующие шаги

1. ✅ Создать структуру модулей
2. ⏳ Заполнить модули кодом из gta2.exe.c
3. ⏳ Добавить комментарии к функциям
4. ⏳ Настроить компиляцию
5. ⏳ Протестировать сборку
