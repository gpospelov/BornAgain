# IsGISAXS011 example: Core shell nanoparticles

import numpy
import matplotlib
import pylab
from libBornAgainCore import *


def get_sample():
    """
    Build and return the sample representing cylinders and pyramids on top of
    substrate without interference.
    """
    # defining materials
    m_air = MaterialManager.getHomogeneousMaterial("Air", 0.0, 0.0 )
    m_shell = MaterialManager.getHomogeneousMaterial("Shell", 1e-4, 2e-8 )
    m_core = MaterialManager.getHomogeneousMaterial("Core", 6e-5, 2e-8 )

    # collection of particles
    parallelepiped1_ff = FormFactorBox(16*nanometer, 16*nanometer, 8*nanometer)
    parallelepiped2_ff = FormFactorBox(12*nanometer, 12*nanometer, 7*nanometer)
    shell_particle = Particle(m_shell, parallelepiped1_ff)
    core_particle = Particle(m_core, parallelepiped2_ff)
    core_position = kvector_t(0.0, 0.0, 0.0)

    particle = ParticleCoreShell(shell_particle, core_particle, core_position)
    particle_layout= ParticleLayout()
    particle_layout.addParticle(particle)
    interference = InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)

    air_layer = Layer(m_air)
    air_layer.setLayout(particle_layout)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)

    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)

    return simulation


def run_simulation():
    """
    Run simulation and plot results
    """

    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    result = simulation.getIntensityData().getArray() + 1  # for log scale
    pylab.imshow(numpy.rot90(result, 1), norm=matplotlib.colors.LogNorm(), extent=[0.0, 2.0, 0, 2.0])
    pylab.show()


if __name__ == '__main__':
    run_simulation()
