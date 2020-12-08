###############################################################################
# Tests/Functional/PyExamples/CMakeLists.txt
#
# Runs check_functionality.py over example scripts found in PY_EXAMPLES_DIR
#
###############################################################################

set(output_dir ${TEST_OUTPUT_DIR_PY_EXAMPLES})
file(MAKE_DIRECTORY ${output_dir})

file(GLOB sim_examples ${PY_EXAMPLES_DIR}/sim*/*.py)
if (WIN32)
    # Convergence problem in Gauss-Kronrod integration
    list(REMOVE_ITEM sim_examples ${PY_EXAMPLES_DIR}/sim03_Structures/Interference2DParaCrystal.py)
endif()


file(GLOB fit_examples ${PY_EXAMPLES_DIR}/fit55_Specular/FitSpecularBasics.py)
set(examples ${sim_examples} ${fit_examples})

set(test_script ${TOOL_DIR}/code-tools/batch-plot.py)

foreach(example_path ${examples})
    get_filename_component(example_name ${example_path} NAME_WE)
    set(test_name PyExamples.${example_name})
    add_test(${test_name}
        env PYTHONPATH=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ${Python3_EXECUTABLE} ${test_script} ${example_path} ${output_dir})
endforeach()
