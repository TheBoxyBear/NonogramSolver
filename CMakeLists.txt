# NonogramSolver

cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

project(NonogramSolver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(Engine)
add_subdirectory(Debug)

if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Debug)
endif()
