# 2D lattice with different disorder (IsGISAXS example #6), sum of lattices
import sys, os, numpy

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0], '..', '..', '..', 'lib')
                ))

sys.path.append(os.path.abspath(os.path.join(os.path.split(__file__)[0],'..')))

from libBornAgainCore import *
from utils.show2d import PlotNumpyArray

M_PI = numpy.pi


# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # building simulation
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, -0.2*degree, 0.0*degree)

    sim_params = SimulationParameters()
    sim_params.me_framework = SimulationParameters.DWBA
    sim_params.me_if_approx = SimulationParameters.LMA
    sim_params.me_lattice_type = SimulationParameters.LATTICE
    simulation.setSimulationParameters(sim_params)

    # running simulation and copying data
    OutputData_total = GetOutputData(simulation)
    nbins = 3
    xi_min = 0.0*degree
    xi_max = 240.0*degree
    xi= StochasticSampledParameter(StochasticDoubleGate(xi_min, xi_max), nbins, xi_min, xi_max)
    #for size_t i in range(xi.getNbins()) :
    for i in range(xi.getNbins()) :
        xi_value = xi.getBinValue(i)
        probability = xi.getNormalizedProbability(i)
        p_sample =  buildSample(xi_value)
        simulation.setSample(p_sample)
        simulation.runSimulation()

        single_output = GetOutputData(simulation)
        single_output *= probability
        OutputData_total += single_output

    return OutputData_total


# IsGISAXS6 functional test sample builder for varying xi angle
def buildSample(xi_value):
    n_particle = complex(1.0-6e-4, 2e-8)
    mAmbience = MaterialManager.getHomogeneousMaterial("Air", 1.0, 0.0 )
    mSubstrate = MaterialManager.getHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8 )
    air_layer = Layer(mAmbience)
    substrate_layer = Layer(mSubstrate)
    
    lattice_params = Lattice2DIFParameters()
    lattice_params.m_length_1 = 10.0*nanometer
    lattice_params.m_length_2 = 10.0*nanometer
    lattice_params.m_angle = 90.0*degree
    lattice_params.m_xi = xi_value
    lattice_params.m_domain_size_1 = 20000.0*nanometer
    lattice_params.m_domain_size_2 = 20000.0*nanometer
    lattice_params.m_corr_length_1 = 300.0*nanometer/2.0/M_PI
    lattice_params.m_corr_length_2 = 100.0*nanometer/2.0/M_PI
    p_interference_function = InterferenceFunction2DLattice(lattice_params)
    pdf = FTDistribution2DCauchy (300.0*nanometer/2.0/M_PI, 100.0*nanometer/2.0/M_PI)
    p_interference_function.setProbabilityDistribution(pdf)

    particle_decoration = ParticleDecoration()
    # particle
    ff_cyl = FormFactorCylinder(5.0*nanometer, 5.0*nanometer)
    position = kvector_t(0.0, 0.0, 0.0)
    cylinder = Particle(n_particle, ff_cyl.clone())
    particle_info = PositionParticleInfo( cylinder, position, 1.0)
    particle_decoration.addParticleInfo(particle_info)
    particle_decoration.addInterferenceFunction(p_interference_function)
    air_layer_decorator = LayerDecorator(air_layer, particle_decoration)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer_decorator)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    result = RunSimulation()
    PlotNumpyArray(result)




 
 
