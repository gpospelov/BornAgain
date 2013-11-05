# IsGISAXS07 example: Mixture of different particles defined in morphology file
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
    mParticle = MaterialManager.getHomogeneousMaterial("Particle", 6e-4, 2e-8 )

    # collection of particles
    particle_decoration = ParticleDecoration()

    #PositionParticleInfo particle_info1(new Particle(n_particle, ff1), 0, pos1, 0.5);
    #particle_decoration.addParticleInfo(particle_info1);
    #
    # add particle number 1:
    ff1 = FormFactorBox(2.0*nanometer, 2.0*nanometer,1.0*nanometer)
    pos1 = kvector_t(0.0*nanometer, 0.0*nanometer, 0.0)
    particle1 = Particle(mParticle, ff1)
    particle_info1 = PositionParticleInfo(particle1, pos1, 0.5)
    particle_decoration.addParticleInfo(particle_info1)
    #add particle number 2:
    ff2 = FormFactorBox(2.0*nanometer, 4.0*nanometer,1.0*nanometer)
    pos2 = kvector_t(5.0*nanometer, 5.0*nanometer, 0.0)
    #rotate3d2 = RotateZ_3D(10*degree)
    #p_rot2 = ITransform3D(rotate3d2)
    p_rot2 = RotateZ_3D(10*degree)
    
    particle2 = Particle(mParticle, ff2, p_rot2)   
    particle_info2 = PositionParticleInfo(particle2, pos2, 0.5)
    particle_decoration.addParticleInfo(particle_info2)
    #add particle number 3:
    ff3 = FormFactorBox(2.0*nanometer, 6.0*nanometer,1.0*nanometer)
    pos3 = kvector_t(-5.0*nanometer, -5.0*nanometer, 0.0)
    #rotate3d3 = RotateZ_3D(20*degree)
    #p_rot3 = ITransform3D(rotate3d3)   
    p_rot3 = RotateZ_3D(20*degree)
    particle3 = Particle(mParticle, ff3, p_rot3)
    particle_info3 = PositionParticleInfo(particle3, pos3, 0.5)
    particle_decoration.addParticleInfo(particle_info3)
    #add particle number 4:
    ff4 = FormFactorBox(2.0*nanometer, 8.0*nanometer,1.0*nanometer)
    pos4 = kvector_t(5.0*nanometer, -5.0*nanometer, 0.0)
    #rotate3d4 = RotateZ_3D(30*degree)
    #p_rot4 = ITransform3D(rotate3d4)   
    p_rot4 = RotateZ_3D(30*degree)
    particle4 = Particle(mParticle, ff4, p_rot4)   
    particle_info4 = PositionParticleInfo(particle4, pos4, 0.5)
    particle_decoration.addParticleInfo(particle_info4)
    #add particle number 5:
    ff5 = FormFactorBox(2.0*nanometer, 10.0*nanometer,1.0*nanometer)
    pos5 = kvector_t(-5.0*nanometer, 5.0*nanometer, 0.0)
    #rotate3d5 = RotateZ_3D(40*degree)
    #p_rot5 = ITransform3D(rotate3d5)   
    p_rot5 = RotateZ_3D(40*degree)
    particle5 = Particle(mParticle, ff5, p_rot5)   
    particle_info5 =  PositionParticleInfo(particle5, pos5, 0.5)
    particle_decoration.addParticleInfo(particle_info5)
    #add particle number 6:
    ff6 = FormFactorBox(2.0*nanometer, 2.0*nanometer,1.0*nanometer)
    pos6 = kvector_t(0.0*nanometer, 0.0*nanometer, 0.0)
    #rotate3d6 = RotateZ_3D(50*degree)
    #p_rot6 = ITransform3D(rotate3d6)
    p_rot6 = RotateZ_3D(50*degree)
    particle6 = Particle(mParticle, ff6, p_rot6)   
    particle_info6 = PositionParticleInfo(particle6, pos6, 0.5)
    particle_decoration.addParticleInfo(particle_info6)
    #add particle number 7:
    ff7 = FormFactorBox(2.0*nanometer, 4.0*nanometer,1.0*nanometer)
    pos7 = kvector_t(5.0*nanometer, 5.0*nanometer, 0.0)
    #rotate3d7 = RotateZ_3D(60*degree)
    #p_rot7 = ITransform3D(rotate3d7)
    p_rot7 = RotateZ_3D(60*degree)
    particle7 = Particle(mParticle, ff7, p_rot7)
    particle_info7 = PositionParticleInfo(particle7, pos7, 0.5)
    particle_decoration.addParticleInfo(particle_info7)
    #add particle number 8:
    ff8 = FormFactorBox(2.0*nanometer, 6.0*nanometer,1.0*nanometer)
    pos8 = kvector_t(-5.0*nanometer, -5.0*nanometer, 0.0)
    #rotate3d8 = RotateZ_3D(70*degree)
    #p_rot8 = ITransform3D(rotate3d8)
    p_rot8 = RotateZ_3D(70*degree)
    particle8 = Particle(mParticle, ff8, p_rot8)    
    particle_info8 = PositionParticleInfo(particle8 , pos8, 0.5)
    particle_decoration.addParticleInfo(particle_info8)
    #add particle number 9:
    ff9 = FormFactorBox(2.0*nanometer, 8.0*nanometer,1.0*nanometer)
    pos9 = kvector_t(5.0*nanometer, -5.0*nanometer, 0.0)
    #rotate3d9 = RotateZ_3D(80*degree)
    #p_rot9 = ITransform3D(rotate3d9)
    p_rot9 = RotateZ_3D(80*degree)
    particle9 = Particle(mParticle, ff9, p_rot9)     
    particle_info9 = PositionParticleInfo(particle9, pos9, 0.5)
    particle_decoration.addParticleInfo(particle_info9)
    #add particle number 10:
    ff10 = FormFactorBox(2.0*nanometer, 10.0*nanometer,1.0*nanometer)
    pos10 = kvector_t(-5.0*nanometer, 5.0*nanometer, 0.0)
    #rotate3d10 = RotateZ_3D(90*degree)
    #p_rot10 = ITransform3D(rotate3d10)
    p_rot10 = RotateZ_3D(90*degree)
    particle10 = Particle(mParticle, ff10, p_rot10)
    particle_info10 = PositionParticleInfo(particle10, pos10, 0.5)
    particle_decoration.addParticleInfo(particle_info10)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(mAmbience)
    air_layer.setDecoration(particle_decoration)
    
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
  
    #build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(100,0.0*degree, 1.0*degree, 100, 0.0*degree, 1.0*degree, True)
    simulation.setBeamParameters(1.0*angstrom, 0.0*degree, 0.0*degree)

    sim_params = SimulationParameters()
    sim_params.me_if_approx = SimulationParameters.ISGISAXSMOR
    simulation.setSimulationParameters(sim_params)
 
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
    f = gzip.open(path+'../../ReferenceData/BornAgain/isgisaxs07_reference.ima.gz', 'rb')
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
    return "IsGISAXS07", "Mixture of different particles defined in morphology file", status


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    name,description,status = runTest()
    print name,description,status
    if("FAILED" in status) : exit(1)
