cmake_minimum_required(VERSION 3.0)
project(MATCH LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

# Публичный интерфейс Математики.
file(GLOB MATCH_SOURCE "*.cpp")
file(GLOB MATCH_HEADERS "*.h")

add_library(${PROJECT_NAME} STATIC ${MATCH_SOURCE} ${MATCH_HEADERS})