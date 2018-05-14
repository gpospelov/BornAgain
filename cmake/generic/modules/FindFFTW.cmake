# Find the FFTW includes and library.
# 
# This module defines
# FFTW_INCLUDE_DIR, where to locate fftw3.h file
# FFTW_LIBRARIES, the libraries to link against to use fftw3
# FFTW_FOUND.  If false, you cannot build anything that requires fftw3.
# FFTW_LIBRARY, where to find the libfftw3 library.

set(FFTW_FOUND 0)
if(FFTW_LIBRARY AND FFTW_INCLUDE_DIR)
  set(FFTW_FIND_QUIETLY TRUE)
endif()

if(NOT WIN32)
    find_path(FFTW_INCLUDE_DIR fftw3.h
        $ENV{FFTW_DIR}/include
        $ENV{FFTW3} $ENV{FFTW3}/include $ENV{FFTW3}/api
        /usr/local/include
        /usr/include
        /opt/fftw3/include
        /opt/local/include
        DOC "Specify the directory containing fftw3.h"
    )

    find_library(FFTW_LIBRARY NAMES fftw3 fftw3-3 PATHS
        $ENV{FFTW_DIR}/lib
        $ENV{FFTW3} $ENV{FFTW3}/lib $ENV{FFTW3}/.libs
        /usr/local/lib
        /usr/lib 
        /opt/fftw3/lib
        HINTS /opt/local/lib
        DOC "Specify the fttw3 library here."
    )
else()
    find_path(FFTW_INCLUDE_DIR fftw3.h
        HINTS ENV PATH
        PATHS "C:/opt/local_x64/include"  # if fftw cannot be found in env path
        PATH_SUFFIXES ../include
        NO_DEFAULT_PATH
    )
#    message("XXX ${FFTW_INCLUDE_DIR}")

    find_library(FFTW_LIBRARY libfftw3-3
        HINTS ENV PATH
        PATHS "C:/opt/local_x64/lib"  # if fftw cannot be found in env path
        NO_DEFAULT_PATH
    )

    string( REPLACE ".lib" ".dll" FFTW_LIBRARY_DLL "${FFTW_LIBRARY}" )
    if (NOT EXISTS ${FFTW_LIBRARY_DLL})
        message(FATAL_ERROR "File ${FFTW_LIBRARY_DLL} does not exist")
    endif (NOT EXISTS ${FFTW_LIBRARY_DLL})
endif()

if(FFTW_INCLUDE_DIR AND FFTW_LIBRARY)
  set(FFTW_FOUND 1 )
  if(NOT FFTW_FIND_QUIETLY)
     message(STATUS "Found fftw3 includes at ${FFTW_INCLUDE_DIR}")
     message(STATUS "Found fftw3 library at ${FFTW_LIBRARY}")
  endif()
endif()


if( NOT FFTW_FOUND )
    if( FFTW_FIND_REQUIRED )
        message( FATAL_ERROR "FindFFTW: can't find fftw3 header or library" )
    endif()
endif()


set(FFTW_LIBRARIES ${FFTW_LIBRARY})

mark_as_advanced(FFTW_FOUND FFTW_LIBRARY FFTW_INCLUDE_DIR FFTW_LIBRARY_DLL)
