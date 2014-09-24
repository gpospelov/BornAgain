# 2D lattice with different disorder (IsGISAXS example #6), rotated lattice
import numpy
import matplotlib
import pylab
from libBornAgainCore import *

M_PI = numpy.pi


def get_sample():
    """
    Build and return the sample representing 2D lattice with different disorder
    rotated lattice
    """
    # defining materials
    m_ambience = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    lattice_params = Lattice2DIFParameters()
    lattice_params.m_length_1 = 10.0*nanometer
    lattice_params.m_length_2 = 10.0*nanometer
    lattice_params.m_angle = 90.0*degree
    lattice_params.m_xi = 30.0*degree
    interference = InterferenceFunction2DLattice(lattice_params)
    pdf = FTDistribution2DCauchy(300.0*nanometer/2.0/M_PI, 100.0*nanometer/2.0/M_PI)
    pdf.setGamma(30.0*degree)
    interference.setProbabilityDistribution(pdf)

    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(m_particle, cylinder_ff)
    position = kvector_t(0.0, 0.0, 0.0)
    particle_layout = ParticleLayout()
    particle_info =  PositionParticleInfo(cylinder, position, 1.0)
    particle_layout.addParticleInfo(particle_info)
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
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = Simulation()
    simulation.setDetectorParameters(100, 0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    sim_params = SimulationParameters()
    sim_params.me_framework = SimulationParameters.DWBA
    sim_params.me_if_approx = SimulationParameters.LMA
    simulation.setSimulationParameters(sim_params)

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
