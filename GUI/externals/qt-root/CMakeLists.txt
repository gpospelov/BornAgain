############################################################################
# CMakeLists.txt file for building libGQt
############################################################################

cmake_minimum_required(VERSION 2.8.9)
cmake_policy(SET CMP0020 NEW)

set(library_name GQt)

# source files
file(GLOB source_files "src/*.cxx")
file(GLOB include_files "inc/*.h")

set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${include_dirs})

set(headers inc/TGQt.h inc/TQtTimer.h inc/TQtApplication.h inc/TQtBrush.h
            inc/TQMimeTypes.h inc/TQtClientFilter.h inc/TQtClientWidget.h inc/TQtWidget.h
            inc/TQtMarker.h inc/TQtTimer.h inc/TQtRootSlot.h inc/TQtPadFont.h)

set(CMAKE_AUTOMOC ON)
#QT5_WRAP_CPP(mocfiles "inc/TQtWidget.h" "inc/TQtEmitter.h" "inc/TQtClientFilter.h"
#                      inc/TQtClientGuard.h" "inc/TQtClientWidget.h" "inc/TQtTimer.h"
#                      inc/TQtRootSlot.h)

#find_package(Qt5Widgets REQUIRED)

ROOT_GENERATE_DICTIONARY(G__GQt ${headers} LINKDEF LinkDef.h)
ROOT_GENERATE_DICTIONARY(AppDict    inc/DrawHelper.h inc/TreeEventStructure.h  LINKDEF AppLinkDef.h)

# --- making library ---
add_library(
    ${library_name}
    STATIC
    ${source_files} ${include_files} ${mocfiles} G__GQt.cxx
)
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)

# --- dependencies ---
include_directories(
    ${ROOT_INCLUDE_DIR}
)

target_link_libraries(${library_name} ${ROOT_LIBRARIES})
qt5_use_modules(${library_name} Widgets)



