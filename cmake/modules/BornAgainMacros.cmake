# --- Collection of scripts for BornAgain CMake infrastructure

#cmake_minimum_required(VERSION 2.8 FATAL_ERROR)



# --- end of the version setting ---

#set(lib lib)
#set(bin bin)

#execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/lib)
#execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin)

##set(BORNAGAIN_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

##set(BORNAGAIN_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
##set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BORNAGAIN_RUNTIME_OUTPUT_DIRECTORY})
##set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BORNAGAIN_RUNTIME_OUTPUT_DIRECTORY})
##set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BORNAGAIN_RUNTIME_OUTPUT_DIRECTORY})
##set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BORNAGAIN_RUNTIME_OUTPUT_DIRECTORY})
##set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
##set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


#if(WIN32)
#  set(ssuffix .bat)
#  set(scomment rem)
#  set(libprefix lib)
#  set(ld_library_path PATH)
#  set(libsuffix .dll)
#  set(runtimedir bin)
#  #set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.lib;.dll") # doesn't work anyway for MSVC generator
#
#elseif(APPLE)
#  set(ld_library_path DYLD_LIBRARY_PATH)
#  set(ssuffix .csh)
#  set(scomment \#)
#  set(libprefix lib)
#  set(libsuffix .so)
#  set(runtimedir lib)
#else()
#  set(ld_library_path LD_LIBRARY_PATH)
#  set(ssuffix .csh)
#  set(scomment \#)
#  set(libprefix lib)
#  set(libsuffix .so)
#  set(runtimedir lib)
#endif()




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
  else ()
  endif ()
  set (${VAR} "${${VAR}}" PARENT_SCOPE)
endfunction ()



# -----------------------------------------------------------------------------
# to disable in-source builds
# -----------------------------------------------------------------------------
#function(AssureOutOfSourceBuilds)

#    # make sure the user doesn't play dirty with symlinks
#    get_filename_component(srcdir "${CMAKE_SOURCE_DIR}" REALPATH)
#    get_filename_component(bindir "${CMAKE_BINARY_DIR}" REALPATH)

#    # disallow in-source builds
#    message("XXX ${srcdir} ${bindir} "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" ")

#    if(${srcdir} STREQUAL ${bindir})
#        message("######################################################")
#        message("You are attempting to build in your Source Directory.")
#        message("You must run cmake from a build directory.")
#        message("######################################################")


#        # attempt to remove cache and cache files... this actually fails to work,
#        # but no hurt trying incase it starts working..
#        file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/CMakeCache.txt" "${CMAKE_SOURCE_DIR}/CMakeFiles")

#        message(FATAL_ERROR "In-source builds are forbidden!")
#    endif()

#    # check for polluted source tree

#    if(EXISTS ${CMAKE_SOURCE_DIR}/CMakeCache.txt OR EXISTS
#        ${CMAKE_SOURCE_DIR}/CMakeFiles)


#        message("################################################################")
#        message( "Found results from an in-source build in your sourcedirectory.")
#        message("################################################################")

#        # attempt to remove cache and cache files...
#        file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/CMakeCache.txt" "${CMAKE_SOURCE_DIR}/CMakeFiles")

#        message(FATAL_ERROR "Source Directory Cleaned, please rerun CMake.")
#  endif()
#endfunction()

