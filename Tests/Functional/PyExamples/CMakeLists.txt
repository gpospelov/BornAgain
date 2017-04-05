###############################################################################
# Tests/Functional/PyExamples/CMakeLists.txt
#
# > Test functionality of all examples found in PY_EXAMPLES_DIR = <BornAgain>/Examples/python
# > Validates selected examples against reference files
#
###############################################################################

# add_custom_target(TempQtCreatorTarget SOURCES check_functionality.py)

file(GLOB examples "${PY_EXAMPLES_DIR}/simulation/ex*/*.py")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/check_functionality.py ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/check_functionality.py @ONLY)

set(test_script ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/check_functionality.py)
foreach(example ${examples})
    set(script_path ${example})

    get_filename_component(script_name ${script_path} NAME_WE)
    set(test_name PyExamples/${script_name})

    add_test(${test_name} ${PYTHON_EXECUTABLE} ${test_script} ${script_path})
    set_tests_properties(${test_name} PROPERTIES LABELS "Examples")
endforeach()
