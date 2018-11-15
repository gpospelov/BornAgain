############################################################################
# Unit tests
############################################################################

include_as_system_directory("${EIGEN3_INCLUDE_DIR}")
include_directories(
    ${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities
    ${BornAgainCore_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIR}
    )

add_subdirectory(Core)
add_subdirectory(Numeric)
add_subdirectory(Fit)

if(BORNAGAIN_GUI)
    add_subdirectory(GUI)
endif()

# to show directory in Qt creator project tree
FILE(GLOB_RECURSE UtilityFiles "utilities/*.*")
add_custom_target(UnitTestUtilities SOURCES ${UtilityFiles})
