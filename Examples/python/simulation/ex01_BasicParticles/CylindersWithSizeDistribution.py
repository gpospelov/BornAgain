"""
Cylinders with size distribution
"""
import numpy
import matplotlib
from matplotlib import pyplot as plt
from bornagain import *

phi_min, phi_max = 0.0, 2.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample():
    """
    Build and return the sample to calculate cylinder formfactor in Born approximation.
    Cylinders have size distribution.
    """
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # cylindrical particle
    radius = 5*nanometer
    height = radius
    cylinder_ff = FormFactorCylinder(radius, height)
    cylinder = Particle(m_particle, cylinder_ff)

    # collection of particles with size distribution
    nparticles = 100
    nfwhm = 2.0
    sigma = 0.2*radius

    gauss_distr = DistributionGaussian(radius, sigma)
    par_distr = ParameterDistribution("*/radius", gauss_distr, nparticles, nfwhm)
    # by uncommenting the line below the height of cylinders can be scaled proportionally to the radius
    #par_distr.linkParameter("*/height")
    part_coll = ParticleDistribution(cylinder, par_distr)

    # assembling the sample
    particle_layout = ParticleLayout()
    particle_layout.addParticle(part_coll)

    air_layer = Layer(m_ambience)
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
    sample.printSampleTree()
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


