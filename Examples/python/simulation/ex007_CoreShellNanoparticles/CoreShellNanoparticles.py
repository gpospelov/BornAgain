# IsGISAXS011 example: Core shell nanoparticles
<<<<<<< HEAD

import numpy
import matplotlib
import pylab
from libBornAgainCore import *


def get_sample():
    """
    Build and return the sample representing cylinders and pyramids on top of
    substrate without interference.
    """
    # defining materials
    m_air = MaterialManager.getHomogeneousMaterial("Air", 0.0, 0.0 )
    m_shell = MaterialManager.getHomogeneousMaterial("Shell", 1e-4, 2e-8 )
    m_core = MaterialManager.getHomogeneousMaterial("Core", 6e-5, 2e-8 )
=======
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
    mAmbience = MaterialManager.getHomogeneousMaterial("Air", 0.0, 0.0 )
    mShell = MaterialManager.getHomogeneousMaterial("Shell", 1e-4, 2e-8 )
    mCore = MaterialManager.getHomogeneousMaterial("Core", 6e-5, 2e-8 )
>>>>>>> 04af5cc1e0a39649077aaf9383bb9f401dd14604

    # collection of particles
    parallelepiped1_ff = FormFactorParallelepiped(8*nanometer, 8*nanometer)
    parallelepiped2_ff = FormFactorParallelepiped(7*nanometer, 6*nanometer)
<<<<<<< HEAD
    shell_particle = Particle(m_shell, parallelepiped1_ff)
    core_particle = Particle(m_core, parallelepiped2_ff)
    core_position = kvector_t(0.0, 0.0, 0.0)

=======
    shell_particle = Particle(mShell, parallelepiped1_ff)
    core_particle = Particle(mCore, parallelepiped2_ff)
    core_position = kvector_t(0.0, 0.0, 0.0)
    ##########################################
>>>>>>> 04af5cc1e0a39649077aaf9383bb9f401dd14604
    particle = ParticleCoreShell(shell_particle, core_particle, core_position)
    particle_decoration= ParticleDecoration()
    particle_decoration.addParticle(particle)
    interference = InterferenceFunctionNone()
    particle_decoration.addInterferenceFunction(interference)
<<<<<<< HEAD

    air_layer = Layer(m_air)
    air_layer.setDecoration(particle_decoration)

    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)

    return multi_layer

def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)

    return simulation

def run_simulation():
    """
    Run simulation and plot results
    """

    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    result = simulation.getIntensityData().getArray() + 1  # for log scale
    pylab.imshow(numpy.rot90(result, 1), norm=matplotlib.colors.LogNorm(), extent=[0.0, 2.0, 0, 2.0])
    pylab.show()


if __name__ == '__main__':
    run_simulation()
=======
     
    air_layer = Layer(mAmbience)
    air_layer.setDecoration(particle_decoration)
    
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    
    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    ## intensity data
    return simulation.getIntensityData().getArray()


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
    if(diff > 2e-10 or numpy.isnan(diff)): status = "FAILED"
    return "IsGISAXS11", "Core shell nanoparticles", status


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    name,description,status = runTest()
    print name,description,status
    if("FAILED" in status) : exit(1)

>>>>>>> 04af5cc1e0a39649077aaf9383bb9f401dd14604
