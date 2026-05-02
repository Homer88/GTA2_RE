cmake_minimum_required(VERSION 3.0)
project(MENU LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

 # Основная библиотека MENU 
file(GLOB MENU_SOURCE "*.cpp")
file(GLOB MENU_HEADERS "*.h")


file(GLOB PLAYER_HEADERS "../Player/*.h")
file(GLOB MAPGM_HEADERS "../MapGm/*.h")
set(GLOBAL_HEADERS "../global.h")
set(REGISTRY_HEADERS "../Registry/Registry.h")
set(TEXTURE_MANAGER_HEADERS "../TextureManager/TextureManager.h")
set(UITILIT_HEADERS "../ultil/WinApi.h")
# библиотека BINKW32

file(GLOB BINKW32_HEADERS "binkw32/*.h")

include_directories(DIRETX 6.0)
include_directories(WIN_INCLUDE PUBLIC  "ms/win/include")
#target_link_libraries(WIN_LIB STATIC "ms/win/lib")





# Сборка  Menu
add_library(${PROJECT_NAME} STATIC ${MENU_SOURCE} ${MENU_HEADERS} ${PLAYER_HEADERS} ${MAPGM_HEADERS} ${GLOBAL_HEADERS} ${REGISTRY_HEADERS} ${TEXTURE_MANAGER_HEADERS} ${UITILIT_HEADERS})