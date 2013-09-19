############################################################################
# CMakeLists.txt file for building coregui
############################################################################

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(executable_name coregui)

# --- source and include files ---
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/Models
    ${CMAKE_CURRENT_SOURCE_DIR}/Views
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/Components/widgetbox
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/Components/SampleDesigner
    ${CMAKE_CURRENT_SOURCE_DIR}/qttools/qtpropertybrowser
)
include_directories(${include_dirs})
include_directories(${CMAKE_CURRENT_BINARY_DIR}) # qtpropertybrowser needs some moc files

file(GLOB source_files
    "mainwindow/*.cpp"
    "utils/*.cpp"
    "Models/*.cpp"
    "Views/*.cpp"
#    "Views/Components/widgetbox/*.cpp"
    "Views/Components/SampleDesigner/*.cpp"
    "qttools/qtpropertybrowser/*.cpp"
)

set(source_widgetbox
    "Views/Components/widgetbox/widgetboxcategorylistview.cpp"
    "Views/Components/widgetbox/widgetboxtreewidget.cpp"
    "Views/Components/widgetbox/widgetbox.cpp"
    "Views/Components/widgetbox/widgetbox_dnditem.cpp"
)
list(APPEND source_files ${source_widgetbox})

file(GLOB include_files
    "mainwindow/*.h"
    "utils/*.h"
    "Models/*.h"
    "Views/*.h"
#    "Views/Components/widgetbox/*.h"
    "Views/Components/SampleDesigner/*.h"
    "qttools/qtpropertybrowser/*.h"
)

set(include_widgetbox
    "Views/Components/widgetbox/widgetboxcategorylistview.h"
    "Views/Components/widgetbox/widgetboxtreewidget.h"
    "Views/Components/widgetbox/widgetbox.h"
    "Views/Components/widgetbox/widgetbox_dnditem.h"
    "Views/Components/widgetbox/widgetbox_global.h"
)
list(APPEND include_files ${include_widgetbox})


set(resource_files
    "coregui.qrc"
    "qttools/qtpropertybrowser/qtpropertybrowser.qrc"
    "Views/Components/SampleDesigner/SampleDesigner.qrc"
    "Views/Components/widgetbox/widgetbox.qrc"
)

set(CMAKE_AUTOMOC ON)
qt5_add_resources(RC_SRCS ${resource_files})
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x040900)

add_executable(${executable_name} ${source_files} ${RC_SRCS} ${include_files})

# --- dependencies ---
include_directories(
    ${BornAgainCore_INCLUDE_DIRS}
    ${BornAgainFit_INCLUDE_DIRS}
    ${ROOT_INCLUDE_DIR}
    ${ManhattanStyle_INCLUDE_DIRS}
    ${GQt_INCLUDE_DIRS}
    ${QtRoot_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
)
target_link_libraries(${executable_name}
)

#core gui script webkit webkitwidgets designer designercomponents

target_link_libraries(${executable_name} 
    ${Qt5Widgets_LIBRARIES} 
    ${PYTHON_LIBRARY} 
    ${Boost_LIBRARIES}
    ${ROOT_LIBRARIES}
    ${BornAgainCore_LIBRARY}
    ${BornAgainFit_LIBRARY}
    ${ManhattanStyle_LIBRARY} 
    ${GQt_LIBRARY}
    ${QtRoot_LIBRARY}
)

message("XXX ${ROOT_LIBRARIES}")

#core gui script webkit webkitwidgets designer designercomponents
qt5_use_modules(${executable_name} Widgets Core Gui Script WebKit WebKitWidgets Designer)


