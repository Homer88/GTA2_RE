cmake_minimum_required(VERSION 3.0)
project(DMAGDI LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

file(GLOB DMAVIDEO_SOURCE "*.cpp")
file(GLOB DMAVIDEO_HEADERS "*.h")

add_library(DMAGDI_SHARED SHARED ${DMAVIDEO_SOURCE} ${DMAVIDEO_HEADERS})
set_target_properties(DMAGDI_SHARED PROPERTIES OUTPUT_NAME "dmagdi")
# Vid_* device layer contract, identical to retail dmaglide.dll.
set_target_properties(DMAGDI_SHARED PROPERTIES LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/Exports.def")
