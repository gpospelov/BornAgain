include(GoogleTest)

set(test UnitTestFit)

include_directories(${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities)

file(GLOB source_files "*.cpp" "../utilities/TestAll.cpp")
file(GLOB include_files "*.h")

add_executable(${test} ${source_files} ${include_files})
target_link_libraries(${test} ${BornAgainFit_LIBRARY} gtest)

gtest_discover_tests(${test} TEST_PREFIX Fit:Unit:)
