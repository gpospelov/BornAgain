############################################################################
# Tests/Functional/Core/CMakeLists.txt
############################################################################

set(CORE_STD_OUT_DIR     ${BUILD_REF_DIR}/StandardSuite)
set(CORE_STD_REF_DIR     ${REFERENCE_DIR}/StandardSuite)
set(CORE_SPECIAL_REF_DIR ${REFERENCE_DIR}/Special)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCORE_STD_OUT_DIR=\\\"${CORE_STD_OUT_DIR}\\\"")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCORE_STD_REF_DIR=\\\"${CORE_STD_REF_DIR}\\\"")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCORE_SPECIAL_REF_DIR=\\\"${CORE_SPECIAL_REF_DIR}\\\"")

# CoreStandardTest cases:
set(test_cases
    ApproximationDA
    ApproximationLMA
    ApproximationSSCA
    Basic2DParaCrystal
    BeamDivergence
    BoxCompositionRotateX
    BoxCompositionRotateY
    BoxCompositionRotateZ
    BoxCompositionRotateZandY
    BoxStackComposition
    CenteredSquareLattice
    CoreShellBoxRotateZandY
    CoreShellParticle
    CosineRipple
    CustomMorphology
    CylindersAndPrisms
    CylindersInSSCA
    CylindersWithSizeDistribution
    DetectorResolution
    FormFactors
    FormFactorsAbs
    HexParaCrystal
    LargeCylindersMonteCarlo
    Lattice1D
    MagneticParticleZeroField
    MesoCrystal
    MultiLayerWithRoughness
    MultipleLayout
    ParticleComposition
    RadialParaCrystal
    RectDetectorGeneric
    RectDetectorPerpToDirectBeam
    RectDetectorPerpToReflectedBeam
    RectDetectorPerpToReflectedBeamDpos
    RectDetectorPerpToSample
    RectParaCrystal
    RotatedPyramids
    RotatedSquareLattice
    SimulationWithMasks
    SquareLattice
    TransformBox
    TriangularRipple
    TwoTypesCylindersDistribution
    SphericalDetWithRoi
    RectDetWithRoi
    )

# Other tests:
set(other_tests
    BatchSimulation
    PolDWBAMagCylinders2
    )

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../TestMachinery
    ${CMAKE_SOURCE_DIR}/Core/Simulation
    )

# for some reason these flags aren't propagated here by SetUpWindows.cmake
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
endif()

# Setup CoreStandardTest:
add_executable(CoreStandardTest CoreStandardTest.cpp CoreTest.h CoreTest.cpp)
target_link_libraries(CoreStandardTest BornAgainCore BornAgainTestMachinery)
foreach(test_case ${test_cases})
    add_test(CoreStandardTest/${test_case}
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CoreStandardTest ${test_case})
endforeach()

# Setup other tests:
foreach(test ${other_tests})
    add_executable(${test} ${test}.cpp)
    target_link_libraries(${test} BornAgainFit BornAgainCore)
    add_test(${test} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test})
endforeach()
