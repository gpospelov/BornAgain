# IsGISAXS07 example: Mixture of different particles defined in morphology file
import sys
import os
import numpy
from utils import get_difference
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
    particle_layout = ParticleLayout()

    #PositionParticleInfo particle_info1(new Particle(n_particle, ff1), 0, pos1, 0.5);
    #particle_layout.addParticleInfo(particle_info1);
    #
    # add particle number 1:
    ff1 = FormFactorBox(2.0*nanometer, 2.0*nanometer,1.0*nanometer)
    pos1 = kvector_t(0.0*nanometer, 0.0*nanometer, 0.0)
    particle1 = Particle(mParticle, ff1)
    particle_info1 = PositionParticleInfo(particle1, pos1, 0.5)
    particle_layout.addParticleInfo(particle_info1)
    #add particle number 2:
    ff2 = FormFactorBox(2.0*nanometer, 4.0*nanometer,1.0*nanometer)
    pos2 = kvector_t(5.0*nanometer, 5.0*nanometer, 0.0)
    p_rot2 = Transform3D.createRotateZ(10*degree)
    particle2 = Particle(mParticle, ff2, p_rot2)   
    particle_info2 = PositionParticleInfo(particle2, pos2, 0.5)
    particle_layout.addParticleInfo(particle_info2)
    #add particle number 3:
    ff3 = FormFactorBox(2.0*nanometer, 6.0*nanometer,1.0*nanometer)
    pos3 = kvector_t(-5.0*nanometer, -5.0*nanometer, 0.0)
    p_rot3 = Transform3D.createRotateZ(20*degree)
    particle3 = Particle(mParticle, ff3, p_rot3)
    particle_info3 = PositionParticleInfo(particle3, pos3, 0.5)
    particle_layout.addParticleInfo(particle_info3)
    #add particle number 4:
    ff4 = FormFactorBox(2.0*nanometer, 8.0*nanometer,1.0*nanometer)
    pos4 = kvector_t(5.0*nanometer, -5.0*nanometer, 0.0)
    p_rot4 = Transform3D.createRotateZ(30*degree)
    particle4 = Particle(mParticle, ff4, p_rot4)   
    particle_info4 = PositionParticleInfo(particle4, pos4, 0.5)
    particle_layout.addParticleInfo(particle_info4)
    #add particle number 5:
    ff5 = FormFactorBox(2.0*nanometer, 10.0*nanometer,1.0*nanometer)
    pos5 = kvector_t(-5.0*nanometer, 5.0*nanometer, 0.0)
    p_rot5 = Transform3D.createRotateZ(40*degree)
    particle5 = Particle(mParticle, ff5, p_rot5)   
    particle_info5 =  PositionParticleInfo(particle5, pos5, 0.5)
    particle_layout.addParticleInfo(particle_info5)
    #add particle number 6:
    ff6 = FormFactorBox(2.0*nanometer, 2.0*nanometer,1.0*nanometer)
    pos6 = kvector_t(0.0*nanometer, 0.0*nanometer, 0.0)
    p_rot6 = Transform3D.createRotateZ(50*degree)
    particle6 = Particle(mParticle, ff6, p_rot6)   
    particle_info6 = PositionParticleInfo(particle6, pos6, 0.5)
    particle_layout.addParticleInfo(particle_info6)
    #add particle number 7:
    ff7 = FormFactorBox(2.0*nanometer, 4.0*nanometer,1.0*nanometer)
    pos7 = kvector_t(5.0*nanometer, 5.0*nanometer, 0.0)
    p_rot7 = Transform3D.createRotateZ(60*degree)
    particle7 = Particle(mParticle, ff7, p_rot7)
    particle_info7 = PositionParticleInfo(particle7, pos7, 0.5)
    particle_layout.addParticleInfo(particle_info7)
    #add particle number 8:
    ff8 = FormFactorBox(2.0*nanometer, 6.0*nanometer,1.0*nanometer)
    pos8 = kvector_t(-5.0*nanometer, -5.0*nanometer, 0.0)
    p_rot8 = Transform3D.createRotateZ(70*degree)
    particle8 = Particle(mParticle, ff8, p_rot8)    
    particle_info8 = PositionParticleInfo(particle8 , pos8, 0.5)
    particle_layout.addParticleInfo(particle_info8)
    #add particle number 9:
    ff9 = FormFactorBox(2.0*nanometer, 8.0*nanometer,1.0*nanometer)
    pos9 = kvector_t(5.0*nanometer, -5.0*nanometer, 0.0)
    p_rot9 = Transform3D.createRotateZ(80*degree)
    particle9 = Particle(mParticle, ff9, p_rot9)     
    particle_info9 = PositionParticleInfo(particle9, pos9, 0.5)
    particle_layout.addParticleInfo(particle_info9)
    #add particle number 10:
    ff10 = FormFactorBox(2.0*nanometer, 10.0*nanometer,1.0*nanometer)
    pos10 = kvector_t(-5.0*nanometer, 5.0*nanometer, 0.0)
    p_rot10 = Transform3D.createRotateZ(90*degree)
    particle10 = Particle(mParticle, ff10, p_rot10)
    particle_info10 = PositionParticleInfo(particle10, pos10, 0.5)
    particle_layout.addParticleInfo(particle_info10)

    particle_layout.setApproximation(ILayout.ISGISAXSMOR)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(mAmbience)
    air_layer.setLayout(particle_layout)
    
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
  
    #build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 1.0*degree, 100, 0.0*degree, 1.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.0*degree, 0.0*degree)

    simulation.setSample(multi_layer)
    simulation.runSimulation()
    ## intensity data
    return simulation.getIntensityData()


# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def runTest():
    result = RunSimulation()
    reference = get_reference_data("isgisaxs07_reference.int.gz")

    diff = IntensityDataFunctions.getRelativeDifference(result, reference)

    status = "OK"
    if(diff > 2e-10 or numpy.isnan(diff)):
        status = "FAILED"
    return "IsGISAXS07", "Mixture of different particles defined in morphology file", diff, status


if __name__ == '__main__':
    name, description, diff, status = runTest()
    print name, description, diff, status
    if("FAILED" in status) :
        exit(1)
