cmake_minimum_required(VERSION 3.0)
project(GTA2VIEWER LANGUAGES CXX)

# стандарт
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_M_IX86 -D_CRT_SECURE_NO_WARNINGS")

# Путь к DirectX 6 SDK (можно переопределить: -DDX6_SDK=...)
if(NOT DX6_SDK)
  set(DX6_SDK "D:/SDK/DirectX/D6" CACHE PATH "DirectX 6 SDK root")
endif()

set(VIEWER_SOURCE
  main.cpp
  DrawDevice.cpp
  ${CMAKE_SOURCE_DIR}/gta2/Engine/Res/TGA.cpp
)

add_executable(${PROJECT_NAME} WIN32 ${VIEWER_SOURCE})

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/gta2/Engine/Res
  ${DX6_SDK}/include
)

target_link_directories(${PROJECT_NAME} PRIVATE ${DX6_SDK}/lib)

target_link_libraries(${PROJECT_NAME} PRIVATE
  ddraw.lib
  dxguid.lib
  user32.lib
  gdi32.lib
)
