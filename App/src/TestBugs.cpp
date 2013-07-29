#include "TestBugs.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "Units.h"
#include "FormFactorSphere.h"
#include "Particle.h"
#include "ParticleDecoration.h"
#include "InterferenceFunction2DParaCrystal.h"

#include <iostream>

TestBugs::TestBugs()
{

}


void TestBugs::execute()
{
    test_item339();
}


void TestBugs::test_item339()
{
    std::cout << "TestBugs::test_item339() -> " << std::endl;

    const IMaterial *mAmbience =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0 );

    const IMaterial *mSubstrate =
            MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8 );

    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *mParticle =
            MaterialManager::getHomogeneousMaterial("Particle", n_particle );


    FormFactorSphere *sphere_ff = new FormFactorSphere(8.0*Units::nanometer, 8.0*Units::nanometer);

    Particle *particle = new Particle(mParticle, sphere_ff);

    InterferenceFunction2DParaCrystal *interf =
            InterferenceFunction2DParaCrystal::createHexagonal(20.0*Units::nanometer,
                                                              0.0,20.0*Units::micrometer, 20.0*Units::micrometer);


    ParticleDecoration *decoration = new ParticleDecoration();

    decoration->addParticle(particle,0., 1.0);



    decoration->addInterferenceFunction(interf);
}




/*

# defining materials

sphere_ff = ba.FormFactorSphere(8 * ba.nanometer, 8 * ba.nanometer)
#sphere = ba.Particle(n_particle, sphere_ff)
sphere = ba.Particle(mParticle, sphere_ff)

interference = ba.InterferenceFunction2DParaCrystal.createHexagonal(20.0*ba.nanometer, 0.0,20.0*ba.micrometer, 20.0*ba.micrometer)
#pdf = ba.FTDistribution2DCauchy(1.0*ba.nanometer, 1.0*ba.nanometer)
#interference.setProbabilityDistributions(pdf, pdf)

particle_decoration = ba.ParticleDecoration()
particle_decoration.addParticle(sphere, 0., 1.)
print 'before addInterferenceFunction'
particle_decoration.addInterferenceFunction(interference)
print 'after addInterferenceFunction'

# air layer with particles and substrate form multi layer
air_layer = ba.Layer(mAmbience)
air_layer.setDecoration(particle_decoration)
substrate_layer = ba.Layer(mSubstrate, 0)

multi_layer = ba.MultiLayer()
multi_layer.addLayer(air_layer)
multi_layer.addLayer(substrate_layer)

# build and run experiment
simulation = ba.Simulation()
simulation.setDetectorParameters(487/5, -1.4 * ba.degree, 0.15 * ba.degree,
                                 407/5, 0. * ba.degree, 1.4 * ba.degree, True)
simulation.setBeamParameters(.96 * ba.angstrom, 0.5 * ba.degree, 0.0 * ba.degree)
simulation.setSample(multi_layer)
simulation.runSimulation()
## intensity data
return ba.GetOutputData(simulation)


*/

