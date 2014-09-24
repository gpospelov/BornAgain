############################################################################
# CMakeLists.txt file for building coregui
############################################################################

cmake_minimum_required(VERSION 2.8.9 FATAL_ERROR)
if(POLICY CMP0020)
cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
cmake_policy(SET CMP0043 NEW)
endif()
if(POLICY CMP0042)
cmake_policy(SET CMP0042 NEW)
endif()

set(library_name BornAgainGUI)

if(BORNAGAIN_CRASHHADLER)
    add_definitions(-DBORNAGAIN_CRASHHANDLER)
endif()

# --- source and include files ---
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/Models
    ${CMAKE_CURRENT_SOURCE_DIR}/Views
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/Components/widgetbox
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/Components/SampleDesigner
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/Components/JobQueueWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/Components/OutputDataWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/Components/MaterialEditor
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/Components/InstrumentWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/Components/SimulationWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/Components/FitWidgets
)
include_directories(${include_dirs})

file(GLOB source_files
    "mainwindow/*.cpp"
    "utils/*.cpp"
    "Models/*.cpp"
    "Views/*.cpp"
    "Views/Components/SampleDesigner/*.cpp"
    "Views/Components/JobQueueWidgets/*.cpp"
    "Views/Components/OutputDataWidgets/*.cpp"
    "Views/Components/MaterialEditor/*.cpp"
    "Views/Components/InstrumentWidgets/*.cpp"
    "Views/Components/SimulationWidgets/*.cpp"
    "Views/Components/FitWidgets/*.cpp"
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
    "Views/Components/SampleDesigner/*.h"
    "Views/Components/JobQueueWidgets/*.h"
    "Views/Components/OutputDataWidgets/*.h"
    "Views/Components/MaterialEditor/*.h"
    "Views/Components/InstrumentWidgets/*.h"
    "Views/Components/SimulationWidgets/*.h"
    "Views/Components/FitWidgets/*.h"
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
#    "qttools/qtpropertybrowser/qtpropertybrowser.qrc"
    "Views/Components/SampleDesigner/SampleDesigner.qrc"
    "Views/Components/widgetbox/widgetbox.qrc"
)

set(CMAKE_AUTOMOC ON)
qt5_add_resources(RC_SRCS ${resource_files})
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x040900)

if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_CORE_BUILD_DLL")
endif()

#add_executable(${executable_name} ${source_files} ${RC_SRCS} ${include_files})

# --- making library ---
add_library(
    ${library_name}
    SHARED
    ${source_files} ${RC_SRCS} ${include_files}
)
set_Target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${library_name}_LIBRARY_TYPE SHARED)
# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)


qt5_use_modules(${library_name} Widgets Core Gui Script Designer PrintSupport)

