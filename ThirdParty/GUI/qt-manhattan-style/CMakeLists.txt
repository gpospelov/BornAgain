############################################################################
# CMakeLists.txt file for building libManhattanStyle
############################################################################
if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()

set(library_name ManhattanStyle)

set(SRCS
    stylehelper.cpp
    styledbar.cpp
    styleanimator.cpp
    stringutils.cpp
    qtcolorbutton.cpp
    qtcassert.cpp
    progressbar.cpp
    minisplitter.cpp
    manhattanstyle.cpp
    historycompleter.cpp
    fancytabwidget.cpp
    fancymainwindow.cpp
    fancylineedit.cpp
    fancyactionbar.cpp
    doubletabwidget.cpp
    extensions/simpleprogressbar.cpp
    stylehelper.h
    styledbar.h
    styleanimator.h
    stringutils.h
    qtcolorbutton.h
    qtcolorbutton_p.h
    qtcassert.h
    progressbar.h
    minisplitter.h
    manhattanstyle.h
    historycompleter.h
    fancytabwidget.h
    fancymainwindow.h
    fancylineedit.h
    fancyactionbar.h
    doubletabwidget.h
    coreconstants.h
    qt-manhattan-style_global.hpp
    extensions/simpleprogressbar.h
    extensions/tabwidget.h
    extensions/tabwidget.cpp
    extensions/threelevelsitempicker.h
    extensions/threelevelsitempicker.cpp
)

set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${include_dirs})

set(RCS
    resources/resources.qrc
)

set(UI_FILES
    doubletabwidget.ui
)

# --- Qt5 ---------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

qt5_wrap_ui(UI_HDRS ${UI_FILES})

# --- definitions ---------
add_definitions(-DQTMANHATTANSTYLE_LIBRARY)


# --- library ---------
add_library(${library_name} STATIC ${SRCS} ${UI_HDRS} ${RCS})
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)


# --- dependencies ---------
target_link_libraries(${library_name} ${Qt5Widgets_LIBRARIES})
target_link_libraries(${library_name} Qt5::Widgets)


