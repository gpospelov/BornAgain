###############################################################################
# Tests/Functional/PyExamples/CMakeLists.txt
#
# > Test functionality of all examples found in PY_EXAMPLES_DIR = <BornAgain>/Examples/python
# > Validates selected examples against reference files
#
###############################################################################

add_custom_target(TempQtCreatorTarget SOURCES check_functionality.py)

set(examples
    simulation/ex01_BasicParticles/CylindersAndPrisms
    )


set(test_script ${CMAKE_SOURCE_DIR}/Tests/Functional/PyExamples/check_functionality.py)

foreach(example ${examples})
    set(script_path ${PY_EXAMPLES_DIR}/${example}.py)

    get_filename_component(script_name ${script_path} NAME_WE)
    set(test_name PyExamples/${script_name})

    add_test(${test_name} ${PYTHON_EXECUTABLE} ${test_script} ${script_path})
    set_tests_properties(${test_name} PROPERTIES LABELS "Examples")

    message(INFO "XXX ${PYTHON_EXECUTABLE} ${test_script} ${script_path}")
endforeach()
