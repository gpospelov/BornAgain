############################################################################
# Unit tests
############################################################################

if(UNITTESTS)
    add_subdirectory(Core)
    add_subdirectory(Fit)

    if(BORNAGAIN_GUI)
        add_subdirectory(GUI)
    endif()

    # to show directory in Qt creator project tree
    FILE(GLOB_RECURSE UtilityFiles "utilities/*.*")
    add_custom_target(UnitTestUtilities SOURCES ${UtilityFiles})
endif()
