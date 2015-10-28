#!/usr/bin/env python
# Plots intensity data difference stored in BornAgain "*.int" or "*.int.gz" format
# Usage: python plot_intensity_data.py intensity_reference.int.gz intensity_other.int.gz

import numpy
import matplotlib
from matplotlib import pyplot as plt
from bornagain import *


def plot_intensity_data(ref, data):
    im = plt.imshow(data,
                    norm=matplotlib.colors.LogNorm(),
                    extent=[ref.getXmin()/deg, ref.getXmax()/deg, ref.getYmin()/deg, ref.getYmax()/deg],
                    aspect='auto')

    cb = plt.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    plt.show()


if __name__ == '__main__':
    if len(sys.argv)!=3:
        exit("Usage: python plot_intensity_data_diff.py intensity_reference.int.gz intensity_other.int.gz")

    intensity_ref = IntensityDataIOFactory.readIntensityData(sys.argv[1])
    intensity_other = IntensityDataIOFactory.readIntensityData(sys.argv[2])
    data = numpy.abs((intensity_ref.getArray() - intensity_other.getArray())/intensity_ref.getArray())
    plot_intensity_data(intensity_ref, data)
