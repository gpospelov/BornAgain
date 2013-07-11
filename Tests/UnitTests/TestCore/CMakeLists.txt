############################################################################
# CMakeLists.txt file for building and running unit tests
############################################################################

enable_testing()

add_executable( TestCore main.cpp )

# dependencies
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${BornAgainCore_INCLUDE_DIRS})
target_link_libraries(TestCore ${BornAgainCore_LIBRARY}) 
target_link_libraries(TestCore gtest)

add_test( TestCore TestCore) # TestName ExeName

# given command adds execution of TestCore just after compilation
add_custom_command(TARGET TestCore POST_BUILD COMMAND TestCore)



