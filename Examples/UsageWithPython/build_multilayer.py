import sys, os
from numpy import linspace, array, zeros
import pylab

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', 'lib')))

from libScattCore import *

# ------------------------------------------------
#defining materials
matMng = MaterialManager.instance()
mAmbience = matMng.addHomogeneousMaterial("ambience", complex(1,0) )
mAg = matMng.addHomogeneousMaterial("ag1", complex(1.0-5e-6, 0) )
mCr = matMng.addHomogeneousMaterial("cr1", complex(1.0-10e-6, 0) )
mSubstrate = matMng.addHomogeneousMaterial("substrate", complex(1-15e-6,0) )

# ------------------------------------------------
#defining layers
lAmbience = Layer()
lAmbience.setMaterial(mAmbience, 0)

lAg = Layer()
lAg.setMaterial(mAg, 150.0*nanometer)

lCr = Layer()
lCr.setMaterial(mCr, 120.0*nanometer)

lSubstrate = Layer()
lSubstrate.setMaterial(mSubstrate, 0);

#defining roughness
roughness = LayerRoughness()
roughness.setSigma(1.0*nanometer);
roughness.setHurstParameter(0.3);
roughness.setLatteralCorrLength(5000*nanometer);

sample = MultiLayer()

sample.addLayer(lAmbience)
for i in range(0,2):
  sample.addLayerWithTopRoughness(lAg, roughness)
  sample.addLayerWithTopRoughness(lCr, roughness)

sample.addLayerWithTopRoughness(lSubstrate, roughness)

print sample

# ------------------------------------------------
# calculations
calculator = OpticalFresnel()

fresnelCoeff = OpticalFresnel.MultiLayerCoeff()

alpha=linspace(0., 2.0*degree, 2000)
ai = array(alpha)
rcoeff = zeros(ai.shape)

for i in range(0,len(ai)):
  kvec = kvector_t.LambdaAlphaPhi(1.54*angstrom, -ai[i], 0.0)
  calculator.execute(sample, kvec, fresnelCoeff)
  rcoeff[i]=abs(fresnelCoeff[0].R)
  print i, rcoeff[i]

fg = pylab.figure()
pylab.semilogy(ai, rcoeff)
pylab.show()

  