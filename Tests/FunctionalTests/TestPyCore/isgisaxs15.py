# IsGISAXS015 example: Size spacing correlation approximation
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
    n_particle = complex(1.0-6e-4, 2e-8)
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    interference = InterferenceFunction1DParaCrystal(15.0*nanometer,5*nanometer, 1e3*nanometer)
    interference.setKappa(4.02698)
    particle_decoration = ParticleDecoration()
    particle_prototype = Particle(n_particle, cylinder_ff)
    stochastic_radius = StochasticSampledParameter(StochasticDoubleGaussian(5.0*nanometer, 1.25*nanometer), 30, 2)
    
    particle_builder = ParticleBuilder()
    particle_builder.setPrototype(particle_prototype, "/Particle/FormFactorCylinder/radius", stochastic_radius)
    particle_builder.plantParticles(particle_decoration)
    #Set height of each particle to its radius (H/R fixed)
    p_parameters = particle_decoration.createParameterTree()
    nbr_replacements = p_parameters.fixRatioBetweenParameters("height", "radius", 1.0)
    #print "Number of replacements: ", nbr_replacements
    particle_decoration.addInterferenceFunction(interference)    
    
    air_layer = Layer(mAmbience)
    air_layer_decorator = LayerDecorator(air_layer, particle_decoration)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer_decorator)
   
    # build and run experiment
    simulation = Simulation()
    simulation.setDetectorParameters(150,0.05*degree, 1.5*degree, 150, 0.05*degree, 1.5*degree, True)
    simulation.setBeamParameters(1.0*angstrom, -0.2*degree, 0.0*degree)

    sim_params = SimulationParameters()
    sim_params.me_if_approx = SimulationParameters.SSCA
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
    f = gzip.open(path+'../../ReferenceData/BornAgain/isgisaxs15_reference.ima.gz', 'rb')
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
    return "IsGISAXS15", "Size spacing correlation approximation", status


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    name,description,status = runTest()
    print name,description,status
    if("FAILED" in status) : exit(1)

