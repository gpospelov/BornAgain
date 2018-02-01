"""
Working with sample parameters.

This example shows how to create a sample with fixed parameters, and then change
these parameters on the fly during runtime. The example doesn't contain any
fitting; it serves as a gentle introduction to other fitting examples.
"""

from __future__ import print_function
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample():
    """
    Returns a sample with uncorrelated cylinders and prisms on a substrate.
    Parameter set is fixed.
    """
    # defining materials
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = ba.FormFactorCylinder(5*nm, 5*nm)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    prism_ff = ba.FormFactorPrism3(5*nm, 5*nm)
    prism = ba.Particle(m_particle, prism_ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 0.5)
    particle_layout.addParticle(prism, 0.5)
    interference = ba.InterferenceFunctionNone()
    particle_layout.setInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = ba.Layer(m_air)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate, 0)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    return simulation


def run_simulation():
    """
    Runs simulations for the sample with different sample parameters.
    """

    sample = get_sample()
    print("The tree structure of the sample")
    print(sample.treeToString())

    print("The sample contains following parameters ('name':value)")
    print(sample.parametersToString())

    simulation = get_simulation()

    results = {}

    # simulation #1
    # initial sample is used
    simulation.setSample(sample)
    simulation.runSimulation()
    results[0] = simulation.result()

    # simulation #2
    # one sample parameter (cylinder height) is changed using exact parameter name
    sample.setParameterValue(
        "/MultiLayer/Layer0/ParticleLayout/Particle0/Cylinder/Height",
        10.0*nm)

    simulation.setSample(sample)
    simulation.runSimulation()
    results[1] = simulation.result()

    # simulation #3
    # all parameters matching criteria will be changed (cylinder height in this case)
    sample.setParameterValue("*/Cylinder/Height", 100.0*nm)
    simulation.setSample(sample)
    simulation.runSimulation()
    results[2] = simulation.result()

    # simulation #4
    # all parameters which are matching criteria will be changed
    sample.setParameterValue("*/Cylinder/Height", 10.0*nm)
    sample.setParameterValue("*/Prism3/*", 10.0*nm)
    simulation.setSample(sample)
    simulation.runSimulation()
    results[3] = simulation.result()

    return results


def plot(results):
    """
    Draw results of several simulations on canvas
    """

    from matplotlib import pyplot as plt
    plt.figure(figsize=(12.80, 10.24))

    for nplot, result in results.items():
        plt.subplot(2, 2, nplot+1)
        ba.plot_colormap(result)
    plt.show()


if __name__ == '__main__':
    results = run_simulation()
    plot(results)
