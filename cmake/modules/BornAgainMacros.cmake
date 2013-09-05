cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(lib lib)
set(bin bin)

set(BORNAGAIN_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${BORNAGAIN_RUNTIME_OUTPUT_DIRECTORY})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BORNAGAIN_RUNTIME_OUTPUT_DIRECTORY})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BORNAGAIN_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BORNAGAIN_RUNTIME_OUTPUT_DIRECTORY}) # for msvc
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BORNAGAIN_RUNTIME_OUTPUT_DIRECTORY}) # for msvc

if(WIN32)
  set(ssuffix .bat)
  set(scomment rem)
  set(libprefix lib)
  set(ld_library_path PATH)
  set(libsuffix .dll)
  set(runtimedir bin)
  #set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.lib;.dll") # doesn't work anyway for MSVC generator

elseif(APPLE)
  set(ld_library_path DYLD_LIBRARY_PATH)
  set(ssuffix .csh)
  set(scomment \#)
  set(libprefix lib)
  set(libsuffix .so)
  set(runtimedir lib)
else()
  set(ld_library_path LD_LIBRARY_PATH)
  set(ssuffix .csh)
  set(scomment \#)
  set(libprefix lib)
  set(libsuffix .so) 
  set(runtimedir lib) 
endif()



# -----------------------------------------------------------------------------
# add executable (ARG, options, one_value_keyword, multi_value_keywoard arguments (aka ${ARG_UNPARSED_ARGUMENTS})
# -----------------------------------------------------------------------------
function(BORNAGAIN_EXECUTABLE executable)
    CMAKE_PARSE_ARGUMENTS(ARG "EXCLUDE_FROM_ALL" "" "LIBRARIES;LOCATIONS" "" ${ARGN})
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
# add cmake test
# -----------------------------------------------------------------------------
function(BORNAGAIN_ADD_TEST test)
    CMAKE_PARSE_ARGUMENTS(ARG "" "INPUT_DIR" "" "" ${ARGN})
    add_test( ${test}  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} "${ARG_INPUT_DIR}") # TestName ExeName
    add_dependencies(check ${test})
endfunction()

