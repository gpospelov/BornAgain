############################################################################
# Tests/Functional/Core/CMakeLists.txt
############################################################################

include_as_system_directory("${EIGEN3_INCLUDE_DIR}")

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../TestMachinery
    ${CMAKE_SOURCE_DIR}/Core/Simulation
    )

add_subdirectory(CoreStandardTest)
add_subdirectory(CoreSpecial)
