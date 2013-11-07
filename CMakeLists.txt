###########################################################################
# CMakeLists.txt file for building BornAgain framework
############################################################################

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(BornAgain)

# --- The version number. Please define it here only! ---
set(BornAgain_VERSION_MAJOR 0)
set(BornAgain_VERSION_MINOR 9)
set(BornAgain_VERSION_PATCH 1)

# --- General project settings ---
option(BORNAGAIN_PYTHON "Build with python support" ON)
option(BORNAGAIN_APP "Build test application" ON)
option(BORNAGAIN_GUI "Build a graphical user interface" OFF)
option(BORNAGAIN_MAN "Build a user manual" OFF)
option(BUILD_DEBIAN "Build a debian package" OFF)


# --- Path for additional cmake modules ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

#--- Including macros ---
include(BornAgainMacros)
include(SearchInstalledSoftware)
include(CheckCompiler)

#--- Recurse into the given subdirectories ---
add_subdirectory(Core)
add_subdirectory(ThirdParty/gtest)
add_subdirectory(Tests/UnitTests/TestCore)
add_subdirectory(ThirdParty/RootMinimizers)
add_subdirectory(Fit)
add_subdirectory(Tests/FunctionalTests)  # functional tests (make check)

if(ROOT_FOUND AND BORNAGAIN_APP)
    add_subdirectory(App)
endif()

if(BORNAGAIN_GUI)
    add_subdirectory(GUI)
endif()

if(BORNAGAIN_MAN)
	add_subdirectory(Doc/UserManual)
endif()

# packaging
include(BornAgainCPack)
