project(CharEditor LANGUAGES CXX)

add_executable(CharEditor main.cpp)

target_link_libraries(CharEditor PRIVATE
	gta2tools
	Qt5::Widgets
)

if(WIN32)
	set_target_properties(CharEditor PROPERTIES WIN32_EXECUTABLE TRUE)
endif()