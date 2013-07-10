#---Check if cmake has the required version-----------------------------------------------------
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

#---Set name of the project to "ROOT". Has to be done after check of cmake version--------------
project(BornAgain)

# ---General project settings-------------------------------------------------------------------
#set(BORNAGAIN_PYTHON ON)

#---Where to look first for cmake modules-------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

#---Enable Folders in IDE like Visual Studio----------------------------------------------------
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(BornAgainMacros)
include(SearchInstalledSoftware)

#---Recurse into the given subdirectories.  
add_subdirectory(Core)
#add_subdirectory(ThirdParty/gtest/gtest-1.6)
if(ROOT_FOUND)
    add_subdirectory(Fit)
endif()


