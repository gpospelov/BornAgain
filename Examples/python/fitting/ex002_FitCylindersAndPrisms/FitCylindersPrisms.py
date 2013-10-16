"""
Fitting example
In this example we use a simple geometry: cylinders and prisms in
air layer, deposited on a substrate layer, with no interference. 
There are 4 fitting parameters: radius and height of cylinders and
 side length and height of prisms. 
 
Our reference data is 2D intensity map obtained from the simulation of
the same geometry with fixed values cylinder_height = prism3_height
 = cylinder_radius = prism3_half_side = 5nm.
 
Then we run our minimization consequently using Minuit2, Migrad algorithm 
as a minimization engine, with cylinder_height = prism3_length = 4nm, 
cylinder_radius = prism3_half_side = 6nm as initial fit parameter values.
"""

import sys, os, numpy
import math
import time

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))


from libBornAgainCore import *
from libBornAgainFit import *

# values we want to find
cylinder_height = 5.0*nanometer
cylinder_radius = 5.0*nanometer
prism3_half_side = 5.0*nanometer
prism3_height = 5.0*nanometer

# -----------------------------------------------------------------------------
# create sample : cylinders and prisms in the air on substrate layer
# -----------------------------------------------------------------------------
def buildSample(): 
    """
    create sample : cylinders and prisms in the air on substrate layer
    """
    # defining materials
    mAmbience = MaterialManager.getHomogeneousMaterial("Air", 0.0, 0.0 ) #: Air material
    mSubstrate = MaterialManager.getHomogeneousMaterial("Substrate", 6e-6, 2e-8 ) 
    mParticle = MaterialManager.getHomogeneousMaterial("Particle", 6e-4, 2e-8 )
    # collection of particles
    cylinder_ff = FormFactorCylinder(cylinder_height, cylinder_radius)
    cylinder = Particle(mParticle, cylinder_ff)
    prism_ff = FormFactorPrism3(prism3_height,  prism3_half_side)
    prism = Particle(mParticle, prism_ff)
    particle_decoration = ParticleDecoration()
    particle_decoration.addParticle(cylinder, 0.0, 0.5)
    particle_decoration.addParticle(prism,0.0, 0.5)  
    interference = InterferenceFunctionNone()
    particle_decoration.addInterferenceFunction(interference)
    # air layer with particles and substrate form multi layer
    air_layer = Layer(mAmbience)
    air_layer.setDecoration(particle_decoration)
    substrate_layer = Layer(mSubstrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


# -----------------------------------------------------------------------------
# create sample : input beam and detector - characteristics
# -----------------------------------------------------------------------------
def createSimulation():
    """
    create sample : input beam and detector - characteristics
    """
    simulation = Simulation()
    simulation.setDetectorParameters(100, 0.0*degree, 2.0*degree,100 , 0.0*degree, 2.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    #simulation.setBeamIntensity(1e10) # to leave or not
    return simulation


# TO MODIFY - GENERATE INPUT DATA FILE
# generating "real" data by adding noise to the simulated data
#def createRealData(simulation):
#    simulation.runSimulation()
#    real_data = simulation.getOutputDataClone()
#    noise_factor = 0.1
#    for i in range(0,real_data.getAllocatedSize()):
#        amplitude = real_data[i]
#        sigma = noise_factor*math.sqrt(amplitude)
#        noisy_amplitude = GenerateNormalRandom(amplitude, sigma)
#        if(noisy_amplitude < 0.0) : noisy_amplitude = 0.0
#        real_data[i] = noisy_amplitude
#    OutputDataIOFactory.writeOutputData(real_data,'Refdata_fitcylinderprisms.txt')
#    return real_data

# ----------------------------------
# read "real" data from file
# ----------------------------------
def GetRealData():
    """
    read "real" data from file
    """
    real_data = OutputDataIOFactory.getOutputData('Refdata_fitcylinderprisms.txt')
    #OutputDataIOFactory.writeOutputData(real_data1,'Refdata_fitcylinderprisms1.ima')
    #f = open('Refdata_fitcylinderprisms.ima', 'r')
    #real_data1=numpy.fromstring(f.read(),numpy.float64,sep=' ')
    #f.close()
    return real_data


# -----------------------------------------------------------------------------
# run fitting 
# -----------------------------------------------------------------------------
def run_fitting():
    """
    run minimization
    """
    sample = buildSample()
    simulation = createSimulation()
    simulation.setSample(sample)

    # get the real data, which is simply results of our simulation with default values
    real_data = GetRealData()
    
    #real_data = createRealData(simulation) 
    #PlotNumpyArray(GetOutputData(simulation))

    # run the simulation
    simulation.runSimulation()

    # linking real and numerical (to be fitted) data
    #chiModule = ChiSquaredModule()
    #chiModule.setOutputDataNormalizer( OutputDataSimpleNormalizer(1.0,0) )
    #chiModule.setChiSquaredFunction( SquaredFunctionWithSystematicError() )
    #chiModule.setChiSquaredFunction( SquaredFunctionWithSystematicError() )
    fitSuite = FitSuite()
    fitSuite.addSimulationAndRealData(simulation, real_data)#, chiModule)

    MinimizerFactory.printCatalogue()

    options = MinimizerOptions()

    options.setMaxFunctionCalls(5)
    fitSuite.getMinimizer().setOptions(options)

    print options.getTolerance(), options.getMaxIterations()

    # setting fitting minimizer
    #fitSuite.setMinimizer(MinimizerFactory.createMinimizer("Minuit2","Migrad")) #: Minuit2, Migrad
    #fitSuite.setMinimizer(MinimizerFactory.createMinimizer ("Minuit2","Simplex"))
    #fitSuite.setMinimizer(MinimizerFactory.createMinimizer("Minuit2","Combined"))
    #fitSuite.setMinimizer(MinimizerFactory.createMinimizer ("Minuit2","Scan"))
    #fitSuite.setMinimizer(MinimizerFactory.createMinimizer("Minuit2" ,"Fumili"))
    #fitSuite.setMinimizer(MinimizerFactory.createMinimizer("GSLMultiMin","ConjugateFR"))
    #fitSuite.setMinimizer(MinimizerFactory.createMinimizer("GSLMultiMin","ConjugatePR"))
    #fitSuite.setMinimizer(MinimizerFactory.createMinimizer("GSLMultiMin","BFGS"))
    # fitSuite.setMinimizer(MinimizerFactory.createMinimizer("GSLMultiMin","BFGS2"))
    #fitSuite.setMinimizer(MinimizerFactory.createMinimizer("GSLMultiMin","SteepestDescent"))
    #fitSuite.setMinimizer(MinimizerFactory.createMinimizer("GSLMultiFit",""))
    #fitSuite.setMinimizer(MinimizerFactory.createMinimizer("GSLSimAn",""))

     #fitSuite.initPrint(20)
  
    # setting fitting parameters
    fitSuite.addFitParameter("*FormFactorCylinder/height", 4.*nanometer, 0.01*nanometer, AttLimits.lowerLimited(0.01) )
    fitSuite.addFitParameter("*FormFactorCylinder/radius", 6.*nanometer, 0.01*nanometer, AttLimits.lowerLimited(0.01) )
    fitSuite.addFitParameter("*FormFactorPrism3/height", 4.*nanometer, 0.01*nanometer, AttLimits.lowerLimited(0.01) )
    fitSuite.addFitParameter("*FormFactorPrism3/half_side", 6.*nanometer, 0.01*nanometer, AttLimits.lowerLimited(0.01) )

    # run fit
    start_time = time.time()
    fitSuite.runFit()
    real_time = time.time() - start_time
    print "            RealTime : {0:.3f} sec".format(real_time)
    
    # analysing fit results
    #initialParameters = [cylinder_height, cylinder_radius,prism3_height, prism3_half_side]
    #results = fitSuite.getFitParameters().getValues()

    # print fit results
    fitSuite.printResults()
    
    # threshold = 1.0e-02
    #status = "OK"
    #for i in range(0, len(initialParameters)):
    #    diff = abs(results[i] - initialParameters[i])/initialParameters[i]
    #    if(diff > threshold): status = "FAILED"
    #return# status

   


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    #status=run_fitting()
    #print status
    #if("FAILED" in status) : exit(1)
    run_fitting()


  
