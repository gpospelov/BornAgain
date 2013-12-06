# - Finds BornAgain instalation
# This module sets up BornAgain information 
# It defines:
# BA_INCLUDE_DIR    PATH to the include directory
# BA_LIBRARY_DIR      PATH to the library directory
# BA_LIBRARY      PATH to the libBornAgainCore.so

if(NOT BORNAGAINSYS)
    set(BORNAGAINSYS /usr)
endif(NOT BORNAGAINSYS)

set(BA_LIBRARY_DIR ${BORNAGAINSYS}/lib)
set(BA_INCLUDE_DIR ${BORNAGAINSYS}/include/BornAgain)

find_library (BA_LIBRARY
        NAMES BornAgainCore
        PATHS ${BA_LIBRARY_DIR}
)
