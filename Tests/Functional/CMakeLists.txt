############################################################################
# Futests/CMakeLists.txt (called from top-level CMakeLists.txt)
############################################################################

execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Tests/ReferenceData/BornAgain
    ${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain )
execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Tests/Functional/PyFit
    ${CMAKE_BINARY_DIR}/Tests/Functional/PyFit )

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
