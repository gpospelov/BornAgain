include(GoogleTest) # provides gtest_discover_tests

set(test UnitTestCore)

include_directories(${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities)

file(GLOB source_files "*/*.cpp" ${CMAKE_SOURCE_DIR}/Tests/GTestWrapper/TestAll.cpp)

add_executable(${test} ${source_files})
target_link_libraries(${test} ${BornAgainCore_LIBRARY} gtest)

gtest_discover_tests(${test} TEST_PREFIX Core.Unit.)
