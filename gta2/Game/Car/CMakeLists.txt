cmake_minimum_required(VERSION 3.0)
project(Car LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

 # Основная библиотека Car 
file(GLOB CAR_SOURCE "*.cpp")
file(GLOB CAR_HEADERS "*.h")

set(GLOBAL_HEADERS "../global.h")





# Сборка  Menu
add_library(${PROJECT_NAME} STATIC ${CAR_SOURCE} ${CAR_HEADERS} ${GLOBAL_HEADERS})