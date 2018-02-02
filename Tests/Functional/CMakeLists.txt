############################################################################
# Tests/Functional/CMakeLists.txt (called from top-level CMakeLists.txt)
############################################################################

include_as_system_directory("${EIGEN3_INCLUDE_DIR}")
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIR}
    ${BornAgainCore_INCLUDE_DIRS}
    ${BornAgainFit_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/Tests/Functional/TestMachinery
)

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
