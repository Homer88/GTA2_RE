cmake_minimum_required(VERSION 3.0)
project(D3DDLL LANGUAGES CXX)


#стандарт
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")


#библиотеки D3DDLL
file(GLOB D3DDLL_SOURCE "*.cpp")
file(GLOB D3DDLL_HEADERS "*.h")

#lib
add_library(D3DDLL STATIC ${D3DDLL_SOURCE} ${D3DDLL_HEADERS})
target_include_directories(D3DDLL PRIVATE ${CMAKE_SOURCE_DIR})
#dll
add_library(D3DDLL_SHARED SHARED ${D3DDLL_SOURCE} ${D3DDLL_HEADERS})
set_target_properties(D3DDLL_SHARED PROPERTIES OUTPUT_NAME "D3DDLL")
# gta2.exe resolves the gbh_* back-end via GetProcAddress, so they must be
# exported under their plain C names (see ..\..\games\GTA2 _old\3dfx.dll).
set_target_properties(D3DDLL_SHARED PROPERTIES LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/Exports.def")
target_include_directories(D3DDLL_SHARED PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(D3DDLL PRIVATE ${CMAKE_SOURCE_DIR})
