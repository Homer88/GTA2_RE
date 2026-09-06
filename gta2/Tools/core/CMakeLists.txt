# Набор инструментов GTA2.
# Общая библиотека моделей/форматов игры (без Qt).

add_library(gta2tools STATIC
	MenuDataModel.cpp
	MenuCodeGen.cpp
	GxtFormat.cpp
	CarInfo.cpp
	StyFormat.cpp
	GciFormat.cpp
	WeaponInfo.cpp
	ZoneInfo.cpp
	GmpFile.cpp
	ScrFormat.cpp
	CharInfo.cpp
	CarInfo.h
	StyFormat.h
	GciFormat.h
	GxtFormat.h
	WeaponInfo.h
	ZoneInfo.h
	GmpFile.h
	ScrFormat.h
	CharInfo.h
)

target_include_directories(gta2tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})