cmake_minimum_required(VERSION 3.0)
project(MENU LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

 # Основная библиотека MENU 
file(GLOB ULTIL_SOURCE "*.cpp")
file(GLOB ULTIL_HEADERS "*.h")



include_directories(DIRETX 6.0)
include_directories(WIN_INCLUDE PUBLIC  "ms/win/include")
#target_link_libraries(WIN_LIB STATIC "ms/win/lib")





# Сборка  Утилитов
add_library(${PROJECT_NAME} STATIC ${ULTIL_SOURCE} ${ULTIL_HEADERS})