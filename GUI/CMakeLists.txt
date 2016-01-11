############################################################################
# CMakeLists.txt file for building BornAgain/GUI libraries and executable
############################################################################
if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()

message(STATUS "Configuring BornAgain GUI")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
#find_package(Qt5Script REQUIRED)
find_package(Qt5Designer REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Network REQUIRED)

if(${Qt5Widgets_FOUND})
    message(STATUS "  Found Qt5 version ${Qt5Widgets_VERSION_STRING}")
    get_target_property(Qt5Widgets_location Qt5::Widgets LOCATION_Release)
    message(STATUS "  ${Qt5Widgets_LIBRARIES} ${Qt5Widgets_location}")
    get_target_property(Qt5Core_location Qt5::Core LOCATION_Release)
    message(STATUS "  ${Qt5Core_LIBRARIES} ${Qt5Core_location}")
    get_target_property(Qt5Gui_location Qt5::Gui LOCATION_Release)
    message(STATUS "  ${Qt5Gui_LIBRARIES} ${Qt5Gui_location}")
    message(STATUS "  Includes: ${Qt5Widgets_INCLUDE_DIRS}")
endif()

add_subdirectory(externals/qt-manhattan-style)
add_subdirectory(externals/qcustomplot)
add_subdirectory(externals/qtpropertybrowser)
add_subdirectory(coregui)

if(BORNAGAIN_CRASHHANDLER)
    add_definitions(-DBORNAGAIN_CRASHHANDLER)
    add_subdirectory(crashhandler)
endif()

add_subdirectory(main)

set(BornAgainGUI_INCLUDE_DIRS ${BornAgainGUI_INCLUDE_DIRS} PARENT_SCOPE)
set(BornAgainGUI_LIBRARY ${BornAgainGUI_LIBRARY} PARENT_SCOPE)
