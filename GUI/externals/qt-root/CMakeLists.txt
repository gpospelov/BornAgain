############################################################################
# CMakeLists.txt file for building libqt-root
############################################################################

cmake_minimum_required(VERSION 2.8.9)
set(library_name qt-root)

# source files
file(GLOB source_files "src/*.cxx")
file(GLOB include_files "inc/*.h")

set(include_dirs "inc")
include_directories(${include_dirs})

set(headers inc/TGQt.h inc/TQtTimer.h inc/TQtApplication.h inc/TQtBrush.h
            inc/TQMimeTypes.h inc/TQtClientFilter.h inc/TQtClientWidget.h inc/TQtWidget.h
            inc/TQtMarker.h inc/TQtTimer.h inc/TQtRootSlot.h inc/TQtPadFont.h)

set(CMAKE_AUTOMOC ON)
#QT5_WRAP_CPP(mocfiles "inc/TQtWidget.h" "inc/TQtEmitter.h" "inc/TQtClientFilter.h"
#                      inc/TQtClientGuard.h" "inc/TQtClientWidget.h" "inc/TQtTimer.h"
#                      inc/TQtRootSlot.h)

find_package(Qt5Widgets REQUIRED)

ROOT_GENERATE_DICTIONARY(G__GQt ${headers} LINKDEF LinkDef.h)
ROOT_GENERATE_DICTIONARY(AppDict    inc/DrawHelper.h inc/TreeEventStructure.h  LINKDEF AppLinkDef.h)

add_library(
    ${library_name}
    SHARED
    ${source_files} ${include_files} ${mocfiles} G__GQt.cxx
)


include_directories(
    ${ROOT_INCLUDE_DIR}
)

target_link_libraries(${library_name} ${ROOT_LIBRARIES})
qt5_use_modules(${library_name} Widgets)

