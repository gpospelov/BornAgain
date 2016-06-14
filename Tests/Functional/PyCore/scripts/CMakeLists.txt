############################################################################
# Futests/TestPyCore/CMakeLists.txt
############################################################################

set(list_of_python_tests
    "customformfactor.py"
    "cylinders_ba_dwba_size.py"
    "detector_resolution.py"
    "intensitydata.py"
    "intensitydata_io.py"
    "layerwithroughness.py"
    "mesocrystal1.py"
    "montecarlo_integration.py"
    "polmagcylinders1.py"
    "polmagcylinders2.py"
    "ripple1.py"
    "ripple2_asym.py"
    "ripple2_sym.py"
    "transform_BoxComposition.py"
    "transform_CoreShellBox.py"
    "transform_box.py"
    "transform_cube.py"
)

if(BORNAGAIN_TIFF_SUPPORT)
    list(APPEND list_of_python_tests "intensitydata_io_tiff.py")
endif()

foreach(_test ${list_of_python_tests})
    add_test(${_test} ${PYTHON_EXECUTABLE} "${CMAKE_BINARY_DIR}/Tests/Functional/PyCore/scripts/${_test}")
endforeach()
