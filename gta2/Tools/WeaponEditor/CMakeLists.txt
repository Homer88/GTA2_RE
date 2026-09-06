project(WeaponEditor LANGUAGES CXX)

add_executable(WeaponEditor
	main.cpp
	MainWindow.cpp
	MainWindow.h
)

target_link_libraries(WeaponEditor PRIVATE
	gta2tools
	Qt5::Widgets
)

if(WIN32)
	set_target_properties(WeaponEditor PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
