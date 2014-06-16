cmake_minimum_required(VERSION 2.8.9 FATAL_ERROR)

if(POLICY CMP0020)
cmake_policy(SET CMP0020 NEW)
endif()

set(executable_name GUIExample01)

# --- source and include files ---
set(include_dirs
#    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow
    ${CMAKE_SOURCE_DIR}/GUI/coregui/utils
    ${CMAKE_SOURCE_DIR}/GUI/coregui/Models
#    ${CMAKE_CURRENT_SOURCE_DIR}/Views
#    ${CMAKE_CURRENT_SOURCE_DIR}/Views/Components/widgetbox
#    ${CMAKE_CURRENT_SOURCE_DIR}/Views/Components/SampleDesigner
#    ${CMAKE_CURRENT_SOURCE_DIR}/Views/Components/JobQueueWidgets
#    ${CMAKE_CURRENT_SOURCE_DIR}/Views/Components/OutputDataWidgets
    ${CMAKE_SOURCE_DIR}/GUI/coregui/Views/Components/MaterialEditor
#    ${CMAKE_CURRENT_SOURCE_DIR}/Views/Components/InstrumentWidgets
)
include_directories(${include_dirs})

file(GLOB source_files
    "*.cpp"
    "${CMAKE_SOURCE_DIR}/GUI/coregui/utils/*.cpp"
    "${CMAKE_SOURCE_DIR}/GUI/coregui/Models/*.cpp"
#    "Views/*.cpp"
#    "Views/Components/SampleDesigner/*.cpp"
#    "Views/Components/JobQueueWidgets/*.cpp"
#    "Views/Components/OutputDataWidgets/*.cpp"
    "${CMAKE_SOURCE_DIR}/GUI/coregui/Views/Components/MaterialEditor/*.cpp"
#    "Views/Components/InstrumentWidgets/*.cpp"
)

#set(source_widgetbox
#    "Views/Components/widgetbox/widgetboxcategorylistview.cpp"
#    "Views/Components/widgetbox/widgetboxtreewidget.cpp"
#    "Views/Components/widgetbox/widgetbox.cpp"
#    "Views/Components/widgetbox/widgetbox_dnditem.cpp"
#)
#list(APPEND source_files ${source_widgetbox})

file(GLOB include_files
#    "mainwindow/*.h"
    "${CMAKE_SOURCE_DIR}/GUI/coregui/utils/*.h"
    "${CMAKE_SOURCE_DIR}/GUI/coregui/Models/*.h"
#    "Views/*.h"
#    "Views/Components/SampleDesigner/*.h"
#    "Views/Components/JobQueueWidgets/*.h"
#    "Views/Components/OutputDataWidgets/*.h"
    "${CMAKE_SOURCE_DIR}/GUI/coregui/Views/Components/MaterialEditor/*.h"
#    "Views/Components/InstrumentWidgets/*.h"
)

#set(include_widgetbox
#    "Views/Components/widgetbox/widgetboxcategorylistview.h"
#    "Views/Components/widgetbox/widgetboxtreewidget.h"
#    "Views/Components/widgetbox/widgetbox.h"
#    "Views/Components/widgetbox/widgetbox_dnditem.h"
#    "Views/Components/widgetbox/widgetbox_global.h"
#)
#list(APPEND include_files ${include_widgetbox})


#set(resource_files
#    "coregui.qrc"
##    "qttools/qtpropertybrowser/qtpropertybrowser.qrc"
#    "Views/Components/SampleDesigner/SampleDesigner.qrc"
#    "Views/Components/widgetbox/widgetbox.qrc"
#)

message("XXX 1.1 ${executable_name} ${source_files} ${include_files}")

set(CMAKE_AUTOMOC ON)
qt5_add_resources(RC_SRCS ${resource_files})
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x040900)

#add_executable(${executable_name} ${source_files} ${RC_SRCS} ${include_files})
add_executable(${executable_name} ${source_files} ${include_files})

qt5_use_modules(${executable_name} Widgets Core Gui Script Designer PrintSupport)

# --- dependencies ---
include_directories(
#    ${qcustomplot_INCLUDE_DIRS}
    ${qtpropertybrowser_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${BornAgainFit_INCLUDE_DIRS}
#    ${ManhattanStyle_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
)


target_link_libraries(${executable_name}
#    ${ManhattanStyle_LIBRARY}
#    ${qcustomplot_LIBRARY}
    ${qtpropertybrowser_LIBRARY}
    ${PYTHON_LIBRARY}
    ${Boost_LIBRARIES}
    ${BornAgainCore_LIBRARY}
    ${BornAgainFit_LIBRARY}
)

