set(test TestMinimizer)

set(test_cases
    MinuitTestV1
    MinuitTestV2
    SteepestDescentTestV1
    SteepestDescentTestV2
    ConjugateFRTestV1
    ConjugateFRTestV2
    ConjugatePRTestV1
    ConjugatePRTestV2
    BfgsTestV1
    BfgsTestV2
    Bfgs2TestV1
    Bfgs2TestV2
    GSLSimAnTestV1
    GSLSimAnTestV2
    GeneticTestV1
    GeneticTestV2
)

include_directories(${RootMinimizers_INCLUDE_DIRS})

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

add_executable(${test} ${include_files} ${source_files})
target_link_libraries(${test} BornAgainCore BornAgainTestMachinery)

foreach(test_case ${test_cases})
    add_test(${test}/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} ${test_case})
endforeach()
