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
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgsl0-dev(>=1.15), libboost-dev(>=1.48), libfftw3-dev(>=3.3.1), python(>=2.7), python-dev(>=2.7), libpython2.7, python-numpy, libc6(>= 2.7), libqt5widgets5(>=5.1.0)")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION    "${CPACK_PACKAGE_DESCRIPTION}")
set(CPACK_DEBIAN_PACKAGE_VERSION ${BornAgain_VERSION_PATCH})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_DEBIAN_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}-${CPACK_DEBIAN_PACKAGE_VERSION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
set(CPACK_DEBIAN_PACKAGE_CONFLICTS "${CPACK_DEBIAN_PACKAGE_NAME}(<=${BORNAGAIN_VERSION})")

# set postinstall and preremove scripts for the debian package
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${destination_runtime_configs}/postinst;${destination_runtime_configs}/prerm;")

# write copyrite file [TODO:] fix the text of copyright
file(WRITE "${CMAKE_BINARY_DIR}/copyright"
     "Copyright (C) 2013 Sceintific Computing at MLZ

   This software is licensed under the terms of the
   GNU General Public License Version 3.

   Software distributed under the License is distributed
   on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
   express or implied. See the GPL for the specific language
   governing rights and limitations.

   You should have received a copy of the GPL along with this
   program. If not, go to http://www.gnu.org/licenses/gpl.html
   or write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

On Debian systems, the complete text of the GNU General Public
License can be found in `/usr/share/common-licenses/GPL-3'.")

install(FILES "${CMAKE_BINARY_DIR}/copyright"
        DESTINATION "share/doc/${CPACK_DEBIAN_PACKAGE_NAME}")


# write changelog file
FIND_PROGRAM(GIT_EXECUTABLE git)
FIND_PROGRAM(GIT2CL_EXECUTABLE git2cl)

# check if such commands are exist

if(GIT_EXECUTABLE AND GIT2CL_EXECUTABLE)
    set(GIT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.git")
    execute_process(COMMAND ${GIT_EXECUTABLE} --git-dir=${GIT_DIR} log 
            COMMAND ${GIT2CL_EXECUTABLE}
            COMMAND gzip -9
            OUTPUT_FILE "${CMAKE_BINARY_DIR}/changelog.gz")
    install(FILES "${CMAKE_BINARY_DIR}/changelog.gz" DESTINATION "share/doc/${CPACK_DEBIAN_PACKAGE_NAME}")
else()
    MESSAGE(STATUS "W: git or git2cl not found. Can't create the debian changelog file.")
endif(GIT_EXECUTABLE AND GIT2CL_EXECUTABLE)

    
    
