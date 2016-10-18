############################################################################
# CMakeLists.txt file for building BornAgain/GUI libraries and executable
############################################################################
if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()

message(STATUS "Configuring BornAgain GUI")

add_subdirectory(coregui)

if(BORNAGAIN_CRASHHANDLER)
    add_definitions(-DBORNAGAIN_CRASHHANDLER)
    add_subdirectory(crashhandler)
endif()

add_subdirectory(main)

set(BornAgainGUI_INCLUDE_DIRS
    ${BornAgainGUI_INCLUDE_DIRS}
    PARENT_SCOPE)
set(BornAgainGUI_LIBRARY
    ${BornAgainGUI_LIBRARY}
    PARENT_SCOPE)
