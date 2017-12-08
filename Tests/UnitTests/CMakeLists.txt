############################################################################
# Unit tests
############################################################################

if(UNITTESTS)
    add_subdirectory(Core)
    add_subdirectory(Fit)

    if(BORNAGAIN_GUI)
        add_subdirectory(GUI)
        add_subdirectory(GUI2)
    endif()

    # to show directory in Qt creator project tree
    FILE(GLOB_RECURSE UtilityFiles "utilities/*.h")
    add_custom_target(UnitTestUtilities SOURCES ${UtilityFiles})
endif()
