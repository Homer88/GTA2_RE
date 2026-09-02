cmake_minimum_required(VERSION 3.0)
project(DMAudio LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

# Публичный интерфейс звука (DMAudio facade). Полагается на движок SOUND.
file(GLOB DMAUDIO_SOURCE "*.cpp")
file(GLOB DMAUDIO_HEADERS "*.h")

add_library(${PROJECT_NAME} STATIC ${DMAUDIO_SOURCE} ${DMAUDIO_HEADERS})
target_link_libraries(${PROJECT_NAME} SOUND)