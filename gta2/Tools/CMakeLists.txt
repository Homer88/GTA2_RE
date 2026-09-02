cmake_minimum_required(VERSION 3.10)
project(GTA2Tools LANGUAGES CXX)

# Набор инструментов GTA2 (редакторы меню/текстов/машин/персонажей/оружия/карты).
# Кросс-платформенный: Qt 5.12+ (Widgets), C++11.

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Исходники с кириллицей (UTF-8) для строк wchar.
if(MSVC)
	add_compile_options(/utf-8)
elseif(MINGW)
	add_compile_options(-finput-charset=UTF-8 -fwide-exec-charset=UTF-16LE)
endif()

find_package(Qt5 5.12 REQUIRED COMPONENTS Widgets)

# Общая библиотека моделей/форматов игры.
add_subdirectory(core)

# Редакторы.
add_subdirectory(MenuEditor)
add_subdirectory(TextEditor)
add_subdirectory(CarEditor)
add_subdirectory(CharEditor)
add_subdirectory(WeaponEditor)
add_subdirectory(MapEditor)