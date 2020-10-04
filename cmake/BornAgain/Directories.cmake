# -----------------------------------------------------------------------------
# source directories
# -----------------------------------------------------------------------------

set(WRAP_DIR ${CMAKE_SOURCE_DIR}/Wrap)
set(AUTO_DIR ${CMAKE_SOURCE_DIR}/auto/Wrap)
set(TEST_OUTPUT_DIR ${CMAKE_BINARY_DIR}/test_output)
set(TEST_REFERENCE_DIR ${CMAKE_SOURCE_DIR}/Tests/ReferenceData)
set(PY_EXAMPLES_DIR ${CMAKE_SOURCE_DIR}/Examples/python)

file(MAKE_DIRECTORY ${AUTO_DIR})
file(MAKE_DIRECTORY ${TEST_OUTPUT_DIR})

# -----------------------------------------------------------------------------
# output directories
# -----------------------------------------------------------------------------

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(BUILD_VAR_DIR ${CMAKE_BINARY_DIR}/var)
set(BUILD_INC_DIR ${CMAKE_BINARY_DIR}/inc)
set(BUILD_SRC_DIR ${CMAKE_BINARY_DIR}/src)
configure_file("${CONFIGURABLES_DIR}/auto_README.in" "${CMAKE_SOURCE_DIR}/auto/README" @ONLY)

file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/bornagain)
file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/exec)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${BUILD_VAR_DIR})
file(MAKE_DIRECTORY ${BUILD_INC_DIR})
file(MAKE_DIRECTORY ${BUILD_SRC_DIR})
