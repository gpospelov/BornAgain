import sys
#sys.path.append('/usr/local/lib')


import pylab
import matplotlib
import numpy
import os

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0], '..', '..', 'lib')
                ))
import libBornAgainCore as ba


# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    mAmbience = ba.MaterialManager.getHomogeneousMaterial("Air", 0.0, 0.0 )
    mSubstrate = ba.MaterialManager.getHomogeneousMaterial("Substrate", 6e-6, 2e-8 )

    # collection of particles
    n_particle = complex(1.0-6e-4, 2e-8)
    mParticle = ba.MaterialManager.getHomogeneousMaterial("Particle", n_particle )
    
    sphere_ff = ba.FormFactorSphere(8 * ba.nanometer, 8 * ba.nanometer)
    #sphere = ba.Particle(n_particle, sphere_ff)
    sphere = ba.Particle(mParticle, sphere_ff)

    interference = ba.InterferenceFunction2DParaCrystal.createHexagonal(20.0*ba.nanometer, 0.0,20.0*ba.micrometer, 20.0*ba.micrometer)
    #pdf = ba.FTDistribution2DCauchy(1.0*ba.nanometer, 1.0*ba.nanometer)
    #interference.setProbabilityDistributions(pdf, pdf)

    particle_decoration = ba.ParticleDecoration()
    particle_decoration.addParticle(sphere, 0., 1.)
    print 'before addInterferenceFunction'
    particle_decoration.addInterferenceFunction(interference)
    print 'after addInterferenceFunction'

    # air layer with particles and substrate form multi layer
    air_layer = ba.Layer(mAmbience)
    air_layer.setDecoration(particle_decoration)
    substrate_layer = ba.Layer(mSubstrate, 0)
    
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)

    # build and run experiment
    simulation = ba.Simulation()
    simulation.setDetectorParameters(487/5, -1.4 * ba.degree, 0.15 * ba.degree, 
                                     407/5, 0. * ba.degree, 1.4 * ba.degree, True)
    simulation.setBeamParameters(.96 * ba.angstrom, 0.5 * ba.degree, 0.0 * ba.degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    ## intensity data
    return ba.GetOutputData(simulation)


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    result = RunSimulation() + 1 # log scale
    pylab.imshow(numpy.rot90(result, 1), 
                 norm=matplotlib.colors.LogNorm(), 
                 extent=[-1.4, .15, 0, 1.4])
    pylab.show()