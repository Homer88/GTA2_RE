cmake_minimum_required(VERSION 3.0)
project(GTA2 LANGUAGES CXX)


#стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

# оснавная игра 
file(GLOB GTA2_SOURCE "GTA2/*.cpp")
file(GLOB GTA2_HEADERS "GTA2/*.h")

#библиотеки 3DFX
file(GLOB 3DFX_SOURCE "3dfx/*.cpp")
file(GLOB 3DFX_HEADERS "3dfx/*.h")

# библиотеки BINKW32

file(GLOB BINKW32_SOURCE "binkw32/*.cpp")
file(GLOB BINKW32_HEADERS "binkw32/*.h")

# библиотеки D3DDLL
file(GLOB D3DDLL_SOURCE  "D3DDLL/*.cpp")
file(GLOB D3DDLL_HEADERS  "D3DDLL/*.h")

# библиотеки D3DPOLY
file(GLOB D3DPOLY_SOURCE "D3DPOLY/*.cpp")
file(GLOB D3DPOLY_HEADERS "D3DPOLY/*.h")
# библиотеки DMAGLIDE
file(GLOB DMAGLIDE_SOURCE "DMAGLIDE/*.cpp")
file(GLOB DMAGLIDE_HEADERS "DMAGLIDE/*.h")
# библиотеки DMAVIDEO
file(GLOB DMAVIDEO_SOURCE "DMAVIDEO/*.cpp")
file(GLOB DMAVIDEO_HEADERS "DMAVIDEO/*.h")

include_directories(DIRETX 6.0)
include_directories(WIN_INCLUDE PUBLIC  "ms/win/include")
#target_link_libraries(WIN_LIB STATIC "ms/win/lib")


add_library(3DFX STATIC ${3DFX_SOURCE} ${3DFX_HEADERS})
add_library(BINKW32 STATIC ${BINKW32_SOURCE} ${BINKW32_HEADERS})
target_include_directories(BINKW32 PRIVATE ${WIN_INCLUDE})
#target_link_libraries(BINKW32 PRIVATE ${WIN_LIB})
add_library(D3DDLL STATIC ${D3DDLL_SOURCE} ${D3DDLL_HEADERS})
add_library(D3DPOLY STATIC ${D3DPOLY_SOURCE} ${D3DPOLY_HEADERS})
add_library(DMAGLIDE STATIC ${DMAGLIDE_SOURCE} ${D3DPOLY_HEADERS})
add_library(DMAVIDEO STATIC ${DMAVIDEO_SOURCE} ${DMAVIDEO_HEADERS})
add_executable(GTA2 ${GTA2_SOURCE} ${GTA2_HEADERS})



#сборка GTA 2
target_link_libraries(GTA2 3DFX BINKW32 D3DDLL D3DPOLY DMAGLIDE DMAVIDEO)