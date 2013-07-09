# Rotated pyramids on top of substrate (IsGISAXS example #9)
import sys, os, numpy

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0], '..', '..', '..', 'lib')
                ))

sys.path.append(os.path.abspath(os.path.join(os.path.split(__file__)[0],'..')))

from libBornAgainCore import *
from utils.show2d import PlotNumpyArray


# ----------------------------------
# describe sample and run simulation - Rotated Pyramid
# ----------------------------------
def RunSimulation():
   # defining materials
    mAmbience = MaterialManager.getHomogeneousMaterial("Air", 1.0, 0.0 )
    mSubstrate = MaterialManager.getHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8 )
    # collection of particles
    n_particle = complex(1.0-6e-4, 2e-8)   
    pyramid_ff = FormFactorPyramid(5*nanometer, 5*nanometer, deg2rad(54.73 ) )
    pyramid = Particle(n_particle, pyramid_ff)
    interference = InterferenceFunctionNone()
    angle_around_z = 45.*degree
    #rotatez3d = RotateZ3D(angle_around_z)
    #transform = Transform3D(rotatez3d)
    transform = RotateZ_3D(angle_around_z)
    particle_decoration = ParticleDecoration()
    particle_decoration.addParticle(pyramid, transform)

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
    simulation.setBeamParameters(1.0*angstrom, -0.2*degree, 0.0*degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    ## intensity data
    return GetOutputData(simulation)


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    result = RunSimulation()
    PlotNumpyArray(result)


