# file to build installer

include(InstallRequiredSystemLibraries)

set(BORNAGAIN_MAJOR_VERSION "0")
set(BORNAGAIN_MINOR_VERSION "9")
set(BORNAGAIN_PATCH_VERSION "0")

set(BORNAGAIN_VERSION "${BORNAGAIN_MAJOR_VERSION}.${BORNAGAIN_MINOR_VERSION}.${BORNAGAIN_PATCH_VERSION}")

message("XXX ${Boost_LIBRARY_DIRS} ${FFTW_LIBRARY}")
if(WIN32)
    if(MSVC)
        set(boost_suffix "-vc110-mt-1_54.dll")
        install(FILES 
        ${CMAKE_LIBRARY_PATH}/boost_date_time${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_chrono${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_program_options${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_zlib${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_bzip2${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_iostreams${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_system${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_filesystem${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_regex${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_thread${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/libfftw3-3.dll
        DESTINATION bin COMPONENT Libraries)
    else()
        install (FILES ${Boost_LIBRARIES} DESTINATION bin COMPONENT Libraries)
        install (FILES ${FFTW_LIBRARY} DESTINATION bin COMPONENT Libraries)
        install (FILES ${GSL_LIBRARIES} DESTINATION bin COMPONENT Libraries)    
    endif()
endif()

set(CPACK_PACKAGE_NAME "BornAgain")
set(CPACK_PACKAGE_DESCRIPTION "BornAgain: simulate and fit scattering at grazing incidence")
set(CPACK_PACKAGE_VENDOR "Sceintific Computing at MLZ")
set(CPACK_PACKAGE_VERSION ${BORNAGAIN_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${BORNAGAIN_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${BORNAGAIN_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${BORNAGAIN_PATCH_VERSION})

configure_file(LICENSE LICENSE.txt COPYONLY)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_BINARY_DIR}/LICENSE.txt")


#set(CPACK_MONOLITHIC_INSTALL ON)

# binary package setup
set(CPACK_PACKAGE_RELOCATABLE True)


if(CMAKE_BUILD_TYPE STREQUAL Release)
    set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${BORNAGAIN_VERSION}-${BORNAGAIN_ARCHITECTURE}")
else()
    set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${BORNAGAIN_VERSION}-${BORNAGAIN_ARCHITECTURE}-${CMAKE_BUILD_TYPE}")
endif()

set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CMAKE_PROJECT_NAME}-${BORNAGAIN_VERSION}")

if(WIN32)
  set(CPACK_GENERATOR "NSIS")  
elseif(APPLE)
  set(CPACK_GENERATOR "PackageMaker;TGZ")
else()
  set(CPACK_GENERATOR "STGZ;TGZ")
endif()

#configure_file(cmake/Templates/CMakeCPackOptions.cmake.in CMakeCPackOptions.cmake @ONLY)
#set(CPACK_PROJECT_CONFIG_FILE ${CMAKE_BINARY_DIR}/CMakeCPackOptions.cmake)

set(CPACK_NSIS_MODIFY_PATH ON)

include(CPack)

set(CPACK_COMPONENTS_ALL Libraries Headers Examples)

#cpack_add_install_type(full      DISPLAY_NAME "Full Installation")
#cpack_add_install_type(runtime   DISPLAY_NAME "Runtime Installation")
#cpack_add_install_type(developer DISPLAY_NAME "Developer Installation")

# - Components for Development
#cpack_add_component(Headers
#    DISPLAY_NAME "Development Components (headers)" 
#    DESCRIPTION "Install all files needed for developing BornAgain applications"
#    INSTALL_TYPES developer full
#)

# - Components for Runtime
#cpack_add_component(Libraries
#    DISPLAY_NAME "BornAgain runtime Libraries" 
#    DESCRIPTION "Install all BornAgain libraries"
#    INSTALL_TYPES runtime developer full
#)

# - Components for Examples
#cpack_add_component(Examples 
#    DISPLAY_NAME "Usage Examples"
#    DESCRIPTION "Install all BornAgain examples"
#    INSTALL_TYPES full developer
#)

#cpack_add_component(Applications
#    DISPLAY_NAME "Applications"
#    DESCRIPTION "Install all BornAgain executables"
##    INSTALL_TYPES full developer
#)


# - Components for Data
#cpack_add_component(Data 
#    DISPLAY_NAME "Geant4 Data Files" 
#    DESCRIPTION "Install all Geant4 data files"
#    INSTALL_TYPES full
#)


