cmake_minimum_required(VERSION 2.8.9)

set(library_name qcustomplot)

set(source_files qcustomplot.h qcustomplot.cpp)

set(CMAKE_AUTOMOC ON)

add_library(
    ${library_name}
    STATIC
    ${source_files} ${mocfiles}
)
set(${library_name}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)

target_link_libraries(${library_name} ${Qt5Widgets_LIBRARIES})

qt5_use_modules(${library_name} Widgets PrintSupport)

