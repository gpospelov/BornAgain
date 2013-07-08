# IsGISAXS011 example: Core shell nanoparticles
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
    mAmbience = MaterialManager.getHomogeneousMaterial("Air", 1.0, 0.0 )

    # collection of particles
    n_particle_shell = complex(1.0-1e-4, 2e-8)
    n_particle_core = complex(1.0-6e-5, 2e-8)
    parallelepiped1_ff = FormFactorParallelepiped(8*nanometer, 8*nanometer)
    parallelepiped2_ff = FormFactorParallelepiped(7*nanometer, 6*nanometer)
    shell_particle = Particle(n_particle_shell, parallelepiped1_ff)
    core_particle = Particle(n_particle_core, parallelepiped2_ff)
    core_position = kvector_t(0.0, 0.0, 0.0)
    ##########################################
    particle = ParticleCoreShell(shell_particle, core_particle, core_position)
    particle_decoration= ParticleDecoration()
    particle_decoration.addParticle(particle)
    interference = InterferenceFunctionNone()
    particle_decoration.addInterferenceFunction(interference)
     
    air_layer = Layer(mAmbience)
    air_layer_decorator = LayerDecorator(air_layer, particle_decoration)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer_decorator)
    
    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, -0.2*degree, 0.0*degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    ## intensity data
    return GetOutputData(simulation)


# ----------------------------------
# read reference data from file
# ----------------------------------
def GetReferenceData():
    path = os.path.split(__file__)[0]
    if path: path +="/"
    f = gzip.open(path+'../../ReferenceData/BornAgain/isgisaxs11_reference.ima.gz', 'rb')
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
    if(diff > 1e-10 or numpy.isnan(diff)): status = "FAILED"
    return "IsGISAXS11", "Core shell nanoparticles", status


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  name,description,status = runTest()
  print name,description,status


