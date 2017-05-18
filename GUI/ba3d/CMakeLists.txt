project (ba3d)
cmake_minimum_required (VERSION 3.1 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 11)
if (CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets OpenGL)

if (${Qt5Core_VERSION_STRING} VERSION_LESS "5.5.1")
  message (FATAL_ERROR "Qt 5.5.1+ is required, have ${Qt5Core_VERSION_STRING}")
endif ()

set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${include_dirs})

set (CMAKE_AUTOMOC ON)

add_subdirectory (ba3d)
# add_subdirectory (main)
add_subdirectory (demo)

set(library_name ba3d)
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)

# eof
