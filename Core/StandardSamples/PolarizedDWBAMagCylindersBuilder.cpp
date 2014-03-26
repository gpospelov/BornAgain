// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/PolarizedDWBAZeroMagBuilder.cpp
//! @brief     Implements class PolarizedDWBAZeroMagBuilder
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PolarizedDWBAMagCylindersBuilder.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Materials.h"
#include "FormFactorCylinder.h"
#include "Units.h"
#include "InterferenceFunctionNone.h"


// ----------------------------------------------------------------------------
// Magnetic cylinders and zero magnetic field
// ----------------------------------------------------------------------------

PolarizedDWBAMagCylinders1Builder::PolarizedDWBAMagCylinders1Builder()
    :  m_cylinder_radius(5*Units::nanometer)
    ,  m_cylinder_height(5*Units::nanometer)

{
    init_parameters();
}


void PolarizedDWBAMagCylinders1Builder::init_parameters()
{
    clearParameterPool();
    registerParameter("cylinder_radius", &m_cylinder_radius);
    registerParameter("cylinder_height", &m_cylinder_height);
}


ISample *PolarizedDWBAMagCylinders1Builder::buildSample() const
{
	MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    kvector_t magnetic_field(0.0, 0.0, 0.0);
    HomogeneousMagneticMaterial particle_material("MagParticle", 6e-4, 2e-8, magnetic_field);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);

    ParticleLayout particle_layout(
            new Particle(particle_material,
                    ff_cylinder));

    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.setLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// ----------------------------------------------------------------------------
// Magnetic cylinders and non-zero magnetic field
// ----------------------------------------------------------------------------
PolarizedDWBAMagCylinders2Builder::PolarizedDWBAMagCylinders2Builder()
    :  m_cylinder_radius(5*Units::nanometer)
    ,  m_cylinder_height(5*Units::nanometer)
{
    init_parameters();
}


void PolarizedDWBAMagCylinders2Builder::init_parameters()
{
    clearParameterPool();
    registerParameter("cylinder_radius", &m_cylinder_radius);
    registerParameter("cylinder_height", &m_cylinder_height);
}


ISample *PolarizedDWBAMagCylinders2Builder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 15e-6, 0.0);
    kvector_t magnetic_field(0.0, 1.0, 0.0);
    HomogeneousMagneticMaterial particle_material("MagParticle2", 5e-6, 0.0, magnetic_field);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);

    ParticleLayout particle_layout(
            new Particle(particle_material,ff_cylinder));

    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.setLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

