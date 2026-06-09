project(AudioSourceParams)

add_library(AudioSourceParams STATIC
    AudioSourceParams.cpp
)

target_include_directories(AudioSourceParams PUBLIC .)
