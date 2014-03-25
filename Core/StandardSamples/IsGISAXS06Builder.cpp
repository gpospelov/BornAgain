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
#include "MaterialManager.h"
#include "InterferenceFunction2DLattice.h"
#include "PositionParticleInfo.h"
#include "OutputDataIOFactory.h"
#include "StochasticSampledParameter.h"
#include "StochasticDoubleGate.h"
#include "Utils.h"


// -----------------------------------------------------------------------------
// lattice #1:
// -----------------------------------------------------------------------------
ISample *IsGISAXS06Lattice1Builder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    const IMaterial *particle_material = MaterialManager::getHomogeneousMaterial("Particle", 6e-4, 2e-8);

    const IMaterial *p_air_material =
         MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *p_substrate_material =
         MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    Lattice2DIFParameters lattice_params;
    lattice_params.m_length_1 = 10.0*Units::nanometer; // L1
    lattice_params.m_length_2 = 10.0*Units::nanometer; // L2
    lattice_params.m_angle = 90.0*Units::degree; // lattice angle
    lattice_params.m_xi = 0.0*Units::degree; // lattice orientation

    InterferenceFunction2DLattice *p_interference_function =
        new InterferenceFunction2DLattice(lattice_params);
    FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI,
                               100.0*Units::nanometer/2.0/M_PI);
    p_interference_function->setProbabilityDistribution(pdf);

    // particles
    ParticleLayout particle_decoration;
    FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
    kvector_t position(0.0, 0.0, 0.0);
    PositionParticleInfo particle_info(
        new Particle(particle_material, ff_cyl.clone()), position, 1.0);
    particle_decoration.addParticleInfo(particle_info);

    particle_decoration.addInterferenceFunction(p_interference_function);

    air_layer.setLayout(particle_decoration);

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

    const IMaterial *particle_material = MaterialManager::getHomogeneousMaterial("Particle", 6e-4, 2e-8);

    const IMaterial *p_air_material =
         MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *p_substrate_material =
         MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    Lattice2DIFParameters lattice_params;
    lattice_params.m_length_1 = 10.0*Units::nanometer; // L1
    lattice_params.m_length_2 = 10.0*Units::nanometer; // L2
    lattice_params.m_angle = 90.0*Units::degree; // lattice angle
    lattice_params.m_xi = 0.0*Units::degree; // lattice orientation

    InterferenceFunction2DLattice *p_interference_function =
        new InterferenceFunction2DLattice(lattice_params);
    FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI,
                               100.0*Units::nanometer/2.0/M_PI);
    p_interference_function->setProbabilityDistribution(pdf);

    ParticleLayout particle_decoration;
    // particle 1
    FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
    kvector_t position(0.0, 0.0, 0.0);
    PositionParticleInfo particle_info(
        new Particle(particle_material, ff_cyl.clone()), position, 1.0);
    particle_decoration.addParticleInfo(particle_info);
    // particle 2
    kvector_t position_2(5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    particle_info.setPosition(position_2);
    particle_decoration.addParticleInfo(particle_info);

    particle_decoration.addInterferenceFunction(p_interference_function);

    air_layer.setLayout(particle_decoration);

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

    const IMaterial *particle_material = MaterialManager::getHomogeneousMaterial("Particle", 6e-4, 2e-8);

    const IMaterial *p_air_material =
        MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *p_substrate_material =
        MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    Lattice2DIFParameters lattice_params;
    lattice_params.m_length_1 = 10.0*Units::nanometer; // L1
    lattice_params.m_length_2 = 10.0*Units::nanometer; // L2
    lattice_params.m_angle = 90.0*Units::degree; // lattice angle
    lattice_params.m_xi = 30.0*Units::degree; // lattice orientation

    InterferenceFunction2DLattice *p_interference_function =
        new InterferenceFunction2DLattice(lattice_params);
    FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI,
                               100.0*Units::nanometer/2.0/M_PI);
    pdf.setGamma(30.0*Units::degree);
    p_interference_function->setProbabilityDistribution(pdf);

    ParticleLayout particle_decoration;
    // particle
    FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
    kvector_t position(0.0, 0.0, 0.0);
    PositionParticleInfo particle_info(
        new Particle(particle_material, ff_cyl.clone()), position, 1.0);
    particle_decoration.addParticleInfo(particle_info);
    particle_decoration.addInterferenceFunction(p_interference_function);

    air_layer.setLayout(particle_decoration);

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

    const IMaterial *particle_material =
            MaterialManager::getHomogeneousMaterial("Particle", 6e-4, 2e-8);
    const IMaterial *p_air_material =
         MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *p_substrate_material =
         MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    Lattice2DIFParameters lattice_params;
    lattice_params.m_length_1 = 10.0*Units::nanometer; // L1
    lattice_params.m_length_2 = 10.0*Units::nanometer; // L2
    lattice_params.m_angle = 90.0*Units::degree; // lattice angle
    lattice_params.m_xi = m_xi; // lattice orientation

    InterferenceFunction2DLattice *p_interference_function =
        new InterferenceFunction2DLattice(lattice_params);
    FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI,
                               100.0*Units::nanometer/2.0/M_PI);
    p_interference_function->setProbabilityDistribution(pdf);

    ParticleLayout particle_decoration;
    // particle
    FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
    kvector_t position(0.0, 0.0, 0.0);
    PositionParticleInfo particle_info(
        new Particle(particle_material, ff_cyl.clone()), position, 1.0);
    particle_decoration.addParticleInfo(particle_info);

    particle_decoration.addInterferenceFunction(p_interference_function);

    air_layer.setLayout(particle_decoration);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;

}
