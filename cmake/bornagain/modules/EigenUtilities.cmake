# This file contains a cmake function, which helps to mute
# Eigen warnings.
# After updating Eigen to >= 3.3.5
# it can be removed, but since it is not the first time
# warnings from Eigen arise, it is better to use the
# function as a wrapper around include_directories
# and modify it if necessary

function(include_eigen)
    if(NOT DEFINED EIGEN3_INCLUDE_DIR)
        message(FATAL_ERROR "EIGEN3_INCLUDE_DIR is undefined")
    endif(NOT DEFINED EIGEN3_INCLUDE_DIR)
    include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})
endfunction(include_eigen)
