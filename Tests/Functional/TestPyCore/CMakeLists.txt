############################################################################
# Futests/TestPyCore/CMakeLists.txt
############################################################################

set(list_of_python_tests
    "intensitydata.py"
    "intensitydata_io.py"
    "cylinders_ba_dwba_size.py"
    "mesocrystal1.py"
    "polmagcylinders1.py"
    "polmagcylinders2.py"
    "layerwithroughness.py"
    "ripple2_sym.py"
    "ripple2_asym.py"
    "ripple1.py"
    "customformfactor.py"
    "montecarlo_integration.py"
#    "beam_divergence.py"
    "detector_resolution.py"
    "transform_cube.py"
    "transform_box.py"
    "transform_CoreShellBox.py"
    "transform_BoxComposition.py"
)

if(BORNAGAIN_TIFF_SUPPORT)
    list(APPEND list_of_python_tests "intensitydata_io_tiff.py")
endif()

foreach(_test ${list_of_python_tests})
    add_test(${_test} ${PYTHON_EXECUTABLE} "${CMAKE_BINARY_DIR}/Tests/Functional/TestPyCore/${_test}")
endforeach()
