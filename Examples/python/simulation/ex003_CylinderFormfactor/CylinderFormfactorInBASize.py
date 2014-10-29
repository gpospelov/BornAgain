# Cylinder formfactor in BA with size distribution (IsGISAXS example #3)
import numpy
import matplotlib
import pylab
from libBornAgainCore import *


def get_sample():
    """
    Build and return the sample to calculate cylinder formfactor in Born approximation.
    Cylinders have size distribution.
    """
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    multi_layer = MultiLayer()

    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    particle_layout = ParticleLayout()
    # preparing prototype of nano particle
    radius = 5*nanometer
    sigma = 0.2*radius
    nano_particle = Particle(m_particle, cylinder_ff)
    # radius of nanoparticles will be sampled with gaussian probability
    nbins = 100
    nfwhm = 2
    stochastic_gaussian = StochasticDoubleGaussian(radius, sigma)
    par = StochasticSampledParameter(stochastic_gaussian, nbins, nfwhm)

    builder = ParticleBuilder()
    builder.setPrototype(nano_particle, "/Particle/FormFactorCylinder/radius", par)
    builder.plantParticles(particle_layout)
    interference = InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)

    air_layer = Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    multi_layer.addLayer(air_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = Simulation()
    simulation.setDetectorParameters(100, 0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree)
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


