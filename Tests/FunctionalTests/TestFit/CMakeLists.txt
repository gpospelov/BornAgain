############################################################################
# CMakeLists.txt file for building TestFit functional tests
############################################################################

set(CMAKE_CXX_FLAGS "-DSTANDALONE")

set(list_of_tests
    "TestFit01"
    "TestFit02"
)

foreach(_test ${list_of_tests})
    BORNAGAIN_EXECUTABLE(${_test} LOCATIONS ${_test} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY} ${BornAgainFit_LIBRARY} ${RootMathMore_LIBRARY})
    BORNAGAIN_ADD_TEST(${_test})
endforeach()
