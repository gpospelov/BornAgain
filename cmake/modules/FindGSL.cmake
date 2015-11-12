# Try to find gnu scientific library GSL
# See
# http://www.gnu.org/software/gsl/  and
# http://gnuwin32.sourceforge.net/packages/gsl.htm
#
# Based on a script of Felix Woelk and Jan Woetzel
# (www.mip.informatik.uni-kiel.de)
#
# It defines the following variables:
#  GSL_FOUND - system has GSL lib
#  GSL_INCLUDE_DIRS - where to find headers
#  GSL_LIBRARIES - full path to the libraries
#  GSL_LIBRARY_DIRS, the directory where the PLplot library is found.
#  GSL_CFLAGS, additional c (c++) required



#FIXME check windows
IF(WIN32)
    find_path( GSL_INCLUDE_DIR
        NAMES gsl/gsl_cdf.h gsl/gsl_randist.h
        PATHS
        $ENV{GSL_DIR}/include
        "C:/opt/local/include"
    )

    set(gsl_library_name gsl)
    set(gslcblas_library_name cblas)

    if( GSL_INCLUDE_DIR )
        # look for gsl library
        find_library( GSL_LIBRARY
            NAMES ${gsl_library_name}
            PATHS
            #$ENV{GSL_DIR}/lib
            "C:/opt/local/lib"
        )

        if( GSL_LIBRARY )
            set( GSL_INCLUDE_DIRS ${GSL_INCLUDE_DIR} )
            get_filename_component( GSL_LIBRARY_DIRS ${GSL_LIBRARY} PATH )
            set( GSL_FOUND ON )
        endif( GSL_LIBRARY )

        # look for gsl cblas library
        find_library( GSL_CBLAS_LIBRARY
            NAMES ${gslcblas_library_name}
            PATHS $ENV{GSL_DIR}/lib
            "C:/opt/local/lib"
        )

        if( GSL_CBLAS_LIBRARY )
            set( GSL_CBLAS_FOUND ON )
        endif( GSL_CBLAS_LIBRARY )

        set( GSL_LIBRARIES ${GSL_LIBRARY} ${GSL_CBLAS_LIBRARY} )
        set( GSL_CFLAGS "-DGSL_DLL")
    endif( GSL_INCLUDE_DIR )

    mark_as_advanced(
        GSL_INCLUDE_DIR
        GSL_LIBRARY
        GSL_CBLAS_LIBRARY
    )

#     SET(GSL_POSSIBLE_ROOT_DIRS
#         ${GSL_ROOT_DIR}
#         $ENV{GSL_ROOT_DIR}
#         ${GSL_DIR}
#         ${GSL_HOME}
#         $ENV{GSL_DIR}
#         $ENV{GSL_HOME}
#         $ENV{EXTRA}
#         "C:/Program Files/GnuWin32")
#
#     FIND_PATH(GSL_INCLUDE_DIR
#         NAMES gsl/gsl_cdf.h gsl/gsl_randist.h
#         PATHS ${GSL_POSSIBLE_ROOT_DIRS}
#         PATH_SUFFIXES include
#         DOC "GSL header include dir")
#
#     FIND_LIBRARY(GSL_GSL_LIBRARY
#         NAMES libgsl.dll.a gsl libgsl
#         PATHS  ${GSL_POSSIBLE_ROOT_DIRS}
#         PATH_SUFFIXES lib
#         DOC "GSL library")
#
#     if(NOT GSL_GSL_LIBRARY)
#         FIND_FILE(GSL_GSL_LIBRARY
#             NAMES libgsl.dll.a
#             PATHS  ${GSL_POSSIBLE_ROOT_DIRS}
#             PATH_SUFFIXES lib
#             DOC "GSL library")
#     endif(NOT GSL_GSL_LIBRARY)
#
#     FIND_LIBRARY(GSL_GSLCBLAS_LIBRARY
#         NAMES libgslcblas.dll.a gslcblas libgslcblas
#         PATHS  ${GSL_POSSIBLE_ROOT_DIRS}
#         PATH_SUFFIXES lib
#         DOC "GSL cblas library dir")
#
#     if(NOT GSL_GSLCBLAS_LIBRARY)
#         FIND_FILE(GSL_GSLCBLAS_LIBRARY
#             NAMES libgslcblas.dll.a
#             PATHS  ${GSL_POSSIBLE_ROOT_DIRS}
#             PATH_SUFFIXES lib
#             DOC "GSL library")
#     endif(NOT GSL_GSLCBLAS_LIBRARY)
#
#     SET(GSL_LIBRARIES ${GSL_GSL_LIBRARY})


