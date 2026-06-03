cmake_minimum_required(VERSION 3.0)
project(ENGINE LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

# Video
#add_subdirectory(video)
#add_subdirectory(display)
#клавиатура
#add_subdirectory(input) 
#сеть
#add_subdirectory(network)
#реестр
#add_subdirectory(Register)
#ресурсы 
#add_subdirectory(text)
#add_subdirectory(TextureManager)

#file 
#add_subdirectory(FileManager)
# Bink
add_subdirectory(bink)
# Debug
add_subdirectory(Debug)
add_subdirectory(System)
add_subdirectory(Registry)
add_subdirectory(Input)
add_subdirectory(Font)
add_subdirectory(Text)
#Ультитилы 
add_subdirectory(ultil)
# ресурсы
add_subdirectory(Res)
add_subdirectory(FileMgr)

#lib
#target_include_directories(ENGINE PRIVATE  System)
