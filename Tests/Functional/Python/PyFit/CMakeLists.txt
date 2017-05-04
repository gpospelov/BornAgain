############################################################################
# Tests/Functional/PyFit/CMakeLists.txt
############################################################################

file(GLOB sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.py")
foreach(_src ${sources})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${_src}
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${_src} @ONLY)
endforeach()

set(tests
    "testfit_UsingBuilder.py"
    "fitsuite_api.py"
#    "testfit_GSLLMA.py"
#    "testfit_GSLMultiMin.py"
#    "testfit_GSLSimAn.py"
#    "testfit_Minuit2.py"
)

foreach(_test ${tests})
    add_test(${_test} ${PYTHON_EXECUTABLE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${_test})
endforeach()
