cmake_minimum_required(VERSION 3.0)
project(D3DDLL LANGUAGES CXX)


#стандарт
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")


#библиотеки D3DDLL
file(GLOB D3DDLL_SOURCE "*.cpp")
file(GLOB D3DDLL_HEADERS "*.h")

#lib
add_library(D3DDLL STATIC ${D3DDLL_SOURCE} ${D3DDLL_HEADERS})
#dll
add_library(D3DDLL SHARED ${D3DDLL_SOURCE} ${D3DDLL_HEADERS})
