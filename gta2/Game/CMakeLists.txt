cmake_minimum_required(VERSION 3.0)
project(MENU LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

# Основная библиотека MENU 
add_subdirectory(Menu)
# Основная библиотека Player
add_subdirectory(Player)
add_subdirectory(Car)
add_subdirectory(Ambulance)
add_subdirectory(Door)
add_subdirectory(Gangs)
add_subdirectory(MapGm)
add_subdirectory(PublicTransport)
add_subdirectory(MissionManager)
add_subdirectory(Map)
add_subdirectory(AudioSourceParams)
add_subdirectory(MapRelatedStruct)

