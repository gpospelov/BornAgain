############################################################################
# Tests/Functional/CMakeLists.txt (called from top-level CMakeLists.txt)
############################################################################

add_subdirectory(TestMachinery)
add_subdirectory(Core)
add_subdirectory(Fit)

if(BORNAGAIN_PYTHON)
    add_subdirectory(PyCore/legacy)
    add_subdirectory(PyCore/export)
    add_subdirectory(PyCore/persistence)
    add_subdirectory(PyFit)
endif()

if(BORNAGAIN_GUI)
    add_subdirectory(GUI)
endif()
