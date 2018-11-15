############################################################################
# Unit tests
############################################################################

include_directories(
    ${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities
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
