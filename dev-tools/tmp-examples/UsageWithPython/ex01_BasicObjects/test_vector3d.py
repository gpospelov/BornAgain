# Example demonstrates arithmetic with kvectors

import sys, os
from numpy import linspace, array, zeros
import pylab
from matplotlib.colors import LogNorm

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *


v1=kvector_t(1,0,0)
print v1

v2=kvector_t(0,1,0)
print v2

v3=0.5*v1+v2
print v3

v4=kvector_t(1,0,0)

t = Transform3D()
t = RotateZ3D(45.*degree)
v4.transform(t)
print v4