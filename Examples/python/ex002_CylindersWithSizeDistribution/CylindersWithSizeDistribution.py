# IsGISAXS02 example: Mixture cylinder particles with different size distribution
import sys, os, numpy

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0], '..', '..', '..', 'lib')
                ))

sys.path.append(os.path.abspath(os.path.join(os.path.split(__file__)[0],'..')))

from libBornAgainCore import *
from utils.show2d import PlotNumpyArray

# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    mAmbience = MaterialManager.getHomogeneousMaterial("Air", 0.0, 0.0 )
    # collection of particles
    n_particle = complex(1.0-6e-4, 2e-8)
    radius1 = 5.0*nanometer
    radius2 = 10.0*nanometer
    height1 = radius1
    height2 = radius2
    cylinder_ff1 = FormFactorCylinder(height1, radius1)
    cylinder1 = Particle(n_particle, cylinder_ff1)
    cylinder_ff2 = FormFactorCylinder(height2, radius2)
    cylinder2 = Particle(n_particle, cylinder_ff2)  
    nbins = 150
    sigma1 = radius1*0.2
    sigma2 = radius2*0.02

    nfwhm = 3
    #to have xmin=average-nfwhm*FWHM, xmax=average+nfwhm*FWHM
    #(nfwhm = xR/2, where xR is what is defined in isgisaxs *.inp file)
    stochastic_gaussian1 = StochasticDoubleGaussian(radius1, sigma1)
    stochastic_gaussian2 = StochasticDoubleGaussian(radius2, sigma2)
    par1 = StochasticSampledParameter(stochastic_gaussian1 , nbins, nfwhm)
    par2 = StochasticSampledParameter(stochastic_gaussian2, nbins, nfwhm)

    #Building nano particles
    particle_decoration = ParticleDecoration()

    builder = ParticleBuilder()
    builder.setPrototype(cylinder1,"/Particle/FormFactorCylinder/radius", par1, 0.95)
    builder.plantParticles(particle_decoration)
    builder.setPrototype(cylinder2,"/Particle/FormFactorCylinder/radius", par2, 0.05)
    builder.plantParticles(particle_decoration)

    interference = InterferenceFunctionNone()
    particle_decoration.addInterferenceFunction(interference)
    #making layer holding all whose nano particles

    air_layer = Layer(mAmbience)
    air_layer.setDecoration(particle_decoration)
    
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)

    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100, 0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)

    simulation.setSample(multi_layer)
    simulation.runSimulation()
    # intensity data
    return GetOutputData(simulation)

#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    result = RunSimulation()
    PlotNumpyArray(result)




