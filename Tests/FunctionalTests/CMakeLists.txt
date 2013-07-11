############################################################################
# CMakeLists.txt file for running functional tests
############################################################################

enable_testing()
add_custom_target(check ${CMAKE_CTEST_COMMAND} )
#add_custom_target(check ${CMAKE_CTEST_COMMAND} -V)

add_subdirectory(TestCore)
add_subdirectory(TestPyCore)
add_subdirectory(TestPyFit)
add_subdirectory(TestFit)


