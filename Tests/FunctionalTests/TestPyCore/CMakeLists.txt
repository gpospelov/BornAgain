############################################################################
# CMakeLists.txt file for building TestPyCore functional tests
############################################################################

set(list_of_tests
    "isgisaxs01.py"
    "isgisaxs02.py"
    "isgisaxs03.py"
    "isgisaxs04.py"
    "isgisaxs06.py"
    "isgisaxs07.py"
    "isgisaxs08.py"
    "isgisaxs09.py"
    "isgisaxs10.py"
    "isgisaxs11.py"
    "isgisaxs15.py"
    "mesocrystal1.py"
)

foreach(_test ${list_of_tests})
#    add_test(${_test} ${PYTHON_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/${_test}")
    add_test(${_test} ${PYTHON_EXECUTABLE} "${CMAKE_BINARY_DIR}/Tests/FunctionalTests/TestPyCore/${_test}")
endforeach()