ELSE(WIN32)

    IF(UNIX)
        SET(GSL_CONFIG_PREFER_PATH
            "$ENV{GSL_DIR}/bin"
            "$ENV{GSL_DIR}"
            "$ENV{GSL_HOME}/bin"
            "$ENV{GSL_HOME}"
            CACHE STRING "preferred path to GSL (gsl-config)")
        FIND_PROGRAM(GSL_CONFIG gsl-config
            ${GSL_CONFIG_PREFER_PATH}
            /usr/bin/
            /usr/local/bin/)

        IF (GSL_CONFIG)
            # set CXXFLAGS to be fed into CXX_FLAGS by the user:
            SET(GSL_CXX_FLAGS "`${GSL_CONFIG} --cflags`")

            # set INCLUDE_DIRS to prefix+include
            EXEC_PROGRAM(${GSL_CONFIG}
                ARGS --prefix
                OUTPUT_VARIABLE GSL_PREFIX)
            SET(GSL_INCLUDE_DIR ${GSL_PREFIX}/include CACHE STRING INTERNAL)

            # set link libraries and link flags
            EXEC_PROGRAM(${GSL_CONFIG}
                ARGS --libs
                OUTPUT_VARIABLE GSL_LIBRARIES )

            # extract link dirs for rpath
            EXEC_PROGRAM(${GSL_CONFIG}
                ARGS --libs
                OUTPUT_VARIABLE GSL_CONFIG_LIBS )

            # extract version
            EXEC_PROGRAM(${GSL_CONFIG}
                ARGS --version
                OUTPUT_VARIABLE GSL_FULL_VERSION )

            # split version as major/minor
            STRING(REGEX MATCH "(.)\\..*" GSL_VERSION_MAJOR_ "${GSL_FULL_VERSION}")
            SET(GSL_VERSION_MAJOR ${CMAKE_MATCH_1})
            STRING(REGEX MATCH ".\\.(.*)" GSL_VERSION_MINOR_ "${GSL_FULL_VERSION}")
            SET(GSL_VERSION_MINOR ${CMAKE_MATCH_1})

            # define BORNAGAIN_GSL_BIGGEROREQUAL_2 when gsl version >= 2.0
            IF (NOT ${GSL_FULL_VERSION} VERSION_LESS 2.0)
                add_definitions(-DBORNAGAIN_GSL_BIGGEROREQUAL_2)
                message( STATUS "GSL version >= 2.0")
            ELSE (NOT ${GSL_FULL_VERSION} VERSION_LESS 2.0)
                message( STATUS "GSL version < 2.0")
            ENDIF (NOT ${GSL_FULL_VERSION} VERSION_LESS 2.0)

            # split off the link dirs (for rpath)
            # use regular expression to match wildcard equivalent "-L*<endchar>"
            # with <endchar> is a space or a semicolon
            STRING(REGEX MATCHALL "[-][L]([^ ;])+"
                GSL_LINK_DIRECTORIES_WITH_PREFIX
                "${GSL_CONFIG_LIBS}" )

            # remove prefix -L because we need the pure directory for LINK_DIRECTORIES

            IF (GSL_LINK_DIRECTORIES_WITH_PREFIX)
                STRING(REGEX REPLACE "[-][L]" "" GSL_LINK_DIRECTORIES ${GSL_LINK_DIRECTORIES_WITH_PREFIX} )
            ENDIF (GSL_LINK_DIRECTORIES_WITH_PREFIX)
            SET(GSL_EXE_LINKER_FLAGS "-Wl,-rpath,${GSL_LINK_DIRECTORIES}" CACHE STRING INTERNAL)

            #      ADD_DEFINITIONS("-DHAVE_GSL")
            #      SET(GSL_DEFINITIONS "-DHAVE_GSL")
            MARK_AS_ADVANCED(
                GSL_CXX_FLAGS
                GSL_INCLUDE_DIR
                GSL_LIBRARIES
                GSL_LINK_DIRECTORIES
                GSL_DEFINITIONS)
            #MESSAGE(STATUS "Using GSL from ${GSL_PREFIX}")
            message( STATUS "Found GSL version ${GSL_FULL_VERSION}, GSL_INCLUDE_DIR=${GSL_INCLUDE_DIR} GSL_LIBRARIES=${GSL_LIBRARIES}" )

        ELSE(GSL_CONFIG)
            MESSAGE("FindGSL.cmake: gsl-config not found. Please set it manually. GSL_CONFIG=${GSL_CONFIG}")
        ENDIF(GSL_CONFIG)

    ENDIF(UNIX)
