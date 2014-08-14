############################################################################
# CMakeLists.txt file for building TestPyFit functional tests
############################################################################

set(list_of_tests
    "testfit_UsingBuilder.py"
    "testfit_Genetic.py"
    "testfit_GSLLMA.py"
    "testfit_GSLMultiMin.py"
    "testfit_GSLSimAn.py"
    "testfit_Minuit2.py"
)


foreach(_test ${list_of_tests})
    #add_test(${_test} ${PYTHON_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/${_test}")
    add_test(${_test} ${PYTHON_EXECUTABLE} "${CMAKE_BINARY_DIR}/Tests/FunctionalTests/TestPyFit/${_test}")
endforeach()
