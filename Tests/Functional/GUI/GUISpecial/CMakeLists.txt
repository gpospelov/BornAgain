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
# Performance tests are not part of the functional test suite.
# They need to be run manually when needed.
#    CsvImportAssistantPerformanceTest
#    GUIPerformanceTest
)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

find_package(Qt5Core REQUIRED)

add_executable(${test} ${include_files} ${source_files})
target_link_libraries(${test} BornAgainCore BornAgainGUI BornAgainTestMachinery)
target_link_libraries(${test} Qt5::Core)

foreach(test_case ${test_cases})
    add_test(${test}/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} ${test_case})
endforeach()
