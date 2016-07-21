############################################################################
# Tests/Functional/GUI/CMakeLists.txt
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
#    CylindersInSSCA # no yet implemented (linked parameter)
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


if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()

find_package(Qt5Widgets REQUIRED)

# for some reason these flags doesn't propagated here by SetUpWindows.cmake
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
endif()

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${BornAgainGUI_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../Utils
)

add_executable(GUITestSuite GUITestSuite.cpp GUITest.cpp GUITest.h )
target_link_libraries(GUITestSuite BornAgainCore BornAgainGUI BornAgainTestMachinery)
qt5_use_modules(GUITestSuite Widgets Core Gui Designer PrintSupport Network)
foreach(test_case ${test_cases})
    add_test(GUITestSuite/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GUITestSuite ${test_case})
endforeach()
