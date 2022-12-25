# CMakeList.txt : CMake project for Target, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.22)

project ("ZwDetectMemoryRead")

# ------------for ZwDetectMemoryRead----------
add_executable (${PROJECT_NAME} "ZwDetectMemoryRead/main.h" "ZwDetectMemoryRead/main.cpp")

# --------for NullifyZwDetectMemoryRead------------
include_directories(${CMAKE_CURRENT_LIST_DIR}/NullifyZwDetectMemoryRead/minhook/include)
FILE(GLOB_RECURSE MINHOOK_SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/NullifyZwDetectMemoryRead/minhook/src/*.c)
FILE(GLOB_RECURSE MINHOOK_HEADER CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/NullifyZwDetectMemoryRead/minhook/src/*.h)
FILE(GLOB_RECURSE MINHOOK_HDE_SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/NullifyZwDetectMemoryRead/minhook/src/hde/*.c)
FILE(GLOB_RECURSE MINHOOK_HDE_HEADER CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/NullifyZwDetectMemoryRead/minhook/src/hde/*.h)

add_library (NullifyZwDetectMemoryRead SHARED "NullifyZwDetectMemoryRead/dllmain.cpp" "NullifyZwDetectMemoryRead/dllmain.cpp" ${MINHOOK_SOURCE} ${MINHOOK_HEADER} ${MINHOOK_HDE_SOURCE} ${MINHOOK_HDE_HEADER})
target_compile_features(NullifyZwDetectMemoryRead PRIVATE cxx_std_20)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

# TODO: Add tests and install targets if needed.
