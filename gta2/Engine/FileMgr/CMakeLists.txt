cmake_minimum_required(VERSION 3.0)
project(FileMgr LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

 # Основная библиотека MENU 
file(GLOB FILEMNG_SOURCE "*.cpp")
file(GLOB FILEMNG_HEADERS "*.h")







# Сборка  FileMng
add_library(${PROJECT_NAME} STATIC ${FILEMNG_SOURCE} ${FILEMNG_HEADERS} )