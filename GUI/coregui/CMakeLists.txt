############################################################################
# CMakeLists.txt file for building libBornAgainGUI library
############################################################################
if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()
if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()
if(POLICY CMP0028)
    cmake_policy(SET CMP0028 NEW)
endif()
set(library_name BornAgainGUI)


# --- source and include files ---
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/Models
    ${CMAKE_CURRENT_SOURCE_DIR}/Views
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/widgetbox
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/SampleDesigner
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/JobWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/IntensityDataWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/InfoWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/MaterialEditor
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/InstrumentWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/SimulationWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/FitWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/PropertyEditor
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/MaskWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/AccordionWidget
)
include_directories(${include_dirs})

file(GLOB source_files
    "mainwindow/*.cpp"
    "utils/*.cpp"
    "Models/*.cpp"
    "Views/*.cpp"
    "Views/SampleDesigner/*.cpp"
    "Views/JobWidgets/*.cpp"
    "Views/IntensityDataWidgets/*.cpp"
    "Views/InfoWidgets/*.cpp"
    "Views/MaterialEditor/*.cpp"
    "Views/InstrumentWidgets/*.cpp"
    "Views/SimulationWidgets/*.cpp"
    "Views/FitWidgets/*.cpp"
    "Views/PropertyEditor/*.cpp"
    "Views/MaskWidgets/*.cpp"
    "Views/AccordionWidget/*.cpp"
)

set(source_widgetbox
    "Views/widgetbox/widgetboxcategorylistview.cpp"
    "Views/widgetbox/widgetboxtreewidget.cpp"
    "Views/widgetbox/widgetbox.cpp"
    "Views/widgetbox/widgetbox_dnditem.cpp"
)
list(APPEND source_files ${source_widgetbox})

file(GLOB include_files
    "mainwindow/*.h"
    "utils/*.h"
    "Models/*.h"
    "Views/*.h"
    "Views/SampleDesigner/*.h"
    "Views/JobWidgets/*.h"
    "Views/IntensityDataWidgets/*.h"
    "Views/InfoWidgets/*.h"
    "Views/MaterialEditor/*.h"
    "Views/InstrumentWidgets/*.h"
    "Views/SimulationWidgets/*.h"
    "Views/FitWidgets/*.h"
    "Views/PropertyEditor/*.h"
    "Views/MaskWidgets/*.h"
    "Views/AccordionWidget/*.h"
)

set(include_widgetbox
    "Views/widgetbox/widgetboxcategorylistview.h"
    "Views/widgetbox/widgetboxtreewidget.h"
    "Views/widgetbox/widgetbox.h"
    "Views/widgetbox/widgetbox_dnditem.h"
    "Views/widgetbox/widgetbox_global.h"
)
list(APPEND include_files ${include_widgetbox})

set(resource_files
    "coregui.qrc"
    "Views/SampleDesigner/SampleDesigner.qrc"
    "Views/MaskWidgets/MaskWidgets.qrc"
    "Views/widgetbox/widgetbox.qrc"
    "Views/AccordionWidget/accordionwidgeticons.qrc"
)


# --- Qt configuration ---------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
qt5_add_resources(RC_SRCS ${resource_files})

# --- definitions ------
if(BORNAGAIN_CRASHHANDLER)
    add_definitions(-DBORNAGAIN_CRASHHANDLER)
endif()

if(BORNAGAIN_TIFF_SUPPORT)
    add_definitions(-DBORNAGAIN_TIFF_SUPPORT)
endif()

if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_CORE_BUILD_DLL")
endif()


# --- making library ---------
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


# --- dependencies ---------
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
    ${PYTHON_LIBRARIES}
    ${Boost_LIBRARIES}
    ${BornAgainCore_LIBRARY}
    ${BornAgainFit_LIBRARY}
)

target_link_libraries(${library_name}
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
#     Qt5::Script
    Qt5::Designer
    Qt5::PrintSupport
    Qt5::Network
)


# --- Installation ---------
install (TARGETS ${library_name} DESTINATION ${destination_lib} COMPONENT Libraries)

if(WIN32)
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
    ${QTDIR}/bin/Qt5Svg.dll
    #${QTDIR}/bin/libGLESv2.dll
    #${QTDIR}/bin/libEGL.dll
    ${QTDIR}/bin/icuin54.dll
    ${QTDIR}/bin/icuuc54.dll
    ${QTDIR}/bin/icudt54.dll
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

    install(FILES
    ${QTDIR}/plugins/iconengines/qsvgicon.dll
    DESTINATION bin/iconengines COMPONENT Libraries)

endif()

