'''
Simulation demo: movie of growing particles on substrate
'''

import os, sys, numpy, pylab, matplotlib

from libBornAgainCore import *

Nframes = 50

radius = 1
height = 4
distance = 5

# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    mAir = MaterialManager.getHomogeneousMaterial("Air", 0.0, 0.0)
    mSubstrate = MaterialManager.getHomogeneousMaterial("Substrate", 6e-6, 2e-8)
    mParticle = MaterialManager.getHomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = FormFactorCylinder(height, radius)
    cylinder = Particle(mParticle, cylinder_ff)
    particle_decoration = ParticleDecoration()
    particle_decoration.addParticle(cylinder)

    # interference function
    interference = InterferenceFunction1DParaCrystal(distance, 3 * nanometer)
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

def SetParameters(i):
    global radius
    global height
    global distance
    radius = (1. + (3.0/Nframes)*i) * nanometer
    height = (1. + (4.0/Nframes)*i) * nanometer
    distance = (10. - (1.0/Nframes)*i) * nanometer

#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    files = []
    fig = pylab.figure(figsize=(5,5))
    ax = fig.add_subplot(111)
    for i in range(Nframes):
        SetParameters(i)
        result = RunSimulation() + 1 # for log scale
        ax.cla()
        im = ax.imshow(numpy.rot90(result, 1), vmax=1e3,
                 norm=matplotlib.colors.LogNorm(),
                 extent=[-4.0, 4.0, 0, 8.0])
        pylab.xlabel(r'$\phi_f$', fontsize=20)
        pylab.ylabel(r'$\alpha_f$', fontsize=20)
        if i==0:
            pylab.colorbar(im)
        fname = '_tmp%03d.png'%i
        print 'Saving frame', fname
        fig.savefig(fname)
        files.append(fname)
    os.system("mencoder 'mf://_tmp*.png' -mf type=png:fps=10 -ovc lavc -lavcopts vcodec=wmv2 -oac copy -o animation.mpg")
    print 'Removing temporary files'
    os.system("rm _tmp*")
