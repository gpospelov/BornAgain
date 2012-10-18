# Example shows how to build sample (cylinders with interference on top of substrate)
# and get access to sample's parameters after the build was completed
#
# For that we use ParameterPool - container of sample's parameters

import sys, os
from numpy import linspace, array, zeros
import pylab
from matplotlib.colors import LogNorm

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libScattCore import *


# ----------------------------------------------------------
# building cylinders with interference on top of substrate
# ----------------------------------------------------------
def BuildSample():
  # creating materials
  n_air = complex(1.0, 0.0)
  n_substrate = complex(1.0-5e-6, 2e-8)
  n_particle = complex(1.0-5e-5, 2e-8)
  air_material = MaterialManager.instance().addHomogeneousMaterial("Air", n_air)
  substrate_material = MaterialManager.instance().addHomogeneousMaterial("Substrate", n_substrate)
  # creating layers
  air_layer = Layer()
  air_layer.setMaterial(air_material)
  substrate_layer = Layer()
  substrate_layer.setMaterial(substrate_material)
  # creating nanoparticle
  ff_cylinder = FormFactorCylinder(5*nanometer, 5*nanometer)
  nano_particle = Particle(n_particle, ff_cylinder)
  # creating particle decoration which is group of particles with given interference function
  interference_function = InterferenceFunction1DParaCrystal(20.0*nanometer, 7*nanometer, 1e7*nanometer)
  particle_decoration = ParticleDecoration()
  particle_decoration.addParticle(nano_particle)
  particle_decoration.addInterferenceFunction(interference_function)
  # decorating air layer with particle decoration
  air_layer_decorator = LayerDecorator(air_layer, particle_decoration)
  # building multi layer and stacking two layers
  multi_layer = MultiLayer()
  multi_layer.addLayer(air_layer_decorator)
  multi_layer.addLayer(substrate_layer)
  return multi_layer


# ---------------------------------------------------
def main():
  print "------ Sample ------"
  multi_layer = BuildSample()
  multi_layer.print_structure() # print on the screen the structure of our sample

  print "------ Pool --------"
  pool = multi_layer.createParameterTree() # create pool of parameters
  print pool

  # starting to change values of sample's parameters
  # one way to change parameters
  pool.setParameterValue("/MultiLayer/Layer/thickness",99.)

  #another way to change several parameters at once
  pool.setMatchedParametersValue("/*ParticleInfo*/depth",88)

  # third way to change parameters
  p = pool.getParameter("/MultiLayer/LayerDecorator/ParticleDecoration/ParticleInfo/Particle/FormFactorCylinder/radius")
  p.setValue(77.)

  print "------ Sample with changed parameters ------"
  multi_layer.print_structure()

# ---------------------------------------------------
if __name__ == '__main__':
  main()

