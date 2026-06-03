cmake_minimum_required(VERSION 3.0)
project(Input LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

 # Основная библиотека MENU 
file(GLOB INPUT_SOURCE "*.cpp")
file(GLOB INPUT_HEADERS "*.h")






# Сборка  Утилитов
add_library(${PROJECT_NAME} STATIC ${INPUT_SOURCE} ${INPUT_HEADERS})