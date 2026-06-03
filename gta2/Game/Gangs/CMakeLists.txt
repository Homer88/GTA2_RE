cmake_minimum_required(VERSION 3.0)
project(Gangs LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

 # Основная библиотека MENU 
file(GLOB GANGS_SOURCE "*.cpp")
file(GLOB GANGS_HEADERS "*.h")







# Сборка  Menu
add_library(${PROJECT_NAME} STATIC ${GANGS_SOURCE} ${GANGS_HEADERS} )