ENDIF(WIN32)


IF(GSL_LIBRARIES)
  IF(GSL_INCLUDE_DIR OR GSL_CXX_FLAGS)
    SET(GSL_FOUND 1)
  ENDIF(GSL_INCLUDE_DIR OR GSL_CXX_FLAGS)
ENDIF(GSL_LIBRARIES)





#set( GSL_FOUND OFF )
#set( GSL_CBLAS_FOUND OFF )

#if(GSL_INCLUDE_DIR OR GSL_CONFIG_EXECUTABLE)
#  set(GSL_FIND_QUIETLY 1)
#endif()

## Windows, but not for Cygwin and MSys where gsl-config is available
#if( WIN32 AND NOT CYGWIN AND NOT MSYS )
#  # look for headers
#  find_path( GSL_INCLUDE_DIR
#    NAMES gsl/gsl_cdf.h gsl/gsl_randist.h
#        PATHS
#        $ENV{GSL_DIR}/include
#        "C:/opt/local/include"
#    )
##    message("XXXXX ${GSL_INCLUDE_DIR}")

#  if(MSVC)
#    set(gsl_library_name gsl)
#    set(gslcblas_library_name cblas)
#  else()
#    set(gsl_library_name libgsl-0)
#    set(gslcblas_library_name libgslcblas-0)
#  endif()


#  if( GSL_INCLUDE_DIR )
#    # look for gsl library
#    find_library( GSL_LIBRARY
#      NAMES ${gsl_library_name}
#          PATHS
#          #$ENV{GSL_DIR}/lib
#          "C:/opt/local/lib"
#    )
##    message("XXXXX ${GSL_LIBRARY}")
#    if( GSL_LIBRARY )
#      set( GSL_INCLUDE_DIRS ${GSL_INCLUDE_DIR} )
#      get_filename_component( GSL_LIBRARY_DIRS ${GSL_LIBRARY} PATH )
#      set( GSL_FOUND ON )
#    endif( GSL_LIBRARY )

#    # look for gsl cblas library
#    find_library( GSL_CBLAS_LIBRARY
#        NAMES ${gslcblas_library_name}
#		PATHS $ENV{GSL_DIR}/lib
#          "C:/opt/local/lib"
#      )
#    if( GSL_CBLAS_LIBRARY )
#      set( GSL_CBLAS_FOUND ON )
#    endif( GSL_CBLAS_LIBRARY )

#    set( GSL_LIBRARIES ${GSL_LIBRARY} ${GSL_CBLAS_LIBRARY} )
#	set( GSL_CFLAGS "-DGSL_DLL")
#  endif( GSL_INCLUDE_DIR )

