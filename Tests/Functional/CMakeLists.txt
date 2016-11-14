############################################################################
# Tests/Functional/CMakeLists.txt (called from top-level CMakeLists.txt)
############################################################################

set(BUILD_REF_DIR ${CMAKE_BINARY_DIR}/ref)
file(MAKE_DIRECTORY ${BUILD_REF_DIR})

set(BUILD_BIN_DIR ${CMAKE_BINARY_DIR}/bin)
set(BUILD_LIB_DIR ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBUILD_BIN_DIR=\\\"${BUILD_BIN_DIR}\\\"")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBUILD_LIB_DIR=\\\"${BUILD_LIB_DIR}\\\"")

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
    add_subdirectory(GUI/GUITranslationTest)
endif()
