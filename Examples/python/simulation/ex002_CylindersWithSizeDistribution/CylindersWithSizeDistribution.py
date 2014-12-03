# Mixture cylinder particles with different size distribution (IsGISAXS example ex-2)
import numpy
import matplotlib
import pylab
from libBornAgainCore import *


def get_sample():
    """
    Build and return the sample representing cylinder particles with different size distribution.
    """
    # defining materials
    m_air = HomogeneousMaterial("Air", 0.0, 0.0)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    radius1 = 5.0*nanometer
    radius2 = 10.0*nanometer
    height1 = radius1
    height2 = radius2
    cylinder_ff1 = FormFactorCylinder(radius1, height1)
    cylinder1 = Particle(m_particle, cylinder_ff1)
    cylinder_ff2 = FormFactorCylinder(radius2, height2)
    cylinder2 = Particle(m_particle, cylinder_ff2)
    nbins = 150
    sigma1 = radius1*0.2
    sigma2 = radius2*0.02

    nfwhm = 3
    gauss_distr1 = DistributionGaussian(radius1, sigma1)
    gauss_distr2 = DistributionGaussian(radius2, sigma2)

    #Building nano particles
    particle_layout = ParticleLayout()

    builder = ParticleBuilder()
    builder.setPrototype(cylinder1, "/Particle/FormFactorCylinder/radius", gauss_distr1, nbins, nfwhm, 0.95)
    builder.plantParticles(particle_layout)
    builder.setPrototype(cylinder2, "/Particle/FormFactorCylinder/radius", gauss_distr2, nbins, nfwhm, 0.05)
    builder.plantParticles(particle_layout)

    print cylinder1.createParameterTree()

    interference = InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)

    air_layer = Layer(m_air)
    air_layer.addLayout(particle_layout)

    multi_layer = MultiLayer()
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




