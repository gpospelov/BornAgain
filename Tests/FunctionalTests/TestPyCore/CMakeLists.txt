############################################################################
# CMakeLists.txt file for running TestPyCore functional tests
############################################################################

set(CMAKE_CXX_FLAGS "-DSTANDALONE")

set(list_of_tests
    "intensitydata.py"
    "intensitydata_io.py"
    "isgisaxs01.py"
    "isgisaxs01_normalize.py"
    "isgisaxs02.py"
    "isgisaxs03.py"
    "isgisaxs04.py"
    "isgisaxs06.py"
    "isgisaxs07.py"
    "isgisaxs08.py"
    "isgisaxs09.py"
    "isgisaxs10.py"
    "isgisaxs11.py"
    "isgisaxs15.py"
    "mesocrystal1.py"
    "polmagcylinders1.py"
    "polmagcylinders2.py"
    "layerwithroughness.py"
    "ripple2_sym.py"
    "ripple2_asym.py"
    "ripple1.py"
    "customformfactor.py"
    "montecarlo_integration.py"
)

set(list_of_cpp_python_tests
    "PyScript_isgisaxs01"
    "PyScript_isgisaxs04_1DDL"
    "PyScript_isgisaxs04_2DDL"
    "PyScript_isgisaxs06a"
    "PyScript_isgisaxs07"
    "PyScript_isgisaxs11"
    "PyScript_multiplelayoutbuilder"
)

foreach(_test ${list_of_tests})
#    add_test(${_test} ${PYTHON_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/${_test}")
    add_test(${_test} ${PYTHON_EXECUTABLE} "${CMAKE_BINARY_DIR}/Tests/FunctionalTests/TestPyCore/${_test}")
endforeach()

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

foreach(_test ${list_of_cpp_python_tests})
   BORNAGAIN_EXECUTABLE(${_test} LOCATIONS ${_test} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY})
   BORNAGAIN_ADD_TEST(${_test} INPUT_DIR ${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain/)
endforeach()
