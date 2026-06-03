cmake_minimum_required(VERSION 3.0)
project(Door LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

 # Основная библиотека Door 
file(GLOB DOOR_SOURCE "*.cpp")
file(GLOB DOOR_HEADERS "*.h")







# Сборка  Door
add_library(${PROJECT_NAME} STATIC ${DOOR_SOURCE} ${DOOR_HEADERS} )