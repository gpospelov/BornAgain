"""
Cosine ripple at 2D lattice
"""
import numpy
import matplotlib
import pylab
from bornagain import *

phi_min, phi_max = -1.5, 1.5
alpha_min, alpha_max = 0.0, 2.5


def get_sample():
    """
    Build and return the sample representing the cosine ripple in the framework of the 1D Paracrystal.
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    ripple1_ff = FormFactorRipple1(100*nanometer, 20*nanometer, 4*nanometer)
    ripple = Particle(m_particle, ripple1_ff)

    particle_layout = ParticleLayout()
    particle_layout.addParticle(ripple, 0.0, 1.0)

    interference = InterferenceFunction2DLattice(200.0*nanometer, 50.0*nanometer, 90.0*degree, 0.0*degree)
    pdf = FTDistribution2DCauchy(1000.*nanometer/2./numpy.pi, 100.*nanometer/2./numpy.pi)
    interference.setProbabilityDistribution(pdf)
    particle_layout.addInterferenceFunction(interference)

    # assemble the sample
    air_layer = Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(m_substrate)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)

    return multi_layer


def get_simulation():
    """
    characterizing the input beam and output detector
    """
    simulation = Simulation()
    simulation.setDetectorParameters(100, phi_min*degree, phi_max*degree, 100, alpha_min*degree, alpha_max*degree)
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
    result = simulation.getIntensityData().getArray() + 1  # for log scale

    # showing the result
    im = pylab.imshow(numpy.rot90(result, 1), norm=matplotlib.colors.LogNorm(),
                      extent=[phi_min, phi_max, alpha_min, alpha_max], aspect='auto')
    pylab.colorbar(im)
    pylab.xlabel(r'$\phi_f$', fontsize=16)
    pylab.ylabel(r'$\alpha_f$', fontsize=16)
    pylab.show()


if __name__ == '__main__':
    run_simulation()

