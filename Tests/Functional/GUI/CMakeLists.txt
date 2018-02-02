if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()

find_package(Qt5Widgets REQUIRED)
include_directories(${BornAgainGUI_INCLUDE_DIRS})

add_subdirectory(GUIStandardTest)
add_subdirectory(GUISpecial)

