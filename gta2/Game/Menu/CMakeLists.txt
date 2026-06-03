cmake_minimum_required(VERSION 3.0)
project(MENU LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

 # Основная библиотека MENU 
file(GLOB MENU_SOURCE "*.cpp")
file(GLOB MENU_HEADERS "*.h")


file(GLOB PLAYER_HEADERS "../Player/*.h")
file(GLOB MAPGM_HEADERS "../MapGm/*.h")
set(GLOBAL_HEADERS "../global.h")
set(REGISTRY_HEADERS "../../Engine/Registry/Registry.h")
set(TEXTURE_MANAGER_HEADERS "../../Engine/TextureManager/TextureManager.h")
set(UITILIT_HEADERS "../../Engine/ultil/WinApi.h")
set(TEXT_HEADERS "../../Engine/Text/Text.h")
set(FONT_HEADERS "../../Engine/Font/Font.h")
set(FILEMGR_HEADERS "../../Engine/FileMgr/FileMgr.h")
set(KEYBRD_HEADERS "../../Engine/Input/Keybrd.h")
set(KEYSTATUS_HEADERS "../../Engine/Input/KeyState.h")
set(BINK_HEADERS "../../Engine/Bink/Bink.h")
set(BINKBUFFER_HEADERS "../../Engine/Bink/BinkBuffer.h")
# библиотека BINKW32

file(GLOB BINKW32_HEADERS "binkw32/*.h")

include_directories(DIRETX 6.0)
include_directories(WIN_INCLUDE PUBLIC  "ms/win/include")
#target_link_libraries(WIN_LIB STATIC "ms/win/lib")





# Сборка  Menu
add_library(${PROJECT_NAME} STATIC ${MENU_SOURCE} ${MENU_HEADERS} 
				${PLAYER_HEADERS} ${MAPGM_HEADERS} ${GLOBAL_HEADERS} 
				${REGISTRY_HEADERS} ${TEXTURE_MANAGER_HEADERS} 
				${UITILIT_HEADERS} ${TEXT_HEADERS} ${FONT_HEADERS}
			    ${FILEMGR_HEADERS} ${KEYBRD_HEADERS} ${KEYSTATUS_HEADERS}
				${BINK_HEADERS}	${BINKBUFFER_HEADERS}


)