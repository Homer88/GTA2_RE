project(CharEditor LANGUAGES CXX)

add_executable(CharEditor
	main.cpp
	MainWindow.cpp
	MainWindow.h
)

target_include_directories(CharEditor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CharEditor PRIVATE
	gta2tools
	Qt5::Widgets
)

if(WIN32)
	set_target_properties(CharEditor PROPERTIES WIN32_EXECUTABLE TRUE)
endif()