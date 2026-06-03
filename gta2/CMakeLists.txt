cmake_minimum_required(VERSION 3.0)
project(GTA2 LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

add_subdirectory(Engine)
add_subdirectory(Game)

file(GLOB MAIN_SOURCE "Game/main/main.cpp")

add_executable(${PROJECT_NAME} WIN32 ${MAIN_SOURCE})
target_link_libraries(${PROJECT_NAME} SYSTEM RES D3DDLL DMAVIDEO ULTIL BINK version.lib)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/d3ddll ${CMAKE_SOURCE_DIR}/dmavideo)
target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
