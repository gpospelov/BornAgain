############################################################################
# CMakeLists.txt file for running TestPyCore functional tests
############################################################################

set(CMAKE_CXX_FLAGS "-DSTANDALONE")

# for some reason these flags doesn't propagated here by SetUpWindows.cmake
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
endif()

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR}
)

#set(list_of_tests
#    "intensitydata.py"
#    "intensitydata_io.py"
#    "isgisaxs01.py"
#    "isgisaxs01_normalize.py"
#    "isgisaxs02.py"
#    "cylinders_ba_dwba_size.py"
#    "isgisaxs04.py"
#    "isgisaxs06.py"
#    "isgisaxs07.py"
#    "isgisaxs08.py"
#    "isgisaxs09.py"
#    "isgisaxs10.py"
#    "isgisaxs11.py"
#    "isgisaxs15.py"
#    "mesocrystal1.py"
#    "polmagcylinders1.py"
#    "polmagcylinders2.py"
#    "layerwithroughness.py"
#    "ripple2_sym.py"
#    "ripple2_asym.py"
#    "ripple1.py"
#    "customformfactor.py"
#    "montecarlo_integration.py"
#    "beam_divergence.py"
#    "detector_resolution.py"
#)

#foreach(_test ${list_of_tests})
##    add_test(${_test} ${PYTHON_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/${_test}")
#    add_test(${_test} ${PYTHON_EXECUTABLE} "${CMAKE_BINARY_DIR}/Tests/FunctionalTests/TestPyCore/${_test}")
#endforeach()


set(list_of_cpp_python_tests
    "PyScript_isgisaxs04_1DDL"
#    "PyScript_isgisaxs04_2DDL"
#    "PyScript_isgisaxs06a"
#    "PyScript_isgisaxs06b"
#    "PyScript_isgisaxs07"
#    "PyScript_isgisaxs11"
#    "PyScript_multiplelayoutbuilder"
#    "PyScript_ParticleDistribution"
#    "PyScript_ParticleComposition"
)

foreach(_test ${list_of_cpp_python_tests})
   BORNAGAIN_EXECUTABLE(${_test} LOCATIONS ${_test} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY})
   BORNAGAIN_ADD_TEST(${_test} INPUT_DIR ${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain/)
endforeach()

# ------------------------------------------------------------------------------------------------
#
#
# ------------------------------------------------------------------------------------------------

set(list_of_tests
    "PySuite/CylindersAndPrisms"
    "PySuite/FormFactors"
)


# ------------------------------------------------------------------------
# Adding executables.
# The list of unique executable names is extracted from the list of tests
# Name of test 'CoreSuite/IsGISAXS01' will be parsed into
# 'CoreSuite' the name of executable
# 'IsGISAXS01' the command line argument
# ------------------------------------------------------------------------
foreach(_test ${list_of_tests})
    string(REPLACE "/" ";"  test_info ${_test})
    list(GET test_info 0 test_exe_name)
    list(APPEND list_of_executables ${test_exe_name})
endforeach()
list(REMOVE_DUPLICATES list_of_executables)
message(INFO "${list_of_executables}")

foreach(test_exe_name ${list_of_executables})
   BORNAGAIN_EXECUTABLE(${test_exe_name} LOCATIONS ${test_exe_name} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY})
endforeach()

# ------------------------------------------------------------------------
# Adding tests
# ------------------------------------------------------------------------
foreach(_test ${list_of_tests})
    string(REPLACE "/" ";"  test_info ${_test})
    list(LENGTH test_info len)
    list(GET test_info 0 test_exe_name)
    if(len EQUAL 2)
        list(GET test_info 1 test_argument)
    endif()

    message(INFO " _test ${_test} test_exe_name ${test_exe_name} test_argument ${test_argument}")
    set(test_input_args "${test_argument}")
    #set(test_input_args "${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain/")

    BORNAGAIN_ADD_TEST2(${_test} ${test_exe_name} TEST_ARGUMENTS ${test_argument})
endforeach()

