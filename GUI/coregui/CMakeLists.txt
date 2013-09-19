############################################################################
# CMakeLists.txt file for building coregui
############################################################################

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

cmake_policy(SET CMP0020 NEW)

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
    ${Boost_INCLUDE_DIRS}
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

#core gui script webkit webkitwidgets designer designercomponents
qt5_use_modules(${executable_name} Widgets Core Gui Script WebKit WebKitWidgets Designer)

# --- Installation ---

install (TARGETS ${executable_name} DESTINATION bin COMPONENT Applications)

# system libraries: ROOT installation
if(WIN32)
    install(FILES 
    ${ROOTSYS}/bin/libGpad.dll
    ${ROOTSYS}/bin/libHist.dll
    ${ROOTSYS}/bin/libGraf.dll
    ${ROOTSYS}/bin/libGraf3d.dll
    ${ROOTSYS}/bin/libTree.dll
    ${ROOTSYS}/bin/libRint.dll
    ${ROOTSYS}/bin/libPostscript.dll
    ${ROOTSYS}/bin/libMatrix.dll
    ${ROOTSYS}/bin/libMathCore.dll
    ${ROOTSYS}/bin/libThread.dll
    ${ROOTSYS}/bin/libCore.dll
    ${ROOTSYS}/bin/libCint.dll
    ${ROOTSYS}/bin/libRIO.dll
    ${ROOTSYS}/bin/liblzma.dll
    ${ROOTSYS}/bin/libNet.dll
    ${ROOTSYS}/bin/libGui.dll
    ${ROOTSYS}/bin/libHistPainter.dll
    ${ROOTSYS}/bin/gdk-1.3.dll
    ${ROOTSYS}/bin/glib-1.3.dll
    ${ROOTSYS}/bin/iconv-1.3.dll
    ${ROOTSYS}/bin/libWin32gdk.dll
    ${ROOTSYS}/bin/libAsImage.dll
    DESTINATION bin COMPONENT Libraries)
    
    install(FILES
    ${ROOTSYS}/fonts/FreeSans.otf
    ${ROOTSYS}/fonts/FreeSansBold.otf
    ${ROOTSYS}/fonts/symbol.ttf
    DESTINATION fonts COMPONENT Libraries)
    
    install(FILES
    ${ROOTSYS}/icons/arrow.xpm
    ${ROOTSYS}/icons/arrow_down.xpm
    ${ROOTSYS}/icons/arrow_left.xpm
    ${ROOTSYS}/icons/arrow_right.xpm
    ${ROOTSYS}/icons/arrow_right2.xpm
    ${ROOTSYS}/icons/arrow_up.xpm
    DESTINATION icons COMPONENT Libraries)
    
    install(FILES
    ${ROOTSYS}/etc/system.rootrc
    ${ROOTSYS}/etc/root.mimes
    DESTINATION etc COMPONENT Libraries)
    
    install(DIRECTORY
    ${ROOTSYS}/etc/plugins/TGuiFactory
    ${ROOTSYS}/etc/plugins/TImage
    ${ROOTSYS}/etc/plugins/TView
    ${ROOTSYS}/etc/plugins/TVirtualGraphPainter
    ${ROOTSYS}/etc/plugins/TVirtualHistPainter
    ${ROOTSYS}/etc/plugins/TVirtualPadPainter
    ${ROOTSYS}/etc/plugins/TVirtualPS
    ${ROOTSYS}/etc/plugins/TVirtualStreamerInfo
    ${ROOTSYS}/etc/plugins/TVirtualX
    DESTINATION etc/plugins COMPONENT Libraries)

    # --- Qt ---
    STRING(REGEX REPLACE "\\\\" "/" QTDIR $ENV{QTDIR} ) # Convert C:\root\ to C:/root/

    install(FILES
    ${QTDIR}/bin/Qt5Widgets.DLL
    ${QTDIR}/bin/Qt5Core.dll
    ${QTDIR}/bin/Qt5Gui.dll
    ${QTDIR}/bin/Qt5Script.dll
    ${QTDIR}/bin/Qt5WebKitWidgets.dll
    ${QTDIR}/bin/Qt5Designer.dll
    ${QTDIR}/bin/Qt5Xml.dll
    ${QTDIR}/bin/libGLESv2.dll
    ${QTDIR}/bin/icuin51.dll
    ${QTDIR}/bin/icuuc51.dll
    ${QTDIR}/bin/icudt51.dll
    ${QTDIR}/bin/Qt5Multimedia.dll
    ${QTDIR}/bin/Qt5MultimediaWidgets.dll
    ${QTDIR}/bin/Qt5OpenGL.dll
    ${QTDIR}/bin/Qt5Network.dll
    ${QTDIR}/bin/Qt5PrintSupport.dll
    ${QTDIR}/bin/Qt5Qml.dll
    ${QTDIR}/bin/Qt5Quick.dll
    ${QTDIR}/bin/Qt5Sensors.dll
    ${QTDIR}/bin/Qt5Sql.dll
    ${QTDIR}/bin/Qt5V8.dll
    ${QTDIR}/bin/Qt5WebKit.dll    
    DESTINATION bin COMPONENT Libraries)

    install(FILES
    ${QTDIR}/plugins/platforms/qwindows.dll
    DESTINATION bin/platforms COMPONENT Libraries)

    
endif()

