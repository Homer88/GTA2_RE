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
add_library(BINKW32 SHARED ${BINKW32_SOURCE} ${BINKW32_HEADERS})
