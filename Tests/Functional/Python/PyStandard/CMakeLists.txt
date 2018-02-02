############################################################################
# Tests/Functional/PyCore/suite/CMakeLists.txt
############################################################################

set(output_dir ${TEST_OUTPUT_DIR}/Functional/Python/PyStandard)
file(MAKE_DIRECTORY ${output_dir})

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
    BoxesWithSpecular
    BoxStackComposition
    CenteredSquareLattice
    ConstantBackground
    CoreShellBoxRotateZandY
    CoreShellParticle
    CosineRipple
    CylindersAndPrisms
    CylindersInSSCA
    CylindersWithSizeDistribution
    DetectorResolution
    FormFactors
    HexParaCrystal
    LargeCylindersMonteCarlo
    Lattice1D
    MagneticSpheres
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
    RotatedCylinder
    RotatedPyramids
    RotatedSquareLattice
    SimulationWithMasks
    SquareLattice
    TransformBox
    TriangularRipple
    AsymRipple
    TwoTypesCylindersDistribution
    SphericalDetWithRoi
    RectDetWithRoi
    SlicedComposition
    RotatedPyramidsDistribution
    SpheresWithLimitsDistribution
    ConesWithLimitsDistribution
)

include_as_system_directory("${EIGEN3_INCLUDE_DIR}")
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/Core/Simulation
    ${CMAKE_CURRENT_SOURCE_DIR}/../../TestMachinery
)

add_executable(PyStandardTest main.cpp PyStandardTest.h PyStandardTest.cpp)
target_link_libraries(PyStandardTest BornAgainCore BornAgainTestMachinery)
foreach(test_case ${test_cases})
    add_test(PyStandardTest/${test_case}
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PyStandardTest ${test_case})
endforeach()
