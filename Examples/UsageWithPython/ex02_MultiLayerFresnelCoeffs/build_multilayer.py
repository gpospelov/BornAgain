# example showing how to build multi layer and calculate fresnel coefficients for set of alpha_i
import sys, os
from numpy import linspace, array, zeros
import pylab

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libScattCore import *

# ------------------------------------------------
# building sample
# ------------------------------------------------
# materials
matMng = MaterialManager.instance()
mAmbience = matMng.addHomogeneousMaterial("ambience", 1, 0 )
mAg = matMng.addHomogeneousMaterial("ag1", 1.0-5e-6, 0 )
mCr = matMng.addHomogeneousMaterial("cr1", 1.0-10e-6, 0 )
mSubstrate = matMng.addHomogeneousMaterial("substrate", 1-15e-6,0 )
# layers
lAmbience = Layer(mAmbience)
lAg = Layer(mAg, 150.0*nanometer)
lCr = Layer(mCr, 120.0*nanometer)
lSubstrate = Layer(mSubstrate, 0)
# defining roughness
roughness = LayerRoughness()
roughness.setSigma(1.0*nanometer);
roughness.setHurstParameter(0.3);
roughness.setLatteralCorrLength(5000*nanometer);
# building multi layer
sample = MultiLayer()
sample.addLayer(lAmbience)
for i in range(0,2):
  sample.addLayerWithTopRoughness(lAg, roughness)
  sample.addLayerWithTopRoughness(lCr, roughness)
sample.addLayerWithTopRoughness(lSubstrate, roughness)
sample.print_structure()

# ------------------------------------------------
# calculations
# ------------------------------------------------
# creating calculator
calculator = OpticalFresnel()
fresnelCoeff = OpticalFresnel.MultiLayerCoeff()
# creating grid of initial alpha
alpha=linspace(0., 2.0*degree, 2000)
ai = array(alpha)
rcoeff = zeros(ai.shape)
kvec = kvector_t()
for i in range(0,len(ai)):
  kvec.setLambdaAlphaPhi(1.54*angstrom, -ai[i], 0.0)
  calculator.execute(sample, kvec, fresnelCoeff)
  rcoeff[i]=abs(fresnelCoeff[0].R)

fg = pylab.figure()
pylab.semilogy(ai, rcoeff)
pylab.show()

  