# Files Qt5WidgetsConfig.cmake etc are part of the Qt5 sources.
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Designer REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Svg REQUIRED)

message(STATUS "Found Qt5 version ${Qt5Widgets_VERSION}")

if(${Qt5Core_VERSION} VERSION_LESS "5.5.1")
    # required for OpenGL, hence for ba3d
    message (FATAL_ERROR "Qt 5.5.1+ is required, have ${Qt5Core_VERSION_STRING}")
endif()

if(BORNAGAIN_OPENGL)
    find_package(OpenGL)
    find_package(Qt5OpenGL)
    if(NOT ${OpenGL_FOUND} OR NOT ${Qt5OpenGL})
        message(WARNING "OpenGL was not found. Switching 3D support off: BORNAGAIN_OPENGL=OFF.")
        set(BORNAGAIN_OPENGL OFF)
    endif()
endif()

get_target_property(Qt5Widgets_location Qt5::Widgets LOCATION_Release)
message(STATUS "  ${Qt5Widgets_LIBRARIES} ${Qt5Widgets_location}")
get_target_property(Qt5Core_location Qt5::Core LOCATION_Release)
message(STATUS "  ${Qt5Core_LIBRARIES} ${Qt5Core_location}")
get_target_property(Qt5Gui_location Qt5::Gui LOCATION_Release)
message(STATUS "  ${Qt5Gui_LIBRARIES} ${Qt5Gui_location}")
if(BORNAGAIN_OPENGL)
    get_target_property(Qt5OpenGL_location Qt5::OpenGL LOCATION_Release)
    message(STATUS "  ${Qt5OpenGL_LIBRARIES} ${Qt5OpenGL_location}")
endif()

message(STATUS "  Includes: ${Qt5Widgets_INCLUDE_DIRS}")
