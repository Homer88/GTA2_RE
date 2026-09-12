cmake_minimum_required(VERSION 3.0)
project(TextureManager LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

 # Основная библиотека TextureManager
file(GLOB TextureManager_SOURCE "*.cpp")
file(GLOB TextureManager_HEADERS "*.h")

add_library(${PROJECT_NAME} STATIC ${TextureManager_SOURCE} ${TextureManager_HEADERS})
