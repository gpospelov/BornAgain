############################################################################
#  Collection of macros/functions for BornAgain CMake infrastructure
############################################################################


# Returns a list of unique executables from a list of functional tests
# Usage:
#   set(list_of_tests "exe1/arg1" "exe1/arg2" "exe1/arg3" "exe2" "exe4/arg1")
#   get_list_of_executables_from_list_of_tests("${list_of_tests}" ${list_of_executables})
# Result:
#   list_of_executables will be "exe1;exe2;exe3;exe4"
macro(GET_LIST_OF_EXECUTABLES_FROM_LIST_OF_TESTS list_of_tests)
    foreach(_test ${list_of_tests})
        string(REPLACE "/" ";"  test_info ${_test})
        list(GET test_info 0 test_exe_name)
        list(APPEND result ${test_exe_name})
    endforeach()
    list(REMOVE_DUPLICATES result)
    set(list_of_executables ${result})
endmacro()


# Parse string containing test info into test name and test argument
# Usage:
#   set(test_string "CoreSuite/CylindersAndPrisms")
#   get_test_name_and_argument(${test_string} ${test_exe_name} ${test_argument})
# Result:
#   test_exe_name will be "CoreSuite",
#   test_argument will be CylindersAndPrisms
macro(GET_TEST_NAME_AND_ARGUMENT _test_string)
    unset(_test_exe_name)
    unset(_test_argument)
    string(REPLACE "/" ";"  test_info ${_test_string})
    list(LENGTH test_info len)
    list(GET test_info 0 _test_exe_name)
    if(len EQUAL 2)
        list(GET test_info 1 _test_argument)
    endif()
    set(test_exe_name ${_test_exe_name})
    set(test_argument ${_test_argument})
endmacro()


# -----------------------------------------------------------------------------
# add executable (ARG, options, one_value_keyword, multi_value_keywoard arguments (aka ${ARG_UNPARSED_ARGUMENTS})
# -----------------------------------------------------------------------------
function(BORNAGAIN_EXECUTABLE executable)
    cmake_parse_arguments(ARG "EXCLUDE_FROM_ALL" "" "LIBRARIES;LOCATIONS" "" ${ARGN})
    # retrieving source list
    file(GLOB source_files ${ARG_LOCATIONS}/*.cpp)

    # making executable
    if(${ARG_EXCLUDE_FROM_ALL})
        add_executable(${executable} ${source_files} )
        # add_executable("${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${executable}" EXCLUDE_FROM_ALL ${source_files} )
    else()
        add_executable(${executable} ${ARG_UNPARSED_ARGUMENTS} )
    endif()
    # linking libraries from the list
    foreach(_libname ${ARG_LIBRARIES})
        include_directories(${${_libname}_INCLUDE_DIRS})
        target_link_libraries(${executable} ${_libname})
    endforeach()
endfunction()


# -----------------------------------------------------------------------------
# advanced add cmake test which allows to pass separately:
# test_name - the name of the test as appears on ctest summary table
# text_exe  - actual executable name
#
# together with additional command line arguments for the test executable
# TEST_ARGUMENTS - any command line argument
# -----------------------------------------------------------------------------
function(BORNAGAIN_ADD_TEST test_name test_exe)
    cmake_parse_arguments(ARG "" "TEST_ARGUMENTS" "" "" ${ARGN})
    add_test(${test_name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test_exe} "${ARG_TEST_ARGUMENTS}")
endfunction()
