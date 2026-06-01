cmake_minimum_required(VERSION 3.0)
project(GTA2 LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")


# Графические библиотеки
add_subdirectory(3dfx)
add_subdirectory(dmaglide)
add_subdirectory(dmavideo)
add_subdirectory(mmsds3dh)
add_subdirectory(polygon)
add_subdirectory(d3ddll)

# библиотека для воспроизведения видео
add_subdirectory(binkw32)

add_subdirectory(d3dpoly)
# Сама игра 
add_subdirectory(gta2)
# Конфигуратор
add_subdirectory(gta2manager)
# Аудио
add_subdirectory(mms32)
