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
    matMng = MaterialManager.instance()
    mAmbience = matMng.addHomogeneousMaterial("Air", 1.0, 0.0 )
    # collection of particles
    n_particle = complex(1.0-6e-4, 2e-8)   
    particle_decoration = ParticleDecoration()

    #PositionParticleInfo particle_info1(new Particle(n_particle, ff1), 0, pos1, 0.5);
    #particle_decoration.addParticleInfo(particle_info1);
    #
    # add particle number 1:
    ff1 = FormFactorBox(1.0*nanometer, 1.0*nanometer,1.0*nanometer)
    pos1 = kvector_t(0.0*nanometer, 0.0*nanometer, 0.0)
    particle1 = Particle(n_particle, ff1)
    particle_info1 = PositionParticleInfo(particle1, pos1, 0.5)
    particle_decoration.addParticleInfo(particle_info1)
    #add particle number 2:
    ff2 = FormFactorBox(1.0*nanometer, 2.0*nanometer,1.0*nanometer)
    pos2 = kvector_t(5.0*nanometer, 5.0*nanometer, 0.0)
    rotate3d2 = RotateZ3D(10*degree)
    p_rot2 = Transform3D(rotate3d2)
    particle2 = Particle(n_particle, ff2)   
    particle_info2 = PositionParticleInfo(particle2, p_rot2, pos2, 0.5)
    particle_decoration.addParticleInfo(particle_info2)
    #add particle number 3:
    ff3 = FormFactorBox(1.0*nanometer, 3.0*nanometer,1.0*nanometer)
    pos3 = kvector_t(-5.0*nanometer, -5.0*nanometer, 0.0)
    rotate3d3 = RotateZ3D(20*degree)
    p_rot3 = Transform3D(rotate3d3)   
    particle3 = Particle(n_particle, ff3)
    particle_info3 = PositionParticleInfo(particle3, p_rot3, pos3, 0.5)
    particle_decoration.addParticleInfo(particle_info3)
    #add particle number 4:
    ff4 = FormFactorBox(1.0*nanometer, 4.0*nanometer,1.0*nanometer)
    pos4 = kvector_t(5.0*nanometer, -5.0*nanometer, 0.0)
    rotate3d4 = RotateZ3D(30*degree)
    p_rot4 = Transform3D(rotate3d4)   
    particle4 = Particle(n_particle, ff4)   
    particle_info4 = PositionParticleInfo(particle4, p_rot4, pos4, 0.5)
    particle_decoration.addParticleInfo(particle_info4)
    #add particle number 5:
    ff5 = FormFactorBox(1.0*nanometer, 5.0*nanometer,1.0*nanometer)
    pos5 = kvector_t(-5.0*nanometer, 5.0*nanometer, 0.0)
    rotate3d5 = RotateZ3D(40*degree)
    p_rot5 = Transform3D(rotate3d5)   
    particle5 = Particle(n_particle, ff5)   
    particle_info5 =  PositionParticleInfo(particle5, p_rot5, pos5, 0.5)
    particle_decoration.addParticleInfo(particle_info5)
    #add particle number 6:
    ff6 = FormFactorBox(1.0*nanometer, 1.0*nanometer,1.0*nanometer)
    pos6 = kvector_t(0.0*nanometer, 0.0*nanometer, 0.0)
    rotate3d6 = RotateZ3D(50*degree)
    p_rot6 = Transform3D(rotate3d6)
    particle6 = Particle(n_particle, ff6)   
    particle_info6 = PositionParticleInfo(particle6, p_rot6, pos6, 0.5)
    particle_decoration.addParticleInfo(particle_info6)
    #add particle number 7:
    ff7 = FormFactorBox(1.0*nanometer, 2.0*nanometer,1.0*nanometer)
    pos7 = kvector_t(5.0*nanometer, 5.0*nanometer, 0.0)
    rotate3d7 = RotateZ3D(60*degree)
    p_rot7 = Transform3D(rotate3d7)
    particle7 = Particle(n_particle, ff7)
    particle_info7 = PositionParticleInfo(particle7, p_rot7, pos7, 0.5)
    particle_decoration.addParticleInfo(particle_info7)
    #add particle number 8:
    ff8 = FormFactorBox(1.0*nanometer, 3.0*nanometer,1.0*nanometer)
    pos8 = kvector_t(-5.0*nanometer, -5.0*nanometer, 0.0)
    rotate3d8 = RotateZ3D(70*degree)
    p_rot8 = Transform3D(rotate3d8)
    particle8 = Particle(n_particle, ff8)    
    particle_info8 = PositionParticleInfo(particle8 , p_rot8, pos8, 0.5)
    particle_decoration.addParticleInfo(particle_info8)
    #add particle number 9:
    ff9 = FormFactorBox(1.0*nanometer, 4.0*nanometer,1.0*nanometer)
    pos9 = kvector_t(5.0*nanometer, -5.0*nanometer, 0.0)
    rotate3d9 = RotateZ3D(80*degree)
    p_rot9 = Transform3D(rotate3d9)
    particle9 = Particle(n_particle, ff9)     
    particle_info9 = PositionParticleInfo(particle9, p_rot9, pos9, 0.5)
    particle_decoration.addParticleInfo(particle_info9)
    #add particle number 10:
    ff10 = FormFactorBox(1.0*nanometer, 5.0*nanometer,1.0*nanometer)
    pos10 = kvector_t(-5.0*nanometer, 5.0*nanometer, 0.0)
    rotate3d10 = RotateZ3D(90*degree)
    p_rot10 = Transform3D(rotate3d10)
    particle10 = Particle(n_particle, ff10)
    particle_info10 = PositionParticleInfo(particle10, p_rot10, pos10, 0.5)
    particle_decoration.addParticleInfo(particle_info10)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(mAmbience)
    air_layer_decorator = LayerDecorator(air_layer, particle_decoration)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer_decorator)
  
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
    return GetOutputData(simulation)


# ----------------------------------
# read reference data from file
# ----------------------------------
def GetReferenceData():
    path = os.path.split(__file__)[0]
    if path: path +="/"
    f = gzip.open(path+'../TestCore/IsGISAXS07/isgisaxs07_reference.ima.gz', 'rb')
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
def RunTest():
    result = RunSimulation()
    reference = GetReferenceData()

    diff = GetDifference(result, reference)
    status = "OK"
    if(diff > 1e-10 or numpy.isnan(diff)): status = "FAILED"
    print diff
    return "IsGISAXS07", "Mixture of different particles defined in morphology file", status


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  name,description,status = RunTest()
  print name,description,status


