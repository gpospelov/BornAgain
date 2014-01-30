cmake_minimum_required(VERSION 2.8.9)

set(library_name qtpropertybrowser)


file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR} # qtpropertybrowser needs some moc files
)

include_directories(${include_dirs})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-overloaded-virtual")

set(resource_files
    "qtpropertybrowser.qrc"
)

set(CMAKE_AUTOMOC ON)
qt5_add_resources(RC_SRCS ${resource_files})
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x040900)

add_library(
    ${library_name}
    STATIC
    ${source_files} ${include_files} ${RC_SRCS} ${mocfiles}
)
set(${library_name}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)

target_link_libraries(${library_name} ${Qt5Widgets_LIBRARIES})

qt5_use_modules(${library_name} Widgets)


