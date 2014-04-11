# IsGISAXS08 example: 2DDL paracrystal
import sys
import os
import numpy
import gzip

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *

M_PI = numpy.pi
# ----------------------------------
# describe sample and run simulation - 2D lattice
# ----------------------------------
def RunSimulation1():
    # defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0 )
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8 )
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8 )
    # collection of particles
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(mParticle, cylinder_ff)
    interference = InterferenceFunction2DParaCrystal(10.0*nanometer, 10.0*nanometer, M_PI/2.0, 0.0, 0.0)
    interference.setDomainSizes(20.0*micrometer, 20.0*micrometer)
    pdf1 = FTDistribution2DCauchy(0.5*nanometer, 2.0*nanometer)
    pdf2 = FTDistribution2DCauchy(0.5*nanometer, 2.0*nanometer)
    interference.setProbabilityDistributions(pdf1, pdf2)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 0.0, 1.0)
    particle_layout.addInterferenceFunction(interference)

    air_layer = Layer(mAmbience)
    air_layer.setLayout(particle_layout)
    substrate_layer = Layer(mSubstrate, 0)
    
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    
    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    ## intensity data
    return simulation.getIntensityData().getArray()


# ----------------------------------
# describe sample and run simulation - 2D paracrystal lattice with isotropic pdfs
# ----------------------------------
def RunSimulation2():
    # defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0 )
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8 )
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8 )
    
    # collection of particles
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(mParticle, cylinder_ff)
    interference = InterferenceFunction2DParaCrystal(10.0*nanometer, 10.0*nanometer, M_PI/2.0, 0.0, 0.0)
    interference.setDomainSizes(20.0*micrometer, 20.0*micrometer)
    pdf1 = FTDistribution2DCauchy(0.5*nanometer, 0.5*nanometer)
    pdf2 = FTDistribution2DCauchy(0.5*nanometer, 0.5*nanometer)
    interference.setProbabilityDistributions(pdf1, pdf2)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 0.0, 1.0)
    particle_layout.addInterferenceFunction(interference)
    
    air_layer = Layer(mAmbience)
    air_layer.setLayout(particle_layout)
    substrate_layer = Layer(mSubstrate, 0)
    
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    
    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    return simulation.getIntensityData().getArray()


# ----------------------------------
# read reference data from file
# ----------------------------------
def GetReferenceData():
    path = os.path.split(__file__)[0]
    if path: path +="/"
    f1 = gzip.open(path+'../../ReferenceData/BornAgain/isgisaxs08_reference_2DDL_lattice.ima.gz', 'rb')
    reference1=numpy.fromstring(f1.read(),numpy.float64,sep=' ')
    f1.close()
    f2 = gzip.open(path+'../../ReferenceData/BornAgain/isgisaxs08_reference_2DDL_lattice2.ima.gz', 'rb')
    reference2=numpy.fromstring(f2.read(),numpy.float64,sep=' ')
    f2.close()
    reference=numpy.concatenate((reference1,reference2),axis=0)    
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
    result1 = RunSimulation1()
    result2 = RunSimulation2()
    result = numpy.concatenate((result1,result2),axis=0) 
    reference = GetReferenceData()

    diff = GetDifference(result, reference)
    status = "OK"
    if(diff > 2e-10 or numpy.isnan(diff)): status = "FAILED"
    return "IsGISAXS08", "2DDL paracrystal", status


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    name,description,status = runTest()
    print name,description,status
    if("FAILED" in status) : exit(1)
