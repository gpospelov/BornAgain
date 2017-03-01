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

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

set (CMAKE_AUTOMOC ON)

add_subdirectory (ba3d)
add_subdirectory (main)

# eof
