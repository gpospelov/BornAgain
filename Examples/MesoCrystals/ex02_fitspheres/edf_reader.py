#-*- coding: utf8 -*-
import os
import sys
from numpy import *

h_c=1.23984193*1e-6/1e-10

def read_edf_header(file_handler):
  '''
    Read the header of an edf file from an open file object.
  '''
  line=file_handler.readline()
  header_lines=[]
  settings={}
  # Set standart values which are overwritten if found in the header
  while '}' not in line:
    if "=" in line:
      key, value=line.split('=', 1)
      key=key.strip()
      value=value.strip().rstrip(';').strip()
      settings[key]=value
    #header_lines.append(line)
    line=file_handler.readline()
  header_lines.append(line)
  # Read some settings
  if 'Dim_1' in settings:
    settings['xdim']=int(settings['Dim_1'])
  if 'Dim_2' in settings:
    settings['ydim']=int(settings['Dim_2'])
  if 'Distance_sample-detector' in settings:
    settings['Distance_sample-detector']=float(settings['Distance_sample-detector'].rstrip('mm'))
  if 'SampleDistance' in settings:
    settings['SampleDistance']=float(settings['SampleDistance'].rstrip('m'))*1000.
  if 'Monochromator_energy' in settings:
    energy=float(settings['Monochromator_energy'].rstrip('keV'))*1000.
    print "XXX",energy
    settings['lambda']=h_c/energy
  if  'WaveLength' in settings:
    settings['lambda']=float(settings['WaveLength'].rstrip('m'))*1e10
  if 'Exposure_time' in settings:
    settings['Exposure_time']=float(settings['Exposure_time'].rstrip('ms'))/1000.
  if 'ExposureTime' in settings:
    settings['ExposureTime']=float(settings['ExposureTime'].rstrip('s (Seconds)'))
  if 'NormalizationFactor' in settings:
    settings['NormalizationFactor']=float(settings['NormalizationFactor'])
  if 'Center_1' in settings:
    settings['Center_1']=float(settings['Center_1'].rstrip('pixel'))
  if 'Center_2' in settings:
    settings['Center_2']=float(settings['Center_2'].rstrip('pixel'))
  if 'PSize_1' in settings:
    settings['PSize_1']=float(settings['PSize_1'].rstrip('m'))*1e3
  if 'PSize_2' in settings:
    settings['PSize_2']=float(settings['PSize_2'].rstrip('m'))*1e3
  return settings

def import_edf_file(file_name):
  '''
    Read the header and data from one edf file.
    
    :return: array of the data and the header information.
  '''
  #  check if file is in gzip format
  if file_name.endswith('.gz'):
    file_handler=gzip.open(file_name, 'rb')
  else:
    file_handler=open(file_name, 'rb')
  # read file header information
  header_settings=read_edf_header(file_handler)
  if header_settings['DataType']=='UnsignedShort':
    # load data as binary integer values
    input_array=array_module.array('H')
    input_array=fromstring(file_handler.read(header_settings['xdim']*header_settings['ydim']*2), 
                           uint16).astype(float)
    input_array-=-200
  elif header_settings['DataType']=='SignedInteger':
    # load data as binary integer values
    input_array=fromstring(file_handler.read(header_settings['xdim']*header_settings['ydim']*2), 
                           int16).astype(float)
  elif header_settings['DataType']=='FloatValue':
    # load data as binary integer values
    input_array=fromstring(file_handler.read(header_settings['xdim']*header_settings['ydim']*4), 
                           float32)
    input_array=maximum(0., input_array)
  else:
    raise IOError, 'Unknown data format in header: %s'%header_settings['DataType']
  file_handler.close()
  return input_array.reshape(header_settings['ydim'], header_settings['xdim']), header_settings


def main():
  if len(sys.argv)!=2:
    print "Usage: 'python edf_reader.py FileName' "
    print " "

  else:
    data=import_edf_file( sys.argv[1] )
    print data[1]
    print data[0].shape
    #savetxt("foo.csv.gz", data[0], fmt='%1.10e', delimiter=" ")




#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  main()

