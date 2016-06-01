set(AUTODIR "${CMAKE_SOURCE_DIR}/auto/Doc/man")
file(MAKE_DIRECTORY ${AUTODIR})

add_custom_target(
    man ALL
    DEPENDS "${AUTODIR}/bornagain.1"
)

add_custom_command(
    OUTPUT "${AUTODIR}/bornagain.1"
    COMMAND ${POD2MAN} -s 1 -c "BornAgain manual" ${CMAKE_CURRENT_SOURCE_DIR}/bornagain.pod ${AUTODIR}/bornagain.1
    DEPENDS bornagain.pod
)

install(FILES ${AUTODIR}/bornagain.1 DESTINATION ${CMAKE_INSTALL_PREFIX}/man/man1)
