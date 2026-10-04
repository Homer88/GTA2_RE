cmake_minimum_required(VERSION 3.0)
project(BINKW32 LANGUAGES CXX)


#стандарт
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")


#библиотеки 3DFX
file(GLOB BINKW32_SOURCE "*.cpp")
file(GLOB BINKW32_HEADERS "*.h")

#lib
add_library(BINKW32 STATIC ${BINKW32_SOURCE} ${BINKW32_HEADERS})
#dll
add_library(BINKW32_SHARED SHARED ${BINKW32_SOURCE} ${BINKW32_HEADERS})
set_target_properties(BINKW32_SHARED PROPERTIES OUTPUT_NAME "BINKW32")
# NOTE: Exports.def is intentionally NOT linked yet. gta2.exe statically imports
# 18 _Bink*@N entry points, but main.cpp only defines BinkCheckCursor /
# BinkRestoreCursor, so the def would not resolve. Keep using retail binkw32.dll
# until the decoder is finished.
