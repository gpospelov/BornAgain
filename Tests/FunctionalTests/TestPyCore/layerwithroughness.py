# Functional test for layer with correlated roughness
import sys
import os
import numpy
import gzip

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))


from libBornAgainCore import *


# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    m_ambience = MaterialManager.getHomogeneousMaterial("ambience", 0.0, 0.0)
    m_part_a = MaterialManager.getHomogeneousMaterial("PartA", 5e-6, 0.0)
    m_part_b = MaterialManager.getHomogeneousMaterial("PartB", 10e-6, 0.0)
    m_substrate = MaterialManager.getHomogeneousMaterial("substrate", 15e-6, 0.0)

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
    simulation = Simulation()
    simulation.setDetectorParameters(100, -0.5*degree, 0.5*degree, 100, 0.0*degree, 1.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    simulation.setSample(my_sample)
    simulation.runSimulation()
    ## intensity data
    return simulation.getIntensityData().getArray()

# ----------------------------------
# read reference data from file
# ----------------------------------
def GetReferenceData():
    path = os.path.split(__file__)[0]
    if path: path +="/"
    f = gzip.open(path+'../../ReferenceData/BornAgain/layer_with_roughness.ima.gz', 'rb')
    reference=numpy.fromstring(f.read(),numpy.float64,sep=' ')
    f.close()
    return reference


# --------------------------------------------------------------
# calculate numeric difference between result and reference data
# --------------------------------------------------------------
def GetDifference(data, reference):
    reference = reference.reshape(data.shape)
    # calculating relative average difference
    data -= reference
    diff=0.0
    epsilon = sys.float_info.epsilon
    for x, y in numpy.ndindex(data.shape):
        v1 = data[x][y]
        v2 = reference[x][y]
        if v1 <= epsilon and v2 <= epsilon:
            diff += 0.0
        elif(v2 <= epsilon):
            diff += abs(v1/epsilon)
        else:
            diff += abs(v1/v2)
    return diff/data.size


# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def runTest():
    result = RunSimulation()
    reference = GetReferenceData()

    diff = GetDifference(result, reference)
    status = "OK"
    if(diff > 2e-10 or numpy.isnan(diff)): status = "FAILED"
    return "LayerWithRoughness", "Layers with correlated roughnress", status


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    name,description,status = runTest()
    print name,description,status
    if("FAILED" in status) : exit(1)
