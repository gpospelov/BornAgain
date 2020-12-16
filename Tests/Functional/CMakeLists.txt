############################################################################
# Tests/Functional/CMakeLists.txt (called from top-level CMakeLists.txt)
############################################################################

include_directories(${CMAKE_SOURCE_DIR}/Tests/Functional/TestMachinery)

add_subdirectory(Core)

if(BORNAGAIN_PYTHON)
    add_subdirectory(PyStd)
    add_subdirectory(PyCore)
    add_subdirectory(PyFit)
    add_subdirectory(PyEmbedded)
endif()

if(BORNAGAIN_GUI)
    add_subdirectory(GUI)
endif()
