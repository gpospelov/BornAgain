set(test GUISpecial)

set(test_cases
    BasicTranslation
    CompositionTranslation
    CoreShellTranslation
    HexParaTranslation
    Lattice1DTranslation
    Lattice2DTranslation
    MesoCrystalTranslation
    Para2DTranslation
    SizeDistributionTranslation
    SquareLatticeTranslation
    RadialParaTranslation
    RotationTranslation
    RoughnessTranslation
    TwoLayerRoughnessTranslation
#    GUIPerformanceTest  # too heavy, call manually when necessary
)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

add_executable(${test} ${include_files} ${source_files})
target_link_libraries(${test} BornAgainCore BornAgainGUI BornAgainTestMachinery)
qt5_use_modules(${test} Widgets Core Gui Designer PrintSupport Network)

foreach(test_case ${test_cases})
    add_test(${test}/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} ${test_case})
endforeach()

