############################################################################
# CMakeLists.txt file for building TestPyFit functional tests
############################################################################

set(list_of_tests
    "testfit01.py"
    "testfit02.py"
)

foreach(_test ${list_of_tests})
    add_test(${_test} ${PYTHON_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/${_test}")
endforeach()
