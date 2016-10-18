###########################################################################
# top-level CMakeLists.txt for building BornAgain
############################################################################

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake/generic/modules
    ${CMAKE_SOURCE_DIR}/cmake/bornagain/modules)
set(TEMPLATE_DIR ${CMAKE_SOURCE_DIR}/cmake/bornagain/scripts)

include(PreventInSourceBuilds)

project(BornAgain)

include(CTest) # equivalent to "enable_testing() ???
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}) # => 'make check' is an alias for 'ctest'

include(VERSION.cmake)

# --- Declare project-wide user flags, and set default values ---
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
option(AUTOGENERATE "Regenerate directory auto (Py docs, Py wrappers, man page)" OFF)
option(ZERO_TOLERANCE "Terminate compilation on warnings" OFF)
option(UNITTESTS "Don't skip unit tests" ON)
option(BORNAGAIN_COVERAGE "Build with test coverage information" OFF)
option(BORNAGAIN_DEBUG_OPTIMIZATION "Build with debug optimization (gcc only)" OFF)

if(AUTOGENERATE)
    set(BORNAGAIN_MANPAGE ON)
    set(BORNAGAIN_GENERATE_PYTHON_DOCS ON)
    set(BORNAGAIN_GENERATE_BINDINGS ON)
endif()

#--- Include CMake macros and functions ---
include(GetFilenameComponent) # overwrite CMake command
include(SearchInstalledSoftware)
include(CheckCompiler)
if(ZERO_TOLERANCE)
    if(BORNAGAIN_USE_PYTHON3)
        message(FATAL_ERROR "Python3 currently incompatible with ZERO_TOLERANCE")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wfatal-errors")
endif()
include(BornAgainConfiguration)
include(GeneratePythonDocs)
include(PyExamplesLineLength)
include(CheckCode)

# debug optimization
if(BORNAGAIN_DEBUG_OPTIMIZATION)
  include(DebugOptimization)
endif()

# code coverage analysis
if(BORNAGAIN_COVERAGE)
  include(CheckCoverage)
  include(SetupCoverage)
endif()

#--- Recurse into the given subdirectories ---
if(BORNAGAIN_USERMANUAL)
    add_subdirectory(Doc/UserManual)
endif()
if(BORNAGAIN_MANPAGE)
    add_subdirectory(Doc/man)
endif()
add_subdirectory(ThirdParty/common)
add_subdirectory(ThirdParty/Fit)
add_subdirectory(Fit)
add_subdirectory(ThirdParty/Core)
add_subdirectory(Core)
if(UNITTESTS)
    add_subdirectory(Tests/UnitTests/Core)
    add_subdirectory(Tests/UnitTests/Fit)
endif()
if(BORNAGAIN_GUI)
    include(SearchQt)
    add_subdirectory(ThirdParty/GUI)
    add_subdirectory(GUI)
    if(UNITTESTS)
        add_subdirectory(Tests/UnitTests/GUI)
    endif()
endif()
add_subdirectory(Tests/Functional) # functional tests (ctest)

add_subdirectory(cmake/bornagain) # trick to print an after-install message

#--- Make package targets ---
include(BornAgainCPack)
