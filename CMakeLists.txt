set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")


cmake_minimum_required(VERSION 3.0.0)
project(gtk-python-test VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(PkgConfig REQUIRED)
pkg_check_modules(PYTHON3 REQUIRED IMPORTED_TARGET python3-embed)
pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0)

add_executable(gtk src/main.c)

target_link_libraries(
	gtk PUBLIC
	PkgConfig::PYTHON3
	PkgConfig::GTK3
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
