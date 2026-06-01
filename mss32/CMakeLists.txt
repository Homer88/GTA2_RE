cmake_minimum_required(VERSION 3.0)
project(MSS32 LANGUAGES CXX)


#стандарт
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")


#библиотеки MSS32
file(GLOB MSS32_SOURCE "*.cpp")
file(GLOB MSS32_HEADERS "*.h")

#lib
add_library(MSS32 STATIC ${MSS32_SOURCE} ${MSS32_HEADERS})
#dll
add_library(MSS32 SHARED ${MSS32_SOURCE} ${MSS32_HEADERS})
