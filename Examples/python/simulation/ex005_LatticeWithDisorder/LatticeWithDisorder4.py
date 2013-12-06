# 2D lattice with different disorder (IsGISAXS example #6), sum of lattices
import numpy
import matplotlib
import pylab
from libBornAgainCore import *

M_PI = numpy.pi


def get_sample(xi_value):
    """
    Build and return the sample representing 2D lattice with different disorder
    rotated lattice
    """
    m_ambience = MaterialManager.getHomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = MaterialManager.getHomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = MaterialManager.getHomogeneousMaterial("Particle", 6e-4, 2e-8)

    air_layer = Layer(m_ambience)
    substrate_layer = Layer(m_substrate)

    lattice_params = Lattice2DIFParameters()
    lattice_params.m_length_1 = 10.0*nanometer
    lattice_params.m_length_2 = 10.0*nanometer
    lattice_params.m_angle = 90.0*degree
    lattice_params.m_xi = xi_value
    p_interference_function = InterferenceFunction2DLattice(lattice_params)
    pdf = FTDistribution2DCauchy(300.0*nanometer/2.0/M_PI, 100.0*nanometer/2.0/M_PI)
    p_interference_function.setProbabilityDistribution(pdf)

    particle_decoration = ParticleDecoration()
    # particle
    ff_cyl = FormFactorCylinder(5.0*nanometer, 5.0*nanometer)
    position = kvector_t(0.0, 0.0, 0.0)
    cylinder = Particle(m_particle, ff_cyl.clone())
    particle_info = PositionParticleInfo(cylinder, position, 1.0)
    particle_decoration.addParticleInfo(particle_info)
    particle_decoration.addInterferenceFunction(p_interference_function)

    air_layer.setDecoration(particle_decoration)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = Simulation()
    simulation.setDetectorParameters(100, 0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    sim_params = SimulationParameters()
    sim_params.me_framework = SimulationParameters.DWBA
    sim_params.me_if_approx = SimulationParameters.LMA
    sim_params.me_lattice_type = SimulationParameters.LATTICE
    simulation.setSimulationParameters(sim_params)
    return simulation


def run_simulation():
    """
    Run several simulations, sum up intensities from different rotated lattices and plot results
    """

    simulation = get_simulation()

    OutputData_total = simulation.getIntensityData().getArray()
    nbins = 3
    xi_min = 0.0*degree
    xi_max = 240.0*degree
    xi= StochasticSampledParameter(StochasticDoubleGate(xi_min, xi_max), nbins, xi_min, xi_max)
    for i in range(xi.getNbins()):
        xi_value = xi.getBinValue(i)
        probability = xi.getNormalizedProbability(i)
        p_sample = get_sample(xi_value)
        simulation.setSample(p_sample)
        simulation.runSimulation()

        single_output = simulation.getIntensityData().getArray()
        single_output *= probability
        OutputData_total += single_output

    result = OutputData_total + 1  # for log scale
    pylab.imshow(numpy.rot90(result, 1), norm=matplotlib.colors.LogNorm(), extent=[0.0, 2.0, 0, 2.0])
    pylab.show()


if __name__ == '__main__':
    run_simulation()

