// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/NewStd/StandardTests.h
//! @brief     Implements class StandardTestCatalog.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/GTestWrapper/google_test.h"

class Minimize : public ::testing::Test
{
};


TEST_F(Std, FormFactors)
{
    EXPECT_TRUE(run("MiniGISAS", "ParticleInTheAirBuilder", 2e-10));
}

TEST_F(Std, FormFactorsWithAbsorption)
{
    EXPECT_TRUE(run("MiniGISAS_v2", "LayersWithAbsorptionBuilder", 2e-10));
}

TEST_F(Std, GISASAbsorptiveSLDLayers)
{
    EXPECT_TRUE(run("MiniGISAS", "LayersWithAbsorptionBySLDBuilder", 2e-10));
}

TEST_F(Std, CylindersAndPrisms)
{
    EXPECT_TRUE(run("MiniGISAS", "CylindersAndPrismsBuilder", 2e-10));
}

TEST_F(Std, RadialParaCrystal)
{
    EXPECT_TRUE(run("MiniGISAS", "RadialParaCrystalBuilder", 2e-10));
}

TEST_F(Std, HardDisk)
{
    EXPECT_TRUE(run("MiniGISAS", "HardDiskBuilder", 2e-10));
}

TEST_F(Std, Basic2DParaCrystal)
{
    EXPECT_TRUE(run("MiniGISAS", "Basic2DParaCrystalBuilder", 2e-10));
}

TEST_F(Std, HexParaCrystal)
{
    EXPECT_TRUE(run("MiniGISAS", "HexParaCrystalBuilder", 2e-10));
}

TEST_F(Std, Lattice1D)
{
    EXPECT_TRUE(run("MiniGISAS", "Lattice1DBuilder", 2e-10));
}

TEST_F(Std, RectParaCrystal)
{
    EXPECT_TRUE(run("MiniGISAS", "RectParaCrystalBuilder", 2e-10));
}
    // --- CoreShell ---
TEST_F(Std, CoreShellParticle)
{
    EXPECT_TRUE(run("MiniGISAS", "CoreShellParticleBuilder", 2e-10));
}

TEST_F(Std, CoreShellBoxRotateZandY)
{
    EXPECT_TRUE(run("MiniGISAS", "CoreShellBoxRotateZandYBuilder", 2e-10));
}
    // ---
TEST_F(Std, MultiLayerWithRoughness)
{
    EXPECT_TRUE(run("MiniGISAS", "MultiLayerWithRoughnessBuilder", 2e-10));
}

TEST_F(Std, SquareLattice)
{
    EXPECT_TRUE(run("MiniGISAS", "SquareLatticeBuilder", 2e-10));
}

TEST_F(Std, CenteredSquareLattice)
{
    EXPECT_TRUE(run("MiniGISAS", "CenteredSquareLatticeBuilder", 2e-10));
}

TEST_F(Std, RotatedSquareLattice)
{
    EXPECT_TRUE(run("MiniGISAS", "RotatedSquareLatticeBuilder", 2e-10));
}

TEST_F(Std, FiniteSquareLattice)
{
    EXPECT_TRUE(run("MiniGISAS", "FiniteSquareLatticeBuilder", 2e-10));
}

TEST_F(Std, SuperLattice)
{
    EXPECT_TRUE(run("MiniGISAS", "SuperLatticeBuilder", 2e-10));
}

TEST_F(Std, RotatedPyramids)
{
    EXPECT_TRUE(run("MiniGISAS", "RotatedPyramidsBuilder", 2e-10));
}

TEST_F(Std, ThickAbsorptiveSampleWithRoughness)
{
    EXPECT_TRUE(run("ExtraLongWavelengthGISAS", "ThickAbsorptiveSampleBuilder", 2e-10));
}
    // --- Compositions ---
TEST_F(Std, ParticleComposition)
{
    EXPECT_TRUE(run("MiniGISAS", "ParticleCompositionBuilder", 2e-10));
}

TEST_F(Std, BoxCompositionRotateX)
{
    EXPECT_TRUE(run("MiniGISAS", "BoxCompositionRotateXBuilder", 2e-10));
}

