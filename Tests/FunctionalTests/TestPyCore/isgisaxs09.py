# Functional test: IsGISAXS09 example: Pyramids on top of substrate - Rotated pyramids on top of substrate
import sys
import os
import numpy
from utils import get_difference
from utils import get_reference_data


sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *

# ----------------------------------
# describe sample and run simulation - Pyramid
# ----------------------------------
def RunSimulation1():
    # defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0 )
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8 )
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8 )
    
    # collection of particles
    pyramid_ff = FormFactorPyramid(10*nanometer, 5*nanometer, deg2rad(54.73 ) )
    pyramid = Particle(mParticle, pyramid_ff)
    interference = InterferenceFunctionNone()
    particle_layout = ParticleLayout()
    particle_layout.addParticle(pyramid, 1.0)
    particle_layout.addInterferenceFunction(interference)

    air_layer = Layer(mAmbience)
    air_layer.addLayout(particle_layout)
    
    substrate_layer = Layer(mSubstrate, 0)
    
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    # build and run experiment
    simulation = GISASSimulation()
    detector = IsGISAXSDetector(100, 0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree)
    simulation.setDetector(detector)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    ## intensity data
    return simulation.getIntensityData()


# ----------------------------------
# describe sample and run simulation - Rotated Pyramid
# ----------------------------------
def RunSimulation2():
   # defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0 )
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8 )
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8 )
    
    # collection of particles
    pyramid_ff = FormFactorPyramid(10*nanometer, 5*nanometer, deg2rad(54.73 ) )
    pyramid = Particle(mParticle, pyramid_ff)
    interference = InterferenceFunctionNone()
    angle_around_z = 45.*degree
    transform = RotationZ(angle_around_z)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(pyramid, 1.0, kvector_t(0,0,0), transform)
    
    particle_layout.addInterferenceFunction(interference)

    air_layer = Layer(mAmbience)
    air_layer.addLayout(particle_layout)

    substrate_layer = Layer(mSubstrate, 0)
    
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    # build and run experiment
    simulation = GISASSimulation()
    detector = IsGISAXSDetector(100, 0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree)
    simulation.setDetector(detector)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    return simulation.getIntensityData()


# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def runTest():
    result1 = RunSimulation1()
    reference1 = get_reference_data("isgisaxs09_reference_pyramid_Z0.int.gz")
    diff = IntensityDataFunctions.getRelativeDifference(result1, reference1)

    result2 = RunSimulation2()
    reference2 = get_reference_data("isgisaxs09_reference_pyramid_Z45.int.gz")
    diff += IntensityDataFunctions.getRelativeDifference(result2, reference2)

    diff /= 2.

    status = "OK"
    if(diff > 2e-10 or numpy.isnan(diff)):
        status = "FAILED"
    return "IsGISAXS09", "Pyramids on top of substrate - Rotated pyramids on top of substrate", diff, status


if __name__ == '__main__':
    name, description, diff, status = runTest()
    print name, description, diff, status
    if("FAILED" in status):
        exit(1)



