############################################################################
# CMakeLists.txt file for building gtest library
############################################################################
# Google Test also has to use one.
option(
  gtest_force_shared_crt
  "Use shared (DLL) run-time lib even when Google Test is built as static lib."
  OFF)

option(gtest_build_tests "Build all of gtest's own tests." OFF)

option(gtest_build_samples "Build gtest's sample programs." OFF)

option(gtest_disable_pthreads "Disable uses of pthreads in gtest." OFF)

# Defines pre_project_set_up_hermetic_build() and set_up_hermetic_build().
include(gtest-1.6.0/cmake/hermetic_build.cmake OPTIONAL)

if (COMMAND pre_project_set_up_hermetic_build)
  pre_project_set_up_hermetic_build()
endif()

########################################################################
#
# Project-wide settings

# Name of the project.
#
# CMake files in this project can refer to the root source directory
# as ${gtest_SOURCE_DIR} and to the root binary directory as
# ${gtest_BINARY_DIR}.
# Language "C" is required for find_package(Threads).
project(gtest CXX C)
cmake_minimum_required(VERSION 2.6.2)

if (COMMAND set_up_hermetic_build)
  set_up_hermetic_build()
endif()

# Define helper functions and macros used by Google Test.
include(gtest-1.6.0/cmake/internal_utils.cmake)

config_compiler_and_linker()  # Defined in internal_utils.cmake.

# Where Google Test's .h files can be found.
include_directories(
  ${gtest_SOURCE_DIR}/gtest-1.6.0/include
  ${gtest_SOURCE_DIR}/gtest-1.6.0)

# Where Google Test's libraries can be found.
link_directories(${gtest_BINARY_DIR}/gtest-1.6.0/src)

########################################################################
#
# Defines the gtest & gtest_main libraries.  User tests should link
# with one of them.

# Google Test libraries.  We build them using more strict warnings than what
# are used for other targets, to ensure that gtest can be compiled by a user
# aggressive about warnings.
cxx_library(gtest "${cxx_strict}" gtest-1.6.0/src/gtest-all.cc)
set_Target_properties(gtest PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(gtest_LIBRARY_TYPE SHARED)



#cxx_library(gtest_main "${cxx_strict}" src/gtest_main.cc)
#target_link_libraries(gtest_main gtest)
