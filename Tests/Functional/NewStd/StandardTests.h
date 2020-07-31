// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Std/StandardTestCatalog.cpp
//! @brief     Implements class StandardTestCatalog.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Std/StandardTestCatalog.h"
#include "Fit/Tools/StringUtils.h"
#include <iostream>

StandardTestCatalog::StandardTestCatalog()
{
TEST_F(STD_TEST_SERIES, FormFactors)
{
    EXPECT_TRUE(run("MiniGISAS", "ParticleInTheAirBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, FormFactorsWithAbsorption)
{
    EXPECT_TRUE(run("MiniGISAS_v2", "LayersWithAbsorptionBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, GISASAbsorptiveSLDLayers)
{
    EXPECT_TRUE(run("MiniGISAS", "LayersWithAbsorptionBySLDBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, CylindersAndPrisms)
{
    EXPECT_TRUE(run("MiniGISAS", "CylindersAndPrismsBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, RadialParaCrystal)
{
    EXPECT_TRUE(run("MiniGISAS", "RadialParaCrystalBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, HardDisk)
{
    EXPECT_TRUE(run("MiniGISAS", "HardDiskBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, Basic2DParaCrystal)
{
    EXPECT_TRUE(run("MiniGISAS", "Basic2DParaCrystalBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, HexParaCrystal)
{
    EXPECT_TRUE(run("MiniGISAS", "HexParaCrystalBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, Lattice1D)
{
    EXPECT_TRUE(run("MiniGISAS", "Lattice1DBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, RectParaCrystal)
{
    EXPECT_TRUE(run("MiniGISAS", "RectParaCrystalBuilder", 2e-10));
}
    // --- CoreShell ---
TEST_F(STD_TEST_SERIES, CoreShellParticle)
{
    EXPECT_TRUE(run("MiniGISAS", "CoreShellParticleBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, CoreShellBoxRotateZandY)
{
    EXPECT_TRUE(run("MiniGISAS", "CoreShellBoxRotateZandYBuilder", 2e-10));
}
    // ---
TEST_F(STD_TEST_SERIES, MultiLayerWithRoughness)
{
    EXPECT_TRUE(run("MiniGISAS", "MultiLayerWithRoughnessBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, SquareLattice)
{
    EXPECT_TRUE(run("MiniGISAS", "SquareLatticeBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, CenteredSquareLattice)
{
    EXPECT_TRUE(run("MiniGISAS", "CenteredSquareLatticeBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, RotatedSquareLattice)
{
    EXPECT_TRUE(run("MiniGISAS", "RotatedSquareLatticeBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, FiniteSquareLattice)
{
    EXPECT_TRUE(run("MiniGISAS", "FiniteSquareLatticeBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, SuperLattice)
{
    EXPECT_TRUE(run("MiniGISAS", "SuperLatticeBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, RotatedPyramids)
{
    EXPECT_TRUE(run("MiniGISAS", "RotatedPyramidsBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, ThickAbsorptiveSampleWithRoughness)
{
    EXPECT_TRUE(run("ExtraLongWavelengthGISAS", "ThickAbsorptiveSampleBuilder", 2e-10));
}
    // --- Compositions ---
TEST_F(STD_TEST_SERIES, ParticleComposition)
{
    EXPECT_TRUE(run("MiniGISAS", "ParticleCompositionBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, BoxCompositionRotateX)
{
    EXPECT_TRUE(run("MiniGISAS", "BoxCompositionRotateXBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, BoxCompositionRotateY)
{
    EXPECT_TRUE(run("MiniGISAS", "BoxCompositionRotateYBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, BoxCompositionRotateZ)
{
    EXPECT_TRUE(run("MiniGISAS", "BoxCompositionRotateZBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, BoxCompositionRotateZandY)
{
    EXPECT_TRUE(run("MiniGISAS", "BoxCompositionRotateZandYBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, BoxStackComposition)
{
    EXPECT_TRUE(run("MiniGISAS", "BoxStackCompositionBuilder", 2e-10));
}
    // ---
TEST_F(STD_TEST_SERIES, CylindersWithSizeDistribution)
{
    EXPECT_TRUE(run("MiniGISAS", "CylindersWithSizeDistributionBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, TwoTypesCylindersDistribution)
{
    EXPECT_TRUE(run("MiniGISAS", "TwoTypesCylindersDistributionBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, RotatedPyramidsDistribution)
{
    EXPECT_TRUE(run("MiniGISAS", "RotatedPyramidsDistributionBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, SpheresWithLimitsDistribution)
{
    EXPECT_TRUE(run("MiniGISAS", "SpheresWithLimitsDistributionBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, ConesWithLimitsDistribution)
{
    EXPECT_TRUE(run("MiniGISAS", "ConesWithLimitsDistributionBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, LinkedBoxDistribution)
{
    EXPECT_TRUE(run("MiniGISAS", "LinkedBoxDistributionBuilder", 2e-10));
}
    // ---
TEST_F(STD_TEST_SERIES, BeamDivergence)
{
    EXPECT_TRUE(run("MiniGISASBeamDivergence", "CylindersInBABuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, DetectorResolution)
{
    EXPECT_TRUE(run("MiniGISASDetectorResolution", "CylindersInBABuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, MultipleLayout)
{
    EXPECT_TRUE(run("MiniGISAS", "MultipleLayoutBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, ApproximationDA)
{
    EXPECT_TRUE(run("MiniGISAS", "SizeDistributionDAModelBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, ApproximationLMA)
{
    EXPECT_TRUE(run("MiniGISAS", "SizeDistributionLMAModelBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, ApproximationSSCA)
{
    EXPECT_TRUE(run("MiniGISAS", "SizeDistributionSSCAModelBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, CylindersInSSCA)
{
    EXPECT_TRUE(run("MiniGISAS", "CylindersInSSCABuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, CosineRipple)
{
    EXPECT_TRUE(run("MiniGISAS", "CosineRippleBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, TriangularRipple)
{
    EXPECT_TRUE(run("MiniGISAS", "TriangularRippleBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, AsymRipple)
{
    EXPECT_TRUE(run("MiniGISAS", "AsymRippleBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, MesoCrystal)
{
    EXPECT_TRUE(run("MiniGISAS", "MesoCrystalBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, CustomMorphology)
{
    EXPECT_TRUE(run("MiniGISAS", "CustomMorphologyBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, TransformBox)
{
    EXPECT_TRUE(run("MiniGISAS", "TransformBoxBuilder", 1e-10));
}
    // polarized GISAS
TEST_F(STD_TEST_SERIES, MagneticParticleZeroField)
{
    EXPECT_TRUE(run("MiniGISAS", "MagneticParticleZeroFieldBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, MagneticSubstrateZeroField)
{
    EXPECT_TRUE(run("MiniGISASPolarizationPP", "MagneticSubstrateZeroFieldBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, MagneticRotation)
{
    EXPECT_TRUE(run("MiniGISASPolarizationPM", "MagneticRotationBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, MagneticSpheres)
{
    EXPECT_TRUE(run("MiniGISASPolarizationPM", "MagneticSpheresBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, MagneticCylindersPP)
{
    EXPECT_TRUE(run("MiniGISASPolarizationPP", "MagneticCylindersBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, MagneticCylindersPM)
{
    EXPECT_TRUE(run("MiniGISASPolarizationPM", "MagneticCylindersBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, MagneticCylindersMP)
{
    EXPECT_TRUE(run("MiniGISASPolarizationMP", "MagneticCylindersBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, MagneticCylindersMM)
{
    EXPECT_TRUE(run("MiniGISASPolarizationMM", "MagneticCylindersBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, MagneticSpheresInMagLayerPP)
{
    EXPECT_TRUE(run("MiniGISASPolarizationPP", "MagneticLayerBuilder", 2e-10));
}

TEST_F(STD_TEST_SERIES, MagneticSpheresInMagLayerMP)
{
    EXPECT_TRUE(run("MiniGISASPolarizationMP", "MagneticLayerBuilder", 2e-10));
}
    // Masking
TEST_F(STD_TEST_SERIES, SimulationWithMasks)
{
    EXPECT_TRUE(run("GISASWithMasks", "CylindersAndPrismsBuilder", 1e-10));
}
    // Various rectangular detector alignment
TEST_F(STD_TEST_SERIES, RectDetectorGeneric)
{
    EXPECT_TRUE(run("RectDetectorGeneric", "CylindersInBABuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, RectDetectorPerpToSample)
{
    EXPECT_TRUE(run("RectDetectorPerpToSample", "CylindersInBABuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, RectDetectorPerpToDirectBeam)
{
    EXPECT_TRUE(run("RectDetectorPerpToDirectBeam", "CylindersInBABuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, RectDetectorPerpToReflectedBeam)
{
    EXPECT_TRUE(run("RectDetectorPerpToReflectedBeam", "CylindersInBABuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, RectDetectorPerpToReflectedBeamDpos)
{
    EXPECT_TRUE(run("RectDetectorPerpToReflectedBeamDpos", "CylindersInBABuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, LargeCylindersMonteCarlo)
{
    EXPECT_TRUE(run("MiniGISASMonteCarlo", "LargeCylindersInDWBABuilder", 5e-1));
}

TEST_F(STD_TEST_SERIES, SphericalDetWithRoi)
{
    EXPECT_TRUE(run("SphericalDetWithRoi", "CylindersAndPrismsBuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, RectDetWithRoi)
{
    EXPECT_TRUE(run("RectDetWithRoi", "CylindersAndPrismsBuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, BoxesWithSpecular)
{
    EXPECT_TRUE(run("MiniGISASSpecular", "BoxesSquareLatticeBuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, RotatedCylinder)
{
    EXPECT_TRUE(run("MiniGISAS", "RotatedCylindersBuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, SlicedComposition)
{
    EXPECT_TRUE(run("MiniGISAS", "SlicedCompositionBuilder", 1e-10));
}
    // Simulations with background
TEST_F(STD_TEST_SERIES, ConstantBackground)
{
    EXPECT_TRUE(run("ConstantBackground", "CylindersInBABuilder", 1e-10));
}
    // Specular simulations
TEST_F(STD_TEST_SERIES, HomogeneousTiNiSample)
{
    EXPECT_TRUE(run("BasicSpecular", "HomogeneousMultilayerBuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, HomogeneousTiNiSampleWithAbsorption)
{
    EXPECT_TRUE(run("BasicSpecular", "PlainMultiLayerBySLDBuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, RoughnessInSpecular)
{
    EXPECT_TRUE(run("BasicSpecular", "MultiLayerWithRoughnessBuilder", 2e-9));
}

TEST_F(STD_TEST_SERIES, NCRoughnessInSpecular)
{
    EXPECT_TRUE(run("BasicSpecular", "MultiLayerWithNCRoughnessBuilder", 2e-9));
}

TEST_F(STD_TEST_SERIES, GaussianBeamFootprint)
{
    EXPECT_TRUE(run("SpecularWithGaussianBeam", "HomogeneousMultilayerBuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, SquareBeamFootprint)
{
    EXPECT_TRUE(run("SpecularWithSquareBeam", "HomogeneousMultilayerBuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, SpecularDivergentBeam)
{
    EXPECT_TRUE(run("SpecularDivergentBeam", "HomogeneousMultilayerBuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, RelativeResolutionTOF)
{
    EXPECT_TRUE(run("TOFRWithRelativeResolution", "PlainMultiLayerBySLDBuilder", 1e-10));
}
TEST_F(STD_TEST_SERIES, SpecularWithSlicing)
{
    EXPECT_TRUE(run("BasicSpecular", "SlicedCylindersBuilder", 1e-10));
    EXPECT_TRUE(run("BasicSpecular", "SLDSlicedCylindersBuilder", 1e-10));
    EXPECT_TRUE(run("BasicSpecular", "AveragedSlicedCylindersBuilder", 1e-10));
    EXPECT_TRUE(run("BasicSpecularQ", "SLDSlicedCylindersBuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, InstrumentDefinitionComparison)
{
    EXPECT_TRUE(run("BasicSpecular", "PlainMultiLayerBySLDBuilder", 1e-10));
    EXPECT_TRUE(run("BasicSpecularQ", "PlainMultiLayerBySLDBuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, TOFResolutionComparison)
{
    EXPECT_TRUE(run("TOFRWithRelativeResolution", "PlainMultiLayerBySLDBuilder", 1e-10));
    EXPECT_TRUE(run("TOFRWithPointwiseResolution", "PlainMultiLayerBySLDBuilder", 1e-10));
}
    // polarized specular
TEST_F(STD_TEST_SERIES, BasicSpecularPP)
{
    EXPECT_TRUE(run("BasicSpecularPP", "SimpleMagneticLayerBuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, BasicSpecularMM)
{
    EXPECT_TRUE(run("BasicSpecularMM", "SimpleMagneticLayerBuilder", 1e-10));
}
TEST_F(STD_TEST_SERIES, PolarizedQAngleReflectivityPP)
{
    EXPECT_TRUE(run("BasicSpecularPP", "SimpleMagneticLayerBuilder", 1e-10));
    EXPECT_TRUE(run("BasicQSpecularPP", "SimpleMagneticLayerBuilder", 1e-10));
}

TEST_F(STD_TEST_SERIES, PolarizedQAngleReflectivityMM)
{
    EXPECT_TRUE(run("BasicSpecularMM", "SimpleMagneticLayerBuilder", 1e-10));
    EXPECT_TRUE(run("BasicQSpecularMM", "SimpleMagneticLayerBuilder", 1e-10));
}
    // off-specular simulation
TEST_F(STD_TEST_SERIES, OffSpecularResonator)
{
    EXPECT_TRUE(run("OffSpecMini", "ResonatorBuilder", 1e-10));
}
    // depth probe simulation
TEST_F(STD_TEST_SERIES, DepthProbeTest)
{
    EXPECT_TRUE(run("BasicDepthProbe", "HomogeneousMultilayerBuilder", 1e-10));
}
}

//! Adds test description to the catalog.

void StandardTestCatalog::add(const std::string& test_name, const std::string& test_description,
                              const std::string& simulation_name,
                              const std::string& sample_builder_name, double threshold)
{
    if (contains(test_name))
        throw std::runtime_error("StandardTestCatalog::add() -> Error. "
                                 "Existing item '"
                                 + test_name + "'");

    m_catalog[test_name] = StandardTestInfo(test_name, test_description, simulation_name,
                                            sample_builder_name, threshold);
}

void StandardTestCatalog::add(const std::string& test_name, const std::string& test_description,
                              std::initializer_list<std::string> simulation_names,
                              std::initializer_list<std::string> sample_builder_names,
                              double threshold)
{
    if (contains(test_name))
        throw std::runtime_error("StandardTestCatalog::add() -> Error. "
                                 "Existing item '"
                                 + test_name + "'");

    m_catalog[test_name] =
        StandardTestInfo(test_name, test_description, std::move(simulation_names),
                         std::move(sample_builder_names), threshold);
}

//! Returns test info for given test name.

StandardTestInfo StandardTestCatalog::testInfo(const std::string& test_name)
{
    if (!contains(test_name))
        throw std::runtime_error("StandardTestCatalog::testInfo() -> Error. No info for "
                                 "given name '"
                                 + test_name + "'");

    return m_catalog[test_name];
}

//! Returns true if catalog contains info for test with given name.

bool StandardTestCatalog::contains(const std::string& test_name)
{
    return m_catalog.find(test_name) != m_catalog.end();
}
