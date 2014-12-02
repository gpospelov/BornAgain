// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS06Builder.cpp
//! @brief     Implements class IsGISAXS06Builder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXS06Builder.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "FormFactorCylinder.h"
#include "Simulation.h"
#include "Units.h"
#include "Materials.h"
#include "InterferenceFunction2DLattice.h"
#include "IntensityDataIOFactory.h"
#include "Utils.h"


// -----------------------------------------------------------------------------
// lattice #1:
// -----------------------------------------------------------------------------
ISample *IsGISAXS06Lattice1Builder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);
    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    InterferenceFunction2DLattice *p_interference_function =
        InterferenceFunction2DLattice::createSquare(10.0*Units::nanometer);
    FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI,
                               100.0*Units::nanometer/2.0/M_PI);
    p_interference_function->setProbabilityDistribution(pdf);

    // particles
    ParticleLayout particle_layout;
    FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
    Particle particle(particle_material, ff_cyl);
    particle_layout.addParticle(particle, 0.0, 1.0);

    particle_layout.addInterferenceFunction(p_interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}


// -----------------------------------------------------------------------------
// lattice #2: centered
// -----------------------------------------------------------------------------
ISample *IsGISAXS06Lattice2Builder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);
    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    InterferenceFunction2DLattice interference_function(10.0*Units::nanometer,
            10.0*Units::nanometer, M_PI/2.0);
    FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI,
                               100.0*Units::nanometer/2.0/M_PI);
    interference_function.setProbabilityDistribution(pdf);

    ParticleLayout particle_layout1;
    // particle 1
    FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
    kvector_t position(0.0, 0.0, 0.0);
    ParticleInfo particle_info(
        Particle(particle_material, ff_cyl), position, 1.0);
    particle_layout1.addParticleInfo(particle_info);
    particle_layout1.addInterferenceFunction(interference_function);
    ParticleLayout particle_layout2;
    // particle 2
    kvector_t position_2(5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    particle_info.setPosition(position_2);
    particle_layout2.addParticleInfo(particle_info);
    particle_layout2.addInterferenceFunction(interference_function);

    air_layer.addLayout(particle_layout1);
    air_layer.addLayout(particle_layout2);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}


// -----------------------------------------------------------------------------
// lattice #3: rotated
// -----------------------------------------------------------------------------
ISample *IsGISAXS06Lattice3Builder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);
    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    InterferenceFunction2DLattice *p_interference_function =
        InterferenceFunction2DLattice::createSquare(10.0*Units::nanometer,
                                                    30.0*Units::degree);
    FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI,
                               100.0*Units::nanometer/2.0/M_PI);
    pdf.setGamma(30.0*Units::degree);
    p_interference_function->setProbabilityDistribution(pdf);

    ParticleLayout particle_layout;
    // particle
    FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
    kvector_t position(0.0, 0.0, 0.0);
    ParticleInfo particle_info(
        Particle(particle_material, ff_cyl), position, 1.0);
    particle_layout.addParticleInfo(particle_info);
    particle_layout.addInterferenceFunction(p_interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}


// -----------------------------------------------------------------------------
// lattice #4: variants
// -----------------------------------------------------------------------------
IsGISAXS06Lattice4Builder::IsGISAXS06Lattice4Builder()
    : m_xi(0.0)
{
    init_parameters();
}

void IsGISAXS06Lattice4Builder::init_parameters()
{
    clearParameterPool();
    registerParameter("xi", &m_xi);
}

ISample *IsGISAXS06Lattice4Builder::buildSample() const
{
    MultiLayer *p_multi_layer = new MultiLayer();

    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);
    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    InterferenceFunction2DLattice *p_interference_function =
        InterferenceFunction2DLattice::createSquare(10.0*Units::nanometer,
                                                    m_xi);
    FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI,
                               100.0*Units::nanometer/2.0/M_PI);
    p_interference_function->setProbabilityDistribution(pdf);

    ParticleLayout particle_layout;
    // particle
    FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
    kvector_t position(0.0, 0.0, 0.0);

    Particle cylinder(particle_material, ff_cyl);

    ParticleInfo particle_info(cylinder, position, 1.0);
    particle_layout.addParticleInfo(particle_info);

    particle_layout.addInterferenceFunction(p_interference_function);

    air_layer.addLayout(particle_layout);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;

}
