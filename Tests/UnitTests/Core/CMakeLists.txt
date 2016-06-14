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

WRAP_GTEST(TestCore0 "0/*.h" ${BornAgainCore_LIBRARY} 0)
WRAP_GTEST(TestCore1 "1/*.h" ${BornAgainCore_LIBRARY} 0)
WRAP_GTEST(TestCore2 "2/*.h" ${BornAgainCore_LIBRARY} 0)
WRAP_GTEST(TestCore3 "3/*.h" ${BornAgainCore_LIBRARY} 0)
WRAP_GTEST(TestCore4 "4/*.h" ${BornAgainCore_LIBRARY} 0)
WRAP_GTEST(TestCore5 "5/*.h" ${BornAgainCore_LIBRARY} 0)
WRAP_GTEST(TestCore6 "6/*.h" ${BornAgainCore_LIBRARY} 0)

WRAP_GTEST(TestCoreFFspec Numeric/FormFactorSpecializationTest.h ${BornAgainCore_LIBRARY} 1)
WRAP_GTEST(TestCoreFFsym  Numeric/FormFactorSymmetryTest.h       ${BornAgainCore_LIBRARY} 1)
