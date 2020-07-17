##      MultilayerPerformance
##      MesoPerformance
##  # disabled because too slow
##  #    CoreIOPerformance
##  #    MultiThreadPerformance

include_directories(${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities)

function(PerformanceTest NAME SPEED DEPS)
    add_executable(${NAME} ${NAME}.cpp ${DEPS})
    target_link_libraries(${NAME} ${BornAgainCore_LIBRARY})
    if((${SPEED} STREQUAL "fast") OR SLOWTESTS)
        add_test(Core:Perf:${NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${NAME})
    endif()
endfunction()

PerformanceTest(CoreIO "slow" ../Benchmark.cpp)
PerformanceTest(Multilayer "fast" "")
PerformanceTest(Mesocrystal "fast" "")
PerformanceTest(Threading "slow" ThreadingComponents.cpp)
