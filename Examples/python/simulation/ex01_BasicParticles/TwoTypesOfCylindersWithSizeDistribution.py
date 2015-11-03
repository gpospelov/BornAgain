"""
Mixture cylinder particles with different size distribution 
"""
import numpy
import matplotlib
from matplotlib import pyplot as plt
from bornagain import *

phi_min, phi_max = 0.0, 2.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample():
    """
    Build and return the sample representing cylinder particles with different size distribution.
    """
    # defining materials
    m_air = HomogeneousMaterial("Air", 0.0, 0.0)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    nparticles = 150
    nfwhm = 3.0

    # collection of particles #1
    radius1 = 5.0*nanometer
    height1 = radius1
    sigma1 = radius1*0.2

    cylinder_ff1 = FormFactorCylinder(radius1, height1)
    cylinder1 = Particle(m_particle, cylinder_ff1)

    gauss_distr1 = DistributionGaussian(radius1, sigma1)

    par_distr1 = ParameterDistribution("*/radius", gauss_distr1, nparticles, nfwhm)
    part_coll1 = ParticleDistribution(cylinder1, par_distr1)

    # collection of particles #2
    radius2 = 10.0*nanometer
    height2 = radius2
    sigma2 = radius2*0.02

    cylinder_ff2 = FormFactorCylinder(radius2, height2)
    cylinder2 = Particle(m_particle, cylinder_ff2)

    gauss_distr2 = DistributionGaussian(radius2, sigma2)

    par_distr2 = ParameterDistribution("*/radius", gauss_distr2, nparticles, nfwhm)
    part_coll2 = ParticleDistribution(cylinder2, par_distr2)

    # assembling the sample
    particle_layout = ParticleLayout()
    particle_layout.addParticle(part_coll1, 0.95)
    particle_layout.addParticle(part_coll2, 0.05)

    air_layer = Layer(m_air)
    air_layer.addLayout(particle_layout)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = GISASSimulation()
    simulation.setDetectorParameters(200, phi_min*degree, phi_max*degree, 200, alpha_min*degree, alpha_max*degree)
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
    result = simulation.getIntensityData()

    # showing the result
    im = plt.imshow(result.getArray(),
                    norm=matplotlib.colors.LogNorm(1.0, result.getMaximum()),
                    extent=[result.getXmin()/deg, result.getXmax()/deg, result.getYmin()/deg, result.getYmax()/deg],
                    aspect='auto')
    cb = plt.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    plt.show()


if __name__ == '__main__':
    run_simulation()




