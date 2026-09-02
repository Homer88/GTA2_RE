# Набор инструментов GTA2.
# Общая библиотека моделей/форматов игры (без Qt).

add_library(gta2tools STATIC
	MenuDataModel.cpp
	MenuCodeGen.cpp
	GxtFormat.cpp
	GxtFormat.h
)

target_include_directories(gta2tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})