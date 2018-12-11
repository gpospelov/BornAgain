############################################################################
# Tests/Functional/PyCore/suite/CMakeLists.txt
############################################################################

set(test TestPyStandard)

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
    GISASAbsorptiveSLDLayers
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
    FiniteSquareLattice
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
    LinkedBoxDistribution
    OffSpecularResonator
    GaussianBeamFootprint
    SpecularDivergentBeam
    HomogeneousTiNiSampleWithAbsorption
)

add_executable(${test} main.cpp PyStandardTest.h PyStandardTest.cpp)
target_link_libraries(${test} BornAgainCore BornAgainTestMachinery)

foreach(test_case ${test_cases})
    add_test(${test}/${test_case}
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} ${test_case})
endforeach()
