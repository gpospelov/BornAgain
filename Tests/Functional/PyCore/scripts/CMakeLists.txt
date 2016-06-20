############################################################################
# Tests/Functional/PyCore/scripts/CMakeLists.txt
############################################################################

file(GLOB sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.py")
if(NOT BORNAGAIN_TIFF_SUPPORT)
    list(REMOVE_ITEM sources "intensitydata_io_tiff.py")
endif()

foreach(_src ${sources})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${_src}
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${_src} @ONLY)
endforeach()

set(tests ${sources})
list(REMOVE_ITEM tests utils.py)

foreach(_test ${tests})
    add_test(${_test} ${PYTHON_EXECUTABLE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${_test})
endforeach()
