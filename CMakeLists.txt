###########################################################################
# top-level CMakeLists.txt for building BornAgain
############################################################################

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(BornAgain)

# --- The version number ---
include(VERSION.cmake)

# --- General project settings ---
option(BORNAGAIN_PYTHON "Build with python support" ON)
option(BORNAGAIN_USE_PYTHON3 "Build against python 3.5 instead of 2.7" OFF)
option(BORNAGAIN_GENERATE_BINDINGS "Generate python bindings during build (requires swig)" OFF)
option(BORNAGAIN_GENERATE_PYTHON_DOCS "Generate python documentation from the doxygen comments" OFF)
option(BORNAGAIN_GUI "Build a graphical user interface" ON)
option(BORNAGAIN_USERMANUAL "Build the User Manual" OFF)
option(BORNAGAIN_MANPAGE "Build Unix man page" OFF)
option(BUILD_DEBIAN "Build a debian package" OFF)
option(BORNAGAIN_APPLE_BUNDLE "Create a Mac OS X bundle" OFF)
option(BORNAGAIN_OPENMPI "Build with OpenMPI support" OFF)
option(BORNAGAIN_RELEASE "Special option for making release" OFF)
option(BORNAGAIN_CRASHHANDLER "Additional machinery to send crash reports" OFF)
option(BORNAGAIN_TIFF_SUPPORT "Tiff files read/write support" ON)

#--- Including macros ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
include(BornAgainMacros)
include(SearchInstalledSoftware)
include(CheckCompiler)
include(BornAgainConfiguration)
include(UnitTests)

#--- Recurse into the given subdirectories ---
if(BORNAGAIN_USERMANUAL)
    add_subdirectory(Doc/UserManual)
endif()
if(BORNAGAIN_MANPAGE)
    add_subdirectory(Doc/man)
endif()
add_subdirectory(ThirdParty)
add_subdirectory(Core)
add_subdirectory(Tests/UnitTests/Core)
add_subdirectory(Fit)
add_subdirectory(Tests/UnitTests/Fit)
if(BORNAGAIN_GUI)
    add_subdirectory(GUI)
    add_subdirectory(Tests/UnitTests/GUI)
endif()
add_subdirectory(Tests/FunctionalTests)  # functional tests (make check)

add_subdirectory(cmake) # trick to print an after-install message

# packaging
include(BornAgainCPack)
