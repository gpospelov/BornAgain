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
# BORNAGAIN_EXECUTABLE( executable LOCATION location LIBRARIES libraries )
# -----------------------------------------------------------------------------
function(BORNAGAIN_EXECUTABLE executable)
    cmake_parse_arguments(ARG "" "LOCATION" "LIBRARIES" "" ${ARGN})

    file(GLOB source_files ${ARG_LOCATION}/*.cpp)
    message(STATUS "ANAFU BAE exe[${executable}] alo[${ARG_LOCATION}] lib[${ARG_LIBRARIES}] src[${source_files}]")

    add_executable(${executable} ${source_files} ) # don't EXCLUDE_FROM_ALL

    target_link_libraries(${executable} ${ARG_LIBRARIES})
endfunction()


# -----------------------------------------------------------------------------
# BORNAGAIN_ADD_TEST( name executable [COMPONENT component] )
# -----------------------------------------------------------------------------
function(BORNAGAIN_ADD_TEST test_name test_exe)
    cmake_parse_arguments(ARG "" "COMPONENT" "" "" ${ARGN})
    message(STATUS "ANAFU ADD [${test_name} ${test_exe} ${ARG_COMPONENT}]")
    add_test(${test_name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test_exe} ${ARG_COMPONENT})
endfunction()
