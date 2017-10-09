############################################################################
# Tests/Functional/CMakeLists.txt (called from top-level CMakeLists.txt)
############################################################################

set(BUILD_REF_DIR ${CMAKE_BINARY_DIR}/ref)
file(MAKE_DIRECTORY ${BUILD_REF_DIR})

add_subdirectory(TestMachinery)
add_subdirectory(Core)
add_subdirectory(Fit)

if(BORNAGAIN_PYTHON)
    add_definitions(-DBORNAGAIN_PYTHON)
    add_subdirectory(Python)
endif()

if(BORNAGAIN_GUI)
    add_subdirectory(GUI)
endif()
