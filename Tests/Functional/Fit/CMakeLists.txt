set(test FitTest)

set(test_cases
    GSLLevenbergMarquardt
    GSLMultiMinBFGS
    GSLMultiMinSteepestDescent
    GSLSimulatedAnnealing
    GeneticMinimizer
    Minuit2_Fumili
    Minuit2_Migrad
    RectDetectorFit
    AdjustMinimizerStrategy
    SpecularFit
    StandaloneFit
)


include_as_system_directory("${EIGEN3_INCLUDE_DIR}")

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${BornAgainFit_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../TestMachinery
    ${RootMinimizers_INCLUDE_DIRS}
)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

add_executable(${test} ${include_files} ${source_files})
target_link_libraries(${test} BornAgainCore BornAgainTestMachinery)

foreach(test_case ${test_cases})
    add_test(${test}/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} ${test_case})
endforeach()
