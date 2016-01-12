# Functional test: IsGISAXS08 example: 2DDL paracrystal
import sys
import os
import numpy
from utils import get_difference
from utils import get_reference_data

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
    particle_layout.addParticle(cylinder, 1.0)
    particle_layout.addInterferenceFunction(interference)

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
    ## intensity data
    return simulation.getIntensityData()


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
    particle_layout.addParticle(cylinder, 1.0)
    particle_layout.addInterferenceFunction(interference)
    
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
    return simulation.getIntensityData()


# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def runTest():
    result1 = RunSimulation1()
    reference1 = get_reference_data("isgisaxs08_reference_2DDL_lattice.int.gz")
    diff = IntensityDataFunctions.getRelativeDifference(result1, reference1)

    result2 = RunSimulation2()
    reference2 = get_reference_data("isgisaxs08_reference_2DDL_lattice2.int.gz")
    diff += IntensityDataFunctions.getRelativeDifference(result2, reference2)

    diff /= 2

    status = "OK"
    if(diff > 2e-10 or numpy.isnan(diff)):
        status = "FAILED"
    return "IsGISAXS07", "Paracrystals", diff, status


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    name, description, diff, status = runTest()
    print name, description, diff, status
    if("FAILED" in status):
        exit(1)
