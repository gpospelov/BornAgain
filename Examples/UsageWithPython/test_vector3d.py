import sys, os
from numpy import linspace, array, zeros
import pylab
from matplotlib.colors import LogNorm

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', 'lib')))

from libScattCore import *


v1=vector3d_t(1,0,0)
print v1

v2=vector3d_t(0,1,0)
print v2

v3=0.5*v1+v2
print v3

t = transform3d_t()
print t