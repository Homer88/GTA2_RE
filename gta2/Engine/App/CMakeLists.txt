cmake_minimum_required(VERSION 3.0)
project(App LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

file(GLOB APP_SOURCE "*.cpp")
file(GLOB APP_HEADERS "*.h")
set(GLOBAL_HEADERS "../../Game/global.h")

# ���ઠ  App
add_library(${PROJECT_NAME} STATIC ${APP_SOURCE} ${APP_HEADERS} ${GLOBAL_HEADERS})
