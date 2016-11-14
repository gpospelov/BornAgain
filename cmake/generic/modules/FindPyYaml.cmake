# Find the python-yaml module.
# This module defines PYYAML_FOUND.

execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "import yaml; print(yaml.__version__)"
  OUTPUT_VARIABLE pyyaml_version_number
  ERROR_VARIABLE  pyyaml_err_msg
  RESULT_VARIABLE PYYAML_NOT_FOUND
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_STRIP_TRAILING_WHITESPACE)

if (PYYAML_NOT_FOUND)
    message(FATAL_ERROR "python-yaml not found (ret='${PYYAML_NOT_FOUND}', "
        "out='${pyyaml_version_number}', "
        "err='${pyyaml_err_msg}')")
    set(PYYAML_FOUND FALSE)
else()
    message (STATUS "Found python module yaml, version ${pyyaml_version_number}.")
    set(PYYAML_FOUND TRUE)
endif()
