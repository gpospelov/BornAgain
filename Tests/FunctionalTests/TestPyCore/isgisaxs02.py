# IsGISAXS02 example: Mixture cylinder particles with different size distribution
import sys
import os
import numpy
import gzip
import math

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
    mParticle = MaterialManager.getHomogeneousMaterial("Particle", 6e-4, 2e-8 )
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

    nfwhm = 3
    #to have xmin=average-nfwhm*FWHM, xmax=average+nfwhm*FWHM
    #(nfwhm = xR/2, where xR is what is defined in isgisaxs *.inp file)
    stochastic_gaussian1 = StochasticDoubleGaussian(radius1, sigma1)
    stochastic_gaussian2 = StochasticDoubleGaussian(radius2, sigma2)
    par1 = StochasticSampledParameter(stochastic_gaussian1 , nbins, nfwhm)
    par2 = StochasticSampledParameter(stochastic_gaussian2, nbins, nfwhm)

    #Building nano particles
    particle_decoration = ParticleDecoration()

    builder = ParticleBuilder()
    builder.setPrototype(cylinder1,"/Particle/FormFactorCylinder/radius", par1, 0.95)
    builder.plantParticles(particle_decoration)
    builder.setPrototype(cylinder2,"/Particle/FormFactorCylinder/radius", par2, 0.05)
    builder.plantParticles(particle_decoration)

    interference = InterferenceFunctionNone()
    particle_decoration.addInterferenceFunction(interference)
    #making layer holding all whose nano particles
    air_layer = Layer(mAmbience)
    air_layer.setDecoration(particle_decoration)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    
    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100, 0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
  
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    # intensity data
    return simulation.getIntensityData().getArray()

# ----------------------------------
# read reference data from file
# ----------------------------------
def GetReferenceData():
    path = os.path.split(__file__)[0]
    if path: path +="/"
    f = gzip.open(path+'../../ReferenceData/BornAgain/isgisaxs02_reference.ima.gz', 'rb')
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
    return "IsGISAXS02", "Mixture cylinder particles with different size distribution", status


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    name,description,status = runTest()
    print name,description,status
    if("FAILED" in status) : exit(1)




