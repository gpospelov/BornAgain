// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/SampleBuilderFactory.cpp
//! @brief     Implement class SampleBuilderFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <memory>
#include "ISample.h"
#include "CylindersAndPrismsBuilder.h"
#include "CylindersBuilder.h"
#include "ParaCrystalBuilder.h"
#include "LatticeBuilder.h"
#include "TwoDimLatticeBuilder.h"
#include "CustomMorphologyBuilder.h"
#include "RotatedPyramidsBuilder.h"
#include "CoreShellParticleBuilder.h"
#include "MesoCrystalBuilder.h"
#include "MultipleLayoutBuilder.h"
#include "MagneticParticlesBuilder.h"
#include "MultiLayerWithRoughnessBuilder.h"
#include "ParticleCompositionBuilder.h"
#include "ParticleInTheAirBuilder.h"
#include "ParticleDistributionsBuilder.h"
#include "RipplesBuilder.h"
#include "SizeDistributionModelsBuilder.h"
#include "TransformationsBuilder.h"
#include "BoxCompositionBuilder.h"
#include "LayersWithAbsorptionBuilder.h"
#include "SampleBuilderFactory.h"

//! build<C> is a function void -> ISampleBuilder*. C must be a child of ISampleBuilder.
template<class Builder> ISampleBuilder* build() { return new Builder(); }

