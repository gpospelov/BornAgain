############################################################################
# FunctionalTests/TestCore/CMakeLists.txt
############################################################################

# CoreSuite cases:
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
    )

# Other tests:
set(other_executables
    BatchSimulation
    PolDWBAMagCylinders2
    )

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

# Setup CoreSuite:
BORNAGAIN_EXECUTABLE(CoreSuite LOCATION CoreSuite LIBRARIES BornAgainCore)
foreach(test_case ${test_cases})
    add_test(CoreSuite/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CoreSuite ${test_case})
endforeach()

# Setup other tests:
foreach(exe ${other_executables})
    BORNAGAIN_EXECUTABLE(${exe} LOCATION ${exe} LIBRARIES BornAgainCore)
    add_test(${exe} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${exe})
endforeach()

