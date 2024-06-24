cmake_minimum_required (VERSION 3.8)

add_executable (project "project.cpp" "project.hpp")
target_link_libraries(project)

if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET project PROPERTY CXX_STANDART 20)
endif()