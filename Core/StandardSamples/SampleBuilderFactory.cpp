// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SampleBuilderFactory.cpp
//! @brief     Implement class SampleBuilderFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "Core/StandardSamples/BoxCompositionBuilder.h"
#include "Core/StandardSamples/BoxesSquareLatticeBuilder.h"
#include "Core/StandardSamples/CoreShellParticleBuilder.h"
#include "Core/StandardSamples/CustomMorphologyBuilder.h"
#include "Core/StandardSamples/CylindersAndPrismsBuilder.h"
#include "Core/StandardSamples/CylindersBuilder.h"
#include "Core/StandardSamples/HomogeneousMultilayerBuilder.h"
#include "Core/StandardSamples/LatticeBuilder.h"
#include "Core/StandardSamples/LayersWithAbsorptionBuilder.h"
#include "Core/StandardSamples/LayersWithAbsorptionBySLDBuilder.h"
#include "Core/StandardSamples/MagneticLayersBuilder.h"
#include "Core/StandardSamples/MagneticParticlesBuilder.h"
#include "Core/StandardSamples/MesoCrystalBuilder.h"
#include "Core/StandardSamples/MultiLayerWithNCRoughnessBuilder.h"
#include "Core/StandardSamples/MultiLayerWithRoughnessBuilder.h"
#include "Core/StandardSamples/MultipleLayoutBuilder.h"
#include "Core/StandardSamples/ParaCrystalBuilder.h"
#include "Core/StandardSamples/ParticleCompositionBuilder.h"
#include "Core/StandardSamples/ParticleDistributionsBuilder.h"
#include "Core/StandardSamples/ParticleInTheAirBuilder.h"
#include "Core/StandardSamples/PercusYevickBuilder.h"
#include "Core/StandardSamples/PlainMultiLayerBySLDBuilder.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/StandardSamples/ResonatorBuilder.h"
#include "Core/StandardSamples/RipplesBuilder.h"
#include "Core/StandardSamples/RotatedPyramidsBuilder.h"
#include "Core/StandardSamples/SizeDistributionModelsBuilder.h"
#include "Core/StandardSamples/SlicedCylindersBuilder.h"
#include "Core/StandardSamples/SlicedParticleBuilder.h"
#include "Core/StandardSamples/ThickAbsorptiveSampleBuilder.h"
#include "Core/StandardSamples/TransformationsBuilder.h"
#include "Core/StandardSamples/TwoDimLatticeBuilder.h"
#include "Core/StandardSamples/TwoLayerRoughnessBuilder.h"

