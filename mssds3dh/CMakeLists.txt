cmake_minimum_required(VERSION 3.0)
project(MSSDS3DH LANGUAGES CXX)


#стандарт
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86")


#библиотеки MSSDS3DH Возможно это файл ресурсов
file(GLOB MSSDS3DH_SOURCE "*.cpp")
file(GLOB MSSDS3DH_HEADERS "*.h")

#lib
add_library(MSSDS3DH STATIC ${MSSDS3DH_SOURCE} ${MSSDS3DH_HEADERS})
#dll
add_library(MSSDS3DH SHARED ${MSSDS3DH_SOURCE} ${MSSDS3DH_HEADERS})
