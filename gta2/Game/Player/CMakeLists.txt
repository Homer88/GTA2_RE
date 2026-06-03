cmake_minimum_required(VERSION 3.0)
project(Player LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

 # Основная библиотека MENU 
file(GLOB PLAYER_SOURCE "*.cpp")
file(GLOB PLAYER_HEADERS "*.h")






# Сборка  Menu
add_library(${PROJECT_NAME} STATIC ${PLAYER_SOURCE} ${PLAYER_HEADERS} )