############################################################################
# CMakeLists.txt file for building qcustomplot static library
############################################################################
if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()
set(library_name qcustomplot)

set(source_files qcustomplot.h qcustomplot.cpp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_library(
    ${library_name}
    STATIC
    ${source_files} ${mocfiles}
)
set(${library_name}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)

target_link_libraries(${library_name} ${Qt5Widgets_LIBRARIES})

target_link_libraries(${library_name}
    Qt5::Widgets
    Qt5::PrintSupport
)
