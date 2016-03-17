###############################################################################
# BornAgain project configuration
###############################################################################

# -----------------------------------------------------------------------------
# Common policies
# -----------------------------------------------------------------------------

# --- from GUI section

#if(POLICY CMP0020)
#    cmake_policy(SET CMP0020 NEW)
#endif()

#if(POLICY CMP0043)
#    cmake_policy(SET CMP0043 NEW)
#endif()

#if(POLICY CMP0028)
#    cmake_policy(SET CMP0028 NEW)
#endif()


# -----------------------------------------------------------------------------
# Common definitions
# -----------------------------------------------------------------------------


# suppress qDebug() output for release build
if(CMAKE_BUILD_TYPE STREQUAL Release)
  add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

# -----------------------------------------------------------------------------
# cmake runtime output configuration
# -----------------------------------------------------------------------------

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(destination_runtime_configs ${CMAKE_BINARY_DIR}/runtime_configs)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${destination_runtime_configs})

# creating bornagain/__init__.py in runtime lib directory
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/bornagain)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/dev-tools/python-setup/bornagain ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/bornagain)

# -----------------------------------------------------------------------------
# file extensions
# -----------------------------------------------------------------------------
if(WIN32)
  set(libprefix _lib)
  set(libsuffix .dll)
elseif(APPLE)
  set(libprefix lib)
  set(libsuffix .so)
else()
  set(libprefix _lib)
  set(libsuffix .so)
endif()


# -----------------------------------------------------------------------------
# destinations
# -----------------------------------------------------------------------------
if(WIN32)
    set(destination_bin bin)
    set(destination_lib bin)
    set(destination_gui bin)
    set(destination_include include)
    set(destination_examples Examples)
    set(destination_images Images)
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


# -----------------------------------------------------------------------------
# configure files
# -----------------------------------------------------------------------------


if(BORNAGAIN_RELEASE)
    # configure a header file to pass CMake settings to the source code
    configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/BAVersion.h.in"  "${CMAKE_SOURCE_DIR}/Core/Samples/inc/BAVersion.h")

    # configure Doxyfile
    configure_file("${CMAKE_SOURCE_DIR}/Doc/Doxygen/Doxyfile.in" "${CMAKE_SOURCE_DIR}/Doc/Doxygen/Doxyfile" @ONLY)

    # configure FindBornagain script
    configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/FindBornAgain.cmake.in"  "${CMAKE_SOURCE_DIR}/Examples/cpp/CylindersAndPrisms/modules/FindBornAgain.cmake" @ONLY)

endif()


# -----------------------------------------------------------------------------
# configure BornAgain launch scripts
# -----------------------------------------------------------------------------
set(this_bindir $BORNAGAINSYS/bin)
set(this_libdir $BORNAGAINSYS/lib/${destination_suffix})
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/thisbornagain.sh.in" "${destination_runtime_configs}/frombin_setup_paths.sh" @ONLY)
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/thisbornagain.csh.in" "${destination_runtime_configs}/frombin_setup_paths.csh" @ONLY)


# -----------------------------------------------------------------------------
# configure BornAgain's Python init module
# -----------------------------------------------------------------------------
set(BA_MODULES_IMPORT_PATH "..")
if(BORNAGAIN_APPLE_BUNDLE)
    set(BA_MODULES_IMPORT_PATH lib/BornAgain-${BornAgain_VERSION_MAJOR}.${BornAgain_VERSION_MINOR})
endif()
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/__init__.py.in" "${destination_runtime_configs}/__init__.py" @ONLY)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy "${destination_runtime_configs}/__init__.py" ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/bornagain)


# -----------------------------------------------------------------------------
# configure C++ source code
# -----------------------------------------------------------------------------
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/BAConfigure.h.in" "${destination_runtime_configs}/BAConfigure.h" @ONLY)
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/BAPython.h.in" "${destination_runtime_configs}/BAPython.h" @ONLY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${destination_runtime_configs}")


# -----------------------------------------------------------------------------
# configure postinst and prerm for the debian package
# -----------------------------------------------------------------------------
if(BUILD_DEBIAN)
    set(CMAKE_INSTALL_PREFIX "/usr")
    execute_process(COMMAND "${PYTHON_EXECUTABLE}" -c "from distutils import sysconfig; print sysconfig.get_python_lib(1,0,prefix=None)"
        OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/postinst.in" "${destination_runtime_configs}/postinst" @ONLY)
    configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/prerm.in" "${destination_runtime_configs}/prerm" @ONLY)
    set(CMAKE_INSTALL_RPATH "\$ORIGIN/../../lib/${destination_suffix}")
endif(BUILD_DEBIAN)


