cmake_minimum_required(VERSION 3.0)
project(DebugLog LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

 # Основная библиотека SYSTEM 
file(GLOB DEBUGLOG_SOURCE "*.cpp")
file(GLOB DEBUGLOG_HEADERS "*.h")






# Сборка  DEBUGLOG
add_library(${PROJECT_NAME} STATIC ${DEBUGLOG_SOURCE} ${DEBUGLOG_HEADERS})