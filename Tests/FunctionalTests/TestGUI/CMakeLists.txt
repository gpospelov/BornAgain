# CMakeLists.txt file for building and running TestGUI functional tests
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
)

set(list_of_tests
    "GUISuite/FormFactors"
    "GUISuite/CylindersAndPrisms"
    "GUISuite/RadialParaCrystal"
    "GUISuite/Basic2DParaCrystal"
    "GUISuite/HexParaCrystal"
    "GUISuite/Lattice1D"
    "GUISuite/RectParaCrystal"
    "GUISuite/CoreShellParticle"
    "GUISuite/CoreShellBoxRotateZandY"
    "GUISuite/MultiLayerWithRoughness"
    "GUISuite/SquareLattice"
    "GUISuite/CenteredSquareLattice"
    "GUISuite/RotatedSquareLattice"
    "GUISuite/RotatedPyramids"
    "GUISuite/ParticleComposition"
    "GUISuite/CylindersWithSizeDistribution"
    "GUISuite/TwoTypesCylindersDistribution"
    "GUISuite/BeamDivergence"
    "GUISuite/DetectorResolution"
    "GUISuite/MultipleLayout"
    "GUISuite/ApproximationDA"
    "GUISuite/ApproximationLMA"
    "GUISuite/ApproximationSSCA"
#    "GUISuite/CylindersInSSCA" # no yet implemented (linked parameter)
    "GUISuite/CosineRipple"
    "GUISuite/TriangularRipple"
    "GUISuite/TransformBox"
    "GUISuite/BoxCompositionRotateX"
    "GUISuite/BoxCompositionRotateY"
    "GUISuite/BoxCompositionRotateZ"
    "GUISuite/BoxCompositionRotateZandY"
    "GUISuite/BoxStackComposition"
    "GUISuite/SimulationWithMasks"
    "GUISuite/RectDetectorGeneric"
    "GUISuite/RectDetectorPerpToSample"
    "GUISuite/RectDetectorPerpToDirectBeam"
    "GUISuite/RectDetectorPerpToReflectedBeam"
    "GUISuite/RectDetectorPerpToReflectedBeamDpos"
)

# Adding executables.
get_list_of_executables_from_list_of_tests("${list_of_tests}" ${list_of_executables})
foreach(test_exe_name ${list_of_executables})
   BORNAGAIN_EXECUTABLE(${test_exe_name} LOCATIONS ${test_exe_name} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY} ${BornAgainGUI_LIBRARY})
   qt5_use_modules(${test_exe_name} Widgets Core Gui Designer PrintSupport Network)
endforeach()

# Adding tests
foreach(_test ${list_of_tests})
    get_test_name_and_argument(${_test} ${test_exe_name} ${test_argument})
    BORNAGAIN_ADD_TEST(${_test} ${test_exe_name} TEST_ARGUMENTS ${test_argument})
endforeach()
