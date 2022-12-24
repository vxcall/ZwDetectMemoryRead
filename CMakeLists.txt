# CMakeList.txt : CMake project for Target, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("ZwDetectMemoryRead")

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "main.cpp" "main.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
