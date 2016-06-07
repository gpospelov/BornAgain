############################################################################
# FunctionalTests/TestFit/CMakeLists.txt
############################################################################

set(list_of_tests
    "FitSuite/Minuit2_Migrad"
    "FitSuite/Minuit2_Fumili"
    "FitSuite/GSLLevenbergMarquardt"
    "FitSuite/GSLMultiMinBFGS"
    "FitSuite/GSLMultiMinSteepestDescent"
    "FitSuite/GSLSimulatedAnnealing"
    "FitSuite/GeneticMinimizer"
    "FitSuite/RectDetectorFit"
)

# for some reason these flags doesn't propagated here by SetUpWindows.cmake
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
endif()

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${BornAgainFit_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR}
)

# Adding executables.
GET_LIST_OF_EXECUTABLES_FROM_LIST_OF_TESTS("${list_of_tests}" ${list_of_executables})
foreach(test_exe_name ${list_of_executables})
    BORNAGAIN_EXECUTABLE(${test_exe_name} LOCATIONS ${test_exe_name} EXCLUDE_FROM_ALL
        LIBRARIES ${BornAgainFit_LIBRARY} ${BornAgainCore_LIBRARY})
endforeach()

# Adding tests
foreach(_test ${list_of_tests})
    GET_TEST_NAME_AND_ARGUMENT(${_test} ${test_exe_name} ${test_argument})
    BORNAGAIN_ADD_TEST(${_test} ${test_exe_name} TEST_ARGUMENTS ${test_argument})
endforeach()
