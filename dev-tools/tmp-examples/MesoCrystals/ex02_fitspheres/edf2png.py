#!/usr/bin/env python
#-*- coding: utf8 -*-

import edf_reader
from numpy import *
from pylab import *
from matplotlib.colors import LogNorm

DISTANCE=0.909 # m
PIX_SIZE=4*41.74e-6 # m
CENTER_X = 108.2
CENTER_Y = 942.0


def make_png(filename):
  data,info=edf_reader.import_edf_file(filename)
  file_title=info['Title'].split('(')[0]
  lamda=info['lambda'] # in A
  t=info['ExposureTime']
  data/=t
  
  if 'Center_1' in info:
    # ESRF Data
    xlim([-0.15,0.15])
    ylim([0.0,0.2])
    x=arange(info['xdim'])-info['Center_1']
    y=-arange(info['ydim'])+info['Center_2']
    phi=180./pi*arctan2(info['PSize_1']*x,info['SampleDistance'])
    tth=180./pi*arctan2(info['PSize_2']*y,info['SampleDistance'])
    data=maximum(data,1) # just for nicer plot
    norm=LogNorm(1,None)
  else:
    # Soleil Data
    xlim([0,0.3])
    ylim([0.0,0.3])
    x=arange(info['xdim'])-CENTER_X
    y=-arange(info['ydim'])+CENTER_Y
    phi=180./pi*arctan2(PIX_SIZE*x,DISTANCE)
    tth=180./pi*arctan2(PIX_SIZE*y,DISTANCE)
    norm=LogNorm(100,None)
    data=maximum(data,100) # just for nicer plot
  Q_y=4.*pi/lamda*sin(phi/360.*pi)
  Q_z=4.*pi/lamda*sin(tth/360.*pi)

  gca().set_aspect('equal')
  pcolormesh(Q_y,Q_z,data, norm=norm, cmap='gist_ncar')
  xlabel('$Q_y [\AA^{-1}]$')
  ylabel('$Q_z [\AA^{-1}]$')
  colorbar()
  title(file_title)
  savefig(filename.rsplit('.',1)[0]+'.png',dpi=300)
  close()

def run(args=None):
  for filename in args:
    print filename,'->', filename.rsplit('.',1)[0]+'.png'
    make_png(filename)

if __name__=='__main__':
  import sys
  if len(sys.argv)==1:
    exit('Usage: edf2png.py name1.edf name2.edf ...')
  run(sys.argv[1:])