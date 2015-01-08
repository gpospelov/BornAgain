"""
Infinitely long boxes on a 1D lattice
"""
import numpy
import matplotlib
import pylab
from bornagain import *

phi_min, phi_max = -1.0, 1.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample():
    """
    Build and return the sample representing infinitely long boxes on a 1D lattice
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    lattice_length = 30.0*nanometer
    lattice_rotation_angle = 0.0*degree
    interference = InterferenceFunction1DLattice(lattice_length, lattice_rotation_angle)
    pdf = FTDistribution1DCauchy(20./2./numpy.pi*nanometer)
    interference.setProbabilityDistribution(pdf)

    infbox_ff = FormFactorInfLongBox(10*nanometer, 15.0*nanometer)
    infbox = Particle(m_particle, infbox_ff)
    transform = Transform3D.createRotateZ(25.0*degree)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(infbox, transform)
    particle_layout.addInterferenceFunction(interference)

    # assembling the sample
    air_layer = Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(m_substrate)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = Simulation()
    simulation.setDetectorParameters(200, phi_min*degree, phi_max*degree, 200, alpha_min*degree, alpha_max*degree)
    simulation.setBeamParameters(24.0*angstrom, 0.2*degree, 0.0*degree)
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
