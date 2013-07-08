# IsGISAXS03 example: Cylinder formfactor in BA with size distribution (IsGISAXS example #3)

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
    mAmbience = MaterialManager.getHomogeneousMaterial("Air", 1.0, 0.0 )
    mSubstrate = MaterialManager.getHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8 )

    multi_layer = MultiLayer()

    n_particle = complex(1.0-6e-4, 2e-8)
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    particle_decoration = ParticleDecoration()
    # preparing prototype of nano particle
    radius = 5*nanometer
    sigma = 0.2*radius
    nano_particle = Particle(n_particle, cylinder_ff)
    # radius of nanoparticles will be sampled with gaussian probability
    nbins = 100
    nfwhm = 2
    stochastic_gaussian = StochasticDoubleGaussian(radius, sigma)
    par = StochasticSampledParameter(stochastic_gaussian, nbins, nfwhm)

    builder = ParticleBuilder()
    builder.setPrototype(nano_particle,"/Particle/FormFactorCylinder/radius", par)
    builder.plantParticles(particle_decoration)
    interference = InterferenceFunctionNone()
    particle_decoration.addInterferenceFunction(interference)    

    air_layer = Layer(mAmbience)
    air_layer_decorator = LayerDecorator(air_layer, particle_decoration)
    multi_layer.addLayer(air_layer_decorator)

    # build and run experiment  
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, -0.2*degree, 0.0*degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    return GetOutputData(simulation)


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    result = RunSimulation()
    PlotNumpyArray(result)


