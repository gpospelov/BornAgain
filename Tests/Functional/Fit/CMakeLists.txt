############################################################################
# Tests/Functional/Fit/CMakeLists.txt
############################################################################

set(test_cases
    GSLLevenbergMarquardt
    GSLMultiMinBFGS
    GSLMultiMinSteepestDescent
    GSLSimulatedAnnealing
    GeneticMinimizer
    Minuit2_Fumili
    Minuit2_Migrad
    RectDetectorFit
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

add_executable(FitTestSuite FitTestSuite.cpp)
target_link_libraries(FitTestSuite BornAgainFit BornAgainCore)
foreach(test_case ${test_cases})
    add_test(FitTestSuite/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FitTestSuite ${test_case})
endforeach()
