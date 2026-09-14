cmake_minimum_required(VERSION 3.0)
project(sdtool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sdtool sdtool.cpp)
target_link_libraries(sdtool winmm.lib)
target_compile_definitions(sdtool PRIVATE _CRT_SECURE_NO_WARNINGS)