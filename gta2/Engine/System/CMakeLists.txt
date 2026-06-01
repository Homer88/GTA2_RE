cmake_minimum_required(VERSION 3.0)
project(SYSTEM LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

 # Основная библиотека SYSTEM 
file(GLOB SYSTEM_SOURCE "*.cpp")
file(GLOB SYSTEM_HEADERS "*.h")






# Сборка  SYSTEM
add_library(${PROJECT_NAME} STATIC ${SYSTEM_SOURCE} ${SYSTEM_HEADERS})