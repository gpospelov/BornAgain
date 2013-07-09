#---Check if cmake has the required version-----------------------------------------------------
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

#---Set name of the project to "ROOT". Has to be done after check of cmake version--------------
project(BornAgain)

# ---General project settings-------------------------------------------------------------------
set(BORNAGAIN_PYTHON ON)

#---Where to look first for cmake modules-------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

#---Enable Folders in IDE like Visual Studio----------------------------------------------------
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


include(BornAgainMacros)


#---Recurse into the given subdirectories.  This does not actually cause another cmake executable
#  to run. The same process will walk through the project's entire directory structure.
add_subdirectory (Core)

