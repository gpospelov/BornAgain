// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS03Builder.cpp
//! @brief     Implements class IsGISAXS03Builder.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXS03Builder.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Materials.h"
#include "FormFactorCylinder.h"
#include "Units.h"
#include "InterferenceFunctionNone.h"
#include "Distributions.h"
#include "ParticleDistribution.h"


// -----------------------------------------------------------------------------
// Cylinders in DWBA
// -----------------------------------------------------------------------------
IsGISAXS03DWBABuilder::IsGISAXS03DWBABuilder()
    : m_height(5*Units::nanometer)
    , m_radius(5*Units::nanometer)
{
    init_parameters();
}


void IsGISAXS03DWBABuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("radius", &m_radius);
    registerParameter("height", &m_height);
}


ISample *IsGISAXS03DWBABuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(m_radius, m_height);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);
    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}


// -----------------------------------------------------------------------------
// Cylinders in BA
// -----------------------------------------------------------------------------
IsGISAXS03BABuilder::IsGISAXS03BABuilder()
    : m_height(5*Units::nanometer)
    , m_radius(5*Units::nanometer)
{
    init_parameters();
}


void IsGISAXS03BABuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("radius", &m_radius);
    registerParameter("height", &m_height);
}


ISample *IsGISAXS03BABuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);

    FormFactorCylinder ff_cylinder(m_radius, m_height);
    Particle cylinder(particle_material,ff_cylinder);

    ParticleLayout particle_layout(cylinder);
    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.addLayout(particle_layout);
    multi_layer->addLayer(air_layer);

    return multi_layer;
}


// -----------------------------------------------------------------------------
// Cylinders in BA with size distribution
// -----------------------------------------------------------------------------
IsGISAXS03BASizeBuilder::IsGISAXS03BASizeBuilder()
    : m_height(5*Units::nanometer)
    , m_radius(5*Units::nanometer)
{
    init_parameters();
}


void IsGISAXS03BASizeBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("radius", &m_radius);
    registerParameter("height", &m_height);
}


ISample *IsGISAXS03BASizeBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);

    ParticleLayout particle_layout;
    // preparing prototype of nano particle
    double sigma = 0.2*m_radius;
    FormFactorCylinder p_ff_cylinder( m_radius, m_height);
    Particle nano_particle(particle_material, p_ff_cylinder);
    // radius of nanoparticles will be sampled with gaussian probability
    int n_samples(100);
    // to get radius_min = average - 2.0*FWHM:
    double n_sigma = 2.0*2.0*std::sqrt(2.0*std::log(2.0));
    DistributionGaussian gauss(m_radius, sigma);
    ParameterDistribution par_distr("*/radius", gauss, n_samples, n_sigma);
    ParticleDistribution particle_collection(nano_particle, par_distr);
    particle_layout.addParticle(particle_collection);
    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);

    return multi_layer;
}
