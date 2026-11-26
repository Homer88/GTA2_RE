project(gbh LANGUAGES CXX)

add_library(gbh STATIC gbh.cpp)
target_compile_definitions(gbh PRIVATE _CRT_SECURE_NO_WARNINGS)
