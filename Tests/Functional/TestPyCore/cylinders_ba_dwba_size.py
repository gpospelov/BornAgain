# Functional test: IsGISAXS03 example: Cylinder formfactor in BA and DWBA
from __future__ import print_function
import sys
import os
import numpy
from utils import get_reference_data

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *

# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulationDWBA():
    
    # defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0 )
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8 )    
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8 )
    # collection of particles
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(mParticle, cylinder_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)
    interference = InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)
    # air layer with particles and substrate form multi layer
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
    # intensity data
    return simulation.getIntensityData()


# ----------------------------------
# describe sample and run simulation - IsGISAXS3 functional test: cylinder in the air
# ----------------------------------
def RunSimulationBA():
     # defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0 )
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8 )
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8 )
    
    # collection of particles
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(mParticle, cylinder_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)
    interference = InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)
    
    air_layer = Layer(mAmbience)
    air_layer.addLayout(particle_layout)
    
    substrate_layer = Layer(mSubstrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    
    # build and run experiment
    simulation = GISASSimulation()
    detector = IsGISAXSDetector(100, 0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree)
    simulation.setDetector(detector)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    return simulation.getIntensityData()


# ----------------------------------
# describe sample and run simulation - IsGISAXS3 functional test: cylinder in the air with size distribution
# ----------------------------------
def RunSimulationBA_Size():
    # defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0 )
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8 )
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8 )

    multi_layer = MultiLayer()

    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    particle_layout = ParticleLayout()
    # preparing prototype of nano particle
    radius = 5*nanometer
    sigma = 0.2*radius
    nano_particle = Particle(mParticle, cylinder_ff)
    # radius of nanoparticles will be sampled with gaussian probability
    nbins = 100
    n_sigma = 4.0*numpy.sqrt(2.0*numpy.log(2.0))
    gauss = DistributionGaussian(radius, sigma)

    par_distr = ParameterDistribution("*/Radius", gauss, nbins, n_sigma)
    part_coll = ParticleDistribution(nano_particle, par_distr)
    particle_layout.addParticle(part_coll)

    interference = InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)    

    air_layer = Layer(mAmbience)
    air_layer.addLayout(particle_layout)
    
    multi_layer.addLayer(air_layer)

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
    resultBA = RunSimulationBA()
    resultDWBA = RunSimulationDWBA()
    resultBA_Size = RunSimulationBA_Size()

    diff = IntensityDataFunctions.getRelativeDifference(resultBA, get_reference_data("isgisaxs03_reference_BA.int.gz"))
    diff += IntensityDataFunctions.getRelativeDifference(resultBA_Size, get_reference_data("isgisaxs03_reference_BA_size.int.gz"))
    diff += IntensityDataFunctions.getRelativeDifference(resultDWBA, get_reference_data("isgisaxs03_reference_DWBA.int.gz"))
    diff /= 3

    status = "OK"
    if(diff > 2e-10 or numpy.isnan(diff)):
        status = "FAILED"
    return "Cylinders_BA_DWBA_SIZE", "Cylinder formfactor in BA and DWBA", diff, status

   
if __name__ == '__main__':
    name, description, diff, status = runTest()
    print(name, description, diff, status)
    if("FAILED" in status):
        exit(1)



