##      MultilayerPerformance
##      MesoPerformance
##  # disabled because too slow
##  #    CoreIOPerformance
##  #    MultiThreadPerformance

include_directories(${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities)

function(PerformanceTest NAME DEPS)
    add_executable(${NAME} ${NAME}.cpp ${DEPS})
    target_link_libraries(${NAME} ${BornAgainCore_LIBRARY})
    add_test(Core:Perf:${NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${NAME})
endfunction()

PerformanceTest(CoreIO ../Benchmark.cpp)
PerformanceTest(Multilayer "")
PerformanceTest(Mesocrystal "")
PerformanceTest(Threading ThreadingComponents.cpp)
