#
# building meso crystal and running the simulation
#
import sys, os
from numpy import linspace, array, zeros, pi, sqrt
import pylab
from matplotlib.colors import LogNorm
import matplotlib.pyplot as plt

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libScattCore import *

M_PI = pi
m_meso_radius = 1000*nanometer
m_surface_filling_ratio = 0.25
m_meso_height = 0.5*micrometer
m_sigma_meso_height = 4*nanometer
m_sigma_meso_radius = 50*nanometer
m_lattice_length_a = 6.2*nanometer
m_nanoparticle_radius = 4.3*nanometer
m_sigma_nanoparticle_radius = 0.14*nanometer
m_sigma_lattice_length_a = 1.5*nanometer
m_roughness = 1.0*nanometer


# --------------------------------------
# building mesocrystal
# ---------------------------------------
def createMesoCrystal(stacking_radius, n_particle, p_meso_form_factor):
  p_lat = createLattice(stacking_radius)
  bas_a = p_lat.getBasisVectorA()
  bas_b = p_lat.getBasisVectorB()
  bas_c = p_lat.getBasisVectorC()
  ff_sphere = FormFactorSphereGaussianRadius(m_nanoparticle_radius, m_sigma_nanoparticle_radius)
  particle = Particle(n_particle, ff_sphere )
  position_0 = kvector_t(0.0, 0.0, 0.0)
  position_1 = kvector_t(0.0, 0.0, 0.0)
  position_2 = kvector_t(0.0, 0.0, 0.0)

  position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c)
  position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c)
  positions = [ position_0, position_1, position_2 ]
  basis = LatticeBasis()
  basis.addParticle(particle, positions)

  npc = Crystal(basis, p_lat)
  dw_factor = m_sigma_lattice_length_a*m_sigma_lattice_length_a/6.0
  npc.setDWFactor(dw_factor)
  meso = MesoCrystal(npc, p_meso_form_factor)
  return meso


# --------------------------------------
# building lattice
# ---------------------------------------
def createLattice(stacking_radius):
  lattice = Lattice.createTrigonalLattice(stacking_radius*2.0, stacking_radius*2.0*2.3)
  p_result = Lattice(lattice)
  selection_rule = SimpleSelectionRule(-1, 1, 1, 3)
  p_result.setSelectionRule( selection_rule )
  return p_result


# ------------------------
# building sample
# ------------------------
def BuildWholeSample():

  surface_density = m_surface_filling_ratio/M_PI/m_meso_radius/m_meso_radius
  n_particle = complex(1.0-2.84e-5, 4.7e-7)
  avg_n_squared_meso = complex(0.7886*n_particle*n_particle + 0.2114)
  n_avg = complex( sqrt(m_surface_filling_ratio*avg_n_squared_meso + 1.0 - m_surface_filling_ratio) )
  n_particle_adapted = complex( sqrt(n_avg*n_avg + n_particle*n_particle - 1.0) )

  ff_cyl = FormFactorCylinder(m_meso_height, m_meso_radius)
  ff_meso = FormFactorDecoratorDebyeWaller(ff_cyl, m_sigma_meso_height*m_sigma_meso_height/2.0, m_sigma_meso_radius*m_sigma_meso_radius/2.0)

  # Create multilayer
  p_multi_layer = MultiLayer()
  n_air = complex(1.0, 0.0)
  n_substrate = complex(1.0-7.57e-6, 1.73e-7)

  p_air_material = MaterialManager.instance().addHomogeneousMaterial("Air", n_air)
  p_average_layer_material = MaterialManager.instance().addHomogeneousMaterial("Averagelayer", n_avg)
  p_substrate_material = MaterialManager.instance().addHomogeneousMaterial("Substrate", n_substrate)

  air_layer = Layer()
  air_layer.setMaterial(p_air_material);

  avg_layer = Layer()
  avg_layer.setMaterial(p_average_layer_material);
  avg_layer.setThickness(m_meso_height);

  substrate_layer = Layer()
  substrate_layer.setMaterial(p_substrate_material)
  p_interference_funtion = InterferenceFunctionNone()
  particle_decoration = ParticleDecoration()

  n_max_phi_rotation_steps = 180
  n_alpha_rotation_steps = 1

  alpha_step = 5.0*degree/n_alpha_rotation_steps
  alpha_start = - (n_alpha_rotation_steps/2.0)*alpha_step

  phi_step = 2.0*M_PI/3.0/n_max_phi_rotation_steps
  phi_start = 0.0
  for i in range(0, n_max_phi_rotation_steps):
    for j in range(0, n_alpha_rotation_steps):
      transform1 = RotateZ3D(phi_start + i*phi_step)
      transform2 = RotateY3D(alpha_start + j*alpha_step)
      p_total_transform = Transform3D(transform1)
      mesocrystal = createMesoCrystal(m_lattice_length_a, n_particle_adapted, ff_meso)
      particle_decoration.addParticle(mesocrystal, p_total_transform, m_meso_height)

  particle_decoration.setTotalParticleSurfaceDensity(surface_density)
  particle_decoration.addInterferenceFunction(p_interference_funtion)
  avg_layer_decorator = LayerDecorator(avg_layer, particle_decoration)

  roughness = LayerRoughness(m_roughness, 0.3, 500.0*nanometer)

  p_multi_layer.addLayer(air_layer)
  p_multi_layer.addLayer(avg_layer_decorator)
  p_multi_layer.addLayerWithTopRoughness(substrate_layer, roughness)

  print "Average layer index: ", n_avg
  print "Adapted particle index: ", n_particle_adapted
  print "Substrate layer index: ", n_substrate
  return p_multi_layer

# ---------------------------------------------------------------
# building sample, experiment, run calculations and plot output
# ---------------------------------------------------------------
def main():
  # building sample
  sample = BuildWholeSample()
  # running experiment
  ai=0.4
  experiment = GISASExperiment()
  experiment.setSample(sample)
  experiment.setDetectorParameters(256, 0.3*degree, 0.073, 256, -0.4*degree, 0.066) # phi, alpha
  experiment.setBeamParameters(1.77*angstrom, -ai*degree, 0.0*degree)
  experiment.setBeamIntensity(8e12)
  print "wait half of the minute..."
  experiment.runSimulation()
  experiment.normalize()

  # getting output data and making plots
  phi = GetOutputDataAxis(experiment, 0)
  alpha = GetOutputDataAxis(experiment, 1)
  output = GetOutputData(experiment) # [phi][alpha]

  phi = phi*180./3.1415926
  alpha = alpha*180./3.1415926
  output2 = output.swapaxes(0, 1)# to have [alpha][phi] ?
  #im=plt.imshow(output2, norm=LogNorm(100, 1e7))
  #plt.colorbar(im)
  #print( "showing" )
  #plt.show()

  fg = pylab.figure()
  xphi,yalpha = pylab.meshgrid(phi,alpha)
  pylab.pcolormesh(xphi,yalpha,output2,  norm=LogNorm(100, 1e+07) )
  pylab.ylim([alpha.min(),alpha.max()])
  pylab.xlim([phi.min(),phi.max()])
  pylab.colorbar()
  pylab.show()


  
#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  main()


