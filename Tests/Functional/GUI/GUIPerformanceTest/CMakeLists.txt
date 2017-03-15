set(test_name GUIPerformanceTest)

add_executable(${test_name} main.cpp GUIPerformanceTest.cpp GUIPerformanceTest.h)

target_link_libraries(${test_name} BornAgainCore BornAgainGUI BornAgainTestMachinery)

qt5_use_modules(${test_name} Widgets Core Gui Designer PrintSupport Network)

add_test(${test_name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test_name})

