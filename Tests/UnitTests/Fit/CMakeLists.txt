############################################################################
# CMakeLists.txt file for building and running unit tests
############################################################################

include(AddGTest)

include_as_system_directory("${EIGEN3_INCLUDE_DIR}")
include_directories(
    ../utilities
    ${BornAgainCore_INCLUDE_DIRS}
    ${BornAgainFit_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${RootMinimizers_INCLUDE_DIRS}
    ${gtest_SOURCE_DIR}
    ${gtest_SOURCE_DIR}/include
    )
if(BORNAGAIN_OPENMPI)
    include_directories(${MPI_INCLUDE_PATH})
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_LINKED_AS_SHARED_LIBRARY=1")

set(libs BornAgainCore BornAgainFit)
ADD_GTEST(Fit "Kernel" "${libs}" 0)

