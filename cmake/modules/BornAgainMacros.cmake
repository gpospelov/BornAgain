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
        add_executable(${executable} EXCLUDE_FROM_ALL ${source_files} )
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
    add_dependencies(check ${test_exe})
endfunction()

# Reimplementation of native CMake function
# (correct handling of leading dot, https://cmake.org/pipermail/cmake-developers/2011-June/013526.html)
function (get_filename_component)
    _get_filename_component (${ARGN})
    list (GET ARGN 0 VAR)
    list (GET ARGN 2 CMD)
    if (${CMD} STREQUAL "EXT")
        string (REGEX MATCHALL "\\.[^.]*" PARTS "${${VAR}}")
        list (LENGTH PARTS LEN)
        if (LEN GREATER 1)
            math (EXPR LEN "${LEN} - 1")
            list (GET PARTS ${LEN} ${VAR})
        endif ()
    endif ()
    set (${VAR} "${${VAR}}" PARENT_SCOPE)
endfunction ()


function(ValidatePythonInstallation)
    message(STATUS "--> Validating Python installation corresponding to the interpreter ${PYTHON_EXECUTABLE}")

    execute_process(COMMAND "${PYTHON_EXECUTABLE}" "-c"
        "from distutils import sysconfig as s;import sys;import struct;
print('.'.join(str(v) for v in sys.version_info));
print(sys.prefix);
print(s.get_python_inc(plat_specific=True));
print(s.get_python_lib(plat_specific=True));
print(s.get_config_var('SO'));
print(hasattr(sys, 'gettotalrefcount')+0);
print(struct.calcsize('@P'));
print(s.get_config_var('LDVERSION') or s.get_config_var('VERSION'));
"
    	RESULT_VARIABLE _PYTHON_SUCCESS
    	OUTPUT_VARIABLE _PYTHON_VALUES
    	ERROR_VARIABLE _PYTHON_ERROR_VALUE
    	OUTPUT_STRIP_TRAILING_WHITESPACE
        )

    if(NOT _PYTHON_SUCCESS MATCHES 0)
        set(ALT_PYTHONLIBS_FOUND FALSE)
        return()
    endif()

    # Convert the process output into a list
    string(REGEX REPLACE ";" "\\\\;" _PYTHON_VALUES ${_PYTHON_VALUES})
    string(REGEX REPLACE "\n" ";" _PYTHON_VALUES ${_PYTHON_VALUES})
    list(GET _PYTHON_VALUES 0 _PYTHON_VERSION_LIST)
    list(GET _PYTHON_VALUES 1 ALT_PYTHON_PREFIX)
    list(GET _PYTHON_VALUES 2 ALT_PYTHON_INCLUDE_DIRS)
    list(GET _PYTHON_VALUES 3 ALT_PYTHON_SITE_PACKAGES)
    list(GET _PYTHON_VALUES 4 ALT_PYTHON_MODULE_EXTENSION)
    list(GET _PYTHON_VALUES 5 ALT_PYTHON_IS_DEBUG)
    list(GET _PYTHON_VALUES 6 ALT_PYTHON_SIZEOF_VOID_P)
    list(GET _PYTHON_VALUES 7 ALT_PYTHON_LIBRARY_SUFFIX)

    string(REGEX REPLACE "\\." ";" _PYTHON_VERSION_LIST ${_PYTHON_VERSION_LIST})
    list(GET _PYTHON_VERSION_LIST 0 ALT_PYTHON_VERSION_MAJOR)
    list(GET _PYTHON_VERSION_LIST 1 ALT_PYTHON_VERSION_MINOR)
    list(GET _PYTHON_VERSION_LIST 2 ALT_PYTHON_VERSION_PATCH)

    set(ALT_PYTHON_VERSION_STRING ${ALT_PYTHON_VERSION_MAJOR}.${ALT_PYTHON_VERSION_MINOR}.${ALT_PYTHON_VERSION_PATCH})

    message(STATUS "----> ALT_PYTHON_PREFIX:${ALT_PYTHON_PREFIX}")
    message(STATUS "----> ALT_PYTHON_INCLUDE_DIRS:${ALT_PYTHON_INCLUDE_DIRS}")
    message(STATUS "----> ALT_PYTHON_SITE_PACKAGES:${ALT_PYTHON_SITE_PACKAGES}")
    message(STATUS "----> ALT_PYTHON_MODULE_EXTENSION:${ALT_PYTHON_MODULE_EXTENSION}")
    message(STATUS "----> ALT_PYTHON_IS_DEBUG:${ALT_PYTHON_IS_DEBUG}")
    message(STATUS "----> ALT_PYTHON_SIZEOF_VOID_P:${ALT_PYTHON_SIZEOF_VOID_P} ")
    message(STATUS "----> ALT_PYTHON_LIBRARY_SUFFIX:${ALT_PYTHON_LIBRARY_SUFFIX}")

    if(NOT PYTHON_INCLUDE_DIRS STREQUAL ALT_PYTHON_INCLUDE_DIRS)
        message(STATUS "----> Python interpreter reports include directory (see ALT_PYTHON_INCLUDE_DIRS) which differs from what we have learned before (see PYTHON_INCLUDE_DIRS).")
        message(STATUS "----> Setting PYTHON_INCLUDE_DIRS=${ALT_PYTHON_INCLUDE_DIRS}")
        set(PYTHON_INCLUDE_DIRS ${ALT_PYTHON_INCLUDE_DIRS} PARENT_SCOPE)
    endif()

    if(PYTHONLIBS_FOUND)
        #if(NOT PYTHON_VERSION_STRING STREQUAL PYTHONLIBS_VERSION_STRING)
            message(STATUS "---> PYTHON_VERSION_STRING ${PYTHON_VERSION_STRING} differs from PYTHONLIBS_VERSION_STRING ${PYTHONLIBS_VERSION_STRING}")
            if(APPLE)
                set(ALT_PYTHON_LIBRARIES "${ALT_PYTHON_PREFIX}/lib/libpython${ALT_PYTHON_LIBRARY_SUFFIX}.dylib")
                message(STATUS "----> Will use library from ${ALT_PYTHON_LIBRARIES} instead")
                set(PYTHON_LIBRARIES ${ALT_PYTHON_LIBRARIES} PARENT_SCOPE)
            else()
                message(STATUS "---> There is inconcistency between versions of interpreter and library. Don't know how to handle, compilation might fail.")
            endif()

        #endif()
    endif()

    if(NOT PYTHONLIBS_FOUND)
        if(APPLE)
            message(STATUS "----> There was a complain that no suitable Python library has been found. This is APPLE of course... well, let's see... ")
            set(ALT_PYTHON_LIBRARIES "${ALT_PYTHON_PREFIX}/lib/libpython${ALT_PYTHON_LIBRARY_SUFFIX}.dylib")
            if(${PYTHON_LIBRARIES} STREQUAL ${ALT_PYTHON_LIBRARIES})
                message(STATUS "----> ... we found that the library is OK. Ignoring complain.")
                set(PYTHONLIBS_FOUND TRUE)
            else()
                if(EXISTS ${ALT_PYTHON_LIBRARIES})
                    message(STATUS "----> ... there is another one which seems to be OK ${ALT_PYTHON_LIBRARIES}.")
                    set(PYTHONLIBS_FOUND TRUE)
                    set(PYTHON_LIBRARIES ${ALT_PYTHON_LIBRARIES} PARENT_SCOPE)
                endif()
            endif()
        endif()
    endif()

    if(PYTHONLIBS_FOUND)
        if(NOT WIN32)
            GET_FILENAME_COMPONENT(PyLibExtension ${PYTHON_LIBRARIES} EXT)
            if(${PyLibExtension}  STREQUAL ".a")
                find_package( Threads )
                set(syslibs "-lm -ldl -lutil ${CMAKE_THREAD_LIBS_INIT} -rdynamic")
                message(STATUS "----> Static python library detected, adding ${syslibs}")
                set(PYTHON_LIBRARIES "${syslibs} ${PYTHON_LIBRARIES}" PARENT_SCOPE)
            endif()
        endif()
        if(BUILD_DEBIAN)
            set(PYTHON_SITE_PACKAGES ${ALT_PYTHON_SITE_PACKAGES} PARENT_SCOPE)
        endif()
    endif()

    if(PYTHONLIBS_FOUND)
        set(PYTHONLIBS_FOUND TRUE PARENT_SCOPE)
        message(STATUS "--> Python seems to be OK.")
    else()
        message(FATAL_ERROR "No appropriate Python library has been found. Sorry.")
    endif()

#    set(ALT_PYTHONLIBS_FOUND ${ALT_PYTHONLIBS_FOUND} PARENT_SCOPE)
#    set(ALT_PYTHON_VERSION_STRING ${ALT_PYTHON_VERSION_STRING} PARENT_SCOPE)
#    set(ALT_PYTHON_INCLUDE_DIRS ${ALT_PYTHON_INCLUDE_DIRS} PARENT_SCOPE)
endfunction()
