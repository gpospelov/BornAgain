# Cylinder formfactor in DWBA with beam divergence
import numpy
import matplotlib
import pylab
from libBornAgainCore import *

def get_sample():
    """
    Build and return the sample to calculate cylinder formfactor in Distorted Wave Born Approximation.
    """
    # defining materials
    m_ambience = MaterialManager.getHomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = MaterialManager.getHomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = MaterialManager.getHomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(m_particle, cylinder_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 0.0, 1.0)
    interference = InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)
    air_layer = Layer(m_ambience)
    air_layer.setLayout(particle_layout)
    substrate_layer = Layer(m_substrate, 0)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer

def get_simulation():
    """
    Create and return GISAXS simulation with beam (+ divergence) and detector defined
    """
    simulation = Simulation()
    simulation.setDetectorParameters(100, 0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    wavelength_distr = DistributionLogNormal(1.0*angstrom, 0.1)
    alpha_distr = DistributionGaussian(-0.2*degree, 0.1*degree)
    phi_distr = DistributionGaussian(0.0*degree, 0.1*degree)
    simulation.addParameterDistribution("*/Beam/wavelength", wavelength_distr, 5)
    simulation.addParameterDistribution("*/Beam/alpha", alpha_distr, 5)
    simulation.addParameterDistribution("*/Beam/phi", phi_distr, 5)
    return simulation


def run_simulation():
    """
    Run simulation and plot results
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.printParameters()
    simulation.runSimulation()
    result = simulation.getIntensityData().getArray()
    pylab.imshow(numpy.rot90(result + 1, 1), norm=matplotlib.colors.LogNorm(), extent=[0.0, 2.0, 0, 2.0])
    pylab.colorbar()
    pylab.show()

if __name__ == '__main__':
    run_simulation()


