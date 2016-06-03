# JWu 5/16: this long piece of code seems to be unused

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
