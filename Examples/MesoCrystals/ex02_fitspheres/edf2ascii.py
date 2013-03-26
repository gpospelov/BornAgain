#!/usr/bin/env python
#
# Convert edf data to text files to load into OutputData from GISASFW 

import edf_reader
from numpy import *
from pylab import *
from matplotlib.colors import LogNorm
import gzip

DISTANCE=0.909 # m
PIX_SIZE=4*41.74e-6 # m
CENTER_X = 108.2
CENTER_Y = 942.0


#-----------------------------------------------------------------------------
# saving 3 numpy arrays in text file
# 1D array with x-values (position of columns) as single line
# 1D array with y-values (position of rows) as single line
# 2D data array where single line represent second dimension [nrows][ncols]
#-----------------------------------------------------------------------------
#def save_text_file(filename, cols, rows, data):
  #if ".gz" in filename:
    #f = gzip.open(filename, 'wb')
  #else:
    #f = file(filename, 'w')
  #f.write("# 2D scattering data\n")
  ## writing header containing the shape of array
  #header = "# shape"
  #for ndim in range(0,len(data.shape)):
      #header += " " + str(data.shape[ndim])
  #f.write(header+"\n")
  ## writing x-axis values
  #f.write("# x-axis \n")
  #savetxt(f, cols, fmt='%1.10e', delimiter=" ", newline=" ")
  #f.write("\n")
  ## writing y-axis values
  #f.write("# y-axis \n")
  #savetxt(f, rows, fmt='%1.10e', delimiter=" ", newline=" ")
  #f.write("\n")

  ## writing data array
  #f.write("# data\n")
  #savetxt(f, data, fmt='%1.10e', delimiter=" ", newline="\n")
  #f.close()


#-----------------------------------------------------------------------------
# here we've got data[theta][phi]
# We have to invert to BornAgain convention [phi][theta]
# saving 3 numpy arrays in text file
# 1D array with x-values (position of columns) as single line
# 1D array with y-values (position of rows) as single line
# 2D data array where single line represent second dimension [nrows][ncols]
#-----------------------------------------------------------------------------
def save_text_file2(filename, phi, theta, data):
  if ".gz" in filename:
    f = gzip.open(filename, 'wb')
  else:
    f = file(filename, 'w')
  f.write("# 2D scattering data\n")
  # writing header containing the shape of array
  # !!!
  data = data.transpose()

  header = "# shape"
  for ndim in range(0,len(data.shape)):
      header += " " + str(data.shape[ndim])
  f.write(header+"\n")
  # writing x-axis values
  f.write("# 0-axis [phi] \n")
  savetxt(f, phi, fmt='%1.10e', delimiter=" ", newline=" ")
  f.write("\n")
  # writing y-axis values
  f.write("# 1-axis [theta] \n")
  savetxt(f, theta, fmt='%1.10e', delimiter=" ", newline=" ")
  f.write("\n")

  # writing data array
  f.write("# data\n")
  savetxt(f, data, fmt='%1.10e', delimiter=" ", newline="\n")
  f.close()




#-----------------------------------------------------------------------------
# modifying 3 arrays (rows, cols and data) to fit in the range rmin, rmax, cmin, cmax
# input:
# cols - 1d array with points on x-axis; cmin, cmax - the interval of interest on this axis
# rows - 1d array with points on y-axis; rmin, rmax - the interval of interest on this axis
# data[ len(rows) ][ len(cols) ] - 2D array with data points
# output:
# the output of the function will be 3 reduced arrays
# newrows - 1d arrays without values outside (rmin, rmax)
# newcols - 1d arrays without values outside (cmin, cmax)
# newdata - corresponding reduced 2d array with data points
#-----------------------------------------------------------------------------
def modify_arrays(cols, rows, data, cmin, cmax, rmin, rmax):

  # check if x,y-arrays in ascending order
  if not all(rows[:-2] < rows[1:-1]):
      exit("rows is not in ascending order")
  if not all(cols[:-2] < cols[1:-1]):
      print cols
      exit("cols is not in ascending order")
  # create x and y arrays with masked values outside required range
  masked_rows = ma.masked_outside(rows, rmin, rmax)
  masked_cols = ma.masked_outside(cols, cmin, cmax)
  # create 2d mask on data
  mask_on_data = ma.getmask(masked_rows[:,None]*masked_cols[None,:])
  # apply mask to 2d data
  masked_data = ma.masked_array(data, mask_on_data)
  # collapsing masked values
  newrows = ma.compressed(masked_rows)
  newcols = ma.compressed(masked_cols)
  newdata=ma.compressed(masked_data).reshape(len(newrows), len(newcols))
  return newcols, newrows, newdata


