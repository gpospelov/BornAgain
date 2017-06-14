############################################################################
# Tests/Functional/Core/CMakeLists.txt
############################################################################

set(CORE_STD_OUT_DIR     ${BUILD_REF_DIR}/StandardSuite)
set(CORE_STD_REF_DIR     ${REFERENCE_DIR}/StandardSuite)
set(CORE_SPECIAL_REF_DIR ${REFERENCE_DIR}/Special)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCORE_STD_OUT_DIR=\\\"${CORE_STD_OUT_DIR}\\\"")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCORE_STD_REF_DIR=\\\"${CORE_STD_REF_DIR}\\\"")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCORE_SPECIAL_REF_DIR=\\\"${CORE_SPECIAL_REF_DIR}\\\"")

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
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
add_subdirectory(CoreIO)
