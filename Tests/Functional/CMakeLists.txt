############################################################################
# Futests/CMakeLists.txt (called from top-level CMakeLists.txt)
############################################################################

add_subdirectory(Core)
add_subdirectory(Fit)

if(BORNAGAIN_PYTHON)
    add_subdirectory(PyCore/scripts)
    add_subdirectory(PyCore/suite)
    add_subdirectory(PyFit)
endif()

if(BORNAGAIN_GUI)
    add_subdirectory(GUI)
endif()
