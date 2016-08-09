# Find the python-yaml module.
# This module defines PYYAML_FOUND.

exec_program ("${PYTHON_EXECUTABLE}"
  ARGS "-c 'import yaml; print(yaml.__version__)'"
  OUTPUT_VARIABLE pyyaml_version_number
  RETURN_VALUE PYYAML_NOT_FOUND)

if (PYYAML_NOT_FOUND)
    message(FATAL_ERROR "python-yaml not found (ret='${PYYAML_NOT_FOUND}', out='${pyyaml_version_number}')")
    set(PYYAML_FOUND FALSE)
else()
    message (STATUS "Found python module yaml, version ${pyyaml_version_number}.")
    set(PYYAML_FOUND TRUE)
endif()
