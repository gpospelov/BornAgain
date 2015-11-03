"""
 Sample from the article D. Babonneau et. al., Phys. Rev. B 85, 235415, 2012 (Fig.3)
"""
import numpy
import matplotlib
from matplotlib import pyplot as plt
from bornagain import *

phi_min, phi_max = -1.5, 1.5
alpha_min, alpha_max = 0.0, 2.5


def get_sample():
    """
    Build and return the sample representing the triangular ripple in the framework of the 1D Paracrystal.
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    ripple2_ff = FormFactorRipple2(100*nanometer, 20*nanometer, 4*nanometer, -3.0*nanometer)
    ripple = Particle(m_particle, ripple2_ff)

    particle_layout = ParticleLayout()
    particle_layout.addParticle(ripple, 1.0)

    interference = InterferenceFunction2DLattice(200.0*nanometer, 50.0*nanometer, 90.0*degree, 0.0*degree)
    pdf = FTDistribution2DGauss(1000.*nanometer/2./numpy.pi, 100.*nanometer/2./numpy.pi)
    interference.setProbabilityDistribution(pdf)
    particle_layout.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(m_substrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)

    return multi_layer


def get_simulation():
    """
    characterizing the input beam and output detector
    """
    simulation = GISASSimulation()
    simulation.setDetectorParameters(400, phi_min*degree, phi_max*degree, 400, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(1.6*angstrom, 0.3*degree, 0.0*degree)
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

