cmake_minimum_required(VERSION 3.0)
project(Text LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

 # Основная библиотека Text 
file(GLOB TEXT_SOURCE "*.cpp")
file(GLOB TEXT_HEADERS "*.h")






# Сборка  Утилитов
add_library(${PROJECT_NAME} STATIC ${TEXT_SOURCE} ${TEXT_HEADERS})