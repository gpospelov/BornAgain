############################################################################
# CMakeLists.txt file for building BornAgain/GUI libraries and executable
############################################################################

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

if(POLICY CMP0020)
cmake_policy(SET CMP0020 NEW)
endif()

find_package(Qt5Widgets REQUIRED)

add_subdirectory(externals/qt-manhattan-style)
add_subdirectory(externals/qcustomplot)
add_subdirectory(externals/qtpropertybrowser)
add_subdirectory(coregui)
add_subdirectory(main)

set(BornAgainGUI_INCLUDE_DIRS ${BornAgainGUI_INCLUDE_DIRS} PARENT_SCOPE)
set(BornAgainGUI_LIBRARY ${BornAgainGUI_LIBRARY} PARENT_SCOPE)
