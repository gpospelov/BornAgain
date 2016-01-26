add_custom_target(
    man ALL
    DEPENDS bornagain.1
)

add_custom_command(
    OUTPUT bornagain.1
    COMMAND pod2man -s 1 -c "BornAgain manual" ${CMAKE_CURRENT_SOURCE_DIR}/bornagain.pod ${CMAKE_CURRENT_BINARY_DIR}/bornagain.1
    DEPENDS bornagain.pod
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bornagain.1 DESTINATION ${CMAKE_INSTALL_PREFIX}/man/man1)