#-----------------------------------------------------------------------------
# for testing two functions above
#-----------------------------------------------------------------------------
def test_array_masking():
  dd = array([[ 0,  1,  2,  3,  4],
              [ 5,  6,  7,  8,  9],
              [10, 11, 12, 13, 14]])
  xx = array([0.0, 1.0, 2.0, 3.0, 4.0])
  yy = array([0.0,0.5,10.0])
  print "--- before"
  print xx
  print yy
  print dd
  xmin = 0.9
  xmax = 3.9
  ymin = 0.1
  ymax = 11.0
  newxx, newyy, newdd = modify_arrays(xx,yy,dd, xmin, xmax, ymin, ymax)
  print "--- after applying xmin, xmax:", xmin, xmax, " umin, ymax:",ymin, ymax
  print newxx
  print newyy
  print newdd
  save_text_file('tmp.txt', newxx, newyy, newdd)
  #save_text_file('tmp.txt', xx, yy, dd)


#-----------------------------------------------------------------------------
# converting edf data to another formats
# (png, txt) for the moment
#-----------------------------------------------------------------------------
def make_file(filename):
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

  #inverting Q_z to have values in ascending order
  Q_z=Q_z[ ::-1]
  data=data[ ::-1,:]

  # The grid orientation follows the MATLAB convention: an array C with shape (nrows, ncolumns) is plotted 
  # with the column number as X and the row number as Y, increasing up; hence it is plotted the way the 
  # array would be printed, except that the Y axis is reversed.
  # e.g. here we have data[Qz][Qy] (data[theta][phi])

  # ---
  # to save png file
  gca().set_aspect('equal')
  pcolormesh(Q_y,Q_z,data, norm=norm, cmap='gist_ncar')
  xlabel('$Q_y [\AA^{-1}]$')
  ylabel('$Q_z [\AA^{-1}]$')
  colorbar()
  title(file_title)
  savefig(filename.rsplit('.',1)[0]+'.png',dpi=300)
  close()

  # test_array_masking
  #test_array_masking()

  # data .vs. qy,qz
  newqy, newqz, newdata = modify_arrays(Q_y, Q_z, data, 0.0, 0.3, 0.0, 0.3)
  #save_text_file(filename.rsplit('.',1)[0]+'_qyqz.txt.gz', newqy, newqz, newdata)

  # data .vs. phi,theta
  phi = phi/180.*pi
  tth=(tth-0.32)/180.*pi
  tth=tth[ ::-1]
  newphi, newtheta, newdata2 = modify_arrays(phi, tth, data, 0.02, 0.06, 0.0, 0.04)
  #save_text_file(filename.rsplit('.',1)[0]+'_phitheta.txt.gz', newphi, newtheta, newdata2)
  
  gca().set_aspect('equal')
  pcolormesh(newphi,newtheta, newdata2, norm=norm, cmap='gist_ncar')
  xlabel('$Q_y [\AA^{-1}]$ (phi)')
  ylabel('$Q_z [\AA^{-1}]$ (theta)')
  colorbar()
  title(file_title)
  savefig('tmp.png',dpi=300)
  close()
  
  save_text_file2(filename.rsplit('.',1)[0]+'_phitheta.txt.gz', newphi, newtheta, newdata2)


#-----------------------------------------------------------------------------
# run()
#-----------------------------------------------------------------------------
def run(args=None):
  for filename in args:
    print filename,'->', filename.rsplit('.',1)[0]+'.png'
    make_file(filename)


#-----------------------------------------------------------------------------
# main()
#-----------------------------------------------------------------------------
if __name__=='__main__':
  import sys
  if len(sys.argv)==1:
    exit('Usage: edf2png.py name1.edf name2.edf ...')
  run(sys.argv[1:])

