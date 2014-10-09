// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS04Builder.cpp
//! @brief     Implements class IsGISAXS04Builder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXS04Builder.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Materials.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "FormFactorCylinder.h"
#include "Units.h"
#include "FTDistributions.h"

IsGISAXS04Para1DBuilder::IsGISAXS04Para1DBuilder()
    : m_corr_peak_distance(20.0*Units::nanometer)
    , m_corr_width(7*Units::nanometer)
    , m_corr_length(1e3*Units::nanometer)
    , m_cylinder_height(5*Units::nanometer)
    , m_cylinder_radius(5*Units::nanometer)
{
    init_parameters();
}

void IsGISAXS04Para1DBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("corr_peak_distance", &m_corr_peak_distance);
    registerParameter("corr_width", &m_corr_width);
    registerParameter("corr_length", &m_corr_length);
    registerParameter("cylinder_height", &m_cylinder_height);
    registerParameter("cylinder_radius", &m_cylinder_radius);
}

ISample *IsGISAXS04Para1DBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    InterferenceFunction1DParaCrystal *p_interference_function =
            new InterferenceFunction1DParaCrystal(
                    m_corr_peak_distance, m_corr_length);
    FTDistribution1DGauss pdf(m_corr_width);
    p_interference_function->setProbabilityDistribution(pdf);
    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);

    ParticleLayout particle_layout( new Particle(
            particle_material, ff_cylinder ) );
    particle_layout.addInterferenceFunction(p_interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}


// -----------------------------------------------------------------------------
//

IsGISAXS04Para2DBuilder::IsGISAXS04Para2DBuilder()
    : m_peak_distance(20.0*Units::nanometer)
    , m_corr_length(0.0)
    , m_domain_size_1(20.0*Units::micrometer)
    , m_domain_size_2(20.0*Units::micrometer)
    , m_cylinder_height(5*Units::nanometer)
    , m_cylinder_radius(5*Units::nanometer)
{
    init_parameters();
}

void IsGISAXS04Para2DBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("m_peak_distance", &m_peak_distance);
    registerParameter("m_corr_length", &m_corr_length);
    registerParameter("m_domain_size_1", &m_domain_size_1);
    registerParameter("m_domain_size_2", &m_domain_size_2);
    registerParameter("cylinder_height", &m_cylinder_height);
    registerParameter("cylinder_radius", &m_cylinder_radius);
}


ISample *IsGISAXS04Para2DBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);
    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    InterferenceFunction2DParaCrystal *p_interference_function =
            InterferenceFunction2DParaCrystal::createHexagonal(
                    m_peak_distance, m_corr_length,
                    m_domain_size_1, m_domain_size_2);
    FTDistribution2DCauchy pdf(1.0*Units::nanometer, 1.0*Units::nanometer);
    p_interference_function->setProbabilityDistributions(pdf, pdf);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);
    Particle cylinder(particle_material,ff_cylinder);

    ParticleLayout particle_layout(cylinder);
    particle_layout.addInterferenceFunction(p_interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}