# --- dependencies ---
include_directories(
    ${qcustomplot_INCLUDE_DIRS}
    ${qtpropertybrowser_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIR}
    ${BornAgainCore_INCLUDE_DIRS}
    ${BornAgainFit_INCLUDE_DIRS}
    ${ManhattanStyle_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
)


target_link_libraries(${library_name}
    ${ManhattanStyle_LIBRARY}
    ${qcustomplot_LIBRARY}
    ${qtpropertybrowser_LIBRARY}
    ${PYTHON_LIBRARY} 
    ${Boost_LIBRARIES}
    ${BornAgainCore_LIBRARY}
    ${BornAgainFit_LIBRARY}
)

# --- Installation ---
install (TARGETS ${library_name} DESTINATION ${destination_lib} COMPONENT Libraries)
if(APPLE AND CREATE_BUNDLE)
  set(source_files ${source_files} ${CMAKE_SOURCE_DIR}/GUI/main/BornAgainApp.icns)
endif(APPLE AND CREATE_BUNDLE)
# system libraries: ROOT installation
if(WIN32)
#     install(FILES 
#     ${ROOTSYS}/bin/libGpad.dll
#     ${ROOTSYS}/bin/libHist.dll
#     ${ROOTSYS}/bin/libGraf.dll
#     ${ROOTSYS}/bin/libGraf3d.dll
#     ${ROOTSYS}/bin/libTree.dll
#     ${ROOTSYS}/bin/libRint.dll
#     ${ROOTSYS}/bin/libPostscript.dll
#     ${ROOTSYS}/bin/libMatrix.dll
#     ${ROOTSYS}/bin/libMathCore.dll
#     ${ROOTSYS}/bin/libThread.dll
#     ${ROOTSYS}/bin/libCore.dll
#     ${ROOTSYS}/bin/libCint.dll
#     ${ROOTSYS}/bin/libRIO.dll
#     ${ROOTSYS}/bin/liblzma.dll
#     ${ROOTSYS}/bin/libNet.dll
#     ${ROOTSYS}/bin/libGui.dll
#     ${ROOTSYS}/bin/libHistPainter.dll
#     ${ROOTSYS}/bin/gdk-1.3.dll
#     ${ROOTSYS}/bin/glib-1.3.dll
#     ${ROOTSYS}/bin/iconv-1.3.dll
#     ${ROOTSYS}/bin/libWin32gdk.dll
#     ${ROOTSYS}/bin/libAsImage.dll
#     DESTINATION ${destination_lib} COMPONENT Libraries)
#     
#     install(FILES
#     ${ROOTSYS}/fonts/FreeSans.otf
#     ${ROOTSYS}/fonts/FreeSansBold.otf
#     ${ROOTSYS}/fonts/symbol.ttf
#     DESTINATION fonts COMPONENT Libraries)
#     
#     install(FILES
#     ${ROOTSYS}/icons/arrow.xpm
#     ${ROOTSYS}/icons/arrow_down.xpm
#     ${ROOTSYS}/icons/arrow_left.xpm
#     ${ROOTSYS}/icons/arrow_right.xpm
#     ${ROOTSYS}/icons/arrow_right2.xpm
#     ${ROOTSYS}/icons/arrow_up.xpm
#     DESTINATION icons COMPONENT Libraries)
#     
#     install(FILES
#     ${ROOTSYS}/etc/system.rootrc
#     ${ROOTSYS}/etc/root.mimes
#     DESTINATION etc COMPONENT Libraries)
#     
#     install(DIRECTORY
#     ${ROOTSYS}/etc/plugins/TGuiFactory
#     ${ROOTSYS}/etc/plugins/TImage
#     ${ROOTSYS}/etc/plugins/TView
#     ${ROOTSYS}/etc/plugins/TVirtualGraphPainter
#     ${ROOTSYS}/etc/plugins/TVirtualHistPainter
#     ${ROOTSYS}/etc/plugins/TVirtualPadPainter
#     ${ROOTSYS}/etc/plugins/TVirtualPS
#     ${ROOTSYS}/etc/plugins/TVirtualStreamerInfo
#     ${ROOTSYS}/etc/plugins/TVirtualX
#     DESTINATION etc/plugins COMPONENT Libraries)
# 
     # --- Qt ---
     STRING(REGEX REPLACE "\\\\" "/" QTDIR $ENV{QTDIR} ) # Convert C:\Qt\ to C:/Qt/

    install(FILES
    ${QTDIR}/bin/Qt5Widgets.DLL
    ${QTDIR}/bin/Qt5Core.dll
    ${QTDIR}/bin/Qt5Gui.dll
    ${QTDIR}/bin/Qt5Script.dll
    ${QTDIR}/bin/Qt5WebKitWidgets.dll
    ${QTDIR}/bin/Qt5Designer.dll
    ${QTDIR}/bin/Qt5Xml.dll
    #${QTDIR}/bin/libGLESv2.dll
    #${QTDIR}/bin/libEGL.dll    
    ${QTDIR}/bin/icuin52.dll
    ${QTDIR}/bin/icuuc52.dll
    ${QTDIR}/bin/icudt52.dll
    ${QTDIR}/bin/Qt5Multimedia.dll
    ${QTDIR}/bin/Qt5MultimediaWidgets.dll
    ${QTDIR}/bin/Qt5OpenGL.dll
    ${QTDIR}/bin/Qt5Network.dll
    ${QTDIR}/bin/Qt5PrintSupport.dll
    ${QTDIR}/bin/Qt5Qml.dll
    ${QTDIR}/bin/Qt5Quick.dll
    ${QTDIR}/bin/Qt5Sensors.dll
    ${QTDIR}/bin/Qt5Sql.dll
    #${QTDIR}/bin/Qt5V8.dll
    ${QTDIR}/bin/Qt5WebKit.dll    
    DESTINATION ${destination_lib} COMPONENT Libraries)

    install(FILES
    ${QTDIR}/plugins/platforms/qwindows.dll
    DESTINATION bin/platforms COMPONENT Libraries)

    
endif()

