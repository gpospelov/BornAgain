'''
Simulation demo: Size Space Coupling Approximation
'''

import numpy, pylab, matplotlib

from libBornAgainCore import *

# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    mAir = MaterialManager.getHomogeneousMaterial("Air", 0.0, 0.0)
    mSubstrate = MaterialManager.getHomogeneousMaterial("Substrate", 6e-6, 2e-8)
    mParticle = MaterialManager.getHomogeneousMaterial("Particle", 6e-4, 2e-8)
    mLayer = MaterialManager.getHomogeneousMaterial("Layer", 2e-5, 2e-8)

    # collection of particles
    cylinder_ff1 = FormFactorCylinder(5 * nanometer, 2 * nanometer)
    cylinder_ff2 = FormFactorCylinder(6 * nanometer, 3 * nanometer)
    cylinder_ff3 = FormFactorCylinder(7 * nanometer, 4 * nanometer)
    cylinder1 = Particle(mParticle, cylinder_ff1)
    cylinder2 = Particle(mParticle, cylinder_ff2)
    cylinder3 = Particle(mParticle, cylinder_ff3)
    particle_decoration = ParticleDecoration()
    particle_decoration.addParticle(cylinder1)
    particle_decoration.addParticle(cylinder2)
    particle_decoration.addParticle(cylinder3)
    interference = InterferenceFunction1DParaCrystal(5 * nanometer, 1 * nanometer)
    # set coupling between size and space
    interference.setKappa(2)
    particle_decoration.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(mAir)
    air_layer.setDecoration(particle_decoration)
    substrate_layer = Layer(mSubstrate)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    roughness = LayerRoughness(10 * nanometer, 3, 20 * nanometer)
    multi_layer.addLayerWithTopRoughness(substrate_layer, roughness)

    # simulation parameters
    sim_params = SimulationParameters()
#    sim_params.me_if_approx = SimulationParameters.SSCA
    sim_params.me_if_approx = SimulationParameters.DA
    # build and run experiment
    simulation = Simulation()
    simulation.setSimulationParameters(sim_params)
    simulation.setDetectorParameters(100, -4.0 * degree, 4.0 * degree, 100, 0.0 * degree, 8.0 * degree)
    simulation.setBeamParameters(1.0 * angstrom, 0.2 * degree, 0.0 * degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    # intensity data
    return simulation.getIntensityData().getArray()


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    result = RunSimulation() + 1 # for log scale
    im = pylab.imshow(numpy.rot90(result, 1),
                 norm=matplotlib.colors.LogNorm(),
                 extent=[-4.0, 4.0, 0, 8.0])
    pylab.colorbar(im)
    pylab.xlabel(r'$\phi_f$', fontsize=20)
    pylab.ylabel(r'$\alpha_f$', fontsize=20)
    pylab.show()
