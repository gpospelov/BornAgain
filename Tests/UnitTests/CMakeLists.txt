############################################################################
# Unit tests
############################################################################

if(UNITTESTS)
    add_subdirectory(Core)
    add_subdirectory(Fit)

    if(BORNAGAIN_GUI)
        add_subdirectory(GUI)
    endif()
endif()