TEST_F(Std, BoxCompositionRotateY)
{
    EXPECT_TRUE(run("MiniGISAS", "BoxCompositionRotateYBuilder", 2e-10));
}

TEST_F(Std, BoxCompositionRotateZ)
{
    EXPECT_TRUE(run("MiniGISAS", "BoxCompositionRotateZBuilder", 2e-10));
}

TEST_F(Std, BoxCompositionRotateZandY)
{
    EXPECT_TRUE(run("MiniGISAS", "BoxCompositionRotateZandYBuilder", 2e-10));
}

TEST_F(Std, BoxStackComposition)
{
    EXPECT_TRUE(run("MiniGISAS", "BoxStackCompositionBuilder", 2e-10));
}
    // ---
TEST_F(Std, CylindersWithSizeDistribution)
{
    EXPECT_TRUE(run("MiniGISAS", "CylindersWithSizeDistributionBuilder", 2e-10));
}

TEST_F(Std, TwoTypesCylindersDistribution)
{
    EXPECT_TRUE(run("MiniGISAS", "TwoTypesCylindersDistributionBuilder", 2e-10));
}

TEST_F(Std, RotatedPyramidsDistribution)
{
    EXPECT_TRUE(run("MiniGISAS", "RotatedPyramidsDistributionBuilder", 2e-10));
}

TEST_F(Std, SpheresWithLimitsDistribution)
{
    EXPECT_TRUE(run("MiniGISAS", "SpheresWithLimitsDistributionBuilder", 2e-10));
}

TEST_F(Std, ConesWithLimitsDistribution)
{
    EXPECT_TRUE(run("MiniGISAS", "ConesWithLimitsDistributionBuilder", 2e-10));
}

TEST_F(Std, LinkedBoxDistribution)
{
    EXPECT_TRUE(run("MiniGISAS", "LinkedBoxDistributionBuilder", 2e-10));
}
    // ---
TEST_F(Std, BeamDivergence)
{
    EXPECT_TRUE(run("MiniGISASBeamDivergence", "CylindersInBABuilder", 2e-10));
}

TEST_F(Std, DetectorResolution)
{
    EXPECT_TRUE(run("MiniGISASDetectorResolution", "CylindersInBABuilder", 2e-10));
}

TEST_F(Std, MultipleLayout)
{
    EXPECT_TRUE(run("MiniGISAS", "MultipleLayoutBuilder", 2e-10));
}

TEST_F(Std, ApproximationDA)
{
    EXPECT_TRUE(run("MiniGISAS", "SizeDistributionDAModelBuilder", 2e-10));
}

TEST_F(Std, ApproximationLMA)
{
    EXPECT_TRUE(run("MiniGISAS", "SizeDistributionLMAModelBuilder", 2e-10));
}

TEST_F(Std, ApproximationSSCA)
{
    EXPECT_TRUE(run("MiniGISAS", "SizeDistributionSSCAModelBuilder", 2e-10));
}

TEST_F(Std, CylindersInSSCA)
{
    EXPECT_TRUE(run("MiniGISAS", "CylindersInSSCABuilder", 2e-10));
}

TEST_F(Std, CosineRipple)
{
    EXPECT_TRUE(run("MiniGISAS", "CosineRippleBuilder", 2e-10));
}

TEST_F(Std, TriangularRipple)
{
    EXPECT_TRUE(run("MiniGISAS", "TriangularRippleBuilder", 2e-10));
}

TEST_F(Std, AsymRipple)
{
    EXPECT_TRUE(run("MiniGISAS", "AsymRippleBuilder", 2e-10));
}

TEST_F(Std, MesoCrystal)
{
    EXPECT_TRUE(run("MiniGISAS", "MesoCrystalBuilder", 2e-10));
}

TEST_F(Std, CustomMorphology)
{
    EXPECT_TRUE(run("MiniGISAS", "CustomMorphologyBuilder", 2e-10));
}

TEST_F(Std, TransformBox)
{
    EXPECT_TRUE(run("MiniGISAS", "TransformBoxBuilder", 1e-10));
}
    // polarized GISAS
TEST_F(Std, MagneticParticleZeroField)
{
    EXPECT_TRUE(run("MiniGISAS", "MagneticParticleZeroFieldBuilder", 2e-10));
}

