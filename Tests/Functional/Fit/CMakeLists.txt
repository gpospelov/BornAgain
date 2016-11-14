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
    AdjustMinimizerStrategy
    StandaloneFit
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
    ${CMAKE_CURRENT_SOURCE_DIR}/../TestMachinery
    ${RootMinimizers_INCLUDE_DIRS}
)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

add_executable(FitTest ${include_files} ${source_files})

target_link_libraries(FitTest BornAgainFit BornAgainCore BornAgainTestMachinery)
foreach(test_case ${test_cases})
    add_test(FitTest/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FitTest ${test_case})
endforeach()
