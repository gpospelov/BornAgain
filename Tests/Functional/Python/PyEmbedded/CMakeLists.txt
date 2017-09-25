# Functional test to read/write large data files.

set(test PyEmbedded)

include_directories(
    ${BornAgainCore_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

add_executable(${test} main.cpp PyEmbeddedTest.h PyEmbeddedTest.cpp)
target_link_libraries(${test} BornAgainCore BornAgainTestMachinery)

#add_test(PyEmbedded/${test} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test})
