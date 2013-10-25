'''
Simulation demo: Cylinder and/or sphere on substrate
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

    # collection of particles
    cylinder_ff = FormFactorCylinder(5 * nanometer, 2 * nanometer)
    cylinder = Particle(mParticle, cylinder_ff)
    sphere_ff = FormFactorFullSphere(4 * nanometer)
    sphere = Particle(mParticle, sphere_ff)
    particle_decoration = ParticleDecoration()
    particle_decoration.addParticle(cylinder)
    particle_decoration.addParticle(sphere)
    interference = InterferenceFunction1DParaCrystal(20 * nanometer, 2 * nanometer)
    particle_decoration.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(mAir)
    air_layer.setDecoration(particle_decoration)
    substrate_layer = Layer(mSubstrate)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)

    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100, -4.0 * degree, 4.0 * degree, 100, 0.0 * degree, 8.0 * degree)
    simulation.setBeamParameters(1.0 * angstrom, 0.2 * degree, 0.0 * degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    # intensity data
    return GetOutputData(simulation)


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
