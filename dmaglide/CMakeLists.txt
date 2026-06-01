cmake_minimum_required(VERSION 3.0)
project(DMAGLIDE LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

set(GLIDE3X_DIR "F:/SDK/glide3x-3_10_00_30303-lib-win32")
set(GLIDE3X_LIB "${GLIDE3X_DIR}/glide3x.lib")

file(GLOB DMAGLIDE_SOURCE "*.cpp")
file(GLOB DMAGLIDE_HEADERS "*.h")

# lib
add_library(DMAGLIDE STATIC ${DMAGLIDE_SOURCE} ${DMAGLIDE_HEADERS})
target_include_directories(DMAGLIDE PRIVATE ../3dfx)
target_link_libraries(DMAGLIDE PRIVATE 3DFX ${GLIDE3X_LIB})

# dll
add_library(DMAGLIDE_SHARED SHARED ${DMAGLIDE_SOURCE} ${DMAGLIDE_HEADERS})
set_target_properties(DMAGLIDE_SHARED PROPERTIES OUTPUT_NAME "DMAGLIDE")
target_include_directories(DMAGLIDE_SHARED PRIVATE ../3dfx)
target_link_libraries(DMAGLIDE_SHARED PRIVATE 3DFX ${GLIDE3X_LIB})
