############################################################################
# Tests/Functional/PyCore/scripts/CMakeLists.txt
############################################################################

file(GLOB sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.py")
if(NOT BORNAGAIN_TIFF_SUPPORT)
    list(REMOVE_ITEM sources "intensitydata_io_tiff.py")
endif()

set(output_dir ${TEST_OUTPUT_DIR}/Functional/Python/PyCore)

foreach(_src ${sources})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${_src}
        ${output_dir}/${_src} @ONLY)
endforeach()

set(tests ${sources})
list(REMOVE_ITEM tests utils.py)

foreach(_test ${tests})
    add_test(PyCore/${_test} ${PYTHON_EXECUTABLE} ${output_dir}/${_test})
endforeach()
