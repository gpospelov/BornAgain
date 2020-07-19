include(GoogleTest) # provides gtest_discover_tests

set(test TestCoreFitting)

set(source_files
    FitTests.cpp
    AdjustMinimizerPlan.cpp
    Plan.cpp
    PlanCases.cpp
    PlanFactory.cpp
    )

add_executable(${test} ${source_files} ${CMAKE_SOURCE_DIR}/Tests/GTestWrapper/TestAll.cpp)
target_include_directories(${test}
    PUBLIC ${CMAKE_SOURCE_DIR}/ThirdParty/common/gtest/gtest-1.8.0/include)
target_link_libraries(${test} BornAgainCore gtest)

gtest_discover_tests(${test} TEST_PREFIX Core.)