TEST_F(Std, MagneticSubstrateZeroField)
{
    EXPECT_TRUE(run("MiniGISASPolarizationPP", "MagneticSubstrateZeroFieldBuilder", 2e-10));
}

TEST_F(Std, MagneticRotation)
{
    EXPECT_TRUE(run("MiniGISASPolarizationPM", "MagneticRotationBuilder", 2e-10));
}

TEST_F(Std, MagneticSpheres)
{
    EXPECT_TRUE(run("MiniGISASPolarizationPM", "MagneticSpheresBuilder", 2e-10));
}

TEST_F(Std, MagneticCylindersPP)
{
    EXPECT_TRUE(run("MiniGISASPolarizationPP", "MagneticCylindersBuilder", 2e-10));
}

TEST_F(Std, MagneticCylindersPM)
{
    EXPECT_TRUE(run("MiniGISASPolarizationPM", "MagneticCylindersBuilder", 2e-10));
}

TEST_F(Std, MagneticCylindersMP)
{
    EXPECT_TRUE(run("MiniGISASPolarizationMP", "MagneticCylindersBuilder", 2e-10));
}

TEST_F(Std, MagneticCylindersMM)
{
    EXPECT_TRUE(run("MiniGISASPolarizationMM", "MagneticCylindersBuilder", 2e-10));
}

TEST_F(Std, MagneticSpheresInMagLayerPP)
{
    EXPECT_TRUE(run("MiniGISASPolarizationPP", "MagneticLayerBuilder", 2e-10));
}

TEST_F(Std, MagneticSpheresInMagLayerMP)
{
    EXPECT_TRUE(run("MiniGISASPolarizationMP", "MagneticLayerBuilder", 2e-10));
}
    // Masking
TEST_F(Std, SimulationWithMasks)
{
    EXPECT_TRUE(run("GISASWithMasks", "CylindersAndPrismsBuilder", 1e-10));
}
    // Various rectangular detector alignment
TEST_F(Std, RectDetectorGeneric)
{
    EXPECT_TRUE(run("RectDetectorGeneric", "CylindersInBABuilder", 1e-10));
}

TEST_F(Std, RectDetectorPerpToSample)
{
    EXPECT_TRUE(run("RectDetectorPerpToSample", "CylindersInBABuilder", 1e-10));
}

TEST_F(Std, RectDetectorPerpToDirectBeam)
{
    EXPECT_TRUE(run("RectDetectorPerpToDirectBeam", "CylindersInBABuilder", 1e-10));
}

TEST_F(Std, RectDetectorPerpToReflectedBeam)
{
    EXPECT_TRUE(run("RectDetectorPerpToReflectedBeam", "CylindersInBABuilder", 1e-10));
}

TEST_F(Std, RectDetectorPerpToReflectedBeamDpos)
{
    EXPECT_TRUE(run("RectDetectorPerpToReflectedBeamDpos", "CylindersInBABuilder", 1e-10));
}

TEST_F(Std, LargeCylindersMonteCarlo)
{
    EXPECT_TRUE(run("MiniGISASMonteCarlo", "LargeCylindersInDWBABuilder", 5e-1));
}

TEST_F(Std, SphericalDetWithRoi)
{
    EXPECT_TRUE(run("SphericalDetWithRoi", "CylindersAndPrismsBuilder", 1e-10));
}

TEST_F(Std, RectDetWithRoi)
{
    EXPECT_TRUE(run("RectDetWithRoi", "CylindersAndPrismsBuilder", 1e-10));
}

TEST_F(Std, BoxesWithSpecular)
{
    EXPECT_TRUE(run("MiniGISASSpecular", "BoxesSquareLatticeBuilder", 1e-10));
}

TEST_F(Std, RotatedCylinder)
{
    EXPECT_TRUE(run("MiniGISAS", "RotatedCylindersBuilder", 1e-10));
}

TEST_F(Std, SlicedComposition)
{
    EXPECT_TRUE(run("MiniGISAS", "SlicedCompositionBuilder", 1e-10));
}
    // Simulations with background
TEST_F(Std, ConstantBackground)
{
    EXPECT_TRUE(run("ConstantBackground", "CylindersInBABuilder", 1e-10));
}
    // Specular simulations
