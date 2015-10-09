"""
Loading raw data (gzipped ASCII format) from Maria reflectometer.

Maria is a reflectometer at FRM-II, with vertical sample orientation. The detector image is an array
of pixels [1024][1024]. Detector X corresponds to our alpha_f, detector Y corresponds to phi_f.

See ./maria_geometry.png
"""
import os
import sys
import pylab
import matplotlib
import numpy
import gzip
from bornagain import *


# coordinates of the detector center according to the instrument responsible
DETECTOR_ALPHA = 2.5*degree
DETECTOR_PHI = 0.4*degree
DETECTOR_DISTANCE = 1965.0  # in mm
NBINS_X = 1024
NBINS_Y = 1024
PIXEL_SIZE = 0.64   # in mm


def read_maria_data(fileName):
    """
    Reads zipped file with raw detector image data and returns numpy array.
    The file contains 1024 lines with 1024 amplitudes (in counts) in each line.
    """
    print "read_maria_data() -> Reading ", fileName
    fin = gzip.GzipFile(fileName)
    data = numpy.array([[int(val) for val in line.split()] for line in fin])
    return numpy.flipud(data)


def get_phif_alphaf_edges():
    """
    Returns two arrays of size [NBINS+1] representing non-equidistant bin edges in phi_f, alpha_f space in radians.

    The first element of the array phi_f_edges[0] corresponds to the left bound of first y-pixel, the last element of
    the array phi_f_edges[1024] corresponds to the right bound of the last y-pixel.
    """

    phi_f_edges = []
    for i_phi in range(0, NBINS_Y+1):
        center_y = NBINS_Y*PIXEL_SIZE/2.
        phi_f_edges.append(numpy.arctan2(i_phi*PIXEL_SIZE - center_y, DETECTOR_DISTANCE) + DETECTOR_PHI)

    alpha_f_edges = []
    for i_alpha in range(0, NBINS_X+1):
        center_x = NBINS_X*PIXEL_SIZE/2.
        alpha_f_edges.append(numpy.arctan2(i_alpha*PIXEL_SIZE - center_x, DETECTOR_DISTANCE) + DETECTOR_ALPHA)

    return phi_f_edges, alpha_f_edges


def create_intensity_data_object(raw_data):
    """
    Creates IntensityData object from numpy array with raw data.
    """
    phi_f_edges, alpha_f_edges = get_phif_alphaf_edges()
    result = IntensityData()
    result.addAxis(VariableBinAxis("phi_f", NBINS_Y, phi_f_edges))
    result.addAxis(VariableBinAxis("alpha_f", NBINS_X, alpha_f_edges))

    # Filling IntensityData object with raw data
    rotated_data = numpy.rot90(raw_data, 3)  # Maria is a vertical reflectometer, need to rotate the data
    result.setRawDataVector(rotated_data.flatten(order='F').tolist())
    return result


if __name__ == '__main__':

    # reading raw data
    raw_data = read_maria_data("maria_raw_data.gz")

    # creating IntensityData object
    intensity = create_intensity_data_object(raw_data)

    # plotting raw detector data
    pylab.figure("Raw data in X,Y space")
    im1 = pylab.imshow(raw_data, norm=matplotlib.colors.LogNorm(1, 1e+04), origin='lower', extent=[0, 1024, 0, 1024])
    pylab.colorbar(im1)
    pylab.xlabel("nbin_x", fontsize=16)
    pylab.ylabel("nbin_y", fontsize=16)

    # plotting intensity data object
    pylab.figure("Imported data in phi_f, alpha_f space")
    im = pylab.imshow(intensity.getArray(), norm=matplotlib.colors.LogNorm(),
                      extent=[intensity.getAxis(0).getMin(), intensity.getAxis(0).getMax(), intensity.getAxis(1).getMin(), intensity.getAxis(1).getMax()])
    pylab.colorbar(im)
    pylab.xlabel(r'$\phi_f, rad$', fontsize=16)
    pylab.ylabel(r'$\alpha_f, rad$', fontsize=16)

    # clipping the dataset
    clip = IntensityDataFunctions.createClippedDataSet(intensity, -5.0*degree, 0.0*degree, 5.0*degree, 5.0*degree)
    pylab.figure("Clipped dataset in phi_f, alpha_f space")
    im = pylab.imshow(clip.getArray(), norm=matplotlib.colors.LogNorm(), aspect='auto',
                      extent=[clip.getAxis(0).getMin(), clip.getAxis(0).getMax(), clip.getAxis(1).getMin(), clip.getAxis(1).getMax()])
    pylab.colorbar(im)
    pylab.xlabel(r'$\phi_f, rad$', fontsize=16)
    pylab.ylabel(r'$\alpha_f, rad$', fontsize=16)

    pylab.show()
