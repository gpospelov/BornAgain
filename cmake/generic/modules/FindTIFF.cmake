#.rst:
# FindTIFF
# --------
#
# Find TIFF and TIFF/C++libraries
#
# This module defines
#
# ::
#
#   TIFF_INCLUDE_DIR, where to find tiff.h, etc.
#   TIFF_LIBRARIES, libraries to link against to use TIFF.
#   TIFF_FOUND, If false, do not try to use TIFF.
#
# also defined, but not for general use are
#
# ::
#
#   TIFF_LIBRARY, where to find the TIFF library.

# This is a heavily patched version of the CMake module FindTIFF.cmake
# Copyright 2002-2009 Kitware, Inc.
# Copyright 2013- BornAgain team
# Distributed under the OSI-approved BSD License

if(WIN32)
    find_path(TIFF_INCLUDE_DIR tiff.h PATHS ${CMAKE_INCLUDE_PATH}/libtiff NO_SYSTEM_ENVIRONMENT_PATH)
else()
    find_path(TIFF_INCLUDE_DIR tiff.h)
endif()

set(TIFF_NAMES ${TIFF_NAMES} libtiff tiff libtiff3 tiff3)
find_library(TIFF_LIBRARY NAMES ${TIFF_NAMES})

if(TIFF_INCLUDE_DIR AND EXISTS "${TIFF_INCLUDE_DIR}/tiffvers.h")
    file(STRINGS "${TIFF_INCLUDE_DIR}/tiffvers.h" tiff_version_str
         REGEX "^#define[\t ]+TIFFLIB_VERSION_STR[\t ]+\"LIBTIFF, Version .*")

    string(REGEX REPLACE "^#define[\t ]+TIFFLIB_VERSION_STR[\t ]+\"LIBTIFF, Version +([^ \\n]*).*"
           "\\1" TIFF_VERSION_STRING "${tiff_version_str}")
    unset(tiff_version_str)
endif()

# handle the QUIETLY and REQUIRED arguments and set TIFF_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TIFF
                                  REQUIRED_VARS TIFF_LIBRARY TIFF_INCLUDE_DIR
                                  VERSION_VAR TIFF_VERSION_STRING)

if(TIFF_FOUND)
    set( TIFF_LIBRARIES ${TIFF_LIBRARY} )
endif()

if(TIFF_FOUND)
    message(STATUS "Found TIFF version ${TIFF_VERSION_STRING}, includes at ${TIFF_INCLUDE_DIR}, libraries at ${TIFF_LIBRARIES}")

    if(NOT WIN32)
        # looking for C++ version of library libtiffxx.so
        list(LENGTH TIFF_LIBRARIES len)
        if(len EQUAL 1)
            get_filename_component(tiff_library_name ${TIFF_LIBRARIES} NAME_WE )
            get_filename_component(tiff_path ${TIFF_LIBRARIES} DIRECTORY )
            get_filename_component(tiff_ext ${TIFF_LIBRARIES} EXT )
            set(cpp_tiff_library "${tiff_path}/${tiff_library_name}xx${tiff_ext}")
            if(NOT EXISTS ${cpp_tiff_library})
                message(FATAL_ERROR "Could NOT find TIFF/C++ library ${cpp_tiff_library}.")
            endif()
            message(STATUS "Found TIFF C++ library ${cpp_tiff_library}")
            set(TIFF_LIBRARIES ${TIFF_LIBRARIES};${cpp_tiff_library})
        endif()
    endif()
endif()

mark_as_advanced(TIFF_INCLUDE_DIR TIFF_LIBRARY)