SampleBuilderFactory::SampleBuilderFactory()
{
    registerItem("CylindersAndPrismsBuilder", create_new<CylindersAndPrismsBuilder>,
                 "Mixture of cylinders and prisms without interference");

    registerItem("TwoTypesCylindersDistributionBuilder",
                 create_new<TwoTypesCylindersDistributionBuilder>,
                 "Mixture of cylinder particles with two types size distribution ");

    registerItem("CylindersInBABuilder", create_new<CylindersInBABuilder>,
                 "Cylinder form factor in BA");
    registerItem("CylindersInDWBABuilder", create_new<CylindersInDWBABuilder>,
                 "Cylinder form factor in DWBA");
    registerItem("LargeCylindersInDWBABuilder", create_new<LargeCylindersInDWBABuilder>,
                 "Large cylinders in DWBA");

    registerItem("CylindersWithSizeDistributionBuilder",
                 create_new<CylindersWithSizeDistributionBuilder>,
                 "Cylinder form factor in BA with size distribution");

    registerItem("RadialParaCrystalBuilder", create_new<RadialParaCrystalBuilder>,
                 "Interference function of radial paracrystal");

    registerItem("HardDiskBuilder", create_new<HardDiskBuilder>,
                 "Interference function of hard disk Percus-Yevick");

    registerItem("Basic2DParaCrystalBuilder", create_new<Basic2DParaCrystalBuilder>,
                 "Interference function of 2D basic paracrystal with variety of FT distributions");

    registerItem("HexParaCrystalBuilder", create_new<HexParaCrystalBuilder>,
                 "Interference function of 2D hexagonal paracrystal");

    registerItem("Lattice1DBuilder", create_new<Lattice1DBuilder>,
                 "Interference function of 1D lattice");

    registerItem("RectParaCrystalBuilder", create_new<RectParaCrystalBuilder>,
                 "Interference function of 2D rectangular paracrystal");

    registerItem("Basic2DLatticeBuilder", create_new<Basic2DLatticeBuilder>,
                 "Square lattice with arbitrary parameters");

    registerItem("SquareLatticeBuilder", create_new<SquareLatticeBuilder>,
                 "Interference of square lattice with disordered");

    registerItem("CenteredSquareLatticeBuilder", create_new<CenteredSquareLatticeBuilder>,
                 "Interference of centered square lattice");

    registerItem("RotatedSquareLatticeBuilder", create_new<RotatedSquareLatticeBuilder>,
                 "2D lattice rotated");

    registerItem("FiniteSquareLatticeBuilder", create_new<FiniteSquareLatticeBuilder>,
                 "Finite 2D lattice");

    registerItem("SuperLatticeBuilder", create_new<SuperLatticeBuilder>, "Superlattice");

    registerItem("CustomMorphologyBuilder", create_new<CustomMorphologyBuilder>,
                 "Mixture of different particles a la IsGISAXS morphology file");

    registerItem("RotatedPyramidsBuilder", create_new<RotatedPyramidsBuilder>,
                 "Rotated pyramids on top of substrate");

    registerItem("CoreShellParticleBuilder", create_new<CoreShellParticleBuilder>,
                 "Core shell nanoparticles");

    registerItem("CoreShellBoxRotateZandYBuilder", create_new<CoreShellBoxRotateZandYBuilder>,
                 "Rotation and translation of core shell box particle in 3 layers system.");

    registerItem("SizeDistributionDAModelBuilder", create_new<SizeDistributionDAModelBuilder>,
                 "Size distribution model: decoupling approximation");

    registerItem("SizeDistributionLMAModelBuilder", create_new<SizeDistributionLMAModelBuilder>,
                 "Size distribution model: local monodisperse approximation");

    registerItem("SizeDistributionSSCAModelBuilder", create_new<SizeDistributionSSCAModelBuilder>,
                 "Size distribution model: size space coupling approximation");

    registerItem("CylindersInSSCABuilder", create_new<CylindersInSSCABuilder>,
                 "Size spacing correlation approximation");

    registerItem("MesoCrystalBuilder", create_new<MesoCrystalBuilder>,
                 "Mesocrystals of cylindrical shape composed by spherical nanoparticles");

    registerItem("MagneticParticleZeroFieldBuilder", create_new<MagneticParticleZeroFieldBuilder>,
                 "Polarized DWBA with zero magnetic field");

    registerItem("MagneticCylindersBuilder", create_new<MagneticCylindersBuilder>,
                 "Polarized DWBA with non-zero magnetic field");

    registerItem("MagneticSubstrateZeroFieldBuilder", create_new<MagneticSubstrateZeroFieldBuilder>,
                 "Polarized DWBA with zero field substrate");

    registerItem("MagneticLayerBuilder", create_new<SimpleMagneticLayerBuilder>,
                 "Sample with one magnetic 10nm-thick layer");

    registerItem("MagnetizedLayerWithSpheresBuilder", create_new<MagneticLayerBuilder>,
                 "Magnetized particles in a magnetized layer");

    registerItem("MagneticRotationBuilder", create_new<MagneticRotationBuilder>,
                 "Rotated magnetic particle in magnetic substrate");

    registerItem("MagneticSpheresBuilder", create_new<MagneticSpheresBuilder>,
                 "Spheres with magnetization inside substrate");

    registerItem("MultiLayerWithRoughnessBuilder", create_new<MultiLayerWithRoughnessBuilder>,
                 "Layer with correlated roughness");

    registerItem("MultiLayerWithNCRoughnessBuilder", create_new<MultiLayerWithNCRoughnessBuilder>,
                 "Layer with correlated roughness");

    registerItem("TwoLayerRoughnessBuilder", create_new<TwoLayerRoughnessBuilder>,
                 "Two layers with rough interface");

    registerItem("MultipleLayoutBuilder", create_new<MultipleLayoutBuilder>,
                 "cylinder and prisms using multiple layouts");

    registerItem("TriangularRippleBuilder", create_new<TriangularRippleBuilder>,
                 "triangular ripple within the 1D-paracrystal model");

    registerItem("AsymRippleBuilder", create_new<AsymRippleBuilder>,
                 "triangular ripple with asymetry within the 1D-paracrystal model");

    registerItem("CosineRippleBuilder", create_new<CosineRippleBuilder>,
                 "cosine ripple within the 1D-paracrystal model");

    registerItem("ParticleCompositionBuilder", create_new<ParticleCompositionBuilder>,
                 "Composition of particles to represent two layers of spheres in hex lattice");

    registerItem("BoxCompositionRotateXBuilder", create_new<BoxCompositionRotateXBuilder>,
                 "Two boxes in particle composition rotated in X by 90 degrees");

    registerItem("BoxCompositionRotateYBuilder", create_new<BoxCompositionRotateYBuilder>,
                 "Two boxes in particle composition rotated in Y by 90 degrees");

    registerItem("BoxCompositionRotateZBuilder", create_new<BoxCompositionRotateZBuilder>,
                 "Two boxes in particle composition rotated in Z by 90 degrees");

    registerItem("BoxCompositionRotateZandYBuilder", create_new<BoxCompositionRotateZandYBuilder>,
                 "Two boxes in particle composition rotated in Z and Y by 90 degrees");

    registerItem(
        "BoxStackCompositionBuilder", create_new<BoxStackCompositionBuilder>,
        "Two different boxes are first rotated and then composed, composition is then rotated.");

    registerItem("ParticleInTheAirBuilder", create_new<ParticleInTheAirBuilder>,
                 "Particle in the air layer to test form factors");

    registerItem("TransformBoxBuilder", create_new<TransformBoxBuilder>,
                 "Rotated and translated box in 3 layer system");

    registerItem("LayersWithAbsorptionBuilder", create_new<LayersWithAbsorptionBuilder>,
                 "3 layer system with absorption");

    registerItem("LayersWithAbsorptionBySLDBuilder", create_new<LayersWithAbsorptionBySLDBuilder>,
                 "3 SLD-layer system with absorption");

    registerItem("BoxesSquareLatticeBuilder", create_new<BoxesSquareLatticeBuilder>,
                 "Boxes in a square lattice");

    registerItem("RotatedCylindersBuilder", create_new<RotatedCylindersBuilder>,
                 "Rotated cylinder in substrate");

    registerItem("SlicedCompositionBuilder", create_new<SlicedCompositionBuilder>,
                 "Spherical particle made of two different materials crossing interface");

    registerItem("RotatedPyramidsDistributionBuilder",
                 create_new<RotatedPyramidsDistributionBuilder>, "Rotated pyramids distribution");

    registerItem(
        "SpheresWithLimitsDistributionBuilder", create_new<SpheresWithLimitsDistributionBuilder>,
        "Spherical particles with the distribution applied to the radius and RealLimits defined");

    registerItem("ConesWithLimitsDistributionBuilder",
                 create_new<ConesWithLimitsDistributionBuilder>,
                 "Cones with the distribution applied to the angle and RealLimits defined.");

    registerItem("LinkedBoxDistributionBuilder", create_new<LinkedBoxDistributionBuilder>,
                 "Distribution of boxes with main parameter and two linked parameters.");

    registerItem("HomogeneousMultilayerBuilder", create_new<HomogeneousMultilayerBuilder>,
                 "Alternating homogeneous layers of Ti and Ni on silicone substrate.");

    registerItem("PlainMultiLayerBySLDBuilder", create_new<PlainMultiLayerBySLDBuilder>,
                 "Alternating homogeneous layers of Ti and Ni on silicone substrate "
                 "(wavelength-independent).");

    registerItem("ResonatorBuilder", create_new<ResonatorBuilder>,
                 "Multilayer with bi-layer sequence for OffSpec testing.");

    registerItem("SlicedCylindersBuilder", create_new<SlicedCylindersBuilder>,
                 "Multilayer with cylinders on substrate (sliced)");

    registerItem("SLDSlicedCylindersBuilder", create_new<SLDSlicedCylindersBuilder>,
                 "Multilayer with cylinders on substrate (sliced, using sld-based materials)");

    registerItem("AveragedSlicedCylindersBuilder", create_new<AveragedSlicedCylindersBuilder>,
                 "Manually sliced multilayer with cylinders on substrate (sld-based materials)");

    registerItem("ThickAbsorptiveSampleBuilder", create_new<ThickAbsorptiveSampleBuilder>,
                 "Thick highly-absorptive multilayer with a rough substrate");
}

//! Retrieves a SampleBuilder from the registry, does the build, and returns the result.

MultiLayer* SampleBuilderFactory::createSample(const std::string& name)
{
    return create(name)->buildSample();
}
