# Functional test: IsGISAXS02 example: Mixture cylinder particles with different size distribution
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
def RunSimulation():
    # defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0 )
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8 )
    # collection of particles
    radius1 = 5.0*nanometer
    radius2 = 10.0*nanometer
    height1 = radius1
    height2 = radius2
    cylinder_ff1 = FormFactorCylinder(radius1, height1)
    cylinder1 = Particle(mParticle, cylinder_ff1)
    cylinder_ff2 = FormFactorCylinder(radius2, height2)
    cylinder2 = Particle(mParticle, cylinder_ff2)  
    nbins = 150
    sigma1 = radius1*0.2
    sigma2 = radius2*0.02

    n_sigma = 3.0
    #to have xmin = average-3*sigma
    gauss1 = DistributionGaussian(radius1, sigma1)
    gauss2 = DistributionGaussian(radius2, sigma2)

    #Building nano particles
    particle_layout = ParticleLayout()

    par_distr1 = ParameterDistribution("*/Radius", gauss1, nbins, n_sigma)
    part_coll1 = ParticleDistribution(cylinder1, par_distr1)
    particle_layout.addParticle(part_coll1, 0.95)
    par_distr2 = ParameterDistribution("*/Radius", gauss2, nbins, n_sigma)
    part_coll2 = ParticleDistribution(cylinder2, par_distr2)
    particle_layout.addParticle(part_coll2, 0.05)

    interference = InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)
    #making layer holding all whose nano particles
    air_layer = Layer(mAmbience)
    air_layer.addLayout(particle_layout)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    
    # build and run experiment
    simulation = GISASSimulation()
    detector = IsGISAXSDetector(100, 0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree)
    simulation.setDetector(detector)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
  
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    # intensity data
    return simulation.getIntensityData()


# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def runTest():
    result = RunSimulation()
    reference = get_reference_data('isgisaxs02_reference.int.gz')
    diff = IntensityDataFunctions.getRelativeDifference(result, reference)
    status = "OK"
    if(diff > 2e-10 or numpy.isnan(diff)):
        status = "FAILED"
    return "IsGISAXS02", "Mixture cylinder particles with different size distribution", diff, status


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    name, description, diff, status = runTest()
    print name, description, diff, status
    if("FAILED" in status):
        exit(1)




