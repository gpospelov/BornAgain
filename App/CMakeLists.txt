############################################################################
# CMakeLists.txt file for building BornAgain/App executable
############################################################################

cmake_minimum_required(VERSION 2.8.3 FATAL_ERROR)

set(executable_name App)

# source files
file(GLOB source_files "src/*.cpp")

# to get rid from files generated via qmake compilation
#list(REMOVE_ITEM source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/AppDict.cpp)

# include files
file(GLOB include_files "inc/*.h")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
endif()

# data files are required by App for comparison
#execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Tests/ReferenceData/IsGISAXS ${CMAKE_BINARY_DIR}/Tests/ReferenceData/IsGISAXS)

# dictionaries
ROOT_GENERATE_DICTIONARY(AppDict inc/DrawHelper.h inc/TreeEventStructure.h  LINKDEF AppLinkDef.h)

add_executable(${executable_name} ${source_files} AppDict.cxx ${include_files})

# --- dependencies ---
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${BornAgainFit_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${ROOT_INCLUDE_DIR}
)
target_link_libraries(${executable_name}
    ${Boost_LIBRARIES}
    ${BornAgainCore_LIBRARY}
    ${BornAgainFit_LIBRARY}
    ${ROOT_LIBRARIES}
)

# --- Installation ---
install (TARGETS ${executable_name} DESTINATION ${destination_bin} COMPONENT Applications)
#install (DIRECTORY ${CMAKE_SOURCE_DIR}/Tests/ReferenceData/IsGISAXS DESTINATION Tests/ReferenceData COMPONENT Applications)

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
        
endif()



