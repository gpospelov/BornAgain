#
# Rotated pyramids without interference on top of substrate (isgisaxs9 example)
#
import sys, os
from numpy import linspace, array, zeros
import pylab
from matplotlib.colors import LogNorm

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libScattCore import *


# ------------------------
# building sample
# ------------------------

# defining materials
n_air = complex(1.0, 0.0)
n_substrate = complex(1.0-6e-6, 2e-8)
n_particle = complex(1.0-6e-4, 2e-8)

matMng = MaterialManager.instance()
mAmbience = matMng.addHomogeneousMaterial("ambience", n_air )
mSubstrate = matMng.addHomogeneousMaterial("substrate", n_substrate )

# building two layers
air_layer = Layer()
air_layer.setMaterial(mAmbience, 0)

substrate = Layer()
substrate.setMaterial(mSubstrate, 0)

# creating rotated nanoparticle
pyramid_ff = FormFactorPyramid(5*nanometer, 5*nanometer, 54.73*deg)
pyramid = Particle(n_particle, pyramid_ff)
angle_around_z = 45.*degree
transform = RotateZ3D(angle_around_z)

# creating collection of nano particles
nanopart_collection = ParticleDecoration()
nanopart_collection.addParticle(pyramid, transform)
interference = InterferenceFunctionNone()
nanopart_collection.addInterferenceFunction(interference);

# creating layer with nano particles
air_layer_with_nanoparticles = LayerDecorator(air_layer, nanopart_collection)

# creating final multi-layer sample
multi_layer = MultiLayer()
multi_layer.addLayer(air_layer_with_nanoparticles)
multi_layer.addLayer(substrate)


# ------------------------
# build and run experiment
# ------------------------
experiment = GISASExperiment()
experiment.setDetectorParameters(100, 0.0*degree, 2.0*degree, 100, 0.0*degree, 2.0*degree, True)
experiment.setBeamParameters(1.0*angstrom, -0.2*degree, 0.0*degree)

experiment.setSample(multi_layer)

experiment.runSimulation()


# -------------------------------------
# getting output data and making plots
# -------------------------------------
#ndim = GetOutputDataNdimensions(experiment)
x = GetOutputDataAxis(experiment, 0)
y = GetOutputDataAxis(experiment, 1)
output = GetOutputData(experiment)

x = x*180./3.1415926
y = y*180./3.1415926

fg = pylab.figure()
Y,X = pylab.meshgrid(y,x)
pylab.pcolormesh(X,Y,output,  norm=LogNorm(0.1, 1e+05) )
pylab.ylim([0,y.max()])
pylab.xlim([0,x.max()])
pylab.colorbar()
pylab.show()


