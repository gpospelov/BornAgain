############################################################################
# CMakeLists.txt file for building BornAgain framework
############################################################################

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(BornAgain)

# --- General project settings ---
#set(BORNAGAIN_PYTHON ON)

#--- Where to look first for cmake modules ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

#--- Including macros ---
include(BornAgainMacros)
include(SearchInstalledSoftware)

#--- Recurse into the given subdirectories ---
add_subdirectory(Core)
add_subdirectory(ThirdParty/gtest)
if(ROOT_FOUND)
    add_subdirectory(Fit)
    add_subdirectory(App)
endif()

# functional tests (cmake; make check)
add_subdirectory(Tests/FunctionalTests)


