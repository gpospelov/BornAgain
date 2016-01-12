# Functional test: IsGISAXS011 example: Core shell nanoparticles
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
    mShell = HomogeneousMaterial("Shell", 1e-4, 2e-8 )
    mCore = HomogeneousMaterial("Core", 6e-5, 2e-8 )

    # collection of particles
    box1_ff = FormFactorBox(16*nanometer, 16*nanometer, 8*nanometer)
    box2_ff = FormFactorBox(12*nanometer, 12*nanometer, 7*nanometer)
    shell_particle = Particle(mShell, box1_ff)
    core_particle = Particle(mCore, box2_ff)
    core_position = kvector_t(0.0, 0.0, 0.0)
    ##########################################
    particle = ParticleCoreShell(shell_particle, core_particle, core_position)
    particle_layout= ParticleLayout()
    particle_layout.addParticle(particle)
    interference = InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)
     
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
    ## intensity data
    return simulation.getIntensityData()


# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def runTest():
    result = RunSimulation()
    reference = get_reference_data("isgisaxs11_reference.int.gz")

    diff = IntensityDataFunctions.getRelativeDifference(result, reference)

    status = "OK"
    if(diff > 2e-10 or numpy.isnan(diff)): status = "FAILED"
    return "IsGISAXS11", "Core shell nanoparticles", diff, status


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    name, description, diff, status = runTest()
    print name, description, diff, status
    if("FAILED" in status):
        exit(1)

