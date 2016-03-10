# BornAgain debian packaging 
set(CPACK_GENERATOR "DEB")

# parameters to build a debian package
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Marina Ganeva <m.ganeva@fz-juelich.de>") 

# Architecture: (mandatory)
IF(NOT CPACK_DEBIAN_PACKAGE_ARCHITECTURE)
    # There is no such thing as i686 architecture on debian, you should use i386 instead
    # $ dpkg --print-architecture
    FIND_PROGRAM(DPKG_CMD dpkg)
    IF(NOT DPKG_CMD)
        MESSAGE(STATUS "Can not find dpkg in your path, default to i386.")
        SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE i386)
    ENDIF(NOT DPKG_CMD)
    EXECUTE_PROCESS(COMMAND "${DPKG_CMD}" --print-architecture
        OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
ENDIF(NOT CPACK_DEBIAN_PACKAGE_ARCHITECTURE)


set(CPACK_DEBIAN_PACKAGE_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_STRIP_FILES "TRUE")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgsl0ldbl(>=1.15), libboost-date-time${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}, libboost-chrono${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}, libboost-python${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}, libboost-program-options${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}, libboost-iostreams${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}, libboost-regex${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}, libboost-filesystem${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}, libboost-thread${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}, libfftw3-3(>=3.3.1), python(>=2.7), libpython2.7, python-numpy, python-matplotlib, libc6(>= 2.7), libqt5widgets5(>=5.1.0), libtiffxx5(>=4.0.2)")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION    "${CPACK_PACKAGE_DESCRIPTION}")
set(CPACK_DEBIAN_PACKAGE_VERSION ${BornAgain_VERSION_PATCH})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_DEBIAN_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}-${CPACK_DEBIAN_PACKAGE_VERSION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
set(CPACK_DEBIAN_PACKAGE_CONFLICTS "${CPACK_DEBIAN_PACKAGE_NAME}(<=${BORNAGAIN_VERSION})")

# set postinstall and preremove scripts for the debian package
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${destination_runtime_configs}/postinst;${destination_runtime_configs}/prerm;")

# write copyrite file
file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/copyright" INPUT "${CMAKE_SOURCE_DIR}/COPYING")

install(FILES "${CMAKE_BINARY_DIR}/copyright"
        DESTINATION "share/${destination_suffix}")


# write changelog file
execute_process(COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/CHANGELOG" "${CMAKE_BINARY_DIR}/changelog")
# execute_process(COMMAND gzip -9 "${CMAKE_BINARY_DIR}/changelog" OUTPUT_FILE "${CMAKE_BINARY_DIR}/changelog.gz")
execute_process(COMMAND gzip -9 "${CMAKE_BINARY_DIR}/changelog")
install(FILES "${CMAKE_BINARY_DIR}/changelog.gz" DESTINATION "share/${destination_suffix}")
 
