# This example shows how to create a sample with fixed parameters and then
# change this parameters on the fly during runtime.
# The example doesn't contain any fitting and serve as a gentle introduction
# to other fitting examples.

import sys, os, numpy, pylab, matplotlib
from libBornAgainCore import *


def get_sample():
    """
    Build and return the sample representing cylinders and pyramids on top of
    substrate without interference. Sample is made for fixed set of parameters.
    """
    # defining materials
    m_air = MaterialManager.getHomogeneousMaterial("Air", 0.0, 0.0 )
    m_substrate = MaterialManager.getHomogeneousMaterial("Substrate", 6e-6, 2e-8 )
    m_particle = MaterialManager.getHomogeneousMaterial("Particle", 6e-4, 2e-8 )

    # collection of particles
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(m_particle, cylinder_ff)
    prism_ff = FormFactorPrism3(5*nanometer, 5*nanometer)
    prism = Particle(m_particle, prism_ff)
    particle_decoration = ParticleDecoration()
    particle_decoration.addParticle(cylinder, 0.0, 0.5)
    particle_decoration.addParticle(prism, 0.0, 0.5)
    interference = InterferenceFunctionNone()
    particle_decoration.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(m_air)
    air_layer.setDecoration(particle_decoration)
    substrate_layer = Layer(m_substrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = Simulation()
    simulation.setDetectorParameters(100, -1.0*degree, 1.0*degree
        , 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


def run_simulations():
    """
    Runs simulations for the sample with different sample parameters.
    """

    sample = get_sample()
    print "The sample contains following parameters ('name':value)"
    sample.printParameters()

    simulation = get_simulation()
    simulation.setSample(sample)

    results = []

    # simulation #1
    # # initial sample is used
    simulation.runSimulation()
    results.append( GetOutputData(simulation) )

    # simulation #2
    # one sample parameter (height of the cylinder) is changed using exact parameter name
    sample.setParameterValue("/MultiLayer/Layer0/ParticleDecoration/ParticleInfo0/Particle/FormFactorCylinder/height"
        , 1.0*nanometer)
    simulation.runSimulation()
    results.append( GetOutputData(simulation) )

    # simulation #3
    # all parameters which are matching criteria will be changed


    return results


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    results = run_simulations()
#    result = run_simulation() + 1 # for log scale
#    pylab.imshow(numpy.rot90(result, 1), 
#                 norm=matplotlib.colors.LogNorm(), 
#                 extent=[-1.0, 1.0, 0, 2.0])
#    pylab.show()    


