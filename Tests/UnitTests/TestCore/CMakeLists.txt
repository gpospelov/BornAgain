############################################################################
# CMakeLists.txt file for building and running unit tests
############################################################################

enable_testing()

add_executable( TestCore main.cpp )

# dependencies
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(TestCore gtest)

include_directories(${BornAgainCore_INCLUDE_DIRS})
target_link_libraries(TestCore ${BornAgainCore_LIBRARY}) 

include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(TestCore ${Boost_LIBRARIES}) 

# to pick up just compiled shared dll's
#link_directories(${CMAKE_BINARY_DIR}/lib) # doesn't work

# to build executable right in lib directory to not to have problems with finding libBornAgainCore.dll under Windows
set_property(TARGET TestCore PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_test( TestCore TestCore) # TestName ExeName

# add execution of TestCore just after compilation
add_custom_command(TARGET TestCore POST_BUILD COMMAND TestCore)



