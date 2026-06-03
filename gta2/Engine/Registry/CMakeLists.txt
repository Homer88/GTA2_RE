cmake_minimum_required(VERSION 3.0)
project(Registry LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

 # Основная библиотека MENU 
file(GLOB REGISTRY_SOURCE "*.cpp")
file(GLOB REGISTRY_HEADERS "*.h")






# Сборка  Утилитов
add_library(${PROJECT_NAME} STATIC ${REGISTRY_SOURCE} ${REGISTRY_HEADERS})