############################################################################
# CMakeLists.txt file for building BornAgain framework
############################################################################

enable_testing()

add_executable( TestCore main.cpp )

# dependencies
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${BornAgainCore_INCLUDE_DIRS})
target_link_libraries(TestCore ${BornAgainCore_LIBRARY}) 
target_link_libraries(TestCore gtest)

add_test( TestCore TestCore ) # TestName ExeName
#add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS TestCore)

