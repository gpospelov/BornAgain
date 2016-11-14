############################################################################
# CMakeLists.txt file for building static qtpropertybrowser library from qtsolutions
############################################################################
if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()
set(library_name qtpropertybrowser)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR} # qtpropertybrowser needs some moc files
)

include_directories(${include_dirs})

set(resource_files
    "qtpropertybrowser.qrc"
)


# --- definitions ---------
if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-overloaded-virtual")
endif()


# --- Qt configuration ---------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
qt5_add_resources(RC_SRCS ${resource_files})


# --- library ---------
add_library(
    ${library_name}
    STATIC
    ${source_files} ${include_files} ${RC_SRCS} ${mocfiles}
)
set(${library_name}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)


# --- dependencies ---------
target_link_libraries(${library_name} ${Qt5Widgets_LIBRARIES})
target_link_libraries(${library_name} Qt5::Widgets)


