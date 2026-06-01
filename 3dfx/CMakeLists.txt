cmake_minimum_required(VERSION 3.0)
project(3DFX LANGUAGES CXX)


#стандарт
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")


#библиотеки 3DFX
file(GLOB 3DFX_SOURCE "*.cpp")
file(GLOB 3DFX_HEADERS "*.h")

#lib
add_library(3DFX STATIC ${3DFX_SOURCE} ${3DFX_HEADERS})
#dll
add_library(3DFX SHARED ${3DFX_SOURCE} ${3DFX_HEADERS})
