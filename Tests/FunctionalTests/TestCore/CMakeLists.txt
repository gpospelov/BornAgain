############################################################################
# FunctionalTests/TestCore/CMakeLists.txt
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

# The entries in the following 'list_of_tests' are NOT path names.
# They have a special semantics 'executable[/argument]' understood by the macros
# GET_LIST_OF_EXECUTABLES_FROM_LIST_OF_TESTS and GET_TEST_NAME_AND_ARGUMENT.
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
    "CoreSuite/LargeCylindersMonteCarlo"
    "BatchSimulation"
    "PolDWBAMagCylinders2"
)


# Adding executables (using macros defined in FuTestMacros.cmake):
GET_LIST_OF_EXECUTABLES_FROM_LIST_OF_TESTS("${list_of_tests}" ${list_of_executables})
message(STATUS "ANAFU lot[${list_of_tests}]")
message(STATUS "ANAFU loe[${list_of_executables}]")

foreach(test_exe_name ${list_of_executables})
    message(STATUS "ANAFU loop ten[${test_exe_name}]")
    BORNAGAIN_EXECUTABLE(${test_exe_name} LOCATION ${test_exe_name}
        LIBRARIES ${BornAgainCore_LIBRARY})
endforeach()

# Adding tests (using macros defined in FuTestMacros.cmake):
foreach(_test ${list_of_tests})
    GET_TEST_NAME_AND_ARGUMENT(${_test} ${test_exe_name} ${test_argument})
    # message(STATUS "ANAFU loop tes[${_test}] [${test_exe_name}] [${test_argument}]")
    BORNAGAIN_ADD_TEST(${_test} ${test_exe_name} COMPONENT ${test_argument})
endforeach()
