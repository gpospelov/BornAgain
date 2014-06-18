cmake_minimum_required(VERSION 2.8.9 FATAL_ERROR)

if(POLICY CMP0020)
cmake_policy(SET CMP0020 NEW)
endif()

set(executable_name BornAgain)

include_directories(
    ${BornAgainGUI_INCLUDE_DIRS}
    ${ManhattanStyle_INCLUDE_DIRS}
)

add_executable(${executable_name} main.cpp)

target_link_libraries(${executable_name}
    ${ManhattanStyle_LIBRARY}
    ${qcustomplot_LIBRARY}
    ${qtpropertybrowser_LIBRARY}
    ${PYTHON_LIBRARY}
    ${Boost_LIBRARIES}
    ${BornAgainCore_LIBRARY}
    ${BornAgainFit_LIBRARY}
    ${BornAgainGUI_LIBRARY}
)

# --- Installation ---
install (TARGETS ${executable_name} DESTINATION ${destination_bin} COMPONENT Applications)

