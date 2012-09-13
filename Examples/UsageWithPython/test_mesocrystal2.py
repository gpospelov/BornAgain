#
# first meso crystal test
#
import sys, os
from numpy import linspace, array, zeros
import pylab
from matplotlib.colors import LogNorm
from math import pi as M_PI
from cmath import sqrt

import matplotlib.pyplot as plt

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', 'lib')))

from libScattCore import *



# ------------------------
# building mesocrystal
# ------------------------
R = 6.1*nanometer
meso_radius = 300*nanometer
surface_filling_ratio = 0.25
surface_density = surface_filling_ratio/M_PI/meso_radius/meso_radius
lattice = Lattice.createTrigonalLattice(R*2.0, R*2.0*2.3);
bas_a = lattice.getBasisVectorA()
bas_b = lattice.getBasisVectorB()
bas_c = lattice.getBasisVectorC()
n_particle = complex(1.0-1.55e-5, 1.37e-6)
avg_n_squared_meso = 0.7886*n_particle*n_particle + 0.2114;
n_avg = sqrt(surface_filling_ratio*avg_n_squared_meso + 1.0 - surface_filling_ratio)
n_particle_adapted = sqrt(n_avg*n_avg + n_particle*n_particle - 1.0)

sphere_ff = FormFactorFullSphere(R)
particle = Particle(n_particle_adapted, sphere_ff )

position_0 = kvector_t(0.0, 0.0, 0.0)
position_1 = kvector_t(0.0, 0.0, 0.0)
position_2 = kvector_t(0.0, 0.0, 0.0)

position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c);
position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c);
basis = LatticeBasis()
positions = [position_0, position_1, position_2 ]
basis.addParticle(particle, positions)

npc = Crystal(basis, lattice)
cylinder_ff = FormFactorCylinder(0.2*micrometer, meso_radius)
meso = MesoCrystal(npc, cylinder_ff )

pyramid_ff = FormFactorPyramid(0.2*micrometer, meso_radius, 84*degree)
meso2 = MesoCrystal(npc, pyramid_ff )



# ------------------------
# building multi layer
# ------------------------

multi_layer = MultiLayer()
n_air = complex(1.0, 0.0)
n_substrate = complex(1.0-7.57e-6, 1.73e-7)

matMng = MaterialManager.instance()
air_material = matMng.addHomogeneousMaterial("Air", n_air )
average_layer_material = matMng.addHomogeneousMaterial("Averagelayer", n_avg )
substrate_material = matMng.addHomogeneousMaterial("Substrate", n_substrate )

air_layer = Layer()
air_layer.setMaterial(air_material)

avg_layer = Layer()
avg_layer.setMaterial(average_layer_material, 0.2*micrometer)

substrate_layer = Layer()
substrate_layer.setMaterial(substrate_material)

interference_function = InterferenceFunctionNone()
particle_decoration = ParticleDecoration()

n_phi_rotation_steps = 1
n_alpha_rotation_steps =1
phi_step = 2*M_PI/3.0/n_phi_rotation_steps
alpha_step = 5*degree/n_alpha_rotation_steps

for i in range(0, n_phi_rotation_steps):
    for j in range(0, n_alpha_rotation_steps):
        transform1 = RotateZ3D(i*phi_step)
        transform2 = RotateZ3D(j*alpha_step)
        particle_decoration.addParticle(meso, transform1*transform2, 0.2*micrometer, 0.5)

particle_decoration.setTotalParticleSurfaceDensity(surface_density)
particle_decoration.addInterferenceFunction(interference_function)

avg_layer_decorator = LayerDecorator(avg_layer, particle_decoration)

multi_layer.addLayer(air_layer)
multi_layer.addLayer(avg_layer_decorator)
multi_layer.addLayer(substrate_layer)


# ------------------------
# build and run experiment
# ------------------------
ai=0.4
experiment = GISASExperiment()
experiment.setSample(multi_layer)
experiment.setDetectorParameters(100, 0.3*degree, 0.073, 100 , -0.4*degree, 0.066)
experiment.setBeamParameters(1.77*angstrom, -ai*degree, 0.0*degree)
experiment.setBeamIntensity(1e7)
experiment.runSimulation()
experiment.normalize()


# -------------------------------------
# getting output data and making plots
# -------------------------------------
#ndim = GetOutputDataNdimensions(experiment)
x = GetOutputDataAxis(experiment, 0)
y = GetOutputDataAxis(experiment, 1)
output = GetOutputData(experiment)

x = x*180./3.1415926
y = y*180./3.1415926

#fg = pylab.figure()
#Y,X = pylab.meshgrid(y,x)
#pylab.pcolormesh(X,Y,output,  norm=LogNorm(1, 1e7) )
#pylab.ylim([0,y.max()])
#pylab.xlim([0,x.max()])
#pylab.colorbar()
#pylab.show()

im=plt.imshow(output, norm=LogNorm(1, 1e7))
plt.colorbar(im)
print( "showing" )
plt.show()

