project(Map)

add_library(Map STATIC
    Map.cpp
)

target_include_directories(Map PUBLIC .)
