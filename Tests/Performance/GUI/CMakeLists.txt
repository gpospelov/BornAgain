include_directories(${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities)

function(PerformanceTest NAME SPEED DEPS)
    add_executable(${NAME} ${NAME}.cpp ${DEPS})
    target_link_libraries(${NAME} ${BornAgainGUI_LIBRARY})
    if((${SPEED} STREQUAL "fast") OR SLOWTESTS)
        add_test(GUI:Perf:${NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${NAME})
    endif()
endfunction()

PerformanceTest(CsvImportAssistantPerformanceTest "fast" "")
PerformanceTest(GUIPerformanceTest "too_slow" ../Benchmark.cpp) # don't run (timeout after 1500s)
