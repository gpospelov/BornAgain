// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestBugs.cpp
//! @brief     Implements class TestBugs.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestBugs.h"
#include "MultiLayer.h"
#include "Materials.h"
#include "Units.h"
#include "FormFactorTruncatedSphere.h"
#include "Particle.h"
#include "ParticleLayout.h"
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
//    std::cout << "TestBugs::test_item339() -> " << std::endl;

//    complex_t n_particle(1.0-6e-4, 2e-8);
//    HomogeneousMaterial mParticle("Particle", n_particle );


//    FormFactorTruncatedSphere sphere_ff(8.0*Units::nanometer, 8.0*Units::nanometer);

//    Particle particle(mParticle, sphere_ff);

//    InterferenceFunction2DParaCrystal *interf =
//            InterferenceFunction2DParaCrystal::createHexagonal(20.0*Units::nanometer,
//                                                              0.0,20.0*Units::micrometer, 20.0*Units::micrometer);


//    ParticleLayout *decoration = new ParticleLayout();

//    decoration->addParticle(particle, 1.0);



//    decoration->addInterferenceFunction(interf);
    throw Exceptions::NotImplementedException("Cleanup the code!");

}




/*

# defining materials

sphere_ff = ba.FormFactorSphere(8 * ba.nanometer, 8 * ba.nanometer)
#sphere = ba.Particle(n_particle, sphere_ff)
sphere = ba.Particle(mParticle, sphere_ff)

interference = ba.InterferenceFunction2DParaCrystal.createHexagonal(20.0*ba.nanometer, 0.0,20.0*ba.micrometer, 20.0*ba.micrometer)
#pdf = ba.FTDistribution2DCauchy(1.0*ba.nanometer, 1.0*ba.nanometer)
#interference.setProbabilityDistributions(pdf, pdf)

particle_layout = ba.ParticleLayout()
particle_layout.addParticle(sphere, 0., 1.)
print 'before addInterferenceFunction'
particle_layout.addInterferenceFunction(interference)
print 'after addInterferenceFunction'

# air layer with particles and substrate form multi layer
air_layer = ba.Layer(mAmbience)
air_layer.setDecoration(particle_layout)
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

