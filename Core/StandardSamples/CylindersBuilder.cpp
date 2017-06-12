// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/CylindersBuilder.cpp
//! @brief     Implements classes of CylindersBuilder family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CylindersBuilder.h"
#include "BornAgainNamespace.h"
#include "FormFactorCylinder.h"
#include "HomogeneousMaterial.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Rotations.h"
#include "Units.h"

// -----------------------------------------------------------------------------
// Cylinders in DWBA
// -----------------------------------------------------------------------------
CylindersInDWBABuilder::CylindersInDWBABuilder()
    : m_height(5*Units::nanometer)
    , m_radius(5*Units::nanometer)
{
    init_parameters();
}

MultiLayer* CylindersInDWBABuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(m_radius, m_height);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

void CylindersInDWBABuilder::init_parameters()
{
    registerParameter(BornAgain::Radius, &m_radius).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
}

// -----------------------------------------------------------------------------
// Cylinders in BA
// -----------------------------------------------------------------------------
CylindersInBABuilder::CylindersInBABuilder()
    : m_height(5*Units::nanometer)
    , m_radius(5*Units::nanometer)
{
    init_parameters();
}

MultiLayer* CylindersInBABuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);

    FormFactorCylinder ff_cylinder(m_radius, m_height);
    Particle cylinder(particle_material,ff_cylinder);

    ParticleLayout particle_layout(cylinder);

    air_layer.addLayout(particle_layout);
    multi_layer->addLayer(air_layer);

    return multi_layer;
}

void CylindersInBABuilder::init_parameters()
{
    registerParameter(BornAgain::Radius, &m_radius).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
}

// -----------------------------------------------------------------------------
// Large cylinders in DWBA
// -----------------------------------------------------------------------------
LargeCylindersInDWBABuilder::LargeCylindersInDWBABuilder()
    : m_height(1000*Units::nanometer)
    , m_radius(500*Units::nanometer)
{
    init_parameters();
}

MultiLayer* LargeCylindersInDWBABuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(m_radius, m_height);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

void LargeCylindersInDWBABuilder::init_parameters()
{

    registerParameter(BornAgain::Radius, &m_radius).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
}

// -----------------------------------------------------------------------------
// Rotated cylinders in DWBA
// -----------------------------------------------------------------------------
RotatedCylindersBuilder::RotatedCylindersBuilder()
    : m_height(5*Units::nanometer)
    , m_radius(5*Units::nanometer)
{
    init_parameters();
}

MultiLayer* RotatedCylindersBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    FormFactorCylinder ff_cylinder(m_radius, m_height);
    RotationY rotation(M_PI);
    kvector_t position(0, 0, 0);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout;
    particle_layout.addParticle(particle, 1.0, position, rotation);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);
    substrate_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

void RotatedCylindersBuilder::init_parameters()
{
    registerParameter(BornAgain::Radius, &m_radius).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
}
