############################################################################
# CMakeLists.txt file for running functional tests
############################################################################

enable_testing()
add_custom_target(check ${CMAKE_CTEST_COMMAND} -V)

#add_subdirectory(TestCore)
add_subdirectory(TestFit)


