"""
Working with sample parameters
"""

import matplotlib
from matplotlib import pyplot as plt
from bornagain import *


def get_sample():
    """
    Build and return the sample representing cylinders and prisms on top of
    substrate without interference. Sample is made for fixed set of parameters.
    """
    # defining materials
    m_air = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(m_particle, cylinder_ff)
    prism_ff = FormFactorPrism3(5*nanometer, 5*nanometer)
    prism = Particle(m_particle, prism_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 0.5)
    particle_layout.addParticle(prism, 0.5)
    interference = InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(m_air)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(m_substrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


def run_simulations():
    """
    Runs simulations for the sample with different sample parameters.
    """

    sample = get_sample()
    print "The tree structure of the sample"
    sample.printSampleTree()

    print "The sample contains following parameters ('name':value)"
    sample.printParameters()

    simulation = get_simulation()

    results = []

    # simulation #1
    # initial sample is used
    simulation.setSample(sample)
    simulation.runSimulation()
    results.append(simulation.getIntensityData())

    # simulation #2
    # one sample parameter (height of the cylinder) is changed using exact parameter name
    sample.setParameterValue(
        "/MultiLayer/Layer0/ParticleLayout/ParticleInfo0/Particle/FormFactorCylinder/height", 10.0*nanometer)

    simulation.setSample(sample)
    simulation.runSimulation()
    results.append(simulation.getIntensityData())

    # simulation #3
    # all parameters matching criteria will be changed (height of the cylinder in this case)
    sample.setParameterValue("*/FormFactorCylinder/height", 100.0*nanometer)
    simulation.setSample(sample)
    simulation.runSimulation()
    results.append(simulation.getIntensityData())

    # simulation #4
    # all parameters which are matching criteria will be changed
    sample.setParameterValue("*/FormFactorCylinder/height", 10.0*nanometer)
    # both FormFactorPrism3/half_side and FormFactorPrism3/height will be set to 10 nanometer
    sample.setParameterValue("*/FormFactorPrism3/*", 10.0*nanometer)
    simulation.setSample(sample)
    simulation.runSimulation()
    results.append(simulation.getIntensityData())

    return results


def draw_results(results):
    """
    Draw results of several simulations on canvas
    """
    plt.figure(1)
    for nplot, hist in enumerate(results):
        plt.subplot(2, 2, nplot+1)
        plt.imshow(hist.getArray(), norm=matplotlib.colors.LogNorm(1, hist.getMaximum()),
                   extent=[hist.getXmin()/deg, hist.getXmax()/deg, hist.getYmin()/deg, hist.getYmax()/deg])

    plt.show()


if __name__ == '__main__':
    results = run_simulations()
    draw_results(results)


