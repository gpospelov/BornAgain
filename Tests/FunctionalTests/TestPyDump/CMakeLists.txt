############################################################################
# FunctionalTests/TestPyDump/CMakeLists.txt
############################################################################

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

set(list_of_tests
    "PySuite/FormFactors"
    "PySuite/CylindersAndPrisms"
    "PySuite/RadialParaCrystal"
    "PySuite/Basic2DParaCrystal"
    "PySuite/HexParaCrystal"
    "PySuite/Lattice1D"
    "PySuite/RectParaCrystal"
    "PySuite/CoreShellParticle"
    "PySuite/CoreShellBoxRotateZandY"
    "PySuite/MultiLayerWithRoughness"
    "PySuite/SquareLattice"
    "PySuite/CenteredSquareLattice"
    "PySuite/RotatedSquareLattice"
    "PySuite/RotatedPyramids"
    "PySuite/ParticleComposition"
    "PySuite/CylindersWithSizeDistribution"
    "PySuite/TwoTypesCylindersDistribution"
    "PySuite/BeamDivergence"
    "PySuite/DetectorResolution"
    "PySuite/MultipleLayout"
    "PySuite/ApproximationDA"
    "PySuite/ApproximationLMA"
    "PySuite/ApproximationSSCA"
    "PySuite/CylindersInSSCA"
    "PySuite/CosineRipple"
    "PySuite/TriangularRipple"
    "PySuite/TransformBox"
    "PySuite/BoxCompositionRotateX"
    "PySuite/BoxCompositionRotateY"
    "PySuite/BoxCompositionRotateZ"
    "PySuite/BoxCompositionRotateZandY"
    "PySuite/BoxStackComposition"
    "PySuite/SimulationWithMasks"
    "PySuite/RectDetectorGeneric"
    "PySuite/RectDetectorPerpToSample"
    "PySuite/RectDetectorPerpToDirectBeam"
    "PySuite/RectDetectorPerpToReflectedBeam"
    "PySuite/RectDetectorPerpToReflectedBeamDpos"
    "PySuite/LargeCylindersMonteCarlo"
)

# Adding executables.
GET_LIST_OF_EXECUTABLES_FROM_LIST_OF_TESTS("${list_of_tests}" ${list_of_executables})
foreach(test_exe_name ${list_of_executables})
    BORNAGAIN_EXECUTABLE(${test_exe_name} LOCATIONS ${test_exe_name} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY})
endforeach()

# Adding tests
foreach(_test ${list_of_tests})
    GET_TEST_NAME_AND_ARGUMENT(${_test} ${test_exe_name} ${test_argument})
    BORNAGAIN_ADD_TEST(${_test} ${test_exe_name} TEST_ARGUMENTS ${test_argument})
endforeach()
