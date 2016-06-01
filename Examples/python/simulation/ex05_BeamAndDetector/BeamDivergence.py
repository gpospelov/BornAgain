"""
Cylinder form factor in DWBA with beam divergence
"""
import numpy
import matplotlib
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import degree, angstrom, nanometer

phi_min, phi_max = 0.0, 2.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample():
    """
    Build and return the sample to calculate cylinder formfactor in Distorted Wave Born Approximation.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = ba.FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)

    # assembling the sample
    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam (+ divergence) and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, phi_min*degree, phi_max*degree, 100, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    wavelength_distr = ba.DistributionLogNormal(1.0*angstrom, 0.1)
    alpha_distr = ba.DistributionGaussian(0.2*degree, 0.1*degree)
    phi_distr = ba.DistributionGaussian(0.0*degree, 0.1*degree)
    simulation.addParameterDistribution("*/Beam/Wavelength", wavelength_distr, 5)
    simulation.addParameterDistribution("*/Beam/Alpha", alpha_distr, 5)
    simulation.addParameterDistribution("*/Beam/Phi", phi_distr, 5)
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

    result = simulation.getIntensityData()

    # showing the result
    im = plt.imshow(result.getArray(),
                    norm=matplotlib.colors.LogNorm(1.0, result.getMaximum()),
                    extent=[result.getXmin()/degree, result.getXmax()/degree, result.getYmin()/degree, result.getYmax()/degree],
                    aspect='auto')
    cb = plt.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    plt.show()


if __name__ == '__main__':
    run_simulation()


