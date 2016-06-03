############################################################################
# CMakeLists.txt file for building and running unit tests
############################################################################

include_directories(
    ${BornAgainCore_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR}
    ../utilities/
    )

if(BORNAGAIN_OPENMPI)
    include_directories(${MPI_INCLUDE_PATH})
endif()

WRAP_GTEST(TestCore0 "0" ${BornAgainCore_LIBRARY} 0)
WRAP_GTEST(TestCore1 "1" ${BornAgainCore_LIBRARY} 0)
WRAP_GTEST(TestCore2 "2" ${BornAgainCore_LIBRARY} 0)
WRAP_GTEST(TestCore3 "3" ${BornAgainCore_LIBRARY} 0)
WRAP_GTEST(TestCore4 "4" ${BornAgainCore_LIBRARY} 0)
WRAP_GTEST(TestCore5 "5" ${BornAgainCore_LIBRARY} 0)
WRAP_GTEST(TestCore6 "6" ${BornAgainCore_LIBRARY} 0)

WRAP_GTEST(TestCoreS "S" ${BornAgainCore_LIBRARY} 1)
WRAP_GTEST(TestCoreQ "Q" ${BornAgainCore_LIBRARY} 1) # q loops, lengthy output
WRAP_GTEST(TestCoreP "P" ${BornAgainCore_LIBRARY} 1) # q loops, lengthy output
