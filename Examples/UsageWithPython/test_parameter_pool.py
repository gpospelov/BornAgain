import sys, os
from numpy import linspace, array, zeros
import pylab
from matplotlib.colors import LogNorm

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', 'lib')))

from libScattCore import *


# ------------------------
# building mesocrystal
# see access to
# ------------------------

def BuildSample():
  R = 6.1*nanometer
  lattice = Lattice.createTrigonalLattice(R*2.0, R*2.0*2.3)
  bas_a = lattice.getBasisVectorA()
  bas_b = lattice.getBasisVectorB()
  bas_c = lattice.getBasisVectorC()

  n_particle = complex(1.0-1.5e-5, 1.3e-6)
  sphere_ff = FormFactorFullSphere(R)
  particle = NanoParticle(n_particle, sphere_ff )

  position_0 = kvector_t(0.0, 0.0, 0.0)
  position_1 = kvector_t(0.0, 0.0, 0.0)
  position_2 = kvector_t(0.0, 0.0, 0.0)

  position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c)
  position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c)

  basis = LatticeBasis()
  basis.addParticle(particle, position_0)
  basis.addParticle(particle, position_1)
  basis.addParticle(particle, position_2)

  npc = NanoParticleCrystal(basis, lattice)

  cylinder_ff = FormFactorCylinder(0.2*micrometer, 300*nanometer)
  meso = MesoCrystal(npc, cylinder_ff )

  pyramid_ff = FormFactorPyramid(0.2*micrometer, 300*nanometer, 84*degree)
  meso2 = MesoCrystal(npc, pyramid_ff )

  # adding mesocrystals in air layer, and then on substrate
  # ------------------------
  multi_layer = MultiLayer()
  n_air = complex(1.0, 0.0)
  n_substrate = complex(1.0-3.5e-6, 7.8e-8)
  matMng = MaterialManager.instance()
  air_material = matMng.addHomogeneousMaterial("Air", n_air )
  substrate_material = matMng.addHomogeneousMaterial("Substrate", n_substrate )

  air_layer = Layer()
  air_layer.setMaterial(air_material)
  substrate_layer = Layer()
  substrate_layer.setMaterial(substrate_material)

  interference_funtion = InterferenceFunction1DParaCrystal(800.0*nanometer,50*nanometer, 1e7*nanometer)
  particle_decoration = NanoParticleDecoration()
  particle_decoration.addNanoParticle(meso, 0.0, 0.5)
  particle_decoration.addNanoParticle(meso2, 0.0, 0.5)
  particle_decoration.addInterferenceFunction(interference_funtion)
  air_layer_decorator = LayerDecorator(air_layer, particle_decoration)

  multi_layer.addLayer(air_layer_decorator)
  multi_layer.addLayer(substrate_layer)
  return multi_layer



# ---------------------------------------------------
def main():
  print "------ Sample ------"
  multi_layer = BuildSample()
  multi_layer.walk_and_print()

  print "------ Pool --------"
  pool = multi_layer.createParameterTree()
  print pool

  # one way to change parameters
  pool.setParameterValue("/MultiLayer/LayerInterface/roughness/corrlength",99.)

  #another way to change several parameters at once
  pool.setMatchedParametersValue("/*NanoParticleInfo*/depth",88)

  # third way to change parameters
  p = pool.getParameter("/MultiLayer/LayerDecorator/NanoParticleDecoration/NanoParticleInfo1/MesoCrystal/FormFactorPyramid/half_side")
  p.setValue(77.)

  print "------ Sample with changed parameters ------"
  multi_layer.walk_and_print()


  
# ---------------------------------------------------
if __name__ == '__main__':
  main()



  
#pool = multi_layer.createParameterTree()