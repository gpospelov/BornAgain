############################################################################
# Tests/Functional/Core/CMakeLists.txt
############################################################################

set(other_tests
    BatchSimulation
    PolDWBAMagCylinders2
    )

# Setup other tests:
foreach(test ${other_tests})
    add_executable(${test} ${test}.cpp)
    target_link_libraries(${test} BornAgainFit BornAgainCore)
    add_test(CoreSpecial/${test} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test})
endforeach()
