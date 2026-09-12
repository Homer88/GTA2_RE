cmake_minimum_required(VERSION 3.0)
project(Movie LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

 # Основная библиотека Movie
file(GLOB Movie_SOURCE "*.cpp")
file(GLOB Movie_HEADERS "*.h")

add_library(${PROJECT_NAME} STATIC ${Movie_SOURCE} ${Movie_HEADERS})
