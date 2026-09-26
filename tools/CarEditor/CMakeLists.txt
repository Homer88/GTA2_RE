project(CarEditor LANGUAGES CXX)

add_executable(CarEditor main.cpp MainWindow.cpp MainWindow.h)

target_link_libraries(CarEditor PRIVATE
	gta2tools
	Qt5::Widgets
)

if(WIN32)
	set_target_properties(CarEditor PROPERTIES WIN32_EXECUTABLE TRUE)
endif()