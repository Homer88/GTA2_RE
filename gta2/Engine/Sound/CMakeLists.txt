cmake_minimum_required(VERSION 3.0)
project(SOUND LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

# Звуковой движок (банки sdt/raw, waveOut)
file(GLOB SOUND_SOURCE "*.cpp")
file(GLOB SOUND_HEADERS "*.h")

add_library(${PROJECT_NAME} STATIC ${SOUND_SOURCE} ${SOUND_HEADERS})
target_link_libraries(${PROJECT_NAME} winmm)
target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)