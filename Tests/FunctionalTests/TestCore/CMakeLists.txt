############################################################################
# CMakeLists.txt file for building TestCore functional tests
############################################################################

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR}
)

# for some reason these flags aren't propagated here by SetUpWindows.cmake
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
endif()

set(list_of_tests
    "CoreSuite/FormFactors"
    "CoreSuite/FormFactorsAbs"
    "CoreSuite/CylindersAndPrisms"
    "CoreSuite/RadialParaCrystal"
    "CoreSuite/Basic2DParaCrystal"
    "CoreSuite/HexParaCrystal"
    "CoreSuite/Lattice1D"
    "CoreSuite/RectParaCrystal"
    "CoreSuite/CoreShellParticle"
    "CoreSuite/CoreShellBoxRotateZandY"
    "CoreSuite/MultiLayerWithRoughness"
    "CoreSuite/SquareLattice"
    "CoreSuite/CenteredSquareLattice"
    "CoreSuite/RotatedSquareLattice"
    "CoreSuite/RotatedPyramids"
    "CoreSuite/ParticleComposition"
    "CoreSuite/CylindersWithSizeDistribution"
    "CoreSuite/TwoTypesCylindersDistribution"
    "CoreSuite/BeamDivergence"
    "CoreSuite/DetectorResolution"
    "CoreSuite/MultipleLayout"
    "CoreSuite/ApproximationDA"
    "CoreSuite/ApproximationLMA"
    "CoreSuite/ApproximationSSCA"
    "CoreSuite/CylindersInSSCA"
    "CoreSuite/CosineRipple"
    "CoreSuite/TriangularRipple"
    "CoreSuite/MesoCrystal"
    "CoreSuite/CustomMorphology"
    "CoreSuite/MagneticParticleZeroField"
    "CoreSuite/TransformBox"
    "CoreSuite/BoxCompositionRotateX"
    "CoreSuite/BoxCompositionRotateY"
    "CoreSuite/BoxCompositionRotateZ"
    "CoreSuite/BoxCompositionRotateZandY"
    "CoreSuite/BoxStackComposition"
    "CoreSuite/SimulationWithMasks"
    "CoreSuite/RectDetectorGeneric"
    "CoreSuite/RectDetectorPerpToSample"
    "CoreSuite/RectDetectorPerpToDirectBeam"
    "CoreSuite/RectDetectorPerpToReflectedBeam"
    "CoreSuite/RectDetectorPerpToReflectedBeamDpos"
    "BatchSimulation"
    "PolDWBAMagCylinders2"
)


# Adding executables.
get_list_of_executables_from_list_of_tests("${list_of_tests}" ${list_of_executables})
foreach(test_exe_name ${list_of_executables})
   BORNAGAIN_EXECUTABLE(${test_exe_name} LOCATIONS ${test_exe_name} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY})
endforeach()

# Adding tests
foreach(_test ${list_of_tests})
    get_test_name_and_argument(${_test} ${test_exe_name} ${test_argument})
    BORNAGAIN_ADD_TEST(${_test} ${test_exe_name} TEST_ARGUMENTS ${test_argument})
endforeach()



