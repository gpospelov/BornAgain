set(test TestCoreSpecial)

set(test_cases
    BatchSimulation
    FourierTransformation
    CoreIOPath
    MultilayerPerformance
    MesoPerformance
# disabled because too slow
#    CoreIOPerformance
#    MultiThreadPerformance
)

# build executables for each test case
file(GLOB source_files "*.cpp")

add_executable(${test} ${source_files})
target_link_libraries(${test} BornAgainCore BornAgainTestMachinery)

# create test cases
foreach(test_case ${test_cases})
    add_test(${test}/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} ${test_case})
endforeach()
