"""
 Sample from the article D. Babonneau et. al., Phys. Rev. B 85, 235415, 2012 (Fig.3)
"""

import numpy
import matplotlib
import pylab
from math import degrees
from libBornAgainCore import *


def plot_with_pylab(data):
    result = data.getArray() + 1  # for log scale
    axis_phi = data.getAxis(0)
    axis_alpha = data.getAxis(1)

    pylab.imshow(numpy.rot90(result, 1), norm=matplotlib.colors.LogNorm(),
                 extent=[degrees(axis_phi.getMin()), degrees(axis_phi.getMax()), degrees(axis_alpha.getMin()), degrees(axis_alpha.getMax())])
    pylab.xlabel(r'$\phi_f$', fontsize=20)
    pylab.ylabel(r'$\alpha_f$', fontsize=20)

    pylab.show()


def get_sample():
    """
    Build and return the sample representing the triangular ripple in the framework of the 1D Paracrystal.
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0 )
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8 )
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8 )

    # collection of particles
    ripple2_ff = FormFactorRipple2(100*nanometer, 20*nanometer, 4*nanometer, -3.0*nanometer)
    ripple = Particle(m_particle, ripple2_ff)

    particle_layout = ParticleLayout()
    particle_layout.addParticle(ripple, 0.0, 1.0)

    interference = InterferenceFunction1DParaCrystal (1e7*nanometer, 20*nanometer, 4*nanometer)
    particle_layout.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(m_ambience)
    air_layer.setLayout(particle_layout)
    substrate_layer = Layer(m_substrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)

    return multi_layer


def get_simulation():
    """
    characterizing the input beam and output detector
    """
    simulation = Simulation()
    simulation.setDetectorParameters(400,-1.5*degree, 1.5*degree, 400, 0.0*degree, 2.5*degree, True)
    simulation.setBeamParameters(1.6*angstrom, 0.3*degree, 0.0*degree)

    return simulation


def run_simulation():
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    result = simulation.getIntensityData()
    return result


if __name__ == '__main__':
    data = run_simulation()
    plot_with_pylab(data)

