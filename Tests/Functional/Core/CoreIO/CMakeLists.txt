# Functional test to read/write large data files.

set(test CoreIO)

add_executable(${test} main.cpp CoreIOTest.h CoreIOTest.cpp)
target_link_libraries(${test} BornAgainCore)
#add_test(CoreSpecial/${test} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test})
