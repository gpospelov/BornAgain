############################################################################
# CMakeLists.txt file for building BornAgain framework
############################################################################

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(BornAgain)

# --- General project settings ---
if(NOT BORNAGAIN_PYTHON)
    set(BORNAGAIN_PYTHON OFF)
endif()

if(NOT BORNAGAIN_APP)
#    set(BORNAGAIN_APP ON)
endif()

if(NOT BORNAGAIN_GUI)
    set(BORNAGAIN_GUI ON)
endif()

#--- Path for additional cmake modules ---
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

# packaging
include(BornAgainCPack)
