#!/usr/bin/env python

# run isgisaxs and plot 2d map

import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt
from matplotlib.colors import LogNorm
import math
import os
import sys

if (len(sys.argv) > 1):
	filename = sys.argv[1]
print( "loading" )
a=np.loadtxt(filename)
#b=a/a.flatten().max()
b=a
factor=1
if (len(sys.argv) > 2):
	normfile = sys.argv[2]
	normb=np.loadtxt(normfile)
	factor=np.sum(normb)/np.sum(b)
print b.shape
print b.flatten().min()
print b.flatten().max()
b=factor*b
print b.flatten().min()
print b.flatten().max()
#b=np.log10(b+1)
print( "plotting" )
bmax=b.flatten().max()
bmean=np.sum(b)/b.size
bminplot=bmean**2/bmax
#im=plt.imshow(b)
b=b+1
im=plt.imshow(b, norm=LogNorm())
plt.colorbar(im)
print( "showing" )
plt.show()
