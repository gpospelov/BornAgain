# BornAgain project configuration

# --- cmake runtime output configuration ---------
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(destination_runtime_configs ${CMAKE_BINARY_DIR}/runtime_configs)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${destination_runtime_configs})


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
    set(destination_include include)
    set(destination_examples Examples)
    set(destination_images Images)

elseif(APPLE)
    set(destination_bundle BornAgain.app)
    set(destination_prefix ${destination_bundle}/Contents)
    set(destination_suffix BornAgain-${BornAgain_VERSION_MAJOR}.${BornAgain_VERSION_MINOR})

    set(destination_bin ${destination_prefix}/MacOs)
    set(destination_lib ${destination_prefix}/lib/${destination_suffix})
    set(destination_libexec ${destination_prefix}/libexec/${destination_suffix})
    set(destination_include ${destination_prefix}/include/${destination_suffix})
    set(destination_examples ${destination_prefix}/share/${destination_suffix}/Examples)
    set(destination_images ${destination_prefix}/share/${destination_suffix}/Images)

else()
    set(destination_bundle "")
    set(destination_prefix ${destination_bundle})
    set(destination_suffix BornAgain-${BornAgain_VERSION_MAJOR}.${BornAgain_VERSION_MINOR})

    set(destination_bin ${destination_prefix}/bin)
    set(destination_lib ${destination_prefix}/lib/${destination_suffix})
    set(destination_libexec ${destination_prefix}/libexec/${destination_suffix})
    set(destination_include ${destination_prefix}/include/${destination_suffix})
    set(destination_examples ${destination_prefix}/share/${destination_suffix}/Examples)
    set(destination_images ${destination_prefix}/share/${destination_suffix}/Images)
endif()


# --- configure files  ---------
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/thisbornagain.sh.in" "${destination_runtime_configs}/thisbornagain.sh" @ONLY)
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/thisbornagain.csh.in" "${destination_runtime_configs}/thisbornagain.csh" @ONLY)

if(BORNAGAIN_RELEASE)
    # configure a header file to pass CMake settings to the source code
    configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/BAVersion.h.in"  "${CMAKE_SOURCE_DIR}/Core/Samples/inc/BAVersion.h")

    # configure deployment script for release
    configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/release.sh.in" "${CMAKE_BINARY_DIR}/bin/release.sh")

    # configure Doxyfile
    configure_file("${CMAKE_SOURCE_DIR}/Doc/Doxygen/Doxyfile.in" "${CMAKE_SOURCE_DIR}/Doc/Doxygen/Doxyfile" @ONLY)
endif()


# --- configure C++ source code ---------
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/BAConfigure.h.in" "${destination_runtime_configs}/BAConfigure.h" @ONLY)
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/BAPython.h.in" "${destination_runtime_configs}/BAPython.h" @ONLY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${destination_runtime_configs}")


# --- installation of scripts, icons, etc ---------
function(install_thisbornagain_script)
    install(FILES ${destination_runtime_configs}/thisbornagain.sh
            ${destination_runtime_configs}/thisbornagain.csh
            PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
            GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
            DESTINATION ${destination_libexec})
endfunction()

if(WIN32)

elseif(APPLE)
    install_thisbornagain_script()

#install ( FILES ${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.icns
#          DESTINATION ${INBUNDLE}/Contents/Resources/)

##set ( CPACK_DMG_BACKGROUND_IMAGE ${CMAKE_SOURCE_DIR}/Images/osx-bundle-background.png )
##set ( CPACK_DMG_DS_STORE ${CMAKE_SOURCE_DIR}/Installers/MacInstaller/osx_DS_Store)
#set ( MACOSX_BUNDLE_ICON_FILE BornAgain.icns )
#SET_SOURCE_FILES_PROPERTIES(${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)


else()
    install_thisbornagain_script()

endif()



#if(APPLE AND CREATE_BUNDLE)
#  include(DarwinSetup)
#endif(APPLE AND CREATE_BUNDLE)
