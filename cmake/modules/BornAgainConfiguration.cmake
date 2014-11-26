############################################################################
# BornAgain project configuration
############################################################################

# --- cmake runtime output configuration ---------
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(destination_runtime_configs ${CMAKE_BINARY_DIR}/runtime_configs)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${destination_runtime_configs})

# creating bornagain/__init__.py in runtime lib directory
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/bornagain)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/dev-tools/python-setup/bornagain ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/bornagain)


# --- file extensions ---------
if(WIN32)
  set(libprefix lib)
  set(libsuffix .dll)
elseif(APPLE)
  set(libprefix lib)
  set(libsuffix .so)
else()
  set(libprefix lib)
  set(libsuffix .so)
endif()


# --- destinations ---------
if(WIN32)
    set(destination_bin bin)
    set(destination_lib bin)
    set(destination_gui bin)
    set(destination_include include)
    set(destination_examples Examples)
    set(destination_images Images)

#elseif(APPLE)
#    set(destination_bundle BornAgain.app)
#    set(destination_prefix ${destination_bundle}/Contents)
#    set(destination_suffix BornAgain-${BornAgain_VERSION_MAJOR}.${BornAgain_VERSION_MINOR})

#    set(destination_bin ${destination_prefix}/bin)
#    set(destination_libexec ${destination_prefix}/libexec/${destination_suffix})
##    set(destination_gui ${destination_prefix}/MacOs)
#    set(destination_gui "./") # will be installed via bundle
#    set(destination_lib ${destination_prefix}/lib/${destination_suffix})
#    set(destination_include ${destination_prefix}/include/${destination_suffix})
#    set(destination_examples ${destination_prefix}/share/${destination_suffix}/Examples)
#    set(destination_images ${destination_prefix}/share/${destination_suffix}/Images)

else()

    set(destination_suffix BornAgain-${BornAgain_VERSION_MAJOR}.${BornAgain_VERSION_MINOR})

    if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
        set(destination_bundle BornAgain.app)
        set(destination_prefix ${destination_bundle}/Contents)
        set(destination_bin ${destination_prefix}/bin)
        set(destination_libexec ${destination_prefix}/libexec/${destination_suffix})
        set(destination_gui ${destination_libexec})
        set(destination_lib ${destination_prefix}/lib/${destination_suffix})
        set(destination_include ${destination_prefix}/include/${destination_suffix})
        set(destination_examples ${destination_prefix}/share/${destination_suffix}/Examples)
        set(destination_images ${destination_prefix}/share/${destination_suffix}/Images)
    else()
        set(destination_bin bin)
        set(destination_libexec libexec/${destination_suffix})
        set(destination_gui ${destination_libexec})
        set(destination_lib lib/${destination_suffix})
        set(destination_include include/${destination_suffix})
        set(destination_examples share/${destination_suffix}/Examples)
        set(destination_images share/${destination_suffix}/Images)
    endif()

endif()


# --- configure files  ---------

if(BORNAGAIN_RELEASE)
    # configure a header file to pass CMake settings to the source code
    configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/BAVersion.h.in"  "${CMAKE_SOURCE_DIR}/Core/Samples/inc/BAVersion.h")

    # configure deployment script for release
    configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/release.sh.in" "${CMAKE_BINARY_DIR}/bin/release.sh")

    # configure Doxyfile
    configure_file("${CMAKE_SOURCE_DIR}/Doc/Doxygen/Doxyfile.in" "${CMAKE_SOURCE_DIR}/Doc/Doxygen/Doxyfile" @ONLY)
endif()


# --- configure BornAgain scripts ---------
set(this_bindir $BORNAGAINSYS/bin)
set(this_libdir $BORNAGAINSYS/lib/${destination_suffix})
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/thisbornagain.sh.in" "${destination_runtime_configs}/frombin_setup_paths.sh" @ONLY)
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/thisbornagain.csh.in" "${destination_runtime_configs}/frombin_setup_paths.csh" @ONLY)


# --- configure C++ source code ---------
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/BAConfigure.h.in" "${destination_runtime_configs}/BAConfigure.h" @ONLY)
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/BAPython.h.in" "${destination_runtime_configs}/BAPython.h" @ONLY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${destination_runtime_configs}")


