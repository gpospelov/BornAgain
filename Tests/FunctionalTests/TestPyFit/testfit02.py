# functional test: fitting using sample builder
#
# This test shows how to use SampleBuilder class for constructing the sample
# and running fitting.


import sys
import os
import numpy
import time
import ctypes
import math

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *
from libBornAgainFit import *



# -----------------------------------------------------------------------------
# run several minimization rounds using different minimizers
# -----------------------------------------------------------------------------
def runTest():
  #print "**********************************************************************"
  #print "*  Starting  TestFit02                                               *"
  #print "**********************************************************************"

  sample_builder = MySampleBuilder()

  simulation = createSimulation()
  simulation.setSampleBuilder(sample_builder)

  real_data = createRealData(simulation)


  status = "OK"
  return "TestFit02", "Ffitting using sample builder.", status


# create simulation
def createSimulation():
    simulation = Simulation();
    simulation.setDetectorParameters(100, 0.0*degree, 2.0*degree,100 , 0.0*degree, 2.0*degree);
    simulation.setBeamParameters(1.0*angstrom, -0.2*degree, 0.0*degree);
    simulation.setBeamIntensity(1e10);
    return simulation


# generating "real" data by adding noise to the simulated data
def createRealData(simulation):
  #x= vdouble1d_t()
  #print x.size()
  simulation.runSimulation();
  real_data = simulation.getOutputDataClone()
  noise_factor = 0.1
  for i in range(0,real_data.size()):
    print i, real_data[i], real_data.toCoordinate(i,0), real_data.toCoordinate(i,1)
    amplitude = real_data[i]
    sigma = noise_factor*math.sqrt(amplitude)
    noisy_amplitude = GenerateNormalRandom(amplitude, sigma)
    if(noisy_amplitude < 0.0) : mnoisy_amplitude = 0.0
    real_data[i] = noisy_amplitude


# ----------------------------------------------------------------------------
# Sample builder to build mixture of cylinders and prisms on top of substrate
# 5 parameters
# ----------------------------------------------------------------------------
class MySampleBuilder(ISampleBuilder):
    def __init__(self):
      ISampleBuilder.__init__(self)
      print "MySampleBuilder ctor"
      self.sample = None
      # parameters describing the sample
      self.cylinder_height  = ctypes.c_double(5.0*nanometer)
      self.cylinder_radius = ctypes.c_double(5.0*nanometer)
      self.prism3_half_side = ctypes.c_double(5.0*nanometer)
      self.prism3_height = ctypes.c_double(5.0*nanometer)
      self.cylinder_ratio = ctypes.c_double(0.2)
      # register parameters
      self.getParameterPool().registerParameter("m_cylinder_height", ctypes.addressof(self.cylinder_height) )
      self.getParameterPool().registerParameter("m_cylinder_radius", ctypes.addressof(self.cylinder_radius) )
      self.getParameterPool().registerParameter("m_prism3_half_side", ctypes.addressof(self.prism3_half_side) )
      self.getParameterPool().registerParameter("m_prism3_height", ctypes.addressof(self.prism3_height) )
      self.getParameterPool().registerParameter("m_cylinder_ratio", ctypes.addressof(self.cylinder_ratio) )

    # constructs the sample for current values of parameters
    def buildSample(self):
      multi_layer = MultiLayer()
      air_material = MaterialManager.getHomogeneousMaterial("Air", 1.0, 0.0)
      substrate_material = MaterialManager.getHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8)
      air_layer = Layer(air_material)
      substrate_layer = Layer(substrate_material)

      n_particle = complex(1.0-6e-4, 2e-8)
      cylinder_ff = FormFactorCylinder( self.cylinder_height.value, self.cylinder_radius.value)
      prism_ff = FormFactorPrism3( self.prism3_height.value, self.prism3_half_side.value)
      cylinder = Particle(n_particle, cylinder_ff)
      prism = Particle(n_particle, prism_ff)
      interference = InterferenceFunctionNone()

      particle_decoration = ParticleDecoration()
      particle_decoration.addParticle(cylinder, self.cylinder_ratio.value)
      particle_decoration.addParticle(prism, 1.0 - self.cylinder_ratio.value)
      particle_decoration.addInterferenceFunction(interference)
      
      layer_with_particles = LayerDecorator(air_layer, particle_decoration)
      multi_layer.addLayer(layer_with_particles)
      multi_layer.addLayer(substrate_layer)
      self.sample = multi_layer
      return self.sample


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  name,description,status = runTest()
  print name,description,status

