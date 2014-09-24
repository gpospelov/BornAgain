'''
Simulation demo: Cylinder form factor without interference
'''

import numpy, pylab, matplotlib

from libBornAgainCore import *

M_PI = numpy.pi

# ----------------------------------
# describe sample and run simulation 
# ----------------------------------
def RunSimulation():
    # defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0 )
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8 )
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8 )

    # particle 1
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(mParticle, cylinder_ff)
    position = kvector_t(0.0, 0.0, 0.0)
    particle_info = PositionParticleInfo(cylinder, position, 1.0)
    particle_layout = ParticleLayout()
    particle_layout.addParticleInfo(particle_info)
    # particle 2
    position_2 = kvector_t(5.0*nanometer, 5.0*nanometer, 0.0)
    particle_info.setPosition(position_2)
    particle_layout.addParticleInfo(particle_info)

    # set lattice parameters
    lattice_params = Lattice2DIFParameters()
    lattice_params.m_length_1 = 10.0*nanometer
    lattice_params.m_length_2 = 10.0*nanometer
    lattice_params.m_angle = 90.0*degree
    lattice_params.m_xi = 0.0*degree

    # interference function
    interference = InterferenceFunction2DLattice(lattice_params)
    pdf = FTDistribution2DCauchy(300.0*nanometer/2.0/M_PI, 100.0*nanometer/2.0/M_PI)
    interference.setProbabilityDistribution(pdf)
    particle_layout.addInterferenceFunction(interference)

    # top air layer
    air_layer = Layer(mAmbience)
    air_layer.setLayout(particle_layout)

    # substrate layer
    substrate_layer = Layer(mSubstrate, 0)

    # multilayer
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)

    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100, -2.0*degree, 2.0*degree, 100, 0.0*degree, 4.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)

    # simulation parameters
    sim_params= SimulationParameters()
    sim_params.me_framework = SimulationParameters.DWBA
    sim_params.me_if_approx = SimulationParameters.LMA
    simulation.setSimulationParameters(sim_params)

    # run simulation
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    return simulation.getIntensityData().getArray()


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    result = RunSimulation()
    im = pylab.imshow(numpy.rot90(result+1, 1),
                 norm=matplotlib.colors.LogNorm(),
                 extent=[-2.0, 2.0, 0, 4.0])
    pylab.colorbar(im)
    pylab.xlabel(r'$\phi_f$', fontsize=20)
    pylab.ylabel(r'$\alpha_f$', fontsize=20)
    pylab.show()


 
 
