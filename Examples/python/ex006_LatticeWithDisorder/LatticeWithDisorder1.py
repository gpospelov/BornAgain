# 2D lattice with different disorder (IsGISAXS example #6)
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
    # defining materials
    mAmbience = MaterialManager.getHomogeneousMaterial("Air", 0.0, 0.0 )
    mSubstrate = MaterialManager.getHomogeneousMaterial("Substrate", 6e-6, 2e-8 )
    # collection of particles
    lattice_params = Lattice2DIFParameters()
    lattice_params.m_length_1 = 10.0*nanometer
    lattice_params.m_length_2 = 10.0*nanometer
    lattice_params.m_angle = 90.0*degree
    lattice_params.m_xi = 0.0*degree
    lattice_params.m_domain_size_1 = 20000.0*nanometer
    lattice_params.m_domain_size_2 = 20000.0*nanometer
    lattice_params.m_corr_length_1 = 300.0*nanometer/2.0/M_PI
    lattice_params.m_corr_length_2 = 100.0*nanometer/2.0/M_PI

    interference = InterferenceFunction2DLattice(lattice_params)
    pdf = FTDistribution2DCauchy(300.0*nanometer/2.0/M_PI, 100.0*nanometer/2.0/M_PI)
    interference.setProbabilityDistribution(pdf)

    n_particle = complex(1.0-6e-4, 2e-8)
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(n_particle, cylinder_ff.clone())
    position = kvector_t(0.0, 0.0, 0.0)
    particle_decoration = ParticleDecoration()
    particle_info =  PositionParticleInfo(cylinder, position, 1.0)
    particle_decoration.addParticleInfo(particle_info)
    particle_decoration.addInterferenceFunction(interference)

    air_layer = Layer(mAmbience)
    air_layer_decorator = LayerDecorator(air_layer, particle_decoration)
    substrate_layer = Layer(mSubstrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer_decorator)
    multi_layer.addLayer(substrate_layer)
    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)

    sim_params= SimulationParameters()
    sim_params.me_framework = SimulationParameters.DWBA
    sim_params.me_if_approx = SimulationParameters.LMA
    sim_params.me_lattice_type = SimulationParameters.LATTICE
    simulation.setSimulationParameters(sim_params)

    simulation.setSample(multi_layer)
    simulation.runSimulation()
    return GetOutputData(simulation)


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    result = RunSimulation()
    PlotNumpyArray(result)




 
 
