// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS02Builder.cpp
//! @brief     Implements class IsGISAXS02Builder.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXS02Builder.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Materials.h"
#include "FormFactorCylinder.h"
#include "Units.h"
#include "InterferenceFunctionNone.h"
#include "ParticleDistribution.h"
#include "Distributions.h"


IsGISAXS02Builder::IsGISAXS02Builder()
    : m_radius1(5*Units::nanometer)
    , m_radius2(10*Units::nanometer)
    , m_height1(5*Units::nanometer)
    , m_height2(10*Units::nanometer)
    , m_sigma1_ratio(0.2)
    , m_sigma2_ratio(0.02)
{
    init_parameters();
}


void IsGISAXS02Builder::init_parameters()
{
    clearParameterPool();
    registerParameter("radius1", &m_radius1);
    registerParameter("radius2", &m_radius2);
    registerParameter("height1", &m_height1);
    registerParameter("height2", &m_height2);
    registerParameter("sigma1_ratio", &m_sigma1_ratio);
    registerParameter("sigma2_ratio", &m_sigma2_ratio);
}


ISample *IsGISAXS02Builder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial particle_material ("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);

    ParticleLayout particle_layout;

    // preparing nano particles prototypes for seeding layer's particle_layout
    FormFactorCylinder p_ff_cylinder1(m_radius1, m_height1);
    Particle cylinder1(particle_material, p_ff_cylinder1 );

    FormFactorCylinder p_ff_cylinder2(m_radius2, m_height2);
    Particle cylinder2(particle_material, p_ff_cylinder2 );

    // radius of nanoparticles will be sampled with gaussian probability
    int nbins=150;
    double sigma1 = m_radius1*m_sigma1_ratio;
    double sigma2 = m_radius2*m_sigma2_ratio;
    // to have xmin=average-3*sigma
    double n_sigma = 3.0;
    DistributionGaussian gauss1(m_radius1, sigma1);
    DistributionGaussian gauss2(m_radius2, sigma2);

    // building distribution of nano particles
    ParameterDistribution par_distr1("*/radius", gauss1, nbins, n_sigma);
    ParticleDistribution particle_collection1(cylinder1, par_distr1);
    particle_layout.addParticle(particle_collection1, 0.0, 0.95);
    ParameterDistribution par_distr2("*/radius", gauss2, nbins, n_sigma);
    ParticleDistribution particle_collection2(cylinder2, par_distr2);
    particle_layout.addParticle(particle_collection2, 0.0, 0.05);

    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);

    return multi_layer;
}

