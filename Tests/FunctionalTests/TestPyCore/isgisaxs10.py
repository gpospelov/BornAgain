# Functional test: IsGISAXS010 example: Cylinders with interference on top of substrate
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
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0)
    mSubstrate = HomogeneousMaterial("Substrate", 5e-6, 2e-8)
    mParticle = HomogeneousMaterial("Particle", 5e-5, 2e-8)
    # collection of particles
    cylinder_ff = FormFactorCylinder(5 * nanometer, 5 * nanometer)
    cylinder = Particle(mParticle, cylinder_ff)
    interference = InterferenceFunctionRadialParaCrystal(20.0 * nanometer, 1e7 * nanometer)
    pdf = FTDistribution1DGauss(7 * nanometer)
    interference.setProbabilityDistribution(pdf)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)
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
    simulation.setBeamParameters(1.0 * angstrom, 0.2 * degree, 0.0 * degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    return simulation.getIntensityData()


# ----------------------------------
# read reference data from file
# ----------------------------------
def GetReferenceData():
    path = os.path.split(__file__)[0]
    if path: path += "/"
    f = gzip.open(path + '../../ReferenceData/BornAgain/isgisaxs10_reference.ima.gz', 'rb')
    reference = numpy.fromstring(f.read(), numpy.float64, sep=' ')
    f.close()
    return reference



# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def runTest():
    result = RunSimulation()
    reference = get_reference_data("isgisaxs10_reference.int.gz")

    diff = IntensityDataFunctions.getRelativeDifference(result, reference)

    status = "OK"
    if (diff > 2e-10 or numpy.isnan(diff)): status = "FAILED"
    return "IsGISAXS10", "Cylinders with interference on top of substrate", diff, status


if __name__ == '__main__':
    name, description, diff, status = runTest()
    print name, description, diff, status
    if("FAILED" in status):
        exit(1)

