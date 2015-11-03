"""
Loading raw data (gzipped .tiff format) from GALAXI (Gallium Anode Low-Angle X-ray Instrument)
GALAXI is a small angle X-ray diffractometer operated in Forschungszentrum Juelich, Germany.

The geometry suggested to be standard GISAXS geometry: 
z axis points to the top, x and y are in the sample plane.
Detector z corresponds to alpha_f, detector y corresponds to phi_f.
"""

import sys, os, matplotlib, pylab
import numpy as np
from osgeo import gdal
from math import *
from bornagain import *


# parameters of the GISAXS experiment 
# detector geometry:
image_width = 981       # pixel
image_height = 1043     # pixel
wavelength = 0.1341     # nm
pixel_size = 0.172      # mm

# coordinates of the beam center
# should be defined for the particular experiment
beam_center_y = 597.1                   # pixel
beam_center_z = 323.4                   # pixel, from bottom
sample_detector_distance = 1730.0       # mm


def load_data(filename):
    """
    loads the data from .tif file to the numpy array data
    returns data
    """
    try:
        im = gdal.Open(os.path.join('/vsigzip', filename))
    except Exception as detail:
        print "Failed to open file ", filename
        print "Reason: ", detail
        print "Data are not loaded!"
    else:
        data = im.ReadAsArray()
        return data


def get_ai(data):
    """
    Tries to get ai from the given data array.
    Very simple algorithm, assumes that the specular peak has maximum intensity
    WARNING! May give wrong results depending on your data.
    """

    # make a slice along the specular line
    zslice = data[:, int(beam_center_y)]
    # find position of the specular peak
    p1 = np.argmax(zslice[:image_height - int(beam_center_z)])

    # calculate distance between the specular peak ang the beam center
    distance = abs(p1 - image_height + beam_center_z)   # in pixel
    d = distance * pixel_size            # to get distance in mm

    # calculate ai
    ai = degrees(0.5 * atan2(d, sample_detector_distance))
    return ai


# useful functions to calculate qy, qz and angles alpha_f and phi_f
# you may need to alter the equations is the geometry of your GISAXS experiment is different

def get_qz(pixno, ai):
    """
    returns qz value for Zpixel number 
    """
    arg = 2.0 * np.pi / wavelength
    qz = arg * (np.sin(np.arctan(((pixno - beam_center_z) * pixel_size) / sample_detector_distance) - radians(ai)) + np.sin(radians(ai)))

    return qz


def get_qy(pixno):
    """
    returns qy value for Ypixel number
    """
    arg = 2.0 * np.pi / wavelength
    qy = arg * np.sin(np.arctan(((pixno - beam_center_y) * pixel_size) / sample_detector_distance))
    return qy


def get_phif(ypixno):
    """
    returns phi_f = qy*wavelength/2pi
    """
    return degrees(0.5 * wavelength * get_qy(ypixno) / np.pi)


def get_af(zpixno, ai):
    """
    returns alpha_f = qz*wavelength/2pi - ai
    """
    return (degrees(0.5 * wavelength * get_qz(zpixno, ai) / np.pi) - ai)


def create_intensity_data_object(data, ai):
    """
    converts the whole raw data dataset to the IntensityData instance
    """
    idata = IntensityData()

    # create axes
    cols = np.arange(start=0, stop=image_width + 1, step=1, dtype=float)
    rows = np.arange(start=0, stop=image_height + 1, step=1, dtype=float)

    # Create two arrays of representing non-equidistant bin edges in phi_f, alpha_f space in radians.
    af_edges = [get_af(p, ai) * degree for p in rows]
    pf_edges = [get_phif(p) * degree for p in cols]

    idata.addAxis(VariableBinAxis("phi_f", image_width, pf_edges))
    idata.addAxis(VariableBinAxis("alpha_f", image_height, af_edges))

    a = np.flipud(data)
    idata.setRawDataVector(a.flatten(order='F').tolist())
    return idata


def plot_intensity_data(idata, fname=None):
    """
    plots the given intensity data instance
    if variable fname is set, plot image will be saved to the given file
    """
    result = idata.getArray() + 1  # for log scale
    axisphi = idata.getAxis(0)
    axisalpha = idata.getAxis(1)

    pylab.cla()
    pylab.clf()

    pylab.imshow(result, norm=matplotlib.colors.LogNorm(),
                 extent=[degrees(axisphi.getMin()), degrees(axisphi.getMax()), degrees(axisalpha.getMin()),
                         degrees(axisalpha.getMax())], aspect='auto')
    pylab.xlabel(r'$\phi_f$ [$^{\circ}$]', fontsize=18)
    pylab.ylabel(r'$\alpha_f$ [$^{\circ}$]', fontsize=18)
    pylab.setp(pylab.getp(pylab.gca(), 'xticklabels'), fontsize=14)
    pylab.setp(pylab.getp(pylab.gca(), 'yticklabels'), fontsize=14)
    ax = pylab.gca()
    ax.xaxis.set_label_coords(0.5, -0.05)

    pylab.colorbar()
    if fname:
        pylab.savefig(fname)

    pylab.show()


if __name__ == '__main__':
    f = "galaxi_raw_data.tif.gz"
    # load the data from the given file
    raw_data = load_data(f)
    alpha_i = get_ai(raw_data)
    print "Determined incident angle ai = ", alpha_i

    intensity_data = create_intensity_data_object(raw_data, alpha_i)
    # plot the intensity data object
    print "Plotting the whole dataset. Close plot to continue."
    plot_intensity_data(intensity_data)

    # sometimes it is useful to take only the part of the dataset
    print "Plotting the clipped dataset. "
    clip = IntensityDataFunctions.createClippedDataSet(intensity_data, 0.03 * degree, 0.0 * degree, 1.35 * degree,
                                                       1.2 * degree)
    plot_intensity_data(clip)