TEST_F(Std, HomogeneousTiNiSample)
{
    EXPECT_TRUE(run("BasicSpecular", "HomogeneousMultilayerBuilder", 1e-10));
}

TEST_F(Std, HomogeneousTiNiSampleWithAbsorption)
{
    EXPECT_TRUE(run("BasicSpecular", "PlainMultiLayerBySLDBuilder", 1e-10));
}

TEST_F(Std, RoughnessInSpecular)
{
    EXPECT_TRUE(run("BasicSpecular", "MultiLayerWithRoughnessBuilder", 2e-9));
}

TEST_F(Std, NCRoughnessInSpecular)
{
    EXPECT_TRUE(run("BasicSpecular", "MultiLayerWithNCRoughnessBuilder", 2e-9));
}

TEST_F(Std, GaussianBeamFootprint)
{
    EXPECT_TRUE(run("SpecularWithGaussianBeam", "HomogeneousMultilayerBuilder", 1e-10));
}

TEST_F(Std, SquareBeamFootprint)
{
    EXPECT_TRUE(run("SpecularWithSquareBeam", "HomogeneousMultilayerBuilder", 1e-10));
}

TEST_F(Std, SpecularDivergentBeam)
{
    EXPECT_TRUE(run("SpecularDivergentBeam", "HomogeneousMultilayerBuilder", 1e-10));
}

TEST_F(Std, RelativeResolutionTOF)
{
    EXPECT_TRUE(run("TOFRWithRelativeResolution", "PlainMultiLayerBySLDBuilder", 1e-10));
}
TEST_F(Std, SpecularWithSlicing)
{
    EXPECT_TRUE(run("BasicSpecular", "SlicedCylindersBuilder", 1e-10));
    EXPECT_TRUE(run("BasicSpecular", "SLDSlicedCylindersBuilder", 1e-10));
    EXPECT_TRUE(run("BasicSpecular", "AveragedSlicedCylindersBuilder", 1e-10));
    EXPECT_TRUE(run("BasicSpecularQ", "SLDSlicedCylindersBuilder", 1e-10));
}

TEST_F(Std, InstrumentDefinitionComparison)
{
    EXPECT_TRUE(run("BasicSpecular", "PlainMultiLayerBySLDBuilder", 1e-10));
    EXPECT_TRUE(run("BasicSpecularQ", "PlainMultiLayerBySLDBuilder", 1e-10));
}

TEST_F(Std, TOFResolutionComparison)
{
    EXPECT_TRUE(run("TOFRWithRelativeResolution", "PlainMultiLayerBySLDBuilder", 1e-10));
    EXPECT_TRUE(run("TOFRWithPointwiseResolution", "PlainMultiLayerBySLDBuilder", 1e-10));
}
    // polarized specular
TEST_F(Std, BasicSpecularPP)
{
    EXPECT_TRUE(run("BasicSpecularPP", "SimpleMagneticLayerBuilder", 1e-10));
}

TEST_F(Std, BasicSpecularMM)
{
    EXPECT_TRUE(run("BasicSpecularMM", "SimpleMagneticLayerBuilder", 1e-10));
}
TEST_F(Std, PolarizedQAngleReflectivityPP)
{
    EXPECT_TRUE(run("BasicSpecularPP", "SimpleMagneticLayerBuilder", 1e-10));
    EXPECT_TRUE(run("BasicQSpecularPP", "SimpleMagneticLayerBuilder", 1e-10));
}

TEST_F(Std, PolarizedQAngleReflectivityMM)
{
    EXPECT_TRUE(run("BasicSpecularMM", "SimpleMagneticLayerBuilder", 1e-10));
    EXPECT_TRUE(run("BasicQSpecularMM", "SimpleMagneticLayerBuilder", 1e-10));
}

TEST_F(Std, OffSpecularResonator)
{
    EXPECT_TRUE(run("OffSpecMini", "ResonatorBuilder", 1e-10));
}

TEST_F(Std, DepthProbeTest)
{
    EXPECT_TRUE(run("BasicDepthProbe", "HomogeneousMultilayerBuilder", 1e-10));
}
