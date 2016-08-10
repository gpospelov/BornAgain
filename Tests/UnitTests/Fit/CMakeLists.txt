############################################################################
# CMakeLists.txt file for building and running unit tests
############################################################################

include_directories(
    ${BornAgainCore_INCLUDE_DIRS}
    ${BornAgainFit_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${RootMinimizers_INCLUDE_DIRS}
)

if(BORNAGAIN_OPENMPI)
    include_directories(${MPI_INCLUDE_PATH})
endif()

WRAP_GTEST(TestFit0 "*.h" ${BornAgainCore_LIBRARY} 0)

