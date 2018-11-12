############################################################################
# Unit tests
############################################################################

include(AddGTest)

# Disabling RUNPATH build time manipulation on unit tests executables.
# We will provide our own RPATH to not to depend on LD_LIBRARY_PATH, see AddGtest.cmake.
if(UNIX AND NOT APPLE)
    SET(CMAKE_SKIP_BUILD_RPATH TRUE)
endif()

include_as_system_directory("${EIGEN3_INCLUDE_DIR}")
include_directories(
    ${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities
    ${BornAgainCore_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIR}
    ${gtest_SOURCE_DIR}
    ${gtest_SOURCE_DIR}/include
    )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_LINKED_AS_SHARED_LIBRARY=1")

if(BORNAGAIN_TIFF_SUPPORT)
    add_definitions(-DBORNAGAIN_TIFF_SUPPORT)
endif(BORNAGAIN_TIFF_SUPPORT)

add_subdirectory(Core)
add_subdirectory(Fit)

if(BORNAGAIN_GUI)
    add_subdirectory(GUI)
endif()

# to show directory in Qt creator project tree
FILE(GLOB_RECURSE UtilityFiles "utilities/*.*")
add_custom_target(UnitTestUtilities SOURCES ${UtilityFiles})
