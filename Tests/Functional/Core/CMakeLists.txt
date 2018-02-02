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

# for some reason these flags aren't propagated here by SetUpWindows.cmake
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
endif()

add_subdirectory(CoreStandardTest)
add_subdirectory(CoreSpecial)
