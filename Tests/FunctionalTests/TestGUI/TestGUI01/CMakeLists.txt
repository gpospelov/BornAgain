
set(executable_name TestGUI01)

include_directories(
    ${CMAKE_SOURCE_DIR}/GUI/coregui/mainwindow
    ${ManhattanStyle_INCLUDE_DIRS}
)

add_executable(${executable_name} TestGUI01.cpp)

target_link_libraries(${executable_name}
    ${BornAgainCore_LIBRARY}
    ${BornAgainFit_LIBRARY}
    ${BornAgainGUI_LIBRARY}
)

