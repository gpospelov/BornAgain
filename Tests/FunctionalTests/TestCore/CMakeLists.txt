############################################################################
# CMakeLists.txt file for building TestCore functional tests
############################################################################

set(CMAKE_CXX_FLAGS "-DSTANDALONE")

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR}
)

# for some reason these flags doesn't propagated here by SetUpWindows.cmake
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
endif()

set(list_of_tests
#    "FormFactors"  # can be removed, FormFactors
#    "IsGISAXS01"       # can be removed, CylindersAndPrisms
#    "IsGISAXS041DDL"   # can be removed, RadialParaCrystal
#    "IsGISAXS042DDL"   # can be removed, TwoDimParaCrystal
#    "IsGISAXS11"        # can be removed, CoreShellParticle
#    "LayerRoughness" # can be removed, MultiLayerWithRoughness
#    "IsGISAXS06L1" # can be removed, SquareLattice
#    "IsGISAXS06L2"  # can be removed, CenteredSquareLattice
#    "IsGISAXS06L3"  # can be removed, RotatedSquareLattice
#    "IsGISAXS09b"  # can be removed, RotatedPyramids
#    "CylindersWithSizeDistribution" # can be removed, CylindersWithSizeDistribution
#    "CylindersInBA" # can be removed
#    "CylindersInDWBA" # can be removed
#    "IsGISAXS08a" # can be removed, RectParaCrystal
#    "IsGISAXS08b" # can be removed, duplicates IsGISAXS08a
#    "IsGISAXS02"  # can be removed, TwoTypesCylindersDistribution
#    "IsGISAXS10"  # can be removed, incliduign IsGISAXS10Builder, duplicates RadialParaCrystal
#    "IsGISAXS15" # can be removed, ParticlesInSSCA
#    "PolDWBAMagCylinders1" # can be removed
#    "Ripple2", # can be removed
#    "Ripple1", # can be removed
#    "MesoCrystal1", can be removed
#    "IsGISAXS06L4", can be removed, CustomRotatedLattice
    "IsGISAXS07"
)

foreach(_test ${list_of_tests})
   BORNAGAIN_EXECUTABLE(${_test} LOCATIONS ${_test} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY})
   BORNAGAIN_ADD_TEST(${_test} INPUT_DIR ${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain/)
endforeach()

# ------------------------------------------------------------------------------------------------
#
#
# ------------------------------------------------------------------------------------------------

set(list_of_tests
#    "CoreSuite/FormFactors"
#    "CoreSuite/CylindersAndPrisms"
#    "CoreSuite/RadialParaCrystal"
#    "CoreSuite/HexParaCrystal"
#    "CoreSuite/RectParaCrystal"
#    "CoreSuite/CoreShellParticle"
#    "CoreSuite/MultiLayerWithRoughness"
#    "CoreSuite/SquareLattice"
#    "CoreSuite/CenteredSquareLattice"
#    "CoreSuite/RotatedSquareLattice"
#    "CoreSuite/RotatedPyramids"
#    "CoreSuite/ParticleComposition"
#    "CoreSuite/CylindersWithSizeDistribution"
#    "CoreSuite/TwoTypesCylindersDistribution"
#    "CoreSuite/BeamDivergence"
#    "CoreSuite/DetectorResolution"
#    "CoreSuite/MultipleLayout"
#    "CoreSuite/ParticlesInSSCA"
#    "CoreSuite/CosineRipple"
#    "CoreSuite/TriangularRipple"
#    "CoreSuite/MesoCrystal"
    "CoreSuite/CustomMorphology"
#    "CoreSuite/MagneticParticleZeroField"
    "BatchSimulation"
    "PolDWBAMagCylinders2"
    "CustomRotatedLattice"
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



