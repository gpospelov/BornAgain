include(GoogleTest) # provides gtest_discover_tests

set(test TestCoreSpecial2)

include_directories(${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities)

set(source_files
    BatchSimulation.cpp
    FourierTransformationTest.cpp
    CoreIOPathTest.cpp
    )

add_executable(${test} ${source_files} ${CMAKE_SOURCE_DIR}/Tests/GTestWrapper/TestAll.cpp)
target_include_directories(${test} PUBLIC ${CMAKE_SOURCE_DIR}/ThirdParty/common/gtest/gtest-1.8.0/include)
target_link_libraries(${test} ${BornAgainCore_LIBRARY} gtest)

gtest_discover_tests(${test} TEST_PREFIX Core:Special:)
