############################################################################
# Futests/CMakeLists.txt (called from top-level CMakeLists.txt)
############################################################################

execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Tests/ReferenceData/BornAgain
    ${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain )
execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Tests/Functional/TestPyCore
    ${CMAKE_BINARY_DIR}/Tests/Functional/TestPyCore )
execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Tests/Functional/TestPyFit
    ${CMAKE_BINARY_DIR}/Tests/Functional/TestPyFit )

add_subdirectory(Core)
add_subdirectory(Fit)

if(BORNAGAIN_PYTHON)
    add_subdirectory(PyCore/scripts)
    add_subdirectory(PyCore/suite)
    add_subdirectory(PyFit)
endif()

if(BORNAGAIN_GUI)
    add_subdirectory(GUI)
endif()
