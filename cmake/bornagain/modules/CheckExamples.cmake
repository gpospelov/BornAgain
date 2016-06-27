set(WEB_LEN_LIM 85) # maximum line length of code for display in Drupal web pages

# Check whether the line length of all python examples remains below WEB_LEN_LIM

file(GLOB PY_EXAMPLES "Examples/python/*/ex*/*.py")

add_test(NAME "PyExampleLineLength"
    COMMAND ${CMAKE_SOURCE_DIR}/dev-tools/code-tools/count-line-length.py ${WEB_LEN_LIM}
    ${PY_EXAMPLES})
