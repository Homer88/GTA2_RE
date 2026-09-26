project(TextEditor LANGUAGES CXX)

add_executable(TextEditor
	main.cpp
	GxtModel.cpp
	GxtModel.h
	MainWindow.cpp
	MainWindow.h
)

target_link_libraries(TextEditor PRIVATE
	gta2tools
	Qt5::Widgets
)

if(WIN32)
	set_target_properties(TextEditor PROPERTIES WIN32_EXECUTABLE TRUE)
endif()