############################################################################
# Futests/TestPyDump/CMakeLists.txt
############################################################################

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
    CylindersAndPrisms
    CylindersInSSCA
    CylindersWithSizeDistribution
    DetectorResolution
    FormFactors
    HexParaCrystal
    LargeCylindersMonteCarlo
    Lattice1D
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

add_executable(PySuite PySuite.cpp)
target_link_libraries(PySuite BornAgainCore)
foreach(test_case ${test_cases})
    add_test(PySuite/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PySuite ${test_case})
endforeach()
