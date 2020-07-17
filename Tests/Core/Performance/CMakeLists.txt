##      MultilayerPerformance
##      MesoPerformance
##  # disabled because too slow
##  #    CoreIOPerformance
##  #    MultiThreadPerformance

include_directories(${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities)

set(test_cases
    Multilayer
    Mesocrystal
    )

foreach(test ${test_cases})
    add_executable(${test} ${test}.cpp)
    target_link_libraries(${test} ${BornAgainCore_LIBRARY})
    add_test(Core:Perf:${test} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test})
endforeach()
