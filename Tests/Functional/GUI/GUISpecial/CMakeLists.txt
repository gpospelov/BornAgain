set(test TestGUISpecial)

set(test_cases
    BasicTranslation
    CompositionTranslation
    CoreShellTranslation
    HexParaTranslation
    Lattice1DTranslation
    Lattice2DTranslation
    MagneticSpheresTranslation
    MesoCrystalTranslation
    Para2DTranslation
    SizeDistributionTranslation
    SquareLatticeTranslation
    RadialParaTranslation
    HardDiskTranslation
    RotationTranslation
    RoughnessTranslation
    TwoLayerRoughnessTranslation
    SaveLoadProject
)

file(GLOB source_files "*.cpp")

find_package(Qt5Core REQUIRED)

add_executable(${test} ${source_files})
target_link_libraries(${test} BornAgainCore BornAgainGUI BornAgainTestMachinery)
target_link_libraries(${test} Qt5::Core)

foreach(test_case ${test_cases})
    add_test(${test}/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} ${test_case})
endforeach()
