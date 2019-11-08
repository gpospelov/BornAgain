############################################################################
# Tests/Functional/Core/CMakeLists.txt
############################################################################

set(test TestCoreStandard)

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
    BoxesWithSpecular
    BoxStackComposition
    CenteredSquareLattice
    ConstantBackground
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
    GISASAbsorptiveSLDLayers
    HexParaCrystal
    LargeCylindersMonteCarlo
    Lattice1D
    MagneticParticleZeroField
    MagneticSpheres
    MagneticSubstrateZeroField
    MagneticRotation
    MagneticCylindersPP
    MagneticCylindersPM
    MagneticCylindersMP
    MagneticCylindersMM
    MesoCrystal
    MultiLayerWithRoughness
    MultipleLayout
    ParticleComposition
    RadialParaCrystal
    HardDisk
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
    SuperLattice
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
    HomogeneousTiNiSample
    HomogeneousTiNiSampleWithAbsorption
    RoughnessInSpecular
    GaussianBeamFootprint
    SquareBeamFootprint
    SpecularDivergentBeam
    RelativeResolutionTOF
    OffSpecularResonator
    DepthProbeTest
    ThickAbsorptiveSampleWithRoughness
    )

add_executable(${test} main.cpp CoreStandardTest.h CoreStandardTest.cpp)
target_link_libraries(${test} BornAgainCore BornAgainTestMachinery)
foreach(test_case ${test_cases})
    add_test(${test}/${test_case}
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} ${test_case})
endforeach()
