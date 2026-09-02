cmake_minimum_required(VERSION 3.0)
project(GTA2 LANGUAGES CXX)


# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
# .lib остаются в build/, в bin попадают только .exe и .dll


# Графические библиотеки
add_subdirectory(3dfx)
add_subdirectory(dmaglide)
add_subdirectory(dmavideo)
#add_subdirectory(mmsds3dh)
add_subdirectory(polygon)
add_subdirectory(d3ddll)

# библиотека для воспроизведения видео
add_subdirectory(binkw32)

add_subdirectory(d3dpoly)
# Сама игра 
add_subdirectory(gta2)
# Вьюер ресурсов игры (TGA-меню, позже STY-тайлы/GMP)
add_subdirectory(viewer)
# Конфигуратор
#add_subdirectory(gta2manager)
# Аудио
#add_subdirectory(mms32)
