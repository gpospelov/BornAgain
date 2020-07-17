##  set(test TestCoreSpecial)
##
##  set(test_cases
##  #    BatchSimulation
##      FourierTransformation
##      CoreIOPath
##      MultilayerPerformance
##      MesoPerformance
##  # disabled because too slow
##  #    CoreIOPerformance
##  #    MultiThreadPerformance
##  )
##
##  # build executables for each test case
##  file(GLOB source_files "*.cpp")
##
##  add_executable(${test} ${source_files})
##  target_link_libraries(${test} BornAgainCore BornAgainTestMachinery)
##
##  # create test cases
##  foreach(test_case ${test_cases})
##      add_test(${test}/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} ${test_case})
##  endforeach()





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
