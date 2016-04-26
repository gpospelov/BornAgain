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

UNIT_TESTS(TestCoreQ "Q" ${BornAgainCore_LIBRARY}) # q loops, lengthy output
UNIT_TESTS(TestCore0 "0" ${BornAgainCore_LIBRARY})
UNIT_TESTS(TestCore1 "1" ${BornAgainCore_LIBRARY})
UNIT_TESTS(TestCore2 "2" ${BornAgainCore_LIBRARY})
UNIT_TESTS(TestCore3 "3" ${BornAgainCore_LIBRARY})
UNIT_TESTS(TestCore4 "4" ${BornAgainCore_LIBRARY})
UNIT_TESTS(TestCore5 "5" ${BornAgainCore_LIBRARY})
UNIT_TESTS(TestCore6 "6" ${BornAgainCore_LIBRARY})
UNIT_TESTS(TestCoreS "S" ${BornAgainCore_LIBRARY})
