############################################################################
# CMakeLists.txt file for building BornAgain framework
############################################################################

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(BornAgain)

# --- General project settings ---
if(NOT BORNAGAIN_PYTHON)
    set(BORNAGAIN_PYTHON ON)
endif()
set(BORNAGAIN_APP ON)
set(BORNAGAIN_GUI OFF)

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

if(NOT ROOT_FOUND)
    add_subdirectory(ThirdParty/RootMinimizers)
endif()

add_subdirectory(ThirdParty/RootMathMore)
add_subdirectory(Fit)

if(ROOT_FOUND AND BORNAGAIN_APP)
    add_subdirectory(App)
endif()

# functional tests (cmake; make check)
add_subdirectory(Tests/FunctionalTests)

