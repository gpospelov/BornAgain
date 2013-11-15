############################################################################
# CMakeLists.txt file for building BornAgain/GUI libraries and executable
############################################################################

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

if(POLICY CMP0020)
cmake_policy(SET CMP0020 NEW)
endif()

find_package(Qt5Widgets REQUIRED)

add_subdirectory(externals/qt-manhattan-style)
add_subdirectory(externals/qt-root)
add_subdirectory(externals/qt-root-gui-factory)
add_subdirectory(coregui)


