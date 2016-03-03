# Find the native numpy includes
# This module defines
#  NUMPY_INCLUDE_DIR, where to find numpy/arrayobject.h, etc.
#  NUMPY_FOUND, If false, do not try to use numpy headers.

if (NUMPY_INCLUDE_DIR)
  # in cache already
  set (Numpy_FIND_QUIETLY TRUE)
endif (NUMPY_INCLUDE_DIR)

if(NOT Numpy_FIND_QUIETLY)
EXEC_PROGRAM ("${PYTHON_EXECUTABLE}"
  ARGS "-c \"import numpy; print(numpy.get_include())\""
  OUTPUT_VARIABLE NUMPY_INCLUDE_DIR
  RETURN_VALUE NUMPY_NOT_FOUND)
endif()

if (NUMPY_INCLUDE_DIR MATCHES "Traceback")
    # Did not successfully include numpy
    set(NUMPY_FOUND FALSE)
else()
    # successful
    if(NOT EXISTS ${NUMPY_INCLUDE_DIR}/numpy/arrayobject.h)
        message(STATUS "Can't find numpy/arrayobject.h, please install python-numpy-devel package")
    else()
        set (NUMPY_FOUND TRUE)
        set (NUMPY_INCLUDE_DIR ${NUMPY_INCLUDE_DIR} CACHE STRING "Numpy include path")
        EXEC_PROGRAM ("${PYTHON_EXECUTABLE}"
        ARGS "-c \"import numpy; print(numpy.__version__)\""
        OUTPUT_VARIABLE numpy_version_number
        RETURN_VALUE numpy_return_value)
    endif()
endif()

if (NUMPY_FOUND)
    if (NOT Numpy_FIND_QUIETLY)
        message (STATUS "Numpy headers found at ${NUMPY_INCLUDE_DIR}, version ${numpy_version_number}.")
    endif()
else()
    if (Numpy_FIND_REQUIRED)
        message (FATAL_ERROR "Numpy headers missing, please install python-numpy-devel package")
    endif()
endif()


MARK_AS_ADVANCED (NUMPY_INCLUDE_DIR)
