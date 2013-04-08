#
# extending C++ ISampleBuilder class in python
#
# The idea is following. We derive python's MySampleBuilder class from C++ ISampleBuilder.
# MySampleBuilder has set of registered parameters and redefined method 'buildSample' which
# build and return some complicated sample
#
# MySampleBuilder is passed to the GISASFWExperiment instance (i.e. inside C++) and then experiment (C++) can
# call MySampleBuilder (python) for new sample.
import sys, os
from numpy import linspace, array, zeros, pi, sqrt
import pylab
from matplotlib.colors import LogNorm
import matplotlib.pyplot as plt
import ctypes

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libScattCore import *


#-----------------------------------------------------------
# Cylinders with interference
# Function constructs sample depending on three parameters
#-----------------------------------------------------------
def BuildSample(m_layer_thickness, m_cylinder_height, m_cylinder_radius):
    n_particle = complex(1.0-5e-5, 2e-8)
    p_air_material = MaterialManager.instance().addHomogeneousMaterial("Air", 1.0, 0.0)
    p_layer_material = MaterialManager.instance().addHomogeneousMaterial("Layer", 1.0-2e-6, 2e-8)
    p_substrate_material = MaterialManager.instance().addHomogeneousMaterial("Substrate", 1.0-2e-6, 2e-8)

    air_layer = Layer(p_air_material)
    middle_layer = Layer(p_layer_material, m_layer_thickness)
    substrate_layer = Layer(p_substrate_material)

    interference_funtion = InterferenceFunction1DParaCrystal(20.0*nanometer, 7*nanometer, 1e7*nanometer)
    ff_cylinder = FormFactorCylinder(m_cylinder_height, m_cylinder_radius)
    nano_particle = Particle(n_particle, ff_cylinder )
    particle_collection = ParticleDecoration()
    particle_collection.addParticle(nano_particle)
    particle_collection.addInterferenceFunction(interference_funtion)
    layer_with_particles = LayerDecorator(air_layer, particle_collection)

    p_multi_layer = MultiLayer()
    p_multi_layer.addLayer(layer_with_particles)
    p_multi_layer.addLayer(middle_layer)
    p_multi_layer.addLayer(substrate_layer)
    return p_multi_layer


# ---------------------------------------------------------------
# defining SampleBuilder class which will build samples for us
# 
# ---------------------------------------------------------------
class MySampleBuilder(ISampleBuilder):
    def __init__(self):
        ISampleBuilder.__init__(self)
        print "MySampleBuilder ctor"
        self.sample = ISample() # this should be the  class variable to increment reference counter and hold object created in buildSample while C++ processes it
        self.layer_thickness = ctypes.c_double(10.0*nanometer)
        self.cylinder_height = ctypes.c_double(5.0*nanometer)
        self.cylinder_radius = ctypes.c_double(5.0*nanometer)
        self.getParameterPool().registerParameter("layer_thickness", ctypes.addressof( self.layer_thickness ) )
        self.getParameterPool().registerParameter("cylinder_height", ctypes.addressof( self.cylinder_height ) )
        self.getParameterPool().registerParameter("cylinder_radius", ctypes.addressof( self.cylinder_radius ) )

    def buildSample(self):
        self.sample = BuildSample(self.layer_thickness.value, self.cylinder_height.value, self.cylinder_radius.value)
        #sample.print_structure()
        return self.sample


# ---------------------------------------------------------------
# building sample, experiment, run calculations and plot output
# ---------------------------------------------------------------
def main():
  builder = MySampleBuilder()
  pool = builder.createParameterTree() # create pool of parameters
  print pool
  #sample.print_structure()

  experiment = GISASExperiment()
  experiment.setDetectorParameters(100, 0.0*degree, 2.0*degree,100 , 0.0*degree, 2.0*degree)
  experiment.setBeamParameters(1.0*angstrom, -0.2*degree, 0.0*degree)
  experiment.setBeamIntensity(1e10)
  experiment.setSampleBuilder(builder)

  cylinder_radiuses = [1., 5., 10. ]
  for i in range(0, len(cylinder_radiuses)):
    rad = cylinder_radiuses[i]
    pool.setParameterValue("/SampleBuilder/cylinder_radius",rad)
    experiment.runSimulation()

    fg1 = pylab.figure(1+i)
    x = GetOutputDataAxis(experiment, 0)
    y = GetOutputDataAxis(experiment, 1)
    output = GetOutputData(experiment)

    x = x*180./3.1415926
    y = y*180./3.1415926

    X,Y = pylab.meshgrid(x,y)
    pylab.pcolormesh(Y,X,output,  norm=LogNorm(0.1, 1e+04) )
    pylab.ylim([0,y.max()])
    pylab.xlim([0,x.max()])
    pylab.colorbar()

  pylab.show()


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  main()
  #pylab.ion()

  #fig1 = pylab.figure()
  #fig1.add_subplot(111).plot([1,2],[3,4])
  ##pylab.draw()

  #fig2 = pylab.figure()
  #fig2.add_subplot(111).plot([5,6],[10,9])
  ##pylab.draw()

  #pylab.show()



