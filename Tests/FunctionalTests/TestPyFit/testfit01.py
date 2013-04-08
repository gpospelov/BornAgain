# functional test: two parameter fit using variety of minimizers
#
# In this test we are using simple geometry: cylinders without interference in
# air layer with two parameters (radius and height of cylinders), describing
# the sample. Our "real" data is 2D intensity map obtained from the simulation of
# the same geometry with fixed values height = 5nm and radius = 5nm.
# Then we run our minimization consequently using different minimization engines,
# with height=4nm, radius=6nm as starting fit parameter values.


import sys
import os
import numpy
import time

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *
from libBornAgainFit import *

# sample parameters we are going to find
cylinder_height = 5*nanometer
cylinder_radius = 5*nanometer

# minimizer name and type of minimization algorithm
Minimizers = [ 
    ("Minuit2","Migrad"), 
    ("Minuit2","Fumili"), 
    ("GSLMultiMin","BFGS"),
    ("GSLMultiMin","SteepestDescent"),
    ("GSLMultiFit",""),
#    ("GSLSimAn","")
]


# -----------------------------------------------------------------------------
# run several minimization rounds using different minimizers
# -----------------------------------------------------------------------------
def runTest():
  #print "**********************************************************************"
  #print "*  Starting  TestFit01                                               *"
  #print "**********************************************************************"
  nTest=0
  status = "OK"
  for m in Minimizers:
    minimizer_name = m[0]
    minimizer_algorithm = m[1]
    print "Minimizer {0:-2d}   {1:}({2:})".format(nTest, minimizer_name, minimizer_algorithm)
    result_ok = run_fitting(minimizer_name, minimizer_algorithm)
    nTest+=1
    if not result_ok: status = "FAILED"

  return "TestFit01", "Two parameters fit using variety of minimizers.", status


# -----------------------------------------------------------------------------
# run fitting specified minimizer
# -----------------------------------------------------------------------------
def run_fitting(minimizer_name, minimizer_algorithm):
  sample = buildSample()
  simulation = createSimulation()
  simulation.setSample(sample)

  # creating real data, which is simply results of our simulation with default values
  simulation.runSimulation()
  real_data = simulation.getOutputDataClone()

  # setting fit suite
  fitSuite = FitSuite()
  fitSuite.setMinimizer( MinimizerFactory.createMinimizer(minimizer_name, minimizer_algorithm) )
  fitSuite.addFitParameter("*height", 4.*nanometer, 0.04*nanometer, AttLimits.lowerLimited(0.01) )
  fitSuite.addFitParameter("*radius", 6.*nanometer, 0.06*nanometer, AttLimits.lowerLimited(0.01) )
  fitSuite.addSimulationAndRealData(simulation, real_data)

  # run fit
  start_time = time.time()
  fitSuite.runFit()
  real_time = time.time() - start_time

  height_found = fitSuite.getMinimizer().getValueOfVariableAtMinimum(0)
  height_diff = abs(height_found - cylinder_height)/cylinder_height
  radius_found = fitSuite.getMinimizer().getValueOfVariableAtMinimum(1)
  radius_diff = abs(radius_found - cylinder_radius)/cylinder_radius

  print "            RealTime : {0:.3f} sec".format(real_time)
  print "            NCalls   : {0:<5d}".format(fitSuite.getNCalls())
  print '            par1     : {0:.4f} ({1:.3g}) '.format(height_found, height_diff)
  print '            par2     : {0:.4f} ({1:.3g}) '.format(radius_found, radius_diff)

  diff = 1.0e-02
  isSuccess = True
  if( (height_diff > diff) or (radius_diff > diff) ) : isSuccess=False
  return isSuccess



# -----------------------------------------------------------------------------
# create cylinders in the air
# -----------------------------------------------------------------------------
def buildSample():
    cylinder_ff = FormFactorCylinder(cylinder_height, cylinder_radius)
    n_particle = complex(1.0-6e-4, 2e-8)
    cylinder = Particle(n_particle, cylinder_ff)
    interference = InterferenceFunctionNone()

    particle_decoration = ParticleDecoration()
    particle_decoration.addParticle(cylinder)
    particle_decoration.addInterferenceFunction(interference)

    mAmbience = MaterialManager.getHomogeneousMaterial("Air", 1.0, 0.0 )
    air_layer = Layer(mAmbience)
    air_layer_decorator = LayerDecorator(air_layer, particle_decoration)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer_decorator)

    return multi_layer


def createSimulation():
    simulation = Simulation();
    simulation.setDetectorParameters(100, 0.0*degree, 2.0*degree,100 , 0.0*degree, 2.0*degree);
    simulation.setBeamParameters(1.0*angstrom, -0.2*degree, 0.0*degree);
    simulation.setBeamIntensity(1e10);
    return simulation


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  name,description,status = runTest()
  print name,description,status


