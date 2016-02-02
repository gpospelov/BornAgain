############################################################################
# FunctionalTests/CMakeLists.txt (called from top-level CMakeLists.txt)
############################################################################

enable_testing()

add_custom_target(check ${CMAKE_CTEST_COMMAND})
# export CTEST_OUTPUT_ON_FAILURE=ON will give some output on failure

execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Tests/ReferenceData/BornAgain
    ${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain )
execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Tests/FunctionalTests/TestPyCore
    ${CMAKE_BINARY_DIR}/Tests/FunctionalTests/TestPyCore )
execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Tests/FunctionalTests/TestPyFit
    ${CMAKE_BINARY_DIR}/Tests/FunctionalTests/TestPyFit )

#file(COPY ${CMAKE_SOURCE_DIR}/Tests/FunctionalTests/TestPyFit DESTINATION ${CMAKE_BINARY_DIR}/Tests/FunctionalTests/TestPyFit)
#COPY_IF_DIFFERENT( ${CMAKE_SOURCE_DIR}/Tests/FunctionalTests/TestPyFit ${CMAKE_BINARY_DIR}/Tests/FunctionalTests/TestPyFit ${SRC_FILES} IncludeTargets "Includes")

add_subdirectory(TestCore)
add_subdirectory(TestFit)

if(BORNAGAIN_PYTHON)
    add_subdirectory(TestPyCore)
    add_subdirectory(TestPyFit)
endif()

if(BORNAGAIN_GUI)
    add_subdirectory(TestGUI)
endif()
