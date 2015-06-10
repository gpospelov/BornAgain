# This function will prevent in-source builds

function(AssureOutOfSourceBuilds)
  # make sure the user doesn't play dirty with symlinks
  get_filename_component(srcdir "${CMAKE_SOURCE_DIR}" REALPATH)
  get_filename_component(bindir "${CMAKE_BINARY_DIR}" REALPATH)

  # disallow in-source builds
  if("${srcdir}" STREQUAL "${bindir}")
    message("###########################################################################")
    message("We do not allow cmake to be run in the source directory.")
    message("You must run cmake in a build directory.")
    message("For example:")
    message("  cd <source directory>")
    message("  mkdir build")
    message("  cd build")
    message("  cmake .. # or ccmake, or cmake-gui")
    message("")
    message("To clean up after this aborted in-place compilation:")
    message("  rm -r CMakeCache.txt CMakeFiles/")
    message("###########################################################################")
    message(FATAL_ERROR "Quitting configuration")
  endif()
endfunction()

AssureOutOfSourceBuilds()
