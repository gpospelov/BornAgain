############################################################################
# CMakeLists.txt file for building BornAgain framework
############################################################################

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(BornAgain)

# --- General project settings ---
if(NOT BORNAGAIN_PYTHON)
    set(BORNAGAIN_PYTHON ON)
endif()
set(BORNAGAIN_APP OFF)
set(BORNAGAIN_GUI OFF)

#--- Path for additional cmake modules ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

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

# functional tests (cmake; make check)
add_subdirectory(Tests/FunctionalTests)

#if(ROOT_FOUND AND BORNAGAIN_APP)
#    add_subdirectory(App)
#endif()


# packaging
#include(BornAgainCPack)
