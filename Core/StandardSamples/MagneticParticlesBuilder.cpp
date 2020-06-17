// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MagneticParticlesBuilder.cpp
//! @brief     Implements classes to build magnetic samples
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MagneticParticlesBuilder.h"
#include "BornAgainNamespace.h"
#include "FormFactorCylinder.h"
#include "FormFactorFullSphere.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MaterialFactoryFuncs.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"

// ----------------------------------------------------------------------------
// Magnetic cylinders and zero magnetic field
// ----------------------------------------------------------------------------
MagneticParticleZeroFieldBuilder::MagneticParticleZeroFieldBuilder()
    : m_cylinder_radius(5 * Units::nanometer), m_cylinder_height(5 * Units::nanometer)
{
}

MultiLayer* MagneticParticleZeroFieldBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);
    kvector_t magnetic_field(0.0, 0.0, 0.0);
    Material particle_material = HomogeneousMaterial("MagParticle", 6e-4, 2e-8, magnetic_field);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// ----------------------------------------------------------------------------
// Magnetic cylinders and non-zero magnetization
// ----------------------------------------------------------------------------
MagneticCylindersBuilder::MagneticCylindersBuilder()
    : m_cylinder_radius(5 * Units::nanometer), m_cylinder_height(5 * Units::nanometer)
{
}

MultiLayer* MagneticCylindersBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 15e-6, 0.0);
    kvector_t magnetization(0.0, 1e6, 0.0);
    Material particle_material = HomogeneousMaterial("MagParticle2", 5e-6, 0.0, magnetization);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// ----------------------------------------------------------------------------
// Magnetic spheres inside substrate
// ----------------------------------------------------------------------------
MagneticSpheresBuilder::MagneticSpheresBuilder() : m_sphere_radius(5 * Units::nanometer) {}

MultiLayer* MagneticSpheresBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();
    kvector_t magnetization(0.0, 0.0, 1e7);
    Material particle_material = HomogeneousMaterial("Particle", 2e-5, 4e-7, magnetization);
    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 7e-6, 1.8e-7);

    FormFactorFullSphere ff_sphere(m_sphere_radius);
    Particle particle(particle_material, ff_sphere);
    kvector_t position(0.0, 0.0, -2.0 * m_sphere_radius);

    ParticleLayout particle_layout;
    particle_layout.addParticle(particle, 1.0, position);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);
    substrate_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
