cmake_minimum_required(VERSION 3.0)
project(3DFX LANGUAGES CXX)


#стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

set(3DFX_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/d3ddll ${CMAKE_SOURCE_DIR}/dmavideo)
set(GLIDE3X_DIR "F:/SDK/glide3x-3_10_00_30303-lib-win32")
set(GLIDE3X_LIB "${GLIDE3X_DIR}/glide3x.lib")


#библиотеки 3DFX
file(GLOB 3DFX_SOURCE "3dfx.cpp")
file(GLOB 3DFX_HEADERS "*.h")

#lib
add_library(3DFX STATIC ${3DFX_SOURCE} ${3DFX_HEADERS})
target_include_directories(3DFX PRIVATE ${3DFX_INCLUDES})
target_link_libraries(3DFX ${GLIDE3X_LIB})

#dll
add_library(3DFX_SHARED SHARED ${3DFX_SOURCE} ${3DFX_HEADERS})
set_target_properties(3DFX_SHARED PROPERTIES OUTPUT_NAME "3DFX")
target_include_directories(3DFX_SHARED PRIVATE ${3DFX_INCLUDES})
target_link_libraries(3DFX_SHARED ${GLIDE3X_LIB})
