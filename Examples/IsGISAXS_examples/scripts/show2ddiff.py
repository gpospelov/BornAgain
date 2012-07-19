#!/usr/bin/env python

# run isgisaxs and plot 2d map

import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt
import math
import os
import sys

if (len(sys.argv) < 3):
	exit()
file_a = sys.argv[1]
file_b = sys.argv[2]
print( "loading" )
a=np.loadtxt(file_a)
b=np.loadtxt(file_b)
print( "normalizing" )
#maxa=a.flatten().max()
#maxb=b.flatten().max()
#factor=maxa/maxb
#b=factor*b
print( "Taking logarithm" )
#a=np.log10(a+1)
#b=np.log10(b+1)
print( "Calculating difference" )
diff=100*(a-b)/(b+0.001)
#diff=a-b
print( "plotting" )
im=plt.imshow(diff)
plt.colorbar(im)
print( "showing" )
plt.show()