SampleBuilderFactory::SampleBuilderFactory()
{
    registerItem(
        "CylindersAndPrismsBuilder",
        build<CylindersAndPrismsBuilder>,
        "Mixture of cylinders and prisms without interference");

    registerItem(
        "TwoTypesCylindersDistributionBuilder",
        build<TwoTypesCylindersDistributionBuilder>,
        "Mixture of cylinder particles with two types size distribution ");

    registerItem(
        "CylindersInBABuilder",
        build<CylindersInBABuilder>,
        "Cylinder formfactor in BA");
    registerItem(
        "CylindersInDWBABuilder",
        build<CylindersInDWBABuilder>,
        "Cylinder formfactor in DWBA");
    registerItem(
        "LargeCylindersInDWBABuilder",
        build<LargeCylindersInDWBABuilder>,
        "Large cylinders in DWBA");

    registerItem(
        "CylindersWithSizeDistributionBuilder",
        build<CylindersWithSizeDistributionBuilder>,
        "Cylinder formfactor in BA with size distribution");

    registerItem(
        "RadialParaCrystalBuilder",
        build<RadialParaCrystalBuilder>,
        "Interference function of radial paracrystal");

    registerItem(
        "Basic2DParaCrystalBuilder",
        build<Basic2DParaCrystalBuilder>,
        "Interference function of 2D basic paracrystal with variety of FT distributions");

    registerItem(
        "HexParaCrystalBuilder",
        build<HexParaCrystalBuilder>,
        "Interference function of 2D hexagonal paracrystal");

    registerItem(
        "Lattice1DBuilder",
        build<Lattice1DBuilder>,
        "Interference function of 1D lattice");

    registerItem(
        "RectParaCrystalBuilder",
        build<RectParaCrystalBuilder>,
        "Interference function of 2D rectangular paracrystal");

    registerItem(
        "SquareLatticeBuilder",
        build<SquareLatticeBuilder>,
        "Interference of square lattice with disordered");

    registerItem(
        "CenteredSquareLatticeBuilder",
        build<CenteredSquareLatticeBuilder>,
        "Interference of centered square lattice");

    registerItem(
        "RotatedSquareLatticeBuilder",
        build<RotatedSquareLatticeBuilder>,
        "2D lattice rotated");

    registerItem(
        "CustomMorphologyBuilder",
        build<CustomMorphologyBuilder>,
        "Mixture of different particles a la IsGISAXS morphology file");

    registerItem(
        "RotatedPyramidsBuilder",
        build<RotatedPyramidsBuilder>,
        "Rotated pyramids on top of substrate");

    registerItem(
        "CoreShellParticleBuilder",
        build<CoreShellParticleBuilder>,
        "Core shell nanoparticles");

    registerItem(
        "CoreShellBoxRotateZandYBuilder",
        build<CoreShellBoxRotateZandYBuilder>,
        "Rotation and translation of core shell box particle in 3 layers system.");

    registerItem(
        "SizeDistributionDAModelBuilder",
        build<SizeDistributionDAModelBuilder>,
        "Size distribution model: decoupling approximation");

    registerItem(
        "SizeDistributionLMAModelBuilder",
        build<SizeDistributionLMAModelBuilder>,
        "Size distribution model: local monodisperse approximation");

    registerItem(
        "SizeDistributionSSCAModelBuilder",
        build<SizeDistributionSSCAModelBuilder>,
        "Size distribution model: size space coupling approximation");

    registerItem(
        "CylindersInSSCABuilder",
        build<CylindersInSSCABuilder>,
        "Size spacing correlation approximation");

    registerItem(
        "MesoCrystalBuilder",
        build<MesoCrystalBuilder>,
        "Mesocrystals of cylindrical shape composed by spherical nanoparticles");

    registerItem(
        "MagneticParticleZeroFieldBuilder",
        build<MagneticParticleZeroFieldBuilder>,
        "Polarized DWBA with zero magnetic field");

    registerItem(
        "MagneticCylindersBuilder",
        build<MagneticCylindersBuilder>,
        "Polarized DWBA with non-zero magnetic field");

    registerItem(
        "MultiLayerWithRoughnessBuilder",
        build<MultiLayerWithRoughnessBuilder>,
        "Layer with correlated roughness");

    registerItem(
       "MultipleLayoutBuilder",
       build<MultipleLayoutBuilder>,
      "cylinder and prisms using multiple layouts");

    registerItem(
        "TriangularRippleBuilder",
        build<TriangularRippleBuilder>,
        "triangular ripple within the 1D-paracrystal model");

    registerItem(
        "CosineRippleBuilder",
        build<CosineRippleBuilder>,
        "cosine ripple within the 1D-paracrystal model");

    registerItem(
        "ParticleCompositionBuilder",
        build<ParticleCompositionBuilder>,
        "Composition of particles to represent two layers of spheres in hex lattice");

    registerItem(
        "BoxCompositionRotateXBuilder",
        build<BoxCompositionRotateXBuilder>,
        "Two boxes in particle composition rotated in X by 90 degrees");

    registerItem(
        "BoxCompositionRotateYBuilder",
        build<BoxCompositionRotateYBuilder>,
        "Two boxes in particle composition rotated in Y by 90 degrees");

    registerItem(
        "BoxCompositionRotateZBuilder",
        build<BoxCompositionRotateZBuilder>,
        "Two boxes in particle composition rotated in Z by 90 degrees");

    registerItem(
        "BoxCompositionRotateZandYBuilder",
        build<BoxCompositionRotateZandYBuilder>,
        "Two boxes in particle composition rotated in Z and Y by 90 degrees");

    registerItem(
        "BoxStackCompositionBuilder",
        build<BoxStackCompositionBuilder>,
        "Two different boxes are first rotated and then composed, composition is then rotated.");

    registerItem(
        "ParticleInTheAirBuilder",
        build<ParticleInTheAirBuilder>,
        "Particle in the air layer to test form factors");

    registerItem(
        "TransformBoxBuilder",
        build<TransformBoxBuilder>,
        "Rotated and translated box in 3 layer system");

    registerItem(
        "LayersWithAbsorptionBuilder",
        build<LayersWithAbsorptionBuilder>,
        "3 layer system with absorption");
}

//! Retrieves a SampleBuilder from the registry, does the build, and returns the result.

ISample *SampleBuilderFactory::createSample(const std::string& name)
{
    return createItem(name)->buildSample();
}
