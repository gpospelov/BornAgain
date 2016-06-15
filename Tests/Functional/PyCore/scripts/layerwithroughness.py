# Functional test: Functional test for layer with correlated roughness
from __future__ import print_function
import sys
import os
import numpy
from utils import get_reference_data

from libBornAgainCore import *


# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    m_ambience = HomogeneousMaterial("ambience", 0.0, 0.0)
    m_part_a = HomogeneousMaterial("PartA", 5e-6, 0.0)
    m_part_b = HomogeneousMaterial("PartB", 10e-6, 0.0)
    m_substrate = HomogeneousMaterial("substrate", 15e-6, 0.0)

    l_ambience = Layer(m_ambience, 0)
    l_part_a = Layer(m_part_a, 2.5*nanometer)
    l_part_b = Layer(m_part_b, 5.0*nanometer)
    l_substrate = Layer(m_substrate, 0)

    roughness = LayerRoughness()
    roughness.setSigma(1.0*nanometer)
    roughness.setHurstParameter(0.3)
    roughness.setLatteralCorrLength(5*nanometer)

    my_sample = MultiLayer()

    # adding layers
    my_sample.addLayer(l_ambience)

    n_repetitions = 5
    for i in range(n_repetitions):
        my_sample.addLayerWithTopRoughness(l_part_a, roughness)
        my_sample.addLayerWithTopRoughness(l_part_b, roughness)

    my_sample.addLayerWithTopRoughness(l_substrate, roughness)
    my_sample.setCrossCorrLength(1e-4)

    # build and run experiment
    simulation = GISASSimulation()
    simulation.setDetectorParameters(100, -0.5*degree, 0.5*degree, 100, 0.0*degree, 1.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    simulation.setSample(my_sample)
    simulation.runSimulation()

    # intensity data
    return simulation.getIntensityData()


# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def runTest():
    result = RunSimulation()
    reference = get_reference_data("roughness01_reference.int.gz")

    # IntensityDataIOFactory.writeIntensityData(result, "roughness01_reference.int.gz")

    diff = IntensityDataFunctions.getRelativeDifference(result, reference)

    status = "OK"
    if diff > 2e-10 or numpy.isnan(diff): status = "FAILED"
    return "LayerWithRoughness", "Layers with correlated roughness", diff, status


# -------------------------------------------------------------
# main()
# -------------------------------------------------------------
if __name__ == '__main__':
    name, description, diff, status = runTest()
    print(name, description, diff, status)
    if "FAILED" in status:
        exit(1)
