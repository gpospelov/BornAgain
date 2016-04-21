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

#include "SampleBuilderFactory.h"
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

SampleBuilderFactory::SampleBuilderFactory()
{
    registerItem(
        "CylindersAndPrismsBuilder",
        IFactoryCreateFunction<CylindersAndPrismsBuilder, ISampleBuilder>,
        "Mixture of cylinders and prisms without interference");

    registerItem(
        "TwoTypesCylindersDistributionBuilder",
        IFactoryCreateFunction<TwoTypesCylindersDistributionBuilder, ISampleBuilder>,
        "Mixture of cylinder particles with two types size distribution ");

    registerItem(
        "CylindersInBABuilder",
        IFactoryCreateFunction<CylindersInBABuilder, ISampleBuilder>,
        "Cylinder formfactor in BA");
    registerItem(
        "CylindersInDWBABuilder",
        IFactoryCreateFunction<CylindersInDWBABuilder, ISampleBuilder>,
        "Cylinder formfactor in DWBA");
    registerItem(
        "LargeCylindersInDWBABuilder",
        IFactoryCreateFunction<LargeCylindersInDWBABuilder, ISampleBuilder>,
        "Large cylinders in DWBA");

    registerItem(
        "CylindersWithSizeDistributionBuilder",
        IFactoryCreateFunction<CylindersWithSizeDistributionBuilder, ISampleBuilder>,
        "Cylinder formfactor in BA with size distribution");

    registerItem(
        "RadialParaCrystalBuilder",
        IFactoryCreateFunction<RadialParaCrystalBuilder, ISampleBuilder>,
        "Interference function of radial paracrystal");

    registerItem(
        "Basic2DParaCrystalBuilder",
        IFactoryCreateFunction<Basic2DParaCrystalBuilder, ISampleBuilder>,
        "Interference function of 2D basic paracrystal with variety of FT distributions");

    registerItem(
        "HexParaCrystalBuilder",
        IFactoryCreateFunction<HexParaCrystalBuilder, ISampleBuilder>,
        "Interference function of 2D hexagonal paracrystal");

    registerItem(
        "Lattice1DBuilder",
        IFactoryCreateFunction<Lattice1DBuilder, ISampleBuilder>,
        "Interference function of 1D lattice");

    registerItem(
        "RectParaCrystalBuilder",
        IFactoryCreateFunction<RectParaCrystalBuilder, ISampleBuilder>,
        "Interference function of 2D rectangular paracrystal");

    registerItem(
        "SquareLatticeBuilder",
        IFactoryCreateFunction<SquareLatticeBuilder, ISampleBuilder>,
        "Interference of square lattice with disordered");

    registerItem(
        "CenteredSquareLatticeBuilder",
        IFactoryCreateFunction<CenteredSquareLatticeBuilder, ISampleBuilder>,
        "Interference of centered square lattice");

    registerItem(
        "RotatedSquareLatticeBuilder",
        IFactoryCreateFunction<RotatedSquareLatticeBuilder, ISampleBuilder>,
        "2D lattice rotated");

    registerItem(
        "CustomMorphologyBuilder",
        IFactoryCreateFunction<CustomMorphologyBuilder, ISampleBuilder>,
        "Mixture of different particles a la IsGISAXS morphology file");

    registerItem(
        "RotatedPyramidsBuilder",
        IFactoryCreateFunction<RotatedPyramidsBuilder, ISampleBuilder>,
        "Rotated pyramids on top of substrate");

    registerItem(
        "CoreShellParticleBuilder",
        IFactoryCreateFunction<CoreShellParticleBuilder, ISampleBuilder>,
        "Core shell nanoparticles");

    registerItem(
        "CoreShellBoxRotateZandYBuilder",
        IFactoryCreateFunction<CoreShellBoxRotateZandYBuilder, ISampleBuilder>,
        "Rotation and translation of core shell box particle in 3 layers system.");

    registerItem(
        "SizeDistributionDAModelBuilder",
        IFactoryCreateFunction<SizeDistributionDAModelBuilder, ISampleBuilder>,
        "Size distribution model: decoupling approximation");

    registerItem(
        "SizeDistributionLMAModelBuilder",
        IFactoryCreateFunction<SizeDistributionLMAModelBuilder, ISampleBuilder>,
        "Size distribution model: local monodisperse approximation");

    registerItem(
        "SizeDistributionSSCAModelBuilder",
        IFactoryCreateFunction<SizeDistributionSSCAModelBuilder, ISampleBuilder>,
        "Size distribution model: size space coupling approximation");

    registerItem(
        "CylindersInSSCABuilder",
        IFactoryCreateFunction<CylindersInSSCABuilder, ISampleBuilder>,
        "Size spacing correlation approximation");

    registerItem(
        "MesoCrystalBuilder",
        IFactoryCreateFunction<MesoCrystalBuilder, ISampleBuilder>,
        "Mesocrystals of cylindrical shape composed by spherical nanoparticles");

    registerItem(
        "MagneticParticleZeroFieldBuilder",
        IFactoryCreateFunction<MagneticParticleZeroFieldBuilder, ISampleBuilder>,
        "Polarized DWBA with zero magnetic field");

    registerItem(
        "MagneticCylindersBuilder",
        IFactoryCreateFunction<MagneticCylindersBuilder, ISampleBuilder>,
        "Polarized DWBA with non-zero magnetic field");

    registerItem(
        "MultiLayerWithRoughnessBuilder",
        IFactoryCreateFunction<MultiLayerWithRoughnessBuilder, ISampleBuilder>,
        "Layer with correlated roughness");

    registerItem(
       "MultipleLayoutBuilder",
       IFactoryCreateFunction<MultipleLayoutBuilder, ISampleBuilder>,
      "cylinder and prisms using multiple layouts");

    registerItem(
        "TriangularRippleBuilder",
        IFactoryCreateFunction<TriangularRippleBuilder, ISampleBuilder>,
        "triangular ripple within the 1D-paracrystal model");

    registerItem(
        "CosineRippleBuilder",
        IFactoryCreateFunction<CosineRippleBuilder, ISampleBuilder>,
        "cosine ripple within the 1D-paracrystal model");

    registerItem(
        "ParticleCompositionBuilder",
        IFactoryCreateFunction<ParticleCompositionBuilder, ISampleBuilder>,
        "Composition of particles to represent two layers of spheres in hex lattice");

    registerItem(
        "BoxCompositionRotateXBuilder",
        IFactoryCreateFunction<BoxCompositionRotateXBuilder, ISampleBuilder>,
        "Two boxes in particle composition rotated in X by 90 degrees");

    registerItem(
        "BoxCompositionRotateYBuilder",
        IFactoryCreateFunction<BoxCompositionRotateYBuilder, ISampleBuilder>,
        "Two boxes in particle composition rotated in Y by 90 degrees");

    registerItem(
        "BoxCompositionRotateZBuilder",
        IFactoryCreateFunction<BoxCompositionRotateZBuilder, ISampleBuilder>,
        "Two boxes in particle composition rotated in Z by 90 degrees");

    registerItem(
        "BoxCompositionRotateZandYBuilder",
        IFactoryCreateFunction<BoxCompositionRotateZandYBuilder, ISampleBuilder>,
        "Two boxes in particle composition rotated in Z and Y by 90 degrees");

    registerItem(
        "BoxStackCompositionBuilder",
        IFactoryCreateFunction<BoxStackCompositionBuilder, ISampleBuilder>,
        "Two different boxes are first rotated and then composed, composition is then rotated.");

    registerItem(
        "ParticleInTheAirBuilder",
        IFactoryCreateFunction<ParticleInTheAirBuilder, ISampleBuilder>,
        "Particle in the air layer to test form factors");

    registerItem(
        "TransformBoxBuilder",
        IFactoryCreateFunction<TransformBoxBuilder, ISampleBuilder>,
        "Rotated and translated box in 3 layer system");

    registerItem(
        "LayersWithAbsorptionBuilder",
        IFactoryCreateFunction<LayersWithAbsorptionBuilder, ISampleBuilder>,
        "3 layer system with absorption");

}

ISample *SampleBuilderFactory::createSample(const std::string& name)
{
    std::shared_ptr<class ISampleBuilder> builder(createItem(name));
    ISample *result = builder->buildSample();
//    result->setName(name);
    return result;
}

std::shared_ptr<class ISampleBuilder> SampleBuilderFactory::createBuilder(const std::string& name)
{
    std::shared_ptr<class ISampleBuilder> result(createItem(name));
//    result->setName(name);
    return result;
}
