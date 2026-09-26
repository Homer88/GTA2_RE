project(MenuEditor LANGUAGES CXX)

# Редактор меню: живой предпросмотр страниц (640x480) с редактированием текста,
# позиций и логики переходов; сохранение в JSON и экспорт в C++ класса меню.

set(CMAKE_AUTOMOC ON)

add_executable(MenuEditor
  main.cpp
  MenuJson.cpp
  MenuJson.h
  MenuScene.cpp
  MenuScene.h
  MainWindow.cpp
  MainWindow.h
)

target_link_libraries(MenuEditor PRIVATE gta2tools Qt5::Widgets)

if(WIN32)
  set_target_properties(MenuEditor PROPERTIES WIN32_EXECUTABLE TRUE)
endif()