project(MapEditor LANGUAGES CXX)

add_executable(MapEditor
	main.cpp
	MainWindow.cpp
	MainWindow.h
)

target_link_libraries(MapEditor PRIVATE
	gta2tools
	Qt5::Widgets
)

if(WIN32)
	set_target_properties(MapEditor PROPERTIES WIN32_EXECUTABLE TRUE)
endif()