#  mark_as_advanced(
#    GSL_INCLUDE_DIR
#    GSL_LIBRARY
#    GSL_CBLAS_LIBRARY
#  )
#else( WIN32 AND NOT CYGWIN AND NOT MSYS )
#  if( UNIX OR MSYS )
#    find_program( GSL_CONFIG_EXECUTABLE gsl-config
#      /usr/bin/
#      /usr/local/bin
#      $ENV{GSL_DIR}/bin
#      ${GSL_DIR}/bin
#    )

#    if( GSL_CONFIG_EXECUTABLE )
#      set( GSL_FOUND ON )

#      # run the gsl-config program to get cxxflags
#      execute_process(
#        COMMAND sh "${GSL_CONFIG_EXECUTABLE}" --cflags
#        OUTPUT_VARIABLE GSL_CFLAGS
#        RESULT_VARIABLE RET
#        ERROR_QUIET
#        )
#      if( RET EQUAL 0 )
#        string( STRIP "${GSL_CFLAGS}" GSL_CFLAGS )
#        separate_arguments( GSL_CFLAGS )

#        # parse definitions from cflags; drop -D* from CFLAGS
#        string( REGEX MATCHALL "-D[^;]+"
#          GSL_DEFINITIONS  "${GSL_CFLAGS}" )
#        string( REGEX REPLACE "-D[^;]+;" ""
#          GSL_CFLAGS "${GSL_CFLAGS}" )

#        # parse include dirs from cflags; drop -I prefix
#        string( REGEX MATCHALL "-I[^;]+"
#          GSL_INCLUDE_DIRS "${GSL_CFLAGS}" )
#        string( REPLACE "-I" ""
#          GSL_INCLUDE_DIRS "${GSL_INCLUDE_DIRS}")
#        string( REGEX REPLACE "-I[^;]+;" ""
#          GSL_CFLAGS "${GSL_CFLAGS}")
#      else( RET EQUAL 0 )
#        set( GSL_FOUND FALSE )
#      endif( RET EQUAL 0 )

#      # run the gsl-config program to get the libs
#      execute_process(
#        COMMAND sh "${GSL_CONFIG_EXECUTABLE}" --libs
#        OUTPUT_VARIABLE GSL_LIBRARIES
#        RESULT_VARIABLE RET
#        ERROR_QUIET
#        )
#      if( RET EQUAL 0 )
#        string(STRIP "${GSL_LIBRARIES}" GSL_LIBRARIES )
#        separate_arguments( GSL_LIBRARIES )

#        # extract linkdirs (-L) for rpath (i.e., LINK_DIRECTORIES)
#        string( REGEX MATCHALL "-L[^;]+"
#          GSL_LIBRARY_DIRS "${GSL_LIBRARIES}" )
#        string( REPLACE "-L" ""
#          GSL_LIBRARY_DIRS "${GSL_LIBRARY_DIRS}" )
#      else( RET EQUAL 0 )
#        set( GSL_FOUND FALSE )
#      endif( RET EQUAL 0 )

#      MARK_AS_ADVANCED(
#        GSL_CFLAGS
#      )
##      if(NOT GSL_FIND_QUIETLY)
##        execute_process(
##          COMMAND sh "${GSL_CONFIG_EXECUTABLE}" --prefix
##          OUTPUT_VARIABLE GSL_PREFIX OUTPUT_STRIP_TRAILING_WHITESPACE)
##        message( STATUS "Using GSL from ${GSL_PREFIX}")
##      endif()
#    else( GSL_CONFIG_EXECUTABLE )
#      message( STATUS "FindGSL: gsl-config not found.")
#    endif( GSL_CONFIG_EXECUTABLE )
#  endif( UNIX OR MSYS )
#endif( WIN32 AND NOT CYGWIN AND NOT MSYS )


#if(GSL_FOUND)
#    message( STATUS "Found GSL: GSL_INCLUDE_DIRS=${GSL_INCLUDE_DIRS} GSL_LIBRARIES=${GSL_LIBRARIES}" )
#else(GSL_FOUND)
#    if( GSL_FIND_REQUIRED )
#        message( FATAL_ERROR "FindGSL: Could not find GSL headers or library" )
#    endif( GSL_FIND_REQUIRED )
#endif()

