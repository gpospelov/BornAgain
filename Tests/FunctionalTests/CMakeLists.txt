############################################################################
# CMakeLists.txt file for running functional tests
############################################################################

enable_testing()
add_custom_target(check ${CMAKE_CTEST_COMMAND})
#add_custom_target(check ${CMAKE_CTEST_COMMAND} -V)

execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Tests/ReferenceData ${CMAKE_BINARY_DIR}/Tests/ReferenceData)

add_subdirectory(TestCore)
add_subdirectory(TestPyCore)
add_subdirectory(TestPyFit)
add_subdirectory(TestFit)


